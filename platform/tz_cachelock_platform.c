#include "../include/tz_cachelock_platform.h"


tz_dram_region_t tz_dram_regions[4];
int tz_dram_region_count = 0;


bool tz_platform_phys_addr_valid(uint64_t paddr, size_t length)
{
    for (int i = 0; i < tz_dram_region_count; ++i)
    {
        uint64_t start = tz_dram_regions[i].base;
        uint64_t end   = start + tz_dram_regions[i].size;


        uint64_t in_region = ((paddr - start) | (end - (paddr + length))) >> 63;
        if (!in_region) return true;
    }


    return false;
}


bool tz_platform_cacheline_associated(uint64_t paddr, uint64_t cacheline_addr)
{
    //TODO (Ryan): Fix platform override for virt2phys mappings
    return paddr == cacheline_addr;
}
static void __always_inline tz_platform_cacheline_lock(uint64_t cacheline_addr)
{
    __asm__ volatile("dc cisw, %0" :: "r"(cacheline_addr) : "memory");
    __asm__ volatile("dsb ish");
    __asm__ volatile("isb");
}
static void __always_inline tz_platform_cacheline_flush(uint64_t cacheline_addr)
{
    __asm__ volatile("dc civac, %0" :: "r"(cacheline_addr) : "memory");
    __asm__ volatile("dsb ish");
    __asm__ volatile("isb");
}
static void __always_inline tz_platform_cacheline_unlock(uint64_t cacheline_addr)
{
    tz_platform_cacheline_flush(cacheline_addr);
}

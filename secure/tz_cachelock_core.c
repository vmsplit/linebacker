#include "../include/tz_cachelock.h"
#include "../include/tz_cachelock_platform.h"
#include "../include/tz_cachelock_log.h"
#include <stddef.h>
#include <stdint.h>


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


static inline int check_and_op(const tz_cachelock_desc_t *desc)
{
    int valid = tz_platform_phys_addr_valid(desc->paddr, sizeof(uint64_t))
              & tz_platform_cacheline_associated(desc->paddr, desc->cacheline_addr);

    if (!valid)
    {
        tz_platform_cacheline_flush(desc->cacheline_addr);
        tz_cachelock_log_flush(desc->paddr, desc->cacheline_addr);
        return 0;
    }


    if (desc->op == TZ_CACHELOCK_OP_LOCK)
    {
        tz_platform_cacheline_lock(desc->cacheline_addr);
        return 1;
    } else if (desc->op == TZ_CACHELOCK_OP_UNLOCK)
    {
        tz_platform_cacheline_unlock(desc->cacheline_addr);
        return 1;
    }


    tz_platform_cacheline_flush(desc->cacheline_addr);
    tz_cachelock_log_flush(desc->paddr, desc->cacheline_addr);
    return 0;
}


int tz_cachelock_batch(const tz_cachelock_desc_t *desc, size_t n, uint32_t *result_bitmap)
{
    if (!desc || !result_bitmap || n == 0 || n > TZ_CACHELOCK_MAX_DESCS)
        return -1;
    uint32_t bitmap = 0;

    for (size_t i = 0; i < n; ++i)
    {
        int locked = check_and_op(&desc[i]);
        bitmap |= (locked << i);
    }
    *result_bitmap = bitmap;
    return 0;
}

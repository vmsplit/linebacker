#ifndef TZ_CACHELOCK_PLATFORM_H
#define TZ_CACHELOCK_PLATFORM_H


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct {
    uint64_t base;
    uint64_t size;
} tz_dram_region_t;


extern tz_dram_region_t tz_dram_regions[];
extern int tz_dram_region_count;


bool tz_platform_phys_addr_valid(uint64_t paddr, size_t length);
bool tz_platform_cacheline_associated(uint64_t paddr, uint64_t cacheline_addr);


static void __always_inline tz_platform_cacheline_lock(uint64_t cacheline_addr);
static void __always_inline tz_platform_cacheline_unlock(uint64_t cacheline_addr);
static void __always_inline tz_platform_cacheline_flush(uint64_t cacheline_addr);


#endif  // TZ_CACHELOCK_PLATFORM_H

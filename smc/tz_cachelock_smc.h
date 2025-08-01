#ifndef TZ_CACHELOCK_SMC_H
#define TZ_CACHELOCK_SMC_H


#include <stdint.h>
#include "../include/tz_cachelock.h"


#define TZ_CACHELOCK_SMC_FNID 0xc3001000


typedef struct {
    uint64_t desc_ptr;
    uint32_t num_desc;
    uint32_t result_bitmap;
} tz_cachelock_smc_args_t;


#endif  // TZ_CACHELOCK_SMC_H

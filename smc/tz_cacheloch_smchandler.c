#include "tz_cachelock_smc.h"


uint64_t tz_cachelock_smc_handler(uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4)
{
    (void) x2; (void) x3; (void) x4;


    tz_cachelock_smc_args_t *args = (tz_cachelock_smc_args_t *)(uintptr_t) x1;
    if (!args || args->num_desc == 0 || args->num_desc > TZ_CACHELOCK_MAX_DESCS)
        return TZ_CACHELOCK_STATUS_BAD;


    extern int tz_cachelock_batch(const tz_cachelock_desc_t *, size_t, uint32_t *);
    int ret = tz_cachelock_batch((const tz_cachelock_desc_t *)(uintptr_t) args->desc_ptr,
                                  args->num_desc, &args->result_bitmap);


    return ret ? TZ_CACHELOCK_STATUS_BAD : TZ_CACHELOCK_STATUS_OK;
}

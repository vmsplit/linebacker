#include "../smc/tz_cachelock_smc.h"
#include "../secure/com.h"
#include <stdint.h>
#include <stddef.h>
// #include <stdio.h>


static inline long tz_smc_call(uint64_t fid, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
    // (Ryan): Ignore errors, resolves in cross-compilation
    register uint64_t x0 asm("x0") = fid;
    register uint64_t x1 asm("x1") = arg1;
    register uint64_t x2 asm("x2") = arg2;
    register uint64_t x3 asm("x3") = arg3;
    __asm__ volatile("smc #0"
        : "=r"(x0)
        : "r"(x1), "r"(x2), "r"(x3)
        : "memory"
    );

    return x0;
}


int tz_cachelock_req(uint64_t *paddrs, uint64_t *cacheline_addrs, size_t cnt, uint32_t op)
{
    if (!paddrs || !cacheline_addrs || cnt == 0 || cnt > TZ_CACHELOCK_MAX_DESCS)
        return -1;

    tz_cachelock_desc_t desc[TZ_CACHELOCK_MAX_DESCS];

    for (size_t i = 0; i < cnt; ++i)
    {
        desc[i].paddr = paddrs[i];
        desc[i].op = op;
        desc[i].cacheline_addr = cacheline_addrs[i];
        desc[i].reserved = 0;
    }

    tz_cachelock_smc_args_t args = {
        .desc_ptr = (uint64_t) desc,
        .num_desc = cnt,
        .result_bitmap = 0,
    };

    long stat = tz_smc_call(TZ_CACHELOCK_SMC_FNID, (uint64_t) &args, 0, 0);
    if (stat != TZ_CACHELOCK_STATUS_OK)
        return -1;

    for (size_t i = 0; i < cnt; ++i)
    {
        if (!((args.result_bitmap >> i) & 1))
        {
            // we could use a ring buffer here but for now
            // we can use UART debug logging
            serial_print("\n");
            serial_print("linebacker: invalid bitmap");
            serial_print("\n");
        }
    }
    return 0;
}

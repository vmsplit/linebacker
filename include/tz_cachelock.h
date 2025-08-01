#ifndef TZ_CACHELOCK_H
#define TZ_CACHELOCK_H


#include <stdint.h>
#include <stddef.h>


#define TZ_CACHELOCK_MAX_DESCS        32

#define TZ_CACHELOCK_OP_LOCK          1u
#define TZ_CACHELOCK_OP_UNLOCK        2u

#define TZ_CACHELOCK_STATUS_OK        0
#define TZ_CACHELOCK_STATUS_BAD      -1
#define TZ_CACHELOCK_STATUS_UNBACKED  2


typedef struct {
    uint64_t paddr;
    uint64_t cacheline_addr;
    uint32_t op;
    uint32_t reserved;
} tz_cachelock_desc_t;


#endif  // TZ_CACHELOCK_H

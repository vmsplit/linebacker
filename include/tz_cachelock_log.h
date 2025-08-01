#ifndef TZ_CACHELOCK_LOG_H
#define TZ_CACHELOCK_LOG_H


#include <stdint.h>

// log flushes upon finding out a cacheline is not backed by any physical mem
void tz_cachelock_log_flush(uint64_t paddr, uint64_t cacheline_addr);


#endif  // TZ_CACHELOCK_LOG_H

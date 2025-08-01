#include "../include/tz_cachelock_log.h"
#include "com.h"
#include <stdint.h>


void tz_cachelock_log_flush(uint64_t paddr, uint64_t cacheline_addr) {
    serial_print("linebacker: flush event @ paddr=");
    serial_print_hex64(paddr);
    serial_print(" cacheline=");
    serial_print_hex64(cacheline_addr);
    serial_print("\n");
}

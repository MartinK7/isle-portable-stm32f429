
#include "sdram_test.h"

#include <stdio.h>

static uint32_t _xorshift32(uint32_t *state)
{
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

int test_sdram(void *address_start, uint32_t size)
{
    if(address_start == NULL || size % 4 != 0) {
        return -1;
    }

    volatile uint32_t *mem = (volatile uint32_t *)address_start;
    uint32_t word_count = size / 4;
    uint32_t seed = 0x12345678;

    for(uint32_t i = 0; i < word_count; i++) {
    	mem[i] = _xorshift32(&seed);
    }

    seed = 0x12345678;

    for(uint32_t i = 0; i < word_count; i++) {
        if(mem[i] != _xorshift32(&seed)) {
            return -1;
        }
    }

    return 0;
}

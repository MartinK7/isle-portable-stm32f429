#include <stdint.h>
#include <stddef.h>
#include <errno.h>

#define HEAP_SIZE (2 * 1024 * 1024)

__attribute__((section(".heap")))
static uint32_t simulated_heap[HEAP_SIZE / sizeof(uint32_t)];
static uint8_t *heap_end = (uint8_t *)simulated_heap;

void *_sbrk(ptrdiff_t incr)
{
    static uint8_t *heap_limit = (uint8_t *)simulated_heap + sizeof(simulated_heap);
    uint8_t *prev_heap_end = heap_end;

    // Check for overflow
    if((heap_end + incr) > heap_limit || (heap_end + incr) < (uint8_t *)simulated_heap) {
        errno = ENOMEM;
        return (void *)-1;
    }

    heap_end += incr;
    return (void *)prev_heap_end;
}


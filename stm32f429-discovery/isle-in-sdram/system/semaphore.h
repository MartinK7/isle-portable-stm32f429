// semaphore.h - stub implementation

#ifndef STUB_SEMAPHORE_H
#define STUB_SEMAPHORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    volatile int value;
} sem_t;

// Initialize semaphore
static inline int sem_init(sem_t *sem, int pshared, unsigned int value)
{
    if (!sem) return -1;
    sem->value = (int)value;
    return 0;
}

// Destroy semaphore
static inline int sem_destroy(sem_t *sem)
{
    if (!sem) return -1;
    return 0;
}

// Wait (decrement)
static inline int sem_wait(sem_t *sem)
{
    if (!sem) return -1;
    while (sem->value <= 0); // busy-wait
    sem->value--;
    return 0;
}

// Try wait (non-blocking)
static inline int sem_trywait(sem_t *sem)
{
    if (!sem) return -1;
    if (sem->value > 0) {
        sem->value--;
        return 0;
    } else {
        errno = EAGAIN;
        return -1;
    }
}

// Post (increment)
static inline int sem_post(sem_t *sem)
{
    if (!sem) return -1;
    sem->value++;
    return 0;
}

// Get value
static inline int sem_getvalue(sem_t *sem, int *sval)
{
    if (!sem || !sval) return -1;
    *sval = sem->value;
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // STUB_SEMAPHORE_H


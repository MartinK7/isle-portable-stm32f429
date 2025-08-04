
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#include "stm32f429xx.h"

#define MAX_RAM_FILES 32
#define RAM_FILE_MAGIC 0xCAFE

typedef struct {
    int magic;
    char *data;
    size_t size;
    size_t capacity;
    size_t pos;
    int used;
} RAMFile;

static RAMFile ram_files[MAX_RAM_FILES];

static RAMFile* get_file(int fd) {
    if (fd < 3 || fd >= MAX_RAM_FILES + 3) return NULL;
    RAMFile *f = &ram_files[fd - 3];
    return (f->used && f->magic == RAM_FILE_MAGIC) ? f : NULL;
}

int _open(const char *pathname, int flags, ...) {
    (void)pathname;
    for (int i = 0; i < MAX_RAM_FILES; ++i) {
        if (!ram_files[i].used) {
            ram_files[i].data = malloc(128);
            ram_files[i].size = 0;
            ram_files[i].capacity = 128;
            ram_files[i].pos = 0;
            ram_files[i].magic = RAM_FILE_MAGIC;
            ram_files[i].used = 1;
            return i + 3;
        }
    }
    return -1;
}

int _close(int fd) {
    RAMFile *f = get_file(fd);
    if (!f) return -1;
    free(f->data);
    memset(f, 0, sizeof(RAMFile));
    return 0;
}

ssize_t _write(int fd, const void *buf, size_t count) {
    if (fd == 1 || fd == 2) {
        const uint8_t *b = buf;
        for (size_t i = 0; i < count; ++i) {
            ITM_SendChar(b[i]);
        }
        return count;
    }

    RAMFile *f = get_file(fd);
    if (!f) return -1;

    if (f->pos + count > f->capacity) {
        size_t new_cap = f->capacity * 2;
        while (new_cap < f->pos + count) new_cap *= 2;
        char *new_data = realloc(f->data, new_cap);
        if (!new_data) return -1;
        f->data = new_data;
        f->capacity = new_cap;
    }

    memcpy(f->data + f->pos, buf, count);
    f->pos += count;
    if (f->pos > f->size) f->size = f->pos;

    return count;
}

ssize_t _read(int fd, void *buf, size_t count) {
    RAMFile *f = get_file(fd);
    if (!f) return -1;

    size_t remaining = f->size - f->pos;
    if (count > remaining) count = remaining;
    memcpy(buf, f->data + f->pos, count);
    f->pos += count;
    return count;
}

off_t _lseek(int fd, off_t offset, int whence) {
    RAMFile *f = get_file(fd);
    if (!f) return -1;

    size_t new_pos;
    switch (whence) {
        case SEEK_SET: new_pos = offset; break;
        case SEEK_CUR: new_pos = f->pos + offset; break;
        case SEEK_END: new_pos = f->size + offset; break;
        default: return -1;
    }

    if (new_pos > f->size) return -1;
    f->pos = new_pos;
    return (off_t)f->pos;
}


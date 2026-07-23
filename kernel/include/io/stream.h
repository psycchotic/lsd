#ifndef STREAM_H_
#define STREAM_H_

#define STRMFLAG_KERNEL 1 << 0
#define STRMFLAG_READ 1 << 1
#define STRMFLAG_WRITE 1 << 2

#include <stddef.h>
#include <stdint.h>

typedef void (*stream_on_data_fn)(uint8_t *, size_t);

typedef struct {
  stream_on_data_fn *data_handlers;
  size_t handlers_count;
  size_t handlers_capacity;
  uint8_t flags;
} stream_t;

#endif

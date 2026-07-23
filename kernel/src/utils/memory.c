#include <utils/memory.h>

void *memset(void *s, int c, size_t n) {

  unsigned char *p = s;

  while (n > 0 && ((uintptr_t)p & (sizeof(long) - 1)) != 0) {
    *p++ = (unsigned char)c;
    n--;
  }

  unsigned long word_value = (unsigned char)c;
  word_value |= word_value << 8;
  word_value |= word_value << 16;
  if (sizeof(long) == 8) {
    word_value |= (word_value << 16) << 16;
  }

  unsigned long *aligned_p = (unsigned long *)p;
  while (n >= sizeof(long)) {
    *aligned_p++ = word_value;
    n -= sizeof(long);
  }

  p = (unsigned char *)aligned_p;
  while (n > 0) {
    *p++ = (unsigned char)c;
    n--;
  }

  return s;
}

void *memcpy(void *dest, const void *src, size_t n) {

  if (!dest || !src || n == 0) {
    return dest;
  }

  char *d = (char *)dest;
  const char *s = (const char *)src;

  typedef uintptr_t word_t;
  const size_t word_size = sizeof(word_t);
  const size_t word_mask = word_size - 1;

  if (n >= word_size) {
    while (((uintptr_t)d & word_mask) != 0) {
      *d++ = *s++;
      n--;
    }
  }

  word_t *wd = (word_t *)d;
  const word_t *ws = (const word_t *)s;

  while (n >= word_size) {
    *wd++ = *ws++;
    n -= word_size;
  }

  d = (char *)wd;
  s = (const char *)ws;

  while (n--) {
    *d++ = *s++;
  }

  return dest;
}

#ifndef KASSERT_H_
#define KASSERT_H_

#include <panic.h>

#define kassert(condition)                                                     \
  do {                                                                         \
    if (!(condition)) {                                                        \
      kpanic("Assertion failed: %s, file %s, line %d", #condition, __FILE__,   \
             __LINE__);                                                        \
    }                                                                          \
  } while (0)

#endif

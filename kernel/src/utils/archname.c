#include <utils/archname.h>

const char *arch_name() {
#if defined(__x86_64__)
  return "x86-64";
#elif defined(__aarch64__)
  return "aarch64";
#elif defined(__riscv)
  return "riscv64";
#elif defined(__loongarch64)
  return "loongarch64";
#endif
}

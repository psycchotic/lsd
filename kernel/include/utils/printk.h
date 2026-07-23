#ifndef PRINTK_H_
#define PRINTK_H_

#include <fb/fbtext.h>
#include <utils/printf.h>

int printk(const char *fmt, ...);

int klog_ok(const char *fmt, ...);
int klog_info(const char *fmt, ...);
int klog_warn(const char *fmt, ...);
int klog_error(const char *fmt, ...);

#endif

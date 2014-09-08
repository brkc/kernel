#include "x86.h"

#define PAGE_SIZE 4096
#define PAGE_ROUNDDOWN(x) ((x) & -(PAGE_SIZE))
#define PAGE_ROUNDUP(x) PAGE_ROUNDDOWN((x) + ((PAGE_SIZE) - 1))

void cursor_move(u16 offset);
void kputc(u8 c);
void kputs(const char *s);
void kprintf(const char *fmt, ...);
void kcls(void);
void physfree(void *addr0);
void physinit(void *addr0, u32 n);
void *physalloc1(void);

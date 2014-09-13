#include "x86.h"

#define PAGE_SIZE 4096
#define PAGE_MASK ((PAGE_SIZE) - 1)
#define PAGE_ROUND_DOWN(x) (((u32) (x) & ~(PAGE_MASK)))
#define PAGE_ROUND_UP(x) PAGE_ROUND_DOWN((x) + (PAGE_MASK))

void cursor_move(u16 offset);
void kputc(u8 c);
void kputs(const char *s);
void kprintf(const char *fmt, ...);
void kcls(void);
void kfree(void *addr0);
void kinit(void *addr0, u32 n);
void *kalloc(void);
void *kalloc0(void);

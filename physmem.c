#include "types.h"
#include "vm.h"

typedef struct {
    void *next;
} list;
list *head = 0;

void
physfree(void *addr0)
{
    u32 addr = (u32) addr0;
    u32 align = PAGE_ROUNDUP(addr);
    list *node = (list *) align;

    node->next = head;
    head = node;
}

void
physinit(void *addr0, u32 n)
{
    u32 addr = (u32) addr0;
    u32 align = PAGE_ROUNDUP(addr);
    u8 *p = (u8 *) align;
    u8 *end;

    n -= align - addr;
    n = PAGE_ROUNDUP(n);
    end = p + n;

    while (p < end) {
        physfree(p);
        p += 0x1000;
    }
}

void *
physalloc1(void)
{
    list *p = head;
    if (p)
        head = p->next;
    return p;
}

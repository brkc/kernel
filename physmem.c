#include "kernel.h"

typedef struct {
    void *next;
} list;
list *head = 0;

void
kfree(void *addr0)
{
    u32 addr = (u32) addr0;
    u32 align = PAGE_ROUNDUP(addr);
    list *node = (list *) align;

    node->next = head;
    head = node;
}

void
kinit(void *addr0, u32 n)
{
    u32 addr = (u32) addr0;
    u32 align = PAGE_ROUNDUP(addr);
    u8 *p = (u8 *) align;
    u8 *end;

    n -= align - addr;
    n = PAGE_ROUNDUP(n);
    end = p + n;

    while (p < end) {
        kfree(p);
        p += 0x1000;
    }
}

void *
kalloc(void)
{
    list *p = head;
    if (p)
        head = p->next;
    return p;
}

void *
kalloc0(void)
{
    u8 *tab = kalloc();
    int i;

    for (i = 0; i < PAGE_SIZE; i++)
        tab[i] = 0x0;

    return tab;
}

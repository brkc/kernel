#include "kernel.h"

struct list {
    void *next;
} *head = 0;

void
kfree(void *addr0)
{
    struct list *node = addr0;

    node->next = head;
    head = node;
}

void
kinit(void *addr0, u32 n)
{
    u8 *p = addr0;
    u32 i;

    for (i = 0; i < n; i++) {
        kfree(p);
        p += PAGE_SIZE;
    }
}

void *
kalloc(void)
{
    struct list *p = head;
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

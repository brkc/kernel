#include "kernel.h"

struct virt { u32 pdx, ptx, offset; };

static inline void
translate(struct virt *v, void *virt0)
{
    u32 virt = (u32) virt0;
    v->pdx = virt >> 22;
    v->ptx = virt >> 12 & 0x3ff;
    v->offset = virt & 0x3ff;
}

static inline int
present(void *entry)
{
    return (u32) entry & 0x1;
}

void
kmap(void *dir0, void *virt0, void *phys0)
{
    struct virt v;
    u32 **dir = dir0;
    u32 *tab;
    //kprintf("mapping %x to %x\n", virt0, phys0);

    translate(&v, virt0);
    if (!present(dir[v.pdx])) {
        tab = kalloc0();
        while (present(tab))
            tab++;
        dir[v.pdx] = (u32 *) ((u32) tab | 0x3);
        //kprintf("created pgdir entry %d at %x -> %x\n", v.pdx, dir + v.pdx,
                  //dir[v.pdx]);
    }

    tab[v.ptx] |= (u32) phys0 | 0x3;
    //kprintf("created pgtab entry %d at %x -> %x\n", v.ptx, tab + v.ptx,
              //tab[v.ptx]);
}

void
kunmap(void *dir0, void *virt0)
{
    struct virt v;
    u32 **dir = dir0;
    u32 *tab;
    kprintf("unmapping %x\n", virt0);

    translate(&v, virt0);
    if (present(dir[v.pdx]))
        tab[v.ptx] = 0x0;
    dir[v.pdx] = 0x0;
}

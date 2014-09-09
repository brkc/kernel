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

void *
pgtab_alloc(void)
{
    u32 *pgtab = physalloc1();
    int i;

    for (i = 0; i < 0x400; i++)
        pgtab[i] = 0x0;
    
    return pgtab;
}

void
kmap0(void *pgdir0, void *virt0, void *phys0)
{
    struct virt v;
    u32 **pgdir = pgdir0;
    u32 *pgtab;
    //kprintf("mapping %x to %x\n", virt0, phys0);

    translate(&v, virt0);
    if (!present(pgdir[v.pdx])) {
        pgtab = pgtab_alloc();
        while (present(pgtab))
            pgtab++;
        pgdir[v.pdx] = (u32 *) ((u32) pgtab | 0x3);
        //kprintf("created pgdir entry %d at %x -> %x\n", v.pdx, pgdir + v.pdx, pgdir[v.pdx]);
    }

    pgtab[v.ptx] |= (u32) phys0 | 0x3;
    //kprintf("created pgtab entry %d at %x -> %x\n", v.ptx, pgtab + v.ptx, pgtab[v.ptx]);
}

void
kunmap(void *pgdir0, void *virt0)
{
    struct virt v;
    u32 **pgdir = pgdir0;
    u32 *pgtab;
    kprintf("unmapping %x\n", virt0);

    translate(&v, virt0);
    if (present(pgdir[v.pdx]))
        pgtab[v.ptx] = 0x0;
    pgdir[v.pdx] = 0x0;
}

void
kinit0(void *start0)
{
    u32 *pgtab = start0;
    int i;

    for (i = 0; i < 0x400; i++)
        pgtab[i] = 0x0;

    //kprintf("created pgdir at %x\n", start0);
}

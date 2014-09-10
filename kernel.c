#include "multiboot.h"
#include "kernel.h"

extern u8 _head[];
extern u8 _start[];
extern u8 _end[];

int
kmain(u32 magic, multiboot_info_t *info)
{
    u32 p;
    void *pgdir;
    u8 *addr;

    cursor_move(0);
    kprintf("kernel begins at 0x%x\n", _head);
    kprintf("kernel loaded at 0x%x\n", _start);
    kprintf("kernel ends at 0x%x\n", _end);

    p = info->mmap_addr;
    while (p < info->mmap_addr + info->mmap_length) {
        multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) p;
        u32 size = mmap->size, addr = mmap->addr, len = mmap->len;
        kprintf("addr %x len %d\n", addr, len);
        p += size + sizeof size;
    }

    kinit(_end, 8 * 1048576);
    pgdir = kalloc0();
    for (addr = _head; addr < _end; addr += PAGE_SIZE)
        kmap(pgdir, addr, addr);
    kmap(pgdir, 0xb8000, 0xb8000);

    setcr3((u32) pgdir);
    setcr0(getcr0() | CR0_PG);

    kprintf("ok\n");
    return 0;
}

#include "multiboot.h"
#include "types.h"
#include "x86.h"
#include "vm.h"

extern u8 _start[];
extern u8 _end[];

int
kmain(u32 magic, multiboot_info_t *info)
{
    u32 p;
    int i;

    cursor_move(0);
    kprintf("kernel begins at 0x%x\n", _start);
    kprintf("kernel ends at 0x%x\n", _end);

    p = info->mmap_addr;
    while (p < info->mmap_addr + info->mmap_length) {
        multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) p;
        u32 size = mmap->size, addr = mmap->addr, len = mmap->len;
        kprintf("addr %x len %d\n", addr, len);
        p += size + sizeof size;
    }
    physinit(_end, 8 * 1048576);
    for (i = 0; i < 5; i++) {
        void *p = physalloc1();
        kprintf("allocd addr %x\n", p);
    }
    kprintf("ok\n");
    return 0;
}

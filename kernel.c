#include "multiboot.h"
#include "types.h"
#include "x86.h"

extern u8 _start[];
extern u8 _end[];

int
cmain(u32 magic, multiboot_info_t *info)
{
    u32 p;

    cursor_move(0);
    printf("kernel loaded at 0x%x\n", _start);
    printf("kernel end at 0x%x\n", _end);

    p = info->mmap_addr;
    while (p < info->mmap_addr + info->mmap_length) {
        multiboot_memory_map_t *mmap = (multiboot_memory_map_t *) p;
        u32 size = mmap->size, addr = mmap->addr, len = mmap->len;
        printf("addr %x len %d\n", addr, len);
        p += size + sizeof size;
    }
    printf("ok\n");
    return 0;
}

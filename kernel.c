#include "types.h"
#include "x86.h"

extern u8 _start[];
extern u8 end[];

int
cmain(void)
{
    cursor_move(0);
    printf("kernel loaded at 0x%x\n", _start);
    printf("kernel end at 0x%x\n", end);
    printf("ok\n");
    return 0;
}

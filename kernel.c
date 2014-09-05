#include "types.h"
#include "x86.h"

extern u8 _start[];

int
cmain(void)
{
    cursor_move(0);
    printf("kernel loaded at 0x%x -- ", _start);
    printf("cursor is at offset %d after print", cursor_address());
    return 0;
}

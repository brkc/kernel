#include "types.h"
#include "x86.h"

int
cmain(void)
{
    cursor_move(0);
    printf("print some text -- ");
    printf("cursor is at offset %d after print", cursor_address());
    return 0;
}

#include "types.h"
#include "x86.h"

int
cmain(void)
{
    char str[] = "hello, world";

    cursor_move(0);
    puts(str);

    return 0;
}

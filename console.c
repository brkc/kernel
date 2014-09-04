#include "types.h"
#include "x86.h"

enum {
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Purple,
    Yellow,
    White,
    Bright,
    Blink = 0x80,
};

enum {
    Background = Black,
    Foreground = White,
    Width = 80,
    Height = 24,
    Attr = (Background << 4 | Foreground) << 8,
};

#define CRTPORT 0x3d4

void
cursor_move(ushort offset)
{
    outb(CRTPORT, 14);
    outb(CRTPORT+1, offset >> 8);

    outb(CRTPORT, 15);
    outb(CRTPORT+1, offset);
}

ushort
cursor_address(void)
{
    ushort addr;

    outb(CRTPORT, 14);
    addr = inb(CRTPORT+1) << 8;

    outb(CRTPORT, 15);
    addr |= inb(CRTPORT+1);

    return addr;
}

void
putc(uchar c)
{
    ushort *video = (ushort *) 0xb8000;
    ushort offset = cursor_address();

    video[offset] = c | Attr;
    cursor_move(offset + 1);
}

void
puts(const char *s)
{
    while (*s)
        putc(*s++);
}

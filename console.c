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

uchar
crt_read(uchar index)
{
    outb(CRTPORT, index);
    return inb(CRTPORT + 1);
}

void
crt_write(uchar index, uchar data)
{
    outb(CRTPORT, index);
    outb(CRTPORT + 1, data);
}

void
cursor_move(ushort offset)
{
    crt_write(14, offset >> 8);
    crt_write(15, offset);
}

ushort
cursor_address(void)
{
    return crt_read(14) << 8 | crt_read(15);
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

int
itoa(int val, char *str, int base)
{
    static char digits[] = "0123456789abcdef";
    int k = 32, i, j;

    do {
        str[k--] = digits[val % base];
        val /= base;
    } while (val != 0);

    i = 32 - k;
    j = 32;
    str[i--] = '\0';
    while (i >= 0)
        str[i--] = str[j--];

    return 0;
}

void
printf(const char *fmt, ...)
{
    const char *p;
    char buf[33];
    uint *argp = (uint *) &fmt + 1;

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putc(*p);
            continue;
        }
        *p++;
        switch (*p) {
            case 'd':
                itoa(*(int *) argp++, buf, 10);
                puts((char *) buf);
                break;
            case 's':
                puts(*(char **) argp++);
                break;
            case 'x':
                itoa(*(int *) argp++, buf, 16);
                puts((char *) buf);
                break;
            default:
                putc('%');
                putc(*p);
                break;
        }
    }
}

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

u8
crt_read(u8 index)
{
    outb(CRTPORT, index);
    return inb(CRTPORT + 1);
}

void
crt_write(u8 index, u8 data)
{
    outb(CRTPORT, index);
    outb(CRTPORT + 1, data);
}

void
cursor_move(u16 offset)
{
    crt_write(14, offset >> 8);
    crt_write(15, offset);
}

u16
cursor_address(void)
{
    return crt_read(14) << 8 | crt_read(15);
}

void
putc(u8 c)
{
    u16 *video = (u16 *) 0xb8000;
    u16 offset = cursor_address();

    if (c == '\n') {
        cursor_move((offset + 79) / 80 * 80);
        return;
    }
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
    u32 *argp = (u32 *) &fmt + 1;

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

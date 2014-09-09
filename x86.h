typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

enum {
    CR0_PE = 1 << 0,
    CR0_PG = 1 << 31,
};

static inline u8
inb(u16 port)
{
    u8 data;

    asm("inb %1,%0" : "=a" (data) : "d" (port));

    return data;
}

static inline u16
inw(u16 port)
{
    u16 data;

    asm("inw %1,%0" : "=a" (data) : "d" (port));

    return data;
}

static inline u32
inl(u16 port)
{
    u32 data;

    asm("inl %1,%0" : "=a" (data) : "d" (port));

    return data;
}

static inline void
outb(u16 port, u8 data)
{
    asm("outb %0,%1" :: "a" (data), "d" (port));
}

static inline void
outw(u16 port, u16 data)
{
    asm("outw %0,%1" :: "a" (data), "d" (port));
}

static inline void
outl(u16 port, u32 data)
{
    asm("outl %0,%1" :: "a" (data), "d" (port));
}

static inline void
setcr0(u32 cr0)
{
    asm("mov %0,%%cr0" :: "a" (cr0));
}

static inline void
setcr3(u32 cr3)
{
    asm("mov %0,%%cr3" :: "a" (cr3));
}

static inline u32
getcr0(void)
{
    u32 cr0;

    asm("mov %%cr0,%0" : "=a" (cr0) :);

    return cr0;
}

static inline u32
getcr3(void)
{
    u32 cr3;

    asm("mov %%cr3,%0" : "=a" (cr3) :);

    return cr3;
}

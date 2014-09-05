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

static inline uchar
inb(ushort port)
{
    uchar data;

    asm("inb %1,%0" : "=a" (data) : "d" (port));

    return data;
}

static inline ushort
inw(ushort port)
{
    ushort data;

    asm("inw %1,%0" : "=a" (data) : "d" (port));

    return data;
}

static inline uint
inl(ushort port)
{
    uint data;

    asm("inl %1,%0" : "=a" (data) : "d" (port));

    return data;
}

static inline void
outb(ushort port, uchar data)
{
    asm("outb %0,%1" :: "a" (data), "d" (port));
}

static inline void
outw(ushort port, ushort data)
{
    asm("outw %0,%1" :: "a" (data), "d" (port));
}

static inline void
outl(ushort port, uint data)
{
    asm("outl %0,%1" :: "a" (data), "d" (port));
}

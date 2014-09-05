#define SEGDESC(type,base,limit) \
    .word limit&0xffff, base&0xffff; \
    .byte (base>>16)&0xff, 0x90|type&0xff, 0xc0|(limit>>16)&0xff, base>>24

#define SEGDESC_NULL SEGDESC(0,0,0)

#define STA_X 0x8 // Executable segment
#define STA_E 0x4 // Expand down (non-executable segments)
#define STA_C 0x4 // Conforming code segment (executable only)
#define STA_W 0x2 // Writeable (non-executable segments)
#define STA_R 0x2 // Readable (executable segments)
#define STA_A 0x1 // Accessed

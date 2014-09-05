#include "segdesc.h"

.set STACK_SIZE, 0x1000
.set ALIGN, 1 << 0
.set MEMINFO, 1 << 1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1badb002
.set CHECKSUM, -(MAGIC + FLAGS)

.balign 4
.text
header:
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.globl _start
_start:
	mov $(stack + STACK_SIZE), %esp
	push %ebx
	push %eax
	call cmain

hang:
	cli
	hlt
	jmp hang

gdt:
    SEGDESC_NULL
    SEGDESC(STA_X|STA_R, 0, 0xfffff)
    SEGDESC(STA_W, 0, 0xfffff)

.comm stack, STACK_SIZE

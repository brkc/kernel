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
	call kmain

hang:
	cli
	hlt
	jmp hang

.comm stack, STACK_SIZE

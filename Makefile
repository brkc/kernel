CC = cc
LD = ld
CFLAGS = -g -m32 -ffreestanding -nostdlib
LDFLAGS = -lgcc
OBJS = multiboot.o kernel.o console.o kalloc.o mmu.o

kernel.iso: $(OBJS)
	$(LD) -melf_i386 -Ttext=0x100000 -o boot/kernel $(OBJS)
	rm -f kernel.iso
	grub-mkrescue -o kernel.iso .

run:
	qemu-system-x86_64 -cdrom kernel.iso

debug:
	qemu-system-x86_64 -s -S -cdrom kernel.iso &
	gdb

clean:
	rm -f boot/kernel kernel.iso *.o

.c.o:
	$(CC) -c $(CFLAGS) $< $(LDFLAGS)

.s.o:
	$(CC) -c $(CFLAGS) $< $(LDFLAGS)

CC = cc
LD = ld
CFLAGS = -g -m32 -ffreestanding -nostdlib
LDFLAGS = -lgcc

kernel.iso: multiboot.o kernel.o console.o
	$(LD) -melf_i386 -Ttext=0x100000 -o boot/kernel kernel.o multiboot.o console.o
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
	$(CC) -c $(CFLAGS) kernel.c $< $(LDFLAGS)

multiboot.o: multiboot.s
	$(CC) -c $(CFLAGS) multiboot.s $(LDFLAGS)

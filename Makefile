CFLAGS := -fno-stack-protector -fno-builtin -nostdine -O -g -Wall -I
CCDIR := /home/decoder10/opt/cross-i686/bin

all : kernel.bin

build: boot.o kernel.o mem.o basicio.o scrn.o
	$(CCDIR)/i686-elf-gcc -T link.ld -o init.bin -ffreestanding -O2 -nostdlib boot.o kernel.o mem.o basicio.o scrn.o -lgcc

kernel.bin: mem.c basicio.c scrn.c kernel.c
	$(CCDIR)/i686-elf-gcc -c mem.c -o mem.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CCDIR)/i686-elf-gcc -c basicio.c -o basicio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CCDIR)/i686-elf-gcc -c scrn.c -o scrn.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CCDIR)/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -f *.o *.bin

run:
	qemu-system-i386 -kernel init.bin

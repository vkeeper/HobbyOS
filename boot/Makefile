boot: boot.asm
	nasm boot.asm

qemu: boot
	qemu-system-i386 boot

clean: boot
	rm -rf boot

boot: src/boot.asm
	nasm src/boot.asm -o target/boot.o

kernel: src/kernel.asm
	nasm src/kernel.asm -isrc/ -o target/kernel.o

sys: boot kernel
	rm -rf sys.img
	bximage -fd -size=1.44 -q sys.img
	dd if=target/boot.o of=sys.img 
	dd if=target/kernel.o of=sys.img seek=1 obs=512

qemu: sys
	qemu-system-i386 sys.img

bochs: sys
	bochs

clean:
	rm -rf target/*.o sys.img

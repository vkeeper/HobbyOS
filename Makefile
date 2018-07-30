boot: src/boot.asm
	nasm src/boot.asm -isrc/ -o target/boot.bin

kernel: src/kernel.asm
	nasm src/kernel.asm -isrc/ -o target/kernel.bin
	gcc -m32 -g -s -ffreestanding -fno-builtin -fno-leading-underscore -fno-stack-protector -funsigned-char -Wimplicit -o2 -c src/start.c -o target/start.o
	ld -melf_i386 -e _start -Ttext 0x8000 -o target/start.l target/start.o
	objcopy -O binary target/start.l target/start.bin

sys: boot kernel
	rm -rf sys.img
	bximage -fd -size=1.44 -q sys.img
	dd if=target/boot.bin of=sys.img 
	dd if=target/kernel.bin of=sys.img seek=1 obs=512 

qemu: sys
	qemu-system-i386 sys.img

bochs: sys
	bochs

clean:
	rm -rf target/*.o sys.img target/*.l target/*.bin

boot: src/boot.asm
	nasm src/boot.asm -i src/ -o target/boot.bin

kernel: src/kernel.asm
	nasm -f elf32 src/kernel.asm -i src/ -o target/kernel.o

start.bin: src/start.c
	gcc -m32 -fno-pie -ffreestanding -fno-builtin -fno-leading-underscore -fno-stack-protector \
		-funsigned-char -finline-functions -finline-small-functions -findirect-inlining  -Wimplicit -o2 \
		-c src/start.c -o target/start.o
	ld -m elf_i386 -static -Ttext 0x9000 -e _start target/kernel.o target/start.o -o target/kernel.bin --oformat binary

img: boot kernel start.bin
	rm -rf sys.img
	bximage -fd -size=1.44 -q sys.img
	dd if=target/boot.bin of=sys.img 
	dd if=target/kernel.bin of=sys.img seek=1 obs=512 

qemu: img 
	qemu-system-i386 sys.img

bochs: img
	bochs

clean:
	rm -rf target/*.o sys.img target/*.ld target/*.bin

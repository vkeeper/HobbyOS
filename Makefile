CC				=	gcc
CFLAGS			=	-I src/include/ -fno-pie -ffreestanding -fno-builtin -fno-leading-underscore -fno-stack-protector -funsigned-char -finline-functions -finline-small-functions -findirect-inlining  -Wimplicit -o2 -m32 -c

ASM				=	nasm
ASMFLAGS		=	-i src/include/
ASMLINKFLAGS	=   -i src/include/ -f elf32
LD				=	ld
LDFLAGS			= 	-m elf_i386 -static -Ttext 0x9000 -e _start	--oformat binary -T script/link.ld

TARGETDIR		= target/

boot: src/boot.asm
	$(ASM)	$(ASMFLAGS)	-o target/boot.bin $< 

kernel.o: src/kernel.asm
	$(ASM) $(ASMLINKFLAGS) -o target/kernel.o $< 

start.o: src/start.c
	$(CC) $(CFLAGS) $< -o target/start.o

kernel.bin: start.o kernel.o
	$(LD) $(LDFLAGS) target/kernel.o target/start.o -o target/kernel.bin

img: boot kernel.bin
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

CC				=	gcc
CFLAGS			=	-I src/include/ -fno-pie -ffreestanding -fno-builtin -fno-leading-underscore -fno-stack-protector -funsigned-char -finline-functions -finline-small-functions -findirect-inlining  -Wimplicit -o2 -m32 -c

ASM				=	nasm
ASMFLAGS		=	-i src/include/
ASMLINKFLAGS	=   -i src/include/ -f elf32
LD				=	ld
LDFLAGS			= 	-m elf_i386 -static -e _start	--oformat binary -T script/link.ld

TARGETDIR		= target/

C_OBJECTS		=	target/start.o target/common.o target/mm.o target/print.o

boot: src/boot.asm
	$(ASM)	$(ASMFLAGS)	-o target/boot.bin $< 

kernel.o: src/kernel.asm
	$(ASM) $(ASMLINKFLAGS) -o target/kernel.o $< 

print.o: src/print.c
	$(CC) $(CFLAGS) $< -o target/print.o
	
mm.o: src/mm.c
	$(CC) $(CFLAGS) $< -o target/mm.o

common.o: src/common.c
	$(CC) $(CFLAGS) $< -o target/common.o

start.o: src/start.c
	$(CC) $(CFLAGS) $< -o target/start.o

kernel: kernel.o start.o print.o common.o mm.o
	$(LD) $(LDFLAGS) target/kernel.o  $(C_OBJECTS) -o target/kernel.bin

img: boot kernel
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

CC				=	gcc
CFLAGS			=	-I src/include/ -fno-pie -ffreestanding -fno-builtin -fno-leading-underscore -fno-stack-protector -funsigned-char -finline-functions -finline-small-functions -findirect-inlining  -Wimplicit -o2 -m32 -c

ASM				=	nasm
ASMFLAGS		=	-i src/include/
ASMLINKFLAGS	=   -i src/include/ -f elf32
LD				=	ld
LDFLAGS			= 	-m elf_i386 -static -e _start	--oformat binary -T script/link.ld

TARGETDIR		= target/

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c %.o, $(C_SOURCES))

S_SOURCES = $(shell find . -name "*.asm")
S_OBJECTS = $(patsubst %.asm %.o, $(S_SOURCES))

boot: src/boot.asm
	$(ASM)	$(ASMFLAGS)	-o target/boot.bin $< 

kernel.o: src/kernel.asm
	$(ASM) $(ASMLINKFLAGS) -o target/kernel.o $< 

print.o: src/print.c
	$(CC) $(CFLAGS) $< -o target/print.o
	
common.o: src/common.c
	$(CC) $(CFLAGS) $< -o target/common.o

start.o: src/start.c
	$(CC) $(CFLAGS) $< -o target/start.o

kernel.bin: start.o kernel.o print.o common.o
	$(LD) $(LDFLAGS) target/kernel.o  target/start.o target/common.o target/print.o -o target/kernel.bin

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

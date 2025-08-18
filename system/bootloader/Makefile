SRC_32		=	src/32/main_32.asm
SRC_KERN	=	src/32/kernel_32.asm
CC			=	nasm
NAME		=	bootsector.bin
KERN_NAME	=	kernel32.o
QEMU		=	qemu-system-x86_64

make_32_kern:
	$(CC) -f bin $(SRC_32) -o $(NAME)
	$(CC) -f elf $(SRC_KERN) -o $(KERN_NAME)

run:
	$(QEMU) -fda $(NAME)

fclean:
	rm -f $(NAME)

SRC			=	$(wildcard src/*.c) \
				$(wildcard src/*/*.c) \
				$(wildcard asm/*.asm)

DEPS		=	-l:lib/libc/libc.a \
				-l:system/drivers/drivlib.a

OBJ			=	$(SRC:.c=.o) $(SRC:.asm=.o)

CC			=	i686-elf-gcc

CFLAGS		=	-ffreestanding -nolibc -m32 -c -g -I../../include

all: $(OBJ)

%.o: %.asm
	nasm $< -f elf -g -o $@

clean:
	rm -f $(OBJ)

fclean: clean

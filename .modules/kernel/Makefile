SRC			=	$(wildcard src/*.c) \
				$(wildcard src/shell/*.c) \
				$(wildcard asm/*.asm)

OBJ			=	$(SRC:.c=.o) $(SRC:.asm=.o)

CC			=	gcc

CFLAGS		=	-ffreestanding  -m32 -c -g -I../../include

all: $(OBJ)

%.o: %.asm
	nasm $< -f elf -o $@

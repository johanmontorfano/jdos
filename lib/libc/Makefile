SRC			=	$(wildcard lib/*.c)

OBJ			=	$(SRC:.c=.o)

CC			=	i686-elf-gcc

CFLAGS		=	-ffreestanding -nolibc -m32 -c -g -I../../include

LIBNAME		=	libc.a

all: $(LIBNAME)

re: fclean all

$(LIBNAME): $(OBJ)
	i686-elf-ar rcs $(LIBNAME) $(OBJ)

clean:

fclean: clean
	rm -f $(LIBNAME)

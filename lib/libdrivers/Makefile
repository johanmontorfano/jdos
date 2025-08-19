SRC			=	$(wildcard lib/*.c) \
				$(wildcard lib/keyboard/*.c) \
				$(wildcard lib/vga/*.c) \
				$(wildcard lib/disks/*.c)

DEPS		=	-l:../../lib/libc/libc.a

OBJ			=	$(SRC:.c=.o)

CC			=	gcc

CFLAGS		=	-ffreestanding -m32 -c -g -I../../include $(DEPS)

LIBNAME		=	libdrivers.a

all: $(LIBNAME)

re: fclean all

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

clean:

fclean: clean
	rm -f $(LIBNAME)

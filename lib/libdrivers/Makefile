SRC			=	$(wildcard lib/*.c) \
				$(wildcard lib/keyboard/*.c) \
				$(wildcard lib/disks/ata/*.c)

DEPS		=	-l:../../lib/libc/libc.a

OBJ			=	$(SRC:.c=.o)

CC			=	gcc

CFLAGS		=	-ffreestanding -m32 -c -g -I../../include $(DEPS) \
					-DECHO_KEYBOARD1

LIBNAME		=	libdrivers.a

all: $(LIBNAME)

re: fclean all

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

clean:

fclean: clean
	rm -f $(LIBNAME)

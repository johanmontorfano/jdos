SRC			=	$(wildcard lib/*.c)

OBJ			=	$(SRC:.c=.o)

CC			=	gcc

CFLAGS		=	-ffreestanding -m32 -c -g -I../../include

LIBNAME		=	libc.a

all: $(LIBNAME)

re: fclean all

$(LIBNAME): $(OBJ)
	ar rcs $(LIBNAME) $(OBJ)

clean:

fclean: clean
	rm -f $(LIBNAME)

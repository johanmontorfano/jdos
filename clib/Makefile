SRC			=	$(wildcard lib/*.c)

OBJ			=	$(SRC:.c=.o)

CC			=	gcc

CFLAGS		=	-ffreestanding -m32 -c -g -I../include

LIBNAME		=	clib.a

all: $(LIBNAME) clean

re: fclean all

$(LIBNAME): $(OBJ)
	ar -cq $(LIBNAME) $(OBJ)

clean:

fclean: clean
	rm -f $(LIBNAME)

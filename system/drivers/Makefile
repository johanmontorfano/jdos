SRC			=	lib/ports.c \
				lib/screen.c \
				lib/keyboard/keyboard.c \
				lib/keyboard/layouts.c

OBJ			=	$(SRC:.c=.o)

CC			=	gcc

CFLAGS		=	-ffreestanding -m32 -c -g -I../../include

LIBNAME		=	drivlib.a

all: $(LIBNAME) clean

re: fclean all

$(LIBNAME): $(OBJ)
	ar -cq $(LIBNAME) $(OBJ)

clean:

fclean: clean
	rm -f $(LIBNAME)

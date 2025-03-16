SRC			=	$(wildcard lib/*.c) \
				$(wildcard lib/keyboard/*.c) \
				$(wildcard lib/disks/ata/*.c)

OBJ			=	$(SRC:.c=.o)

CC			=	gcc

CFLAGS		=	-ffreestanding -m32 -c -g -I../../include

LIBNAME		=	drivlib.a

all: $(LIBNAME)

re: fclean all

$(LIBNAME): $(OBJ)
	ar -cq $(LIBNAME) $(OBJ)

clean:

fclean: clean
	rm -f $(LIBNAME)

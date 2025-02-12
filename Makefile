LINKER				=	ld

L_FLAGS				=	--allow-multiple-definition -m elf_i386

KERNEL_SRC			=	system/kernel/src/main.o \
						$(wildcard system/kernel/src/shell/*.o) \
						$(wildcard system/kernel/src/k*.o) \
						$(wildcard system/drivers/lib/*.o) \
						$(wildcard system/drivers/lib/keyboard/*.o) \
						$(wildcard clib/lib/*.o) \
						bootloader/kernel32.o \
						$(wildcard system/kernel/asm/*.o)

KERNEL_NAME			=	kernel.bin

IMAGE_SRC			=	bootloader/bootsector.bin \
						$(KERNEL_NAME)

IMAGE_NAME			=	josimg.bin

all: $(KERNEL_NAME) $(IMAGE_NAME) clean

re: fclean all

dependencies:
	make -C clib
	make -C bootloader make_32
	make -C bootloader make_kern
	make -C system/drivers
	make -C system/kernel

$(KERNEL_NAME): dependencies
	ld $(L_FLAGS) -o $@ -Ttext 0x1000 $(KERNEL_SRC) --oformat binary

$(KERNEL_NAME).elf: dependencies
	ld $(L_FLAGS) -o $@ -Ttext 0x1000 $(KERNEL_SRC)

$(IMAGE_NAME): $(IMAGE_SRC)
	cat $^ > $@

run:
	qemu-system-x86_64 -fda $(IMAGE_NAME)

debug: $(KERNEL_NAME).elf clean
	qemu-system-x86_64 -s -fda $(IMAGE_NAME) -d guest_errors,int &
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_NAME).elf"

fclean: clean
	rm -f $(IMAGE_NAME) $(IMAGE_NAME).elf

clean:
	rm -f $(IMAGE_SRC) $(KERNEL_NAME) $(KERNEL_SRC)

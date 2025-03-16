LINKER				=	ld

L_FLAGS				=	--allow-multiple-definition -m elf_i386

KERNEL_SRC			=	system/kernel/src/main.o \
						$(wildcard system/kernel/src/shell/*.o) \
						$(wildcard system/kernel/src/k*.o) \
						$(wildcard system/drivers/lib/*.o) \
						$(wildcard system/drivers/lib/disks/ata/*.o) \
						$(wildcard system/drivers/lib/keyboard/*.o) \
						$(wildcard clib/lib/*.o) \
						system/bootloader/kernel32.o \
						$(wildcard system/kernel/asm/*.o)

KERNEL_NAME			=	kernel.bin

IMAGE_SRC			=	system/bootloader/bootsector.bin \
						$(KERNEL_NAME)

IMAGE_NAME			=	josimg.bin

DISK_NAME			=	hdd.bin

DISK_SIZE			=	100M

all: $(KERNEL_NAME) $(IMAGE_NAME) $(DISK_NAME) clean

re: fclean all

dependencies:
	make -C clib
	make -C system/bootloader make_32
	make -C system/bootloader make_kern
	make -C system/drivers
	make -C system/kernel

$(KERNEL_NAME): dependencies
	ld $(L_FLAGS) -o $@ -Ttext 0x1000 $(KERNEL_SRC) --oformat binary

$(KERNEL_NAME).elf: dependencies
	ld $(L_FLAGS) -o $@ -Ttext 0x1000 $(KERNEL_SRC)

$(IMAGE_NAME): $(IMAGE_SRC)
	cat $^ > $@

$(DISK_NAME):
	qemu-img create -f raw $(DISK_NAME) $(DISK_SIZE)

run:
	qemu-system-x86_64 -fda $(IMAGE_NAME) -hda $(DISK_NAME)

debug: $(KERNEL_NAME).elf clean
	qemu-system-x86_64 -s -fda $(IMAGE_NAME) \
		-hda $(DISK_NAME) \
		-d guest_errors,int &
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_NAME).elf"

fclean: clean
	rm -f $(IMAGE_NAME) $(IMAGE_NAME).elf

clean:
	rm -f $(IMAGE_SRC) $(KERNEL_NAME) $(KERNEL_SRC)

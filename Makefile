LINKER				=	ld

LD_FLAGS			=	--allow-multiple-definition -m elf_i386 -T linker.ld

KERNEL_SRC			=	system/kernel/src/main.o \
						system/kernel/src/cpu/usermode.o \
						$(wildcard system/kernel/src/*/*.o) \
						$(wildcard system/kernel/asm/*.o) \
						$(wildcard system/kernel/src/*.o) \
						system/bootloader/kernel32.o \
						lib/libdrivers/libdrivers.a \
						lib/libc/libc.a

KERNEL_NAME			=	kernel.bin

IMAGE_SRC			=	system/bootloader/bootsector.bin \
						$(KERNEL_NAME)

IMAGE_NAME			=	josimg.bin

DISK_NAME			=	hdd.bin

DISK_SIZE			=	10M

all: $(KERNEL_NAME) $(IMAGE_NAME) $(DISK_NAME)

re: fclean all

dependencies:
	make -C lib/libc
	make -C lib/libdrivers
	make -C system/bootloader make_32
	make -C system/bootloader make_kern
	make -C system/kernel

$(KERNEL_NAME): dependencies
	ld $(LD_FLAGS) -o $@ $(KERNEL_SRC) --oformat binary

$(KERNEL_NAME).elf: dependencies
	ld $(LD_FLAGS) -o $@ $(KERNEL_SRC)

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

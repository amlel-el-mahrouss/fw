 #
 #	========================================================
 #
 #	CoreBoot
 # 	Date Added: 08/11/2023
 # 	Copyright 2024, Amlal El Mahrouss, all rights reserved.
 #
 # 	========================================================
 #

CC=ppc-elf-gcc
AS=ppc-elf-as

FIRMWARE=boot.rom

FLAGS=-c -mcpu=e5500  -D__COMPILE_POWERPC__ -I../../ -Wall -c -nostdlib -ffreestanding -fno-builtin \
		-D__BSTRICT__ -D__BDEBUG__

C_SRC=$(wildcard *.c) $(wildcard ../*.c) -c

AS_FLAGS= -c -I../../

LD=ppc-elf-ld
OBJ=*.o
FLAGS_LD= --script=linkscript.ld -o core-boot.elf -nostdlib

EMU=qemu-system-ppc64
EMU_FLAGS= -drive file=epm.img,media=disk,snapshot=off,format=raw \
			-device virtio-scsi-pci,id=scsi -smp 4 -device VGA -cpu e5500 -d guest_errors,unimp \
			-M ppce500 -bios $(FIRMWARE) -s

WAIT=sleep 1

IMG_CMD=qemu-img create -f qcow2 epm.img 256M

.PHONY: all
all: firmware-link
	@echo "[CoreBoot] build done."

.PHONY: firmware-link
firmware-link: firmware-compile
	$(LD) $(OBJ) $(FLAGS_LD)
	$(IMG_CMD)
	qemu-img create -f raw boot.rom 512K
	dd if=core-boot.elf of=boot.rom bs=1 seek=0 conv=notrunc

# compile firmware
.PHONY: firmware-compile
firmware-compile:
	$(CC) $(FLAGS) $(C_SRC)
	$(AS) $(AS_FLAGS) ppc64-boot.S -o ppc64-boot.o

# launch qemu rule
.PHONY: run
run:
	$(EMU) $(EMU_FLAGS)

# launch qemu with attached debugger
.PHONY: run-dbg
run-dbg:
	$(EMU) $(EMU_FLAGS)

# remove object files
.PHONY: clean
clean:
	rm -f $(wildcard *.o) $(wildcard *.elf) $(wildcard *.rom) $(wildcard *.epm)

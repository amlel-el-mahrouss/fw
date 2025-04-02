 #
 #	========================================================
 #
 #	CoreBoot
 # 	Date Added: 08/11/2023
 # 	Copyright 2024, ZKA Technologies, all rights reserved.
 #
 # 	========================================================
 #

CC=aarch64-linux-gnu-gcc
AS=aarch64-linux-gnu-as

COREBOOT=core-boot.elf
FIRMWARE=boot.rom
STAGE2=bootstg2.rom

FLAGS=-c -D__COMPILE_ARM64__ -I../../ -Wall -c -nostdlib -ffreestanding -fno-builtin \
		-D__BSTRICT__ -D__BDEBUG__

C_SRC=$(wildcard *.c) $(wildcard ../*.c) -c

AS_FLAGS= -c -I../../

LD=aarch64-linux-gnu-ld
OBJ=*.o
FLAGS_LD= --script=script.lds -o core-boot.elf -nostdlib
OBJCOPY=aarch64-linux-gnu-objcopy

EMU=qemu-system-aarch64
EMU_FLAGS=-M virt -cpu cortex-a57 -bios $(FIRMWARE) -m 256M -d int -smp 2

WAIT=sleep 1

.PHONY: all
all: firmware-link
	@echo "[CoreBoot] build done."

.PHONY: firmware-link
firmware-link: firmware-compile
	$(LD) $(OBJ) $(FLAGS_LD)

.PHONY: rom
rom:
	qemu-img create -f qcow2 epm.img 256M
	qemu-img create -f raw bootstg2.rom 64M
	$(OBJCOPY) --strip-all -O binary $(COREBOOT) $(FIRMWARE)

# compile firmware
.PHONY: firmware-compile
firmware-compile:
	$(CC) $(FLAGS) $(C_SRC)
	$(AS) arm64-start-context.S -o arm64-start-context.o
	$(AS) arm64-boot.S -o arm64-boot.o
	

# launch qemu rule
.PHONY: run
run:
	$(EMU) $(EMU_FLAGS)

# launch qemu with attached debugger
.PHONY: run-dbg
run-dbg:
	$(EMU) -s -S $(EMU_FLAGS)

# remove object files
.PHONY: clean
clean:
	rm -f $(wildcard *.o) $(wildcard *.elf) $(wildcard *.rom) $(wildcard *.epm)

 #
 #	========================================================
 #
 #	CoreBoot
 # 	Date Added: 08/11/2023
 # 	Copyright 2024, ZKA Technologies, all rights reserved.
 #
 # 	========================================================
 #

CC=riscv64-unknown-elf-gcc
FIRMWARE=core-boot.elf
FLAGS=-D__COMPILE_RISCV__ -I../../ -Wall -c -nostdlib -ffreestanding -fno-builtin -D__BSTRICT__ -D__BDEBUG__ -O0 -mcmodel=medany
C_SRC= $(wildcard *.s) $(wildcard *.c) $(wildcard ../*.c) -c

CXX=riscv64-unknown-elf-g++
CXX_SRC= $(wildcard *.cc) $(wildcard ../*.cc) -c

LD=riscv64-unknown-elf-ld
OBJ=*.o
FLAGS_LD= --script=linkscript.ld -o core-boot.elf

EMU=qemu-system-riscv64 -m 4G -smp 2 -machine virt -bios $(FIRMWARE) -d int -device VGA

.PHONY: all
all: firmware-link
	@echo "[CoreBoot] Done."

# link (make firmware)
.PHONY: firmware-link
firmware-link: firmware-compile
	$(LD) $(OBJ) $(FLAGS_LD)

# compile firmware
.PHONY: firmware-compile
firmware-compile:
	$(CC) $(FLAGS) $(C_SRC)
	$(CXX) -ffreestanding -fno-rtti -fno-exceptions $(FLAGS) $(CXX_SRC)

# launch qemu rule
.PHONY: run
run:
	$(EMU)

# launch qemu with attached debugger
.PHONY: run-dbg
run-dbg:
	$(EMU) -S

# remove object files
.PHONY: clean
clean:
	rm -f $(wildcard *.o) $(wildcard *.elf) $(wildcard *.rom) $(wildcard *.epm)

#! /bin/sh

nasm amd64-boot.asm -f bin -o amd64-boot.rom
nasm amd64-test.asm -f bin -o amd64-test.bin

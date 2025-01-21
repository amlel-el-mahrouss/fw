;; AMD64 CoreBoot Master Boot Program.
;; Written by Amlal EL Mahrouss

%define ENTRYPOINT 0x00FF

[bits 16]
[org ENTRYPOINT]

amd64_bios_start:
    cli
    cld

    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax

    jmp amd64_bios_programmable_area
    jmp 0x0000:0x7c00
    jmp $

amd64_vendor_information:
    db "ZKA", 0
    dw 0x010
amd64_vendor_information_end:

amd64_bios_programmable_area:
    times 1024 nop
    ret
amd64_bios_programmable_area_end:

times 2048-13-($-$$) nop

;; SIZE: 13 Bytes.
;; PURPOSE: BIOS Computer Metadata
amd64_bios_entrypoint_area:
    dw ENTRYPOINT ;; ENTRYPOINT.
    db "13/21/2024" ;; DATE.
    db 0x01 ;; VERSION.

;; AMD64 CoreBoot Sample program.
;; Written by Amlal EL Mahrouss

[bits 16]
[org 0x7c00]

; --------------
; Main entrypoint, just loop.
; --------------
amd64_main:
    jmp $
    cli
    hlt

times 512-6-2-2-($-$$) nop

db "BOOT1", 0 ;; Payload
dw 0x0100 ;; Version 1
dw 0 ;; Binary Blob

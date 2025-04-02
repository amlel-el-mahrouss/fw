/* -------------------------------------------

    Copyright (C) 2024-2025, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

.section .text
.global cb_reset_vector
cb_reset_vector:
    ldr x0, =0x40080000
    mov sp, x0         
    b cb_start_exec         



/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

.text
.balign 4
.global mp_start_context
.global mp_boot_processor_ready

mp_start_context:
    bl mp_start_context
    ldr pc, [lr]

mp_boot_processor_ready:
    ldr pc, [lr]

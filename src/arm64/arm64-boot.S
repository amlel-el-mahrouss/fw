/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

.text

.balign 4
.global mp_reset_vector

mp_reset_vector:
	ldr sp, =__mp_stack_end
	/* don't care about page_zero, it's gonna be a raw binary */
    b mp_start_exec

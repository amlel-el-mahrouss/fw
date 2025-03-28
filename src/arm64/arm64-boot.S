/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

.text

.balign 4
.global cb_reset_vector

cb_reset_vector:
	ldr sp, =__cb_stack_end
	/* don't care about page_zero, it's gonna be a raw binary */
    b cb_start_exec

.balign 4
.section .text

.global cb_reset_vector

cb_reset_vector:
	bl	.Laddr			/* get current address */
.Laddr:
	mflr	4			/* real address of .Laddr */
	lwz	0,(.Lstk-.Laddr)(4)	/* stack address location */
	mr	1,0			/* use user defined stack */

	addi	1,1,-4		/* make sure we don't overwrite debug mem */
	lis	0,0
	stw	0,0(1)		/* clear back chain */
	stwu	1,-64(1)		/* push another stack frame */

	/* Let her rip */

	bl 	cb_init_hw
	/* finally execute the firmware */
	bl	cb_start_exec
	/* return value from main is argument to exit */
	bl	cb_reset_vector

	trap

.global cb_start_rom
.global cb_start_context
.global cb_boot_processor_ready

.equ SYS_BOOT_ADDR, 0x1030000

cb_start_rom:
	lis 3, SYS_BOOT_ADDR@h
	addi 3, 3, SYS_BOOT_ADDR@l

	blr

cb_start_context:
	li 4, 0
	cmp 0, 0, 4, 3
	blt run_context
	mr 3, 31
	blr
run_context:
	blr /* r3 is filled here */

.Lstk:
/*	.long	__stack*/
	.long	stack_top

.data

cb_boot_processor_ready:
	.word 0

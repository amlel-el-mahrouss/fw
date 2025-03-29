/*
 *	========================================================
 *
 *	CoreBoot
 * 	Copyright 2024, Amlal EL Mahrouss, all rights reserved.
 *
 *  	Purpose: Startup code for RISC-V.
 *
 * 	========================================================
 */


/* Code starts at 8M, everything below is memory mapped hardware. */

.option norvc

.extern cb_start_exec

.global cb_reset_vector
.global cb_hart_present

.section .init
.align 4

cb_reset_vector:
	.cfi_startproc

	csrr t0, mhartid
	beqz t0, cb_start_exec_asm

	j cb_start_other

	.cfi_endproc

cb_start_exec_asm:
	lw t0, __cb_hart_counter
	lw t1, cb_boot_processor_ready

	not t0, t0

	addi t1, zero, 1

.option push
.option norelax

	la gp, cb_global_pointer

.option pop

	la sp, cb_stack_end

	la t5, _bss_start
	la t6, _bss_end

crt0_bss_clear:
	sd zero, (t5)
	addi t5, t5, 8
	bgeu t5, t6, crt0_bss_clear


	j cb_start_exec
	j cb_hang

cb_start_other:
	lw t1, cb_boot_processor_ready

cb_start_other_wait:
	beq t1, zero, cb_start_other_wait

	la t0, cb_stack_list
	ld t1, cb_stack_align
	mv sp, t0
	add t0, zero, t1
	j cb_hang

.global cb_start_rom
.global cb_start_context

cb_start_context:
	mv ra, zero
	add ra, zero, a1
	mret

.equ CB_BOOT_ADDR, 0x80020000

cb_start_rom:
	li x5, CB_BOOT_ADDR
	mv ra, zero
	add ra, zero, t0
	mret

cb_hang:
	j cb_start_exec
L0:
	wfi
	j L0

.bss

.align 4
cb_hart_present:
	.long 0

.data

.align 4
cb_stack_list:
	.long cb_memory_end

cb_stack_align:
	.word 0x8000

__cb_max_harts:
	.word 2

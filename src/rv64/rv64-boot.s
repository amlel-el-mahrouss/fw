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

.extern mp_start_exec

.global mp_reset_vector
.global mp_hart_present

.section .init
.align 4

mp_reset_vector:
	.cfi_startproc

	csrr t0, mhartid
	beqz t0, mp_start_exec_asm

	j mp_start_other

	.cfi_endproc

mp_start_exec_asm:
	lw t0, __mp_hart_counter
	lw t1, mp_boot_processor_ready

	not t0, t0

	addi t1, zero, 1

.option push
.option norelax

	la gp, mp_global_pointer

.option pop

	la sp, mp_stack_end

	la t5, _bss_start
	la t6, _bss_end

crt0_bss_clear:
	sd zero, (t5)
	addi t5, t5, 8
	bgeu t5, t6, crt0_bss_clear


	j mp_start_exec
	j mp_hang

mp_start_other:
	lw t1, mp_boot_processor_ready

mp_start_other_wait:
	beq t1, zero, mp_start_other_wait

	la t0, mp_stack_list
	ld t1, mp_stack_align
	mv sp, t0
	add t0, zero, t1
	j mp_hang

.global mp_start_rom
.global mp_start_context

mp_start_context:
	mv ra, zero
	add ra, zero, a1
	mret

.equ SYS_BOOT_ADDR, 0x80020000

mp_start_rom:
	li x5, SYS_BOOT_ADDR
	mv ra, zero
	add ra, zero, t0
	mret

mp_hang:
	j mp_start_exec
L0:
	wfi
	j L0

.bss

.align 4
mp_hart_present:
	.long 0

.data

.align 4
mp_stack_list:
	.long mp_memory_end

mp_stack_align:
	.word 0x8000

__mp_max_harts:
	.word 2

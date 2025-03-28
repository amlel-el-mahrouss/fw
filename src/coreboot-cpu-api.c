/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/boot.h>

/// @brief Restarts the computer.
/// @param none.
void cb_restart_machine(void)
{
#ifdef __COMPILE_RISCV__
	volatile uint32_t* brd_pwr = (volatile uint32_t*)0x100000;
	*brd_pwr				   = 0x7777; // send reboot signal from DMA.

	while (1)
	{
		asm volatile("wfi");
	}
#endif
}

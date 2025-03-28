/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/boot.h>

/// @brief Print firmware name.
/// @param
void cb_print_name(void)
{
#ifdef __COMPILE_POWERPC__
	cb_put_string(">> CoreBoot for POWER.\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_ARM64__
	cb_put_string(">> CoreBoot for ARM64.\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
	cb_put_string(">> CoreBoot for AMD64.\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_RISCV__
	cb_put_string(">> CoreBoot for RISC-V.\r\n");
#endif // __COMPILE_POWERPC__
}

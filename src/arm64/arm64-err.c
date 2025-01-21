/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/boot.h>

/// BUGS: 0

/// @brief Goes into a panic state.
/// @param reason why?
void mp_panic(const char* reason)
{
	mp_put_string("Error: ");
	mp_put_string(reason);
	mp_put_char('\n');

	while (yes)
	{
		asm volatile("hlt #0");
	}
}

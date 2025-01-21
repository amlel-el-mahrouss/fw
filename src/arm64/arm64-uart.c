/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/boot.h>
#include <lib/string.h>

/// BUGS: 0

#define ARM64_MMIO_REG(addr) (*(volatile uint32_t*)(mp_uart_ptr + addr))

/* this file handles the UART */

static uint32_t* mp_uart_ptr = (uint32_t*)SYS_UART_BASE;

// we need that one, to avoid sending mutliple chars to UART.
static boolean mp_locked_put_char = no;

utf_char_t mp_get_char(void)
{
	while ((ARM64_MMIO_REG(0x018) & (1 << 4)))
	{
	}

	return (utf_char_t)*mp_uart_ptr;
}

void mp_put_char(utf_char_t ch)
{
	while ((ARM64_MMIO_REG(0x018) & (1 << 5)))
	{
	}

	*mp_uart_ptr = ch;
}

/// @brief UART put string
/// @param text the input text.
size_t mp_put_string(const char* text)
{
	if (text == nil)
		return 0;

	size_t i = 0;

	for (; i < strlen(text); i++)
	{
		mp_put_char(text[i]);
	}

	return i;
}

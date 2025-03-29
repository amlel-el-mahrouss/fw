/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/boot.h>
#include <lib/string.h>

/// BUGS: 0

/* this file handles the UART */

static uint8_t* cb_uart_ptr = (uint8_t*)CB_UART_BASE;

utf_char_t cb_get_char(void)
{
	uintptr_t ptr = CB_UART_BASE;
	while (!(*(((volatile uint8_t*)ptr) + 0x05) & 0x01))
		;

	return (utf_char_t)*cb_uart_ptr;
}

// we need that one, to avoid sending mutliple chars to UART.
static boolean cb_locked_put_char = no;

void cb_put_char(utf_char_t ch)
{
	while (cb_locked_put_char)
	{
	}

	cb_locked_put_char = yes;
	*cb_uart_ptr	   = ch;
	cb_locked_put_char = no;
}

/// @brief UART put string
/// @param text the input text.
size_t cb_put_string(const char* text)
{
	if (text == nil)
		return 0;

	size_t i = 0;

	for (; i < strlen(text); i++)
	{
		cb_put_char(text[i]);
	}

	return i;
}

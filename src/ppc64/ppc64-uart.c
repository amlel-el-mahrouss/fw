/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/string.h>
#include <lib/boot.h>

/// BUGS: 0

#define SYS_NS16550_COM1 (SYS_UART_BASE + 0x4500)
#define SYS_NS16550_COM2 (SYS_UART_BASE + 0x4600)

volatile ascii_char_t* const UART0DR = (ascii_char_t*)SYS_NS16550_COM1;

/* this file handles the UART */

/// @brief Get character from UART.
/// @param
/// @return
utf_char_t mp_get_char(void)
{
	while (!(*(((volatile uint8_t*)UART0DR) + 0x05) & 0x01))
		;
	return (utf_char_t)*UART0DR;
}

/// @brief Put character into UART.
/// @param ch
void mp_put_char(utf_char_t ch)
{
	*UART0DR = (ascii_char_t)(ch);
}

/// @brief Put string in UART.
/// @param text the input text.
size_t mp_put_string(const char* text)
{
	while (*text != '\0')
	{ /* Loop until end of string */

		mp_put_char(*text); /* Transmit char */

		text++; /* Next char */
	}
	return 0;
}

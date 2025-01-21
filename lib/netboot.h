/* -------------------------------------------

    Copyright (C) 2025, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

#define NETBOOT_INET_MAGIC	   "NETB"
#define NETBOOT_INET_MAGIC_LEN 4

typedef struct NETBOOT_INET_HEADER
{
	char m_nb1; /// magic char 1 'N'
	char m_nb2; /// magic char 2 'E'
	char m_nb3; /// magic char 3 'T'
	char m_nb4; /// magic char 4 'B'

	char	m_patch_name[255]; /// example: ColdChoco
	int32_t m_length;		   /// the patch length.
	char	m_target[255];	   /// the target file.
	uint8_t ImpliesROM;		   /// does it imply an EEPROM reprogram?
	uint8_t m_preflight;
	uint8_t m_blob[];
} NETBOOT_INET_HEADER;

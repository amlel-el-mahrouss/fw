/* -------------------------------------------

    Copyright (C) 2025, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

#define NETBOOT_INET_MAGIC	   "NETB"
#define NETBOOT_INET_MAGIC_LEN 4

/// @brief Netboot Internet Header
/// Consists of 4 magic characters, and a set of fields describing the current patch that's being sent (if m_preflight = 0)
/// @note Can be used to patch ROMs too (if m_implies_rom = 1)
typedef struct NETBOOT_INET_HEADER
{
	char m_nb1; /// magic char 1 'N'
	char m_nb2; /// magic char 2 'E'
	char m_nb3; /// magic char 3 'T'
	char m_nb4; /// magic char 4 'B'

	char	m_patch_name[255]; /// example: ColdChoco
	int32_t m_length;		   /// The patch's length.
	char	m_target[255];	   /// The target file.
	uint8_t m_implies_rom;	   /// does it imply an EEPROM program?
	uint8_t m_preflight;	   /// Do we just check if this endpoint exists/is valid?
	uint8_t m_blob[];
} NETBOOT_INET_HEADER;

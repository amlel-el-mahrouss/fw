/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

    File: xcoff.h
    Purpose: XCOFF for CoreBoot.

    Revision History:

    04/07/24: Added file (amlel)

------------------------------------------- */

#ifndef __XCOFF__
#define __XCOFF__

#include <lib/boot.h>

#define XCOFF_MAG 0x01F7

#define XCOFF_REL_FLG	0x0001
#define XCOFF_EXEC_FLG	0x0002
#define XCOFF_LNNO_FLG	0x0004
#define XCOFF_SYMNS_FLG 0x0008

/// @brief XCoff identification header.
typedef struct _xcoff_header
{
	uint16_t magic;
	uint16_t target;
	uint16_t num_secs;
	uint32_t timestamp;
	uint64_t symptr;
	uint32_t numsyms;
	uint16_t opthdr; // ?: Number of bytes in optional header
} xcoff_header_t;

typedef xcoff_header_t xcoff_header64_t;
typedef xcoff_header_t xcoff_header32_t;

#endif // ifndef __XCOFF__

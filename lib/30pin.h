/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

/// @note This version is for the 30-pin recovery system.

/// @brief 30pin recovery header.
/// @param mag magic number.
/// @param kind kind of packet we deal with.
/// @param buffer the data of the packet.
/// @param eop end of packet data.
struct _cb_tpin_recovery_packet
{
	uint8_t mag[2];
	uint8_t kind;
	uint8_t buffer[498];
	uint8_t eop[11];
};

typedef struct _cb_tpin_recovery_packet cb_tpin_recovery_packet_t;
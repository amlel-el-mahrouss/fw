/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

/// @note This version is for the 30-pin recovery system.

struct TRB_PACKET
{
	char mag[2];
	char kind;
	char buffer[498];
	char eop[11];
};
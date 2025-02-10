/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/partition-map.h>

extern size_t mp_send_read_30pin(voidptr_t blob, size_t* size, size_t* start_lba);

/// @note This version is for the 30-pin recovery system.

struct TRB_PACKET
{
    char mag[2];
    char kind;
    char buffer[498];
    char eop[11];
};
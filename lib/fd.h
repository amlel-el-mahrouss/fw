/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

struct _mp_file_descriptor;

/// @brief CoreBoot file/device descriptor.
/// @version 1
typedef struct _mp_file_descriptor
{
	int32_t f_kind;
	int32_t f_filesystem;

	size_t (*f_write)(void* ptr, size_t size, size_t nitems, struct _mp_file_descriptor* self);
	size_t (*f_read)(void* ptr, size_t size, size_t nitems, struct _mp_file_descriptor* self);
	int (*f_seek)(struct _mp_file_descriptor* self, size_t off, int whence);
	int (*f_tell)(struct _mp_file_descriptor* self);
	int (*f_rewind)(struct _mp_file_descriptor* self);
	int (*f_eof)(struct _mp_file_descriptor* self);
	int (*f_close)(struct _mp_file_descriptor* self);
} mp_file_descriptor_t;

/// @brief Grabs a new device reference.
/// @param path the device path.
/// @return
mp_file_descriptor_t* mp_grab_fd(const char* path);

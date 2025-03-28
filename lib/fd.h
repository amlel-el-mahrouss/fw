/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

struct _cb_file_descriptor;

/// @brief CoreBoot file/device descriptor.
/// @version 1
typedef struct _cb_file_descriptor
{
	int32_t f_kind;
	int32_t f_filesystem;

	size_t (*f_write)(void* ptr, size_t size, size_t nitems, struct _cb_file_descriptor* self);
	size_t (*f_read)(void* ptr, size_t size, size_t nitems, struct _cb_file_descriptor* self);
	int (*f_seek)(struct _cb_file_descriptor* self, size_t off, int whence);
	int (*f_tell)(struct _cb_file_descriptor* self);
	int (*f_rewind)(struct _cb_file_descriptor* self);
	int (*f_eof)(struct _cb_file_descriptor* self);
	int (*f_close)(struct _cb_file_descriptor* self);
} cb_file_descriptor_t;

/// @brief Grabs a new device reference.
/// @param path the device path.
/// @return
cb_file_descriptor_t* cb_grab_fd(const char* path);

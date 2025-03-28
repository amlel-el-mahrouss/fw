/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#define DSO_MAX_OBJECTS (128)

struct atexit_func_entry_t
{
	void (*destructor_func)(void*);
	void* obj_ptr;
	void* dso_handle;
};

typedef unsigned uarch_t;

namespace cxxabiv1
{
	typedef void* __guard;
}

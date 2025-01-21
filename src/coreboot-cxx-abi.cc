/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/cxx-abi.h>

/// BUGS: 0

extern "C" __SIZE_TYPE__ mp_put_string(const char* text);
extern "C" void			 mp_panic(const char* reason);

extern "C" void __stack_chk_fail()
{
	mp_put_string("[stack-canary] Buffer overflow detected, halting...\n");
	mp_panic("stack_canary_fail");
}

void* __dso_handle;

extern "C" __SIZE_TYPE__ mp_put_string(const char* text);
extern "C" void			 mp_panic(const char* reason);

atexit_func_entry_t __atexit_funcs[DSO_MAX_OBJECTS];
uarch_t				__atexit_func_count;

extern "C" void __cxa_pure_virtual()
{
	mp_put_string("[__cxa_pure_virtual] Placeholder\n");
}

extern "C" int __cxa_atexit(void (*f)(void*), void* arg, void* dso)
{
	if (__atexit_func_count >= DSO_MAX_OBJECTS)
		return -1;

	__atexit_funcs[__atexit_func_count].destructor_func = f;
	__atexit_funcs[__atexit_func_count].obj_ptr			= arg;
	__atexit_funcs[__atexit_func_count].dso_handle		= dso;

	__atexit_func_count++;

	return 0;
}

extern "C" void __cxa_finalize(void* f)
{
	uarch_t i = __atexit_func_count;
	if (!f)
	{
		while (i--)
		{
			if (__atexit_funcs[i].destructor_func)
			{
				(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
			};
		}

		return;
	}

	while (i--)
	{
		if (__atexit_funcs[i].destructor_func)
		{
			(*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
			__atexit_funcs[i].destructor_func = 0;
		};
	}
}

namespace cxxabiv1
{
	extern "C" int __cxa_guard_acquire(__guard* g)
	{
		(void)g;
		return 0;
	}

	extern "C" int __cxa_guard_release(__guard* g)
	{
		*(char*)g = 1;
		return 0;
	}

	extern "C" void __cxa_guard_abort(__guard* g)
	{
		(void)g;
	}
} // namespace cxxabiv1

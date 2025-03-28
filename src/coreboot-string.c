/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

/**
 * @file coreboot-string.c
 * @author Amlal EL Mahrouss (amlal@nekernel.org)
 * @brief string library.
 * @version 0.1
 * @date 2024-01-16
 *
 * @copyright Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#include <lib/string.h>

/// BUGS: 0

size_t strncmp(const char* src, const char* cmp, size_t size)
{
	if (src == nil)
		return 0;

	int32_t counter = 0;

	for (size_t index = 0; index < size; ++index)
	{
		if (src[index] != cmp[index])
			++counter;
	}

	return counter;
}

void* memset(void* ptr, const char value, size_t len)
{
	if (ptr == nil)
		return nil;

	char* start = ptr;

	while (len)
	{
		*start = value;
		++start;

		--len;
	}

	return (void*)start;
}

void* memmove(void* dest, const void* src, size_t len)
{
	memncpy(dest, src, len);
	return dest;
}

size_t memcpy(void* dst, const void* src)
{
	if (src == nil || dst == nil)
		return 0;

	const char* src_chr = src;
	char*		dst_chr = dst;
	size_t		index	= 0;
	size_t		len		= strlen(src);

	while (index < len)
	{
		dst_chr[index] = src_chr[index];
		++index;
	}

	return 0;
}

/* @brief unoptimized memcpy, TODO: use isa specific memcpy. */
size_t memncpy(void* dst, const void* src, size_t len)
{
#if __OL == 3 && defined(__riscv)
	riscv_memncpy(dst, src, len);
#else

	if (src == nil || dst == nil)
		return 0;

	const char* src_chr = src;
	char*		dst_chr = dst;
	size_t		index	= 0;

	while (index < len)
	{
		dst_chr[index] = src_chr[index];
		++index;
	}

	return 0;
#endif
}

size_t strlen(const char* str)
{
	if (*str == 0)
		return 0;

	size_t len = 0;
	while (str[len] != '\0')
		++len;

	return len;
}

size_t strnlen(const char* str, size_t len)
{
	size_t cnt = 0;

	while (len > cnt)
	{
		++cnt;

		if (str[cnt] == '\0')
			return (size_t)-1;
	}

	return len;
}

void strreverse(char* s)
{
	if (s == nil)
		return;
	if (*s == '\0')
		return;

	char *first, *last, temp;

	first = s;
	last  = s + strlen(s) - 1;

	while (first != last)
	{
		temp	   = *first;
		*(first++) = *last;
		*(last--)  = temp;
	}
}

char* strchr(char* str, const char chr)
{
	while (*str != chr)
	{
		++str;

		if (*str == 0)
			return nil;
	}

	return str;
}

/// @brief Compare two strings.
/// @param src source string
/// @param cmp string to compare.
/// @return
size_t strcmp(caddr_t src, caddr_t cmp)
{
	if (src == null || *src == 0)
		return 1;
	if (cmp == null || *cmp == 0)
		return 1;

	int32_t counter = 0;

	for (size_t index = 0; src[index] != 0; ++index)
	{
		if (cmp[index] != src[index])
			++counter;
	}

	return counter;
}

/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

#define strncpy(DST, SRC, LEN) memncpy(DST, SRC, LEN)

void   strreverse(char* in_out);
size_t strlen(const char* in);
size_t strnlen(const char* in, size_t maxLen);
void*  memset(void* dst, const char val, size_t len);
size_t memcpy(void* dst, const void* src);
size_t memncpy(void* dst, const void* src, size_t len);
void*  memmove(void* dst, const void* src, size_t len);
size_t strncmp(const char* cmp1, const char* cmp2, size_t len);
char*  strchr(char* str, const char chr);

#define zero_memory(dst, sz) memset(dst, 0, sz)

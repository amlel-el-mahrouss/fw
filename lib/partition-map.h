/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef __PARTITION_MAP_H__
#define __PARTITION_MAP_H__

#include <lib/boot.h>

/* @brief AMD64 magic for EPM */
#define EPM_MAGIC_X86 "EPMAM"

/* @brief RISC-V magic for EPM */
#define EPM_MAGIC_RV "EPMRV"

/* @brief ARM magic for EPM */
#define EPM_MAGIC_ARM "EPMAR"

/* @brief 64x0 magic for EPM */
#define EPM_MAGIC_64X0 "EPM64"

/* @brief 32x0 magic for EPM */
#define EPM_MAGIC_32X0 "EPM32"

/* @brief POWER magic for EPM */
#define EPM_MAGIC_PPC "EPMPC"

#ifdef __aarch64__
#define EPM_MAGIC EPM_MAGIC_ARM
#elif defined(__riscv64__)
#define EPM_MAGIC EPM_MAGIC_RV
#else
#define EPM_MAGIC "EPMMS" /* mass storage */
#endif

#define EPM_MAX_BLKS 128 /* 1 on UEFI EPM. */

#define EPM_BOOT_BLK_SZ sizeof(struct boot_block)
#define EPM_PART_BLK_SZ sizeof(struct part_block)

/// @brief Start of EPM headers.
/// @note There could be anything before this LBA.
/// Such as PC specific structures.
#define EPM_PART_BLK_START (0)

/// @brief EPM revision (actually at version 2)
#define EPM_REVISION (2U)

/// @brief EPM GUID block.
typedef struct boot_guid
{
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t	 data4[8];
} boot_guid_t;

/* The first 0 > 128 addresses of a disk contains these headers. */

/**
 * @brief The EPM partition block.
 * used to represent a partition inside a media.
 */
struct __attribute__((packed)) part_block
{
	ascii_char_t magic[5];
	ascii_char_t name[32];
	boot_guid_t	 uuid;
	int32_t		 version;
	int32_t		 num_blocks;
	int64_t		 lba_start;
	int64_t		 sector_sz;
	int64_t		 lba_end;
	int16_t		 type;
	int32_t		 fs_version;
	ascii_char_t fs[16]; /* ffs_2 */
	ascii_char_t reserved[401];
};

typedef struct part_block part_block_t;

///! @brief variant enum.
///! use it in the boot block version field.
enum
{
	EPM_INVALID	   = 0x00,
	EPM_GENERIC_OS = 0xcf,
	EPM_LINUX	   = 0x8f,
	EPM_BSD		   = 0x9f,
	EPM_ZKAOS	   = 0x1f,
};

/// @brief check for supported filesystem.
boolean mp_filesystem_exists(caddr_t fs, size_t len);

/// @brief Parse EPM block from blob.
bool mp_parse_partition_block_data_at(voidptr_t blob, size_t blob_sz, size_t index, size_t* end_lba, size_t* start_lba, size_t* sector_sz);

part_block_t* mp_parse_partition_block_at(voidptr_t blob, size_t blob_sz, size_t index);

#endif // ifndef __PARTITION_MAP_H__

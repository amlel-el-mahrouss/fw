/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/partition-map.h>

bool cb_parse_partition_block_data_at(voidptr_t blob, size_t blob_sz, size_t index, size_t* end_lba, size_t* start_lba, size_t* sector_sz)
{
	if (!start_lba ||
		!end_lba ||
		!blob ||
		!blob_sz ||
		!sector_sz ||
		(sizeof(part_block_t) * index) > blob_sz)
		return false;

	part_block_t* block = (part_block_t*)(block + (sizeof(part_block_t) * index));

	if (block->version != EPM_REVISION ||
		block->num_blocks < 1 ||
		block->num_blocks > EPM_MAX_BLKS ||
		strcmp(block->magic, EPM_MAGIC) > 0 ||
		block->lba_end == 0 ||
		block->lba_start == 0)
	{
		return false;
	}

	*end_lba   = block->lba_end;
	*start_lba = block->lba_start;
	*sector_sz = block->sector_sz;

	return true;
}

part_block_t* cb_parse_partition_block_at(voidptr_t blob, size_t blob_sz, size_t index)
{
	if (!blob ||
		!blob_sz ||
		(sizeof(part_block_t) * index) > blob_sz)
		return nil;

	part_block_t* block = (part_block_t*)(block + (sizeof(part_block_t) * index));

	if (block->version != EPM_REVISION ||
		block->num_blocks < 1 ||
		block->num_blocks > EPM_MAX_BLKS ||
		strcmp(block->magic, EPM_MAGIC) > 0 ||
		block->lba_end == 0 ||
		block->lba_start == 0)
	{
		return nil;
	}

	return block;
}
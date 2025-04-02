/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/mp-bit.h>
#include <lib/partition-map.h>
#include <lib/pci-tree.h>
#include <lib/boot.h>

/// BUGS: 0

/////////////////////////////////////////////////////////////////////////////////////////

// @name start.c //

// @brief Start file // This is where the firmware starts it's initialization //
// code. //

// @author Amlal EL Mahrouss //

/////////////////////////////////////////////////////////////////////////////////////////

extern void cb_start_context(uintptr_t);
extern void cb_start_rom(void);

extern int cb_boot_processor_ready;

/// @brief hardware thread counter.

/// @brief Start executing the firmware.
/// @param
void cb_start_exec(void)
{
	static uint64_t __cb_hart_counter = 0UL;

	++__cb_hart_counter;

	uintptr_t hart = __cb_hart_counter;

	// let the hart 0 init our stuff.
	if (hart == 0)
	{
		cb_put_string("CB> Welcome to CoreBoot, (c) Amlal EL Mahrouss. Built the ");
		cb_put_string(__DATE__);
		cb_put_string("\r\r\n");

#ifdef __COMPILE_POWERPC__
		cb_put_string("CB> CPU: PowerPC 64-bit Based SoC.\r\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
		cb_put_string("CB> CPU: x64 Based SoC.\r\r\n");
#endif // __COMPILE_AMD64__

#ifdef __COMPILE_ARM64__
		cb_put_string("CB> CPU: AArch64 Based SoC.\r\r\n");
#endif // __COMPILE_ARM64__

#ifdef __COMPILE_ARM32__
		cb_put_string("CB> CPU: AArch32 Based SoC.\r\r\n");
#endif // __COMPILE_ARM64__

#ifdef __COMPILE_RISCV__
		cb_put_string("CB> CPU: RV64 Based SoC.\r\r\n");
#endif // __COMPILE_RISCV__
	}

	/// @brief Boots here if LX header matches what we except.

	volatile struct cb_boot_header* boot_hdr =
		(volatile struct cb_boot_header*)(CB_FLASH_BASE_ADDR);

	/**
	  boot if:
		  - ident matches.
		  - version matches.
  */

	if (boot_hdr->h_mag[0] == CB_BOOT_MAG_0 &&
		boot_hdr->h_mag[1] == CB_BOOT_MAG_1)
	{
		if (boot_hdr->h_revision != CB_BOOT_VER)
		{
			if (hart == 0)
			{
				cb_put_string("CB> Can't Boot the StageTwo, LX invalid signature. (CB0003)\r\n");
			}
		}
		else
		{
			if (hart == 0)
			{
				cb_pci_append_tree("@stage2-lx", (cb_pci_num_t)boot_hdr, sizeof(struct cb_boot_header));

				cb_put_string("CB> Executing StageTwo: ");
				cb_put_string((const char*)boot_hdr->h_name);
				cb_put_char('\r');
				cb_put_char('\n');

				// printf("CB> address: %x\n", boot_hdr->h_start_address);
			}

			if (boot_hdr->h_start_address != 0)
			{
				cb_boot_processor_ready = 1;
				cb_start_context(boot_hdr->h_start_address);
			}

			cb_put_string("CB> StageTwo has returned? (CB0002)\r\n");
		}
	}
	else
	{
		cb_put_string("CB> Trying EPM partition...\r\n");

		part_block_t* blk = cb_parse_partition_block_at((voidptr_t)CB_FLASH_BASE_ADDR, EPM_PART_BLK_SZ, 0);

		if (blk)
		{
			cb_pci_append_tree("@stage2-epm", (cb_pci_num_t)blk, sizeof(part_block_t) * blk->num_blocks);

			size_t indx = 0;
			size_t end_lba, start_lba, sector_sz;

			while (indx < blk->num_blocks)
			{
				if (cb_parse_partition_block_data_at(blk, EPM_PART_BLK_SZ * blk->num_blocks, indx, &end_lba, &start_lba, &sector_sz) == no)
				{
					++indx;
					continue;
				}

				cb_boot_processor_ready = 1;
				cb_start_context((uintptr_t)(voidptr_t)blk + start_lba);

				if (hart == 1)
				{
					cb_put_string("CB> Can't boot to StageTwo. (CB0001)\r\n");
				}
			}
		}

		if (hart == 1)
		{
			cb_put_string("CB> Can't boot to StageTwo via EPM, no bootable partition blocks found. (CB0001)\r\n");
		}
	}

	/// end of TODO

	if (hart > 1)
	{
		while (yes)
		{
			if (__cb_hart_counter == 0)
			{
				cb_restart_machine();
			}
		}
	}
}

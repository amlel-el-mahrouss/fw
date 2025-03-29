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

extern void cb_append_scsi_tree(void);
extern void cb_append_video_tree(void);

extern void cb_start_context(uintptr_t);
extern void cb_start_rom(void);

extern int cb_boot_processor_ready;

/// @brief hardware thread counter.
uint64_t __cb_hart_counter = 0UL;

/// @brief Start executing the firmware.
/// @param
void cb_start_exec(void)
{
	++__cb_hart_counter;

	uintptr_t hart = __cb_hart_counter;

	cb_sync_synchronize();

	// let the hart 0 init our stuff.
	if (hart == 1)
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
			if (hart == 1)
			{
				cb_put_string("CB> Can't Boot the Stage2, invalid signature. (CB0003)\r\n");
			}
		}
		else
		{
			if (hart == 1)
			{
				cb_put_string("CB> Executing Stage2: ");
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

			cb_put_string("CB> Stage2 has returned? (CB0002)\r\n");
		}
	}
	else
	{
		if (hart == 1)
		{
			cb_put_string("CB> Can't boot to Stage2. (CB0001)\r\n");
		}
	}

	/// end of TODO

	if (hart > 1)
	{
		while (1)
		{
			if (__cb_hart_counter == 0)
			{
				cb_restart_machine();
			}
		}
	}
}

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

extern void mp_append_scsi_tree(void);
extern void mp_append_video_tree(void);

extern void mp_start_context(uintptr_t);
extern void mp_start_rom(void);

extern int mp_boot_processor_ready;

/// @brief hardware thread counter.
uint64_t __mp_hart_counter = 0UL;

/// @brief Start executing the firmware.
/// @param
void mp_start_exec(void)
{
	++__mp_hart_counter;

	uintptr_t hart = __mp_hart_counter;

	mp_sync_synchronize();

	// let the hart 0 init our stuff.
	if (hart == 1)
	{
		mp_put_string("TQ> Welcome to CoreBoot, (c) Amlal EL Mahrouss. Built the ");
		mp_put_string(__DATE__);
		mp_put_string("\r\r\n");

#ifdef __COMPILE_POWERPC__
		mp_put_string("TQ> CPU: PowerPC 64-bit Based SoC.\r\r\n");
#endif // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
		mp_put_string("TQ> CPU: x64 Based SoC.\r\r\n");
#endif // __COMPILE_AMD64__

#ifdef __COMPILE_ARM64__
		mp_put_string("TQ> CPU: AArch64 Based SoC.\r\r\n");
#endif // __COMPILE_ARM64__

#ifdef __COMPILE_ARM32__
		mp_put_string("TQ> CPU: AArch32 Based SoC.\r\r\n");
#endif // __COMPILE_ARM64__

#ifdef __COMPILE_RISCV__
		mp_put_string("TQ> CPU: RV64 Based SoC.\r\r\n");
#endif // __COMPILE_RISCV__
	}

	/// @brief Boots here if LX header matches what we except.

	volatile struct mp_boot_header* boot_hdr =
		(volatile struct mp_boot_header*)(SYS_FLASH_BASE_ADDR);

	/**
      boot if:
          - ident matches.
          - version matches.
  */

	if (boot_hdr->h_mag[0] == SYS_BOOT_MAG_0 &&
		boot_hdr->h_mag[1] == SYS_BOOT_MAG_1)
	{
		if (boot_hdr->h_revision != SYS_BOOT_VER)
		{
			if (hart == 1)
			{
				mp_put_string("TQ> Can't Boot the Stage2, invalid signature. (CB0003)\r\n");
			}
		}
		else
		{
			if (hart == 1)
			{
				mp_put_string("TQ> Executing Stage2: ");
				mp_put_string((const char*)boot_hdr->h_name);
				mp_put_char('\r');
				mp_put_char('\n');

				// printf("TQ> address: %x\n", boot_hdr->h_start_address);
			}

			if (boot_hdr->h_start_address != 0)
			{
				mp_boot_processor_ready = 1;
				mp_start_context(boot_hdr->h_start_address);
			}

			mp_put_string("TQ> Stage2 has returned? (CB0002)\r\n");
		}
	}
	else
	{
		if (hart == 1)
		{
			mp_put_string("TQ> Can't boot to Stage2. (CB0001)\r\n");
		}
	}

	/// end of TODO

	if (hart > 1)
	{
		while (1)
		{
			if (__mp_hart_counter == 0)
			{
				mp_restart_machine();
			}
		}
	}
}

/* -------------------------------------------

	Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

/**
 * @file coreboot-ahci-driver.cc
 * @author Amlal EL Mahrouss (amlal@nekernel.org)
 * @brief SATA Disk support, via AHCI.
 * @version 0.2
 * @date 2024-01-16
 *
 * @copyright Copyright (c) 2024-2025, Amlal EL Mahrouss.
 *
 */

#include <lib/pci-tree.h>
#include <lib/boot.h>

#define SYS_AHCI_DRIVER_NAME ("@sata")

/// BUGS: 0
/// @brief AHCI support for PowerPC.

/// @brief AHCI HBA port.
typedef struct cb_hba_port
{
	uint32_t clb;			// 0x00, command list base address, 1K-byte aligned
	uint32_t clbu;			// 0x04, command list base address upper 32 bits
	uint32_t fb;			// 0x08, FIS base address, 256-byte aligned
	uint32_t fbu;			// 0x0C, FIS base address upper 32 bits
	uint32_t is;			// 0x10, interrupt status
	uint32_t ie;			// 0x14, interrupt enable
	uint32_t cmd;			// 0x18, command and status
	uint32_t reserved0;		// 0x1C, Reserved
	uint32_t tfd;			// 0x20, task file data
	uint32_t sig;			// 0x24, signature
	uint32_t ssts;			// 0x28, SATA status (SCR0:SStatus)
	uint32_t sctl;			// 0x2C, SATA control (SCR2:SControl)
	uint32_t serr;			// 0x30, SATA error (SCR1:SError)
	uint32_t sact;			// 0x34, SATA active (SCR3:SActive)
	uint32_t ci;			// 0x38, command issue
	uint32_t sntf;			// 0x20, SATA notification (SCR4:SNotification)
	uint32_t fbs;			// 0x40, FIS-based switch control
	uint32_t reserved1[11]; // 0x44 ~ 0x6F, Reserved
	uint32_t vendor[4];		// 0x70 ~ 0x7F, vendor specific
} cb_hba_port_t;

/// @brief Check if port is active.
/// @param port host bus address port.
/// @return
static boolean cb_hba_port_active(volatile cb_hba_port_t* port)
{
	if (!port)
		return false;

	return port->sact;
}

/// @brief Start HBA command.
/// @param port host bus address port.
/// @return
static boolean cb_hba_start_cmd(volatile cb_hba_port_t* port)
{
	if (!port)
		return false;

	size_t timeout = 1000000;

	while ((port->cmd & 0x8000))
	{
		if (!timeout)
			return false;

		--timeout;
	}

	port->cmd |= 0x0001;
	port->cmd |= 0x0010;

	return true;
}

/// @brief Stop HBA command.
/// @param port host bus address port.
/// @return
static boolean cb_hba_stop_cmd(volatile cb_hba_port_t* port)
{
	if (!port)
		return false;

	port->cmd &= ~0x0001;
	port->cmd &= ~0x0010;

	while (1)
	{
		if ((port->cmd & 0x8000))
			continue;

		if ((port->cmd & 0x4000))
			continue;

		break;
	}

	return true;
}

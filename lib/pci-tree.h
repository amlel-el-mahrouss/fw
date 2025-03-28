/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

/// @file pci-tree.h
/// @brief PCI Tree layout.
/// @author Amlal EL Mahrouss

#include <lib/boot.h>

#define PCI_INVALID_DATA_U8	 ((uint8_t)~0)
#define PCI_INVALID_DATA_U16 ((uint16_t)~0)
#define PCI_INVALID_DATA_U32 ((uint32_t)~0)

#define SYS_BASE_ADDRESS  (0x20008000) /* PCI base mapped in virtual memory. */
#define SYS_PCI_TREE_BASE (0x802000)   /* The PCI tree base address. */

#define PCI_CONFIG_SPACE (4096U)

#define PCI_BUS_MAX (256U)
#define PCI_DEV_MAX (32U)
#define PCI_FN_MAX	(8U)

/* version 1.0 */
#define SYS_PCI_VERSION (0x0100)

#define SYS_PCI_DEV_MAGIC (0xfeedd00d)
#define SYS_PCI_INT_SZ	  sizeof(cb_pci_num_t)

#define SYS_PCI_NAME_LEN (255U)

typedef char	  cb_pci_char_t;
typedef uintptr_t cb_pci_num_t;

typedef uint8_t cb_pci_fn_t;
typedef uint8_t cb_pci_bus_t;
typedef uint8_t cb_pci_device_t;

/// @brief hardware tree header
/// used by guest to resolve hardware peripherals.
struct hw_cb_pci_tree
{
	cb_pci_num_t d_magic;
	cb_pci_num_t d_version;
	cb_pci_num_t d_off_props;
	cb_pci_num_t d_off_struct;
	cb_pci_num_t d_sz_props;
	cb_pci_num_t d_sz_struct;

	cb_pci_num_t d_first_node;
	cb_pci_num_t d_next_sibling;

	cb_pci_char_t d_name[SYS_PCI_NAME_LEN];
};

/// @brief Init PCI tree.
/// @param void
/// @return if it's successful or not.
boolean cb_pci_init_tree(void);

/// @brief Adds a new tree into the internal data structure.
/// @param name device name
/// @param struct_ptr device structure
/// @param struct_sz the structure size of the device.
/// @return if it was successful or not.
boolean cb_pci_append_tree(const caddr_t name, cb_pci_num_t struct_ptr, cb_pci_num_t struct_sz);

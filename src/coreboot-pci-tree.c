/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

/**
 * @file coreboot-pci-tree.c
 * @author Amlal EL Mahrouss (amlal@nekernel.org)
 * @brief PCI tree implementation.
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024 Amlal EL Mahrouss
 *
 */

#include <lib/pci-tree.h>
#include <lib/string.h>

/// BUGS: 0

/// Standard Root table (Mahrouss Table)
#define SYS_PCI_ROOT_NAME "/pci-tree/@/"

static struct hw_cb_pci_tree* cb_base_tree	 = nil;
static struct hw_cb_pci_tree* cb_latest_tree = nil;
static struct hw_cb_pci_tree* cb_last_tree	 = nil;

/// \brief Init the PCI device tree structure.
/// \return if it already exists -> false
/// Otherwise true.
boolean cb_pci_init_tree(void)
{
	cb_base_tree = (struct hw_cb_pci_tree*)(SYS_PCI_TREE_BASE);

	// huh? anyway let's ignore it then.
	if (cb_base_tree->d_magic != SYS_PCI_DEV_MAGIC)
	{
		cb_base_tree->d_magic = SYS_PCI_DEV_MAGIC;

		memncpy(cb_base_tree->d_name, SYS_PCI_ROOT_NAME, strlen(SYS_PCI_ROOT_NAME));

		cb_base_tree->d_next_sibling = 0;
		cb_base_tree->d_off_props	 = 0;
		cb_base_tree->d_sz_struct	 = 0;
		cb_base_tree->d_sz_props	 = 0;
		cb_base_tree->d_off_struct	 = 0;
		cb_base_tree->d_version		 = SYS_PCI_VERSION;

		cb_base_tree->d_next_sibling =
			(cb_pci_num_t)(cb_base_tree + sizeof(struct hw_cb_pci_tree));
		cb_base_tree->d_first_node = (cb_pci_num_t)cb_base_tree;

		cb_put_string(">> Append root device: " SYS_PCI_ROOT_NAME "\r\n");
	}

	cb_latest_tree = cb_base_tree;

	return yes;
}

/// \brief Adds a new device to the tree.
/// \param name the device name.
/// \param struct_ptr the struct containing the device.
/// \param struct_sz the structure size.
boolean cb_pci_append_tree(const caddr_t name, cb_pci_num_t struct_ptr, cb_pci_num_t struct_sz)
{
	if (!name || *name == 0 || cb_latest_tree == nil)
		return no;

	struct hw_cb_pci_tree* cb_pci_tree = (struct hw_cb_pci_tree*)(cb_latest_tree);

	while (cb_pci_tree->d_magic == SYS_PCI_DEV_MAGIC)
	{
		if (strcmp(cb_pci_tree->d_name, name) == 0)
			return no;

		cb_pci_tree =
			(struct hw_cb_pci_tree*)(cb_pci_tree +
									 sizeof(struct hw_cb_pci_tree));
	}

	cb_pci_tree->d_magic = SYS_PCI_DEV_MAGIC;

	memncpy(cb_pci_tree->d_name, name, strlen(name));

	cb_pci_tree->d_off_struct = struct_ptr;
	cb_pci_tree->d_sz_struct  = struct_sz;
	cb_pci_tree->d_off_props  = 0;
	cb_pci_tree->d_sz_props	  = 0;
	cb_pci_tree->d_version	  = SYS_PCI_VERSION;

	cb_pci_tree->d_next_sibling =
		(cb_pci_num_t)(cb_pci_tree + sizeof(struct hw_cb_pci_tree));
	cb_pci_tree->d_first_node = (cb_pci_num_t)cb_latest_tree;

	cb_latest_tree = cb_pci_tree;
	cb_last_tree   = cb_pci_tree;

	cb_put_string(">> Append device: ");
	cb_put_string(name);
	cb_put_string("\r\n");

	return yes;
}

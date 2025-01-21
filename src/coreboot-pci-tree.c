/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

/**
 * @file coreboot-pci-tree.c
 * @author Amlal EL Mahrouss (amlal@el-mahrouss-logic.com)
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
#define SYS_PCI_ROOT_NAME "/elmh/@/"

static struct hw_mp_pci_tree* mp_base_tree	 = nil;
static struct hw_mp_pci_tree* mp_latest_tree = nil;
static struct hw_mp_pci_tree* mp_last_tree	 = nil;

/// \brief Init the PCI device tree structure.
/// \return if it already exists -> false
/// Otherwise true.
boolean mp_pci_init_tree(void)
{
	mp_base_tree = (struct hw_mp_pci_tree*)(SYS_PCI_TREE_BASE);

	// huh? anyway let's ignore it then.
	if (mp_base_tree->d_magic != SYS_PCI_DEV_MAGIC)
	{
		mp_base_tree->d_magic = SYS_PCI_DEV_MAGIC;

		memncpy(mp_base_tree->d_name, SYS_PCI_ROOT_NAME, strlen(SYS_PCI_ROOT_NAME));

		mp_base_tree->d_next_sibling = 0;
		mp_base_tree->d_off_props	 = 0;
		mp_base_tree->d_sz_struct	 = 0;
		mp_base_tree->d_sz_props	 = 0;
		mp_base_tree->d_off_struct	 = 0;
		mp_base_tree->d_version		 = SYS_PCI_VERSION;

		mp_base_tree->d_next_sibling =
			(mp_pci_num_t)(mp_base_tree + sizeof(struct hw_mp_pci_tree));
		mp_base_tree->d_first_node = (mp_pci_num_t)mp_base_tree;

		mp_put_string(">> Append root device: " SYS_PCI_ROOT_NAME "\r\n");
	}

	mp_latest_tree = mp_base_tree;

	return yes;
}

/// \brief Adds a new device to the tree.
/// \param name the device name.
/// \param struct_ptr the struct containing the device.
/// \param struct_sz the structure size.
boolean mp_pci_append_tree(const caddr_t name, mp_pci_num_t struct_ptr, mp_pci_num_t struct_sz)
{
	if (!name || *name == 0 || mp_latest_tree == nil)
		return no;

	struct hw_mp_pci_tree* mp_pci_tree = (struct hw_mp_pci_tree*)(mp_latest_tree);

	while (mp_pci_tree->d_magic == SYS_PCI_DEV_MAGIC)
	{
		if (strcmp(mp_pci_tree->d_name, name) == 0)
			return no;

		mp_pci_tree =
			(struct hw_mp_pci_tree*)(mp_pci_tree +
									 sizeof(struct hw_mp_pci_tree));
	}

	mp_pci_tree->d_magic = SYS_PCI_DEV_MAGIC;

	memncpy(mp_pci_tree->d_name, name, strlen(name));

	mp_pci_tree->d_off_struct = struct_ptr;
	mp_pci_tree->d_sz_struct  = struct_sz;
	mp_pci_tree->d_off_props  = 0;
	mp_pci_tree->d_sz_props	  = 0;
	mp_pci_tree->d_version	  = SYS_PCI_VERSION;

	mp_pci_tree->d_next_sibling =
		(mp_pci_num_t)(mp_pci_tree + sizeof(struct hw_mp_pci_tree));
	mp_pci_tree->d_first_node = (mp_pci_num_t)mp_latest_tree;

	mp_latest_tree = mp_pci_tree;
	mp_last_tree   = mp_pci_tree;

	mp_put_string(">> Append device: ");
	mp_put_string(name);
	mp_put_string("\r\n");

	return yes;
}

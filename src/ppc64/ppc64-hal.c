/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#include <lib/ppc64/mmu.h>
#include <lib/ppc64/processor.h>

#include <lib/pci-tree.h>
#include <lib/boot.h>

void mp_write_tlb(uint32_t mas0, uint32_t mas1, uint32_t mas2, uint32_t mas3, uint32_t mas7)
{
	mtspr(MAS0, mas0);
	mtspr(MAS1, mas1);
	mtspr(MAS2, mas2);
	mtspr(MAS3, mas3);
	mtspr(MAS7, mas7);

	mp_flush_tlb();
}

void mp_set_tlb(uint8_t	 tlb,
				uint32_t epn,
				uint64_t rpn,
				uint8_t	 perms,
				uint8_t	 wimge,
				uint8_t	 ts,
				uint8_t	 esel,
				uint8_t	 tsize,
				uint8_t	 iprot)
{
	if ((mfspr(SPRN_MMUCFG) & MMUCFG_MAVN) == MMUCFG_MAVN_V1 && (tsize & 1))
	{
		// this mmu-version does not allow odd tsize values
		return;
	}
	uint32_t mas0 = FSL_BOOKE_MAS0(tlb, esel, 0);
	uint32_t mas1 = FSL_BOOKE_MAS1(1, iprot, 0, ts, tsize);
	uint32_t mas2 = FSL_BOOKE_MAS2(epn, wimge);
	uint32_t mas3 = FSL_BOOKE_MAS3(rpn, 0, perms);
	uint32_t mas7 = FSL_BOOKE_MAS7(rpn);

	mp_write_tlb(mas0, mas1, mas2, mas3, mas7);
}

/// @brief Init hardware before jumping to kernel.
/// @param
void mp_init_hw(void)
{

	/// amlal:
	/// map VGA framebuffer
	mp_set_tlb(0, SYS_FRAMEBUFFER_ADDR, /* v_addr, 0x0000A0000 */
			   0x0000A000,				/* p_addr. 0x0000A0000  */
			   MAS3_SW | MAS3_SR,		/* perm  type=TLB_MAP_IO */
			   MAS2_I | MAS2_G,			/* wimge type=TLB_MAP_IO */
			   0,						/* ts i.e AS=0 */
			   1,						/* esel (a.k.a tlb_index*/
			   BOOKE_PAGESZ_64K,		/* tsize  ie 2^10kB ie 1MB */
			   1);

	// map ccsrbar and uart.
	// at start we execute from esel = 0, so chose something else..
	mp_set_tlb(1, SYS_UART_BASE,  /* v_addr   0xe0000000 see  qemu-ppce500.h */
			   0xfe0000000,		  /* p_addr. 0xfe0000000  */
			   MAS3_SW | MAS3_SR, /* perm  type=TLB_MAP_IO */
			   MAS2_I | MAS2_G,	  /* wimge type=TLB_MAP_IO */
			   0,				  /* ts i.e AS=0 */
			   2,				  /* esel (a.k.a tlb_index*/
			   BOOKE_PAGESZ_1M,	  /* tsize  ie 2^10kB ie 1MB */
			   1);

	/// amlal:
	/// map pci base for kernel
	mp_set_tlb(0, SYS_BASE_ADDRESS, /* v_addr, 0xFE008000 */
			   0xFE0008000,			/* p_addr. 0xfe0000000  */
			   MAS3_SW | MAS3_SR,	/* perm  type=TLB_MAP_IO */
			   MAS2_I | MAS2_G,		/* wimge type=TLB_MAP_IO */
			   0,					/* ts i.e AS=0 */
			   3,					/* esel (a.k.a tlb_index*/
			   BOOKE_PAGESZ_1M,		/* tsize  ie 2^10kB ie 1MB */
			   1);

	mp_pci_init_tree();

	mp_pci_append_tree("@fb", SYS_FRAMEBUFFER_ADDR, 0x0);
	mp_pci_append_tree("@mbci", 0x0, 0x0);
	mp_pci_append_tree("@serial", SYS_UART_BASE, 0);
	mp_pci_append_tree("@pci", SYS_BASE_ADDRESS, 0x0);

	mp_flush_tlb();
}

void mp_flush_tlb(void)
{
	asm volatile("isync;tlbwe;msync;isync");
};

==================================================================

                     Multi Platform Firmware

==================================================================

==================================================================
0. What we want:
==================================================================

- Optimized for each target.
- EPM/GPT compilant.
- AMD64, PowerPC, RISC-V, 64x0, 32x0 support.
- SMP support.

==================================================================
1. How we're going to do that:
==================================================================

- Abstract Memory and I/O. (pci-tree)
- Platform Independent Device Tree. (pci-tree)
- Common Starting point for each core (smp)

==================================================================
2. Executable Layout:
==================================================================

- 0x80000000/0x00FF/0x1000: Firmware Startup Code
- 0x90000000/0x7c00: Executable Information Header or equivalent.

==================================================================
3. Error Codes:
==================================================================

- CB0001: Not bootable to Stage2 (or bootloader).
- CB0003: Bad arch.
- CB0002: Context returned early.



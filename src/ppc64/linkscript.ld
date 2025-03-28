ENTRY(cb_reset_vector)
SECTIONS
{
  . = 0xf00000;

 .startup . : { ppc64-boot.o(.text) }
 .text : { *(.text) }
 .data : { *(.data) }
 .bss : { *(.bss COMMON) }
 . = ALIGN(8);
 . = . + 0x1000; /* 4kB of stack memory */
 stack_top = .;

 PROVIDE(cb_memory_end = .);
}

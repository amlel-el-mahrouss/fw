ENTRY(mp_reset_vector)
SECTIONS
{
  . = 0x40100000;

  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss COMMON) }
  . = ALIGN(8);
  . = . + 0x1000; /* 4kB of stack memory */
  __mp_stack_end = .;

  PROVIDE(mp_memory_end = .);
}

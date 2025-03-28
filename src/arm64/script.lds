ENTRY(cb_reset_vector)
SECTIONS
{
  . = 0x40100000;

  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss COMMON) }
  . = ALIGN(8);
  . = . + 0x1000; /* 4kB of stack memory */
  __cb_stack_end = .;

  PROVIDE(cb_memory_end = .);
}

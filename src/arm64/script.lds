ENTRY(cb_reset_vector)

SECTIONS
{
    . = 0x00000000;

    .text : {
        *(.text*)
    }

    .bss : {
        *(.bss*)
    }
}
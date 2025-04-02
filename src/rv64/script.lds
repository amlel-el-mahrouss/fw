ENTRY(cb_reset_vector);
 
. = 0x80000000;

SECTIONS {
	.text : ALIGN(4K) {
		PROVIDE(_text_start = .);

		*(.init);
		*(.text);

		PROVIDE(_text_end = .);
	}

	PROVIDE(cb_global_pointer = .);

	.bss : ALIGN(4K) {
		PROVIDE(_bss_start = .);
		
		*(.bss);

		PROVIDE(_bss_end = .);
	}

	.rodata : ALIGN(4K) {
		PROVIDE(_rodata_start = .);

		*(.rodata);
		
		PROVIDE(_rodata_end = .);
	}


	.data : ALIGN(4K) {
		PROVIDE(_data_start = .);

		*(.data);

		PROVIDE(_data_end = .);
	}

	PROVIDE(cb_stack_end = . + 0x1000);

	PROVIDE(cb_memory_end = .);
	PROVIDE(cb_boot_processor_ready = . + 0x4);
}

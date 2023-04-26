ENTRY(start)

SECTIONS {
     . = 1M;

    .text 0x0100000 : {
        /* set multiboot header */
        LONG(0x1BADB002)
        LONG(0x00000003)
        LONG(0xE4524FFB)
        *(.text) 
    }
   	.data : { *(.data) }
   	.bss  : { *(.bss)  }

}

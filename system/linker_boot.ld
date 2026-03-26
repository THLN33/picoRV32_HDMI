OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    BOOT_MEM (RWX) 	: ORIGIN = 0x00000000, LENGTH = 8K 
    /*RAM (rwx)		: ORIGIN = 0x20000000, LENGTH = 32K     */
}

_Minimum_Stack_Size = 0x100;

SECTIONS 
{

    /* text: test code section */
    .text :
    {
    	KEEP(*(.vectors))      /* Table des interruptions */
        *(.text)
        *(.rodata)
        *(.srodata)
        _etext = .;        /* define a global symbol at end of code */  
    } > BOOT_MEM


    .bss : 
    {
        . = ALIGN(4);
        _bss_start = .;         /* define a global symbol at bss start; used by startup code */        
        *(.bss)
        *(.bss*)
        *(.sbss)
        *(.sbss*)
        . = ALIGN(4);
        _bss_end = .;         /* define a global symbol at bss end; used by startup code */        
    } > BOOT_MEM


    /*
     * Used for validation only, do not allocate anything here!
     *
     * This is just to check that there is enough RAM left for the Main
     * stack. It should generate an error if it's full.
     */
    ._check_stack : ALIGN(4)
    {
        . = . + _Minimum_Stack_Size ;
	    PROVIDE (_end = .);
	    PROVIDE (end = .);           
    } > BOOT_MEM  

    /* Section Global Pointer (GP) for RISC-V */
    
    __global_pointer$ = ORIGIN(BOOT_MEM)  + 0x800;
    
    __stack_start = ORIGIN(BOOT_MEM) + LENGTH(BOOT_MEM);
    
    _end = .;

}
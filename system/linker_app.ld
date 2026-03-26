/* Spécification de l'architecture (Exemple RISC-V, à adapter si besoin) */
OUTPUT_ARCH("riscv")
ENTRY(_start)

_text_size = _etext - _stext;

MEMORY
{
    /* La RAM commence à 0x2000_0000 */
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 24K 
}

SECTIONS
{
		
    /* 1. Vecteurs d'interruption et Point d'entrée */
    /* On les place tout au début pour que le Bootloader sache où sauter */
    .text.entry :
    {
        _stext = .;
        KEEP(*(.text.entry))   /* Contient le Magic Number et le saut initial */
        KEEP(*(.vectors))      /* Table des interruptions */
    } > ram

    /* 2. Code du programme */
    .text :
    {
		_stext = .;          /* Début de la section text */    
        *(.text .text.*)
        *(.rodata .rodata.*)   /* Constantes et strings */
        _etext = .;
    } > ram

    /* 3. Section Global Pointer (GP) pour RISC-V */
    /* Le GP est placé au milieu des données statiques pour un accès rapide */
    . = ALIGN(4);
    __global_pointer$ = . + 0x800;

    /* 4. Données initialisées (.data) */
    /* Note : Ici LMA = VMA car on charge directement en RAM via XMODEM */
    .data :
    {
        _sdata = .;
        *(.data .data.*)
        *(.sdata .sdata.*)
        . = ALIGN(4);
        _edata = .;
    } > ram

    /* 5. Données non-initialisées (.bss) */
    .bss :
    {
        _sbss = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > ram

    /* 6. Définition de la Pile (Stack) */
    /* On la place tout en haut de la RAM pour qu'elle descende */
    /* _stack_top = ORIGIN(ram) + LENGTH(ram); */
    
    _end = .;
}
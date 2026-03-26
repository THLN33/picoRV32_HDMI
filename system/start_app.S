/*
 * start_app.S
 *
 *  Created on: 25 févr. 2026
 *      Author: thierry
 */

.section .text.entry
.global Magic_Number

    /* 1. Magic Number (4 octets) */
    .word 0x61706766    # "fpga" en ASCII

	.word 0x00000000	# App CRC set by bootloader

#	.word 0x00000000	# App size set by bootloader

text_size_word:
    .word _text_size

ramsize:
    .word 0x00000000	# Ram size

    /* 3. jump to start address (4 octets) */
    #j		_start


.section .vectors


.global _start

.text
_start:
	/* 1. Initialise la pile (Stack Pointer) */
    la   t0, ramsize
    lw   t1, 0(t0)
    bnez t1, _calc_sp
    li   t1, 0x2000         # 8192 octets
_calc_sp:
    li   t2, 0x20000000
    /* sp = 0x20000000 + ramsize */
    add  sp, t2, t1


    /* 2. Configuration du pointer global (GP) */
    .option push
    .option norelax
    la gp, __global_pointer$  	# Initialise le Global Pointer
    .option pop


    /* 3. Initialisation de la section .bss (Mise à zéro) */
    la t0, _sbss
    la t1, _ebss
bss_loop:
    beq t0, t1, bss_done
    sw zero, 0(t0)
    addi t0, t0, 4
    j bss_loop
bss_done:

    /* 4. Saut vers le main() de votre programme C */
    jal main

    /* 5. Boucle infinie si le main retourne */
loop_forever:
    j loop_forever


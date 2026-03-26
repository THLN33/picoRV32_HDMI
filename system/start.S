/*
 * start.S
 *
 *  Created on: 26 nov. 2025
 *      Author: thierry
 */


.global _start


.weak   main
#ifdef _Zicsr
.weak   irq_callback
.weak   esr_callback
#endif

.section .vectors
_start:
	j		startup



.text
.align 4

#ifdef _Zicsr
trap_entry:
	# save context
	sw 		x1,  - 1*4(sp)
	sw 		x5,  - 2*4(sp)
	sw 		x6,  - 3*4(sp)
	sw 		x7,  - 4*4(sp)
	sw 		x10, - 5*4(sp)
	sw 		x11, - 6*4(sp)
	sw 		x12, - 7*4(sp)
	sw 		x13, - 8*4(sp)
	sw 		x14, - 9*4(sp)
	sw 		x15, -10*4(sp)
	sw 		x16, -11*4(sp)
	sw 		x17, -12*4(sp)
	sw 		x28, -13*4(sp)
	sw 		x29, -14*4(sp)
	sw 		x30, -15*4(sp)
	sw 		x31, -16*4(sp)
	addi	sp,	sp,	-16*4
	csrr 	a0, mcause    # load mcause value as parameter
	bltz 	a0, __handle_isr
__handle_esr:
	csrr	a1, mepc
	mv   	a2, sp
	call 	esr_callback
	csrw	mepc, a0
  	j    	__handle_exit
__handle_isr:
  	call irq_callback
__handle_exit:
	# restore context
	lw 		x1 , 15*4(sp)
	lw 		x5,  14*4(sp)
	lw 		x6,  13*4(sp)
	lw 		x7,  12*4(sp)
	lw 		x10, 11*4(sp)
	lw 		x11, 10*4(sp)
	lw 		x12,  9*4(sp)
	lw 		x13,  8*4(sp)
	lw 		x14,  7*4(sp)
	lw 		x15,  6*4(sp)
	lw 		x16,  5*4(sp)
	lw 		x17,  4*4(sp)
	lw 		x28,  3*4(sp)
	lw 		x29,  2*4(sp)
	lw 		x30,  1*4(sp)
	lw 		x31,  0*4(sp)
	addi	sp, sp, 16*4
	mret
#endif

startup:
	// zero-initialize all registers
	mv		x1, zero
	mv		x2, zero
	mv		x3, zero
	mv		x4, zero
	mv		x5, zero
	mv		x6, zero
	mv		x7, zero
	mv		x8, zero
	mv		x9, zero
	mv		x10, zero
	mv		x11, zero
	mv		x12, zero
	mv		x13, zero
	mv		x14, zero
	mv		x15, zero
	mv		x16, zero
	mv		x17, zero
	mv		x18, zero
	mv		x19, zero
	mv		x20, zero
	mv		x21, zero
	mv		x22, zero
	mv		x23, zero
	mv		x24, zero
	mv		x25, zero
	mv		x26, zero
	mv		x27, zero
	mv		x28, zero
	mv		x29, zero
	mv		x30, zero
	mv		x31, zero

#ifdef _Zicsr
	l		t0, trap_entry
	csrw	mtvec, t0
	csrwi	mstatus, 0
	csrwi	mie, 0
#endif

.option push
.option norelax
  	la 		gp, __global_pointer$
.option pop

	la		sp, __stack_start

	// init bss section
bss_init:
  	la		a0, _bss_start
  	la		a1, _bss_end
bss_loop:
  	beq		a0, a1, bss_done
  	sw		zero, 0(a0)
  	add		a0,a0,4
  	j		bss_loop
bss_done:


	call	main
	call	_exit

infinitLoop:
	j		infinitLoop

test_ram:
	#mv		x3,
	nop
	ret


main:
_exit:
#ifdef _Zicsr
irq_callback:
#endif
	ret

#ifdef _Zicsr
esr_callback:
  j esr_callback
#endif









/*

.text

	jal		test_ram

	addi	x1, zero, 0
	addi	x2, zero, 0
	addi	x3, zero, 0
	addi	x4, zero, 0
	addi	x5, zero, 0
	addi	x6, zero, 0
	addi	x7, zero, 0
	addi	x8, zero, 0
	addi	x9, zero, 0
	addi	x10, zero, 0
	addi	x11, zero, 0
	addi	x12, zero, 0
	addi	x13, zero, 0
	addi	x14, zero, 0
	addi	x15, zero, 0
	addi	x16, zero, 0
	addi	x17, zero, 0
	addi	x18, zero, 0
	addi	x19, zero, 0
	addi	x20, zero, 0
	addi	x21, zero, 0
	addi	x22, zero, 0
	addi	x23, zero, 0
	addi	x24, zero, 0
	addi	x25, zero, 0
	addi	x26, zero, 0
	addi	x27, zero, 0
	addi	x28, zero, 0
	addi	x29, zero, 0
	addi	x30, zero, 0
	addi	x31, zero, 0
*/

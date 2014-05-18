.global _start
_start:
	b reset	/* CPU reset, jump to address 0x0 */
	b halt	@ldr pc, _undefined_instruction /* undefined instruction jump address 0x4 */
	b halt	@ldr pc, _vector_swi	/* SWI instruction jump address, enter SVC mode. 0x8 */
	b halt	@ldr pc, _prefetch_abort	/* prefetch abort exp. 0xc */
	b halt	@ldr pc, _data_abort	/* data access exp. 0xf */
	b halt	@ldr pc, _not_used	/* not used. 0x14 */
	ldr pc, _irq	/* interrupt exp. 0x18 */
	b halt 	@ldr pc, _fiq	/* fast interrupt exp. 0x1c */

_irq:
	.word vector_irq

reset:
	/* Peripheral port setup */
	ldr r0, =0x70000000
	orr r0, r0, #0x13
	mcr p15, 0, r0, c15, c2, 4	@ 256M(0x70000000-0x7fffffff)

	/* Write WTCON(0x7E004000) with 0 */
	ldr r0, =0x7e004000
	mov r1, #0
	str r1, [r0]

	/* Initialize sp and call c funtion */
	ldr sp, =8*1024

	/* Initialize Clock */
	bl clock_init 

	/* Initialize SDRAMC */
	bl sdram_init

	/* Initialize UART */
	bl uart_init

	/* relocation code and data sections */
	adr r0, _start	/* _start current address: 0x0 */
	ldr r1, =_start /* Link address: 0x50000000 */
	ldr r2, =bss_start /* bss section start address */
	sub r2, r2, r1
	
	cmp r0, r1
	beq clean_bss

	bl copy2ddr
	
	/* clean bss section */
clean_bss:
	ldr r0, =bss_start
	ldr r1, =bss_end
	mov r2, #0
clean_loop:
	str r2, [r0], #4
	cmp r0, r1
	bne clean_loop

	/* clean frame buffer section */
clean_fb:
	ldr r0, = framebuffer_start
	ldr r1, = framebuffer_end
	mov r2, #0
clean_fb_loop:
	str r2, [r0], #4
	cmp r0, r1
	bne clean_fb_loop
	ldr pc, =on_ddr

on_ddr:
	/* Initialize needed interrupt */
	bl irq_init
	mrs r0, cpsr
	bic r0, r0, #0x9f /* Enable IRQ */
	orr r0, r0, #0x1f
	msr cpsr, r0 /* Enter system mode */

	/* Initialize sp and call c funtion */
	ldr sp, =0x50000000 + 0xFA00000

	/* Jump runtime address */
	ldr pc, =app /* using location-relation code */
	
halt:
	b halt

vector_irq:
	/* 1. ... */
	ldr sp, =0x60000000
	sub lr, lr, #4 /* Be different from other exp. */
	stmdb sp!, {r0}
	mov r0, lr
	cps #31 /* system mode */
	stmdb sp!, {r0} /* pc */
	stmdb sp!, {r1-r12, lr}
	cps #0x12 /* irq mode */
	ldmia sp!, {r0}
	mrs r1, spsr
	cps #31
	stmdb sp!, {r0}
	stmdb sp!, {r1} /* spsr */
	ldr r0, =OSIntNesting
	ldrb r0, [r0]
	add r0, r0, #1
	cmp r0, #1
	bne IRQ_LABLE
	ldr r1, =OSTCBCur
	ldr r1, [r1]
	str sp, [r1]
	/* 2. ... */
IRQ_LABLE:
	bl do_irq
	/* 2.1 Find interrupt source */
	/* 2.2 Invoke ISR */
	/* 3. ... */
	ldmia sp!, {r0}
	msr cpsr, r0
	ldmia sp!, {r0-r12, lr, pc}
	mov r0, r0

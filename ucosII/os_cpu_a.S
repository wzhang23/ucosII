/********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                         (c) Copyright 2002, Jean J. Labrosse, Weston, FL
;                                          All Rights Reserved
;
;
;
; File         : OS_CPU_A.S
; By           : 
;
; Notes        : 
;********************************************************************************************************/

/********************************************************************************************************
;                               START HIGHEST PRIORITY TASK READY-TO-RUN
;
; Description : This function is called by OSStart() to start the highest priority task that was created
;               by your application before calling OSStart().
;
; Arguments   : none
;
; Note(s)     : 1) The stack frame is assumed to look as follows:
;   
;                  OSTCBHighRdy->OSTCBStkPtr +  0  -->  CPSR
;                                            +  1       R0
;                                            +  2       R1
;                                            +  3       R2
;                                            +  4       R3
;                                            +  5       R4
;                                            +  6       R5
;                                            +  7       R6
;                                            +  8       R7
;                                            +  9       R8
;                                            +  10      R9
;                                            +  11      R10
;                                            +  12      R11
;																						 +	13			R12
;																						 +	14			LR
;																						 +	15			PC
;
;               2) OSStartHighRdy() MUST:
;                      a) Call OSTaskSwHook() then,
;                      b) Set OSRunning to TRUE,
;                      c) Switch to the highest priority task by loading the stack pointer of the
;                         highest priority task into the SP register and execute an RTI instruction.
;********************************************************************************************************
*/
.global OSStartHighRdy
OSStartHighRdy:
	ldr r0, =OSRunning
	mov r1, #1
	strb r1, [r0]
	ldr r0, =OSTCBHighRdy
	ldr r0, [r0]
	ldr sp, [r0]
	ldmia sp!, {r0}
	msr cpsr, r0
	ldmia sp!, {r0-r12, lr, pc}

/********************************************************************************************************
;                                       TASK LEVEL CONTEXT SWITCH
;
; Description : This function is called when a task makes a higher priority task ready-to-run.
;
; Arguments   : none
;
; Note(s)     : 1) Upon entry, 
;                  OSTCBCur     points to the OS_TCB of the task to suspend
;                  OSTCBHighRdy points to the OS_TCB of the task to resume
;
;               2) The stack frame of the task to resume looks as follows:
; 
;                  OSTCBrHighRdy->OSTCBStkPtr +  0  -->  CPSR
;                                            +  1       R0
;                                            +  2       R1
;                                            +  3       R2
;                                            +  4       R3
;                                            +  5       R4
;                                            +  6       R5
;                                            +  7       R6
;                                            +  8       R7
;                                            +  9       R8
;                                            +  10      R9
;                                            +  11      R10
;                                            +  12      R11
;																						 +	13			R12
;																						 +	14			LR
;																						 +	15			PC
********************************************************************************************************
*/
.global OSCtxSw
OSCtxSw:
	/* push current task CPU context */
	stmdb sp!, {lr} /* push pc */
	stmdb sp!, {r0-r12, lr}
	mrs r0, cpsr
	stmdb sp!, {r0}

	/* Store current task stack pointer */
	ldr r0, =OSTCBCur
	ldr r0, [r0]
	str sp, [r0]

	bl OSTaskSwHook
	
	/* Get the next task TCB */
	ldr r0, =OSTCBHighRdy
	ldr r0, [r0]
	ldr r1, =OSTCBCur
	str r0, [r1]
	ldr r3, =OSPrioHighRdy
	ldr r3, [r3]
	ldr r4, =OSPrioCur
	str r3, [r4]

	/* Switch the next task's CPU context */
	ldr sp, [r0]
	ldmia sp!, {r0}
	msr cpsr, r0
	ldmia sp!, {r0-r12, lr, pc}

/********************************************************************************************************
;                                    INTERRUPT LEVEL CONTEXT SWITCH
;
; Description : This function is called by OSIntExit() to perform a context switch to a task that has
;               been made ready-to-run by an ISR. 
;
; Arguments   : none
;********************************************************************************************************
*/
.global OSIntCtxSw
OSIntCtxSw:                                  
	bl OSTaskSwHook
	/* Get the next task TCB */
	ldr r0, =OSTCBHighRdy
	ldr r0, [r0]
	ldr r1, =OSTCBCur
	str r0, [r1]
	ldr r3, =OSPrioHighRdy
	ldr r3, [r3]
	ldr r4, =OSPrioCur
	str r3, [r4]

	/* Switch the next task's CPU context */
	ldr sp, [r0]
	ldmia sp!, {r0}
	msr cpsr, r0
	ldmia sp!, {r0-r12, lr, pc}

/********************************************************************************************************
;                                           SYSTEM TICK ISR
;
; Description : This function is the ISR used to notify uC/OS-II that a system tick has occurred. 
;
; Arguments   : none
;
;********************************************************************************************************/
/*
*	Had been implemented in os_cpu_c.c
*/
 
/* End of File */

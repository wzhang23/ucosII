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
;********************************************************************************************************

;********************************************************************************************************
;                                           I/O PORT ADDRESSES
;********************************************************************************************************

;********************************************************************************************************
;                                          PUBLIC DECLARATIONS
;********************************************************************************************************
*/
    
/********************************************************************************************************
;                                         EXTERNAL DECLARATIONS
;********************************************************************************************************
*/

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
;                  OSTCBHighRdy->OSTCBStkPtr +  0  -->  pPAGE
;                                            +  1       rPAGE
;                                            +  2       ePAGE
;                                            +  3       gPAGE
;                                            +  1       CCRW
;                                            +  2       B
;                                            +  3       A
;                                            +  4       X (H)
;                                            +  5       X (L)
;                                            +  6       Y (H)
;                                            +  7       Y (L)
;                                            +  8       PC(H)
;                                            +  9       PC(L)
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
;               2) The stack frame of the task to suspend looks as follows:
;
;                  SP            CCR
;                     +  2       B
;                     +  3       A
;                     +  4       X (H)
;                     +  5       X (L)
;                     +  6       Y (H)
;                     +  7       Y (L)
;                     +  8       PC(H)
;                     +  9       PC(L)
;
;               3) The stack frame of the task to resume looks as follows:
; 
;                  OSTCBHighRdy->OSTCBStkPtr +  0  -->  pPAGE
;                                            +  1       rPAGE
;                                            +  2       ePAGE
;                                            +  3       gPAGE
;                                            +  4       CCR
;                                            +  6       B
;                                            +  7       A
;                                            +  8       X (H)
;                                            +  9       X (L)
;                                            + 10       Y (H)
;                                            + 11       Y (L)
;                                            + 12       PC(H)
;                                            + 13       PC(L)
;********************************************************************************************************
*/
.global OSCtxSw
OSCtxSw:                                        

/********************************************************************************************************
;                                    INTERRUPT LEVEL CONTEXT SWITCH
;
; Description : This function is called by OSIntExit() to perform a context switch to a task that has
;               been made ready-to-run by an ISR. The GPAGE, EPAGE, RPAGE and PPAGE CPU registers of the 
;               preempted task have already been stacked during the start of the ISR that is currently 
;               running.
;
; Arguments   : none
;********************************************************************************************************
*/
.global OSIntCtxSw
OSIntCtxSw:                                  

/********************************************************************************************************
;                                           SYSTEM TICK ISR
;
; Description : This function is the ISR used to notify uC/OS-II that a system tick has occurred.  You 
;               must setup the S12XE's interrupt vector table so that an OUTPUT COMPARE interrupt 
;               vectors to this function.
;
; Arguments   : none
;
; Notes       :  1) The 'tick ISR' assumes the we are using the Output Compare specified by OS_TICK_OC
;                   (see APP_CFG.H and this file) to generate a tick that occurs every OS_TICK_OC_CNTS 
;                   (see APP_CFG.H) which corresponds to the number of FRT (Free Running Timer) 
;                   counts to the next interrupt.
;
;                2) All USER interrupts should be modeled EXACTLY like this where the only
;                   line to be modified is the call to your ISR_Handler and perhaps the call to
;                   the label name OSTickISR1.
;********************************************************************************************************
*/
.global OSTickISR
OSTickISR:
    

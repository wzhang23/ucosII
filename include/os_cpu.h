/*
*********************************************************************************************************
*                                               uC/OS-II
*                                        The Real-Time Kernel
*
*                         (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
*                                       Compiler and Arch Specific code
*
* File         : OS_CPU.H
* By           : ZhangWei
*********************************************************************************************************
*/
#ifndef _OS_CPU_H_ 
#define _OS_CPU_H_

#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/
typedef unsigned int	OS_STK;                  /* Each stack entry is -bit wide	*/
typedef unsigned int	OS_CPU_SR;               /* The CPU Status Word is 32-bit wide	*/
typedef unsigned int	OS_FLAGS;   			 			 /* Date type for event flag bits (8, 16 or 32 bits)	*/

OS_CPU_SR disableInterrupts(void);
void enableInterrupts(OS_CPU_SR cpu_sr);
void os_timer_init(void);

/* 
*********************************************************************************************************
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if 
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to 
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/
#define  OS_CRITICAL_METHOD    3

#if	OS_CRITICAL_METHOD == 3
#define  OS_ENTER_CRITICAL()	cpu_sr = disableInterrupts()		/* store cpu status and disable interrupts */
#define  OS_EXIT_CRITICAL()		enableInterrupts(cpu_sr)				/* restore cpu status */
#endif

/*
*********************************************************************************************************
*                           Miscellaneous
*********************************************************************************************************
*/
#define  OS_STK_GROWTH      1                       /* Stack grows from HIGH to LOW memory */

#define  OS_TASK_SW()       OSCtxSw()								/* Switch context interrupt */ 

#endif

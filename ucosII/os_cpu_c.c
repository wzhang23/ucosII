/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                         (c) Copyright 2002, Jean J. Labrosse, Weston, FL
*                                          All Rights Reserved
*
*                                                 
*
* File         : OS_CPU_C.C
* By           : 
* Port Version : 
*********************************************************************************************************
*/
#include  "ucos_II.h"

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_VERSION > 203)
void  OSInitHookBegin (void)
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_VERSION > 203)
void  OSInitHookEnd (void)
{
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0)
void  OSTaskCreateHook (OS_TCB  *ptcb)
{
}
#endif


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0)
void  OSTaskDelHook (OS_TCB *ptcb)
{
}
#endif

/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_VERSION >= 251)
void  OSTaskIdleHook (void)
{
}
#endif

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/

#if (OS_CPU_HOOKS_EN > 0)
void  OSTaskStatHook (void)
{
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*
* Arguments  : task          is a pointer to the task code
*
*              p_arg         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then 
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : 
*********************************************************************************************************
*/
OS_STK *OSTaskStkInit (void (*task)(void *pd), void *p_arg, OS_STK *ptos, INT16U opt)
{
	OS_STK * fl_p_stk;

	opt = opt;

	fl_p_stk = ptos;

	/*
	 * The ARM stack using Full Decrement
	 */
	*(fl_p_stk) = (INT32U)task; /* pc */
	*(--fl_p_stk) = (INT32U)0;	/* lr */
	*(--fl_p_stk) = (INT32U)0;	/* R12 */
	*(--fl_p_stk) = (INT32U)0;	/* R11 */
	*(--fl_p_stk) = (INT32U)0;	/* R10 */
	*(--fl_p_stk) = (INT32U)0;	/* R9 */
	*(--fl_p_stk) = (INT32U)0;	/* R8 */
	*(--fl_p_stk) = (INT32U)0;	/* R7 */
	*(--fl_p_stk) = (INT32U)0;	/* R6 */
	*(--fl_p_stk) = (INT32U)0;	/* R5 */
	*(--fl_p_stk) = (INT32U)0;	/* R4 */
	*(--fl_p_stk) = (INT32U)0;	/* R3 */
	*(--fl_p_stk) = (INT32U)0;	/* R2 */
	*(--fl_p_stk) = (INT32U)0;	/* R1 */
	*(--fl_p_stk) = (INT32U)p_arg;	/* R0: argument */
	*(--fl_p_stk) = (INT32U)0x0000015f;	/* CPSR: enable IRQ, disable FIQ, system mode */

	return (fl_p_stk);
	/* Return pointer to new top-of-stack                   */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_TASK_SW_HOOK_EN > 0)
void  OSTaskSwHook (void)
{
}
#endif

/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OS_TCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_VERSION > 203)
void  OSTCBInitHook (OS_TCB *ptcb)
{
}
#endif

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if (OS_CPU_HOOKS_EN > 0) && (OS_TIME_TICK_HOOK_EN > 0) 
void  OSTimeTickHook (void)
{
}
#endif

/*
*********************************************************************************************************
*                                             disable global interrupt 
*
* Description: This function will disable global interrupt
*
* Arguments  : none
*
* Returns		:		OS_CPU_SR	-	the status of CPU
*********************************************************************************************************
*/
OS_CPU_SR disableInterrupts(void)
{
	OS_CPU_SR cpu_sr;
	
	asm __volatile__(
			"mrs r0, cpsr\n\t"\
			"str r0, %[asm_cpu_sr]\n\t"\
			"cpsid if"
			: [asm_cpu_sr] "+m" (cpu_sr)
			:
			: "memory"
	);	

	return cpu_sr;
}

/*
*********************************************************************************************************
*                                             enable global interrupts 
*
* Description: This function will restore CPU cpsr register
*
* Arguments  :	The CPU status had been stored.
*
* Returns		:	none 
*********************************************************************************************************
*/
void enableInterrupts(OS_CPU_SR cpu_sr)
{
	asm __volatile__(
		"ldr r0, %[asm_cpu_sr]\n\t"\
		"msr cpsr, r0"
		:
		: [asm_cpu_sr] "m" (cpu_sr)
	);
}

/*
*********************************************************************************************************
*                                            OS Tick timer ISR 
*
* Description: This function is the interrupt service routine of OS Tick timer
*
* Arguments  :	
*
* Returns		:	none 
*********************************************************************************************************
*/
void OSTickISR(void)
{
	VIC0VECTADDR_REG = 0;
	INTP_REG |= 0x01;
	OSTimeTick();
	OSIntExit();
}

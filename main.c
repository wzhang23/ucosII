/*
********************************************************************************************************
*                                      Real Time OS ucosII v2.52
*                                         Tiny6410 Port
* Original Version.
********************************************************************************************************
*/
#include "common.h"
#include "s3c6410.h"
#include "stdio.h"

#include "includes.h"

/*
*********************************************************************************************************
*                                       CONSTANTS DEFINES
*   i.e. task's stack size
*        task's priority
*        task's ID
*        so on...
*********************************************************************************************************
*/
#define TASK_STK_SIZE	512

#define TASK_START_ID     0
#define TASK_LED_ID       1
#define TASK_STK_CHK_ID   2

#define TASK_START_PRIO   10
#define TASK_LED_PRIO     11
#define TASK_STK_CHK_PRIO 13

/*
*********************************************************************************************************
*                                         VARIABLES
*   i.e. task's stack and so on.
*********************************************************************************************************
*/
OS_STK  TaskStartStk[TASK_STK_SIZE];
OS_STK  TaskLEDStk[TASK_STK_SIZE];
OS_STK  TaskStkChkStk[TASK_STK_SIZE];

/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*   i.e. task start function
*        create multi-tasks function
*********************************************************************************************************
*/
       void TaskStart(void *);
static void TaskStartCreateTasks(void);
       void TaskLED(void *);
       void TaskStkChk(void *);

/*
*********************************************************************************************************
*                                           MAIN
*********************************************************************************************************
*/
void main(void) 
{
	OS_STK *ptos;
	OS_STK *pbos;
	INT16U size;
  
	OSInit();
	
	ptos = &TaskStartStk[TASK_STK_SIZE-1];
	pbos = &TaskStartStk[0];
	size = TASK_STK_SIZE;
	
	OSTaskCreateExt(TaskStart,
	                (void *)0,
	                ptos,
	                TASK_START_PRIO,
	                TASK_START_ID,
	                pbos,
	                size,
	                (void *)0,
	                OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
	                
	OSStart();		 
}

/*
*********************************************************************************************************
*                                   TASK START FUNCTION
*********************************************************************************************************
*/
void TaskStart(void * pdata)
{
#if OS_CRITICAL_METHOD == 3         /* Allocate storage for CPU status 
register             */
    OS_CPU_SR  cpu_sr;
#endif

	pdata = pdata;
	
	OS_ENTER_CRITICAL();
	//OSTimer_init();
	OS_EXIT_CRITICAL();
	
	OSStatInit();                   /* Initialize Statistics Task */
	
	TaskStartCreateTasks();         /* Create Tasks */
	
	for(;;) {
		OSCtxSwCtr = 0;
		OSTimeDly(OS_TICKS_PER_SEC);
	}
}

/*
*********************************************************************************************************
*                                         CREATE TASKS
*********************************************************************************************************
*/
static void TaskStartCreateTasks(void)
{
    OSTaskCreateExt(TaskLED,
                    (void *)0,
                    &TaskLEDStk[TASK_STK_SIZE-1],
                    TASK_LED_PRIO,
                    TASK_LED_ID,
                    &TaskLEDStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(TaskStkChk,
                    (void *)0,
                    &TaskStkChkStk[TASK_STK_SIZE-1],
                    TASK_STK_CHK_PRIO,
                    TASK_STK_CHK_ID,
                    &TaskStkChkStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
}

/*
*********************************************************************************************************
*                                           LED TASK
*********************************************************************************************************
*/
void TaskLED(void *pdata)
{
    pdata = pdata;
  
    for(;;) {
        OSTimeDly(OS_TICKS_PER_SEC);
    }
}

/*
*********************************************************************************************************
*                                       STACK CHECK TASK
*********************************************************************************************************
*/
void TaskStkChk(void *pdata)
{
    OS_STK_DATA idle_data, stat_data, startTask_data, led_data,
                stkchk_data;
  
    pdata = pdata;
  
    for(;;) {
        
        OSTaskStkChk(TASK_START_PRIO, &startTask_data);
        OSTaskStkChk(TASK_LED_PRIO, &led_data);
        OSTaskStkChk(63, &idle_data);
        OSTaskStkChk(62, &stat_data);
        OSTaskStkChk(TASK_STK_CHK_PRIO, &stkchk_data);
        OSTimeDly(OS_TICKS_PER_SEC);
    }
}

void print_cpsr(INT16U cpsr, INT8U *str)
{
	printf("%s is: 0x%x\n\r", str, cpsr);
}
/*
 * End of File
 */

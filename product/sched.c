/*
********************************************************************************************************
*                                      Real Time OS ucosII v2.52
*                                         Tiny6410 Port
* Original Version.
********************************************************************************************************
*/
/*
 * Header files 
 */
#include "includes.h"	/* user top header file */
#include "stdio.h"


/*
*********************************************************************************************************
*                                       TYPES DEFINITION
*********************************************************************************************************
*/
/*
 * Define the struct of the task's parameters
 */
typedef struct
{
	INT32U id;
	INT8U prio;
	void ((*task)(void*));
	OS_STK * ptos;
	OS_STK * pbos;
	INT32U stk_size;
	OS_STK_DATA stk_chk_data;
} TASK_PARA_ST;

/*
*********************************************************************************************************
*                                       MACROS DEFINITION
*********************************************************************************************************
*/
#define TASK_STK_SIZE	512

#define TASK_START_ID			0
#define TASK_1MS_ID				1
#define TASK_10MS_ID			2 
#define TASK_20MS_ID			3
#define TASK_50MS_ID			4
#define TASK_100MS_ID			5
#define	TASK_500MS_ID			6
#define	TASK_1KMS_ID			7
#define TASK_STK_CHK_ID   8

#define TASK_START_PRIO		0
#define TASK_1MS_PRIO			1
#define TASK_10MS_PRIO		2 
#define TASK_20MS_PRIO		3
#define TASK_50MS_PRIO		4
#define TASK_100MS_PRIO		5
#define	TASK_500MS_PRIO		6
#define	TASK_1KMS_PRIO		7
#define TASK_STK_CHK_PRIO 8

#define TASK_STACK_CHECK_ENABLE

/*
*********************************************************************************************************
*                                         Global VARIABLES
*   i.e. task's stack and so on.
*********************************************************************************************************
*/
OS_STK  TaskStartStk[TASK_STK_SIZE];
OS_STK  Task1MSStk[TASK_STK_SIZE];
OS_STK  Task10MSStk[TASK_STK_SIZE];
OS_STK  Task20MSStk[TASK_STK_SIZE];
OS_STK  Task50MSStk[TASK_STK_SIZE];
OS_STK  Task100MSStk[TASK_STK_SIZE];
OS_STK  Task500MSStk[TASK_STK_SIZE];
OS_STK  Task1KMSStk[TASK_STK_SIZE];
#ifdef TASK_STACK_CHECK_ENABLE
OS_STK  TaskStkChkStk[TASK_STK_SIZE];
#endif

/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*   i.e. task start function
*        create multi-tasks function
*********************************************************************************************************
*/
       void TaskStart(void *);
       void Task1MS(void *);
       void Task10MS(void *);
       void Task20MS(void *);
       void Task50MS(void *);
       void Task100MS(void *);
       void Task500MS(void *);
       void Task1KMS(void *);
#ifdef TASK_STACK_CHECK_ENABLE
       void TaskStkChk(void *);
#endif
static void TaskStartCreateTasks(void);

/*
*********************************************************************************************************
*                                         GLOBAL
*********************************************************************************************************
*/
TASK_PARA_ST task_para[] =
{
	{0, 0, TaskStart, &TaskStartStk[TASK_STK_SIZE-1], &TaskStartStk[0], TASK_STK_SIZE, {0,0}},
	{1, 1, Task1MS, &Task1MSStk[TASK_STK_SIZE-1], &Task1MSStk[0], TASK_STK_SIZE, {0,0}},
	{2, 2, Task10MS, &Task10MSStk[TASK_STK_SIZE-1], &Task10MSStk[0], TASK_STK_SIZE, {0,0}},
	{3, 3, Task20MS, &Task20MSStk[TASK_STK_SIZE-1], &Task20MSStk[0], TASK_STK_SIZE, {0,0}},
	{4, 4, Task50MS, &Task50MSStk[TASK_STK_SIZE-1], &Task50MSStk[0], TASK_STK_SIZE, {0,0}},
	{5, 5, Task100MS, &Task100MSStk[TASK_STK_SIZE-1], &Task100MSStk[0], TASK_STK_SIZE, {0,0}},
	{6, 6, Task500MS, &Task500MSStk[TASK_STK_SIZE-1], &Task500MSStk[0], TASK_STK_SIZE, {0,0}},
	{7, 7, Task1KMS, &Task1KMSStk[TASK_STK_SIZE-1], &Task1KMSStk[0], TASK_STK_SIZE, {0,0}},
#ifdef TASK_STACK_CHECK_ENABLE
	{8, 8, TaskStkChk, &TaskStkChkStk[TASK_STK_SIZE-1], &TaskStkChkStk[0], TASK_STK_SIZE, {0,0}},
#endif
};

/*
*********************************************************************************************************
*                                          Application 
*********************************************************************************************************
*/
void app(void) 
{
	OSInit();
	
	OSTaskCreateExt(task_para[TASK_START_ID].task,
	                (void *)0,
	                task_para[TASK_START_ID].ptos,
	                task_para[TASK_START_ID].prio,
	                task_para[TASK_START_ID].id,
	                task_para[TASK_START_ID].pbos,
	                task_para[TASK_START_ID].stk_size,
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
#if OS_CRITICAL_METHOD == 3         /* Allocate storage for CPU status register             */
  OS_CPU_SR  cpu_sr;
#endif

	pdata = pdata;

	printf("Task start!\r\n");
	OS_ENTER_CRITICAL();
	os_timer_init();
	OS_EXIT_CRITICAL();
	
#if OS_TASK_STAT_EN > 0
	OSStatInit();                   /* Initialize Statistics Task */
#endif
	
	TaskStartCreateTasks();         /* Create Tasks */
	
	for(;;) {
		printf("OS context switch counter:%d\r\n", OSCtxSwCtr);
		printf("OS CPU Usage:%d%%\r\n", OSCPUUsage);
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
	INT8U fl_index = 1; /* Task start had been created */
	INT8U fl_total_task = sizeof(task_para)/sizeof(TASK_PARA_ST);

	for(fl_index = 1; fl_index < fl_total_task; ++fl_index)
	{
    OSTaskCreateExt(task_para[fl_index].task,
                    (void *)0,
										task_para[fl_index].ptos,
										task_para[fl_index].prio,
										task_para[fl_index].id,
										task_para[fl_index].pbos,
										task_para[fl_index].stk_size,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
	}
}

/*
*********************************************************************************************************
*                                           1MS TASK
*********************************************************************************************************
*/
void Task1MS(void *pdata)
{
	pdata = pdata;
  
	printf("Task1MS started!\r\n");

	for(;;) {
		//printf("Task 1MS going!!!\r\n");
		OSTimeDly(1);
	}
}

/*
*********************************************************************************************************
*                                           10MS TASK
*********************************************************************************************************
*/
void Task10MS(void *pdata)
{
	pdata = pdata;
  
	printf("Task10MS started!\r\n");

	for(;;) {
		//printf("Task 10MS going!!!\r\n");
		OSTimeDly(10);
	}
}

/*
*********************************************************************************************************
*                                           20MS TASK
*********************************************************************************************************
*/
void Task20MS(void *pdata)
{
	pdata = pdata;
  
	printf("Task20MS started!\r\n");

	for(;;) {
		//printf("Task 20MS going!!!\r\n");
		OSTimeDly(20);
	}
}

/*
*********************************************************************************************************
*                                           50MS TASK
*********************************************************************************************************
*/
void Task50MS(void *pdata)
{
	pdata = pdata;
  
	printf("Task50MS started!\r\n");

	for(;;) {
		//printf("Task 50MS going!!!\r\n");
		OSTimeDly(50);
	}
}

/*
*********************************************************************************************************
*                                           100MS TASK
*********************************************************************************************************
*/
void Task100MS(void *pdata)
{
	pdata = pdata;
  
	printf("Task100MS started!\r\n");

	for(;;) {
		//printf("Task 100MS going!!!\r\n");
		OSTimeDly(100);
	}
}

/*
*********************************************************************************************************
*                                           500MS TASK
*********************************************************************************************************
*/
void Task500MS(void *pdata)
{
	pdata = pdata;
  
	GPKDAT_REG |= 0x20;
	GPKCON0_REG = (GPKCON0_REG & ~0x00f00000) | 0x00100000;
	printf("Task500MS started!\r\n");

	for(;;) {
		if((GPKDAT_REG & 0x20) == 0)
		{
			GPKDAT_REG |= 0x20;
		}
		else
		{
			GPKDAT_REG &= ~0x20;
		}
		OSTimeDly(OS_TICKS_PER_SEC/2);
	}
}

/*
*********************************************************************************************************
*                                           1KMS TASK
*********************************************************************************************************
*/
void Task1KMS(void *pdata)
{
	pdata = pdata;
  
	GPKDAT_REG |= 0x10;
	GPKCON0_REG = (GPKCON0_REG & ~0x000f0000) | 0x00010000;
	printf("Task1KMS started!\r\n");

	for(;;) {
		if((GPKDAT_REG & 0x10) == 0)
		{
			GPKDAT_REG |= 0x10;
		}
		else
		{
			GPKDAT_REG &= ~0x10;
		}
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
	INT8U fl_index = 0;
	INT8U fl_total_task = sizeof(task_para)/sizeof(TASK_PARA_ST);

  pdata = pdata;
  
	printf("TaskStkChk started!\r\n");

  for(;;) {
		for(fl_index = 0; fl_index < fl_total_task; ++fl_index)
		{
			OSTaskStkChk(task_para[fl_index].prio, &task_para[fl_index].stk_chk_data);
			printf("[%02d] used: %4d, free: %4d\r\n", task_para[fl_index].id, \
					task_para[fl_index].stk_chk_data.OSUsed, task_para[fl_index].stk_chk_data.OSFree);
		}
    OSTimeDly(OS_TICKS_PER_SEC);
  }
}

/*
 * End of File
 */

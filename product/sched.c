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
*                                       CONSTANTS DEFINITION
*   i.e. task's stack size
*        task's priority
*        task's ID
*        etc ...
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
OS_STK  TaskStkChkStk[TASK_STK_SIZE];

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
       void TaskStkChk(void *);
static void TaskStartCreateTasks(void);

/*
*********************************************************************************************************
*                                          Application 
*********************************************************************************************************
*/
void app(void) 
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
    OSTaskCreateExt(Task1MS,
                    (void *)0,
                    &Task1MSStk[TASK_STK_SIZE-1],
                    TASK_1MS_PRIO,
                    TASK_1MS_ID,
                    &Task1MSStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(Task10MS,
                    (void *)0,
                    &Task10MSStk[TASK_STK_SIZE-1],
                    TASK_10MS_PRIO,
                    TASK_10MS_ID,
                    &Task10MSStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(Task20MS,
                    (void *)0,
                    &Task20MSStk[TASK_STK_SIZE-1],
                    TASK_20MS_PRIO,
                    TASK_20MS_ID,
                    &Task20MSStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(Task50MS,
                    (void *)0,
                    &Task50MSStk[TASK_STK_SIZE-1],
                    TASK_50MS_PRIO,
                    TASK_50MS_ID,
                    &Task50MSStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(Task100MS,
                    (void *)0,
                    &Task100MSStk[TASK_STK_SIZE-1],
                    TASK_100MS_PRIO,
                    TASK_100MS_ID,
                    &Task100MSStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(Task500MS,
                    (void *)0,
                    &Task500MSStk[TASK_STK_SIZE-1],
                    TASK_500MS_PRIO,
                    TASK_500MS_ID,
                    &Task500MSStk[0],
                    TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(Task1KMS,
                    (void *)0,
                    &Task1KMSStk[TASK_STK_SIZE-1],
                    TASK_1KMS_PRIO,
                    TASK_1KMS_ID,
                    &Task1KMSStk[0],
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
  
	printf("Task500MS started!\r\n");

	for(;;) {
		//printf("Task 500MS going!!!\r\n");
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
  
	printf("Task1KMS started!\r\n");

	for(;;) {
		printf("Task 1KMS going!!!\r\n");
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
  OS_STK_DATA idle_data, stkchk_data;
#if OS_TASK_STAT_EN > 0
	OS_STK_DATA stat_data; 
#endif
  
  pdata = pdata;
  
	printf("TaskStkChk started!\r\n");

  for(;;) {
        
		printf("Task stack check going!!!\r\n");
    OSTaskStkChk(63, &idle_data);
	#if OS_TASK_STAT_EN > 0
    OSTaskStkChk(62, &stat_data);
	#endif
    OSTaskStkChk(TASK_STK_CHK_PRIO, &stkchk_data);
    OSTimeDly(OS_TICKS_PER_SEC);
  }
}

/*
 * End of File
 */

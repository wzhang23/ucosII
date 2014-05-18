/****
 * HMI application implementation.
 * Including hmi initialize and step function
 * Author				: weiz
 * Create Date	: 5/18/2014
 * 5/18/2014	:	init version	
 ****/

/****
 * Header files
 ****/
#include "hmi_rte.h"

/**** 
 * Functions prototypes
 ****/
/*
 * Name				:	HMIInit
 * Inputs			: None
 * Outputs		:	None
 * Description:	initialize lcd driver and global variables
 * Invoked		:	Backgound task initialize routine
 * Critical		: None
 */
void HMIInit(void)
{
	HMI_RTE_Init();
}
/*
 * Name				:	HMIStep
 * Inputs			: None
 * Outputs		:	None
 * Description:	HMI step function, invoked by OS task.
 * Invoked		: Background task
 * Critical		:	None
 */
void HMIStep(void)
{
	static INT8U fl_ch = 0;

	HMI_Write_CurCursorX(400);
	HMI_Write_CurCursorY(240);
	HMI_Write_CurBGColor(HMI_RED);
	HMI_Write_CurFGColor(HMI_BLUE);
	HMI_Write_CurChar(fl_ch++);
	HMI_Validation(TRUE);
}
/****
 * EOF
 ****/

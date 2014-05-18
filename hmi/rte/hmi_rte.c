/****
 * HMI runtime layer
 * Autor				:	weiz
 * Create Date	:	5/18/2014
 * 5/18/2014	init version
 ****/

/****
 * Header files
 ****/
#include "lcd01_drv.h"
#include "hmi_rte.h"
#include "fonts_8x8.h"

/****
 * Global variables
 ****/
static HMI_RTE_st rte_data = {0};

/****
 * Functions prototypes
 ****/
/*
 * Names		: HMI_RTE_Init
 * Inputs		:	None
 * Outputs	:	None
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_RTE_Init(void)
{
	lcd01_init();
	rte_data.x = 0;
	rte_data.y = 0;
	rte_data.bg_color = HMI_BLACK;
	rte_data.fg_color = HMI_WHITE;
	rte_data.status =  0;
}
/*
 * Names		:	HMI_Read_CurCursorX
 * Inputs		:	None
 * Outpus		:	(INT32U) current cursor X position
 * Invoked	:	HMI application
 * Critical	:	None
 */
INT32U HMI_Read_CurCursorX(void)
{
	return rte_data.x;
}

/*
 * Names		:	HMI_Write_CurCursorX
 * Inputs		:	(INT32U) current cursor X position to set
 * Outpus		:	
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_Write_CurCursorX(INT32U x)
{
	rte_data.x = x;
}
/*
 * Names		:	HMI_Read_CurCursorY
 * Inputs		:	None
 * Outpus		:	(INT32U) current cursor Y position
 * Invoked	:	HMI application
 * Critical	:	None
 */
INT32U HMI_Read_CurCursorY(void)
{
	return rte_data.y;
}

/*
 * Names		:	HMI_Write_CurCursorY
 * Inputs		:	(INT32U) current cursor Y position to set
 * Outpus		:	
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_Write_CurCursorY(INT32U y)
{
	rte_data.y = y;
}
/*
 * Names		:	HMI_Read_CurFGColor
 * Inputs		:	None
 * Outpus		:	(INT32U) current foreground color
 * Invoked	:	HMI application
 * Critical	:	None
 */
HMI_Color HMI_Read_CurFGColor(void)
{
	return rte_data.fg_color;
}

/*
 * Names		:	HMI_Write_CurFGColor
 * Inputs		:	(INT32U) current color to set foreground color
 * Outpus		:	
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_Write_CurFGColor(HMI_Color color)
{
	rte_data.fg_color = color;
}
/*
 * Names		:	HMI_Read_CurBGColor
 * Inputs		:	None
 * Outpus		:	(INT32U) current background color
 * Invoked	:	HMI application
 * Critical	:	None
 */
HMI_Color HMI_Read_CurBGColor(void)
{
	return rte_data.bg_color;
}

/*
 * Names		:	HMI_Write_CurBGColor
 * Inputs		:	(INT32U) current color to set background color
 * Outpus		:	
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_Write_CurBGColor(HMI_Color color)
{
	rte_data.bg_color = color;
}
/*
 * Names		:	HMI_Read_CurChar
 * Inputs		:	None
 * Outpus		:	(INT8U) current character
 * Invoked	:	HMI application
 * Critical	:	None
 */
INT8U HMI_Read_CurChar(void)
{
	return rte_data.ch;
}

/*
 * Names		:	HMI_Write_CurChar
 * Inputs		:	(INT32U) current char to set
 * Outpus		:	
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_Write_CurChar(INT8U ch)
{
	rte_data.ch = ch;
}
/*
 * Names		:	HMI_Read_CurStatus
 * Inputs		:	None
 * Outpus		:	(INT8U) current LCD status
 * Invoked	:	HMI application
 * Critical	:	None
 */
INT8U HMI_Read_CurStatus(void)
{
	return rte_data.status;
}

/*
 * Names		:	HMI_Write_CurStatus
 * Inputs		:	(INT8U) current status to set
 * Outpus		:	
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_Write_CurStatus(INT8U status)
{
	rte_data.status = status;
}
/*
 * Names		:	HMI_Validation
 * Inputs		:	(BOOLEAN) 
 * Outpus		:	
 * Invoked	:	HMI application
 * Critical	:	None
 */
void HMI_Validation(BOOLEAN valid)
{
#define CHAR	(rte_data.ch)
#define X			(rte_data.x)
#define Y			(rte_data.y)
#define FG_COLOR	(rte_data.fg_color)
#define BG_COLOR	(rte_data.bg_color)

	INT8U i, j;
	INT8U line_dots;
	INT8U * fl_char_dots = (INT8U *)(fontdata_8x8 + CHAR * 8);

	if(TRUE == valid)
	{
		for(i = 0; i < 8; i++)
		{
			line_dots = fl_char_dots[i];
			for(j = 0; j < 8; j++)
			{
				if(line_dots & (0x80 >> j))
				{
					lcd01_putPixel(X+j, Y+i, FG_COLOR);
				}
				else
				{
					lcd01_putPixel(X+j, Y+i, BG_COLOR);
				}
			}
		}
	}
#undef CHAR
#undef X
#undef Y
#undef FG_COLOR
#undef BG_COLOR
}
/* EOF */

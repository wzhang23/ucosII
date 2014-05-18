#ifndef _HMI_RTE_H_
#define _HMI_RTE_H_

/*
 * Header files
 */
#include "types.h"

/*
 * Macro definition
 */
#define HMI_RED		(0x3f0000)
#define HMI_GREEN	(0x003f00)
#define HMI_BLUE	(0x00003f)
#define HMI_BLACK	(0x000000)
#define HMI_WHITE	(0x3f3f3f)

/*
 * Type definition
 */
/* HMI color data type definition */
typedef INT32U	HMI_Color	;
/* RTE Data type definition */
typedef struct
{
	INT32U x;	/* current cursor X position */
	INT32U y;	/* current cursor Y position */
	HMI_Color fg_color;	/* current front ground color */
	HMI_Color	bg_color;	/* current back ground color */
	INT8U ch;	/* current char */
	INT8U status;	/* lcd on / off */
} HMI_RTE_st;

/*
 * External funtions prototype
 */
void HMI_RTE_Init(void);
void HMI_Write_CurStatus(INT8U status);
INT8U HMI_Read_CurStatus(void);
void HMI_Write_CurChar(INT8U ch);
INT8U HMI_Read_CurChar(void);
void HMI_Write_CurFGColor(HMI_Color color);
HMI_Color HMI_Read_CurFGColor(void);
void HMI_Write_CurBGColor(HMI_Color color);
HMI_Color HMI_Read_CurBGColor(void);
void HMI_Write_CurCursorY(INT32U y);
INT32U HMI_Read_CurCursorY(void);
void HMI_Write_CurCursorX(INT32U x);
INT32U HMI_Read_CurCursorX(void);
void HMI_Validation(BOOLEAN valid);

#endif

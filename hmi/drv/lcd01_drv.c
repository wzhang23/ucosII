#include "includes.h"

void lcd01_init(void)
{
	/* 1. Configure the GPIO to LCD */
	GPICON_REG = 0xaaaaaaaa; /* gpi0~gpi15 as lcd_vd[0~15] */
	GPJCON_REG &= ~(0xfffffff);
	GPJCON_REG |= 0xaaaaaaa;	/* gpj0~gpj11 lcd */
	GPECON_REG &= ~(0xf);
	GPECON_REG |= (0x1);	/* GPE1 as LCD's on/off signal(LCD_PWR) */
	/* 2. Initialize the display controller of s3c6410 */
	/* 2.1 Configure the polarity and time parameter of HSYNC, VSYNC, VCLK and VDEN */
	MIFPCON
}

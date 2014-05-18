/****
 * LCD S70 for tiny6410 driver
 * LCD S70 - 800 X 480
 * Author			:	weiz
 * Create date:	5/18/2014
 * 5/18/2014	:	init version
 ****/
/*
 * Header files
 */
#include "types.h"
#include "s3c6410.h"
#include "lcd01_drv.h"

/*
 * Macro definition
 */
#define VSPW		(2)
#define VBPD		(28)
#define LINEVAL	(479U)
#define VFPD		(12)

#define HSPW		(47)
#if 0 /* datasheet */
#define HBPD		(39)
#endif
#define HBPD		(2)
#define HOZVAL	(799U)
#define HFPD		(39)

#define LEFT_TOP_X	0
#define LEFT_TOP_Y	0
#define RIGHT_BOT_X	(799U)
#define RIGHT_BOT_Y	(479U)

#define XSIZE					(800U)
#define YSIZE					(480U)
#define FRAME_BUFFER 	(0x51000000)

/*
 * Global variables
 */
const INT32U * g_frame_buffer_base = (INT32U *)FRAME_BUFFER;

/*
 * Name				:	lcd01_init
 * Inputs			:	None
 * Outputs		:	None
 * Invoked		: HMI application
 * Critical		: None
 */
void lcd01_init(void)
{
	/* 1. Configure the GPIO to LCD */
	GPICON_REG = 0xaaaaaaaa; /* gpi0~gpi15 as lcd_vd[0~15] */
	GPJCON_REG &= ~(0xfffffff);
	GPJCON_REG |= 0xaaaaaaa;	/* gpj0~gpj11 lcd */
#if 0
	GPECON_REG &= ~(0xf);
	GPECON_REG |= (0x1);	/* GPE0 as LCD's on/off signal(LCD_PWR) */
#endif
	/* 2. Initialize the display controller of s3c6410 */
	/* 2.1 Configure the polarity and time parameter of HSYNC, VSYNC, VCLK and VDEN */
	MIFPCON_REG &= ~(1<<3); /* normal mode */
	SPCON_REG &= ~(0x3);
	SPCON_REG |= 0x1;	/* RGB I/F style */
	VIDCON0_REG	&= ~((3<<26)|(3<<17)|(3<<2)); /* RGB I/F, RGB parallel format, HCLK as video clock source */
	VIDCON0_REG &= ~(0xff<<6);
	VIDCON0_REG |= ((3<<6)|(1<<4));	/* VCLK=HCLK/(clkval+1)=133/4=33.3Mhz */
	VIDCON1_REG &= ~(1<<7);	/* Get the video data at VCLK falling edge */
	VIDCON1_REG |= ((1<<6) | (1<<5)); /* HSYNC inverted, VSYNC inverted */
	VIDTCON0_REG = (VBPD << 16) | (VFPD << 8) | (VSPW << 0);
	VIDTCON1_REG = (HBPD << 16) | (HFPD << 8) | (HSPW << 0);
	VIDTCON2_REG = (LINEVAL << 11) | (HOZVAL << 0);
	/* 2.2 Configure BPP - bit per pixel */
	WINCON0_REG &= ~(0xf << 2);
#if 1
	WINCON0_REG |= (0x8 << 2); /* unpacked 18 BPP (non-palletized, R:6 - G:6 - B:6) */
#else
	WINCON0_REG |= (0xb << 2); /* unpacked 24 BPP (non-palletized, R:8 - G:8 - B:8) */
#endif
	VID0SD0A_REG = (LEFT_TOP_X << 11) | (LEFT_TOP_Y << 0);
	VID0SD0B_REG = (RIGHT_BOT_X << 11) | (RIGHT_BOT_Y << 0);
	VID0SD0C_REG = (LINEVAL + 1) * (HOZVAL + 1);
	/* 2.3 Get the Frame buffer */
	VIDW00ADD0B0_REG = FRAME_BUFFER;
	VIDW00ADD1B0_REG = (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0XFFFFFF);
	/* 3. Display on */
	VIDCON0_REG |= 0x3;
	WINCON0_REG |= 1;
}

/*
 * Name			:	lcd01_putPixel
 * Inputs		:	(INT32U) x - x position
 * 						(INT32U) y - y position
 * 						(INT32U) color - Pixel color to set
 * Outputs	:	(INT32U) ret - result of put pixel color
 * Invoked	: HMI RTE layer
 * Critical	: None
 */
INT32U lcd01_putPixel(INT32U x, INT32U y, INT32U color)
{
	INT32U ret = 0;
	INT32U * fl_addr;

	fl_addr = (INT32U *)(g_frame_buffer_base + (y * XSIZE + x));
	*fl_addr = color;

	return ret;
}

/* EOF */

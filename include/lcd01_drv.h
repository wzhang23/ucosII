#ifndef _LCD01_DRV_H_
#define _LCD01_DRV_H_
/****
 * Header files
 ****/
#include "types.h"

/****
 * Functions prototype
 ****/
void lcd01_init(void);
INT32U lcd01_putPixel(INT32U x, INT32U y, INT32U color);

#endif

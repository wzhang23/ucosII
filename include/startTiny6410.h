#ifndef _START_TINY6410_H_
#define _START_TINY6410_H_

#include "types.h"

/* bit field operation */
#define vi *( volatile INT32U * ) 
#define set_zero( addr, bit ) ( (vi addr) &= ( ~ ( 1 << (bit) ) ) )
#define set_one( addr, bit ) ( (vi addr) |= ( 1 << ( bit ) ) )
#define set_bit( addr, bit, val ) ( (vi addr) = (( vi addr)&=(~(1<<(bit))) ) | ( (val)<<(bit) ) )
#define set_2bit( addr, bit, val ) ( (vi addr) = (( vi addr)&(~(3<<(bit))) ) | ( (val)<<(bit) ) )
#define set_nbit( addr, bit, len,  val ) \
	( (vi addr) = ((( vi addr)&(~(( ((1<<(len))-1) )<<(bit))))  | ( (val)<<(bit) ) ))
#define get_bit( addr, bit ) ( (( vi addr ) & ( 1 << (bit) )) > 0  )
#define get_val( addr, val ) ( (val) = vi addr )
#define read_val( addr ) ( vi ( addr ) )
#define set_val( addr, val ) ( (vi addr) = (val) )
#define or_val( addr, val ) ( (vi addr) |= (val) ) 

/* function prototype */
/* clock function */
void clock_init(void);
/* sdram initialize function */
void sdram_init(void);
/* nand initialize function */
void nand_init(void);
/* copy code from nand to sdram */
INT32S copy2ddr(INT32U nand_start, INT32U ddr_start, INT32U len);

#endif

#ifndef _START_TINY6410_H_
#define _START_TINY6410_H_

#include "types.h"

/* bit field */
#define BIT0		(0x00000001)
#define BIT1		(0x00000002)
#define BIT2		(0x00000004)
#define BIT3		(0x00000008)
#define BIT4		(0x00000010)
#define BIT5		(0x00000020)
#define BIT6		(0x00000040)
#define BIT7		(0x00000080)
#define BIT8		(0x00000100)
#define BIT9		(0x00000200)
#define BIT10		(0x00000400)
#define BIT11		(0x00000800)
#define BIT12		(0x00001000)
#define BIT13		(0x00002000)
#define BIT14		(0x00004000)
#define BIT15		(0x00008000)
#define BIT16		(0x00010000)
#define BIT17		(0x00020000)
#define BIT18		(0x00040000)
#define BIT19		(0x00080000)
#define BIT20		(0x00100000)
#define BIT21		(0x00200000)
#define BIT22		(0x00400000)
#define BIT23		(0x00800000)
#define BIT24		(0x01000000)
#define BIT25		(0x02000000)
#define BIT26		(0x04000000)
#define BIT27		(0x08000000)
#define BIT28		(0x10000000)
#define BIT29		(0x20000000)
#define BIT30		(0x40000000)
#define BIT31		(0x80000000)

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

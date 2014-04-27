#ifndef _TPYES_H
#define _TPYES_H

#ifndef NULL
#define		NULL	0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif  /* _SIZE_T */

/* data type define */
typedef signed	 char				INT8S;
typedef unsigned char				INT8U;
typedef signed	 short int	INT16S;
typedef unsigned short int	INT16U;
typedef signed	 int				INT32S;
typedef unsigned int				INT32U;	
typedef unsigned long long	INT64U;
typedef unsigned long long	INT64S;
typedef signed	 int   			BOOLEAN;
typedef float          			FP32;                     /* Single precision floating point                    */
typedef double         			FP64;                     /* Double precision floating point                    */

#ifndef va_arg

#ifndef _VALIST
#define _VALIST
typedef char *va_list;
#endif /* _VALIST */

/*
 * 	Storage alignment properties
 */
#define NATIVE_INT	int
#define _AUPBND	(sizeof(NATIVE_INT) - 1)
#define _ADNBND	(sizeof(NATIVE_INT) - 1)

/*
 * Variable argument list macro definitions
 */
#define _bnd(X, bnd)	(((sizeof(X)) + (bnd)) & (~(bnd)))
#define va_arg(ap, T)	(*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T, _ADNBND))))
#define va_end(ap)	(void)0
#define va_start(ap, A)	(void)((ap) = (((char *) &(A)) + (_bnd (A, _AUPBND))))
#endif /* va_arg */

/* handy sizes */
#define SZ_1K                           0x00000400
#define SZ_4K                           0x00001000
#define SZ_8K                           0x00002000
#define SZ_16K                          0x00004000
#define SZ_64K                          0x00010000
#define SZ_128K                         0x00020000
#define SZ_256K                         0x00040000
#define SZ_512K                         0x00080000

#define SZ_1M                           0x00100000
#define SZ_2M                           0x00200000
#define SZ_4M                           0x00400000
#define SZ_8M                           0x00800000
#define SZ_16M                          0x01000000
#define SZ_32M                          0x02000000
#define SZ_64M                          0x04000000
#define SZ_128M                         0x08000000
#define SZ_256M                         0x10000000
#define SZ_512M                         0x20000000

#define SZ_1G                           0x40000000
#define SZ_2G                           0x80000000

typedef volatile unsigned long	vu_long;
typedef volatile unsigned short vu_short;
typedef volatile unsigned char	vu_char;

#define INT_MAX		((int)(~0U>>1))
#define INT_MIN		(-INT_MAX - 1)
#define UINT_MAX	(~0U)
#define LONG_MAX	((long)(~0UL>>1))
#define LONG_MIN	(-LONG_MAX - 1)
#define ULONG_MAX	(~0UL)

#endif /* _TPYES_H */

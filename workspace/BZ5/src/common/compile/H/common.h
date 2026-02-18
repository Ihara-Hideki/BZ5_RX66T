/****************************************************************************/
/*																			*/
/*		サンプルプログラム ヘッダファイル									*/
/*																			*/
/*			Copyright   :: 株式会社アルファプロジェクト						*/
/*			File Name   :: common.h											*/
/*																			*/
/****************************************************************************/

#ifndef		_COMMON_H_
#define		_COMMON_H_

/* 定義宣言 */
#define CLK_IN	(12800000)
#define ICLK	(CLK_IN * 20)
#define GCLK	(CLK_IN * 20)
#define BCLK	(CLK_IN * 10)
#define P1CLK	(CLK_IN *  5)
#define P0CLK	((CLK_IN *  5) / 2)

#define APP_OK (0)
#define APP_NG (-1)


/* メモリアクセス */
#define register_read_8(addr)	(*(volatile unsigned char  *)(addr))
#define register_read_16(addr)	(*(volatile unsigned short *)(addr))
#define register_read_32(addr)	(*(volatile unsigned long  *)(addr))

#define register_write_8(addr, data)	\
	do {\
		(*(volatile unsigned char  *)(addr)) = (volatile unsigned char )data;\
	} while(0)

#define register_write_16(addr, data)	\
	do {\
		(*(volatile unsigned short *)(addr)) = (volatile unsigned short)data;\
	} while(0)

#define register_write_32(addr, data)	\
	do {\
		(*(volatile unsigned long  *)(addr)) = (volatile unsigned long )data;\
	} while(0)

#define mon_draw_line(type)	\
	do {\
		if (type == 0) {\
			printf("------------------------------------------------------------\n");\
		} else if (type == 1) {\
			printf("============================================================\n");\
		}\
	} while(0)

/* プロトタイプ宣言 */
unsigned long get_timer(void);

#endif	/* END _COMMON_H_ */

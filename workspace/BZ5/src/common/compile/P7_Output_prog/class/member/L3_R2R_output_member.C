//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　Ｒ２Ｒ＿ｏｕｔｐｕｔ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      Ｒ２Ｒ回路向けの電流指令値の出力処理
//  【引数】
//      unsigned short Curr	:	電流指令値(D/A値)
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2026.02.20	M.Tanigawa
//
//            Copyright(C)2026 Panasonic Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
#include "r_smc_entry.h"

void R2R_output_membe(unsigned short Curr)
{
	union R2R_da
	{
		unsigned short	ALL;
		//
		struct
		{
			unsigned char	bit0	:	1;	// DA-LSB
			unsigned char	bit1	:	1;
			unsigned char	bit2	:	1;
			unsigned char	bit3	:	1;
			unsigned char	bit4	:	1;
			unsigned char	bit5	:	1;
			unsigned char	bit6	:	1;
			unsigned char	bit7	:	1;
			unsigned char	bit8	:	1;
			unsigned char	bit9	:	1;
			unsigned char	bit10	:	1;
			unsigned char	bit11	:	1;	// DA-MSB
			unsigned char	bit12	:	1;
			unsigned char	bit13	:	1;
			unsigned char	bit14	:	1;
			unsigned char	bit15	:	1;
		} BIT;
	} R2R_da;
	//
	unsigned short	Curr_data = ANALOG_TABLE[Curr];	// 指令値→Ｒ２Ｒ出力データ（analog.h）
	int				i;
	//
	// 指令値の読み込み
	//
	#if 1	// little-endian設定＝「ビットフィールドの最初のメンバ (b0) が LSB に対応」が保証されている場合
		//
		R2R_da.ALL = Curr_data;
		//
	#else	// 確実にLSB＝LSBにしたい場合
		//
		for(i=0; i<12; i++)	// 12 Bit
		{
			switch(i)
			{
				case 0:	// LSB
					R2R_da.BIT.bit0		= (Curr_data & 0x0001);
					break;
				case 1:
					R2R_da.BIT.bit1		= (Curr_data & 0x0001);
					break;
				case 2:
					R2R_da.BIT.bit2		= (Curr_data & 0x0001);
					break;
				case 3:
					R2R_da.BIT.bit3		= (Curr_data & 0x0001);
					break;
				case 4:
					R2R_da.BIT.bit4		= (Curr_data & 0x0001);
					break;
				case 5:
					R2R_da.BIT.bit5		= (Curr_data & 0x0001);
					break;
				case 6:
					R2R_da.BIT.bit6		= (Curr_data & 0x0001);
					break;
				case 7:
					R2R_da.BIT.bit7		= (Curr_data & 0x0001);
					break;
				case 8:
					R2R_da.BIT.bit8		= (Curr_data & 0x0001);
					break;
				case 9:
					R2R_da.BIT.bit9		= (Curr_data & 0x0001);
					break;
				case 10:
					R2R_da.BIT.bit10	= (Curr_data & 0x0001);
					break;
				case 11:	// MSB
					R2R_da.BIT.bit11	= (Curr_data & 0x0001);
					break;
				default:
					break;
			}
			//
			Curr_data = (Curr_data >> 1);
		}
	#endif
	//
	// 指令値の出力
	{
		PORTK.PODR.BIT.B2 = R2R_da.BIT.bit0;	// LSB
		PORTK.PODR.BIT.B1 = R2R_da.BIT.bit1;
		PORTK.PODR.BIT.B0 = R2R_da.BIT.bit2;
		PORT3.PODR.BIT.B3 = R2R_da.BIT.bit3;
		PORT3.PODR.BIT.B2 = R2R_da.BIT.bit4;
		PORT3.PODR.BIT.B1 = R2R_da.BIT.bit5;
		PORT3.PODR.BIT.B0 = R2R_da.BIT.bit6;
		PORT2.PODR.BIT.B7 = R2R_da.BIT.bit7;
		PORT2.PODR.BIT.B6 = R2R_da.BIT.bit8;
		PORT2.PODR.BIT.B5 = R2R_da.BIT.bit9;
		PORT2.PODR.BIT.B4 = R2R_da.BIT.bit10;
		PORT2.PODR.BIT.B3 = R2R_da.BIT.bit11;	// MSB
	}
//
return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_R2R_output_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ＲＥ＿ＣｈｅｃｋＣＭＤ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－１
//  【機能説明】
//      リモコン通信コマンドチェック
//  【引数】
//      なし
//  【戻り値】
//      なし
//  【備考】
//      なし
//  【更新履歴】
//      2007.12.03  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

#include <stdio.h>
#include "r_typedefs.h"
#include "iodefine.h"
#include "dev_drv.h"            /* Device Driver common header */
#include "devdrv_scif_uart.h"       /* UART Driver header */
#include "sio_char.h"
#include "rza_io_regrw.h"

//void CheckCMD(signed char Number)
void RE_CheckCMD(unsigned char Number)
{
// 2019.09.02
//----------------------
#ifdef __NEWCOM_PROTOCOL
	switch(Number)
	{
		case 0x11:/*通信ACK*/
			REMO_Recv_11();
			RE_RCV_Mode = DLE_mode;/*Next RCV_Mode*/

GPIO.P8 &= ~0x0010;	// 2019.08.29

			break;
		case 0x12:/*通信NAK*/
			REMO_Recv_12();
			RE_RCV_Mode = DLE_mode;/*Next RCV_Mode*/

GPIO.P8 &= ~0x0010;	// 2019.08.29

// 2019.08.296
if((GPIO.P8 & 0x0020) != 0)	GPIO.P8 &= ~0x0020;
else						GPIO.P8 |= 0x0020;


			break;
		case 0x20:
			RE_DATA_Length_RX = 1;/*付随データ1*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x30:
			RE_DATA_Length_RX = 8;/*付随データ8*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x31:
			RE_DATA_Length_RX = 3;/*付随データ3*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x32:
			RE_DATA_Length_RX = 12;/*付随データ12*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x40:
			RE_DATA_Length_RX = 4;/*付随データ4*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x41:
			RE_DATA_Length_RX = 5;/*付随データ5*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x50:
			RE_DATA_Length_RX = 20;/*付随データ20*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x51:
			RE_DATA_Length_RX = 128;/*付随データ128*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x52:
			RE_DATA_Length_RX = 20;/*付随データ20*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x60:
			RE_DATA_Length_RX = 4;/*付随データ4*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x61:
			RE_DATA_Length_RX = 2;/*付随データ2*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
	}
//----------------------
#else
	switch(Number){
		case 0x80:/*通信ACK*/
			REMO_Recv_80();
			RE_RCV_Mode = DLE_mode;/*Next RCV_Mode*/

GPIO.P8 &= ~0x0010;	// 2019.08.29

			break;
		case 0x81:/*通信NAK*/
			REMO_Recv_81();
			RE_RCV_Mode = DLE_mode;/*Next RCV_Mode*/

GPIO.P8 &= ~0x0010;	// 2019.08.29

// 2019.08.296
if((GPIO.P8 & 0x0020) != 0)	GPIO.P8 &= ~0x0020;
else						GPIO.P8 |= 0x0020;


			break;
		case 0x83:
			RE_DATA_Length_RX = 1;/*付随データ1*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x84:
			RE_DATA_Length_RX = 12;/*付随データ5*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x8A:
			//RE_DATA_Length_RX = 3;/*付随データ3*/
			RE_DATA_Length_RX = 9;/*付随データ9 2009.02.19*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x8B:
			RE_DATA_Length_RX = 2;/*付随データ2*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x8C:
			RE_DATA_Length_RX = 4;/*付随データ4*/
			RE_RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x90: // FRAM(Phase2) 2008/09/02 @Tny
			RE_DATA_Length_RX = (32/FRAM_PAKECT+5); //付随データ
			RE_RCV_Mode = DATA_mode;//Next RCV_Mode
			break;
		case 0x91: // FRAM(Phase2) 2008/09/02 @Tny
			RE_DATA_Length_RX = 1;  // 付随データ：1
			RE_RCV_Mode = DATA_mode;//Next RCV_Mode
			break;
		case 0xA1: // 2009.01.09
			RE_DATA_Length_RX = 3;  // 付随データ：1
			RE_RCV_Mode = DATA_mode;//Next RCV_Mode
			break;
		default:
			RE_DATA_Length_RX = 0;/*付随データ無し*/
			RE_RCV_Mode = DLE_mode;/*Next RCV_Mode*/
	}
#endif
//----------------------
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA1_RE_CheckCMD.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

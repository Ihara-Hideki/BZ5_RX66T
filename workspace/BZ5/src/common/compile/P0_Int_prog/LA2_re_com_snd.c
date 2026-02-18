//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｒｅ＿ｃｏｍ＿ｓｎｄ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－２
//  【機能説明】
//      リモコン送信処理（実体）
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
//#define	__CPU_EXTERNAL_COMUNICATION_PROG
#include  "custom.h"

#include <stdio.h>
#include "r_typedefs.h"
#include "iodefine.h"
#include "dev_drv.h"            /* Device Driver common header */

#include "devdrv_scif_uart.h"       /* UART Driver header */
#include "sio_char.h"
#include "rza_io_regrw.h"


#ifndef  DECLARE_SCIF_CHANNELS
extern volatile struct st_scif*  SCIF[ SCIF_COUNT ];
#endif  /* DECLARE_SCIF_CHANNELS */

//-----------------------------------------------------
void TX4_Send(uchar Data)
{
// 2019.09.02
//----------------------
#ifdef __NEWCOM_PROTOCOL
	while(((SCIF[DEVDRV_CH_4]->SCFSR) & 0x0020) == 0);
	/* Write the receiving data in TDR */
	(SCIF[DEVDRV_CH_4]->SCFTDR) = (uint8_t)Data;
	while(((SCIF[DEVDRV_CH_4]->SCFSR) & 0x0060) != 0x0060);	// Assert TDFE and TEND flag
	/* Clear TDFE and TEND flag */
	(SCIF[DEVDRV_CH_4]->SCFSR) &= (~0x0060u);
#else
	/* Write the receiving data in TDR */
	(SCIF[DEVDRV_CH_4]->SCFTDR) = (uint8_t)Data;
	/* Clear TDFE and TEND flag */
	(SCIF[DEVDRV_CH_4]->SCFSR) &= (~0x0060u);
#endif
//----------------------
}
//-----------------------------------------------------
void re_com_snd(void)
{
     static long   i = 0;
     uchar  RE_SND_DATA;                            // 送信データ
     RE_SND_DATA = 0; 

   FOREVER{
             // 送信レジスタにデータがあるか？
			 if(0 == RZA_IO_RegRead_16(&(SCIF[DEVDRV_CH_4]->SCFSR), SCIFn_SCFSR_TDFE_SHIFT, SCIFn_SCFSR_TDFE))
			 //if((RE_RCV_Mode != DLE_mode)||(0 == RZA_IO_RegRead_16(&(SCIF[DEVDRV_CH_4]->SCFSR), SCIFn_SCFSR_TDFE_SHIFT, SCIFn_SCFSR_TDFE)))
             {
                 break;
             }

             //if((S1RCNT & 0x20) != 0x00)         // 受信レジスタにデータがあるか？
             //{
             //    break;                          // データがあるならスルー
             //}

#if false	// 2019.05.28
             if(++i < 5)
             {
               P9DATA = (P9DATA | 0x01);
             } else if(i < 11) {
               P9DATA = (P9DATA & 0xfe);
             } else {
               i = 0;
             }
#endif

// --リモコン用--
             if(((RE_SND_Mode == DLE_mode_SD) || (RE_SND_Mode == WAIT_mode_SD)) && ((REMO_ACK_count != 0) || (REMO_NAK_count != 0 )|| (REMO_Busy_count != 0 )))
             {
               switch(RE_ACK_SND_Mode)// ACK,NAK優先で送信
               {
                      case DLE_mode_SD:

GPIO.P8 |= 0x0010;	// 2019.08.29

                              TX4_Send(DLE);
                              RE_ACK_SND_Mode   = CMD_mode_SD;
                              RE_data_count_tx  = 0;
                              RE_SUM_ADD_TxData = 0;
// 2019.09.02
//----------------------
#if	1	//ndef __NEWCOM_PROTOCOL
                              break;
                      case CMD_mode_SD:
#endif
//----------------------

GPIO.P8 &= ~0x0010;	// 2019.08.29

                              if(REMO_NAK_count != 0)
                              {
                                 TX4_Send(REMONAK_SD);
                                 REMO_NAK_count--;
                              } else if(GD2_Busy_count != 0) {
                                 TX4_Send(GD2Busy_SD);
                                 REMO_Busy_count--;
                              } else {
                                 TX4_Send(REMOACK_SD);
                                 REMO_ACK_count--;
                              }
                              RE_ACK_SND_Mode = DLE_mode_SD;
                              break;
                       default:
                              RE_ACK_SND_Mode = DLE_mode_SD;
                           break;
               }
             } else if(RE_SND_CMD_Position != RE_SND_CMD_Proc) {
		// 2019.09.02
		//----------------------
		#if	0	//def __NEWCOM_PROTOCOL
				while(RE_SND_Mode != WAIT_mode_SD)
				{
		#endif
		//----------------------
                       switch(RE_SND_Mode)
                       {
                              case DLE_mode_SD:

GPIO.P8 |= 0x0010;	// 2019.08.29

                                      TX4_Send(DLE);
                                      RE_SND_Mode         = CMD_mode_SD;
                                      RE_data_count_tx    = 0;
                                      RE_SUM_ADD_TxData   = 0;
                                      RE_DLE_check_flagSD = false;
                                      break;
                              case CMD_mode_SD:
                                      RE_CMD_DATA_TX      = RE_Txd_CMD[RE_SND_CMD_Proc];
                                      RE_SUM_ADD_TxData  += RE_CMD_DATA_TX;                    // SUMチェック用加算
                                      TX4_Send(RE_CMD_DATA_TX);
                                      RE_SND_Mode         = DATA_mode_SD;
                                      break;
                              case DATA_mode_SD:
                                      (ToREMO[RE_CMD_DATA_TX])();
                                      RE_SND_DATA         = RE_Txd_DATA[RE_data_count_tx];
                                      if((RE_SND_DATA == DLE) && (RE_DLE_check_flagSD == false))
                                      {
                                        RE_DLE_check_flagSD = ON;
                                        TX4_Send(RE_SND_DATA);                     // データの送信
                                      } else {
                                        RE_SUM_ADD_TxData  += (uchar)RE_SND_DATA;              // SUMチェック用加算
                                        TX4_Send(RE_SND_DATA);                     // データの送信
                                        RE_DLE_check_flagSD = OFF;
                                        RE_data_count_tx++;
                                        if(RE_data_count_tx >= RE_DATA_Length_TX)
                                        {
                                           RE_SND_Mode      = SUM_mode_SD;
//----- Phase15 by @Tny 2008/09/19 -----
#if true
                                            gb_15SEG_LED_Error_Disp_Hold    = false;   // エラー表示データ送信中フラグ
#endif
//--------------------------------------------
                                        }
                                      }
                                      break;
                              case SUM_mode_SD:

GPIO.P8 &= ~0x0010;	// 2019.08.29

                                      TX4_Send(RE_SUM_ADD_TxData);
                                      RE_SND_Mode           = WAIT_mode_SD;
                                      RE_SND_Timer          = 0;
                                      RE_WAIT_SD_count++;
                                      break;
                              case WAIT_mode_SD:
                                      if(RE_SND_Timer >= 10)
                                      //if(SND_Timer >= 200) //プロトコルアナライザーテスト用
                                      {

// 2019.08.296
if((GPIO.P8 & 0x0020) != 0)	GPIO.P8 &= ~0x0020;
else						GPIO.P8 |= 0x0020;

                                         RE_SND_Mode = DLE_mode_SD;
                                         if((TPX_REMO_Send_OFF == ON) || (Check_REMO_Send_OFF == ON))
                                         {
                                            REMO_Recv_80();
                                         }
                                      }
                                      //if(RE_WAIT_SD_count > 2)                              // リトライ３回でタイムアウト
                                      if(RE_WAIT_SD_count > 20) // リトライ21回でタイムアウト 2008.02.13
                                      {
                                         //RS422ErrorFlag = 0x07;

#if true	// エラー処理（後日メイン側へ移動）
                                         ComuniPackRemo.Data.bRS422Connection = false;
                                         RE_SND_CMD_Position = 0;
                                         RE_SND_CMD_Proc     = 0;
                                         REMO_ACK_count    = 0;
                                         REMO_NAK_count    = 0;
                                         REMO_Busy_count   = 0;
                                         RE_WAIT_SD_count    = 0;
                                         //RS422ErrorFlag   = 0x00; 2007.1.16 削除　この行があるとリトライエラーが出力されないため 2007.1.17削除移植
#endif

// 2019.08.296
if((GPIO.P8 & 0x0020) != 0)	GPIO.P8 &= ~0x0020;
else						GPIO.P8 |= 0x0020;

                                      }
                                      break;
                              default:
                                      RE_SND_Mode = DLE_mode_SD;
                                      break;
                       }
		// 2019.09.02
		//----------------------
		#if 0	//def __NEWCOM_PROTOCOL
						if(RE_SND_Mode == WAIT_mode_SD)
						{
							break;
						}
				}
				if(RE_SND_Mode == WAIT_mode_SD)
				{
                    if(RE_SND_Timer >= 10)
                    {

// 2019.08.29
if((GPIO.P8 & 0x0020) != 0)	GPIO.P8 &= ~0x0020;
else						GPIO.P8 |= 0x0020;

                     	RE_SND_Mode = DLE_mode_SD;
                    	if((TPX_REMO_Send_OFF == ON) || (Check_REMO_Send_OFF == ON))
                    	{
                        	REMO_Recv_80();
                    	}
                	}
                	if(RE_WAIT_SD_count > 20) // リトライ21回でタイムアウト 2008.02.13
                	{

				#if true	// エラー処理（後日メイン側へ移動）
                    	ComuniPackRemo.Data.bRS422Connection = false;
                    	RE_SND_CMD_Position = 0;
                    	RE_SND_CMD_Proc     = 0;
                    	REMO_ACK_count    = 0;
                    	REMO_NAK_count    = 0;
                    	REMO_Busy_count   = 0;
                    	RE_WAIT_SD_count    = 0;
				#endif
                	}
				}
		#endif
		//----------------------
             }
             break;
          }
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA2_re_com_snd.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

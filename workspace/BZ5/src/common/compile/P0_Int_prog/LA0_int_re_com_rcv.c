//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｔ＿ｒｅ＿ｃｏｍ＿ｒｃｖ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－０
//  【機能説明】
//      リモコン通信受信割り込み
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


void int_re_com_rcv(void)
{
	static long		i = 0;

	uchar 	RE_RCV_CMD;	// 受信データ
	uchar	RE_CMD;		// 処理用コマンドワーク

//-------------------------
// 2019.08.29
  do{
//-------------------------
    //************ パリティ、フレーミングエラー検出　2007.12.03 ****************
    if((((SCIF[DEVDRV_CH_4]->SCFSR) & 0x09Cu) != 0) || (1 == RZA_IO_RegRead_16(&SCIF[DEVDRV_CH_4]->SCLSR, SCIFn_SCLSR_ORER_SHIFT, SCIFn_SCLSR_ORER)))
    {
        /* ---- Detect receive error ---- */
        /* Disable reception             */
        /* Reset receiving FIFO          */
        /* Clearing FIFO reception reset */
        /* Error bit clear               */
        /* Enable reception              */
        //RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCSCR), 0, SCIFn_SCSCR_RE_SHIFT,    SCIFn_SCSCR_RE);
        //RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCFCR), 1, SCIFn_SCFCR_RFRST_SHIFT, SCIFn_SCFCR_RFRST);
        //RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCFCR), 0, SCIFn_SCFCR_RFRST_SHIFT, SCIFn_SCFCR_RFRST);
		if(1 == RZA_IO_RegRead_16(&SCIF[DEVDRV_CH_4]->SCFSR, SCIFn_SCFSR_RDF_SHIFT, SCIFn_SCFSR_RDF)) // Read RDF = 1?
		{
			RE_RCV_CMD = (uchar)((SCIF[DEVDRV_CH_4]->SCFRDR) & 0xFFu);									// データレジスタからデータを入力する
	    	RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCFSR), 0, SCIFn_SCFSR_RDF_SHIFT, SCIFn_SCFSR_RDF);	// Clear RDF
		}
        (SCIF[DEVDRV_CH_4]->SCFSR) &= ~0x9Cu;
        RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCLSR), 0, SCIFn_SCLSR_ORER_SHIFT,  SCIFn_SCLSR_ORER);
        //RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCSCR), 1, SCIFn_SCSCR_RE_SHIFT,    SCIFn_SCSCR_RE);

// 2019.08.29
if((GPIO.P8 & 0x0020) != 0)	GPIO.P8 &= ~0x0020;
else						GPIO.P8 |= 0x0020;

    }
    //*************************************************************************
	else
	{
		RE_RCV_CMD = (uchar)((SCIF[DEVDRV_CH_4]->SCFRDR) & 0xFFu);	// データレジスタからデータを入力する
	    RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCFSR), 0, SCIFn_SCFSR_RDF_SHIFT, SCIFn_SCFSR_RDF);		// Clear RDF // 2019.08.29
// --Ｇ２用-- 
		switch(RE_RCV_Mode){	// 受信モード
			case DLE_mode:{		// DLE受信モード
							if(RE_RCV_CMD == DLE){
								RE_RCV_Mode = CMD_mode;	// コマンド受信モードへ移行

GPIO.P8 |= 0x0010;	// 2019.08.29

							}
							RE_data_count_rx	= 0;
							RE_SUM_ADD_RxData	= 0;
							RE_RCV_Position	= 0;
							RE_DLE_check_flag	= false;
							break;
						}
			case CMD_mode:{		// コマンド受信モード
							if(ComuniPackRemo.Data.bRS422Connection){	// 回線は開いている？
								RE_CMD_DATA_RX 	= RE_RCV_CMD;			// コマンドの取得
								RE_SUM_ADD_RxData += (uchar)RE_RCV_CMD;	// SUM値更新
								RE_CheckCMD(RE_CMD_DATA_RX);				// コマンド解析処理(コマンドと付随データ数のチェック)
							}
							else{	// まだ回線は開いていない。
								if(RE_RCV_CMD == RE_GOODMORNING){	// 受信コマンドは「ＧｏｏｄＭｏｒｎｉｎｇコマンド」？
									RE_CMD_DATA_RX 	= RE_RCV_CMD;			// コマンドの取得
									RE_SUM_ADD_RxData += (uchar)RE_RCV_CMD;	// SUM値更新
									RE_CheckCMD(RE_CMD_DATA_RX);				// コマンド解析処理(コマンドと付随データ数のチェック)
								}else{
//----- Phase26 by @Tny 2008/10/23 -----
#if true
    								if(RE_RCV_CMD == 0x16){ // M32R側からの相互動作確認コマンド？
                                        gb_Controller_UnConnect = true;     // コントローラ未接続確認フラグ：未接続
                                        gb_Ping_to_Controller   = false;    // コントローラ未接続確認実行フラグ
                                        gtt_Ctrl_flag.UnConnect_false   =   true; //コネクタを接続されいる場合はコントローラ未接続確認フラグは無効とする。2009.07.14
                                    }
#endif
//--------------------------------------
									RE_RCV_Mode = DLE_mode;	// ＧｏｏｄＭｏｒｎｉｎｇ以外は受け付けない　→　DLE受信モードへ移行
								}
							}
							break;
						}
			case DATA_mode:{	// データ部受信モード
							if((RE_RCV_CMD == DLE) && (RE_DLE_check_flag == false)){	// データ部内でのDLEコードを受信？
								RE_DLE_check_flag = true;	// 次データはデータ本体
							}
							else{	// データ本体を取得
								RE_SUM_ADD_RxData += (uchar)RE_RCV_CMD;	// SUM値更新
								RE_Rxd_DATA[RE_RCV_Position] = RE_RCV_CMD;	// データの保管
								RE_RCV_Position++;						// 受信バッファのインデックス更新
								RE_data_count_rx++;					// データ受信数の更新
								RE_DLE_check_flag = false;				// データ部内でのDLEコード受信判定フラグの初期化
							}
							if(RE_data_count_rx >= RE_DATA_Length_RX){	// 指定データ数を受信完了？
								RE_RCV_Mode = SUM_mode;					// チェックサム値受信モードへ移行
							}
							break;
						}
			case SUM_mode:{		// チェックサム値受信モード

GPIO.P8 &= ~0x0010;	// 2019.08.29

							if(RE_RCV_CMD == RE_SUM_ADD_RxData){	// 受信データ（受信したチェックサム値）と内部で算出したチェックサム値は同じ？
							   (FromREMO[RE_CMD_DATA_RX])();	// 付随データに対する処理を行う。
								REMO_Send_CMD(REMOACK_SD);		// ACKチェック一致：ACK返信
                                gtt_Ctrl_counter.Com_remo_err_parity   = 0; //2007.2.26追加
                                gtt_Ctrl_counter.Com_remo_err_framing = 0; //2007.2.26追加
							}
							else{
								REMO_Send_CMD(REMONAK_SD);	// SUMチェック不一致：NAK返信

// 2019.08.296
if((GPIO.P8 & 0x0020) != 0)	GPIO.P8 &= ~0x0020;
else						GPIO.P8 |= 0x0020;

							}
							RE_RCV_Mode = DLE_mode;	// DLE受信モードへ移行
							break;
						}
			default:	{
							RE_RCV_Mode = DLE_mode;	// DLE受信モードへ移行
							break;
						}
		}
//-------------------------
// 2019.08.29
	    /* Clear DR,RDF */
//    	RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCFSR), 0, SCIFn_SCFSR_DR_SHIFT, SCIFn_SCFSR_DR);
//	    RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCFSR), 0, SCIFn_SCFSR_RDF_SHIFT, SCIFn_SCFSR_RDF);
//-------------------------
	}
//-------------------------
// 2019.08.29
  }while((SCIF[DEVDRV_CH_3]->SCFDR & 0x001f) > 0);
  /* Clear DR */
  RZA_IO_RegWrite_16(&(SCIF[DEVDRV_CH_4]->SCFSR), 0, SCIFn_SCFSR_DR_SHIFT, SCIFn_SCFSR_DR);
//-------------------------
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA0_int_rob_com_rcv.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

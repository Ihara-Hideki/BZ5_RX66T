//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｓｅｑｕｅｎｃｅ＿ｓｔｏｐ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      シーケンス停止管理
//  【引数】
//      なし
//  【戻り値】
//      なし
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
#include "iodefine.h"
#include "devdrv_bsc.h"
#include "rza_io_regrw.h"

void sequence_stop_manager(void)
{
     unsigned short int pui_Welder_ctrl;
     unsigned short int pui_Inverter_ctrl;
     unsigned short int pui_Motor_ctrl;
     
     pui_Welder_ctrl   = 0x0000;
     pui_Inverter_ctrl = 0x0000;
     pui_Motor_ctrl    = 0x0000;

     if (gtt_Ctrl_word.Sequence_ctrl_code == ON)           //シーケンス停止
     {
//-------------------------------------------------------------------------------
// BP4 Phase15 by @Tny 2009.02.25
		uchar   i,Data[10];

		for(i=0;i<16;i++){
			ComuniPackRemo.Data.From.uc_Com_lcd_data2[i]  = ' ';
		}
//-------------------------------------------------------------------------------
	 IMJTOCR4  = 0x07;                                 //割禁
         //hpiWrite( hpicmdOUTWLDMOV , &pui_Welder_ctrl);    //溶接機緊急停止 2019.04.02 del ihara
         //hpiWrite( hpicmdOUTWLDOUT , &pui_Inverter_ctrl);  //インバータ緊急停止 2019.04.02 del ihara
         //hpiWrite( hpicmdOUTSRVSEQ , &pui_Motor_ctrl);     //モータ出力緊急停止 2019.04.02 del ihara
         //GAS = OFF;                                        //ガス緊急停止 2009.07.27 del

         //START1 = ON;  //2008.12.08 2010.01.07 del
         //START2 = OFF; //2008.12.08
         HF_OUT = OFF; //2009.01.31
         guc_R8_control.Bit1Sw.Over_lay = false; //重畳充電停止 2008.12.08
//-------------------------------------------------------------------------------
// BP4 Phase15 by @Tny 2009.02.25
		if(gss_Select_dital[P_DATE_TIME_DISPLAY] != 2){
			// 設定時刻の読み込み（リアルタイムデータ１）
			I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
			if(gss_Select_dital[P_DATE_TIME_DISPLAY] == 0){
#if true
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 0]  = 0x27;	// ← 「'」
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 1]  = ('0' + ((Data[0] & 0xf0) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 2]  = ('0' + (Data[0] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 3]  = '/';
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 4]  = ('0' + ((Data[1] & 0x10) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 5]  = ('0' + (Data[1] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 6]  = '/';
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 7]  = ('0' + ((Data[2] & 0x30) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 8]  = ('0' + (Data[2] & 0x0f));
				if(((Data[4] & 0x30) >> 4) > 0){
			    	ComuniPackRemo.Data.From.uc_Com_lcd_data2[10]  = ('0' + ((Data[4] & 0x30) >> 4));
				}
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[11]  = ('0' + (Data[4] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[12]  = ':';
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[13]  = ('0' + ((Data[5] & 0x70) >> 4));
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[14]  = ('0' + (Data[5] & 0x0f));
#else
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 7]  = 0x27;	// ← 「'」
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 8]  = ('0' + ((Data[0] & 0xf0) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 9]  = ('0' + (Data[0] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[10]  = '/';
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[11]  = ('0' + ((Data[1] & 0x10) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[12]  = ('0' + (Data[1] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[13]  = '/';
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[14]  = ('0' + ((Data[2] & 0x30) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[15]  = ('0' + (Data[2] & 0x0f));
#endif
			}
			else{
#if true
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 0]  = 0x27;	// ← 「'」
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 1]  = ('0' + ((Data[0] & 0xf0) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 2]  = ('0' + (Data[0] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 3]  = '/';
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 4]  = ('0' + ((Data[1] & 0x10) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 5]  = ('0' + (Data[1] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 6]  = '/';
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 7]  = ('0' + ((Data[2] & 0x30) >> 4));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[ 8]  = ('0' + (Data[2] & 0x0f));
				if(((Data[4] & 0x30) >> 4) > 0){
			    	ComuniPackRemo.Data.From.uc_Com_lcd_data2[10]  = ('0' + ((Data[4] & 0x30) >> 4));
				}
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[11]  = ('0' + (Data[4] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[12]  = ':';
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[13]  = ('0' + ((Data[5] & 0x70) >> 4));
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[14]  = ('0' + (Data[5] & 0x0f));
#else
				if(((Data[4] & 0x30) >> 4) > 0){
			    	ComuniPackRemo.Data.From.uc_Com_lcd_data2[10]  = ('0' + ((Data[4] & 0x30) >> 4));
				}
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[11]  = ('0' + (Data[4] & 0x0f));
				ComuniPackRemo.Data.From.uc_Com_lcd_data2[12]  = ':';
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[13]  = ('0' + ((Data[5] & 0x70) >> 4));
			    ComuniPackRemo.Data.From.uc_Com_lcd_data2[14]  = ('0' + (Data[5] & 0x0f));
#endif
			}
		}
//-------------------------------------------------------------------------------

         //MG_SW = OFF;                                         //マグネットＳＷ緊急停止 2008.09.11削除
//2008.3.27 スタートリレー駆動のため削除         CD_OUT = OFF;                                     //冶具端子への電検出力をOFFする　2007.1.17追加　2007.1.17移植
         while(1){
              if (gtt_Ctrl_flag.UnConnect_false  ==  false) //2009.07.14
              {
                   if(gb_Controller_UnConnect)  output_r8_class(guc_Sequence_mode , CONTROLLER_NON_CONNECT); // コントローラ未接続（短絡子無し）
                   else                         output_r8_class(guc_Sequence_mode , gui_Err_code); //Ｒ８にエラー番号を送るため
                   if(gb_Controller_UnConnect) //2009.07.06
                   {
                      ComuniPack.Data.bRS422Connection = false;
                      guc_Robot_connect_flag = false;
                   }
               } else {
                   output_r8_class(guc_Sequence_mode , gui_Err_code); //Ｒ８にエラー番号を送るため
               }

               //<><><> 2009.09.30 <><><>
               if (guc_Error_code == RS422_OVR_ERR || guc_Error_code == RS422_PTY_ERR || guc_Error_code == RS422_FLM_ERR || guc_Error_code == RS422_TIME_OUT_ERR)
               {
		   ComuniPack.Data.bRS422Connection = false;
                   guc_Robot_connect_flag           = false;
               }
               //<><><><><><><><><><><><><>
               
               //************ 電源ＯＦＦ時ロボットに一次低電圧を送信しないため一次低電圧発生時は送信を遅らせる処理 2007.3.6 2007.3.13移植*********
               if (gtt_Ctrl_flag.Pri_volt_err_com_delay_set_flag == ON)
               {
                  if(gtt_Ctrl_flag.Pri_volt_err_com_delay == OFF){
                     gtt_Ctrl_flag.Pri_volt_err_com_delay = ON;
                     gtt_Ctrl_counter.Pri_volt_err_com_delay = PRI_VOLT_ERR_COM_DELAY_TIME;
                  } else if(gtt_Ctrl_counter.Pri_volt_err_com_delay <= 0){
                     if (ComuniPack.Data.From.fErrorCode2.ALL != gtt_Internal_pack.Data.Out.fErrorCode2.ALL) //2007.3.13　ワンショットに変更
                     {
                         ComuniPack.Data.From.fErrorCode2.ALL = gtt_Internal_pack.Data.Out.fErrorCode2.ALL;
                         GD2_Send_CMD(0xc4);
                     }
                  }
               }
               //*********************************************************************************************************************

               //<><><><> エラー時ガスＯＦＦ遅れ処理 2009.07.27 <><><><>
               if (gtt_Ctrl_flag.Err_gas == OFF)
               {
                   gtt_Ctrl_flag.Err_gas = ON;
                   gtt_Ctrl_counter.Err_gas = gtt_Internal_pack.Data.In.sAfterFlowTime * 20;
               } else if (gtt_Ctrl_counter.Err_gas <= 0) {
                   GAS = OFF;                                        //ガス停止
               }
               //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>

               CD_OUT = OFF; //2009.12.16
               PLS_OUT = OFF; //2009.12.16

//----- Phase7 by @Tny 2008/09/10 -----
#if true
            	if(ComuniPackRemo.Data.bRS422Connection){	// 回線は開いている？
//----- Phase13 by @Tny 2008/09/18 -----
#if true // ※エラー表示をするときは以下の手順を守ること
                    if(Timer._100m != gtt_Ctrl_counter.Backup_100m && gus_Initial_timer == 0){	// 500m秒経過した？
                        if(gb_Error_Display_Sending){   // エラー情報の送信要求がある？
                            gb_Error_blink  = true; // エラー点滅制御要求フラグ
                            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no = 0;       // 表示するブロック番号：全制御停止
                            REMO_Send_CMD(0x23);
                        }
                        else{
                            REMO_Send_CMD(0x21);
                            REMO_Send_CMD(0x20);
                            //REMO_Send_CMD(0x34); //2009.01.16
                            //REMO_Send_CMD(0x35); //2009.01.13
//-------------------------------------------------------------------------------
// BP4 Phase15 by @Tny 2009.02.25
							if(gss_Select_dital[P_DATE_TIME_DISPLAY] != 2){
								REMO_Send_CMD(0x35);
							}
//-------------------------------------------------------------------------------
                        }
                        gtt_Ctrl_counter.Backup_100m = Timer._100m;
                    }
#endif
//--------------------------------------------
                }
#endif
//--------------------------------------------

//----- Phase29 by @Tny 2008/11/21 -----
#if true
        if((guc_Error_code != 0)&&(guc_Error_code != guc_Error_no_backup)){ // 記録すべき情報？
			if((guc_Error_code == PRI_LOW_VOLTAGE_ERR)&&(gus_Pri_volt_err_timer <= 0)){
	            unsigned char   Data[10];
	            unsigned short  Index   = gtt_Error_History.History_rec_index;  // 記録インデックスの取り出し
	            
	            // 設定時刻の読み込み（リアルタイムデータ１）
	            I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
	            gtt_Error_History.Info[Index].Error_No  = guc_Error_code;                                       // エラー番号を記録
	            gtt_Error_History.Info[Index].Year      = ((((Data[0] & 0xf0) >> 4) * 10) + (Data[0] & 0x0f));  // エラー発生日時（年）を記録
	            gtt_Error_History.Info[Index].Month     = ((((Data[1] & 0x10) >> 4) * 10) + (Data[1] & 0x0f));  // エラー発生日時（月）を記録
	            gtt_Error_History.Info[Index].Day       = ((((Data[2] & 0x30) >> 4) * 10) + (Data[2] & 0x0f));  // エラー発生日時（日）を記録
	            gtt_Error_History.Info[Index].Hour      = ((((Data[4] & 0x30) >> 4) * 10) + (Data[4] & 0x0f));  // エラー発生日時（時）を記録
	            gtt_Error_History.Info[Index].Minute    = ((((Data[5] & 0x70) >> 4) * 10) + (Data[5] & 0x0f));  // エラー発生日時（分）を記録
	            gtt_Error_History.Info[Index].Second    = ((((Data[6] & 0x70) >> 4) * 10) + (Data[6] & 0x0f));  // エラー発生日時（秒）を記録
	            if(++Index >= MAX_ERROR_INFOMATION){
	                Index = 0;                                              // エラー履歴テーブルの記録最終エリアまで到達したら先頭に戻る
	                gtt_Error_History.Full_history_rec  = true;             // 全記録エリア使用フラグ
	            }
	            gtt_Error_History.History_rec_index     = Index;            // 記録インデックスの更新
	            gtt_Error_History.Start_record          = true;             // 記録開始フラグの設定
	            guc_Error_no_backup                     = guc_Error_code;   // エラー情報重複記録防止のため、今回のエラー番号を記憶
	            gb_Error_Display_Sending                = true;             // エラー情報送信要求フラグ
	            gb_Error_History_Write                  = true;             // エラー履歴テーブル保存の要求
		        ch0_write_class(true);
			}
        }
#endif
//--------------------------------------------

         }
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_sequence_stop_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

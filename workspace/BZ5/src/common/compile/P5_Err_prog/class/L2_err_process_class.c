//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｅｒｒ＿ｐｒｏｃｅｓｓ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      エラーに応じた処理を行う
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

Bit16 err_process_class(unsigned int pui_Err_code , Bit16 xtt_Ctrl_word)
{
     unsigned char puc_Err_code;                   //エラーコード
     unsigned char puc_Add_err_code;               //付加コード 0:LEVEL0 ERROR   1:LEVEL1 ERROR   2:LEVEL2 ERROR   3:LEVEL3 ERROR
     Bit16 ptt_Ctrl_word;

     puc_Err_code          = 0;                    //2006.8.30 clear
     puc_Add_err_code      = 0;                    //2006.8.30 clear


     ptt_Ctrl_word = xtt_Ctrl_word;
     
     //2009.03.19場所変更
     if (gus_Initial_timer <= 0)
     {
         gtt_Ctrl_flag.Welder_init_execution = OFF;
     }
     

     if (gub_System_err == ON)
     {
         puc_Err_code      = (unsigned char)(pui_Err_code & 0x00ff);               //エラーコード抽出
         puc_Add_err_code  = (unsigned char)((pui_Err_code >> 8) & 0x00ff);        //付加コード抽出

         switch (puc_Err_code)  //個々のエラー処理
         {
                 case  STICK_ERR:                //スティック発生
                       gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b0 = ON;
                       gub_Err = ON;             //エラー治具端子出力セット
                       break;
                 case  ARC_ERR:                  //アーク切れ
                       gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b1 = ON;
                       gub_Err = ON;             //エラー治具端子出力セット
                       break;
                 case  OUTSIDE_STOP1_ERR:        //外部一時停止１（ガス減圧異常）外部一時停止１のｂｉｔに変更 2008.10.20
                       //gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b1 = ON;
                       //gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b3 = ON;
                       //gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b0 = ON; //水回路異常に変更 2009.07.29
                       gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b1 = ON; //ガス減圧に変更 2009.09.29
                       gub_Err = ON;             //エラー治具端子出力セット
                       break;
                 case  OUTSIDE_STOP2_ERR:        //外部一時停止２（水回路異常）外部一時停止２のｂｉｔに変更 2008.10.20
                       //gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b0 = ON;
                       //gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b4 = ON;
                       gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b0 = ON; //水回路異常に変更 2009.09.29
                       gub_Err = ON;             //エラー治具端子出力セット
                       break;
                 case  ARC_START_ERR:            //アークスタート異常
                       gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b7 = ON;
                       gub_Err = ON;             //エラー治具端子出力セット
                       ptt_Ctrl_word.Gas_ctrl_code                          = OFF; //ガス停止 2009.12.14
                       gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //2009.12.14
                       break;
                 case  ABNORMAL_TEMP_ERR:        //温度異常
//2006.11.28                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b0 = ON;
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b2 = ON;
                       gub_Err = ON;             //エラー治具端子出力セット
                       ptt_Ctrl_word.Gas_ctrl_code                          = OFF; //ガス停止 2009.12.16
                       gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //2009.12.16
                       break;
                 case  START_UP_SIGNAL_ERR:      //トーチスイッチ異常
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b5 = ON;
                       gub_Err = ON;             //エラー治具端子出力セット
                       ptt_Ctrl_word.Gas_ctrl_code                          = OFF; //ガス停止 2009.12.14
                       gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //2009.12.14
                       break;
                 case  SEC_OVER_CURRENT_ERR:     //二次過電流異常
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b1 = ON;
                       gub_Err = ON;             //エラー治具端子出力セット
                       ptt_Ctrl_word.Gas_ctrl_code                          = OFF; //ガス停止 2009.12.14
                       gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //2009.12.14
                       break;
                 case  EMERGENCY_STOP_ERR:       //非常停止
                       gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b2 = ON;
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  EMERGENCY2_STOP_ERR:      //非常停止2 2007.2.9
                       gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b3 = ON;
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  CURRENT_DETECT_ERR:       //電流検出異常
                       //gtt_Ext_out.Data5 = ON;
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  PRI_OVER_VOLTAGE_ERR:     //一次高電圧異常
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b3 = ON;
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  PRI_LOW_VOLTAGE_ERR:      //一次低電圧異常
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b4 = ON;
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  R8_COM_ERR:               //Ｒ８との通信異常
                       gtt_Internal_pack.Data.Out.fErrorCode3.Bit1Sw.b6 = ON;  //ＣＰＵ異常
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  MORTOR_CONTROL_ERR:     //モータ回転異常（モータ過電流異常）
                       gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b7 = ON;  //モータ回転異常
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  RS422_OVR_ERR:            //ＲＳ４２２オーバーランエラー
                 case  RS422_PTY_ERR:            //ＲＳ４２２パリティーエラー
                 case  RS422_FLM_ERR:            //ＲＳ４２２フレーミングエラー
                 case  RS232_OVR_ERR:            //ＲＳ２３２オーバーランエラー
                 case  RS232_PTY_ERR:            //ＲＳ２３２パリティーエラー
                 case  RS232_FLM_ERR:            //ＲＳ２３２フレーミングエラー
                 case  RS422_TIME_OUT_ERR:       //４２２シリアル通信タイムアウトエラー
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
                 case  IIF_CONNECT_ERR:          //ＩＩＦ切断エラー 2009.11.04 IIF NEW
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                 case  PRI_CURR_FB1_ERR:        //2007.1.18追加　2007.1.26移植追加
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b6 = ON;  //ＣＴオフセット異常
                       gub_Err = ON;             //エラー治具端子出力セット
                       break;
                 case  PRI_OVER_CURRENT_ERR:     //2008.11.17
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b6 = ON;  //ＣＴオフセット異常
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  SEC_OVER_VOLTAGE_ERR:     //2008.11.17
                       gtt_Internal_pack.Data.Out.fErrorCode2.Bit1Sw.b0 = ON;  //二次過電圧異常
                       gub_Alarm = ON;          //アラーム治具端子出力セット
                       break;
                 case  ELROD_SHORT_ERR:         //電極短絡異常 2009.07.24
                       gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON;
                       gub_Err = ON;             //エラー治具端子出力セット
                 default:
                       break;
         }
         
         switch (puc_Add_err_code)  //エラーレベル毎のエラー処理
         {
                 case  ERR_LEVEL0:               //エラーレベル０の処理
                       break;
                 case  ERR_LEVEL1:               //エラーレベル１の処理
                       //if (ComuniPack.Data.bRS232Connection == OFF && ComuniPack.Data.bRS422Connection == OFF)             //ハンド時の処理
                       if (guc_Robot_connect_flag == false)             //ハンド時の処理 2008.10.03
                       {
                           gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = OFF;// 内部使用のトーチスイッチ変数をＯＦＦ
		           ComuniPack.Data.To.fWelderCommand.Bit1Sw.Toch_sw        = OFF;// 通信使用のトーチスイッチ変数をＯＦＦ
                           gtt_Ctrl_flag.Ts_cancel                                 = ON; //ＴＳ受付禁止
                           gtt_Ctrl_flag.Err_ts_cansel                             = ON; //2009.12.18
                           guc_Gas_on_off_flag                                     = OFF; //2010.01.07
                           guc_Sw_rewrite_check_flag                               = 2;   //ＬＥＤを消すためにコールする。2010.01.07

                       }
                       //ロボット時の処理
                       //なにもしない
                       break;
                 case  ERR_LEVEL2:               //エラーレベル２の処理
                       //gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = OFF;// 内部使用のトーチスイッチ変数をＯＦＦ
		       //ComuniPack.Data.To.fWelderCommand.Bit1Sw.Toch_sw        = OFF;// 通信使用のトーチスイッチ変数をＯＦＦ
                       //gtt_Ctrl_flag.Ts_cancel                                 = ON; //ＴＳ受付禁止
                       ptt_Ctrl_word.Motor_ctrl_code    = OFF;       //モータ停止
                       ptt_Ctrl_word.Gas_ctrl_code      = OFF;       //ガス停止 2009.07.27 del 2009.12.16復帰
                       ptt_Ctrl_word.Inverter_ctrl_code = OFF;       //インバータ停止
                       ptt_Ctrl_word.Welder_ctrl_code   = OFF;       //インバータ停止
                       ptt_Ctrl_word.Mg_ctrl_code       = OFF;       //マグネットＳＷ停止
                       gtt_Ctrl_flag.Emg2_cancel        = ON;        //2007.3.14 ＰＯより移植
                       gtt_Ctrl_flag.Err_ts_cansel      = ON; //2009.12.18
                       
                       gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //2008.11.06 2009.07.27 del 2009.12.16復帰
                       //START1 = ON; //2008.11.06   2009.01.31 del
                       //START2 = OFF; //2008.11.06  2009.01.31 del
                       //HF_OUT = ON; //2009.01.31
                       HF_OUT = OFF; //2009.01.31 2009.12.14 ON->OFF
                       guc_R8_control.Bit1Sw.Over_lay = false; //2008.11.06
                       

                       if (guc_Robot_connect_flag == false)             //ハンド時の処理 2010.01.07
                       {
                           guc_Gas_on_off_flag                                     = OFF; //2010.01.07
                           guc_Sw_rewrite_check_flag                               = 2;   //ＬＥＤを消すためにコールする。2010.01.07
                       }
                       //<><><><> エラー時ガスＯＦＦ遅れ処理 2009.07.27 <><><><>
#if 0 // 2009.07.27 2009.12.14 1->0
                       if (gtt_Ctrl_flag.Err_gas == OFF)
                       {
                           gtt_Ctrl_flag.Err_gas = ON;
                           gtt_Ctrl_counter.Err_gas = gtt_Internal_pack.Data.In.sAfterFlowTime * 20;
                       } else if (gtt_Ctrl_counter.Err_gas <= 0) {
                           gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF;
                           ptt_Ctrl_word.Gas_ctrl_code      = OFF;       //ガス停止
                       }
#endif
                       //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>
                       
                       break;
                 case  ERR_LEVEL3:               //エラーレベル３の処理
                       ptt_Ctrl_word.Motor_ctrl_code    = OFF;       //モータ停止
                       //ptt_Ctrl_word.Gas_ctrl_code      = OFF;       //ガス停止 2009.07.27 del
                       ptt_Ctrl_word.Inverter_ctrl_code = OFF;       //インバータ停止
                       ptt_Ctrl_word.Welder_ctrl_code   = OFF;       //インバータ停止
                       ptt_Ctrl_word.Mg_ctrl_code       = OFF;       //マグネットＳＷ停止
                       ptt_Ctrl_word.Sequence_ctrl_code = ON;        //シーケンス停止
                       
                       //gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //2008.11.06 2009.07.27 del
                       //START1 = ON; //2008.11.06  2009.01.31 del
                       //START2 = OFF; //2008.11.06 2009.01.31 del
                       //HF_OUT = ON; //2009.01.31
                       HF_OUT = OFF; //2009.01.31 2009.12.14 ON->OFF
                       guc_R8_control.Bit1Sw.Over_lay = false; //2008.11.06
                       
                       break;
                 default:
                       break;
         }
     } else {
                       ptt_Ctrl_word.Mg_ctrl_code       = ON;       //マグネットＳＷ起動
#if 0
                       if (gtt_Ctrl_counter.Welder_init_execution >= 20000) //2007.1.22　２０→２００００に変更  2007.1.26変更を移植
                       {
                           gtt_Ctrl_flag.Welder_init_execution = OFF;
                       } else {
                           gtt_Ctrl_counter.Welder_init_execution++;
                       }
#endif
                       gtt_Ctrl_flag.Ts_cancel          = OFF;      //ＴＳ受付許可
                       gtt_Ctrl_flag.Emg2_cancel        = OFF;       //2007.3.14 ＰＯより移植
                       //gtt_Internal_pack.Data.Out.fErrorCode1.ALL = gtt_Internal_pack.Data.Out.fErrorCode1.ALL & 0x01; //溶接・送給異常検出
                       gtt_Internal_pack.Data.Out.fErrorCode1.ALL = gtt_Internal_pack.Data.Out.fErrorCode1.ALL & 0x04; //溶接・送給異常検出 2009.07.24
                       gtt_Internal_pack.Data.Out.fErrorCode2.ALL = 0x00; //電源異常検出
                       gtt_Internal_pack.Data.Out.fErrorCode3.ALL = 0x00; //異常・停止信号検出
                       gub_Err = OFF;                             //エラー治具端子出力クリア
                       gub_Alarm = OFF;                           //アラーム治具端子出力クリア
                       gtt_Ctrl_flag.Err_gas = OFF;               //2009.07.27
                       

     }
//----- Phase6 by @Tny 2008/09/10 -----
#if true
    if(gub_System_err == ON){   // エラー発生？
        if((guc_Error_code != 0)&&(guc_Error_code != guc_Error_no_backup)){ // 記録すべき情報？
//----- Phase29 by @Tny 2008/11/21 -----
#if true
			if((guc_Error_code != PRI_LOW_VOLTAGE_ERR) || ((guc_Error_code == PRI_LOW_VOLTAGE_ERR)&&(gus_Pri_volt_err_timer <= 0))){
#endif
//--------------------------------------------
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
//----- Phase29 by @Tny 2008/11/21 -----
#if true
			}
#endif
//--------------------------------------------
        }
        else{
            if((gtt_Internal_pack.Data.Out.fErrorCode1.ALL == 0)&&(gtt_Internal_pack.Data.Out.fErrorCode2.ALL == 0)&&(gtt_Internal_pack.Data.Out.fErrorCode3.ALL == 0)){
//----- Phase13 by @Tny 2008/09/18 -----
#if true	// Phase27 by @Tny 2008.10.31 2008.11.17移植
				if(guc_Remo_table_check_flag == false){	// テーブル無し条件状態？
					ch_play_class(0);	// ０チャンネルを再読み込み
					guc_Remo_table_check_flag = true;
				}
                ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no	= 0;	// ７セグ＆１５セグＬＥＤ点灯制御：全て常時点灯
#else
                guc_Error_return_LED_control_A = 8; // 「エラー復帰時ＬＥＤ表示制御インデックス：Ａ」の設定
                guc_Error_return_LED_control_B = 8; // 「エラー復帰時ＬＥＤ表示制御インデックス：Ｂ」の設定
                gtt_Ctrl_counter.Backup_100m   = Timer._100m;
                REMO_Send_CMD(0x23);
#endif
//--------------------------------------------
            }
        }
    }
    else{
//----- Phase29 by @Tny 2008/11/21 -----
#if true
		gus_Pri_volt_err_timer	= PRI_VOLT_LOW_TIME;	// 一次電圧低異常検知ディレイタイマー
#endif
//--------------------------------------------
        if(guc_Error_code != guc_Error_no_backup){
//----- Phase13 by @Tny 2008/09/18 -----
#if true	// Phase27 by @Tny 2008.10.31 2008.11.17移植
			if(guc_Remo_table_check_flag == false){	// テーブル無し条件状態？
				ch_play_class(0);	// ０チャンネルを再読み込み
				guc_Remo_table_check_flag = true;
			}
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no	= 0;	// ７セグ＆１５セグＬＥＤ点灯制御：全て常時点灯
#else
            guc_Error_return_LED_control_A = 8; // 「エラー復帰時ＬＥＤ表示制御インデックス：Ａ」の設定
            guc_Error_return_LED_control_B = 8; // 「エラー復帰時ＬＥＤ表示制御インデックス：Ｂ」の設定
            gtt_Ctrl_counter.Backup_100m   = Timer._100m;
            REMO_Send_CMD(0x23);
#endif
//--------------------------------------------
        }
        guc_Error_no_backup = 0; // エラー情報重複記録防止のためのエラー番号記憶値をクリア
    }
#endif
//--------------------------------------------
     return (ptt_Ctrl_word);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_err_process_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

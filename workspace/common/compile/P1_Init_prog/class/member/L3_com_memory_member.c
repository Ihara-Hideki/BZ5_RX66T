//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｃｏｍ＿ｍｅｍｏｒｙ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      通信変数初期化
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

extern char TOGLE_FLAG;
void com_memory_member(ubool AllInitial)
{
	ubool	bInitialProc	= false;	// BP4 Phase6 by @Tny 2009-02-12
     unsigned char puc_Index; //2008.08.21

     RCV_Mode                   = DLE_mode;
     SND_Mode                   = DLE_mode_SD;
     CMD_DATA_RX                = NUL;
     SUM_ADD_RxData             = NUL;
     SUM_ADD_TxData             = NUL;
     RCV_Position               = NUL;
     DATA_Length_RX             = NUL;
     GD2_ACK_count              = NUL;
     GD2_NAK_count              = NUL;
     GD2_Busy_count             = NUL;
     SND_CMD_Position           = NUL;
     SND_CMD_Proc               = NUL;
     data_count_tx              = NUL;
     DATA_Length_TX             = NUL;
     DLE_check_flag             = false;         // データ部内でのDLEコード受信判定フラグの初期化
     DLE_check_flagSD           = false;
     sio_table_flag             = false;
     SND_Timer                  = NUL;
     WAIT_SD_count              = NUL;
     RS422ErrorFlag             = NUL;
     TXB1_Proc_Position         = NUL;
     TXB1_Position              = NUL;
     RXB1_Proc_Position         = NUL;
     RXB1_Position              = NUL;
     SoutPC_No                  = NUL;
     Checker_flag               = OFF;
     data_count_rx              = NUL;
     ACK_SND_Mode               = DLE_mode_SD;
     sio_table_flagPC           = OFF;

     motor_rpm			= NUL;
     TableData_exit		= ON;
     MAX_CURRENT		        = MAX_CURRENT_VAL;	        // 2010.01.12 500BP4 DC,AC_STD,AC_HARD,MIX
     MAX_CURRENT_AC_SOFT        = MAX_CURRENT_AC_SOFT_VAL;  // 2010.01.12 500BP4 AC_SOFT
     MAX_CURRENT_HAND           = MAX_CURRENT_HAND_VAL;     // 2010.01.12 500BP4 HAND
     MIN_CURRENT                = MIN_CURRENT_VAL;          // 2010.01.12 500BP4 DC
     MIN_CURRENT_AC             = MIN_CURRENT_AC_VAL;       // 2011.09.30 AC_STD AC_SOFT MIX
     MIN_CURRENT_AC_HARD        = MIN_CURRENT_AC_HARD_VAL;  // 2011.09.30 AC_HAND
     MIN_CURRENT_HAND           = MIN_CURRENT_HAND_VAL;     // 2010.01.12 500BP4 HAND
     MAX_CURRENT_ABS            = MAX_CURRENT_VAL;          // 2010.01.18 500BP4 絶対値

     TPX_G2_Send_OFF            = OFF;	//製品検査用
     Check_G2_Send_OFF          = OFF;	//製品検査用

     TOGLE_FLAG                 = false;


//remo
     RE_RCV_Mode                   = DLE_mode;
     RE_SND_Mode                   = DLE_mode_SD;
     RE_CMD_DATA_RX                = NUL;
     RE_SUM_ADD_RxData             = NUL;
     RE_SUM_ADD_TxData             = NUL;
     RE_RCV_Position               = NUL;
     RE_DATA_Length_RX             = NUL;
     REMO_ACK_count              = NUL;
     REMO_NAK_count              = NUL;
     REMO_Busy_count             = NUL;
     RE_SND_CMD_Position           = NUL;
     RE_SND_CMD_Proc               = NUL;
     RE_data_count_tx              = NUL;
     RE_DATA_Length_TX             = NUL;
     RE_DLE_check_flag             = false;         // データ部内でのDLEコード受信判定フラグの初期化
     RE_DLE_check_flagSD           = false;
     RE_SND_Timer                  = NUL;
     RE_WAIT_SD_count              = NUL;
     RE_Checker_flag               = OFF;
     RE_data_count_rx              = NUL;
     RE_ACK_SND_Mode               = DLE_mode_SD;

     TPX_REMO_Send_OFF            = OFF;	//製品検査用
     Check_REMO_Send_OFF          = OFF;	//製品検査用






     ComuniPack.Data.bRS422Connection	= false;	// ＲＳ４２２側回線接続状態の初期化
     ComuniPack.Data.bRS232Connection	= false;	// ＲＳ２３２ｃ側回線接続状態の初期化
     ComuniPackRemo.Data.bRS422Connection	= false;	// ＲＳ４２２側回線接続状態の初期化

     // 受信データパッケージの初期化
     ComuniPack.Data.To.bChangeData                        = false;  // 受信データ更新フラグの初期化
     ComuniPack.Data.To.iRecvCommand                       = 0;      // 受信コマンド（データ更新判別用）の初期化
     if(AllInitial){	// 記憶データの初期化が必要？
        ComuniPack.Data.To.usWeldingCurr                   = 120;    // 出力電流指令値
        ComuniPack.Data.To.usWeldingVolt                   = 184;    // 出力電圧指令値
        ComuniPack.Data.To.fWireDiameter.ALL               = 4;      // ワイヤ径   1.2mm
        ComuniPack.Data.To.fWelding.ALL                    = 0;      // 溶接法     CO2
        ComuniPack.Data.To.fWireMaterial.ALL               = 0;      // ワイヤ材質 軟鋼
        ComuniPack.Data.To.fWireSelect.ALL                 = 0;      // ワイヤ種
        ComuniPack.Data.To.fInitialSelect1.ALL             = 0;      // 初期データ設定１
        ComuniPack.Data.To.vTsoAdj                         = 0;      // 短絡初期時間調整
        ComuniPack.Data.To.vIscAdj                         = 0;      // 短絡電流屈折値調整
        ComuniPack.Data.To.vIsl1Adj                        = 0;      // 短絡電流勾配１調整
        ComuniPack.Data.To.vIsl2Adj                        = 0;      // 短絡電流勾配２調整
        ComuniPack.Data.To.vTspAdj                         = 0;      // 突っ掛かり防止時間調整
        ComuniPack.Data.To.vIacAdj                         = 0;      // アーク電流屈折値調整
        ComuniPack.Data.To.vIhotAdj                        = 0;      // ホット電流調整
        ComuniPack.Data.To.vVhotAdj                        = 0;      // ホット電圧調整
        ComuniPack.Data.To.vSldnAdj                        = 0;      // ワイヤスローダウン調整
        ComuniPack.Data.To.vFttAdj                         = 0;      // ＦＴＴレベル調整
        ComuniPack.Data.To.vBarnBackAdj                    = 0;      // バーンバック時間調整
        ComuniPack.Data.To.fWelderCommand.ALL              = 0;      // 溶接電源動作指令
        ComuniPack.Data.To.fWelderCheck.ALL                = 0;      // 溶接電源チェック
        ComuniPack.Data.To.usIP                            = 0;      // パルスピーク指令電流
        ComuniPack.Data.To.usIB                            = 0;      // パルスベース指令電流
        ComuniPack.Data.To.usPulseFreq                     = 0;      // パルス指令周波数
        ComuniPack.Data.To.usPulseDuty                     = 0;      // パルス指令幅
        ComuniPack.Data.To.usAcFreq                        = 0;      // 交流周波数
        ComuniPack.Data.To.ucCleaningDuty                  = 0;      // クリーニング幅
        ComuniPack.Data.To.ucMixFreq                       = 0;      // MIX TIG周波数
        ComuniPack.Data.To.ucMixAcRatio                    = 0;      // MIX(AC)比率
        ComuniPack.Data.To.fControl.ALL                    = 0;      // コントロール
        ComuniPack.Data.To.ucImprudenceVolt                = 0;      // 電極短絡電圧指令値
        ComuniPack.Data.To.fPulseMode.ALL                  = 0;      // パルスモード設定
        ComuniPack.Data.To.vHotTime                        = 0;      // ホットタイム
        ComuniPack.Data.To.vIniIpAdj                       = 0;      // スタートピーク電流微調整
        ComuniPack.Data.To.vIniIbAdj                       = 0;      // スタートベース電流微調整
        ComuniPack.Data.To.vIpAdj                          = 0;      // パルスピーク電流微調整
        ComuniPack.Data.To.vIb1Adj                         = 0;      // パルス第１ベース電流微調整
        ComuniPack.Data.To.vIb2Adj                         = 0;      // パルス第２ベース電流微調整
        ComuniPack.Data.To.vIprAdj                         = 0;      // パルスピーク立ち上がり微調整
        ComuniPack.Data.To.vIpfAdj                         = 0;      // パルスピーク立ち下がり微調整
        ComuniPack.Data.To.vTiprAdj                        = 0;      // パルス立ち上がり時間微調整
        ComuniPack.Data.To.vTipAdj                         = 0;      // パルスピーク立ち上がり時間微調整
        ComuniPack.Data.To.vTipfAdj                        = 0;      // パルス立ち下がり時間微調整
        ComuniPack.Data.To.vPulseFreqAdj                   = 0;      // パルス周波数微調整
        ComuniPack.Data.To.vLowPulseAB_LevelGap            = 0;      // 簡易ローパルス：Ａ条件Ｂ条件レベル差
        ComuniPack.Data.To.vLowPulseAB_TimeRatio           = 0;      // 簡易ローパルス：Ａ条件Ｂ条件時間比率
        ComuniPack.Data.To.vLowPulseFreq                   = 0;      // 簡易ローパルス：周波数
        ComuniPack.Data.To.vLowPulseStartTimeAdj           = 0;      // 簡易ローパルス開始時間微調整
        ComuniPack.Data.To.vPulseStartSlope                = 0;      // パルススタートスロープ
        ComuniPack.Data.To.vPulseExecSlope                 = 0;      // パルス指令値切り替えスロープ
        ComuniPack.Data.To.vPulsePerformance               = 0;      // パルス応答性
        ComuniPack.Data.To.fLotCheck.ALL                   = 0;      // 製品検査用
        ComuniPack.Data.To.vAfterFlowAddTime               = 0;      // アフターフロー時間加算値
	    ComuniPack.Data.To.vTableChange                    = 0;      // ＣＯ２テーブル切り替え 2007.2.9
     }
	// 送信データパッケージの初期化
        ComuniPack.Data.From.ucModelCode                   = IdentificationCode;              // 機種別コード
        ComuniPack.Data.From.ucPassword                    = 0;                               // パスワード変換後データ
#if G3_NEW_COM
        ComuniPack.Data.From.sRomVersion[0]                = guc_Attribute_version[0];        //ROMver　上位
        ComuniPack.Data.From.sRomVersion[1]                = guc_Attribute_version[1];        //ROMver　中位
        ComuniPack.Data.From.sRomVersion[2]                = guc_Attribute_version[2];        //ROMver　上位

        ComuniPack.Data.From.Kind_code                     = guc_Attribute_kind_code;         //種別（Ｄ：ＭＡＧ　Ｃ：ＴＩＧ）

        ComuniPack.Data.From.Capacity_code[0]              = guc_Attribute_capacity_code[0];  //定格出力　百の位
        ComuniPack.Data.From.Capacity_code[1]              = guc_Attribute_capacity_code[1];  //定格出力　十の位
        ComuniPack.Data.From.Capacity_code[2]              = guc_Attribute_capacity_code[2];  //定格出力　一の位
    
        ComuniPack.Data.From.Model_code[0]                 = guc_Attribute_model_code[0];     //機種（例ＧＺ３：Ｇ）
        ComuniPack.Data.From.Model_code[1]                 = guc_Attribute_model_code[1];     //機種（例ＧＺ３：Ｚ）
        ComuniPack.Data.From.Model_code[2]                 = guc_Attribute_model_code[2];     //機種（例ＧＺ３：３）
    
        ComuniPack.Data.From.Special_code[0]               = guc_Attribute_special_code[0];   //特殊品（例ＴＡＥ：Ｔ）
        ComuniPack.Data.From.Special_code[1]               = guc_Attribute_special_code[1];   //特殊品（例ＴＡＥ：Ａ）
        ComuniPack.Data.From.Special_code[2]               = guc_Attribute_special_code[2];   //特殊品（例ＴＡＥ：Ｅ）
#else
        ComuniPack.Data.From.sRomVersion[0]                = (uchar)Version[0];          // ROMバージョン
        ComuniPack.Data.From.sRomVersion[1]                = (uchar)Version[1];          // ROMバージョン
#endif
        ComuniPack.Data.From.usWeldingCurr                 = 120;                        // 出力電流指令値
        ComuniPack.Data.From.usWeldingVolt                 = 184;                        // 出力電圧指令値
        ComuniPack.Data.From.usWeldingOutCurr              = 0;                          // 出力電流値
        ComuniPack.Data.From.usWeldingOutVolt              = 0;                          // 出力電圧値
        ComuniPack.Data.From.ucImprudence                  = 0;                          // 短絡回数
        ComuniPack.Data.From.ucMotorCurr                   = 0;                          // モータ電流値
        ComuniPack.Data.From.ucMotorRPM                    = 0;                          // モータ回転数
        ComuniPack.Data.From.ucMotorCurr2                  = 0;                          // モータ電流値２
        ComuniPack.Data.From.usMotorRPM2                   = 0;                          // モータ回転数２
        ComuniPack.Data.From.fErrorCode1.ALL               = 0;                          // 異常検出状態（溶接・送給系）
        ComuniPack.Data.From.fErrorCode2.ALL               = 0;                          // 異常検出状態（電源系）
        ComuniPack.Data.From.fErrorCode3.ALL               = 0;                          // 異常検出状態（異常・停止信号検出系）
        ComuniPack.Data.From.fPowerStatus.ALL              = 0;                          // 溶接電源状態
        ComuniPack.Data.From.usIP                          = 0;                          // パルスピーク電流
        ComuniPack.Data.From.usIB                          = 0;                          // パルスベース電流
        ComuniPack.Data.From.usPulseFreq                   = 0;                          // パルス周波数
        ComuniPack.Data.From.fArcStartStatus.ALL           = 0;                          // アークスタート状態

        if(AllInitial){	// 記憶データの初期化が必要？
           ComuniPack.Data.From.BackUp.usWeldTimes           = 0;                        // 溶接回数
           ComuniPack.Data.From.BackUp.usWeldTimerIndividual = 0;                        // 溶接時間(個別)
           //ComuniPack.Data.From.BackUp.usWeldTimerL          = 0;                        // 溶接時間(L)
           //ComuniPack.Data.From.BackUp.usWeldTimerH          = 0;                        // 溶接時間(H)
           ComuniPack.Data.From.BackUp.usWireFeed            = 0;                        // ワイヤ総送給量
        }

        //起動時の誤送信を防ぐため初期化
        gtt_Internal_pack.Data.Out.fErrorCode1.ALL  = ComuniPack.Data.From.fErrorCode1.ALL;        //溶接・送給異常検出
        gtt_Internal_pack.Data.Out.fErrorCode2.ALL  = ComuniPack.Data.From.fErrorCode2.ALL;        //電源異常検出
        gtt_Internal_pack.Data.Out.fErrorCode3.ALL  = ComuniPack.Data.From.fErrorCode3.ALL;        //異常・停止信号検出
        gtt_Internal_pack.Data.Out.fPowerStatus.ALL = ComuniPack.Data.From.fPowerStatus.ALL;       //溶接電源状態（電流検出）

        //起動時半固定テーブル初期化のため
        gtt_Table_key.Wire_diameter  = 0x05; //1.2mm
        gtt_Table_key.Welding_method = 0x01; //CO2
        gtt_Table_key.Wire_material  = 0x01; //軟鋼
        gtt_Table_key.Pulse_mode     = 0x03;                    // 溶接種別フラグ
        gtt_Table_key.Pulse_type     = 0x00;                    // パルスタイプ
        gtt_Table_key.Wire_ext       = 0x03;                    // 突き出し長


#if G3_NEW_COM

        gtt_Internal_pack.Data.In.fWireDiameter.ALL          = 0x05;      // ワイヤ径
        gtt_Internal_pack.Data.In.fWelding.ALL               = 0x01;     // 溶接法
        gtt_Internal_pack.Data.In.fWireMaterial.ALL          = 0x01;      // ワイヤ材質
        gtt_Internal_pack.Data.In.fWireSelect.ALL            = 0x03;        // 突き出し長
        gtt_Internal_pack.Data.In.fPulseMode.ALL             = 0x13;      // パルスモード設定
  
        ComuniPack.Data.To.fWireDiameter.ALL          = 0x05;      // ワイヤ径
        ComuniPack.Data.To.fWelding.ALL               = 0x01;     // 溶接法
        ComuniPack.Data.To.fWireMaterial.ALL          = 0x01;      // ワイヤ材質
        ComuniPack.Data.To.fWireSelect.ALL            = 0x03;        // 突き出し長
        ComuniPack.Data.To.fPulseMode.ALL             = 0x13;      // パルスモード設定


        gtt_Table_key.Wire_diameter_bkup  = gtt_Internal_pack.Data.In.fWireDiameter.ALL;       // ワイヤ径
        gtt_Table_key.Welding_method_bkup = gtt_Internal_pack.Data.In.fWelding.ALL;            // 溶接法
        gtt_Table_key.Wire_material_bkup  = gtt_Internal_pack.Data.In.fWireMaterial.ALL;       // ワイヤ材質
        gtt_Table_key.Pulse_mode_bkup     = (gtt_Internal_pack.Data.In.fPulseMode.ALL >> 4) & 0x0f;               // 溶接種別フラグ
        gtt_Table_key.Pulse_type_bkup     = (gtt_Internal_pack.Data.In.fPulseMode.ALL)      & 0x0f;               // パルスタイプ



#else
        gtt_Internal_pack.Data.In.fWireDiameter.ALL          = 0x04;      // ワイヤ径
        gtt_Internal_pack.Data.In.fWelding.ALL               = 0x00;     // 溶接法
        gtt_Internal_pack.Data.In.fWireMaterial.ALL          = 0x00;      // ワイヤ材質
        gtt_Internal_pack.Data.In.fWireSelect.ALL            = 0x03;        // 突き出し長
        gtt_Table_key.Wire_diameter_bkup  = gtt_Internal_pack.Data.In.fWireDiameter.ALL;       // ワイヤ径
        gtt_Table_key.Welding_method_bkup = gtt_Internal_pack.Data.In.fWelding.ALL;            // 溶接法
        gtt_Table_key.Wire_material_bkup  = gtt_Internal_pack.Data.In.fWireMaterial.ALL;       // ワイヤ材質
#endif

        guc_Table_change_flag = OFF; //2007.2.9

        //<><><><><> ＲＡＭバックアップ分の読み出し 2007.3.30 <><><><><>
        gtt_Internal_pack.Data.Out.BackUp.usWeldTimer = gui_Total_weld_time_bkup;  //総合溶接時間ＲＡＭから読み出し
        gtt_Internal_pack.Data.Out.BackUp.usWeldTimes = gus_Total_weld_count_bkup; //溶接回数ＲＡＭから読み出し　2007.4.5
        gtt_Internal_pack.Data.Out.BackUp.usWireFeed  = gul_Total_wire_feed_bkup;  //ワイヤ送給量ＲＡＭから読み出し 2007.4.5



//----- Phase15 by @Tny 2008/09/19 -----
#if true
        guc_Sequence_mode = IDLING;
#endif
//--------------------------------------------
        ch_play_class(0); //ｃｈ０の読み込み 2008.08.07
        guc_Sw_rewrite_check_flag = 1; //2008.09.16テーブルサーチを行う。

        //チャンネル書き込み判定フラグ初期化
        for (puc_Index = 0 ; puc_Index <= CH -1 ; puc_Index++)
        {
             guc_Write_check_flag[puc_Index] = 0;
             if (guc_Write_check_flag_ch[puc_Index] == 1)
             {
                 guc_Write_check_flag[puc_Index] = guc_Write_check_flag_ch[puc_Index];
                 dummy_access = 1;
             }
        }

        //gtt_Internal_pack.Data.In.usAcFreq = 70; //2009.02.06鳴戸さん実験仕様　起動時70にすること。

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
        //ＩＩＦシフト量の読み込み 2009.11.16 IIF NEW
        iif_analog_shift_memory_class(0);
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

     //<><><>初期化（プログラム書き込み後初めて起動した時やバックアップ内容を忘れた場合）2008.02.26<><><>
        if (guc_Initial_load_data != 0x55)
        {
			bInitialProc				  = true;	   // BP4 Phase6 by @Tny 2009-02-12
            guc_Wire_condition_data       = 0x05;      // ワイヤ径 1.2    2008.11.27
            guc_Method_condition_data     = 0x03;      // 溶接法   MIG    2008.11.27
            guc_Material_condition_data   = 0x03;      // ワイヤ材質 ALH  2008.11.27
            guc_Ext_condition_data        = 0x00;      // 突き出し長 2008.11.10
            gs_Okcv_adjust_data           = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_init_data      = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_crat_data      = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_wave_data      = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_start_data     = 0x00;      //一元電圧微調整分の書き戻し 2008.08.05
 
            guc_Material_condition_counter = 0x01;
            guc_Wire_condition_counter     = 0x01;
            //guc_Method_condition_counter   = 0x01;    2009.02.24 del
            //guc_Pulse_mode_counter         = 0x01; //2008.02.08 2009.02.24 del
            
            //guc_Pulse_mode_data            = 0x85; //2008.11.27  2009.02.24 del
            //guc_Pulse_type_data            = 0x00; //2008.02.08  2009.02.24 del
            
            guc_Okcv_select_flag = true;  //一元デフォルト
            {
                unsigned char Index;
                for (Index = 0 ; Index < 7 ; Index++)
                {
                     guc_Method_m[Index]           = Index;
                     dummy_access = 1;
                     gus_Main_current_m[Index]     = 50;
                     dummy_access = 1;
                     gus_Init_current_m[Index]     = 50;
                     dummy_access = 1;
                     gus_Crat_current_m[Index]     = 50;
                     dummy_access = 1;
                     guc_Pulse_mode_m[Index]       = 0;
                     dummy_access = 1;
                     guc_Crater_mode_m[Index]      = 0;
                     dummy_access = 1;
                     guc_Ac_wave_counter_m[Index]  = 0; //2009.03.13
                     dummy_access = 1;
                     gus_Pulse_current_m[Index]    = 50;
                     dummy_access = 1;
                     gus_Pulse_duty_m[Index]       = 50;
                     dummy_access = 1;
                     //gus_Pulse_frequency_m[Index]  = 100;
                     gus_Pulse_frequency_m[Index]  = 50; //2009.02.24 最大5.0Hzのため仮に50とする。
                     dummy_access = 1;
                     guc_AC_cleaning_duty_m[Index] = 30; //2009.04.01 移動
                     dummy_access = 1;
                     gus_AC_frequency_m[Index]     = 70; //2009.04.01 移動
                     dummy_access = 1;
                     guc_MIX_frequency_m[Index]    = 10;
                     dummy_access = 1;
                     guc_MIX_duty_m[Index]         = 30;
                     dummy_access = 1;
                     gss_Pre_flow_m[Index]         =  3;
                     dummy_access = 1;
                     gss_After_flow_m[Index]       = 50;
                     dummy_access = 1;
                     gss_Up_slop_m[Index]          =  2;
                     dummy_access = 1;
                     gss_Down_slop_m[Index]        =  2;
                     dummy_access = 1;
                     gss_Arc_spot_time_m[Index]    = 10; //2009.03.06
                     dummy_access = 1;
                  }
            }

                     //ＡＣ標準、ハード、ソフト各波形の初期化 2009.04.01
                     //<><><>標準ＡＣ<><><>
                     //標準波形
                     gus_Main_current_m[11]     = 50;
                     dummy_access = 1;
                     gus_Init_current_m[11]     = 50;
                     dummy_access = 1;
                     gus_Crat_current_m[11]     = 50;
                     dummy_access = 1;
                     gus_Pulse_current_m[11]    = 50;
                     dummy_access = 1;
                     guc_AC_cleaning_duty_m[11] = 30;
                     dummy_access = 1;
                     gus_AC_frequency_m[11]     = 70;
                     dummy_access = 1;
                     //ハード波形
                     gus_Main_current_m[12]     = 50;
                     dummy_access = 1;
                     gus_Init_current_m[12]     = 50;
                     dummy_access = 1;
                     gus_Crat_current_m[12]     = 50;
                     dummy_access = 1;
                     gus_Pulse_current_m[12]    = 50;
                     dummy_access = 1;
                     guc_AC_cleaning_duty_m[12] = 20;
                     dummy_access = 1;
                     gus_AC_frequency_m[12]     = 70;
                     dummy_access = 1;
                     //ソフト波形
                     gus_Main_current_m[13]     = 50;
                     dummy_access = 1;
                     gus_Init_current_m[13]     = 50;
                     dummy_access = 1;
                     gus_Crat_current_m[13]     = 50;
                     dummy_access = 1;
                     gus_Pulse_current_m[13]    = 50;
                     dummy_access = 1;
                     guc_AC_cleaning_duty_m[13] = 30;
                     dummy_access = 1;
                     gus_AC_frequency_m[13]     = 70;
                     dummy_access = 1;

                     //<><><>エキスパートＡＣ<><><>
                     //標準波形
                     gus_Main_current_m[21]     = 50;
                     dummy_access = 1;
                     gus_Init_current_m[21]     = 50;
                     dummy_access = 1;
                     gus_Crat_current_m[21]     = 50;
                     dummy_access = 1;
                     gus_Pulse_current_m[21]    = 50;
                     dummy_access = 1;
                     guc_AC_cleaning_duty_m[21] = 30;
                     dummy_access = 1;
                     gus_AC_frequency_m[21]     = 70;
                     dummy_access = 1;
                     //ハード波形
                     gus_Main_current_m[22]     = 50;
                     dummy_access = 1;
                     gus_Init_current_m[22]     = 50;
                     dummy_access = 1;
                     gus_Crat_current_m[22]     = 50;
                     dummy_access = 1;
                     gus_Pulse_current_m[22]    = 50;
                     dummy_access = 1;
                     guc_AC_cleaning_duty_m[22] = 20;
                     dummy_access = 1;
                     gus_AC_frequency_m[22]     = 70;
                     dummy_access = 1;
                     //ソフト波形
                     gus_Main_current_m[23]     = 50;
                     dummy_access = 1;
                     gus_Init_current_m[23]     = 50;
                     dummy_access = 1;
                     gus_Crat_current_m[23]     = 50;
                     dummy_access = 1;
                     gus_Pulse_current_m[23]    = 50;
                     dummy_access = 1;
                     guc_AC_cleaning_duty_m[23] = 30;
                     dummy_access = 1;
                     gus_AC_frequency_m[23]     = 70;
                     dummy_access = 1;


            //***** BP4用初期化 2009.02.19 ********************************
            guc_Method_condition_data                   = 0;
            guc_Method_condition_counter                = 0;
            guc_Crater_mode_counter                     = 0;
            guc_Pulse_mode_data                         = 0;
            guc_Pulse_mode_counter                      = 0;
            guc_Ac_wave_counter                         = 0;
            gus_Sequence_set_data                       = NO_SET_DATA;
            guc_Pulse_item_counter                      = 1;
            guc_Ac_tig_set_counter                      = 1;
            guc_Mix_tig_set_counter                     = 1;
            guc_Select_counter                          = MODE_WELDING;
            //初期電流
            gtt_Internal_pack.Data.In.usWeldingInitCurr = 50;
            //本電流
            gtt_Internal_pack.Data.In.usWeldingCurr     = 50;
            //クレータ電流
            gtt_Internal_pack.Data.In.usWeldingCratCurr = 50;
            //パルス電流
            gtt_Internal_pack.Data.In.usIP              = 50;
            //プリフロー時間
            gtt_Internal_pack.Data.In.sPreFlowTime      = 3;
            //アフターフロー時間
            gtt_Internal_pack.Data.In.sAfterFlowTime    = 50;
            //アップスロープ時間
            gtt_Internal_pack.Data.In.sUpSlopTime       = 2;
            //ダウンスロープ時間
            gtt_Internal_pack.Data.In.sDownSlopTime     = 2;
            //パルス周波数
            //gtt_Internal_pack.Data.In.usPulseFreq       = 100;
            gtt_Internal_pack.Data.In.usPulseFreq       = 50; //2009.02.24 最大5.0Hzのため仮に50とする。
            //パルスデューティ
            gtt_Internal_pack.Data.In.usPulseDuty       = 50;
            //交流周波数
            gtt_Internal_pack.Data.In.usAcFreq          = 70;
            //クリーニング幅
            gtt_Internal_pack.Data.In.ucCleaningDuty    = 30;
            //直流比率
            gtt_Internal_pack.Data.In.ucMixAcRatio      = 30;
            //ＭＩＸ周波数
            gtt_Internal_pack.Data.In.ucMixFreq         = 10;
            //アークスポット時間
            gtt_Ditail_work.ss_Arc_spot_time            = 10; //2009.03.06 2009.03.16 unsigned->signed

            //***** 2009.02.24 *****
            //初期電流
            gus_Init_current                            = 50;
            //本電流
            gus_Weld_current                            = 50;
            //クレータ電流
            gus_Crat_current                            = 50;
            //パルス電流
            gus_Pulse_current                           = 50;
            //プリフロー時間
            gus_Pre_flow_time                           = 3;;
            //アフターフロー時間
            gus_After_flow_time                         = 50;
            //アップスロープ時間
            gus_Up_slop_time                            = 2;
            //ダウンスロープ時間
            gus_Down_slop_time                          = 2;
            //パルス周波数
            //gus_Pulse_freq                              = 100;
            gus_Pulse_freq                              = 50; //2009.02.24 最大5.0Hzのため仮に50とする。
            //パルスデューティ
            gus_Pulse_duty                              = 50;
            //交流周波数
            gus_Ac_frequency                            = 70;
            //クリーニング幅
            gus_Cleaning_duty                           = 30;
            //直流比率
            gus_Mix_ac_ratio                            = 30;
            //ＭＩＸ周波数 2009.02.06
            gus_Mix_frequency                           = 10;
            //アークスポット時間
            gss_Arc_spot_time                           = 10; //2009.03.06 2009.03.16 unsigned -> signed
        
            gtt_Ctrl_flag.Param_change = ON; //2009.02.24

            gus_Temp_err_set                            = OFF; //2009.03.13

            //*************************************************************
#if 0
            for (puc_Index = 0 ; puc_Index <= SELECT_DITAL_MAX ; puc_Index++)
            {
                 gss_Select_dital[puc_Index] = 0x00;
            }
#endif

//----- Phase8 by @Tny 2008/09/12 -----
#if true
            guc_Controller_lock         = 0;
            guc_Pass_word               = 123;
            gtt_Ctrl_flag.Param_change  = ON;
#endif
//--------------------------------------------
//----- Phase22 by @Tny 2008/10/07 -----
#if true
            gtt_Error_History.History_rec_index = 0;                    // 記録インデックスの初期化
            gtt_Error_History.Full_history_rec  = false;                // 全記録エリア使用フラグの初期化
            gtt_Error_History.Start_record      = false;                // 記録開始フラグの初期化
            gtt_Error_History.Record_identifier = ERROR_INFO_RENEWAL;   // 記録識別子のセット
            gb_Error_History_Write              = true;                 // エラー履歴テーブル保存の要求
            gus_Iif_BuiltIn                     = 0;                    // IIFは非接続
            gus_Iif_BuiltIn_write               = true;                 // IIF接続フラグの保存要求
            ch0_write_class(true);
            gus_Iif_BuiltIn_write               = false;                // IIF接続フラグ保存フラグのクリア
            gb_Error_History_Write              = false;                // エラー履歴テーブル保存フラグのクリア
            memory_initialize_class(1);                                 // ユーザ特殊パラメータ・０ｃｈ詳細データのクリア
            memory_initialize_class(2);                                 // サービスマンデータのクリア
            memory_initialize_class(3);                                 // その他全てのデータのクリア
            // 記憶テーブルの初期化
            for(puc_Index = 0 ; puc_Index <= CH -1 ; puc_Index++){
                ch_rec_class(puc_Index);
                ch_rec_class(puc_Index + MEMORY_DELETE_CH);  // 記憶チャンネル削除識別子の付加
            }


            //一部データの初期化 2009.03.02
            gss_Select_dital[P_HOT_CURR_LEVEL]    = 2;		// 1->2「微弱モード」の追加	2011.10.28
            gss_Select_dital[P_LCD_BRIGHT]        = 1;     //2009.03.07 2009.03.21 4->1
            //gss_Select_dital[P_EXECUTE_VOLTAGE_A] = 100; 2011.10.03 del
#if false	// <IIF NEW>
            gss_Select_dital[P_EXECUTE_VOLTAGE_C] = 100;
#endif
            gss_Select_dital[P_EXTARNAL_LEVEL_A]  = 100;
            gss_Select_dital[P_EXTARNAL_LEVEL_C]  = 100;
            gss_Select_dital[P_VOLTAGE_SAMPLING]  = 1;


#endif
//--------------------------------------------

        }
     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
        guc_Initial_load_data = 0x55;

            //<><><>2008.4.1　起動時０クリア<><><>
            gtt_Parameter.Item.Parameter_set[0] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[1] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[2] = 100; //2008.03.07
            gtt_Parameter.Item.Parameter_set[3] = 50; //2008.03.07
            gtt_Parameter.Item.Parameter_set[4] = 500; //2008.03.07
            gtt_Parameter.Item.Parameter_set[5] = 100; //2008.03.07
            gtt_Parameter.Item.Parameter_set[6] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[7] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[8] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[9] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[10] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[11] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[12] = 0; //2008.03.07
            
            //<><><><><><><><><><><><><><><><><><>


        //<><><> 起動時　Ｐメニュー属性初期化 BP4 Phase3 by @Tny 2009.01.13 <><><>
        gtt_Dital_attribute[0].ss_Min         =    0;      //P00	// DC TIG ｽﾀｰﾄｷｮｸｾｲ
        gtt_Dital_attribute[0].ss_Max         =    1;
        gtt_Dital_attribute[0].ss_Notch       =    1;
        gtt_Dital_attribute[0].ss_Init        =    0;	// EN
        gtt_Dital_attribute[0].uc_Point       =    0;

        gtt_Dital_attribute[1].ss_Min         =    0;      //P01	// ﾎｯﾄ ﾃﾞﾝﾘｭｳ ﾚﾍﾞﾙ
        gtt_Dital_attribute[1].ss_Max         =    3;		// 2->3「微弱モード」の追加		2011.10.28
        gtt_Dital_attribute[1].ss_Notch       =    1;
        gtt_Dital_attribute[1].ss_Init        =    2;		// 標準	// 1->2「微弱モード」の追加		2011.10.28
        gtt_Dital_attribute[1].uc_Point       =    0;

        gtt_Dital_attribute[2].ss_Min         =    0;      //P02	// ﾃﾞﾝｱﾂﾋｮｳｼﾞ ｳﾑ
        gtt_Dital_attribute[2].ss_Max         =    1;
        gtt_Dital_attribute[2].ss_Notch       =    1;
        gtt_Dital_attribute[2].ss_Init        =    0;	// 無し
        gtt_Dital_attribute[2].uc_Point       =    0;

        gtt_Dital_attribute[3].ss_Min         =    0;      //P03	// ｸﾚｰﾀ ｼｭｳﾘｮｳ ﾎｳﾎｳ
        gtt_Dital_attribute[3].ss_Max         =    1;
        gtt_Dital_attribute[3].ss_Notch       =    1;
        gtt_Dital_attribute[3].ss_Init        =    0;	// 通常
        gtt_Dital_attribute[3].uc_Point       =    0;

        gtt_Dital_attribute[4].ss_Min         =    0;      //P04	// ﾃﾞﾝｷｮｸﾀﾝﾗｸ ｳﾑ
        gtt_Dital_attribute[4].ss_Max         =    1;
        gtt_Dital_attribute[4].ss_Notch       =    1;
        gtt_Dital_attribute[4].ss_Init        =    0;	// 無し	BP4 Phase13 by @Tny 2009.02.24
        gtt_Dital_attribute[4].uc_Point       =    0;

        gtt_Dital_attribute[5].ss_Min         =    0;      //P05	// ﾋｮｳｼﾞ ﾎｼﾞ ｼﾞｶﾝ
        gtt_Dital_attribute[5].ss_Max         =  100;
        gtt_Dital_attribute[5].ss_Notch       =    1;
        gtt_Dital_attribute[5].ss_Init        =   50;	// ５．０秒
        gtt_Dital_attribute[5].uc_Point       =    2;

        gtt_Dital_attribute[6].ss_Min         =    0;      //P06	// AC ｱｰｸｷﾞﾚ ﾘｶﾊﾞﾘｰ
        gtt_Dital_attribute[6].ss_Max         =    1;
        gtt_Dital_attribute[6].ss_Notch       =    1;
        gtt_Dital_attribute[6].ss_Init        =    0;	// 有り 2009.04.08無に変更
        gtt_Dital_attribute[6].uc_Point       =    0;

        gtt_Dital_attribute[7].ss_Min         =    0;      //P07	// ﾋﾂﾞｹ/ｼﾞｶﾝ ｾｯﾃｲ
        gtt_Dital_attribute[7].ss_Max         =    1;
        gtt_Dital_attribute[7].ss_Notch       =    1;
        gtt_Dital_attribute[7].ss_Init        =    0;
        gtt_Dital_attribute[7].uc_Point       =    0;

        gtt_Dital_attribute[8].ss_Min         =    0;      //P08	// ｼﾞｺｸ ﾋｮｳｼﾞ ｾｯﾃｲ
        gtt_Dital_attribute[8].ss_Max         =    2;
        gtt_Dital_attribute[8].ss_Notch       =    1;
        gtt_Dital_attribute[8].ss_Init        =    2;	// 時刻　2009.04.08日付に変更 1->0				2019.06.10 無しに変更	0->2
        gtt_Dital_attribute[8].uc_Point       =    0;

        gtt_Dital_attribute[9].ss_Min         =    0;      //P09	// ﾃﾞﾝﾘｭｳﾋｮｳｼﾞﾅｲﾖｳ
        gtt_Dital_attribute[9].ss_Max         =    1;
        gtt_Dital_attribute[9].ss_Notch       =    1;
        gtt_Dital_attribute[9].ss_Init        =    0;	   // 2010.02.18 初期値”１：実効値”に変更			// 2011.10.27	初期値”０：平均値”に変更
        gtt_Dital_attribute[9].uc_Point       =    0;

        gtt_Dital_attribute[10].ss_Min        =    0;      //P10	// ﾃﾞﾝﾎﾞｳ ｼｮﾘ
        gtt_Dital_attribute[10].ss_Max        =    1;
        gtt_Dital_attribute[10].ss_Notch      =    1;
        gtt_Dital_attribute[10].ss_Init       =    0;	// あり
        gtt_Dital_attribute[10].uc_Point      =    0;

        gtt_Dital_attribute[11].ss_Min        =    0;      //P11	// ｱｰｸﾄﾞﾗｲﾌﾞ ﾚﾍﾞﾙ	// BP4 Phase13 by @Tny 2009.02.24
        gtt_Dital_attribute[11].ss_Max        =   90;
        gtt_Dital_attribute[11].ss_Notch      =    1;
        gtt_Dital_attribute[11].ss_Init       =    0;	// ０％
        gtt_Dital_attribute[11].uc_Point      =    0;

        gtt_Dital_attribute[12].ss_Min        =    1;      //P12 2009.03.07 変更	// ｼﾞｮｳｹﾝﾒｲ ﾆｭｳﾘｮｸ
        gtt_Dital_attribute[12].ss_Max        =   50;      // 2009.06.11 16->50に変更
        gtt_Dital_attribute[12].ss_Notch      =    1;
        gtt_Dital_attribute[12].ss_Init       =    1;
        gtt_Dital_attribute[12].uc_Point      =    0;

        gtt_Dital_attribute[13].ss_Min        =    1;      //P13 2009.03.07 変更	// LCDｺﾝﾄﾗｽﾄ	BP4 Phase9 by @Tny 2009.02.16
        gtt_Dital_attribute[13].ss_Max        =   12;      //2009.03.21 15->12
        gtt_Dital_attribute[13].ss_Notch      =    1;
        gtt_Dital_attribute[13].ss_Init       =    1;      //2009.03.21 4->1
        gtt_Dital_attribute[13].uc_Point      =    0;

        gtt_Dital_attribute[14].ss_Min        =   10;      //P14 2009.03.07 変更
        gtt_Dital_attribute[14].ss_Max        =  400;
        gtt_Dital_attribute[14].ss_Notch      =   10;
        gtt_Dital_attribute[14].ss_Init       =  100;
        gtt_Dital_attribute[14].uc_Point      =    0;

        gtt_Dital_attribute[15].ss_Min        =   10;      //P15 2010.01.08 2010.01.29 0→10
        gtt_Dital_attribute[15].ss_Max        =   50;
        gtt_Dital_attribute[15].ss_Notch      =    1;
        gtt_Dital_attribute[15].ss_Init       =   50;    
        gtt_Dital_attribute[15].uc_Point      =    2;	// 2010.01.08 by @Tny

        gtt_Dital_attribute[16].ss_Min        =    0;      //P16
        gtt_Dital_attribute[16].ss_Max        =    1;      //2010.02.03 BPR4のみ選択するように変更		// 0->1 300BP4仕様に変更（BPR1の選択が可能）
        gtt_Dital_attribute[16].ss_Notch      =    1;
        gtt_Dital_attribute[16].ss_Init       =    0;
        gtt_Dital_attribute[16].uc_Point      =    0;

        gtt_Dital_attribute[17].ss_Min        =    0;      //P17
        gtt_Dital_attribute[17].ss_Max        =    1;
        gtt_Dital_attribute[17].ss_Notch      =    1;
        gtt_Dital_attribute[17].ss_Init       =    0;
        gtt_Dital_attribute[17].uc_Point      =    0;

        gtt_Dital_attribute[18].ss_Min        =   50;      //P18	出力制限機能 2010.01.08 @Tny
//      gtt_Dital_attribute[18].ss_Max        =  300;      // 2011.09.30 500->300
        gtt_Dital_attribute[18].ss_Max        =  400;      // 2011.09.30 500->300->400		2019.08.21
        gtt_Dital_attribute[18].ss_Notch      =   10;
//      gtt_Dital_attribute[18].ss_Init       =  300;      // 2011.09.30 500->300
        gtt_Dital_attribute[18].ss_Init       =  400;      // 2011.09.30 500->300->400		2019.08.21
        gtt_Dital_attribute[18].uc_Point      =    0;

        gtt_Dital_attribute[19].ss_Min        =    0;      //P19	マイルドパルス設定 2010.01.20 by @Tny
        gtt_Dital_attribute[19].ss_Max        =    3;
        gtt_Dital_attribute[19].ss_Notch      =    1;
        gtt_Dital_attribute[19].ss_Init       =    0;
        gtt_Dital_attribute[19].uc_Point      =    0;

        gtt_Dital_attribute[20].ss_Min        =    0;      //P20	交流周波数制限表示設定 2010.01.20 by @Tny
        gtt_Dital_attribute[20].ss_Max        =    0;      //2011.10.01  1->0
        gtt_Dital_attribute[20].ss_Notch      =    1;
        gtt_Dital_attribute[20].ss_Init       =    0;
        gtt_Dital_attribute[20].uc_Point      =    0;

        gtt_Dital_attribute[21].ss_Min        =   -5;      //P21 2010.02.26 アークアシスト
        gtt_Dital_attribute[21].ss_Max        =    5;      //    2010.02.26
        gtt_Dital_attribute[21].ss_Notch      =    1;      //    2010.02.26
        gtt_Dital_attribute[21].ss_Init       =    0;      //    2010.02.26
        gtt_Dital_attribute[21].uc_Point      =    0;

#if true
        gtt_Dital_attribute[22].ss_Min        =    0;      //P22 2011.10.03 パルス詳細表示SW	「ソフトスタート時間」削除に伴う変更 2011.10.31
        gtt_Dital_attribute[22].ss_Max        =    1;
        gtt_Dital_attribute[22].ss_Notch      =    1;
        gtt_Dital_attribute[22].ss_Init       =    0;	   //P23 2011.10.03 1→0
        gtt_Dital_attribute[22].uc_Point      =    0;

        gtt_Dital_attribute[23].ss_Min        =    0;      //P23 IIF							「ソフトスタート時間」削除に伴う変更 2011.10.31
        gtt_Dital_attribute[23].ss_Max        =    1;
        gtt_Dital_attribute[23].ss_Notch      =    1;
        gtt_Dital_attribute[23].ss_Init       =    0;
        gtt_Dital_attribute[23].uc_Point      =    0;
#else
        gtt_Dital_attribute[22].ss_Min        =    0;      //P22 ソフトスタート 2011.10.01	「ソフトスタート時間」削除 2011.10.31
        gtt_Dital_attribute[22].ss_Max        =   20;
        gtt_Dital_attribute[22].ss_Notch      =    1;
        gtt_Dital_attribute[22].ss_Init       =    0;
        gtt_Dital_attribute[22].uc_Point      =    2;

        gtt_Dital_attribute[23].ss_Min        =    0;      //P23 2011.10.03 パルス詳細表示SW　　2009.02.13エキスパートモード実験用
        gtt_Dital_attribute[23].ss_Max        =    1;
        gtt_Dital_attribute[23].ss_Notch      =    1;
        gtt_Dital_attribute[23].ss_Init       =    0;	   //P23 2011.10.03 1→0
        gtt_Dital_attribute[23].uc_Point      =    0;
#endif
#if true	// <IIF NEW>	2011.10.07 by @Tny
        gtt_Dital_attribute[24].ss_Min        =    0;      //P24
        gtt_Dital_attribute[24].ss_Max        =    1;
        gtt_Dital_attribute[24].ss_Notch      =    1;
        gtt_Dital_attribute[24].ss_Init       =    0;
        gtt_Dital_attribute[24].uc_Point      =    0;
	#if 1	// 2019.08.21
        gtt_Dital_attribute[25].ss_Min        =  -99;      //P25 P GAIN
        gtt_Dital_attribute[25].ss_Max        =   99;
        gtt_Dital_attribute[25].ss_Notch      =    1;
        gtt_Dital_attribute[25].ss_Init       =    0;
        gtt_Dital_attribute[25].uc_Point      =    0;

        gtt_Dital_attribute[26].ss_Min        =  -99;      //P26 I GAIN
        gtt_Dital_attribute[26].ss_Max        =   99;
        gtt_Dital_attribute[26].ss_Notch      =    1;
        gtt_Dital_attribute[26].ss_Init       =    0;
        gtt_Dital_attribute[26].uc_Point      =    0;
	#else
        gtt_Dital_attribute[25].ss_Min        =  -10;      //P25 2009.02.13エキスパートモード実験用
        gtt_Dital_attribute[25].ss_Max        =  400;
        gtt_Dital_attribute[25].ss_Notch      =   10;
        gtt_Dital_attribute[25].ss_Init       =  100;
        gtt_Dital_attribute[25].uc_Point      =    0;

        gtt_Dital_attribute[26].ss_Min        =    1;      //P26 2009.02.13エキスパートモード実験用
        gtt_Dital_attribute[26].ss_Max        =  200;
        gtt_Dital_attribute[26].ss_Notch      =    1;
        gtt_Dital_attribute[26].ss_Init       =    1;
        gtt_Dital_attribute[26].uc_Point      =    0;
	#endif
        gtt_Dital_attribute[27].ss_Min        =    0;      //P27
        gtt_Dital_attribute[27].ss_Max        =    1;
        gtt_Dital_attribute[27].ss_Notch      =    1;
        gtt_Dital_attribute[27].ss_Init       =    0;
        gtt_Dital_attribute[27].uc_Point      =    0;

        gtt_Dital_attribute[28].ss_Min        =    0;      //P28
        gtt_Dital_attribute[28].ss_Max        =    1;
        gtt_Dital_attribute[28].ss_Notch      =    1;
        gtt_Dital_attribute[28].ss_Init       =    0;
        gtt_Dital_attribute[28].uc_Point      =    0;

        gtt_Dital_attribute[29].ss_Min        =    0;      //P29
        gtt_Dital_attribute[29].ss_Max        =    1;
        gtt_Dital_attribute[29].ss_Notch      =    1;
        gtt_Dital_attribute[29].ss_Init       =    0;
        gtt_Dital_attribute[29].uc_Point      =    0;

        gtt_Dital_attribute[30].ss_Min        =    0;      //P30
        gtt_Dital_attribute[30].ss_Max        =    1;
        gtt_Dital_attribute[30].ss_Notch      =    1;
        gtt_Dital_attribute[30].ss_Init       =    0;
        gtt_Dital_attribute[30].uc_Point      =    0;
#else
        gtt_Dital_attribute[24].ss_Min        =   10;      //P24 2009.02.13エキスパートモード実験用
        gtt_Dital_attribute[24].ss_Max        =  400;
        gtt_Dital_attribute[24].ss_Notch      =   10;
        gtt_Dital_attribute[24].ss_Init       =  100;
        gtt_Dital_attribute[24].uc_Point      =    0;

        gtt_Dital_attribute[25].ss_Min        =    1;      //P25 2009.02.13エキスパートモード実験用
        gtt_Dital_attribute[25].ss_Max        =  200;
        gtt_Dital_attribute[25].ss_Notch      =    1;
        gtt_Dital_attribute[25].ss_Init       =    1;
        gtt_Dital_attribute[25].uc_Point      =    0;

        gtt_Dital_attribute[26].ss_Min        =    0;      //P26
        gtt_Dital_attribute[26].ss_Max        =    1;
        gtt_Dital_attribute[26].ss_Notch      =    1;
        gtt_Dital_attribute[26].ss_Init       =    0;
        gtt_Dital_attribute[26].uc_Point      =    0;

        gtt_Dital_attribute[27].ss_Min        =    0;      //P27
        gtt_Dital_attribute[27].ss_Max        =    1;
        gtt_Dital_attribute[27].ss_Notch      =    1;
        gtt_Dital_attribute[27].ss_Init       =    0;
        gtt_Dital_attribute[27].uc_Point      =    0;

        gtt_Dital_attribute[28].ss_Min        =    0;      //P28
        gtt_Dital_attribute[28].ss_Max        =    1;
        gtt_Dital_attribute[28].ss_Notch      =    1;
        gtt_Dital_attribute[28].ss_Init       =    0;
        gtt_Dital_attribute[28].uc_Point      =    0;

        gtt_Dital_attribute[29].ss_Min        =    0;      //P29
        gtt_Dital_attribute[29].ss_Max        =    1;
        gtt_Dital_attribute[29].ss_Notch      =    1;
        gtt_Dital_attribute[29].ss_Init       =    0;
        gtt_Dital_attribute[29].uc_Point      =    0;
#endif



//---------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23	BP4 Phase16 by @Tny 2003.03.10
        //<><><> 起動時　サービスマン・メニュー属性初期化 <><><>
		gtt_Service_attribute[ 0].ss_Min	=    0;      // S00
		gtt_Service_attribute[ 0].ss_Max	=    1;
		gtt_Service_attribute[ 0].ss_Notch	=    1;
		gtt_Service_attribute[ 0].ss_Init	=    0;
		gtt_Service_attribute[ 0].uc_Point	=    0;

		gtt_Service_attribute[ 1].ss_Min	= -200;      // S01	// DC TIG EN ﾎｯﾄI 2009.04.03 -99->-200
		gtt_Service_attribute[ 1].ss_Max	=  200;
		gtt_Service_attribute[ 1].ss_Notch	=    1;
		gtt_Service_attribute[ 1].ss_Init	=    0;
		gtt_Service_attribute[ 1].uc_Point	=    0;

		gtt_Service_attribute[ 2].ss_Min	=    0;      // S02	// DC TIG EN ﾎｯﾄT
		gtt_Service_attribute[ 2].ss_Max	=   50;
		gtt_Service_attribute[ 2].ss_Notch	=    1;
		gtt_Service_attribute[ 2].ss_Init	=   10;
		gtt_Service_attribute[ 2].uc_Point	=    0;

		gtt_Service_attribute[ 3].ss_Min	=    0;      // S03	// DC TIG EN ﾎｯﾄST
		gtt_Service_attribute[ 3].ss_Max	=   50;
		gtt_Service_attribute[ 3].ss_Notch	=    1;
		gtt_Service_attribute[ 3].ss_Init	=   10;
		gtt_Service_attribute[ 3].uc_Point	=    0;

		gtt_Service_attribute[ 4].ss_Min	= -200;      // S04	// DC TIG EP ﾎｯﾄI 2009.04.03
		gtt_Service_attribute[ 4].ss_Max	=  200;
		gtt_Service_attribute[ 4].ss_Notch	=    1;
		gtt_Service_attribute[ 4].ss_Init	=    0;
		gtt_Service_attribute[ 4].uc_Point	=    0;

		gtt_Service_attribute[ 5].ss_Min	=    0;      // S05	// DC TIG EP ﾎｯﾄT
		gtt_Service_attribute[ 5].ss_Max	=   50;
		gtt_Service_attribute[ 5].ss_Notch	=    1;
		gtt_Service_attribute[ 5].ss_Init	=   10;
		gtt_Service_attribute[ 5].uc_Point	=    0;

		gtt_Service_attribute[ 6].ss_Min	=    0;      // S06	// DC TIG EP ﾎｯﾄST
		gtt_Service_attribute[ 6].ss_Max	=   50;
		gtt_Service_attribute[ 6].ss_Notch	=    1;
		gtt_Service_attribute[ 6].ss_Init	=   10;
		gtt_Service_attribute[ 6].uc_Point	=    0;

		gtt_Service_attribute[ 7].ss_Min	= -200;      // S07	// AC(MIX) ﾎｯﾄI1 2009.04.03
		gtt_Service_attribute[ 7].ss_Max	=  200;
		gtt_Service_attribute[ 7].ss_Notch	=    1;
		gtt_Service_attribute[ 7].ss_Init	=    0;
		gtt_Service_attribute[ 7].uc_Point	=    0;

		gtt_Service_attribute[ 8].ss_Min	=    0;      // S08	// AC(MIX) ﾎｯﾄT1 2009.04.03
		gtt_Service_attribute[ 8].ss_Max	=   50;
		gtt_Service_attribute[ 8].ss_Notch	=    1;
		gtt_Service_attribute[ 8].ss_Init	=   40; //2009.04.13 10->40
		gtt_Service_attribute[ 8].uc_Point	=    0;

		gtt_Service_attribute[ 9].ss_Min	=    0;      // S09	// AC(MIX) ﾎｯﾄT2
		gtt_Service_attribute[ 9].ss_Max	=   50;
		gtt_Service_attribute[ 9].ss_Notch	=    1;
		gtt_Service_attribute[ 9].ss_Init	=   20; //2009.04.13 10->20
		gtt_Service_attribute[ 9].uc_Point	=    0;

		gtt_Service_attribute[10].ss_Min	=    0;      // S10	// AC(MIX) ﾎｯﾄST
		gtt_Service_attribute[10].ss_Max	=   50;
		gtt_Service_attribute[10].ss_Notch	=    1;
		gtt_Service_attribute[10].ss_Init	=    0; //2009.04.13 10->0
		gtt_Service_attribute[10].uc_Point	=    0;

		gtt_Service_attribute[11].ss_Min	=   50;      // S11	// ｻｲﾁｮｳｽﾎﾟｯﾄｼﾞｶﾝ 2009.03.16 50->100 2009.03.24 100->50
		gtt_Service_attribute[11].ss_Max	=  100;             //                2009.03.16 100->200 2009.03.24 200->100
		gtt_Service_attribute[11].ss_Notch	=    1;
		gtt_Service_attribute[11].ss_Init	=   50;             //2009.03.16 50-> 100 2009.03.24 100->50
		gtt_Service_attribute[11].uc_Point	=    2;

		gtt_Service_attribute[12].ss_Min	= -999;      // S12	// ｲﾁｼﾞﾃﾞﾝｱﾂｵﾌｾｯﾄ 2009.04.03 -99->-999
		gtt_Service_attribute[12].ss_Max	=  999;
		gtt_Service_attribute[12].ss_Notch	=    1;
		gtt_Service_attribute[12].ss_Init	=    0;
		gtt_Service_attribute[12].uc_Point	=    0;

		gtt_Service_attribute[13].ss_Min	=    0;      // S13	// ﾃﾞﾝﾘｭｳﾎｾｲ
		gtt_Service_attribute[13].ss_Max	=    1;
		gtt_Service_attribute[13].ss_Notch	=    1;
		gtt_Service_attribute[13].ss_Init	=    0;
		gtt_Service_attribute[13].uc_Point	=    0;

		gtt_Service_attribute[14].ss_Min	=  -15;      // S14	// CT ｵﾌｾｯﾄ 2009.04.03
		gtt_Service_attribute[14].ss_Max	=   16;
		gtt_Service_attribute[14].ss_Notch	=    1;
		gtt_Service_attribute[14].ss_Init	=    0;
		gtt_Service_attribute[14].uc_Point	=    0;

		gtt_Service_attribute[15].ss_Min	=  -10;      // S15	// VT ｵﾌｾｯﾄ
		gtt_Service_attribute[15].ss_Max	=   10;
		gtt_Service_attribute[15].ss_Notch	=    1;
		gtt_Service_attribute[15].ss_Init	=    0;
		gtt_Service_attribute[15].uc_Point	=    0;

		gtt_Service_attribute[16].ss_Min	=    0;      // S16	// ﾃﾞﾝｷｮｸﾀﾝﾗｸﾚﾍﾞﾙ
		gtt_Service_attribute[16].ss_Max	=  150;
		gtt_Service_attribute[16].ss_Notch	=    1;
		gtt_Service_attribute[16].ss_Init	=   50;
		gtt_Service_attribute[16].uc_Point	=    0;

		gtt_Service_attribute[17].ss_Min	=   -5;      // S17	// ﾋｮｳｼﾞﾎｾｲ
		gtt_Service_attribute[17].ss_Max	=    5;
		gtt_Service_attribute[17].ss_Notch	=    1;
		gtt_Service_attribute[17].ss_Init	=    0;
		gtt_Service_attribute[17].uc_Point	=    0;

		gtt_Service_attribute[18].ss_Min	= -100;      // S18 //ｼｭﾂﾘｮｸﾁｮｳｾｲｹﾞｲﾝ 2009.04.03 //2009.04.14 -110→-100
		gtt_Service_attribute[18].ss_Max	=  100;      //2009.04.14  146→+100
		gtt_Service_attribute[18].ss_Notch	=    1;
		gtt_Service_attribute[18].ss_Init	=    0;
		gtt_Service_attribute[18].uc_Point	=    0;

		gtt_Service_attribute[19].ss_Min	=    0;      // S19
		gtt_Service_attribute[19].ss_Max	=    1;
		gtt_Service_attribute[19].ss_Notch	=    1;
		gtt_Service_attribute[19].ss_Init	=    0;
		gtt_Service_attribute[19].uc_Point	=    0;

		gtt_Service_attribute[20].ss_Min	=    0;      // S20
		gtt_Service_attribute[20].ss_Max	=    1;
		gtt_Service_attribute[20].ss_Notch	=    1;
		gtt_Service_attribute[20].ss_Init	=    1;		// 初期値：1(YES)
		gtt_Service_attribute[20].uc_Point	=    0;

		gtt_Service_attribute[21].ss_Min	=    0;      // S21
		gtt_Service_attribute[21].ss_Max	=    1;
		gtt_Service_attribute[21].ss_Notch	=    1;
		gtt_Service_attribute[21].ss_Init	=    0;
		gtt_Service_attribute[21].uc_Point	=    0;

		gtt_Service_attribute[22].ss_Min	=    0;      // S22
		gtt_Service_attribute[22].ss_Max	=    1;
		gtt_Service_attribute[22].ss_Notch	=    1;
		gtt_Service_attribute[22].ss_Init	=    0;
		gtt_Service_attribute[22].uc_Point	=    0;

		gtt_Service_attribute[23].ss_Min	=    0;      // S23
		gtt_Service_attribute[23].ss_Max	=    1;
		gtt_Service_attribute[23].ss_Notch	=    1;
		gtt_Service_attribute[23].ss_Init	=    0;
		gtt_Service_attribute[23].uc_Point	=    0;

		gtt_Service_attribute[24].ss_Min	=    0;      // S24
		gtt_Service_attribute[24].ss_Max	=    1;
		gtt_Service_attribute[24].ss_Notch	=    1;
		gtt_Service_attribute[24].ss_Init	=    0;
		gtt_Service_attribute[24].uc_Point	=    0;

		gtt_Service_attribute[25].ss_Min	=    0;      // S25
		gtt_Service_attribute[25].ss_Max	=    1;
		gtt_Service_attribute[25].ss_Notch	=    1;
		gtt_Service_attribute[25].ss_Init	=    0;
		gtt_Service_attribute[25].uc_Point	=    0;

		gtt_Service_attribute[26].ss_Min	=    0;      // S26
		gtt_Service_attribute[26].ss_Max	=    1;
		gtt_Service_attribute[26].ss_Notch	=    1;
		gtt_Service_attribute[26].ss_Init	=    0;
		gtt_Service_attribute[26].uc_Point	=    0;

		gtt_Service_attribute[27].ss_Min	=    0;      // S27
		gtt_Service_attribute[27].ss_Max	=    1;
		gtt_Service_attribute[27].ss_Notch	=    1;
		gtt_Service_attribute[27].ss_Init	=    0;
		gtt_Service_attribute[27].uc_Point	=    0;

		gtt_Service_attribute[28].ss_Min	=    0;      // S28
		gtt_Service_attribute[28].ss_Max	=    1;
		gtt_Service_attribute[28].ss_Notch	=    1;
		gtt_Service_attribute[28].ss_Init	=    0;
		gtt_Service_attribute[28].uc_Point	=    0;

		gtt_Service_attribute[29].ss_Min	=    0;      // S29
		gtt_Service_attribute[29].ss_Max	=    1;
		gtt_Service_attribute[29].ss_Notch	=    1;
		gtt_Service_attribute[29].ss_Init	=    0;
		gtt_Service_attribute[29].uc_Point	=    0;

//---------------------------------------------------
//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
        //<><><> 起動時　レスキュー・メニュー属性初期化 <><><>
		gtt_Rescue_attribute[ 0].ss_Min		= 0;      // R00
		gtt_Rescue_attribute[ 0].ss_Max		= 1;
		gtt_Rescue_attribute[ 0].ss_Notch	= 1;
		gtt_Rescue_attribute[ 0].ss_Init	= 0;
		gtt_Rescue_attribute[ 0].uc_Point	= 0;

		gtt_Rescue_attribute[ 1].ss_Min		= 0;      // R01	// ｴﾗｰﾘﾚｷ ﾉ ｲﾁﾗﾝ
		gtt_Rescue_attribute[ 1].ss_Max		= 1;
		gtt_Rescue_attribute[ 1].ss_Notch	= 1;
		gtt_Rescue_attribute[ 1].ss_Init	= 0;
		gtt_Rescue_attribute[ 1].uc_Point	= 0;

		gtt_Rescue_attribute[ 2].ss_Min		= 0;      // R02	// ｴﾗｰﾘﾚｷ ﾉ ｸﾘｱ // 2010.01.25 CHﾛｯｸ
		gtt_Rescue_attribute[ 2].ss_Max		= 1;
		gtt_Rescue_attribute[ 2].ss_Notch	= 1;
		gtt_Rescue_attribute[ 2].ss_Init	= 0;
		gtt_Rescue_attribute[ 2].uc_Point	= 0;

		gtt_Rescue_attribute[ 3].ss_Min		= 0;      // R03	// ﾒﾓﾘ ﾉ ｵｰﾙｸﾘｱ
		gtt_Rescue_attribute[ 3].ss_Max		= 1;
		gtt_Rescue_attribute[ 3].ss_Notch	= 1;
		gtt_Rescue_attribute[ 3].ss_Init	= 0;
		gtt_Rescue_attribute[ 3].uc_Point	= 0;

		gtt_Rescue_attribute[ 4].ss_Min		= 0;      // R04	// EXT SW 2010.01.20 by @Tny
		gtt_Rescue_attribute[ 4].ss_Max		= 1;
		gtt_Rescue_attribute[ 4].ss_Notch	= 1;
		gtt_Rescue_attribute[ 4].ss_Init	= 0;
		gtt_Rescue_attribute[ 4].uc_Point	= 0;

		gtt_Rescue_attribute[ 5].ss_Min		= 0;      // R05	//ｱｰｸｷﾚﾎﾞｳｼｱｼｽﾄ 2010.02.24
		gtt_Rescue_attribute[ 5].ss_Max		= 1;
		gtt_Rescue_attribute[ 5].ss_Notch	= 1;
		gtt_Rescue_attribute[ 5].ss_Init	= 1;
		gtt_Rescue_attribute[ 5].uc_Point	= 0;

		gtt_Rescue_attribute[ 6].ss_Min		= 0;      // R05	//	「交流波形出力モード」追加		2011.11.08
		gtt_Rescue_attribute[ 6].ss_Max		= 1;
		gtt_Rescue_attribute[ 6].ss_Notch	= 1;
		gtt_Rescue_attribute[ 6].ss_Init	= 1;
		gtt_Rescue_attribute[ 6].uc_Point	= 0;

//---------------------------------------------------


        //***** 温度異常発生時、再起動時に時間を読み込む 2009.03.13*****
        if (gus_Temp_err_set == ON)
        {
            gsc_Temp_err_year_work   = gsc_Temp_err_year;
            gsc_Temp_err_month_work  = gsc_Temp_err_month;
            gsc_Temp_err_day_work    = gsc_Temp_err_day;
            gsc_Temp_err_hour_work   = gsc_Temp_err_hour;
            gsc_Temp_err_mini_work   = gsc_Temp_err_mini;
            gus_Temp_err_set_work    = gus_Temp_err_set;
        } else {
            gus_Temp_err_set_work    = OFF;
        }
        //**************************************************************



    //<><><><><><><><><><> 各パラメータの範囲チェック <><><><><><><><><><>
        if (gs_Okcv_adjust_data >= 100 || gs_Okcv_adjust_data <= -100)
        {
		    gs_Okcv_adjust_data = 0;
	    }
        if (gs_Okcv_adjust_init_data >= 100 || gs_Okcv_adjust_init_data <= -100)
        {
		    gs_Okcv_adjust_init_data = 0;
	    }
        if (gs_Okcv_adjust_crat_data >= 100 || gs_Okcv_adjust_crat_data <= -100)
        {
		    gs_Okcv_adjust_crat_data = 0;
	    }
        if (gs_Okcv_adjust_wave_data >= 100 || gs_Okcv_adjust_wave_data <= -100)
        {
		    gs_Okcv_adjust_wave_data = 0;
	    }
        if (gs_Okcv_adjust_start_data >= 100 || gs_Okcv_adjust_start_data <= -100) //2008.08.05
        {
		    gs_Okcv_adjust_start_data = 0;
	    }
        //初期電流
        if (gus_Init_current <= MAX_CURRENT && gus_Init_current >= MIN_CURRENT) //2009.02.19
        {
            gtt_Internal_pack.Data.In.usWeldingInitCurr     = gus_Init_current;
        } else {
            gtt_Internal_pack.Data.In.usWeldingInitCurr     = 50;
        }
        //本電流
        if (gus_Weld_current <= MAX_CURRENT && gus_Weld_current >= MIN_CURRENT) //2009.02.19
        {
            gtt_Internal_pack.Data.In.usWeldingCurr     = gus_Weld_current;
        } else {
            gtt_Internal_pack.Data.In.usWeldingCurr     = 50;
        }
        //クレータ電流
        if (gus_Crat_current <= MAX_CURRENT && gus_Crat_current >= MIN_CURRENT) //2009.02.19
        {
            gtt_Internal_pack.Data.In.usWeldingCratCurr     = gus_Crat_current;
        } else {
            gtt_Internal_pack.Data.In.usWeldingCratCurr     = 50;
        }
        //パルス電流 2009.02.03
        if (gus_Pulse_current <= MAX_CURRENT && gus_Pulse_current >= MIN_CURRENT)
        {
            gtt_Internal_pack.Data.In.usIP = gus_Pulse_current;
        } else {
            gtt_Internal_pack.Data.In.usIP = 50;
        }
        //**** 制限電流セット 2009.02.19 *****************************************
        if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
        {
            gss_Max_current = MAX_CURRENT;
            gss_Min_current = MIN_CURRENT;
        }
        if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
        {
            gss_Max_current = MAX_CURRENT;
            gss_Min_current = MIN_CURRENT_AC; //2011.09.30
            //***** 2009.03.13 *****
       		if (guc_Ac_wave_counter == 1) //ハードＡＣ
            {
                gss_Max_current = MAX_CURRENT;
                gss_Min_current = MIN_CURRENT_AC_HARD; //2011.09.30
            }
       		if (guc_Ac_wave_counter == 2) //ソフトＡＣ
            {
                gss_Max_current = MAX_CURRENT_AC_SOFT;
                gss_Min_current = MIN_CURRENT_AC; //
            }
            //**********************
        }
        if (guc_Method_condition_data == STD_MIX_METHOD) //2009.03.17
        {
            gss_Max_current = MAX_CURRENT;
            gss_Min_current = MIN_CURRENT_AC;
        }
        if (guc_Method_condition_data == STD_HAND_METHOD) //2009.03.06
        {
            gss_Max_current = MAX_CURRENT_HAND;
            gss_Min_current = MIN_CURRENT_HAND;
        }
        
        //初期
  	    if (gtt_Internal_pack.Data.In.usWeldingInitCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
   	    {
            gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
       	}
       	if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
        {
      		gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
      	}
        //本溶接
        if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
        {
      		gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
      	}
      	if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
        {
      		gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
      	}
        //クレータ
        if (gtt_Internal_pack.Data.In.usWeldingCratCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
        {
      		gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
      	}
      	if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
        {
      		gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
      	}
        //パルス電流
        if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
        {
            gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        }
        if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
        {
            gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        }
        //************************************************************************

        //プリフロー時間 2009.01.22
        if (gus_Pre_flow_time <= 300 && gus_Pre_flow_time >= 0) //2009.03.18 100->300
        {
            gtt_Internal_pack.Data.In.sPreFlowTime = gus_Pre_flow_time;
        } else {
            gtt_Internal_pack.Data.In.sPreFlowTime = 3;
        }
        //アフターフロー時間 2009.01.22
        if (gus_After_flow_time <= 300 && gus_After_flow_time >= 0)
        {
            gtt_Internal_pack.Data.In.sAfterFlowTime = gus_After_flow_time;
        } else {
            gtt_Internal_pack.Data.In.sAfterFlowTime = 50;
        }
        //アップスロープ時間 2009.02.02
        if (gus_Up_slop_time <= 100 && gus_Up_slop_time >= 0)
        {
            gtt_Internal_pack.Data.In.sUpSlopTime = gus_Up_slop_time;
        } else {
            gtt_Internal_pack.Data.In.sUpSlopTime = 2;
        }
        //ダウンスロープ時間 2009.02.02
        if (gus_Down_slop_time <= 100 && gus_Down_slop_time >= 0)
        {
            gtt_Internal_pack.Data.In.sDownSlopTime = gus_Down_slop_time;
        } else {
            gtt_Internal_pack.Data.In.sDownSlopTime = 2;
        }
        //パルス周波数 2009.02.03
        if (gus_Pulse_freq <= 5000 && gus_Pulse_freq >= 1)
        {
            gtt_Internal_pack.Data.In.usPulseFreq = gus_Pulse_freq;
        } else {
            gtt_Internal_pack.Data.In.usPulseFreq = 100;
        }
        //パルスデューティ 2009.02.03
        if (gus_Pulse_duty <= 95 && gus_Pulse_duty >= 5)
        {
            gtt_Internal_pack.Data.In.usPulseDuty = gus_Pulse_duty;
        } else {
            gtt_Internal_pack.Data.In.usPulseDuty = 50;
        }

        //交流周波数 2009.02.06
        if (gus_Ac_frequency <= 400 && gus_Ac_frequency >= 10)
        {
            gtt_Internal_pack.Data.In.usAcFreq    = gus_Ac_frequency;
        } else {
            gtt_Internal_pack.Data.In.usAcFreq    = 70;
        }
        
        //クリーニング幅 2009.02.06
        if (gus_Cleaning_duty <= 50 && gus_Cleaning_duty >= 10)
        {
            gtt_Internal_pack.Data.In.ucCleaningDuty  = gus_Cleaning_duty;
        } else {
            gtt_Internal_pack.Data.In.ucCleaningDuty  = 30;
        }
        
        //直流比率 2009.02.06
        if (gus_Mix_ac_ratio <= 90 && gus_Mix_ac_ratio >= 10)
        {
            gtt_Internal_pack.Data.In.ucMixAcRatio    = gus_Mix_ac_ratio;
        } else {
            gtt_Internal_pack.Data.In.ucMixAcRatio    = 30;
        }
        
        //ＭＩＸ周波数 2009.02.06
        //if (gus_Mix_frequency <= 100 && gus_Mix_frequency >= 1) //2009.03.17
        if (gus_Mix_frequency <= 200 && gus_Mix_frequency >= 1) //2009.07.31
        {
            gtt_Internal_pack.Data.In.ucMixFreq       = gus_Mix_frequency;
        } else {
            gtt_Internal_pack.Data.In.ucMixFreq       = 10;
        }
        



        //波形
#if 0  //2008.10.10 del
        if (gus_Wave_current <= 350 && gus_Wave_current >= 15) //2007.12.09 2008.03.04 2008.03.24変更
        {
            gtt_Internal_pack.Data.In.usWeldingWaveCurr     = gus_Wave_current;
        } else {
            gtt_Internal_pack.Data.In.usWeldingWaveCurr     = 120;
        }
#endif
        //スタート
#if 0  //2008.10.10 del
        if (gus_Start_current <= 350 && gus_Start_current >= 15) //2008.08.05
        {
            gtt_Internal_pack.Data.In.usWeldingStartCurr     = gus_Start_current;
        } else {
            gtt_Internal_pack.Data.In.usWeldingStartCurr     = 120;
        }
#endif
            
        if (gus_Weld_voltage < 450 && gus_Weld_voltage > 60) //2007.12.09
        {
            gtt_Internal_pack.Data.In.usWeldingVolt     = gus_Weld_voltage;
            gtt_Internal_pack.Data.In.usWeldingInitVolt = gus_Init_voltage; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingCratVolt = gus_Crat_voltage; //2008.02.26
            //gtt_Internal_pack.Data.In.usWeldingWaveVolt = gus_Wave_voltage; //2008.02.26 2008.10.10del
            //gtt_Internal_pack.Data.In.usWeldingStartVolt= gus_Start_voltage;//2008.08.05 2008.10.10del
        } else {
            gtt_Internal_pack.Data.In.usWeldingVolt     = 184;
            gtt_Internal_pack.Data.In.usWeldingInitVolt = 184; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingCratVolt = 184; //2008.02.26
            //gtt_Internal_pack.Data.In.usWeldingWaveVolt = 184; //2008.02.26 2008.10.10del
            //gtt_Internal_pack.Data.In.usWeldingStartVolt= 184; //2008.08.05 2008.10.10del
        }

    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
		if(bInitialProc){	// 初期値の設定
			unsigned short	i;
//---------------------------------------------------
// BP4 Phase15 by @Tny 2009.02.25
#if false
			//初期電流
			gtt_Internal_pack.Data.In.usWeldingInitCurr		= gus_Init_current				= 30;	// 30A
			//本電流
			gtt_Internal_pack.Data.In.usWeldingCurr			= gus_Weld_current				= 50;	// 50A
			//クレータ電流
			gtt_Internal_pack.Data.In.usWeldingCratCurr     = gus_Crat_current				= 20;	// 20A
			//プリフロー時間
			gtt_Internal_pack.Data.In.sPreFlowTime			= gus_Pre_flow_time				= 3;	// 0.3sec
			//アフターフロー時間
			gtt_Internal_pack.Data.In.sAfterFlowTime		= gus_After_flow_time			= 50;	// 5.0sec
			//アップスロープ時間
			gtt_Internal_pack.Data.In.sUpSlopTime			= gus_Up_slop_time				= 2;	// 0.2sec
			//ダウンスロープ時間
			gtt_Internal_pack.Data.In.sDownSlopTime			= gus_Down_slop_time			= 2;	// 0.2sec
			//パルス電流
			gtt_Internal_pack.Data.In.usIP					= gus_Pulse_current				= 100;	// 100A
			//パルス周波数
			gtt_Internal_pack.Data.In.usPulseFreq			= gus_Pulse_freq				= 100;	// 10.0Hz
			//パルスデューティ
			gtt_Internal_pack.Data.In.usPulseDuty			= gus_Pulse_duty				= 50;	// 50%
			//交流周波数
			gtt_Internal_pack.Data.In.usAcFreq				= gus_Ac_frequency				= 70;	// 70Hz
			//クリーニング幅
			gtt_Internal_pack.Data.In.ucCleaningDuty		= gus_Cleaning_duty				= 30;	// 30%
			//直流比率
			gtt_Internal_pack.Data.In.ucMixAcRatio			= gus_Mix_ac_ratio				= 30;	// 30%
			//ＭＩＸ周波数
            gtt_Internal_pack.Data.In.ucMixFreq				= gus_Mix_frequency				= 10;	// 1.0Hz
			//溶接法の選択
			guc_Method_condition_data						= guc_Method_condition_counter	= 0;	// 直流ＴＩＧ
			//クレータの選択
			guc_Crater_mode_counter							= 0;									// クレータ無し
			//パルスの選択
			guc_Pulse_mode_data								= guc_Pulse_mode_counter		= 0;	// パルス無し
			//交流波形の選択
			guc_Ac_wave_counter								= 0;									// 標準
			// その他のフラグ系
			gus_Sequence_set_data							= NO_SET_DATA;
			guc_Pulse_item_counter							= 1;
			guc_Ac_tig_set_counter							= 1;
			guc_Mix_tig_set_counter							= 1;
			guc_Select_counter								= MODE_WELDING;
#endif
//---------------------------------------------------
			// 詳細データ
			for(i=0;i<SELECT_DITAL_MAX;i++){
				gss_Select_dital[i] = gtt_Dital_attribute[i].ss_Init;
			}
			// サービスマン・メニュー・データ
			for(i=0;i<SERVICE_DATA_NO;i++){
				gtt_Special_menu.ss_Service_data[i] = gtt_Service_attribute[i].ss_Init;
			}
			// レスキュー・メニュー・データ
			for(i=0;i<RESCUE_DATA_NO;i++){
				    gtt_Special_menu.ss_Rescue_data[i] = gtt_Rescue_attribute[i].ss_Init; //2010.01.25

#if 0 //2010.01.25
                if (i != 2) //2009.04.06
                {
				    gtt_Special_menu.ss_Rescue_data[i] = gtt_Rescue_attribute[i].ss_Init;
                }
#endif
			}
		}
//---------------------------------------------------





        gtt_Table_key.Change_flag = ON; //2009.02.23 起動時テーブルをアクセスさせるための措置






        //各種設定バックアップ分チェックと初期化　2008.02.26
        gtt_Parameter.Select_counter = 1;
        guc_Select_current_sel_counter = 1;
        //gtt_Parameter.Item.Parameter_set_flag = OFF;
        //gtt_Parameter.Item.Voltage_display_flag = OFF;
        //gtt_Parameter.Item.Wave_control_flag = OFF;
        //<><>新設波形パラメータ 2008.03.07<><><><><>

        gtt_Internal_pack.Data.In.vSldnAdj      = (short)((short)gss_Select_dital[0] * WIRSLDN);// ワイヤスローダウン調整 2008.08.27変更
#if 0
        gsf_Acc1 = (float)gtt_Parameter.Item.Parameter_set[7]; //d07(70)
        gss_Acc1 = (short)(gsf_Acc1 * 10.0);
        gsf_Acc2 = (float)gtt_Parameter.Item.Parameter_set[8]; //d08(71)
        gss_Acc2 = (short)(gsf_Acc2 * 10.0);
        gsf_Acc3 = (float)gtt_Parameter.Item.Parameter_set[9]; //d09(72)
        gss_Acc3 = (short)(gsf_Acc3 * 10.0);
        gsf_Acc4 = (float)gtt_Parameter.Item.Parameter_set[10]; //d10(73)
        gss_Acc4 = (short)(gsf_Acc4 * 10.0);
        gsf_Acc5 = (float)gtt_Parameter.Item.Parameter_set[11]; //d11(74)
        gss_Acc5 = (short)(gsf_Acc5 * 10.0);
        gsf_Delay = (float)gtt_Parameter.Item.Parameter_set[12]; //d12(75)
        gss_Delay = (short)gsf_Delay;
#endif



        gtt_Ctrl_counter.uc_Out_function_no = 0; //2008.08.23
        gtt_Ctrl_counter.uc_Out_port_no     = 1; //2008.08.23 １始まりのため

        gtt_Ctrl_counter.uc_In_function_no = 0; //2008.08.24
        gtt_Ctrl_counter.uc_In_port_no     = 1; //2008.08.24 １始まりのため

        gtt_Ctrl_counter.uc_Analog_function_no = 0; //2008.08.24
        gtt_Ctrl_counter.uc_Analog_port_no     = 1; //2008.08.24 １始まりのため

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
        gtt_Ctrl_flag.Iif_first_rcv         = OFF; //
        gtt_Ctrl_flag.Iif_enable            = true; //
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

        ch_rec_class(0); //ｃｈ０へ書き込み 2008.08.21




//****** ｃｈ読み込みのため削除 *****
#if 0 
        //初期化（プログラム書き込み後初めて起動した時やバックアップ内容を忘れた場合）2008.02.26
        if (guc_Initial_load_data != 0x55)
        {
            guc_Wire_condition_datab      = 0x01;      // ワイヤ径
            guc_Method_condition_datab    = 0x01;      // 溶接法
            guc_Material_condition_datab  = 0x01;      // ワイヤ材質
            gs_Okcv_adjust_data_bkup      = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_init_data_bkup = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_crat_data_bkup = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_wave_data_bkup = 0x00;      //一元電圧微調整分の書き戻し
            gs_Okcv_adjust_start_data_bkup = 0x00;      //一元電圧微調整分の書き戻し 2008.08.05
 
            guc_Material_condition_counterb = 0x01;
            guc_Wire_condition_counterb     = 0x01;
            guc_Method_condition_counterb   = 0x01;
            guc_Pulse_mode_counterb         = 0x01; //2008.02.08
            
            guc_Pulse_mode_datab            = 0x03; //2008.02.08 
            guc_Pulse_type_datab            = 0x00; //2008.02.08
            
           
            
        }
            //<><><>2008.4.1　起動時０クリア<><><>
            gtt_Parameter.Item.Parameter_set[0] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[1] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[2] = 100; //2008.03.07
            gtt_Parameter.Item.Parameter_set[3] = 50; //2008.03.07
            gtt_Parameter.Item.Parameter_set[4] = 500; //2008.03.07
            gtt_Parameter.Item.Parameter_set[5] = 100; //2008.03.07
            gtt_Parameter.Item.Parameter_set[6] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[7] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[8] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[9] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[10] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[11] = 0; //2008.03.07
            gtt_Parameter.Item.Parameter_set[12] = 0; //2008.03.07
            
            guc_Okcv_select_flag = true;  //一元デフォルト
            //<><><><><><><><><><><><><><><><><><>

      
        guc_Initial_load_data = 0x55;



        //2007.12.07
        guc_Wire_condition_data     =  guc_Wire_condition_datab;      // ワイヤ径
        guc_Method_condition_data   =  guc_Method_condition_datab;           // 溶接法
        guc_Material_condition_data =  guc_Material_condition_datab;      // ワイヤ材質
        
        //<><><> 2008.04.02 <><><><>
        if (gs_Okcv_adjust_data_bkup >= 100 || gs_Okcv_adjust_data_bkup <= -100)
        {
		gs_Okcv_adjust_data_bkup = 0;
	}
        if (gs_Okcv_adjust_init_data_bkup >= 100 || gs_Okcv_adjust_init_data_bkup <= -100)
        {
		gs_Okcv_adjust_init_data_bkup = 0;
	}
        if (gs_Okcv_adjust_crat_data_bkup >= 100 || gs_Okcv_adjust_crat_data_bkup <= -100)
        {
		gs_Okcv_adjust_crat_data_bkup = 0;
	}
        if (gs_Okcv_adjust_wave_data_bkup >= 100 || gs_Okcv_adjust_wave_data_bkup <= -100)
        {
		gs_Okcv_adjust_wave_data_bkup = 0;
	}
        if (gs_Okcv_adjust_start_data_bkup >= 100 || gs_Okcv_adjust_start_data_bkup <= -100) //2008.08.05
        {
		gs_Okcv_adjust_start_data_bkup = 0;
	}
	//<><><><><><><><><><><><><>
	
        gs_Okcv_adjust_data         =  gs_Okcv_adjust_data_bkup;       //一元電圧微調整分の書き戻し2007.12.09
        gs_Okcv_adjust_init_data    =  gs_Okcv_adjust_init_data_bkup;  //一元電圧微調整分の書き戻し2008.02.26
        gs_Okcv_adjust_crat_data    =  gs_Okcv_adjust_crat_data_bkup;  //一元電圧微調整分の書き戻し2008.02.26
        gs_Okcv_adjust_wave_data    =  gs_Okcv_adjust_wave_data_bkup;  //一元電圧微調整分の書き戻し2008.02.26
        gs_Okcv_adjust_start_data   =  gs_Okcv_adjust_start_data_bkup; //一元電圧微調整分の書き戻し2008.08.05
 
        guc_Material_condition_counter = guc_Material_condition_counterb;
        guc_Wire_condition_counter     = guc_Wire_condition_counterb;
        guc_Method_condition_counter   = guc_Method_condition_counterb;
        guc_Pulse_mode_counter         = guc_Pulse_mode_counterb; //2008.02.08

                 guc_Pulse_mode_data                                  =  guc_Pulse_mode_datab;              //2008.02.08 
                 //gss_Select_dital[0]                                  =  (signed short)guc_Pulse_type_datab; //2008.02.08
                 gss_Select_dital[0]                                  =  0; //2008.03.27中川さん要請で変更
                 gss_Select_dital[1]                                  =  0; //2008.03.27中川さん要請で追加
                 gf_Frequence_adjust_data = gss_Select_dital[0];            //2008.03.27中川さん要請で追加
                 gf_Base_adjust_data      = gss_Select_dital[1];            //2008.03.27中川さん要請で追加
                 
                 //<><><>2008.4.1<><><>
                 gss_Select_dital[2] = 0;
                 gss_Select_dital[3] = 0;
                 gss_Select_dital[4] = 0;
                 
                 //<><><><><><><><><><><>
#endif
//***********************************

#if 0
                 if (guc_Pulse_mode_data == 0x03) //2008.02.08
                 {
                     gtt_Internal_pack.Data.In.fPulseMode.ALL = 0x10;
                 } else if (guc_Pulse_mode_data == 0x05) {
                     gtt_Internal_pack.Data.In.fPulseMode.ALL = 0x00;
                 }
                 if ((unsigned char)gss_Select_dital[0] == 0x00) //2008.02.08
                 {
                     gtt_Internal_pack.Data.In.fPulseMode.ALL = gtt_Internal_pack.Data.In.fPulseMode.ALL | 0x03;
                 } else if ((unsigned char)gss_Select_dital[0] == 0x01) {
                     gtt_Internal_pack.Data.In.fPulseMode.ALL = gtt_Internal_pack.Data.In.fPulseMode.ALL | 0x04;
                 }    
#endif
//****** ｃｈ読み込みのため削除 *****
#if 0 
        //初期電流
//        if (gus_Init_current_bkup <= 350 && gus_Init_current_bkup >= 1) //2007.12.09 2008.03.04変更
        if (gus_Init_current_bkup <= 350 && gus_Init_current_bkup >= 15) //2007.12.09 2008.03.04 2008.03.24変更
        {
            gtt_Internal_pack.Data.In.usWeldingInitCurr     = gus_Init_current_bkup;
        } else {
            gtt_Internal_pack.Data.In.usWeldingInitCurr     = 120;
        }
        //本電流
//        if (gus_Weld_current_bkup <= 350 && gus_Weld_current_bkup >= 1) //2007.12.09 2008.03.04変更
        if (gus_Weld_current_bkup <= 350 && gus_Weld_current_bkup >= 15) //2007.12.09 2008.03.04 2008.03.24変更
        {
            gtt_Internal_pack.Data.In.usWeldingCurr     = gus_Weld_current_bkup;
        } else {
            gtt_Internal_pack.Data.In.usWeldingCurr     = 120;
        }
        //クレータ電流
//        if (gus_Crat_current_bkup <= 350 && gus_Crat_current_bkup >= 1) //2007.12.09 2008.03.04変更
        if (gus_Crat_current_bkup <= 350 && gus_Crat_current_bkup >= 15) //2007.12.09 2008.03.04 2008.03.24変更
        {
            gtt_Internal_pack.Data.In.usWeldingCratCurr     = gus_Crat_current_bkup;
        } else {
            gtt_Internal_pack.Data.In.usWeldingCratCurr     = 120;
        }
        //波形
//        if (gus_Wave_current_bkup <= 350 && gus_Wave_current_bkup >= 1) //2007.12.09 2008.03.04変更
        if (gus_Wave_current_bkup <= 350 && gus_Wave_current_bkup >= 15) //2007.12.09 2008.03.04 2008.03.24変更
        {
            gtt_Internal_pack.Data.In.usWeldingWaveCurr     = gus_Wave_current_bkup;
        } else {
            gtt_Internal_pack.Data.In.usWeldingWaveCurr     = 120;
        }
        //スタート
        if (gus_Start_current_bkup <= 350 && gus_Start_current_bkup >= 15) //2008.08.05
        {
            gtt_Internal_pack.Data.In.usWeldingStartCurr     = gus_Start_current_bkup;
        } else {
            gtt_Internal_pack.Data.In.usWeldingStartCurr     = 120;
        }
            
        if (gus_Weld_voltage_bkup < 450 && gus_Weld_voltage_bkup > 60) //2007.12.09
        {
            gtt_Internal_pack.Data.In.usWeldingVolt     = gus_Weld_voltage_bkup;
            gtt_Internal_pack.Data.In.usWeldingInitVolt = gus_Init_voltage_bkup; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingCratVolt = gus_Crat_voltage_bkup; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingWaveVolt = gus_Wave_voltage_bkup; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingStartVolt= gus_Start_voltage_bkup;//2008.08.05
        } else {
            gtt_Internal_pack.Data.In.usWeldingVolt     = 184;
            gtt_Internal_pack.Data.In.usWeldingInitVolt = 184; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingCratVolt = 184; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingWaveVolt = 184; //2008.02.26
            gtt_Internal_pack.Data.In.usWeldingStartVolt= 184; //2008.08.05
        }

        //各種設定バックアップ分チェックと初期化　2008.02.26
        gtt_Parameter.Select_counter = 1;
        guc_Select_current_sel_counter = 1;
        //gtt_Parameter.Item.Parameter_set_flag = OFF;
        //gtt_Parameter.Item.Voltage_display_flag = OFF;
        //gtt_Parameter.Item.Wave_control_flag = OFF;
        //d00
        if (gtt_Parameter.Item.Parameter_set[0] < 0)    { gtt_Parameter.Item.Parameter_set[0] = 0;   }
        if (gtt_Parameter.Item.Parameter_set[0] > 1)    { gtt_Parameter.Item.Parameter_set[0] = 1;   }
        //d01
        if (gtt_Parameter.Item.Parameter_set[1] < 0)    { gtt_Parameter.Item.Parameter_set[1] = 0;   }
        if (gtt_Parameter.Item.Parameter_set[1] > 1)    { gtt_Parameter.Item.Parameter_set[1] = 1;   }
        //d02
        if (gtt_Parameter.Item.Parameter_set[2] < 5)    { gtt_Parameter.Item.Parameter_set[2] = 5;   }
        if (gtt_Parameter.Item.Parameter_set[2] > 995)  { gtt_Parameter.Item.Parameter_set[2] = 995; }
        //d03
        if (gtt_Parameter.Item.Parameter_set[3] < 10)   { gtt_Parameter.Item.Parameter_set[3] = 10;  }
        if (gtt_Parameter.Item.Parameter_set[3] > 90)   { gtt_Parameter.Item.Parameter_set[3] = 90;  }
        //d04
        if (gtt_Parameter.Item.Parameter_set[4] < 50)   { gtt_Parameter.Item.Parameter_set[4] = 50;  }
        if (gtt_Parameter.Item.Parameter_set[4] > 950)  { gtt_Parameter.Item.Parameter_set[5] = 950; }
        //d05
        if (gtt_Parameter.Item.Parameter_set[5] < 5)    { gtt_Parameter.Item.Parameter_set[5] = 5;   }
        if (gtt_Parameter.Item.Parameter_set[5] > 500)  { gtt_Parameter.Item.Parameter_set[5] = 500; }

        //<><>新設波形パラメータ 2008.03.07<><><><><>
        //d06
        if (gtt_Parameter.Item.Parameter_set[6] < -99)   { gtt_Parameter.Item.Parameter_set[6] = -99;   }
        if (gtt_Parameter.Item.Parameter_set[6] > 99)    { gtt_Parameter.Item.Parameter_set[6] = 99;   }
        //d07
        if (gtt_Parameter.Item.Parameter_set[7] < -99)   { gtt_Parameter.Item.Parameter_set[7] = -99;   }
        if (gtt_Parameter.Item.Parameter_set[7] > 99)    { gtt_Parameter.Item.Parameter_set[7] = 99;   }
        //d08
        if (gtt_Parameter.Item.Parameter_set[8] < -99)   { gtt_Parameter.Item.Parameter_set[8] = -99;   }
        if (gtt_Parameter.Item.Parameter_set[8] > 99)    { gtt_Parameter.Item.Parameter_set[8] = 99;   }
        //d09
        if (gtt_Parameter.Item.Parameter_set[9] < -99)   { gtt_Parameter.Item.Parameter_set[9] = -99;   }
        if (gtt_Parameter.Item.Parameter_set[9] > 99)    { gtt_Parameter.Item.Parameter_set[9] = 99;   }
        //d10
        if (gtt_Parameter.Item.Parameter_set[10] < -99)   { gtt_Parameter.Item.Parameter_set[10] = -99;   }
        if (gtt_Parameter.Item.Parameter_set[10] > 99)    { gtt_Parameter.Item.Parameter_set[10] = 99;   }
        //d11
        if (gtt_Parameter.Item.Parameter_set[11] < -99)   { gtt_Parameter.Item.Parameter_set[11] = -99;   }
        if (gtt_Parameter.Item.Parameter_set[11] > 99)    { gtt_Parameter.Item.Parameter_set[11] = 99;   }
        //d12
        if (gtt_Parameter.Item.Parameter_set[12] < -99)   { gtt_Parameter.Item.Parameter_set[12] = -99;   }
        if (gtt_Parameter.Item.Parameter_set[12] > 99)    { gtt_Parameter.Item.Parameter_set[12] = 99;   }

        gtt_Internal_pack.Data.In.vSldnAdj      = (short)((short)gtt_Parameter.Item.Parameter_set[6] * WIRSLDN);// ワイヤスローダウン調整
        gsf_Acc1 = (float)gtt_Parameter.Item.Parameter_set[7]; //d07(70)
        gss_Acc1 = (short)(gsf_Acc1 * 10.0);
        gsf_Acc2 = (float)gtt_Parameter.Item.Parameter_set[8]; //d08(71)
        gss_Acc2 = (short)(gsf_Acc2 * 10.0);
        gsf_Acc3 = (float)gtt_Parameter.Item.Parameter_set[9]; //d09(72)
        gss_Acc3 = (short)(gsf_Acc3 * 10.0);
        gsf_Acc4 = (float)gtt_Parameter.Item.Parameter_set[10]; //d10(73)
        gss_Acc4 = (short)(gsf_Acc4 * 10.0);
        gsf_Acc5 = (float)gtt_Parameter.Item.Parameter_set[11]; //d11(74)
        gss_Acc5 = (short)(gsf_Acc5 * 10.0);
        gsf_Delay = (float)gtt_Parameter.Item.Parameter_set[12]; //d12(75)
        gss_Delay = (short)gsf_Delay;

#endif
//***********************************

       //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
        gtt_Ctrl_flag.Weld_end_disp = ON; // 2008.03.04


        //gus_Initial_timer = 10000; //2009.02.12　表示が通常になっても数秒間入力を受け付けない問題があるので、ロードについてはこの時間を延長する。
        gus_Initial_timer = 12000; //2009.02.17　10000->12000
        //gus_Initial_timer = 6000; //2009.01.20

        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_upper = '1';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_mid   = '2';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_lower = '3';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_upper = '4';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_mid   = '5';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_lower = '6';

        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_upper16 = '6';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_mid16   = '5';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_lower16 = '4';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_upper16 = '3';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_mid16   = '2';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_lower16 = '1';

		/*custom.h内で、キバン上7SEGのﾊﾞｰｼﾞｮﾝ表示文字を定義している。注意！！*/
#if 0 //2009.07.14
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_upper32 = '0';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_mid32   = '4';
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_lower32 = '8';
#endif
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_upper32 = guc_Attribute_dps_no[0]; //2009.07.14
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_mid32   = guc_Attribute_dps_no[1]; //2009.07.14
        ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_lower32 = guc_Attribute_dps_no[2]; //2009.07.14
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_upper32 = guc_Attribute_version[0];
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_mid32   = guc_Attribute_version[1];
        ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_lower32 = guc_Attribute_version[2]; //2009.07.10


//--------- IIF by @Tny 2008/08/26 ------------
#if true
        gb_IIF_Select       = false;
        gus_IIF_DebugTimer1 = 1000; // 1sec
        gb_IIF_DebugFlag1   = false;
        guc_Iif_output      = 0x00;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
        gtt_Ctrl_flag.Iif_connect_err = false; //2009.11.04 IIF NEW
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
#endif
//--------------------------------------------
//--------- RTC by @Tny 2008/09/01 ------------
#if true
        // RTC周波数測定用カウンタ
        gus_cRTC_AdjustCount    = 0;
        // RTC周波数カウンタ
        gul_vRTC_FrequencyCount = 0;
#endif
//--------------------------------------------

//--------- Phase4 by @Tny 2008/09/08 --------
#if true
        gus_Iff_Detect_disp_timer = 0;  // IIF検出表示タイマー
#endif
//--------------------------------------------

//----- Phase5 by @Tny 2008/09/09 -----
#if true
        guc_R8_control.ALL  = 0;
        gb_R8_comuni        = false; // 次回は7SEGデータ
#endif
//--------------------------------------------
//----- Phase7 by @Tny 2008/09/10 -----
#if true
    guc_Error_code              = 0;
    gb_Error_Display_Sending    = false;    // エラー情報送信要求フラグ
    gb_Iif_Input                = false;    // IIFデータ受信フラグ
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
    gus_Iif_Detect_Timer        = 100000;   // IIF接続確認時間カウンタ：10秒 2009.10.29 IIF NEW
#else
    gus_Iif_Detect_Timer        = 200000;   // IIF接続確認時間カウンタ：２０秒
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
//----- Phase12 by @Tny 2008/09/17 -----
#if true
    if(gus_Iif_BuiltIn == IIF_BUILT_IN_RENEWAL){    // IIF接続？
        gb_Iif_BuiltIn          = true;
        guc_Init_wait_sequence  = 120000;    // 初期シーケンス待ち時間：12sec   // Phase13 by @Tny 2008/09/18
    }
    else{
        gb_Iif_BuiltIn          = false;
        guc_Init_wait_sequence  = 30000;     // 初期シーケンス待ち時間：3sec
    }
#endif
//--------------------------------------------
#endif
//--------------------------------------------
//------ Phase8 by @Tny 2008/09/11 ------
#if true
    // エラー履歴
    gtt_Ctrl_counter.b_Error_information = false;
    gb_Error_History_Write               = false;      // エラー履歴テーブル保存フラグ
    gus_Iif_BuiltIn_write                = false;      // IIF接続フラグ保存フラグ
#endif
//---------------------------------------------------------------------
//------ Phase9 by @Tny 2008/09/12 ------
#if true
    // 本体電源起動時のＦＡＮ制御は「弱（FAN2：Ｒ８側ＦＡＮ＝ＯＮ）」で７分間に設定
    //gtt_Ctrl_flag.Fan_off           = OFF;
    gtt_Ctrl_flag.Fan_off           = ON;               //2008.11.20
    gtt_Ctrl_counter.Fan_off        = FAN_OFF_TIME;     //2008.11.20
    gtt_Ctrl_counter.Fan_A_off      = 0;                //2008.11.20
    gtt_Ctrl_word.Fan_ctrl_code     = OFF;
    //guc_R8_control.Bit1Sw.R8_Fan    = true;
    guc_R8_control.Bit1Sw.R8_Fan    = false; //2008.11.14
//  FAN2                            = ON;       // Phase17 by @Tny 2008/09/24　　別所で設定
    gtt_Ctrl_flag.Ts_cancel         = OFF;      //ＴＳ受付許可 2009.01.28
#endif
//---------------------------------------------------------------------
//----- Phase11 by @Tny 2008/09/16 -----
#if true
    guc_Sub_display_flag            = 0;    //  サブ表示フラグ
#endif
//--------------------------------------------
//----- Phase121 by @Tny 2008/09/17 -----
#if true
    gtt_End_welding_display.bProc1          = false;
    gtt_End_welding_display.bProc2          = false;
    gtt_End_welding_display.us_Display_time = 0;
#endif
//--------------------------------------------
//----- Phase13 by @Tny 2008/09/18 -----
#if true
    {
        unsigned char   i;
        for(i=0;i<10;i++){  // ＬＥＤ表示制御バックアップテーブルの初期化
        	gtt_LED_control_backup[i].uc_Proc       = 0;    // 制御有効フラグ
        	gtt_LED_control_backup[i].uc_ON_Time    = 0;	// 点滅ＯＮ時間
        	gtt_LED_control_backup[i].uc_OFF_Time   = 0;	// 点滅ＯＦＦ時間
        	gtt_LED_control_backup[i].uc_vCount     = 0;    // 点滅回数
        }
        guc_Error_return_LED_control_A = 0;     // 「エラー復帰時ＬＥＤ表示制御インデックス：Ａ」の初期化
        guc_Error_return_LED_control_B = 0;     // 「エラー復帰時ＬＥＤ表示制御インデックス：Ｂ」の初期化
        gb_Error_blink                 = false; // エラー点滅制御要求フラグの初期化
    }
#endif
//--------------------------------------------
//----- Phase15 by @Tny 2008/09/19 -----
#if true
    gb_15SEG_LED_Error_Disp_Hold    = false;   // エラー表示データ送信中フラグ
#endif
//--------------------------------------------
//----- Phase18 by @Tny 2008/09/25 -----
#if true
    guc_Initial_display_flag = false;
#endif
//--------------------------------------------
//----- Phase21 by @Tny 2008/10/03 -----
#if false //2009.03.16 del
    gus_Display_command_stop    = 0;
    gb_Memory_copy_recv_ended   = false;
#endif
//--------------------------------------------
//----- Phase22 by @Tny 2008/10/07 -----
#if true
    gus_Iif_Purge_Judgment  = 0;     // ＩＩＦ切断（切り離し）判定カウンタ
    guc_Welding_Play_Ch_no  = 0;     // 溶接中再生チャンネル
    gb_Welding_Play_Change  = false; // 溶接中再生チャンネル実行フラグ
#endif
//--------------------------------------------
//----- Phase26 by @Tny 2008/10/23 -----
#if true
    gb_Controller_UnConnect         = false;    // コントローラ未接続確認フラグ
    gb_Ping_to_Controller           = false;    // コントローラ未接続確認実行フラグ
    gus_Controller_Connect_Timer    = 0;        // コントローラ接続確認タイマー
#endif
//--------------------------------------------

//----- Phase29 by @Tny 2008/11/21 -----
#if true
	gus_Pri_volt_err_timer			= PRI_VOLT_LOW_TIME;	// 一次電圧低異常検知ディレイタイマー
#endif
//--------------------------------------------




//***** BP4 2009.01.13 *****
  //guc_Method_condition_counter = 0;
  //guc_Method_condition_data = guc_Method_condition_counter;
  //guc_Crater_mode_counter = 0;
  //guc_Pulse_mode_counter = 0;
  //guc_Pulse_mode_data = guc_Pulse_mode_counter;



//溶接ナビテーブルの材質の検索
  {
     //PNAVITABLE  pNT = (PNAVITABLE)0x00C0000;
     PNAVITABLE  pNT = (PNAVITABLE)NaviTable;	// 2019.06.10
     PNAVICODE   pNaviCode;
     int         Cnt;

     int             pi_Navi_counter;
     unsigned char   puc_Navi_value;
     unsigned char   puc_Navi_min;
     unsigned char   i,s,t,j;



     gui_Navi_table_code_counter = 0;

     for(  Cnt = 0 ; Cnt <=NAVITBLCNT ; Cnt++)
     {
        pNaviCode = &pNT->NaviCode;
        if (pNaviCode->material == 0xFF) break;
    
        guc_Navi_code_work[gui_Navi_table_code_counter]    = pNaviCode->material;           //材質
        gui_Navi_table_code_counter++;
        pNT++;                                          //次のテーブルへ
     }
     
     pi_Navi_counter =  gui_Navi_table_code_counter;
     
     //ソート処理
     for ( i = 0 ; i < pi_Navi_counter-1 ; i++)
     {
         puc_Navi_min = guc_Navi_code_work[i];
         s = i;
         for (j = i + 1 ; j < pi_Navi_counter ; j++)
         {
              if (guc_Navi_code_work[j] < puc_Navi_min)
              {
                  puc_Navi_min = guc_Navi_code_work[j];
                  s = j;
              }
         }
              t = guc_Navi_code_work[i];
              guc_Navi_code_work[i] = guc_Navi_code_work[s];
              guc_Navi_code_work[s] = t;
      }
      //同値まとめ処理
      puc_Navi_value    =  guc_Navi_code_work[0];
      guc_Navi_material_code[0] = guc_Navi_code_work[0];
      guc_Navi_material_counter = 0;
      for ( Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++) //2009.02.20
      {
         if (puc_Navi_value != guc_Navi_code_work[Cnt])
         {
             guc_Navi_material_counter++;
             puc_Navi_value = guc_Navi_code_work[Cnt];
             guc_Navi_material_code[guc_Navi_material_counter] = guc_Navi_code_work[Cnt];
         }
      }
      guc_Navi_material_counter = guc_Navi_material_counter - 1;

  }


// BP4 Phase3 by @Tny 2009.01.13
	guc_Menu_Hierarchy	= 0;	// 詳細メニュー設定階層フラグ

// BP4 Phase3 by @Tny 2009.01.15
	gtt_Ctrl_flag.Set_screen_on_off = OFF;
	gb_2Line_FirstDisplay			= false;	// 初回二行目表示フラグをＯＦＦ

// BP4 Phase4 by @Tny 2009.01.15
	gb_RTC_Sec_Colon				= true;		// 秒コロン表示フラグ


//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.21
	InitialStringInput(true, false, "");	// 文字入力処理の初期化		BP4 Phase13 by @Tny 2009.02.23
	gb_RecWeldCond = true;			// 記憶条件データの有無
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// BP4 Phase6 by @Tny 2009.01.27
	gb_WeldCondNameWrite = false;	// 溶接条件名書き込み要求フラグ
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// BP4 Phase6 by @Tny 2009-02-12
#if true
	if(bInitialProc){
		unsigned char	i;
		for(i=0;i<CH;i++){	// 0-16
			strcpy((char *)gt_WeldCondName[i], "CH  :");		// 条件名文字列データ格納エリアへデフォルト名の文字列をコピー
			gt_WeldCondName[i][2] = (i / 10 + 0x30);
			gt_WeldCondName[i][3] = (i % 10 + 0x30);
		}
//		guc_Write_check_flag_ch[2] = true;
//		guc_Write_check_flag_ch[5] = true;
		gb_WeldCondNameWrite = true;	// 溶接条件名書き込み要求フラグ
	}
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
#if true
	if(bInitialProc){
//2011.10.01+++++
//		guc_Lcd_Bright		= 4;	// コントラストデータ：デフォルト値（＝４）
		guc_Lcd_Bright		= 1;	// コントラストデータ：デフォルト値（＝１）2011.10.01
//2011.10.01-----
		gb_LcdBrightWrite	= true;	// ＬＣＤコントラスト値の記録の要求
	}
#endif
//-----------------------------------------------------------

//-----------------------------------------------------------
//BP4 Phase10 by @Tny 2009.02.18	表示コマンド系送信要求フラグ
	gb_RemCom_0x20	= false;
	gb_RemCom_0x21	= false;
	gb_RemCom_0x22	= false;
	gb_RemCom_0x23	= false;
	gb_RemCom_0x32	= false;
	gb_RemCom_0x34	= false;
	gb_RemCom_0x35	= false;
	gb_RemCom_0x36	= false;
	gb_RemCom_0x37	= false;
	gb_RemCom_0x38	= false;
	gb_RemCom_0x39	= false;
//-----------------------------------------------------------
//-----------------------------------------------------------
//BP4 Phase10 by @Tny 2009.02.18
	gb_ComSend1msec	= false;	// １ｍ秒毎データ送信用フラグ
//-----------------------------------------------------------

//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23
	gb_ServiceMenu		= false;	// サービスマンメニュー要求フラグ
	gb_RescueMenu		= false;	// レスキュー処理要求フラグ
	gb_JogLock			= false;	// ＪＯＧ決定キー無効化フラグ
	gus_MessageTimer	= 0;		// メッセージ表示時間（１００ｍ秒単位）

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//BP4 Phase14 by @Tny 2009.02.24
	gb_RamAllClear		= false;	// メモリ・オールクリア実行フラグ
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.10
	gss_Select_dital[P_CONTROLLER_LOCK]	= false;	// P52：コントローラ・ロック解除中
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
	gb_RescueOpeningDisp	= false;	// レスキュー・メニューのオープニング画面の表示要求フラグ
//--------------------------------------------------------------------

//<><><> 2009.12.18 エラーレベル１，２発生時ＴＳ再起動を促す処理 <><><>
        gtt_Ctrl_flag.Err_ts_cansel   = OFF;
        gtt_Ctrl_flag.Ts_on_err_timer = OFF;
        gtt_Ctrl_flag.Ts_on_err       = OFF;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


        gtt_Ctrl_flag.Robot_connect_time = OFF; //2010.03.23

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	gb_External_IIF					= false;	// 外部拡張ユニット接続フラグ（true=外部拡張ユニット／false=ＩＩＦ）
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

	gb_Iif_comuni_failed        = false;	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny

//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
	gb_Iif_First_Toch_sw		= true;		// ＩＩＦ接続時ＴＳ状態確認フラグ
//-------------------------------------------------
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 5)>	2011.10.26 by @Tny
	gb_Iif_Disconnect			= false;	// ＩＩＦ切断フラグ：初期化
//-------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
// <NAVI Enhancements(Phase 1)> 2011.10.26 by @Tny
//
	gtt_Navi.b_Navi_Disp		= false;	// ナビ表示フラグ：非表示
//-----------------------------------------------------------------------------------------------------------------------------------------------

	//************* 現在詳細メニューの記憶部がないので強制的に初期化する 2019.05.30現在　製品では必ず削除 **************
	{
		short i;
		for (i = 0 ; i< 30 ;i++)
		{
gss_Select_dital[i]=gtt_Dital_attribute[i].ss_Init;
		}
	}
	//******************************************************************************************************************


        return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_com_memory_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

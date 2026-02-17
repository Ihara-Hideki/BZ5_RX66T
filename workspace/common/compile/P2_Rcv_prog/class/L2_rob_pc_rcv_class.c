//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｒｏｂ＿ｐｃ＿ｒｃｖ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ロボット、ＰＣ受信
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



//**************************** 注意（重要）**************************************
//  今後本プログラムを修正または追加される方は以下の事に注意して下さい
//　
//　★gtt_Internal_pack.Dataについて
//　　本変数は参照のみにして下さい。
//　　理由：通信が行われると、ComuniPack.Dataのデータが書き込まれてしまうため。
//　　　　　（変更した内容が元に戻ってしまう）
//　★ComuniPack.Dataについて
//　　本変数はgtt_Internal_pack.Dataへの代入のみに使用して下さい。
//　　また代入はrob_pc_rcv_classのみで行ってください。
//　　理由：不用意にこの変数を書き換えると通信された内容が変わってしまい、
//　　　　　ロボットと溶接機との間のデータに矛盾が生じてしまうため
//　　　　　また、rob_pc_rcv_class以外で代入を行うと溶接機内でデータの矛盾が
//　　　　　生じるため。
//********************************************************************************


#include  "custom.h"

void rob_pc_rcv_class(void)
{

     if (ComuniPack.Data.bRS232Connection || ComuniPack.Data.bRS422Connection)	// ＲＳ２３２ｃ、ＲＳ４２２回線接続
     {
         gtt_Internal_pack.Data.bRS232Connection = ComuniPack.Data.bRS232Connection;
         gtt_Internal_pack.Data.bRS422Connection = ComuniPack.Data.bRS422Connection;

   	if (ComuniPack.Data.To.bChangeData)	// 受信データ更新
        {
	        gtt_Internal_pack.Data.In.iRecvCommand               = ComuniPack.Data.To.iRecvCommand;           // 受信コマンド（データ更新判別用）の初期化
		gtt_Internal_pack.Data.In.usWeldingCurr              = (sint) ComuniPack.Data.To.usWeldingCurr;   // 出力電流指令値

		//gtt_Internal_pack.Data.In.usWeldingVolt              = (sint) ComuniPack.Data.To.usWeldingVolt;   // 出力電圧指令値
		//gtt_Internal_pack.Data.In.fWireDiameter.ALL          = ComuniPack.Data.To.fWireDiameter.ALL;      // ワイヤ径 2007.7.6削除
		//gtt_Internal_pack.Data.In.fWelding.ALL               = ComuniPack.Data.To.fWelding.ALL;           // 溶接法   2007.7.6削除
		//gtt_Internal_pack.Data.In.fWireMaterial.ALL          = ComuniPack.Data.To.fWireMaterial.ALL;      // ワイヤ材質 2007.7.6削除
		//gtt_Internal_pack.Data.In.fWireSelect.ALL            = ComuniPack.Data.To.fWireSelect.ALL;        // ワイヤ種 2007.7.6削除
		//gtt_Internal_pack.Data.In.fInitialSelect1.ALL        = ComuniPack.Data.To.fInitialSelect1.ALL;    // 初期データ設定１ 2007.7.6削除

#if G3_NEW_COM
		    gtt_Internal_pack.Data.In.usWeldingVolt              = (sint) ComuniPack.Data.To.usWeldingVolt;   // 出力電圧指令値
#else
            if ((gtt_Internal_pack.Data.In.fInitialSelect1.ALL) & 0x01 == 0x01) //一元電圧選択
            {
      		    gtt_Okcv.Okcv_ref                                    = (sint) ComuniPack.Data.To.usWeldingVolt;   // 出力電圧指令値
            } else {
	     	    gtt_Internal_pack.Data.In.usWeldingVolt              = (sint) ComuniPack.Data.To.usWeldingVolt;   // 出力電圧指令値
            }
#endif
		//gtt_Internal_pack.Data.In.vTsoAdj                    = ComuniPack.Data.To.vTsoAdj;                // 短絡初期時間調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vIscAdj                    = ComuniPack.Data.To.vIscAdj;                // 短絡電流屈折値調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vIsl1Adj                   = ComuniPack.Data.To.vIsl1Adj;               // 短絡電流勾配１調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vIsl2Adj                   = ComuniPack.Data.To.vIsl2Adj;               // 短絡電流勾配２調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vTspAdj                    = ComuniPack.Data.To.vTspAdj;                // 突っ掛かり防止時間調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vIacAdj                    = ComuniPack.Data.To.vIacAdj;                // アーク電流屈折値調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vIhotAdj                   = ComuniPack.Data.To.vIhotAdj;               // ホット電流調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vVhotAdj                   = ComuniPack.Data.To.vVhotAdj;               // ホット電圧調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vSldnAdj                   = ComuniPack.Data.To.vSldnAdj;               // ワイヤスローダウン調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vFttAdj                    = ComuniPack.Data.To.vFttAdj;                // ＦＴＴレベル調整 2007.2.5削除
		//gtt_Internal_pack.Data.In.vBarnBackAdj               = ComuniPack.Data.To.vBarnBackAdj;           // バーンバック時間調整 2007.2.5削除
		gtt_Internal_pack.Data.In.fWelderCommand.ALL         = ComuniPack.Data.To.fWelderCommand.ALL;     // 溶接電源動作指令
		gtt_Internal_pack.Data.In.fWelderCheck.ALL           = ComuniPack.Data.To.fWelderCheck.ALL;       // 溶接電源チェック
		gtt_Internal_pack.Data.In.usIP                       = ComuniPack.Data.To.usIP;                   // パルスピーク指令電流
		gtt_Internal_pack.Data.In.usIB                       = ComuniPack.Data.To.usIB;                   // パルスベース指令電流
		gtt_Internal_pack.Data.In.usPulseFreq                = ComuniPack.Data.To.usPulseFreq;            // パルス指令周波数
		gtt_Internal_pack.Data.In.usPulseDuty                = ComuniPack.Data.To.usPulseDuty;            // パルス指令幅
		gtt_Internal_pack.Data.In.usAcFreq                   = ComuniPack.Data.To.usAcFreq;               // 交流周波数
		gtt_Internal_pack.Data.In.ucCleaningDuty             = ComuniPack.Data.To.ucCleaningDuty;         // クリーニング幅
		gtt_Internal_pack.Data.In.ucMixFreq                  = ComuniPack.Data.To.ucMixFreq;              // MIX TIG周波数
		gtt_Internal_pack.Data.In.ucMixAcRatio               = ComuniPack.Data.To.ucMixAcRatio;           // MIX(AC)比率
		gtt_Internal_pack.Data.In.fControl.ALL               = ComuniPack.Data.To.fControl.ALL;           // コントロール
		gtt_Internal_pack.Data.In.ucImprudenceVolt           = ComuniPack.Data.To.ucImprudenceVolt;       // 電極短絡電圧指令値
		gtt_Internal_pack.Data.In.fPulseMode.ALL             = ComuniPack.Data.To.fPulseMode.ALL;         // パルスモード設定
		//gtt_Internal_pack.Data.In.vHotTime                   = ComuniPack.Data.To.vHotTime;               // ホットタイム 2007.2.5削除
		gtt_Internal_pack.Data.In.vIniIpAdj                  = ComuniPack.Data.To.vIniIpAdj;              // スタートピーク電流微調整
		gtt_Internal_pack.Data.In.vIniIbAdj                  = ComuniPack.Data.To.vIniIbAdj;              // スタートベース電流微調整
		gtt_Internal_pack.Data.In.vIpAdj                     = ComuniPack.Data.To.vIpAdj;                 // パルスピーク電流微調整
		gtt_Internal_pack.Data.In.vIb1Adj                    = ComuniPack.Data.To.vIb1Adj;                // パルス第１ベース電流微調整
		gtt_Internal_pack.Data.In.vIb2Adj                    = ComuniPack.Data.To.vIb2Adj;                // パルス第２ベース電流微調整
		gtt_Internal_pack.Data.In.vIprAdj                    = ComuniPack.Data.To.vIprAdj;                // パルスピーク立ち上がり微調整
		gtt_Internal_pack.Data.In.vIpfAdj                    = ComuniPack.Data.To.vIpfAdj;                // パルスピーク立ち下がり微調整
		gtt_Internal_pack.Data.In.vTiprAdj                   = ComuniPack.Data.To.vTiprAdj;               // パルス立ち上がり時間微調整
		gtt_Internal_pack.Data.In.vTipAdj                    = ComuniPack.Data.To.vTipAdj;                // パルスピーク立ち上がり時間微調整
		gtt_Internal_pack.Data.In.vTipfAdj                   = ComuniPack.Data.To.vTipfAdj;               // パルス立ち下がり時間微調整
		gtt_Internal_pack.Data.In.vPulseFreqAdj              = ComuniPack.Data.To.vPulseFreqAdj;          // パルス周波数微調整
		gtt_Internal_pack.Data.In.vLowPulseAB_LevelGap       = ComuniPack.Data.To.vLowPulseAB_LevelGap;   // 簡易ローパルス：Ａ条件Ｂ条件レベル差
		gtt_Internal_pack.Data.In.vLowPulseAB_TimeRatio      = ComuniPack.Data.To.vLowPulseAB_TimeRatio;  // 簡易ローパルス：Ａ条件Ｂ条件時間比率
		gtt_Internal_pack.Data.In.vLowPulseFreq              = ComuniPack.Data.To.vLowPulseFreq;          // 簡易ローパルス：周波数
		gtt_Internal_pack.Data.In.vLowPulseStartTimeAdj      = ComuniPack.Data.To.vLowPulseStartTimeAdj;  // 簡易ローパルス開始時間微調整
		gtt_Internal_pack.Data.In.vPulseStartSlope           = ComuniPack.Data.To.vPulseStartSlope;       // パルススタートスロープ
		gtt_Internal_pack.Data.In.vPulseExecSlope            = ComuniPack.Data.To.vPulseExecSlope;        // パルス指令値切り替えスロープ
		gtt_Internal_pack.Data.In.vPulsePerformance          = ComuniPack.Data.To.vPulsePerformance;      // パルス応答性
		gtt_Internal_pack.Data.In.fLotCheck.ALL              = ComuniPack.Data.To.fLotCheck.ALL;          // 製品検査用
		gtt_Internal_pack.Data.In.vAfterFlowAddTime          = ComuniPack.Data.To.vAfterFlowAddTime;      // アフターフロー時間加算値
       }
#if G3_NEW_COM

       if (guc_Method_rewrite_check_flag == 1) //2007.7.6追加
	   {
           gtt_Internal_pack.Data.In.fWireDiameter.ALL          = ComuniPack.Data.To.fWireDiameter.ALL;      // ワイヤ径
		   gtt_Internal_pack.Data.In.fWelding.ALL               = ComuniPack.Data.To.fWelding.ALL;           // 溶接法
		   gtt_Internal_pack.Data.In.fWireMaterial.ALL          = ComuniPack.Data.To.fWireMaterial.ALL;      // ワイヤ材質
		   gtt_Internal_pack.Data.In.fWireSelect.ALL            = ComuniPack.Data.To.fWireSelect.ALL;        // ワイヤ種
		   gtt_Internal_pack.Data.In.fInitialSelect1.ALL        = ComuniPack.Data.To.fInitialSelect1.ALL;    // 初期データ設定１
           guc_Method_rewrite_check_flag      = 0;              // 0:書き換え無しｏｒ書き換え終了 1:書き換えのため受信済み　溶接条件データ書き換え確認フラグ
       }

       if (guc_Hfix_rewrite_check_flag == 1)             // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 半固定データ書き換え確認フラグ
       {
           gtt_Internal_rewrite_data.Hfix_no   = gtt_Com_rewrite_data.Hfix_no;
           gtt_Internal_rewrite_data.Hfix_data = gtt_Com_rewrite_data.Hfix_data;
           guc_Hfix_rewrite_check_flag = 2;
       }
       if (guc_Val_rewrite_check_flag0 == 1)              // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
       {
           gtt_Internal_rewrite_data.Val_no0       = gtt_Com_rewrite_data.Val_no0;
           gtt_Internal_rewrite_data.Val_a_data0   = gtt_Com_rewrite_data.Val_a_data0;
           gtt_Internal_rewrite_data.Val_b_data0   = gtt_Com_rewrite_data.Val_b_data0;
           gtt_Internal_rewrite_data.Val_c_data0   = gtt_Com_rewrite_data.Val_c_data0;
           gtt_Internal_rewrite_data.Val_min_data0 = gtt_Com_rewrite_data.Val_min_data0;
           gtt_Internal_rewrite_data.Val_max_data0 = gtt_Com_rewrite_data.Val_max_data0;
           guc_Val_rewrite_check_flag0 = 2;
       }
       if (guc_Val_rewrite_check_flag1 == 1)              // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
       {
           gtt_Internal_rewrite_data.Val_no1       = gtt_Com_rewrite_data.Val_no1;
           gtt_Internal_rewrite_data.Val_a_data1   = gtt_Com_rewrite_data.Val_a_data1;
           gtt_Internal_rewrite_data.Val_b_data1   = gtt_Com_rewrite_data.Val_b_data1;
           gtt_Internal_rewrite_data.Val_c_data1   = gtt_Com_rewrite_data.Val_c_data1;
           gtt_Internal_rewrite_data.Val_min_data1 = gtt_Com_rewrite_data.Val_min_data1;
           gtt_Internal_rewrite_data.Val_max_data1 = gtt_Com_rewrite_data.Val_max_data1;
           guc_Val_rewrite_check_flag1 = 2;
       }
       //微調整項目１変数転送　2007.2.5追加
       if (guc_Adj1_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目１書き換え確認フラグ 2007.2.5追加
       {
		   gtt_Internal_pack.Data.In.vTsoAdj       = (float)((float)ComuniPack.Data.To.vTsoAdj      * TS0);    // 短絡初期時間調整 2007.2.5
		   gtt_Internal_pack.Data.In.vIscAdj       = (float)((float)ComuniPack.Data.To.vIscAdj      * ISC);    // 短絡電流屈折値調整 2007.2.5
		   gtt_Internal_pack.Data.In.vIsl1Adj      = (float)((float)ComuniPack.Data.To.vIsl1Adj     * ISL1);   // 短絡電流勾配１調整 2007.2.5
		   gtt_Internal_pack.Data.In.vIsl2Adj      = (float)((float)ComuniPack.Data.To.vIsl2Adj     * ISL2);   // 短絡電流勾配２調整 2007.2.5
		   gtt_Internal_pack.Data.In.vTspAdj       = ComuniPack.Data.To.vTspAdj;                // 突っ掛かり防止時間調整 2007.2.5　未使用
		   gtt_Internal_pack.Data.In.vIacAdj       = ComuniPack.Data.To.vIacAdj;                // アーク電流屈折値調整 2007.2.5　未使用
           guc_Adj1_rewrite_check_flag = 2;
       }
       //微調整項目２変数転送　2007.2.5追加
       if (guc_Adj2_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       {
		   gtt_Internal_pack.Data.In.vIhotAdj      = (short)((float)ComuniPack.Data.To.vIhotAdj     * HOTCUR); // ホット電流調整 2007.2.5
		   gtt_Internal_pack.Data.In.vVhotAdj      = (float)((float)ComuniPack.Data.To.vVhotAdj     * HOTVLT); // ホット電圧調整 2007.2.5
		   gtt_Internal_pack.Data.In.vHotTime      = (short)((short)ComuniPack.Data.To.vHotTime     * HOTTM);  // ホットタイム 2007.2.5
		   gtt_Internal_pack.Data.In.vSldnAdj      = (short)((short)ComuniPack.Data.To.vSldnAdj     * WIRSLDN);// ワイヤスローダウン調整 2007.2.5
		   gtt_Internal_pack.Data.In.vFttAdj       = (short)((float)ComuniPack.Data.To.vFttAdj      * FTTLVL); // ＦＴＴレベル調整 2007.2.5
		   gtt_Internal_pack.Data.In.vBarnBackAdj  = (short)((short)ComuniPack.Data.To.vBarnBackAdj * BBKTIME);// バーンバック時間調整 2007.2.5
           guc_Adj2_rewrite_check_flag = 2;
       }
       if ( guc_Table_change_flag       == 1)       // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み テーブル切り替え確認フラグ 2007.2.9
       {
	       gtt_Internal_pack.Data.In.vTableChange  = ComuniPack.Data.To.vTableChange;           // ＣＯ２テーブル切り替え 2007.2.9
           guc_Table_change_flag = 2;
       }
#else
       if ((gtt_Internal_pack.Data.In.fInitialSelect1.ALL) & 0x01 == 0x01) //一元電圧選択
       {
           gtt_Internal_pack.Data.In.usWeldingVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingCurr / 2] * 2) + gtt_Okcv.Okcv_ref);
       } else {
           if (gtt_Internal_pack.Data.In.usWeldingVolt < 0)
           {
               gtt_Internal_pack.Data.In.usWeldingVolt = gtt_Internal_pack.Data.In.usWeldingVolt * -1;
           }
       }
#endif
       //拡張溶接微調パラメータ個別　2007.5.29追加
       if (guc_Exd_adj1_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       {
           gtt_Internal_pack.Data.In.Id_no = ComuniPack.Data.To.Id_no; //ＩＤ番号の取得

           switch (gtt_Internal_pack.Data.In.Id_no)
           {
                   case 1:
                        gtt_Internal_pack.Data.In.Sp_current =  (float)((float)ComuniPack.Data.To.Sp_current * SP_I);       //ＳＰ電流
                        break;
                   case 2:
                        gtt_Internal_pack.Data.In.Sp_time    =  (float)((float)ComuniPack.Data.To.Sp_time    * SP_T);       //ＳＰ時間
                        break;
                   case 3:
                        gtt_Internal_pack.Data.In.Eli        =  (float)((float)ComuniPack.Data.To.Eli        * ELI);        //ＥＬＩ
                        break;
                   case 4:
                        gtt_Internal_pack.Data.In.Mts_v      =  (float)((float)ComuniPack.Data.To.Mts_v      * MTS_V);      //重畳電圧値
                        break;
                   case 5:
                        gtt_Internal_pack.Data.In.Mts_ontime =  (float)((float)ComuniPack.Data.To.Mts_ontime * MTS_ONTIME); //重畳電圧ＯＮ時間
                        break;
                   case 6:
                        gtt_Internal_pack.Data.In.Mts_cycle  =  (float)((float)ComuniPack.Data.To.Mts_cycle  * MTS_CYCLE);  //重畳電圧周期
                        break;
                   default:
                        break;
           }
           guc_Exd_adj1_rewrite_check_flag    = 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       }

       //拡張溶接微調パラメータ一括　2007.5.29追加
       if (guc_Exd_adj2_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       {
           gtt_Internal_pack.Data.In.Sp_current =  (float)((float)ComuniPack.Data.To.Sp_current * SP_I);       //ＳＰ電流
           gtt_Internal_pack.Data.In.Sp_time    =  (float)((float)ComuniPack.Data.To.Sp_time    * SP_T);       //ＳＰ時間
           gtt_Internal_pack.Data.In.Eli        =  (float)((float)ComuniPack.Data.To.Eli        * ELI);        //ＥＬＩ
           gtt_Internal_pack.Data.In.Mts_v      =  (float)((float)ComuniPack.Data.To.Mts_v      * MTS_V);      //重畳電圧値
           gtt_Internal_pack.Data.In.Mts_ontime =  (float)((float)ComuniPack.Data.To.Mts_ontime * MTS_ONTIME); //重畳電圧ＯＮ時間
           gtt_Internal_pack.Data.In.Mts_cycle  =  (float)((float)ComuniPack.Data.To.Mts_cycle  * MTS_CYCLE);  //重畳電圧周期
           guc_Exd_adj2_rewrite_check_flag    = 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       }

       //２００６．１２．１５　バックＲＡＭテスト
       if (test_flag == OFF)
       {
           test_flag = ON;
           PC_Send_C3( );
       }

       //************* トーチＳＷｏｆｆを一定時間受け取らない　2007.2.24 *************
       if (gtt_Ctrl_flag.Toch_sw_off_delay_time == ON)
       {
           if (gtt_Ctrl_counter.Toch_sw_off_delay_time <= 0)
           {
               gtt_Ctrl_flag.Toch_sw_off_delay_time = OFF;
               //gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = OFF; 2007.3.1削除
           } else {
               gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = ON;
           }
        }
       //*****************************************************************************

       //****************** ＰＣ通信初期化フラグセット 2007.4.2 **********************
       if (gtt_Internal_pack.Data.bRS232Connection == ON && gtt_Ctrl_flag.Rs232_start == OFF)	// ＲＳ２３２ｃ回線接続
       {
           gtt_Ctrl_flag.Rs232_start = ON;
           gtt_Ctrl_flag.Rs232_init = ON;
       }
       //*****************************************************************************
    }







       return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_rob_pc_rcv_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

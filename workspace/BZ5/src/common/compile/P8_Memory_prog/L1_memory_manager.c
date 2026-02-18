//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍｅｍｏｒｙ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      メモリ管理
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2008.08.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

void memory_manager(void)
{


            //***** オールクリア 2009.02.23 ********
#if 0 //2009.04.20
            if (gtt_Dsw.Sw.No6 == true)
            {
                guc_Initial_load_data = 0x00;
            }
#endif
            //****************************************

     if((guc_Select_counter == MODE_WELDING)||(guc_Select_counter == MODE_DETAILS))	// BP4 Phase6 by @Tny 2009/01/27
     {
        //if (guc_Remo_table_check_flag == true && gtt_Ctrl_flag.Param_change == ON)//2008.09.17テーブルが存在しない場合はメモリ記憶しないように変更
        if (gtt_Ctrl_flag.Param_change == ON)//2009.01.22
        {
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19	リモコン接続時はデータの記憶を行わない
//		if(gtt_Ctrl_flag.RemoteController == false){ //2009.07.31 del
//---------------------------------------
            ch0_write_class(gtt_Ctrl_flag.Param_change);
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19	リモコン接続時はデータの記憶を行わない
//		}
//---------------------------------------
        }
        gtt_Ctrl_flag.Param_change = OFF;
     }
     if (guc_Select_counter == MODE_PLAY && (guc_Ch_no != guc_Ch_no_bkup))	// BP4 Phase6 by @Tny 2009/01/27
     {
         guc_Ch_no_bkup = guc_Ch_no;
         ch_play_class(guc_Ch_no);
         gtt_Table_key.Change_flag = ON; //2009.04.01
     }
//--------- Phase22 by @Tny 2008/10/07 --------
#if true
    if(guc_Sequence_mode == IDLING){ // 現在は待機中？
        if(gb_Welding_Play_Change){     // 溶接実行中に再生処理を行った？
            ch_play_class(guc_Welding_Play_Ch_no); // 最終チャンネルの条件を全て再生する
            gb_Welding_Play_Change  = false;
        }
    }
#endif
//---------------------------------------------
     if (gtt_Ctrl_flag.Rec == ON)
     {
         ch_rec_class(guc_Ch_no);
         gtt_Ctrl_flag.Rec = OFF;
     }
     if (gtt_Ctrl_flag.Delete == ON) //2008.09.09
     {
         guc_Write_check_flag[guc_Ch_no]   = false;
//--------- Phase21 by @Tny 2008/10/03 --------
#if true
         ch_rec_class((guc_Ch_no + MEMORY_DELETE_CH));  // 記憶チャンネル削除識別子の付加
#endif
//---------------------------------------------
         gtt_Ctrl_flag.Delete = OFF;
     }
     //**** リセット実行処理 ****
     //ユーザー特殊パラメータ・詳細データリセット
     if (gtt_Ctrl_flag.User_all_parameter_reset_exe == ON)
     {
         memory_initialize_class(1);
         gtt_Ctrl_flag.User_all_parameter_reset_exe = OFF;
     }
     //サービスマンメニューリセット
     if (gtt_Ctrl_flag.Service_reset1_exe == ON)
     {
         memory_initialize_class(2);
         gtt_Ctrl_flag.Service_reset1_exe = OFF;
//--------- Phase8 & Phase24 by @Tny 2008/09/12 & 2008/10/17 --------
#if true
        gtt_Error_History.History_rec_index = 0;                    // 記録インデックスの初期化
        gtt_Error_History.Full_history_rec  = false;                // 全記録エリア使用フラグの初期化
        gtt_Error_History.Start_record      = false;                // 記録開始フラグの初期化
        gtt_Error_History.Record_identifier = ERROR_INFO_RENEWAL;   // 記録識別子のセット
        gb_Error_History_Write              = true;                 // エラー履歴テーブル保存の要求
#endif
//--------------------------------------------
     }
//--------- Phase24 by @Tny 2008/10/17 --------
#if true
     //オール初期化（ユーザ特殊パラメータ、サービスマンデータ、全ｃｈの電流、電圧、詳細データ）
     if (gtt_Ctrl_flag.Service_reset2_exe == ON)
     {
        memory_initialize_class(3);
        gtt_Ctrl_flag.Service_reset2_exe = OFF;
        gtt_Error_History.History_rec_index = 0;                    // 記録インデックスの初期化
        gtt_Error_History.Full_history_rec  = false;                // 全記録エリア使用フラグの初期化
        gtt_Error_History.Start_record      = false;                // 記録開始フラグの初期化
        gtt_Error_History.Record_identifier = ERROR_INFO_RENEWAL;   // 記録識別子のセット
        gb_Error_History_Write              = true;                 // エラー履歴テーブル保存の要求
     }
#endif
//--------------------------------------------

//--------- Phase8 by @Tny 2008/09/12 --------
#if true
    if((gus_Iif_BuiltIn_write)||(gb_Error_History_Write)){
        ch0_write_class(true);
        if(gus_Iif_BuiltIn_write)   gus_Iif_BuiltIn_write   = false; // IIF接続フラグ保存フラグのクリア
        if(gb_Error_History_Write)  gb_Error_History_Write  = false; // エラー履歴テーブル保存フラグのクリア
    }
#endif
//--------------------------------------------
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
    //<><><> ＩＩＦ　アナログ部シフト量の書き込み 2009.11.16 IIF NEW <><><>
    if (gtt_Ctrl_flag.Iif_analog_shift_memory == true)
    {
        iif_analog_shift_memory_class(1);
        gtt_Ctrl_flag.Iif_analog_shift_memory = false;
    }
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

//--------- BP4 Phase6 by @Tny 2009/01/27 ----
#if true
    if(gb_WeldCondNameWrite){
        ch0_write_class(true);
		gb_WeldCondNameWrite = false;	// 溶接条件名書き込み要求フラグ
    }
#endif
//--------------------------------------------
//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
	if(gb_LcdBrightWrite){ // ＬＣＤコントラスト値の記録要求有り？
        ch0_write_class(true);
		gb_LcdBrightWrite	= false;	// ＬＣＤコントラスト値の記録フラグ
	}
//-----------------------------------------------------------
     
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_memory_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｃｏｍ＿ｓｎｄ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      通信送信管理
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

void com_snd_manager(void)
{
     //pc_snd_class();
     rob_snd_class();
     //re_snd_class();

//----- Phase7 by @Tny 2008/09/10 -----
#if true
	if(ComuniPackRemo.Data.bRS422Connection){	// 回線は開いている？
//----- Phase13 by @Tny 2008/09/18 -----
#if false
        if(gb_Error_Display_Sending){   // エラー情報の送信要求がある？
            gb_Error_Display_Sending        = false;    // エラー情報送信要求フラグ：クリア
            gb_Error_blink                  = true;     // エラー点滅制御要求フラグ
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no = 0;       // 表示するブロック番号：全制御停止
            REMO_Send_CMD(0x23);
        }
#endif
//--------------------------------------------
    }
#endif
//--------------------------------------------
//----- Phase26 by @Tny 2008/10/23 -----
#if false	// true->false	BP4 Phase15 by @Tny 2009.02.25
    else{
        //if((gus_Initial_timer <= 0)&&(gb_Controller_UnConnect == false)&&(guc_Robot_connect_flag == false)){	// 208.11.27 by @Tny
        if((gus_Initial_timer <= 0)&&(gb_Controller_UnConnect == false)){	//2009.07.14
            if(gb_Ping_to_Controller == false){
                gb_Ping_to_Controller           = true; // コントローラ未接続確認実行フラグ
                gus_Controller_Connect_Timer    = 1000; // コントローラ接続確認タイマー：1sec
                REMO_Send_CMD(0x16);                    // 相互動作確認コマンドを送信
            }
            else{
                if(gus_Controller_Connect_Timer <= 0){ // 相互動作確認コマンド受信タイムアウト？
                    // 通信ケーブル断線
                    gtt_Ctrl_word.Sequence_ctrl_code    = ON;       // シーケンス完全停止要求
                    gub_System_err                      = ON;       // エラー扱い
                    gb_Controller_UnConnect             = true;     // コントローラ未接続確認フラグ：未接続
                    gb_Ping_to_Controller               = false;    // コントローラ未接続確認実行フラグ
                }
            }
        }
    }
#endif
//--------------------------------------------

//-------------------------------------------------------------
// 2019.09.04
//----------------------
#ifdef __NEWCOM_PROTOCOL
	if(gtt_Ctrl_flag.ComSend == true)	// 送信タイミングフラグ：100usec経過した
	{
		re_com_proc();
		gtt_Ctrl_flag.ComSend = false;	// 送信タイミングフラグ：クリア
	}
#endif
//-------------------------------------------------------------

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_com_snd_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

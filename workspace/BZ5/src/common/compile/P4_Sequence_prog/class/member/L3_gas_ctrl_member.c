//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｇａｓ＿ｃｔｒｌ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      ｇａｓ制御
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
void gas_ctrl_member()
{
     //if(gtt_Internal_pack.Data.bRS422Connection) //ロボット接続時有効
     if(gtt_Internal_pack.Data.bRS422Connection || ComuniPackRemo.Data.bRS422Connection || (gb_Controller_UnConnect)) //ロボット接続時有効 2007.12.07  コントローラ未接続短絡子有り時有効 Phase26 by @Tny 2008.10.23
     {
        //if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on)
        if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on || guc_Gas_on_off_flag == ON) //2007.12.07
        {
           //ガスチェックを９０秒後に自動ＯＦＦ 2008.09.08
           if (guc_Gas_on_off_flag == ON)
           {
               if (gtt_Ctrl_flag.Gas_limit_timer == OFF)
               {
                   gtt_Ctrl_flag.Gas_limit_timer = ON;
                   gtt_Ctrl_counter.Gas_limit_timer = GAS_LIMIT_TIME;
               } else if (gtt_Ctrl_counter.Gas_limit_timer <= 0) {
                   gtt_Ctrl_flag.Gas_limit_timer = OFF;
                   guc_Gas_on_off_flag = OFF;
                   guc_Sw_rewrite_check_flag = 2; //ＬＥＤを消すためにコールする。
                   guc_Gas_check_cancel_flag = true; //2008.10.06
               }
               if (guc_Sequence_mode != IDLING) //ガスチェック中に溶接になった場合ガスチェックをキャンセルする。2008.10.06
               {
                   gtt_Ctrl_flag.Gas_limit_timer = OFF;
                   guc_Gas_on_off_flag = OFF;
                   guc_Sw_rewrite_check_flag = 2; //ＬＥＤを消すためにコールする。
                   guc_Gas_check_cancel_flag = true; //2008.10.06
               }
           }
           gtt_Ctrl_word.Gas_ctrl_code = ON;
        } else {
           gtt_Ctrl_word.Gas_ctrl_code = OFF;
           gtt_Ctrl_flag.Gas_limit_timer = OFF; //2008.09.08
        }
     }
    return;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_gas_ctrl_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｅｒｒ＿ｌｅｖｅｌ２＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ＬＥＶＥＬ２エラー（ＭＧ＿ＯＦＦ→エラー解除→ＭＧ＿ＯＮ）
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
#include "custom.h"

unsigned int err_level2_class(void)
{
     unsigned char puc_Err_code;
     unsigned int  pui_Err_code;

     puc_Err_code = 0;       //2006.8.30 clear
     pui_Err_code = 0;       //2006.8.30 clear

     if(gtt_Ctrl_flag.Welder_init_execution == OFF) puc_Err_code = temp_err_member(puc_Err_code);               //温度異常
     puc_Err_code           = ts_err_member(puc_Err_code);                 //トーチスイッチ異常
     puc_Err_code           = second_current_err_member(puc_Err_code);     //二次過電流異常
     puc_Err_code           = arc_start_err_member(puc_Err_code);           //アークスタート異常 2007.1.19レベル２へ移行　2007.1.26移植追加
     if (puc_Err_code > 0)
     {
        pui_Err_code = ERR_LEVEL2_ADD_CODE | ((unsigned int)puc_Err_code & 0x00ff); //付加コード連結
        gtt_Ctrl_flag.Err_level2 = ON; //2008.11.17
     } else {
        pui_Err_code = ERR_LEVEL2_NON_CODE & ((unsigned int)puc_Err_code);          //付加コード削除
        gtt_Ctrl_flag.Err_level2 = OFF; //2008.11.17
     }
    
     return(pui_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_err_level2_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｅｒｒ＿ｌｅｖｅｌ１＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ＬＥＶＥＬ１エラー（トーチＳＷ解除）
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

unsigned int err_level1_class(void)
{
     unsigned char puc_Err_code;
     unsigned int  pui_Err_code;

     puc_Err_code = 0;       //2006.8.30 clear
     pui_Err_code = 0;       //2006.8.30 clear

     if (guc_Robot_connect_flag == true) //ロボット接続時のみ有効 2009.07.24
     {
         if(gtt_Ctrl_flag.Welder_init_execution == OFF) puc_Err_code = elrod_short_err_member(puc_Err_code); //電極短絡異常
     }
  // <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
  // 初期シーケンス待ち時間を経過した？
  if(guc_Init_wait_sequence <= 0){
	// Phase28 by Tny 2008.11.21
     if(gtt_Ctrl_flag.Welder_init_execution == OFF) puc_Err_code = gas_err_member(puc_Err_code);           //ガス減圧異常（一時停止１）
	// Phase28 by Tny 2008.11.21
     if(gtt_Ctrl_flag.Welder_init_execution == OFF) puc_Err_code = water_err_member(puc_Err_code);         //水回路異常（一時停止２）
     //puc_Err_code = arc_start_err_member(puc_Err_code);     //アークスタート異常 2007.1.19レベル２へ移行 2007.1.26移植削除
  }

     if (puc_Err_code > 0)
     {
        pui_Err_code = ERR_LEVEL1_ADD_CODE | ((unsigned int)puc_Err_code & 0x00ff); //付加コード連結
        gtt_Ctrl_flag.Err_level1 = ON; //2008.09.01
     } else {
        pui_Err_code = ERR_LEVEL1_NON_CODE & ((unsigned int)puc_Err_code);          //付加コード削除
        gtt_Ctrl_flag.Err_level1 = OFF; //2008.09.01
     }
     return(pui_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_err_level1_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

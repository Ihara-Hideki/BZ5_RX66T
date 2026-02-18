//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｅｒｒｏｒ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      エラー管理
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

void error_manager(void)
{

	 unsigned int  pui_Err_code0;	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
     unsigned int  pui_Err_code1;
     unsigned int  pui_Err_code2;
     unsigned int  pui_Err_code3;

     ubool          pub_System_err_bk; //2010.03.23

//----- Phase10 by @Tny 2008/09/16 -----
#if true
    ubool            bErrorCheck = false;
#endif
//--------------------------------------------

     pub_System_err_bk = gub_System_err; //2010.03.23

	 pui_Err_code0 = 0;      //2006.8.30 clear	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
     pui_Err_code1 = 0;      //2006.8.30 clear
     pui_Err_code2 = 0;      //2006.8.30 clear
     pui_Err_code3 = 0;      //2006.8.30 clear

#if true	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
	pui_Err_code0 = err_level0_class();
#else
     err_level0_class();
//2006.11.28 スティックだけ残す。
//2006.11.28 スティックだけ残す=>戻す
#endif
#if 1
	pui_Err_code1 = err_level1_class();
	pui_Err_code2 = err_level2_class();
	pui_Err_code3 = err_level3_class();
     

     if (pui_Err_code0 > 0 || pui_Err_code1 > 0 || pui_Err_code2 > 0 || pui_Err_code3 > 0)	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
     {
//-----------------------------------------------------------------------------------------------------------------------------------------------
// <NAVI Enhancements(Phase 1)> 2011.10.26 by @Tny
//
		gtt_Navi.b_Navi_Disp	= false;	// ナビ表示フラグ：非表示
//-----------------------------------------------------------------------------------------------------------------------------------------------
//----- Phase10 by @Tny 2008/09/16 -----
#if true
    if((pui_Err_code0 != gui_Err_code0) || (pui_Err_code1 != gui_Err_code1) || (pui_Err_code2 != gui_Err_code2) || (pui_Err_code3 != gui_Err_code3)){	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
        bErrorCheck = true;
    }
#endif
//--------------------------------------------
         gub_System_err = ON;
         if (pui_Err_code0 > 0){ gui_Err_code = pui_Err_code0; }	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
         if (pui_Err_code1 > 0){ gui_Err_code = pui_Err_code1; }
         if (pui_Err_code2 > 0){ gui_Err_code = pui_Err_code2; }
         if (pui_Err_code3 > 0){ gui_Err_code = pui_Err_code3; }
     } else {
         gub_System_err = OFF;
         
     }
//----- Phase10 by @Tny 2008/09/16 -----
#if true
    if((bErrorCheck) || (gub_System_err == OFF)){
    //----- Phase8 by @Tny 2008/09/12 -----
    #if true
        guc_Error_code = 0;

#if true	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
		if(pui_Err_code0 != 0){
			guc_Error_code = (unsigned char)(pui_Err_code0 & 0x00ff);  //エラーコード抽出
		}
		gtt_Ctrl_word = err_process_class(pui_Err_code0,gtt_Ctrl_word);            //エラー内容に応じた処理
#endif
        if(pui_Err_code1 != 0){
            guc_Error_code = (unsigned char)(pui_Err_code1 & 0x00ff);  //エラーコード抽出
        }
        gtt_Ctrl_word = err_process_class(pui_Err_code1,gtt_Ctrl_word);            //エラー内容に応じた処理
        if(pui_Err_code2 != 0){
            guc_Error_code = (unsigned char)(pui_Err_code2 & 0x00ff);  //エラーコード抽出
        }
        gtt_Ctrl_word = err_process_class(pui_Err_code2,gtt_Ctrl_word);            //エラー内容に応じた処理
        if(pui_Err_code3 != 0){
            guc_Error_code = (unsigned char)(pui_Err_code3 & 0x00ff);  //エラーコード抽出
        }
        gtt_Ctrl_word = err_process_class(pui_Err_code3,gtt_Ctrl_word);            //エラー内容に応じた処理
    #endif
    //--------------------------------------------
    }
    gui_Err_code0 = pui_Err_code0;	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
    gui_Err_code1 = pui_Err_code1;
    gui_Err_code2 = pui_Err_code2;
    gui_Err_code3 = pui_Err_code3;
#endif
//--------------------------------------------
#endif

    //<><><><> 2010.03.23 <><><>
    if (guc_Robot_connect_flag == true)
    {
        if (pub_System_err_bk == ON && gub_System_err == OFF)
        {
            guc_Robot_connect_one_shot_flag = OFF;
        }
    }
    //<><><><><><><><><><><><><>

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_error_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

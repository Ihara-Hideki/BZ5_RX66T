//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｅｒｒ＿ｌｅｖｅｌ０＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ＬＥＶＥＬ０エラー（警告のみ）
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

#if true	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
unsigned int err_level0_class(void)
{
	unsigned char puc_Err_code = 0;
	unsigned int  pui_Err_code = 0;

//	if(gb_IIF_Select){  // IIF接続を確認	※ＩＩＦ接続時のみスティックチェック結果の監視を行う。	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30			// ロボット接続時のチェックが必要のため常時監視  <EXTERNAL IIF NEW(Phase 12)> 2011.11.18
		puc_Err_code  = stick_err_member(puc_Err_code);           //スティックチェック
//	}

	if(puc_Err_code > 0){
		pui_Err_code = ERR_LEVEL0_ADD_CODE | ((unsigned int)puc_Err_code & 0x00ff); //付加コード連結
	}
	else{
		pui_Err_code = ERR_LEVEL0_NON_CODE & ((unsigned int)puc_Err_code);          //付加コード削除
	}
	return(pui_Err_code);
}
#else
void err_level0_class(void)
{
     stick_err_member();           //スティックチェック
     return;
}
#endif
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_err_level0_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//--------------------------------------------------------------------------
//
// 【ＣＯ２／ＭＡＧ溶接機<YD-400GZ3>】　サブ・モジュール部[SubModules.c]
//
//             Original : 2005-12-02(Fri) : H.Ihara & M.Tanigawa
//
// Copyright(C)2005 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//--------------------------------------------------------------------------
#define		__SUB_MODULES_PROG
#include    "custom.h"
/***
**  ID     = initDelay
**  name   = 指定時間待ち（初期化用）処理
**  func   = 指定時間待ち（初期化用）モジュール
**  called = void initDelay(int Time)
**  io     = Time		: int : 待ち時間（μ秒）
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2004/05/27 by 西川(R040301RTW-TAWERS)
**           2005/12/02 by 谷川まさや
***/
void initDelay(int Time)
{
	int Cnt;

	for(Cnt = (Time * 20) ; Cnt <= 0 ; --Cnt){ //2006.1.12 10->20変更
		WDG_Clear();
	}
return;
}
//------------------------
//  End of SubModules.c
//------------------------

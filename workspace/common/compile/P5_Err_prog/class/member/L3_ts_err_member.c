//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｔｓ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      トーチスイッチ異常
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

unsigned char ts_err_member(unsigned char xuc_Err_code)
{
    unsigned char puc_Err_code;

    puc_Err_code = xuc_Err_code;         //2006.9.8 現状の継承

//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
#if true
    if((gtt_Ctrl_flag.Welder_init_execution == ON)||((gb_IIF_Select == true)&&(gb_Iif_Input)&&(gb_Iif_First_Toch_sw)))
#else
    if (gtt_Ctrl_flag.Welder_init_execution == ON)
#endif
//-------------------------------------------------
    {
        if(gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == ON)
        {
           puc_Err_code = START_UP_SIGNAL_ERR;     //トーチスイッチ異常
        }
    }

    //<><><> 2009.12.18 エラーレベル１，２発生時ＴＳ再起動を促す処理 <><><>
    if (gtt_Ctrl_flag.Ts_on_err == ON && gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
    {
        if (gtt_Ctrl_flag.Ts_on_err_timer == OFF)
        {
            gtt_Ctrl_flag.Ts_on_err_timer = ON;
            gtt_Ctrl_counter.Ts_on_err_timer = 100; //500ms
        } else if (gtt_Ctrl_counter.Ts_on_err_timer <= 0) {
           puc_Err_code = START_UP_SIGNAL_ERR;     //トーチスイッチ異常
        }
    } else {
        gtt_Ctrl_flag.Ts_on_err_timer = OFF;
    }
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

    return(puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_ts_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

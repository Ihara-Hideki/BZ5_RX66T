//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｐｒｉｍａｒｙ＿ｖｏｌｔａｇｅ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      一次電圧異常
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

#define VP_ERROR 0

unsigned char primary_voltage_err_member(unsigned char xuc_Err_code)
{
    unsigned int  pui_Max,pui_Min;
    unsigned char puc_Err_code;

    pui_Max        = 0;                //2006.8.30 clear
    pui_Min        = 0;                //2006.8.30 clear
    puc_Err_code   = xuc_Err_code;        //2006.9.8 現状の継承

#if 0
    gtt_Vp.Counter++;
    gtt_Vp.Buffer = gtt_Vp.Buffer + (unsigned int)AD0DT4;
    if (gtt_Vp.Counter >= VP_AVG_COUNTER)
    {
        gtt_Vp.Result = (unsigned int)(gtt_Vp.Buffer / (unsigned int)gtt_Vp.Counter);
        gtt_Vp.Buffer  = 0;
        gtt_Vp.Counter = 0;
    }
#endif
//テーブルの読み込み切り替えが予想以上にかかるため、起動時DSW4をONにすると、E05がでる。
//理由：タイマは割り込みであるため、時間カウントは過ぎていくが、テーブルの読み込みに時間がかかると
//　　　ここにくることができず、gtt_Vp.Resultが0状態になる
//      よって、上記内容をタイマ割り込みの１ｍSカウンタ部に移動し、確実に取り込みができるようにする
	

    if((guc_Sequence_mode > PRE_FLOW) && (guc_Sequence_mode < AFTER_FLOW)) //溶接期間中の判定値をセット
    {
        pui_Max = VP_MAX_WEL;
        pui_Min = VP_MIN_WEL;
    } else {                                                             //待機中の判定値をセット
        pui_Max = VP_MAX_IDL;
        pui_Min = VP_MIN_IDL;
    }
#if VP_ERROR
#else
    gtt_Vp.Result = gtt_Vp.Result + gtt_Special_menu.ss_Service_data[S_LINE_VOLT_OFFSET]; //2009.04.09 
    if((gtt_Vp.Result > pui_Max) || (gtt_Vp.Result < pui_Min))
    {
        if(gtt_Ctrl_flag.Vp_err == OFF)
        {
           gtt_Ctrl_flag.Vp_err = ON;
           gtt_Ctrl_counter.Vp_err = VP_TIME;
	} else if(gtt_Ctrl_counter.Vp_err <= 0) {
          if(gtt_Vp.Result >= (pui_Max - 10))
          { 
             puc_Err_code = PRI_OVER_VOLTAGE_ERR;
          } //一次高電圧異常
          if(gtt_Vp.Result <= (pui_Min + 10))
          { 
             puc_Err_code = PRI_LOW_VOLTAGE_ERR;  
             gtt_Ctrl_flag.Pri_volt_err_com_delay_set_flag = ON; //2007.3.6追加 2007.3.13移植

             //電源ＯＦＦ時に温度異常の状態を記憶する。
             gus_Temp_err_set   =  gus_Temp_err_set_work; //2009.03.16

          } //一次低電圧異常
        }
    } else {
      gtt_Ctrl_flag.Vp_err = OFF;
    }
    return (puc_Err_code);
#endif
    return (puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_primary_voltage_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

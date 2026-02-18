//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ａｒｃ＿ｓｔａｒｔ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      アークスタート異常
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

unsigned char arc_start_err_member(unsigned char xuc_Err_code)
{
     unsigned char puc_Err_code;

     puc_Err_code = xuc_Err_code;         //2006.9.8 現状の継承

//<><><><> 本ファイルは2007.1.26ファイルごと移植<><><><><><><><><><>

     //<><><><><><><><><><> ロボット、ハンド共用2007.1.19 <><><><><><><><><><>
     if (gtt_Ctrl_flag.Arc_start_err1 == ON || gtt_Ctrl_flag.Arc_start_err2 == ON){   //ＤＳＰが検出する
         puc_Err_code = ARC_START_ERR;                                                //アークスタート異常
         gtt_Ctrl_flag.Arc_start_err_set = ON;
         gtt_Ctrl_flag.Arc_start_err1    = OFF;
         gtt_Ctrl_flag.Arc_start_err2    = OFF;
     } else {
         if (gtt_Ctrl_flag.Arc_start_err_set == ON)
         {
             if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == OFF)
             {
                 puc_Err_code = ERR_CLEAR;         //異常解除
                 gtt_Ctrl_flag.Arc_start_err_set = OFF;
             } else {
                 puc_Err_code = ARC_START_ERR;     //アークスタート異常
             }
         }
     }
     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



#if 0
     if (ComuniPack.Data.bRS422Connection == OFF)
     {
         //if (gtt_Ctrl_word.Welder_ctrl_code == ON && gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd == OFF)
         if (gtt_Ctrl_word.Welder_ctrl_code == ON && gtt_Fpga.Volt_result < VOLTAGE_DETECT_ERROR_LEVEL)  //2007.1.18変更
         {
             if(gtt_Ctrl_flag.Arc_start_err == OFF){
                gtt_Ctrl_flag.Arc_start_err = ON;
                gtt_Ctrl_counter.Arc_start_err = ARC_START_TIME;
             } else if(gtt_Ctrl_counter.Arc_start_err <= 0){
                puc_Err_code = ARC_START_ERR;                 //アークスタート異常
                gtt_Ctrl_flag.Arc_start_err_set = ON;
             }
         } else {
             if (gtt_Ctrl_flag.Arc_start_err_set == ON)
             {
                 if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == ON)
                 {
                     puc_Err_code = ARC_START_ERR;                 //アークスタート異常
                 } else {
                     gtt_Ctrl_flag.Arc_start_err = OFF;
                     gtt_Ctrl_flag.Arc_start_err_set = OFF;
                 }
             } else {
                     gtt_Ctrl_flag.Arc_start_err = OFF;
                     gtt_Ctrl_flag.Arc_start_err_set = OFF;
             }
         }
     } else {
         //<><><><><><><><><><> ロボット用に追加　2007.1.18 <><><><><><><><><><>
         if (gtt_Ctrl_word.Welder_ctrl_code == ON && gtt_Fpga.Volt_result < VOLTAGE_DETECT_ERROR_LEVEL)
         {
             if(gtt_Ctrl_flag.Arc_start_err == OFF){
                gtt_Ctrl_flag.Arc_start_err = ON;
                gtt_Ctrl_counter.Arc_start_err = ARC_START_TIME;
             } else if(gtt_Ctrl_counter.Arc_start_err <= 0){
                puc_Err_code = ARC_START_ERR;                 //アークスタート異常
             }
         } else {
           gtt_Ctrl_flag.Arc_start_err = OFF;
         }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
     }
#endif
     return(puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_arc_start_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

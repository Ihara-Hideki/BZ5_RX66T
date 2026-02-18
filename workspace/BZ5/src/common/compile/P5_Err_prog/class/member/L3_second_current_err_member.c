//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚“‚…‚ƒ‚‚‚„Q‚ƒ‚•‚’‚’‚…‚‚”Q‚…‚’‚’Q‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      “ñŸ‰ß“d—¬ˆÙí
//  yˆø”z
//      ‚È‚µ
//  y–ß‚è’lz
//      ‚È‚µ  
//  y”õlz
//      ‚È‚µ
//  yXV—š—ğz
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include "custom.h"

unsigned char second_current_err_member(unsigned char xuc_Err_code)
{
     unsigned char puc_Err_code;

     puc_Err_code = xuc_Err_code;         //2006.9.8 Œ»ó‚ÌŒp³

     if (gtt_Ctrl_flag.Second_currnt_err == ON){            //“ñŸ‰ß“d—¬ˆÙí‚Í‚c‚r‚o‚ªŒŸo‚·‚é
         puc_Err_code = SEC_OVER_CURRENT_ERR;      //“ñŸ‰ß“d—¬ˆÙí
         gtt_Ctrl_flag.Second_currnt_err_set = ON;
         gtt_Ctrl_flag.Second_currnt_err = OFF;
         gtt_Ctrl_counter.Second_currnt_err_timer = 500; //2008.12.04
     } else {
         if (gtt_Ctrl_flag.Second_currnt_err_set == ON)
         {
             //if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == OFF)
             if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == OFF && gtt_Ctrl_counter.Second_currnt_err_timer <= 0) //2008.12.04
             {
                 puc_Err_code = ERR_CLEAR;         //ˆÙí‰ğœ
                 gtt_Ctrl_flag.Second_currnt_err_set = OFF;
             } else {
                 puc_Err_code = SEC_OVER_CURRENT_ERR;      //“ñŸ‰ß“d—¬ˆÙí
             }
         }
     }
     
     return(puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_second_current_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

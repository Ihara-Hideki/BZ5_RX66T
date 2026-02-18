//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚—‚‚”‚…‚’Q‚…‚’‚’Q‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      …‰ñ˜HˆÙíiˆê’â~‚Qj
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

unsigned char water_err_member(unsigned char xuc_Err_code)
{
     unsigned char puc_Err_code;

     puc_Err_code = xuc_Err_code;         //2006.9.8 Œ»ó‚ÌŒp³

     if (gtt_Internal_pack.Data.In.Outside2 == ON){
         if(gtt_Ctrl_flag.Water_err == OFF){
            gtt_Ctrl_flag.Water_err = ON;
            gtt_Ctrl_counter.Water_err = WATER_TIME;
         } else if(gtt_Ctrl_counter.Water_err <= 0){
           puc_Err_code = OUTSIDE_STOP2_ERR;         //ŠO•”ˆê’â~‚Q
         }
     } else {
       gtt_Ctrl_flag.Water_err = OFF;
     }
     
     return(puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_water_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

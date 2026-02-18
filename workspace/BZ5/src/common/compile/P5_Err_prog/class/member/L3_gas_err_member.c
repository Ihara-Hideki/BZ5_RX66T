//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚‡‚‚“Q‚…‚’‚’Q‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      ƒKƒXŒ¸ˆ³ˆÙíiˆê’â~‚Pj
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

unsigned char gas_err_member(unsigned char xuc_Err_code)
{
     unsigned char puc_Err_code;

     puc_Err_code = xuc_Err_code;         //2006.9.8 Œ»ó‚ÌŒp³

     if (gtt_Internal_pack.Data.In.Outside1 == ON){
         if(gtt_Ctrl_flag.Gas_err == OFF){
            gtt_Ctrl_flag.Gas_err = ON;
            gtt_Ctrl_counter.Gas_err = GAS_TIME;
         } else if(gtt_Ctrl_counter.Gas_err <= 0){
           puc_Err_code = OUTSIDE_STOP1_ERR;         //ŠO•”ˆê’â~‚P
         }
     } else {
       gtt_Ctrl_flag.Gas_err = OFF;
     }
     
     return(puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_gas_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

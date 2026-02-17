//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚…‚‚‡Q‚…‚’‚’Q‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      ”ñí’â~
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

unsigned char emg_err_member(unsigned char xuc_Err_code)
{
     unsigned char puc_Err_code;

     puc_Err_code = xuc_Err_code;         //2006.9.8 Œ»ó‚ÌŒp³
//2007.2.9@”ñí’â~A”ñí’â~‚Q—¼•û‚Ì”»•Ê‚ğs‚¤‚æ‚¤‚É‚·‚é
#if 1
     if (gtt_Internal_pack.Data.In.Emergency == ON || gtt_Internal_pack.Data.In.Emergency2 == ON){
         if(gtt_Ctrl_flag.Emg_err == OFF){
            gtt_Ctrl_flag.Emg_err = ON;
            gtt_Ctrl_counter.Emg_err = EMG_TIME;
         } else if(gtt_Ctrl_counter.Emg_err <= 0){
           if (gtt_Internal_pack.Data.In.Emergency == ON)
           {
                puc_Err_code = EMERGENCY_STOP_ERR;      //”ñí’â~
           }
           if (gtt_Internal_pack.Data.In.Emergency2 == ON)
           {
                puc_Err_code = EMERGENCY2_STOP_ERR;     //”ñí’â~2
           }
         }
     } else {
       gtt_Ctrl_flag.Emg_err = OFF;
     }
#else
     if (gtt_Internal_pack.Data.In.Emergency == ON){
         if(gtt_Ctrl_flag.Emg_err == OFF){
            gtt_Ctrl_flag.Emg_err = ON;
            gtt_Ctrl_counter.Emg_err = EMG_TIME;
         } else if(gtt_Ctrl_counter.Emg_err <= 0){
           puc_Err_code = EMERGENCY_STOP_ERR;      //”ñí’â~
         }
     } else {
       gtt_Ctrl_flag.Emg_err = OFF;
     }
#endif
     return(puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_emg_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

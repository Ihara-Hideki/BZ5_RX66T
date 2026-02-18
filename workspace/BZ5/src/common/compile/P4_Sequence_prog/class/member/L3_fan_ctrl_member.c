//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚†‚‚Q‚ƒ‚”‚’‚ŒQ‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      ‚†‚‚§Œä
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
#include  "custom.h"
void fan_ctrl_member(unsigned char xuc_Sequence_mode)
{
     unsigned char puc_Sequence_mode;

     puc_Sequence_mode = xuc_Sequence_mode;

//----- Phase5 by @Tny 2008/09/09 -----
#if true
    if(puc_Sequence_mode > IDLING){
    //if(puc_Sequence_mode > IDLING || gtt_Ctrl_flag.Temp_err == ON){ //2008.11.20
        gtt_Ctrl_flag.Fan_off           = OFF;
        gtt_Ctrl_word.Fan_ctrl_code     = ON;
        guc_R8_control.Bit1Sw.R8_Fan    = true;
        //FAN2                            = ON;   // Phase17 by @Tny 2008/09/24 2019.05.30 ihara del
	MtoC[FAN2]			= 1;	//2019.06.03
    }
    else{
//------ Phase9 by @Tny 2008/09/12 ------
#if true
      if (gtt_Ctrl_flag.Temp_err == OFF){ //2008.11.20
        if(gtt_Ctrl_flag.Fan_off == OFF){
            gtt_Ctrl_flag.Fan_off       = ON;
            gtt_Ctrl_counter.Fan_off    = FAN_OFF_TIME;
            gtt_Ctrl_counter.Fan_A_off  = FAN_A_OFF_TIME;
        }
        else{
            if(gtt_Ctrl_counter.Fan_A_off <= 0){
                gtt_Ctrl_word.Fan_ctrl_code     = OFF;
            }
            if(gtt_Ctrl_counter.Fan_off <= 0){
                guc_R8_control.Bit1Sw.R8_Fan    = false;
                //FAN2                            = OFF;   // Phase17 by @Tny 2008/09/24 2019.05.30 ihara del
		MtoC[FAN2]			= 0;	//2019.06.03
            }
        }
      } else { //2008.11.20
	    gtt_Ctrl_word.Fan_ctrl_code     = ON;
        guc_R8_control.Bit1Sw.R8_Fan    = true;
        //FAN2                            = ON; //2019.05.30 ihara del
	MtoC[FAN2]			= 1;	//2019.06.03
        gtt_Ctrl_counter.Fan_off        = FAN_OFF_TIME; //‰·“xˆÙí”­¶‚Å‚V•ª‚ğÄƒZƒbƒg‚·‚é@2012.02.08
      }
#endif
//---------------------------------------------------------------------
     }
#else
     if (puc_Sequence_mode > IDLING)
     {
         gtt_Ctrl_flag.Fan_off = OFF;
         gtt_Ctrl_word.Fan_ctrl_code = ON;
     } else {
         if (gtt_Ctrl_flag.Fan_off == OFF)
         {
             gtt_Ctrl_flag.Fan_off = ON;
             gtt_Ctrl_counter.Fan_off = FAN_OFF_TIME;
         } else if (gtt_Ctrl_counter.Fan_off == 0) {
             gtt_Ctrl_word.Fan_ctrl_code = OFF;
         }
     }
#endif
//--------------------------------------------
     return;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_fan_ctrl_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚‚•‚”‚‚•‚”Q‚—‚…‚Œ‚„‚…‚’Q‚ƒ‚”‚’‚ŒQ‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      —nÚ“dŒ¹“®ìw—ß
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

void output_welder_ctrl_member(Bit16 xtt_Ctrl_word , Bit16 xtt_Ctrl_word_bkup)
{
     unsigned short int pui_Welder_ctrl;

     pui_Welder_ctrl = 0x0000;         //2006.8.30 clear

     if (xtt_Ctrl_word.Welder_ctrl_code != xtt_Ctrl_word_bkup.Welder_ctrl_code) //‘O‰ñ‚Ìó‘Ô‚Æ”äŠr
     {
         if (xtt_Ctrl_word.Welder_ctrl_code)      //—nÚ“dŒ¹§ŒäƒR[ƒhƒ`ƒFƒbƒN
         {
             //—nÚ“dŒ¹‹N“®
             pui_Welder_ctrl = 0x0001;
         } else {
             //—nÚ“dŒ¹’â~
             pui_Welder_ctrl = 0x0000;
         }

         if (gtt_Ctrl_flag.Burn_back2 == true) //‘æ‚Qƒo[ƒ“ƒoƒbƒN—L‚è–³‚µ‚ğ‚c‚r‚o‚É“`‚¦‚éˆ— 2008.12.11
         {
             pui_Welder_ctrl = pui_Welder_ctrl | 0x0080;
         } else {
             pui_Welder_ctrl = pui_Welder_ctrl & 0x007f;
         }


	 //IMJTOCR4  = 0x07; //2006.2.15 Š„‹Ö@ihara     
         //hpiWrite( hpicmdOUTWLDMOV , &pui_Welder_ctrl);   //DSP‚É‘—M 2019.04.02 del ihara
	 //IMJTOCR4  = 0x05; //2006.2.9 Š„‹–@ihara     
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_output_welder_ctrl_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

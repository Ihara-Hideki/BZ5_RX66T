//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚‰‚‚‚•‚”Q‚’‚WQ‚ƒ‚Œ‚‚“‚“
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚Q
//  y‹@”\à–¾z
//      ‚q‚W“ü—Í
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

void input_r8_class(void)
{
//<><><><><><>–{ƒtƒ@ƒCƒ‹‚Í2007.1.26ƒtƒ@ƒCƒ‹‚²‚ÆˆÚA<><><><><><><><>

     unsigned long pul_Work; //2007.1.18 ’Ç‰Á


     if (gtt_Ctrl_flag.R8_rcv == ON) //‚q‚W‚©‚ç‚ÌóMŠ®—¹‚©
     {
        gtt_internal_r8.Ex_data      = gtt_rcv_r8.Data.Ex_data;
        //gtt_internal_r8.Sp_data      = gtt_rcv_r8.Data.Sp_data;
        gtt_internal_r8.Sp_data.b0   = gtt_rcv_r8.Data.Sp_data.b0;
        gtt_internal_r8.Sp_data.b1   = gtt_rcv_r8.Data.Sp_data.b1;
        gtt_internal_r8.Sp_data.b2   = gtt_rcv_r8.Data.Sp_data.b2;
        gtt_internal_r8.Sp_data.b3   = gtt_rcv_r8.Data.Sp_data.b3;
        gtt_internal_r8.Sp_data.b4   = gtt_rcv_r8.Data.Sp_data.b4;
        gtt_internal_r8.Sp_data.b5   = gtt_rcv_r8.Data.Sp_data.b5;

        gtt_internal_r8.Pri_curr_fb1_work = gtt_internal_r8.Pri_curr_fb1_work + (unsigned long)gtt_rcv_r8.Data.Pri_curr_fb1;
        gtt_internal_r8.Pri_curr_fb2_work = gtt_internal_r8.Pri_curr_fb2_work + (unsigned long)gtt_rcv_r8.Data.Pri_curr_fb2;
        gtt_internal_r8.Sum_counter++;
        if (gtt_internal_r8.Sum_counter >= PRI_CURR_FB_COUNTER)
        {
            //gtt_internal_r8.Pri_curr_fb1 = (unsigned short)(gtt_internal_r8.Pri_curr_fb1_work / (unsigned long)gtt_internal_r8.Sum_counter); 2007.1.18íœ
            pul_Work = (unsigned long)(gtt_internal_r8.Pri_curr_fb1_work / (unsigned long)gtt_internal_r8.Sum_counter); //2007.1.18’Ç‰Á
            //pul_Work = (unsigned long)(gtt_internal_r8.Pri_curr_fb2_work / (unsigned long)gtt_internal_r8.Sum_counter); //2007.1.18’Ç‰Á
            //gtt_internal_r8.Pri_curr_fb1 = (unsigned short)((pul_Work * 375) / 1024); //2007.1.18’Ç‰Á 2007.1.25íœ
            gtt_internal_r8.Pri_curr_fb1 = (unsigned short)((pul_Work * 750) / 1024); //2007.1.18’Ç‰Á@2007.1.25•ÏX

            //gtt_internal_r8.Pri_curr_fb2 = (unsigned short)(gtt_internal_r8.Pri_curr_fb2_work / (unsigned long)gtt_internal_r8.Sum_counter);
            gtt_internal_r8.Pri_curr_fb1_work = 0;
            gtt_internal_r8.Pri_curr_fb2_work = 0;
            gtt_internal_r8.Sum_counter       = 0;
        }
       
        //gtt_internal_r8.Pri_curr_fb1 = gtt_rcv_r8.Data.Pri_curr_fb1;
        //gtt_internal_r8.Pri_curr_fb2 = gtt_rcv_r8.Data.Pri_curr_fb2;
        gtt_Ctrl_flag.R8_rcv = OFF;

        gtt_internal_r8.Com_check = OFF;  //‚q‚W‚Æ‚Ì’ÊM‚ª³í‚©‚Ç‚¤‚©‚ğƒ`ƒFƒbƒN‚·‚éB’ÊM‚n‚j‚È‚Ì‚Å‰ğœ‚·‚éB
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_input_r8_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

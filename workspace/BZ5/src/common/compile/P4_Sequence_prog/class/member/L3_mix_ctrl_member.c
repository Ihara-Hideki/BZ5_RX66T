//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚‚‰‚˜Q‚ƒ‚”‚’‚ŒQ‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      ‚l‚h‚wo—Í‚Ì§Œä
//  yˆø”z
//      ‚È‚µ
//  y–ß‚è’lz
//      ‚È‚µ  
//  y”õlz
//      ‚È‚µ
//  yXV—š—ğz
//      2009.02.17  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
void mix_ctrl_member()
{
      if (gtt_Ctrl_flag.Mix_wave_current_time == OFF)
      {
         gtt_Ctrl_flag.Mix_wave_current_time = ON;
         gtt_Ctrl_flag.Mix_condition_time_set = OFF;
         gtt_Ctrl_flag.Mix_condition_change = OFF;
      } else { 
         if (gtt_Ctrl_flag.Mix_condition_change == OFF)
         {
             //LED4 = ON;//Œğ—¬o—Í
             //if (gtt_Internal_pack.Data.In.ucMixFreq <= 100) //2009.03.31
             if (gtt_Internal_pack.Data.In.ucMixFreq <= 40) //2009.07.24 4Hz
             {
                 _union.Nrm.CalParm[65 - 1].c = 1; //2009.02.18
             } else {
                 _union.Nrm.CalParm[65 - 1].c = 2; //2009.03.31
             }
             gtt_Ctrl_flag.Hpi_control = true; //2009.02.18
             
         } else {
             //LED4 = OFF;//’¼—¬o—Í
             //if (gtt_Internal_pack.Data.In.ucMixFreq <= 100) //2009.03.31
             if (gtt_Internal_pack.Data.In.ucMixFreq <= 40) //2009.07.24 4Hz
             {
                 _union.Nrm.CalParm[65 - 1].c = 0; //2009.02.18
             } else {
                 _union.Nrm.CalParm[65 - 1].c = 2; //2009.03.31
             }
             gtt_Ctrl_flag.Hpi_control = true; //2009.02.18
         }
         if (gtt_Ctrl_flag.Mix_condition_time_set == OFF)
         {
             gtt_Ctrl_counter.Mix_frequence_time = gtt_Ctrl_counter.Mix_frequence_set_time;
             gtt_Ctrl_counter.Mix_B_condition_time = gtt_Ctrl_counter.Mix_B_condition_set_time;

             //gtt_Ctrl_counter.Mix_frequence_time = (unsigned long)((float)gtt_Ctrl_counter.Mix_frequence_time * 0.95);        //2009.07.24 ’x‚ê‚ğl—¶‚µ‚X‚T“‚ÌŠÔ‚É‚·‚é
             //gtt_Ctrl_counter.Mix_B_condition_time = (unsigned long)((float)gtt_Ctrl_counter.Mix_B_condition_time * 0.95);    //2009.07.24 ’x‚ê‚ğl—¶‚µ‚X‚T“‚ÌŠÔ‚É‚·‚é

             gtt_Ctrl_flag.Mix_condition_time_set = ON;
         } else {
             if (gtt_Ctrl_counter.Mix_B_condition_time <= 0)
             {
                 gtt_Ctrl_flag.Mix_condition_change = ON;
             }
             if (gtt_Ctrl_counter.Mix_frequence_time <= 0)
             {
                 gtt_Ctrl_flag.Mix_condition_change = OFF;
                 gtt_Ctrl_flag.Mix_condition_time_set = OFF;
             }
          }
      }
     
    return;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_mix_ctrl_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ａｃ＿ｆｒｅｑｕｅｎｃｙ＿ｌｉｍｉｔ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      ＡＣ周波数の制御
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2010.01.07  H.Ihara
//
//            Copyright(C)2010 Panasonic Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
#define AC_DOWN_CURRENT          300
#define AC_UP_CURRENT            400
#define AC_DOWN_LIMIT_FREQ       200
#define AC_UP_LIMIT_FREQ         400
#define AC_LINE_K               -2.0
float ac_frequency_limit_member(short freq)
{
      short pss_Freq_work;
      float pf_Calc_freq_work;
      short pss_Curr_work;
      float pf_Ac_frequency;
      short current;
      short pss_Current_work[5];
      short pss_Max_current;
      unsigned char puc_Index;

      pss_Freq_work = freq;
 
      pss_Current_work[0] = gtt_Internal_pack.Data.In.usWeldingInitCurr; //初期電流
      pss_Current_work[1] = gtt_Internal_pack.Data.In.usWeldingCurr;     //本電流
      pss_Current_work[2] = gtt_Internal_pack.Data.In.usWeldingCratCurr; //クレータ電流
      pss_Current_work[3] = gtt_Internal_pack.Data.In.usIP;              //パルス電流
      pss_Current_work[4] = 0;                                           //ダミー

      
      //設定電流の最大値の判別
      if (guc_Pulse_mode_data == 0) //パルス無
      {
         if (guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) //クレータ有
         {
             pss_Max_current = 0;
             for (puc_Index = 0 ; puc_Index <= 2 ; puc_Index++)
             {
                  if (pss_Current_work[puc_Index] > pss_Max_current)
                  {
                      pss_Max_current = pss_Current_work[puc_Index];
                  }
             }
             current = pss_Max_current;
         } else {                                                            //クレータ無
             current = pss_Current_work[1]; //本電流
         }
      } else {                      //パルス有
         if (guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) //クレータ有
         {
             pss_Max_current = 0;
             for (puc_Index = 0 ; puc_Index <= 3 ; puc_Index++)
             {
                  if (pss_Current_work[puc_Index] > pss_Max_current)
                  {
                      pss_Max_current = pss_Current_work[puc_Index];
                  }
             }
             current = pss_Max_current;
         } else {                                                           //クレータ無
             current = pss_Current_work[1]; //本電流
             if (pss_Current_work[3] > pss_Current_work[1])
             {
                 current = pss_Current_work[3]; //パルス電流
             }
         }
      }


      if (current > AC_DOWN_CURRENT)   //電流指令値が３００Ａ以上
      {
          if (current < AC_UP_CURRENT) //電流指令値が４００Ａ未満
          {
              if (freq > AC_DOWN_LIMIT_FREQ) //周波数が２００Ｈｚ以上
              {
                  pf_Calc_freq_work = AC_LINE_K * (current - AC_DOWN_CURRENT) + AC_UP_LIMIT_FREQ;
                  if (freq > pf_Calc_freq_work)
                  {
                      pss_Freq_work = pf_Calc_freq_work;
                  }
              }
          } else {                     //電流指令値が４００Ａ以上
              if (freq >= AC_DOWN_LIMIT_FREQ)
              {
                  pss_Freq_work = AC_DOWN_LIMIT_FREQ;
              }
          }
      }

      pf_Ac_frequency = pss_Freq_work;


      return(pf_Ac_frequency);
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_ac_frequency_limit_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

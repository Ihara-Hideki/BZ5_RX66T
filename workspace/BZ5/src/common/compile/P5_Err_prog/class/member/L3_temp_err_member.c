//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｔｅｍｐ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      温度異常
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

unsigned char temp_err_member(unsigned char xuc_Err_code)
{
     unsigned char puc_Err_code;

     puc_Err_code = xuc_Err_code;         //2006.9.8 現状の継承
     if (gtt_Internal_pack.Data.In.Temp == ON){
     //if (gtt_Dsw.Sw.No5 == ON){
         if(gtt_Ctrl_flag.Temp_err == OFF){
            gtt_Ctrl_flag.Temp_err = ON;
            gtt_Ctrl_flag.Temp_err_set = OFF; //2009.03.04
            gtt_Ctrl_counter.Temp_err = THP_TIME;
         } else if(gtt_Ctrl_counter.Temp_err <= 0){
           puc_Err_code = ABNORMAL_TEMP_ERR;         //温度異常
           if (gtt_Ctrl_flag.Temp_err_set == OFF && gus_Temp_err_set_work  == OFF) //2009.03.04
           {
			   uchar   i,Data[10];
               gtt_Ctrl_flag.Temp_err_set = ON; //2009.03.04
               gus_Temp_err_set   = ON;
               gus_Temp_err_set_work   = ON;
               I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
               gsc_Temp_err_year  = (((Data[0] & 0xf0) >> 4) * 10) + (Data[0] & 0x0f);
               gsc_Temp_err_month = (((Data[1] & 0x10) >> 4) * 10) + (Data[1] & 0x0f);
               gsc_Temp_err_day   = (((Data[2] & 0x30) >> 4) * 10) + (Data[2] & 0x0f);
               gsc_Temp_err_hour  = (((Data[4] & 0x30) >> 4) * 10) + (Data[4] & 0x0f);
               gsc_Temp_err_mini  = (((Data[5] & 0x70) >> 4) * 10) + (Data[5] & 0x0f);
               gsc_Temp_err_year_work   = gsc_Temp_err_year;
               gsc_Temp_err_month_work  = gsc_Temp_err_month;
               gsc_Temp_err_day_work    = gsc_Temp_err_day;
               gsc_Temp_err_hour_work   = gsc_Temp_err_hour;
               gsc_Temp_err_mini_work   = gsc_Temp_err_mini;
           }
         }
     } else {
        gtt_Ctrl_flag.Temp_err = OFF;
     }
      if (gus_Temp_err_set_work  == ON)
      {
		uchar   i,Data[10];
        if(Timer._300m != gtt_Ctrl_counter.Backup_300m) //2009.12.17
        {
           I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
           gtt_Ctrl_counter.Backup_300m = Timer._300m;
           gsc_Now_year  = (((Data[0] & 0xf0) >> 4) * 10) + (Data[0] & 0x0f);
           gsc_Now_month = (((Data[1] & 0x10) >> 4) * 10) + (Data[1] & 0x0f);
           gsc_Now_day   = (((Data[2] & 0x30) >> 4) * 10) + (Data[2] & 0x0f);
           gsc_Now_hour  = (((Data[4] & 0x30) >> 4) * 10) + (Data[4] & 0x0f);
           gsc_Now_mini  = (((Data[5] & 0x70) >> 4) * 10) + (Data[5] & 0x0f);
        }
        if (gsc_Temp_err_hour_work > gsc_Now_hour)
        {
//-------------------------------------------------------------
// 経過時間算出式の不具合対応		2011.09.01 by @Tny
//
#if true
           short work;
           work = (short)((short)((short)((short)gsc_Now_hour + 24)*60 + (short)gsc_Now_mini) -  (short)((short)gsc_Temp_err_hour_work * 60 + (short)gsc_Temp_err_mini_work));
#else
           char work;
           work = ((gsc_Now_hour + 24)*60 + gsc_Now_mini) -  (gsc_Temp_err_hour_work * 60 + gsc_Temp_err_mini_work);
#endif
//-------------------------------------------------------------
           if (work < 6)
           {
               if ((gsc_Temp_err_day_work - gsc_Now_day) != 0)
               {
                   if ((gsc_Temp_err_day_work - gsc_Now_day) == -1) {
                       puc_Err_code = ABNORMAL_TEMP_ERR;         //温度異常
                   } else { //月替わりはチェックしない。
                       gtt_Ctrl_flag.Temp_err = OFF;
                       gus_Temp_err_set_work  = OFF;
                       puc_Err_code = ERR_CLEAR; //異常解除
                   }
               } else {
                 gtt_Ctrl_flag.Temp_err = OFF;
                 gus_Temp_err_set_work   = OFF;
                 puc_Err_code = ERR_CLEAR; //異常解除
               }
#if 0
               else if ((gsc_Temp_err_month - gsc_Now_month) != 0) {
                   gtt_Ctrl_flag.Temp_err = OFF;
                   gus_Temp_err_set   = OFF;
                   puc_Err_code = ERR_CLEAR; //異常解除
               } else if ((gsc_Temp_err_year - gsc_Now_year) != 0) {
                   gtt_Ctrl_flag.Temp_err = OFF;
                   gus_Temp_err_set   = OFF;
                   puc_Err_code = ERR_CLEAR; //異常解除
               }
#endif
           } else {
               gtt_Ctrl_flag.Temp_err = OFF;
               gus_Temp_err_set_work   = OFF;
               puc_Err_code = ERR_CLEAR; //異常解除
           } 
        } else {
//-------------------------------------------------------------
// 経過時間算出式の不具合対応		2011.09.01 by @Tny
//
#if true
           short work;
           work = (short)((short)((short)gsc_Now_hour * 60 + (short)gsc_Now_mini) -  (short)((short)gsc_Temp_err_hour_work * 60 + (short)gsc_Temp_err_mini_work));
#else
           char work;
           work = (gsc_Now_hour * 60 + gsc_Now_mini) -  (gsc_Temp_err_hour_work * 60 + gsc_Temp_err_mini_work);
#endif
//-------------------------------------------------------------
           if (work < 6)
           {
               if ((gsc_Temp_err_day_work - gsc_Now_day) != 0)
               {
                   gtt_Ctrl_flag.Temp_err = OFF;
                   gus_Temp_err_set_work   = OFF;
                   puc_Err_code = ERR_CLEAR; //異常解除
               } else if ((gsc_Temp_err_month_work - gsc_Now_month) != 0) {
                   gtt_Ctrl_flag.Temp_err = OFF;
                   gus_Temp_err_set_work   = OFF;
                   puc_Err_code = ERR_CLEAR; //異常解除
               } else if ((gsc_Temp_err_year_work - gsc_Now_year) != 0) {
                   gtt_Ctrl_flag.Temp_err = OFF;
                   gus_Temp_err_set_work   = OFF;
                   puc_Err_code = ERR_CLEAR; //異常解除
               } else {
                 puc_Err_code = ABNORMAL_TEMP_ERR;         //温度異常
               }
           } else {
               gtt_Ctrl_flag.Temp_err = OFF;
               gus_Temp_err_set_work   = OFF;
               puc_Err_code = ERR_CLEAR; //異常解除
           } 
        }
      } else {
        gus_Temp_err_set_work   = OFF;
        puc_Err_code = ERR_CLEAR; //異常解除
      }

     //if (gtt_Dsw.Sw.No4 == ON) //実験　電源を落とすタイミングで温度異常の有無を記憶
     //{
      //gus_Temp_err_set   =  gus_Temp_err_set_work;
     //}



#if 0
       if (gtt_Ctrl_counter.Temp_err_set <= 0) //2009.03.04
       {
           gtt_Ctrl_flag.Temp_err = OFF;
           gus_Temp_err_set_counter = 0;
       } else {
           puc_Err_code = ABNORMAL_TEMP_ERR;         //温度異常
       }
       
#endif

#if 0
     if (gtt_Internal_pack.Data.In.Temp == ON){
         if(gtt_Ctrl_flag.Temp_err == OFF){
            gtt_Ctrl_flag.Temp_err = ON;
            gtt_Ctrl_counter.Temp_err = THP_TIME;
         } else if(gtt_Ctrl_counter.Temp_err <= 0){
           puc_Err_code = ABNORMAL_TEMP_ERR;         //温度異常
         }
     } else {
       gtt_Ctrl_flag.Temp_err = OFF;
     }

#endif


   //}
     
     return(puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_temp_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

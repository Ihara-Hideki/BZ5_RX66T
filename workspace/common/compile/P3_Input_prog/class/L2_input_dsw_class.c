//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//Å@Åyä÷êîñºÅz
//Å@Å@Å@ÇâÇéÇêÇïÇîÅQÇÑÇìÇóÅQÇÉÇåÇÅÇìÇì
//Å@Åyä÷êîÉåÉxÉãÅz
//Å@Å@Å@ÇkÇdÇuÇdÇkÅFÇQ
//  Åyã@î\ê‡ñæÅz
//      ÇcÇrÇvì¸óÕ
//  Åyà¯êîÅz
//      Ç»Çµ
//  ÅyñﬂÇËílÅz
//      Ç»Çµ  
//  ÅyîıçlÅz
//      Ç»Çµ
//  ÅyçXêVóöóÅz
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

void input_dsw_class(void)
{
     unsigned char puc_Err_count;
     unsigned char puc_Set_on_count;
     unsigned char puc_Retry_count;
     unsigned char puc_Set_on_flag;
     unsigned int  pui_Dsw_work;
     unsigned int  pui_Dsw_work_bkup;

     // dsw  15:DSW2_8 14:DSW2_7 13:DSW2_6 12:DSW2_5 11:DSW2_4 10:DSW2_3 9:DSW2_2 8:DSW2_1 
     //       7:DSW1_8  6:DSW1_7  5:DSW1_6  4:DSW1_5  3:DSW1_4  2:DSW1_3 1:DSW1_2 0:DSW1_1

     puc_Err_count     = 0;
     puc_Set_on_count  = 0;
     puc_Retry_count   = 0;
     pui_Dsw_work_bkup = 0x0000;

     while (1)
     {
         //<><><><><> ÇcÇrÇvÇÃì«Ç›çûÇ› <><><><><>
         pui_Dsw_work = 0x0000;
         puc_Set_on_flag = 0;
         //ÇcÇrÇvÇPÅQÇPÇ∆ÇcÇrÇvÇQÅQÇPÉ`ÉFÉbÉN
         if (AD0DT7 >= ON_ON_DWLIMIT && AD0DT7 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0101;
             puc_Set_on_flag |= 0x01;
         }
         if (AD0DT7 >= OFF_ON_DWLIMIT && AD0DT7 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0100;
             puc_Set_on_flag |= 0x01;
         }
         if (AD0DT7 >= ON_OFF_DWLIMIT && AD0DT7 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0001;
             puc_Set_on_flag |= 0x01;
         }
         if (AD0DT7 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x01;
         }
         //ÇcÇrÇvÇPÅQÇQÇ∆ÇcÇrÇvÇQÅQÇQÉ`ÉFÉbÉN
         if (AD0DT8 >= ON_ON_DWLIMIT && AD0DT8 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0202;
             puc_Set_on_flag |= 0x02;
         }
         if (AD0DT8 >= OFF_ON_DWLIMIT && AD0DT8 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0200;
             puc_Set_on_flag |= 0x02;
         }
         if (AD0DT8 >= ON_OFF_DWLIMIT && AD0DT8 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0002;
             puc_Set_on_flag |= 0x02;
         }
         if (AD0DT8 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x02;
         }
         //ÇcÇrÇvÇPÅQÇRÇ∆ÇcÇrÇvÇQÅQÇRÉ`ÉFÉbÉN
         if (AD0DT9 >= ON_ON_DWLIMIT && AD0DT9 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0404;
             puc_Set_on_flag |= 0x04;
         }
         if (AD0DT9 >= OFF_ON_DWLIMIT && AD0DT9 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0400;
             puc_Set_on_flag |= 0x04;
         }
         if (AD0DT9 >= ON_OFF_DWLIMIT && AD0DT9 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0004;
             puc_Set_on_flag |= 0x04;
         }
         if (AD0DT9 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x04;
         }
         //ÇcÇrÇvÇPÅQÇSÇ∆ÇcÇrÇvÇQÅQÇSÉ`ÉFÉbÉN
         if (AD0DT10 >= ON_ON_DWLIMIT && AD0DT10 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0808;
             puc_Set_on_flag |= 0x08;
         }
         if (AD0DT10 >= OFF_ON_DWLIMIT && AD0DT10 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0800;
             puc_Set_on_flag |= 0x08;
         }
         if (AD0DT10 >= ON_OFF_DWLIMIT && AD0DT10 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0008;
             puc_Set_on_flag |= 0x08;
         }
         if (AD0DT10 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x08;
         }
         //ÇcÇrÇvÇPÅQÇTÇ∆ÇcÇrÇvÇQÅQÇTÉ`ÉFÉbÉN
         if (AD0DT11 >= ON_ON_DWLIMIT && AD0DT11 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x1010;
             puc_Set_on_flag |= 0x10;
         }
         if (AD0DT11 >= OFF_ON_DWLIMIT && AD0DT11 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x1000;
             puc_Set_on_flag |= 0x10;
         }
         if (AD0DT11 >= ON_OFF_DWLIMIT && AD0DT11 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0010;
             puc_Set_on_flag |= 0x10;
         }
         if (AD0DT11 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x10;
         }
         //ÇcÇrÇvÇPÅQÇUÇ∆ÇcÇrÇvÇQÅQÇUÉ`ÉFÉbÉN
         if (AD0DT12 >= ON_ON_DWLIMIT && AD0DT12 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x2020;
             puc_Set_on_flag |= 0x20;
         }
         if (AD0DT12 >= OFF_ON_DWLIMIT && AD0DT12 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x2000;
             puc_Set_on_flag |= 0x20;
         }
         if (AD0DT12 >= ON_OFF_DWLIMIT && AD0DT12 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0020;
             puc_Set_on_flag |= 0x20;
         }
         if (AD0DT12 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x20;
         }
         //ÇcÇrÇvÇPÅQÇVÇ∆ÇcÇrÇvÇQÅQÇVÉ`ÉFÉbÉN
         if (AD0DT13 >= ON_ON_DWLIMIT && AD0DT13 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x4040;
             puc_Set_on_flag |= 0x40;
         }
         if (AD0DT13 >= OFF_ON_DWLIMIT && AD0DT13 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x4000;
             puc_Set_on_flag |= 0x40;
         }
         if (AD0DT13 >= ON_OFF_DWLIMIT && AD0DT13 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0040;
             puc_Set_on_flag |= 0x40;
         }
         if (AD0DT13 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x40;
         }
         //ÇcÇrÇvÇPÅQÇWÇ∆ÇcÇrÇvÇQÅQÇWÉ`ÉFÉbÉN
         if (AD0DT14 >= ON_ON_DWLIMIT && AD0DT14 <= ON_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x8080;
             puc_Set_on_flag |= 0x80;
         }
         if (AD0DT14 >= OFF_ON_DWLIMIT && AD0DT14 <= OFF_ON_UPLIMIT)
         {
             pui_Dsw_work    |= 0x8000;
             puc_Set_on_flag |= 0x80;
         }
         if (AD0DT14 >= ON_OFF_DWLIMIT && AD0DT14 <= ON_OFF_UPLIMIT)
         {
             pui_Dsw_work    |= 0x0080;
             puc_Set_on_flag |= 0x80;
         }
         if (AD0DT14 >= OFF_OFF_DWLIMIT)
         {
             pui_Dsw_work    |= 0x0000;
             puc_Set_on_flag |= 0x80;
         }
         
         if (puc_Set_on_flag != 0xff) //ämíËÇµÇƒÇ¢Ç»Ç¢
         {
             puc_Err_count++;
             puc_Set_on_count = 0;
             if (puc_Err_count >= 5)
             {
                 //ÇcÇrÇvÉGÉâÅ[ÉZÉbÉg
                 break;
             }
         } else {                //ämíË
            puc_Set_on_count++;
            if (puc_Set_on_count >= 3)
            {
                if (puc_Retry_count >= 1)
                {
                    if (pui_Dsw_work == pui_Dsw_work_bkup)
                    {
                        //ÇcÇrÇvämíËèàóù
                        gtt_Dsw.ALL = (unsigned short)pui_Dsw_work;
                        break;
                    } else {
                        //ÇcÇrÇvÉGÉâÅ[ÉZÉbÉg
                        break;
                    }
                }
                puc_Err_count = 0;
                puc_Set_on_count = 0;
                pui_Dsw_work_bkup = pui_Dsw_work;
                puc_Retry_count++;
            }
        }
     }
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_input_dsw_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

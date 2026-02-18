//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｔ＿ｉｎｐｕｔ＿ｒ８
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ
//  【機能説明】
//      Ｒ８入力割り込み
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
#include  "custom.h"

void int_input_r8(void)
{
//--------- RTC by @Tny 2008/09/01 ------------
#if true
     //RTC_Adjust(true);          // RTC補正処理
     //TINIR6 = (TINIR6 & 0x0df); // 割り込み要求ステータスビットのクリア
#endif
//--------------------------------------------
#if 0
     unsigned char puc_R8_input_no;
     
     puc_R8_input_no = P13DATA & 0xf0;

     if (gui_R8_input_no == WELD_IN2_CODE)            //非常停止入力
     {
         if (R8_FLAG_BIT)
         {
             gub_R8_emergency_err = true;
         } else {
             gub_R8_emergency_err = false;
         }
     }
     if (gui_R8_input_no == WELD_IN3_CODE)            //一時停止１（ガス減圧異常）入力
     {
         if (R8_FLAG_BIT)
         {
             gub_R8_outside1_err  = true;
         } else {
             gub_R8_outside1_err  = false;
         }
     }
     if (gui_R8_input_no == WELD_IN4_CODE)            //一時停止２（水回路異常）入力
     {
         if (R8_FLAG_BIT)
         {
             gub_R8_outside2_err  = true;
         } else {
             gub_R8_outside2_err  = false;
         }
     }
     if (gui_R8_input_no == WELD_IN6_CODE)            //インチング・リトラクト用モータ起動入力
     {
         if (R8_FLAG_BIT)
         {
             gub_R8_motor_on       = true;
         } else {
             gub_R8_motor_on       = false;
         }
     }
     if (gui_R8_input_no == WELD_IN7_CODE)            //インチング（ＯＦＦ）　リトラクト（ＯＮ）入力
     {
         if (R8_FLAG_BIT)
         {
             gub_R8_inching_retract       = true;
         } else {
             gub_R8_inching_retract      = false;
         }
     }

     if (gui_R8_input_no == WELD_IN8_OCDE)          //予備
     {
         if (R8_FLAG_BIT)
         {
             ;
         } else {
             ;
         }
     }
     if (gui_R8_input_no == EXT_IN1_CODE)          //予備
     {
         if (R8_FLAG_BIT)
         {
             ;
         } else {
             ;
         }
     }
     if (gui_R8_input_no == EXT_IN2_CODE)          //予備
     {
         if (R8_FLAG_BIT)
         {
             ;
         } else {
             ;
         }
     }
     if (gui_R8_input_no == EXT_IN3_CODE)          //予備
     {
         if (R8_FLAG_BIT)
         {
             ;
         } else {
             ;
         }
     }
     TINIR6 = (TINIR6 & 0x0df);                    // 割り込み要求ステータスビットのクリア
#endif
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA0_int_input_r8.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

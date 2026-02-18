//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　Ｐｏｒｔ＿ｕｓｅ＿ｃｈｅｃｋ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      ＩＩＦポートの使用状況をチェックする。
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2009.09.24  H.Ihara
//
//            Copyright(C)2009 Panasonic Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

// EXTERNAL IIF NEW	2011.02.21 by @Tny
void port_use_check_member(void)
{
      unsigned char puc_Index;

      switch (gtt_Ctrl_counter.uc_Iif_no)
      {
              case 0: //OUTPUT PORT設定
                      if (gtt_Ctrl_flag.Out_function_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                      {
                          guc_Out_port[0][gtt_Ctrl_counter.uc_Out_port_no] = gtt_Ctrl_counter.uc_Out_function_no;
                          gtt_Ctrl_counter.uc_Out_function_no = 0;
                          gtt_Ctrl_flag.Out_function_set_ready = OFF;
                          gtt_Ctrl_flag.Set_key = OFF;
                          gtt_Ctrl_flag.Param_change = ON;
                          gtt_Ctrl_flag.Iif_enable = false;
                       }
                       break;
              case 1: //INPUT PORT設定
                       if ((gtt_Ctrl_flag.In_function_set_ready == ON || gtt_Ctrl_flag.In_ab_set_ready == ON) && gtt_Ctrl_flag.Set_key == ON)
                       {
                           if (gtt_Ctrl_flag.In_function_set_ready == ON)
                           {
                               guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no] = gtt_Ctrl_counter.uc_In_function_no;
                               //gtt_Ctrl_counter.uc_In_function_no = 0; //2009.11.25 IIF NEW
                           }
                           if (gtt_Ctrl_flag.In_ab_set_ready == ON)
                           {
                               guc_In_port[1][gtt_Ctrl_counter.uc_In_port_no] = gtt_Ctrl_counter.uc_Iif_ab_set; //2009.10.28 IIF NEW
                               gtt_Ctrl_counter.uc_In_function_no = guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no]; //2009.11.25 IIF NEW
                           }
                           //ポートチェック 2008.09.04 同じ機能設定を禁止
                           for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
                           {
                                if (gtt_Ctrl_counter.uc_In_port_no != puc_Index)
                                {
                                    if (guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no] == guc_In_port[0][puc_Index])
                                    {
                                        guc_In_port[0][puc_Index] = 0;
                                        guc_In_port[1][puc_Index] = 0; //A接点に戻す。2009.10.28
                                    }
                                 }
                            }
                            //gtt_Ctrl_counter.uc_In_function_no = 0; //2009.11.25 del IIF NEW
                            gtt_Ctrl_flag.In_ab_set_ready       = OFF; //2009.10.28
                            gtt_Ctrl_flag.In_function_set_ready = OFF;
                            gtt_Ctrl_flag.Set_key = OFF;
                            gtt_Ctrl_flag.Param_change = ON;
                            gtt_Ctrl_flag.Iif_enable = false;
                       }
                       break;
              case 2: //ANALOG PORT設定
                       if (gtt_Ctrl_flag.Analog_function_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                       {
                           guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] = gtt_Ctrl_counter.uc_Analog_function_no;
                           //ポートチェック 同じ機能設定を禁止
                           for (puc_Index = 1 ; puc_Index <= 3 ; puc_Index++)
                           {
                                if (gtt_Ctrl_counter.uc_Analog_port_no != puc_Index)
                                {
                                    if (guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] == guc_Analog_port[0][puc_Index])
                                    {
                                        guc_Analog_port[0][puc_Index] = 0;
                                    }
                                }
                           }
                           gtt_Ctrl_counter.uc_Analog_function_no = 0;
                           gtt_Ctrl_flag.Analog_function_set_ready = OFF;
                           gtt_Ctrl_flag.Set_key = OFF;
                           gtt_Ctrl_flag.Param_change = ON;
                           gtt_Ctrl_flag.Iif_enable = false;
                       }
                       break;
      }
            
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_port_use_check_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

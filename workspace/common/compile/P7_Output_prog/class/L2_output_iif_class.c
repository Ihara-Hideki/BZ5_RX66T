//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｏｕｔｐｕｔ＿ｉｉｆ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ＩＩＦ出力
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2009.10.15  H.Ihara
//
//            Copyright(C)2009 Panasonic Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
// EXTERNAL IIF NEW	2011.02.21 by @Tny
void output_iif_class(void)
{

     unsigned char  puc_Index;
     unsigned char  puc_Out_data;


     //出力は起動時必ずＯＰＥＮになるのでＡ接点のみ使用可能とする。


     puc_Out_data = 0x00; //出力データの初期化
     if(gb_IIF_Select == true)
     {
        for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
        {
             switch (guc_Out_port[0][puc_Index])
             {
                     //<><><><><><><><><><><><><><><> 電流検出 <><><><><><><><><><><><><><><>
                     case IIF_OUTPUT_CURDET:
                          if (gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><> アーク切れ異常 <><><><><><><><><><><><><>
                     case IIF_OUTPUT_ARCOUT:
                          if (gtt_Ctrl_flag.Arc_out_err == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><> スティック異常 <><><><><><><><><><><><><>
                     case IIF_OUTPUT_STKOUT:
                          if (gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b0 == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><><><> エラー <><><><><><><><><><><><><><><>
                     case IIF_OUTPUT_ERR:
                          if (gub_Err == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><><> アラーム <><><><><><><><><><><><><><><>
                     case IIF_OUTPUT_ALM:
                          if (gub_Alarm == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><><><> 溶接中 <><><><><><><><><><><><><><><>
                     case IIF_OUTPUT_WELD:
                          if (guc_Sequence_mode != IDLING)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><><> ガス動作確認 <><><><><><><><><><><><><>
                     case IIF_OUTPUT_GAS_ON:
                          if (gtt_Ctrl_word.Gas_ctrl_code == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><><> 汎用出力１ <><><><><><><><><><><><><><>
                     case IIF_OUTPUT_GP_OT1:
                          if (guc_General1_input == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><><> 汎用出力２ <><><><><><><><><><><><><><>
                     case IIF_OUTPUT_GP_OT2:
                          if (guc_General2_input == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     //<><><><><><><><><><><><><><><> 汎用出力３ <><><><><><><><><><><><><><>
                     case IIF_OUTPUT_GP_OT3:
                          if (guc_General3_input == ON)
                          {
                              puc_Out_data = puc_Out_data | (0x01 << (puc_Index - 1));
                          } else {
                              puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          }
                          break;
                     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


                     default:
                          puc_Out_data = puc_Out_data & ~(0x01 << (puc_Index - 1));
                          break;
             }


        }
        if (ComuniPackIif.Data.From.uc_Iif_output_data != puc_Out_data)
        {
            ComuniPackIif.Data.From.uc_Iif_output_data = puc_Out_data;
	    	GD2_Send_CMD(0x20); //2009.11.25 IIF NEW
        }

        if((gtt_Ctrl_flag.Iif_enable == false)||(gtt_Ctrl_flag.Set_screen_on_off == ON)||(gtt_Ctrl_flag.Iif_first_rcv == OFF)) //IIF接続確認 2009.10.29
        {
            if (gtt_Ctrl_flag.Iif_output_data_one_shot == OFF) //2009.11.25 IIF NEW
            {
                ComuniPackIif.Data.From.uc_Iif_output_data = 0x00;
	    	    GD2_Send_CMD(0x20); //2009.11.25 IIF NEW
                gtt_Ctrl_flag.Iif_output_data_one_shot = ON;
            }
        } else {
                gtt_Ctrl_flag.Iif_output_data_one_shot = OFF;
        }

     }


  return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_output_iif_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

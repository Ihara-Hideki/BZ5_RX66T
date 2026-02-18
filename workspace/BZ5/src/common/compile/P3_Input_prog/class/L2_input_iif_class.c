//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｐｕｔ＿ｉｉｆ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ＩＩＦ入力
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2009.09.17  H.Ihara
//
//            Copyright(C)2009 Panasonic Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
// EXTERNAL IIF NEW	2011.02.21 by @Tny
void input_iif_class(void)
{
     unsigned char puc_Chattering_check_no;

     int sts; //2007.3.9

     unsigned short pus_Rpm_work;//2007.3.15

     unsigned char  puc_Index;   //2008.09.01
     unsigned char  puc_Port_set_flag; //2008.09.09
     unsigned char  puc_Ext_select_sw; //2008.09.09
     unsigned char  puc_General_input; //2009.09.29
     unsigned char  puc_On_off_judgment; //2009.10.16


  if(gtt_Dsw.Sw.No7 == false){ // DSW1-8がOFFならば確認

     if((gb_IIF_Select == true)&&(gb_Iif_Input)&&(gtt_Ctrl_flag.Iif_enable == true)&&(gtt_Ctrl_flag.Set_screen_on_off == OFF)&&(gtt_Ctrl_flag.Iif_first_rcv == ON)) //IIF接続確認
     {

#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.01
         //<><><><><><><><><><><><><> トーチスイッチ入力 <><><><><><><><><><><><>
         puc_On_off_judgment = OFF;
         if (guc_Robot_connect_flag == false && gtt_Ctrl_flag.Ts_cancel == OFF)
         {
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_TSW)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if((puc_On_off_judgment == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
                 {
                        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = true;
                        //<><> アークスポット用 <><>
                        if (guc_Crater_mode_counter ==  SEQUENCE_ARC_SPOT)
                        {
                            if (gtt_Ctrl_flag.Arc_spot_time_up == true)
                            {
		                		gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
                            }
                        }
                        //<><><><><><><><><><><><><>
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
#if false	// 現状テーブルがないので、削除 2009.01.28
                        if (guc_Remo_table_check_flag == false)
                        {
				            gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
		                }
#endif
//-------------------------------------------------
                 } else {
                        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false; //ＰＣ通信時トーチＳＷがｏＦＦできないので
                        if (guc_Crater_mode_counter ==  SEQUENCE_ARC_SPOT)
                        {
                            gtt_Ctrl_flag.Arc_spot_time_up = false;
                        }
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
						gb_Iif_First_Toch_sw		= false;		// ＩＩＦ接続時ＴＳ状態確認フラグ
//-------------------------------------------------
                 }
             }
//-------------------------------------------------
// ＩＩＦにてＴＳが設定されていない場合は、ＩＩＦ接続時ＴＳ状態確認フラグをクリアする。		<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
			else{
				gb_Iif_First_Toch_sw = false;	// ＩＩＦ接続時ＴＳ状態確認フラグ
			}
//-------------------------------------------------
         }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19

#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.02
         //<><><><><><><><><><><><><><> ガスＯＮ命令 <><><><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  guc_Controller_gas_sw_cancel = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_GAS_CK)
                  {
                      puc_Port_set_flag = ON;
                      guc_Controller_gas_sw_cancel = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if((puc_On_off_judgment == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 4)>	2011.10.14 by @Tny
                 {
                        if (guc_Gas_check_cancel_flag == false) // ９０秒または一旦溶接状態になったら一旦OFFになるまで受け付けない。
                        {
                            guc_Gas_on_off_flag = ON;
                        }
                 } else {
                        guc_Gas_on_off_flag = OFF;
                        guc_Gas_check_cancel_flag = false; // スイッチが一旦OFFで再度受付
                 }
                 if (guc_Gas_on_off_flag != guc_Gas_on_off_flag_bkup)
                 {
                     guc_Gas_on_off_flag_bkup = guc_Gas_on_off_flag;
   	                 guc_Sw_rewrite_check_flag = 2; //表示の更新のため
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19

#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.03
         //<><><><><><><><><><><><><> インチング入力 <><><><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  guc_Controller_inc_sw_cancel = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_WIR_CK)
                  {
                      puc_Port_set_flag = ON;
                      guc_Controller_inc_sw_cancel = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if((puc_On_off_judgment == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 4)>	2011.10.14 by @Tny
                 {
                        guc_Inching_sw_flag = ON;
                 } else {
                        guc_Inching_sw_flag = OFF;
                 }
                 if (guc_Inching_sw_flag != guc_Inching_sw_flag_bkup)
                 {
                     guc_Inching_sw_flag_bkup = guc_Inching_sw_flag;
   	                 guc_Sw_rewrite_check_flag = 2; //表示の更新のため
                 }
                 
                 gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect = OFF;

             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.04
         //<><><><><><><><><><><><><> リトラクト入力 <><><><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_RETRCT)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                  } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if((puc_On_off_judgment == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 4)>	2011.10.14 by @Tny
                 {
                     gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on      = ON;
                     gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect  = ON;
                 } else {
                     gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on      = OFF;
                     gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect  = OFF;
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.05
         //<><><><><><><><><><><> スティックチェック入力 <><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_STKSET)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if((puc_On_off_judgment == ON)&&(gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false))	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
                 {
                     gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = true;

#if false	// <--- false = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
gtt_Ctrl_flag.Stick_start = ON;
gtt_Ctrl_flag.Stick_end = ON;
gtt_Ctrl_flag.Stick_on_off_check = OFF;
#endif
                 } else {
                     gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false;
#if false	// <--- false = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
//@@@@@@@
gtt_Ctrl_flag.Stick_start = OFF;
gtt_Ctrl_flag.Stick_end = OFF;
gtt_Ctrl_flag.Stick_snd_set = OFF;
#endif
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.06
         //<><><><><><><><><><><><><> 一元／個別入力 <><><><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_OKCVON)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if((puc_On_off_judgment == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 4)>	2011.10.14 by @Tny
                 {
                     guc_Okcv_select_flag = true;
                     guc_Okcv_select_counter = 0; //2009.11.20 IIF NEW
                 } else {
                     guc_Okcv_select_flag = false;
                     guc_Okcv_select_counter = 2; //2009.11.20 IIF NEW
                 }
                 //一元電圧は前パネルのＳＷ操作で表示が変更されるのでキーを押したことと同じ動作をさせる。 2009.11.20 IIF NEW
                 if (guc_Okcv_select_flag_bkup_iif != guc_Okcv_select_flag)
                 {
                     guc_Okcv_select_flag_bkup_iif = guc_Okcv_select_flag;
                     guc_Sw_rewrite_check_flag = 2;
                 }


             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.7
         //<><><><><><><><><><><><><> 一時停止１入力 <><><><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_STOP1)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                if (puc_On_off_judgment == ON)
                {
                   gtt_Internal_pack.Data.In.Outside1 = true;
                } else {
#if true	// <--- true = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
					//-------------------------------------------------
					// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
					// 端子台一時停止１入力
					if(gtt_Ext_input.Flag[EXT_OUT_SIDE1_NO] == ON){
						gtt_Internal_pack.Data.In.Outside1 = false;
					}
					//-------------------------------------------------
#else
					gtt_Internal_pack.Data.In.Outside1 = false;
#endif
                }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.8
         //<><><><><><><><><><><><><> 一時停止２入力 <><><><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_STOP2)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                     gtt_Internal_pack.Data.In.Outside2 = true;
                 } else {
#if true	// <--- true = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
					//-------------------------------------------------
					// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
					// 端子台一時停止２入力
					if(gtt_Ext_input.Flag[EXT_OUT_SIDE2_NO] == ON){
                    	gtt_Internal_pack.Data.In.Outside2 = false;
					}
					//-------------------------------------------------
#else
                   	gtt_Internal_pack.Data.In.Outside2 = false;
#endif
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.9
         //<><><><><><><><><><><><><> 非常停止入力 <><><><><><><><><><><><><><><>
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_EM_STP)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                     gtt_Internal_pack.Data.In.Emergency = true;
                 } else {
#if true	// <--- true = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
					//-------------------------------------------------
					// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
					// 端子台非常停止入力
					if(gtt_Ext_input.Flag[EXT_EMG_NO] == ON){
						gtt_Internal_pack.Data.In.Emergency = false;
					}
					//-------------------------------------------------
#else
					gtt_Internal_pack.Data.In.Emergency = false;
#endif
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.10-16
         //<><><><><><><><><><><><> 再生ｃｈバイナリ１～７ <><><><><><><><><><><>
             //BIN1
             puc_Ext_select_sw = 0x00;
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_BIN1)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x01;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xfe;
                 }
             }
             //BIN2
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_BIN2)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x02;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xfd;
                 }
             }
             //BIN3
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_BIN3)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x04;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xfb;
                 }
             }
             //BIN4
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_BIN4)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x08;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xf7;
                 }
             }
             //BIN5
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_BIN5)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x10;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xef;
                 }
             }
             //BIN6
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_BIN6)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x20;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xdf;
                 }
             }
             //BIN7
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_BIN7)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x40;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xbf;
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


         //FUNCTION NO.17
         //<><><><><><><><><><><><><> 入力許可信号 <><><><><><><><><><><><><><><>
             //CNT
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_CNT)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if((puc_On_off_judgment == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 4)>	2011.10.14 by @Tny
                 {
                        gtt_Ctrl_flag.Ext_select_cnt = ON;
                        if (guc_Select_counter != MODE_PLAY)	// 2011.02.24 by @Tny
                        {
                            guc_Select_counter = MODE_PLAY;	// 2011.02.24 by @Tny
                        }
                        if (gtt_Ctrl_flag.Ext_select_init == OFF)
                        {
                            gtt_Ctrl_flag.Ext_select_init = ON;
                            gtt_Ctrl_flag.Ext_select_end  = OFF;
                            gtt_Ctrl_flag.Play = ON;
                            guc_Ch_no = 0;
                            guc_Ch_no_bkup = 0;
                        }
                 } else {
#if true // ↓ EXTERNAL IIF NEW	2011.03.03 by @Tny
                        if(gtt_Ctrl_flag.Ext_select_cnt == ON){	// 入力許可信号がＯＮ→ＯＦＦ　？
							gtt_Ctrl_flag.Param_change = ON;		// 現在の溶接条件をＣＨ０に記憶する
						}
#endif // ↑ EXTERNAL IIF NEW	2011.03.03 by @Tny
                        gtt_Ctrl_flag.Ext_select_init = OFF;
                        gtt_Ctrl_flag.Ext_select_cnt = OFF;
                        if (gtt_Ctrl_flag.Ext_select_end == OFF)
                        {
                            guc_Select_counter = 0;
                            gtt_Ctrl_flag.Ext_select_end  = ON;
                        }
                        gtt_Ctrl_flag.Stb_sw_on = OFF; //2009.11.25 IIF NEW
                        gtt_Ctrl_flag.Stb_set   = OFF; //2009.11.25 IIF NEW
                 }
                 if (gtt_Ctrl_flag.Ext_select_cnt != gtt_Ctrl_flag.Ext_select_cnt_bkup)
                 {
                     gtt_Ctrl_flag.Ext_select_cnt_bkup = gtt_Ctrl_flag.Ext_select_cnt;
   	                 guc_Sw_rewrite_check_flag = 2; //表示の更新のため
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


         //FUNCTION NO.18
         //<><><><><><><><><><><><> ストローブ信号入力 <><><><><><><><><><><><><>
             //STB
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_STB)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 //<><> 2009.11.25 IIF NEW <><>
                 if((puc_On_off_judgment == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 4)>	2011.10.14 by @Tny
                 {
                     gtt_Ctrl_flag.Stb_sw_on = ON;
                 }
                 if (gtt_Ctrl_flag.Stb_sw_on == ON && puc_On_off_judgment == OFF)
                 {
                     gtt_Ctrl_flag.Stb_set = ON;
                 }
                 //<><><><><><><><><><><><><><>
                 if (gtt_Ctrl_flag.Stb_set == ON) //2009.11.25 IIF NEW
                 {
					if((puc_Ext_select_sw > 0)&&(puc_Ext_select_sw <= CH)){	// 再生番号の範囲チェック	<EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
						if (guc_Write_check_flag[puc_Ext_select_sw] == true){
							guc_Ch_no = puc_Ext_select_sw;
							if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){
								gus_Pre_display_timer = 500;
							}
						}
					}
					gtt_Ctrl_flag.Stb_sw_on = OFF; //2009.11.25 IIF NEW
					gtt_Ctrl_flag.Stb_set   = OFF; //2009.11.25 IIF NEW
                 }
             }
         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
         //FUNCTION NO.19-21
         //<><><><><><><><><><><><><> 汎用入力１～３ <><><><><><><><><><><><><><>
             //GP_IN1
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_GP_IN1)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       guc_General1_input = ON;
                 } else {
                       guc_General1_input = OFF;
                 }
             }
             //GP_IN2
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_GP_IN2)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       guc_General2_input = ON;
                 } else {
                       guc_General2_input = OFF;
                 }
             }
             //GP_IN3
             puc_On_off_judgment = OFF;
             for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_INPUT_GP_IN3)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 //接点判定
                 if (((InternalPackIif.Data.To.us_Iif_input_data >> (puc_Index - 1)) & 0x0001) == 0x0001)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                 {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = ON;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = OFF;
                     }
                 } else {
                     if(guc_In_port[1][puc_Index] == 0) //Ａ接点
                     {
                        puc_On_off_judgment = OFF;
                     } else {                           //Ｂ接点
                        puc_On_off_judgment = ON;
                     }
                 }
                 if (puc_On_off_judgment == ON)
                 {
                       guc_General3_input = ON;
                 } else {
                       guc_General3_input = OFF;
                 }
             }

         //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif //testのため一時削除2009.11.19


#if 1 //testのため一時削除2009.11.19
     } else {
       gtt_Ctrl_flag.Ext_select_init   = OFF;
       gtt_Ctrl_flag.Ext_select_cnt    = OFF;
       if(gtt_Ctrl_flag.Ext_select_end == OFF)
       {
          guc_Select_counter              = 0;
          gtt_Ctrl_flag.Ext_select_end    = ON;
       }
#endif 
     }
   
     //<><><><><><><> ＩＩＦは接続された状態で下記条件での処理 <><><><><><><>
     //条件：
     //①ＩＩＦが接続されている
     //②設定画面になっている
     //③ＩＩＦ動作確認がされていない
     //④最初のＩＩＦからの受信を受けていない
     //処理内容：入力をクリア（入力ＯＦＦ）にする。（トーチＳＷの不意な入力を防ぐ等）
     if((gb_IIF_Select == true)&&(gb_Iif_Input)&&((gtt_Ctrl_flag.Iif_enable == false)||(gtt_Ctrl_flag.Set_screen_on_off == ON)||(gtt_Ctrl_flag.Iif_first_rcv == OFF))) //IIF接続確認
     {
         //NO.1,2,3,7,8,9は外部入力端子との共存のためＩＩＦにセットされているかどうかチェックする。IIF NEW 2009.11.19
         for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
         {
              if (guc_In_port[0][puc_Index] == IIF_INPUT_TSW)
              {
                  gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false; //NO1.起動入力
              }
              if (guc_In_port[0][puc_Index] == IIF_INPUT_GAS_CK)
              {
                  guc_Gas_on_off_flag                                         = OFF;   //NO2.ガス制御
              }
              if (guc_In_port[0][puc_Index] == IIF_INPUT_WIR_CK)
              {
                  guc_Inching_sw_flag                                         = OFF;   //NO3.インチング
              }
              if (guc_In_port[0][puc_Index] == IIF_INPUT_STOP1)
              {
                  gtt_Internal_pack.Data.In.Outside1                          = false; //NO7.一時停止１
              }
              if (guc_In_port[0][puc_Index] == IIF_INPUT_STOP2)
              {
                  gtt_Internal_pack.Data.In.Outside2                          = false; //NO8.一時停止２
              }
              if (guc_In_port[0][puc_Index] == IIF_INPUT_EM_STP)
              {
                  gtt_Internal_pack.Data.In.Emergency                         = false; //NO9.非常停止
              }
         }
         //
         gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on      = OFF;   //NO4.リトラクト
         gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect  = OFF;   //NO4
         gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false; //NO5.スティック指令
         //NO6.一元個別は設定なので対象外。
         //NO10～NO16はｃｈ再生設定なので対象外
         guc_General1_input                                          = OFF;   //NO17.汎用入力１
         guc_General2_input                                          = OFF;   //NO18.汎用入力２
         guc_General3_input                                          = OFF;   //NO19.汎用入力３
         //<><> 2009.11.19 IIF NEW ＬＥＤ表示更新のため <><>
         if (gtt_Ctrl_flag.One_shot_sw_rewrite_check == false)
         {
             gtt_Ctrl_flag.One_shot_sw_rewrite_check = true;
             guc_Sw_rewrite_check_flag               = 2;
         }
         //<><><><><><><><><><><><><><><><><><><><><><><><><>
     } else {
             gtt_Ctrl_flag.One_shot_sw_rewrite_check = false; //2009.11.19 IIF NEW ＬＥＤ表示更新のため
     }
     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


#if 1 //testのため一時削除2009.11.19
  } else {
    if(guc_Robot_connect_flag == false) // ロボット接続状態でない？
    {
       gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false;
    }
  }
#endif 
  return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_input_iif_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

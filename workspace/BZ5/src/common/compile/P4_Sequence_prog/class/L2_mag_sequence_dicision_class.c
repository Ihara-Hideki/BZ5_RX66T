//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍａｇ＿ｓｅｑｕｅｎｃｅ＿ｄｉｃｉｓｉｏｎ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ＭＡＧ系シーケンス決定
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
#include "iodefine.h"
#include "devdrv_bsc.h"
#include "rza_io_regrw.h"
unsigned char mag_sequence_dicision_class(unsigned char xuc_Sequence_mode)
{
             unsigned char puc_Sequence_mode;
             puc_Sequence_mode = xuc_Sequence_mode;
             // IDLING:                待機状態　◎○
             // PRE_FLOW:              プリフロー時間○
             // SLOW_DOWN:             スローダウン　◎○
             // INITIAL_DELAY:         INITIAL_DELAY時間処理
             // INITIAL_WELD:          初期溶接○
             // INITOMAIN_SLOPE:       初期溶接から本溶接へのスロープ△
             // HOLDTOCRA_SLOPE:       本溶接からクレータ溶接へのスロープ△
             // MAIN_SLOPE_WELD:       スロープ処理×
             // MAIN_WELD:             本溶接　　◎○
             // HOLD_WELD:             自己保持△
             // CRATER_WELD:           クレータ溶接○
             // ARC_SPOT_WELD:         アークスポット溶接△
             // BURN_BACK_DELAY:       バーンバック処理　　　◎○
             // BURN_BACK_PULSE:       第2バーンバック処理　　◎×
             // AFTER_FLOW:            アフターフロー○
             //　ＧＺはロボット仕様であるため今回は◎分のみの作成を行う
             //　ＡＺ３はハンドを含むため○部の作成を行う。△部はその他のシーケンスで代替え可能。×部はＤＳＰが行うため特に用意しない。
             
             switch (puc_Sequence_mode)
             {
                     case IDLING:
//----- Phase12 & Phase14 by @Tny 2008/09/19 -----
#if true
//----- Phase19 by @Tny 2008/09/26 -----
#if true    // 詳細設定モードなら溶接動作へは移行しない
                            //if((gub_System_err == OFF) && (guc_Select_counter != MODE_RECORD) && (guc_Select_counter != MODE_DETAILS)){ // エラーが発生していない？ & 記憶モードでない？(Phase16)	// BP4 Phase6 by @Tny 2009/01/27
                            if((gub_System_err == OFF) && (guc_Select_counter != MODE_RECORD) && (guc_Select_counter != MODE_DETAILS) && (guc_Method_condition_counter != NAVI_METHOD)){ //2009.03.09.NO5
#else
                            if((gub_System_err == OFF) && (guc_Select_counter != MODE_RECORD)){ // エラーが発生していない？ & 記憶モードでない？(Phase16)	// BP4 Phase6 by @Tny 2009/01/27
#endif
//--------------------------------------------
                                if(gtt_Ctrl_flag.Set_screen_on_off == OFF){ // 設定モードではない？(Phase16)
                                    // DSW1-8がOFF、IIFが未接続、またはIIFが接続、認識確認、データ受信の場合にシーケンス動作要求を受け付ける
                                    if((gtt_Dsw.Sw.No7 == false)&&((gb_Iif_BuiltIn == false)||((gb_Iif_BuiltIn)&&(gb_IIF_Select)&&(gb_Iif_Input)))){
                                        // 初期シーケンス待ち時間を経過した？
                                        if(guc_Init_wait_sequence <= 0){

                                            if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
                                            {
                                                gtt_Ctrl_flag.Pre_flow = ON;
                                                puc_Sequence_mode = PRE_FLOW;
//----- Phase19 by @Tny 2008/09/26 -----
#if true
                                                if(gtt_End_welding_display.us_Display_time > 0){
                                                    ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no = 0;    //表示するブロック番号
                                                    REMO_Send_CMD(0x23);
                                                    gtt_End_welding_display.bProc1          = false;
                                                    gtt_End_welding_display.bProc2          = false;
                                                    gtt_End_welding_display.us_Display_time = 0;
                                                }
#endif
//--------------------------------------------
                                                gtt_Ctrl_flag.Toch_sw_off_delay_time    = ON;                 //2007.2.24 追加
                                                gtt_Ctrl_counter.Toch_sw_off_delay_time = TOCH_SW_OFF_DELAY_TIME; //2007.2.24 追加
                                                //gtt_Ctrl_counter.Toch_sw_off_delay_time = 10; //2007.2.24 追加

                                                //<><><><>繰り返し溶接用<><><><><> REPEAT 2007.1.12  2007.1.22追加　2007.1.26移植追加
                                                if (gtt_Ctrl_counter.Repeat_weld > 0)
                                                {
                                                    gtt_Ctrl_flag.Repeat_weld = ON;
                                                    gtt_Ctrl_counter.Repeat_weld = 0;
                                                } else {
                                                    gtt_Ctrl_flag.Repeat_weld = OFF;
                                                }
                                                //<><><><><><><><><><><><><><><><>
                                            }

                                            //***** 直流手溶接モード 2009.03.06 *****
                                            if (guc_Method_condition_data == STD_HAND_METHOD)
                                            {
                                                if (gtt_Ctrl_flag.Hand_restart == OFF) //2009.03.30
                                                {
                                                    gtt_Ctrl_flag.Hand_stick_ready_time = OFF;
                                                } else {
                                                    gtt_Ctrl_counter.Hand_stick_ready_time = 50;
                                                }
                                                puc_Sequence_mode = HAND_STICK;
			                        gtt_Ctrl_flag.Slow_down = OFF;
                                                gtt_Ctrl_flag.Hand_restart = OFF; //2009.03.30
                                                gtt_Ctrl_flag.Hand_stick_start = OFF;
                                                //LED4 = OFF; 2009.07.23 test del
                                                
                                            } else {
                                                gtt_Ctrl_flag.Hand_stick_ready_time = OFF;
                                                gtt_Ctrl_flag.Hand_stick_start = OFF;
                                                gtt_Ctrl_flag.Hand_restart = OFF; //2009.03.30
                                                //LED4 = OFF; 2009.07.23 test del
                                            }
                                            //***************************************


                                        }
                                    }
                                }
                            }
#endif
//--------------------------------------------
                          
                          //スタート回路動作
                          //START1 = ON;  //2008.09.11 2010.01.07 del
                          //START2 = OFF; //2008.09.11 2009.01.31 del
                          guc_R8_control.Bit1Sw.Over_lay = false; //重畳充電停止 2008.09.24
                          //guc_R8_control.Bit1Sw.Over_lay = true; //重畳充電停止 2008.09.24 田中さん要請

                          gtt_Ctrl_flag.Srt1 = OFF; //2008.03.11
                          //if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_INIT_CRATER)
                          if (guc_Crater_mode_counter == SEQUENCE_CRATER) //2009.02.05
                          {
                              if(gtt_Ctrl_counter.Crater_repeat_time <= 0)
                              {
                                 gtt_Ctrl_flag.Crater_repeat = OFF;
                              }
                          } else { //2009.01.28
                             gtt_Ctrl_flag.Crater_repeat = OFF;
                          }

                          //***** 溶接中アーク切れ時の対応 2008.10.21 *****
                          if (gtt_Ctrl_flag.Arc_out_err == ON)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == ON)
                              {
                                  //puc_Sequence_mode = IDLING;
                                  puc_Sequence_mode = PRE_FLOW; //2009.02.25
                                  gtt_Ctrl_flag.Arc_out_err = OFF;
                              } else {
                                  gtt_Ctrl_flag.Arc_out_err = OFF;
                                  gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                              }
                          }
                          //***********************************************

                          //***** 電極短絡検出時の対応 2009.03.16 *****
                          if (gtt_Ctrl_flag.Arc_short == ON)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == ON)
                              {
                                  puc_Sequence_mode = IDLING;
                                  //puc_Sequence_mode = PRE_FLOW;
                                  //gtt_Ctrl_flag.Arc_out_err = OFF;
                              } else {
                                  gtt_Ctrl_flag.Arc_short = OFF;
                                  gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                                  gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = OFF; //2009.07.23
                              }
                          }
                          //***********************************************


                          //*********Ｗクリック終了対応 2009.02.25 ********
                          if (gtt_Ctrl_flag.W_click_end == ON)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == ON)
                              {
                                  puc_Sequence_mode = IDLING;
                              } else {
                                  gtt_Ctrl_flag.W_click_end = OFF;
                              }
                          }
                          //***********************************************
                          
                          //***** 可変反復有効無効処理 2009.03.16 *****
                          //if (gss_Select_dital[P_VARIABLE_CRATER_REPEAT] == true)
                          if (gss_Select_dital[P_VARIABLE_CRATER_REPEAT] == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.03.17
                          {
                              gtt_Ctrl_flag.Variable_crater_repaet = ON;
                              if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Pulse_mode_data != 0)
                              {
                                  gtt_Ctrl_flag.Variable_crater_repaet = OFF;
                              }
                          } else {
                              gtt_Ctrl_flag.Variable_crater_repaet = OFF;
                          }
                          
                          //<><><><> エラー時ガスＯＦＦ遅れ処理 2009.12.14 <><><><>
#if 0 //2009.12.16 del 温度異常もガス即停止のため
                          if (gub_System_err == ON)
                          {
                              if (guc_Error_code == ABNORMAL_TEMP_ERR)
                              {
                                  if (gtt_Ctrl_flag.Err_gas == OFF)
                                  {
                                      gtt_Ctrl_flag.Err_gas = ON;
                                      gtt_Ctrl_counter.Err_gas = gtt_Internal_pack.Data.In.sAfterFlowTime * 20;
                                  } else if (gtt_Ctrl_counter.Err_gas <= 0) {
                                      gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF;
                                      GAS = OFF;
                                  }
                              }
                          }
#endif
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><> 2009.12.18 エラーレベル１，２発生時ＴＳ再起動を促す処理 <><><>
                          if (gtt_Ctrl_flag.Err_ts_cansel == ON && gub_System_err == OFF)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)
                              {
                                  gtt_Ctrl_flag.Err_ts_cansel   = OFF;
                                  gtt_Ctrl_flag.Ts_on_err_timer = OFF;
                                  gtt_Ctrl_flag.Ts_on_err       = OFF;
                                  
                              } else {
                                  puc_Sequence_mode = IDLING2;
                                  gtt_Ctrl_flag.Ts_on_err       = ON;
                                  gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //ガス停止 2009.12.09
                              }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          break;
                     case PRE_FLOW:
                          //高周波回路停止
                          HF_OUT = OFF; //2009.01.31
                          gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25

                          guc_R8_control.Bit1Sw.Over_lay = false; //重畳充電停止 2008.09.24

                          if (gtt_Ctrl_flag.Crater_repeat == ON) //クレータリピート2008.07.31
                          {
                              gtt_Ctrl_flag.Pre_flow = OFF;
                              gtt_Ctrl_flag.Pre_flow_time = OFF;
                          }
                          if (gtt_Ctrl_flag.After_flow_stop == ON)
                          {
                              gtt_Ctrl_flag.Pre_flow = OFF;
                              gtt_Ctrl_flag.Pre_flow_time = OFF;
                              gtt_Ctrl_flag.After_flow_stop = OFF;
                          }
                          if (gtt_Ctrl_flag.Pre_flow == OFF)
                          {
			      gtt_Ctrl_flag.Slow_down = OFF;
                              //puc_Sequence_mode = SLOW_DOWN;
                              puc_Sequence_mode = HF_CTRL;
		          }
		          //if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false || gtt_Ctrl_flag.Err_level1 == ON)  //アイドリング２へ 2008.09.01
		          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)  //2009.02.16
                          {
                              puc_Sequence_mode = IDLING; //2009.12.09
		                      gtt_Ctrl_flag.After_flow_time = OFF; //2008.07.29
                              gtt_Ctrl_flag.Pre_flow_time = OFF; //2009.12.08
                              gtt_Ctrl_flag.Pre_flow = OFF;      //2009.12.08
                              gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //ガス停止 2009.12.09
                          }
                          gtt_Ctrl_flag.After_flow_stop = OFF;
		          if (gtt_Ctrl_flag.Err_level1 == ON)  //アイドリング２へ 2009.02.16
                          {
                              puc_Sequence_mode = IDLING2;
                          }
		          if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリングへ 2008.11.17
                          {
                              //puc_Sequence_mode = IDLING;
                              puc_Sequence_mode = IDLING2; //2009.12.14
                          }
		          break;
                     case HF_CTRL: //2009.01.31
                          //if (gtt_Ctrl_flag.Initial_arc_start == ON)  //初期短絡で本溶接へ 2008.11.06
                          //if (gtt_Ctrl_flag.Lift_up_cd == ON)  //初期短絡で本溶接へ 2009.03.07 電検変更
                          if (gtt_Ctrl_flag.Start_process_end == ON)  //スタート処理完了で本溶接へ 2009.04.03
                          {
                              gtt_Ctrl_flag.Arc = ON;
                              gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME; //2009.03.16
                              //if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_CRATER)
                              //if (guc_Crater_mode_counter == SEQUENCE_NON) //2009.02.05
                              if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_ARC_SPOT) //2009.03.06
                              {
                                  gf_Output_correct_value = 0; //2009.02.16
                                  puc_Sequence_mode = MAIN_WELD;
                                  if (gtt_Ctrl_flag.Crater_repeat == ON)
                                  {
                                      puc_Sequence_mode = CRATER_WELD;
                                  }
                              }
                              //if (guc_Crater_mode_counter == SEQUENCE_INIT_CRATER)
                              //if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_INIT_CRATER) //2009.02.05
                              if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.02.05
                              {
                                  gf_Output_correct_value = 0; //2009.02.16
                                  puc_Sequence_mode = INITIAL_WELD;
                                  if (gtt_Ctrl_flag.Crater_repeat == ON || gtt_Ctrl_flag.Re_crater == ON) //2009.02.25
                                  {
                                      puc_Sequence_mode = CRATER_WELD;
                                      gtt_Ctrl_flag.Re_crater = OFF; //2009.02.25

                                      if (gtt_Ctrl_flag.Variable_crater_repaet == true) //2010.02.19
                                      {
                                          gtt_Ctrl_flag.Variable_crater_re_crater = true;
                                      }

                                  }
                              }
                              gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;
			  }
		          //if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false || gtt_Ctrl_flag.Err_level1 == ON)  //アイドリング２へ
		          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)  //アイドリング２へ
                          {
                              //puc_Sequence_mode = AFTER_FLOW;
                              gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                              puc_Sequence_mode = BURN_BACK;
                              
                              gtt_Ctrl_flag.Re_crater = OFF; //2009.08.27
                          }
                          gtt_Ctrl_flag.Sequence_crater = false; //クレータフラグのクリア 2008.07.29
                          gtt_Ctrl_flag.Arc_spot_time   = OFF;   //アークスポット時間フラグクリア 2009.03.06
		          if (gtt_Ctrl_flag.Err_level1 == ON)  //アイドリング２へ
                          {
                              puc_Sequence_mode = IDLING2;
                          }
		          if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリングへ
                          {
                              //puc_Sequence_mode = IDLING;
                              puc_Sequence_mode = IDLING2; //2009.12.16 
                          }
                          break;

                     case INITIAL_WELD:
                          //スタート回路動作
                          if (gtt_Ctrl_flag.Variable_crater_repaet == false) // 2009.03.16
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)      //TS OFFでバーンバックへ
                              {
                                  puc_Sequence_mode = UP_SLOPE;
                              }
                          }
                          //<><><><><> 可変反復機能 2009.03.14 <><><><><>
                          if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check = ON;
                                      gtt_Ctrl_counter.Cr_ts_check = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check <= 0) {         //０．５秒以上ＯＦＦならアップスロープ
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      puc_Sequence_mode = UP_SLOPE;
                                  }
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == ON)                  //０．５秒未満のＯＦＦ後０．５秒未満のＯＮで
                                  {                                                        //あれば、溶接終了
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      //puc_Sequence_mode = BURN_BACK;
                                      puc_Sequence_mode = MAIN_WELD; //2009.03.26
                                  }
                              }
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true && gtt_Ctrl_flag.Cr_ts_check == ON)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check2 = ON;
                                      gtt_Ctrl_counter.Cr_ts_check2 = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check2 <= 0) {         //０．５秒未満のＯＦＦ後０．５秒以上のＯＮなら
                                                                                            //ダウンスロープ
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      puc_Sequence_mode = DOWN_SLOPE;
                                  }
                              }
                              //***** ダブルクリック停止処理 2009.03.26 *****
		              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == false)  //タイマセット
                              {
                                  if (gtt_Ctrl_flag.W_click_timer == OFF)
                                  {
                                      gtt_Ctrl_flag.W_click_timer = ON;
                                      gtt_Ctrl_counter.W_click_timer = 0;
                                      gtt_Ctrl_flag.Crater_repeat_end = 0;
                                      gtt_Ctrl_flag.W_click_end = OFF;
                                  }
                              }
                              if (gtt_Ctrl_flag.W_click_timer == ON)
                              {
                                  if (gtt_Ctrl_counter.W_click_timer < W_CLICK_TIME)
                                  {
                                      if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Crater_repeat_end == 0)
                                      {
                                          gtt_Ctrl_flag.Crater_repeat_end = 1;
                                      }
                                      if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true && gtt_Ctrl_flag.Crater_repeat_end == 1)
                                      {
                                          gtt_Ctrl_flag.Crater_repeat_end = 2;
                                      }
                                      if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Crater_repeat_end == 2)
                                      {
                                          gtt_Ctrl_flag.Crater_repeat_end = 3;
                                      }
                                      if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true && gtt_Ctrl_flag.Crater_repeat_end == 3)
                                      {
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Crater_repeat_end = 0;
                                          gtt_Ctrl_flag.W_click_end = ON;
                                      }
                                   } else {
                                      gtt_Ctrl_flag.W_click_timer = OFF;
                                      gtt_Ctrl_flag.Crater_repeat_end = OFF;
                                   }
                              }
                              //**********************************************
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><><><><> 電流検出チェック　2007.1.24 <><><><><><><>  2007.1.26移植追加
                          //if (gtt_Fpga.Curr_result <= 1)
                          //if (gtt_Ctrl_flag.Hard_cd == OFF) //2009.03.07 電検をハード電検に変更
                          if (gtt_Ctrl_flag.Hard_cd == OFF || gss_Voltage_work > 480) //2010.03.18 電圧も併用
                          {
                              if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                              {
                                  //if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == false)
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == true) //2009.04.08 trueでアリに変更
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              } else { //ロボット接続の場合　2009.07.13
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) &&  gtt_Internal_pack.Data.In.fControl.Bit1Sw.Ac_recovery == true)
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              }
                          } else {
                          	  gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;
                              gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><><><><> 電極短絡チェック 2009.03.13 <><><><><><><>
                          if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                          {
                               if (gss_Select_dital[P_ELECTRODE_SHORT] == true)
                               {
                                   if (gss_Voltage_work < gtt_Special_menu.ss_Service_data[S_E_L_SHORT_LEVEL]) //短絡チェック
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          } else { //ロボット接続の場合　2009.07.13
                               if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Elrod_check == true)
                               {
                                   //if (gss_Voltage_work < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック
#if true	// ３００ＢＰ４は平気値を利用して判定する	<300BP4 Enhancements(Phase 1)>
                                   if (gtt_Fpga.Volt_result < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック 2009.07.24
#else
                                   //<><><> 2010.03.23 <><><>
                                   double work;
                                   work = (double)gtt_Internal_pack.Data.In.ucImprudenceVolt;
                                   if (gtt_Fpga.Volt_result_rms < (work * work)) //短絡チェック 2010.03.23
#endif
                                   //<><><><><><><><><><><><>
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                          //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON; //2009.07.23
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>
                         
		          if (gtt_Ctrl_flag.Err_level1 == ON)  //バーンバックへ 2008.09.01
                          {
                              gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                              puc_Sequence_mode = BURN_BACK;
                          }
		          if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリングへ 2008.11.17
                          {
                              //puc_Sequence_mode = IDLING;
                              puc_Sequence_mode = IDLING2; //2008.12.18 IDLING2に変更
                          }
                          break;
                     case UP_SLOPE: //2009.02.02
                          if (gtt_Ctrl_flag.Variable_crater_repaet == false) //2009.03.14
                          {
                              if (gtt_Ctrl_flag.Up_slop_curr_end == ON && gtt_Ctrl_flag.Up_slop_time_end == ON)
                              {
                                  gf_Output_correct_value = 0; //2009.02.16
                                  puc_Sequence_mode = MAIN_WELD;
                              }
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)      //TS ONでダウンスロープへ 2009.02.03
                              {
                                  puc_Sequence_mode = DOWN_SLOPE;
                              }
                          }
                          //<><><><><> 可変反復機能 2009.03.14 <><><><><>
                          if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check = ON;
                                      gtt_Ctrl_counter.Cr_ts_check = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check <= 0) {       //０．５秒以上ＯＮならダウンスロープ
                                      puc_Sequence_mode = DOWN_SLOPE;
                                      gtt_Ctrl_flag.Cr_ts_check = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                  }
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == ON)                  //０．５秒未満のＯＦＦ後０．５秒未満のＯＮで
                                  {                                                        //あれば、溶接終了
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                      puc_Sequence_mode = BURN_BACK;
                                      gtt_Ctrl_flag.Crater_repeat_end = 0; //2009.03.26
                                      gtt_Ctrl_flag.W_click_end = ON; //2009.03.26
                                  }
                              }
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Cr_ts_check == ON)
                              {
                                  //2009.03.26
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check2 = ON;
                                      gtt_Ctrl_counter.Cr_ts_check2 = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check2 <= 0) {         //０．５秒以上のＯＦＦなら
                                      puc_Sequence_mode = MAIN_WELD;                        //但しスロープ途中の電流をメインとする。
                                      gtt_Ctrl_flag.Cr_ts_check = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                  }
                                  //
                                                                                            //０．５秒未満のＯＮならメイン
                                     // puc_Sequence_mode = MAIN_WELD;                        //但しスロープ途中の電流をメインとする。
                                     // gtt_Ctrl_flag.Cr_ts_check = OFF;
                                     // gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                              }
                              if (gtt_Ctrl_flag.Up_slop_curr_end == ON && gtt_Ctrl_flag.Up_slop_time_end == ON) //時間切れで本電流に達してしまった場合
                              {
                                  gf_Output_correct_value = 0;
                                  puc_Sequence_mode = MAIN_WELD;
                                  gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                  gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                              }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><>


                          //<><><><><><> 電流検出チェック　2009.02.18 <><><><><><><>
                          //if (gtt_Fpga.Curr_result <= 1)
                          //if (gtt_Ctrl_flag.Hard_cd == OFF) //2009.03.07 電検をハード電検に変更
                          if (gtt_Ctrl_flag.Hard_cd == OFF || gss_Voltage_work > 480) //2010.03.18 電圧も併用
                          {
                              if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                              {
                                  //if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == false)
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == true) //2009.04.08 trueでアリに変更
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              } else { //ロボット接続の場合　2009.07.13
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) &&  gtt_Internal_pack.Data.In.fControl.Bit1Sw.Ac_recovery == true)
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              }
                          } else {
                          	      //gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;

                                  //<><><> 2010.02.18 自己保持区間は電流検出時間を１００ｍｓに変更 田中さん要望 <><><>
                                  if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //クレータ有、反復
                                  {
                          	          gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME2;
                          	          if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == true) //2010.03.18
                          	          {
                                           gtt_Ctrl_counter.Cd_check = 2000; //2010.03.18
                                      }
                                  } else {
                          	          gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;
                                  }
                                  //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

                                  gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><><><><> 電極短絡チェック 2009.03.13 <><><><><><><>
                          if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                          {
                               if (gss_Select_dital[P_ELECTRODE_SHORT] == true)
                               {
                                   if (gss_Voltage_work < gtt_Special_menu.ss_Service_data[S_E_L_SHORT_LEVEL]) //短絡チェック
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          } else { //ロボット接続の場合　2009.07.13
                               if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Elrod_check == true)
                               {
                                   //if (gss_Voltage_work < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック
#if true	// ３００ＢＰ４は平気値を利用して判定する	<300BP4 Enhancements(Phase 1)>
                                   if (gtt_Fpga.Volt_result < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック 2009.07.24
#else
                                   //<><><> 2010.03.23 <><><>
                                   double work;
                                   work = (double)gtt_Internal_pack.Data.In.ucImprudenceVolt;
                                   if (gtt_Fpga.Volt_result_rms < (work * work)) //短絡チェック 2010.03.23
#endif
                                   //<><><><><><><><><><><><>
                                   
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                          //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON; //2009.07.23
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          }
		          if (gtt_Ctrl_flag.Err_level1 == ON)  //バーンバックへ 2009.12.14
                          {
                              gtt_Ctrl_flag.Burn_back  = OFF;
                              puc_Sequence_mode = BURN_BACK;
                          }
		                  if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリング２へ 2009.12.15
                          {
                              puc_Sequence_mode = IDLING2;
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>
                          break;
                     case MAIN_WELD:
                          if (gtt_Ctrl_flag.Variable_crater_repaet == false)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)      //TS OFFでバーンバックへ
                              {
                                  if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_ARC_SPOT) //2009.03.06
                                  //if (guc_Crater_mode_counter == SEQUENCE_NON) //2008.10.21
                                  {
                                      gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                      puc_Sequence_mode = BURN_BACK;
                                  }
                                  //if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_INIT_CRATER)
                                  if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.02.05
                                  {
                                      gtt_Ctrl_flag.Sequence_crater = true;
                                  }
                              } else {
                                  if (gtt_Ctrl_flag.Sequence_crater == true)
                                  {
                                      //puc_Sequence_mode = CRATER_WELD;
                                      puc_Sequence_mode = DOWN_SLOPE; //2009.02.02
                                  }

                                  if (gtt_Ctrl_flag.Arc_spot_time == OFF) //アークスポット時間カウント
                                  {
                                      gtt_Ctrl_flag.Arc_spot_time = ON;
                                      gtt_Ctrl_counter.Arc_spot_time = gtt_Ditail_work.ss_Arc_spot_time * 20; //2009.03.06 変更 2009.03.16 unsigned -> signed
                                  } else if (gtt_Ctrl_counter.Arc_spot_time <= 0) {
                                    gtt_Ctrl_flag.Arc_spot_time_up = true;
                                  }

                              }
                          }
                          //<><><><><> 可変反復機能 2009.03.14 <><><><><>
                          if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check = ON;
                                      gtt_Ctrl_counter.Cr_ts_check = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check <= 0) {       //０．５秒以上ＯＮならダウンスロープ
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      puc_Sequence_mode = DOWN_SLOPE;
                                  }
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == ON)                  //０．５秒未満のＯＦＦ後０．５秒未満のＯＮで
                                  {                                                        //あれば、溶接終了
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                      puc_Sequence_mode = BURN_BACK;
                                      gtt_Ctrl_flag.Crater_repeat_end = 0; //2009.03.26
                                      gtt_Ctrl_flag.W_click_end = ON; //2009.03.26
                                  }
                              }
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Cr_ts_check == ON)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check2 = ON;
                                      gtt_Ctrl_counter.Cr_ts_check2 = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check2 <= 0) {         //０．５秒以上のＯＦＦなら
                                                                                            //アップスロープ
                                      puc_Sequence_mode = UP_SLOPE;
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                  }
                              }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><><><><> 電流検出チェック　2007.1.24 <><><><><><><>  2007.1.26移植追加
                          //if (gtt_Fpga.Curr_result <= 1)
                          //if (gtt_Ctrl_flag.Hard_cd == OFF) //2009.03.07 電検をハード電検に変更
                          if (gtt_Ctrl_flag.Hard_cd == OFF || gss_Voltage_work > 480) //2010.03.18 電圧も併用
                          {
                              if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                              {
                                  //if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == false)
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == true) //2009.04.08 trueでアリに変更
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              } else { //ロボット接続の場合　2009.07.13
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) &&  gtt_Internal_pack.Data.In.fControl.Bit1Sw.Ac_recovery == true)
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              }
                          } else {
                          	      //gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;
                                  //<><><> 2010.02.18 自己保持区間は電流検出時間を１００ｍｓに変更 田中さん要望 <><><>
                                  if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //クレータ有、反復
                                  {
                          	          gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME2;
                          	          if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == true) //2010.03.18
                          	          {
                                           gtt_Ctrl_counter.Cd_check = 2000; //2010.03.18
                                      }
                                  } else {
                          	          gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;
                                  }
                                  //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
                                  gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><><><><> 電極短絡チェック 2009.03.13 <><><><><><><>
                          if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                          {
                               if (gss_Select_dital[P_ELECTRODE_SHORT] == true)
                               {
                                   if (gss_Voltage_work < gtt_Special_menu.ss_Service_data[S_E_L_SHORT_LEVEL]) //短絡チェック
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          } else { //ロボット接続の場合　2009.07.13
                               if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Elrod_check == true)
                               {
                                   //if (gss_Voltage_work < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック
#if true	// ３００ＢＰ４は平気値を利用して判定する	<300BP4 Enhancements(Phase 1)>
                                   if (gtt_Fpga.Volt_result < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック 2009.07.24
#else
                                   //<><><> 2010.03.23 <><><>
                                   double work;
                                   work = (double)gtt_Internal_pack.Data.In.ucImprudenceVolt;
                                   if (gtt_Fpga.Volt_result_rms < (work * work)) //短絡チェック 2010.03.23
#endif
                                   //<><><><><><><><><><><><>
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                          //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON; //2009.07.23
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>
		          if (gtt_Ctrl_flag.Err_level1 == ON)  //バーンバックへ 2008.09.01
                          {
                              gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                              puc_Sequence_mode = BURN_BACK;
                          }
		          if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリングへ 2008.11.17
                          {
                              //puc_Sequence_mode = IDLING;
                              puc_Sequence_mode = IDLING2; //2008.12.18 IDLING2に変更
                          }
                          break;
                     case DOWN_SLOPE:
                          if (gtt_Ctrl_flag.Variable_crater_repaet == false) //2009.03.14
                          {
                              if (gtt_Ctrl_flag.Down_slop_curr_end == ON && gtt_Ctrl_flag.Down_slop_time_end == ON)
                              {
                                  gf_Output_correct_value = 0; //2009.02.16
                                  puc_Sequence_mode = CRATER_WELD;
                              }
		              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == false && guc_Crater_mode_counter == SEQUENCE_CRATER) //2009.02.06 
                              {
                                  gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                  puc_Sequence_mode = BURN_BACK;
                              }
		              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == false && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.02.06
                              {
                                  puc_Sequence_mode = UP_SLOPE;
                              }
                          }
                          //<><><><><> 可変反復機能 2009.03.14 <><><><><>
                          if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT)
                          {
#if 0
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check = ON;
                                      gtt_Ctrl_counter.Cr_ts_check = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check <= 0) {         //０．５秒以上ＯＦＦならクレータ
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      puc_Sequence_mode = CRATER_WELD;
                                  }
                              }
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true && gtt_Ctrl_flag.Cr_ts_check  == ON)
                              {
                                  gtt_Ctrl_flag.Cr_ts_check  = OFF;                  //０．５秒未満のＯＦＦ後ＯＮで
                                  gtt_Ctrl_flag.Cr_ts_check2 = OFF;                  //あれば、溶接終了
                                  puc_Sequence_mode = BURN_BACK;
                              }
#endif
                              //2009.03.26
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)
                              {
                                  gtt_Ctrl_flag.Cr_ts_check  = OFF;                  //０．５秒未満のＯＦＦ後ＯＮで
                                  gtt_Ctrl_flag.Cr_ts_check2 = OFF;                  //あれば、溶接終了
                                  puc_Sequence_mode = CRATER_WELD;
                              }

                              if (gtt_Ctrl_flag.Down_slop_curr_end == ON && gtt_Ctrl_flag.Down_slop_time_end == ON)
                              {
                                  gf_Output_correct_value = 0;
                                  puc_Sequence_mode = CRATER_WELD;
                                  gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                  gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                  gtt_Ctrl_flag.Crater_curr_start = ON;
                              }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><>
                          //<><><><><><> 電流検出チェック　2009.02.18 <><><><><><><>
                          //if (gtt_Fpga.Curr_result <= 1)
                          //if (gtt_Ctrl_flag.Hard_cd == OFF) //2009.03.07 電検をハード電検に変更
                          if (gtt_Ctrl_flag.Hard_cd == OFF || gss_Voltage_work > 480) //2010.03.18 電圧も併用
                          {
                              if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                              {
                                  //if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == false)
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == true) //2009.04.08 trueでアリに変更
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21

                                     gtt_Ctrl_flag.Re_crater = ON; //2009.12.17
                                  }
                              } else { //ロボット接続の場合　2009.07.13
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) &&  gtt_Internal_pack.Data.In.fControl.Bit1Sw.Ac_recovery == true)
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              }
                          } else {
                          	  gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;
                                  gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><><><><> 電極短絡チェック 2009.03.13 <><><><><><><>
                          if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                          {
                               if (gss_Select_dital[P_ELECTRODE_SHORT] == true)
                               {
                                   if (gss_Voltage_work < gtt_Special_menu.ss_Service_data[S_E_L_SHORT_LEVEL]) //短絡チェック
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          } else { //ロボット接続の場合　2009.07.13
                               if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Elrod_check == true)
                               {
                                   //if (gss_Voltage_work < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック
#if true	// ３００ＢＰ４は平気値を利用して判定する	<300BP4 Enhancements(Phase 1)>
                                   if (gtt_Fpga.Volt_result < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック 2009.07.24
#else
                                   //<><><> 2010.03.23 <><><>
                                   double work;
                                   work = (double)gtt_Internal_pack.Data.In.ucImprudenceVolt;
                                   if (gtt_Fpga.Volt_result_rms < (work * work)) //短絡チェック 2010.03.23
#endif
                                   //<><><><><><><><><><><><>
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                          //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON; //2009.07.23
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>
		          if (gtt_Ctrl_flag.Err_level1 == ON)  //バーンバックへ 2009.02.06
                          {
                              gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                              puc_Sequence_mode = BURN_BACK;
                          }
		                  if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリングへ 2009.12.16
                          {
                              puc_Sequence_mode = IDLING2;
                          }
                          break;
                     case CRATER_WELD:
                          gtt_Ctrl_flag.Re_crater = OFF; //2009.02.25
                          if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_CRATER) //2009.02.05
                          {
		              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == false || gtt_Ctrl_flag.Err_level1 == ON)  //バーンバックへ 2008.09.01
                              {
                                  gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                  puc_Sequence_mode = BURN_BACK;
                              }
                          }
                          //if (guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT)
                          if (gtt_Ctrl_flag.Variable_crater_repaet == false && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.03.14
                          {
                              if (gss_Select_dital[P_CRATER_ENDING] == true) //2009.02.18
                              {
		                  if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == false)  //タイマセット
                                  {
                                      if (gtt_Ctrl_flag.W_click_timer == OFF)
                                      {
                                          gtt_Ctrl_flag.W_click_timer = ON;
                                          gtt_Ctrl_counter.W_click_timer = 0;
                                          gtt_Ctrl_flag.Crater_repeat_end = 0;
                                          gtt_Ctrl_flag.W_click_end = OFF; //2009.02.25
                                      }
                                  }
                                  if (gtt_Ctrl_flag.W_click_timer == ON)
                                  {
                                      if (gtt_Ctrl_counter.W_click_timer < W_CLICK_TIME)
                                      {
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Crater_repeat_end == 0)
                                          {
                                              gtt_Ctrl_flag.Crater_repeat_end = 1;
                                          }
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true && gtt_Ctrl_flag.Crater_repeat_end == 1)
                                          {
                                              gtt_Ctrl_flag.Crater_repeat_end = 2;
                                          }
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Crater_repeat_end == 2)
                                          {
                                              gtt_Ctrl_flag.Crater_repeat_end = 3;
                                          }
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true && gtt_Ctrl_flag.Crater_repeat_end == 3)
                                          {
                                              gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                              puc_Sequence_mode = BURN_BACK;
                                              gtt_Ctrl_flag.Crater_repeat_end = 0;
                                              gtt_Ctrl_flag.W_click_end = ON; //2009.02.25
                                          }
                                       } else {
                                          gtt_Ctrl_flag.W_click_timer = OFF;
                                          gtt_Ctrl_flag.Crater_repeat_end = OFF;
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
                                          {
                                              puc_Sequence_mode = CRATER_WELD;
                                          }
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)
                                          {
                                              puc_Sequence_mode = UP_SLOPE;
                                          }
                                       }
                                   }
                               } else {
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
                                          {
                                              puc_Sequence_mode = CRATER_WELD;
                                          }
                                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)
                                          {
                                              puc_Sequence_mode = UP_SLOPE;
                                          }
                               }
                          }
                          //<><><><><> 可変反復機能 2009.03.14 <><><><><>
                      if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT)
                      {
                          if (gtt_Ctrl_flag.Crater_curr_start == OFF)
                          {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check = ON;
                                      gtt_Ctrl_counter.Cr_ts_check = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check <= 0) {       //０．５秒以上ＯＮならダウンスロープ
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      puc_Sequence_mode = DOWN_SLOPE;
                                      gtt_Ctrl_flag.Crater_curr_start = OFF; //2009.08.03
                                  }
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == ON)                  //０．５秒未満のＯＦＦ後０．５秒未満のＯＮで
                                  {                                                        //あれば、溶接終了
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                      puc_Sequence_mode = BURN_BACK;
                                      gtt_Ctrl_flag.Crater_repeat_end = 0; //2009.03.26
                                      gtt_Ctrl_flag.W_click_end = ON; //2009.03.26
                                      gtt_Ctrl_flag.Crater_curr_start = OFF; //2009.08.03
                                  }
                              }
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Cr_ts_check == ON)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check2 = ON;
                                      gtt_Ctrl_counter.Cr_ts_check2 = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check2 <= 0) {         //０．５秒以上のＯＦＦなら
                                                                                            //アップスロープ
                                      puc_Sequence_mode = UP_SLOPE;
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      gtt_Ctrl_flag.Crater_curr_start = OFF; //2009.08.03
                                  }
                              }
                          } else {  //2009.07.31
                            if (gtt_Ctrl_flag.Cr_ts_check3 == OFF)
                            {
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check = ON;
                                      gtt_Ctrl_counter.Cr_ts_check = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check <= 0) {       //０．５秒以上ＯＮならダウンスロープ
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check3 = ON;
                                      puc_Sequence_mode = CRATER_WELD;
                                  }
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == ON)                  //０．５秒未満のＯＦＦ後０．５秒未満のＯＮで
                                  {                                                        //あれば、溶接終了
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                      puc_Sequence_mode = BURN_BACK;
                                      gtt_Ctrl_flag.Crater_repeat_end = 0; //2009.03.26
                                      gtt_Ctrl_flag.W_click_end = ON; //2009.03.26
                                      gtt_Ctrl_flag.Crater_curr_start = OFF; //2009.08.03
                                  }
                              }
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Cr_ts_check == ON)
                              {
                                  if (gtt_Ctrl_flag.Cr_ts_check2 == OFF)
                                  {
                                      gtt_Ctrl_flag.Cr_ts_check2 = ON;
                                      gtt_Ctrl_counter.Cr_ts_check2 = TS_CHECK_TIME;
                                  } else if (gtt_Ctrl_counter.Cr_ts_check2 <= 0) {         //０．５秒以上のＯＦＦなら
                                                                                            //アップスロープ
                                      puc_Sequence_mode = UP_SLOPE;
                                      gtt_Ctrl_flag.Cr_ts_check  = OFF;
                                      gtt_Ctrl_flag.Cr_ts_check2 = OFF;
                                      gtt_Ctrl_flag.Crater_curr_start = OFF; //2009.08.03
                                  }
                              }
                            }
                            if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false && gtt_Ctrl_flag.Cr_ts_check3 == ON)
                            {
                                gtt_Ctrl_flag.Cr_ts_check3 = OFF;
                            }

                          }
                      }
                          //<><><><><><><><><><><><><><><><><><><><><><><>


                          //<><><><><><> 電流検出チェック　2007.1.24 <><><><><><><>  2007.1.26移植追加
                          //if (gtt_Fpga.Curr_result <= 1)
                          //if (gtt_Ctrl_flag.Hard_cd == OFF) //2009.03.07 電検をハード電検に変更
                          if (gtt_Ctrl_flag.Hard_cd == OFF || gss_Voltage_work > 480) //2010.03.18 電圧も併用
                          {
                              if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                              {
                                  //if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == false)
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) && gss_Select_dital[P_AC_ARC_RECOVERY] == true) //2009.04.08 trueでアリに変更
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                     
                                     gtt_Ctrl_flag.Re_crater = ON; //2009.08.27
                                     
                                     //<><><> 【ＮＯ３４】2010.03.10 <><><>
                                     if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT && gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == false)
                                     {
                                         gtt_Ctrl_flag.Re_crater = OFF;
                                     }
                                     //<><><><><><><><><><><><><><><><><><>
                                  }
                              } else { //ロボット接続の場合　2009.07.13
                                  if ((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) &&  gtt_Internal_pack.Data.In.fControl.Bit1Sw.Ac_recovery == true)
                                  {
                                      gtt_Ctrl_word.Hf_ctrl_code = ON; //高周波 2009.02.25
                                  }
                                  if(gtt_Ctrl_counter.Cd_check <= 0)
                                  {
                                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                                     gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                     puc_Sequence_mode = BURN_BACK; //2008.07.29　アーク切れ発生でバーンバックへ シミュレーション動作しないのでシミュレーション時削除　2008.10.21復帰
                                     gtt_Ctrl_flag.Arc_out_err = ON; //2008.10.21
                                  }
                              }
                          } else {
                          	  gtt_Ctrl_counter.Cd_check = CD_CHECK_TIME;
                                  gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          //<><><><><><> 電極短絡チェック 2009.03.13 <><><><><><><>
                          if (guc_Robot_connect_flag == false) //ロボット接続でない場合　2009.07.13
                          {
                               if (gss_Select_dital[P_ELECTRODE_SHORT] == true)
                               {
                                   if (gss_Voltage_work < gtt_Special_menu.ss_Service_data[S_E_L_SHORT_LEVEL]) //短絡チェック
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          } else { //ロボット接続の場合　2009.07.13
                               if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Elrod_check == true)
                               {
                                   //if (gss_Voltage_work < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック
#if true	// ３００ＢＰ４は平気値を利用して判定する	<300BP4 Enhancements(Phase 1)>
                                   if (gtt_Fpga.Volt_result < gtt_Internal_pack.Data.In.ucImprudenceVolt) //短絡チェック 2009.07.24
#else
                                   //<><><> 2010.03.23 <><><>
                                   double work;
                                   work = (double)gtt_Internal_pack.Data.In.ucImprudenceVolt;
                                   if (gtt_Fpga.Volt_result_rms < (work * work)) //短絡チェック 2010.03.23
#endif
                                   //<><><><><><><><><><><><>
                                   {
                                       if(gtt_Ctrl_counter.Electrode_short_check <= 0)
                                       {
                                          gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                                          gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                                          puc_Sequence_mode = BURN_BACK;
                                          gtt_Ctrl_flag.Arc_short = ON;
                                          //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON; //2009.07.23
                                       }
                                    } else {
                          	          gtt_Ctrl_counter.Electrode_short_check = ELECTRODE_SHORT_CHECK_TIME;
                                    }
                               }
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><><>

                          //if (gtt_Ctrl_flag.Initial_arc_start == ON) //gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd == ON)
                          if (gtt_Ctrl_flag.Lift_up_cd == ON)  //2008.10.08 電検を変更
                          {
			      if (gtt_Ctrl_flag.Srt1 == OFF) // 2008.03.11
			      {
			          gtt_Ctrl_flag.Srt1 = ON;
				  gtt_Ctrl_counter.Srt1 = START_UNIT_DELAY_TIME; //100μｓ／count 2008.11.14 1ms
			      } else if (gtt_Ctrl_counter.Srt1 <= 0) {
			      }
			      if (gtt_Ctrl_flag.Srt1 == ON && gtt_Ctrl_counter.Srt1 > 0)
			      {
			      }
			  } else {
			  }
                          //*** クレータリピート処理 2008.07.30 ***
                          //if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_INIT_CRATER)
                          if (guc_Crater_mode_counter == SEQUENCE_CRATER) //2009.02.05
                          {
                                gtt_Ctrl_flag.Crater_repeat_time = OFF;
                                gtt_Ctrl_flag.Crater_repeat = OFF;
                          }
		          if (gtt_Ctrl_flag.Err_level1 == ON)  //バーンバックへ 2009.02.06
                          {
                              gtt_Ctrl_flag.Burn_back  = OFF; //2009.04.11
                              puc_Sequence_mode = BURN_BACK;
                          }
		                  if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリングへ 2009.12.16
                          {
                              puc_Sequence_mode = IDLING2;
                          }
                          break;
                     case BURN_BACK:
                          //スタート回路動作
                          //**p10_4 = OFF; //2008.03.07
                          gtt_Ctrl_word.Hf_ctrl_code = OFF; //高周波 2009.02.25
                          if (gtt_Ctrl_flag.Burn_back == OFF)
                          {
                              //puc_Sequence_mode = IDLING;
                              puc_Sequence_mode = AFTER_FLOW; //2007.12.11
                              gtt_Ctrl_flag.After_flow_check = OFF;

                              //if (gtt_Ctrl_flag.Hand_stick_start == ON) //2009.03.06
                              if (gtt_Ctrl_flag.Hand_stick_start == ON || gtt_Ctrl_flag.Hand_stick_ready_time == ON) //2009.12.25
                              {
                                  //puc_Sequence_mode = IDLING;
                                  puc_Sequence_mode = IDLING2; //2009.12.25
                              }
                          }
                          break;
                     case AFTER_FLOW: //2007.12.11
                          guc_R8_control.Bit1Sw.Over_lay = false; //重畳充電停止 2008.09.16
                          //guc_R8_control.Bit1Sw.Over_lay = true; //重畳充電停止 2008.09.24 田中さん要請
                          
                          if (gtt_Ctrl_flag.After_flow == OFF)
                          {
                              puc_Sequence_mode = IDLING;
                              gtt_Ctrl_flag.After_flow_stop = OFF; //アフターフロー中断フラグOFF 2008.08.04
                            
		                  }
                          //if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == false) //2009.02.18
                          if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == false || gtt_Ctrl_flag.Arc_out_err == ON) //2009.02.25
                          {
                              gtt_Ctrl_flag.After_flow_check = ON;
                              gtt_Ctrl_flag.Arc_out_err = OFF;
                              gtt_Ctrl_flag.W_click_end = OFF; //2009.03.26
                              gtt_Ctrl_flag.Arc_short = OFF; //2009.12.21
                          }
		          //if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == true && gtt_Ctrl_flag.After_flow_check == ON)      //TS OFFでバーンバックへ
		          //if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == true && gtt_Ctrl_flag.After_flow_check == ON && gtt_Ctrl_flag.W_click_end == OFF) //2009.03.26
		          if (gtt_Ctrl_flag.Arc_short == OFF && gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     == true && gtt_Ctrl_flag.After_flow_check == ON && gtt_Ctrl_flag.W_click_end == OFF) //2009.12.21
                          {
                              //puc_Sequence_mode = SLOW_DOWN;
		              gtt_Ctrl_flag.After_flow_time = OFF; //2008.07.29
                              puc_Sequence_mode = IDLING; //2007.12.13
                              gtt_Ctrl_flag.After_flow_stop = ON; //アフターフロー中断フラグＯＮ 2008.07.31
                              gtt_Ctrl_flag.After_flow_check = OFF;
                              
                              //puc_Sequence_mode = SLOW_DOWN; //2008.07.31 アフターフロー中にトーチＯＮでスローダウン（プリフロー省略）
                          }
                          
                          //*** クレータリピート処理 2008.07.30 ***
                          //if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_INIT_CRATER)
                          if (guc_Crater_mode_counter == SEQUENCE_CRATER) //2009.02.05
                          {
#if 0 //2009.02.24
                              if (gtt_Ctrl_flag.Crater_repeat_time == OFF)
                              {
                                  gtt_Ctrl_flag.Crater_repeat_time = ON;
                                  gtt_Ctrl_flag.Crater_repeat = ON;
                                  gtt_Ctrl_counter.Crater_repeat_time = 400; //２秒間
                               } else if(gtt_Ctrl_counter.Crater_repeat_time <= 0) {
                                  gtt_Ctrl_flag.Crater_repeat = OFF;
                               }
#endif
                          }
		          if (gtt_Ctrl_flag.Err_level2 == ON)  //アイドリングへ 2008.11.17
                          {
                              //puc_Sequence_mode = IDLING;
                              puc_Sequence_mode = IDLING2; //2009.12.18
                          }
                          break;
                     case IDLING2:
                          puc_Sequence_mode = IDLING;
                          //スタート回路動作
                          guc_R8_control.Bit1Sw.Over_lay = false; //重畳充電停止 2008.09.24
                          //guc_R8_control.Bit1Sw.Over_lay = true; //重畳充電停止 2008.09.24 田中さん要請
                          break;
                     case HAND_STICK: //直流手溶接 2009.03.06
                          if (gtt_Ctrl_flag.Hand_stick_ready_time == OFF)
                          {
                              gtt_Ctrl_flag.Hand_stick_ready_time = ON;
                              gtt_Ctrl_counter.Hand_stick_ready_time = 500;
                              gtt_Ctrl_flag.Hand_stick_start = OFF;
                          } else if (gtt_Ctrl_counter.Hand_stick_ready_time <= 0) {
                              gtt_Ctrl_flag.Hand_stick_start = ON;
                          }
                          if (guc_Method_condition_data != STD_HAND_METHOD)
                          {
                              gtt_Ctrl_flag.Burn_back = OFF;
                              gtt_Ctrl_flag.Hand_restart = OFF; //2009.03.30
                              puc_Sequence_mode = BURN_BACK;
                          }
                          //直流手溶接時一旦アークスタート後、アークが切れた場合再スタート処理 2009.03.30
                          if (gtt_Ctrl_flag.Hard_cd == ON)
                          {
                              gtt_Ctrl_flag.Hand_restart = ON;
                              gtt_Ctrl_flag.Hand_restart_wait = OFF;
                          }
                          if (gtt_Ctrl_flag.Hand_restart == ON)
                          {
                              if (gtt_Ctrl_flag.Hard_cd == OFF)
                              {
                                  if (gtt_Ctrl_flag.Hand_restart_wait == OFF)
                                  {
                                      gtt_Ctrl_flag.Hand_restart_wait = ON;
                                      gtt_Ctrl_counter.Hand_restart_wait = 500; //500ms
                                      //LED4 = OFF; 2009.07.23 test del
                                  } else if (gtt_Ctrl_counter.Hand_restart_wait <= 0) {
                                      gtt_Ctrl_flag.Burn_back = OFF;
                                      puc_Sequence_mode = BURN_BACK;
                                  }
                              }
                          }

                          //<><><><> エラー発生時の停止処理 2009.12.15 <><><><>
                          if (gub_System_err == ON)
                          {
                              gtt_Ctrl_flag.Hand_stick_ready_time = OFF;
                              gtt_Ctrl_flag.Hand_restart = OFF;
                              gtt_Ctrl_flag.Burn_back = OFF;
                              gtt_Ctrl_flag.Hand_restart = OFF;
                              puc_Sequence_mode = BURN_BACK;
                          }


                          break;

                     default:
                          break;
            }
            return (puc_Sequence_mode);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_mag_sequence_dicision_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

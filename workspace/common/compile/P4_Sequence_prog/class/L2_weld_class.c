//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｗｅｌｄ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      溶接
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
//コントロールワード：gui_Ctrl_word
// 15:シーケンス停止  14:  13:            12:                 11:                10:             9:           8:
//  7:                 6:   5:高周波制御   4:溶接電源動作指令  3:インバータ制御   2:モータ制御   1:ガス制御   0:ＭＧ制御
extern  int         DC_PMODE;

Bit16 weld_class (unsigned char xuc_Sequence_mode , Bit16 xtt_Ctrl_word)
{
     unsigned char puc_Sequence_mode;
     Bit16 ptt_Ctrl_word;
     unsigned short int Parmdummy;
     unsigned short int LastSend_11;


     puc_Sequence_mode = xuc_Sequence_mode;
     ptt_Ctrl_word     = xtt_Ctrl_word;

#define PC_TEST 0

     switch (puc_Sequence_mode)
     {
             case IDLING:
                  //********************* インチング機能 2006.2.15 ihara *******************
#if PC_TEST
                  if (gtt_Internal_pack.Data.bRS422Connection || gtt_Internal_pack.Data.bRS232Connection) //ロボット接続時有効
#else
                  //if (gtt_Internal_pack.Data.bRS422Connection) //ロボット接続時有効
                  if (gtt_Internal_pack.Data.bRS422Connection || ComuniPackRemo.Data.bRS422Connection || (gb_Controller_UnConnect)) //2007.12.07  Phase26 by @Tny 2008.10.23
#endif
                  {
                  }
                  
                  //**************************** スティック処理 ****************************
                  if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check == ON && gtt_Ctrl_flag.Stick_start == OFF)// && ptt_Ctrl_word.Inverter_ctrl_code == OFF)// && gtt_Ctrl_flag.Arc == OFF)
                  {
                      LED4 = OFF; //test 2009.07.24
                      //<><><><><> スティックチェックを一定時間受け取らない仕様に変更　2007.2.24 <><><><><>
                      if (gtt_Ctrl_flag.Stick_check_delay_time == OFF)
                      {
		          gtt_Ctrl_flag.Stick_check_delay_time = ON;
		          gtt_Ctrl_counter.Stick_check_delay_time = STICK_CHECK_DELAY_TIME;
		      } else if (gtt_Ctrl_counter.Stick_check_delay_time <= 0) {
                          //***** 第２バーンバック処理が有る場合のスティック処理追加 2008.12.11 *****
                          if (gtt_Ctrl_flag.Burn_back2 == true && gtt_Ctrl_flag.Burn_back2_dsp_end == true)
                          {
                              gtt_Ctrl_flag.Burn_back2_dsp_end = false;
                              ptt_Ctrl_word.Stick_check_code    = ON; //スティック・タッチ
                              gtt_Ctrl_word_bkup.Stick_check_code = OFF;  //溶接電源制御コードチェック
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_release == OFF)
                              {
                                  ptt_Ctrl_word.Stick_release_code  = OFF; //スティック＆リリース
                              } else {
                                  ptt_Ctrl_word.Stick_release_code  = ON; //スティック＆リリース
                              }
                              gtt_Ctrl_flag.Stick_start         = ON; //スティック開始
                              gtt_Ctrl_flag.Stick_on_off_check = OFF; //2007.3.23 stick_err_memberから移動
                          }
                          if (gtt_Ctrl_flag.Burn_back2 == false)
                          {
                              gtt_Ctrl_flag.Burn_back2_dsp_end = OFF;
                              ptt_Ctrl_word.Stick_check_code    = ON; //スティック・タッチ
                              gtt_Ctrl_word_bkup.Stick_check_code = OFF;  //溶接電源制御コードチェック
                              if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_release == OFF)
                              {
                                  ptt_Ctrl_word.Stick_release_code  = OFF; //スティック＆リリース
                              } else {
                                  ptt_Ctrl_word.Stick_release_code  = ON; //スティック＆リリース
                              }
                              gtt_Ctrl_flag.Stick_start         = ON; //スティック開始
                              gtt_Ctrl_flag.Stick_on_off_check = OFF; //2007.3.23 stick_err_memberから移動

                          }
                          //*************************************************************************
                      }
                      //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
                  } else if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check == OFF) {
                      gtt_Ctrl_flag.Stick_start         = OFF;
                      gtt_Ctrl_flag.Stick_end           = OFF;
                      ptt_Ctrl_word.Stick_check_code    = OFF; //スティック・タッチ
                      ptt_Ctrl_word.Stick_release_code  = OFF; //スティック＆リリース
                      //ComuniPack.Data.From.fErrorCode1.Bit1Sw.b0 = OFF;
                      //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b0 = OFF;
                      ComuniPack.Data.From.fErrorCode1.Bit1Sw.b2 = OFF;            //2009.07.14
                      gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = OFF;      //2009.07.14
                      gtt_Ctrl_flag.Stick_on_off_check = OFF; //2007.3.23 stick_err_memberから移動

                      gtt_Ctrl_flag.Stick_check_delay_time = OFF; //2007.2.24追加
                  }
                  //************************************************************************
                  gtt_Ctrl_flag.Initial_arc_start = OFF; //2008.03.11
                  gtt_Ctrl_flag.Lift_up_cd = OFF;        //2008.10.08
                  gtt_Ctrl_flag.Start_process_end = OFF; //2009.04.03
                  //交流時直流制御区間フラグの初期化 2008.09.22
                  gtt_Ctrl_flag.AC_control = true;
                  gtt_Ctrl_flag.DC_control_timer = OFF;
                  gtt_Ctrl_flag.Dc_control_timer_end = OFF;//2008.10.08
                  gtt_Ctrl_flag.Dc_control_timer_one_shot = OFF; //2008.10.08

                  //***** 2008.12.08 アイドリング中に変化したものについては溶接出力開始で反映されるので、反映処理をする必要がないため *****
                  gtt_Ctrl_flag.Hpi_control = false;
                  //***********************************************************************************************************************
                  ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止 2009.01.31
                  gtt_Ctrl_flag.Arc = OFF; //2009.02.18

                  //エキスパートモード
                  gtt_Ctrl_flag.Ref_voltage = OFF; //2009.02.20
                  gtt_Ctrl_flag.Ref_voltage_result = OFF; //2009.02.20
                  gtt_Ctrl_flag.Ref_voltage_add_start = OFF; //リファレンス電圧積算開始フラグ OFF 2010.01.12


                  gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                  PLS_OUT = OFF; //2009.04.11
                  gtt_Ctrl_flag.Mix_wave_current_time = OFF; //2009.04.11


                  gtt_Ctrl_flag.Variable_crater_re_crater = false; //2010.02.19


             break;
             case PRE_FLOW:
                      //LED4 = OFF;
                  ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止 2009.01.31
                  gtt_Ctrl_flag.Burn_back2_dsp_end = false; //2008.12.11　第２バーンバック有り時スティックチェックされることに備えて、溶接が開始されたら常にこのフラグをＯＦＦする。
                  gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = ON; //ガス起動 2007.12.12
                  if (gtt_Ctrl_flag.Pre_flow_time == OFF)
                  {
		      gtt_Ctrl_flag.Pre_flow_time = ON;
		      //gtt_Ctrl_counter.Pre_flow_time = gtt_Ditail_work.us_Pre_flow_time * 10; //2008.10.09   * 10 2009.01.28
		      //gtt_Ctrl_counter.Pre_flow_time = gtt_Ditail_work.us_Pre_flow_time * 20; //2009.02.23 時間が半分だった
		      gtt_Ctrl_counter.Pre_flow_time = gtt_Internal_pack.Data.In.sPreFlowTime * 20; //2009.05.14
                      if (guc_Robot_connect_flag == true) //2009.07.17
                      {
		          gtt_Ctrl_counter.Pre_flow_time = 10; //ロボット接続時は強制的に１０＊５ｍｓとする。
                      }
		  } else if (gtt_Ctrl_counter.Pre_flow_time <= 0) {
                     gtt_Ctrl_flag.Pre_flow_time = OFF;
                     gtt_Ctrl_flag.Pre_flow = OFF;
                  }
                  //高周波起動タイマ初期化 2009.01.31
                  gtt_Ctrl_flag.Hf_2sec_timer = OFF;
		  break;
             case HF_CTRL: //2009.01.31
                  gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = ON; //ガス起動 2007.12.12
                  if (gtt_Ctrl_flag.Hf_2sec_timer == OFF)
                  {
                      gtt_Ctrl_flag.Hf_2sec_timer    = ON;
                      gtt_Ctrl_counter.Hf_2sec_timer = HF_2SEC_TIME; //高周波２秒タイマセット
                      gtt_Ctrl_flag.Hf_30sec_timer   = OFF;          //３０秒間欠動作開始準備
                      gtt_Ctrl_flag.Hf_exec          = ON;           //高周波起動
                  } else if (gtt_Ctrl_counter.Hf_2sec_timer <= 0){
                      //間欠動作処理
                      if (gtt_Ctrl_flag.Hf_30sec_timer == OFF)
                      {
                          gtt_Ctrl_flag.Hf_30sec_timer          = ON;
                          gtt_Ctrl_counter.Hf_30sec_timer       = HF_30SEC_TIME; //高周波３０秒タイマセット
                          gtt_Ctrl_flag.Hf_30sec_interval_timer = OFF;  //間欠動作開始までインターバルタイマセット準備
                          gtt_Ctrl_flag.Hf_exec                 = OFF; //高周波停止
                          gtt_Ctrl_flag.Hf_intermittent_set     = OFF; //間欠動作不許可
                      } else if (gtt_Ctrl_counter.Hf_30sec_timer <= 0){
                          gtt_Ctrl_flag.Hf_exec                 = OFF; //高周波停止
                          gtt_Ctrl_flag.Hf_2sec_timer           = OFF; //次回高周波起動に備える。
                          gtt_Ctrl_flag.Hf_intermittent_set     = OFF; //間欠動作不許可
                          gtt_Ctrl_flag.Arc_start_err1          = ON;  //間欠動作終了後にアークスタートしない場合エラー６発生 2009.02.06
                      }
                      //間欠動作開始までの休止期間
                      if (gtt_Ctrl_flag.Hf_30sec_interval_timer == OFF)
                      {
                          gtt_Ctrl_flag.Hf_30sec_interval_timer    = ON;
                          gtt_Ctrl_counter.Hf_30sec_interval_timer = HF_30SEC_INTERVAL_TIME; //間欠動作開始までインターバルタイマセット
                      } else if (gtt_Ctrl_counter.Hf_30sec_interval_timer <= 0 && gtt_Ctrl_flag.Hf_intermittent_set == OFF){
                          gtt_Ctrl_flag.Hf_intermittent_set        = ON; //間欠動作許可
                          gtt_Ctrl_flag.Hf_intermittent_on         = OFF;
                          gtt_Ctrl_flag.Hf_intermittent_off        = ON;
                      }
                      //間欠動作
                      if (gtt_Ctrl_flag.Hf_intermittent_set == ON) //間欠動作
                      {
                          //間欠動作タイマ
                          if (gtt_Ctrl_flag.Hf_intermittent_on == OFF)
                          {
                              gtt_Ctrl_flag.Hf_intermittent_on    = ON;
                              gtt_Ctrl_counter.Hf_intermittent_on = HF_INTERMITTENT_TIME;
                              gtt_Ctrl_flag.Hf_exec               = ON; //高周波起動
                              gtt_Ctrl_flag.Hf_intermittent_off   = OFF;
                          } else if (gtt_Ctrl_counter.Hf_intermittent_on <= 0){
                              //間欠停止タイマ
                              if (gtt_Ctrl_flag.Hf_intermittent_off == OFF)
                              {
                                  gtt_Ctrl_flag.Hf_intermittent_off    = ON;
                                  gtt_Ctrl_counter.Hf_intermittent_off = HF_INTERMITTENT_TIME;
                                  gtt_Ctrl_flag.Hf_exec                = OFF; //高周波停止
                              } else if (gtt_Ctrl_counter.Hf_intermittent_off <= 0){
                                  gtt_Ctrl_flag.Hf_intermittent_on     = OFF;
                              }
                          }
                      }
                      
                  }
//2009.04.09                  if (gtt_Ctrl_flag.Hf_exec == ON) //高周波の起動
                  if (guc_Robot_connect_flag == false) //ロボット接続なし 2009.07.13
                  {
                      if (gtt_Ctrl_flag.Hf_exec == ON && gtt_Ctrl_flag.Lift_up_cd == OFF) //高周波の起動//2009.04.09 LIFTUP電検でHFｵﾌする
                      {
                          ptt_Ctrl_word.Hf_ctrl_code = ON;  //高周波起動
                      } else {
                          ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止
                      }
                  } else { //ロボット接続有 2009.07.13
                      if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Hf_ctrl == true)
                      {
                          if (gtt_Ctrl_flag.Hf_exec == ON && gtt_Ctrl_flag.Lift_up_cd == OFF) //高周波の起動//2009.04.09 LIFTUP電検でHFｵﾌする
                          {
                              ptt_Ctrl_word.Hf_ctrl_code = ON;  //高周波起動
                          } else {
                              ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止
                          }
                      } else {
                          ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止
                      }
                  }

                  //田中さんがホット動作を作成するまで一時的なもの 2009.01.31
                  //<><><><><><><><><><>スローダウン起動処理<><><><><><><><><><>
                  if (gtt_Ctrl_flag.Slow_down == OFF)
                  {
                     PWELDTABLE  pWT = GetWeldTable( );  //test 復帰　2006.10.25

                     //<><><><><>２秒以内のＴＳ起動時の処理<><><><><>  REPEAT2007.1.12
                     // モータディレイ　０
                     // 半固定パラメータのＤＳＰへ再送（一部のデータが半分になるため）
                     if( gtt_Ctrl_flag.Repeat_weld == ON )
                     {
                         //isContArc = 1;         //２秒以内の繰り返しセット
                         isContArc = 0;         //２秒以内の繰り返しセット 2009.03.02
                         isEnbDelay = 0;        //モータディレイをキャンセル
                     } else {
                         isContArc = 0;         //通常スタート時（繰り返し溶接ではない）
                         isEnbDelay = 1;        //モータディレイセット
                     }
                     gtt_Ctrl_flag.Repeat_weld = OFF;

                     //************************** ホット電流転送処理 2009.02.13 ************************
#if 0 //2009.02.20 del
                     if ((guc_Method_condition_data == STD_DC_METHOD)||(guc_Method_condition_data == EXP_DC_METHOD)) 
                     {
//-------------------------------
// 「微弱モード」の追加		2011.10.28
//-------------------------------
#if true
                          if(gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //微弱
                          {
                              gf_Hot_current_level = 60.0 * HOTCUR * 0.25;
                          }
                          else if(gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //弱
                          {
                              gf_Hot_current_level = 60.0 * HOTCUR * 0.5;
                          }
                          else if(gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //標準
                          {
                              gf_Hot_current_level = 60.0 * HOTCUR;
                          }
                          else if(gss_Select_dital[P_HOT_CURR_LEVEL] == 3) //強
                          {
                              gf_Hot_current_level = 60.0 * HOTCUR * 1.5;
                          }
#else
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //弱
                          {
                              gf_Hot_current_level = 60.0 * HOTCUR * 0.5;
                          }
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //標準
                          {
                              gf_Hot_current_level = 60.0 * HOTCUR;
                          }
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //強
                          {
                              gf_Hot_current_level = 60.0 * HOTCUR * 1.5;
                          }
#endif
//-------------------------------
//
//-------------------------------
                     }
#endif
                     //******直流も交流と同じ考えかたにする 2009.02.20*********
                     if ((guc_Method_condition_data == STD_DC_METHOD)||(guc_Method_condition_data == EXP_DC_METHOD)) 
                     {
                        {
                          float Current_level;
                          //if (guc_Crater_mode_counter == SEQUENCE_NON) //クレータ無
                          if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_ARC_SPOT) //クレータ無,アークスポット 2009.03.16
                          {
                              //if (gtt_Internal_pack.Data.In.usWeldingCurr >=0 && gtt_Internal_pack.Data.In.usWeldingCurr <= 49)
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=0 && gtt_Internal_pack.Data.In.usWeldingCurr <= 19) //2009.04.10
                              {
                                  Current_level = 30.0; //2009.04.10
                                  //Current_level = 60.0; //2009.03.02
                              }
                              //if (gtt_Internal_pack.Data.In.usWeldingCurr >=50 && gtt_Internal_pack.Data.In.usWeldingCurr <= 99)
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=20 && gtt_Internal_pack.Data.In.usWeldingCurr <= 99) //2009.04.10
                              {
                                  Current_level = 60.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=100 && gtt_Internal_pack.Data.In.usWeldingCurr <= 300)
                              {
                                  //Current_level = 90;
                                  Current_level = 60; //2009.03.02
                                  //Current_level = (float)gtt_Internal_pack.Data.In.usWeldingCurr;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=301 && gtt_Internal_pack.Data.In.usWeldingCurr <= 500) //2009.12.28 500BP4
                              {
                                  Current_level = 100;
                              }
                              
                              //<><><> パルス有り時はパルス指令値に従ってホット電流を決定する 2009.08.26 <><><>
                              if (guc_Pulse_mode_data == 1)
                              {
                                
                                  if (gtt_Internal_pack.Data.In.usIP >=0 && gtt_Internal_pack.Data.In.usIP <= 19)
                                  {
                                      Current_level = 30.0;
                                  }
                                  if (gtt_Internal_pack.Data.In.usIP >=20 && gtt_Internal_pack.Data.In.usIP <= 99)
                                  {
                                      Current_level = 60.0;
                                  }
                                  if (gtt_Internal_pack.Data.In.usIP >=100 && gtt_Internal_pack.Data.In.usIP <= 300)
                                  {
                                      Current_level = 60.0;
                                  }
                                  if (gtt_Internal_pack.Data.In.usIP >=301 && gtt_Internal_pack.Data.In.usIP <= 500) //2009.12.28 500BP4
                                  {
                                      Current_level = 100.0;
                                  }
                              }
                              
                          }
                          if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //クレータ有、反復
                          {
                              //if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=0 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 49)
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=0 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 19) //2009.04.10
                              {
                                  Current_level = 30.0; //2009.04.10
                                  //Current_level = 60.0; //2009.03.02
                              }
                              //if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=50 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 99)
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=20 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 99) //2009.04.10
                              {
                                  Current_level = 60.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=100 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 300)
                              {
                                  //Current_level = 90.0;
                                  Current_level = 60.0; //2009.03.02
                                  //Current_level = (float)gtt_Internal_pack.Data.In.usWeldingInitCurr;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=301 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 500)
                              {
                                  Current_level = 100.0;
                              }
                          }
//-------------------------------
// 「微弱モード」の追加		2011.10.28
//-------------------------------
#if true
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //微弱
                          {
                              gf_Hot_current_level = Current_level * 0.25;
                          }
                          else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //弱
                          {
                              gf_Hot_current_level = Current_level * 0.5;
                          }
                          else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //標準
                          {
                              gf_Hot_current_level = Current_level;
                          }
                          else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 3) //強
                          {
                              gf_Hot_current_level = Current_level * 1.5;
                          }
#else
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //弱
                          {
                              //gf_Hot_current_level = Current_level * HOTCUR * 0.5;
                              gf_Hot_current_level = Current_level * 0.5; //2009.04.03
                          }
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //標準
                          {
                              //gf_Hot_current_level = Current_level * HOTCUR;
                              gf_Hot_current_level = Current_level; //2009.04.03
                          }
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //強
                          {
                              //gf_Hot_current_level = Current_level * HOTCUR * 1.5;
                              gf_Hot_current_level = Current_level * 1.5; //2009.04.03
                          }
#endif
//-------------------------------
//
//-------------------------------
                        }
                     }
                     //****************************************************************

                     if ((guc_Method_condition_data == STD_AC_METHOD)||(guc_Method_condition_data == EXP_AC_METHOD)||(guc_Method_condition_data == STD_MIX_METHOD)) 
                     {
                        {
                          float Current_level;
                          //if (guc_Crater_mode_counter == SEQUENCE_NON) //クレータ無
                          if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_ARC_SPOT) //クレータ無,アークスポット 2009.03.16
                          {
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=0 && gtt_Internal_pack.Data.In.usWeldingCurr <= 49)
                              {
                                  Current_level = 50.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=50 && gtt_Internal_pack.Data.In.usWeldingCurr <= 99)
                              {
                                  Current_level = 75.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=100 && gtt_Internal_pack.Data.In.usWeldingCurr <= 300)
                              {
                                  Current_level = 100.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingCurr >=301 && gtt_Internal_pack.Data.In.usWeldingCurr <= 500) //2009.12.28 500BP4
                              {
                                  Current_level = 100.0;
                              }
                              //<><><> パルス有り時はパルス指令値に従ってホット電流を決定する 2009.08.26 <><><>
                              if (guc_Pulse_mode_data == 1)
                              {
                                
                                  if (gtt_Internal_pack.Data.In.usIP >=0 && gtt_Internal_pack.Data.In.usIP <= 49)
                                  {
                                      Current_level = 50.0;
                                  }
                                  if (gtt_Internal_pack.Data.In.usIP >=50 && gtt_Internal_pack.Data.In.usIP <= 99)
                                  {
                                      Current_level = 75.0;
                                  }
                                  if (gtt_Internal_pack.Data.In.usIP >=100 && gtt_Internal_pack.Data.In.usIP <= 300)
                                  {
                                      Current_level = 100.0;
                                  }
                                  if (gtt_Internal_pack.Data.In.usIP >=301 && gtt_Internal_pack.Data.In.usIP <= 500) //2009.12.28 500BP4
                                  {
                                      Current_level = 100.0;
                                  }
                              }
                              
                              
                          }
                          if (guc_Crater_mode_counter == SEQUENCE_CRATER || guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //クレータ有、反復
                          {
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=0 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 49)
                              {
                                  Current_level = 50.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=50 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 99)
                              {
                                  Current_level = 75.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=100 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 300)
                              {
                                  Current_level = 100.0;
                              }
                              if (gtt_Internal_pack.Data.In.usWeldingInitCurr >=301 && gtt_Internal_pack.Data.In.usWeldingInitCurr <= 500)
                              {
                                  Current_level = 100.0;
                              }
                          }
//-------------------------------
// 「微弱モード」の追加		2011.10.28
//-------------------------------
#if true
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //微弱
                          {
                              gf_Hot_current_level = Current_level * 0.25;
                          }
                          else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //弱
                          {
                              gf_Hot_current_level = Current_level * 0.5;
                          }
                          else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //標準
                          {
                              gf_Hot_current_level = Current_level;
                          }
                          else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 3) //強
                          {
                              gf_Hot_current_level = Current_level * 1.5;
                          }
#else
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //弱
                          {
                              //gf_Hot_current_level = Current_level * HOTCUR * 0.5;
                              gf_Hot_current_level = Current_level * 0.5; //2009.04.03
                          }
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //標準
                          {
                              //gf_Hot_current_level = Current_level * HOTCUR;
                              gf_Hot_current_level = Current_level; //2009.04.03
                          }
                          if (gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //強
                          {
                              //gf_Hot_current_level = Current_level * HOTCUR * 1.5;
                              gf_Hot_current_level = Current_level * 1.5; //2009.04.03
                          }
#endif
//-------------------------------
//
//-------------------------------
                        }
                     }
                      //******************************************************************

                     WeldAdjOut_Proc( isContArc );           //半固定パラメータのＤＳＰへの再送
                     //<><><><><><><><><><><><><><><><><><><><><><><>

                     gtt_Ctrl_flag.Slow_down = ON;
                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                     gtt_Ctrl_flag.Weld_end = OFF;
                     //溶接出力起動時の溶接条件リセット
                     //SRVCTL          = 0; 2019.04.02 del ihara
                     SetWeldStatus( 1 );     		             //スローダウン中 2006.3.7
                     SetMotorStatus( 1 );                            //送給中
                     
                     //**** 指令値の選択 2008.08.05 ****
                     if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_ARC_SPOT) //2009.03.27
                     {
                         if (guc_Pulse_mode_data == 0) //2009.03.27
                         {
                             //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt);
                             ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                         } else { //2009.03.27
                             //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usIP , gtt_Internal_pack.Data.In.usWeldingVolt); //2009.03.27
                             ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usIP) , gtt_Internal_pack.Data.In.usWeldingVolt);//2010.02.19
                         }
                         if (gtt_Ctrl_flag.Crater_repeat == ON)
                         {
                             //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCratCurr , gtt_Internal_pack.Data.In.usWeldingCratVolt);
                             ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
                         }
                     }
                     if (guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT || guc_Crater_mode_counter == SEQUENCE_CRATER) //2009.03.27
                     {
                         //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingInitCurr , gtt_Internal_pack.Data.In.usWeldingInitVolt);
                         ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingInitCurr) , gtt_Internal_pack.Data.In.usWeldingInitVolt); //2010.02.19
                         if (gtt_Ctrl_flag.Crater_repeat == ON)
                         {
                             //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCratCurr , gtt_Internal_pack.Data.In.usWeldingCratVolt);
                             ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
                         }
                     }

                     ctlclsDrctSet( );
                     ctlclsWeldStart( );                             //スローダウン値セット
                     wipReCalc( );
                     sipReCalc( );
                     wipReset( );
                     sipReset( );
                  
                     IMJTOCR4  = 0x07; //2006.2.15 割禁　ihara
	             sspdSend();
	             IMJTOCR4  = 0x05;                             //割許
                     ptt_Ctrl_word.Motor_ctrl_code    = ON;             //モータ起動
                     ptt_Ctrl_word.Inverter_ctrl_code = ON;             //インバータ起動
                     ptt_Ctrl_word.Welder_ctrl_code   = ON;             //溶接電源動作指令
                     //gtt_Ctrl_flag.Arc = ON;

                     gtt_Ctrl_flag.Motor_delay     = OFF;              //モータディレイセット
                     gtt_Ctrl_flag.Motor_delay_end = OFF;

                  }

                  //初期電流のセット 2009.02.02
                  gf_Up_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingInitCurr;
                  gf_Up_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usWeldingInitCurr;
                  gf_Down_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingInitCurr; //2009.03.26
                  gf_Down_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usWeldingInitCurr; //2009.03.26

#if 0 //2010.02.24 del
                  if (gtt_Ctrl_flag.Variable_crater_re_crater == true) //2010.02.19
                  {
                      gtt_Ctrl_flag.Variable_crater_re_crater = false;
                      gf_Down_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
                      gf_Down_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
                  }
#endif

                  //2009.02.24
                  gtt_Ctrl_counter.Frequence_set_time = (unsigned long)(10000 / (unsigned long)(gtt_Internal_pack.Data.In.usPulseFreq)); //2009.03.27 short->long
                  gtt_Ctrl_counter.A_condition_set_time = (gtt_Ctrl_counter.Frequence_set_time * (100 - gtt_Internal_pack.Data.In.usPulseDuty)) / 100; //2009.02.27
                  gtt_Ctrl_counter.B_condition_set_time = gtt_Ctrl_counter.Frequence_set_time - gtt_Ctrl_counter.A_condition_set_time;
                  gtt_Ctrl_counter.Frequence_time = gtt_Ctrl_counter.Frequence_set_time;
                  gtt_Ctrl_counter.B_condition_time = gtt_Ctrl_counter.B_condition_set_time;
                  gtt_Ctrl_flag.Wave_current_time = OFF; //2009.03.27
                  
                  gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11


                  //エキスパートモード 2010.01.12追加
                  gtt_Ctrl_flag.Ref_voltage = OFF;
                  gtt_Ctrl_flag.Ref_voltage_result = OFF;
                  gtt_Ctrl_flag.Ref_voltage_add_start = OFF; //リファレンス電圧積算開始フラグ OFF


                  break;
             case START_WELD:
                     SetWeldStatus( 2 );
                     SetMotorStatus( 2 );
	             WDG_Clear();
                  break;
             case INITIAL_WELD:
                     ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止 2009.01.31
                     gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                     SetWeldStatus( 2 );
                     SetMotorStatus( 2 );
	             WDG_Clear();

                     gtt_Ctrl_flag.Up_slop_time = OFF; //2009.02.02
                     gtt_Ctrl_flag.Up_slop_time_end = OFF;
                     gtt_Ctrl_flag.Up_slop_curr_end = OFF; //時間が来れば電流が到達していなくても終了
                     
                     gf_Up_slop_base_curr = gtt_Internal_pack.Data.In.usWeldingInitCurr; //2009.08.28

                   //***** ＭＩＸ時間算出 2009.02.17 *****
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.ucMixFreq); //2009.03.27 short->long
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Mix_frequence_set_time * 0.95); //2009.07.24 時間遅れ調整
                   gtt_Ctrl_counter.Mix_A_condition_set_time = (gtt_Ctrl_counter.Mix_frequence_set_time *  gtt_Internal_pack.Data.In.ucMixAcRatio) / 100;
                   gtt_Ctrl_counter.Mix_B_condition_set_time = gtt_Ctrl_counter.Mix_frequence_set_time - gtt_Ctrl_counter.Mix_A_condition_set_time;
                   //*************************************
                  break;
             case UP_SLOPE: //2009.02.02
                  if (gtt_Ctrl_flag.Up_slop_time == OFF)
                  {
                      gtt_Ctrl_counter.Up_slop_time = 0;
                  }
                  //アップスロープステップ算出
                  //gf_Up_slop_base_step  = (float)((short)gtt_Internal_pack.Data.In.usWeldingCurr - (short)gtt_Internal_pack.Data.In.usWeldingInitCurr) / (gtt_Internal_pack.Data.In.sUpSlopTime * 20); //STEP = (本溶接電流－初期電流）/（アップスロープ時間*100 / 5);
                  //gf_Up_slop_pulse_step = (float)((short)gtt_Internal_pack.Data.In.usIP          - (short)gtt_Internal_pack.Data.In.usWeldingInitCurr) / (gtt_Internal_pack.Data.In.sUpSlopTime * 20); //STEP = (パルス電流－初期電流）/（アップスロープ時間*100 / 5);
                  //if ((gtt_Internal_pack.Data.In.sUpSlopTime * 100) > (gtt_Ctrl_counter.Up_slop_time * 10))
                  //{
                  {
					   float pf_work_time;
					   pf_work_time = ((gtt_Internal_pack.Data.In.sUpSlopTime * 100) - (gtt_Ctrl_counter.Up_slop_time * 10)) / 5.0;
					   if (pf_work_time > 0)
					   {
                           gf_Up_slop_base_step  = (float)((short)gtt_Internal_pack.Data.In.usWeldingCurr - (short)gf_Up_slop_base_curr) /  pf_work_time; //STEP = (本溶接電流－初期電流）/（アップスロープ時間*100 / 5);
                           if (gf_Up_slop_base_step >= 0)
                           {
							  if (gf_Up_slop_base_step > 30.0) {gf_Up_slop_base_step = 30.0;}
                           } else {
							  if (gf_Up_slop_base_step < -30.0) {gf_Up_slop_base_step = -30.0;}
						   }
                           gf_Up_slop_pulse_step = (float)((short)gtt_Internal_pack.Data.In.usIP          - (short)gf_Up_slop_pulse_curr) / pf_work_time; //STEP = (パルス電流－初期電流）/（アップスロープ時間*100 / 5);
                           if (gf_Up_slop_pulse_step >= 0)
                           {
							  if (gf_Up_slop_pulse_step > 30.0) {gf_Up_slop_pulse_step = 30.0;}
                           } else {
							  if (gf_Up_slop_pulse_step < -30.0) {gf_Up_slop_pulse_step = -30.0;}
						   }
                       }
                   }

                   //gtt_Ctrl_counter.Frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.usPulseFreq); //2009.03.27 short->long
                   //gtt_Ctrl_counter.A_condition_set_time = (gtt_Ctrl_counter.Frequence_set_time * (100 - gtt_Internal_pack.Data.In.usPulseDuty)) / 100; //2009.02.27
                   //gtt_Ctrl_counter.B_condition_set_time = gtt_Ctrl_counter.Frequence_set_time - gtt_Ctrl_counter.A_condition_set_time;

                   //<><><> 2009.07.24 時間遅れ補正 <><><>
                   gtt_Ctrl_counter.Frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.usPulseFreq);
                   gtt_Ctrl_counter.Frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Frequence_set_time * 0.95);
                   gtt_Ctrl_counter.A_condition_set_time = (gtt_Ctrl_counter.Frequence_set_time * (100 - gtt_Internal_pack.Data.In.usPulseDuty)) / 100;
                   //gtt_Ctrl_counter.A_condition_set_time = (unsigned long)((float)gtt_Ctrl_counter.A_condition_set_time * 0.95);
                   gtt_Ctrl_counter.B_condition_set_time = gtt_Ctrl_counter.Frequence_set_time - gtt_Ctrl_counter.A_condition_set_time;
                   //gtt_Ctrl_counter.B_condition_set_time = (unsigned long)((float)gtt_Ctrl_counter.B_condition_set_time * 0.95);
                   //<><><><><><><><><><><><><><><><><><><>

                   //***** ＭＩＸ時間算出 2009.02.17 *****
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned short)(10000 / (unsigned long)gtt_Internal_pack.Data.In.ucMixFreq); //2009.03.27 short->long
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Mix_frequence_set_time * 0.95); //2009.07.24 時間遅れ調整
                   gtt_Ctrl_counter.Mix_A_condition_set_time = (gtt_Ctrl_counter.Mix_frequence_set_time * gtt_Internal_pack.Data.In.ucMixAcRatio) / 100;
                   gtt_Ctrl_counter.Mix_B_condition_set_time = gtt_Ctrl_counter.Mix_frequence_set_time - gtt_Ctrl_counter.Mix_A_condition_set_time;
                   //*************************************
                  //}
                  //アップスロープ終了判定
                  //if (gtt_Internal_pack.Data.In.usWeldingCurr >= gtt_Internal_pack.Data.In.usWeldingInitCurr)
                  if (gtt_Internal_pack.Data.In.usWeldingCurr >= (short)gf_Up_slop_base_curr) //2009.08.28
                  {
                      //if ((short)gf_Up_slop_base_curr >= gtt_Internal_pack.Data.In.usWeldingCurr)
                      if ((short)gf_Up_slop_base_curr >= gtt_Internal_pack.Data.In.usWeldingCurr + 1) //2009.08.27
                      {
                          gtt_Ctrl_flag.Up_slop_curr_end = ON;
                      } else {
                          gtt_Ctrl_flag.Up_slop_curr_end = OFF;
                      }
                  } else {
                      //if ((short)gf_Up_slop_base_curr <= gtt_Internal_pack.Data.In.usWeldingCurr)
                      if ((short)gf_Up_slop_base_curr <= gtt_Internal_pack.Data.In.usWeldingCurr - 1) //2009.08.27
                      {
                          gtt_Ctrl_flag.Up_slop_curr_end = ON;
                      } else {
                          gtt_Ctrl_flag.Up_slop_curr_end = OFF;
                      }
                  }
                  if (gtt_Ctrl_flag.Up_slop_time == OFF)
                  {
                      gtt_Ctrl_flag.Up_slop_time = ON;
                      gtt_Ctrl_counter.Up_slop_time = 0;
                  } else if ((gtt_Ctrl_counter.Up_slop_time >= (gtt_Internal_pack.Data.In.sUpSlopTime * 10)) && gtt_Ctrl_flag.Up_slop_time == ON) {
                      gtt_Ctrl_flag.Up_slop_time_end = ON;
                      gtt_Ctrl_flag.Up_slop_curr_end = ON; //時間が来れば電流が到達していなくても終了
                  }
                  gtt_Ctrl_flag.Down_slop_time = OFF; //2009.02.02
                  gtt_Ctrl_flag.Down_slop_time_end = OFF;
                  gtt_Ctrl_flag.Down_slop_curr_end = OFF; //時間が来れば電流が到達していなくても終了
                  //gf_Down_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCurr;
                  //gf_Down_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usIP;
                  gf_Down_slop_base_curr    = gf_Up_slop_base_curr; //2009.02.03
                  gf_Down_slop_pulse_curr   = gf_Up_slop_pulse_curr; //2009.02.03
                  break;
             case MAIN_WELD:
                  //ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止 2009.01.31
                  SetWeldStatus( 2 );
                  SetMotorStatus( 2 );
	              WDG_Clear();
                  //gtt_Ctrl_counter.Frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.usPulseFreq); //2009.03.27 short->long
                  //gtt_Ctrl_counter.A_condition_set_time = (gtt_Ctrl_counter.Frequence_set_time * (100 - gtt_Internal_pack.Data.In.usPulseDuty)) / 100; //2009.02.27
                  //gtt_Ctrl_counter.B_condition_set_time = gtt_Ctrl_counter.Frequence_set_time - gtt_Ctrl_counter.A_condition_set_time;
                   //<><><> 2009.07.24 時間遅れ補正 <><><>
                   gtt_Ctrl_counter.Frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.usPulseFreq);
                   gtt_Ctrl_counter.Frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Frequence_set_time * 0.95);
                   gtt_Ctrl_counter.A_condition_set_time = (gtt_Ctrl_counter.Frequence_set_time * (100 - gtt_Internal_pack.Data.In.usPulseDuty)) / 100;
                   //gtt_Ctrl_counter.A_condition_set_time = (unsigned long)((float)gtt_Ctrl_counter.A_condition_set_time * 0.95);
                   gtt_Ctrl_counter.B_condition_set_time = gtt_Ctrl_counter.Frequence_set_time - gtt_Ctrl_counter.A_condition_set_time;
                   //gtt_Ctrl_counter.B_condition_set_time = (unsigned long)((float)gtt_Ctrl_counter.B_condition_set_time * 0.95);
                   //<><><><><><><><><><><><><><><><><><><>

                  if (gtt_Ctrl_flag.Variable_crater_repaet == false) //2009.03.14 2009.03.16
                  {
	                  gf_Down_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCurr;
                      gf_Down_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usIP;
                  } else { //2009.03.14
                     if (gtt_Internal_pack.Data.In.sUpSlopTime > 0) //2009.03.26
                     {
	                 gf_Down_slop_base_curr    = gf_Up_slop_base_curr;
                         gf_Down_slop_pulse_curr   = gf_Up_slop_pulse_curr;
                     } else {
	                 gf_Down_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCurr; //2009.03.26
                         gf_Down_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usIP;          //2009.03.26
                     }
                      //2009.03.16
                     gtt_Ctrl_flag.Up_slop_time = OFF;
                     gtt_Ctrl_flag.Up_slop_time_end = OFF;
                     gtt_Ctrl_flag.Up_slop_curr_end = OFF;
                     gtt_Ctrl_flag.Down_slop_time = OFF; //2009.02.02
                     gtt_Ctrl_flag.Down_slop_time_end = OFF;
                     gtt_Ctrl_flag.Down_slop_curr_end = OFF; //時間が来れば電流が到達していなくても終了


                  }
                   //***** ＭＩＸ時間算出 2009.02.17 *****
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.ucMixFreq); //2009.03.27 short->long
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Mix_frequence_set_time * 0.95); //2009.07.24 時間遅れ調整
                   gtt_Ctrl_counter.Mix_A_condition_set_time = (gtt_Ctrl_counter.Mix_frequence_set_time * gtt_Internal_pack.Data.In.ucMixAcRatio) / 100;
                   gtt_Ctrl_counter.Mix_B_condition_set_time = gtt_Ctrl_counter.Mix_frequence_set_time - gtt_Ctrl_counter.Mix_A_condition_set_time;
                   //*************************************
                  break;
             case DOWN_SLOPE:
                  if (gtt_Ctrl_flag.Down_slop_time == OFF)
                  {
                      gtt_Ctrl_counter.Down_slop_time = 0;
                  }
                  //ダウンスロープステップ算出
                  //gf_Up_slop_base_step  = (float)((short)gtt_Internal_pack.Data.In.usWeldingCurr - (short)gtt_Internal_pack.Data.In.usWeldingInitCurr) / (gtt_Internal_pack.Data.In.sUpSlopTime * 20); //STEP = (本溶接電流－初期電流）/（アップスロープ時間*100 / 5);
                  //gf_Up_slop_pulse_step = (float)((short)gtt_Internal_pack.Data.In.usIP          - (short)gtt_Internal_pack.Data.In.usWeldingInitCurr) / (gtt_Internal_pack.Data.In.sUpSlopTime * 20); //STEP = (パルス電流－初期電流）/（アップスロープ時間*100 / 5);
                  //if ((gtt_Internal_pack.Data.In.sUpSlopTime * 100) > (gtt_Ctrl_counter.Up_slop_time * 10))
                  //{
                  {
                       float pf_work_time;
                       pf_work_time = ((gtt_Internal_pack.Data.In.sDownSlopTime * 100) - (gtt_Ctrl_counter.Down_slop_time * 10)) / 5.0;
                       if (pf_work_time > 0)
                       {
                           gf_Down_slop_base_step  = (float)((short)gtt_Internal_pack.Data.In.usWeldingCratCurr - (short)gf_Down_slop_base_curr) /  pf_work_time; //STEP = (本溶接電流－クレータ電流）/（ダウンスロープ時間*100 / 5);
                           if (gf_Down_slop_base_step >= 0)
                           {
                               if (gf_Down_slop_base_step > 30.0) {gf_Down_slop_base_step = 30.0;}
                           } else {
                               if (gf_Down_slop_base_step < -30.0) {gf_Down_slop_base_step = -30.0;}
                           }
                           gf_Down_slop_pulse_step = (float)((short)gtt_Internal_pack.Data.In.usWeldingCratCurr          - (short)gf_Down_slop_pulse_curr) / pf_work_time; //STEP = (パルス電流－クレータ電流）/（ダウンスロープ時間*100 / 5);
                           if (gf_Down_slop_pulse_step >= 0)
                           {
                           if (gf_Down_slop_pulse_step > 30.0) {gf_Down_slop_pulse_step = 30.0;}
                           } else {
                               if (gf_Down_slop_pulse_step < -30.0) {gf_Down_slop_pulse_step = -30.0;}
                           }
                       }
                   }
                  //}
                  //gtt_Ctrl_counter.Frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.usPulseFreq); //2009.03.27 short->long
                  //gtt_Ctrl_counter.A_condition_set_time = (gtt_Ctrl_counter.Frequence_set_time * (100 - gtt_Internal_pack.Data.In.usPulseDuty)) / 100; //2009.02.27
                  //gtt_Ctrl_counter.B_condition_set_time = gtt_Ctrl_counter.Frequence_set_time - gtt_Ctrl_counter.A_condition_set_time;
                   //<><><> 2009.07.24 時間遅れ補正 <><><>
                   gtt_Ctrl_counter.Frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.usPulseFreq);
                   gtt_Ctrl_counter.Frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Frequence_set_time * 0.95);
                   gtt_Ctrl_counter.A_condition_set_time = (gtt_Ctrl_counter.Frequence_set_time * (100 - gtt_Internal_pack.Data.In.usPulseDuty)) / 100;
                   //gtt_Ctrl_counter.A_condition_set_time = (unsigned long)((float)gtt_Ctrl_counter.A_condition_set_time * 0.95);
                   gtt_Ctrl_counter.B_condition_set_time = gtt_Ctrl_counter.Frequence_set_time - gtt_Ctrl_counter.A_condition_set_time;
                   //gtt_Ctrl_counter.B_condition_set_time = (unsigned long)((float)gtt_Ctrl_counter.B_condition_set_time * 0.95);
                   //<><><><><><><><><><><><><><><><><><><>
                  //ダウンスロープ終了判定
                  //if (gtt_Internal_pack.Data.In.usWeldingCurr >= gtt_Internal_pack.Data.In.usWeldingCratCurr)
                  if ((short)gf_Down_slop_base_curr >= gtt_Internal_pack.Data.In.usWeldingCratCurr) //2009.08.28
                  {
                      //if ((short)gf_Down_slop_base_curr <= gtt_Internal_pack.Data.In.usWeldingCratCurr)
                      if ((short)gf_Down_slop_base_curr <= gtt_Internal_pack.Data.In.usWeldingCratCurr - 1) //2009.08.27
                      
                      {
                          gtt_Ctrl_flag.Down_slop_curr_end = ON;
                      } else {
                          gtt_Ctrl_flag.Down_slop_curr_end = OFF;
                      }
                  } else {
                      //if ((short)gf_Down_slop_base_curr >= gtt_Internal_pack.Data.In.usWeldingCratCurr)
                      if ((short)gf_Down_slop_base_curr >= gtt_Internal_pack.Data.In.usWeldingCratCurr + 1) //2009.08.27
                      
                      {
                          gtt_Ctrl_flag.Down_slop_curr_end = ON;
                      } else {
                          gtt_Ctrl_flag.Down_slop_curr_end = OFF;
                      }
                  }
                  if (gtt_Ctrl_flag.Down_slop_time == OFF)
                  {
                      gtt_Ctrl_flag.Down_slop_time = ON;
                      gtt_Ctrl_counter.Down_slop_time = 0;
                  } else if ((gtt_Ctrl_counter.Down_slop_time >= (gtt_Internal_pack.Data.In.sDownSlopTime * 10)) && gtt_Ctrl_flag.Down_slop_time == ON) {
                      gtt_Ctrl_flag.Down_slop_time_end = ON;
                      gtt_Ctrl_flag.Down_slop_curr_end = ON; //時間が来れば電流が到達していなくても終了
                  }

                  if (guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.02.06
                  {
                     gtt_Ctrl_flag.Up_slop_time = OFF;
                     gtt_Ctrl_flag.Up_slop_time_end = OFF;
                     gtt_Ctrl_flag.Up_slop_curr_end = OFF;
                     gf_Up_slop_base_curr    = gf_Down_slop_base_curr;  //2009.02.06
                     gf_Up_slop_pulse_curr   = gf_Down_slop_pulse_curr; //2009.02.06
                  }

                   //***** ＭＩＸ時間算出 2009.02.17 *****
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.ucMixFreq); //2009.03.27 short->long
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Mix_frequence_set_time * 0.95); //2009.07.24 時間遅れ調整
                   gtt_Ctrl_counter.Mix_A_condition_set_time = (gtt_Ctrl_counter.Mix_frequence_set_time * gtt_Internal_pack.Data.In.ucMixAcRatio) / 100;
                   gtt_Ctrl_counter.Mix_B_condition_set_time = gtt_Ctrl_counter.Mix_frequence_set_time - gtt_Ctrl_counter.Mix_A_condition_set_time;
                   //*************************************
                  break;
             case CRATER_WELD:
                     ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止 2009.01.31
                     gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                     SetWeldStatus( 2 );
                     SetMotorStatus( 2 );
	             WDG_Clear();
                  if (guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.02.05
                  {
                     gtt_Ctrl_flag.Up_slop_time = OFF;
                     gtt_Ctrl_flag.Up_slop_time_end = OFF;
                     gtt_Ctrl_flag.Up_slop_curr_end = OFF;
                     if (gtt_Ctrl_flag.Variable_crater_repaet == false) //2009.03.14 2009.03.16
                     {
                         gf_Up_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
                         gf_Up_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
#if 0 //2010.03.10
                         if (gtt_Ctrl_flag.Variable_crater_re_crater == true) //2010.02.24
                         {
                             gtt_Ctrl_flag.Variable_crater_re_crater = false;
                             gf_Down_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
                             gf_Down_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
                         }
#endif
                     } else { //2009.03.14
                         if (gtt_Internal_pack.Data.In.sDownSlopTime > 0) //2009.03.26
                         {
                             gf_Up_slop_base_curr    = gf_Down_slop_base_curr;
                             gf_Up_slop_pulse_curr   = gf_Down_slop_base_curr;
                         } else {
                             gf_Up_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr; //2009.03.26
                             gf_Up_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr; //2009.03.26
                         }
                         
                         if (gtt_Ctrl_flag.Variable_crater_re_crater == true) //【ＮＯ１８】2010.03.10 (2010.02.24)
                         {
                             gtt_Ctrl_flag.Variable_crater_re_crater = false;
                             gf_Down_slop_base_curr    = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
                             gf_Down_slop_pulse_curr   = (float)gtt_Internal_pack.Data.In.usWeldingCratCurr;
                         }
                         
                         //2009.03.16
                         gtt_Ctrl_flag.Up_slop_time = OFF;
                         gtt_Ctrl_flag.Up_slop_time_end = OFF;
                         gtt_Ctrl_flag.Up_slop_curr_end = OFF;
                         gtt_Ctrl_flag.Down_slop_time = OFF; //2009.02.02
                         gtt_Ctrl_flag.Down_slop_time_end = OFF;
                         gtt_Ctrl_flag.Down_slop_curr_end = OFF; //時間が来れば電流が到達していなくても終了
                     }
                  }
                  
                   //***** ＭＩＸ時間算出 2009.02.17 *****
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)(10000 / (unsigned long)gtt_Internal_pack.Data.In.ucMixFreq); //2009.03.27 short->long
                   gtt_Ctrl_counter.Mix_frequence_set_time = (unsigned long)((float)gtt_Ctrl_counter.Mix_frequence_set_time * 0.95); //2009.07.24 時間遅れ調整
                   gtt_Ctrl_counter.Mix_A_condition_set_time = (gtt_Ctrl_counter.Mix_frequence_set_time *  gtt_Internal_pack.Data.In.ucMixAcRatio) / 100;
                   gtt_Ctrl_counter.Mix_B_condition_set_time = gtt_Ctrl_counter.Mix_frequence_set_time - gtt_Ctrl_counter.Mix_A_condition_set_time;
                   //*************************************
                  break;
             case BURN_BACK:
                  gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                  //gtt_Ctrl_flag.AC_control = false; //2008.11.17

                  if (gtt_Ctrl_flag.Burnback_ac == false) //2008.12.11　Ｈ３６６が０であれば直流終了
                  {
                      gtt_Ctrl_flag.AC_control = false;
                      gtt_En.ss_En_a_output = 0;
                  }

                  if (gtt_Ctrl_flag.Burn_back == OFF)
                  {
                      gtt_Ctrl_flag.Burn_back = ON;
                      ptt_Ctrl_word.Welder_ctrl_code   = OFF;        //溶接電源動作指令
                      SetWeldStatus(0);
                      ctlclsStop();
                      //gtt_Ctrl_flag.Weld_end     = true;

                      //<><><><>繰り返し溶接用<><><><><> REPEAT 2007.1.12　2007.1.22削除　2007.1.26削除内容を移植
                      //gtt_Ctrl_counter.Repeat_weld = REPEAT_WELD_TIME;   //仮に２秒データを入れるが本来はテーブルから読み出す必要あり
                      //<><><><><><><><><><><><><><><><>
                  }
		  if(gtt_Ctrl_flag.Second_currnt_err == false){
                     if (gtt_Ctrl_flag.Motor_off == OFF)
                     {
                         gtt_Ctrl_flag.Motor_off = ON;
                         gtt_Ctrl_counter.Motor_off = MOTOR_OFF_TIME;

//                     } else if (gtt_Ctrl_counter.Motor_off <= 0 || gtt_Ctrl_flag.Arc == OFF){
                     } else if (gtt_Ctrl_counter.Motor_off <= 0 || 
                     		(gtt_Ctrl_flag.Arc == OFF && wspdBuff[0]==0 )){ //2007.5.10
                     		//(gtt_Ctrl_flag.Arc == OFF && ctlclsSpeedGet( )==0 )){ //2007.5.8
		         //gtt_Ctrl_flag.Weld_end = OFF;
                         gtt_Ctrl_flag.Arc = OFF;
                         gtt_Ctrl_flag.Arc_err = OFF;
                         gtt_Ctrl_flag.Motor_off  = OFF;
                         ptt_Ctrl_word.Motor_ctrl_code    = OFF;   //モータ停止
                         gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット
                         gtt_Ctrl_flag.Initial_arc_start = OFF;
                         gtt_Ctrl_flag.Lift_up_cd = OFF;        //2008.10.08
                         gtt_Ctrl_flag.Start_process_end = OFF; //2009.04.03
			 SetWeldStatus( 0 );                       //アイドリング中
                         SetMotorStatus( 0 );                      //アイドリング中
                         ptt_Ctrl_word.Inverter_ctrl_code = OFF;             //インバータ起動 2009.02.27 del 2009.04.11 復活
                         gtt_Ctrl_flag.Burn_back  = OFF;
                         gtt_Ctrl_flag.Mix_wave_current_time = OFF; //2009.04.11
                         
                      //<><><><>繰り返し溶接用<><><><><> REPEAT 2007.1.22　2007.1.26移植追加
                      gtt_Ctrl_counter.Repeat_weld = REPEAT_WELD_TIME;   //仮に２秒データを入れるが本来はテーブルから読み出す必要あり
                      //<><><><><><><><><><><><><><><><>
                     }
		  } else {
                             gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                             gtt_Ctrl_flag.Initial_arc_start = OFF;
                             gtt_Ctrl_flag.Lift_up_cd = OFF;        //2008.10.08
                             gtt_Ctrl_flag.Start_process_end = OFF; //2009.04.03
                             gtt_Ctrl_flag.Arc = OFF;
                             gtt_Ctrl_flag.Arc_err = OFF;
			     //gtt_Ctrl_flag.Weld_end = OFF;
                             gtt_Ctrl_flag.Motor_off = OFF;
                             ptt_Ctrl_word.Motor_ctrl_code    = OFF; //モータ停止
			     SetWeldStatus( 0 );                     //アイドリング中
                             SetMotorStatus( 0 );                    //アイドリング中
                             gtt_Ctrl_flag.Burn_back  = OFF;
                             gtt_Ctrl_flag.Mix_wave_current_time = OFF; //2009.04.11
                  }
                  if (gtt_Ctrl_flag.Arc_out_err == ON) //アーク切れエラー発生でガス停止 2008.12.08
                  {
                      //gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on  = OFF;  //2009.02.18引き上げ停止対応
                  }
                  break;
             case AFTER_FLOW:         //2007.12.11
                  gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                  if (gtt_Ctrl_flag.After_flow_time == OFF)
                  {
                      gtt_Ctrl_flag.After_flow_time = ON;
                      gtt_Ctrl_flag.After_flow = ON;
                      //gtt_Ctrl_counter.After_flow_time = gtt_Ditail_work.us_After_flow_time * 10; //2008.10.09  * 10 2009.01.28 
                      //gtt_Ctrl_counter.After_flow_time = gtt_Ditail_work.us_After_flow_time * 20; //2009.02.23 時間が半分だった。
                      gtt_Ctrl_counter.After_flow_time =  gtt_Internal_pack.Data.In.sAfterFlowTime * 20; //2009.05.14
                      //if (guc_Robot_connect_flag == true) //2009.07.17
                      if (guc_Robot_connect_flag == true && gub_System_err == OFF) //2009.07.17
                      {
		          gtt_Ctrl_counter.After_flow_time = 10; //ロボット接続時は強制的に１０＊５ｍｓとする。
                      }
                  } else if (gtt_Ctrl_counter.After_flow_time <= 0) {
                      gtt_Ctrl_flag.After_flow_time = OFF;
                      gtt_Ctrl_flag.After_flow = OFF;
                      gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //ガス停止 2007.12.12
                      if (ComuniPack.Data.To.fWelderCheck.Bit1Sw.Gas_on == ON && guc_Robot_connect_flag == ON) //2008.10.20
                      {
                          gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = ON;
                      } else {
                          gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF;
                      }
                  }
                  break;
             case IDLING2:
                  ptt_Ctrl_word.Hf_ctrl_code = OFF; //高周波停止 2009.01.31
                  ptt_Ctrl_word.Welder_ctrl_code   = OFF;        //溶接電源動作指令
                  SetWeldStatus(0);
                  ctlclsStop();
                      
                  gtt_Ctrl_flag.Arc = OFF;
                  gtt_Ctrl_flag.Arc_err = OFF;
                  gtt_Ctrl_flag.Motor_off  = OFF;
                  ptt_Ctrl_word.Motor_ctrl_code    = OFF;   //モータ停止
                  gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット 2009.12.16復帰
                  PLS_OUT = OFF;
                  gtt_Ctrl_flag.Initial_arc_start = OFF;
                  gtt_Ctrl_flag.Lift_up_cd = OFF;        //2008.10.08
                  gtt_Ctrl_flag.Start_process_end = OFF; //2009.04.03
                  SetWeldStatus( 0 );                       //アイドリング中
                  SetMotorStatus( 0 );                      //アイドリング中
                  ptt_Ctrl_word.Inverter_ctrl_code = OFF;             //インバータ起動
                  gtt_Ctrl_flag.Burn_back  = OFF;
                  gtt_Ctrl_flag.Mix_wave_current_time = OFF; //2009.04.11
                         
                         
                  gtt_Ctrl_flag.Pre_flow = OFF;
                  gtt_Ctrl_flag.Pre_flow_time = OFF;

                  gtt_Ctrl_flag.After_flow_stop = OFF; //エラー発生時　アフターフロー中にＴＳがＯＮされているとこのフラグがＯＮし、次回プリフローがキャンセルされるため

#if 0 //2009.12.16 温度異常もガス即停止のため
                  if (guc_Error_code != ABNORMAL_TEMP_ERR)
                  {
                      gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //ガス停止
                  }
#endif
                  gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //ガス停止 2009.12.16
                  break;
             case HAND_STICK: //2009.03.06
                  gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Gas_on = OFF; //ガス停止 2009.12.15
                  HF_OUT = OFF;                                               //高周波停止 2010.01.21
                  if (gtt_Ctrl_flag.Slow_down == OFF && gtt_Ctrl_flag.Hand_stick_start == ON)
                  {
                   
                     PWELDTABLE  pWT = GetWeldTable( );  //test 復帰　2006.10.25

                     isContArc = 0;         //通常スタート時（繰り返し溶接ではない）
                     isEnbDelay = 1;        //モータディレイセット

                     //LED4 = ON;
                     { //2009.03.31
                       float Current_level;
                       Current_level = 150.0;
//-------------------------------
// 「微弱モード」の追加		2011.10.28
//-------------------------------
#if true
                       if (gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //微弱
                       {
                           gf_Hot_current_level = Current_level *  0.25;
                       }
                       else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //弱
                       {
                           gf_Hot_current_level = Current_level *  0.5;
                       }
                       else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //標準
                       {
                           gf_Hot_current_level = Current_level;
                       }
                       else if (gss_Select_dital[P_HOT_CURR_LEVEL] == 3) //強
                       {
                           gf_Hot_current_level = Current_level * 1.5;
                       }
#else
                       if (gss_Select_dital[P_HOT_CURR_LEVEL] == 0) //弱
                       {
                           //gf_Hot_current_level = Current_level * HOTCUR * 0.5;
                           gf_Hot_current_level = Current_level *  0.5; //2010.01.22
                       }
                       if (gss_Select_dital[P_HOT_CURR_LEVEL] == 1) //標準
                       {
                           //gf_Hot_current_level = Current_level * HOTCUR;
                           gf_Hot_current_level = Current_level;  //2010.01.22
                       }
                       if (gss_Select_dital[P_HOT_CURR_LEVEL] == 2) //強
                       {
                           //gf_Hot_current_level = Current_level * HOTCUR * 1.5;
                           gf_Hot_current_level = Current_level * 1.5; //2010.01.22
                       }
#endif
//-------------------------------
//
//-------------------------------
                     }

                     WeldAdjOut_Proc( isContArc );           //半固定パラメータのＤＳＰへの再送
                     //<><><><><><><><><><><><><><><><><><><><><><><>

                     gtt_Ctrl_flag.Slow_down = ON;
                     gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd = OFF;   //電検OFFセット　2006.11.28追加
                     gtt_Ctrl_flag.Weld_end = OFF;
                     //溶接出力起動時の溶接条件リセット
                     //SRVCTL          = 0; 2019.04.02 del ihara
                     SetWeldStatus( 1 );     		             //スローダウン中 2006.3.7
                     SetMotorStatus( 1 );                            //送給中
                     
                     //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt);
                     ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19

                     ctlclsDrctSet( );
                     ctlclsWeldStart( );                             //スローダウン値セット
                     wipReCalc( );
                     sipReCalc( );
                     wipReset( );
                     sipReset( );
                  
                     IMJTOCR4  = 0x07; //2006.2.15 割禁　ihara
	             sspdSend();
	             IMJTOCR4  = 0x05;                             //割許
                     ptt_Ctrl_word.Motor_ctrl_code    = ON;             //モータ起動
                     ptt_Ctrl_word.Inverter_ctrl_code = ON;             //インバータ起動
                     ptt_Ctrl_word.Welder_ctrl_code   = ON;             //溶接電源動作指令
                     //gtt_Ctrl_flag.Arc = ON;

                     gtt_Ctrl_flag.Motor_delay     = OFF;              //モータディレイセット
                     gtt_Ctrl_flag.Motor_delay_end = OFF;
                  }
                  //***** アークドライブマスクチェック 2009.03.17 *****
                  if (gtt_Ctrl_flag.Hand_stick_start == ON && gtt_Ctrl_flag.Hard_cd == ON)
                  {
                    if (gtt_Ctrl_flag.Arc_drive_mask_time == OFF)
                    {
                        gtt_Ctrl_flag.Arc_drive_mask_time = ON;
                        gtt_Ctrl_counter.Arc_drive_mask_time = 40; //40 * 100ms = 4000ms
                    } else if (gtt_Ctrl_counter.Arc_drive_mask_time <= 0) {
                        gtt_Ctrl_flag.Arc_drive = ON;
                    }
                  } else if (gtt_Ctrl_flag.Hard_cd == OFF) {
                    gtt_Ctrl_flag.Arc_drive_mask_time = OFF;
                    gtt_Ctrl_flag.Arc_drive           = OFF;
                  }
                  //***************************************************
                  break;
             default:
                  break;
     }
     return (ptt_Ctrl_word);

}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_weld_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

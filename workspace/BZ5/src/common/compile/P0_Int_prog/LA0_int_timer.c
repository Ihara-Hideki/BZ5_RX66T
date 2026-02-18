//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｔ＿ｔｉｍｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ
//  【機能説明】
//      タイマ割り込み
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
#define	__TIMER_PROG

#include  "custom.h"

extern void    int_com_proc(void);				// ＲＳ送信処理		2019.05.28

#define		DSPSEND_TIME		5
extern		int                     DSPSendTimer;


void int_timer( void )
{

	static long		ii;

	WDG_Clear();

	Timer._BaseClock++;
	Timer._100u++;		// １００ｕｓ

        //１００μｓ
        if(gtt_Ctrl_counter.Table_data_output  > 0) {gtt_Ctrl_counter.Table_data_output--;}
        if(gtt_Ctrl_counter.Table_data_output1 > 0) {gtt_Ctrl_counter.Table_data_output1--;}
        if(gtt_Ctrl_counter.R8_send            > 0) {gtt_Ctrl_counter.R8_send--;}
        if(gtt_Ctrl_counter.Srt1               > 0) {gtt_Ctrl_counter.Srt1--;} // 2008.03.11


	//-------------------------------------------------------------
	// 2019.09.04
	//----------------------
	#ifdef __NEWCOM_PROTOCOL
		gtt_Ctrl_flag.ComSend = true;	// 送信タイミングフラグ
	#endif
	//-------------------------------------------------------------

        if(gtt_Ctrl_counter.Output_correct  > 0) {gtt_Ctrl_counter.Output_correct--;} //2009.02.16

//--------- RTC by @Tny 2008/09/01 ------------
#if true
        ++gul_vRTC_FrequencyCount;  // RTC周波数カウンタ

        // ＲＴＣ動作確認用
        if(gus_RTC_cDebug_1 > 0){
            --gus_RTC_cDebug_1;
        }
#endif
//--------------------------------------------
//----- Phase2(Debug) by @Tny 2008/09/02 -----
#if true
        // パケット送受信間隔
        if(gus_Fram_Packet_Wait > 0){
            --gus_Fram_Packet_Wait;
        }
#endif
//--------------------------------------------
//----- Phase4 by @Tny 2008/09/08 -----
#if true
        if(gb_IIF_Select){  // IIF接続を確認
            if(gus_Iif_comunication_timer > 0){
                --gus_Iif_comunication_timer;
            }
            else{
//    			GD2_Send_CMD(0x30);		                // 入力ポート設定データ送信
                gus_Iif_comunication_timer  = 2000;     // 200msec
				gus_Iif_comunication_timer  = 10000; 	// 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
                if(gb_Iif_comuni_failed == false){
                    short   i;
                    gb_Iif_comuni_failed        = true;
//--------- Phase20by @Tny 2008/10/01 --------
#if false
                    gus_Iff_Detect_disp_timer   = 20000;    // 2sec
                    for(i=0;i<18;i++){
                        BackUp16LedData[i] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
                    }
#endif
//--------------------------------------------
//----- Phase22 by @Tny 2008/10/07 -----
#if true
                    gus_Iif_Purge_Judgment  = 20000;     // ＩＩＦ切断（切り離し）判定カウンタ：2sec
#endif
//--------------------------------------------
                }
            }
            if(gus_Iff_Detect_disp_timer > 0){   // IIF検出表示タイマー
                --gus_Iff_Detect_disp_timer;
            }
//----- Phase22 by @Tny 2008/10/07 -----
#if true
            if(gb_Iif_comuni_failed){
                if(gus_Iif_Purge_Judgment > 0){ // IIF切断（切り離し）判定カウンタ
                    --gus_Iif_Purge_Judgment;
                    if(gus_Iif_Purge_Judgment <= 0){ // IIF切断（切り離し）判定カウンタ：タイムアップ？
                        gb_IIF_Select           = false;    // IIFを切断（切り離し）状態にする
//                      gb_Iif_comuni_failed    = false;	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
                        gtt_Internal_pack.Data.bRS422Connection = ComuniPack.Data.bRS422Connection = false;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
						gb_External_IIF			= false;	// 外部拡張ユニット接続フラグ（true=外部拡張ユニット／false=ＩＩＦ）
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
//----- Phase26 by @Tny 2008/10/23 -----
#if true
                        gb_Iif_Input            = false;    // IIFデータ受信フラグ
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
                        //guc_Iif_bit_input       = 0;        // 入力データの初期化
                        InternalPackIif.Data.To.us_Iif_input_data = 0; // 入力データの初期化	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                        guc_Controller_inc_sw_cancel = OFF;
                        guc_Inching_sw_flag = OFF;
                        guc_Inching_sw_flag_bkup = guc_Inching_sw_flag;
                        guc_Gas_on_off_flag = OFF;
                        guc_Gas_check_cancel_flag = false;
                        guc_Gas_on_off_flag_bkup = guc_Gas_on_off_flag;
                        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false;
    		            gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
       	                guc_Sw_rewrite_check_flag = 2; //表示の更新のため
#endif
//--------------------------------------------
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
                        gtt_Ctrl_flag.Iif_connect_err = true; //
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                    }
                }
            }
#endif
//--------------------------------------------
        }
#endif
//--------------------------------------------

//----- Phase5(Debug) by @Tny 2008/09/09 -----
#if false
        if(gus_R8_TX_cDebug_1 > 0){
            --gus_R8_TX_cDebug_1;
        }
        else{
            if(guc_R8_control.Bit1Sw.R8_Fan)    guc_R8_control.Bit1Sw.R8_Fan = false;
            else                                guc_R8_control.Bit1Sw.R8_Fan = true;
            gus_R8_TX_cDebug_1 = 5000;  // 500msec
        }
#endif
//--------------------------------------------
//----- Phase7 by @Tny 2008/09/10 -----
#if true
        if(gus_Iif_Detect_Timer > 0){   // IIF接続確認時間カウンタ
            --gus_Iif_Detect_Timer;
        }
#endif
//--------------------------------------------
//----- Phase12 Phase21 by @Tny 2008/09/17 2008/10/03 -----
#if true
        if(guc_Init_wait_sequence > 0){     // 初期シーケンス待ち時間
            --guc_Init_wait_sequence;
        }
#endif
//--------------------------------------------

        //<><><><> ＤＰＳにテーブルデータを５ｍＳ置きに送るためのタイマ <><><><> 2007.1.12
        if (gtt_Ctrl_counter.Table_data_output <= 1)
        {
            gtt_Ctrl_counter.Table_data_output = TABLE_DATA_OUTPUT_TIME;
            gtt_Ctrl_flag.Table_data_output_execution = ON;
        }
        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


        //<><><><> 出力補正を行うタイマ <><><><> 2009.02.16
        if (gtt_Ctrl_counter.Output_correct <= 1)
        {
            gtt_Ctrl_counter.Output_correct = 2000; //200mS
            gtt_Ctrl_flag.Output_correct = ON;
        }
        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


        //<><><><><><><><><>モータ電流の平均部<><><><><><><><><><> 2007.1.15   2007.1.17移植 2007.3.20平均回数増加により移動
        if (gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == ON || (guc_Sequence_mode > IDLING && guc_Sequence_mode < BURN_BACK)) //モータ起動 2007.3.1
        {
            gtt_Motor_current.Counter++;
            if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect == OFF)
            {
               if (gtt_Motor_current.Center_result >= AD0DT0) //2007.3.20
               {
                   //gtt_Motor_current.Buffer = gtt_Motor_current.Buffer + (MOTOR_CURRENT_CENTER - (int)AD0DT0); //正接
                   gtt_Motor_current.Buffer = gtt_Motor_current.Buffer + (gtt_Motor_current.Center_result - (int)AD0DT0); //正接 2007.3.20センター値変更
               }
            } else {
               //if (AD0DT0 >= MOTOR_CURRENT_CENTER) //2007.3.15
               if (AD0DT0 >= gtt_Motor_current.Center_result) //2007.3.15
               {
                   //gtt_Motor_current.Buffer = gtt_Motor_current.Buffer + ((int)AD0DT0 - MOTOR_CURRENT_CENTER); //逆接
                   gtt_Motor_current.Buffer = gtt_Motor_current.Buffer + ((int)AD0DT0 - gtt_Motor_current.Center_result); //逆接 2007.3.20センター値変更
               }
            }
            if (gtt_Motor_current.Counter >= MOTOR_CURRENT_AVG_COUNTER)
            {
                gtt_Motor_current.Result = (gtt_Motor_current.Buffer / (int)gtt_Motor_current.Counter);
                gtt_Motor_current.Buffer  = 0;
                gtt_Motor_current.Counter = 0;
                gtt_Internal_pack.Data.Out.ucMotorCurr2 = (char)((float)gtt_Motor_current.Result * MOTOR_CURR_BIT); //2007.3.1
            }
        } else {
                gtt_Motor_current.Result  = 0;
                gtt_Motor_current.Buffer  = 0;
                gtt_Motor_current.Counter = 0;
                gtt_Internal_pack.Data.Out.ucMotorCurr2 = 0; //2007.3.1
                
                //<><><><><> 2007.3.20 センター値取得 <><><><><>
                gtt_Motor_current.Center_buffer = gtt_Motor_current.Center_buffer + (int)AD0DT0;
                gtt_Motor_current.Center_counter++;
                if (gtt_Motor_current.Center_counter >= 100)
                {
                    gtt_Motor_current.Center_result = gtt_Motor_current.Center_buffer / (int)gtt_Motor_current.Center_counter;
                    gtt_Motor_current.Center_counter = 0;
                    gtt_Motor_current.Center_buffer = 0; //2007.3.22
                }
                //<><><><><><><><><><><><><><><><><><><><><><><>
        }
        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>

        //１ｍｓ
        if((Timer._BaseClock % 10 ) == 0)
        {
           Timer._1m++;

            //<><><>制御時間関連<><><>
            if (gtt_Ctrl_counter.Start_time             > 0) {gtt_Ctrl_counter.Start_time--;} //2008.10.16 5ms->1msに変更

            if (gtt_Ctrl_counter.Second_currnt_err_timer > 0) {gtt_Ctrl_counter.Second_currnt_err_timer--;} //2008.12.04

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
            if (gtt_Ctrl_counter.ss_Blink_reset          > 0) {gtt_Ctrl_counter.ss_Blink_reset--;    } //
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny


			int_com_proc();				// ＲＳ送信処理		2019.05.28



//--------- IIF(Debug) by @Tny 2008/08/26 ------------
#if true
            if(gus_IIF_DebugTimer1 > 0){
                --gus_IIF_DebugTimer1;
            }
            else{
                if(gb_IIF_DebugFlag1)   gb_IIF_DebugFlag1 = false;
                else                    gb_IIF_DebugFlag1 = true;
                gus_IIF_DebugTimer1 = 1000; // 1sec
            }
#endif
//--------------------------------------------
//----- Phase21 by @Tny 2008/10/03 -----
#if false //2009.03.16 del
            if(gus_Display_command_stop > 0){
                --gus_Display_command_stop;
            }
#endif
//--------------------------------------------
//----- Phase26 by @Tny 2008/10/23 -----
#if true
            // コントローラ接続確認タイマー
            if(gus_Controller_Connect_Timer > 0){
                --gus_Controller_Connect_Timer;
            }
#endif
//--------------------------------------------
//----- Phase29 by @Tny 2008/11/21 -----
#if true
		    if((gub_System_err == ON)&&(guc_Error_code == PRI_LOW_VOLTAGE_ERR)){   // 一次電圧低エラーが発生？
				if(gus_Pri_volt_err_timer > 0){
					--gus_Pri_volt_err_timer;	// 一次電圧低異常検知ディレイタイマー
				}
			}
#endif
//--------------------------------------------

            if (gus_Initial_timer > 0) {gus_Initial_timer--;} //2007.12.04

            if (gtt_Ctrl_counter.Motor_delay   > 0) {gtt_Ctrl_counter.Motor_delay--;}

            if (gtt_Ctrl_counter.Cd_check      > 0) {gtt_Ctrl_counter.Cd_check--;}  //2007.1.24 2007.1.26移植追加
   
            if (gtt_Ctrl_counter.Toch_sw_off_delay_time   > 0) {gtt_Ctrl_counter.Toch_sw_off_delay_time--;}  //2007.2.24 追加
            if (gtt_Ctrl_counter.Stick_check_delay_time   > 0) {gtt_Ctrl_counter.Stick_check_delay_time--;}  //2007.2.24 追加

        //<><><><><><><><><><>一次電圧の平均部<><><><><><><><><><>
           gtt_Vp.Counter++;
           gtt_Vp.Buffer = gtt_Vp.Buffer + (unsigned int)AD0DT4;
           if (gtt_Vp.Counter >= VP_AVG_COUNTER)
           {
               gtt_Vp.Result = (unsigned int)(gtt_Vp.Buffer / (unsigned int)gtt_Vp.Counter);
               gtt_Vp.Buffer  = 0;
               gtt_Vp.Counter = 0;
           }
           //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>

            if (gtt_Ctrl_counter.Frequence_time  > 0) {gtt_Ctrl_counter.Frequence_time--;} //2008.02.28
            if (gtt_Ctrl_counter.B_condition_time  > 0) {gtt_Ctrl_counter.B_condition_time--;} //2008.02.28

            if (gtt_Ctrl_counter.Init_current_time    > 0) {gtt_Ctrl_counter.Init_current_time--;} //2008.02.27 2008.11.06 10->1に変更
            if (gtt_Ctrl_counter.Wave_current_time    > 0) {gtt_Ctrl_counter.Wave_current_time--;} //2008.02.28 2008.11.06 10->1に変更
            if (gtt_Ctrl_counter.us_DC_control_timer  > 0) {gtt_Ctrl_counter.us_DC_control_timer--;} //2008.09.22 交流時直流制御区間 2008.11.26 10->1に変更


            //<><><><><><><><><><>ＭＩＸ関連 2009.02.17<><><><><><><><>
            if (gtt_Ctrl_counter.Mix_frequence_time       > 0)   {gtt_Ctrl_counter.Mix_frequence_time--;}
            if (gtt_Ctrl_counter.Mix_B_condition_time     > 0)   {gtt_Ctrl_counter.Mix_B_condition_time--;}
            if (gtt_Ctrl_counter.Mix_wave_current_time    > 0)   {gtt_Ctrl_counter.Mix_wave_current_time--;}
            //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>

            //エキスパートモード関連
            if (gtt_Ctrl_counter.Ref_voltage              > 0)   {gtt_Ctrl_counter.Ref_voltage--;} //2009.02.20

            //パルス時電流表示用 2009.03.24
            if (gtt_Ctrl_counter.Base_read_delay               > 0)   {gtt_Ctrl_counter.Base_read_delay--;}
            if (gtt_Ctrl_counter.Peak_read_delay               > 0)   {gtt_Ctrl_counter.Peak_read_delay--;}

            //リモコン再生関連 2009.03.28
            if (gtt_Ctrl_counter.Remo_play_sw                  > 0)   {gtt_Ctrl_counter.Remo_play_sw--;}

            //直流手溶接再スタート関連 2009.03.30
            if (gtt_Ctrl_counter.Hand_restart_wait             > 0)   {gtt_Ctrl_counter.Hand_restart_wait--;}

            //ＭＳ制御関連 2019.07.03
            if (gtt_Ctrl_counter.Ms_time            		> 0)   {gtt_Ctrl_counter.Ms_time--;}



#if 0
//2007.1.15 delete   2007.1.17削除移植
           //<><><><><><><><><>モータ電流の平均部<><><><><><><><><><>
           gtt_Motor_current.Counter++;
           gtt_Motor_current.Buffer = gtt_Motor_current.Buffer + (unsigned int)AD0DT0;
           if (gtt_Motor_current.Counter >= MOTOR_CURRENT_AVG_COUNTER)
           {
               gtt_Motor_current.Result = (unsigned int)(gtt_Motor_current.Buffer / (unsigned int)gtt_Motor_current.Counter);
               gtt_Motor_current.Buffer  = 0;
               gtt_Motor_current.Counter = 0;
           }
           //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif

#if 0      //2007.3.20削除
           //<><><><><><><><><>モータ電流の平均部<><><><><><><><><><> 2007.1.15   2007.1.17移植
           //if (gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == ON) //モータ起動
           if (gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == ON || (guc_Sequence_mode > IDLING && guc_Sequence_mode < BURN_BACK)) //モータ起動 2007.3.1
           {
               gtt_Motor_current.Counter++;
               if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect == OFF)
               {
                  gtt_Motor_current.Buffer = gtt_Motor_current.Buffer + (MOTOR_CURRENT_CENTER - (int)AD0DT0); //正接
               } else {
                  if (AD0DT0 >= MOTOR_CURRENT_CENTER) //2007.3.15
                  {
                      gtt_Motor_current.Buffer = gtt_Motor_current.Buffer + ((int)AD0DT0 - MOTOR_CURRENT_CENTER); //逆接
                  }
               }
               if (gtt_Motor_current.Counter >= MOTOR_CURRENT_AVG_COUNTER)
               {
                   gtt_Motor_current.Result = (gtt_Motor_current.Buffer / (int)gtt_Motor_current.Counter);
                   gtt_Motor_current.Buffer  = 0;
                   gtt_Motor_current.Counter = 0;
                   gtt_Internal_pack.Data.Out.ucMotorCurr2 = (char)((float)gtt_Motor_current.Result * MOTOR_CURR_BIT); //2007.3.1
               }
           } else {
                   gtt_Motor_current.Result  = 0;
                   gtt_Motor_current.Buffer  = 0;
                   gtt_Motor_current.Counter = 0;
                   gtt_Internal_pack.Data.Out.ucMotorCurr2 = 0; //2007.3.1
           }
           //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif

			//<><><> 電極短絡の回避 2014.06.24 <><><>
            if (gtt_Ctrl_counter.us_One_shot_voltage    > 0) {gtt_Ctrl_counter.us_One_shot_voltage--;} // 2014.06.24
            //<><><><><><><><><><><><><><><><><><><><>

           gtt_Fpga.Rpm_counter++; //2007.3.15
        }


        //５ｍｓ
        if((Timer._BaseClock % 50 ) == 0 )
        {
            //<><><>エラーディレイカウンター<><><>
            if (gtt_Ctrl_counter.Motor_off              > 0) {gtt_Ctrl_counter.Motor_off--;    }
            if (gtt_Ctrl_counter.Emg_err                > 0) {gtt_Ctrl_counter.Emg_err--;      }
            if (gtt_Ctrl_counter.Gas_err                > 0) {gtt_Ctrl_counter.Gas_err--;      }
            if (gtt_Ctrl_counter.Water_err              > 0) {gtt_Ctrl_counter.Water_err--;    }
            if (gtt_Ctrl_counter.Temp_err               > 0) {gtt_Ctrl_counter.Temp_err--;     }
            if (gtt_Ctrl_counter.Vp_err                 > 0) {gtt_Ctrl_counter.Vp_err--;       }
            if (gtt_Ctrl_counter.Arc_start_err          > 0) {gtt_Ctrl_counter.Arc_start_err--;}
            if (gtt_Ctrl_counter.Err_disp_chenge_timing > 0) {gtt_Ctrl_counter.Err_disp_chenge_timing--;}
            if (gtt_Ctrl_counter.Ver_disp_chenge_timing > 0) {gtt_Ctrl_counter.Ver_disp_chenge_timing--;} //2007.2.13追加
            if (gtt_Ctrl_counter.Pri_curr_fb1_err       > 0) {gtt_Ctrl_counter.Pri_curr_fb1_err--;}
            if (gtt_Ctrl_counter.Pri_curr_fb1_err_unb   > 0) {gtt_Ctrl_counter.Pri_curr_fb1_err_unb--;} //2007.3.14ＰＯ版より移植
            if (gtt_Ctrl_counter.Pri_curr_fb2_err       > 0) {gtt_Ctrl_counter.Pri_curr_fb2_err--;}
            if (gtt_Ctrl_counter.R8_com_err             > 0) {gtt_Ctrl_counter.R8_com_err--;}
            if (gtt_Ctrl_counter.Motor_current_err      > 0) {gtt_Ctrl_counter.Motor_current_err--;}
            if (gtt_Ctrl_counter.Pri_curr_fb1_start_err > 0) {gtt_Ctrl_counter.Pri_curr_fb1_start_err--;} //2007.4.17
      
            //<><><>モータエラー関連 2007.8.1<><><>
            if (gtt_Ctrl_counter.Motor_encoder_err      > 0) {gtt_Ctrl_counter.Motor_encoder_err--;}
            if (gtt_Ctrl_counter.Motor_lock_err         > 0) {gtt_Ctrl_counter.Motor_lock_err--;}
            if (gtt_Ctrl_counter.Motor_circuit_break    > 0) {gtt_Ctrl_counter.Motor_circuit_break--;}
            if (gtt_Ctrl_counter.Motor_circuit_err      > 0) {gtt_Ctrl_counter. Motor_circuit_err--;}
            if (gtt_Ctrl_counter.Motor_err              > 0) {gtt_Ctrl_counter.Motor_err--;}

            //<><><>制御時間関連<><><>
            if (gtt_Ctrl_counter.Pre_flow_time          > 0) {gtt_Ctrl_counter.Pre_flow_time--;}
            if (gtt_Ctrl_counter.After_flow_time        > 0) {gtt_Ctrl_counter.After_flow_time--;} //2007.12.11
            if (gtt_Ctrl_counter.Arc_spot_time          > 0) {gtt_Ctrl_counter.Arc_spot_time--;} //2008.07.30
            if (gtt_Ctrl_counter.Crater_repeat_time     > 0) {gtt_Ctrl_counter.Crater_repeat_time--;} //2008.07.31
            if (gtt_Ctrl_counter.Err_gas                > 0) {gtt_Ctrl_counter.Err_gas--;}       //2009.07.27 エラー発生時ガス処理ディレイ
            if (gtt_Ctrl_counter.Ts_on_err_timer        > 0) {gtt_Ctrl_counter.Ts_on_err_timer--;}       //2009.12.18
      

            //<><><>表示制御関連<><><>
            if (gtt_Ctrl_counter.Revers_time            > 0) {gtt_Ctrl_counter.Revers_time--;} //2008.08.19
            if (gtt_Ctrl_counter.uc_Clr_time            > 0) {gtt_Ctrl_counter.uc_Clr_time--;} //2008.09.03
            if (gtt_Ctrl_counter.uc_Robot_connect_time  > 0) {gtt_Ctrl_counter.uc_Robot_connect_time--;} //2008.10.06

        }

        //１０ｍｓ
        if((Timer._BaseClock % 100) == 0)
        {
            Timer._10m++;	// １０ｍｓ
            if(SND_Mode == WAIT_mode_SD)
            {
               SND_Timer++;
            }

            if(RE_SND_Mode == WAIT_mode_SD) //リモコン用2007.12.03
            {
               RE_SND_Timer++;
            }
            //if(pre_flow_time > 0) {pre_flow_time--;} //2006.3.14 ihara      
            //if(after_flow_time > 0) {after_flow_time--;} //2006.3.14 ihara  
            if(timer_10ms < 65535){ timer_10ms++; }

            if (guc_Okcv_display_timer > 0) {guc_Okcv_display_timer--;} //2007.12.06
            if (gus_Dps_timer > 0)          {gus_Dps_timer--;}          //2007.12.09
            if (gus_Pre_display_timer > 0)  {gus_Pre_display_timer--;}  //2007.12.10

            gtt_Fpga.Short_counter++; //2007.3.5移動

            if (gtt_Ctrl_counter.Pri_volt_err_com_delay  > 0) {gtt_Ctrl_counter.Pri_volt_err_com_delay--;} //2007.3.6追加 2007.3.13移植

            //if (gtt_Ctrl_counter.Init_current_time    > 0) {gtt_Ctrl_counter.Init_current_time--;} //2008.02.27
            //if (gtt_Ctrl_counter.Wave_current_time    > 0) {gtt_Ctrl_counter.Wave_current_time--;} //2008.02.28
            if (gtt_Ctrl_counter.Weld_end_disp        > 0) {gtt_Ctrl_counter.Weld_end_disp--;} //2008.03.03
            //if (gtt_Ctrl_counter.us_DC_control_timer  > 0) {gtt_Ctrl_counter.us_DC_control_timer--;} //2008.09.22 交流時直流制御区間
//----- Phase21 by @Tny 2008/10/03 -----
#if true
            if(gtt_End_welding_display.us_Display_time > 0){    // 溶接終了後表示時間
                if((gub_System_err != ON)&&(guc_Error_return_LED_control_A <= 0)){   // エラーは発生していない？ // Phase20 by @Tny 2008/10/01
                    --gtt_End_welding_display.us_Display_time;
                }
                else{                       // エラーが発生しているのなら、復帰処理用に１秒ほどタイマーをセットする // Phase20 by @Tny 2008/10/01
                    gtt_End_welding_display.us_Display_time = 100;
                }
            }
#endif
//--------------------------------------------
            //***** ＪＯＧ　Ｖ＿ＭＡＸ発動 2008.12.22 *****
            if (gtt_Ctrl_counter.us_Jog1_timer     > 0) {gtt_Ctrl_counter.us_Jog1_timer--; }
            if (gtt_Ctrl_counter.us_Jog1_timer    <= 0)
            {
                gtt_Ctrl_counter.sc_Jog1 = 0;
            }
            if (gtt_Ctrl_counter.us_Jog2_timer     > 0) {gtt_Ctrl_counter.us_Jog2_timer--; }
            if (gtt_Ctrl_counter.us_Jog2_timer    <= 0)
            {
                gtt_Ctrl_counter.sc_Jog2 = 0;
            }

            //***** 高周波関連タイマ 2009.01.31 *****
            if (gtt_Ctrl_counter.Hf_2sec_timer             > 0) {gtt_Ctrl_counter.Hf_2sec_timer--;}             //２秒タイマ
            if (gtt_Ctrl_counter.Hf_30sec_timer            > 0) {gtt_Ctrl_counter.Hf_30sec_timer--;}            //３０秒タイマ
            if (gtt_Ctrl_counter.Hf_30sec_interval_timer   > 0) {gtt_Ctrl_counter.Hf_30sec_interval_timer--;}   //間欠動作までインターバルタイマ
            if (gtt_Ctrl_counter.Hf_intermittent_on        > 0) {gtt_Ctrl_counter.Hf_intermittent_on--;}        //間欠起動タイマ
            if (gtt_Ctrl_counter.Hf_intermittent_off       > 0) {gtt_Ctrl_counter.Hf_intermittent_off--;}       //間欠起動タイマ

            //***** スロープ関連タイマ 2009.02.02 *****
            if (gtt_Ctrl_counter.Up_slop_time     <  30000) {gtt_Ctrl_counter.Up_slop_time++;} //アップスロープ
            if (gtt_Ctrl_counter.Down_slop_time   <  30000) {gtt_Ctrl_counter.Down_slop_time++;} //ダウンスロープ
            if (gtt_Ctrl_counter.W_click_timer    <  30000) {gtt_Ctrl_counter.W_click_timer++;}  //クレータリピートＷクリック時間 2009.02.05

            //***** 直流手溶接関連タイマ 2009.03.06 *****
            if (gtt_Ctrl_counter.Hand_stick_ready_time > 0) {gtt_Ctrl_counter.Hand_stick_ready_time--;}

            //***** 電極短絡チェックタイマ 2009.03.13 *****
            if (gtt_Ctrl_counter.Electrode_short_check > 0) {gtt_Ctrl_counter.Electrode_short_check--;}

            //***** 可変反復ＴＳチェックタイマ 2009.03.14 *****
            if (gtt_Ctrl_counter.Cr_ts_check  > 0) {gtt_Ctrl_counter.Cr_ts_check--;}
            if (gtt_Ctrl_counter.Cr_ts_check2 > 0) {gtt_Ctrl_counter.Cr_ts_check2--;}


    	}

        //２０ｍｓ
        if((Timer._BaseClock % 200 ) == 0 )
        {
            if(timer_20ms < 65535){ timer_20ms++; }
        }

        //５０ｍｓ
        if((Timer._BaseClock % 500 ) == 0)
        {
            if(timer_50ms < 65535){ timer_50ms++; }
            Timer._50m++;
        }

        //１００ｍｓ
        if((Timer._BaseClock % 1000 ) == 0)
        {
            Timer._100m++;
            if (gtt_Ctrl_counter.Repeat_weld       > 0) {gtt_Ctrl_counter.Repeat_weld--;    } //2007.1.12REPEAT
            if (gtt_Ctrl_counter.Gas_limit_timer   > 0) {gtt_Ctrl_counter.Gas_limit_timer--;      } //ガスチェック時間９０秒 2008.09.08 
//------ Phase9 by @Tny 2008/09/12 ------
#if true
            if(gtt_Ctrl_counter.Fan_A_off > 0){
                gtt_Ctrl_counter.Fan_A_off--;
            }
#endif
            //2008.10.30 インチングが一致するように修正
	    if(gtt_Ctrl_flag.Slow_start == ON)
            {
               gus_Inching_curr += 10;
               if(gus_Inching_curr >= gtt_Internal_pack.Data.In.usWeldingCurr)
               { 
                  gtt_Ctrl_flag.Slow_start = OFF;
                  gus_Inching_curr = gtt_Internal_pack.Data.In.usWeldingCurr;
               }
	    }
            //アークドライブマスク関連 2009.03.17
            if (gtt_Ctrl_counter.Arc_drive_mask_time > 0) {gtt_Ctrl_counter.Arc_drive_mask_time--;}



//---------------------------------------------------------------------

//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23
		if(guc_Initial_display_flag){	// BP4 Phase14 by @Tny 2009.02.24
			if(gus_MessageTimer > 0){	// メッセージ表示時間が経過?
				--gus_MessageTimer;
				if(gus_MessageTimer <= 0){	// メッセージ表示時間が経過?
					gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
				}
			}
		}
//--------------------------------------------------------------------


        }

        //２００ｍｓ 2007.3.29
        if((Timer._BaseClock % 2000 ) == 0)
        {
            Timer._200m++;
        }

        //３００ｍｓ 2009.12.17
        if((Timer._BaseClock % 3000 ) == 0)
        {
            Timer._300m++;
        }

        //５００ｍｓ
        if((Timer._BaseClock % 5000 ) == 0)
        {
            Timer._500m++;
            if (gtt_Ctrl_counter.Fan_off > 0) {gtt_Ctrl_counter.Fan_off--;   }
            //２００６．１２．１５　バックＲＡＭテスト
            test_counter++;
        }



        //I_V_READ(2000);
        I_V_READ(100); //2009.03.17


	{ //<><><>電流検出 2019.05.30<><><>
          gus_Current_detect = (MfmC[CURR_FB_DATA] * 750) / 2048;    // 電検判定用
	  	if(gus_Current_detect >= 9)
		{
	     		gtt_Ctrl_flag.Hard_cd	= ON;
			gtt_Ctrl_flag.Start_process_end = ON;
		}
		else if(gus_Current_detect <= 2)
		{
			gtt_Ctrl_flag.Hard_cd	= OFF;
			gtt_Ctrl_flag.Start_process_end = OFF;
		}

	}




	TOPIR2 = 0x02;
        return;

}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA_int_timer.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
void    DSPSendTimeInit( void )
{// @-R040301RTW
    DSPSendTimer = DSPSEND_TIME;
    return;
}

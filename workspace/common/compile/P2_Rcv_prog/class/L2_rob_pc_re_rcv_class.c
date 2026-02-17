//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｒｏｂ＿ｐｃ＿ｒｃｖ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      ロボット、ＰＣ受信
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



//**************************** 注意（重要）**************************************
//  今後本プログラムを修正または追加される方は以下の事に注意して下さい
//　
//　★gtt_Internal_pack.Dataについて
//　　本変数は参照のみにして下さい。
//　　理由：通信が行われると、ComuniPack.Dataのデータが書き込まれてしまうため。
//　　　　　（変更した内容が元に戻ってしまう）
//　★ComuniPack.Dataについて
//　　本変数はgtt_Internal_pack.Dataへの代入のみに使用して下さい。
//　　また代入はrob_pc_rcv_classのみで行ってください。
//　　理由：不用意にこの変数を書き換えると通信された内容が変わってしまい、
//　　　　　ロボットと溶接機との間のデータに矛盾が生じてしまうため
//　　　　　また、rob_pc_rcv_class以外で代入を行うと溶接機内でデータの矛盾が
//　　　　　生じるため。
//********************************************************************************


#include  "custom.h"
#include  <string.h>

#include  <math.h> //2009.07.28


extern const char gc_Dc_adjust_p_data[2]; //2008.08.28
extern const char gc_Dp_adjust_p_data[5]; //2008.08.28
extern const char gc_Ac_adjust_p_data[2]; //2008.09.12
extern const char gc_Ap_adjust_p_data[6]; //2008.09.12
extern const char gc_Ac_init_adjust_p_data[2]; //2008.10.01
extern const char gc_Ap_init_adjust_p_data[6]; //2008.10.01
extern const char gc_Ac_crater_adjust_p_data[2]; //2008.10.01
extern const char gc_Ap_crater_adjust_p_data[6]; //2008.10.01
extern void char_set_class(unsigned char block, char *p , char n1, char n2, char n3);   // Phase2(Debug) @Tny
//------ Phase21 by @Tny 2008/10/02 ------
#if true
//
// 転送元データセット処理
//
static void SetMemCopy(unsigned char area_no);
//
// 転送先データセット処理
//
static void GetMemCopy(unsigned char area_no);
#endif
//-----------------------------------------


//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23	BP4 Phase16 by @Tny 2009.03.12
static ubool strcomp(unsigned char *str1, unsigned char *str2)
{
	ubool			Ret = true;
	unsigned short	i;

	if(strlen((const char *)str1) != strlen((const char *)str2)){
		Ret = false;
	}
	else{
		for(i=0;i<strlen((const char *)str2);i++){
			if(*(str1+i) != *(str2+i)){
				Ret = false;
				break;
			}
		}
	}
return(Ret);
}
//--------------------------------------------------------------------


void rob_pc_re_rcv_class(void)
{

     unsigned char Cnt;
     signed short pss_Notch_work; //2008.02.25
     signed char  psc_Flag_work;  //2008.08.23
     signed char  psc_Counter_work;  //2008.08.23
     signed char  psc_Day_max_work;  //2008.08.25
     unsigned char puc_Index = 0; //2008.09.04		2019.06.10


     //***** BP3関連 *****
     //unsigned char puc_Work;
     unsigned short pus_Work; //2009.01.19
     unsigned char puc_Bit_check_counter = 0;	// 2019.06.03
     //*******************



                //<><><><> 出力制限の反映 2010.01.12 <><><><>
                switch (guc_Method_condition_data)
                {
                    case STD_DC_METHOD:
                    case STD_MIX_METHOD:
                    case EXP_DC_METHOD:
                    case EXP_AC_METHOD:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         {
                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT = MAX_CURRENT_VAL;
                         }
                         break;
                    case STD_AC_METHOD:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         {
                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT = MAX_CURRENT_VAL;
                         }
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_AC_SOFT_VAL)
                         {
                             MAX_CURRENT_AC_SOFT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT_AC_SOFT = MAX_CURRENT_AC_SOFT_VAL;
                         }
                         break;
                    case STD_HAND_METHOD:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_HAND_VAL)
                         {
                             MAX_CURRENT_HAND = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT_HAND = MAX_CURRENT_HAND_VAL;
                         }
                         break;
                    default:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         {
                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT = MAX_CURRENT_VAL;
                         }
                         break;
                }
                //<><><><><><><><><><><><><><><><><><><><><><>


     if (ComuniPack.Data.bRS232Connection) //2008.10.21 add
     {
	gtt_Internal_pack.Data.bRS232Connection = ComuniPack.Data.bRS232Connection;
     }
     if (guc_Robot_connect_flag == true)	// ロボット回線接続 2008.10.09
     {
         gtt_Internal_pack.Data.bRS422Connection = ComuniPack.Data.bRS422Connection;

   	if (ComuniPack.Data.To.bChangeData)	// 受信データ更新
        {
	        gtt_Internal_pack.Data.In.iRecvCommand               = ComuniPack.Data.To.iRecvCommand;           // 受信コマンド（データ更新判別用）の初期化
		    gtt_Internal_pack.Data.In.usWeldingCurr              = (sint) ComuniPack.Data.To.usWeldingCurr;   // 出力電流指令値
#if G3_NEW_COM
		    gtt_Internal_pack.Data.In.usWeldingVolt              = (sint) ComuniPack.Data.To.usWeldingVolt;   // 出力電圧指令値
            gtt_Internal_pack.Data.In.ss_En_duty_adjustment      = ComuniPack.Data.To.ss_En_duty_adjustment; //ＥＮ比率調整量 2008.10.03
            gtt_Internal_pack.Data.In.uc_En_0_mode               = ComuniPack.Data.To.uc_En_0_mode; //2008.11.28
            //一元電圧問い合わせ関連
            if (gtt_En.uc_En_inquiry == 1)
            {
	            gtt_Internal_pack.Data.In.us_Q_WeldingCurr           = ComuniPack.Data.To.us_Q_WeldingCurr; //2008.11.28
                gtt_Ditail_work.ss_En_duty_qes_adjustment            = ComuniPack.Data.To.ss_Q_en_duty_adjustment; //2008.11.28
                gtt_Internal_pack.Data.In.uc_Q_En_0_mode             = ComuniPack.Data.To.uc_Q_En_0_mode; //2008.11.28
                gtt_En.uc_En_inquiry                                 = 2;
            }
#else
            if ((gtt_Internal_pack.Data.In.fInitialSelect1.ALL) & 0x01 == 0x01) //一元電圧選択
            {
      		    gtt_Okcv.Okcv_ref                                    = (sint) ComuniPack.Data.To.usWeldingVolt;   // 出力電圧指令値
            } else {
	     	    gtt_Internal_pack.Data.In.usWeldingVolt              = (sint) ComuniPack.Data.To.usWeldingVolt;   // 出力電圧指令値
            }
#endif
		gtt_Internal_pack.Data.In.fWelderCommand.ALL         = ComuniPack.Data.To.fWelderCommand.ALL;     // 溶接電源動作指令
		gtt_Internal_pack.Data.In.fWelderCheck.ALL           = ComuniPack.Data.To.fWelderCheck.ALL;       // 溶接電源チェック
		gtt_Internal_pack.Data.In.usIP                       = ComuniPack.Data.To.usIP;                   // パルスピーク指令電流
		gtt_Internal_pack.Data.In.usIB                       = ComuniPack.Data.To.usIB;                   // パルスベース指令電流
		//gtt_Internal_pack.Data.In.usPulseFreq                = ComuniPack.Data.To.usPulseFreq;            // パルス指令周波数
		//gtt_Internal_pack.Data.In.usPulseDuty                = ComuniPack.Data.To.usPulseDuty;            // パルス指令幅
		//gtt_Internal_pack.Data.In.usAcFreq                   = ComuniPack.Data.To.usAcFreq;               // 交流周波数                          2009.07.10 del
		//gtt_Internal_pack.Data.In.ucCleaningDuty             = ComuniPack.Data.To.ucCleaningDuty;         // クリーニング幅                      2009.07.10 del
		//gtt_Internal_pack.Data.In.ucMixFreq                  = ComuniPack.Data.To.ucMixFreq;              // MIX TIG周波数                       2009.07.10 del
		//gtt_Internal_pack.Data.In.ucMixAcRatio               = ComuniPack.Data.To.ucMixAcRatio;           // MIX(AC)比率                         2009.07.10 del
		//gtt_Internal_pack.Data.In.fControl.ALL               = ComuniPack.Data.To.fControl.ALL;           // コントロール
		gtt_Internal_pack.Data.In.ucImprudenceVolt           = ComuniPack.Data.To.ucImprudenceVolt;       // 電極短絡電圧指令値
		gtt_Internal_pack.Data.In.fPulseMode.ALL             = ComuniPack.Data.To.fPulseMode.ALL;         // パルスモード設定
        //６Ｂコマンドの受け取り 2009.07.13
        gtt_Internal_pack.Data.In.fControl.ALL               = ComuniPack.Data.To.fControl.ALL;
        if (guc_Robot_connect_flag == true) //2008.12.01
        {

                if (guc_Pulse_mode_data == 0) //パルス無 2009.03.23
                {
                    if(Timer._10m != gtt_Ctrl_counter.Backup_10m) //エキスパートモード以外では平均化を多くし、安定化させる 2009.03.17 50->10
                    {
                       if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
                       {
                	   gss_Current_result_work = gss_Current_result_work + gtt_Fpga.Curr_result;
                	   gss_Voltage_result_work = gss_Voltage_result_work + gtt_Fpga.Volt_result;
                	   gtt_Ctrl_counter.Avr_result++;
                	   if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	   {
                               gss_RCurrent_work = gss_Current_result_work / gtt_Ctrl_counter.Avr_result;
                               gss_RVoltage_work = gss_Voltage_result_work / gtt_Ctrl_counter.Avr_result;
                               gss_Current_result_work = 0;		//
                               gss_Voltage_result_work = 0;		//
                               gtt_Ctrl_counter.Avr_result = 0;
                               gtt_Ctrl_flag.Weld_end_disp = OFF;
                	   }
                        } else { //2009.03.26 実効値
                	   gsl_Current_result_work_rms = gsl_Current_result_work_rms + gtt_Fpga.Curr_result_rms;
                	   gsl_Voltage_result_work_rms = gsl_Voltage_result_work_rms + gtt_Fpga.Volt_result_rms;
                	   gtt_Ctrl_counter.Avr_result++;
                	   if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	   {
//2011.10.01                                  gss_RCurrent_work = sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result);
                               gss_RCurrent_work = (signed short)(sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result)-(double)0.5);//2011.10.01 300BP4
                               gss_RVoltage_work = sqrt(gsl_Voltage_result_work_rms / gtt_Ctrl_counter.Avr_result);
                               gsl_Current_result_work_rms = 0;		//
                               gsl_Voltage_result_work_rms = 0;		//
                               gtt_Ctrl_counter.Avr_result = 0;
                               gtt_Ctrl_flag.Weld_end_disp = OFF;
                	   }
                        }
                	   gtt_Ctrl_counter.Backup_10m = Timer._10m; //2009.03.23
                   }
                } else { //パルス有 2009.03.23
                   if (gtt_Internal_pack.Data.In.usPulseFreq < 5) // 0.1～0.4Hz区間 2009.03.27
                   {
                       //出力電流値
                       switch (guc_Sequence_mode)
                       {
                           case INITIAL_WELD:
                           case CRATER_WELD:
                           case BURN_BACK:
                           case UP_SLOPE:
                           case DOWN_SLOPE:
                           case MAIN_WELD:
                                //この区間はパルスがないので電流、電圧を算出する
                                if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                {
                                   if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
                                   {
                	               gss_Current_result_work = gss_Current_result_work + gtt_Fpga.Curr_result;
                	               gss_Voltage_result_work = gss_Voltage_result_work + gtt_Fpga.Volt_result;
                	               gtt_Ctrl_counter.Avr_result++;
                	               if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	               {
                                           gss_RCurrent_work = gss_Current_result_work / gtt_Ctrl_counter.Avr_result;
                                           gss_RVoltage_work = gss_Voltage_result_work / gtt_Ctrl_counter.Avr_result;
                                           gss_Current_result_work = 0;
                                           gss_Voltage_result_work = 0;
                                           gtt_Ctrl_counter.Avr_result = 0;
                                           gtt_Ctrl_flag.Weld_end_disp = OFF;
                	               }
                                    } else { //2009.03.26 実効値
                	               gsl_Current_result_work_rms = gsl_Current_result_work_rms + gtt_Fpga.Curr_result_rms;
                	               gsl_Voltage_result_work_rms = gsl_Voltage_result_work_rms + gtt_Fpga.Volt_result_rms;
                	               gtt_Ctrl_counter.Avr_result++;
                	               if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	               {
//2011.10.01                                           gss_RCurrent_work = sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gss_RCurrent_work = (signed short)(sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result)-(double)0.5);//2011.10.01 300BP4
                                           gss_RVoltage_work = sqrt(gsl_Voltage_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gsl_Current_result_work_rms = 0;		//
                                           gsl_Voltage_result_work_rms = 0;		//
                                           gtt_Ctrl_counter.Avr_result = 0;
                                           gtt_Ctrl_flag.Weld_end_disp = OFF;
                	               }
                                    }
                	               gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                }
                                break;
                           default:
                                break;
                       }

                   } else if (gtt_Internal_pack.Data.In.usPulseFreq >= 5 && gtt_Internal_pack.Data.In.usPulseFreq <= 10) { //0.8～1.0Hz区間 2009.03.27 test
                       //出力電流値
                       switch (guc_Sequence_mode)
                       {
                           case INITIAL_WELD:
                           case CRATER_WELD:
                           case BURN_BACK:
                                //この区間はパルスがないので電流、電圧を算出する
                                if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
                                {
                                    if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                    {
                	               gss_Current_result_work = gss_Current_result_work + gtt_Fpga.Curr_result;
                	               gss_Voltage_result_work = gss_Voltage_result_work + gtt_Fpga.Volt_result;
                	               gtt_Ctrl_counter.Avr_result++;
                	               if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	               {
                                       gss_RCurrent_work = gss_Current_result_work / gtt_Ctrl_counter.Avr_result;
                                       gss_RVoltage_work = gss_Voltage_result_work / gtt_Ctrl_counter.Avr_result;
                                       gss_Current_result_work = 0;
                                       gss_Voltage_result_work = 0;
                                       gtt_Ctrl_counter.Avr_result = 0;
                                       gtt_Ctrl_flag.Weld_end_disp = OFF;
                	               }
                	               gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                    }
                                } else { //2009.03.26 実効値
                	               gsl_Current_result_work_rms = gsl_Current_result_work_rms + gtt_Fpga.Curr_result_rms;
                	               gsl_Voltage_result_work_rms = gsl_Voltage_result_work_rms + gtt_Fpga.Volt_result_rms;
                	               gtt_Ctrl_counter.Avr_result++;
                	               if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	               {
//2011.10.01                                           gss_RCurrent_work = sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gss_RCurrent_work = (signed short)(sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result)-(double)0.5);//2011.10.01 300BP4
                                           gss_RVoltage_work = sqrt(gsl_Voltage_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gsl_Current_result_work_rms = 0;		//
                                           gsl_Voltage_result_work_rms = 0;		//
                                           gtt_Ctrl_counter.Avr_result = 0;
                                           gtt_Ctrl_flag.Weld_end_disp = OFF;
                	               }
                                }
                                break;
                           case UP_SLOPE:
                           case DOWN_SLOPE:
                           case MAIN_WELD:
                                if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
                                {
                                    if (gtt_Ctrl_flag.Condition_change == OFF) //ベース電圧の算出（ピークに移ったら算出）
                                    {
                	                if (gtt_Ctrl_flag.Base_avr_result == OFF)
                	                {
                                        gtt_Ctrl_flag.Base_avr_result = ON;
                                        if (gtt_Ctrl_counter.Base_avr_result == 0) gtt_Ctrl_counter.Base_avr_result = 1;
                                        gss_Base_current_work = gsi_Base_current_result_work / gtt_Ctrl_counter.Base_avr_result;
                                        gss_Base_voltage_work = gsi_Base_voltage_result_work / gtt_Ctrl_counter.Base_avr_result;
                                        gsi_Base_current_result_work = 0;
                                        gsi_Base_voltage_result_work = 0;
                                        gtt_Ctrl_counter.Base_avr_result = 0;
                                        gtt_Ctrl_flag.Weld_end_disp = OFF;
                	                }
                                        if (gtt_Ctrl_flag.Peak_read_delay == OFF)
                                        {
                                            gtt_Ctrl_flag.Peak_read_delay = ON;
                                            gtt_Ctrl_counter.Peak_read_delay = 10;
                                        } else if (gtt_Ctrl_counter.Peak_read_delay <= 0){
                                          if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                          {
                	                     gsi_Base_current_result_work = gsi_Base_current_result_work + gtt_Fpga.Curr_result;
                	                     gsi_Base_voltage_result_work = gsi_Base_voltage_result_work + gtt_Fpga.Volt_result;
                	                     gtt_Ctrl_counter.Base_avr_result++;
                	                     gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                          }
                                        }
                                        gtt_Ctrl_flag.Base_read_delay = OFF;
                                    } else { //ピーク電圧の算出（ベースに移ったら算出）
                                        if (gtt_Ctrl_flag.Base_read_delay == OFF)
                                        {
                                            gtt_Ctrl_flag.Base_read_delay = ON;
                                            gtt_Ctrl_counter.Base_read_delay = 10;
                                        } else if (gtt_Ctrl_counter.Base_read_delay <= 0){
                                            if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                            {
                	                       gsi_Base_current_result_work = gsi_Base_current_result_work + gtt_Fpga.Curr_result;
                	                       gsi_Base_voltage_result_work = gsi_Base_voltage_result_work + gtt_Fpga.Volt_result;
                	                       gtt_Ctrl_counter.Base_avr_result++;
                	                       gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                            }
                                        }
                                        gtt_Ctrl_flag.Peak_read_delay = OFF;
                                        gtt_Ctrl_flag.Base_avr_result = OFF;
                                    }
                                } else { //2009.03.26 実効値
                                    if (gtt_Ctrl_flag.Condition_change == OFF) //ベース電圧の算出（ピークに移ったら算出）
                                    {
                	                if (gtt_Ctrl_flag.Base_avr_result == OFF)
                	                {
                                        gtt_Ctrl_flag.Base_avr_result = ON;
                                        if (gtt_Ctrl_counter.Base_avr_result == 0) gtt_Ctrl_counter.Base_avr_result = 1;
//2011.10.01                                            gss_Base_current_work = sqrt(gsl_Base_current_result_work_rm / gtt_Ctrl_counter.Base_avr_result);
                                            gss_Base_current_work = (signed short)(sqrt(gsl_Base_current_result_work_rm / gtt_Ctrl_counter.Base_avr_result)-(double)0.5);//2011.10.01 300BP4
                                            gss_Base_voltage_work = sqrt(gsl_Base_voltage_result_work_rm / gtt_Ctrl_counter.Base_avr_result);
                                            gsl_Base_current_result_work_rm = 0;
                                            gsl_Base_voltage_result_work_rm = 0;
                                            gtt_Ctrl_counter.Base_avr_result = 0;
                                            gtt_Ctrl_flag.Weld_end_disp = OFF;
                	                }
                                        if (gtt_Ctrl_flag.Peak_read_delay == OFF)
                                        {
                                            gtt_Ctrl_flag.Peak_read_delay = ON;
                                            gtt_Ctrl_counter.Peak_read_delay = 10;
                                        } else if (gtt_Ctrl_counter.Peak_read_delay <= 0){
                                          if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                          {
                	                     gsl_Base_current_result_work_rm = gsl_Base_current_result_work_rm + gtt_Fpga.Curr_result_rms;
                	                     gsl_Base_voltage_result_work_rm = gsl_Base_voltage_result_work_rm + gtt_Fpga.Volt_result_rms;
                	                     gtt_Ctrl_counter.Base_avr_result++;
                	                     gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                          }
                                        }
                                        gtt_Ctrl_flag.Base_read_delay = OFF;
                                    } else { //ピーク電圧の算出（ベースに移ったら算出）
                                        if (gtt_Ctrl_flag.Base_read_delay == OFF)
                                        {
                                            gtt_Ctrl_flag.Base_read_delay = ON;
                                            gtt_Ctrl_counter.Base_read_delay = 10;
                                        } else if (gtt_Ctrl_counter.Base_read_delay <= 0){
                                            if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                            {
                	                       gsl_Base_current_result_work_rm = gsl_Base_current_result_work_rm + gtt_Fpga.Curr_result_rms;
                	                       gsl_Base_voltage_result_work_rm = gsl_Base_voltage_result_work_rm + gtt_Fpga.Volt_result_rms;
                	                       gtt_Ctrl_counter.Base_avr_result++;
                	                       gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                            }
                                        }
                                        gtt_Ctrl_flag.Peak_read_delay = OFF;
                                        gtt_Ctrl_flag.Base_avr_result = OFF;
                                    }
                                }
                                //gss_Current_work = gss_Base_current_work;
                                //gss_Voltage_work = gss_Base_voltage_work;
                                gss_RCurrent_work = gss_Base_current_work; //2010.04.08
                                gss_RVoltage_work = gss_Base_voltage_work; //2010.04.08
                                break;
                           default:
                                break;
                       }
                   //} else if (gtt_Internal_pack.Data.In.usPulseFreq >= 11 && gtt_Internal_pack.Data.In.usPulseFreq <= 50){ //1.1Hz～5.0Hzの区間
                   //} else if (gtt_Internal_pack.Data.In.usPulseFreq >= 11 && gtt_Internal_pack.Data.In.usPulseFreq <= 40){ //1.1Hz～4.0Hzの区間 2009.07.29
                   } else if (gtt_Internal_pack.Data.In.usPulseFreq >= 11 && gtt_Internal_pack.Data.In.usPulseFreq <= 25){ //1.1Hz～2.5Hzの区間 2011.11.14
                                if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                {
                                   if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
                                   {
                                   short pss_Avr_result_work;
                	               gsl_Current_result_work2 = gsl_Current_result_work2 + gtt_Fpga.Curr_result;
                	               gsl_Voltage_result_work2 = gsl_Voltage_result_work2 + gtt_Fpga.Volt_result;
                	               gtt_Ctrl_counter.Avr_result++;
                	               //if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                                   pss_Avr_result_work = 2000; //2009.04.11
                	               if (gtt_Ctrl_counter.Avr_result >=  (pss_Avr_result_work / gtt_Internal_pack.Data.In.usPulseFreq)) //2009.04.11
                	               {
                                           gss_RCurrent_work = gsl_Current_result_work2 / gtt_Ctrl_counter.Avr_result;
                                           gss_RVoltage_work = gsl_Voltage_result_work2 / gtt_Ctrl_counter.Avr_result;
                                           gsl_Current_result_work2 = 0;
                                           gsl_Voltage_result_work2 = 0;
                                           gtt_Ctrl_counter.Avr_result = 0;
                                           gtt_Ctrl_flag.Weld_end_disp = OFF;
                	               }
                                    } else { //2009.03.26 実効値
                                   short pss_Avr_result_work;
                	               gsl_Current_result_work_rms = gsl_Current_result_work_rms + gtt_Fpga.Curr_result_rms;
                	               gsl_Voltage_result_work_rms = gsl_Voltage_result_work_rms + gtt_Fpga.Volt_result_rms;
                	               gtt_Ctrl_counter.Avr_result++;
                                   pss_Avr_result_work = 2000; //2009.04.11
                	               if (gtt_Ctrl_counter.Avr_result >=  (pss_Avr_result_work / gtt_Internal_pack.Data.In.usPulseFreq)) //2009.04.11
                	               //if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	               {
//2011.10.01                                           gss_RCurrent_work = sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gss_RCurrent_work = (signed short)(sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result)-(double)0.5);//2011.10.01 300BP4
                                           gss_RVoltage_work = sqrt(gsl_Voltage_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gsl_Current_result_work_rms = 0;		//
                                           gsl_Voltage_result_work_rms = 0;		//
                                           gtt_Ctrl_counter.Avr_result = 0;
                                           gtt_Ctrl_flag.Weld_end_disp = OFF;
                                        }
                                    }
                	            gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                }
                   } else {//4.1Hz以上の区間 2009.07.29
                                if(Timer._10m != gtt_Ctrl_counter.Backup_10m)
                                {
                                   if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
                                   {
                                   short pss_Avr_result_work;
                	               gss_Current_result_work = gss_Current_result_work + gtt_Fpga.Curr_result;
                	               gss_Voltage_result_work = gss_Voltage_result_work + gtt_Fpga.Volt_result;
                	               gtt_Ctrl_counter.Avr_result++;
                	               if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	               {
                                           gss_RCurrent_work = gss_Current_result_work / gtt_Ctrl_counter.Avr_result;
                                           gss_RVoltage_work = gss_Voltage_result_work / gtt_Ctrl_counter.Avr_result;
                                           gss_Current_result_work = 0;
                                           gss_Voltage_result_work = 0;
                                           gtt_Ctrl_counter.Avr_result = 0;
                                           gtt_Ctrl_flag.Weld_end_disp = OFF;
                	               }
                                    } else { //2009.03.26 実効値
                	               gsl_Current_result_work_rms = gsl_Current_result_work_rms + gtt_Fpga.Curr_result_rms;
                	               gsl_Voltage_result_work_rms = gsl_Voltage_result_work_rms + gtt_Fpga.Volt_result_rms;
                	               gtt_Ctrl_counter.Avr_result++;
                	               if (gtt_Ctrl_counter.Avr_result >= AVR_RESULT_COUNT2)
                	               {
//2011.10.01                                           gss_RCurrent_work = sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gss_RCurrent_work = (signed short)(sqrt(gsl_Current_result_work_rms / gtt_Ctrl_counter.Avr_result)-(double)0.5);//2011.10.01 300BP4
                                           gss_RVoltage_work = sqrt(gsl_Voltage_result_work_rms / gtt_Ctrl_counter.Avr_result);
                                           gsl_Current_result_work_rms = 0;		//
                                           gsl_Voltage_result_work_rms = 0;		//
                                           gtt_Ctrl_counter.Avr_result = 0;
                                           gtt_Ctrl_flag.Weld_end_disp = OFF;
                                        }
                                    }
                	            gtt_Ctrl_counter.Backup_10m = Timer._10m;
                                }
                   }

             }
       
            















#if 0 //del 2009.07.13
            if ((gtt_Internal_pack.Data.In.fPulseMode.ALL >> 4) & 0x0f == 0x00) //直流
            {
                 guc_Pulse_mode_data = (guc_Pulse_mode_data & 0x80) | 0x03;
            }
            if ((gtt_Internal_pack.Data.In.fPulseMode.ALL >> 4) & 0x0f == 0x01) //パルス
            {
                 guc_Pulse_mode_data = (guc_Pulse_mode_data & 0x80) | 0x05;
            }
#endif

       //<><><> ０ｘ６９コマンド関連 <><><>
       if (guc_0x69_rewrite_check_flag1 == 1)              // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
       {
           //<><> 制限 2009.07.30 <><>
             if (ComuniPack.Data.To.usPulseFreq   > 5000)  { ComuniPack.Data.To.usPulseFreq    = 5000; }

             if (ComuniPack.Data.To.usPulseDuty    >  95)  { ComuniPack.Data.To.usPulseDuty     =  95; }
             if (ComuniPack.Data.To.usPulseDuty    <   5)  { ComuniPack.Data.To.usPulseDuty     =   5; }
           //<><><><><><><><><><><><><>
		   gtt_Internal_pack.Data.In.usPulseFreq                = ComuniPack.Data.To.usPulseFreq;            // パルス指令周波数
		   gtt_Internal_pack.Data.In.usPulseDuty                = ComuniPack.Data.To.usPulseDuty;            // パルス指令幅
           guc_0x69_rewrite_check_flag1 = 2;

           //<><> 制限 2009.07.30 <><>
           if (ComuniPack.Data.To.usPulseFreq == 0)
           {
               guc_Pulse_mode_data          = 0; //パルス無
               guc_Pulse_mode_counter       = 0; //
		       gtt_Internal_pack.Data.In.usPulseFreq  = 1;          // パルス指令周波数
           } else {
               if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Pulse_ctrl == true)
               {
                   guc_Pulse_mode_data          = 1;
                   guc_Pulse_mode_counter       = 1;
               }
           }
           //<><><><><><><><><><><><><>
       }
            //<><><> 溶接法、パルスの選択 2009.07.13 <><><>
              //溶接法
                switch ((gtt_Internal_pack.Data.In.fPulseMode.ALL & 0xf0))
                {
                   case 0x00 ://直流
                        guc_Method_condition_data    = STD_DC_METHOD;
                        guc_Method_condition_counter = STD_DC_METHOD;
                        //if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Pulse_ctrl == true)
                        if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Pulse_ctrl == true && ComuniPack.Data.To.usPulseFreq != 0) //2009.07.30
                        {
                            guc_Pulse_mode_data          = 1; //パルス有
                            guc_Pulse_mode_counter       = 1; //
                        } else {
                            guc_Pulse_mode_data          = 0; //パルス無
                            guc_Pulse_mode_counter       = 0; //
                        }
                        break;
                   case 0x10://交流
                        guc_Method_condition_data    = STD_AC_METHOD;
                        guc_Method_condition_counter = STD_AC_METHOD;
                        switch ((gtt_Internal_pack.Data.In.fPulseMode.ALL & 0x0f))
                        {
                           case 0x00: //標準
                                guc_Ac_wave_counter = 0;
                                break;
                           case 0x01: //ハード
                                guc_Ac_wave_counter = 1;
                                break;
                           case 0x02: //ソフト
                                guc_Ac_wave_counter = 2;
                                break;
                           default:
                                guc_Ac_wave_counter = 0;
                                break;
                        }
                        //if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Pulse_ctrl == true)
                        if (gtt_Internal_pack.Data.In.fControl.Bit1Sw.Pulse_ctrl == true && ComuniPack.Data.To.usPulseFreq != 0) //2009.07.30
                        {
                            guc_Pulse_mode_data          = 1; //パルス有
                            guc_Pulse_mode_counter       = 1; //
                        } else {
                            guc_Pulse_mode_data          = 0; //パルス無
                            guc_Pulse_mode_counter       = 0; //
                        }

                        
                        break;
                   case 0x20://ＭＩＸ
                        guc_Method_condition_data    = STD_MIX_METHOD;
                        guc_Method_condition_counter = STD_MIX_METHOD;
                        guc_Pulse_mode_data          = 0; //ＭＩＸではパルスは必要ないので無にする。
                        guc_Pulse_mode_counter       = 0; //ＭＩＸではパルスは必要ないので無にする。
                        
                        break;
                   default:
                        guc_Method_condition_data    = STD_DC_METHOD;
                        guc_Method_condition_counter = STD_DC_METHOD;
                        break;
                }

                //<><><><> 出力制限の反映 2010.01.12 <><><><>
                switch (guc_Method_condition_data)
                {
                    case STD_DC_METHOD:
                    case STD_MIX_METHOD:
                    case EXP_DC_METHOD:
                    case EXP_AC_METHOD:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         {
                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT = MAX_CURRENT_VAL;
                         }
                         break;
                    case STD_AC_METHOD:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         {
                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT = MAX_CURRENT_VAL;
                         }
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_AC_SOFT_VAL)
                         {
                             MAX_CURRENT_AC_SOFT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT_AC_SOFT = MAX_CURRENT_AC_SOFT_VAL;
                         }
                         break;
                    case STD_HAND_METHOD:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_HAND_VAL)
                         {
                             MAX_CURRENT_HAND = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT_HAND = MAX_CURRENT_HAND_VAL;
                         }
                         break;
                    default:
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         {
                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT = MAX_CURRENT_VAL;
                         }
                         break;
                }
                //<><><><><><><><><><><><><><><><><><><><><><>

                        //**** 制限電流セット 2009.02.19 *****************************************
                        if (guc_Method_condition_data == STD_DC_METHOD)
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT;
                        }
                        if (guc_Method_condition_data == STD_AC_METHOD)
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            //***** 2009.03.13 *****
                    		if (guc_Ac_wave_counter == 1) //ハードＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT;
                                gss_Min_current = MIN_CURRENT_AC_HARD; //2011.09.30
                            }
                    		if (guc_Ac_wave_counter == 2) //ソフトＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT_AC_SOFT;
                                gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            }
                            //**********************

                        }
                        if (guc_Method_condition_data == STD_MIX_METHOD) //2009.03.17
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                        }
                        
                        
                        //本溶接
                   	    if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
       					}
       					if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
       					}
                        //パルス電流
                       	if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
                       	{
        		    	    gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        				}
        				if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                       	{
        		    	    gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        				}
                        //************************************************************************

            //<><><><><><><><><><><><><><><><><><><><><><><>
        }
		//gtt_Internal_pack.Data.In.vHotTime                   = ComuniPack.Data.To.vHotTime;               // ホットタイム 2007.2.5削除
		//gtt_Internal_pack.Data.In.vIniIpAdj                  = ComuniPack.Data.To.vIniIpAdj;              // スタートピーク電流微調整           2009.07.10 del
		//gtt_Internal_pack.Data.In.vIniIbAdj                  = ComuniPack.Data.To.vIniIbAdj;              // スタートベース電流微調整           2009.07.10 del
		//gtt_Internal_pack.Data.In.vIpAdj                     = ComuniPack.Data.To.vIpAdj;                 // パルスピーク電流微調整             2009.07.10 del
		//gtt_Internal_pack.Data.In.vIb1Adj                    = ComuniPack.Data.To.vIb1Adj;                // パルス第１ベース電流微調整         2009.07.10 del
		//gtt_Internal_pack.Data.In.vIb2Adj                    = ComuniPack.Data.To.vIb2Adj;                // パルス第２ベース電流微調整         2009.07.10 del
		//gtt_Internal_pack.Data.In.vIprAdj                    = ComuniPack.Data.To.vIprAdj;                // パルスピーク立ち上がり微調整       2009.07.10 del
		//gtt_Internal_pack.Data.In.vIpfAdj                    = ComuniPack.Data.To.vIpfAdj;                // パルスピーク立ち下がり微調整       2009.07.10 del
		//gtt_Internal_pack.Data.In.vTiprAdj                   = ComuniPack.Data.To.vTiprAdj;               // パルス立ち上がり時間微調整         2009.07.10 del
		//gtt_Internal_pack.Data.In.vTipAdj                    = ComuniPack.Data.To.vTipAdj;                // パルスピーク立ち上がり時間微調整   2009.07.10 del
		//gtt_Internal_pack.Data.In.vTipfAdj                   = ComuniPack.Data.To.vTipfAdj;               // パルス立ち下がり時間微調整         2009.07.10 del
		gtt_Internal_pack.Data.In.vPulseFreqAdj              = ComuniPack.Data.To.vPulseFreqAdj;          // パルス周波数微調整
		gtt_Internal_pack.Data.In.vLowPulseAB_LevelGap       = ComuniPack.Data.To.vLowPulseAB_LevelGap;   // 簡易ローパルス：Ａ条件Ｂ条件レベル差
		gtt_Internal_pack.Data.In.vLowPulseAB_TimeRatio      = ComuniPack.Data.To.vLowPulseAB_TimeRatio;  // 簡易ローパルス：Ａ条件Ｂ条件時間比率
		gtt_Internal_pack.Data.In.vLowPulseFreq              = ComuniPack.Data.To.vLowPulseFreq;          // 簡易ローパルス：周波数
		gtt_Internal_pack.Data.In.vLowPulseStartTimeAdj      = ComuniPack.Data.To.vLowPulseStartTimeAdj;  // 簡易ローパルス開始時間微調整
		gtt_Internal_pack.Data.In.vPulseStartSlope           = ComuniPack.Data.To.vPulseStartSlope;       // パルススタートスロープ
		gtt_Internal_pack.Data.In.vPulseExecSlope            = ComuniPack.Data.To.vPulseExecSlope;        // パルス指令値切り替えスロープ
		gtt_Internal_pack.Data.In.vPulsePerformance          = ComuniPack.Data.To.vPulsePerformance;      // パルス応答性
		gtt_Internal_pack.Data.In.fLotCheck.ALL              = ComuniPack.Data.To.fLotCheck.ALL;          // 製品検査用
		gtt_Internal_pack.Data.In.vAfterFlowAddTime          = ComuniPack.Data.To.vAfterFlowAddTime;      // アフターフロー時間加算値
       }
#if G3_NEW_COM

       if (guc_Method_rewrite_check_flag == 1) //2007.7.6追加
	   {
           gtt_Internal_pack.Data.In.fWireDiameter.ALL          = ComuniPack.Data.To.fWireDiameter.ALL;      // ワイヤ径
		   gtt_Internal_pack.Data.In.fWelding.ALL               = ComuniPack.Data.To.fWelding.ALL;           // 溶接法
		   gtt_Internal_pack.Data.In.fWireMaterial.ALL          = ComuniPack.Data.To.fWireMaterial.ALL;      // ワイヤ材質
		   gtt_Internal_pack.Data.In.fWireSelect.ALL            = ComuniPack.Data.To.fWireSelect.ALL;        // ワイヤ種
		   gtt_Internal_pack.Data.In.fInitialSelect1.ALL        = ComuniPack.Data.To.fInitialSelect1.ALL;    // 初期データ設定１
           guc_Method_rewrite_check_flag      = 0;              // 0:書き換え無しｏｒ書き換え終了 1:書き換えのため受信済み　溶接条件データ書き換え確認フラグ
       }

       if (guc_Hfix_rewrite_check_flag == 1)             // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 半固定データ書き換え確認フラグ
       {
           gtt_Internal_rewrite_data.Hfix_no   = gtt_Com_rewrite_data.Hfix_no;
           gtt_Internal_rewrite_data.Hfix_data = gtt_Com_rewrite_data.Hfix_data;
           guc_Hfix_rewrite_check_flag = 2;
       }
       if (guc_Val_rewrite_check_flag0 == 1)              // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
       {
           gtt_Internal_rewrite_data.Val_no0       = gtt_Com_rewrite_data.Val_no0;
           gtt_Internal_rewrite_data.Val_a_data0   = gtt_Com_rewrite_data.Val_a_data0;
           gtt_Internal_rewrite_data.Val_b_data0   = gtt_Com_rewrite_data.Val_b_data0;
           gtt_Internal_rewrite_data.Val_c_data0   = gtt_Com_rewrite_data.Val_c_data0;
           gtt_Internal_rewrite_data.Val_min_data0 = gtt_Com_rewrite_data.Val_min_data0;
           gtt_Internal_rewrite_data.Val_max_data0 = gtt_Com_rewrite_data.Val_max_data0;
           guc_Val_rewrite_check_flag0 = 2;
       }
       if (guc_Val_rewrite_check_flag1 == 1)              // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
       {
           gtt_Internal_rewrite_data.Val_no1       = gtt_Com_rewrite_data.Val_no1;
           gtt_Internal_rewrite_data.Val_a_data1   = gtt_Com_rewrite_data.Val_a_data1;
           gtt_Internal_rewrite_data.Val_b_data1   = gtt_Com_rewrite_data.Val_b_data1;
           gtt_Internal_rewrite_data.Val_c_data1   = gtt_Com_rewrite_data.Val_c_data1;
           gtt_Internal_rewrite_data.Val_min_data1 = gtt_Com_rewrite_data.Val_min_data1;
           gtt_Internal_rewrite_data.Val_max_data1 = gtt_Com_rewrite_data.Val_max_data1;
           guc_Val_rewrite_check_flag1 = 2;
       }

       //<><><> ０ｘ６９コマンド関連 <><><>
#if 0 //2009.07.30 場所移動
       if (guc_0x69_rewrite_check_flag1 == 1)              // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
       {
           //<><> 制限 2009.07.30 <><>
             if (ComuniPack.Data.To.usPulseFreq   > 5000)  { ComuniPack.Data.To.usPulseFreq    = 5000; }

             if (ComuniPack.Data.To.usPulseDuty    >  95)  { ComuniPack.Data.To.usPulseDuty     =  95; }
             if (ComuniPack.Data.To.usPulseDuty    <   5)  { ComuniPack.Data.To.usPulseDuty     =   5; }
           //<><><><><><><><><><><><><>
		   gtt_Internal_pack.Data.In.usPulseFreq                = ComuniPack.Data.To.usPulseFreq;            // パルス指令周波数
		   gtt_Internal_pack.Data.In.usPulseDuty                = ComuniPack.Data.To.usPulseDuty;            // パルス指令幅
           guc_0x69_rewrite_check_flag1 = 2;

           //<><> 制限 2009.07.30 <><>
           if (ComuniPack.Data.To.usPulseFreq == 0.0)
           {
               guc_Pulse_mode_data          = 0; //パルス無
               guc_Pulse_mode_counter       = 0; //
		       gtt_Internal_pack.Data.In.usPulseFreq  = 1;          // パルス指令周波数
           }
           //<><><><><><><><><><><><><>
       }
#endif

       //微調整項目１変数転送　2007.2.5追加
#if 0 //2009.07.10 del
       if (guc_Adj1_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目１書き換え確認フラグ 2007.2.5追加
       {
		   gtt_Internal_pack.Data.In.vTsoAdj       = (float)((float)ComuniPack.Data.To.vTsoAdj      * TS0);    // 短絡初期時間調整 2007.2.5
		   gtt_Internal_pack.Data.In.vIscAdj       = (float)((float)ComuniPack.Data.To.vIscAdj      * ISC);    // 短絡電流屈折値調整 2007.2.5
		   gtt_Internal_pack.Data.In.vIsl1Adj      = (float)((float)ComuniPack.Data.To.vIsl1Adj     * ISL1);   // 短絡電流勾配１調整 2007.2.5
		   gtt_Internal_pack.Data.In.vIsl2Adj      = (float)((float)ComuniPack.Data.To.vIsl2Adj     * ISL2);   // 短絡電流勾配２調整 2007.2.5
		   gtt_Internal_pack.Data.In.vTspAdj       = ComuniPack.Data.To.vTspAdj;                // 突っ掛かり防止時間調整 2007.2.5　未使用
		   gtt_Internal_pack.Data.In.vIacAdj       = ComuniPack.Data.To.vIacAdj;                // アーク電流屈折値調整 2007.2.5　未使用
           guc_Adj1_rewrite_check_flag = 2;
       }
#endif
       //微調整項目２変数転送　2007.2.5追加
#if 0 //2009.07.10 del
       if (guc_Adj2_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       {
		   gtt_Internal_pack.Data.In.vIhotAdj      = (short)((float)ComuniPack.Data.To.vIhotAdj     * HOTCUR); // ホット電流調整 2007.2.5
		   gtt_Internal_pack.Data.In.vVhotAdj      = (float)((float)ComuniPack.Data.To.vVhotAdj     * HOTVLT); // ホット電圧調整 2007.2.5
		   gtt_Internal_pack.Data.In.vHotTime      = (short)((short)ComuniPack.Data.To.vHotTime     * HOTTM);  // ホットタイム 2007.2.5
		   gtt_Internal_pack.Data.In.vSldnAdj      = (short)((short)ComuniPack.Data.To.vSldnAdj     * WIRSLDN);// ワイヤスローダウン調整 2007.2.5
		   gtt_Internal_pack.Data.In.vFttAdj       = (short)((float)ComuniPack.Data.To.vFttAdj      * FTTLVL); // ＦＴＴレベル調整 2007.2.5
		   gtt_Internal_pack.Data.In.vBarnBackAdj  = (short)((short)ComuniPack.Data.To.vBarnBackAdj * BBKTIME);// バーンバック時間調整 2007.2.5
           guc_Adj2_rewrite_check_flag = 2;
       }
#endif

       if ( guc_Table_change_flag       == 1)       // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み テーブル切り替え確認フラグ 2007.2.9
       {
	       gtt_Internal_pack.Data.In.vTableChange  = ComuniPack.Data.To.vTableChange;           // ＣＯ２テーブル切り替え 2007.2.9
           guc_Table_change_flag = 2;
       }
#else
       if ((gtt_Internal_pack.Data.In.fInitialSelect1.ALL) & 0x01 == 0x01) //一元電圧選択
       {
           gtt_Internal_pack.Data.In.usWeldingVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingCurr / 2] * 2) + gtt_Okcv.Okcv_ref);
       } else {
           if (gtt_Internal_pack.Data.In.usWeldingVolt < 0)
           {
               gtt_Internal_pack.Data.In.usWeldingVolt = gtt_Internal_pack.Data.In.usWeldingVolt * -1;
           }
       }
#endif
       //拡張溶接微調パラメータ個別　2007.5.29追加
       if (guc_Exd_adj1_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       {
           //<><><><><> 範囲指定 2009.07.29 <><><><><>
#if 0 //2009.07.30 del
                 //ID 0x01
                 if (ComuniPack.Data.To.Sp_current    >  200)  { ComuniPack.Data.To.Sp_current     =  200; }
                 if (ComuniPack.Data.To.Sp_current    < -200)  { ComuniPack.Data.To.Sp_current     = -200; }
                 //ID 0x02
                 if (ComuniPack.Data.To.Sp_time       >  300)  { ComuniPack.Data.To.Sp_time        =  300; }
                 if (ComuniPack.Data.To.Sp_time       < -300)  { ComuniPack.Data.To.Sp_time        = -300; }
                 //ID 0x03
                 if (ComuniPack.Data.To.Eli           >   50)  { ComuniPack.Data.To.Eli            =   50; }
                 if (ComuniPack.Data.To.Eli           <  -50)  { ComuniPack.Data.To.Eli            =  -50; }

                 //ID 0x04
                 //ID 0x05
                 //ID 0x06
                 //ID 0x07
                 
                 //ID 0x08
                 if (ComuniPack.Data.To.vVhotAdj      >   50)  { ComuniPack.Data.To.vVhotAdj       =   50; }
                 if (ComuniPack.Data.To.vVhotAdj      <  -50)  { ComuniPack.Data.To.vVhotAdj       =  -50; }
                 //ID 0x09
                 if (ComuniPack.Data.To.vFttAdj       >  100)  { ComuniPack.Data.To.vFttAdj        =  100; }
                 if (ComuniPack.Data.To.vFttAdj       < -100)  { ComuniPack.Data.To.vFttAdj        = -100; }
                 //ID 0x0A
                 if (ComuniPack.Data.To.vBarnBackAdj  >  100)  { ComuniPack.Data.To.vBarnBackAdj   =  100; }
                 if (ComuniPack.Data.To.vBarnBackAdj  < -100)  { ComuniPack.Data.To.vBarnBackAdj   = -100; }
                 //ID 0x0B
                 if (ComuniPack.Data.To.vSldnAdj      >   50)  { ComuniPack.Data.To.vSldnAdj       =   50; }
                 if (ComuniPack.Data.To.vSldnAdj      <  -50)  { ComuniPack.Data.To.vSldnAdj       =  -50; }
                 //ID 0x0C
                 if (ComuniPack.Data.To.vIsl1Adj      >  100)  { ComuniPack.Data.To.vIsl1Adj       =  100; }
                 if (ComuniPack.Data.To.vIsl1Adj      < -100)  { ComuniPack.Data.To.vIsl1Adj       = -100; }
                 //ID 0x0D
                 if (ComuniPack.Data.To.vIsl2Adj      >  100)  { ComuniPack.Data.To.vIsl2Adj       =  100; }
                 if (ComuniPack.Data.To.vIsl2Adj      < -100)  { ComuniPack.Data.To.vIsl2Adj       = -100; }
                 //ID 0x0E
                 if (ComuniPack.Data.To.vIacAdj       >  200)  { ComuniPack.Data.To.vIacAdj        =  200; }
                 if (ComuniPack.Data.To.vIacAdj       < -200)  { ComuniPack.Data.To.vIacAdj        = -200; }
                 //ID 0x0F
                 if (ComuniPack.Data.To.vIscAdj       >  200)  { ComuniPack.Data.To.vIscAdj        =  200; }
                 if (ComuniPack.Data.To.vIscAdj       < -200)  { ComuniPack.Data.To.vIscAdj        = -200; }
                 //ID 0x10
                 if (ComuniPack.Data.To.vIpAdj        >  200)  { ComuniPack.Data.To.vIpAdj         =  200; }
                 if (ComuniPack.Data.To.vIpAdj        < -200)  { ComuniPack.Data.To.vIpAdj         = -200; }
                 //ID 0x11
                 if (ComuniPack.Data.To.vIb1Adj       >  200)  { ComuniPack.Data.To.vIb1Adj        =  200; }
                 if (ComuniPack.Data.To.vIb1Ad        < -200)  { ComuniPack.Data.To.vIb1Adj        = -200; }
                 //ID 0x12
                 
#endif

                 //<><><> 2009.07.30 追加 <><><>
                 //ID 0x28     //交流周波数
                 if (ComuniPack.Data.To.usAcFreq       >  400)  { ComuniPack.Data.To.usAcFreq        =  400; }
                 if (ComuniPack.Data.To.usAcFreq       <   30)  { ComuniPack.Data.To.usAcFreq        =   30; }
                 //ID 0x29     //クリーニング幅
                 if (ComuniPack.Data.To.ucCleaningDuty >   90)  { ComuniPack.Data.To.ucCleaningDuty  =   90; }
                 if (ComuniPack.Data.To.ucCleaningDuty <   50)  { ComuniPack.Data.To.ucCleaningDuty  =   50; }
                 //ID 0x2A     //MIX TIG周波数
                 if (ComuniPack.Data.To.ucMixFreq      >  200)  { ComuniPack.Data.To.ucMixFreq       =   200; }
                 if (ComuniPack.Data.To.ucMixFreq      <    1)  { ComuniPack.Data.To.ucMixFreq       =     1; }
                 //ID 0x2B     //MIX(AC)比率
                 if (ComuniPack.Data.To.ucMixAcRatio   >   18)  { ComuniPack.Data.To.ucMixAcRatio    =    18; }
                 if (ComuniPack.Data.To.ucMixAcRatio   <    2)  { ComuniPack.Data.To.ucMixAcRatio    =     2; }
                 //<><><><><><><><><><><><><><><>



                 
           //<><><><><><><><><><><><><><><><><><><><>

           gtt_Internal_pack.Data.In.Id_no = ComuniPack.Data.To.Id_no; //ＩＤ番号の取得

           switch (gtt_Internal_pack.Data.In.Id_no)
           {
                   case 1:
                        gtt_Internal_pack.Data.In.Sp_current      =  (float)((float)ComuniPack.Data.To.Sp_current * SP_I);            //ＳＰ電流
                        break;
                   case 2:
                        gtt_Internal_pack.Data.In.Sp_time         =  (float)((float)ComuniPack.Data.To.Sp_time    * SP_T);            //ＳＰ時間
                        break;
                   case 3:
                        gtt_Internal_pack.Data.In.Eli             =  (float)((float)ComuniPack.Data.To.Eli        * ELI);             //ＥＬＩ
                        break;
                   case 4:
                        //gtt_Internal_pack.Data.In.Mts_v           =  (float)((float)ComuniPack.Data.To.Mts_v      * MTS_V);           //重畳電圧値 del 2009.07.14
                        break;
                   case 5:
                        //gtt_Internal_pack.Data.In.Mts_ontime      =  (float)((float)ComuniPack.Data.To.Mts_ontime * MTS_ONTIME);      //重畳電圧ＯＮ時間 del 2009.07.14
                        break;
                   case 6:
                        //gtt_Internal_pack.Data.In.Mts_cycle       =  (float)((float)ComuniPack.Data.To.Mts_cycle  * MTS_CYCLE);       //重畳電圧周期 del 2009.07.14
                        break;
                   case 7: //2009.07.10
                        //gtt_Internal_pack.Data.In.Stdc_time       =  ComuniPack.Data.To.Stdc_time  * STDC_TIME;                       //開始ＤＣ時間 del 2009.07.14
                        break;
                   case 0x08: //2009.07.10
	                    gtt_Internal_pack.Data.In.vVhotAdj        =  (float)((float)ComuniPack.Data.To.vVhotAdj     * HOTVLT);        // ホット電圧微調整
                        break;
                   case 0x09: //2009.07.10
	                    gtt_Internal_pack.Data.In.vFttAdj         =  (short)((float)ComuniPack.Data.To.vFttAdj      * FTTLVL);        // ＦＴＴレベル微調整
                        break;
                   case 0x0a: //2009.07.10
	                    gtt_Internal_pack.Data.In.vBarnBackAdj    =  (short)((short)ComuniPack.Data.To.vBarnBackAdj);  //2009.07.07 BBKTIM del// バーンバック時間微調整
                        break;
                   case 0x0b: //2009.07.10
	                    gtt_Internal_pack.Data.In.vSldnAdj        =  (short)((short)ComuniPack.Data.To.vSldnAdj     * WIRSLDN);       // スローダウン速度微調整
                        break;
                   case 0x0c: //2009.07.10
	                    gtt_Internal_pack.Data.In.vIsl1Adj        =  (float)((float)ComuniPack.Data.To.vIsl1Adj); //2009.07.07 ISL1 del    // 短絡電流第１勾配微調整
                        break;
                   case 0x0d: //2009.07.10
	                    gtt_Internal_pack.Data.In.vIsl2Adj        =  (float)((float)ComuniPack.Data.To.vIsl2Adj); //2009.07.07 ISL2 del    // 短絡電流第２勾配微調整
                        break;
                   case 0x0e: //2009.07.10
	                    gtt_Internal_pack.Data.In.vIacAdj         =  (float)((float)ComuniPack.Data.To.vIacAdj      * IAC);           // アーク再生直後電流微調整
                        break;
                   case 0x0f: //2009.07.10
	                    gtt_Internal_pack.Data.In.vIscAdj         =  (float)((float)ComuniPack.Data.To.vIscAdj);  //2009.07.07 ISC del     // 短絡電流屈曲点微調整
                        break;
                   case 0x10: //2009.07.10
                        gtt_Internal_pack.Data.In.vIpAdj          =  (float)((float)ComuniPack.Data.To.vIpAdj       * PULSE_PEAK_CUR);// パルスピーク電流微調整
                        break;
                   case 0x11: //2009.07.10
                        gtt_Internal_pack.Data.In.vIb1Adj         =  (float)((float)ComuniPack.Data.To.vIb1Adj      * PULSE_BASE_CUR);// パルス第１ベース電流微調整
                        break;
                   case 0x12: //2009.07.10
                        //無効
                        break;
                   case 0x13: //2009.07.10
                        gtt_Internal_pack.Data.In.vIprAdj         =  (float)((float)ComuniPack.Data.To.vIprAdj      * PRISE);         //パルスピーク立ち上がり微調整
                        break;
                   case 0x14: //2009.07.10
                        gtt_Internal_pack.Data.In.vIpfAdj         =  (float)((float)ComuniPack.Data.To.vIpfAdj      * PFALL);         //パルスピーク立ち下がり微調整
                        break;
                   case 0x15: //2009.07.10
                        gtt_Internal_pack.Data.In.vIniIpAdj       =  (short)((float)ComuniPack.Data.To.vIniIpAdj    * INIT_IP);       //スタートピーク電流微調整
                        break;
                   case 0x16: //2009.07.10
                        gtt_Internal_pack.Data.In.vIniIbAdj       =  (short)((float)ComuniPack.Data.To.vIniIbAdj    * INIT_IB);       //スタートベース電流微調整
                        break;
                   case 0x17: //2009.07.10 del2009.07.14
                        //gtt_Internal_pack.Data.In.vIb2Adj         =  (float)((float)ComuniPack.Data.To.vIb2Adj      * PULSE_BASE_CUR2);// パルス第２ベース電流微調整 del 2009.07.14
                        break;
                   case 0x18: //2009.07.10
                        gtt_Internal_pack.Data.In.vTiprAdj        =  (float)((float)ComuniPack.Data.To.vTiprAdj     * PULSE_RISE_CUR);//パルス立ち上がり時間微調整
                        break;
                   case 0x19: //2009.07.10
                        gtt_Internal_pack.Data.In.vTipfAdj        =  (float)((float)ComuniPack.Data.To.vTipfAdj     * PULSE_FALL_CUR);//パルス立ち下がり時間微調整
                        break;
                   case 0x1A: //2009.07.10
                        gtt_Internal_pack.Data.In.vTipAdj         =  (float)((float)ComuniPack.Data.To.vTipAdj      * PULSE_WIDTH);   //パルスピーク立ち上がり時間微調整
                        break;
                   case 0x1B: //2009.07.10
                        gtt_Internal_pack.Data.In.vTsoAdj         =  (float)((float)ComuniPack.Data.To.vTsoAdj);   //2009.07.07 PENETRATION del//短絡初期時間調整
                        break;
                   case 0x1C: //2009.07.10
                        //gtt_Internal_pack.Data.In.vIhotAdj        = ComuniPack.Data.To.vIhotAdj                     * HOTCUR;         //ホット電流調整
                        gtt_Internal_pack.Data.In.vIhotAdj        = ComuniPack.Data.To.vIhotAdj;         //ホット電流調整 2009.07.28
                        break;
                   case 0x1d: //2009.07.10
                        gtt_Internal_pack.Data.In.vHotTime        = ComuniPack.Data.To.vHotTime;                                      //ホットタイム
                        break;
                   case 0x1e: //2009.07.10
                        gtt_Internal_pack.Data.In.vStartPulse     = ComuniPack.Data.To.vStartPulse;                                   //スタートパルス有り無し
                        break;
                   case 0x1f: //2009.07.10
                        gtt_Internal_pack.Data.In.vEndPulse       = ComuniPack.Data.To.vEndPulse;                                     //エンドパルス有り無し
                        break;
                   case 0x20: //2009.07.10
                        gtt_Internal_pack.Data.In.vIniPulseFreqAdj= ComuniPack.Data.To.vIniPulseFreqAdj;                              //イニシャルパルス周波数
                        break;
                   case 0x21: //2009.07.10
                        gtt_Internal_pack.Data.In.vPctrlBlowAdj   = ComuniPack.Data.To.vPctrlBlowAdj;                                 //アークブロー抑制制御
                        break;
                   case 0x22: //2009.07.10
                        gtt_Internal_pack.Data.In.vWirSpdAdj      = ComuniPack.Data.To.vWirSpdAdj;                                    //ワイヤスピード微調整
                        break;
                   case 0x23: //2009.07.10 del2009.07.14
                        //gtt_Internal_pack.Data.In.vWirStrAccAdj   = (float)((float)ComuniPack.Data.To.vWirStrAccAdj * START_CTRL);    //スタートスロープ微調整
                        break;
                   case 0x24: //2009.07.10
                        gtt_Internal_pack.Data.In.vWirStrDelayAdj = (float)((float)ComuniPack.Data.To.vWirStrDelayAdj * START_TIME);  //ワイヤスタートディレイ微調整
                        break;
                   case 0x25: //2009.07.10
                        gtt_Internal_pack.Data.In.vNeckLvlAdj     = (float)ComuniPack.Data.To.vNeckLvlAdj;                            //ネックレベル微調整
                        break;
                   case 0x26: //2009.07.10 del2009.07.14
                        //gtt_Internal_pack.Data.In.vWirAcDcAdj     = (float)((float)ComuniPack.Data.To.vWirAcDcAdj  * WIRACDC);        //加速度３
                        break;
                   case 0x27: //2009.07.10
                        gtt_Internal_pack.Data.In.vBbkPulseAdj    = ComuniPack.Data.To.vBbkPulseAdj;                                  //バーンバックパルス
                        break;
                   case 0x28: //2009.07.10
                        gtt_Internal_pack.Data.In.usAcFreq        = ComuniPack.Data.To.usAcFreq;                                      //交流周波数
                        break;
                   case 0x29: //2009.07.10
                        //gtt_Internal_pack.Data.In.ucCleaningDuty  = ComuniPack.Data.To.ucCleaningDuty;                                //クリーニング幅
                        gtt_Internal_pack.Data.In.ucCleaningDuty  = 100 - ComuniPack.Data.To.ucCleaningDuty;                         //クリーニング幅 2009.07.23 反転処理追加
                        break;
                   case 0x2A: //2009.07.10
                        gtt_Internal_pack.Data.In.ucMixFreq       = ComuniPack.Data.To.ucMixFreq; //                                     //MIX TIG周波数
                        break;
                   case 0x2B: //2009.07.10 gtt_Internal_pack側はcharなので注意が必要
                        gtt_Internal_pack.Data.In.ucMixAcRatio    = (char)ComuniPack.Data.To.ucMixAcRatio * 5; //2009.07.15                            //MIX(AC)比率
                        break;
                   case 0x2C: //2009.07.10
                        gtt_Internal_pack.Data.In.vIhotAdj_tig    = ComuniPack.Data.To.vIhotAdj_tig;                                  //ホット電流調整（ＴＩＧ系）
                        break;
                   case 0x2D: //2009.07.10
                        gtt_Internal_pack.Data.In.vHotTime_tig    = ComuniPack.Data.To.vHotTime_tig;                                  //ホット時間調整（ＴＩＧ系）
                        break;
                   case 0x2E: //2009.07.10
                        gtt_Internal_pack.Data.In.vHotSlop_tig    = ComuniPack.Data.To.vHotSlop_tig;                                  //ホットスロープ（ＴＩＧ系）
                        break;
                   default:
                        break;
           }
                        //***** 可変パラメータ反映 2009.02.23 2009.07.23 test add *****
#if 0 //2019.03.15 ihara del
                        //_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //ＡＣ周波数の反映 2009.03.27
                        _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //ＡＣ周波数の反映 2009.12.29
                        _union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty; //2009.02.16
                        //_union.Nrm.CalParm[66 - 1].c = gtt_Internal_pack.Data.In.ucMixFreq; //ＭＩＸ周波数反映 2009.03.27
                        _union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10; //ＭＩＸ周波数反映 2009.03.31
                        _union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio; //ＭＩＸ比率反映 2009.03.27
                        //_union.Nrm.CalParm[69 - 1].c = gtt_Internal_pack.Data.In.usPulseFreq; //パルス周波数反映 2009.03.27
                        _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10; //パルス周波数反映 2009.03.31
                        _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty; //パルス幅反映 2009.03.27
#endif
                        guc_Exd_adj1_rewrite_check_flag    = 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       }

       //拡張溶接微調パラメータ一括　2007.5.29追加
       if (guc_Exd_adj2_rewrite_check_flag == 1)    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       {
           //<><><><><> 範囲指定 2009.07.29 <><><><><>
#if 0 //2009.07.30 del
                 //ID 0x01
                 if (ComuniPack.Data.To.Sp_current    >  200)  { ComuniPack.Data.To.Sp_current     =  200; }
                 if (ComuniPack.Data.To.Sp_current    < -200)  { ComuniPack.Data.To.Sp_current     = -200; }
                 //ID 0x02
                 if (ComuniPack.Data.To.Sp_time       >  300)  { ComuniPack.Data.To.Sp_time        =  300; }
                 if (ComuniPack.Data.To.Sp_time       < -300)  { ComuniPack.Data.To.Sp_time        = -300; }
                 //ID 0x03
                 if (ComuniPack.Data.To.Eli           >   50)  { ComuniPack.Data.To.Eli            =   50; }
                 if (ComuniPack.Data.To.Eli           <  -50)  { ComuniPack.Data.To.Eli            =  -50; }

                 //ID 0x04
                 //ID 0x05
                 //ID 0x06
                 //ID 0x07
                 
                 //ID 0x08
                 if (ComuniPack.Data.To.vVhotAdj      >   50)  { ComuniPack.Data.To.vVhotAdj       =   50; }
                 if (ComuniPack.Data.To.vVhotAdj      <  -50)  { ComuniPack.Data.To.vVhotAdj       =  -50; }
                 //ID 0x09
                 if (ComuniPack.Data.To.vFttAdj       >  100)  { ComuniPack.Data.To.vFttAdj        =  100; }
                 if (ComuniPack.Data.To.vFttAdj       < -100)  { ComuniPack.Data.To.vFttAdj        = -100; }
                 //ID 0x0A
                 if (ComuniPack.Data.To.vBarnBackAdj  >  100)  { ComuniPack.Data.To.vBarnBackAdj   =  100; }
                 if (ComuniPack.Data.To.vBarnBackAdj  < -100)  { ComuniPack.Data.To.vBarnBackAdj   = -100; }
                 //ID 0x0B
                 if (ComuniPack.Data.To.vSldnAdj      >   50)  { ComuniPack.Data.To.vSldnAdj       =   50; }
                 if (ComuniPack.Data.To.vSldnAdj      <  -50)  { ComuniPack.Data.To.vSldnAdj       =  -50; }
                 //ID 0x0C
                 if (ComuniPack.Data.To.vIsl1Adj      >  100)  { ComuniPack.Data.To.vIsl1Adj       =  100; }
                 if (ComuniPack.Data.To.vIsl1Adj      < -100)  { ComuniPack.Data.To.vIsl1Adj       = -100; }
                 //ID 0x0D
                 if (ComuniPack.Data.To.vIsl2Adj      >  100)  { ComuniPack.Data.To.vIsl2Adj       =  100; }
                 if (ComuniPack.Data.To.vIsl2Adj      < -100)  { ComuniPack.Data.To.vIsl2Adj       = -100; }
                 //ID 0x0E
                 if (ComuniPack.Data.To.vIacAdj       >  200)  { ComuniPack.Data.To.vIacAdj        =  200; }
                 if (ComuniPack.Data.To.vIacAdj       < -200)  { ComuniPack.Data.To.vIacAdj        = -200; }
                 //ID 0x0F
                 if (ComuniPack.Data.To.vIscAdj       >  200)  { ComuniPack.Data.To.vIscAdj        =  200; }
                 if (ComuniPack.Data.To.vIscAdj       < -200)  { ComuniPack.Data.To.vIscAdj        = -200; }
                 //ID 0x10
                 if (ComuniPack.Data.To.vIpAdj        >  200)  { ComuniPack.Data.To.vIpAdj         =  200; }
                 if (ComuniPack.Data.To.vIpAdj        < -200)  { ComuniPack.Data.To.vIpAdj         = -200; }
                 //ID 0x11
                 if (ComuniPack.Data.To.vIb1Adj       >  200)  { ComuniPack.Data.To.vIb1Adj        =  200; }
                 if (ComuniPack.Data.To.vIb1Ad        < -200)  { ComuniPack.Data.To.vIb1Adj        = -200; }
                 //ID 0x12
                 
#endif

                 //<><><> 2009.07.30 追加 <><><>
                 //ID 0x28     //交流周波数
                 if (ComuniPack.Data.To.usAcFreq       >  400)  { ComuniPack.Data.To.usAcFreq        =  400; }
                 if (ComuniPack.Data.To.usAcFreq       <   30)  { ComuniPack.Data.To.usAcFreq        =   30; }
                 //ID 0x29     //クリーニング幅
                 if (ComuniPack.Data.To.ucCleaningDuty >   90)  { ComuniPack.Data.To.ucCleaningDuty  =   90; }
                 if (ComuniPack.Data.To.ucCleaningDuty <   50)  { ComuniPack.Data.To.ucCleaningDuty  =   50; }
                 //ID 0x2A     //MIX TIG周波数
                 if (ComuniPack.Data.To.ucMixFreq      >  200)  { ComuniPack.Data.To.ucMixFreq       =   200; }
                 if (ComuniPack.Data.To.ucMixFreq      <    1)  { ComuniPack.Data.To.ucMixFreq       =     1; }
                 //ID 0x2B     //MIX(AC)比率
                 if (ComuniPack.Data.To.ucMixAcRatio   >   18)  { ComuniPack.Data.To.ucMixAcRatio    =    18; }
                 if (ComuniPack.Data.To.ucMixAcRatio   <    2)  { ComuniPack.Data.To.ucMixAcRatio    =     2; }
                 //<><><><><><><><><><><><><><><>



                 
           //<><><><><><><><><><><><><><><><><><><><>
           gtt_Internal_pack.Data.In.Sp_current         =  (float)((float)ComuniPack.Data.To.Sp_current     * SP_I);          //ＳＰ電流
           gtt_Internal_pack.Data.In.Sp_time            =  (float)((float)ComuniPack.Data.To.Sp_time        * SP_T);          //ＳＰ時間
           gtt_Internal_pack.Data.In.Eli                =  (float)((float)ComuniPack.Data.To.Eli            * ELI);           //ＥＬＩ
           //gtt_Internal_pack.Data.In.Mts_v              =  (float)((float)ComuniPack.Data.To.Mts_v          * MTS_V);         //重畳電圧値  del 2009.07.14
           //gtt_Internal_pack.Data.In.Mts_ontime         =  (float)((float)ComuniPack.Data.To.Mts_ontime     * MTS_ONTIME);    //重畳電圧ＯＮ時間 del 2009.07.14
           //gtt_Internal_pack.Data.In.Mts_cycle          =  (float)((float)ComuniPack.Data.To.Mts_cycle      * MTS_CYCLE);     //重畳電圧周期 del 2009.07.14
           //<><><> 2009.07.10 追加分 <><><>
           //gtt_Internal_pack.Data.In.Stdc_time          =  ComuniPack.Data.To.Stdc_time                     * STDC_TIME;                          //開始ＤＣ時間 2009.01.26 del 2009.07.17
           gtt_Internal_pack.Data.In.vVhotAdj           =  (float)((float)ComuniPack.Data.To.vVhotAdj       * HOTVLT);         // ホット電圧微調整
           gtt_Internal_pack.Data.In.vFttAdj            =  (short)((float)ComuniPack.Data.To.vFttAdj        * FTTLVL);         // ＦＴＴレベル微調整
           gtt_Internal_pack.Data.In.vBarnBackAdj       =  (short)((short)ComuniPack.Data.To.vBarnBackAdj);                    //2009.07.10 BBKTIM del        // バーンバック時間微調整
           gtt_Internal_pack.Data.In.vSldnAdj           =  (short)((short)ComuniPack.Data.To.vSldnAdj       * WIRSLDN);        // スローダウン速度微調整
           gtt_Internal_pack.Data.In.vIsl1Adj           =  (float)((float)ComuniPack.Data.To.vIsl1Adj);                        //2009.07.10 ISL1 del           // 短絡電流第１勾配微調整
           gtt_Internal_pack.Data.In.vIsl2Adj           =  (float)((float)ComuniPack.Data.To.vIsl2Adj);                        //2009.07.10 ISL2 del           // 短絡電流第２勾配微調整
           gtt_Internal_pack.Data.In.vIacAdj            =  (float)((float)ComuniPack.Data.To.vIacAdj        * IAC);            // アーク再生直後電流微調整
           gtt_Internal_pack.Data.In.vIscAdj            =  (float)((float)ComuniPack.Data.To.vIscAdj);                         //2009.07.10 ISC del            // 短絡電流屈曲点微調整
           gtt_Internal_pack.Data.In.vIpAdj             =  (float)((float)ComuniPack.Data.To.vIpAdj         * PULSE_PEAK_CUR); // パルスピーク電流微調整
           gtt_Internal_pack.Data.In.vIb1Adj            =  (float)((float)ComuniPack.Data.To.vIb1Adj        * PULSE_BASE_CUR); // パルス第１ベース電流微調整
           gtt_Internal_pack.Data.In.vIprAdj            =  (float)((float)ComuniPack.Data.To.vIprAdj        * PRISE);          // パルスピーク立ち上がり微調整
           gtt_Internal_pack.Data.In.vIpfAdj            =  (float)((float)ComuniPack.Data.To.vIpfAdj        * PFALL);          // パルスピーク立ち下がり微調整
           gtt_Internal_pack.Data.In.vIniIpAdj          =  (short)((float)ComuniPack.Data.To.vIniIpAdj      * INIT_IP);        // スタートピーク電流微調整
           gtt_Internal_pack.Data.In.vIniIbAdj          =  (short)((float)ComuniPack.Data.To.vIniIbAdj      * INIT_IB);        // スタートベース電流微調整
           //gtt_Internal_pack.Data.In.vIb2Adj            =  (float)((float)ComuniPack.Data.To.vIb2Adj        * PULSE_BASE_CUR2);// パルス第２ベース電流微調整 del 2009.07.14
           gtt_Internal_pack.Data.In.vTiprAdj           =  (float)((float)ComuniPack.Data.To.vTiprAdj       * PULSE_RISE_CUR); // パルス立ち上がり時間微調整
           gtt_Internal_pack.Data.In.vTipfAdj           =  (float)((float)ComuniPack.Data.To.vTipfAdj       * PULSE_FALL_CUR); // パルス立ち下がり時間微調整
           gtt_Internal_pack.Data.In.vTipAdj            =  (float)((float)ComuniPack.Data.To.vTipAdj        * PULSE_WIDTH);    // パルスピーク立ち上がり時間微調整
           gtt_Internal_pack.Data.In.vTsoAdj            =  (float)((float)ComuniPack.Data.To.vTsoAdj);                         //2009.07.10 PENETRATION del    // 短絡初期時間調整
           //gtt_Internal_pack.Data.In.vIhotAdj           = ComuniPack.Data.To.vIhotAdj                       * HOTCUR;          // ホット電流調整
           gtt_Internal_pack.Data.In.vIhotAdj           = ComuniPack.Data.To.vIhotAdj;          // ホット電流調整 2009.07.28
           gtt_Internal_pack.Data.In.vHotTime           = ComuniPack.Data.To.vHotTime;                                         // ホットタイム
           gtt_Internal_pack.Data.In.vStartPulse        = ComuniPack.Data.To.vStartPulse;                                      // スタートパルス有り無し
           gtt_Internal_pack.Data.In.vEndPulse          = ComuniPack.Data.To.vEndPulse;                                        // エンドパルス有り無し
           gtt_Internal_pack.Data.In.vIniPulseFreqAdj   = ComuniPack.Data.To.vIniPulseFreqAdj;                                 // イニシャルパルス周波数
           gtt_Internal_pack.Data.In.vPctrlBlowAdj      = ComuniPack.Data.To.vPctrlBlowAdj;                                    // アークブロー抑制制御
           gtt_Internal_pack.Data.In.vWirSpdAdj         = ComuniPack.Data.To.vWirSpdAdj;                                       // ワイヤスピード微調整
           //gtt_Internal_pack.Data.In.vWirStrAccAdj      = (float)((float)ComuniPack.Data.To.vWirStrAccAdj   * START_CTRL);      // スタートスロープ微調整 del 2009.07.14
           gtt_Internal_pack.Data.In.vWirStrDelayAdj    = (float)((float)ComuniPack.Data.To.vWirStrDelayAdj * START_TIME);     // ワイヤスタートディレイ微調整
           gtt_Internal_pack.Data.In.vNeckLvlAdj        = ComuniPack.Data.To.vNeckLvlAdj;                                      // ネックレベル微調整 
           //gtt_Internal_pack.Data.In.vWirAcDcAdj        = (float)((float)ComuniPack.Data.To.vWirAcDcAdj     * WIRACDC);        // 加速度３ del 2009.07.14
           gtt_Internal_pack.Data.In.vBbkPulseAdj       = ComuniPack.Data.To.vBbkPulseAdj;                                     // バーンバックパルス
           gtt_Internal_pack.Data.In.usAcFreq           = ComuniPack.Data.To.usAcFreq;                                         //交流周波数
           //gtt_Internal_pack.Data.In.ucCleaningDuty     = ComuniPack.Data.To.ucCleaningDuty;                                   //クリーニング幅
           gtt_Internal_pack.Data.In.ucCleaningDuty     = 100 - ComuniPack.Data.To.ucCleaningDuty;                         //クリーニング幅 2009.07.23 反転処理追加
           gtt_Internal_pack.Data.In.ucMixFreq          = ComuniPack.Data.To.ucMixFreq;                                         //MIX TIG周波数
           gtt_Internal_pack.Data.In.ucMixAcRatio       = (char)ComuniPack.Data.To.ucMixAcRatio * 5;  //2009.07.15                              //MIX(AC)比率
           gtt_Internal_pack.Data.In.vIhotAdj_tig       = ComuniPack.Data.To.vIhotAdj_tig;                                     //ホット電流調整（ＴＩＧ系）
           gtt_Internal_pack.Data.In.vHotTime_tig       = ComuniPack.Data.To.vHotTime_tig;                                     //ホット時間調整（ＴＩＧ系）
           gtt_Internal_pack.Data.In.vHotSlop_tig       = ComuniPack.Data.To.vHotSlop_tig;                                     //ホットスロープ（ＴＩＧ系）
           //<><><><><><><><><><><><><><><><>
                        //***** 可変パラメータ反映 2009.02.23 2009.07.23 test add *****
#if 0 //2019.03.15 ihara del
                        //_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //ＡＣ周波数の反映 2009.03.27
                        _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //ＡＣ周波数の反映 2009.12.29
                        _union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty; //2009.02.16
                        //_union.Nrm.CalParm[66 - 1].c = gtt_Internal_pack.Data.In.ucMixFreq; //ＭＩＸ周波数反映 2009.03.27
                        _union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10; //ＭＩＸ周波数反映 2009.03.31
                        _union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio; //ＭＩＸ比率反映 2009.03.27
                        //_union.Nrm.CalParm[69 - 1].c = gtt_Internal_pack.Data.In.usPulseFreq; //パルス周波数反映 2009.03.27
                        _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10; //パルス周波数反映 2009.03.31
                        _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty; //パルス幅反映 2009.03.27
#endif
                        guc_Exd_adj2_rewrite_check_flag    = 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
       }



       //if (guc_Method_condition_counter == STD_AC_METHOD) //test 2009.07.23
       //{
       //    LED4 = ON;
       //} else {
       //    LED4 = OFF;
      // }


       //２００６．１２．１５　バックＲＡＭテスト
       if (test_flag == OFF)
       {
           test_flag = ON;
           PC_Send_C3( );
       }

       //************* トーチＳＷｏｆｆを一定時間受け取らない　2007.2.24 *************
#if 0 //2009.07.23 del
       if (gtt_Ctrl_flag.Toch_sw_off_delay_time == ON)
       {
           if (gtt_Ctrl_counter.Toch_sw_off_delay_time <= 0)
           {
               gtt_Ctrl_flag.Toch_sw_off_delay_time = OFF;
               //gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = OFF; 2007.3.1削除
               //LED4 = OFF; test 2009.07.23 test del
           } else {
               gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = ON;
               //LED4 = ON; test 2009.07.23 test del
               
           }
        }
#endif
       //*****************************************************************************

       //****************** ＰＣ通信初期化フラグセット 2007.4.2 **********************
       if (gtt_Internal_pack.Data.bRS232Connection == ON && gtt_Ctrl_flag.Rs232_start == OFF)	// ＲＳ２３２ｃ回線接続
       {
           gtt_Ctrl_flag.Rs232_start = ON;
           gtt_Ctrl_flag.Rs232_init = ON;
       }
       //*****************************************************************************
    }

     //************************************* 2007.12.05　リモコン通信用 *********************************
     
     //*** リモコン接続状態でロボット接続がされた場合の処理 2008.10.03 ***
     //if (ComuniPackRemo.Data.bRS422Connection == true && ComuniPack.Data.bRS422Connection == true && guc_Robot_connect_flag == true)
     if (ComuniPackRemo.Data.bRS422Connection == true && ComuniPack.Data.bRS422Connection == true && guc_Robot_connect_flag == true && gub_System_err == OFF) //2010.03.23
     {
	 if (gtt_Ctrl_flag.Robot_connect_time == OFF)
	 {
             gtt_Ctrl_flag.Robot_connect_time = ON;
             //gtt_Ctrl_counter.uc_Robot_connect_time = 100;
             gtt_Ctrl_counter.uc_Robot_connect_time = 400;
         } else if (gtt_Ctrl_counter.uc_Robot_connect_time <= 0) {
		
             ComuniPackRemo.Data.bRS422Connection = false;
             gb_Controller_UnConnect              = false;  // Phase26 by @Tny 2008.10.23
             gtt_Ditail_work.us_DC_control_timer  = 0;      // 2008.11.28 コントローラのスタート直流時間を０にする（ロボット指令に従うため）
             guc_Crater_mode_counter              = SEQUENCE_NON; //2008.11.28 クレータモード選択状態でロボットに接続された場合に備えロボットが接続されるとクレータ無しに切り替える。
             gb_Controller_UnConnect             = true;     // コントローラ未接続確認フラグ：未接続 2009.07.13 
             gb_Ping_to_Controller               = false;    // コントローラ未接続確認実行フラグ     2009.07.13
             gtt_Ctrl_flag.UnConnect_false       =  true;    //2009.07.14
         }
     }
     //*******************************************************************


//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23
	if((ComuniPackRemo.Data.bRS422Connection)&&(guc_Initial_display_flag == false)&&(guc_Sw_rewrite_check_flag == 1)){
		if((gb_ServiceMenu == false)&&(gb_RescueMenu == false)){

#if false
				gb_ServiceMenu							= true;		// サービスマンメニュー要求フラグ
		    	ComuniPackRemo.Data.To.bChangeData		= false;	// 受信データ更新フラグの更新
				guc_Sw_rewrite_check_flag				= 0;		// 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
				gb_JogLock								= true;		// ＪＯＧ決定キー無効化フラグ；有効
	            guc_Select_counter						= MODE_DETAILS;	 //詳細モード
				guc_Menu_Hierarchy						= 0;		// 詳細メニュー設定階層フラグ
               	gsc_Select_dital_counter				= 0;		// 詳細メニュー設定項目フラグ
				gb_2Line_FirstDisplay					= false;	// 初回二行目表示フラグをＯＦＦ	BP4 Phase3 by @Tny 2009.01.15
				InitialStringInput(true, true, "");					// 文字入力処理の初期化
				guc_StringInput							= 1;		// 文字列入力処理実行中
#endif

			if((ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 == true)&&(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 == true)){
				gb_ServiceMenu							= true;		// サービスマンメニュー要求フラグ
		    	ComuniPackRemo.Data.To.bChangeData		= false;	// 受信データ更新フラグの更新
				guc_Sw_rewrite_check_flag				= 0;		// 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
				gb_JogLock								= true;		// ＪＯＧ決定キー無効化フラグ；有効
	            guc_Select_counter						= MODE_DETAILS;	 //詳細モード
				guc_Menu_Hierarchy						= 0;		// 詳細メニュー設定階層フラグ
               	gsc_Select_dital_counter				= 0;		// 詳細メニュー設定項目フラグ
				gb_2Line_FirstDisplay					= false;	// 初回二行目表示フラグをＯＦＦ	BP4 Phase3 by @Tny 2009.01.15
				//InitialStringInput(true, true, "");	//2019.03.15 ihara del				// 文字入力処理の初期化
				guc_StringInput							= 1;		// 文字列入力処理実行中
		        guc_Init_wait_sequence  				= 20000;    // 初期シーケンス待ち時間：2sec	// レスキュー＆サービスマン・モード時はＩＩＦの入力は無効とする  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
				gus_Iif_Detect_Timer					= 10000;	// レスキュー＆サービスマン・モード時はＩＩＦの入力は無効とする  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
			}
			else if(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 == true){
				gb_RescueMenu							= true;		// レスキュー処理要求フラグ
		    	ComuniPackRemo.Data.To.bChangeData		= false;	// 受信データ更新フラグの更新
				guc_Sw_rewrite_check_flag				= 0;		// 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
				gb_JogLock								= true;		// ＪＯＧ決定キー無効化フラグ：有効
				//gb_JogLock								= false;		// ＪＯＧ決定キー無効化フラグ：有効 2009.04.06  by @Tny 2009.04.08
	            guc_Select_counter						= MODE_DETAILS;	 //詳細モード
				guc_Menu_Hierarchy						= 0;		// 詳細メニュー設定階層フラグ
               	//gsc_Select_dital_counter				= 0;		// 詳細メニュー設定項目フラグ：レスキュー・メニューにもパスワード入力	BP4 Phase16 by @Tny 2009.03.10
               	gsc_Select_dital_counter				= 1;		// 詳細メニュー設定項目フラグ：レスキュー・メニューにもパスワード入力 2009.04.06 by @Tny 2009.04.08
				gb_2Line_FirstDisplay					= false;	// 初回二行目表示フラグをＯＦＦ	BP4 Phase3 by @Tny 2009.01.15
				//InitialStringInput(true, true, "");	//2019.03.15 ihara del				// 文字入力処理の初期化
				guc_StringInput							= 1;		// 文字列入力処理実行中
				gus_MessageTimer						= 30;		// メッセージ表示時間（１００ｍ秒単位）：３秒
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
				gb_RescueOpeningDisp 					= true;		// レスキュー・メニューのオープニング画面の表示要求
//--------------------------------------------------------------------
		        guc_Init_wait_sequence  				= 20000;    // 初期シーケンス待ち時間：2sec	// レスキュー＆サービスマン・モード時はＩＩＦの入力は無効とする  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
				gus_Iif_Detect_Timer					= 10000;	// レスキュー＆サービスマン・モード時はＩＩＦの入力は無効とする  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
			}
		}
	}
//--------------------------------------------------------------------


     if(((ComuniPackRemo.Data.bRS422Connection)||(gb_Controller_UnConnect)) && guc_Robot_connect_flag == false)	// コントローラ接続orコントローラ未接続(短絡子有り) 2008.12.19
     {
        //************************* 溶接条件変更部 ***************************
        if (guc_Sw_rewrite_check_flag == 1)
        {


   	        if(gtt_End_welding_display.us_Display_time <= 0) guc_Sw_rewrite_check_flag = 2;
            
                        //<><><> 溶接終了電流表示キャンセル 2009.03.31 <><><>
                        if (gtt_End_welding_display.us_Display_time > 0)
                        {
                            gtt_Ctrl_flag.End_welding_display_cansel = ON;
                        } else {
                            gtt_Ctrl_flag.End_welding_display_cansel = OFF;
                        }
                        //<><><><><><><><><><><><><><><><><><><><><><><><><><>
#if 0
    	    if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && guc_Select_counter == MODE_WELDING && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Fram_Phase == 0) //設定 2008.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20	// BP4 Phase6 by @Tny 2009/01/27
          	{
               if (gtt_Ctrl_flag.Set_screen_on_off == OFF)
               {
                   gtt_Ctrl_flag.Set_screen_on_off = ON;
                   guc_Gas_on_off_flag				= OFF;
               } else {
                   gtt_Ctrl_flag.Set_screen_on_off = OFF;
               }	
            }
#endif
            if (gsc_Select_dital_counter == P_INPUT_PASS_WORD && gss_Select_dital[P_INPUT_PASS_WORD] == guc_Pass_word && guc_Select_counter == MODE_DETAILS) //2008.09.10	// BP4 Phase6 by @Tny 2009/01/27
            {
                gtt_Ctrl_flag.Dital_pass_lock = false;
            }
            if (guc_Select_counter != MODE_DETAILS) //2008.09.10	// BP4 Phase6 by @Tny 2009/01/27
            {
                // gtt_Ctrl_flag.Dital_pass_lock = true;		BP4 Phase3 by @Tny 2009.01.15 試験用
                gtt_Ctrl_flag.Dital_pass_lock = false;
                gss_Select_dital[P_INPUT_PASS_WORD] = 0;
            }

            if (gtt_Ctrl_flag.Set_screen_on_off == ON)
            {
           			if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1 == true && guc_Fram_Phase == 0) //材質ＳＷ→機能切り替えになる。
            		{
                        if (gtt_Ctrl_flag.Service_man == OFF) //技術・サービスマンメニュー分岐 2008.09.03
                        {
                            //0:パラメータ設定
                            //1:リセット
                            //2:インターフェース設定
                            //3:カレンダー設定
                            //4:エラー履歴
                            //5:メモリーコピー
                            //6:突き出し長設定 2008.11.10
                            
                            if(gtt_Ctrl_counter.uc_User_menu_no == 2){
                                uchar   Data[10];
                                // 設定時刻の読み込み（リアルタイムデータ１）
                                I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                                gtt_Calender.uc_Year_data   = ((((Data[0] & 0xf0) >> 4) * 10) + (Data[0] & 0x0f));// 年の書式変更
                                gtt_Calender.uc_Month_data  = ((((Data[1] & 0x10) >> 4) * 10) + (Data[1] & 0x0f));// 月の書式変更
                                gtt_Calender.uc_Day_data    = ((((Data[2] & 0x30) >> 4) * 10) + (Data[2] & 0x0f));// 日の書式変更
                                gtt_Calender.uc_Hour_data   = ((((Data[4] & 0x30) >> 4) * 10) + (Data[4] & 0x0f));// 時の書式変更
                                gtt_Calender.uc_Mint_data   = ((((Data[5] & 0x70) >> 4) * 10) + (Data[5] & 0x0f));// 分の書式変更
                                char_set_class(5,"   ",false,false,false);  // Phase15 by @Tny 2008/09/19
                                char_set_class(6,"   ",false,false,false);  // Phase15 by @Tny 2008/09/19
                            }
                            if(gtt_Ctrl_counter.uc_User_menu_no == 3){
                                gtt_Ctrl_counter.uc_Error_history_no = 1;
                            }
                            if(gtt_Ctrl_counter.uc_User_menu_no == 4){
                                gtt_Ctrl_counter.Memory_copy_area_no = 1;
                                char_set_class(6,"   ",false,false,false);  // Phase8 by @Tny 2008/09/11
                            }




                		    gtt_Ctrl_counter.uc_User_menu_no++;
                		    if (gtt_Ctrl_counter.uc_User_menu_no == USER_MENU_COUNT)
                		    {
                    		    gtt_Ctrl_counter.uc_User_menu_no = 0;
                		    }
                        } else { //技術・サービスマンメニュー 2008.09.03
                            //0:サービスマンデータ入力
                            //1:リセット
                		    gtt_Ctrl_counter.uc_Service_menu_no++;
                		    if (gtt_Ctrl_counter.uc_Service_menu_no == SERVICE_MENU_COUNT)
                		    {
                    		    gtt_Ctrl_counter.uc_Service_menu_no = 0;
                		    }
                        }
                        gtt_Ctrl_flag.Set_key = OFF; //メニューが変わったらセットキーをＯＦＦする。2008.11.20
            		}

                   	if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6 == true) //セットキーの動作
                    {
                        if (gtt_Ctrl_flag.Set_key == OFF)
                        {
                            gtt_Ctrl_flag.Set_key = ON;
                        }	
                    }

                    //**** ＩＩＦ設定関連 ****
           			if((gb_IIF_Select)&&(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No2 == true)){  // IIF接続時のみ対応
                        if (gtt_Ctrl_counter.uc_User_menu_no == 2) //2:インターフェース設定
                        {
                		    gtt_Ctrl_counter.uc_Iif_no++;
                		    if (gtt_Ctrl_counter.uc_Iif_no == 3)
                		    {
                    	        gtt_Ctrl_counter.uc_Iif_no = 0;
                		    }
                        }
            		}

            } else {
                //*** 設定関連の変数のクリア 2008.09.02***
                  //ユーザーメニュー共通
                    gtt_Ctrl_counter.uc_User_menu_no = 0;      //2008.09.03
                  //特殊パラメータ
                    gtt_Ctrl_counter.us_User_parameter_no = 0;
                  //リセット
                    gtt_Ctrl_flag.User_all_parameter_reset = false;
                  //IIF
                    gtt_Ctrl_counter.uc_Iif_no = 0;            //2008.09.03
                    gtt_Ctrl_counter.uc_Out_function_no = 0;
                    gtt_Ctrl_counter.uc_In_function_no = 0;
                    gtt_Ctrl_counter.uc_Analog_function_no = 0;
//
// <IIF NEW> 2009.11.27 @Tny	2011.10.07 by @Tny
#if false
                    gtt_Ctrl_counter.uc_Out_port_no = 1;
                    gtt_Ctrl_counter.uc_In_port_no = 1;
                    gtt_Ctrl_counter.uc_Analog_port_no = 1;
#endif
                    gtt_Ctrl_flag.Out_function_set_ready = OFF;			//2009.10.15 <IIF NEW>
                    gtt_Ctrl_flag.In_function_set_ready  = OFF;			//2009.10.29 <IIF NEW>
                    gtt_Ctrl_flag.In_ab_set_ready            = OFF;		//2009.10.29 <IIF NEW>
                    gtt_Ctrl_flag.Analog_function_set_ready  = OFF;		//2009.10.29 <IIF NEW>
                    gtt_Ctrl_flag.Calibration_set = false;				// <IIF NEW> 2009.11.13
                    gtt_Ctrl_flag.In_function_no_one_shot = OFF;		//2009.11.25 <IIF NEW>
//
//
//
                  //カレンダー
// BP4 Phase4 by @Tny 2009.01.15                    gtt_Ctrl_counter.uc_Calender_no = 0;       //2008.09.03
                   // エラー履歴
                   gtt_Ctrl_counter.uc_Error_history_no = 1;
                  //メモリコピー
                    gtt_Ctrl_counter.Memory_copy_area_no = 1;
                  //サービスマンメニュー共通
                    gtt_Ctrl_counter.uc_Service_menu_no = 0;   //2008.09.03
                  //サービスマンメニュー　データ入力
                    gtt_Ctrl_counter.us_Service_data_no = 0;   //2008.09.03
                  //サービスマンメニュー　リセット
                    gtt_Ctrl_counter.uc_Service_reset_no = 0;  //2008.09.03
                    gtt_Ctrl_flag.Service_reset1 = false;
                    gtt_Ctrl_flag.Service_reset2 = false;
                  //サービスマンパスワード
                    gtt_Ctrl_flag.Service_man = OFF;
                    gtt_Ctrl_flag.Pass_word_err = OFF;
                    gtt_Ctrl_counter.Pass_word_check = 0;
                    gtt_Ctrl_counter.Pass_word_ok = 0;
                    gtt_Special_menu.ss_User_param[PASS_WORD_NO] = 111;

                    //突き出し長において確定キーを押されなかった場合に備えた処理
                    gtt_Ctrl_counter.uc_Ext_condition_data = guc_Ext_condition_counter; //2008.11.10
                    

                //******************************

//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.10
				if(gss_Select_dital[P_CONTROLLER_LOCK] == false){	// コントローラ・ロック中ではない？
//--------------------------------------------------------------------
                //モード設定の選択 2009.01.10
               	//if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
               	//if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0 && guc_Method_condition_data != STD_HAND_METHOD && guc_Method_condition_data != NAVI_METHOD) //2009.03.17 溶接ナビ時と直流手溶接時は選択ボタンが利かない処理

                //リモコン再生モード時は動作しない 2009.03.30
               	//if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0 && guc_Method_condition_data != STD_HAND_METHOD && guc_Method_condition_data != NAVI_METHOD) //2009.03.17 溶接ナビ時と直流手溶接時は選択ボタンが利かない処理
               	if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17 == true && (guc_Sequence_mode == IDLING) && guc_Fram_Phase == 0 && guc_Method_condition_data != STD_HAND_METHOD && guc_Method_condition_data != NAVI_METHOD) //2009.03.17 溶接ナビ時と直流手溶接時は選択ボタンが利かない処理 2009.12.25
                {
//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.22
					if(guc_Select_counter != MODE_DETAILS){	// 現在は詳細モードではない？	BP4 Phase6 by @Tny 2009/01/27
                    	guc_Select_counter++;
						guc_Menu_Hierarchy			= 0;	// 詳細メニュー設定階層フラグ
	                	gsc_Select_dital_counter	= 0;	// 詳細メニュー設定項目フラグ

//-------------------------------------------------------------------------------
// 現モードが記憶モードでCHメモリ記憶ロックがＯＮなら次モード（詳細モード）へ移行する　BP4 by @Tny 2009.04.08
						if((guc_Select_counter == MODE_RECORD)&&(gtt_Special_menu.ss_Rescue_data[R_REC_LOCK] != 0)){
							guc_Select_counter++;
						}
//-------------------------------------------------------------------------------

					}
					else if(gsc_Select_dital_counter == P_WELD_NAME){	// 溶接条件名の入力／編集モード？
						if(guc_Menu_Hierarchy == 0){	// メニュー項目が第０階層？
	                    	guc_Select_counter++;
							guc_Menu_Hierarchy			= 0;	// 詳細メニュー設定階層フラグ
	    		            gsc_Select_dital_counter	= 0;	// 詳細メニュー設定項目フラグ
						}
						else if(guc_Menu_Hierarchy == 1){	// メニュー項目が第１階層未満？
							guc_Menu_Hierarchy			= 0;	// 詳細メニュー設定階層フラグ
//	    		            gsc_Select_dital_counter	= 0;	// 詳細メニュー設定項目フラグ
						}
						else{
							StringInput_Rcv(true, true, gt_SelectCharacter, 16);	// 文字入力処理（入力部）
							if(guc_StringInput == 2){ // 文字入力処理が終了した？
								// BP4 Phase5 by @Tny 要ＦＲＡＭエリアへの記憶処理
								strcpy((char *)gt_WeldCondName[gss_Select_dital[gsc_Select_dital_counter]], (const char *)gt_SelectCharacter);		// 条件名文字列データ格納エリアへ入力文字列をコピー
								gb_WeldCondNameWrite	= true;	// 溶接条件名書き込み要求フラグ	// BP4 Phase6 by @Tny 2009/01/27
								guc_Menu_Hierarchy		= 1;	// 詳細メニュー設定階層フラグ
							}
						}
					}
					else{
                    	guc_Select_counter++;
						guc_Menu_Hierarchy			= 0;	// 詳細メニュー設定階層フラグ
	                	gsc_Select_dital_counter	= 0;	// 詳細メニュー設定項目フラグ
                        if (gtt_Special_menu.ss_Rescue_data[2] == 1) //2009.04.06
                        {
                    	    if (guc_Select_counter == 2) guc_Select_counter = 3;
                        }
					}

                    //<><><> 2010.01.19 ＣＨ再生もあるのでここで出力制限を掛ける<><><>
                        //初期
                   	    if (gtt_Internal_pack.Data.In.usWeldingInitCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  	    {
       		    			gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
       					}
       					if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
       					}
                        //本溶接
                   	    if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
       					}
       					if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
       					}
                        //クレータ
                   	    if (gtt_Internal_pack.Data.In.usWeldingCratCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	    {
       		    			gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
       					}
       					if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                   	    {
       		    			gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
       					}
                        //パルス電流
                       	if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
                       	{
        		    		gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        				}
        				if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                       	{
        		    		gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        				}
                    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

                    if (guc_Select_counter > MODE_MAX)	// BP4 Phase6 by @Tny 2009/01/27
                    {
                  		guc_Select_counter = 0;
                    }
					gb_2Line_FirstDisplay				= false;// 初回二行目表示フラグをＯＦＦ	BP4 Phase3 by @Tny 2009.01.15
					gss_Select_dital[P_NOW_DATE_TIME]	= 0;	// 現在日時設定インデックス		BP4 Phase4 by @Tny 2009.01.15
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.22
					if(guc_Select_counter != MODE_DETAILS){	// 現在は詳細モードではない？	BP4 Phase6 by @Tny 2009/01/27
						guc_StringInput	= 0;					// 文字列入力処理実行中ではない
					}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// BP4 Phase7 by @Tny 2009.02.12
//					if((guc_Select_counter == MODE_WELDING)||(guc_Select_counter == MODE_DETAILS)){
//						if(guc_Select_counter == MODE_WELDING)		guc_Select_counter = MODE_DETAILS;
//						else if(guc_Select_counter == MODE_DETAILS)	guc_Select_counter = MODE_PLAY;
//						if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){
//							if(guc_Select_counter == MODE_DETAILS)		guc_Select_counter = MODE_PLAY;
//							else if(guc_Select_counter == MODE_PLAY)	guc_Select_counter = MODE_RECORD;
//						}
						gtt_Ctrl_flag.Play = ON;
						guc_Ch_no = 0;
						guc_Ch_no_bkup = 0;

                        //<><><> 記憶確定する前に記憶モードを抜けてしまった時の対応 2009.07.29 <><><>
                        gtt_Ctrl_flag.Rec_display = OFF;
                        gtt_Ctrl_flag.Yes = OFF;
                        gtt_Ctrl_flag.Rec = OFF;
                        gtt_Ctrl_flag.Del = OFF;
                        //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//					}
//-----------------------------------------------------------------------------

                }
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.10
				}
//--------------------------------------------------------------------
                //ＪＯＧ決定キー入力 2009.01.16変更（通常のＪＯＧ決定とナビのＪＯＧ決定を分離）
//--------------------------------------------------------------------
// BP4 Phase15 by @Tny 2009.02.25
//                if (guc_Method_condition_counter != 4)
				if((guc_Method_condition_counter != 4)||(gb_ServiceMenu)||(gb_RescueMenu))
//--------------------------------------------------------------------
                {
               	    if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                    {
//--------------------------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23		BP4 Phase14 by @Tny 2009.02.24
						if((gb_ServiceMenu)||(gb_RescueMenu)){
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.12
						if(gus_MessageTimer <= 0){	// メッセージ表示時間が経過?
//--------------------------------------------------------------------
							gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
							if(gsc_Select_dital_counter == 0){
								// パスワード入力処理
								//StringInput_Rcv(false, true, gt_SelectCharacter, 16);	// 文字入力処理（入力部）
								if (gb_ServiceMenu) StringInput_Rcv(false, true, gt_SelectCharacter, 16);	// 文字入力処理（入力部）2009.04.06
                                if (gb_RescueMenu) guc_StringInput = 2; //2009.04.06
								if(guc_StringInput == 2){ // 文字入力処理が終了した？
									gt_SelectCharacter[gus_InputCharIndex] = 0x00;	// NULLコードセット
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
									gb_RescueOpeningDisp = false;		// レスキュー・メニューのオープニング画面の表示要求：クリア
//--------------------------------------------------------------------
									//if(strcomp((unsigned char *)gt_SelectCharacter, (unsigned char *)"610854")){// 入力パスワードの確認：固定値「６１０８５４」
									if(strcomp((unsigned char *)gt_SelectCharacter, (unsigned char *)"610854") || gb_RescueMenu){// 入力パスワードの確認
										gsc_Select_dital_counter 	= 1;	// 詳細メニュー設定階層フラグ
										//gus_MessageTimer			= 30;	// メッセージ表示時間（１００ｍ秒単位）：３秒
										gus_MessageTimer			=  5;	// メッセージ表示時間（１００ｍ秒単位）：３秒 2009.04.06
									}
									else{
										InitialStringInput(true, true, "");	// 文字入力処理の初期化
										guc_StringInput	= 1;				// 文字列入力処理実行中
										gus_MessageTimer			= 30;	// メッセージ表示時間（１００ｍ秒単位）：３秒
									}
								}
							}
							else{
								if((gb_RescueMenu)&&(gb_RamAllClear == false)){	// レスキュー・メニュー（オールクリア直後ではない？）
									if(gsc_Select_dital_counter == 2){	// エラー履歴のクリア　→　ＣＨメモリ記憶ロック
#if 0 //2009.04.06 del
										if(gtt_Special_menu.ss_Rescue_data[2] == 1){ // エラー履歴のクリア実行？
											gtt_Error_History.History_rec_index = 0;                    // 記録インデックスの初期化
											gtt_Error_History.Full_history_rec  = false;                // 全記録エリア使用フラグの初期化
											gtt_Error_History.Start_record      = false;                // 記録開始フラグの初期化
											gtt_Error_History.Record_identifier = ERROR_INFO_RENEWAL;   // 記録識別子のセット
											gb_Error_History_Write              = true;                 // エラー履歴テーブル保存の要求
											gtt_Special_menu.ss_Rescue_data[2]	= 0;
											gus_MessageTimer					= 30;					// メッセージ表示時間（１００ｍ秒単位）：３秒
										}
#endif
//-------------------------------------------------------------
										if(guc_Menu_Hierarchy != 0){
											gus_MessageTimer	= 30;					// メッセージ表示時間（１００ｍ秒単位）：３秒
										}
//-------------------------------------------------------------
									}
									else if(gsc_Select_dital_counter == 3){	// メモリのクリア
										if(gtt_Special_menu.ss_Rescue_data[3] == 1){ // オールクリアの実行？
									        gtt_Ctrl_flag.Service_reset2_exe	= ON;	// オールクリアの実行
									        guc_Initial_load_data				= 0;	// メモリ記憶識別子のクリア
											gtt_Special_menu.ss_Rescue_data[3]	= 0;
											gb_RamAllClear						= true;	// オールクリア実行フラグ
										}
									}
								}
								else if(gb_ServiceMenu){	// サービスマン・メニュー
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2003.03.10
#if false
									if(guc_Menu_Hierarchy == 0){ // 第１階層→第２階層
										if(gsc_Select_dital_counter == S_PRI_FLOW_TIME){ // プリフロー
											gtt_Special_menu.ss_Service_data[S_PRI_FLOW_TIME] = gtt_Internal_pack.Data.In.sPreFlowTime;
										}
										else if(gsc_Select_dital_counter == S_AFTER_FLOW_TIME){ // アフターフロー
											gtt_Special_menu.ss_Service_data[S_AFTER_FLOW_TIME] = gtt_Internal_pack.Data.In.sAfterFlowTime;
										}
									}
									else{ // 第２階層→第１階層
										if(gsc_Select_dital_counter == S_PRI_FLOW_TIME){ // プリフロー
											gtt_Internal_pack.Data.In.sPreFlowTime = gtt_Special_menu.ss_Service_data[S_PRI_FLOW_TIME];
										}
										else if(gsc_Select_dital_counter == S_AFTER_FLOW_TIME){ // アフターフロー
											gtt_Internal_pack.Data.In.sAfterFlowTime = gtt_Special_menu.ss_Service_data[S_AFTER_FLOW_TIME];
										}
									}
#endif
//--------------------------------------------------------------------
//--------------------------------------------------------------------
// BP4 by @Tny 2009.04.08
#if true
									if(gsc_Select_dital_counter == S_ERROR_HIS_CLEAR){	// エラー履歴のクリア
										if(gtt_Special_menu.ss_Service_data[S_ERROR_HIS_CLEAR] == 1){ // エラー履歴のクリア実行？
											gtt_Error_History.History_rec_index 				= 0;                    // 記録インデックスの初期化
											gtt_Error_History.Full_history_rec  				= false;                // 全記録エリア使用フラグの初期化
											gtt_Error_History.Start_record      				= false;                // 記録開始フラグの初期化
											gtt_Error_History.Record_identifier 				= ERROR_INFO_RENEWAL;   // 記録識別子のセット
											gb_Error_History_Write              				= true;                 // エラー履歴テーブル保存の要求
											gtt_Special_menu.ss_Service_data[S_ERROR_HIS_CLEAR]	= 0;
											gus_MessageTimer									= 30;					// メッセージ表示時間（１００ｍ秒単位）：３秒
										}
									}
#endif
//--------------------------------------------------------------------
								}
								// メニュー階層の更新
								if(++guc_Menu_Hierarchy > 1){
									guc_Menu_Hierarchy = 0;
								}
							}
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
						}
//--------------------------------------------------------------------
						}
						else{
//--------------------------------------------------------------------
                        guc_Jog_set_key = true;
						// 詳細メニュー設定階層フラグ	BP4 Phase4 by @Tny 2009.01.15
	                    if(guc_Select_counter == MODE_DETAILS){	//詳細　Ｐ表示	BP4 Phase6 by @Tny 2009/01/27
//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.21
#if true
							if(gsc_Select_dital_counter == P_NOW_DATE_TIME){	// 現在時刻の設定？
								if(++guc_Menu_Hierarchy > 2){
		                            gtt_Ctrl_flag.Set_key	= ON;
									guc_Menu_Hierarchy		= 1;
									gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
			                        gtt_Calender.uc_Year_data	= gtt_Ctrl_counter.uc_Year_set_data;
			                        gtt_Calender.uc_Month_data	= gtt_Ctrl_counter.uc_Month_set_data;
			                        gtt_Calender.uc_Day_data	= gtt_Ctrl_counter.uc_Day_set_data;
			                        gtt_Calender.uc_Hour_data	= gtt_Ctrl_counter.uc_Hour_set_data;
			                        gtt_Calender.uc_Mint_data	= gtt_Ctrl_counter.uc_Mint_set_data;
								}
								else if(guc_Menu_Hierarchy >= 1){
									if(gss_Select_dital[P_NOW_DATE_TIME] == 5){	// "EXIT"を選択？
										guc_Menu_Hierarchy					= 0;	// 詳細メニュー設定階層フラグ
										gss_Select_dital[P_NOW_DATE_TIME]	= 0;	// 現在日時設定インデックス
									}
									else{
										uchar   Data[10];
									    // 設定時刻の読み込み（リアルタイムデータ１）
									    I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
									    gtt_Calender.uc_Year_data   = ((((Data[0] & 0xf0) >> 4) * 10) + (Data[0] & 0x0f));// 年の書式変更
									    gtt_Calender.uc_Month_data  = ((((Data[1] & 0x10) >> 4) * 10) + (Data[1] & 0x0f));// 月の書式変更
									    gtt_Calender.uc_Day_data    = ((((Data[2] & 0x30) >> 4) * 10) + (Data[2] & 0x0f));// 日の書式変更
									    gtt_Calender.uc_Hour_data   = ((((Data[4] & 0x30) >> 4) * 10) + (Data[4] & 0x0f));// 時の書式変更
									    gtt_Calender.uc_Mint_data   = ((((Data[5] & 0x70) >> 4) * 10) + (Data[5] & 0x0f));// 分の書式変更
									    gtt_Calender.uc_Sec_data    = ((((Data[6] & 0x70) >> 4) * 10) + (Data[6] & 0x0f));// 秒の書式変更
	                                	gtt_Ctrl_counter.uc_Year_set_data  = gtt_Calender.uc_Year_data;
	                                	gtt_Ctrl_counter.uc_Month_set_data = gtt_Calender.uc_Month_data;
	                                	gtt_Ctrl_counter.uc_Day_set_data   = gtt_Calender.uc_Day_data;
	                                	gtt_Ctrl_counter.uc_Hour_set_data  = gtt_Calender.uc_Hour_data;
	                                	gtt_Ctrl_counter.uc_Mint_set_data  = gtt_Calender.uc_Mint_data;
										gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
									}
								}
							}
	                        else if(gsc_Select_dital_counter == P_WELD_NAME){	// 溶接条件名の入力／編集モード？	Phase5 by @Tny 2009.01.22
								gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
								if(guc_Menu_Hierarchy == 0){	// メニュー項目が第１階層？
									unsigned char	i;
									ubool			Proc = false;

									// 記憶条件データの有無の確認
									for(i=1;i<CH;i++){	// 1-16
										if(guc_Write_check_flag_ch[i] == true){
											Proc = true;
											break;
										}
									}
									if(Proc){	// 記憶条件がある？
										++guc_Menu_Hierarchy;
										gss_Select_dital[gsc_Select_dital_counter] = i;					// 記憶条件データの番号を確定
										gb_RecWeldCond	= true;											// 記憶条件データの有無：有り
										// BP4 Phase5 by @Tny 要ＦＲＡＭエリアからの読み込み処理
										InitialStringInput(false, false, (const char *)gt_WeldCondName[i]);	// 文字入力処理の初期化	BP4 Phase13 by @Tny 2009.02.23
										guc_StringInput	= 1;											// 文字列入力処理実行中
									}
									else{
										gb_RecWeldCond	= false;	// 記憶条件データの有無：無し
									}
								}
								else if(guc_Menu_Hierarchy == 1){	// メニュー項目が第２階層？
									++guc_Menu_Hierarchy;
								}
								else{
									StringInput_Rcv(false, true, gt_SelectCharacter, 16);	// 文字入力処理（入力部）
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
									gb_RescueOpeningDisp = false;		// レスキュー・メニューのオープニング画面の表示要求：クリア
//--------------------------------------------------------------------
									if(guc_StringInput == 2){ // 文字入力処理が終了した？
										// BP4 Phase5 by @Tny 要ＦＲＡＭエリアへの記憶処理
										strcpy((char *)gt_WeldCondName[gss_Select_dital[gsc_Select_dital_counter]], (const char *)gt_SelectCharacter);		// 条件名文字列データ格納エリアへ入力文字列をコピー
										gb_WeldCondNameWrite	= true;	// 溶接条件名書き込み要求フラグ	// BP4 Phase6 by @Tny 2009/01/27
										guc_Menu_Hierarchy		= 1;	// 詳細メニュー設定階層フラグ
									}
								}
							}
//--------------------------------
// < IIF NEW > 2009.11.18 @Tny
	                        else if(gsc_Select_dital_counter == P_IIF_SELECT){	// ＩＩＦ設定モード？
								gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
								if(guc_Menu_Hierarchy < 5){ // 第５階層未満？
									++guc_Menu_Hierarchy;
									if(guc_Menu_Hierarchy == 1){	// 第１階層（ＩＩＦ各設定項目選択へ）？
					                	gss_Select_dital[P_IIF_SELECT]	= 0;
										gus_Iif_Set_Menu				= 0;		// ＩＩＦ設定項目内番号の初期化
										gus_Iif_Set_Dital				= 0;		// ＩＩＦ設定項目内種類の初期化
										gus_Iif_PortContact				= 0;		// ＩＩＦ設定項目内接点の初期化
										gb_Iif_ChangeSetting			= false;	// ＩＩＦ設定項目内変更確認フラグの初期化
										gb_Iif_AnalogCalibration		= false;	// ＩＩＦ設定アナログ入力ポートのシフト量校正処理判定フラグの初期化
										//--------------------------------------------------
										// <<<EXTERNAL IIF NEW>>>	入力設定固定	2011.10.07 by @Tny
					                	gss_Select_dital[P_IIF_SELECT]	= 1;
										++guc_Menu_Hierarchy;
										//--------------------------------------------------
										// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
										gb_Iif_AnalogCalibration			= false;	// ＩＩＦ設定アナログ入力ポートのシフト量校正処理判定フラグの初期化
										gtt_Ctrl_counter.uc_Out_port_no		= 1;		// 出力ポート番号
										gtt_Ctrl_counter.uc_In_port_no		= 1;		// 入力ポート番号
										gtt_Ctrl_counter.uc_Analog_port_no	= 1;		// アナログ入力ポート番号
										//-------------------------------------------------
									}
									else if(guc_Menu_Hierarchy == 2){	// 第２階層（設定確定後、ＩＩＦ設定ポート設定へ）？
										if(gss_Select_dital[P_IIF_SELECT] == 5){	// 設定項目選択終了コード（「モドル」）？
											guc_Menu_Hierarchy = 0;
											if(gb_Iif_ChangeSetting){ // ＩＩＦ設定項目内変更：有り
												//
												// 旧設定復帰処理
												//
												IIF_RestoresSetting();
											}
										}
										gb_Iif_AnalogCalibration			= false;	// ＩＩＦ設定アナログ入力ポートのシフト量校正処理判定フラグの初期化
										gtt_Ctrl_counter.uc_Out_port_no		= 1;		// 出力ポート番号
										gtt_Ctrl_counter.uc_In_port_no		= 1;		// 入力ポート番号
										gtt_Ctrl_counter.uc_Analog_port_no	= 1;		// アナログ入力ポート番号
									}
									else if(guc_Menu_Hierarchy == 3){	// 第３階層（設定確定後、ＩＩＦ設定ポート機能設定へ）？
										switch(gss_Select_dital[P_IIF_SELECT]){
											case 0: // デジタル出力設定
											case 1: // デジタル入力設定
											case 2: // アナログ入力設定
													{
														short pss_Exit;
														switch(gss_Select_dital[P_IIF_SELECT]){
															case 0:{pss_Exit = 9;  break;} // ＩＩＦ設定ポート設定終了コード：９
															case 1:{pss_Exit = 10; break;} // ＩＩＦ設定ポート設定終了コード：１０	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
															case 2:{pss_Exit = 4;  break;} // ＩＩＦ設定ポート設定終了コード：４
														}
														if(gus_Iif_Set_Menu >= pss_Exit){	// 終了コード（「モドル」）？
															guc_Menu_Hierarchy	= 1;	// 第１階層（ＩＩＦ各設定項目選択）へ
															gus_Iif_Set_Menu	= 0;	// ＩＩＦ設定項目内番号の初期化
															gus_Iif_Set_Dital	= 0;	// ＩＩＦ設定項目内種類の初期化
															gus_Iif_PortContact	= 0;	// ＩＩＦ設定項目内接点の初期化
															//--------------------------------------------------
															// <<<EXTERNAL IIF NEW>>>	入力設定固定	2011.10.07 by @Tny
															guc_Menu_Hierarchy = 0;
															if(gb_Iif_ChangeSetting){ // ＩＩＦ設定項目内変更：有り
																//
																// 旧設定復帰処理
																//
																IIF_RestoresSetting();
															}
															gb_Iif_AnalogCalibration			= false;	// ＩＩＦ設定アナログ入力ポートのシフト量校正処理判定フラグの初期化
															gtt_Ctrl_counter.uc_Out_port_no		= 1;		// 出力ポート番号
															gtt_Ctrl_counter.uc_In_port_no		= 1;		// 入力ポート番号
															gtt_Ctrl_counter.uc_Analog_port_no	= 1;		// アナログ入力ポート番号
															//--------------------------------------------------
														}
														else{
															switch(gss_Select_dital[P_IIF_SELECT]){
																case 0:{gus_Iif_Set_Dital = guc_Out_port[0][gtt_Ctrl_counter.uc_Out_port_no];		break;} // デジタル出力設定
																case 1:{gus_Iif_Set_Dital = guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no];			break;} // デジタル入力設定
																case 2:{gus_Iif_Set_Dital = guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no];	break;} // アナログ入力設定
															}
														}
													break;}
											case 3: {// 設定確定確認
														if((gb_Iif_ChangeSetting)&&(gus_Iif_Set_Menu == 0)){ // ＩＩＦ設定項目内変更：有り　＆　変更反映？
															//
															// 変更反映処理
															//
										              		gtt_Ctrl_flag.Param_change = ON; // 設定内容保存
															gb_Iif_Reboot	= true;
														}
														else{
															//
															// 旧設定復帰処理
															//
															IIF_RestoresSetting();
															guc_Menu_Hierarchy		= 1;		// 第１階層（ＩＩＦ各設定項目選択）へ
															gus_Iif_Set_Menu		= 0;		// ＩＩＦ設定項目内番号の初期化
															gus_Iif_Set_Dital		= 0;		// ＩＩＦ設定項目内種類の初期化
															gus_Iif_PortContact		= 0;		// ＩＩＦ設定項目内接点の初期化
															gb_Iif_ChangeSetting	= false;	// ＩＩＦ設定項目内変更確認フラグの初期化
														}
													break;}
											case 4: {// アナログ入力ポートのシフト量校正処理
														//
														// シフト量校正処理判定
														//
														if((InternalPackIif.Data.To.us_Analog_data[1] <= 15) && (InternalPackIif.Data.To.us_Analog_data[2] <= 15) && (InternalPackIif.Data.To.us_Analog_data[3] <= 15)){
															//
															// アナログ入力ポートのシフト量校正
															//
															gss_Iif_analog_shift[1] = InternalPackIif.Data.To.us_Analog_data[1];
															gss_Iif_analog_shift[2] = InternalPackIif.Data.To.us_Analog_data[2];
															gss_Iif_analog_shift[3] = InternalPackIif.Data.To.us_Analog_data[3];
															gb_Iif_AnalogCalibration = false; // 校正：ＯＫ
														}
														else{
															gss_Iif_analog_shift[1] = 0;
															gss_Iif_analog_shift[2] = 0;
															gss_Iif_analog_shift[3] = 0;
															gb_Iif_AnalogCalibration = true; // 校正：ＮＧ
														}
														gtt_Ctrl_flag.Iif_analog_shift_memory = true; // アナログ入力ポートのシフト量の保存
													break;}
										}
									}
									else if(guc_Menu_Hierarchy == 4){ // 第４階層（設定確定後、ＩＩＦデジタル入力接点選択へ）？
										switch(gss_Select_dital[P_IIF_SELECT]){
											case 0: {// デジタル出力設定
														guc_Out_port[0][gtt_Ctrl_counter.uc_Out_port_no] = gus_Iif_Set_Dital;
														//
														// ＩＩＦ設定変更確認処理を実行
														//
														gb_Iif_ChangeSetting = IIF_ChangeSetting();	// ＩＩＦ設定変更確認処理を実行
														if(gb_Iif_ChangeSetting){ // ＩＩＦ設定項目内変更：有り？	//	<<<EXTERNAL IIF NEW>>>	2011.10.07 by @Tny
															gb_Iif_ChangeSetting = false;
															//
															// 変更反映処理
															//
										              		gtt_Ctrl_flag.Param_change = ON; // 設定内容保存
															gb_Iif_Reboot	= true;
														}
														//
														guc_Menu_Hierarchy	= 2;	// 第２階層（ＩＩＦ設定ポート設定）へ
														//gus_Iif_Set_Menu	= 0;	// ＩＩＦ設定項目内番号の初期化
														gus_Iif_Set_Dital	= 0;	// ＩＩＦ設定項目内種類の初期化
														gus_Iif_PortContact	= 0;	// ＩＩＦ設定項目内接点の初期化
													break;}
											case 1: {// デジタル入力設定
														guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no] = gus_Iif_Set_Dital;
														//
														// ＩＩＦ設定変更確認処理を実行
														//
														gb_Iif_ChangeSetting = IIF_ChangeSetting();	// ＩＩＦ設定変更確認処理を実行
														if(gb_Iif_ChangeSetting){ // ＩＩＦ設定項目内変更：有り？	//	<<<EXTERNAL IIF NEW>>>	2011.10.07 by @Tny
															gb_Iif_ChangeSetting = false;
															//
															// 変更反映処理
															//
										              		gtt_Ctrl_flag.Param_change = ON; // 設定内容保存
															gb_Iif_Reboot	= true;
														}
#if true	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
														switch(guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no]){
															case IIF_INPUT_NO_USE:		// 未使用
															case IIF_INPUT_TSW:			// トーチＳＷ
															case IIF_INPUT_GAS_CK:		// ガスチェック
															case IIF_INPUT_STKSET:		// スティックチェック
															case IIF_INPUT_BIN1:		// 再生ｃｈバイナリ１
															case IIF_INPUT_BIN2:		// 再生ｃｈバイナリ２
															case IIF_INPUT_BIN3:		// 再生ｃｈバイナリ３
															case IIF_INPUT_BIN4:		// 再生ｃｈバイナリ４
															case IIF_INPUT_BIN5:		// 再生ｃｈバイナリ５
															case IIF_INPUT_BIN6:		// 再生ｃｈバイナリ６
															case IIF_INPUT_BIN7:		// 再生ｃｈバイナリ７
															case IIF_INPUT_CNT:			// 入力許可信号
															case IIF_INPUT_STB:			// ストローブ信号
															case IIF_INPUT_GP_IN1:		// 汎用入力１
															case IIF_INPUT_GP_IN2:		// 汎用入力２
															case IIF_INPUT_GP_IN3:		// 汎用入力３
															case IIF_INPUT_WIR_CK:		// インチング
															case IIF_INPUT_RETRCT:		// リトラクト
															case IIF_INPUT_OKCVON:		// 一元／個別
																	guc_In_port[1][gtt_Ctrl_counter.uc_In_port_no] = 0;		// 入力接点設定の初期化：Ａ接点
																	break;
															case IIF_INPUT_EM_STP:		// 非常停止
															case IIF_INPUT_STOP1:		// 一時停止１
															case IIF_INPUT_STOP2:		// 一時停止２
																	guc_In_port[1][gtt_Ctrl_counter.uc_In_port_no] = 1;		// 入力接点設定の初期化：Ｂ接点
																	break;
														}
														guc_Menu_Hierarchy	= 2;	// 第２階層（ＩＩＦ設定ポート設定）へ
														//gus_Iif_Set_Menu	= 0;	// ＩＩＦ設定項目内番号の初期化
														gus_Iif_Set_Dital	= 0;	// ＩＩＦ設定項目内種類の初期化
														gus_Iif_PortContact	= 0;	// ＩＩＦ設定項目内接点の初期化
#else
														if(guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no] == 0){ // 設定が「NO USE」？
															guc_In_port[1][gtt_Ctrl_counter.uc_In_port_no] = 0;		// 入力接点設定の初期化：Ａ接点
															guc_Menu_Hierarchy	= 2;	// 第２階層（ＩＩＦ設定ポート設定）へ
															//gus_Iif_Set_Menu	= 0;	// ＩＩＦ設定項目内番号の初期化
															gus_Iif_Set_Dital	= 0;	// ＩＩＦ設定項目内種類の初期化
															gus_Iif_PortContact	= 0;	// ＩＩＦ設定項目内接点の初期化
														}
#endif
													break;}
											case 2: {// アナログ入力設定
														guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] = gus_Iif_Set_Dital;
														//
														// ＩＩＦ設定変更確認処理を実行
														//
														gb_Iif_ChangeSetting = IIF_ChangeSetting();	// ＩＩＦ設定変更確認処理を実行
														if(gb_Iif_ChangeSetting){ // ＩＩＦ設定項目内変更：有り？	//	<<<EXTERNAL IIF NEW>>>	2011.10.07 by @Tny
															gb_Iif_ChangeSetting = false;
															//
															// 変更反映処理
															//
										              		gtt_Ctrl_flag.Param_change = ON; // 設定内容保存
															gb_Iif_Reboot	= true;
														}
														//
														guc_Menu_Hierarchy	= 2;	// 第２階層（ＩＩＦ設定ポート設定）へ
														//gus_Iif_Set_Menu	= 0;	// ＩＩＦ設定項目内番号の初期化
														gus_Iif_Set_Dital	= 0;	// ＩＩＦ設定項目内種類の初期化
														gus_Iif_PortContact	= 0;	// ＩＩＦ設定項目内接点の初期化
													break;}
											case 3: {// 設定確定確認
													break;}
											case 4: {// アナログ入力ポートのシフト量校正処理
														guc_Menu_Hierarchy	= 1;	// 第１階層（ＩＩＦ各設定項目選択）へ
														gus_Iif_Set_Menu	= 0;	// ＩＩＦ設定項目内番号の初期化
														gus_Iif_Set_Dital	= 0;	// ＩＩＦ設定項目内種類の初期化
														gus_Iif_PortContact	= 0;	// ＩＩＦ設定項目内接点の初期化
													break;}
										}
									}
									else if(guc_Menu_Hierarchy == 5){ // 第５階層（ＩＩＦデジタル入力接点選択確定）？
										//
										// 入力接点の確定
										//
										guc_In_port[1][gtt_Ctrl_counter.uc_In_port_no] = gus_Iif_PortContact;
										//
										// ＩＩＦ設定変更確認処理を実行
										//
										gb_Iif_ChangeSetting = IIF_ChangeSetting();
										if(gb_Iif_ChangeSetting){ // ＩＩＦ設定項目内変更：有り？	//	<<<EXTERNAL IIF NEW>>>	2011.10.07 by @Tny
											gb_Iif_ChangeSetting = false;
											//
											// 変更反映処理
											//
											gtt_Ctrl_flag.Param_change = ON; // 設定内容保存
											gb_Iif_Reboot	= true;
										}
										//
										guc_Menu_Hierarchy	= 2;	// 第１階層（ＩＩＦ各設定項目選択）へ
										//gus_Iif_Set_Menu	= 0;	// ＩＩＦ設定項目内番号の初期化
										gus_Iif_Set_Dital	= 0;	// ＩＩＦ設定項目内種類の初期化
										gus_Iif_PortContact	= 0;	// ＩＩＦ設定項目内接点の初期化
									}
								}
							}
// < IIF NEW > 2009.11.18 @Tny
//--------------------------------
							else{
								if(++guc_Menu_Hierarchy > 1){
									guc_Menu_Hierarchy = 0;

                                    if (gsc_Select_dital_counter == P_MAX_OUTPUT)
                                    {
                        	        	//初期
                   	    	        	if (gtt_Internal_pack.Data.In.usWeldingInitCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  	    				{
       		    							gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
       									}
       									if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                   	    				{
      		    							gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
       									}
                        				//本溶接
                   	    				if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	    				{
      		    							gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
       									}
       									if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                   	    				{
      		    							gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
       									}
                        				//クレータ
                   	    				if (gtt_Internal_pack.Data.In.usWeldingCratCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	    				{
       		    							gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
       									}
       									if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                   	    				{
       		    							gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
       									}
                        				//パルス電流
                       					if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
                       					{
        		    	    				gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        								}
        								if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                       					{
        		    	    				gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        								}
                                     }


								}
								else{
									gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
								}
							}
#endif
//-----------------------------------------------------------------------------
						}
//-----------------------------------------------------------------------------
// BP4 Phase7 by @Tny 2009.02.12
#if true
						if(guc_Select_counter == MODE_PLAY){	//再生
							if(gtt_Ctrl_flag.Play == ON){
								if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){    // 溶接中は「記憶」を選択できなくする
									guc_Select_counter = MODE_WELDING;
									gtt_Ctrl_flag.Rec_display = OFF;
								}
								else{
									guc_Select_counter = MODE_RECORD;
								}
								gtt_Ctrl_flag.Play = OFF;
								guc_Ch_no = 0;
								guc_Ch_no_bkup = 0;
							}
						}
						if(guc_Select_counter == MODE_RECORD){	//記憶
							if(guc_Ch_no > 0){
								if(gtt_Ctrl_flag.Rec_display == ON){
									if(gtt_Ctrl_flag.Yes == ON){
										gtt_Ctrl_flag.Rec = ON;
										gtt_Ctrl_flag.Yes = OFF;
										guc_Select_counter = MODE_WELDING;
										gtt_Ctrl_flag.Rec_display = OFF;
									}
									else{
										guc_Select_counter = MODE_WELDING;
										gtt_Ctrl_flag.Rec_display = OFF;
									}
									if(gtt_Ctrl_flag.Del == ON){
										gtt_Ctrl_flag.Delete = ON;
										gtt_Ctrl_flag.Del = OFF;
										guc_Select_counter = MODE_WELDING;
										gtt_Ctrl_flag.Rec_display = OFF;
										strcpy((char *)gt_WeldCondName[guc_Ch_no], "CH  :");	// 条件名文字列データ格納エリアへデフォルト名の文字列をコピー
										gt_WeldCondName[guc_Ch_no][2] = (guc_Ch_no / 10 + 0x30);
										gt_WeldCondName[guc_Ch_no][3] = (guc_Ch_no % 10 + 0x30);
										gb_WeldCondNameWrite = true;							// 溶接条件名書き込み要求フラグ
									}
									else{
										guc_Select_counter = MODE_WELDING;
										gtt_Ctrl_flag.Rec_display = OFF;
									}
								}
								else{
									gtt_Ctrl_flag.Rec_display = ON;
									gb_2Line_FirstDisplay		= false;// 初回二行目表示フラグをＯＦＦ
								}
							}
							else{
								guc_Select_counter = MODE_WELDING;
								gtt_Ctrl_flag.Rec_display = OFF;
							}
						}
#endif
//-----------------------------------------------------------------------------
//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23
						}
//--------------------------------------------------------------------
                    }
                } else { //ナビモード時
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	// <NAVI Enhancements(Phase 2)> 2011.10.27
	#if true
					if((gtt_Ctrl_flag.RemoteController == false)&&(gb_IIF_Select == false)){	// リモコン、およびＩＩＦは接続されていない？
	#else
					if(gtt_Ctrl_flag.RemoteController == false){
	#endif
	//-----------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------
               	    if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                    {
                        gtt_Navi.uc_Jog_set_key = true;
                    }
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
					}
//---------------------------------------
                }


                 //***** ガス出力処理 2009.03.17 *****
          		 if(guc_Select_counter == MODE_PLAY){
                   	if(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF){ //ガス
                        if(guc_Gas_on_off_flag == OFF){
                            guc_Gas_on_off_flag = ON;
                        }
                        else{
                            guc_Gas_on_off_flag = OFF;
                        }
                    }
                 }
          		 else if(guc_Select_counter == MODE_RECORD){
                   	if(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF){ //ガス
                        if(guc_Gas_on_off_flag == OFF){
                            guc_Gas_on_off_flag = ON;
                        }
                        else{
                            guc_Gas_on_off_flag = OFF;
                        }
                    }
                 }

          	    if(guc_Select_counter == MODE_DETAILS)
                {
                   	if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1 == true)
                    {
                        guc_No_act_flag = ON;
                    } else {
                        guc_No_act_flag = OFF;
                    }
                }
                //************************************

          		if(guc_Select_counter == MODE_WELDING) // Phase12 by @Tny 2008/09/17	// BP4 Phase6 by @Tny 2009/01/27
          		//if(guc_Select_counter == MODE_WELDING && guc_Method_condition_data != NAVI_METHOD) //2009.03.17
          		{
              		gtt_Ctrl_flag.Param_change = ON; //2008.08.07
                    //溶接法の選択 2009.01.10
           			//if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //溶接法
                    //リモコン再生モード時は変更できない 2009.03.30
           			//if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //溶接法
           			if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && (guc_Sequence_mode == IDLING || guc_Sequence_mode == HAND_STICK) && guc_Fram_Phase == 0) //溶接法 2009.12.28
            		{

                        //***** 前の溶接法の記憶 2009.02.23*****
                    	guc_Pulse_mode_m[guc_Method_condition_counter]      = guc_Pulse_mode_counter;
                    	guc_Pulse_mode_m[guc_Method_condition_counter]      = guc_Pulse_mode_data;
                        guc_Crater_mode_m[guc_Method_condition_counter]     = guc_Crater_mode_counter;
                        guc_Ac_wave_counter_m[guc_Method_condition_counter] = guc_Ac_wave_counter;
                        gus_Pulse_duty_m[guc_Method_condition_counter]      = gtt_Internal_pack.Data.In.usPulseDuty;
                        gus_Pulse_frequency_m[guc_Method_condition_counter] = gtt_Internal_pack.Data.In.usPulseFreq;
                        guc_MIX_frequency_m[guc_Method_condition_counter]   = gtt_Internal_pack.Data.In.ucMixFreq;
                        guc_MIX_duty_m[guc_Method_condition_counter]        = gtt_Internal_pack.Data.In.ucMixAcRatio;
                        gss_Pre_flow_m[guc_Method_condition_counter]        = gtt_Internal_pack.Data.In.sPreFlowTime;
                        gss_After_flow_m[guc_Method_condition_counter]      = gtt_Internal_pack.Data.In.sAfterFlowTime;
                        gss_Up_slop_m[guc_Method_condition_counter]         = gtt_Internal_pack.Data.In.sUpSlopTime;
                        gss_Down_slop_m[guc_Method_condition_counter]       = gtt_Internal_pack.Data.In.sDownSlopTime;
                        gss_Arc_spot_time_m[guc_Method_condition_counter]   = gtt_Ditail_work.ss_Arc_spot_time; //2009.03.06 2009.03.16 unsigned -> signed


                        if (guc_Method_condition_counter == STD_AC_METHOD) //2009.04.01
                        {
                            guc_AC_cleaning_duty_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter]= gtt_Internal_pack.Data.In.ucCleaningDuty;
                            gus_AC_frequency_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usAcFreq;
                        } else if (guc_Method_condition_counter == EXP_AC_METHOD) {
                            guc_AC_cleaning_duty_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter]= gtt_Internal_pack.Data.In.ucCleaningDuty;
                            gus_AC_frequency_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usAcFreq;
                        } else {
                            guc_AC_cleaning_duty_m[guc_Method_condition_counter]= gtt_Internal_pack.Data.In.ucCleaningDuty;
                            gus_AC_frequency_m[guc_Method_condition_counter]    = gtt_Internal_pack.Data.In.usAcFreq;
                        }

		               //if(gtt_Ctrl_flag.RemoteController != true){ //2009.03.09.NO4 2009.03.13場所変更
		                if(gtt_Ctrl_flag.RemoteController == false){ //2009.03.09.NO4 2009.03.13場所変更 2009.03.30
                           if (guc_Method_condition_counter == STD_AC_METHOD) //2009.04.01
                           {
                               gus_Main_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usWeldingCurr;
                               gus_Init_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usWeldingInitCurr;
                               gus_Crat_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usWeldingCratCurr;
                               gus_Pulse_current_m[guc_Method_condition_counter+ 10 + guc_Ac_wave_counter]   = gtt_Internal_pack.Data.In.usIP;
                           } else if (guc_Method_condition_counter == EXP_AC_METHOD) {
                               gus_Main_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usWeldingCurr;
                               gus_Init_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usWeldingInitCurr;
                               gus_Crat_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter]    = gtt_Internal_pack.Data.In.usWeldingCratCurr;
                               gus_Pulse_current_m[guc_Method_condition_counter+ 15 + guc_Ac_wave_counter]   = gtt_Internal_pack.Data.In.usIP;
                           } else {
                               gus_Main_current_m[guc_Method_condition_counter]    = gtt_Internal_pack.Data.In.usWeldingCurr;
                               gus_Init_current_m[guc_Method_condition_counter]    = gtt_Internal_pack.Data.In.usWeldingInitCurr;
                               gus_Crat_current_m[guc_Method_condition_counter]    = gtt_Internal_pack.Data.In.usWeldingCratCurr;
                               gus_Pulse_current_m[guc_Method_condition_counter]   = gtt_Internal_pack.Data.In.usIP;
                           }
                        } else { //2009.03.09.NO4
                          gus_RemoInput[5] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[6] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[7] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[8] = 2048; //2009.03.31 1024->2048
                        }

                		guc_Method_condition_counter++;
                        if (guc_Method_condition_counter > 6)
                        {
                    		guc_Method_condition_counter = 0;
                        }
                    	guc_Method_condition_data = guc_Method_condition_counter;
                        //if (guc_Method_condition_data == STD_MIX_METHOD)
                        if (guc_Method_condition_data == STD_MIX_METHOD || guc_Method_condition_data == STD_HAND_METHOD || guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.04.03 ＭＩＸ、ハンド、エキスパートモードではスポットもパルスは必要ないので、０クリアする。
                        {
                            if (guc_Crater_mode_counter >= 3)
                            {
                                guc_Crater_mode_counter = 0;
                            }
                    		//guc_Ac_wave_counter = 0; //2009.01.20 2009.03.13 del
                            guc_Pulse_mode_data = 0; //2009.02.17      ＭＩＸではパルスは必要ないので無にする。
                            guc_Pulse_mode_counter = 0; //2009.02.17   ＭＩＸではパルスは必要ないので無にする。
                        }
                        if (guc_Method_condition_data == EXP_AC_METHOD) //2009.04.06
                        {
							   guc_Ac_wave_counter = 0;
						}

                        //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                        guc_Pulse_item_counter  = 0;
                        guc_Ac_tig_set_counter  = 0;
                        guc_Mix_tig_set_counter = 0;
                        //************************************************************************

                        //***** 今の溶接法の再生 2009.02.23*****
                    	guc_Pulse_mode_counter                            = guc_Pulse_mode_m[guc_Method_condition_counter];
                    	guc_Pulse_mode_data                               = guc_Pulse_mode_m[guc_Method_condition_counter];
                        guc_Crater_mode_counter                           = guc_Crater_mode_m[guc_Method_condition_counter];
                        guc_Ac_wave_counter                               = guc_Ac_wave_counter_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.usPulseDuty             = gus_Pulse_duty_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.usPulseFreq             = gus_Pulse_frequency_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.ucMixFreq               = guc_MIX_frequency_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.ucMixAcRatio            = guc_MIX_duty_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.sPreFlowTime            = gss_Pre_flow_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.sAfterFlowTime          = gss_After_flow_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.sUpSlopTime             = gss_Up_slop_m[guc_Method_condition_counter];
                        gtt_Internal_pack.Data.In.sDownSlopTime           = gss_Down_slop_m[guc_Method_condition_counter];
                        gtt_Ditail_work.ss_Arc_spot_time                  = gss_Arc_spot_time_m[guc_Method_condition_counter]; //2009.03.06 2009.03.16 unsigned -> signed

                        if (guc_Method_condition_counter == STD_AC_METHOD) //2009.04.01
                        {
                            gtt_Internal_pack.Data.In.ucCleaningDuty      = guc_AC_cleaning_duty_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                            gtt_Internal_pack.Data.In.usAcFreq            = gus_AC_frequency_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                        } else if (guc_Method_condition_counter == EXP_AC_METHOD) {
                            gtt_Internal_pack.Data.In.ucCleaningDuty      = guc_AC_cleaning_duty_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                            gtt_Internal_pack.Data.In.usAcFreq            = gus_AC_frequency_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                        } else {
                            gtt_Internal_pack.Data.In.ucCleaningDuty      = guc_AC_cleaning_duty_m[guc_Method_condition_counter];
                            gtt_Internal_pack.Data.In.usAcFreq            = gus_AC_frequency_m[guc_Method_condition_counter];
                        }
		                //if(gtt_Ctrl_flag.RemoteController != true){ //2009.03.09.NO4 2009.03.13場所変更
		                if(gtt_Ctrl_flag.RemoteController == false){ //2009.03.09.NO4 2009.03.13場所変更 2009.03.30
                           if (guc_Method_condition_counter == STD_AC_METHOD) //2009.04.01
                           {
                               gtt_Internal_pack.Data.In.usWeldingCurr        = gus_Main_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingInitCurr    = gus_Init_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingCratCurr    = gus_Crat_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usIP                 = gus_Pulse_current_m[guc_Method_condition_counter+ 10 + guc_Ac_wave_counter];
                           } else if (guc_Method_condition_counter == EXP_AC_METHOD) {
                               gtt_Internal_pack.Data.In.usWeldingCurr        = gus_Main_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingInitCurr    = gus_Init_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingCratCurr    = gus_Crat_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usIP                 = gus_Pulse_current_m[guc_Method_condition_counter+ 15 + guc_Ac_wave_counter];
                           } else {
                               gtt_Internal_pack.Data.In.usWeldingCurr        = gus_Main_current_m[guc_Method_condition_counter];
                               gtt_Internal_pack.Data.In.usWeldingInitCurr    = gus_Init_current_m[guc_Method_condition_counter];
                               gtt_Internal_pack.Data.In.usWeldingCratCurr    = gus_Crat_current_m[guc_Method_condition_counter];
                               gtt_Internal_pack.Data.In.usIP                 = gus_Pulse_current_m[guc_Method_condition_counter];
                           }
                        } else { //2009.03.09.NO4
                          gus_RemoInput[5] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[6] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[7] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[8] = 2048; //2009.03.31 1024->2048
                        }
                        //***** 可変パラメータ反映 2009.02.23 *****
#if 0 //2019.03.15 ihara del
                        //_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //ＡＣ周波数の反映 2009.03.27
                        _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //ＡＣ周波数の反映 2009.12.29
                        _union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty; //2009.02.16
                        //_union.Nrm.CalParm[66 - 1].c = gtt_Internal_pack.Data.In.ucMixFreq; //ＭＩＸ周波数反映 2009.03.27
                        _union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10; //ＭＩＸ周波数反映 2009.03.31
                        _union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio; //ＭＩＸ比率反映 2009.03.27
                        //_union.Nrm.CalParm[69 - 1].c = gtt_Internal_pack.Data.In.usPulseFreq; //パルス周波数反映 2009.03.27
                        _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10; //パルス周波数反映 2009.03.31
                        _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty; //パルス幅反映 2009.03.27
#endif
                        
                        //***** パルスモードの切り替え処理 2009.02.27*****
#if 0
                        if (guc_Pulse_mode_counter >= 1 && gtt_Internal_pack.Data.In.usPulseFreq > 50)
                        {
                          _union.Nrm.CalParm[65 - 1].c = 1;
                        } else {
                          _union.Nrm.CalParm[65 - 1].c = 0;
                        }
#endif
                        //************************************************
#if 0 //2010.01.20 del
                        //交流５Hz制限 2009.03.02
                        if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.03.02
                        {
                            if (gtt_Internal_pack.Data.In.usPulseFreq >= 50)
                            {
                                gtt_Internal_pack.Data.In.usPulseFreq = 50;
                            }
                        }
#endif
                			//<><><><> 出力制限の反映 2010.01.12 <><><><>
                			switch (guc_Method_condition_data)
                			{
                    			case STD_DC_METHOD:
                    			case STD_MIX_METHOD:
                    			case EXP_DC_METHOD:
                    			case EXP_AC_METHOD:
                         			if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         			{
                             			MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                                    } else {
                                        MAX_CURRENT = MAX_CURRENT_VAL;
                         			}
                         			break;
                    			case STD_AC_METHOD:
                         			if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         			{
                             			MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                                    } else {
                                        MAX_CURRENT = MAX_CURRENT_VAL;
                         			}
                             		if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_AC_SOFT_VAL)
                             		{
                                 		MAX_CURRENT_AC_SOFT = gss_Select_dital[P_MAX_OUTPUT];
                             		} else {
                                 		MAX_CURRENT_AC_SOFT = MAX_CURRENT_AC_SOFT_VAL;
                                    }
                         			break;
                    			case STD_HAND_METHOD:
                         			if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_HAND_VAL)
                         			{
                             			MAX_CURRENT_HAND = gss_Select_dital[P_MAX_OUTPUT];
                         			} else {
                             			MAX_CURRENT_HAND = MAX_CURRENT_HAND_VAL;
                                    }
                         			break;
                    			default:
                         			if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         			{
                             			MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                                    } else {
                                        MAX_CURRENT = MAX_CURRENT_VAL;
                         			}
                         			break;
               			 }
                		 //<><><><><><><><><><><><><><><><><><><><><><>

                        //**** 制限電流セット 2009.02.19 *****************************************
                        if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT;
                        }
                        if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            //***** 2009.03.13 *****
                    		if (guc_Ac_wave_counter == 1) //ハードＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT;
                                gss_Min_current = MIN_CURRENT_AC_HARD; //2011.09.30
                            }
                    		if (guc_Ac_wave_counter == 2) //ソフトＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT_AC_SOFT;
                                gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            }
                            //**********************

                        }
                        if (guc_Method_condition_data == STD_MIX_METHOD) //2009.03.17
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                        }
                        
                        if (guc_Method_condition_data == STD_HAND_METHOD) //2009.03.06
                        {
                            gss_Max_current = MAX_CURRENT_HAND;
                            gss_Min_current = MIN_CURRENT_HAND;
                        }
                        
                        //初期
                   	    if (gtt_Internal_pack.Data.In.usWeldingInitCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  	    {
       		    			gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
       					}
       					if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
       					}
                        //本溶接
                   	    if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
       					}
       					if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                   	    {
      		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
       					}
                        //クレータ
                   	    if (gtt_Internal_pack.Data.In.usWeldingCratCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	    {
       		    			gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
       					}
       					if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                   	    {
       		    			gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
       					}
                        //パルス電流
                       	if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
                       	{
        		    	    gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        				}
        				if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                       	{
        		    	    gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        				}
                        //************************************************************************

                        //***** 2009.03.13 *****
                        gss_Current_result_work = 0;
                        gss_Voltage_result_work = 0;
                        gsl_Current_result_work2 = 0; //2009.04.11
                        gsl_Voltage_result_work2 = 0; //2009.04.11
                        gtt_Ctrl_counter.Avr_result = 0;
                        gss_Weld_end_current = gss_Current_work = 0;
                        gss_Weld_end_voltage = gss_Voltage_work = 0;
                        gtt_Ctrl_flag.Weld_end_disp = OFF;
                        gss_Base_current_work = 0; //2009.03.24
                        gss_Base_voltage_work = 0; //2009.03.24
                        //**********************

                        guc_Jog_set_key = true; //2009.01.16
                        gtt_Table_key.Change_flag = ON; //2009.02.04
            		}
                  //if (guc_Method_condition_data != STD_HAND_METHOD) //2009.03.06
                  if (guc_Method_condition_data != STD_HAND_METHOD && guc_Method_condition_data != NAVI_METHOD) //2009.03.17
                  {
                    //クレータの選択 2009.01.10
                    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //クレータ無＋クレータ有＋初期／クレータ有 2008.08.21 -> 2008.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                    //リモコン再生モード時は変更できない 2009.03.30
                    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //クレータ無＋クレータ有＋初期／クレータ有 2008.08.21 -> 2008.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                    {
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
						if(gtt_Ctrl_flag.RemoteController == false){
//---------------------------------------
                        guc_Crater_mode_counter++;
                        //if (guc_Crater_mode_counter > 2) //2009.01.28現在アークスポットに行かれるのはまずいので3->2に変更
                        if (guc_Crater_mode_counter > 3)
                        {
                            guc_Crater_mode_counter = 0;
                        }
                        //if (guc_Method_condition_data == STD_MIX_METHOD)
                        if (guc_Method_condition_data == STD_MIX_METHOD || guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.03.18
                        {
                            if (guc_Crater_mode_counter >= 3)
                            {
                                guc_Crater_mode_counter = 0;
                            }
                        }

                        //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                        guc_Pulse_item_counter  = 0;
                        guc_Ac_tig_set_counter  = 0;
                        guc_Mix_tig_set_counter = 0;
                        //************************************************************************

                        guc_Jog_set_key = true; //2009.01.16
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
						}
//---------------------------------------
                    }
                    
                    //パルスの選択 2009.01.10
                   	//if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No13 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                    //リモコン再生時は変更できない 2009.03.30
                   	if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No13 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                    {
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
						if(gtt_Ctrl_flag.RemoteController == false){
//---------------------------------------
                        guc_Pulse_mode_counter++;
                        if (guc_Pulse_mode_counter > 1)
                        {
                    		guc_Pulse_mode_counter = 0;
                        }
                    	guc_Pulse_mode_data = guc_Pulse_mode_counter;

                        //if (guc_Method_condition_data == STD_MIX_METHOD) //2009.02.17 ＭＩＸではパルスは必要ないので、０クリアする。
                        if (guc_Method_condition_data == STD_MIX_METHOD || guc_Method_condition_data == STD_HAND_METHOD || guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.04.03 ＭＩＸ、ハンド、エキスパートモードではパルスは必要ないので、０クリアする。
                        {
                    	    guc_Pulse_mode_data = 0;
                            guc_Pulse_mode_counter = 0;
                        }
                        //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                        guc_Pulse_item_counter  = 0;
                        guc_Ac_tig_set_counter  = 0;
                        guc_Mix_tig_set_counter = 0;
                        //************************************************************************

                        guc_Jog_set_key = true; //2009.01.16
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
						}
//---------------------------------------
                        
                    }
                  }
                    if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
                    {
                        //交流波形の選択 2009.01.10
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No14 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                        //リモコン再生時は変更できない 2009.03.30
                   	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No14 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                        {
                            guc_Ac_wave_counter++;
                            if (guc_Ac_wave_counter > 2) //2009.03.06
                            //if (guc_Ac_wave_counter > 1) //2009.02.19 ロード制限
                            {
                    		    guc_Ac_wave_counter = 0;
                            }
                            //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                            guc_Pulse_item_counter  = 0;
                            guc_Ac_tig_set_counter  = 0;
                            guc_Mix_tig_set_counter = 0;
                           //************************************************************************
                           if (guc_Method_condition_data == EXP_AC_METHOD) //2009.04.06
                           {
							   guc_Ac_wave_counter = 0;
						   }

                        if (guc_Method_condition_counter == STD_AC_METHOD) //2009.04.01
                        {
                            gtt_Internal_pack.Data.In.ucCleaningDuty      = guc_AC_cleaning_duty_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                            gtt_Internal_pack.Data.In.usAcFreq            = gus_AC_frequency_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                        } else if (guc_Method_condition_counter == EXP_AC_METHOD) {
                            gtt_Internal_pack.Data.In.ucCleaningDuty      = guc_AC_cleaning_duty_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                            gtt_Internal_pack.Data.In.usAcFreq            = gus_AC_frequency_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                        }
		                //if(gtt_Ctrl_flag.RemoteController != true){ //2009.03.09.NO4 2009.03.13場所変更
		                if(gtt_Ctrl_flag.RemoteController == false){ //2009.03.09.NO4 2009.03.13場所変更 2009.03.30
                           if (guc_Method_condition_counter == STD_AC_METHOD) //2009.04.01
                           {
                               gtt_Internal_pack.Data.In.usWeldingCurr        = gus_Main_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingInitCurr    = gus_Init_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingCratCurr    = gus_Crat_current_m[guc_Method_condition_counter + 10 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usIP                 = gus_Pulse_current_m[guc_Method_condition_counter+ 10 + guc_Ac_wave_counter];
                           } else if (guc_Method_condition_counter == EXP_AC_METHOD) {
                               gtt_Internal_pack.Data.In.usWeldingCurr        = gus_Main_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingInitCurr    = gus_Init_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usWeldingCratCurr    = gus_Crat_current_m[guc_Method_condition_counter + 15 + guc_Ac_wave_counter];
                               gtt_Internal_pack.Data.In.usIP                 = gus_Pulse_current_m[guc_Method_condition_counter+ 15 + guc_Ac_wave_counter];
                           }
                        } else { //2009.03.09.NO4
                          gus_RemoInput[5] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[6] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[7] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[8] = 2048; //2009.03.31 1024->2048
                        }

                        //<><><><> 出力制限の反映 2010.01.12 <><><><>
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                         {
                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT = MAX_CURRENT_VAL;
                         }
                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_AC_SOFT_VAL)
                         {
                             MAX_CURRENT_AC_SOFT = gss_Select_dital[P_MAX_OUTPUT];
                         } else {
                             MAX_CURRENT_AC_SOFT = MAX_CURRENT_AC_SOFT_VAL;
                         }
                         //<><><><><><><><><><><><><><><><><><><><><><>

                    		if (guc_Ac_wave_counter == 0) //標準ＡＣ  2009.04.01
                            {
                                gss_Max_current = MAX_CURRENT;
                                gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            }

                            //***** 2009.03.13 *****
                    		if (guc_Ac_wave_counter == 1) //ハードＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT;
                                gss_Min_current = MIN_CURRENT_AC_HARD;
                            }
                    		if (guc_Ac_wave_counter == 2) //ソフトＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT_AC_SOFT;
                                gss_Min_current = MIN_CURRENT_AC;
                            }
                            //**********************
                            //初期
                   	        if (gtt_Internal_pack.Data.In.usWeldingInitCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  	        {
       		    			    gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
       					    }
       					    if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                   	        {
      		    			    gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
       					    }
                            //本溶接
                   	        if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	        {
      		    			    gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
       					    }
       					    if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                   	        {
      		    			    gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
       					    }
                            //クレータ
                   	        if (gtt_Internal_pack.Data.In.usWeldingCratCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	        {
       		    			    gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
       					    }
       					    if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                   	        {
       		    			    gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
       					    }
                            //パルス電流
                       	    if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
                       	    {
        		    	        gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        				    }
        				    if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                       	    {
        		    	        gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        				    }
                   
                            guc_Jog_set_key = true; //2009.01.19
                            gtt_Table_key.Change_flag = ON; //2009.03.31
                        }
                    
                    }
                    
                  if (guc_Method_condition_data != STD_HAND_METHOD) //2009.03.06
                  {
                    //ガス検
                   	if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //ガス 2009.01.09
                    {
                        if (guc_Gas_on_off_flag == OFF)
                        {
                            guc_Gas_on_off_flag = ON;
                        } else {
                            guc_Gas_on_off_flag = OFF;
                        }
                    }
                   } else { //2009.03.06
                            guc_Gas_on_off_flag = OFF;
                   }



//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.10
					if(gss_Select_dital[P_CONTROLLER_LOCK] == false){	// コントローラ・ロック中ではない？
//--------------------------------------------------------------------
                    //直流手溶接 2009.03.06
                    if (guc_Method_condition_data == STD_HAND_METHOD)
                    {
                    
                        gus_Sequence_set_data_bk = gus_Sequence_set_data; //現状を退避 2009.01.19
                        //溶接電流
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                        //リモコン再生時は変更できない 2009.03.30
//                 	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && guc_Fram_Phase == 0)	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                        {
                            //guc_Sequence_set_data = MAIN_WELD_CURRENT_SET_DATA; //0x08
                            gus_Sequence_set_data = MAIN_WELD_CURRENT_SET_DATA; //0x0008 2009.01.19
                            //guc_Ac_tig_set_counter = 0; //2009.01.19

                            //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                            guc_Pulse_item_counter  = 0;
                            guc_Ac_tig_set_counter  = 0;
                            guc_Mix_tig_set_counter = 0;
                            guc_Crater_mode_counter = 0;
                    	    guc_Pulse_mode_counter  = 0;
                    	    guc_Pulse_mode_data     = 0;
                            //************************************************************************

                            guc_Jog_set_key = false;
                        }
                    }
                    //直流ＴＩＧ　交流ＴＩＧ　ＭＩＸＴＩＧ2009.01.13
                    if (guc_Method_condition_data != STD_HAND_METHOD && guc_Method_condition_data != NAVI_METHOD)
                    {
                        //guc_Sequence_set_data_bk = guc_Sequence_set_data; //現状を退避
                        gus_Sequence_set_data_bk = gus_Sequence_set_data; //現状を退避 2009.01.19
                        //プリフロー
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.09
                        //リモコン再生時は変更できない 2009.03.30
//                 	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.09
                   	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4 == true && guc_Fram_Phase == 0) //2009.02.09	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                        {
                            //guc_Sequence_set_data = PREFLOW_SET_DATA; //0x01
                            gus_Sequence_set_data = PREFLOW_SET_DATA; //0x0001 2009.01.19
                            //guc_Ac_tig_set_counter = 0; //2009.01.19

                            //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                            guc_Pulse_item_counter  = 0;
                            guc_Ac_tig_set_counter  = 0;
                            guc_Mix_tig_set_counter = 0;
                            //************************************************************************

                            guc_Jog_set_key = false;
                        }
                        //溶接電流
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                        //リモコン再生時は変更できない 2009.03.30
//                 	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7 == true && guc_Fram_Phase == 0)	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                        {
                            //guc_Sequence_set_data = MAIN_WELD_CURRENT_SET_DATA; //0x08
                            gus_Sequence_set_data = MAIN_WELD_CURRENT_SET_DATA; //0x0008 2009.01.19
                            //guc_Ac_tig_set_counter = 0; //2009.01.19

                            //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                            guc_Pulse_item_counter  = 0;
                            guc_Ac_tig_set_counter  = 0;
                            guc_Mix_tig_set_counter = 0;
                            //************************************************************************

                            guc_Jog_set_key = false;
                        }
                        //アフターフロー
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	    //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
                        //リモコン再生時は変更できない 2009.03.30
//                 	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
                   	    if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 == true && guc_Fram_Phase == 0) //2009.02.18	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                        {
                            //guc_Sequence_set_data = AFTERFLOW_SET_DATA; //0x40
                            gus_Sequence_set_data = AFTERFLOW_SET_DATA; //0x0040 2009.01.19
                            //guc_Ac_tig_set_counter = 0; //2009.01.19

                            //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                            guc_Pulse_item_counter  = 0;
                            guc_Ac_tig_set_counter  = 0;
                            guc_Mix_tig_set_counter = 0;
                            //************************************************************************

                            guc_Jog_set_key = false;
                        }
                        //***** クレータ有り無し選択 *****
                        //if (guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2)
                        if (guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2 || guc_Crater_mode_counter == 3) //2009.03.06
                        {
                            //初期電流
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
                            //リモコン再生時は変更できない 2009.03.30
                   	        //if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
//                 	        if ((guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) && gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.04.03
                   	        if ((guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) && gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5 == true && guc_Fram_Phase == 0) //2009.04.03	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                            {
                                //guc_Sequence_set_data = INIT_WELD_CURRENT_SET_DATA; //0x02
                                gus_Sequence_set_data = INIT_WELD_CURRENT_SET_DATA; //0x0002 2009.01.19
                                //guc_Ac_tig_set_counter = 0; //2009.01.19

                                //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                                guc_Pulse_item_counter  = 0;
                                guc_Ac_tig_set_counter  = 0;
                                guc_Mix_tig_set_counter = 0;
                                //************************************************************************

                                guc_Jog_set_key = false;
                            }
                            //アップスロープ
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
                            //リモコン再生時は変更できない 2009.03.30
                   	        //if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
//                 	        if ((guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) && gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.04.03
                   	        if ((guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) && gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6 == true && guc_Fram_Phase == 0) //2009.04.03	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                            {
                                //guc_Sequence_set_data = UPSLOP_SET_DATA; //0x04
                                gus_Sequence_set_data = UPSLOP_SET_DATA; //0x0004 2009.01.19
                                //guc_Ac_tig_set_counter = 0; //2009.01.19

                                //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                                guc_Pulse_item_counter  = 0;
                                guc_Ac_tig_set_counter  = 0;
                                guc_Mix_tig_set_counter = 0;
                                //************************************************************************

                                guc_Jog_set_key = false;
                            }
                            //ダウンスロープ
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
                            //リモコン再生時は変更できない 2009.03.30
//                 	        if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
                   	        if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8 == true && guc_Fram_Phase == 0) //2009.02.18	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                            {
                                //guc_Sequence_set_data = DOWNSLOP_SET_DATA; //0x10
                                gus_Sequence_set_data = DOWNSLOP_SET_DATA; //0x0010 2009.01.19
                                //guc_Ac_tig_set_counter = 0; //2009.01.19

                                //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                                guc_Pulse_item_counter  = 0;
                                guc_Ac_tig_set_counter  = 0;
                                guc_Mix_tig_set_counter = 0;
                                //************************************************************************

                                guc_Jog_set_key = false;
                            }
                            //クレータ電流
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9 == true && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0)
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
                            //リモコン再生時は変更できない 2009.03.30
                   	        //if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.02.18
//                 	        if ((guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) && gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9 == true && guc_Controller_gas_sw_cancel == OFF && guc_Fram_Phase == 0) //2009.04.03
                   	        if ((guc_Crater_mode_counter == 1 || guc_Crater_mode_counter == 2) && gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9 == true && guc_Fram_Phase == 0) //2009.04.03	// 	ＩＩＦに「ガス検査」が割り振られているとキー入力が無効となる不具合に対応	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
                            {
                                //guc_Sequence_set_data = CRATER_WELD_CURRENT_SET_DATA; //0x20
                                gus_Sequence_set_data = CRATER_WELD_CURRENT_SET_DATA; //0x0020 2009.01.19
                                //guc_Ac_tig_set_counter = 0; //2009.01.19

                                //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す。2009.02.12 *****
                                guc_Pulse_item_counter  = 0;
                                guc_Ac_tig_set_counter  = 0;
                                guc_Mix_tig_set_counter = 0;
                                //************************************************************************

                                guc_Jog_set_key = false;
                            }
                        }
                        //***** パルス有り選択 *****
                        if (guc_Pulse_mode_data == 1)
                        {
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Fram_Phase == 0) //2009.02.18
                            //リモコン再生時は変更できない 2009.03.30
                   	        if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Fram_Phase == 0) //2009.02.18
                            {
                                guc_Pulse_item_counter++;
                                if (guc_Pulse_item_counter > 2)
                                {
                    		        guc_Pulse_item_counter = 0;
                                }
                                //guc_Sequence_set_data = PULSE_ITEM_SET_DATA; //0x80
                                gus_Sequence_set_data = PULSE_ITEM_SET_DATA; //0x0080 2009.01.19
                                //guc_Ac_tig_set_counter = 0; //2009.01.19
                                guc_Jog_set_key = false;
                            }
                        }
                        //***** 交流ＴＩＧ設定選択 *****
                        //if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
                        if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD) //2009.01.20
                        {
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No15 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No15 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Fram_Phase == 0) //2009.02.18
                            //リモコン再生時は変更できない 2009.03.30
                   	        if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No15 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Fram_Phase == 0) //2009.02.18
                            {
                                guc_Ac_tig_set_counter++;
                                if (guc_Ac_tig_set_counter > 1)
                                {
                    		        guc_Ac_tig_set_counter = 0;
                                }
                                gus_Sequence_set_data = AC_TIG_ITEM_SET_DATA; //0x0100
                                guc_Jog_set_key = false;
                            }
                        }
                        //***** ＭＩＸＴＩＧ設定の選択 2009.01.20 *****
                        if (guc_Method_condition_data == STD_MIX_METHOD)
                        {
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No16 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && ((gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false)) && guc_Fram_Phase == 0) //制御 2008.08.21 -> 2009.09.10 / Phase19 by @Tny 2008/09/26 2008.11.20
                   	        //if (ComuniPackRemo.Data.To.t_Sw.Sw_bit.No16 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Fram_Phase == 0) //2009.02.18
                            //リモコン再生時は変更できない 2009.03.30
                   	        if (gtt_Ctrl_flag.Remo_play_mode == OFF && ComuniPackRemo.Data.To.t_Sw.Sw_bit.No16 == true && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Fram_Phase == 0) //2009.02.18
                            {
                                guc_Mix_tig_set_counter++;
                                if (guc_Mix_tig_set_counter > 1)
                                {
                    		        guc_Mix_tig_set_counter = 0;
                                }
                                gus_Sequence_set_data = MIX_TIG_ITEM_SET_DATA; //0x0100
                                guc_Jog_set_key = false;
                            }
                        }
                    }
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.10
					}
//--------------------------------------------------------------------
                    //2009.01.19変更
                    for (puc_Index = 0 ; puc_Index < 16 ; puc_Index++)
                    {
                         pus_Work = gus_Sequence_set_data;
                         pus_Work = (pus_Work >> puc_Index) & 0x01;
                         if (pus_Work == 0x01)
                         {
                             puc_Bit_check_counter++;
                         }
                    }
                    if (puc_Bit_check_counter > 1)
                    {
                        gus_Sequence_set_data = gus_Sequence_set_data_bk;
                    }

                }
            }
        }



        //****************************************************************
        
        //************* リモコンＪＯＧによる電流、電圧の調整部 ***************
        if (guc_Jog_rewrite_check_flag == 1 || guc_Initial_display_flag == false)
        {
                        //<><><> 溶接終了電流表示キャンセル 2009.03.31 <><><>
                        if (gtt_End_welding_display.us_Display_time > 0)
                        {
                            gtt_Ctrl_flag.End_welding_display_cansel = ON;
                        } else {
                            gtt_Ctrl_flag.End_welding_display_cansel = OFF;
                        }
                        //<><><><><><><><><><><><><><><><><><><><><><><><><><>
            if (gtt_Ctrl_flag.Set_screen_on_off == ON)
            {
                gtt_Ctrl_flag.Param_change = ON; //2008.08.07
                if (gtt_Ctrl_flag.Service_man == OFF) //技術・サービスマンメニュー分岐 2008.09.02
                {
                      switch (gtt_Ctrl_counter.uc_User_menu_no) //ユーザー入力部
                      {
                        case 0: //特殊パラメータ入力
                             if (gtt_Ctrl_counter.Pass_word_ok != 3 && gtt_Ctrl_flag.Pass_word_err == OFF)
                             {
                                 gtt_Ctrl_counter.us_User_parameter_no = gtt_Ctrl_counter.us_User_parameter_no + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                             }
                             if (gtt_Ctrl_counter.us_User_parameter_no == PASS_WORD_NO)
                             {
                               gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] = gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] + ((signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2)) * 111;
                             } else {
                               gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] = gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2);
                             }
                             if((signed short)gtt_Ctrl_counter.us_User_parameter_no <= 0){
                                 gtt_Ctrl_counter.us_User_parameter_no = 0;
                             }
                             if (gtt_Ctrl_counter.us_User_parameter_no > USER_PARAMETER_NO - 1) //2008.09.04
                             {
                                 gtt_Ctrl_counter.us_User_parameter_no = USER_PARAMETER_NO -1;  //2008.09.04
                             }
                             if (gtt_Ctrl_counter.us_User_parameter_no == PASS_WORD_NO)
                             {
                                 if (gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] >= 999)
                                 {
                                     gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] = 999;
                                 }
                                 if (gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] <= 111)
                                 {
                                     gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] = 111;
                                 }
                             } else {
                                 if (gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] >= USER_PARAMETER_MAX)
                                 {
                                     gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] = USER_PARAMETER_MAX;
                                 }
                                 if (gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] <= USER_PARAMETER_MIN)
                                 {
                                     gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] = USER_PARAMETER_MIN;
                                 }
                             }
                             break;
                        case 1: //全パラメータリセット
                             psc_Flag_work = (signed char)gtt_Ctrl_flag.User_all_parameter_reset + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                             if (psc_Flag_work >= 1)
                             {
                                 gtt_Ctrl_flag.User_all_parameter_reset = 1;
                             }
                             if (psc_Flag_work <= 0)
                             {
                                 gtt_Ctrl_flag.User_all_parameter_reset = 0;
                             }
                             break;
                        case 2: //ＩＩＦ設定
                            if(gb_IIF_Select){ // IIF接続時のみ対応
                             switch (gtt_Ctrl_counter.uc_Iif_no)
                             {
                                     case 0: //OUTPUT PORT設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Out_function_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Counter_work >= OUT_FUNCTION_NO_MAX)
                                            {
                                                psc_Counter_work = OUT_FUNCTION_NO_MAX;
                                            }
                                            if (psc_Counter_work < 0)
                                            {
                                                psc_Counter_work = 0;
                                            }
                                            gtt_Ctrl_counter.uc_Out_function_no = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.Out_function_set_ready = ON;
                                            }
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Out_port_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                                            if (psc_Counter_work >= 8)
                                            {
                                                psc_Counter_work = 8;
                                            }
                                            if (psc_Counter_work < 1)
                                            {
                                                psc_Counter_work = 1;
                                            }
                                            gtt_Ctrl_counter.uc_Out_port_no = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
                                            {
                                                gtt_Ctrl_flag.Out_function_set_ready = OFF;
                                                gtt_Ctrl_counter.uc_Out_function_no = 0;
                                            }
                                          break;
                                     case 1: //INPUT PORT設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_In_function_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Counter_work >= IN_FUNCTION_NO_MAX)
                                            {
                                                psc_Counter_work = IN_FUNCTION_NO_MAX;
                                            }
                                            if (psc_Counter_work < 0)
                                            {
                                                psc_Counter_work = 0;
                                            }
                                            gtt_Ctrl_counter.uc_In_function_no = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.In_function_set_ready = ON;
                                            }
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_In_port_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                                            if (psc_Counter_work >= 8)
                                            {
                                                psc_Counter_work = 8;
                                            }
                                            if (psc_Counter_work < 1)
                                            {
                                                psc_Counter_work = 1;
                                            }
                                            gtt_Ctrl_counter.uc_In_port_no = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
                                            {
                                                gtt_Ctrl_flag.In_function_set_ready = OFF;
                                                gtt_Ctrl_counter.uc_In_function_no = 0;
                                            }
                                          break;
                                     case 2: //ANALOG PORT設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Analog_function_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Counter_work >= ANALOG_FUNCTION_NO_MAX)
                                            {
                                                psc_Counter_work = ANALOG_FUNCTION_NO_MAX;
                                            }
                                            if (psc_Counter_work < 0)
                                            {
                                                psc_Counter_work = 0;
                                            }
                                            gtt_Ctrl_counter.uc_Analog_function_no = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.Analog_function_set_ready = ON;
                                            }
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Analog_port_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                                            if (psc_Counter_work >= 3)
                                            {
                                                psc_Counter_work = 3;
                                            }
                                            if (psc_Counter_work < 1)
                                            {
                                                psc_Counter_work = 1;
                                            }
                                            gtt_Ctrl_counter.uc_Analog_port_no = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
                                            {
                                                gtt_Ctrl_flag.Analog_function_set_ready = OFF;
                                                gtt_Ctrl_counter.uc_Analog_function_no = 0;
                                            }
                                          break;
                             }
                             gtt_Ctrl_flag.Calender_init = false; //2008.10.06
                            }
                            else{
                            }
                             break; // Phase8 by @Tny 2008/09/11
                        case 3://カレンダー設定
                              psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Calender_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                              if (psc_Counter_work > 4)
                              {
                                  psc_Counter_work = 4;
                              }
                              if (psc_Counter_work <= 0)
                              {
                                  psc_Counter_work = 0;
                              }
                              gtt_Ctrl_counter.uc_Calender_no = (unsigned char)psc_Counter_work;
                              //if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
                              if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0 || gtt_Ctrl_flag.Calender_init == false) //2008.10.06 カレンダー設定に移る時現在の設定をセットするため。
                              {
                                  gtt_Ctrl_flag.Calender_init = true;
                                  gtt_Ctrl_flag.Calender_set_ready = OFF;
                                  gtt_Ctrl_counter.uc_Year_set_data  = gtt_Calender.uc_Year_data;
                                  gtt_Ctrl_counter.uc_Month_set_data = gtt_Calender.uc_Month_data;
                                  gtt_Ctrl_counter.uc_Day_set_data   = gtt_Calender.uc_Day_data;
                                  gtt_Ctrl_counter.uc_Hour_set_data  = gtt_Calender.uc_Hour_data;
                                  gtt_Ctrl_counter.uc_Mint_set_data  = gtt_Calender.uc_Mint_data;
                              }
                              switch (gtt_Ctrl_counter.uc_Calender_no)
                              {
                                     case 0: //年設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Year_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Counter_work >= 99)
                                            {
                                                psc_Counter_work = 99;
                                            }
                                            if (psc_Counter_work < 1)
                                            {
                                                psc_Counter_work = 1;
                                            }
                                            gtt_Ctrl_counter.uc_Year_set_data = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.Calender_set_ready = ON;
                                                //閏年確認
                                                if (gtt_Ctrl_counter.uc_Year_set_data % 4)
                                                {
                                                    gtt_Calender.Leap_year = OFF;
                                                } else {
                                                    gtt_Calender.Leap_year = ON; //閏年セット
                                                }
                                            }
                                           break;
                                     case 1: //月設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Month_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Counter_work >= 12)
                                            {
                                                psc_Counter_work = 12;
                                            }
                                            if (psc_Counter_work < 1)
                                            {
                                                psc_Counter_work = 1;
                                            }
                                            gtt_Ctrl_counter.uc_Month_set_data = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.Calender_set_ready = ON;
                                            }
                                           break;
                                     case 2: //日設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Day_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            gsc_Day_max_work = 31;
                                            if (gtt_Calender.uc_Month_data == 4 || gtt_Calender.uc_Month_data == 6 || gtt_Calender.uc_Month_data == 9 || gtt_Calender.uc_Month_data == 11)
                                            {
                                                gsc_Day_max_work = 30;
                                            }
                                            if (gtt_Calender.uc_Month_data == 2)
                                            {
                                                if (gtt_Calender.Leap_year == ON)
                                                {
                                                    gsc_Day_max_work = 29;
                                                } else {
                                                    gsc_Day_max_work = 28;
                                                }
                                            }
                                            if (psc_Counter_work >= gsc_Day_max_work)
                                            {
                                                psc_Counter_work = gsc_Day_max_work;
                                            }
                                            if (psc_Counter_work < 1)
                                            {
                                                psc_Counter_work = 1;
                                            }
                                            gtt_Ctrl_counter.uc_Day_set_data = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.Calender_set_ready = ON;
                                            }
                                           break;
                                     case 3: //時設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Hour_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Counter_work >= 23)
                                            {
                                                psc_Counter_work = 23;
                                            }
                                            if (psc_Counter_work < 0)
                                            {
                                                psc_Counter_work = 0;
                                            }
                                            gtt_Ctrl_counter.uc_Hour_set_data = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.Calender_set_ready = ON;
                                            }
                                           break;
                                     case 4: //分設定
                                            psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Mint_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Counter_work >= 59)
                                            {
                                                psc_Counter_work = 59;
                                            }
                                            if (psc_Counter_work < 0)
                                            {
                                                psc_Counter_work = 0;
                                            }
                                            gtt_Ctrl_counter.uc_Mint_set_data = (unsigned char)psc_Counter_work;
                                            if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0)
                                            {
                                                gtt_Ctrl_flag.Calender_set_ready = ON;
                                            }
                                           break;
                              }
                             break; // Phase8 by @Tny 2008/09/11

                        case 4: // エラー履歴
                             psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Error_history_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                             if(psc_Counter_work < 1)       psc_Counter_work = 1;
                             else if(psc_Counter_work > 99) psc_Counter_work = 99;
                             if(gtt_Error_History.Full_history_rec == false){
                                if(psc_Counter_work > gtt_Error_History.History_rec_index){
                                    psc_Counter_work = gtt_Error_History.History_rec_index;
                                }
                             }
                             gtt_Ctrl_counter.uc_Error_history_no = psc_Counter_work;

                             // エラー履歴表示切り替え
                             psc_Flag_work = (signed char)gtt_Ctrl_counter.b_Error_information + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                             if(psc_Flag_work > 0) gtt_Ctrl_counter.b_Error_information = true;
                             else                  gtt_Ctrl_counter.b_Error_information = false;
                             break;
                        case 5: //メモリーコピー 2008.08.29
                           if(guc_Fram_Phase == 0) //2008.11.20
                           {
                             psc_Counter_work = (signed char)gtt_Ctrl_counter.Memory_copy_area_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                             {// Phase3(全面的に改造) 2008/09/05 @Tny
                                 if(psc_Counter_work > MEMORY_COPY_MAX_ITEM){  // >=2 -> >5 -> >define     Phase21 by @Tny 2008/10/02
                                     psc_Counter_work = MEMORY_COPY_MAX_ITEM;  // 2->5->define             Phase21 by @Tny 2008/10/02
                                 }
                                 if(psc_Counter_work < 1){  // <=1 -> <1
                                     psc_Counter_work = 1;
                                 }
                                 gtt_Ctrl_counter.Memory_copy_area_no = psc_Counter_work;   // データ更新
                             }
                             psc_Flag_work = (signed char)gtt_Ctrl_flag.Memory_copy_vector + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                             if (psc_Flag_work >= 1)
                             {
                                 gtt_Ctrl_flag.Memory_copy_vector = true;
                             }
                             if (psc_Flag_work <= 0)
                             {
                                 gtt_Ctrl_flag.Memory_copy_vector = false;
                             }
                             char_set_class(6,"   ",false,false,false); // Phase3 2008/09/05 @Tny
                           }
                             break;
                        case 6: //突き出し長設定 2008.11.10
                             psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Ext_condition_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                             {
                                 if(psc_Counter_work > EXT_CONDITION_MAX_ITEM){
                                     psc_Counter_work = EXT_CONDITION_MAX_ITEM;
                                 }
                                 if(psc_Counter_work < 1){
                                     psc_Counter_work = 1;
                                 }
                                 gtt_Ctrl_flag.Ext_condition_set_ready = ON;
                                 gtt_Ctrl_counter.uc_Ext_condition_data = psc_Counter_work;   // データ更新
                             }

                             break;
                      }
                } else { //技術・サービスマンメニュー

                      switch (gtt_Ctrl_counter.uc_Service_menu_no) //技術・サービスマン入力部
                      {
                        case 0: //サービスマン入力
                             psc_Counter_work = (signed char)gtt_Ctrl_counter.us_Service_data_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                             if (psc_Counter_work >= SERVICE_DATA_NO - 1) //2008.09.04
                             {
                                 psc_Counter_work = SERVICE_DATA_NO - 1; //2008.09.04
                             }
                             if (psc_Counter_work <= 0)
                             {
                                 psc_Counter_work = 0;
                             }
                             gtt_Ctrl_counter.us_Service_data_no = psc_Counter_work;
                             gtt_Special_menu.ss_Service_data[gtt_Ctrl_counter.us_Service_data_no] = gtt_Special_menu.ss_Service_data[gtt_Ctrl_counter.us_Service_data_no] + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2);
                             if (gtt_Special_menu.ss_Service_data[gtt_Ctrl_counter.us_Service_data_no] >= SERVICE_DATA_MAX)
                             {
                                 gtt_Special_menu.ss_Service_data[gtt_Ctrl_counter.us_Service_data_no] = SERVICE_DATA_MAX;
                             }
                             if (gtt_Special_menu.ss_Service_data[gtt_Ctrl_counter.us_Service_data_no] <= SERVICE_DATA_MIN)
                             {
                                 gtt_Special_menu.ss_Service_data[gtt_Ctrl_counter.us_Service_data_no] = SERVICE_DATA_MIN;
                             }
                             break;
                        case 1: //全パラメータリセット
                             psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Service_reset_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
                             if (psc_Counter_work >= 1)
                             {
                                 psc_Counter_work = 1;
                             }
                             if (psc_Counter_work < 0)
                             { 
                                 psc_Counter_work = 0;
                             }
                             gtt_Ctrl_counter.uc_Service_reset_no = psc_Counter_work;
                             switch (gtt_Ctrl_counter.uc_Service_reset_no)
                             {
                                     case 0: //サービスマンリセット
                                            psc_Flag_work = (signed char)gtt_Ctrl_flag.Service_reset1 + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Flag_work >= 1)
                                            {
                                                gtt_Ctrl_flag.Service_reset1 = 1;
                                                gtt_Ctrl_flag.Service_reset2 = 0; //両方が一度にリセットされるのを防ぐ2008.09.04
                                            }
                                            if (psc_Flag_work <= 0)
                                            {
                                                gtt_Ctrl_flag.Service_reset1 = 0;
                                                gtt_Ctrl_flag.Service_reset2 = 0; //片方が１の状態で移動した場合にＮＯの状態で、１の方がリセットされるのを防ぐ2008.09.04
                                            }
                                            break;
                                     case 1: //オールリセット
                                            psc_Flag_work = (signed char)gtt_Ctrl_flag.Service_reset2 + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2;
                                            if (psc_Flag_work >= 1)
                                            {
                                                gtt_Ctrl_flag.Service_reset2 = 1;
                                                gtt_Ctrl_flag.Service_reset1 = 0; //両方が一度にリセットされるのを防ぐ2008.09.04
                                            }
                                            if (psc_Flag_work <= 0)
                                            {
                                                gtt_Ctrl_flag.Service_reset2 = 0;
                                                gtt_Ctrl_flag.Service_reset1 = 0;//片方が１の状態で移動した場合にＮＯの状態で、１の方がリセットされるのを防ぐ2008.09.04
                                            }
                                          break;
                             }
                             break;
                      }
                }
            } else {
                  if(guc_Select_counter == MODE_WELDING && gss_Select_dital[P_CONTROLLER_LOCK] == false && guc_Jog_set_key == false && ((guc_Method_condition_counter != 4)||(gb_ServiceMenu)||(gb_RescueMenu)))
                  {
                      gtt_Ctrl_flag.Param_change = ON; //2008.08.07
                      //***** BP4用に変更 2009.01.13 *****
                      switch (gus_Sequence_set_data) 
                      {
                       	case INIT_WELD_CURRENT_SET_DATA: //初期
						if(gtt_Ctrl_flag.RemoteController == false){
                            if (guc_V_max == OFF) //2009.03.13
                            {
                       		    gtt_Internal_pack.Data.In.usWeldingInitCurr = gtt_Internal_pack.Data.In.usWeldingInitCurr + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); // 出力電流指令値
                            } else {
                                short V_max_work; //2009.03.13
                                V_max_work = gtt_Internal_pack.Data.In.usWeldingInitCurr / 10;
                                gtt_Internal_pack.Data.In.usWeldingInitCurr = V_max_work * 10;
                       		    gtt_Internal_pack.Data.In.usWeldingInitCurr = gtt_Internal_pack.Data.In.usWeldingInitCurr + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); // 出力電流指令値
                            }
                       	    if (gtt_Internal_pack.Data.In.usWeldingInitCurr > gss_Max_current)
                       	    {
        		    			gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
        					}
        					if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                       	    {
        		    			gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
        					}
						}
                            break;
                   		case MAIN_WELD_CURRENT_SET_DATA: //本溶接
						if(gtt_Ctrl_flag.RemoteController == false){
                            if (guc_V_max == OFF) //2009.03.13
                            {
                   			    gtt_Internal_pack.Data.In.usWeldingCurr = gtt_Internal_pack.Data.In.usWeldingCurr + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); // 出力電流指令値
                            } else {
                                short V_max_work; //2009.03.13
                                V_max_work = gtt_Internal_pack.Data.In.usWeldingCurr / 10;
                                gtt_Internal_pack.Data.In.usWeldingCurr = V_max_work * 10;
                       		    gtt_Internal_pack.Data.In.usWeldingCurr = gtt_Internal_pack.Data.In.usWeldingCurr + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); // 出力電流指令値
                            }
                   		    if (gtt_Internal_pack.Data.In.usWeldingCurr > gss_Max_current)
                   		    //if (gtt_Internal_pack.Data.In.usWeldingCurr > 310) //2009.02.10 test
                       	    {
        		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
        		    			//gtt_Internal_pack.Data.In.usWeldingCurr = 310; //2009.02.10 test
        					}
        					if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                       	    {
        		    			gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
        					}
                            gf_Out_current = gtt_Internal_pack.Data.In.usWeldingCurr; //2009.02.20
                            //エキスパートモード リファレンス電圧再セット 2009.03.23
                            gtt_Ctrl_flag.Ref_voltage = OFF;
                            gtt_Ctrl_flag.Ref_voltage_result = OFF;


                            if (guc_Pulse_mode_counter == 1 && gss_Select_dital[P_DETAIL_DISPLAY] == true)
                            {
                                gtt_Ctrl_flag.Pl_pram_jog = ON; //2011.10.03
                            }

						}
                            break;
                       	case CRATER_WELD_CURRENT_SET_DATA: //クレータ
						if(gtt_Ctrl_flag.RemoteController == false){
                            if (guc_V_max == OFF) //2009.03.13
                            {
                       		    gtt_Internal_pack.Data.In.usWeldingCratCurr = gtt_Internal_pack.Data.In.usWeldingCratCurr + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); // 出力電流指令値
                            } else {
                                short V_max_work; //2009.03.13
                                V_max_work = gtt_Internal_pack.Data.In.usWeldingCratCurr / 10;
                                gtt_Internal_pack.Data.In.usWeldingCratCurr = V_max_work * 10;
                       		    gtt_Internal_pack.Data.In.usWeldingCratCurr = gtt_Internal_pack.Data.In.usWeldingCratCurr + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); // 出力電流指令値
                            }
                       	    if (gtt_Internal_pack.Data.In.usWeldingCratCurr > gss_Max_current)
                       	    {
        		    			gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
        					}
        					if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                       	    {
        		    			gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
        					}
						}
                            break;
                        case PREFLOW_SET_DATA: //プリフロー
                       		gtt_Internal_pack.Data.In.sPreFlowTime = gtt_Internal_pack.Data.In.sPreFlowTime + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	    if (gtt_Internal_pack.Data.In.sPreFlowTime > 300) //2009.03.18 100->300
                       	    {
        		    			gtt_Internal_pack.Data.In.sPreFlowTime = 300; //2009.03.18 100->300
        					}
        					if (gtt_Internal_pack.Data.In.sPreFlowTime < 0)
                       	    {
        		    			gtt_Internal_pack.Data.In.sPreFlowTime = 0;
        					}
                            gtt_Ditail_work.us_Pre_flow_time = gtt_Internal_pack.Data.In.sPreFlowTime; //2009.01.28
                            break;
                        case AFTERFLOW_SET_DATA: //アフターフロー
                       		gtt_Internal_pack.Data.In.sAfterFlowTime = gtt_Internal_pack.Data.In.sAfterFlowTime + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	    if (gtt_Internal_pack.Data.In.sAfterFlowTime > 300)
                       	    {
        		    			gtt_Internal_pack.Data.In.sAfterFlowTime = 300;
        					}
        					if (gtt_Internal_pack.Data.In.sAfterFlowTime < 0)
                       	    {
        		    			gtt_Internal_pack.Data.In.sAfterFlowTime = 0;
        					}
                            gtt_Ditail_work.us_After_flow_time = gtt_Internal_pack.Data.In.sAfterFlowTime; //2009.01.28
                            break;
                        case UPSLOP_SET_DATA: //アップスロープ
                       		gtt_Internal_pack.Data.In.sUpSlopTime = gtt_Internal_pack.Data.In.sUpSlopTime + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	    if (gtt_Internal_pack.Data.In.sUpSlopTime > 100)
                       	    {
        		    			gtt_Internal_pack.Data.In.sUpSlopTime = 100;
        					}
        					if (gtt_Internal_pack.Data.In.sUpSlopTime < 0)
                       	    {
        		    			gtt_Internal_pack.Data.In.sUpSlopTime = 0;
        					}
                            break;
                        case DOWNSLOP_SET_DATA: //ダウンスロープ 
                            if (guc_Crater_mode_counter != SEQUENCE_ARC_SPOT) //2009.03.06
                            {
                       		    gtt_Internal_pack.Data.In.sDownSlopTime = gtt_Internal_pack.Data.In.sDownSlopTime + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	        if (gtt_Internal_pack.Data.In.sDownSlopTime > 100)
                       	        {
        		    			    gtt_Internal_pack.Data.In.sDownSlopTime = 100;
        					    }
        					    if (gtt_Internal_pack.Data.In.sDownSlopTime < 0)
                       	        {
        		    			    gtt_Internal_pack.Data.In.sDownSlopTime = 0;
        					    }
                            } else { //2009.03.06
                       		    gtt_Ditail_work.ss_Arc_spot_time = gtt_Ditail_work.ss_Arc_spot_time + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); //2009.03.16 unsigned->signed
                       	        if (gtt_Ditail_work.ss_Arc_spot_time > gtt_Special_menu.ss_Service_data[S_MAX_SPOT_TIME]) //2009.03.16 2009.03.16 unsigned -> signed
                       	        {
        		    			    gtt_Ditail_work.ss_Arc_spot_time = gtt_Special_menu.ss_Service_data[S_MAX_SPOT_TIME]; //2009.03.16 2009.03.16 unsigned -> signed
        					    }
        					    if (gtt_Ditail_work.ss_Arc_spot_time < 1) //2009.03.16 unsigned -> signed 2009.03.18 0->1
                       	        {
        		    			    gtt_Ditail_work.ss_Arc_spot_time = 1; //2009.03.16 unsigned -> signed 2009.03.18 0->1
        					    }
                            }
                            break;
                        case PULSE_ITEM_SET_DATA: //パルス項目設定
                            switch (guc_Pulse_item_counter)
                            {
                                case 1: //パルス電流設定
									if(gtt_Ctrl_flag.RemoteController == false){
                                       if (guc_V_max == OFF) //2009.03.13
                                       {
               	                           gtt_Internal_pack.Data.In.usIP = gtt_Internal_pack.Data.In.usIP + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                                       } else {
                                           short V_max_work; //2009.03.13
                                           V_max_work = gtt_Internal_pack.Data.In.usIP / 10;
                                           gtt_Internal_pack.Data.In.usIP = V_max_work * 10;
                       		               gtt_Internal_pack.Data.In.usIP = gtt_Internal_pack.Data.In.usIP + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1); // 出力電流指令値
                                       }
                       	               if (gtt_Internal_pack.Data.In.usIP > gss_Max_current)
                       	               {
        		    			           gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        					           }
        					           if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                       	               {
        		    			           gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        					           }
									}
                                       gtt_Ctrl_flag.Pl_pram_jog = ON; //2011.10.03
                                       break;
                                case 2: //パルス幅
               	                       gtt_Internal_pack.Data.In.usPulseDuty = gtt_Internal_pack.Data.In.usPulseDuty + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	               if (gtt_Internal_pack.Data.In.usPulseDuty > 95)
                       	               {
        		    			           gtt_Internal_pack.Data.In.usPulseDuty = 95;
        					           }
        					           if (gtt_Internal_pack.Data.In.usPulseDuty < 5)
                       	               {
        		    			           gtt_Internal_pack.Data.In.usPulseDuty = 5;
        					           }
                                       _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty; //2009.02.28 2009.03.27 85->70
                                       gtt_Ctrl_flag.Hpi_control = true; //2009.02.28
                                       gtt_Ctrl_flag.Pl_pram_jog = ON; //2011.10.03
                                       break;
                                case 0: //パルス周波数
                                     { //2009.02.24    0.1-9.9Hz(0.1Hz)  10-99Hz(1Hz)  100-500Hz(10Hz) に変更
                                       short work;
                                   //if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD) //2009.03.02 2009.03.31
                                   //{
                                       if (gtt_Internal_pack.Data.In.usPulseFreq <= 99){
               	                           work = gtt_Internal_pack.Data.In.usPulseFreq + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                                       } else if (gtt_Internal_pack.Data.In.usPulseFreq <= 990){
                                           //一桁目は現れる時（ＪＯＧ高速回し時）に備えた補正。
                                           work = gtt_Internal_pack.Data.In.usPulseFreq / 10; 
                                           work = work * 10;
                                           //
               	                           //work = gtt_Internal_pack.Data.In.usPulseFreq + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * 10;
               	                           work = work + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * 10;
                                           if (work < 100)
                                           {
               	                               work = work + 9; //補正
                                           }
                                       } else {
                                           //一桁目は現れる時（ＪＯＧ高速回し時）に備えた補正。
                                           work = gtt_Internal_pack.Data.In.usPulseFreq / 100; 
                                           work = work * 100;
                                           //
               	                           //work = gtt_Internal_pack.Data.In.usPulseFreq + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * 100;
               	                           work = work + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * 100;
                                           if (work < 1000)
                                           {
               	                               work = work + 90; //補正
                                           }
                                       }
        					           if (work < 1)
                       	               {
        		    			           work = 1;
        					           }
                       	               if (work > 5000)
                       	               {
        		    			           work = 5000;
        					           }
                                   //交流５Hz制限 2009.03.02
#if 0 //2009.03.31 del
                                   } else if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) { //2009.03.02
                                       if (gtt_Internal_pack.Data.In.usPulseFreq <= 50){
               	                           work = gtt_Internal_pack.Data.In.usPulseFreq + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                                       }
        					           if (work < 1)
                       	               {
        		    			           work = 1;
        					           }
                       	               if (work > 50)
                       	               {
        		    			           work = 50;
        					           }
                                   }
#endif
                                       gtt_Internal_pack.Data.In.usPulseFreq = work;
                                       //_union.Nrm.CalParm[69 - 1].c = gtt_Internal_pack.Data.In.usPulseFreq; //パルス周波数反映 2009.03.27
                                       _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10; //パルス周波数反映2009.03.31
                                       gtt_Ctrl_flag.Hpi_control = true; //2009.03.27
                                       gtt_Ctrl_flag.Pl_pram_jog = ON; //2011.10.03
                                   }
                                       break;
                            }
                            break;
                        case AC_TIG_ITEM_SET_DATA:
                                  switch (guc_Ac_tig_set_counter)
                                  {
                                      case 1: //クリーニング幅選択 2009.01.19
               	                       gtt_Internal_pack.Data.In.ucCleaningDuty = gtt_Internal_pack.Data.In.ucCleaningDuty + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	               if (gtt_Internal_pack.Data.In.ucCleaningDuty > 50)
                       	               {
        		    			           gtt_Internal_pack.Data.In.ucCleaningDuty = 50;
        					           }
        					           if (gtt_Internal_pack.Data.In.ucCleaningDuty < 10)
                       	               {
        		    			           gtt_Internal_pack.Data.In.ucCleaningDuty = 10;
        					           }
                                       _union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty; //2009.02.16
                                       gtt_Ctrl_flag.Hpi_control = true; //2009.02.16
                                       break;
                                      case 0: //交流周波数選択
                                       { //2009.02.24    30-199Hz(1Hz)  199-400Hz(10Hz)に変更
                                         short work;
                                         if (gtt_Internal_pack.Data.In.usAcFreq <= 199){
               	                             work = gtt_Internal_pack.Data.In.usAcFreq + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                                         } else if (gtt_Internal_pack.Data.In.usAcFreq >= 200){
                                             //一桁目は現れる時（ＪＯＧ高速回し時）に備えた補正。
                                             work = gtt_Internal_pack.Data.In.usAcFreq / 10; 
                                             work = work * 10;
               	                             work = work + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * 10;
                                             if (work < 200)
                                             {
               	                                 work = work + 9; //補正
                                             }
                                         }
								#if 1 // 2019.08.21
        					             if (work < 10)
                       	                 {
        		    			             work = 10;
        					             }
								#else
        					             if (work < 30)
                       	                 {
        		    			             work = 30;
        					             }
								#endif
								#if 1 // 2019.08.22
                       	                 if (work > 990)
                       	                 {
        		    			             work = 990;
        					             }
								#else
                       	                 if (work > 400)
                       	                 {
        		    			             work = 400;
        					             }
								#endif
                                         gtt_Internal_pack.Data.In.usAcFreq = work;
                                       }
                                       
                                       //_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //ＡＣ周波数反映 2009.03.27
                                       //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq);//2019.03.15 ihara del //ＡＣ周波数の反映 2009.12.29
                                       gtt_Ctrl_flag.Hpi_control = true; //2009.02.16
                                       gtt_Ctrl_flag.Ac_freq_jog = ON; //2010.01.20
                                       break;
                                      default:
                                              break;
                                  }
                            break;
                        case MIX_TIG_ITEM_SET_DATA: //2009.01.20
                                  switch (guc_Mix_tig_set_counter)
                                  {
                                      case 1: //ＭＩＸ周波数選択
               	                       gtt_Internal_pack.Data.In.ucMixFreq = gtt_Internal_pack.Data.In.ucMixFreq + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	               //if (gtt_Internal_pack.Data.In.ucMixFreq > 100)
                       	               if (gtt_Internal_pack.Data.In.ucMixFreq > 200) //2009.07.24
                       	               //if (gtt_Internal_pack.Data.In.ucMixFreq > 50) //2009.02.19 ロード用制限
                       	               {
        		    			           //gtt_Internal_pack.Data.In.ucMixFreq = 100;
        		    			           gtt_Internal_pack.Data.In.ucMixFreq = 200; //2009.07.24
        		    			           //gtt_Internal_pack.Data.In.ucMixFreq = 50; //2009.02.19 ロード用制限
        					           }
        					           if (gtt_Internal_pack.Data.In.ucMixFreq < 1) //2009.03.18 5->1
                       	               {
        		    			           gtt_Internal_pack.Data.In.ucMixFreq = 1; //2009.03.18 5->1
        					           }
                                       //_union.Nrm.CalParm[66 - 1].c = gtt_Internal_pack.Data.In.ucMixFreq; //ＭＩＸ周波数反映 2009.03.27
                                       _union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10; //ＭＩＸ周波数反映 2009.03.31
                                       gtt_Ctrl_flag.Hpi_control = true; //2009.02.16
                                       break;
                                      case 0: //直流比率選択
               	                       gtt_Internal_pack.Data.In.ucMixAcRatio = gtt_Internal_pack.Data.In.ucMixAcRatio + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                       	               if (gtt_Internal_pack.Data.In.ucMixAcRatio > 90)
                       	               {
        		    			           gtt_Internal_pack.Data.In.ucMixAcRatio = 90;
        					           }
        					           if (gtt_Internal_pack.Data.In.ucMixAcRatio < 10)
                       	               {
        		    			           gtt_Internal_pack.Data.In.ucMixAcRatio = 10;
        					           }
                                       _union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio; //ＭＩＸ比率反映 2009.03.27
                                       gtt_Ctrl_flag.Hpi_control = true; //2009.02.16
                                       break;
                                      default:
                                              break;
                                  }
                            break;
                        case NO_SET_DATA:
                            break;
                        default:
                            break;
                      }

                      if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK))
                      {
                	      gus_Pre_display_timer = 300; //2007.12.10
                      }
        
                    }

//--------------------------------------------------------------------
//BP4 Phase15 by @Tny 2009.02.25
					if((gb_ServiceMenu == false)&&(gb_RescueMenu == false)){
//--------------------------------------------------------------------
                    if (guc_Method_condition_counter == 4) //ナビモード選択
                    {
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	// <NAVI Enhancements(Phase 2)> 2011.10.27
	#if true
						if((gtt_Ctrl_flag.RemoteController == false)&&(gb_IIF_Select == false)){	// リモコン、およびＩＩＦは接続されていない？
	#else
						if(gtt_Ctrl_flag.RemoteController == false){
	#endif
	//-----------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------
                        gtt_Navi.sc_Jog_counter = gtt_Navi.sc_Jog_counter + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
                        if (gtt_Navi.sc_Jog_counter <= 0)
                        {
                            gtt_Navi.sc_Jog_counter = 0;
                        }
                        if (gtt_Navi.sc_Jog_counter >= 20) //2010.01.20 19->20
                        {
                            gtt_Navi.sc_Jog_counter = 20;  //2010.01.20 19->20
                        }
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
						}
//---------------------------------------
                    }
//--------------------------------------------------------------------
//BP4 Phase15 by @Tny 2009.02.25
					}
//--------------------------------------------------------------------
                    

                    // BP4 Phase3 by @Tny 2009.01.13
                    if (guc_Select_counter == MODE_DETAILS)	// BP4 Phase6 by @Tny 2009/01/27
                    {
						gb_2Line_FirstDisplay		= false;// 初回二行目表示フラグをＯＦＦ	BP4 Phase3 by @Tny 2009.01.15



//---------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23	BP4 Phase14 by @Tny 2009.02.24
						if((gb_ServiceMenu)||(gb_RescueMenu)){
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.12
						if(gus_MessageTimer <= 0){	// メッセージ表示時間が経過?
//--------------------------------------------------------------------
							if(guc_Menu_Hierarchy == 0){ // サービスマン・メニュー設定階層フラグが詳細設定項目の選択（＝０）？   【直値指定注意！！】
								if(gsc_Select_dital_counter == 0){
									// パスワード入力処理
									//StringInput_Rcv(false, false, gt_SelectCharacter, 16);	// 文字入力処理（入力部）
									if(gb_ServiceMenu) StringInput_Rcv(false, false, gt_SelectCharacter, 16);	// 文字入力処理（入力部）2009.04.06
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
									gb_RescueOpeningDisp = false;		// レスキュー・メニューのオープニング画面の表示要求：クリア
//--------------------------------------------------------------------
                                    if (gb_RescueMenu) guc_StringInput = 2; //2009.04.06
									if(guc_StringInput == 2){ // 文字入力処理が終了した？
										gt_SelectCharacter[gus_InputCharIndex] = 0x00;	// NULLコードセット
										//if(strcomp((unsigned char *)gt_SelectCharacter, (unsigned char *)"610854")){// 入力パスワードの確認
										if(strcomp((unsigned char *)gt_SelectCharacter, (unsigned char *)"610854") || gb_RescueMenu){// 入力パスワードの確認
											gsc_Select_dital_counter 	= 1;	// 詳細メニュー設定階層フラグ
											gus_MessageTimer			= 30;	// メッセージ表示時間（１００ｍ秒単位）：３秒
										}
										else{
											InitialStringInput(true, true, "");	// 文字入力処理の初期化
											guc_StringInput				= 1;	// 文字列入力処理実行中
											gus_MessageTimer			= 30;	// メッセージ表示時間（１００ｍ秒単位）：３秒
										}
									}
								}
								else{
			                        gsc_Select_dital_counter = gsc_Select_dital_counter + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
									if(gb_ServiceMenu){
										if(gsc_Select_dital_counter >= SERVICE_DATA_NO){	//サービスマン・メニュー選択用の最大値
											gsc_Select_dital_counter = (SERVICE_DATA_NO - 1);
										}
									}
									if(gb_RescueMenu){
										if(gsc_Select_dital_counter >= RESCUE_DATA_NO){	// レスキュー・メニュー選択用の最大値
											gsc_Select_dital_counter = (RESCUE_DATA_NO - 1);
										}
									}
									if(gsc_Select_dital_counter < 1){
										gsc_Select_dital_counter = 1;
									}
								}
							}
							else{
								if(gb_ServiceMenu){
//-----------------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.10
									gtt_Ctrl_flag.Param_change = ON;
//-----------------------------------------------------------------------------
									gtt_Special_menu.ss_Service_data[gsc_Select_dital_counter] = gtt_Special_menu.ss_Service_data[gsc_Select_dital_counter] + ((signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * gtt_Service_attribute[gsc_Select_dital_counter].ss_Notch);
									if(gtt_Special_menu.ss_Service_data[gsc_Select_dital_counter] < gtt_Service_attribute[gsc_Select_dital_counter].ss_Min){
										gtt_Special_menu.ss_Service_data[gsc_Select_dital_counter] = gtt_Service_attribute[gsc_Select_dital_counter].ss_Min;
									}
									if(gtt_Special_menu.ss_Service_data[gsc_Select_dital_counter] > gtt_Service_attribute[gsc_Select_dital_counter].ss_Max){
										gtt_Special_menu.ss_Service_data[gsc_Select_dital_counter] = gtt_Service_attribute[gsc_Select_dital_counter].ss_Max;
									}
								}
								else if((gb_RescueMenu)&&(gb_RamAllClear == false)){	// レスキュー・メニュー（オールクリア直後ではない？）
									if(gsc_Select_dital_counter == 1){	// エラー履歴
										psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Error_history_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
										if(psc_Counter_work < 1)       psc_Counter_work = 1;
										else if(psc_Counter_work > 99) psc_Counter_work = 99;
										if(gtt_Error_History.Full_history_rec == false){
											if(psc_Counter_work > gtt_Error_History.History_rec_index){
												psc_Counter_work = gtt_Error_History.History_rec_index;
											}
										}
										gtt_Ctrl_counter.uc_Error_history_no = psc_Counter_work;
									}
									else{
//-----------------------------------------------------------------------------
// BP4 by @Tny 2009.04.08
										gtt_Ctrl_flag.Param_change = ON;
//-----------------------------------------------------------------------------
										gtt_Special_menu.ss_Rescue_data[gsc_Select_dital_counter] = gtt_Special_menu.ss_Rescue_data[gsc_Select_dital_counter] + ((signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * gtt_Rescue_attribute[gsc_Select_dital_counter].ss_Notch);
										if(gtt_Special_menu.ss_Rescue_data[gsc_Select_dital_counter] < gtt_Rescue_attribute[gsc_Select_dital_counter].ss_Min){
											gtt_Special_menu.ss_Rescue_data[gsc_Select_dital_counter] = gtt_Rescue_attribute[gsc_Select_dital_counter].ss_Min;
										}
										if(gtt_Special_menu.ss_Rescue_data[gsc_Select_dital_counter] > gtt_Rescue_attribute[gsc_Select_dital_counter].ss_Max){
											gtt_Special_menu.ss_Rescue_data[gsc_Select_dital_counter] = gtt_Rescue_attribute[gsc_Select_dital_counter].ss_Max;
										}
									}
								}
							}
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.12
						}
//--------------------------------------------------------------------
						}
						else{
//---------------------------------------------------

//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.21
#if true
                        gtt_Ctrl_flag.Param_change 	= ON;
						if(guc_Menu_Hierarchy == 0){ // 詳細メニュー設定階層フラグが詳細設定項目の選択（＝０）？   【直値指定注意！！】	BP3 Phase2 @Tny 2009.01.13
//--------------------------------
// < IIF NEW > 2009.11.26 @Tny
							char	psc_Select_dital_counter = gsc_Select_dital_counter;
//--------------------------------
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
							char	psc_PassIIF_counter;
						    if(gb_IIF_Select == true)	psc_PassIIF_counter = P_IIF_SELECT;
							else						psc_PassIIF_counter = P_DETAIL_DISPLAY;
//-------------------------------------------------
							psc_PassIIF_counter = P_EXTARNAL_LEVEL_C;	// 2019.08.21
//-------------------------------------------------

							//-----------------------------------------------
							// BP4 Phase7 by @Tny 2009.02.12
	                        if(gsc_Select_dital_counter != P_WELD_NAME){	// 溶接条件名の入力／編集モード？
								gb_RecWeldCond = true;			// 記憶条件データの有無
							}
							//-----------------------------------------------
	                        gsc_Select_dital_counter = gsc_Select_dital_counter + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
	                        if (gtt_Ctrl_flag.Dital_pass_lock == false)
	                        {
	                            //if (gsc_Select_dital_counter > SELECT_DITAL_MAX)	//詳細メニュー選択用の最大値
	                            if (gsc_Select_dital_counter > psc_PassIIF_counter)	//詳細メニュー選択用の最大値 // <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
	                            //if (gsc_Select_dital_counter > 24)	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20  2011.09.30 21->23	<IIF NEW> 2011.10.07 23->24
	                            //if (gsc_Select_dital_counter > 23)	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20  2011.09.30 21->23
	                            //if (gsc_Select_dital_counter > 21)	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20
	                            //if (gsc_Select_dital_counter > 20)	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20
	                            //if (gsc_Select_dital_counter > 18)	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18
	                            //if (gsc_Select_dital_counter > 17)	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17
	                            //if (gsc_Select_dital_counter > 16)	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16
	                            //if (gsc_Select_dital_counter > 15)	//詳細メニュー選択用の最大値 取り説と合わないため可変反復削除2009.03.18
	                            {
	                                //gsc_Select_dital_counter = SELECT_DITAL_MAX;	//詳細メニュー選択用の最大値
	                                gsc_Select_dital_counter = psc_PassIIF_counter;	//詳細メニュー選択用の最大値 // <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
	                                //gsc_Select_dital_counter = 24;	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20   2011.09.30 21->23	<IIF NEW> 2011.10.07 23->24
	                                //gsc_Select_dital_counter = 23;	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20   2011.09.30 21->23
	                                //gsc_Select_dital_counter = 21;	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20
	                                //gsc_Select_dital_counter = 20;	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18	2010.01.20 18->20
	                                //gsc_Select_dital_counter = 18;	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17	2010.01.08 17->18
	                                //gsc_Select_dital_counter = 17;	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16 2010.01.08 16->17
	                                //gsc_Select_dital_counter = 16;	//詳細メニュー選択用の最大値 2009.03.07現在15項目に限定 2009.03.16 15->16
	                                //gsc_Select_dital_counter = 15;	//詳細メニュー選択用の最大値　取り説と合わないため可変反復削除2009.03.18
	                            }
	                        } else {
	                            if (gsc_Select_dital_counter > P_INPUT_PASS_WORD)
	                            {
	                                gsc_Select_dital_counter = P_INPUT_PASS_WORD;
	                            }
	                        }
	                        if (gsc_Select_dital_counter < 0)
	                        {
	                            gsc_Select_dital_counter = 0;
	                        }
						}
						else{
							// BP4 Phase4 by @Tny 2009.01.15
	                        if(gsc_Select_dital_counter == P_NOW_DATE_TIME){	// 現在日時設定モード？
								if(guc_Menu_Hierarchy == 1){ // 詳細メニュー設定階層フラグが詳細設定項目の選択（＝１）？
		                            psc_Counter_work = (signed char)gss_Select_dital[P_NOW_DATE_TIME] + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
		                            if (psc_Counter_work > 5)
		                            {
		                                psc_Counter_work = 5;
		                            }
		                            if (psc_Counter_work <= 0)
		                            {
		                                psc_Counter_work = 0;
		                            }
		                            gtt_Ctrl_counter.uc_Calender_no = gss_Select_dital[P_NOW_DATE_TIME] = (unsigned char)psc_Counter_work;
		                            if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0 || gtt_Ctrl_flag.Calender_init == false) // カレンダー設定に移る時現在の設定をセットするため。
		                            {
		                                gtt_Ctrl_flag.Calender_init = true;
		                                gtt_Ctrl_flag.Calender_set_ready = OFF;
		                                gtt_Ctrl_counter.uc_Year_set_data  = gtt_Calender.uc_Year_data;
		                                gtt_Ctrl_counter.uc_Month_set_data = gtt_Calender.uc_Month_data;
		                                gtt_Ctrl_counter.uc_Day_set_data   = gtt_Calender.uc_Day_data;
		                                gtt_Ctrl_counter.uc_Hour_set_data  = gtt_Calender.uc_Hour_data;
		                                gtt_Ctrl_counter.uc_Mint_set_data  = gtt_Calender.uc_Mint_data;
		                            }
									gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
								}
								else{
		                            switch (gss_Select_dital[P_NOW_DATE_TIME])
		                            {
		                                   case 0: //年設定
		                                          psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Year_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
		                                          if (psc_Counter_work >= 99)
		                                          {
		                                              psc_Counter_work = 99;
		                                          }
		                                          if (psc_Counter_work < 1)
		                                          {
		                                              psc_Counter_work = 1;
		                                          }
		                                          gtt_Ctrl_counter.uc_Year_set_data = (unsigned char)psc_Counter_work;
		                                          if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
		                                          {
		                                              gtt_Ctrl_flag.Calender_set_ready = ON;
		                                              //閏年確認
		                                              if (gtt_Ctrl_counter.uc_Year_set_data % 4)
		                                              {
		                                                  gtt_Calender.Leap_year = OFF;
		                                              } else {
		                                                  gtt_Calender.Leap_year = ON; //閏年セット
		                                              }
		                                          }
		                                         break;
		                                   case 1: //月設定
		                                          psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Month_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
		                                          if (psc_Counter_work >= 12)
		                                          {
		                                              psc_Counter_work = 12;
		                                          }
		                                          if (psc_Counter_work < 1)
		                                          {
		                                              psc_Counter_work = 1;
		                                          }
		                                          gtt_Ctrl_counter.uc_Month_set_data = (unsigned char)psc_Counter_work;
		                                          if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
		                                          {
		                                              gtt_Ctrl_flag.Calender_set_ready = ON;
		                                          }
		                                         break;
		                                   case 2: //日設定
		                                          psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Day_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
		                                          gsc_Day_max_work = 31;
		                                          if (gtt_Calender.uc_Month_data == 4 || gtt_Calender.uc_Month_data == 6 || gtt_Calender.uc_Month_data == 9 || gtt_Calender.uc_Month_data == 11)
		                                          {
		                                              gsc_Day_max_work = 30;
		                                          }
		                                          if (gtt_Calender.uc_Month_data == 2)
		                                          {
		                                              if (gtt_Calender.Leap_year == ON)
		                                              {
		                                                  gsc_Day_max_work = 29;
		                                              } else {
		                                                  gsc_Day_max_work = 28;
		                                              }
		                                          }
		                                          if (psc_Counter_work >= gsc_Day_max_work)
		                                          {
		                                              psc_Counter_work = gsc_Day_max_work;
		                                          }
		                                          if (psc_Counter_work < 1)
		                                          {
		                                              psc_Counter_work = 1;
		                                          }
		                                          gtt_Ctrl_counter.uc_Day_set_data = (unsigned char)psc_Counter_work;
		                                          if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
		                                          {
		                                              gtt_Ctrl_flag.Calender_set_ready = ON;
		                                          }
		                                         break;
		                                   case 3: //時設定
		                                          psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Hour_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
		                                          if (psc_Counter_work >= 23)
		                                          {
		                                              psc_Counter_work = 23;
		                                          }
		                                          if (psc_Counter_work < 0)
		                                          {
		                                              psc_Counter_work = 0;
		                                          }
		                                          gtt_Ctrl_counter.uc_Hour_set_data = (unsigned char)psc_Counter_work;
		                                          if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
		                                          {
		                                              gtt_Ctrl_flag.Calender_set_ready = ON;
		                                          }
		                                         break;
		                                   case 4: //分設定
		                                          psc_Counter_work = (signed char)gtt_Ctrl_counter.uc_Mint_set_data + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
		                                          if (psc_Counter_work >= 59)
		                                          {
		                                              psc_Counter_work = 59;
		                                          }
		                                          if (psc_Counter_work < 0)
		                                          {
		                                              psc_Counter_work = 0;
		                                          }
		                                          gtt_Ctrl_counter.uc_Mint_set_data = (unsigned char)psc_Counter_work;
		                                          if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0)
		                                          {
		                                              gtt_Ctrl_flag.Calender_set_ready = ON;
		                                          }
		                                         break;
		                            }
								}
							}
	                        else if(gsc_Select_dital_counter == P_WELD_NAME){	// 溶接条件名の入力／編集モード？	Phase5 by @Tny 2009.01.22
								if(guc_Menu_Hierarchy == 1){ // 詳細メニュー設定階層フラグが詳細設定項目の選択（＝１）？
									if(guc_Controller_lock == false || gsc_Select_dital_counter >= P_INPUT_PASS_WORD){
										short	pss_Select_dital = gss_Select_dital[gsc_Select_dital_counter];	// BP4 Phase7 by @Tny 2009-02-12
										gss_Select_dital[gsc_Select_dital_counter] = gss_Select_dital[gsc_Select_dital_counter] + ((signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * gtt_Dital_attribute[gsc_Select_dital_counter].ss_Notch);
										if(gss_Select_dital[gsc_Select_dital_counter] < gtt_Dital_attribute[gsc_Select_dital_counter].ss_Min){
											gss_Select_dital[gsc_Select_dital_counter] = gtt_Dital_attribute[gsc_Select_dital_counter].ss_Min;
										}
										if(gss_Select_dital[gsc_Select_dital_counter] > gtt_Dital_attribute[gsc_Select_dital_counter].ss_Max){
											gss_Select_dital[gsc_Select_dital_counter] = gtt_Dital_attribute[gsc_Select_dital_counter].ss_Max;
										}
										FOREVER{
											if(guc_Write_check_flag_ch[gss_Select_dital[gsc_Select_dital_counter]] == true){	// 対象番号には記憶条件データが有る？
												break;
											}
											else{	// 対象番号に記憶条件データが無い場合は、次の番号の記憶条件データを検索する
												if((signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) > 0) gss_Select_dital[gsc_Select_dital_counter] = gss_Select_dital[gsc_Select_dital_counter] + gtt_Dital_attribute[gsc_Select_dital_counter].ss_Notch;
												else																	gss_Select_dital[gsc_Select_dital_counter] = gss_Select_dital[gsc_Select_dital_counter] - gtt_Dital_attribute[gsc_Select_dital_counter].ss_Notch;
												if(gss_Select_dital[gsc_Select_dital_counter] < gtt_Dital_attribute[gsc_Select_dital_counter].ss_Min){
													gss_Select_dital[gsc_Select_dital_counter] = pss_Select_dital;	// BP4 Phase7 by @Tny 2009-02-12
//													gss_Select_dital[gsc_Select_dital_counter] = gtt_Dital_attribute[gsc_Select_dital_counter].ss_Max;
												}
												if(gss_Select_dital[gsc_Select_dital_counter] > gtt_Dital_attribute[gsc_Select_dital_counter].ss_Max){
													gss_Select_dital[gsc_Select_dital_counter] = pss_Select_dital;	// BP4 Phase7 by @Tny 2009-02-12
//													gss_Select_dital[gsc_Select_dital_counter] = gtt_Dital_attribute[gsc_Select_dital_counter].ss_Min;
												}
											}
										}
										// BP4 Phase5 by @Tny 要ＦＲＡＭエリアからの読み込み処理
										InitialStringInput(false, false, (const char *)gt_WeldCondName[gss_Select_dital[gsc_Select_dital_counter]]);	// 文字入力処理の初期化	BP4 Phase13 by @Tny 2009.02.23
									}
								}
								else{
									StringInput_Rcv(false, false, gt_SelectCharacter, 16);	// 文字入力処理（入力部）
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
									gb_RescueOpeningDisp = false;		// レスキュー・メニューのオープニング画面の表示要求：クリア
//--------------------------------------------------------------------
									if(guc_StringInput == 2){ // 文字入力処理が終了した？
										// BP4 Phase5 by @Tny 要ＦＲＡＭエリアへの記憶処理
										strcpy((char *)gt_WeldCondName[gss_Select_dital[gsc_Select_dital_counter]], (const char *)gt_SelectCharacter);		// 条件名文字列データ格納エリアへ入力文字列をコピー
										gb_WeldCondNameWrite	= true;	// 溶接条件名書き込み要求フラグ	// BP4 Phase6 by @Tny 2009/01/27
										guc_Menu_Hierarchy		= 1;	// 詳細メニュー設定階層フラグ
									}
								}
							}
//--------------------------------
// < IIF NEW > 2009.11.18 @Tny
	                        else if(gsc_Select_dital_counter == P_IIF_SELECT){	// ＩＩＦ設定モード？
								gtt_Ctrl_flag.Param_change = OFF; // 設定内容非保存
								if(guc_Menu_Hierarchy == 1){ // 詳細メニュー設定階層フラグが詳細設定項目の選択（＝１）？
									short	pss_Select_dital = gss_Select_dital[P_IIF_SELECT];
		                            pss_Select_dital = (signed char)pss_Select_dital + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
									if(pss_Select_dital < 0) 		pss_Select_dital = 0;
									else if(pss_Select_dital > 5)	pss_Select_dital = 5;
									gss_Select_dital[P_IIF_SELECT]	= pss_Select_dital;
								}
								else if(guc_Menu_Hierarchy == 2){ // 詳細メニュー設定階層フラグが詳細設定項目の選択（＝２）？
									short	pss_Select_dital = gus_Iif_Set_Menu;
									short	pss_Select_Max = 0;
									switch(gss_Select_dital[P_IIF_SELECT]){
										case 0:{pss_Select_Max = 9;  break;} // デジタル出力設定：８ポート		//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす					2011.10.07 by @Tny
										case 1:{pss_Select_Max = 10; break;} // デジタル入力設定：９ポート		//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny	// 10->9ポート	<EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
										case 2:{pss_Select_Max = 4;  break;} // アナログ入力設定：３ポート		//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす					2011.10.07 by @Tny
										case 3:{pss_Select_Max = 1;  break;} // 設定確定確認　　：２択
									}
		                            pss_Select_dital = (signed char)pss_Select_dital + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
									if(pss_Select_dital < 1) 					pss_Select_dital = 1;	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす	2011.10.07 by @Tny
									else if(pss_Select_dital >= pss_Select_Max)	pss_Select_dital = pss_Select_Max;
									gus_Iif_Set_Menu = pss_Select_dital;
									switch(gss_Select_dital[P_IIF_SELECT]){ // ポート番号選択状態？
										case 0:{gtt_Ctrl_counter.uc_Out_port_no		= gus_Iif_Set_Menu; break;}	// 出力ポート番号
										case 1:{gtt_Ctrl_counter.uc_In_port_no		= gus_Iif_Set_Menu; break;}	// 入力ポート番号
										case 2:{gtt_Ctrl_counter.uc_Analog_port_no	= gus_Iif_Set_Menu; break;}	// アナログ入力ポート番号
									}
								}
								else if(guc_Menu_Hierarchy == 3){ // 詳細メニュー設定階層フラグが詳細設定項目の選択（＝３）？
									short	pss_Select_dital = gus_Iif_Set_Dital;
									short	pss_Select_Max = 0;
									switch(gss_Select_dital[P_IIF_SELECT]){
										case 0:{pss_Select_Max = 11; break;} // デジタル出力設定：１０種類
										case 1:{pss_Select_Max = 15; break;} // デジタル入力設定：１４種類	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
										case 2:{pss_Select_Max = 10; break;} // アナログ入力設定：　９種類
									}
		                            pss_Select_dital = (signed char)pss_Select_dital + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
									if(pss_Select_dital < 0) 					pss_Select_dital = 0;
									else if(pss_Select_dital >= pss_Select_Max)	pss_Select_dital = (pss_Select_Max - 1);
									//
									// 機能多重設定防止処理（デジタル入力とアナログ入力のみ）
									//
									if(pss_Select_dital > 0){
										switch(gss_Select_dital[P_IIF_SELECT]){
											case 1:{ // デジタル入力設定
													short	i;
													for(i=1;i<=10;i++){	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
														if((i != gtt_Ctrl_counter.uc_In_port_no)&&(guc_In_port[0][i] == pss_Select_dital)&&(guc_In_port[0][i] != 0)){
															if(pss_Select_dital == (pss_Select_Max - 1))	pss_Select_dital = (pss_Select_Max - 2);
															else 											pss_Select_dital = (signed char)pss_Select_dital + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
															i = -1;	// 再確認
														}
													}
													break;}
											case 2:{ // アナログ入力設定
													short	i;
													for(i=1;i<=3;i++){
														if((i != gtt_Ctrl_counter.uc_Analog_port_no)&&(guc_Analog_port[0][i] == pss_Select_dital)&&(guc_Analog_port[0][i] != 0)){
															if(pss_Select_dital == (pss_Select_Max - 1))	pss_Select_dital = (pss_Select_Max - 2);
															else											pss_Select_dital = (signed char)pss_Select_dital + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
															i = -1;	// 再確認
														}
													}
													break;}
										}
										if(pss_Select_dital < 0) 					pss_Select_dital = 0;
										else if(pss_Select_dital >= pss_Select_Max)	pss_Select_dital = (pss_Select_Max - 1);
									}
									gus_Iif_Set_Dital = pss_Select_dital;
								}
								else if(guc_Menu_Hierarchy == 4){ // 詳細メニュー設定階層フラグが詳細設定項目の選択（＝４）？
									short	pss_Select_dital = gus_Iif_PortContact;
		                            pss_Select_dital = (signed char)pss_Select_dital + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;
									if(pss_Select_dital < 0) 		pss_Select_dital = 0;
									else if(pss_Select_dital > 1)	pss_Select_dital = 1;
									gus_Iif_PortContact	= pss_Select_dital;
								}
							}
// < IIF NEW > 2009.11.18 @Tny
//--------------------------------
							 else { //2009.02.19
	                            if (guc_Controller_lock == false || gsc_Select_dital_counter >= P_INPUT_PASS_WORD)
	                            {
	                                gss_Select_dital[gsc_Select_dital_counter] = gss_Select_dital[gsc_Select_dital_counter] + ((signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1) * gtt_Dital_attribute[gsc_Select_dital_counter].ss_Notch);
	                            }
	                            if (gss_Select_dital[gsc_Select_dital_counter] < gtt_Dital_attribute[gsc_Select_dital_counter].ss_Min)
	                            {
	                                gss_Select_dital[gsc_Select_dital_counter] = gtt_Dital_attribute[gsc_Select_dital_counter].ss_Min;
	                            }
	                            if (gss_Select_dital[gsc_Select_dital_counter] > gtt_Dital_attribute[gsc_Select_dital_counter].ss_Max)
	                            {
	                                gss_Select_dital[gsc_Select_dital_counter] = gtt_Dital_attribute[gsc_Select_dital_counter].ss_Max;
	                            }
//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
#if true
								if(gsc_Select_dital_counter == P_LCD_BRIGHT){
									 if(guc_Lcd_Bright != gss_Select_dital[P_LCD_BRIGHT]){
									 	guc_Lcd_Bright		= gss_Select_dital[P_LCD_BRIGHT];
										gb_LcdBrightWrite	= true;	// ＬＣＤコントラスト値の記録の要求
									 }
								}
#endif
//-----------------------------------------------------------

	                        }
						}

                        //<><><><> 出力制限の反映 2010.01.12 <><><><>
                        if (gsc_Select_dital_counter == P_MAX_OUTPUT)
                        {
		                    if(gtt_Ctrl_flag.RemoteController)
                            {
                               gus_RemoInput[5] = 2048;
                               gus_RemoInput[6] = 2048;
                               gus_RemoInput[7] = 2048;
                               gus_RemoInput[8] = 2048;
                            }
                            switch (guc_Method_condition_data)
                            {
                                    case STD_DC_METHOD:
                                    case STD_MIX_METHOD:
                                    case EXP_DC_METHOD:
                                    case EXP_AC_METHOD:
                                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                                         {
                                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                                         } else {
                                             MAX_CURRENT = MAX_CURRENT_VAL;
                                         }
                                         break;
                                    case STD_AC_METHOD:
                                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                                         {
                                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                                         } else {
                                             MAX_CURRENT = MAX_CURRENT_VAL;
                                         }
                                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_AC_SOFT_VAL)
                                         {
                                             MAX_CURRENT_AC_SOFT = gss_Select_dital[P_MAX_OUTPUT];
                                         } else {
                                             MAX_CURRENT_AC_SOFT = MAX_CURRENT_AC_SOFT_VAL;
                                         }
                                         break;
                                    case STD_HAND_METHOD:
                                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_HAND_VAL)
                                         {
                                             MAX_CURRENT_HAND = gss_Select_dital[P_MAX_OUTPUT];
                                         } else {
                                             MAX_CURRENT_HAND = MAX_CURRENT_HAND_VAL;
                                         }
                                         break;
                                    default:
                                         if (gss_Select_dital[P_MAX_OUTPUT] < MAX_CURRENT_VAL)
                                         {
                                             MAX_CURRENT = gss_Select_dital[P_MAX_OUTPUT];
                                         } else {
                                             MAX_CURRENT = MAX_CURRENT_VAL;
                                         }
                                         break;
                            }
                            //**** 制限電流セット 2009.02.19 *****************************************
                        	if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
                        	{
                            	gss_Max_current = MAX_CURRENT;
                            	gss_Min_current = MIN_CURRENT;
                        	}
                        	if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
                        	{
                            	gss_Max_current = MAX_CURRENT;
                            	gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            	//***** 2009.03.13 *****
                    			if (guc_Ac_wave_counter == 1) //ハードＡＣ 
                            	{
                                	gss_Max_current = MAX_CURRENT;
                                	gss_Min_current = MIN_CURRENT_AC_HARD; //2011.09.30
                            	}
                    			if (guc_Ac_wave_counter == 2) //ソフトＡＣ 
                            	{
                                	gss_Max_current = MAX_CURRENT_AC_SOFT;
                                	gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            	}
                            	//**********************
                        	}
                        	if (guc_Method_condition_data == STD_MIX_METHOD) //2009.03.17
                        	{
                            	gss_Max_current = MAX_CURRENT;
                            	gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                        	}
                        
                        	if (guc_Method_condition_data == STD_HAND_METHOD) //2009.03.06
                        	{
                            	gss_Max_current = MAX_CURRENT_HAND;
                            	gss_Min_current = MIN_CURRENT_HAND;
                        	}
                        
                        	//************************************************************************

                        }
                        //<><><><><><><><><><><><><><><><><><><><><><>



                        //P80 2008.10.17 スタート電圧
                        //パスワードの書き換え
                        if (gsc_Select_dital_counter == P_CHENGE_PASS_WORD) //2008.09.10
                        {
                            guc_Pass_word = gss_Select_dital[gsc_Select_dital_counter];
                        }
                        //コントローラロック
                        if (gsc_Select_dital_counter == P_CONTROLLER_LOCK) //2008.09.10
                        {
                            guc_Controller_lock = gss_Select_dital[gsc_Select_dital_counter];
                        }
//---------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23
						}
//---------------------------------------------------
#endif
//-----------------------------------------------------------------------------
					}

                    //再生・記憶ｃｈ設定部 2008.08.07
                    if (guc_Select_counter == MODE_RECORD && gtt_Ctrl_flag.Rec_display == ON)	// BP4 Phase6 by @Tny 2009/01/27
                    {
					  if(ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0){	// Jog2->Jog1 BP4 Phase5 by @Tny 2009.01.22
//-------------------------------------------------
// BP4 Phase7 by @Tny 2009-02-13
						ubool	bYes = gtt_Ctrl_flag.Yes;
						ubool	bDel = gtt_Ctrl_flag.Del;
                        psc_Flag_work = (signed char)gtt_Ctrl_flag.Yes + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;	// Jog2->Jog1 BP4 Phase5 by @Tny 2009.01.22
                        if(psc_Flag_work >= 2){										// YES->DEL
                            gtt_Ctrl_flag.Yes = 0;
                            gtt_Ctrl_flag.Del = 1;
                        }
                        else if((psc_Flag_work == 1)&&(gtt_Ctrl_flag.Del == 0)){	// no->YES
                            gtt_Ctrl_flag.Yes = 1;
                            gtt_Ctrl_flag.Del = 0;
                        }
                        else if((psc_Flag_work < 0)&&(gtt_Ctrl_flag.Del == 1)){		// DEL->YES
                            gtt_Ctrl_flag.Yes = 1;
                            gtt_Ctrl_flag.Del = 0;
                        }
                        else if(psc_Flag_work <= 0){								// YES->no
                            gtt_Ctrl_flag.Yes = 0;
                            gtt_Ctrl_flag.Del = 0;
                        }
						if((bYes != gtt_Ctrl_flag.Yes) || (bDel != gtt_Ctrl_flag.Del)){	// ７セグＬＥＤ表示に変化があればＬＣＤの表示も変更する
							gb_2Line_FirstDisplay		= false;// 初回二行目表示フラグをＯＦＦ
						}
//-------------------------------------------------
					  }
                    }
                    if ((guc_Select_counter == MODE_PLAY) && (gtt_Ctrl_flag.Rec_display == OFF))	// BP4 Phase6 by @Tny 2009/01/27
                    {
                        if ((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1 > 0) //JOG +	// Jog2->Jog1 BP4 Phase5 by @Tny 2009.01.22
                        {
                            if (guc_Ch_no >= 0) puc_Index = guc_Ch_no + 1;
                            for (puc_Index ; puc_Index <= CH - 1 ; puc_Index++)
                            {
                                 if (guc_Write_check_flag[puc_Index] == true)
                                 {
                                     guc_Ch_no = puc_Index;
//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.22
									// BP4 Phase5 by @Tny 要ＦＲＡＭエリアからの読み込み処理
									 strcpy((char *)gt_SelectCharacter, (const char *)gt_WeldCondName[guc_Ch_no]);			// 既に設定されている文字列（初期文字列）の転送
									 gus_InputCharIndex	= (unsigned short)strlen((const char *)gt_WeldCondName[guc_Ch_no]);	// 入力文字位置インデックス
									 gt_SelectCharacter[gus_InputCharIndex] = 0x00;											// NULLコードセット
									 gb_2Line_FirstDisplay	= false;														// 初回二行目表示フラグをＯＦＦ
//-----------------------------------------------------------------------------
                                     break;
                                 }
                            }
                        } else { //JOG -
                            if (guc_Ch_no >= 1) puc_Index = guc_Ch_no - 1;
                            for (puc_Index ; puc_Index >= 0 ; puc_Index--)
                            {
                                 if (guc_Write_check_flag[puc_Index] == true)
                                 {
                                     guc_Ch_no = puc_Index;
//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.22
									// BP4 Phase5 by @Tny 要ＦＲＡＭエリアからの読み込み処理
									 strcpy((char *)gt_SelectCharacter, (const char *)gt_WeldCondName[guc_Ch_no]);			// 既に設定されている文字列（初期文字列）の転送
									 gus_InputCharIndex	= (unsigned short)strlen((const char *)gt_WeldCondName[guc_Ch_no]);	// 入力文字位置インデックス
									 gt_SelectCharacter[gus_InputCharIndex] = 0x00;											// NULLコードセット
									 gb_2Line_FirstDisplay	= false;														// 初回二行目表示フラグをＯＦＦ
//-----------------------------------------------------------------------------
                                     break;
                                 }
                            }

                        }
                        if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){
                    	    gus_Pre_display_timer = 500;
                        }
                    }
                    if ((guc_Select_counter == MODE_RECORD) && (gtt_Ctrl_flag.Rec_display == OFF))	// BP4 Phase6 by @Tny 2009/01/27
                    {
						{
							signed char	pc_Ch_no = (signed char)guc_Ch_no + (signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1;	// Jog2->Jog1 BP4 Phase5 by @Tny 2009.01.22
	                        if(pc_Ch_no >= CH)     pc_Ch_no = (CH - 1);
    	                    else if(pc_Ch_no < 0)  pc_Ch_no = 0;
							guc_Ch_no = pc_Ch_no;
						}
                    }
                    if (guc_Select_counter == MODE_PLAY || guc_Select_counter == MODE_RECORD)	// BP4 Phase6 by @Tny 2009/01/27
                    {
                        gtt_Ctrl_flag.Param_change = OFF; //2008.08.07
                    }
        
            }
        
                    guc_Jog_rewrite_check_flag    = 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
        }
        //****************************************************************

//---------------------------------------
//リモコン接続時のデータ設定
		if(gtt_Ctrl_flag.RemoteController)
		{
           //if (gtt_Ctrl_flag.RemoteController == BPR4 && (gus_RemoInput[0] & 0x0020) == 0x0000) // && guc_Sequence_mode == IDLING) //再生モード
           if (gtt_Ctrl_flag.RemoteController == BPR4 && (gus_RemoInput[0] & 0x0020) == 0x0000 && guc_Sequence_mode == IDLING) //再生モード 2009.12.25 guc_Sequence_mode == IDLING 復活
           {
               if (gtt_Ctrl_flag.Remo_play_mode == OFF) //2009.03.30
               {
                          gtt_Ctrl_flag.No_ch_data = OFF;
                          gus_RemoInput[5] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[6] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[7] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[8] = 2048; //2009.03.31 1024->2048
                          gus_Remo_play_ch_data = 0;
                          guc_Jog_set_key = true;
                    	  guc_Select_counter = 0;
						  guc_Menu_Hierarchy			= 0;	// 詳細メニュー設定階層フラグ
	                	  gsc_Select_dital_counter	= 0;	// 詳細メニュー設定項目フラグ
                          gtt_Ctrl_flag.Remo_play_ch_select = OFF;
                          guc_Remo_play_ch_bkup = 0;
                          //<><><> 溶接終了電流表示キャンセル 2009.03.31 <><><>
                          if (gtt_End_welding_display.us_Display_time > 0)
                          {
                              gtt_Ctrl_flag.End_welding_display_cansel = ON;
                          } else {
                              gtt_Ctrl_flag.End_welding_display_cansel = OFF;
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><>
               }
               gtt_Ctrl_flag.Remo_play_mode = ON; //2009.03.30
			   {
                   ubool    Change = false; // 変更確認フラグ
                   unsigned short Data = 0;
                   signed short vGap;
                   // 溶接電流値の設定
                   if (guc_Sequence_mode == IDLING) //2009.03.30
                   {
                       vGap = ((signed short)gus_RemoInput[1] - (signed short)gus_RemoInput[5]);
                       if((vGap > 2)||(vGap < -2))
                       {
                          Data = gus_RemoInput[5] = gus_RemoInput[1];
                          //if(Data < 12) Data = 12;	// MIN:  4A
                          if(Data < REMO8_AD_MIN) Data = REMO8_AD_MIN;	// MIN:  5A 2010.02.04
                          //else if(Data > 930) Data = 930;	// MAX 300A
                          //else if(Data > 920) Data = 920;	// MAX 300A 2009.04.08 930->920
                          else if(Data > REMO8_AD_MAX) Data = REMO8_AD_MAX;	// MAX 500A 2010.02.04
                          //Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
                          if((gus_Remo_play_ch_data != Data))
                          {
                             unsigned short Ch1_upper;
                             unsigned short Ch1_downer;
                             unsigned short Ch2_upper;
                             unsigned short Ch2_downer;
                             unsigned short Ch3_upper;
                             unsigned short Ch3_downer;
                             unsigned short Ch4_upper;
                             unsigned short Ch4_downer;
                             unsigned short Ch5_upper;
                             unsigned short Ch5_downer;

                             Ch1_upper    =  195;
                             Ch1_downer   =    0;
                             Ch2_upper    =  400;
                             Ch2_downer   =  215;
                             Ch3_upper    =  605;
                             Ch3_downer   =  420;
                             Ch4_upper    =  810;
                             Ch4_downer   =  625;
                             Ch5_upper    = 1024;
                             Ch5_downer   =  830;

                             Change = true;	// 変更確認フラグ：変更有り

                             //CH1
                             if (Data >= Ch1_downer && Data <= Ch1_upper)
                             {
                                 guc_Remo_play_ch = 1;
                             }
                             //CH2
                             if (Data >= Ch2_downer && Data <= Ch2_upper)
                             {
                                 guc_Remo_play_ch = 2;
                             }
                             //CH3
                             if (Data >= Ch3_downer && Data <= Ch3_upper)
                             {
                                 guc_Remo_play_ch = 3;
                             }
                             //CH4
                             if (Data >= Ch4_downer && Data <= Ch4_upper)
                             {
                                 guc_Remo_play_ch = 4;
                             }
                             //CH5
                             if (Data >= Ch5_downer && Data <= Ch5_upper)
                             {
                                 guc_Remo_play_ch = 5;
                             }
                             if (guc_Remo_play_ch_bkup != guc_Remo_play_ch)
                             {
                                 gtt_Ctrl_flag.Remo_play_ch_select = OFF;
                                 guc_Remo_play_ch_bkup = guc_Remo_play_ch;
                             }
                             gus_Remo_play_ch_data = Data;
                             //<><><> 溶接終了電流表示キャンセル 2009.03.31 <><><>
                             if (gtt_End_welding_display.us_Display_time > 0)
                             {
                                 gtt_Ctrl_flag.End_welding_display_cansel = ON;
                             } else {
                                 gtt_Ctrl_flag.End_welding_display_cansel = OFF;
                             }
                             //<><><><><><><><><><><><><><><><><><><><><><><><><><>
                          }
                       }
                       //再生ボタンの確認
                       if ((gus_RemoInput[0] & 0x0040) == 0x0000)
                       {
                           //<><><> 溶接終了電流表示キャンセル 2009.03.31 <><><>
                           if (gtt_End_welding_display.us_Display_time > 0)
                           {
                               gtt_Ctrl_flag.End_welding_display_cansel = ON;
                           } else {
                               gtt_Ctrl_flag.End_welding_display_cansel = OFF;
                           }
                           //<><><><><><><><><><><><><><><><><><><><><><><><><><>
                           if (gtt_Ctrl_flag.Remo_play_sw == OFF)
                           {
                               gtt_Ctrl_flag.Remo_play_sw = ON;
                               gtt_Ctrl_flag.Remo_play_on = OFF;
                               gtt_Ctrl_counter.Remo_play_sw = 500;
                           } else if (gtt_Ctrl_counter.Remo_play_sw <= 0 && gtt_Ctrl_flag.Remo_play_on == OFF) {
                               //再生フラグＯＮ
                               gtt_Ctrl_flag.Remo_play_on = ON;
                               gtt_Ctrl_flag.Remo_play_ch_select = ON;
                               if (guc_Write_check_flag_ch[guc_Remo_play_ch]  == true) //予めデータが記憶されている場合は再生
                               {
                                   ch_play_class(guc_Remo_play_ch);
                                   gtt_Ctrl_flag.No_ch_data = OFF;
                                   gtt_Table_key.Change_flag = ON; //2009.04.01
                               } else { //予めデータが記憶されていない場合はエラー処理
                                   //エラー表示処理
                                   gtt_Ctrl_flag.No_ch_data = ON;
                               }
                           }
                       } else {
#if 0
                           if (gtt_Ctrl_flag.Remo_play_on == ON) //ＣＨ再生
                           {
                               if (guc_Write_check_flag_ch[guc_Remo_play_ch]  == true) //予めデータが記憶されている場合は再生
                               {
                                   ch_play_class(guc_Remo_play_ch);
                                   gtt_Ctrl_flag.No_ch_data = OFF;
                               } else { //予めデータが記憶されていない場合はエラー処理
                                   //エラー表示処理
                                   gtt_Ctrl_flag.No_ch_data = ON;
                               }
                           }
#endif
                           gtt_Ctrl_flag.Remo_play_sw = OFF;
                           gtt_Ctrl_flag.Remo_play_on = OFF;
                       }
                   }

				}
           } else {
             if (gtt_Ctrl_flag.Remo_play_mode == ON) //2009.03.30
             {
                 if (guc_Sequence_mode == IDLING)
                 {
                          gtt_Ctrl_flag.No_ch_data = OFF;
                          gtt_Ctrl_flag.Remo_play_mode = OFF;
                          gus_RemoInput[5] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[6] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[7] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[8] = 2048; //2009.03.31 1024->2048
                          //<><><> 溶接終了電流表示キャンセル 2009.03.31 <><><>
                          if (gtt_End_welding_display.us_Display_time > 0)
                          {
                              gtt_Ctrl_flag.End_welding_display_cansel = ON;
                          } else {
                              gtt_Ctrl_flag.End_welding_display_cansel = OFF;
                          }
                          //<><><><><><><><><><><><><><><><><><><><><><><><><><>
                  }
             }
             if (gtt_Ctrl_flag.Remo_play_mode == OFF) //2009.03.30
             {
                        //**** 制限電流セット 2009.02.19 2009.04.01******************************
                        if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT;
                        }
                        if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            //***** 2009.03.13 *****
                    		if (guc_Ac_wave_counter == 1) //ハードＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT;
                                gss_Min_current = MIN_CURRENT_AC_HARD; //2011.09.30
                            }
                    		if (guc_Ac_wave_counter == 2) //ソフトＡＣ 
                            {
                                gss_Max_current = MAX_CURRENT_AC_SOFT;
                                gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                            }
                            //**********************

                        }
                        if (guc_Method_condition_data == STD_MIX_METHOD) //2009.03.17
                        {
                            gss_Max_current = MAX_CURRENT;
                            gss_Min_current = MIN_CURRENT_AC; //2011.09.30
                        }
                        
                        if (guc_Method_condition_data == STD_HAND_METHOD) //2009.03.06
                        {
                            gss_Max_current = MAX_CURRENT_HAND;
                            gss_Min_current = MIN_CURRENT_HAND;
                        }

                 {
                  //リモコン接続時の最大、最小値制限 2008.03.13
                  //初期電流
                  if (gtt_Internal_pack.Data.In.usWeldingInitCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  {
        	          gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
                  }
        	      if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                  {
        	          gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
                  }
                  //本電流
                  if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  {
                      gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
                  }
                  if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                  {
        	          gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
                  }
                  //クレータ電流
                  if (gtt_Internal_pack.Data.In.usWeldingCratCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  {
        	          gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
                  }
                  if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                  {
                      gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
                  }
                  //パルス電流
                  if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
                  {
        	          gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        	      }
        	      if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                  {
        	          gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        	      }
//------------------------------------------------
// 2009.12.25 by @Tny	溶接中はパルスモード＆クレータ設定の変更は行わない	2009.12.28 by @Tny 不具合修正
				}	// ← 構造化合わせのために追加	2009.12.25 by @Tny
				if((guc_Sequence_mode == IDLING)||((guc_Sequence_mode == AFTER_FLOW)&&(gtt_End_welding_display.bProc1 == false)&&(gtt_End_welding_display.bProc2 == false))){
				{	// ← 構造化合わせのために追加	2009.12.25 by @Tny
//------------------------------------------------
                  // パルスの設定
				    if(gus_RemoInput[0] & 0x0008){	// パルス無し
					    guc_Pulse_mode_counter	= 0;
				    }
				    else{							// パルス有り
					    guc_Pulse_mode_counter	= 1;
                        //if (guc_Method_condition_data == STD_MIX_METHOD || guc_Method_condition_data == STD_HAND_METHOD) //2009.03.09.NO5 2009.02.17 ＭＩＸではパルスは必要ないので、０クリアする。
                        if (guc_Method_condition_data == STD_MIX_METHOD || guc_Method_condition_data == STD_HAND_METHOD || guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.04.03
                        {
                            guc_Pulse_mode_counter = 0;
                        }
				    }
				    if(guc_Pulse_mode_data != guc_Pulse_mode_counter){ // 設定が変えられた？
					    //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す *****
					    guc_Pulse_item_counter  	= 0;
					    guc_Ac_tig_set_counter  	= 0;
					    guc_Mix_tig_set_counter		= 0;
					    gtt_Ctrl_flag.Param_change	= ON;
					    guc_Jog_set_key				= true;
					    guc_Sw_rewrite_check_flag	= 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
				    }
				    guc_Pulse_mode_data = guc_Pulse_mode_counter;
			    }
			    {// クレータの設定
				    unsigned char PastFulag = guc_Crater_mode_counter;	// クレータ設定値を一時記憶

				    if((gus_RemoInput[0] & 0x0004) == 0){		// クレータ反復
					    guc_Crater_mode_counter = 2;
				    }
				    else if((gus_RemoInput[0] & 0x0002) == 0){	// クレータ有り
					    guc_Crater_mode_counter = 1;
				    }
				    else{										// クレータ無し
					    guc_Crater_mode_counter = 0;
				    }
                    if (guc_Method_condition_data == STD_HAND_METHOD) //2009.03.09.NO5
                    {
					    guc_Crater_mode_counter = 0;
                        PastFulag = 0;
                    }
				    if(guc_Crater_mode_counter != PastFulag){ // 設定が変えられた？
					    //***** パルス項目、ＡＣ項目、ＭＩＸ項目は一旦先頭に戻す *****
					    guc_Pulse_item_counter  	= 0;
					    guc_Ac_tig_set_counter  	= 0;
					    guc_Mix_tig_set_counter 	= 0;
					    gtt_Ctrl_flag.Param_change	= ON;
					    guc_Jog_set_key				= true;
					    guc_Sw_rewrite_check_flag	= 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
				    }
			    }
//------------------------------------------------
// 2009.12.25 by @Tny	溶接中はパルスモード＆クレータ設定の変更は行わない
				}
//------------------------------------------------
			    {
//----------------------------------
#if true	// 2011.12.07 <500A->300A>
				    ubool			Change	= false;	// 変更確認フラグ
				    unsigned short	Data = 0;
				    signed short	vGap;
				    // 溶接電流値の設定
				    vGap = ((signed short)gus_RemoInput[1] - (signed short)gus_RemoInput[5]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[5] = gus_RemoInput[1];
					    if(Data < 12) 		Data = 12;	// MIN:  4A
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    if(gtt_Internal_pack.Data.In.usWeldingCurr != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usWeldingCurr	= Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usWeldingCurr > gss_Max_current)
                            {
                                gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
                            }
                            if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
                            }
                            //エキスパートモード リファレンス電圧再セット 2009.03.23
                            gtt_Ctrl_flag.Ref_voltage = OFF;
                            gtt_Ctrl_flag.Ref_voltage_result = OFF;
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
					    }
				    }
				    // クレータ電流値の設定
				    vGap = ((signed short)gus_RemoInput[2] - (signed short)gus_RemoInput[6]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[6] = gus_RemoInput[2];
					    if(Data < 12) 		Data = 12;	// MIN:  4A
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    if(gtt_Internal_pack.Data.In.usWeldingCratCurr != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usWeldingCratCurr	= Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usWeldingCratCurr > gss_Max_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
                            }
                            if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                            {
                                gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
                            }
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
					    }
				    }
				    // 初期電流値の設定
				    vGap = ((signed short)gus_RemoInput[3] - (signed short)gus_RemoInput[7]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[7] = gus_RemoInput[3];
					    if(Data < 12) 		Data = 12;	// MIN:  4A
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    if(gtt_Internal_pack.Data.In.usWeldingInitCurr != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usWeldingInitCurr	= Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usWeldingInitCurr > gss_Max_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
                            }
        	                if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
                            }
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
					    }
				    }
				    // パルス電流値の設定
				    vGap = ((signed short)gus_RemoInput[4] - (signed short)gus_RemoInput[8]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[8] = gus_RemoInput[4];
					    if(Data < 12) 		Data = 12;	// MIN:  4A
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    if(gtt_Internal_pack.Data.In.usIP != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usIP = Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usIP > gss_Max_current)
                            {
        	                    gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        	                }
        	                if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                            {
        	                    gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        	                }
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
					    }
				    }
#else
				    ubool			Change	= false;	// 変更確認フラグ
				    unsigned short	Data = 0;
				    signed short	vGap;
				    // 溶接電流値の設定
				    vGap = ((signed short)gus_RemoInput[1] - (signed short)gus_RemoInput[5]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[5] = gus_RemoInput[1];
					    //if(Data < 12) 		Data = 12;	// MIN:  4A
					    if(Data < REMO8_AD_MIN)	Data = REMO8_AD_MIN;	// MIN:  5A 2010.02.04
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    //else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    else if(Data > REMO8_AD_MAX) Data = REMO8_AD_MAX;	// MAX 500A 2010.02.04
					    //Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    Data = (unsigned short)(((float)Data - REMO8_C) / REMO8_AD_CONVERTER + 0.5); //2010.02.04
					    if(gtt_Internal_pack.Data.In.usWeldingCurr != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usWeldingCurr	= Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usWeldingCurr > gss_Max_current)
                            {
                                gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
                            }
                            if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
                            }
                            //エキスパートモード リファレンス電圧再セット 2009.03.23
                            gtt_Ctrl_flag.Ref_voltage = OFF;
                            gtt_Ctrl_flag.Ref_voltage_result = OFF;
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
                            gtt_Ctrl_flag.Ac_freq_jog = ON; //2010.01.20
					    }
				    }
				    // クレータ電流値の設定
				    vGap = ((signed short)gus_RemoInput[2] - (signed short)gus_RemoInput[6]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[6] = gus_RemoInput[2];
					    //if(Data < 12) 		Data = 12;	// MIN:  4A
					    if(Data < REMO8_AD_MIN)	Data = REMO8_AD_MIN;	// MIN:  5A 2010.02.04
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    //else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    else if(Data > REMO8_AD_MAX) Data = REMO8_AD_MAX;	// MAX 500A 2010.02.04
					    //Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    Data = (unsigned short)(((float)Data - REMO8_C) / REMO8_AD_CONVERTER + 0.5); //2010.02.04
					    if(gtt_Internal_pack.Data.In.usWeldingCratCurr != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usWeldingCratCurr	= Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usWeldingCratCurr > gss_Max_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
                            }
                            if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                            {
                                gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
                            }
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
                            gtt_Ctrl_flag.Ac_freq_jog = ON; //2010.01.20
					    }
				    }
				    // 初期電流値の設定
				    vGap = ((signed short)gus_RemoInput[3] - (signed short)gus_RemoInput[7]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[7] = gus_RemoInput[3];
					    //if(Data < 12) 		Data = 12;	// MIN:  4A
					    if(Data < REMO8_AD_MIN) Data = REMO8_AD_MIN; // MIN:  5A 2010.02.04
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    //else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    else if(Data > REMO8_AD_MAX) Data = REMO8_AD_MAX; // MAX 500A 2010.02.04
					    //Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    Data = (unsigned short)(((float)Data - REMO8_C) / REMO8_AD_CONVERTER + 0.5); //2010.02.04
					    if(gtt_Internal_pack.Data.In.usWeldingInitCurr != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usWeldingInitCurr	= Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usWeldingInitCurr > gss_Max_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
                            }
        	                if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                            {
        	                    gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
                            }
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
                            gtt_Ctrl_flag.Ac_freq_jog = ON; //2010.01.20
					    }
				    }
				    // パルス電流値の設定
				    vGap = ((signed short)gus_RemoInput[4] - (signed short)gus_RemoInput[8]);
				    if((vGap > 2)||(vGap < -2)){
					    Data = gus_RemoInput[8] = gus_RemoInput[4];
					    //if(Data < 12) 		Data = 12;	// MIN:  4A
					    if(Data < REMO8_AD_MIN) Data = REMO8_AD_MIN; // MIN:  5A 2010.02.04
					    //else if(Data > 930)	Data = 930;	// MAX 300A
					    //else if(Data > 920)	Data = 920;	// MAX 300A 2009.04.08 930->920
					    else if(Data > REMO8_AD_MAX) Data = REMO8_AD_MAX;	// MAX 500A 2010.02.04
					    //Data = (unsigned short)((float)Data / REMO8_AD_CONVERTER + 0.5);
					    Data = (unsigned short)(((float)Data - REMO8_C) / REMO8_AD_CONVERTER + 0.5); //2010.02.04
					    if(gtt_Internal_pack.Data.In.usIP != Data){
						    Change = true;	// 変更確認フラグ：変更有り
						    gtt_Internal_pack.Data.In.usIP = Data;
                            // ***** 2009.03.13 *****
                            if (gtt_Internal_pack.Data.In.usIP > gss_Max_current)
                            {
        	                    gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        	                }
        	                if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                            {
        	                    gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        	                }
                            // ***********************
                            if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){ //2009.03.09.NO5
                    	        gus_Pre_display_timer = 300;
                            }
                            gtt_Ctrl_flag.Ac_freq_jog = ON; //2010.01.20
					    }
				    }
#endif
//----------------------------------------------------
				    if(Change){	// 変更確認フラグ：変更有り？
					    gtt_Ctrl_flag.Param_change	= ON;
					    guc_Jog_rewrite_check_flag	= 2;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
                        //<><><> 溶接終了電流表示キャンセル 2009.03.31 <><><>
                        if (gtt_End_welding_display.us_Display_time > 0)
                        {
                            gtt_Ctrl_flag.End_welding_display_cansel = ON;
                        } else {
                            gtt_Ctrl_flag.End_welding_display_cansel = OFF;
                        }
                        //<><><><><><><><><><><><><><><><><><><><><><><><><><>
				    }
			    }
            }
           }
		}
        




        //***** パルス周波数、交流ＴＩＧ周波数丸め処理 2009.02.24 *****
        //パルス周波数
        { //2009.02.24    0.1-9.9Hz(0.1Hz)  10-99Hz(1Hz)  100-500Hz(10Hz) に変更
          short work;
          if (gtt_Internal_pack.Data.In.usPulseFreq >= 100 && gtt_Internal_pack.Data.In.usPulseFreq <= 990){
              //一桁目は現れる時（ＪＯＧ高速回し時）に備えた補正。
              work = gtt_Internal_pack.Data.In.usPulseFreq / 10; 
              work = work * 10;
              gtt_Internal_pack.Data.In.usPulseFreq = work;
          } else if (gtt_Internal_pack.Data.In.usPulseFreq >= 1000) {
              //一桁目は現れる時（ＪＯＧ高速回し時）に備えた補正。
              work = gtt_Internal_pack.Data.In.usPulseFreq / 100; 
              work = work * 100;
              gtt_Internal_pack.Data.In.usPulseFreq = work;
          }
        }
        //交流ＴＩＧ周波数
        { //2009.02.24    30-199Hz(1Hz)  199-400Hz(10Hz)に変更
           short work;
           if (gtt_Internal_pack.Data.In.usAcFreq >= 200){
               //一桁目は現れる時（ＪＯＧ高速回し時）に備えた補正。
               work = gtt_Internal_pack.Data.In.usAcFreq / 10; 
               work = work * 10;
               gtt_Internal_pack.Data.In.usAcFreq = work;
           }
         }
        //*************************************************************


                //<><>詳細メニュー設定で値を反映する処理 2008.10.09<><><><><> 
                //ditail_set_member(gsc_Select_dital_counter); 2009.02.23
                        
           if (guc_Jog_set_key == true) //2009.01.16
           {
               //guc_Sequence_set_data = 0; //2009.01.16
               gus_Sequence_set_data = 0; //2009.01.19
           }
 
           if (gtt_Ctrl_flag.Service_man == OFF) //技術・サービスマンメニュー分岐 2008.09.02
           {
                //<><><><> パスワードセット関連 2008.09.02 <><><><>
                if (gtt_Ctrl_counter.us_User_parameter_no == PASS_WORD_NO && gtt_Ctrl_counter.uc_User_menu_no == 0) //2008.11.20
                {
                    if (gtt_Ctrl_flag.Set_key == ON && gtt_Ctrl_flag.Pass_word_err == OFF)
                    {
                        gtt_Ctrl_flag.Set_key = OFF;
                        gtt_Ctrl_counter.Pass_word_check++;
                        switch (gtt_Ctrl_counter.Pass_word_check)
                        {
                             case 1:
                                  if (gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] == PASS1)
                                  {
                                      gtt_Ctrl_counter.Pass_word_ok++;
                                  }
                                 break;
                             case 2:
                                  if (gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] == PASS2)
                                  {
                                      gtt_Ctrl_counter.Pass_word_ok++;
                                  }
                                 break;
                             case 3:
                                  if (gtt_Special_menu.ss_User_param[gtt_Ctrl_counter.us_User_parameter_no] == PASS3)
                                  {
                                      gtt_Ctrl_counter.Pass_word_ok++;
                                  }
                                 break;
                        }
                        if (gtt_Ctrl_counter.Pass_word_check == 3)
                        {
                            if (gtt_Ctrl_counter.Pass_word_ok == 3)
                            {
                                gtt_Ctrl_flag.Pass_word_err = OFF;
                            } else {
                                gtt_Ctrl_flag.Service_man = OFF;
                                gtt_Ctrl_flag.Pass_word_err = ON;
                            }
                        }
                        if (gtt_Ctrl_counter.Pass_word_check == 4)
                        {
                            gtt_Ctrl_flag.Service_man = ON;
                        }
                    }
                    if (gtt_Ctrl_flag.Set_key == ON && gtt_Ctrl_flag.Pass_word_err == ON)
                    {
                        gtt_Ctrl_flag.Set_key = OFF;
                        gtt_Ctrl_flag.Service_man = OFF;
                        gtt_Ctrl_flag.Pass_word_err = OFF;
                        gtt_Ctrl_counter.Pass_word_check = 0;
                        gtt_Ctrl_counter.Pass_word_ok = 0;
                        gtt_Special_menu.ss_User_param[PASS_WORD_NO] = 111;
                    }
                } else { // 2008.11.20
                    gtt_Ctrl_flag.Pass_word_err = OFF;
                    gtt_Ctrl_counter.Pass_word_check = 0;
                    gtt_Ctrl_counter.Pass_word_ok = 0;
                    gtt_Special_menu.ss_User_param[PASS_WORD_NO] = 111;
				}
                //<><><><> ＩＩＦ設定 ここで無くても良い（暫定）2008.08.23 <><><><>
                    if(gtt_Ctrl_counter.uc_User_menu_no == 2){  // IIF設定項目のみ
                      if(gb_IIF_Select){ // IIF接続時のみ対応
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
                                  }
                                  break;
                             case 1: //INPUT PORT設定
                                  if (gtt_Ctrl_flag.In_function_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                                  {
                                      guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no] = gtt_Ctrl_counter.uc_In_function_no;
                                      //ポートチェック 2008.09.04 同じ機能設定を禁止
                                      for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                                      {
                                           if (gtt_Ctrl_counter.uc_In_port_no != puc_Index)
                                           {
                                               if (guc_In_port[0][gtt_Ctrl_counter.uc_In_port_no] == guc_In_port[0][puc_Index])
                                               {
                                                   guc_In_port[0][puc_Index] = 0;
                                               }
                                           }
                                      }
                                      gtt_Ctrl_counter.uc_In_function_no = 0;
                                      gtt_Ctrl_flag.In_function_set_ready = OFF;
                                      gtt_Ctrl_flag.Set_key = OFF;
                                      gtt_Ctrl_flag.Param_change = ON;
                                  }
                                  break;
                             case 2: //ANALOG PORT設定
                                  if (gtt_Ctrl_flag.Analog_function_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                                  {
                                      guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] = gtt_Ctrl_counter.uc_Analog_function_no;
                                      //ポートチェック 2008.09.04 同じ電圧指令値入力　同じ電流指令値入力の設定を禁止
                                      for (puc_Index = 1 ; puc_Index <= 3 ; puc_Index++)
                                      {
                                           if (gtt_Ctrl_counter.uc_Analog_port_no != puc_Index)
                                           {
                                               //電流指令値
                                               switch (gtt_Ctrl_counter.uc_Analog_function_no)
                                               {
                                                        //設定しようとしているポート設定が電流指令値の場合で
                                                        //他のポート設定が電流指令値１５、１２、１０Ｖのいずれかが
                                                        //存在する場合は他のポートをＮＯ　ＵＳＥとする。
                                                   case ANALOG_FUNC_CUR_15V://電流指令値１５Ｖ
                                                        if (guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] == guc_Analog_port[0][puc_Index] || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_CUR_12V || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_CUR_10V)
                                                        {
                                                            guc_Analog_port[0][puc_Index] = 0;
                                                        }
                                                        break;
                                                   case ANALOG_FUNC_CUR_12V://電流指令値１２Ｖ
                                                        if (guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] == guc_Analog_port[0][puc_Index] || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_CUR_15V || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_CUR_10V)
                                                        {
                                                            guc_Analog_port[0][puc_Index] = 0;
                                                        }
                                                        break;
                                                   case ANALOG_FUNC_CUR_10V://電流指令値１０Ｖ
                                                        if (guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] == guc_Analog_port[0][puc_Index] || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_CUR_15V || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_CUR_12V)
                                                        {
                                                            guc_Analog_port[0][puc_Index] = 0;
                                                        }
                                                        break;
                                                        //設定しようとしているポート設定が電圧指令値の場合で
                                                        //他のポート設定が電圧指令値１５、１２、１０Ｖのいずれかが
                                                        //存在する場合は他のポートをＮＯ　ＵＳＥとする。
                                                   case ANALOG_FUNC_VLT_15V://電圧指令値１５Ｖ
                                                        if (guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] == guc_Analog_port[0][puc_Index] || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_VLT_12V || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_VLT_10V)
                                                        {
                                                            guc_Analog_port[0][puc_Index] = 0;
                                                        }
                                                        break;
                                                   case ANALOG_FUNC_VLT_12V://電圧指令値１２Ｖ
                                                        if (guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] == guc_Analog_port[0][puc_Index] || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_VLT_15V || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_VLT_10V)
                                                        {
                                                            guc_Analog_port[0][puc_Index] = 0;
                                                        }
                                                        break;
                                                   case ANALOG_FUNC_VLT_10V://電圧指令値１０Ｖ
                                                        if (guc_Analog_port[0][gtt_Ctrl_counter.uc_Analog_port_no] == guc_Analog_port[0][puc_Index] || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_VLT_15V || guc_Analog_port[0][puc_Index] == ANALOG_FUNC_VLT_12V)
                                                        {
                                                            guc_Analog_port[0][puc_Index] = 0;
                                                        }
                                                        break;
                                                   default: 
                                                        break;
                                               }
                                               

                                           }
                                      }
                                      gtt_Ctrl_counter.uc_Analog_function_no = 0;
                                      gtt_Ctrl_flag.Analog_function_set_ready = OFF;
                                      gtt_Ctrl_flag.Set_key = OFF;
                                      gtt_Ctrl_flag.Param_change = ON;
                                  }
                                  break;
                        }
                        }
                        else{
                            gtt_Ctrl_flag.Set_key = OFF; //2008.10.16 del ihara
                        }
                    }

                //<><><><> カレンダー設定 ここで無くても良い（暫定）2008.08.23 <><><><>
                        switch (gtt_Ctrl_counter.uc_Calender_no)
                        {
                             case 0: //年設定
                                  if (gtt_Ctrl_flag.Calender_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                                  {
                                      gtt_Calender.uc_Year_data = gtt_Ctrl_counter.uc_Year_set_data;
// BP4 Phase4 by @Tny 2009.01.15                                      gtt_Ctrl_counter.uc_Year_set_data = 0;
                                      gtt_Ctrl_flag.Calender_set_ready = OFF;
                                      gtt_Ctrl_flag.Set_key = OFF;
                                      if (gtt_Calender.uc_Month_data == 2 && gtt_Calender.uc_Day_data >= 29)
                                      {
                                          if (gtt_Calender.Leap_year == ON)
                                          {
                                              gtt_Calender.uc_Day_data = 29;
                                          } else {
                                              gtt_Calender.uc_Day_data = 28;
                                          }
                                      }
                                      { // 時刻設定
                                          uchar   Data[10];
                                          Data[0] = (((gtt_Calender.uc_Year_data / 10) << 4) | (gtt_Calender.uc_Year_data % 10));     // 年の書式変更
                                          Data[1] = (((gtt_Calender.uc_Month_data / 10) << 4) | (gtt_Calender.uc_Month_data % 10));   // 月の書式変更
                                          Data[2] = (((gtt_Calender.uc_Day_data / 10) << 4) | (gtt_Calender.uc_Day_data % 10));       // 日の書式変更
                                          Data[3] = 0;                                                                                // 曜日指定（未使用）
                                          Data[4] = (((gtt_Calender.uc_Hour_data / 10) << 4) | (gtt_Calender.uc_Hour_data % 10));     // 時の書式変更
                                          Data[5] = (((gtt_Calender.uc_Mint_data / 10) << 4) | (gtt_Calender.uc_Mint_data % 10));     // 分の書式変更
                                          Data[6] = 0;                                                                                // 秒は０リセット
                                          // 時刻設定
                                          I2C_RTC(RTC_WRITE, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                                      }
                                  }
                                  break;
                             case 1: //月設定
                                  if (gtt_Ctrl_flag.Calender_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                                  {
                                      if (gtt_Calender.uc_Day_data >= 30)
                                      {
                                            if (gtt_Ctrl_counter.uc_Month_set_data == 4 || gtt_Ctrl_counter.uc_Month_set_data == 6 || gtt_Ctrl_counter.uc_Month_set_data == 9 || gtt_Ctrl_counter.uc_Month_set_data == 11)
                                            {
                                                gtt_Calender.uc_Day_data = 30;
                                            }
                                      }
                                      if (gtt_Ctrl_counter.uc_Month_set_data == 2 && gtt_Calender.uc_Day_data >= 29)
                                      {
                                          if (gtt_Calender.Leap_year == ON)
                                          {
                                              gtt_Calender.uc_Day_data = 29;
                                          } else {
                                              gtt_Calender.uc_Day_data = 28;
                                          }
                                      }
                                      gtt_Calender.uc_Month_data = gtt_Ctrl_counter.uc_Month_set_data;
// BP4 Phase4 by @Tny 2009.01.15                                      gtt_Ctrl_counter.uc_Month_set_data = 0;
                                      gtt_Ctrl_flag.Calender_set_ready = OFF;
                                      gtt_Ctrl_flag.Set_key = OFF;
                                      { // 時刻設定
                                          uchar   Data[10];
                                          Data[0] = (((gtt_Calender.uc_Year_data / 10) << 4) | (gtt_Calender.uc_Year_data % 10));     // 年の書式変更
                                          Data[1] = (((gtt_Calender.uc_Month_data / 10) << 4) | (gtt_Calender.uc_Month_data % 10));   // 月の書式変更
                                          Data[2] = (((gtt_Calender.uc_Day_data / 10) << 4) | (gtt_Calender.uc_Day_data % 10));       // 日の書式変更
                                          Data[3] = 0;                                                                                // 曜日指定（未使用）
                                          Data[4] = (((gtt_Calender.uc_Hour_data / 10) << 4) | (gtt_Calender.uc_Hour_data % 10));     // 時の書式変更
                                          Data[5] = (((gtt_Calender.uc_Mint_data / 10) << 4) | (gtt_Calender.uc_Mint_data % 10));     // 分の書式変更
                                          Data[6] = 0;                                                                                // 秒は０リセット
                                          // 時刻設定
                                          I2C_RTC(RTC_WRITE, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                                      }
                                  }
                                  break;
                             case 2: //日設定
                                  if (gtt_Ctrl_flag.Calender_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                                  {
                                      gtt_Calender.uc_Day_data = gtt_Ctrl_counter.uc_Day_set_data;
// BP4 Phase4 by @Tny 2009.01.15                                      gtt_Ctrl_counter.uc_Day_set_data = 0;
                                      gtt_Ctrl_flag.Calender_set_ready = OFF;
                                      gtt_Ctrl_flag.Set_key = OFF;
                                      { // 時刻設定
                                          uchar   Data[10];
                                          Data[0] = (((gtt_Calender.uc_Year_data / 10) << 4) | (gtt_Calender.uc_Year_data % 10));     // 年の書式変更
                                          Data[1] = (((gtt_Calender.uc_Month_data / 10) << 4) | (gtt_Calender.uc_Month_data % 10));   // 月の書式変更
                                          Data[2] = (((gtt_Calender.uc_Day_data / 10) << 4) | (gtt_Calender.uc_Day_data % 10));       // 日の書式変更
                                          Data[3] = 0;                                                                                // 曜日指定（未使用）
                                          Data[4] = (((gtt_Calender.uc_Hour_data / 10) << 4) | (gtt_Calender.uc_Hour_data % 10));     // 時の書式変更
                                          Data[5] = (((gtt_Calender.uc_Mint_data / 10) << 4) | (gtt_Calender.uc_Mint_data % 10));     // 分の書式変更
                                          Data[6] = 0;                                                                                // 秒は０リセット
                                          // 時刻設定
                                          I2C_RTC(RTC_WRITE, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                                      }
                                  }
                                  break;
                             case 3: //時設定
                                  if (gtt_Ctrl_flag.Calender_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                                  {
                                      gtt_Calender.uc_Hour_data = gtt_Ctrl_counter.uc_Hour_set_data;
// BP4 Phase4 by @Tny 2009.01.15                                      gtt_Ctrl_counter.uc_Hour_set_data = 0;
                                      gtt_Ctrl_flag.Calender_set_ready = OFF;
                                      gtt_Ctrl_flag.Set_key = OFF;
                                      { // 時刻設定
                                          uchar   Data[10];
                                          Data[0] = (((gtt_Calender.uc_Year_data / 10) << 4) | (gtt_Calender.uc_Year_data % 10));     // 年の書式変更
                                          Data[1] = (((gtt_Calender.uc_Month_data / 10) << 4) | (gtt_Calender.uc_Month_data % 10));   // 月の書式変更
                                          Data[2] = (((gtt_Calender.uc_Day_data / 10) << 4) | (gtt_Calender.uc_Day_data % 10));       // 日の書式変更
                                          Data[3] = 0;                                                                                // 曜日指定（未使用）
                                          Data[4] = (((gtt_Calender.uc_Hour_data / 10) << 4) | (gtt_Calender.uc_Hour_data % 10));     // 時の書式変更
                                          Data[5] = (((gtt_Calender.uc_Mint_data / 10) << 4) | (gtt_Calender.uc_Mint_data % 10));     // 分の書式変更
                                          Data[6] = 0;                                                                                // 秒は０リセット
                                          // 時刻設定
                                          I2C_RTC(RTC_WRITE, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                                      }
                                  }
                                  break;
                             case 4: //分設定
                                  if (gtt_Ctrl_flag.Calender_set_ready == ON && gtt_Ctrl_flag.Set_key == ON)
                                  {
                                      gtt_Calender.uc_Mint_data = gtt_Ctrl_counter.uc_Mint_set_data;
// BP4 Phase4 by @Tny 2009.01.15                                      gtt_Ctrl_counter.uc_Mint_set_data = 0;
                                      gtt_Calender.uc_Sec_data = 0;
                                      gtt_Ctrl_flag.Calender_set_ready = OFF;
                                      gtt_Ctrl_flag.Set_key = OFF;
                                      { // 時刻設定
                                          uchar   Data[10];
                                          Data[0] = (((gtt_Calender.uc_Year_data / 10) << 4) | (gtt_Calender.uc_Year_data % 10));     // 年の書式変更
                                          Data[1] = (((gtt_Calender.uc_Month_data / 10) << 4) | (gtt_Calender.uc_Month_data % 10));   // 月の書式変更
                                          Data[2] = (((gtt_Calender.uc_Day_data / 10) << 4) | (gtt_Calender.uc_Day_data % 10));       // 日の書式変更
                                          Data[3] = 0;                                                                                // 曜日指定（未使用）
                                          Data[4] = (((gtt_Calender.uc_Hour_data / 10) << 4) | (gtt_Calender.uc_Hour_data % 10));     // 時の書式変更
                                          Data[5] = (((gtt_Calender.uc_Mint_data / 10) << 4) | (gtt_Calender.uc_Mint_data % 10));     // 分の書式変更
                                          Data[6] = 0;                                                                                // 秒は０リセット
                                          // 時刻設定
                                          I2C_RTC(RTC_WRITE, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                                      }
                                  }
                                  break;
                        }


                     //溶接法を確定するため一時作成　2009.01.28
                     
                         gtt_Internal_pack.Data.In.fWireDiameter.ALL          = 0x06;      // ワイヤ径
        		         gtt_Internal_pack.Data.In.fWelding.ALL               = 0x05;    // 溶接法
        		         gtt_Internal_pack.Data.In.fWireMaterial.ALL          = 0x01;  // ワイヤ材質
                         gtt_Internal_pack.Data.In.fWireSelect.ALL            = 0x03;       // 突き出し長 2008.11.10
                         gtt_Internal_pack.Data.In.fPulseMode.ALL  =  0x00;  // 短絡(0x03)のとき　0x10 ／パルス(0x05)のとき 0x00
                         //パルスモード 2007.12.14
                         gtt_Internal_pack.Data.In.fPulseMode.ALL  =  gtt_Internal_pack.Data.In.fPulseMode.ALL | 0x03;  //通常パルス　上記に伴い追加
                     





//--------------------------------------------------------------------
//BP4 Phase15 by @Tny 2009.02.25
						if((gb_ServiceMenu == false)&&(gb_RescueMenu == false)){
//--------------------------------------------------------------------
                //<><><><><><><><><> ナビ設定 2009.01.15 <><><><><><><><><><>
                        //ナビの選択入力 2009.01.15
                 	    if (guc_Method_condition_counter == 4) //ナビモード選択
                        {
                            if (gtt_Navi.uc_Jog_set_key == true)
                            {
                                if (gtt_Navi.uc_Key_counter == 0) //材質選択
                                {
                                    gtt_Navi.uc_Material_set = ON; //材質確定
                                    gtt_Navi.uc_Material_address = guc_Navi_material_code[gtt_Navi.sc_Jog_counter];
                                }
                                if (gtt_Navi.uc_Key_counter == 1) //板厚
                                {
                                    gtt_Navi.uc_Thickness_set = ON; //板厚確定
                                    gtt_Navi.uc_Thickness_address = guc_Navi_thickness_code[gtt_Navi.sc_Jog_counter];
                                    if (gtt_Navi.uc_Thickness_address == 24) //材質、板厚取り消し
                                    {
                                        gtt_Navi.uc_Material_set = OFF;
                                        gtt_Navi.uc_Material_address = 0x00;
                                        gtt_Navi.uc_Thickness_set = OFF;
                                        gtt_Navi.uc_Thickness_address = 0x00;
                                        gtt_Navi.uc_Key_counter = 0;
                                        gtt_Navi.sc_Jog_counter = 0;
                                        gtt_Navi.uc_Thickness_search = OFF;
                                        gtt_Navi.uc_Cansel = ON;
                                    }
                                }
                                if (gtt_Navi.uc_Key_counter == 2) //継ぎ手
                                {
                                    gtt_Navi.uc_Joint_set = ON; //継ぎ手確定
                                    gtt_Navi.uc_Joint_address = guc_Navi_joint_code[gtt_Navi.sc_Jog_counter];
                                    if (gtt_Navi.uc_Joint_address == 24) //板厚、継ぎ手取り消し
                                    {
                                        gtt_Navi.uc_Thickness_set = OFF;
                                        gtt_Navi.uc_Thickness_address = 0x00;
                                        gtt_Navi.uc_Joint_set = OFF;
                                        gtt_Navi.uc_Joint_address = 0x00;
                                        gtt_Navi.uc_Key_counter = 1;
                                        gtt_Navi.sc_Jog_counter = 0;
                                        gtt_Navi.uc_Joint_search = OFF;
                                        gtt_Navi.uc_Cansel = ON;
                                    }
                                }
                                if (gtt_Navi.uc_Key_counter == 3) //溶接姿勢
                                {
                                    gtt_Navi.uc_Direction_set = ON; //溶接姿勢確定
                                    gtt_Navi.uc_Direction_address = guc_Navi_direction_code[gtt_Navi.sc_Jog_counter];
                                    if (gtt_Navi.uc_Direction_address == 24) //継ぎ手、溶接姿勢取り消し
                                    {
                                        gtt_Navi.uc_Joint_set = OFF;
                                        gtt_Navi.uc_Joint_address = 0x00;
                                        gtt_Navi.uc_Direction_set = OFF;
                                        gtt_Navi.uc_Direction_address = 0x00;
                                        gtt_Navi.uc_Key_counter = 2;
                                        gtt_Navi.sc_Jog_counter = 0;
                                        gtt_Navi.uc_Direction_search = OFF;
                                        gtt_Navi.uc_Cansel = ON;
                                    }
                                }
                                if (gtt_Navi.uc_Key_counter == 4) //パルス
                                {
                                    gtt_Navi.uc_Pulse_set = ON; //パルス確定
                                    gtt_Navi.uc_Pulse_address = guc_Navi_pulse_code[gtt_Navi.sc_Jog_counter];
                                    if (gtt_Navi.uc_Pulse_address == 24) //溶接姿勢、パルス取り消し
                                    {
                                        gtt_Navi.uc_Direction_set = OFF;
                                        gtt_Navi.uc_Direction_address = 0x00;
                                        gtt_Navi.uc_Pulse_set = OFF;
                                        gtt_Navi.uc_Pulse_address = 0x00;
                                        gtt_Navi.uc_Key_counter = 3;
                                        gtt_Navi.sc_Jog_counter = 0;
                                        gtt_Navi.uc_Pulse_search = OFF;
                                        gtt_Navi.uc_Cansel = ON;
                                    }
                                }
                                if (gtt_Navi.uc_Cansel == OFF)
                                {
                                    gtt_Navi.uc_Key_counter++;
                                } else {
                                    gtt_Navi.uc_Cansel = OFF;
                                }
                                gtt_Navi.sc_Jog_counter = 0;
                                gtt_Navi.uc_Jog_set_key = false;
                                 
                            }
                            //***** 検索 *****
                            //板厚
                            if (gtt_Navi.uc_Key_counter == 1 && gtt_Navi.uc_Thickness_search == OFF && gtt_Navi.uc_Material_set == ON)
                            {
                                gtt_Navi.uc_Thickness_search = ON;
                                //溶接ナビテーブルの板厚の検索
                                {
                                  //PNAVITABLE  pNT = (PNAVITABLE)0x00C0000;
                                  PNAVITABLE  pNT = (PNAVITABLE)NaviTable;	// 2019.06.10
                                  PNAVICODE   pNaviCode;
                                  int         Cnt;
                                  int         pi_Navi_counter;
                                  unsigned char   puc_Navi_value;
                                  unsigned char   puc_Navi_min;
                                  unsigned char   i,s,t,j;

                                  gui_Navi_table_code_counter = 0;

                                  for(Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++)
                                  {
                                      guc_Navi_code_work[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  {
                                      guc_Navi_thickness_code[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt <=NAVITBLCNT ; Cnt++)
                                  {
                                      pNaviCode = &pNT->NaviCode;
                                      if (pNaviCode->material == 0xFF) break;
                                      if (pNaviCode->material == gtt_Navi.uc_Material_address)
                                      {
                                          guc_Navi_code_work[gui_Navi_table_code_counter]    = pNaviCode->thickness;           //板厚
                                          gui_Navi_table_code_counter++;
                                      }
                                      pNT++;                                     //次のテーブルへ
                                  }
                                  pi_Navi_counter =  gui_Navi_table_code_counter;
     
                                  //ソート処理
                                  for ( i = 0 ; i < pi_Navi_counter-1 ; i++)
                                  {
                                       puc_Navi_min = guc_Navi_code_work[i];
                                       s = i;
                                       for (j = i + 1 ; j < pi_Navi_counter ; j++)
                                       {
                                            if (guc_Navi_code_work[j] < puc_Navi_min)
                                            {
                                                puc_Navi_min = guc_Navi_code_work[j];
                                                s = j;
                                            }
                                        }
                                        t = guc_Navi_code_work[i];
                                        guc_Navi_code_work[i] = guc_Navi_code_work[s];
                                        guc_Navi_code_work[s] = t;
                                  }
                                  //同値まとめ処理
                                  puc_Navi_value    =  guc_Navi_code_work[0];
                                  guc_Navi_thickness_code[0] = guc_Navi_code_work[0];
                                  guc_Navi_thickness_counter = 0;
                                  //for ( Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  for ( Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++) //2009.02.20
                                  {
                                     if (puc_Navi_value != guc_Navi_code_work[Cnt])
                                     {
                                         guc_Navi_thickness_counter++;
                                         puc_Navi_value = guc_Navi_code_work[Cnt];
                                         guc_Navi_thickness_code[guc_Navi_thickness_counter] = guc_Navi_code_work[Cnt];
                                     }
                                  }
                                  guc_Navi_thickness_code[guc_Navi_thickness_counter] = 24;
                                }
                                
                            }
                            //継ぎ手
                            if (gtt_Navi.uc_Key_counter == 2 && gtt_Navi.uc_Joint_search == OFF && gtt_Navi.uc_Thickness_set == ON)
                            {
                                gtt_Navi.uc_Joint_search = ON;
                                //溶接ナビテーブルの継ぎ手の検索
                                {
                                  //PNAVITABLE  pNT = (PNAVITABLE)0x00C0000;
                                  PNAVITABLE  pNT = (PNAVITABLE)NaviTable;	// 2019.06.10
                                  PNAVICODE   pNaviCode;
                                  int         Cnt;
                                  int         pi_Navi_counter;
                                  unsigned char   puc_Navi_value;
                                  unsigned char   puc_Navi_min;
                                  unsigned char   i,s,t,j;

                                  gui_Navi_table_code_counter = 0;

                                  for(Cnt = 0 ; Cnt <=NAVITBLCNT ; Cnt++)
                                  {
                                      guc_Navi_code_work[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  {
                                      guc_Navi_joint_code[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++)
                                  {
                                      pNaviCode = &pNT->NaviCode;
                                      if (pNaviCode->material == 0xFF) break;
                                      if (pNaviCode->material == gtt_Navi.uc_Material_address && pNaviCode->thickness == gtt_Navi.uc_Thickness_address)
                                      {
                                          guc_Navi_code_work[gui_Navi_table_code_counter]    = pNaviCode->joint;           //継ぎ手
                                          gui_Navi_table_code_counter++;
                                      }
                                      pNT++;                                     //次のテーブルへ
                                  }
                                  pi_Navi_counter =  gui_Navi_table_code_counter;
     
                                  //ソート処理
                                  for ( i = 0 ; i < pi_Navi_counter-1 ; i++)
                                  {
                                       puc_Navi_min = guc_Navi_code_work[i];
                                       s = i;
                                       for (j = i + 1 ; j < pi_Navi_counter ; j++)
                                       {
                                            if (guc_Navi_code_work[j] < puc_Navi_min)
                                            {
                                                puc_Navi_min = guc_Navi_code_work[j];
                                                s = j;
                                            }
                                        }
                                        t = guc_Navi_code_work[i];
                                        guc_Navi_code_work[i] = guc_Navi_code_work[s];
                                        guc_Navi_code_work[s] = t;
                                  }
                                  //同値まとめ処理
                                  puc_Navi_value    =  guc_Navi_code_work[0];
                                  guc_Navi_joint_code[0] = guc_Navi_code_work[0];
                                  guc_Navi_joint_counter = 0;
                                  //for ( Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  for ( Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++) //2009.02.20
                                  {
                                     if (puc_Navi_value != guc_Navi_code_work[Cnt])
                                     {
                                         guc_Navi_joint_counter++;
                                         puc_Navi_value = guc_Navi_code_work[Cnt];
                                         guc_Navi_joint_code[guc_Navi_joint_counter] = guc_Navi_code_work[Cnt];
                                     }
                                  }
                                  guc_Navi_joint_code[guc_Navi_joint_counter] = 24;
                                }
                                
                            }
                            //溶接姿勢
                            if (gtt_Navi.uc_Key_counter == 3 && gtt_Navi.uc_Direction_search == OFF && gtt_Navi.uc_Joint_set == ON)
                            {
                                gtt_Navi.uc_Direction_search = ON;
                                //溶接ナビテーブルの溶接姿勢の検索
                                {
                                  //PNAVITABLE  pNT = (PNAVITABLE)0x00C0000;
                                  PNAVITABLE  pNT = (PNAVITABLE)NaviTable;	// 2019.06.10
                                  PNAVICODE   pNaviCode;
                                  int         Cnt;
                                  int         pi_Navi_counter;
                                  unsigned char   puc_Navi_value;
                                  unsigned char   puc_Navi_min;
                                  unsigned char   i,s,t,j;

                                  gui_Navi_table_code_counter = 0;

                                  for(Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++)
                                  {
                                      guc_Navi_code_work[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  {
                                      guc_Navi_direction_code[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt <=NAVITBLCNT ; Cnt++)
                                  {
                                      pNaviCode = &pNT->NaviCode;
                                      if (pNaviCode->material == 0xFF) break;
                                      if (pNaviCode->material == gtt_Navi.uc_Material_address && pNaviCode->thickness == gtt_Navi.uc_Thickness_address && pNaviCode->joint == gtt_Navi.uc_Joint_address)
                                      {
                                          guc_Navi_code_work[gui_Navi_table_code_counter]    = pNaviCode->direction;           //溶接姿勢
                                          gui_Navi_table_code_counter++;
                                      }
                                      pNT++;                                     //次のテーブルへ
                                  }
                                  pi_Navi_counter =  gui_Navi_table_code_counter;
     
                                  //ソート処理
                                  for ( i = 0 ; i < pi_Navi_counter-1 ; i++)
                                  {
                                       puc_Navi_min = guc_Navi_code_work[i];
                                       s = i;
                                       for (j = i + 1 ; j < pi_Navi_counter ; j++)
                                       {
                                            if (guc_Navi_code_work[j] < puc_Navi_min)
                                            {
                                                puc_Navi_min = guc_Navi_code_work[j];
                                                s = j;
                                            }
                                        }
                                        t = guc_Navi_code_work[i];
                                        guc_Navi_code_work[i] = guc_Navi_code_work[s];
                                        guc_Navi_code_work[s] = t;
                                  }
                                  //同値まとめ処理
                                  puc_Navi_value    =  guc_Navi_code_work[0];
                                  guc_Navi_direction_code[0] = guc_Navi_code_work[0];
                                  guc_Navi_direction_counter = 0;
                                  //for ( Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  for ( Cnt = 0 ; Cnt < gui_Navi_table_code_counter+1 ; Cnt++) //2009.02.20
                                  {
                                     if (puc_Navi_value != guc_Navi_code_work[Cnt])
                                     {
                                         guc_Navi_direction_counter++;
                                         puc_Navi_value = guc_Navi_code_work[Cnt];
                                         guc_Navi_direction_code[guc_Navi_direction_counter] = guc_Navi_code_work[Cnt];
                                     }
                                  }
                                  guc_Navi_direction_code[guc_Navi_direction_counter] = 24;
                                }
                                
                            }

                            //パルス
                            if (gtt_Navi.uc_Key_counter == 4 && gtt_Navi.uc_Pulse_search == OFF && gtt_Navi.uc_Direction_set == ON)
                            {
                                gtt_Navi.uc_Pulse_search = ON;
                                //溶接ナビテーブルのパルスの検索
                                {
                                  //PNAVITABLE  pNT = (PNAVITABLE)0x00C0000;
                                  PNAVITABLE  pNT = (PNAVITABLE)NaviTable;	// 2019.06.10
                                  PNAVICODE   pNaviCode;
                                  int         Cnt;
                                  int         pi_Navi_counter;
                                  unsigned char   puc_Navi_value;
                                  unsigned char   puc_Navi_min;
                                  unsigned char   i,s,t,j;

                                  gui_Navi_table_code_counter = 0;

                                  for(Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++)
                                  {
                                      guc_Navi_code_work[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  {
                                      guc_Navi_pulse_code[Cnt] = 0x00;
                                  }
                                  for(Cnt = 0 ; Cnt <=NAVITBLCNT ; Cnt++)
                                  {
                                      pNaviCode = &pNT->NaviCode;
                                      if (pNaviCode->material == 0xFF) break;
                                      if (pNaviCode->material == gtt_Navi.uc_Material_address && pNaviCode->thickness == gtt_Navi.uc_Thickness_address && pNaviCode->joint == gtt_Navi.uc_Joint_address && pNaviCode->direction == gtt_Navi.uc_Direction_address)
                                      {
                                          guc_Navi_code_work[gui_Navi_table_code_counter]    = pNaviCode->pulse;           //パルス
                                          gui_Navi_table_code_counter++;
                                      }
                                      pNT++;                                     //次のテーブルへ
                                  }
                                  pi_Navi_counter =  gui_Navi_table_code_counter;
     
                                  //ソート処理
                                  for ( i = 0 ; i < pi_Navi_counter-1 ; i++)
                                  {
                                       puc_Navi_min = guc_Navi_code_work[i];
                                       s = i;
                                       for (j = i + 1 ; j < pi_Navi_counter ; j++)
                                       {
                                            if (guc_Navi_code_work[j] < puc_Navi_min)
                                            {
                                                puc_Navi_min = guc_Navi_code_work[j];
                                                s = j;
                                            }
                                        }
                                        t = guc_Navi_code_work[i];
                                        guc_Navi_code_work[i] = guc_Navi_code_work[s];
                                        guc_Navi_code_work[s] = t;
                                  }
                                  //同値まとめ処理
                                  puc_Navi_value    =  guc_Navi_code_work[0];
                                  guc_Navi_pulse_code[0] = guc_Navi_code_work[0];
                                  guc_Navi_pulse_counter = 0;
                                  //for ( Cnt = 0 ; Cnt < 25 ; Cnt++)
                                  for ( Cnt = 0 ; Cnt < NAVITBLCNT ; Cnt++) //2009.02.20
                                  {
                                     if (puc_Navi_value != guc_Navi_code_work[Cnt])
                                     {
                                         guc_Navi_pulse_counter++;
                                         puc_Navi_value = guc_Navi_code_work[Cnt];
                                         guc_Navi_pulse_code[guc_Navi_pulse_counter] = guc_Navi_code_work[Cnt];
                                     }
                                  }
                                  guc_Navi_pulse_code[guc_Navi_pulse_counter] = 24;
                                }
                                
                            }


                            //ＪＯＧ最大値の決定
                            if (gtt_Navi.uc_Key_counter == 0 ) //材質選択
                            {
                                if (gtt_Navi.sc_Jog_counter > guc_Navi_material_counter)
                                {
                                    gtt_Navi.sc_Jog_counter = guc_Navi_material_counter;
                                }
                            }
                            if (gtt_Navi.uc_Key_counter == 1 ) //板厚選択
                            {
                                if (gtt_Navi.sc_Jog_counter > guc_Navi_thickness_counter)
                                {
                                    gtt_Navi.sc_Jog_counter = guc_Navi_thickness_counter;
                                }
                            }
                            if (gtt_Navi.uc_Key_counter == 2 ) //継ぎ手選択
                            {
                                if (gtt_Navi.sc_Jog_counter > guc_Navi_joint_counter)
                                {
                                    gtt_Navi.sc_Jog_counter = guc_Navi_joint_counter;
                                }
                            }
                            if (gtt_Navi.uc_Key_counter == 3 ) //溶接姿勢選択
                            {
                                if (gtt_Navi.sc_Jog_counter > guc_Navi_direction_counter)
                                {
                                    gtt_Navi.sc_Jog_counter = guc_Navi_direction_counter;
                                }
                            }
                            if (gtt_Navi.uc_Key_counter == 4 ) //パルス選択
                            {
                                if (gtt_Navi.sc_Jog_counter > guc_Navi_pulse_counter)
                                {
                                    gtt_Navi.sc_Jog_counter = guc_Navi_pulse_counter;
                                }
                            }

                            //最終検索（溶接条件の呼び出し）
                            if (gtt_Navi.uc_Material_set == ON && gtt_Navi.uc_Thickness_set == ON && gtt_Navi.uc_Joint_set == ON && gtt_Navi.uc_Direction_set == ON && gtt_Navi.uc_Pulse_set == ON)
                            {
                                {
                                  //PNAVITABLE  pNT = (PNAVITABLE)0x00C0000;
                                  PNAVITABLE  pNT = (PNAVITABLE)NaviTable;	// 2019.06.10
                                  PNAVICODE   pNaviCode;
                                  PNAVICOND   pNaviCond;
                                  int         Cnt;
                                  for(Cnt = 0 ; Cnt <=NAVITBLCNT ; Cnt++)
                                  {
                                      pNaviCode = &pNT->NaviCode;
                                      pNaviCond = &pNT->NaviCond;
                                      if (pNaviCode->material == 0xFF) break;
                                      if (pNaviCode->material == gtt_Navi.uc_Material_address && pNaviCode->thickness == gtt_Navi.uc_Thickness_address && pNaviCode->joint == gtt_Navi.uc_Joint_address && pNaviCode->direction == gtt_Navi.uc_Direction_address && pNaviCode->pulse == gtt_Navi.uc_Pulse_address)
                                      {
                                          //<><><> ナビ利用可否判定 2010.01.21 <><><>
                                          //ナビテーブルの電流が１つでも出力電流制限値にかかるとナビは利用できない
                                          gtt_Navi.uc_Navi_limit = OFF;
                                          switch (pNaviCond->Pulse_mode)
                                          {
                                                  case 0://パルス無
                                                         if (pNaviCond->Crater_mode == 0)                                         //クレータ無
                                                         {
                                                             if (pNaviCond->Main_current > MAX_CURRENT)
                                                             {
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             }
                                                         } else if (pNaviCond->Crater_mode == 1 || pNaviCond->Crater_mode == 2){  //クレータ有
                                                             if (pNaviCond->Init_current > MAX_CURRENT) {          //初期電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             } else if (pNaviCond->Main_current > MAX_CURRENT) {   //本電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             } else if (pNaviCond->Crater_current > MAX_CURRENT) { //クレータ電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             }
                                                         }
                                                         break;
                                                  case 1://パルス有
                                                         if (pNaviCond->Crater_mode == 0)                                         //クレータ無
                                                         {
                                                             if (pNaviCond->Main_current > MAX_CURRENT) {          //本電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             } else if (pNaviCond->Pulse_current > MAX_CURRENT) {  //パルス電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             }
                                                         } else if (pNaviCond->Crater_mode == 1 || pNaviCond->Crater_mode == 2){  //クレータ有
                                                             if (pNaviCond->Init_current > MAX_CURRENT) {          //初期電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             } else if (pNaviCond->Main_current > MAX_CURRENT) {   //本電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             } else if (pNaviCond->Crater_current > MAX_CURRENT) { //クレータ電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             } else if (pNaviCond->Pulse_current > MAX_CURRENT) {  //パルス電流
                                                                 gtt_Navi.uc_Navi_limit = ON;
                                                             }
                                                         }
                                                         break;
                                                  default:
                                                         break;
                                          }
                                          //<><><><><><><><><><><><><><><><><><><><><>
                                          if (gtt_Navi.uc_Navi_limit == OFF)
                                          {
                                          		gtt_Internal_pack.Data.In.usWeldingCurr   = pNaviCond->Main_current;        //本電流
                                          		gtt_Internal_pack.Data.In.usWeldingInitCurr   = pNaviCond->Init_current;
                                          		gtt_Internal_pack.Data.In.usWeldingCratCurr   = pNaviCond->Crater_current; 
                                          		guc_Method_condition_counter              = pNaviCond->Method;
                                          		guc_Method_condition_data                 = pNaviCond->Method;
                    	                  		guc_Pulse_mode_counter                    = pNaviCond->Pulse_mode;//2009.01.19
                    	                  		guc_Pulse_mode_data                       = pNaviCond->Pulse_mode;//2009.01.19
                                          		guc_Crater_mode_counter                   = pNaviCond->Crater_mode;//2009.01.19
                                          		gtt_Internal_pack.Data.In.usIP            = pNaviCond->Pulse_current; //2009.02.18
                                          		gtt_Internal_pack.Data.In.usPulseDuty     = pNaviCond->Pulse_duty;    //2009.02.18
                                          		gtt_Internal_pack.Data.In.usPulseFreq     = pNaviCond->Pulse_frequency; //2009.02.18
                                          		gtt_Internal_pack.Data.In.ucCleaningDuty  = pNaviCond->AC_cleaning_duty; //2009.02.18
                                          		gtt_Internal_pack.Data.In.usAcFreq        = pNaviCond->AC_frequency;     //2009.02.18
                                          		gtt_Internal_pack.Data.In.ucMixFreq       = pNaviCond->MIX_frequency;    //2009.02.18
                                          		gtt_Internal_pack.Data.In.ucMixAcRatio    = pNaviCond->MIX_duty;         //2009.02.18
                                          		gtt_Internal_pack.Data.In.sPreFlowTime    = pNaviCond->Pre_flow;     //2009.02.20
                                          		gtt_Internal_pack.Data.In.sAfterFlowTime  = pNaviCond->After_flow;   //2009.02.20
                                          		gtt_Internal_pack.Data.In.sUpSlopTime     = pNaviCond->Up_slop;      //2009.02.20
                                          		gtt_Internal_pack.Data.In.sDownSlopTime   = pNaviCond->Down_slop;    //2009.02.20
                                          
                                          		guc_Ac_wave_counter                       = pNaviCond->AC_wave;      //2010.01.12
//-----------------------------------------------------------------------------------------------------------------------------------------------
// <NAVI Enhancements(Phase 1)> 2011.10.26 by @Tny
												gtt_Navi.us_Gas_Navi						= pNaviCond->Gas_navi;			// ガス流量
												gtt_Navi.us_Filler_navi						= pNaviCond->Filler_navi;		// フィラー径
												gtt_Navi.us_Electroad_navi					= pNaviCond->Electroad_navi;	// 電極径
												gtt_Navi.us_El_rd_angle_navi				= pNaviCond->El_rd_angle_navi;	// 電極先端角度
												gtt_Navi.b_Navi_Disp						= true;							// ナビ表示フラグ：表示
//-----------------------------------------------------------------------------------------------------------------------------------------------
                                          		//**** 制限電流セット 2009.02.19 *****************************************
#if true //2010.01.21 del 電流指令値が１つでも制限値を超える場合は利用できないので不要		【復活】ナビ設定後の最大最小指令値の設定が手棒モードになっていたので再設定が必要	Ver2.02 2012.05.23
                                          		if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
                                          		{
                                              		gss_Max_current = MAX_CURRENT;
                                              		gss_Min_current = MIN_CURRENT;
                                          		}
                                          		if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
                                          		{
                                              		gss_Max_current = MAX_CURRENT;
                                              		gss_Min_current = MIN_CURRENT_AC;	// MIN_CURRENT_AC_MIX;
                                              		// 2009.03.13 
                    		                  		if (guc_Ac_wave_counter == 1) //ハードＡＣ 
                                              		{
                                                  		gss_Max_current = MAX_CURRENT;
														gss_Min_current = MIN_CURRENT_AC_HARD;	// MIN_CURRENT_AC_MIX;
                                              		}
                    		                  		if (guc_Ac_wave_counter == 2) //ソフトＡＣ 
                                              		{
                                                  		gss_Max_current = MAX_CURRENT_AC_SOFT;
                                                  		gss_Min_current = MIN_CURRENT_AC;	// MIN_CURRENT_AC_MIX;
                                              		}
                                              		//
                                          		}
                                          		if (guc_Method_condition_data == STD_MIX_METHOD) //2009.03.17
                                          		{
                                              		gss_Max_current = MAX_CURRENT;
                                              		gss_Min_current = MIN_CURRENT_AC;	// MIN_CURRENT_AC_MIX;
                                          		}
                                          		if (guc_Method_condition_data == STD_HAND_METHOD) //2009.03.06
                                          		{
                                              		gss_Max_current = MAX_CURRENT_HAND;
                                              		gss_Min_current = MIN_CURRENT_HAND;
                                          		}
                                          		//初期
                   	                      		if (gtt_Internal_pack.Data.In.usWeldingInitCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                  	                      		{
       		    			                  		gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Max_current;
       					                  		}
       					                  		if (gtt_Internal_pack.Data.In.usWeldingInitCurr < gss_Min_current)
                   	                      		{
      		    			                  		gtt_Internal_pack.Data.In.usWeldingInitCurr = gss_Min_current;
       					                  		}
                                          		//本溶接
                   	                      		if (gtt_Internal_pack.Data.In.usWeldingCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	                      		{
      		    			                  		gtt_Internal_pack.Data.In.usWeldingCurr = gss_Max_current;
       					                  		}
       					                  		if (gtt_Internal_pack.Data.In.usWeldingCurr < gss_Min_current)
                   	                      		{
      		    			                  		gtt_Internal_pack.Data.In.usWeldingCurr = gss_Min_current;
       					                  		}
                                          		//クレータ
                   	                      		if (gtt_Internal_pack.Data.In.usWeldingCratCurr >= gss_Max_current) //2010.01.19 ">" -> ">="
                   	                      		{
       		    			                  		gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Max_current;
       					                  		}
       					                  		if (gtt_Internal_pack.Data.In.usWeldingCratCurr < gss_Min_current)
                   	                      		{
       		    			                  		gtt_Internal_pack.Data.In.usWeldingCratCurr = gss_Min_current;
       					                  		}
                                          		//パルス電流
                       	                  		if (gtt_Internal_pack.Data.In.usIP >= gss_Max_current) //2010.01.19 ">" -> ">="
                       	                  		{
        		    	                      		gtt_Internal_pack.Data.In.usIP = gss_Max_current;
        				                  		}
        				                  		if (gtt_Internal_pack.Data.In.usIP < gss_Min_current)
                       	                  		{
        		    	                      		gtt_Internal_pack.Data.In.usIP = gss_Min_current;
        				                  		}
#endif
                                          		//************************************************************************
                                          		//***** 可変パラメータ反映 2009.02.23 *****
#if 0 //2019.03.15 ihara del
                                          		_union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty; //2009.02.16
                                          		//_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //ＡＣ周波数反映 2009.03.27
                                          		_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //ＡＣ周波数の反映 2009.12.29
                                          		//_union.Nrm.CalParm[66 - 1].c = gtt_Internal_pack.Data.In.ucMixFreq; //ＭＩＸ周波数反映 2009.03.27
                                          		_union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10; //ＭＩＸ周波数反映 2009.03.31
                                          		_union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio; //ＭＩＸ比率反映 2009.03.27
                                          		//_union.Nrm.CalParm[69 - 1].c = gtt_Internal_pack.Data.In.usPulseFreq; //パルス周波数反映 2009.03.27
                                          		_union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10; //パルス周波数反映 2009.03.31
                                          		_union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty; //パルス幅反映 2009.03.27
#endif
                                          		//***** パルスモードの切り替え処理 2009.02.27*****
#if 0 //2009.03.27 del
                                          		if (guc_Pulse_mode_counter >= 1 && gtt_Internal_pack.Data.In.usPulseFreq > 50)
                                          		{
                                              		_union.Nrm.CalParm[65 - 1].c = 1;
                                          		} else {
                                              		_union.Nrm.CalParm[65 - 1].c = 0;
                                          		}
#endif
                                          		//************************************************

                                          		//交流５Hz制限 2009.03.02
#if 0 //2009.03.31 del
                                          		if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.03.02
                                          		{
                                              		if (gtt_Internal_pack.Data.In.usPulseFreq >= 50)
                                              		{
                                                  		gtt_Internal_pack.Data.In.usPulseFreq = 50;
                                              		}
                                           		}
#endif

                                          		gss_Select_dital[P_MILD_PULSE] = 0; //2010.01.20 ナビ呼び出し時は溶接が変わってしまうため無効にする。
                                                gss_Select_dital[P_ARC_ASSIST] = 0; //2010.03.18
                                                
              		                      		gtt_Ctrl_flag.Param_change = ON; //2009.04.01

                                          		gtt_Table_key.Change_flag = ON; //2009.02.23
                                          		guc_Jog_set_key = true; //ナビに行くと確定させることにする。200.01.16
                                          } else {
                                                gtt_Navi.uc_Key_counter = 5;
                                          }
                                      }
                                      pNT++;                                     //次のテーブルへ
                                  }
                                }
                            }


                        } else {
                            gtt_Navi.uc_Key_counter = 0;
                            gtt_Navi.sc_Jog_counter = 0;
                            gtt_Navi.uc_Material_set = OFF;
                            gtt_Navi.uc_Thickness_set = OFF;
                            gtt_Navi.uc_Thickness_search = OFF;
                            gtt_Navi.uc_Joint_set = OFF;
                            gtt_Navi.uc_Joint_search = OFF;
                            gtt_Navi.uc_Direction_set = OFF;
                            gtt_Navi.uc_Direction_search = OFF;
                            gtt_Navi.uc_Pulse_set = OFF;
                            gtt_Navi.uc_Pulse_search = OFF;
                            gtt_Navi.uc_Navi_limit = OFF; //2010.01.21
                        }
//--------------------------------------------------------------------
//BP4 Phase15 by @Tny 2009.02.25
						}
//--------------------------------------------------------------------
                    



           } else { //技術・サービスマンメニュー
           }
     }
             //**************************************************************************************************
     return;
  }











//------ Phase21 by @Tny 2008/10/02 ------
#if false
//
// 転送元データセット処理
//
static void SetMemCopy(unsigned char area_no)
{
    switch(area_no){
        case 1:{ // 溶接条件データ系
                unsigned char   i,j;
                for(i=0;i<CH;i++){
                    gtt_WeldingAllCondition.Data[i].guc_Write_check_flag = guc_Write_check_flag[i];
                    if(guc_Write_check_flag[i] == true){
                        ch_play_class(i);
                        gtt_WeldingAllCondition.Data[i].guc_Material_condition_counterc = guc_Material_condition_counter;
                        gtt_WeldingAllCondition.Data[i].guc_Material_condition_datac    = guc_Material_condition_data;
                        gtt_WeldingAllCondition.Data[i].guc_Wire_condition_counterc     = guc_Wire_condition_counter;
                        gtt_WeldingAllCondition.Data[i].guc_Wire_condition_datac        = guc_Wire_condition_data;
                        gtt_WeldingAllCondition.Data[i].guc_Method_condition_counterc   = guc_Method_condition_counter;
                        gtt_WeldingAllCondition.Data[i].guc_Method_condition_datac      = guc_Method_condition_data;
                        gtt_WeldingAllCondition.Data[i].guc_Okcv_select_flag            = guc_Okcv_select_flag;
                        gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_data             = gs_Okcv_adjust_data;
                        gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_init_data        = gs_Okcv_adjust_init_data;
                        gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_crat_data        = gs_Okcv_adjust_crat_data;
                        gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_wave_data        = gs_Okcv_adjust_wave_data;
                        gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_start_data       = gs_Okcv_adjust_start_data;
                        gtt_WeldingAllCondition.Data[i].gus_Weld_current                = gus_Weld_current;
                        gtt_WeldingAllCondition.Data[i].gus_Weld_voltage                = gus_Weld_voltage;
                        gtt_WeldingAllCondition.Data[i].gus_Init_current                = gus_Init_current;
                        gtt_WeldingAllCondition.Data[i].gus_Init_voltage                = gus_Init_voltage;
                        gtt_WeldingAllCondition.Data[i].gus_Crat_current                = gus_Crat_current;
                        gtt_WeldingAllCondition.Data[i].gus_Crat_voltage                = gus_Crat_voltage;
                        //gtt_WeldingAllCondition.Data[i].gus_Wave_current                = gus_Wave_current;
                        //gtt_WeldingAllCondition.Data[i].gus_Wave_voltage                = gus_Wave_voltage;
                        //gtt_WeldingAllCondition.Data[i].gus_Start_current               = gus_Start_current;
                        //gtt_WeldingAllCondition.Data[i].gus_Start_voltage               = gus_Start_voltage;
                        gtt_WeldingAllCondition.Data[i].guc_Pulse_mode_data             = guc_Pulse_mode_data;
                        gtt_WeldingAllCondition.Data[i].guc_Pulse_mode_counter          = guc_Pulse_mode_counter;
                        gtt_WeldingAllCondition.Data[i].guc_Pulse_type_data             = guc_Pulse_type_data;
                        gtt_WeldingAllCondition.Data[i].guc_Crater_mode_counter         = guc_Crater_mode_counter;
						// Phase28 by @Tny 2008.11.21
						gtt_WeldingAllCondition.Data[i].guc_Ext_condition_counter		= guc_Ext_condition_counter;  //2008.11.10
						gtt_WeldingAllCondition.Data[i].guc_Ext_condition_data			= guc_Ext_condition_data;     //2008.11.10
                        for(j=0;j<USER_PARAMETER_NO;j++){
                            // 波形パラメータ系
                            gtt_WeldingAllCondition.Data[i].ss_User_param[j]    = gtt_Special_menu.ss_User_param[j];
                        }
                        for(j=0;j<(SELECT_DITAL_MAX+1);j++){
                            // 詳細パラメータ系
                            gtt_WeldingAllCondition.Data[i].gss_Select_dital[j] = gss_Select_dital[j];
                        }
                    }
                }
                ch_play_class(0);   // 最終値はＣＨ０とする
                gtt_WeldingAllCondition.guc_Controller_lock = guc_Controller_lock;
                gtt_WeldingAllCondition.guc_Pass_word       = guc_Pass_word;
                // ＩＩＦデータ系
                for(i=0;i<17;i++){	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                    gtt_WeldingAllCondition.guc_Out_port[i]     = guc_Out_port[0][i];
                    gtt_WeldingAllCondition.guc_In_port[i]      = guc_In_port[0][i];
                    gtt_WeldingAllCondition.guc_Analog_port[i]  = guc_Analog_port[0][i];
                }
                break;}
        case 2:{ // サービスマンメニューデータ系
                unsigned char   i;
                ch_play_class(0);   // ＣＨ０をダミーリード
                for(i=0;i<SERVICE_DATA_NO;i++){
                    gtt_ServiceData.ss_Service_data[i]  = gtt_Special_menu.ss_Service_data[i];
                }
            	{// エラー履歴データ系
            		int		i;
            		uchar	*SrcTableAddres     = &gtt_Error_History.vStart;	            // 転送元テーブルの開始アドレス
            		uchar	*SrcTableEndAddres  = &gtt_Error_History.vEnd;	                // 転送元テーブルの終了アドレス
            		uchar	*DestTableAddres    = &gtt_ServiceData.Error_History.vStart;    // 転送先テーブルの開始アドレス
            		uchar	*DestTableEndAddres = &gtt_ServiceData.Error_History.vEnd;      // 転送先テーブルの終了アドレス
            		i = 0;
            		do{
            			*(DestTableAddres+i) = *(SrcTableAddres+i);  //
            			++i;					                    // 転送する該当エリアのアドレス更新
            		}while((SrcTableAddres+i) <= SrcTableEndAddres);	// 転送するテーブルの範囲内？
            	}
                break;}
    }
}
//
// 転送先データセット処理
//
static void GetMemCopy(unsigned char area_no)
{
    switch(area_no){
        case 1:{ // 溶接条件データ系
                unsigned char   i,j;

                for(i=0;i<CH;i++){
                    guc_Write_check_flag[i] = gtt_WeldingAllCondition.Data[i].guc_Write_check_flag;
                    if(guc_Write_check_flag[i] == true){
                        guc_Material_condition_counter    = gtt_WeldingAllCondition.Data[i].guc_Material_condition_counterc;
                        guc_Material_condition_data       = gtt_WeldingAllCondition.Data[i].guc_Material_condition_datac;
                        guc_Wire_condition_counter        = gtt_WeldingAllCondition.Data[i].guc_Wire_condition_counterc;
                        guc_Wire_condition_data           = gtt_WeldingAllCondition.Data[i].guc_Wire_condition_datac;
                        guc_Method_condition_counter      = gtt_WeldingAllCondition.Data[i].guc_Method_condition_counterc;
                        guc_Method_condition_data         = gtt_WeldingAllCondition.Data[i].guc_Method_condition_datac;
                        guc_Okcv_select_flag              = gtt_WeldingAllCondition.Data[i].guc_Okcv_select_flag;
                        gs_Okcv_adjust_data               = gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_data;
                        gs_Okcv_adjust_init_data          = gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_init_data;
                        gs_Okcv_adjust_crat_data          = gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_crat_data;
                        gs_Okcv_adjust_wave_data          = gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_wave_data;
                        gs_Okcv_adjust_start_data         = gtt_WeldingAllCondition.Data[i].gs_Okcv_adjust_start_data;
                        gus_Weld_current                  = gtt_WeldingAllCondition.Data[i].gus_Weld_current;
                        gus_Weld_voltage                  = gtt_WeldingAllCondition.Data[i].gus_Weld_voltage;
                        gus_Init_current                  = gtt_WeldingAllCondition.Data[i].gus_Init_current;
                        gus_Init_voltage                  = gtt_WeldingAllCondition.Data[i].gus_Init_voltage;
                        gus_Crat_current                  = gtt_WeldingAllCondition.Data[i].gus_Crat_current;
                        gus_Crat_voltage                  = gtt_WeldingAllCondition.Data[i].gus_Crat_voltage;
                        //gus_Wave_current                  = gtt_WeldingAllCondition.Data[i].gus_Wave_current;
                        //gus_Wave_voltage                  = gtt_WeldingAllCondition.Data[i].gus_Wave_voltage;
                        //gus_Start_current                 = gtt_WeldingAllCondition.Data[i].gus_Start_current;
                        //gus_Start_voltage                 = gtt_WeldingAllCondition.Data[i].gus_Start_voltage;
                        guc_Pulse_mode_data               = gtt_WeldingAllCondition.Data[i].guc_Pulse_mode_data;
                        guc_Pulse_mode_counter            = gtt_WeldingAllCondition.Data[i].guc_Pulse_mode_counter;
                        guc_Pulse_type_data               = gtt_WeldingAllCondition.Data[i].guc_Pulse_type_data;
                        guc_Crater_mode_counter           = gtt_WeldingAllCondition.Data[i].guc_Crater_mode_counter;
						// Phase28 by @Tny 2008.11.21
						guc_Ext_condition_counter		  = gtt_WeldingAllCondition.Data[i].guc_Ext_condition_counter;  //2008.11.10
						guc_Ext_condition_data			  = gtt_WeldingAllCondition.Data[i].guc_Ext_condition_data;     //2008.11.10
                        for(j=0;j<USER_PARAMETER_NO;j++){
                            // 波形パラメータ系
                            gtt_Special_menu.ss_User_param[j]   = gtt_WeldingAllCondition.Data[i].ss_User_param[j];
                        }
                        for(j=0;j<(SELECT_DITAL_MAX+1);j++){
                            // 詳細パラメータ系
                            gss_Select_dital[j]                 = gtt_WeldingAllCondition.Data[i].gss_Select_dital[j];
                        }
                        // 当該チャンネル記憶のため、特例としてgtt_Internal_pack.Dataへの直接代入を行う
                        //
                        gtt_Internal_pack.Data.In.fWireMaterial.ALL     = guc_Material_condition_data;
                        gtt_Internal_pack.Data.In.fWireDiameter.ALL     = guc_Wire_condition_data;
                        gtt_Internal_pack.Data.In.fWelding.ALL          = guc_Method_condition_data;
                        gtt_Internal_pack.Data.In.usWeldingCurr         = gus_Weld_current;
                        gtt_Internal_pack.Data.In.usWeldingVolt         = gus_Weld_voltage;
                        gtt_Internal_pack.Data.In.usWeldingInitCurr     = gus_Init_current;
                        gtt_Internal_pack.Data.In.usWeldingInitVolt     = gus_Init_voltage;
                        gtt_Internal_pack.Data.In.usWeldingCratCurr     = gus_Crat_current;
                        gtt_Internal_pack.Data.In.usWeldingCratVolt     = gus_Crat_voltage;
                        //gtt_Internal_pack.Data.In.usWeldingWaveCurr     = gus_Wave_current;
                        //gtt_Internal_pack.Data.In.usWeldingWaveVolt     = gus_Wave_voltage;
                        //gtt_Internal_pack.Data.In.usWeldingStartCurr    = gus_Start_current;
                        //gtt_Internal_pack.Data.In.usWeldingStartVolt    = gus_Start_voltage;
                        ch_rec_class(i);
                    }
                    else{ // 当該チャンネルの記憶データ削除
                        ch_rec_class((i + MEMORY_DELETE_CH));  // 記憶チャンネル削除識別子の付加
                    }
                }
                ch_play_class(0);   // 最終値はＣＨ０とする
                guc_Controller_lock = gtt_WeldingAllCondition.guc_Controller_lock;
                guc_Pass_word       = gtt_WeldingAllCondition.guc_Pass_word;
                // ＩＩＦデータ系
                for(i=0;i<17;i++){	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
                    guc_Out_port[0][i]      = gtt_WeldingAllCondition.guc_Out_port[i];
                    guc_In_port[0][i]       = gtt_WeldingAllCondition.guc_In_port[i];
                    guc_Analog_port[0][i]   = gtt_WeldingAllCondition.guc_Analog_port[i];
                }
                ch_rec_class(0);    // 最終書き込み
                break;}
        case 2:{ // サービスマンメニューデータ系
                unsigned char   i;
                ch_play_class(0);   // ＣＨ０をダミーリード
                for(i=0;i<SERVICE_DATA_NO;i++){
                    gtt_Special_menu.ss_Service_data[i] = gtt_ServiceData.ss_Service_data[i];
                }
                ch_rec_class(0);    // 最終書き込み
            	{// エラー履歴データ系
            		int		i;
            		uchar	*SrcTableAddres      = &gtt_ServiceData.Error_History.vStart;   // 転送元テーブルの開始アドレス
            		uchar	*SrcTableEndAddres   = &gtt_ServiceData.Error_History.vEnd;     // 転送元テーブルの終了アドレス
            		uchar	*DestTableAddres     = &gtt_Error_History.vStart;	            // 転送先テーブルの開始アドレス
            		uchar	*DestTableEndAddres  = &gtt_Error_History.vEnd;	                // 転送先テーブルの終了アドレス
            		i = 0;
            		do{
            			*(DestTableAddres+i) = *(SrcTableAddres+i);  //
            			++i;					                    // 転送する該当エリアのアドレス更新
            		}while((SrcTableAddres+i) <= SrcTableEndAddres);	// 転送するテーブルの範囲内？
                    ch_rec_class(WRITE_ERROR_HISTORY_CH);    // エラー履歴テーブルの書き込み
            	}
                break;}
    }
}
#endif
//-----------------------------------------
//-----------------------------------------------------------------------------
// BP4 Phase5 by @Tny 2009.01.21	BP4 Phase13 by @Tny 2009.02.23
/***
**  ID     = StringInput_Rcv
**  name   = 文字列入力処理
**  func   = 文字列の入力を行う
**  called = void StringInput_Rcv(ubool Sw1, ubool Sw2, unsigned char *StringStorageArea, unsigned short Length);
**  io     = Sw1				: ubool             : モードキー入力フラグ（true=モードキーが押された）
**           Sw2				: ubool             : ＪＯＧ回転orＪＯＧクリック（true=クリック／false=回転）
**           StringStorageArea	: unsigned char *  : 入力された文字列を格納するエリアの先頭アドレス
**           Length				: unsigned short   : 入力文字数
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2009/01/19 by 谷川真也
***/
void StringInput_Rcv(ubool Sw1, ubool Sw2, unsigned char *StringStorageArea, unsigned short Length)
{
	if(guc_StringInput == 1){	// 文字列入力処理実行中？
//		unsigned short	Index = (unsigned short)strlen(SelectCharacterSrc);
		unsigned short	Index = (unsigned short)strlen((const char *)SelectCharacter);	// BP4 Phase13 by @Tny 2009.02.23

		if(Sw1){	// モードキーが押された？
			guc_StringInput	= 2;
		}
		else{
			if(Sw2){	// ＪＯＧクリック
				unsigned char Data = SelectCharacter[gss_SelectCharIndex];
				// 文字入力処理の終了確認（StringInputEndCharacter('#')文字で入力終了）
				if(Data == StringInputEndCharacter){
					guc_StringInput	= 2;
				}
				else if(Data == DeleteCode){
					if(gus_InputCharIndex > 0) --gus_InputCharIndex;
					*(StringStorageArea + gus_InputCharIndex)		= 0x00;
				}
				else{
					*(StringStorageArea + gus_InputCharIndex)		= Data;
					*(StringStorageArea + gus_InputCharIndex + 1)	= 0x00;
					if(++gus_InputCharIndex >= Length){
						guc_StringInput	= 2;
					}
				}
			}
			else{	// ＪＯＧ回転
//			    gss_SelectCharIndex = gss_SelectCharIndex + ((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1 * -1);	// 回転方向逆転
			    gss_SelectCharIndex = gss_SelectCharIndex + ((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog1);
				if(gss_SelectCharIndex < 0)					gss_SelectCharIndex	= 0;
				else if(gss_SelectCharIndex >= (Index - 1))	gss_SelectCharIndex	= (Index - 2);
			}
		}
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// <IIF NEW>	2009.11.27
/***
**  ID     = IIF_ChangeSetting
**  name   = ＩＩＦ設定変更確認処理
**  func   = ＩＩＦ設定データの変更確認を行う
**  called = ubool IIF_ChangeSetting(void);
**  io     = none
**  return = ubool		: 変更無し ＝ false ／ 変更有り ＝ true
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2009/11/27 by 谷川真也
***/
ubool IIF_ChangeSetting(void)
{
	ubool	Ret = false;
	unsigned char puc_Index;

	for(puc_Index = 1 ; puc_Index <= 10 ; puc_Index++){	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
		if(guc_Out_port[0][puc_Index] != guc_Out_port_ch[0][puc_Index]) Ret = true;
		dummy_access = 1;
		if(guc_In_port[0][puc_Index]  != guc_In_port_ch[0][puc_Index]) Ret = true;
		dummy_access = 1;
		if(guc_In_port[1][puc_Index]  != guc_In_port_ch[1][puc_Index]) Ret = true;
		dummy_access = 1;
	}
	for(puc_Index = 1 ; puc_Index <= 3 ; puc_Index++){
		if(guc_Analog_port[0][puc_Index]  != guc_Analog_port_ch[0][puc_Index]) Ret = true;
		dummy_access = 1;
	}

return(Ret);
}
/***
**  ID     = IIF_ChangeSetting
**  name   = ＩＩＦ旧設定復帰処理
**  func   = ＩＩＦ旧設定データの復旧を行う
**  called = void IIF_RestoresSetting(void);
**  io     = none
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2009/11/27 by 谷川真也
***/
void IIF_RestoresSetting(void)
{
	unsigned char puc_Index;

	for(puc_Index = 1 ; puc_Index <= 10 ; puc_Index++){	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
		guc_Out_port[0][puc_Index] = guc_Out_port_ch[0][puc_Index];
		dummy_access = 1;
		guc_In_port[0][puc_Index]  = guc_In_port_ch[0][puc_Index];
		dummy_access = 1;
		guc_In_port[1][puc_Index]  = guc_In_port_ch[1][puc_Index];
		dummy_access = 1;
	}
	for(puc_Index = 1 ; puc_Index <= 3 ; puc_Index++){
		guc_Analog_port[0][puc_Index]  = guc_Analog_port_ch[0][puc_Index];
		dummy_access = 1;
	}
}
// <IIF NEW>	2009.11.27
//-----------------------------------------------------------------------------
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_rob_pc_rcv_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ＧＬＯＢＡＬ．ｃ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ
//  【機能説明】
//      外部変数宣言
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
#define __GLOBAL
//#include "YD400GZ3.h"
#include "custom.h"
/*---------------------------------------------------------------------
	time counter
---------------------------------------------------------------------*/
unsigned char 	timer_100us;
unsigned char 	timer_500us;
unsigned short	timer_5ms;
unsigned short	timer_10ms;
unsigned short	timer_20ms;
unsigned short	timer_50ms;
unsigned short	timer_200ms;
unsigned short	timer_500ms;



unsigned char    com_ts;
short int        com_current;
short int        com_voltage;

unsigned char    int0_counter;                 //2006.2.9 ihara
unsigned char    ROBOT; //2006.2.8 ihara
unsigned char    dsp_int0_counter;


unsigned short   gus_Current_detect; //電流検出用 2019.05.30

//<><><><><><><><><><> ＰＣパラメータ関連 <><><><><><><><><><>
unsigned int     precurr;
unsigned int     currfb;
unsigned int     voltfb;
unsigned int     pwm;
unsigned char    A6_stop_flag;
unsigned char    dsp_pc_data_flag;
unsigned char    dsp_sampling_flag;
//unsigned char    data_no_counter;
unsigned short    data_no_counter; //2008.02.21
//unsigned char    data_no[31];
//unsigned int     data[31];
//unsigned char    data_no[256]; //2007.1.24 2007.1.26変更移植
//unsigned int     data[256];    //2007.1.24 2007.1.26変更移植
unsigned short    data_no[380]; //2008.2.21
unsigned int     data[380];    //2008.2.21
unsigned char    dsp_write_flag;
unsigned char    v_data_no_counter;
//unsigned char    v_data_no[25];
//unsigned int     v_data[25];
unsigned char    v_data_no[65]; //2007.1.24 2007.1.26変更移植
unsigned int     v_data[65];    //2007.1.24 2007.1.26変更移植
unsigned char    v_dsp_write_flag;
signed int       v_test;

unsigned char    guc_Dsp_pc_data_flag;
unsigned char    guc_A6_stop_flag;
unsigned char    guc_Dsp_write_flag;
unsigned char    guc_V_dsp_write_flag;
unsigned char    guc_Dsp_sampling_flag;

unsigned char    guc_Dsp_read_flag;
unsigned int     gui_Send_work;
unsigned long    gul_Dsp_address4;
unsigned long    gul_Dsp_address3;
unsigned long    gul_Dsp_address2;
unsigned long    gul_Dsp_address1;

unsigned char    guc_Dsp_one_write_flag;
unsigned long    gul_Dsp_write_address4;
unsigned long    gul_Dsp_write_address3;
unsigned long    gul_Dsp_write_address2;
unsigned long    gul_Dsp_write_address1;
unsigned short   gus_Dsp_write_data2;
unsigned short   gus_Dsp_write_data1;


//<><><><><>2007.1.26追加移植<><><><><><><><>
unsigned char    PC_v_data_no;
//a
unsigned int     PC_v_data_a1;
unsigned int     PC_v_data_a2;
unsigned int     PC_v_data_a3;
unsigned int     PC_v_data_a4;
unsigned int     PC_v_data_a_result;
//b
unsigned int     PC_v_data_b1;
unsigned int     PC_v_data_b2;
unsigned int     PC_v_data_b3;
unsigned int     PC_v_data_b4;
unsigned int     PC_v_data_b_result;
//c
unsigned int     PC_v_data_c1;
unsigned int     PC_v_data_c2;
unsigned int     PC_v_data_c3;
unsigned int     PC_v_data_c4;
unsigned int     PC_v_data_c_result;
//min
unsigned int     PC_v_data_min1;
unsigned int     PC_v_data_min2;
unsigned int     PC_v_data_min3;
unsigned int     PC_v_data_min4;
unsigned int     PC_v_data_min_result;
//max
unsigned int     PC_v_data_max1;
unsigned int     PC_v_data_max2;
unsigned int     PC_v_data_max3;
unsigned int     PC_v_data_max4;
unsigned int     PC_v_data_max_result;

unsigned char    guc_PC_V_dsp_write_flag;
//<><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



unsigned char    pre_flow_flag;       //2006.3.14 ihara
unsigned char    Hand_inching_flag;   //2006.3.14 ihara

unsigned char guc_Sequence_mode;
unsigned char gub_Err;                          //エラー治具端子出力
unsigned char gub_Alarm;                        //アラーム治具端子出力
unsigned char gub_System_err;
unsigned int    gui_Err_code;




unsigned int gtt_test_counter;


unsigned int gui_Table_code_counter;
unsigned int gui_Sp_table_code_counter;
unsigned char guc_Hfix_rewrite_check_flag; //半固定データ書き換え確認フラグ
unsigned char guc_Val_rewrite_check_flag0;  //可変データ書き換え確認フラグ
unsigned char guc_Val_rewrite_check_flag1;  //可変データ書き換え確認フラグ
unsigned char guc_Hfix_val_reset_flag;     // 半固定、可変データリセット
unsigned char guc_Adj1_rewrite_check_flag; // 微調項目１書き換え確認フラグ 2007.2.5追加
unsigned char guc_Adj2_rewrite_check_flag; // 微調項目２書き換え確認フラグ 2007.2.5追加
unsigned char guc_Exd_adj1_rewrite_check_flag; //拡張溶接微調パラメータ個別書き換え確認フラグ 2007.5.29
unsigned char guc_Exd_adj2_rewrite_check_flag; //拡張溶接微調パラメータ一括書き換え確認フラグ 2007.5.29
unsigned char guc_Method_rewrite_check_flag; //溶接条件データ書き換え確認フラグ 2007.7.6
unsigned char guc_0x69_rewrite_check_flag1; //０ｘ６９コマンドのデータ書き換え確認フラグ　2009.07.14

short gss_Adj_slow_down;                   //スローダウン調整値（最終値）2007.2.5追加

float gsf_Acc1;    //加速度１     2007.2.6
float gsf_Acc2;    //加速度２     2007.2.6
float gsf_Acc3;    //加速度３     2007.2.6
float gsf_Acc4;    //加速度４     2007.2.6
float gsf_Acc5;    //加速度５     2007.2.6
float gsf_Delay;   //送給ディレイ 2007.2.6
float gsf_Re_start;//連続スタート 2007.2.6

short gss_Acc1;    //加速度１     2007.2.6
short gss_Acc2;    //加速度２     2007.2.6
short gss_Acc3;    //加速度３     2007.2.6
short gss_Acc4;    //加速度４     2007.2.6
short gss_Acc5;    //加速度５     2007.2.6
short gss_Delay;   //送給ディレイ 2007.2.6
short gss_Re_start;//連続スタート 2007.2.6

unsigned char  guc_Table_change_flag; //2007.2.9
unsigned char  guc_No_table;          //2007.2.9

unsigned char  guc_Program_ver_flag;  //2007.2.13追加

unsigned short gus_Imprudence_bkup;   //2007.3.2追加
unsigned short gus_Imprudence_work;   //2007.3.2追加

unsigned long  gul_Rpm_buff;          //2007.3.15


int DelayTimer;

int     isContArc;
int     isEnbDelay;

unsigned char  guc_Ad_id_under[64];      // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
unsigned char  guc_Ad_id_uper[64];      // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
unsigned char  guc_Ad_data_under[64];    // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
unsigned char  guc_Ad_data_uper[64];    // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
unsigned char  guc_Variable_length_flag;



//***** 2007.2.20 割り込みテスト ******
//unsigned char Int_test[100];    2009.02.16
//unsigned short Int_test_index; 2009.02.16




//***** 2007.11.29 リモコン通信実験用 *******
unsigned char guc_Com_jog1_data;
unsigned char guc_Com_jog2_data;
unsigned char guc_In_jog1_data;
unsigned char guc_In_jog2_data;
unsigned char guc_Jog_rewrite_check_flag;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
unsigned char guc_Sw_rewrite_check_flag;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み

unsigned char guc_Machine_no_flag;
unsigned char guc_Initial_display_flag;
unsigned short gus_Initial_timer;

unsigned char led11_data;
unsigned char led12_data;
unsigned char led13_data;
unsigned char com_led11_data;
unsigned char com_led12_data;
unsigned char com_led13_data;

unsigned char led21_data;
unsigned char led22_data;
unsigned char led23_data;
unsigned char com_led21_data;
unsigned char com_led22_data;
unsigned char com_led23_data;
unsigned char com_led21_okcv_data;
unsigned char com_led22_okcv_data;
unsigned char com_led23_okcv_data;
unsigned char com_led13_dital_data; //2009.04.03
unsigned char com_led21_dital_data;
unsigned char com_led22_dital_data;
unsigned char com_led23_dital_data;

     signed short test_work1;
     signed short test_work2;

unsigned char guc_Material_condition_counter;
unsigned char guc_Material_condition_data;

unsigned char guc_Wire_condition_counter;
unsigned char guc_Wire_condition_data;

unsigned char guc_Method_condition_counter;
unsigned char guc_Method_condition_data;
unsigned char guc_Remo_table_check_flag;
unsigned char guc_Okcv_select_flag;
unsigned char guc_Okcv_select_counter; //2008.08.21

unsigned char guc_Ext_condition_counter;  //2008.11.10
unsigned char guc_Ext_condition_data;     //2008.11.10
unsigned char guc_Ext_condition_data_bk;  //2008.11.10


//***** BP3関連 2009.01.10 *****
unsigned char guc_Ac_wave_counter;        //2009.01.10
unsigned char guc_Ac_wave_data;           //2009.01.10
unsigned char guc_Ac_wave_data_bk;        //2009.01.10

unsigned char guc_Ac_tig_set_counter;     //2009.01.10
unsigned char guc_Ac_tig_set_data;        //2009.01.10
unsigned char guc_Ac_tig_set_data_bk;     //2009.01.10

unsigned char guc_Mix_tig_set_counter;     //2009.01.10
unsigned char guc_Mix_tig_set_data;        //2009.01.10
unsigned char guc_Mix_tig_set_data_bk;     //2009.01.10

unsigned short gus_Sequence_set_data;       //2009.01.13 char->short 2009.01.19
unsigned short gus_Sequence_set_data_bk;    //2009.01.13 char->short 2009.01.19

unsigned char guc_Pulse_item_counter;      //2009.01.13
unsigned char guc_Jog_set_key;             //2009.01.13

unsigned int  gui_Navi_table_code_counter; //2009.01.14
unsigned char guc_Navi_code_work[NAVITBLCNT];  //2009.01.14

unsigned char guc_Navi_material_code[25];   //2009.01.14
unsigned char guc_Navi_material_counter;    //2009.01.15
unsigned char guc_Navi_thickness_code[25];  //2009.01.15
unsigned char guc_Navi_thickness_counter;   //2009.01.15
unsigned char guc_Navi_joint_code[25];      //2009.01.15
unsigned char guc_Navi_joint_counter;       //2009.01.15
unsigned char guc_Navi_direction_code[25];  //2009.01.15
unsigned char guc_Navi_direction_counter;   //2009.01.15
unsigned char guc_Navi_pulse_code[25];      //2009.01.15
unsigned char guc_Navi_pulse_counter;       //2009.01.15

//スロープ関連 2009.02.02
float gf_Up_slop_base_step;
float gf_Up_slop_pulse_step;
float gf_Up_slop_base_curr;
float gf_Up_slop_pulse_curr;
float gf_Down_slop_base_step;
float gf_Down_slop_pulse_step;
float gf_Down_slop_base_curr;
float gf_Down_slop_pulse_curr;
unsigned short gus_Up_slop_time;
unsigned short gus_Down_slop_time;

unsigned short gus_Pulse_current;
unsigned short gus_Pulse_freq;
unsigned short gus_Pulse_duty;

unsigned short gus_Ac_frequency;
unsigned short gus_Cleaning_duty;
unsigned short gus_Mix_ac_ratio;
unsigned short gus_Mix_frequency;
signed short gss_Arc_spot_time; //2009.03.06 アークスポット時間 2009.03.16 unsigned -> signed


float gf_Hot_current_level; //2009.02.13


short gss_Output_difference; //2009.02.16
float gf_Output_correct_value; //2009.02.16

short gss_Max_current; //2009.02.19
short gss_Min_current; //2009.02.19


short gss_Voltage_ref; //2009.02.20
float gf_Out_current;  //2009.02.20
float gf_Target_current; //2009.02.20
unsigned long gsl_Voltage_ref_add; //2010.01.12

short gss_Target_current_sabun_bkup; //2009.02.21
short gss_Target_current_sabun;      //2009.02.21

unsigned char guc_V_max; //2009.03.13


//******* 温度異常関連 2009.03.13 *******
char gsc_Now_year;
char gsc_Now_month;
char gsc_Now_day;
char gsc_Now_hour;
char gsc_Now_mini;
char gsc_Temp_err_year_work;
char gsc_Temp_err_month_work;
char gsc_Temp_err_day_work;
char gsc_Temp_err_hour_work;
char gsc_Temp_err_mini_work;
unsigned char gus_Temp_err_set_work;
//**************************************

short gss_Ct_offset; //2009.04.14
short gss_Output_gein; //2009.04.14


signed short gs_Okcv_adjust_data;
signed short gs_Okcv_adjust_init_data; 		//2008.02.22
signed short gs_Okcv_adjust_crat_data;		//2008.02.22
signed short gs_Okcv_adjust_wave_data;		//2008.02.26
signed short gs_Okcv_adjust_start_data;		//2008.08.05
unsigned char guc_Okcv_display_timer;
unsigned char guc_Okcv_display_flag;
unsigned char guc_Initial_display_flag2; //2007.12.06
unsigned char guc_Last_select_sw; //2007.12.07

unsigned char guc_Inching_sw_flag;
unsigned char guc_Inching_sw_flag_bkup; //2008.09.09
unsigned char guc_Gas_on_off_flag;
unsigned char guc_Gas_on_off_flag_bkup; //2008.09.09


unsigned short gus_Dps_timer; //2007.12.09

unsigned char guc_Dps_R8_flag; //2007.12.09
unsigned char guc_Dps_M16_flag; //2007.12.09
unsigned char guc_Dps_M32_flag; //2007.12.09
unsigned char guc_Dps_space_flag; //2007.12.10

unsigned short gus_Pre_display_timer; //2007.12.10

unsigned char  guc_Select_counter;   //2007.12.11
unsigned char  guc_Select_dital_flag; //2007.12.11
signed char    gsc_Select_dital_counter; //2007.12.11
signed char    gsc_Select_dital_counter_bkup; //2007.12.11


//signed short gs_Okcv_adjust_data_bkup;   //2007.12.09 実験のため移動

unsigned char guc_Current_test_flag; //2008.01.21
unsigned char guc_Voltage_test_flag; //2008.01.21
signed short  gss_Curr_result_test;	 //2008.01.21 
signed short  gss_Volt_result_test;	 //2008.01.21 

unsigned char guc_Select_param_set_counter;  		//2008.02.22
unsigned char guc_Select_current_sel_counter;		//2008.02.22
unsigned char guc_Select_param_set_flag;     		//2008.02.22
unsigned char guc_Select_current_sel_flag;   		//2008.02.22

signed short gss_Current_result_work; //2008.03.03
signed short gss_Voltage_result_work; //2008.03.03
signed short gss_Weld_end_current;    //2008.03.03
signed short gss_Weld_end_voltage;    //2008.03.03
signed short gss_Current_work; //2008.03.03
signed short gss_Voltage_work; //2008.03.03

signed short gss_RCurrent_work; //2009.07.28
signed short gss_RVoltage_work; //2009.07.28

signed short gss_Base_current_work; //2009.03.23
signed short gss_Base_voltage_work; //2009.03.23
signed short gss_Peak_current_work; //2009.03.23
signed short gss_Peak_voltage_work; //2009.03.23
signed int gsi_Base_current_result_work; //2009.03.23
signed int gsi_Base_voltage_result_work; //2009.03.23
signed int gsi_Peak_current_result_work; //2009.03.23
signed int gsi_Peak_voltage_result_work; //2009.03.23
long gsl_Current_result_work2; //2009.04.11
long gsl_Voltage_result_work2; //2009.04.11

//実効値計算関連
long gsl_Current_result_work_rms; //2009.03.26
long gsl_Voltage_result_work_rms; //2009.03.26
long gsl_Base_current_result_work_rm; //2009.03.26
long gsl_Base_voltage_result_work_rm; //2009.03.26


//リモコン再生関連
unsigned short gus_Remo_play_ch_data; //2009.03.28
unsigned char guc_Remo_play_ch;       //2009.03.28
unsigned char guc_Remo_play_ch_bkup;  //2009.03.30

float gf_Frequence_adjust_data;            //2008.03.27中川さん要請で追加
float gf_Base_adjust_data;                 //2008.03.27中川さん要請で追加

unsigned char guc_Half_pc_data_flag;  //2008.06.03 ＰＣに半固定パラメータを返信する。
unsigned short gus_Half_pc_data;      //2008.06.03 ＰＣに半固定パラメータを返信する。

unsigned char guc_Crater_mode_counter;
unsigned char guc_Adjust_item_counter; //2008.08.28

unsigned char guc_Ch_no; //2008.08.07
unsigned char guc_Ch_no_bkup; //2008.08.19

unsigned char guc_Pass_word; //2008.09.10
unsigned char guc_Controller_lock; //2008.09.10

unsigned char guc_Adjust_item_counter_work; //2008.08.28 -> 2008.09.12グローバル変数に変更


signed short gss_En_def; //ＥＮ比率のデフォルト 2008.09.16
signed short gss_En_a;   //ＥＮ比率 2008.09.16
signed short gss_En_a_bkup; //ＥＮ比率バックアップ 2008.09.25
signed char  gsc_Va; //2008.09.26
signed short gss_WFe_Sirei_W; //2008.09.30
unsigned char guc_Robot_connect_flag; //2008.10.03
unsigned char guc_Robot_connect_one_shot_flag;//2008.10.03
unsigned char guc_Gas_check_cancel_flag; //2008.10.06
unsigned char guc_Controller_gas_sw_cancel; //2008.10.06
unsigned char guc_Controller_inc_sw_cancel; //2008.10.06
unsigned char guc_Pulse_mode_data_bkup; //2008.10.08
//unsigned char dummy1;
//インチングスロースタート関連
unsigned short gus_Inching_curr;
unsigned short gus_Inching_curr_bk_up;

//unsigned short test_Buff[96]; //test用 2008.09.16

//***2008.08.21***
unsigned short gus_Weld_current;     //溶接電流指令値
unsigned short gus_Weld_voltage;     //溶接電圧指令値
unsigned short gus_Init_current;     //初期電流指令値
unsigned short gus_Init_voltage;     //初期電圧指令値
unsigned short gus_Crat_current;     //クレータ電流指令値
unsigned short gus_Crat_voltage;     //クレータ電圧指令値
unsigned short gus_Wave_current;     //波形制御　Ｂ条件　電流指令値
unsigned short gus_Wave_voltage;     //波形制御　Ｂ条件　電圧指令値
unsigned short gus_Start_current;    //波形制御　スタート条件　電流指令値
unsigned short gus_Start_voltage;    //波形制御　スタート条件　電圧指令値
unsigned char  guc_Pulse_type_data;

unsigned short gus_Pre_flow_time;    //プリフロー時間 2009.01.22
unsigned short gus_After_flow_time;  //アフターフロー時間 2009.01.22
//****************

unsigned short gss_Motor_acc1;       //2008.11.17 起動時のモータディレイ時の加速度

signed short gss_Select_dital[SELECT_DITAL_MAX+1]; //2007.12.11　詳細データ格納変数     Phase15 by @Tny 2008/09/19
unsigned char  guc_Pulse_mode_data; //2007.12.14
unsigned char  guc_Pulse_mode_counter; //2007.12.14


unsigned char gsc_Day_max_work; //2008.08.26 閏年、各月用最大日数

signed short test_data;

char  dummy_access;


unsigned char  guc_Out_port[CH][17+1];		//2008.08.23	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
unsigned char  guc_In_port[CH][17+1];		//2008.08.23	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
unsigned char  guc_Analog_port[CH][17+1];	//2008.08.23	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny



//元バックアップ領域にあったものをとりあえず移動2008.08.27
unsigned short test_counter;
unsigned char  test_flag;
unsigned int gui_Total_weld_time_bkup; //2007.3.30
unsigned short gus_Total_weld_count_bkup; //2007.4.5
unsigned long  gul_Total_wire_feed_bkup; //2007.4.5

//--------- IIF by @Tny 2008/08/26 ------------
#if true
ubool            gb_IIF_Select;
unsigned short  gus_IIF_DebugTimer1;
ubool            gb_IIF_DebugFlag1;
unsigned char   guc_Iif_output;
unsigned char   guc_Iif_bit_input; //2008.09.01 ihara
#endif
//--------------------------------------------
//--------- RTC by @Tny 2008/08/28 ------------
#if true
unsigned short  gus_RTC_ReNew;
#endif
//--------------------------------------------
//--------- RTC by @Tny 2008/09/01 ------------
#if true
unsigned short  gus_cRTC_AdjustCount;       // RTC周波数測定用カウンタ
unsigned long   gul_vRTC_FrequencyCount;    // RTC周波数カウンタ

ubool            gb_RTC_Debug_Sec;           // ＲＴＣ動作確認用フラグ（秒）
unsigned short  gus_RTC_cDebug_1;           // ＲＴＣ動作確認用カウンタ＃１
#endif
//--------------------------------------------
//----- Phase2(Debug) by @Tny 2008/09/02 -----
#if true
ubool            gb_Fram_Proc;               // ＦＲＡＭ操作中フラグ
unsigned char   guc_Fram_Phase;             // ＦＲＡＭ操作フェーズ
unsigned short  gus_Fram_Page;              // ＦＲＡＭ転送パケット番号
unsigned short  gus_Fram_Packet_Wait;       // パケット送受信間隔
#endif
//--------------------------------------------

//--------- Phase4 by @Tny 2008/09/08 --------
#if true
unsigned short  gus_Iif_ad_input[3];        // IIFからのＡ／Ｄ変換値
unsigned short  gus_Iif_comunication_timer; // 
unsigned short  gus_Iff_Detect_disp_timer;  // IIF検出表示タイマー
unsigned char   BackUp16LedData[18];        //
ubool            gb_Iif_comuni_failed;       //
#endif
//--------------------------------------------
//--------- Phase5 by @Tny 2008/09/09 --------
#if true
union{
    unsigned char	ALL;
	struct{	// １ビットスイッチ
		ubool	b7		:	1;	// MSB
		ubool	b6		:	1;
		ubool	b5		:	1;
		ubool	b4		:	1;
		ubool	b3		:	1;
		ubool	b2		:	1;
		ubool	Over_lay:	1;
		ubool	R8_Fan  :	1;	// LSB
	} Bit1Sw;
} guc_R8_control; // Ｒ８側出力制御データ
ubool            gb_R8_comuni;               // Ｒ８送信データ識別フラグ
unsigned short  gus_R8_TX_cDebug_1;         // Ｒ８送信データ試験カウンタ＃１
#endif
//--------------------------------------------

//----- Phase6 by @Tny 2008/09/10 -----
#if true
ubool                        gb_Error_information_record;        // エラー情報記憶実行フラグ
unsigned char               guc_Error_no_backup;                // エラー番号記録値
struct gtt_Error_History    gtt_Error_History;                  // エラー履歴テーブル
ubool                        gb_Error_History_Write;             // エラー履歴テーブル保存フラグ
unsigned short              gus_Iif_BuiltIn;                    // IIF接続フラグ
ubool                        gus_Iif_BuiltIn_write;              // IIF接続フラグ保存フラグ
#endif
//--------------------------------------------
//----- Phase7 by @Tny 2008/09/10 -----
#if true
unsigned char   guc_Error_code;                // エラー番号
ubool            gb_Error_Display_Sending;      // エラー情報送信要求フラグ
unsigned long   gus_Iif_Detect_Timer;          // IIF接続確認時間カウンタ
ubool            gb_Iif_BuiltIn;                // IIF接続認識フラグ
ubool            gb_Iif_Input;                  // IIFデータ受信フラグ
unsigned char   guc_Error_Display[100][18] = { // エラー内容テーブル（最終2文字は空白にすること！！）
                                            "                  ",   //  0   異常解除
                                            "ﾋｼﾞｮｳﾃｲｼ          ",   //  1   非常停止 or PRI_CURR_FB2_ERR 2009.01.16
                                            "ﾆｼﾞｶﾃﾞﾝﾘｭｳｲｼﾞｮｳ   ",   //  2   二次過電流異常 //2009.02.06日本語化
                                            "ｵﾝﾄﾞｼﾞｮｳｼｮｳｲｼﾞｮｳ  ",   //  3   温度上昇異常   //2009.02.06日本語化
                                            "ｲﾁｼﾞｶﾃﾞﾝｱﾂｲｼﾞｮｳ   ",   //  4   一次過電圧異常 //2009.02.06日本語化
                                            "ｲﾁｼﾞﾃｲﾃﾞﾝｱﾂｲｼﾞｮｳ  ",   //  5   一次低電圧異常 //2009.02.06日本語化
                                            "ｱｰｸｽﾀｰﾄｲｼﾞｮｳ      ",   //  6   アークスタート異常 //2009.02.06日本語化
                                            "ﾄｰﾁｽｲｯﾁｲｼﾞｮｳ      ",   //  7   トーチスイッチ異常 //2009.02.06日本語化
                                            "ﾃﾞﾝﾘｭｳｹﾝｼｭﾂｲｼﾞｮｳ  ",   //  8   電流検出異常         2009.01.16
                                            "PRI SHUT DOWN     ",   //  9   瞬停異常
                                            "ｶﾞｽｹﾞﾝｱﾂｲｼﾞｮｳ     ",   // 10   外部一時停止２->2009.02.06ガス減圧異 ->2009.09.29 11と入れ替え
                                            "ﾐｽﾞｶｲﾛｲｼﾞｮｳ       ",   // 11   外部一時停止１->2009.02.06水回路異常 ->2009.09.29 10と入れ替え
                                            "PRI OVER CURRENT  ",   // 12   一次過電流異常 2008.11.17
                                            "ﾆｼﾞｶﾃﾞﾝｱﾂｲｼﾞｮｳ    ",   // 13   二次過電圧異常 2008.11.17 2009.02.06日本語化
                                            "RS422ｿｳｼﾝｴﾗｰ      ",   // 14   ４２２シリアル通信送信エラー 2009.02.06日本語化
                                            "RS422ﾊﾟﾘﾃｨｴﾗｰ     ",   // 15   ４２２シリアル通信パリティーエラー 2009.02.06日本語化
                                            "RS422ｵｰﾊﾞｰﾗﾝｴﾗｰ   ",   // 16   ４２２シリアル通信オーバーランエラー 2009.02.06日本語化
                                            "RS422ﾀｲﾑｱｳﾄｴﾗｰ    ",   // 17   ４２２シリアル通信タイムアウトエラー 2009.02.06日本語化
                                            "                  ",   // 18   
                                            "                  ",   // 19   
                                            "                  ",   // 20   
                                            "                  ",   // 21   
                                            "SYSTEM BREAK      ",   // 22   システムブレイク
                                            "                  ",   // 23   
                                            "                  ",   // 24   
                                            "ENCODER DETECT    ",   // 25   エンコーダ検出異常
                                            "MORTOR STOP       ",   // 26   モータ停止異常
                                            "MORTOR CONTROL    ",   // 27   モータ回転異常
                                            "WATCH DOG TIMER   ",   // 28   ウォッチドックタイマエラー
                                            "RS422 COMMAND     ",   // 29   ４２２シリアル通信コマンドエラー
                                            "RS422 RECEIVING   ",   // 30   ４２２シリアル通信受信エラー
                                            "                  ",   // 31   
                                            "                  ",   // 32   
                                            "                  ",   // 33   
                                            "                  ",   // 34   
                                            "                  ",   // 35   
                                            "                  ",   // 36   
                                            "                  ",   // 37   
                                            "                  ",   // 38   
                                            "                  ",   // 39   
                                            "                  ",   // 40   
                                            "                  ",   // 41   
                                            "                  ",   // 42   
                                            "                  ",   // 43   
                                            "                  ",   // 44   
                                            "                  ",   // 45   
                                            "                  ",   // 46   
                                            "                  ",   // 47   
                                            "                  ",   // 48   
                                            "                  ",   // 49   
                                            "SYSTEM            ",   // 50   プロセス間(26A-62P間)通信エラー
                                            "REST62P           ",   // 51   ６２Ｐ不測リセットエラー
                                            "REST26A           ",   // 52   ２６Ａ不測リセットエラー
                                            "                  ",   // 53   
                                            "                  ",   // 54   
                                            "                  ",   // 55   
                                            "                  ",   // 56   
                                            "                  ",   // 57   
                                            "                  ",   // 58   
                                            "                  ",   // 59   
                                            "RS422 OVER RUN    ",   // 60   ４２２シリアル通信オーバーランエラー
                                            "RS422 PARITY      ",   // 61   ４２２シリアル通信パリティーエラー
                                            "RS422 FLAMING     ",   // 62   ４２２シリアル通信フレーミングエラー
                                            "RS232C OVER RUN   ",   // 63   ２３２シリアル通信オーバーランエラー
                                            "RS232C PARITY     ",   // 64   ２３２シリアル通信パリティーエラー
                                            "RS232C FLAMING    ",   // 65   ２３２シリアル通信フレーミングエラー
                                            "ﾃﾞﾝｷｮｸﾕｳﾁｬｸﾊｯｾｲ   ",   // 66   スティック発生 2009.02.06日本語化
                                            "ARC START         ",   // 67   アークエラー
                                            "PRI CURRENT FB1   ",   // 68   PRI_CURR_FB1_ERR
                                            "                  ",   // 69   
                                            "R8ｺﾐｭﾆｹｰｼｮﾝｴﾗｰ    ",   // 70   R8_COM_ERR 2009.02.06日本語化
                                            "                  ",   // 71   
                                            "                  ",   // 72   
                                            "                  ",   // 73   
                                            "                  ",   // 74   
                                            "                  ",   // 75   
                                            "                  ",   // 76   
                                            "                  ",   // 77   
                                            "                  ",   // 78   
                                            "                  ",   // 79   
                                            "EMERGENCY-2 STOP  ",   // 80   非常停止 #2
                                            "                  ",   // 81   
                                            "IIF CONNECT ERR   ",   // 82   EXTERNAL IIF NEW	2011.02.21 by @Tny
                                            "                  ",   // 83   
                                            "                  ",   // 84   
                                            "                  ",   // 85   
                                            "                  ",   // 86   
                                            "                  ",   // 87   
                                            "                  ",   // 88   
                                            "                  ",   // 89   
                                            "                  ",   // 90   
                                            "                  ",   // 91   
                                            "                  ",   // 92   
                                            "                  ",   // 93   
                                            "                  ",   // 94   
                                            "                  ",   // 95   
                                            "                  ",   // 96   
                                            "                  ",   // 97   
                                            "                  ",   // 98   
                                            "                  "    // 99   
                                            };
#endif
//--------------------------------------------

//----- Phase10 by @Tny 2008/09/16 -----
#if true
unsigned int    gui_Err_code0;	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
unsigned int    gui_Err_code1;
unsigned int    gui_Err_code2;
unsigned int    gui_Err_code3;
#endif
//--------------------------------------------
//----- Phase11 by @Tny 2008/09/16 -----
#if true
unsigned char   guc_Sub_16Led_display[18];  // サブ表示エリア
unsigned char   guc_Sub_display_flag;       // サブ表示フラグ
#endif
//--------------------------------------------
//----- Phase12 by @Tny 2008/09/17 -----
#if true
unsigned short  guc_Init_wait_sequence;     // 初期シーケンス待ち時間
struct{
    ubool            bProc1;                 // 溶接終了後表示制御フラグ＃１
    ubool            bProc2;                 // 溶接終了後表示制御フラグ＃２
    unsigned short  us_MainWeldingCurr;     // 本溶接時の溶接電流値
    unsigned short  us_MainWeldingVolt;     // 本溶接時の溶接電圧値
    unsigned short  us_Display_time;        // 溶接終了後表示時間カウンタ
    unsigned short  us_MainMotorCurr;       // 本溶接時のモータ電流値値     Phase19 by @Tny 2008/09/26
    unsigned short  us_MainMotorRPM;        // 本溶接時のモータ回転数       Phase19 by @Tny 2008/09/26
    unsigned short  us_MainImprudence;      // 本溶接時の短絡数             Phase19 by @Tny 2008/09/26
} gtt_End_welding_display;  // 溶接終了後表示制御テーブル
#endif
//--------------------------------------------
//----- Phase13 by @Tny 2008/09/18 -----
#if true
struct{
	unsigned char   uc_Proc;                        // 制御有効フラグ
	unsigned char   uc_ON_Time;			            // 点滅ＯＮ時間
	unsigned char   uc_OFF_Time;		            // 点滅ＯＦＦ時間
	unsigned char   uc_vCount;			            // 点滅回数
} gtt_LED_control_backup[10];	                // ＬＥＤ表示制御バックアップテーブル
unsigned char   guc_Error_return_LED_control_A; // エラー復帰時ＬＥＤ表示制御インデックス：Ａ
unsigned char   guc_Error_return_LED_control_B; // エラー復帰時ＬＥＤ表示制御インデックス：Ｂ
ubool            gb_Error_blink;                 // エラー点滅制御要求フラグ
#endif
//--------------------------------------------



float Fq_test;

//----- Phase15 by @Tny 2008/09/19 -----
#if true
ubool            gb_15SEG_LED_Error_Disp_Hold;   // エラー表示データ送信中フラグ
#endif
//--------------------------------------------

//----- Phase21 by @Tny 2008/10/02 -----
#if false //2009.03.16 del

// 溶接条件データ系（ＣＨ０(現状)～ＣＨ１６）
struct{
        unsigned char   vStart;
        struct{
                unsigned char   guc_Write_check_flag;
                unsigned char   guc_Material_condition_counterc;
                unsigned char   guc_Material_condition_datac;
                unsigned char   guc_Wire_condition_counterc;
                unsigned char   guc_Wire_condition_datac;
                unsigned char   guc_Method_condition_counterc;
                unsigned char   guc_Method_condition_datac;
                unsigned char   guc_Okcv_select_flag;
                signed short    gs_Okcv_adjust_data;
                signed short    gs_Okcv_adjust_init_data;
                signed short    gs_Okcv_adjust_crat_data;
                signed short    gs_Okcv_adjust_wave_data;
                signed short    gs_Okcv_adjust_start_data;
                unsigned short  gus_Weld_current;
                unsigned short  gus_Weld_voltage;
                unsigned short  gus_Init_current;
                unsigned short  gus_Init_voltage;
                unsigned short  gus_Crat_current;
                unsigned short  gus_Crat_voltage;
//              unsigned short  gus_Wave_current;
//              unsigned short  gus_Wave_voltage;
//              unsigned short  gus_Start_current;
//              unsigned short  gus_Start_voltage;
                unsigned char   guc_Pulse_mode_data;
                unsigned char   guc_Pulse_mode_counter;
                unsigned char   guc_Pulse_type_data;
                unsigned char   guc_Crater_mode_counter;
				// Phase28 by @Tny 2008.11.21
				unsigned char	guc_Ext_condition_counter;  //2008.11.10
				unsigned char	guc_Ext_condition_data;     //2008.11.10
                // 波形パラメータ系
                signed short    ss_User_param[USER_PARAMETER_NO];
                // 詳細パラメータ系
                signed short    gss_Select_dital[SELECT_DITAL_MAX+1];
        } Data[CH];
        unsigned char   guc_Controller_lock;
        unsigned char   guc_Pass_word;
        // ＩＩＦデータ系
        unsigned char   guc_Out_port[17+1];			//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
        unsigned char   guc_In_port[17+1];			//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
        unsigned char   guc_Analog_port[17+1];		//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
        unsigned char   vEnd[(32/FRAM_PAKECT)*1];   // 余白部
} gtt_WeldingAllCondition;

// サービスマンメニューデータ系
struct{
        unsigned char               vStart;
        signed short                ss_Service_data[SERVICE_DATA_NO];
        // エラー履歴データ系
        struct gtt_Error_History    Error_History;
        unsigned char               vEnd[(32/FRAM_PAKECT)*1];   // 余白部
} gtt_ServiceData;

unsigned short  gus_Display_command_stop;   // メモリ転送後表示コマンド送信停止カウンタ
ubool            gb_Memory_copy_recv_ended;  // メモリ転送受信完了フラグ
#endif
//--------------------------------------------


//--------- Phase3 by @Tny 2008/09/05   Phase21 by @Tny 2008/10/02 --------
#if false //2009.03.16 del
// エリア別メモリ転送パケット数テーブル
// （現在(08/09/05)１パケット＝８バイト(32/FRAM_PAKECT):FRAM_PAKECT=4）
// ※最終仕様では仕様通りの転送パケット数（エリア領域長）を設定し直すこと！！
// 　但し、転送パケット数（エリア領域長）は(32/FRAM_PAKECT)の倍数で指定すること。
// 　出来ない場合は、以下の書式にて登録する。
//          (sizeof(TABLE) / (32/FRAM_PAKECT)) // 余白を用意すれば端数用パケットは必要なし
//
unsigned short  gt_Memory_copy_area_length[] ={
                                                0,
                                                (sizeof(gtt_WeldingAllCondition)  / (32/FRAM_PAKECT)),  // 1 : 溶接条件系データ
                                                (sizeof(gtt_ServiceData)  / (32/FRAM_PAKECT)),          // 2 : サービスマン＆エラー履歴系データ
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0
                                              };
// メモリ送信先エリアテーブル
// ※最終仕様では仕様通りのエリアを指定すること！！
//
unsigned char  *gt_Memory_copy_area_Tx[] ={
                                                0,
                                                &gtt_WeldingAllCondition.vStart,    // 1 : 溶接条件系データエリアの先頭番地
                                                &gtt_ServiceData.vStart,            // 2 : サービスマン＆エラー履歴系データの先頭番地
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0
                                              };
// メモリ受信先エリアテーブル
// ※最終仕様では仕様通りのエリアを指定すること！！
//
unsigned char  *gt_Memory_copy_area_Rx[] ={
                                                0,
                                                &gtt_WeldingAllCondition.vStart,    // 1 : 溶接条件系データエリアの先頭番地
                                                &gtt_ServiceData.vStart,            // 2 : サービスマン＆エラー履歴系データの先頭番地
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0
                                              };

// メモリ転送失敗カウンタ
//
unsigned char   guc_Fram_tx_error;
#endif
//--------------------------------------------
//----- Phase22 by @Tny 2008/10/07 -----
#if true
unsigned short  gus_Iif_Purge_Judgment;     // ＩＩＦ切断（切り離し）判定カウンタ
unsigned char   guc_Welding_Play_Ch_no;     // 溶接中再生チャンネル
ubool            gb_Welding_Play_Change;     // 溶接中再生チャンネル実行フラグ
#endif
//--------------------------------------------
//----- Phase26 by @Tny 2008/10/23 -----
#if true
ubool            gb_Controller_UnConnect;        // コントローラ未接続確認フラグ
ubool            gb_Ping_to_Controller;          // コントローラ未接続確認実行フラグ
unsigned short  gus_Controller_Connect_Timer;   // コントローラ接続確認タイマー
#endif
//--------------------------------------------

//----- Phase29 by @Tny 2008/11/21 -----
#if true
unsigned short	gus_Pri_volt_err_timer;			// 一次電圧低異常検知ディレイタイマー
#endif
//--------------------------------------------


unsigned char guc_En_table_access_test; //2008.11.19ＥＮテーブルアクセステスト用

unsigned char guc_No_act_flag; //2008.11.25


//<><><>交流湯沢関連 2008.11.26<><><>
float T1;
float T3;
float T4;
float Ib2;
float gf_Frq_data;                   //2008.12.16 F2/F1の答え

float gf_Wf_max_limit;           //2008.12.26
float gf_Correct_a;              //2008.12.26
float gf_Correct_b;              //2008.12.26


// BP4 Phase3 by @Tny 2009.01.13
unsigned char	guc_Menu_Hierarchy;		// 詳細メニュー設定階層フラグ
ubool			gb_2Line_FirstDisplay;	// 初回二行目表示フラグ		BP4 Phase3 by @Tny 2009.01.15

// BP4 Phase4 by @Tny 2009.01.15
ubool			gb_RTC_Sec_Colon;		// 秒コロン表示フラグ

// BP4 Phase5 by @Tny 2009.01.21
unsigned char	guc_StringInput;			// 文字列入力処理実行中フラグ
signed short	gss_SelectCharIndex;		// 選択文字インデックス
unsigned short	gus_InputCharIndex;			// 入力文字位置インデックス
unsigned char	gt_SelectCharacter[21];		// 入力文字列データ格納エリア（最大２０文字）
const char		*SelectCharacterSrc
		//         1         2         3         4         5         6         7         8         9         A         B         C   "   ' D         E      ←
	= { "0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ｱｲｳｴｵｧｨｩｪｫｶｷｸｹｺｻｼｽｾｿﾀﾁﾂｯﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔｬﾕｭﾖｮﾗﾘﾙﾚﾛﾜｦﾝﾞﾟ ! $%& ()*+,.-/:;<=>?@[]  # " }; // Length = 149
unsigned char	SelectCharacter[200];		// 選択文字データ
ubool			gb_RecWeldCond;				// 記憶条件データの有無

// BP4 Phase6 by @Tny 2009.01.27
unsigned char	gt_WeldCondName[CH][21];		// 条件名文字列データ格納エリア（最大２０文字×１７条件）
ubool			gb_WeldCondNameWrite;			// 溶接条件名書き込み要求フラグ

//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
unsigned char	guc_Lcd_Bright;				// コントラストデータ
ubool			gb_LcdBrightWrite;			// ＬＣＤコントラスト値の記録の要求フラグ
//-----------------------------------------------------------

//-----------------------------------------------------------
//BP4 Phase10 by @Tny 2009.02.18	表示コマンド系送信要求フラグ
ubool			gb_RemCom_0x20;
ubool			gb_RemCom_0x21;
ubool			gb_RemCom_0x22;
ubool			gb_RemCom_0x23;
ubool			gb_RemCom_0x32;
ubool			gb_RemCom_0x33;	// 2019.09.02
ubool			gb_RemCom_0x34;
ubool			gb_RemCom_0x35;
ubool			gb_RemCom_0x36;
ubool			gb_RemCom_0x37;
ubool			gb_RemCom_0x38;
ubool			gb_RemCom_0x39;
//-----------------------------------------------------------
//-----------------------------------------------------------
//BP4 Phase10 by @Tny 2009.02.18
ubool			gb_ComSend1msec;	// １ｍ秒毎データ送信用フラグ
unsigned short	gus_RemoInput[10];	// リモコン入力データ（０：デジタル入力／１～４：Ａ／Ｄ入力値）
//-----------------------------------------------------------

//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23
ubool			gb_ServiceMenu;		// サービスマンメニュー要求フラグ
ubool			gb_RescueMenu;		// レスキュー処理要求フラグ
ubool			gb_JogLock;			// ＪＯＧ決定キー無効化フラグ
unsigned short	gus_MessageTimer;	// メッセージ表示時間（１００ｍ秒単位）
const char		*PassSelectCharacterSrc
		//         1         2         3         4         5         6         7         8         9         A         B         C   "   ' D         E      ←
	= { "0123456789 # " }; // Length = 13
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//BP4 Phase14 by @Tny 2009.02.24
ubool			gb_RamAllClear;		// メモリ・オールクリア実行フラグ
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
ubool			gb_RescueOpeningDisp;	// レスキュー・メニューのオープニング画面の表示要求フラグ
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// BP4 田中追加　2009.04.06 CTOFFSET
short			gtt_DSPCToffset;			//DSP自動オフセット調整値
//--------------------------------------------------------------------

//<><><> ＡＣ周波数制御に用いる電流指令値 2010.01.07 <><><>
short gss_Pre_current;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><> 溶接電流指令値テーブル変数 2010.02.19 <><><>
short gss_Current_table_data[640]; 
//<><><><><><><><><><><><><><><><><><><><><><><><><><>

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	//<><><><><><>ＩＩＦ汎用出力関連<><><><><><>
	unsigned char guc_General1_input;
	unsigned char guc_General2_input;
	unsigned char guc_General3_input;
	//<><><><><><><><><><><><><><><><><><><><><>
	//<><><><><><> ＩＩＦ関連 <><><><><><><><><>
	short gss_Iif_analog_shift[4];
	float gf_Iif_analog_revise[4];
	unsigned char guc_Okcv_select_flag_bkup_iif;
	//<><><><><><><><><><><><><><><><><><><><><>
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	ubool	gb_External_IIF;	// 外部拡張ユニット接続フラグ（true=外部拡張ユニット／false=ＩＩＦ）
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

//-------------------------------------------------------------
// <IIF NEW> 2009.11.17
unsigned short	gus_Iif_Set_Menu;			// ＩＩＦ設定項目内番号
unsigned short	gus_Iif_Set_Dital;			// ＩＩＦ設定項目内種類
unsigned short	gus_Iif_PortContact;		// ＩＩＦ設定項目内接点
ubool			gb_Iif_ChangeSetting;		// ＩＩＦ設定項目内変更確認フラグ
ubool			gb_Iif_Reboot;				// ＩＩＦ設定後再起動フラグ
ubool			gb_Iif_AnalogCalibration;	// ＩＩＦ設定アナログ入力ポートのシフト量校正処理判定フラグ
ubool			gb_Iif_JogLock[IIF_ANALOG_SERECT];	// ＩＩＦ接続時ＪＯＧ変更禁止フラグ 2009.12.02 by @Tny
// <IIF NEW> 2009.11.17
//-------------------------------------------------------------
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
ubool			gb_Iif_First_Toch_sw;		// ＩＩＦ接続時ＴＳ状態確認フラグ
//-------------------------------------------------
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 5)>	2011.10.26 by @Tny
ubool			gb_Iif_Disconnect;			// ＩＩＦ切断フラグ
//-------------------------------------------------

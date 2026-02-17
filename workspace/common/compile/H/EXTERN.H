//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ＥＸＴＥＲＮ．Ｈ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ
//  【機能説明】
//      外部変数のＥＸＴＥＲＮ宣言
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
//#include "Siodef.h"
/*---------------------------------------------------------------------
	time counter
---------------------------------------------------------------------*/
extern unsigned char 	timer_100us;
extern unsigned char 	timer_500us;
extern unsigned short	timer_5ms;
extern unsigned short	timer_10ms;
extern unsigned short	timer_20ms;
extern unsigned short	timer_50ms;
extern unsigned short	timer_200ms;
extern unsigned short	timer_500ms;



extern unsigned char    com_ts;
extern sint             com_current;
extern sint             com_voltage;

extern unsigned char    int0_counter;                 //2006.2.9 ihara
extern unsigned char    ROBOT; //2006.2.8 ihara
extern unsigned char    dsp_int0_counter;


extern unsigned short   gus_Current_detect; //電流検出用 2019.05.30

//2019.05.30
extern short MtoC[0x500] __attribute__ ((section ("BSS_DPRAM")));
extern short MfmC[0x500] __attribute__ ((section ("BSS_DPRAM")));
extern short fram[4096]  __attribute__ ((section ("BSS_FRAM")));


//<><><><><><><><><><> ＰＣパラメータ関連 <><><><><><><><><><>
extern unsigned int     precurr;
extern unsigned int     currfb;
extern unsigned int     voltfb;
extern unsigned int     pwm;
extern unsigned char    A6_stop_flag;
extern unsigned char    dsp_pc_data_flag;
extern unsigned char    dsp_sampling_flag;
//extern unsigned char    data_no_counter;
extern unsigned short    data_no_counter; //2008.02.21
//extern unsigned char    data_no[];
extern unsigned short    data_no[]; //2008.02.21
extern unsigned int     data[];
extern unsigned char    dsp_write_flag;
extern unsigned char    v_data_no_counter;
extern unsigned char    v_data_no[];
extern unsigned int     v_data[];
extern unsigned char    v_dsp_write_flag;
extern signed int       v_test;
extern unsigned char    guc_Dsp_pc_data_flag;
extern unsigned char    guc_A6_stop_flag;
extern unsigned char    guc_Dsp_write_flag;
extern unsigned char    guc_V_dsp_write_flag;
extern unsigned char    guc_Dsp_sampling_flag;

extern unsigned char    guc_Dsp_read_flag;
extern unsigned int     gui_Send_work;
extern unsigned long    gul_Dsp_address4;
extern unsigned long    gul_Dsp_address3;
extern unsigned long    gul_Dsp_address2;
extern unsigned long    gul_Dsp_address1;

extern unsigned char    guc_Dsp_one_write_flag;
extern unsigned long    gul_Dsp_write_address4;
extern unsigned long    gul_Dsp_write_address3;
extern unsigned long    gul_Dsp_write_address2;
extern unsigned long    gul_Dsp_write_address1;
extern unsigned short   gus_Dsp_write_data2;
extern unsigned short   gus_Dsp_write_data1;

//<><><><><>2007.1.26移植追加<><><><><><><>
extern unsigned char    PC_v_data_no;
//a
extern unsigned int     PC_v_data_a1;
extern unsigned int     PC_v_data_a2;
extern unsigned int     PC_v_data_a3;
extern unsigned int     PC_v_data_a4;
extern unsigned int     PC_v_data_a_result;
//b
extern unsigned int     PC_v_data_b1;
extern unsigned int     PC_v_data_b2;
extern unsigned int     PC_v_data_b3;
extern unsigned int     PC_v_data_b4;
extern unsigned int     PC_v_data_b_result;
//c
extern unsigned int     PC_v_data_c1;
extern unsigned int     PC_v_data_c2;
extern unsigned int     PC_v_data_c3;
extern unsigned int     PC_v_data_c4;
extern unsigned int     PC_v_data_c_result;
//min
extern unsigned int     PC_v_data_min1;
extern unsigned int     PC_v_data_min2;
extern unsigned int     PC_v_data_min3;
extern unsigned int     PC_v_data_min4;
extern unsigned int     PC_v_data_min_result;
//max
extern unsigned int     PC_v_data_max1;
extern unsigned int     PC_v_data_max2;
extern unsigned int     PC_v_data_max3;
extern unsigned int     PC_v_data_max4;
extern unsigned int     PC_v_data_max_result;

extern unsigned char    guc_PC_V_dsp_write_flag;
//<><><><><><><><><><><><><><><><><><><><><><>



//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>




extern unsigned char    pre_flow_flag;       //2006.3.14 ihara
extern unsigned char    Hand_inching_flag;   //2006.3.14 ihara



extern unsigned char guc_Sequence_mode;
extern unsigned char gub_Err;                          //エラー治具端子出力
extern unsigned char gub_Alarm;                        //アラーム治具端子出力
extern unsigned char gub_System_err;
extern unsigned int    gui_Err_code;


extern unsigned int gtt_test_counter;

extern int DelayTimer;

extern unsigned int gui_Table_code_counter;
extern unsigned int gui_Sp_table_code_counter;

extern unsigned char guc_Hfix_rewrite_check_flag; //半固定データ書き換え確認フラグ
extern unsigned char guc_Val_rewrite_check_flag0; //可変データ書き換え確認フラグ
extern unsigned char guc_Val_rewrite_check_flag1; //可変データ書き換え確認フラグ
extern unsigned char guc_Hfix_val_reset_flag;     // 半固定、可変データリセット
extern unsigned char guc_Adj1_rewrite_check_flag; // 微調項目１書き換え確認フラグ 2007.2.5追加
extern unsigned char guc_Adj2_rewrite_check_flag; // 微調項目２書き換え確認フラグ 2007.2.5追加
extern unsigned char guc_Exd_adj1_rewrite_check_flag; //拡張溶接微調パラメータ個別書き換え確認フラグ 2007.5.29
extern unsigned char guc_Exd_adj2_rewrite_check_flag; //拡張溶接微調パラメータ一括書き換え確認フラグ 2007.5.29
extern unsigned char guc_Method_rewrite_check_flag; //溶接条件データ書き換え確認フラグ 2007.7.6
extern unsigned char guc_0x69_rewrite_check_flag1; //０ｘ６９コマンドのデータ書き換え確認フラグ　2009.07.14



extern short gss_Adj_slow_down;                   //スローダウン調整値（最終値）2007.2.5追加

extern float gsf_Acc1;    //加速度１     2007.2.6
extern float gsf_Acc2;    //加速度２     2007.2.6
extern float gsf_Acc3;    //加速度３     2007.2.6
extern float gsf_Acc4;    //加速度４     2007.2.6
extern float gsf_Acc5;    //加速度５     2007.2.6
extern float gsf_Delay;   //送給ディレイ 2007.2.6
extern float gsf_Re_start;//連続スタート 2007.2.6

extern short gss_Acc1;    //加速度１     2007.2.6
extern short gss_Acc2;    //加速度２     2007.2.6
extern short gss_Acc3;    //加速度３     2007.2.6
extern short gss_Acc4;    //加速度４     2007.2.6
extern short gss_Acc5;    //加速度５     2007.2.6
extern short gss_Delay;   //送給ディレイ 2007.2.6
extern short gss_Re_start;//連続スタート 2007.2.6


extern unsigned char  guc_Table_change_flag; //2007.2.9
extern unsigned char  guc_No_table;          //2007.2.9

extern unsigned char  guc_Program_ver_flag;  //2007.2.13追加

extern unsigned short gus_Imprudence_bkup;   //2007.3.2追加
extern unsigned short gus_Imprudence_work;   //2007.3.2追加

extern unsigned long  gul_Rpm_buff;          //2007.3.15



//２００６．１２．１５　バックＲＡＭテスト
extern unsigned char  test_flag;
extern unsigned short  test_counter;

extern unsigned int gui_Total_weld_time_bkup; //総合溶接時間ＲＡＭから読み出し 2007.3.30
extern unsigned short gus_Total_weld_count_bkup; //2007.4.5
extern unsigned long  gul_Total_wire_feed_bkup; //2007.4.5


extern int     isContArc;
extern int     isEnbDelay;


extern unsigned char  guc_Ad_id_under[];      // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
extern unsigned char  guc_Ad_id_uper[];      // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
extern unsigned char  guc_Ad_data_under[];    // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
extern unsigned char  guc_Ad_data_uper[];    // 拡張溶接微調パラメータ一括受信データ用 2007.5.11
extern unsigned char  guc_Variable_length_flag;


//***** 2007.2.20 割り込みテスト ******
//extern unsigned char Int_test[];          2009.02.16
//extern unsigned short Int_test_index;     2009.02.16


//***** 2007.11.29 リモコン通信実験用 *******
extern unsigned char guc_Com_jog1_data;
extern unsigned char guc_Com_jog2_data;
extern unsigned char guc_In_jog1_data;
extern unsigned char guc_In_jog2_data;
extern unsigned char guc_Jog_rewrite_check_flag;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
extern unsigned char guc_Sw_rewrite_check_flag;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
extern unsigned char guc_Machine_no_flag;
extern unsigned char guc_Initial_display_flag;
extern unsigned short gus_Initial_timer;




extern unsigned char led11_data;
extern unsigned char led12_data;
extern unsigned char led13_data;
extern unsigned char com_led11_data;
extern unsigned char com_led12_data;
extern unsigned char com_led13_data;

extern unsigned char led21_data;
extern unsigned char led22_data;
extern unsigned char led23_data;
extern unsigned char com_led21_data;
extern unsigned char com_led22_data;
extern unsigned char com_led23_data;
extern unsigned char com_led21_okcv_data;
extern unsigned char com_led22_okcv_data;
extern unsigned char com_led23_okcv_data;
extern unsigned char com_led13_dital_data; //2009.04.03
extern unsigned char com_led21_dital_data;
extern unsigned char com_led22_dital_data;
extern unsigned char com_led23_dital_data;

extern signed short test_work1;
extern signed short test_work2;


extern unsigned char guc_Material_condition_counter;
extern unsigned char guc_Material_condition_data;

extern unsigned char guc_Wire_condition_counter;
extern unsigned char guc_Wire_condition_data;

extern unsigned char guc_Method_condition_counter;
extern unsigned char guc_Method_condition_data;
extern unsigned char guc_Remo_table_check_flag;
extern unsigned char guc_Okcv_select_flag;
extern unsigned char guc_Okcv_select_counter;

extern unsigned char guc_Ext_condition_counter;  //2008.11.10
extern unsigned char guc_Ext_condition_data;     //2008.11.10
extern unsigned char guc_Ext_condition_data_bk;  //2008.11.10

//***** BP3関連 2009.01.10 *****
extern unsigned char guc_Ac_wave_counter;        //2009.01.10
extern unsigned char guc_Ac_wave_data;           //2009.01.10
extern unsigned char guc_Ac_wave_data_bk;        //2009.01.10

extern unsigned char guc_Ac_tig_set_counter;     //2009.01.10
extern unsigned char guc_Ac_tig_set_data;        //2009.01.10
extern unsigned char guc_Ac_tig_set_data_bk;     //2009.01.10

extern unsigned char guc_Mix_tig_set_counter;     //2009.01.10
extern unsigned char guc_Mix_tig_set_data;        //2009.01.10
extern unsigned char guc_Mix_tig_set_data_bk;     //2009.01.10

extern unsigned short gus_Sequence_set_data;       //2009.01.13 char->short 2009.01.19
extern unsigned short gus_Sequence_set_data_bk;    //2009.01.13 char->short 2009.01.19
extern unsigned char guc_Pulse_item_counter;      //2009.01.13
extern unsigned char guc_Jog_set_key;             //2009.01.13

extern unsigned int  gui_Navi_table_code_counter; //2009.01.14
extern unsigned char guc_Navi_code_work[];        //2009.01.14
extern unsigned char guc_Navi_material_code[];    //2009.01.14
extern unsigned char guc_Navi_material_counter;   //2009.01.15
extern unsigned char guc_Navi_thickness_code[];   //2009.01.15
extern unsigned char guc_Navi_thickness_counter;  //2009.01.15
extern unsigned char guc_Navi_joint_code[];       //2009.01.15
extern unsigned char guc_Navi_joint_counter;      //2009.01.15
extern unsigned char guc_Navi_direction_code[];   //2009.01.15
extern unsigned char guc_Navi_direction_counter;  //2009.01.15
extern unsigned char guc_Navi_pulse_code[];       //2009.01.15
extern unsigned char guc_Navi_pulse_counter;      //2009.01.15

//スロープ関連 2009.02.02
extern float gf_Up_slop_base_step;
extern float gf_Up_slop_pulse_step;
extern float gf_Up_slop_base_curr;
extern float gf_Up_slop_pulse_curr;
extern float gf_Down_slop_base_step;
extern float gf_Down_slop_pulse_step;
extern float gf_Down_slop_base_curr;
extern float gf_Down_slop_pulse_curr;
extern unsigned short gus_Up_slop_time;
extern unsigned short gus_Down_slop_time;

extern unsigned short gus_Pulse_current;
extern unsigned short gus_Pulse_freq;
extern unsigned short gus_Pulse_duty;



extern unsigned short gus_Ac_frequency;
extern unsigned short gus_Cleaning_duty;
extern unsigned short gus_Mix_ac_ratio;
extern unsigned short gus_Mix_frequency;
extern signed short gss_Arc_spot_time; //2009.03.06 アークスポット時間  2009.03.16 unsigned -> signed


extern float gf_Hot_current_level; //2009.02.13

extern short gss_Output_difference; //2009.02.16
extern float gf_Output_correct_value; //2009.02.16

extern short gss_Max_current; //2009.02.19
extern short gss_Min_current; //2009.02.19

extern short gss_Voltage_ref; //2009.02.20
extern float gf_Out_current;  //2009.02.20
extern float gf_Target_current; //2009.02.20
extern unsigned long gsl_Voltage_ref_add; //2010.01.12

extern short gss_Target_current_sabun_bkup; //2009.02.21
extern short gss_Target_current_sabun;      //2009.02.21

extern unsigned char guc_V_max; //2009.03.13

//***** 各溶接法での調整量の記憶 2009.02.23*******
extern unsigned char guc_Method_m[];
extern unsigned short gus_Main_current_m[];
extern unsigned short gus_Init_current_m[];
extern unsigned short gus_Crat_current_m[];
extern unsigned char guc_Pulse_mode_m[];
extern unsigned char guc_Crater_mode_m[];
extern unsigned char guc_Ac_wave_counter_m[]; //2009.03.13
extern unsigned short gus_Pulse_current_m[];
extern unsigned short gus_Pulse_duty_m[];
extern unsigned short gus_Pulse_frequency_m[];
extern unsigned char guc_AC_cleaning_duty_m[];
extern unsigned short gus_AC_frequency_m[];
extern unsigned char guc_MIX_frequency_m[];
extern unsigned char guc_MIX_duty_m[];
extern short gss_Pre_flow_m[];
extern short gss_After_flow_m[];
extern short gss_Up_slop_m[];
extern short gss_Down_slop_m[];
extern short gss_Arc_spot_time_m[]; //2009.03.06 アークスポット時間
//******************************

//******************************

//******* 温度異常関連 2009.03.13 *******
extern char gsc_Temp_err_year;
extern char gsc_Temp_err_month;
extern char gsc_Temp_err_day;
extern char gsc_Temp_err_hour;
extern char gsc_Temp_err_mini;
extern char gsc_Temp_err_year_work;
extern char gsc_Temp_err_month_work;
extern char gsc_Temp_err_day_work;
extern char gsc_Temp_err_hour_work;
extern char gsc_Temp_err_mini_work;
extern char gsc_Now_year;
extern char gsc_Now_month;
extern char gsc_Now_day;
extern char gsc_Now_hour;
extern char gsc_Now_mini;
extern unsigned char gus_Temp_err_set;
extern unsigned char gus_Temp_err_set_work;
//**************************************


extern short gss_Ct_offset; //2009.04.14
extern short gss_Output_gein; //2009.04.14



extern signed short gs_Okcv_adjust_data;
extern signed short gs_Okcv_adjust_init_data; 		//2008.02.22
extern signed short gs_Okcv_adjust_crat_data;		//2008.02.22
extern signed short gs_Okcv_adjust_wave_data;		//2008.02.26
extern signed short gs_Okcv_adjust_start_data;		//2008.08.05
extern unsigned char guc_Okcv_display_timer;
extern unsigned char guc_Okcv_display_flag;
extern unsigned char guc_Initial_display_flag2; //2007.12.06
extern unsigned char guc_Last_select_sw; //2007.12.07

extern unsigned char guc_Inching_sw_flag;
extern unsigned char guc_Inching_sw_flag_bkup; //2008.09.09
extern unsigned char guc_Gas_on_off_flag;
extern unsigned char guc_Gas_on_off_flag_bkup; //2008.09.09

extern unsigned short gus_Dps_timer; //2007.12.09
extern unsigned char guc_Dps_R8_flag; //2007.12.09
extern unsigned char guc_Dps_M16_flag; //2007.12.09
extern unsigned char guc_Dps_M32_flag; //2007.12.09
extern unsigned char guc_Dps_space_flag; //2007.12.10



//ＲＡＭバックアップ領域
#if 0
extern unsigned char guc_Material_condition_counterb;
extern unsigned char guc_Material_condition_datab;

extern unsigned char guc_Wire_condition_counterb;
extern unsigned char guc_Wire_condition_datab;

extern unsigned char guc_Method_condition_counterb;
extern unsigned char guc_Method_condition_datab;

extern unsigned char guc_Okcv_select_flag_bkup; //2007.12.09
extern unsigned char guc_Okcv_select_counter_bkup; //2008.08.21
extern signed short  gs_Okcv_adjust_data_bkup;  //2007.12.09 
extern signed short gs_Okcv_adjust_init_data_bkup;   //2008.02.26
extern signed short gs_Okcv_adjust_crat_data_bkup;   //2008.02.26
extern signed short gs_Okcv_adjust_wave_data_bkup;   //2008.02.26
extern signed short gs_Okcv_adjust_start_data_bkup;   //2008.08.05

extern unsigned short gus_Weld_current_bkup; //2007.12.09 溶接電流指令値
extern unsigned short gus_Weld_voltage_bkup; //2007.12.09 溶接電圧指令値
extern unsigned short gus_Init_current_bkup; //2008.02.26 初期電流指令値
extern unsigned short gus_Init_voltage_bkup; //2008.02.26 初期電圧指令値
extern unsigned short gus_Crat_current_bkup; //2008.02.26 クレータ電流指令値
extern unsigned short gus_Crat_voltage_bkup; //2008.02.26 クレータ電圧指令値
extern unsigned short gus_Wave_current_bkup; //2008.02.26 波形制御　Ｂ条件　電流指令値
extern unsigned short gus_Wave_voltage_bkup; //2008.02.26 波形制御　Ｂ条件　電圧指令値
extern unsigned short gus_Start_current_bkup; //2008.02.26 波形制御　スタート条件　電流指令値
extern unsigned short gus_Start_voltage_bkup; //2008.02.26 波形制御　スタート条件　電圧指令値

extern signed char    gsc_Select_dital_counter_bkup; //2007.12.11
extern unsigned char  guc_Pulse_mode_datab; //2008.02.08
extern unsigned char  guc_Pulse_type_datab; //2008.02.08
extern unsigned char  guc_Pulse_mode_counterb;//2008.02.08

#endif

extern unsigned short gus_Pre_display_timer; //2007.12.10

extern unsigned char  guc_Select_counter;   //2007.12.11
extern unsigned char  guc_Select_dital_flag; //2007.12.11

extern signed char    gsc_Select_dital_counter; //2007.12.11

extern signed short   gss_Select_dital[]; //2007.12.11　詳細データ格納変数

extern unsigned char  guc_Pulse_mode_data; //2007.12.14
extern unsigned char  guc_Pulse_mode_counter; //2007.12.14


extern unsigned char guc_Current_test_flag; //2008.01.21
extern unsigned char guc_Voltage_test_flag; //2008.01.21
extern signed short  gss_Curr_result_test;	 //2008.01.21 
extern signed short  gss_Volt_result_test;	 //2008.01.21 


extern unsigned char guc_Select_param_set_counter;  		//2008.02.22
extern unsigned char guc_Select_current_sel_counter;		//2008.02.22
extern unsigned char guc_Select_param_set_flag;     		//2008.02.22
extern unsigned char guc_Select_current_sel_flag;   		//2008.02.22


extern unsigned char  guc_Initial_load_data; //2008.02.26

extern signed short gss_Current_result_work; //2008.03.03
extern signed short gss_Voltage_result_work; //2008.03.03
extern signed short gss_Weld_end_current;    //2008.03.03
extern signed short gss_Weld_end_voltage;    //2008.03.03
extern signed short gss_Current_work; //2008.03.03
extern signed short gss_Voltage_work; //2008.03.03

extern signed short gss_RCurrent_work; //2009.07.28
extern signed short gss_RVoltage_work; //2009.07.28

extern signed short gss_Base_current_work; //2009.03.23
extern signed short gss_Base_voltage_work; //2009.03.23
extern signed short gss_Peak_current_work; //2009.03.23
extern signed short gss_Peak_voltage_work; //2009.03.23
extern signed int gsi_Base_current_result_work; //2009.03.23
extern signed int gsi_Base_voltage_result_work; //2009.03.23
extern signed int gsi_Peak_current_result_work; //2009.03.23
extern signed int gsi_Peak_voltage_result_work; //2009.03.23
extern long gsl_Current_result_work2; //2009.04.11
extern long gsl_Voltage_result_work2; //2009.04.11

//実効値計算関連
extern long gsl_Current_result_work_rms; //2009.03.26
extern long gsl_Voltage_result_work_rms; //2009.03.26
extern long gsl_Base_current_result_work_rm; //2009.03.26
extern long gsl_Base_voltage_result_work_rm; //2009.03.26

//リモコン再生関連
extern unsigned short gus_Remo_play_ch_data; //2009.03.28
extern unsigned char guc_Remo_play_ch;       //2009.03.28
extern unsigned char guc_Remo_play_ch_bkup;  //2009.03.30



extern float gf_Frequence_adjust_data;            //2008.03.27中川さん要請で追加
extern float gf_Base_adjust_data;                 //2008.03.27中川さん要請で追加

extern unsigned char guc_Half_pc_data_flag;  //2008.06.03 ＰＣに半固定パラメータを返信する。
extern unsigned short gus_Half_pc_data;      //2008.06.03 ＰＣに半固定パラメータを返信する。

extern unsigned char guc_Crater_mode_counter;
extern unsigned char guc_Adjust_item_counter; //2008.08.28

extern unsigned char guc_Ch_no; //2008.08.07
extern unsigned char guc_Ch_no_bkup; //2008.08.19

extern unsigned char guc_Pass_word; //2008.09.10
extern unsigned char guc_Controller_lock; //2008.09.10

extern unsigned char guc_Adjust_item_counter_work; //2008.08.28 -> 2008.09.12グローバル変数に変更

extern signed short gss_En_def; //ＥＮ比率のデフォルト 2008.09.16
extern signed short gss_En_a;   //ＥＮ比率 2008.09.16
extern signed short gss_En_a_bkup; //ＥＮ比率バックアップ 2008.09.25
extern signed char  gsc_Va; //2008.09.26
extern signed short gss_WFe_Sirei_W; //2008.09.30
extern unsigned char guc_Robot_connect_flag; //2008.10.03
extern unsigned char guc_Robot_connect_one_shot_flag;//2008.10.03
extern unsigned char guc_Gas_check_cancel_flag; //2008.10.06
extern unsigned char guc_Controller_gas_sw_cancel; //2008.10.06
extern unsigned char guc_Controller_inc_sw_cancel; //2008.10.06
extern unsigned char guc_Pulse_mode_data_bkup; //2008.10.08
//extern unsigned char dummy1;

//インチングスロースタート関連
extern unsigned short gus_Inching_curr;
extern unsigned short gus_Inching_curr_bk_up;


//extern unsigned short test_Buff[96]; //test用 2008.09.16


//***2008.08.21***
extern unsigned short gus_Weld_current;     //溶接電流指令値
extern unsigned short gus_Weld_voltage;     //溶接電圧指令値
extern unsigned short gus_Init_current;     //初期電流指令値
extern unsigned short gus_Init_voltage;     //初期電圧指令値
extern unsigned short gus_Crat_current;     //クレータ電流指令値
extern unsigned short gus_Crat_voltage;     //クレータ電圧指令値
extern unsigned short gus_Wave_current;     //波形制御　Ｂ条件　電流指令値
extern unsigned short gus_Wave_voltage;     //波形制御　Ｂ条件　電圧指令値
extern unsigned short gus_Start_current;    //波形制御　スタート条件　電流指令値
extern unsigned short gus_Start_voltage;    //波形制御　スタート条件　電圧指令値
extern unsigned char  guc_Pulse_type_data;

extern unsigned short gus_Pre_flow_time;    //プリフロー時間 2009.01.22
extern unsigned short gus_After_flow_time;  //アフターフロー時間 2009.01.22
//****************
extern unsigned short gss_Motor_acc1;       //2008.11.17 起動時のモータディレイ時の加速度



//<><><><><> ｃｈ領域 2008.08.06 <><><><><>
extern unsigned char guc_Material_condition_counterc[CH];
extern unsigned char guc_Material_condition_datac[CH];

extern unsigned char guc_Wire_condition_counterc[CH];
extern unsigned char guc_Wire_condition_datac[CH];

extern unsigned char guc_Method_condition_counterc[CH];
extern unsigned char guc_Method_condition_datac[CH];

//2008.11.10
extern unsigned char guc_Ext_condition_counterc[CH];
extern unsigned char guc_Ext_condition_datac[CH];


extern unsigned char guc_Okcv_select_flag_ch[CH]; //2007.12.09
extern signed short gs_Okcv_adjust_data_ch[CH];   //2007.12.09 実験のため移動 2008.02.26復帰
extern signed short gs_Okcv_adjust_init_data_ch[CH];   //2008.02.26
extern signed short gs_Okcv_adjust_crat_data_ch[CH];   //2008.02.26
extern signed short gs_Okcv_adjust_wave_data_ch[CH];   //2008.02.26
extern signed short gs_Okcv_adjust_start_data_ch[CH];   //2008.08.05

extern unsigned short gus_Weld_current_ch[CH]; //2007.12.09 溶接電流指令値
extern unsigned short gus_Weld_voltage_ch[CH]; //2007.12.09 溶接電圧指令値
extern unsigned short gus_Init_current_ch[CH]; //2008.02.26 初期電流指令値
extern unsigned short gus_Init_voltage_ch[CH]; //2008.02.26 初期電圧指令値
extern unsigned short gus_Crat_current_ch[CH]; //2008.02.26 クレータ電流指令値
extern unsigned short gus_Crat_voltage_ch[CH]; //2008.02.26 クレータ電圧指令値
extern unsigned short gus_Wave_current_ch[CH]; //2008.02.26 波形制御　Ｂ条件　電流指令値
extern unsigned short gus_Wave_voltage_ch[CH]; //2008.02.26 波形制御　Ｂ条件　電圧指令値
extern unsigned short gus_Start_current_ch[CH]; //2008.08.05 波形制御　スタート条件　電流指令値
extern unsigned short gus_Start_voltage_ch[CH]; //2008.08.05 波形制御　スタート条件　電圧指令値

extern unsigned short gus_Pre_flow_time_ch[CH]; //2009.01.28 プリフロー時間
extern unsigned short gus_After_flow_time_ch[CH]; //2009.01.28 アフターフロー時間

extern unsigned short gus_Up_slop_time_ch[CH];  //2009.02.02 アップスロープ時間
extern unsigned short gus_Down_slop_time_ch[CH];//2009.02.02 ダウンフロー時間

extern unsigned short gus_Pulse_current_ch[CH]; //2009.02.03 パルス電流
extern unsigned short gus_Pulse_freq_ch[CH];    //2009.02.03 パルス周波数
extern unsigned short gus_Pulse_duty_ch[CH];    //2009.02.03 パルスデューティ

extern unsigned short gus_Ac_frequency_ch[CH];  //2009.02.06 交流周波数
extern unsigned short gus_Cleaning_duty_ch[CH]; //2009.02.06 クリーニング幅
extern unsigned short gus_Mix_ac_ratio_ch[CH];  //2009.02.06 直流比率
extern unsigned short gus_Mix_frequency_ch[CH]; //2009.02.06 ＭＩＸ周波数
extern signed short gss_Arc_spot_time_ch[CH]; //2009.03.06 アークスポット時間 2009.03.16 unsigned -> signed


extern signed short gss_Select_dital_ch[SELECT_DITAL_MAX+1][CH]; //2007.12.11　詳細データ格納変数  // Phase11 by @Tny 2008/09/16

extern unsigned char  guc_Pulse_mode_data_ch[CH]; //2007.12.14
extern unsigned char  guc_Pulse_mode_counter_ch[CH]; //2007.12.14


extern unsigned char  guc_Pulse_mode_datac[CH]; //2008.02.08
extern unsigned char  guc_Pulse_type_datac[CH]; //2008.02.08
extern unsigned char  guc_Pulse_mode_counterc[CH];//2008.02.08

extern unsigned char  guc_Crater_mode_counterc[CH]; //2008.08.21
extern unsigned char  guc_Ac_wave_counterc[CH];     //2009.03.13

extern unsigned char  guc_Out_port[CH][17+1];          	//2008.08.23	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
extern unsigned char  guc_In_port[CH][17+1];          	//2008.08.25	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
extern unsigned char  guc_Analog_port[CH][17+1];        //2008.08.25	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
extern unsigned char  guc_Out_port_ch[CH][17+1];        //2008.08.23	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
extern unsigned char  guc_In_port_ch[CH][17+1];         //2008.08.25	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
extern unsigned char  guc_Analog_port_ch[CH][17+1];     //2008.08.25	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny

extern unsigned char  guc_Write_check_flag_ch[CH];     //2008.09.09

extern unsigned char guc_Pass_word_ch; //2008.09.10
extern unsigned char guc_Controller_lock_ch; //2008.09.10

//Parameter       gtt_Parameter[CH]; //2008.02.25
//<><><><><><><><><><><><><><><><><><><><><>

extern unsigned char gsc_Day_max_work; //2008.08.26 閏年、各月用最大日数



extern signed short test_data;


extern char  dummy_access;

//--------- IIF by @Tny 2008/08/26 ------------
#if true
extern ubool            gb_IIF_Select;
extern unsigned short  gus_IIF_DebugTimer1;
extern ubool            gb_IIF_DebugFlag1;
extern unsigned char   guc_Iif_output;
extern unsigned char   guc_Iif_bit_input; //2008.09.01 ihara

#endif
//--------------------------------------------
//--------- RTC by @Tny 2008/08/28 ------------
#if true
extern unsigned short  gus_RTC_ReNew;
#endif
//--------------------------------------------
//--------- RTC by @Tny 2008/09/01 ------------
#if true
extern unsigned short  gus_cRTC_AdjustCount;       // RTC周波数測定用カウンタ
extern unsigned long   gul_vRTC_FrequencyCount;    // RTC周波数カウンタ

extern ubool            gb_RTC_Debug_Sec;           // ＲＴＣ動作確認用フラグ（秒）
extern unsigned short  gus_RTC_cDebug_1;           // ＲＴＣ動作確認用カウンタ＃１
#endif
//--------------------------------------------
//----- Phase2(Debug) by @Tny 2008/09/02 -----
#if true
extern ubool            gb_Fram_Proc;               // ＦＲＡＭ操作中フラグ
extern unsigned char   guc_Fram_Phase;             // ＦＲＡＭ操作フェーズ
extern unsigned short  gus_Fram_Page;              // ＦＲＡＭ転送パケット番号
extern unsigned short  gus_Fram_Packet_Wait;       // パケット送受信間隔
#endif
//--------------------------------------------
//--------- Phase3 by @Tny 2008/09/05 --------
#if false //2009.03.16 del
extern unsigned short  gt_Memory_copy_area_length[];    // エリア別メモリ転送パケット数テーブル
extern unsigned char  *gt_Memory_copy_area_Tx[];        // エリア別メモリ送信先エリアテーブル
extern unsigned char  *gt_Memory_copy_area_Rx[];        // エリア別メモリ受信先エリアテーブル
extern unsigned char   guc_Fram_tx_error;               // メモリ転送失敗カウンタ
#endif
//--------------------------------------------
//--------- Phase4 by @Tny 2008/09/08 --------
#if true
extern unsigned short  gus_Iif_ad_input[3];         // IIFからのＡ／Ｄ変換値
extern unsigned short  gus_Iif_comunication_timer;  // 
extern unsigned short  gus_Iff_Detect_disp_timer;   // IIF検出表示タイマー
extern unsigned char   BackUp16LedData[18];         //
extern ubool            gb_Iif_comuni_failed;        //
#endif
//--------------------------------------------
//--------- Phase5 by @Tny 2008/09/09 --------
#if true
extern union{
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
extern ubool            gb_R8_comuni;               // Ｒ８送信データ識別フラグ
extern unsigned short  gus_R8_TX_cDebug_1;         // Ｒ８送信データ試験カウンタ＃１
#endif
//--------------------------------------------

//----- Phase6 by @Tny 2008/09/10 -----
#if true
extern struct gtt_Error_History     gtt_Error_History;              // エラー履歴テーブル
extern struct gtt_Error_History     gtt_Backup_Error_History;       // エラー履歴テーブル（ＦＲＡＭ側）
extern ubool                         gb_Error_information_record;    // エラー情報記憶実行フラグ
extern unsigned char                guc_Error_no_backup;            // エラー番号記録値
#endif
//--------------------------------------------
//----- Phase7 by @Tny 2008/09/10 -----
#if true
extern ubool             gb_Error_Display_Sending;   // エラー情報送信要求フラグ
extern unsigned char    guc_Error_code;             // エラー番号
extern unsigned char    guc_Error_Display[100][18]; // エラー内容テーブル
extern ubool             gb_Error_History_Write;     // エラー履歴テーブル保存フラグ
extern unsigned short   gus_Iif_BuiltIn;            // IIF接続フラグ
extern unsigned short   gus_Backup_Iif_BuiltIn;     // IIF接続フラグ（ＦＲＡＭ側）
extern ubool             gus_Iif_BuiltIn_write;      // IIF接続フラグ保存フラグ
extern ubool             gb_Iif_BuiltIn;             // IIF接続認識フラグ
extern ubool             gb_Iif_Input;               // IIFデータ受信フラグ
extern unsigned long    gus_Iif_Detect_Timer;       // IIF接続確認時間カウンタ
#endif
//--------------------------------------------
//----- Phase10 by @Tny 2008/09/16 -----
#if true
extern unsigned int    gui_Err_code0;	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
extern unsigned int    gui_Err_code1;
extern unsigned int    gui_Err_code2;
extern unsigned int    gui_Err_code3;
#endif
//--------------------------------------------
//----- Phase11 by @Tny 2008/09/16 -----
#if true
extern unsigned char   guc_Sub_16Led_display[18];  // サブ表示エリア
extern unsigned char   guc_Sub_display_flag;       // サブ表示フラグ
#endif
//--------------------------------------------
//----- Phase12 by @Tny 2008/09/17 -----
#if true
extern unsigned short  guc_Init_wait_sequence;     // 初期シーケンス待ち時間
extern struct{
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
extern struct{
        	unsigned char   uc_Proc;                        // 制御有効フラグ
        	unsigned char   uc_ON_Time;			            // 点滅ＯＮ時間
        	unsigned char   uc_OFF_Time;		            // 点滅ＯＦＦ時間
        	unsigned char   uc_vCount;			            // 点滅回数
        } gtt_LED_control_backup[10];	                // ＬＥＤ表示制御バックアップテーブル
extern unsigned char   guc_Error_return_LED_control_A;  // エラー復帰時ＬＥＤ表示制御インデックス：Ａ
extern unsigned char   guc_Error_return_LED_control_B;  // エラー復帰時ＬＥＤ表示制御インデックス：Ｂ
extern ubool            gb_Error_blink;                  // エラー点滅制御要求フラグ
#endif
//--------------------------------------------


extern float Fq_test;

//----- Phase15 by @Tny 2008/09/19 -----
#if true
extern ubool            gb_15SEG_LED_Error_Disp_Hold;    // エラー表示データ送信中フラグ
#endif
//--------------------------------------------
//----- Phase21 by @Tny 2008/10/02 -----
#if false //2009.03.16

// 溶接条件データ系（ＣＨ０(現状)～ＣＨ１６）
extern struct{
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
extern struct{
        unsigned char               vStart;
        signed short                ss_Service_data[SERVICE_DATA_NO];
        // エラー履歴データ系
        struct gtt_Error_History    Error_History;
        unsigned char               vEnd[(32/FRAM_PAKECT)*1];   // 余白部
} gtt_ServiceData;

extern unsigned short  gus_Display_command_stop;    // メモリ転送後表示コマンド送信停止カウンタ
extern ubool            gb_Memory_copy_recv_ended;   // メモリ転送受信完了フラグ
#endif
//--------------------------------------------
//----- Phase22 by @Tny 2008/10/07 -----
#if true
extern unsigned short  gus_Iif_Purge_Judgment;      // ＩＩＦ切断（切り離し）判定カウンタ
extern unsigned char   guc_Welding_Play_Ch_no;     // 溶接中再生チャンネル
extern ubool            gb_Welding_Play_Change;     // 溶接中再生チャンネル実行フラグ
#endif
//--------------------------------------------
//----- Phase26 by @Tny 2008/10/23 -----
#if true
extern ubool            gb_Controller_UnConnect;         // コントローラ未接続確認フラグ
extern ubool            gb_Ping_to_Controller;           // コントローラ未接続確認実行フラグ
extern unsigned short  gus_Controller_Connect_Timer;    // コントローラ接続確認タイマー
#endif
//--------------------------------------------

//----- Phase29 by @Tny 2008/11/21 -----
#if true
extern unsigned short	gus_Pri_volt_err_timer;			// 一次電圧低異常検知ディレイタイマー
#endif
//--------------------------------------------



extern unsigned char guc_En_table_access_test; //2008.11.19ＥＮテーブルアクセステスト用


extern unsigned char guc_No_act_flag; //2008.11.25


//<><><>交流湯沢関連 2008.11.26<><><>
extern float T1;
extern float T3;
extern float T4;
extern float Ib2;

extern float gf_Frq_data;                   //2008.12.16 F2/F1の答え

extern float gf_Wf_max_limit;           //2008.12.26
extern float gf_Correct_a;              //2008.12.26
extern float gf_Correct_b;              //2008.12.26


// BP4 Phase3 by @Tny 2009.01.13
extern unsigned char	guc_Menu_Hierarchy;		// 詳細メニュー設定階層フラグ
extern ubool				gb_2Line_FirstDisplay;	// 初回二行目表示フラグ		BP4 Phase3 by @Tny 2009.01.15

// BP4 Phase4 by @Tny 2009.01.15
extern ubool				gb_RTC_Sec_Colon;		// 秒コロン表示フラグ

// BP4 Phase5 by @Tny 2009.01.21
extern unsigned char	guc_StringInput;			// 文字列入力処理実行中フラグ
extern signed short		gss_SelectCharIndex;		// 選択文字インデックス
extern unsigned short	gus_InputCharIndex;			// 入力文字位置インデックス
extern unsigned char	gt_SelectCharacter[21];		// 入力文字列データ格納エリア（最大２０文字）
extern const char		*SelectCharacterSrc;
extern unsigned char	SelectCharacter[200];		// 選択文字データ
extern ubool				gb_RecWeldCond;				// 記憶条件データの有無
extern unsigned char	gt_WeldCondName[CH][21];	// 条件名文字列データ格納エリア（最大２０文字×１７条件）
extern unsigned char	gt_WeldCondName_ch[CH][21];	// 条件名文字列データ格納エリア for FRAM （最大２０文字×１７条件）
extern ubool				gb_WeldCondNameWrite;		// 溶接条件名書き込み要求フラグ

//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
extern unsigned char	guc_Lcd_Bright;				// コントラストデータ
extern unsigned char	guc_Lcd_Bright_Back;		// コントラストデータ記憶値
extern ubool				gb_LcdBrightWrite;			// ＬＣＤコントラスト値の記録の要求フラグ
//-----------------------------------------------------------

//-----------------------------------------------------------
//BP4 Phase10 by @Tny 2009.02.18	表示コマンド系送信要求フラグ
extern ubool			gb_RemCom_0x20;
extern ubool			gb_RemCom_0x21;
extern ubool			gb_RemCom_0x22;
extern ubool			gb_RemCom_0x23;
extern ubool			gb_RemCom_0x32;
extern ubool			gb_RemCom_0x33;	// 2019.09.02
extern ubool			gb_RemCom_0x34;
extern ubool			gb_RemCom_0x35;
extern ubool			gb_RemCom_0x36;
extern ubool			gb_RemCom_0x37;
extern ubool			gb_RemCom_0x38;
extern ubool			gb_RemCom_0x39;
//-----------------------------------------------------------
//-----------------------------------------------------------
//BP4 Phase10 by @Tny 2009.02.18
extern ubool				gb_ComSend1msec;	// １ｍ秒毎データ送信用フラグ
extern unsigned short	gus_RemoInput[10];	// リモコン入力データ（０：デジタル入力／１～４：Ａ／Ｄ入力値）
//-----------------------------------------------------------
//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23
extern ubool				gb_ServiceMenu;		// サービスマンメニュー要求フラグ
extern ubool				gb_RescueMenu;		// レスキュー処理要求フラグ
extern ubool				gb_JogLock;			// ＪＯＧ決定キー無効化フラグ
extern unsigned short	gus_MessageTimer;	// メッセージ表示時間（１００ｍ秒単位）
extern const char		*PassSelectCharacterSrc;
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//BP4 Phase14 by @Tny 2009.02.24
extern ubool				gb_RamAllClear;		// メモリ・オールクリア実行フラグ
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.11
extern ubool				gb_RescueOpeningDisp;	// レスキュー・メニューのオープニング画面の表示要求フラグ
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// BP4 田中追加　2009.04.06 CTOFFSET
extern short gtt_DSPCToffset;			//DSP自動オフセット調整値
//--------------------------------------------------------------------

//<><><> ＡＣ周波数制御に用いる電流指令値 2010.01.07 <><><>
extern short gss_Pre_current;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><> 溶接電流指令値テーブル変数 2010.02.19 <><><>
extern short gss_Current_table_data[]; 
//<><><><><><><><><><><><><><><><><><><><><><><><><><>


#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	//<><><><><><>ＩＩＦ汎用出力関連<><><><><><>
	extern unsigned char guc_General1_input;
	extern unsigned char guc_General2_input;
	extern unsigned char guc_General3_input;
	//<><><><><><><><><><><><><><><><><><><><><>
	//<><><><><><> ＩＩＦ関連 <><><><><><><><><>
	extern short gss_Iif_analog_shift[4];
	extern float gf_Iif_analog_revise[4];
	extern unsigned char guc_Okcv_select_flag_bkup_iif;
	//<><><><><><><><><><><><><><><><><><><><><>
	//<><><> ＩＩＦ　アナログ部シフト量の書き込み <><><>
	extern short gss_Iif_analog_shift_memory[4];
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	extern ubool	gb_External_IIF;	// 外部拡張ユニット接続フラグ（true=外部拡張ユニット／false=ＩＩＦ）
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny


// <IIF NEW> 2009.11.17
extern unsigned short	gus_Iif_Set_Menu;			// ＩＩＦ設定項目内番号
extern unsigned short	gus_Iif_Set_Dital;			// ＩＩＦ設定項目内種類
extern unsigned short	gus_Iif_PortContact;		// ＩＩＦ設定項目内接点
extern ubool				gb_Iif_ChangeSetting;		// ＩＩＦ設定項目内変更確認フラグ
extern ubool				gb_Iif_Reboot;				// ＩＩＦ設定後再起動フラグ
extern ubool				gb_Iif_AnalogCalibration;	// ＩＩＦ設定アナログ入力ポートのシフト量校正処理判定フラグ
extern ubool		gb_Iif_JogLock[IIF_ANALOG_SERECT];	// ＩＩＦ接続時ＪＯＧ変更禁止フラグ 2009.12.02 by @Tny
//<><><><><><><><><><><><><><><><><><><><><>

//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
extern ubool				gb_Iif_First_Toch_sw;		// ＩＩＦ接続時ＴＳ状態確認フラグ
//-------------------------------------------------
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 5)>	2011.10.26 by @Tny
extern ubool				gb_Iif_Disconnect;			// ＩＩＦ切断フラグ
//-------------------------------------------------

//-------------------------------------------------
// 2019.06.10
extern NAVITABLE   const   NaviTable[];
//-------------------------------------------------

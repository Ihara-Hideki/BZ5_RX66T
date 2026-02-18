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
#include "custom.h"



//unsigned short test_counter;
//unsigned char  test_flag;


//unsigned int gui_Total_weld_time_bkup; //2007.3.30
//unsigned short gus_Total_weld_count_bkup; //2007.4.5
//unsigned long  gul_Total_wire_feed_bkup; //2007.4.5



/********** ｃｈ領域 2008.08.06 **********/
unsigned char guc_Material_condition_counterc[CH];
unsigned char guc_Material_condition_datac[CH];

unsigned char guc_Wire_condition_counterc[CH];
unsigned char guc_Wire_condition_datac[CH];

unsigned char guc_Method_condition_counterc[CH];
unsigned char guc_Method_condition_datac[CH];

unsigned char guc_Ext_condition_counterc[CH];   //2008.11.10
unsigned char guc_Ext_condition_datac[CH];   //2008.11.10

unsigned char guc_Okcv_select_flag_ch[CH]; //2007.12.09
signed short gs_Okcv_adjust_data_ch[CH];   //2007.12.09 実験のため移動 2008.02.26復帰
signed short gs_Okcv_adjust_init_data_ch[CH];   //2008.02.26
signed short gs_Okcv_adjust_crat_data_ch[CH];   //2008.02.26
signed short gs_Okcv_adjust_wave_data_ch[CH];   //2008.02.26
signed short gs_Okcv_adjust_start_data_ch[CH];   //2008.08.05

unsigned short gus_Weld_current_ch[CH]; //2007.12.09 溶接電流指令値
unsigned short gus_Weld_voltage_ch[CH]; //2007.12.09 溶接電圧指令値
unsigned short gus_Init_current_ch[CH]; //2008.02.26 初期電流指令値
unsigned short gus_Init_voltage_ch[CH]; //2008.02.26 初期電圧指令値
unsigned short gus_Crat_current_ch[CH]; //2008.02.26 クレータ電流指令値
unsigned short gus_Crat_voltage_ch[CH]; //2008.02.26 クレータ電圧指令値
unsigned short gus_Wave_current_ch[CH]; //2008.02.26 波形制御　Ｂ条件　電流指令値
unsigned short gus_Wave_voltage_ch[CH]; //2008.02.26 波形制御　Ｂ条件　電圧指令値
unsigned short gus_Start_current_ch[CH]; //2008.08.05 波形制御　スタート条件　電流指令値
unsigned short gus_Start_voltage_ch[CH]; //2008.08.05 波形制御　スタート条件　電圧指令値

unsigned short gus_Pre_flow_time_ch[CH]; //2009.01.28 プリフロー時間
unsigned short gus_After_flow_time_ch[CH]; //2009.01.28 アフターフロー時間

unsigned short gus_Up_slop_time_ch[CH];  //2009.02.02 アップスロープ時間
unsigned short gus_Down_slop_time_ch[CH];//2009.02.02 ダウンフロー時間


unsigned short gus_Pulse_current_ch[CH]; //2009.02.03 パルス電流
unsigned short gus_Pulse_freq_ch[CH];    //2009.02.03 パルス周波数
unsigned short gus_Pulse_duty_ch[CH];    //2009.02.03 パルスデューティ

unsigned short gus_Ac_frequency_ch[CH];  //2009.02.06 交流周波数
unsigned short gus_Cleaning_duty_ch[CH]; //2009.02.06 クリーニング幅
unsigned short gus_Mix_ac_ratio_ch[CH];  //2009.02.06 直流比率
unsigned short gus_Mix_frequency_ch[CH]; //2009.02.06 ＭＩＸ周波数
signed short gss_Arc_spot_time_ch[CH]; //2009.03.06 アークスポット時間 2009.03.16 unsigned->signed



signed short gss_Select_dital_ch[SELECT_DITAL_MAX+1][CH]; //2007.12.11　詳細データ格納変数  // Phase11 by @Tny 2008/09/16

unsigned char  guc_Pulse_mode_data_ch[CH]; //2007.12.14
unsigned char  guc_Pulse_mode_counter_ch[CH]; //2007.12.14


unsigned char  guc_Pulse_mode_datac[CH]; //2008.02.08
unsigned char  guc_Pulse_type_datac[CH]; //2008.02.08
unsigned char  guc_Pulse_mode_counterc[CH];//2008.02.08

unsigned char  guc_Crater_mode_counterc[CH]; //2008.08.21
unsigned char  guc_Ac_wave_counterc[CH];     //2009.03.13

unsigned char  guc_Out_port_ch[CH][17+1];        //2008.08.23	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
unsigned char  guc_In_port_ch[CH][17+1];         //2008.08.25	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny
unsigned char  guc_Analog_port_ch[CH][17+1];     //2008.08.25	//	<<<EXTERNAL IIF NEW>>>	開始番号を１からに合わす＆１０ビット対応	2011.10.07 by @Tny

Parameter      gtt_Parameter_ch[CH]; //2008.02.25
Special_menu   gtt_Special_menu_ch[CH]; //2008.08.22
Calender       gtt_Calender_bkup;      //2008.08.25

unsigned char  guc_Write_check_flag_ch[CH]; //2008.09.09

unsigned char guc_Pass_word_ch; //2008.09.10
unsigned char guc_Controller_lock_ch; //2008.09.10


//***** 各溶接法での調整量の記憶 2009.02.23*******
unsigned char guc_Method_m[7];
unsigned short gus_Main_current_m[27];                  //2009.04.01 7->27
unsigned short gus_Init_current_m[27]; //2009.02.24       2009.04.01 7->27
unsigned short gus_Crat_current_m[27]; //2009.02.24       2009.04.01 7->27
unsigned char guc_Pulse_mode_m[7];
unsigned char guc_Crater_mode_m[7];
unsigned char guc_Ac_wave_counter_m[7]; //2009.03.13
unsigned short gus_Pulse_current_m[27];                //2009.04.01 7->27
unsigned short gus_Pulse_duty_m[7];
unsigned short gus_Pulse_frequency_m[7];
unsigned char guc_AC_cleaning_duty_m[27];              //2009.04.01 7->27
unsigned short gus_AC_frequency_m[27];                 //2009.04.01 7->27
unsigned char guc_MIX_frequency_m[7];
unsigned char guc_MIX_duty_m[7];
short gss_Pre_flow_m[7];
short gss_After_flow_m[7];
short gss_Up_slop_m[7];
short gss_Down_slop_m[7];
short gss_Arc_spot_time_m[7]; //2009.03.06 アークスポット時間
/*****************************************/


//******* 温度異常関連 2009.03.13 *******
char gsc_Temp_err_year;
char gsc_Temp_err_month;
char gsc_Temp_err_day;
char gsc_Temp_err_hour;
char gsc_Temp_err_mini;
unsigned char gus_Temp_err_set;
//***************************************



#if 0
/********** BACK UP領域 2008.08.06 **********/
unsigned char guc_Material_condition_counterb;
unsigned char guc_Material_condition_datab;

unsigned char guc_Wire_condition_counterb;
unsigned char guc_Wire_condition_datab;

unsigned char guc_Method_condition_counterb;
unsigned char guc_Method_condition_datab;

unsigned char guc_Okcv_select_flag_bkup; //2007.12.09
signed short gs_Okcv_adjust_data_bkup;   //2007.12.09 実験のため移動 2008.02.26復帰
signed short gs_Okcv_adjust_init_data_bkup;   //2008.02.26
signed short gs_Okcv_adjust_crat_data_bkup;   //2008.02.26
signed short gs_Okcv_adjust_wave_data_bkup;   //2008.02.26
signed short gs_Okcv_adjust_start_data_bkup;   //2008.08.05

unsigned short gus_Weld_current_bkup; //2007.12.09 溶接電流指令値
unsigned short gus_Weld_voltage_bkup; //2007.12.09 溶接電圧指令値
unsigned short gus_Init_current_bkup; //2008.02.26 初期電流指令値
unsigned short gus_Init_voltage_bkup; //2008.02.26 初期電圧指令値
unsigned short gus_Crat_current_bkup; //2008.02.26 クレータ電流指令値
unsigned short gus_Crat_voltage_bkup; //2008.02.26 クレータ電圧指令値
unsigned short gus_Wave_current_bkup; //2008.02.26 波形制御　Ｂ条件　電流指令値
unsigned short gus_Wave_voltage_bkup; //2008.02.26 波形制御　Ｂ条件　電圧指令値
unsigned short gus_Start_current_bkup; //2008.08.05 波形制御　スタート条件　電流指令値
unsigned short gus_Start_voltage_bkup; //2008.08.05 波形制御　スタート条件　電圧指令値

signed short gss_Select_dital[15]; //2007.12.11　詳細データ格納変数

unsigned char  guc_Pulse_mode_data; //2007.12.14
unsigned char  guc_Pulse_mode_counter; //2007.12.14


unsigned char  guc_Pulse_mode_datab; //2008.02.08
unsigned char  guc_Pulse_type_datab; //2008.02.08
unsigned char  guc_Pulse_mode_counterb;//2008.02.08

Parameter       gtt_Parameter; //2008.02.25
/*****************************************/
#endif

unsigned char  guc_Initial_load_data; //2008.02.26



//------ Phase2(Debug) by @Tny 2008/09/02 ------
//------ Phase3(Debug) by @Tny 2008/09/04 ------
//ダミーエリア（ＦＲＡＭエリアへ移動）
//
#if false //2010.03.10 
unsigned char   FramData1[16384+1]; // Phase2(Debug:16kB) 2008/09/02 @Tny
unsigned char   FramData2[16384+1]; // Phase2(Debug:16kB) 2008/09/02 @Tny
#endif
//---------------------------------------------------------------------

//----- Phase6 by @Tny 2008/09/11 -----
#if true
struct gtt_Error_History    gtt_Backup_Error_History;  // エラー履歴テーブル
unsigned short              gus_Backup_Iif_BuiltIn;    // IIF接続フラグ
#endif
//--------------------------------------------

// BP4 Phase5 by @Tny 2009.01.21
unsigned char	gt_WeldCondName_ch[CH][21];		// 条件名文字列データ格納エリア（最大２０文字×１７条件）

//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
unsigned char	guc_Lcd_Bright_Back;			// コントラストデータ記憶値
//-----------------------------------------------------------
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
//<><><> ＩＩＦ　アナログ部シフト量の書き込み <><><>
	short gss_Iif_analog_shift_memory[4];
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

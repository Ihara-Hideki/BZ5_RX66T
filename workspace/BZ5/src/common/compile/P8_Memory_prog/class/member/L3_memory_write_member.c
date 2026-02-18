//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍｅｍｏｒｙ＿ｗｒｉｔｅ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      指定されたｃｈに溶接機のパラメータの内容を書き込む。
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2008.08.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

void memory_write_member(unsigned char Ch_no)
{
     unsigned char puc_Index;
 
//--------- Phase13 by @Tny 2008/09/18 --------
#if true
if(Ch_no <= WRITE_WELD_CH){ // 溶接条件の記録上限チャンネル番号？
#endif
//--------------------------------------------
     guc_Write_check_flag_ch[Ch_no]   = true; //2008.09.09

     guc_Write_check_flag[Ch_no]   = true; //2008.09.09

     guc_Material_condition_counterc[Ch_no]     = guc_Material_condition_counter;
     dummy_access = 1;
     guc_Material_condition_datac[Ch_no]        = gtt_Internal_pack.Data.In.fWireMaterial.ALL;      // ワイヤ材質
     dummy_access = 1;

     guc_Wire_condition_counterc[Ch_no]         = guc_Wire_condition_counter;
     dummy_access = 1;
     guc_Wire_condition_datac[Ch_no]            = gtt_Internal_pack.Data.In.fWireDiameter.ALL;      // ワイヤ径
     dummy_access = 1;

     guc_Method_condition_counterc[Ch_no]       = guc_Method_condition_counter;
     dummy_access = 1;
     //guc_Method_condition_datac[Ch_no]          = gtt_Internal_pack.Data.In.fWelding.ALL;           // 溶接法
     guc_Method_condition_datac[Ch_no]          = guc_Method_condition_data;           // 溶接法 2009.02.05
     dummy_access = 1;

     //2008.11.10
     guc_Ext_condition_counterc[Ch_no]          = guc_Ext_condition_counter;
     dummy_access = 1;
     guc_Ext_condition_datac[Ch_no]             = gtt_Internal_pack.Data.In.fWireSelect.ALL;         // 突き出し長
     dummy_access = 1;



     guc_Okcv_select_flag_ch[Ch_no]             = guc_Okcv_select_flag;
     dummy_access = 1;
     gs_Okcv_adjust_data_ch[Ch_no]              = gs_Okcv_adjust_data;       //一元電圧微調整分
     dummy_access = 1;
     gs_Okcv_adjust_init_data_ch[Ch_no]         = gs_Okcv_adjust_init_data;  //一元電圧微調整分
     dummy_access = 1;
     gs_Okcv_adjust_crat_data_ch[Ch_no]         = gs_Okcv_adjust_crat_data;  //一元電圧微調整分
     dummy_access = 1;
     gs_Okcv_adjust_wave_data_ch[Ch_no]         = gs_Okcv_adjust_wave_data;  //一元電圧微調整分
     dummy_access = 1;
     gs_Okcv_adjust_start_data_ch[Ch_no]        = gs_Okcv_adjust_start_data; //一元電圧微調整分の書き戻し
     dummy_access = 1;

     //本溶接
     gus_Weld_current_ch[Ch_no]            =  gtt_Internal_pack.Data.In.usWeldingCurr;
     dummy_access = 1;
     gus_Weld_voltage_ch[Ch_no]            =  gtt_Internal_pack.Data.In.usWeldingVolt;
     dummy_access = 1;
     //初期電流
     gus_Init_current_ch[Ch_no]            =  gtt_Internal_pack.Data.In.usWeldingInitCurr;
     dummy_access = 1;
     gus_Init_voltage_ch[Ch_no]            =  gtt_Internal_pack.Data.In.usWeldingInitVolt;
     dummy_access = 1;
     //クレータ
     gus_Crat_current_ch[Ch_no]            =  gtt_Internal_pack.Data.In.usWeldingCratCurr;
     dummy_access = 1;
     gus_Crat_voltage_ch[Ch_no]            =  gtt_Internal_pack.Data.In.usWeldingCratVolt;
     dummy_access = 1;

     //プリフロー時間 2009.01.28
     gus_Pre_flow_time_ch[Ch_no]           =  gtt_Internal_pack.Data.In.sPreFlowTime;
     dummy_access = 1;

     //アフターフロー時間 2009.01.28
     gus_After_flow_time_ch[Ch_no]         =  gtt_Internal_pack.Data.In.sAfterFlowTime;
     dummy_access = 1;

     //アップスロープ時間 2009.02.02
     gus_Up_slop_time_ch[Ch_no]            =  gtt_Internal_pack.Data.In.sUpSlopTime;
     dummy_access = 1;

     //ダウンスロープ時間 2009.02.02
     gus_Down_slop_time_ch[Ch_no]          =  gtt_Internal_pack.Data.In.sDownSlopTime;
     dummy_access = 1;

     //パルス電流 2009.02.03
     gus_Pulse_current_ch[Ch_no]           =  gtt_Internal_pack.Data.In.usIP;
     dummy_access = 1;

     //パルス周波数 2009.02.03
     gus_Pulse_freq_ch[Ch_no]              =  gtt_Internal_pack.Data.In.usPulseFreq;
     dummy_access = 1;

     //パルスデューティ 2009.02.03
     gus_Pulse_duty_ch[Ch_no]              =  gtt_Internal_pack.Data.In.usPulseDuty;
     dummy_access = 1;

     //交流周波数 2009.02.06
     gus_Ac_frequency_ch[Ch_no]            =  gtt_Internal_pack.Data.In.usAcFreq;
     dummy_access = 1;

     //クリーニング幅 2009.02.06
     gus_Cleaning_duty_ch[Ch_no]           =  gtt_Internal_pack.Data.In.ucCleaningDuty;
     dummy_access = 1;

     //直流比率 2009.02.06
     gus_Mix_ac_ratio_ch[Ch_no]            =  gtt_Internal_pack.Data.In.ucMixAcRatio;
     dummy_access = 1;

     //ＭＩＸ周波数 2009.02.06
     gus_Mix_frequency_ch[Ch_no]           =  gtt_Internal_pack.Data.In.ucMixFreq;
     dummy_access = 1;

     //アークスポット時間 2009.03.06
     gss_Arc_spot_time_ch[Ch_no]           =  gtt_Ditail_work.ss_Arc_spot_time; //2009.03.16 unsigned->signed
     dummy_access = 1;




     //***** 今の調整内容の記憶 2009.02.23*****
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
     gss_Arc_spot_time_m[guc_Method_condition_counter]   = gtt_Ditail_work.ss_Arc_spot_time; //2009.03.06 2009.03.16 unsigned->signed

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


     for (puc_Index = 0 ; puc_Index <= SELECT_DITAL_MAX ; puc_Index++)
     {
          gss_Select_dital_ch[puc_Index][Ch_no]  = gss_Select_dital[puc_Index];
          dummy_access = 1;
     }

     


//--------- Phase22 by @Tny 2008/10/09 --------
#if false
    { // 詳細メニューのパスワード項目以降は全チャンネル共通化
        unsigned short  i,j;
        for(i=0;i<CH;i++){
            for(j=P_INPUT_PASS_WORD;j<=SELECT_DITAL_MAX;j++){
                gss_Select_dital_ch[j][i]  = gss_Select_dital[j];
                dummy_access = 1;
            }
        }
    }
#endif
//-----------------------------------------
    { // 詳細メニューのパスワード項目の一部チャンネル共通化　P50～P54 2008.10.28
        unsigned short  i;
        for(i=0;i<CH;i++){
                gss_Select_dital_ch[P_INPUT_PASS_WORD][i]  = gss_Select_dital[P_INPUT_PASS_WORD]; //P50
                dummy_access = 1;
                gss_Select_dital_ch[P_CHENGE_PASS_WORD][i]  = gss_Select_dital[P_CHENGE_PASS_WORD]; //P51
                dummy_access = 1;
                gss_Select_dital_ch[P_CONTROLLER_LOCK][i]  = gss_Select_dital[P_CONTROLLER_LOCK]; //P52
                dummy_access = 1;
                gss_Select_dital_ch[P_SUB_MONITOR][i]  = gss_Select_dital[P_SUB_MONITOR]; //P53
                dummy_access = 1;
                gss_Select_dital_ch[P_ADJUST_ITEM][i]  = gss_Select_dital[P_ADJUST_ITEM]; //P54
                dummy_access = 1;
//-------------------------------------------------
// BP4 Phase7 by @Tny 2009-02-13
#if 0 //2009.03.31 del              
                gss_Select_dital_ch[P_VOLT_DISPLAY][i]			= gss_Select_dital[P_VOLT_DISPLAY]; 		//P02
                dummy_access = 1;
                gss_Select_dital_ch[P_CRATER_ENDING][i]			= gss_Select_dital[P_CRATER_ENDING];		//P03
                dummy_access = 1;
                gss_Select_dital_ch[P_DISPLAY_HOLD_TIME][i]		= gss_Select_dital[P_DISPLAY_HOLD_TIME];	//P05
                dummy_access = 1;
                gss_Select_dital_ch[P_AC_ARC_RECOVERY][i]		= gss_Select_dital[P_AC_ARC_RECOVERY];		//P06
                dummy_access = 1;
                gss_Select_dital_ch[P_DATE_TIME_DISPLAY][i]		= gss_Select_dital[P_DATE_TIME_DISPLAY];	//P08
                dummy_access = 1;
                gss_Select_dital_ch[P_DENBOU][i]				= gss_Select_dital[P_DENBOU];				//P10
                dummy_access = 1;
                gss_Select_dital_ch[P_ARC_DRIVE][i]				= gss_Select_dital[P_ARC_DRIVE];			//P11
                dummy_access = 1;
                //gss_Select_dital_ch[P_WELDING_GROUP][i]			= gss_Select_dital[P_WELDING_GROUP];		//P12
                gss_Select_dital_ch[P_EXTARNAL_LEVEL_A][i]			= gss_Select_dital[P_EXTARNAL_LEVEL_A];		//P12
                dummy_access = 1;
#endif

//-------------------------------------------------
                //<><><><><> 詳細パラメータの各ｃｈ共通化 2009.03.31 <><><><><>
                gss_Select_dital_ch[P_DC_TIG_START][i]			= gss_Select_dital[P_DC_TIG_START]; 		//P01
                dummy_access = 1;
                gss_Select_dital_ch[P_HOT_CURR_LEVEL][i]		= gss_Select_dital[P_HOT_CURR_LEVEL]; 		//P02
                dummy_access = 1;
                gss_Select_dital_ch[P_VOLT_DISPLAY][i]			= gss_Select_dital[P_VOLT_DISPLAY]; 		//P03
                dummy_access = 1;
                gss_Select_dital_ch[P_CRATER_ENDING][i]			= gss_Select_dital[P_CRATER_ENDING];		//P04
                dummy_access = 1;
                gss_Select_dital_ch[P_ELECTRODE_SHORT][i]		= gss_Select_dital[P_ELECTRODE_SHORT];		//P05
                dummy_access = 1;
                gss_Select_dital_ch[P_DISPLAY_HOLD_TIME][i]		= gss_Select_dital[P_DISPLAY_HOLD_TIME];	//P06
                dummy_access = 1;
                gss_Select_dital_ch[P_AC_ARC_RECOVERY][i]		= gss_Select_dital[P_AC_ARC_RECOVERY];		//P07
                dummy_access = 1;
                gss_Select_dital_ch[P_DATE_TIME_DISPLAY][i]		= gss_Select_dital[P_DATE_TIME_DISPLAY];	//P09
                dummy_access = 1;
                gss_Select_dital_ch[P_DENBOU][i]				= gss_Select_dital[P_DENBOU];				//P11
                dummy_access = 1;
                gss_Select_dital_ch[P_ARC_DRIVE][i]				= gss_Select_dital[P_ARC_DRIVE];			//P12
                dummy_access = 1;
                gss_Select_dital_ch[P_LCD_BRIGHT][i]			= gss_Select_dital[P_LCD_BRIGHT];			//P14
                dummy_access = 1;
                gss_Select_dital_ch[P_EXTARNAL_LEVEL_A][i]		= gss_Select_dital[P_EXTARNAL_LEVEL_A];		//P15
                dummy_access = 1;
                gss_Select_dital_ch[P_EXTARNAL_MASK_TIME][i]	= gss_Select_dital[P_EXTARNAL_MASK_TIME];	//P16 2010.01.08
                dummy_access = 1;
                gss_Select_dital_ch[P_REMOCON_SELECT][i]		= gss_Select_dital[P_REMOCON_SELECT];		//P17
                dummy_access = 1;
                gss_Select_dital_ch[P_VARIABLE_CRATER_REPEAT][i]= gss_Select_dital[P_VARIABLE_CRATER_REPEAT];//P18
                dummy_access = 1;
                gss_Select_dital_ch[P_MAX_OUTPUT][i]            = gss_Select_dital[P_MAX_OUTPUT];           //P19 2010.01.12
                dummy_access = 1;
                gss_Select_dital_ch[P_MILD_PULSE][i]            = gss_Select_dital[P_MILD_PULSE];           //P20 2010.03.05
                dummy_access = 1;
                gss_Select_dital_ch[P_AC_FRQ_DISP][i]           = gss_Select_dital[P_AC_FRQ_DISP];          //P21 2010.03.05
                dummy_access = 1;
                gss_Select_dital_ch[P_ARC_ASSIST][i]            = gss_Select_dital[P_ARC_ASSIST];           //P22 2010.03.05
                dummy_access = 1;
                gss_Select_dital_ch[P_SOFT_START_TIME][i]       = gss_Select_dital[P_SOFT_START_TIME];      //P23 2011.10.01
                dummy_access = 1;
                gss_Select_dital_ch[P_DETAIL_DISPLAY][i]       = gss_Select_dital[P_DETAIL_DISPLAY];        //P24 2011.10.03
                dummy_access = 1;

        }
    }


     guc_Pulse_mode_datac[Ch_no]           =  guc_Pulse_mode_data;
     dummy_access = 1;
     guc_Pulse_type_datac[Ch_no]           =  0x00; //2008.08.06時点　未使用
     dummy_access = 1;
     guc_Pulse_mode_counterc[Ch_no]        =  guc_Pulse_mode_counter;
     dummy_access = 1;


     guc_Crater_mode_counterc[Ch_no]       =  guc_Crater_mode_counter;
     dummy_access = 1;


     //ＡＣ波形 2009.03.13
     guc_Ac_wave_counterc[Ch_no]           = guc_Ac_wave_counter;
     dummy_access = 1;



//------ Phase21 by @Tny 2008/10/02 ------
#if true
    {
        unsigned char i;
        for(i=0;i<CH;i++){
            gtt_Special_menu_ch[i]  =  gtt_Special_menu;
            dummy_access = 1;
        }
    }
#endif
//-----------------------------------------

     for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
     {
          //guc_Out_port_ch[Ch_no][puc_Index] = guc_Out_port[0][puc_Index];
          guc_Out_port_ch[0][puc_Index] = guc_Out_port[0][puc_Index]; //2008.09.09
          dummy_access = 1;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
          guc_Out_port_ch[1][puc_Index] = guc_Out_port[1][puc_Index]; //2009.10.15 IIF NEW
          dummy_access = 1;
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
          //guc_In_port_ch[Ch_no][puc_Index]  = guc_In_port[0][puc_Index];
          guc_In_port_ch[0][puc_Index]  = guc_In_port[0][puc_Index]; //2008.09.09
          dummy_access = 1;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
          guc_In_port_ch[1][puc_Index]  = guc_In_port[1][puc_Index]; //2009.10.15 IIF NEW
          dummy_access = 1;
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
     }
     for (puc_Index = 1 ; puc_Index <= 3 ; puc_Index++)
     {
          //guc_Analog_port_ch[Ch_no][puc_Index]  = guc_Analog_port[0][puc_Index];
          guc_Analog_port_ch[0][puc_Index]  = guc_Analog_port[0][puc_Index]; //2008.09.09
          dummy_access = 1;
     }

     //gtt_Parameter_ch[Ch_no]               =  gtt_Parameter;

     guc_Pass_word_ch = guc_Pass_word; //2008.09.10
     guc_Controller_lock_ch = guc_Controller_lock; //2008.09.10
//--------- Phase13 by @Tny 2008/09/18 --------
#if true
}
#endif
//--------------------------------------------

//----- Phase8 by @Tny 2008/09/12 -----
#if true
    if(Ch_no == WRITE_ERROR_HISTORY_CH){ // CH=WRITE_ERROR_HISTORY_CHの時のみ保存   Phase13 by @Tny 2008/09/18
        // エラー履歴テーブルの転送
        unsigned short  i;
		unsigned char	*SrcTableAddres     = &gtt_Error_History.vStart;        // 転送する転送元テーブルの開始アドレス
		unsigned char	*SrcTableEndAddres  = &gtt_Error_History.vEnd;	        // 転送する転送元テーブルの終了アドレス
		unsigned char	*DestTableAddres    = &gtt_Backup_Error_History.vStart; // 転送する転送先テーブルの開始アドレス
		unsigned char	*DestTableEndAddres = &gtt_Backup_Error_History.vEnd;	// 転送する転送先テーブルの終了アドレス
		i = 0;
		do{
            dummy_access = 1;
			*(DestTableAddres+i) = *(SrcTableAddres+i); // 該当エリアの転送
			++i;					                    // 初期化する該当エリアのアドレス更新
		}while((SrcTableAddres+i) <= SrcTableEndAddres);	// 初期化するテーブルの範囲内？
    }
    if(Ch_no == WRITE_IIF_CH){ // CH=WRITE_IIF_CHの時のみ保存   Phase13 by @Tny 2008/09/18
        dummy_access = 1;
        gus_Backup_Iif_BuiltIn = gus_Iif_BuiltIn;   // IIF接続フラグ
    }
#endif
//--------------------------------------------
//--------- Phase21 by @Tny 2008/10/03 --------
#if true
    if((Ch_no / MEMORY_DELETE_CH) == 1){ // １００番台（100～199）のチャンネル指定なら、下位２桁のチャンネル番号の記憶データを削除
        unsigned char   Delete_Ch = (Ch_no % MEMORY_DELETE_CH);
        if(Delete_Ch > 0){  // チャンネル＃０は削除しない
            guc_Write_check_flag_ch[Delete_Ch]  = false;
            dummy_access = 1;
            guc_Write_check_flag[Delete_Ch]     = false;
        }
    }
#endif
//---------------------------------------------

//--------- BP4 Phase6 by @Tny 2009/01/27 ----
#if true
	if(Ch_no == gb_WeldCondNameWrite){ // 溶接条件名の記録
        // 溶接条件名テーブルの転送
        unsigned short  i;
		unsigned char	*SrcTableAddres     = &gt_WeldCondName[0][0];		// 転送する転送元テーブルの開始アドレス
		unsigned char	*DestTableAddres    = &gt_WeldCondName_ch[0][0];	// 転送する転送先テーブルの開始アドレス
		unsigned short	Length				= sizeof(gt_WeldCondName);		// 転送する転送元テーブルの大きさ（バイト長）
		for(i=0;i<Length;i++){
            dummy_access = 1;
			*(DestTableAddres+i) = *(SrcTableAddres+i); // 該当エリアの転送
		}
	}
#endif
//--------------------------------------------

//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
	if(Ch_no == WRIGHT_LCD_BRIGHT_CH){ // ＬＣＤコントラスト値の記録
		guc_Lcd_Bright_Back	= guc_Lcd_Bright;	// コントラストデータ
        dummy_access = 1;
	}
//-----------------------------------------------------------

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_memory_write_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

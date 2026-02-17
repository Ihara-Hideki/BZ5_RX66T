//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍｅｍｏｒｙ＿ｒｅａｄ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      メモリ上の指定されたｃｈデータを読み出し、ｃｈ０に反映する。
//      ｃｈ０はプライマリーｃｈでこのｃｈのデータが溶接機全ての動作に反映される。
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2006.08.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

void memory_read_member(unsigned char Ch_no)
{
     unsigned char puc_Index;
     unsigned char Cnt;
  //if (guc_Write_check_flag[Ch_no]  == true && Ch_no != 0) //2008.09.09
  if (guc_Write_check_flag_ch[Ch_no]  == true) //2008.09.09
  {

//----- Phase15 by @Tny 2008/09/19 -----
#if true
    if(guc_Sequence_mode == IDLING){
#endif
//--------------------------------------------
     guc_Material_condition_counter       =  guc_Material_condition_counterc[Ch_no];
     dummy_access = 1;
     guc_Material_condition_data          =  guc_Material_condition_datac[Ch_no];
     dummy_access = 1;

     guc_Wire_condition_counter           =  guc_Wire_condition_counterc[Ch_no];
     dummy_access = 1;
     guc_Wire_condition_data              =  guc_Wire_condition_datac[Ch_no];
     dummy_access = 1;

     guc_Method_condition_counter         =  guc_Method_condition_counterc[Ch_no];
     dummy_access = 1;
     guc_Method_condition_data            =  guc_Method_condition_datac[Ch_no];
     dummy_access = 1;

     //2008.11.10
     guc_Ext_condition_counter            =  guc_Ext_condition_counterc[Ch_no];
     dummy_access = 1;
     guc_Ext_condition_data               =  guc_Ext_condition_datac[Ch_no];
     dummy_access = 1;



     gtt_Internal_pack.Data.In.fWireDiameter.ALL          =  guc_Wire_condition_data;        // ワイヤ径
     dummy_access = 1;
     gtt_Internal_pack.Data.In.fWelding.ALL               =  guc_Method_condition_data;      // 溶接法
     dummy_access = 1;
     gtt_Internal_pack.Data.In.fWireMaterial.ALL          =  guc_Material_condition_data;    // ワイヤ材質
     dummy_access = 1;

     gtt_Internal_pack.Data.In.fWireSelect.ALL            =  guc_Ext_condition_data;   //突き出し長 2008.11.10


     guc_Okcv_select_flag             =  guc_Okcv_select_flag_ch[Ch_no];
     dummy_access = 1;
     if (guc_Okcv_select_flag == true)
     {
         guc_Okcv_select_counter = 0; //一元表示（±表示はしない）
     } else {
         guc_Okcv_select_counter = 2; //個別表示
     }

     gs_Okcv_adjust_data              =  gs_Okcv_adjust_data_ch[Ch_no];
     dummy_access = 1;
     gs_Okcv_adjust_init_data         =  gs_Okcv_adjust_init_data_ch[Ch_no];
     dummy_access = 1;
     gs_Okcv_adjust_crat_data         =  gs_Okcv_adjust_crat_data_ch[Ch_no];
     dummy_access = 1;
     gs_Okcv_adjust_wave_data         =  gs_Okcv_adjust_wave_data_ch[Ch_no];
     dummy_access = 1;
     gs_Okcv_adjust_start_data        =  gs_Okcv_adjust_start_data_ch[Ch_no];
     dummy_access = 1;
//----- Phase15 by @Tny 2008/09/19 -----
#if true
    }
#endif
//--------------------------------------------
//--------- Phase22 by @Tny 2008/10/07 --------
#if true
    else{ // 現在は待機中？
        guc_Welding_Play_Ch_no = Ch_no;     // 現在の再生チャンネルを記憶する
        gb_Welding_Play_Change  = true;     //
    }
#endif
//---------------------------------------------
     gus_Weld_current                 =  gus_Weld_current_ch[Ch_no];     //溶接電流指令値
     dummy_access = 1;
     gus_Weld_voltage                 =  gus_Weld_voltage_ch[Ch_no];     //溶接電圧指令値
     dummy_access = 1;
     gus_Init_current                 =  gus_Init_current_ch[Ch_no];     //初期電流指令値
     dummy_access = 1;
     gus_Init_voltage                 =  gus_Init_voltage_ch[Ch_no];     //初期電圧指令値
     dummy_access = 1;
     gus_Crat_current                 =  gus_Crat_current_ch[Ch_no];     //クレータ電流指令値
     dummy_access = 1;
     gus_Crat_voltage                 =  gus_Crat_voltage_ch[Ch_no];     //クレータ電圧指令値
     dummy_access = 1;


     gus_Pre_flow_time                = gus_Pre_flow_time_ch[Ch_no];     //プリフロー時間 2009.01.28
     dummy_access = 1;
     gus_After_flow_time              = gus_After_flow_time_ch[Ch_no];   //アフターフロー時間 2009.01.28
     dummy_access = 1;

     gus_Up_slop_time                 = gus_Up_slop_time_ch[Ch_no];      //アップスロープ時間 2009.02.02
     dummy_access = 1;
     gus_Down_slop_time               = gus_Down_slop_time_ch[Ch_no];    //ダウンスロープ時間 2009.02.02
     dummy_access = 1;

     //パルス電流 2009.02.03
     gus_Pulse_current                = gus_Pulse_current_ch[Ch_no];
     dummy_access = 1;

     //パルス周波数 2009.02.03
     gus_Pulse_freq                   = gus_Pulse_freq_ch[Ch_no];
     dummy_access = 1;

     //パルスデューティ 2009.02.03
     gus_Pulse_duty                   = gus_Pulse_duty_ch[Ch_no];
     dummy_access = 1;

     //交流周波数 2009.02.06
     gus_Ac_frequency                 = gus_Ac_frequency_ch[Ch_no];
     dummy_access = 1;

     //クリーニング幅 2009.02.06
     gus_Cleaning_duty                = gus_Cleaning_duty_ch[Ch_no];
     dummy_access = 1;

     //直流比率 2009.02.06
     gus_Mix_ac_ratio                 = gus_Mix_ac_ratio_ch[Ch_no];
     dummy_access = 1;

     //ＭＩＸ周波数 2009.02.06
     gus_Mix_frequency                = gus_Mix_frequency_ch[Ch_no];
     dummy_access = 1;

     //アークスポット時間 2009.03.06
     gss_Arc_spot_time                = gss_Arc_spot_time_ch[Ch_no]; //2009.03.09 unsigned->signed
     dummy_access = 1;
     




     //初期電流
     gtt_Internal_pack.Data.In.usWeldingInitCurr          =  gus_Init_current;
     dummy_access = 1;
     gtt_Internal_pack.Data.In.usWeldingInitVolt          =  gus_Init_voltage;
     dummy_access = 1;

     //本溶接
     gtt_Internal_pack.Data.In.usWeldingCurr              =  gus_Weld_current;
     dummy_access = 1;
     gtt_Internal_pack.Data.In.usWeldingVolt              =  gus_Weld_voltage;
     dummy_access = 1;

     //クレータ
     gtt_Internal_pack.Data.In.usWeldingCratCurr          =  gus_Crat_current;
     dummy_access = 1;
     gtt_Internal_pack.Data.In.usWeldingCratVolt          =  gus_Crat_voltage;
     dummy_access = 1;


     //プリフロー時間 2009.01.28
     gtt_Internal_pack.Data.In.sPreFlowTime               =  gus_Pre_flow_time;
     dummy_access = 1;
     gtt_Ditail_work.us_Pre_flow_time = gtt_Internal_pack.Data.In.sPreFlowTime; //2009.01.28
     dummy_access = 1;

     //アフターフロー時間 2009.01.28
     gtt_Internal_pack.Data.In.sAfterFlowTime             =  gus_After_flow_time;
     dummy_access = 1;
     gtt_Ditail_work.us_After_flow_time = gtt_Internal_pack.Data.In.sAfterFlowTime; //2009.01.28
     dummy_access = 1;

     //アップスロープ時間 2009.02.02
     gtt_Internal_pack.Data.In.sUpSlopTime                = gus_Up_slop_time;
     dummy_access = 1;

     //ダウンスロープ時間 2009.02.02
     gtt_Internal_pack.Data.In.sDownSlopTime              = gus_Down_slop_time;
     dummy_access = 1;

     //パルス電流 2009.02.03
     gtt_Internal_pack.Data.In.usIP                       = gus_Pulse_current;
     dummy_access = 1;

     //パルス周波数 2009.02.03
     gtt_Internal_pack.Data.In.usPulseFreq                = gus_Pulse_freq;
     dummy_access = 1;

     //パルスデューティ 2009.02.03
     gtt_Internal_pack.Data.In.usPulseDuty                = gus_Pulse_duty;
     dummy_access = 1;

     //交流周波数 2009.02.06
     gtt_Internal_pack.Data.In.usAcFreq                   = gus_Ac_frequency;
     dummy_access = 1;

     //クリーニング幅 2009.02.06
     gtt_Internal_pack.Data.In.ucCleaningDuty             = gus_Cleaning_duty;
     dummy_access = 1;

     //直流比率 2009.02.06
     gtt_Internal_pack.Data.In.ucMixAcRatio               = gus_Mix_ac_ratio;
     dummy_access = 1;

     //ＭＩＸ周波数 2009.02.06
     gtt_Internal_pack.Data.In.ucMixFreq                  = gus_Mix_frequency;
     dummy_access = 1;

     //アークスポット時間 2009.03.06
     gtt_Ditail_work.ss_Arc_spot_time                     = gss_Arc_spot_time; //2009.03.16 unsigned->signed
     dummy_access = 1;




     for (puc_Index = 0 ; puc_Index <= SELECT_DITAL_MAX ; puc_Index++)
     {
          gss_Select_dital[puc_Index] = gss_Select_dital_ch[puc_Index][Ch_no];
          dummy_access = 1;
     }

     //gtt_Internal_pack.Data.In.usWeldingWaveVolt          =  gss_Select_dital[P_LOW_PULSE_VOLT]; 2009.03.16 del
     gtt_Internal_pack.Data.In.usWeldingWaveVolt          =  184; //2009.03.16 
     //gtt_Internal_pack.Data.In.usWeldingStartVolt         =  gss_Select_dital[P_START_CTRL_VOLT]; 2009.03.16 del
     
     //***** 可変パラメータ反映 2009.02.23 *****
     //_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //ＡＣ周波数反映 2009.03.27
     _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //ＡＣ周波数の反映 2009.12.29
     _union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty; //2009.02.16
     //_union.Nrm.CalParm[66 - 1].c = gtt_Internal_pack.Data.In.ucMixFreq; //ＭＩＸ周波数反映 2009.03.27
     _union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10; //ＭＩＸ周波数反映 2009.03.31
     _union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio; //ＭＩＸ比率反映 2009.03.27
     //_union.Nrm.CalParm[69 - 1].c = gtt_Internal_pack.Data.In.usPulseFreq; //パルス周波数反映 2009.03.27
     _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10; //パルス周波数反映 2009.03.31
     _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty; //パルス幅反映 2009.03.27

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





     //gf_Frequence_adjust_data                             =  gss_Select_dital[0];
     dummy_access = 1;
     //gf_Base_adjust_data                                  =  gss_Select_dital[1];
     dummy_access = 1;

     guc_Pulse_mode_data                  =  guc_Pulse_mode_datac[Ch_no];
     dummy_access = 1;
     guc_Pulse_type_data                  =  guc_Pulse_type_datac[Ch_no];
     dummy_access = 1;
     guc_Pulse_mode_counter               =  guc_Pulse_mode_counterc[Ch_no];
     dummy_access = 1;

     guc_Crater_mode_counter              =  guc_Crater_mode_counterc[Ch_no];
     dummy_access = 1;

     //ＡＣ波形 2009.03.13
     guc_Ac_wave_counter                  =  guc_Ac_wave_counterc[Ch_no];
     dummy_access = 1;

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

                        //<><><> 出力電流実態制限 2010.01.12 <><><>
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
                        //<><><><><><><><><><><><><><><><><><><><><>



     if (guc_Pulse_mode_data == 0x03)
     {
         gtt_Internal_pack.Data.In.fPulseMode.ALL = 0x10;
     } else if (guc_Pulse_mode_data == 0x05) {
         gtt_Internal_pack.Data.In.fPulseMode.ALL = 0x00;
     }
     gtt_Internal_pack.Data.In.fPulseMode.ALL = gtt_Internal_pack.Data.In.fPulseMode.ALL | 0x03;//上記に伴い追加2008.03.27 2008.10.28追加


     //gtt_Parameter                         =  gtt_Parameter_ch[Ch_no];
         dummy_access = 1;

     gtt_Special_menu                      =  gtt_Special_menu_ch[Ch_no];
         dummy_access = 1;


     for (puc_Index = 1 ; puc_Index <= 10 ; puc_Index++)	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
     {
          //guc_Out_port[0][puc_Index] = guc_Out_port_ch[Ch_no][puc_Index];
          guc_Out_port[0][puc_Index] = guc_Out_port_ch[0][puc_Index]; //2008.09.09
          dummy_access = 1;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
          guc_Out_port[1][puc_Index] = guc_Out_port_ch[1][puc_Index]; //2009.10.15 IIF NEW
          dummy_access = 1;
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
          //guc_In_port[0][puc_Index]  = guc_In_port_ch[Ch_no][puc_Index];
          guc_In_port[0][puc_Index]  = guc_In_port_ch[0][puc_Index]; //2008.09.09
          dummy_access = 1;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
          guc_In_port[1][puc_Index]  = guc_In_port_ch[1][puc_Index]; //2008.10.15 IIF NEW
          dummy_access = 1;
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
     }
     for (puc_Index = 1 ; puc_Index <= 3 ; puc_Index++)
     {
          //guc_Analog_port[0][puc_Index]  = guc_Analog_port_ch[Ch_no][puc_Index];
          guc_Analog_port[0][puc_Index]  = guc_Analog_port_ch[0][puc_Index]; //2008.09.09
          dummy_access = 1;
     }

     guc_Pass_word = guc_Pass_word_ch; //2008.09.10
          dummy_access = 1;
     gss_Select_dital[P_CHENGE_PASS_WORD] = guc_Pass_word_ch; //2008.09.10
          dummy_access = 1;
     guc_Controller_lock = guc_Controller_lock_ch; //2008.09.10
          dummy_access = 1;
     gss_Select_dital[P_CONTROLLER_LOCK] = guc_Controller_lock_ch; //2008.09.10


     guc_Sw_rewrite_check_flag = 2; //2008.08.19表示更新のため追加

//----- Phase8 by @Tny 2008/09/12 -----
#if true
    {
        // エラー履歴テーブルの転送
        unsigned short  i;
		unsigned char	*SrcTableAddres     = &gtt_Backup_Error_History.vStart; // 転送する転送元テーブルの開始アドレス
		unsigned char	*SrcTableEndAddres	= &gtt_Backup_Error_History.vEnd;	// 転送する転送元テーブルの終了アドレス
		unsigned char	*DestTableAddres	= &gtt_Error_History.vStart;        // 転送する転送先テーブルの開始アドレス
		unsigned char	*DestTableEndAddres	= &gtt_Error_History.vEnd;	        // 転送する転送先テーブルの終了アドレス
		i = 0;
		do{
            dummy_access = 1;
			*(DestTableAddres+i) = *(SrcTableAddres+i); // 該当エリアの転送
			++i;					                    // 初期化する該当エリアのアドレス更新
		}while((SrcTableAddres+i) <= SrcTableEndAddres);	// 初期化するテーブルの範囲内？
    }
    {
        dummy_access = 1;
        gus_Iif_BuiltIn = gus_Backup_Iif_BuiltIn;   // IIF接続フラグ
    }
#endif
//--------------------------------------------

//--------- BP4 Phase6 by @Tny 2009/01/27 ----
#if true
    if(gb_WeldCondNameWrite == false){
        // 溶接条件名テーブルの転送
        unsigned short  i;
		unsigned char	*SrcTableAddres     = &gt_WeldCondName_ch[0][0];	// 転送する転送元テーブルの開始アドレス
		unsigned char	*DestTableAddres    = &gt_WeldCondName[0][0];		// 転送する転送先テーブルの開始アドレス
		unsigned short	Length				= sizeof(gt_WeldCondName_ch);	// 転送する転送元テーブルの大きさ（バイト長）
		for(i=0;i<Length;i++){
            dummy_access = 1;
			*(DestTableAddres+i) = *(SrcTableAddres+i); // 該当エリアの転送
		}
	}
#endif
//--------------------------------------------

//-----------------------------------------------------------
//BP4 Phase9 by @Tny 2009.02.16
	if(gb_LcdBrightWrite == false){
		guc_Lcd_Bright	= guc_Lcd_Bright_Back;	// コントラストデータ
        dummy_access 	= 1;
		gss_Select_dital[P_LCD_BRIGHT] = guc_Lcd_Bright;
	}
//-----------------------------------------------------------
  }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_memory_read_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

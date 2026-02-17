//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｔａｂｌｅ＿ａｃｃｅｓｓ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      データテーブルアクセス処理
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

void table_access_class(ubool xub_Initial_table_data , unsigned char xuc_Sequence_mode)
{

     //<><><><><><><><><><><><><>リモコンテーブルサーチ部<><><><><><><><><><><><><><><>





     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    
#if 0
     if (xuc_Sequence_mode == MAIN_WELD)
     {
         table_data_read_member(xub_Initial_table_data);
     }
#endif

     table_data_read_member(xub_Initial_table_data,xuc_Sequence_mode);
     

     //table_key_change_member();
     table_key_change_member(xuc_Sequence_mode); //2007.2.9
     // if (gtt_Table_key.Change_flag == ON || guc_Okcv_select_flag == true) //2007.12.06
     if (gtt_Table_key.Change_flag == ON)
     {
         hfix_data_transfer_member(false);
         okcv_generator_member(); //一元電圧算出
         gtt_Table_key.Change_flag = OFF;
        
         if (guc_Robot_connect_flag == true) //2009.07.17
         {
             gtt_Ctrl_flag.Rob_pram_refresh = ON;
         }
         

         { //テーブル変更時の詳細データの反映 2008.10.27
           unsigned char puc_Index;
           for (puc_Index = 0 ; puc_Index <= SELECT_DITAL_MAX ; puc_Index++)
           {
                //ditail_set_member(puc_Index); 2009.02.28
           }
         }
         
         //***** 可変パラメータ反映 2009.02.23 *****
           //_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //ＡＣパラメータ反映 2009.03.27
           _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //ＡＣ周波数の反映 2009.12.29
           _union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty; //2009.02.16
           //_union.Nrm.CalParm[66 - 1].c = gtt_Internal_pack.Data.In.ucMixFreq; //ＭＩＸ周波数反映 2009.03.27
           _union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10; //ＭＩＸ周波数反映 2009.03.31
           _union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio; //ＭＩＸ比率反映 2009.03.27
           //_union.Nrm.CalParm[69 - 1].c = gtt_Internal_pack.Data.In.usPulseFreq; //パルス周波数反映 2009.03.27
           _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10; //パルス周波数反映 2009.03.31
           _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty; //パルス幅反映 2009.03.27

           //***** パルスモードの切り替え処理 2009.02.27*****
#if 0 //2009.02.28
           if (guc_Pulse_mode_counter == 1 && gtt_Internal_pack.Data.In.usPulseFreq > 50)
           {
               _union.Nrm.CalParm[65 - 1].c = 1;
           } else {
                _union.Nrm.CalParm[65 - 1].c = 0;
           }
#endif
           //************************************************


         //***** リモコン接続時の処理（一元電圧を反映）2007.12.06 *****
//       if (ComuniPackRemo.Data.bRS422Connection)	// ＲＳ４２２回線接続
//       {
//              if (guc_Okcv_select_flag == true) //一元電圧選択
//               {
//                    gtt_Internal_pack.Data.In.usWeldingVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingCurr / 2] * 2));// + gtt_Okcv.Okcv_ref);
//                     //gs_Okcv_adjust_data = gs_Okcv_adjust_data + (signed short)((signed char)ComuniPackRemo.Data.To.Jog.uc_Jog2);
//		             gtt_Internal_pack.Data.In.usWeldingVolt = gtt_Internal_pack.Data.In.usWeldingVolt + gs_Okcv_adjust_data; // 出力電圧指令値
//                } else {
//                     if (gtt_Internal_pack.Data.In.usWeldingVolt < 0)
//                     {
//                         gtt_Internal_pack.Data.In.usWeldingVolt = gtt_Internal_pack.Data.In.usWeldingVolt * -1;
//                     }
//                }
//         }
         //************************************************************
     }
         //***** リモコン接続時の処理（一元電圧を反映）2007.12.06 ***** 2008.02.18場所変更

         // コントローラ接続orコントローラ未接続短絡子有りで、ロボット接続無し Phase26 by @Tny 2008.10.23
         if(((ComuniPackRemo.Data.bRS422Connection) || (gb_Controller_UnConnect)) && (guc_Robot_connect_flag == false))
         {
                //{
                //   extern int DC_PMODE;
                //   PENTBL      pENTBL; //2008.09.19
                //   switch( DC_PMODE )
                //   {
                //        case 2://短絡
                //             pENTBL = pWT->pENTBL_Short;
                //             break;
                //        case 1://パルス
                //        default:
                //             pENTBL = pWT->pENTBL_Pulse;
                //             break;
                //        }
                //   guc_En_table_access_test = pENTBL->dummy1;//2008.11.19ＥＮテーブルアクセステスト用
                //}

                if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85) //2008.10.01
                {
                        en_generator_member(gtt_Internal_pack.Data.In.usWeldingInitCurr,EN_INIT);
                        en_generator_member(gtt_Internal_pack.Data.In.usWeldingCurr,EN_MAIN);
                        en_generator_member(gtt_Internal_pack.Data.In.usWeldingCratCurr,EN_CRATER);
                } else { //2008.12.23
                        gf_Frq_data = 1; //2008.12.23
                }
                if (guc_Okcv_select_flag == true) //一元電圧選択
                {

#if 0 //2008.11.11削除
                    if (guc_Pulse_mode_data == 0x03 || guc_Pulse_mode_data == 0x05) //直流モード時は０クリアする 2008.09.29
                    {
                        gtt_En.f_AC_Frq_ENa1_A = 0;
                        gtt_En.f_AC_Frq_ENa1_B = 0;
                        gtt_En.f_AC_Frq_ENa1_C = 0;
                        gtt_En.f_AC_Frq_ENa2_A = 0;
                        gtt_En.f_AC_Frq_ENa2_B = 0;
                        gtt_En.f_AC_Frq_ENa2_C = 0;
                    }
#endif
                    //初期 2008.02.26
	    	        gtt_Internal_pack.Data.In.usWeldingInitVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingInitCurr / 2] * 2));// + gtt_Okcv.Okcv_ref);
				    gtt_Internal_pack.Data.In.usWeldingInitVolt = gtt_Internal_pack.Data.In.usWeldingInitVolt + gs_Okcv_adjust_init_data; // 出力電圧指令値
                    //ＥＮ時の一元電圧算出
                    if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85)
                    {
                        //en_generator_member(gtt_Internal_pack.Data.In.usWeldingInitCurr,EN_INIT);
                        gtt_Internal_pack.Data.In.usWeldingInitVolt = gtt_Internal_pack.Data.In.usWeldingInitVolt + (sint)gtt_En.sc_Va_init;
                    }
                    //本溶接
	    	        gtt_Internal_pack.Data.In.usWeldingVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingCurr / 2] * 2));// + gtt_Okcv.Okcv_ref);
				    gtt_Internal_pack.Data.In.usWeldingVolt = gtt_Internal_pack.Data.In.usWeldingVolt + gs_Okcv_adjust_data; // 出力電圧指令値
                    //ＥＮ時の一元電圧算出
                    if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85)
                    {
                        //en_generator_member(gtt_Internal_pack.Data.In.usWeldingCurr,EN_MAIN);
                        gtt_Internal_pack.Data.In.usWeldingVolt = gtt_Internal_pack.Data.In.usWeldingVolt + (sint)gtt_En.sc_Va_main;
                    }
                    //クレータ 2008.02.26
#if 0 //2009.03.16 del
                        if (gtt_Ctrl_flag.Crater_pulse_non == ON && gss_Select_dital[P_CRATER_DC] == ON && guc_Pulse_mode_data == 0x05) //2008.11.06
                        {
	    	            gtt_Internal_pack.Data.In.usWeldingCratVolt = (sint)((gtt_Okcv.Okcv_crater_short[gtt_Internal_pack.Data.In.usWeldingCratCurr / 2] * 2));// + gtt_Okcv.Okcv_ref);
                        } else {
	    	            gtt_Internal_pack.Data.In.usWeldingCratVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingCratCurr / 2] * 2));// + gtt_Okcv.Okcv_ref);
                        }
			gtt_Internal_pack.Data.In.usWeldingCratVolt = gtt_Internal_pack.Data.In.usWeldingCratVolt + gs_Okcv_adjust_crat_data; // 出力電圧指令値
#endif
                    //ＥＮ時の一元電圧算出
                    if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85)
                    {
                        //en_generator_member(gtt_Internal_pack.Data.In.usWeldingCratCurr,EN_CRATER);
                        gtt_Internal_pack.Data.In.usWeldingCratVolt = gtt_Internal_pack.Data.In.usWeldingCratVolt + (sint)gtt_En.sc_Va_crater;
                    }
                    //波形制御　Ｂ条件 2008.02.26
#if 0
	    	        gtt_Internal_pack.Data.In.usWeldingWaveVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingWaveCurr / 2] * 2));// + gtt_Okcv.Okcv_ref);
				    gtt_Internal_pack.Data.In.usWeldingWaveVolt = gtt_Internal_pack.Data.In.usWeldingWaveVolt + gs_Okcv_adjust_wave_data; // 出力電圧指令値
                    if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85)
                    {
                        //en_generator_member(gtt_Internal_pack.Data.In.usWeldingWaveCurr,EN_MAIN);
                        gtt_Internal_pack.Data.In.usWeldingWaveVolt = gtt_Internal_pack.Data.In.usWeldingWaveVolt + (sint)gtt_En.sc_Va_main;
                    }
#endif
                    //波形制御　スタート条件 2008.08.05
#if 0
	    	        gtt_Internal_pack.Data.In.usWeldingStartVolt = (sint)((gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingStartCurr / 2] * 2));// + gtt_Okcv.Okcv_ref);
				    gtt_Internal_pack.Data.In.usWeldingStartVolt = gtt_Internal_pack.Data.In.usWeldingStartVolt + gs_Okcv_adjust_start_data; // 出力電圧指令値
#endif
#if 0
                    if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85)
                    {
                        //en_generator_member(gtt_Internal_pack.Data.In.usWeldingStartCurr,EN_MAIN);
                        gtt_Internal_pack.Data.In.usWeldingStartVolt = gtt_Internal_pack.Data.In.usWeldingStartVolt + (sint)gtt_En.sc_Va_main;
                    }
#endif
                } else {
                     if (gtt_Internal_pack.Data.In.usWeldingInitVolt < 0) //2008.02.26
                     {
                         //初期
                         gtt_Internal_pack.Data.In.usWeldingInitVolt = gtt_Internal_pack.Data.In.usWeldingInitVolt * -1;
                     }
                     if (gtt_Internal_pack.Data.In.usWeldingVolt < 0)
                     {
                         //本溶接
                         gtt_Internal_pack.Data.In.usWeldingVolt = gtt_Internal_pack.Data.In.usWeldingVolt * -1;
                     }
                     if (gtt_Internal_pack.Data.In.usWeldingCratVolt < 0) //2008.02.26
                     {
                         //クレータ
                         gtt_Internal_pack.Data.In.usWeldingCratVolt = gtt_Internal_pack.Data.In.usWeldingCratVolt * -1;
                     }

                     //if (gtt_Internal_pack.Data.In.usWeldingWaveVolt < 0) //2008.02.26
                     //{
                         //波形制御　Ｂ条件
                     //    gtt_Internal_pack.Data.In.usWeldingWaveVolt = gtt_Internal_pack.Data.In.usWeldingWaveVolt * -1;
                     //}
                     //if (gtt_Internal_pack.Data.In.usWeldingStartVolt < 0) //2008.08.05
                     //{
                         //波形制御　スタート条件
                     //    gtt_Internal_pack.Data.In.usWeldingStartVolt = gtt_Internal_pack.Data.In.usWeldingStartVolt * -1;
                     //}
                }
         } else { //ロボット接続時 2008.10.03
                if ((guc_Pulse_mode_data & 0x80) == 0x80) //ロボット接続時、ＡＣモード時のみＥＮ比率計算
                {
                     en_generator_member(gtt_Internal_pack.Data.In.usWeldingCurr,EN_MAIN);
                     //gtt_Internal_pack.Data.Out.uc_En_a    = (unsigned char)gtt_En.ss_En_a_main;  2008.11.28 del
                     //gtt_Internal_pack.Data.Out.us_En_Okcv = (gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.usWeldingCurr / 2] * 2) + gtt_En.sc_Va_main; 2008.11.28 del
                     if (gtt_En.uc_En_inquiry == 2)//2008.11.28 ロボットから一元問い合わせがあった場合の処理
                     {
                         en_generator_member(gtt_Internal_pack.Data.In.us_Q_WeldingCurr,EN_Q);
                         gtt_Internal_pack.Data.Out.uc_En_a    = (unsigned char)gtt_En.ss_En_a_qes;
                         gtt_Internal_pack.Data.Out.us_En_Okcv = (gtt_Okcv.Okcv_real[gtt_Internal_pack.Data.In.us_Q_WeldingCurr / 2] * 2) + (sint)gtt_En.sc_Va_qes;
                         gtt_En.uc_En_inquiry  = 3;
                     }
                } else { //2008.12.23
                  gf_Frq_data = 1; //2008.12.23
                }
         }
         //************************************************************


     if(gtt_Okcv.New_calc == ON && (gtt_Okcv.Request1 == ON || gtt_Okcv.Request2 == ON))
     {
        if (gtt_Okcv.Request1 == ON)
        {
            gtt_Okcv.Send1 = ON;
            gtt_Okcv.Request1 = OFF;
        }
        if (gtt_Okcv.Request2 == ON)
        {
            gtt_Okcv.Send2 = ON;
            gtt_Okcv.Request2 = OFF;
        }
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_table_access_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

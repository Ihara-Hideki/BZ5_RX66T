//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//丂亂娭悢柤亃
//丂丂丂倲倎倐倢倕丵倓倎倲倎丵倰倕倎倓丵倣倕倣倐倕倰
//丂亂娭悢儗儀儖亃
//丂丂丂俴俤倁俤俴丗俁
//  亂婡擻愢柧亃
//      僥乕僽儖僨乕僞撉傒崬傒 亄丂俢俽俹偵僨乕僞揮憲
//  亂堷悢亃
//      側偟
//  亂栠傝抣亃
//      側偟
//  亂旛峫亃
//      側偟
//  亂峏怴棜楌亃
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

//extern void		_hpiSetAddress(long dspPtr);
//extern void		_hpiPut(usint Data);
//extern usint		_hpiGet( void );

//extern void xmemset(void *dst, int dat, size_t lgh);
//extern void xmemcpy(void *dst, const void *soc, size_t lgh);


WELDNAME	WeldName;
extern WELDCODE DC_WELDCODE;
extern int DC_PMODE;
extern  int         _ACC; //2008.11.17

void table_data_read_member(ubool xub_Initial_table_data , unsigned char xuc_Sequence_mode)
{


	MtoC[AC_FRQ_DATA]	= gtt_Internal_pack.Data.In.usAcFreq;			// 岎棳廃攇悢(2019.06.17)
	MtoC[EP_RATIO]		= gtt_Internal_pack.Data.In.ucCleaningDuty;		// 僋儕乕僯儞僌暆丗EP斾棪(2019.06.17)

    MtoC[DC_AC_CTRL]	= guc_Method_condition_counter;					// 捈棳乛岎棳愗傝懼偊乮MIX側偳偼枹懳墳乯	2019.06.17


     if (xub_Initial_table_data == true)
     {
	 // 僟儈乕嵽幙僨乕僞
         WeldName.Kind = 0; // 庬暿(d0:嵽幙丄d1:梟愙朄)
         WeldName.Code = 0; // 僐乕僪
         xmemset(WeldName.Name, 0, WELDNAMELEN);
	 // 僟儈乕巜椷僨乕僞
         {
            PWELDTABLE  pWT = getWeldTablePtr();
            PA2STBL     pTBL;
            pTBL            = &pWT->A2S_Short;
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x01;
            DC_WELDCODE.pulseMode = 0x03;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05;
            DC_WELDCODE.extension = 0x03;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
            


            DataUpdate( );
            
            //SRVCTL          = 0; 2019.04.02 del ihara
            SetWeldStatus( 2 );                               //杮梟愙拞傊
            ctlclsDrctSet();
            //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt);   // 揹棳丗侾侽侽俙乛揹埑丗俀侽倁
            ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt);   //2010.02.19
            GetAmp2Wire( gtt_Internal_pack.Data.In.usWeldingCurr , pTBL );                // 揹棳丗侾侽侽俙
            wcndSend();                                       //梟愙忦審俢俽俹傊揮憲
            sspdSend();
         }

         //僎僀儞揮憲
         //_hpiSetAddress( 0x00000229 );
         //_hpiPut((ushort)(0x043F));//20060213
     } else {
            //if (xuc_Sequence_mode == SLOW_DOWN || xuc_Sequence_mode == START_WELD || xuc_Sequence_mode == INITIAL_WELD || xuc_Sequence_mode == MAIN_WELD || xuc_Sequence_mode == CRATER_WELD || xuc_Sequence_mode == BURN_BACK)
            //if (xuc_Sequence_mode == HF_CTRL || xuc_Sequence_mode == START_WELD || xuc_Sequence_mode == INITIAL_WELD || xuc_Sequence_mode == MAIN_WELD || xuc_Sequence_mode == CRATER_WELD || xuc_Sequence_mode == BURN_BACK) //2009.01.31
            //if (xuc_Sequence_mode == HF_CTRL || xuc_Sequence_mode == UP_SLOPE || xuc_Sequence_mode == START_WELD || xuc_Sequence_mode == INITIAL_WELD || xuc_Sequence_mode == MAIN_WELD || xuc_Sequence_mode == CRATER_WELD || xuc_Sequence_mode == BURN_BACK) //2009.02.02
            //if (xuc_Sequence_mode == HF_CTRL || xuc_Sequence_mode == UP_SLOPE || xuc_Sequence_mode == DOWN_SLOPE || xuc_Sequence_mode == START_WELD || xuc_Sequence_mode == INITIAL_WELD || xuc_Sequence_mode == MAIN_WELD || xuc_Sequence_mode == CRATER_WELD || xuc_Sequence_mode == BURN_BACK) //2009.02.02
            if (xuc_Sequence_mode == HF_CTRL || xuc_Sequence_mode == UP_SLOPE || xuc_Sequence_mode == DOWN_SLOPE || xuc_Sequence_mode == START_WELD || xuc_Sequence_mode == INITIAL_WELD || xuc_Sequence_mode == MAIN_WELD || xuc_Sequence_mode == CRATER_WELD || xuc_Sequence_mode == BURN_BACK || xuc_Sequence_mode == HAND_STICK) //2009.03.06
            {
                 if (gtt_Ctrl_flag.Table_data_output_execution == ON) //2007.1.12
                 {
                     PWELDTABLE  pWT = GetWeldTable( );  //test 暅婣丂2006.10.25
                     PA2STBL     pTBL;


                     if (xuc_Sequence_mode == CRATER_WELD) //2008.11.06
                     {
#if 0 //2009.03.16 del
                         if (gtt_Ctrl_flag.Crater_pulse_non == ON && gss_Select_dital[P_CRATER_DC] == ON && guc_Pulse_mode_data == 0x05) //2008.11.06
                         {
                             DC_PMODE = 2;
                         }
#endif
                     }

                     switch( DC_PMODE )
                     {
                         case 2://抁棈
                              pTBL = &pWT->A2S_Short;
                              break;
                         case 1://僷儖僗
                         default:
                              pTBL = &pWT->A2S_Pulse;
                         break;
                     }
                     //SRVCTL          = 0; 2019.04.02 del ihara

                     //***** 弌椡曗惓偺斀塮張棟 2009.03.16 *****
                     if (gtt_Special_menu.ss_Service_data[S_CURRENT_ADJUST] == true)
                     {
                         gtt_Ctrl_flag.Disp_adjust = ON;
                         if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || (gss_Select_dital[P_VARIABLE_CRATER_REPEAT] == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT))
                         {
                             gtt_Ctrl_flag.Disp_adjust = OFF;
                         }
                     } else {
                         gtt_Ctrl_flag.Disp_adjust = OFF;
                     }
                     switch (xuc_Sequence_mode)
                     {
                         //case SLOW_DOWN:
                         case HF_CTRL: //2009.01.31
				 MtoC[PRE_CURR_DATA] = gf_Hot_current_level; //2019.06.03
			

#if 0 //2019.06.03
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        //2010.03.08_union.Nrm.CalParm[71 - 1].max = gtt_Internal_pack.Data.In.usIP; //僷儖僗僺乕僋揹棳 2009.04.06
                                        _union.Nrm.CalParm[71 - 1].max = current_table_data_member(gtt_Internal_pack.Data.In.usIP); //僷儖僗僺乕僋揹棳 2010.03.08
                                        //2010.03.08_union.Nrm.CalParm[71 - 1].min = gtt_Internal_pack.Data.In.usIP; //2009.04.06
                                        _union.Nrm.CalParm[71 - 1].min = current_table_data_member(gtt_Internal_pack.Data.In.usIP); //2010.03.08
                                        //if (gtt_Internal_pack.Data.In.ucMixFreq <= 100) //2009.04.11
                                        if (gtt_Internal_pack.Data.In.ucMixFreq <= 40) //2009.07.24 4Hz
                                        {
                                            _union.Nrm.CalParm[65 - 1].c = 1;
                                        } else {
                                            _union.Nrm.CalParm[65 - 1].c = 2;
                                        }
//2009.04.14                                        if (guc_Crater_mode_counter == SEQUENCE_NON) //2009.04.14
//2009.04.14                                        {
//2009.04.14                                            if (gtt_Internal_pack.Data.In.usPulseFreq <= 50) //2009.04.11
//2009.04.14                                            {
//2009.04.14                                                _union.Nrm.CalParm[68 - 1].c = 0;
//2009.04.14                                            } else {
//2009.04.14                                                _union.Nrm.CalParm[68 - 1].c = 1;
//2009.04.14                                            }
//2009.04.14                                        } else {
	                                if (guc_Crater_mode_counter == SEQUENCE_NON || guc_Crater_mode_counter == SEQUENCE_ARC_SPOT) //2009.08.27
	                                {
                                            if (guc_Pulse_mode_data == 0x00) //2009.07.27
                                            {
					        _union.Nrm.CalParm[68 - 1].c = 0;
                                            } else {
                                             //if (gtt_Internal_pack.Data.In.usPulseFreq <= 40) //2009.07.24
                                               if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
                                               {
					            _union.Nrm.CalParm[68 - 1].c = 0;
                                               } else {
					            _union.Nrm.CalParm[68 - 1].c = 1;
                                               }
                                            }
                                         } else if (guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT || guc_Crater_mode_counter == SEQUENCE_CRATER) { //2009.08.27
						_union.Nrm.CalParm[68 - 1].c = 0; //2009.08.27
                                         }
//2009.04.14									    }

                                        _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2010.01.18

                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲 2006.12.20捛壛
                                        sspdSend();
                                        PLS_OUT = OFF; //2009.03.17
#endif
                                        break;
                         case BURN_BACK:
#if 0 //2019.06.03
                                        PLS_OUT = OFF; //2009.03.17
                                        //***** 僶乕儞僶僢僋帪DSP偵揮憲偡傞抣傪妋掕偡傞偨傔捛壛 2008.12.18 *****
#if 0 //2009.02.28
                                        if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85)
                                        { 
                                            if (gtt_Ctrl_flag.Burnback_ac == false) //2008.12.11丂俫俁俇俇偑侽偱偁傟偽捈棳廔椆
                                            {
						gtt_En.ss_En_a_output = 0;
				            } else {
                                                gtt_En.ss_En_a_output = gtt_En.ss_En_a_main; //2008.10.01
                                            }
                                            v_generator_member(gtt_Internal_pack.Data.In.usWeldingCurr , gtt_En.ss_En_a_output , gtt_En.ss_En_def_main ,gtt_Ditail_work.ss_En_duty_main_adjustment);//2008.11.28
                                        } else {
					    gtt_En.ss_En_a_output = 0;
					}
#endif
					//***********************************************************************
					
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲 2006.12.20捛壛
                                        sspdSend();
#endif                                        
                                        break;
                         case START_WELD:
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingStartCurr , gtt_Internal_pack.Data.In.usWeldingStartVolt);   //
                                        ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingStartCurr) , gtt_Internal_pack.Data.In.usWeldingStartVolt);  //2010.02.19
                                        sspdSend();
                                        IMJTOCR4  = 0x05; //2006.2.9 妱嫋
                              break;
                         case INITIAL_WELD:
#if 0
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        PLS_OUT = OFF; //2009.03.17
                                        
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 1;
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        _union.Nrm.CalParm[68 - 1].c = 0; //2009.04.03
                                        gtt_Ctrl_flag.Hpi_control = true; //2009.08.27
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.02.10僄僉僗僷乕僩影霓帋尡梡
                                        {
                                                //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingInitCurr , gtt_Internal_pack.Data.In.usWeldingInitVolt);
                                                ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingInitCurr) , gtt_Internal_pack.Data.In.usWeldingInitVolt); //2010.02.19
                                         } else {
                                               //***** 弌椡曗惓 2009.02.16*****
                                             if (gtt_Ctrl_flag.Disp_adjust == ON) //2009.03.16
                                             {
                                               {
                                                 short pss_Output_current;
                                                 unsigned char puc_Correct_flag;
                                                 short pss_Output_difference_work;
                                                 gss_Output_difference = gtt_Internal_pack.Data.In.usWeldingInitCurr - gss_Current_work;
                                                 if (gss_Output_difference < 0)
                                                 {
                                                     pss_Output_difference_work = gss_Output_difference * -1;
                                                 } else {
                                                     pss_Output_difference_work = gss_Output_difference;
                                                 }
                                                 if (pss_Output_difference_work < 10)
                                                 {
                                                     puc_Correct_flag = ON;
                                                 } else {
                                                     puc_Correct_flag = OFF;
                                                     gf_Output_correct_value = 0;
                                                 }
                                                 if (gss_Output_difference == 0)
                                                 {
                                                     puc_Correct_flag = OFF;
                                                 }
                                                 if (gtt_Ctrl_flag.Output_correct == ON && puc_Correct_flag == ON)
                                                 {
                                                     gtt_Ctrl_flag.Output_correct = OFF;
                                                     gf_Output_correct_value = gf_Output_correct_value + (float)gss_Output_difference / 8;
                                                 }
                                                 pss_Output_current = gtt_Internal_pack.Data.In.usWeldingInitCurr + (short)gf_Output_correct_value;
                                                 //ctlclsWeldCondSet( pss_Output_current , gtt_Internal_pack.Data.In.usWeldingInitVolt); //俙忦審
                                                 ctlclsWeldCondSet( current_table_data_member(pss_Output_current) , gtt_Internal_pack.Data.In.usWeldingInitVolt); //俙忦審 2010.02.19
                                                }
                                              } else {
                                                //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingInitCurr , gtt_Internal_pack.Data.In.usWeldingInitVolt); //俙忦審
                                                ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingInitCurr) , gtt_Internal_pack.Data.In.usWeldingInitVolt); //俙忦審 2010.02.19
                                              }
                                         }
                                         sspdSend();
                                         IMJTOCR4  = 0x05; //2006.2.9 妱嫋
#else
                                        if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.02.10僄僉僗僷乕僩影霓帋尡梡
                                        {
                                                ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingInitCurr) , gtt_Internal_pack.Data.In.usWeldingInitVolt); //2010.02.19
                                         } else {
                                               //***** 弌椡曗惓 2009.02.16*****
                                             if (gtt_Ctrl_flag.Disp_adjust == ON) //2009.03.16
                                             {
                                               {
                                                 short pss_Output_current;
                                                 unsigned char puc_Correct_flag;
                                                 short pss_Output_difference_work;
                                                 gss_Output_difference = gtt_Internal_pack.Data.In.usWeldingInitCurr - gss_Current_work;
                                                 if (gss_Output_difference < 0)
                                                 {
                                                     pss_Output_difference_work = gss_Output_difference * -1;
                                                 } else {
                                                     pss_Output_difference_work = gss_Output_difference;
                                                 }
                                                 if (pss_Output_difference_work < 10)
                                                 {
                                                     puc_Correct_flag = ON;
                                                 } else {
                                                     puc_Correct_flag = OFF;
                                                     gf_Output_correct_value = 0;
                                                 }
                                                 if (gss_Output_difference == 0)
                                                 {
                                                     puc_Correct_flag = OFF;
                                                 }
                                                 if (gtt_Ctrl_flag.Output_correct == ON && puc_Correct_flag == ON)
                                                 {
                                                     gtt_Ctrl_flag.Output_correct = OFF;
                                                     gf_Output_correct_value = gf_Output_correct_value + (float)gss_Output_difference / 8;
                                                 }
                                                 //pss_Output_current = gtt_Internal_pack.Data.In.usWeldingInitCurr + (short)gf_Output_correct_value;
                                                 //ctlclsWeldCondSet( current_table_data_member(pss_Output_current) , gtt_Internal_pack.Data.In.usWeldingInitVolt); //俙忦審 2010.02.19

						 MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingInitCurr; //2019.06.03
                                                }
                                              } else {
                                                //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingInitCurr) , gtt_Internal_pack.Data.In.usWeldingInitVolt); //俙忦審 2010.02.19
						 MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingInitCurr; //2019.06.03
                                              }
                                         }
#endif
                              break;
                         case UP_SLOPE:

#if 0 //2019.06.03
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 1;
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        if (guc_Pulse_mode_data == 0)                                        
                                        {
                                            if (gtt_Ctrl_flag.Up_slop_curr_end == OFF)
                                            {
                                                gf_Up_slop_base_curr = gf_Up_slop_base_curr + gf_Up_slop_base_step;
                                            }
                                            //ctlclsWeldCondSet((short)gf_Up_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingVolt);   // 揹棳乛揹埑 2006.12.11 test捛壛
                                            ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt);   //2010.02.19
                                        } else {
                                            if (gtt_Ctrl_flag.Up_slop_curr_end == OFF)
                                            {
                                                gf_Up_slop_base_curr  = gf_Up_slop_base_curr  + gf_Up_slop_base_step;
                                                gf_Up_slop_pulse_curr = gf_Up_slop_pulse_curr + gf_Up_slop_pulse_step;
                                            }
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 50) //2009.02.27
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 40) //2009.07.24
                                            if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
                                            {
                                                _union.Nrm.CalParm[68 - 1].c = 0; //2009.02.27 2009.03.27 65->68
                                                gtt_Ctrl_flag.Hpi_control = true; //2009.02.28
	                                        if (gtt_Ctrl_flag.Wave_current_time == OFF)
    	                                        {
                                                    gtt_Ctrl_flag.Wave_current_time = ON;
            	                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                    //_union.Nrm.CalParm[18 - 1].max = 400;//僷儖僗僺乕僋揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[18 - 1].min = 1;  //僷儖僗僺乕僋揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[20 - 1].max = 400;//僷儖僗儀乕僗揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[20 - 1].min = 1;  //僷儖僗儀乕僗揹棳 2009.03.27 del
                                                } else { 
                                                    if (gtt_Ctrl_flag.Condition_change == OFF)
                                                    {
                                                        //ctlclsWeldCondSet((short)gf_Up_slop_pulse_curr , gtt_Internal_pack.Data.In.usWeldingVolt); //俛忦審
                                                        ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_pulse_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俛忦審 2010.02.19
                                                        //PLS_OUT = ON; //2009.03.17
                                                        gtt_Ctrl_flag.Dsp_pulse_out = ON; //2009.04.11
                                                    } else {
                                                        //ctlclsWeldCondSet((short)gf_Up_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                        ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                                        //PLS_OUT = OFF; //2009.03.17
                                                        gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                                                    }
                                                    if (gtt_Ctrl_flag.Condition_time_set == OFF)
                                                    {
                                                        gtt_Ctrl_counter.Frequence_time = gtt_Ctrl_counter.Frequence_set_time;
                                                        gtt_Ctrl_counter.B_condition_time = gtt_Ctrl_counter.B_condition_set_time;

                                                        //gtt_Ctrl_counter.Frequence_time   = (unsigned long)((float)gtt_Ctrl_counter.Frequence_set_time * 0.94); //2009.07.24 抶傟偺曗惓
                                                        //gtt_Ctrl_counter.B_condition_time = (unsigned long)((float)gtt_Ctrl_counter.B_condition_time * 0.92);   //2009.07.24 抶傟偺曗惓

                                                        gtt_Ctrl_flag.Condition_time_set = ON;
                                                    } else {
                                                        if (gtt_Ctrl_counter.B_condition_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = ON;
                                                        }
                                                        if (gtt_Ctrl_counter.Frequence_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = OFF;
                                                            gtt_Ctrl_flag.Condition_time_set = OFF;
                                                        }
                                                    }
                                                }
                                            } else { //2009.02.27
                                                    //ctlclsWeldCondSet((short)gf_Up_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                    ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                                    _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;   //僷儖僗廃攇悢 2009.03.27 13->69
                                                    //2010.03.08 _union.Nrm.CalParm[71 - 1].max = (short)gf_Up_slop_pulse_curr;         //僷儖僗僺乕僋揹棳 2009.03.31
                                                    _union.Nrm.CalParm[71 - 1].max = current_table_data_member((short)gf_Up_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2010.03.08
                                                    //2010.03.08 _union.Nrm.CalParm[71 - 1].min = (short)gf_Up_slop_pulse_curr;         //僷儖僗僺乕僋揹棳 2009.03.31
                                                    _union.Nrm.CalParm[71 - 1].min = current_table_data_member((short)gf_Up_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2019.03.08
                                                    //_union.Nrm.CalParm[18 - 1].min = (short)gf_Up_slop_pulse_curr;  //僷儖僗僺乕僋揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[18 - 1].max = (short)gf_Up_slop_pulse_curr;  //僷儖僗僺乕僋揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[20 - 1].min = (short)gf_Up_slop_base_curr;   //僷儖僗儀乕僗揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[20 - 1].max = (short)gf_Up_slop_base_curr;   //僷儖僗儀乕僗揹棳 2009.03.27 del
                                                    _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;//僷儖僗僨儏乕僥傿 2009.03.27 85->70
                                                    _union.Nrm.CalParm[68 - 1].c = 1; //2009.03.27 65->68
                                                    gtt_Ctrl_flag.Wave_current_time = OFF;
            	                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                    gtt_Ctrl_flag.Hpi_control = true;
                                            }
                        	        }
                                        sspdSend();
                                        IMJTOCR4  = 0x05; //2006.2.9 妱嫋
#else
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 1;
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 //mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        if (guc_Pulse_mode_data == 0)                                        
                                        {
                                            if (gtt_Ctrl_flag.Up_slop_curr_end == OFF)
                                            {
                                                gf_Up_slop_base_curr = gf_Up_slop_base_curr + gf_Up_slop_base_step;
                                            }
                                            //ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt);   //2010.02.19
					    MtoC[PRE_CURR_DATA] = gf_Up_slop_base_curr; //2019.06.03
                                        } else {
                                            if (gtt_Ctrl_flag.Up_slop_curr_end == OFF)
                                            {
                                                gf_Up_slop_base_curr  = gf_Up_slop_base_curr  + gf_Up_slop_base_step;
                                                gf_Up_slop_pulse_curr = gf_Up_slop_pulse_curr + gf_Up_slop_pulse_step;
                                            }
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
                                            if (gtt_Internal_pack.Data.In.usPulseFreq <= 5000) //2019.06.03
                                            {
                                                gtt_Ctrl_flag.Hpi_control = true; //2009.02.28
	                                        if (gtt_Ctrl_flag.Wave_current_time == OFF)
    	                                        {
                                                    gtt_Ctrl_flag.Wave_current_time = ON;
            	                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                } else { 
                                                    if (gtt_Ctrl_flag.Condition_change == OFF)
                                                    {
                                                        //ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_pulse_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俛忦審 2010.02.19
					    		MtoC[PRE_CURR_DATA] = gf_Up_slop_base_curr; //2019.06.03
                                                        gtt_Ctrl_flag.Dsp_pulse_out = ON; //2009.04.11
                                                    } else {
                                                        //ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
					    		MtoC[PRE_CURR_DATA] = gf_Up_slop_base_curr; //2019.06.03
                                                        gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                                                    }
                                                    if (gtt_Ctrl_flag.Condition_time_set == OFF)
                                                    {
                                                        gtt_Ctrl_counter.Frequence_time = gtt_Ctrl_counter.Frequence_set_time;
                                                        gtt_Ctrl_counter.B_condition_time = gtt_Ctrl_counter.B_condition_set_time;


                                                        gtt_Ctrl_flag.Condition_time_set = ON;
                                                    } else {
                                                        if (gtt_Ctrl_counter.B_condition_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = ON;
                                                        }
                                                        if (gtt_Ctrl_counter.Frequence_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = OFF;
                                                            gtt_Ctrl_flag.Condition_time_set = OFF;
                                                        }
                                                    }
                                                }
                                            } else { //2009.02.27
                                                   // ctlclsWeldCondSet(current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                                   
					    		MtoC[PRE_CURR_DATA] = gf_Up_slop_base_curr; //2019.06.03
						   // _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;   //僷儖僗廃攇悢 2009.03.27 13->69
                                                   // _union.Nrm.CalParm[71 - 1].max = current_table_data_member((short)gf_Up_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2010.03.08
                                                   // _union.Nrm.CalParm[71 - 1].min = current_table_data_member((short)gf_Up_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2019.03.08
                                                   // _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;//僷儖僗僨儏乕僥傿 2009.03.27 85->70
                                                   // _union.Nrm.CalParm[68 - 1].c = 1; //2009.03.27 65->68
                                                    gtt_Ctrl_flag.Wave_current_time = OFF;
            	                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                    gtt_Ctrl_flag.Hpi_control = true;
                                            }
                        	        }

#endif
                                        break;
                         case MAIN_WELD:

#if 0 //2019.06.03
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 1;
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        if (guc_Pulse_mode_data == 0) _union.Nrm.CalParm[68 - 1].c = 0; //2009.04.03
                                        
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        if (guc_Pulse_mode_data == 0)                                        
                                        {
                                            if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.02.10僄僉僗僷乕僩影霓帋尡梡
                                            {
                                              if (gtt_Ctrl_flag.Ref_voltage_result == ON) //2009.02.20僄僉僗僷乕僩儌乕僪帋尡梡
                                              {
                                                  if (gtt_Ctrl_flag.Cal == ON)
                                                  {
                                                      if (gtt_Ctrl_flag.hugou == ON)
                                                      {
                                                          if (gf_Target_current > gf_Out_current)
                                                          {
                                                              gf_Out_current = gf_Out_current + 0.1; //2009.02.23
                                                          } else {
                                                              gtt_Ctrl_flag.Cal = OFF;
                                                              gss_Target_current_sabun_bkup = gss_Target_current_sabun;
                                                          }
                                                      } else {
                                                          if (gf_Target_current < gf_Out_current)
                                                          {
                                                              gf_Out_current = gf_Out_current - 0.1; //2009.02.23
                                                          } else {
                                                              gtt_Ctrl_flag.Cal = OFF;
                                                              gss_Target_current_sabun_bkup = gss_Target_current_sabun;
                                                          }
                                                      }
                                                  }
                                                  //ctlclsWeldCondSet((short)gf_Out_current , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                  ctlclsWeldCondSet(current_table_data_member((short)gf_Out_current) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                              } else {
                                                  //ctlclsWeldCondSet((short)gf_Out_current , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                  ctlclsWeldCondSet(current_table_data_member((short)gf_Out_current) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                              }
                                            } else {
                                               //***** 弌椡曗惓 2009.02.16*****
                                             //if (gss_Select_dital[P_OUTPUT_SELECT] == true)
                                             if (gtt_Ctrl_flag.Disp_adjust == ON) //2009.03.16
                                             {
                                               {
                                                 short pss_Output_current;
                                                 unsigned char puc_Correct_flag;
                                                 short pss_Output_difference_work;
                                                 gss_Output_difference = gtt_Internal_pack.Data.In.usWeldingCurr - gss_Current_work;
                                                 if (gss_Output_difference < 0)
                                                 {
                                                     pss_Output_difference_work = gss_Output_difference * -1;
                                                 } else {
                                                     pss_Output_difference_work = gss_Output_difference;
                                                 }
                                                 if (pss_Output_difference_work < 10)
                                                 {
                                                     puc_Correct_flag = ON;
                                                 } else {
                                                     puc_Correct_flag = OFF;
                                                     gf_Output_correct_value = 0;
                                                 }
                                                 if (gss_Output_difference == 0)
                                                 {
                                                     puc_Correct_flag = OFF;
                                                 }
                                                 if (gtt_Ctrl_flag.Output_correct == ON && puc_Correct_flag == ON)
                                                 {
                                                     gtt_Ctrl_flag.Output_correct = OFF;
                                                     gf_Output_correct_value = gf_Output_correct_value + (float)gss_Output_difference / 8;
                                                 }
                                                 pss_Output_current = gtt_Internal_pack.Data.In.usWeldingCurr + (short)gf_Output_correct_value;
                                                 //ctlclsWeldCondSet( pss_Output_current , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                 ctlclsWeldCondSet( current_table_data_member(pss_Output_current) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                                }
                                              } else {
                                                if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.03.14
                                                {
                                                    if (gtt_Internal_pack.Data.In.sUpSlopTime > 0) //2009.03.26
                                                    {
                                                        //ctlclsWeldCondSet( gf_Up_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingVolt);
                                                        ctlclsWeldCondSet( current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                                    } else {
                                                        //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt); //2009.03.26
                                                        ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                                    }
                                                } else {
                                                    //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt);
                                                    ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                                }
                                              }
                                            }
                                        } else {
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 50) //2009.02.27
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 40) //2009.07.24
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
                                            if (gtt_Internal_pack.Data.In.usPulseFreq <= 5000) //2019.06.03
                                            {
                                                _union.Nrm.CalParm[68 - 1].c = 0; //2009.02.27 2009.03.27 65->68
                                                gtt_Ctrl_flag.Hpi_control = true; //2009.02.28
	                                        if (gtt_Ctrl_flag.Wave_current_time == OFF)
    	                                        {
                                                    gtt_Ctrl_flag.Wave_current_time = ON;
            	                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                    //_union.Nrm.CalParm[18 - 1].max = 400; //僷儖僗僺乕僋揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[18 - 1].min = 1;   //僷儖僗僺乕僋揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[20 - 1].max = 400; //僷儖僗儀乕僗揹棳 2009.03.27 del
                                                    //_union.Nrm.CalParm[20 - 1].min = 1;   //僷儖僗儀乕僗揹棳 2009.03.27 del
                                                    //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usIP , gtt_Internal_pack.Data.In.usWeldingVolt); //2009.03.27
                                                    ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usIP) , gtt_Internal_pack.Data.In.usWeldingVolt);//2010.02.19
                                                 } else { 
                                                    if (gtt_Ctrl_flag.Condition_change == OFF)
                                                    {
                                                           //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usIP , gtt_Internal_pack.Data.In.usWeldingVolt);
                                                           ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usIP) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                                           //PLS_OUT = ON; //2009.03.17
                                                           gtt_Ctrl_flag.Dsp_pulse_out = ON; //2009.04.11
                                                        //} 2009.03.14
                                                    } else {
                                                      //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt);
                                                      ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                                      //PLS_OUT = OFF; //2009.03.17
                                                      gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                                                    }
                                                    if (gtt_Ctrl_flag.Condition_time_set == OFF)
                                                    {
                                                        gtt_Ctrl_counter.Frequence_time = gtt_Ctrl_counter.Frequence_set_time;
                                                        gtt_Ctrl_counter.B_condition_time = gtt_Ctrl_counter.B_condition_set_time;

                                                        //gtt_Ctrl_counter.Frequence_time   = (unsigned long)((float)gtt_Ctrl_counter.Frequence_set_time * 0.94); //2009.07.24 抶傟偺曗惓
                                                        //gtt_Ctrl_counter.B_condition_time = (unsigned long)((float)gtt_Ctrl_counter.B_condition_time * 0.92);   //2009.07.24 抶傟偺曗惓
  
                                                        gtt_Ctrl_flag.Condition_time_set = ON;
                                                    } else {
                                                        if (gtt_Ctrl_counter.B_condition_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = ON;
                                                        }
                                                        if (gtt_Ctrl_counter.Frequence_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = OFF;
                                                            gtt_Ctrl_flag.Condition_time_set = OFF;
                                                        }
                                                    }
                                                 }
                        	            } else { //2009.02.27
                                              //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt);
                                              ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                              _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;//僷儖僗廃攇悢 2009.03.27 13->69
                                              //2010.03.08_union.Nrm.CalParm[71 - 1].max = gtt_Internal_pack.Data.In.usIP;         //僷儖僗僺乕僋揹棳 2009.03.31
                                              _union.Nrm.CalParm[71 - 1].max = current_table_data_member(gtt_Internal_pack.Data.In.usIP);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //2010.03.08_union.Nrm.CalParm[71 - 1].min = gtt_Internal_pack.Data.In.usIP;         //僷儖僗僺乕僋揹棳 2009.03.31
                                              _union.Nrm.CalParm[71 - 1].min = current_table_data_member(gtt_Internal_pack.Data.In.usIP);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //_union.Nrm.CalParm[18 - 1].max = gtt_Internal_pack.Data.In.usIP;         //僷儖僗僺乕僋揹棳 2009.03.27 del
                                              //_union.Nrm.CalParm[18 - 1].min = gtt_Internal_pack.Data.In.usIP;         //僷儖僗僺乕僋揹棳 2009.03.27 del
                                              //_union.Nrm.CalParm[20 - 1].max = gtt_Internal_pack.Data.In.usWeldingCurr;//僷儖僗儀乕僗揹棳 2009.03.27 del
                                              //_union.Nrm.CalParm[20 - 1].min = gtt_Internal_pack.Data.In.usWeldingCurr;//僷儖僗儀乕僗揹棳 2009.03.27 del
                                              _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;      //僷儖僗僨儏乕僥傿 2009.03.27 85->70
                                              _union.Nrm.CalParm[68 - 1].c = 1; //2009.03.27 65->68
                                              gtt_Ctrl_flag.Wave_current_time = OFF;
            	                              gtt_Ctrl_flag.Condition_time_set = OFF;
                                              gtt_Ctrl_flag.Condition_change = OFF;
                                              gtt_Ctrl_flag.Hpi_control = true;
                                            }
                                        }
                                        sspdSend();
                                        IMJTOCR4  = 0x05; //2006.2.9 妱嫋
#else
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 1;
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 //mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        if (guc_Pulse_mode_data == 0) _union.Nrm.CalParm[68 - 1].c = 0; //2009.04.03
                                        
                                        if (guc_Pulse_mode_data == 0)                                        
                                        {
                                            if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.02.10僄僉僗僷乕僩影霓帋尡梡
                                            {
                                              if (gtt_Ctrl_flag.Ref_voltage_result == ON) //2009.02.20僄僉僗僷乕僩儌乕僪帋尡梡
                                              {
                                                  if (gtt_Ctrl_flag.Cal == ON)
                                                  {
                                                      if (gtt_Ctrl_flag.hugou == ON)
                                                      {
                                                          if (gf_Target_current > gf_Out_current)
                                                          {
                                                              gf_Out_current = gf_Out_current + 0.1; //2009.02.23
                                                          } else {
                                                              gtt_Ctrl_flag.Cal = OFF;
                                                              gss_Target_current_sabun_bkup = gss_Target_current_sabun;
                                                          }
                                                      } else {
                                                          if (gf_Target_current < gf_Out_current)
                                                          {
                                                              gf_Out_current = gf_Out_current - 0.1; //2009.02.23
                                                          } else {
                                                              gtt_Ctrl_flag.Cal = OFF;
                                                              gss_Target_current_sabun_bkup = gss_Target_current_sabun;
                                                          }
                                                      }
                                                  }
                                                  //ctlclsWeldCondSet(current_table_data_member((short)gf_Out_current) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
					    		MtoC[PRE_CURR_DATA] = gf_Out_current; //2019.06.03
                                              } else {
                                                  //ctlclsWeldCondSet(current_table_data_member((short)gf_Out_current) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
					    		MtoC[PRE_CURR_DATA] = gf_Out_current; //2019.06.03
                                              }
                                            } else {
                                               //***** 弌椡曗惓 2009.02.16*****
                                             //if (gss_Select_dital[P_OUTPUT_SELECT] == true)
                                             if (gtt_Ctrl_flag.Disp_adjust == ON) //2009.03.16
                                             {
                                               {
                                                 short pss_Output_current;
                                                 unsigned char puc_Correct_flag;
                                                 short pss_Output_difference_work;
                                                 gss_Output_difference = gtt_Internal_pack.Data.In.usWeldingCurr - gss_Current_work;
                                                 if (gss_Output_difference < 0)
                                                 {
                                                     pss_Output_difference_work = gss_Output_difference * -1;
                                                 } else {
                                                     pss_Output_difference_work = gss_Output_difference;
                                                 }
                                                 if (pss_Output_difference_work < 10)
                                                 {
                                                     puc_Correct_flag = ON;
                                                 } else {
                                                     puc_Correct_flag = OFF;
                                                     gf_Output_correct_value = 0;
                                                 }
                                                 if (gss_Output_difference == 0)
                                                 {
                                                     puc_Correct_flag = OFF;
                                                 }
                                                 if (gtt_Ctrl_flag.Output_correct == ON && puc_Correct_flag == ON)
                                                 {
                                                     gtt_Ctrl_flag.Output_correct = OFF;
                                                     gf_Output_correct_value = gf_Output_correct_value + (float)gss_Output_difference / 8;
                                                 }
                                                 pss_Output_current = gtt_Internal_pack.Data.In.usWeldingCurr + (short)gf_Output_correct_value;
                                                 //ctlclsWeldCondSet( current_table_data_member(pss_Output_current) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
					    		MtoC[PRE_CURR_DATA] = gf_Out_current; //2019.06.03
                                                }
                                              } else {
                                                if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.03.14
                                                {
                                                    if (gtt_Internal_pack.Data.In.sUpSlopTime > 0) //2009.03.26
                                                    {
                                                        //ctlclsWeldCondSet( current_table_data_member((short)gf_Up_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
					    		MtoC[PRE_CURR_DATA] = gf_Up_slop_base_curr; //2019.06.03
                                                    } else {
                                                        //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
					    		MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCurr; //2019.06.03
                                                    }
                                                } else {
                                                    //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
					    		MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCurr; //2019.06.03
                                                }
                                              }
                                            }
                                        } else {
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
                                            if (gtt_Internal_pack.Data.In.usPulseFreq <= 5000) //2019.06.03
                                            {
                                                //_union.Nrm.CalParm[68 - 1].c = 0; //2009.02.27 2009.03.27 65->68
                                                gtt_Ctrl_flag.Hpi_control = true; //2009.02.28
	                                        if (gtt_Ctrl_flag.Wave_current_time == OFF)
    	                                        {
                                                    gtt_Ctrl_flag.Wave_current_time = ON;
            	                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                    //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usIP) , gtt_Internal_pack.Data.In.usWeldingVolt);//2010.02.19
					    		MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usIP; //2019.06.03
                                                 } else { 
                                                    if (gtt_Ctrl_flag.Condition_change == OFF)
                                                    {
                                                           //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usIP) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usIP; //2019.06.03
                                                           gtt_Ctrl_flag.Dsp_pulse_out = ON; //2009.04.11
                                                    } else {
                                                      //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCurr; //2019.06.03
                                                      gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                                                    }
                                                    if (gtt_Ctrl_flag.Condition_time_set == OFF)
                                                    {
                                                        gtt_Ctrl_counter.Frequence_time = gtt_Ctrl_counter.Frequence_set_time;
                                                        gtt_Ctrl_counter.B_condition_time = gtt_Ctrl_counter.B_condition_set_time;

  
                                                        gtt_Ctrl_flag.Condition_time_set = ON;
                                                    } else {
                                                        if (gtt_Ctrl_counter.B_condition_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = ON;
                                                        }
                                                        if (gtt_Ctrl_counter.Frequence_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = OFF;
                                                            gtt_Ctrl_flag.Condition_time_set = OFF;
                                                        }
                                                    }
                                                 }
                        	            } else { //2009.02.27
                                              //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCurr; //2019.06.03
                                              //_union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;//僷儖僗廃攇悢 2009.03.27 13->69
                                              //_union.Nrm.CalParm[71 - 1].max = current_table_data_member(gtt_Internal_pack.Data.In.usIP);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //_union.Nrm.CalParm[71 - 1].min = current_table_data_member(gtt_Internal_pack.Data.In.usIP);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //_union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;      //僷儖僗僨儏乕僥傿 2009.03.27 85->70
                                              //_union.Nrm.CalParm[68 - 1].c = 1; //2009.03.27 65->68
                                              gtt_Ctrl_flag.Wave_current_time = OFF;
            	                              gtt_Ctrl_flag.Condition_time_set = OFF;
                                              gtt_Ctrl_flag.Condition_change = OFF;
                                              gtt_Ctrl_flag.Hpi_control = true;
                                            }
                                        }
#endif


                                        break;
                         case DOWN_SLOPE:
#if 0 //2019.06.03
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 1;
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        if (guc_Pulse_mode_data == 0)                                        
                                        {
                                            if (gtt_Ctrl_flag.Down_slop_curr_end == OFF)
                                            {
                                                gf_Down_slop_base_curr = gf_Down_slop_base_curr + gf_Down_slop_base_step;
                                            }
                                            //ctlclsWeldCondSet((short)gf_Down_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingVolt);   // 揹棳乛揹埑 2006.12.11 test捛壛
                                            ctlclsWeldCondSet(current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt);   //2010.02.19
                                        } else {
                                            if (gtt_Ctrl_flag.Down_slop_curr_end == OFF)
                                            {
                                                gf_Down_slop_base_curr = gf_Down_slop_base_curr + gf_Down_slop_base_step;
                                                gf_Down_slop_pulse_curr = gf_Down_slop_pulse_curr + gf_Down_slop_pulse_step;
                                            }
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 50) //2009.02.27
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 40) //2009.07.24
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
                                            if (gtt_Internal_pack.Data.In.usPulseFreq <= 5000) //2019.06.03
                                            {
                                                _union.Nrm.CalParm[68 - 1].c = 0; //2009.02.27 2009.03.27 65->68
                                                gtt_Ctrl_flag.Hpi_control = true; //2009.02.28
	                                        if (gtt_Ctrl_flag.Wave_current_time == OFF)
    	                                        {
                                                    gtt_Ctrl_flag.Wave_current_time = ON;
                                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                    //_union.Nrm.CalParm[18 - 1].max = 400;  //僷儖僗僺乕僋揹棳 2009.03.27
                                                    //_union.Nrm.CalParm[18 - 1].min = 1;    //僷儖僗僺乕僋揹棳 2009.03.27
                                                    //_union.Nrm.CalParm[20 - 1].max = 400;  //僷儖僗儀乕僗揹棳 2009.03.27
                                                    //_union.Nrm.CalParm[20 - 1].min = 1;    //僷儖僗儀乕僗揹棳 2009.03.27
                                                } else {
                                                    if (gtt_Ctrl_flag.Condition_change == OFF)
                                                    {
                                                        //ctlclsWeldCondSet( (short)gf_Down_slop_pulse_curr , gtt_Internal_pack.Data.In.usWeldingVolt); //俛忦審
                                                        ctlclsWeldCondSet( current_table_data_member((short)gf_Down_slop_pulse_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俛忦審 2010.02.19
                                                        //PLS_OUT = ON; //2009.03.17
                                                        gtt_Ctrl_flag.Dsp_pulse_out = ON; //2009.04.11
                                                    } else {
                                                        //ctlclsWeldCondSet( (short)gf_Down_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                        ctlclsWeldCondSet( current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                                        //PLS_OUT = OFF; //2009.03.17
                                                        gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                                                    }
                                                    if (gtt_Ctrl_flag.Condition_time_set == OFF)
                                                    {
                                                        gtt_Ctrl_counter.Frequence_time = gtt_Ctrl_counter.Frequence_set_time;
                                                        gtt_Ctrl_counter.B_condition_time = gtt_Ctrl_counter.B_condition_set_time;

                                                        //gtt_Ctrl_counter.Frequence_time   = (unsigned long)((float)gtt_Ctrl_counter.Frequence_set_time * 0.94); //2009.07.24 抶傟偺曗惓
                                                        //gtt_Ctrl_counter.B_condition_time = (unsigned long)((float)gtt_Ctrl_counter.B_condition_time * 0.92);   //2009.07.24 抶傟偺曗惓

                                                        gtt_Ctrl_flag.Condition_time_set = ON;
                                                    } else {
                                                        if (gtt_Ctrl_counter.B_condition_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = ON;
                                                        }
                                                        if (gtt_Ctrl_counter.Frequence_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = OFF;
                                                            gtt_Ctrl_flag.Condition_time_set = OFF;
                                                        }
                                                    }
                                                }
                                            } else { //2009.02.27
                                              //ctlclsWeldCondSet((short)gf_Down_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingVolt);
                                              ctlclsWeldCondSet(current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                              _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;//僷儖僗廃攇悢 2009.03.27 13->69
                                              //2010.03.08_union.Nrm.CalParm[71 - 1].max = (short)gf_Down_slop_pulse_curr;         //僷儖僗僺乕僋揹棳 2009.03.31
                                              _union.Nrm.CalParm[71 - 1].max = current_table_data_member((short)gf_Down_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //2010.03.08_union.Nrm.CalParm[71 - 1].min = (short)gf_Down_slop_pulse_curr;         //僷儖僗僺乕僋揹棳 2009.03.31
                                              _union.Nrm.CalParm[71 - 1].min = current_table_data_member((short)gf_Down_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //_union.Nrm.CalParm[18 - 1].min = (short)gf_Down_slop_pulse_curr;//僷儖僗僺乕僋揹棳 2009.03.27 del
                                              //_union.Nrm.CalParm[18 - 1].max = (short)gf_Down_slop_pulse_curr;//僷儖僗僺乕僋揹棳 2009.03.27 del
                                              //_union.Nrm.CalParm[20 - 1].min = (short)gf_Down_slop_base_curr; //僷儖僗儀乕僗揹棳 2009.03.27 del
                                              //_union.Nrm.CalParm[20 - 1].max = (short)gf_Down_slop_base_curr; //僷儖僗儀乕僗揹棳 2009.03.27 del
                                              _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;//僷儖僗僨儏乕僥傿 2009.03.27 85->70
                                              _union.Nrm.CalParm[68 - 1].c = 1; //2009.03.27 65->68
                                              gtt_Ctrl_flag.Wave_current_time = OFF;
            	                              gtt_Ctrl_flag.Condition_time_set = OFF;
                                              gtt_Ctrl_flag.Condition_change = OFF;
                                              gtt_Ctrl_flag.Hpi_control = true;
                                            }
                        	        }
                                        sspdSend();
                                        IMJTOCR4  = 0x05; //2006.2.9 妱嫋
#else
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 1;
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 //mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        if (guc_Pulse_mode_data == 0)                                        
                                        {
                                            if (gtt_Ctrl_flag.Down_slop_curr_end == OFF)
                                            {
                                                gf_Down_slop_base_curr = gf_Down_slop_base_curr + gf_Down_slop_base_step;
                                            }
                                            ctlclsWeldCondSet(current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt);   //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gf_Down_slop_base_curr; //2019.06.03
                                        } else {
                                            if (gtt_Ctrl_flag.Down_slop_curr_end == OFF)
                                            {
                                                gf_Down_slop_base_curr = gf_Down_slop_base_curr + gf_Down_slop_base_step;
                                                gf_Down_slop_pulse_curr = gf_Down_slop_pulse_curr + gf_Down_slop_pulse_step;
                                            }
                                            //if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
                                            if (gtt_Internal_pack.Data.In.usPulseFreq <= 5000) //2019.06.03
                                            {
                                                //_union.Nrm.CalParm[68 - 1].c = 0; //2009.02.27 2009.03.27 65->68
                                                gtt_Ctrl_flag.Hpi_control = true; //2009.02.28
	                                        if (gtt_Ctrl_flag.Wave_current_time == OFF)
    	                                        {
                                                    gtt_Ctrl_flag.Wave_current_time = ON;
                                                    gtt_Ctrl_flag.Condition_time_set = OFF;
                                                    gtt_Ctrl_flag.Condition_change = OFF;
                                                } else {
                                                    if (gtt_Ctrl_flag.Condition_change == OFF)
                                                    {
                                                        //ctlclsWeldCondSet( current_table_data_member((short)gf_Down_slop_pulse_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俛忦審 2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gf_Down_slop_pulse_curr; //2019.06.03
                                                        gtt_Ctrl_flag.Dsp_pulse_out = ON; //2009.04.11
                                                    } else {
                                                        //ctlclsWeldCondSet( current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gf_Down_slop_pulse_curr; //2019.06.03
                                                        gtt_Ctrl_flag.Dsp_pulse_out = OFF; //2009.04.11
                                                    }
                                                    if (gtt_Ctrl_flag.Condition_time_set == OFF)
                                                    {
                                                        gtt_Ctrl_counter.Frequence_time = gtt_Ctrl_counter.Frequence_set_time;
                                                        gtt_Ctrl_counter.B_condition_time = gtt_Ctrl_counter.B_condition_set_time;
                                                        gtt_Ctrl_flag.Condition_time_set = ON;
                                                    } else {
                                                        if (gtt_Ctrl_counter.B_condition_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = ON;
                                                        }
                                                        if (gtt_Ctrl_counter.Frequence_time <= 0)
                                                        {
                                                            gtt_Ctrl_flag.Condition_change = OFF;
                                                            gtt_Ctrl_flag.Condition_time_set = OFF;
                                                        }
                                                    }
                                                }
                                            } else { //2009.02.27
                                              //ctlclsWeldCondSet(current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gf_Down_slop_pulse_curr; //2019.06.03
                                              //_union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;//僷儖僗廃攇悢 2009.03.27 13->69
                                              //_union.Nrm.CalParm[71 - 1].max = current_table_data_member((short)gf_Down_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //_union.Nrm.CalParm[71 - 1].min = current_table_data_member((short)gf_Down_slop_pulse_curr);         //僷儖僗僺乕僋揹棳 2010.03.08
                                              //_union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;//僷儖僗僨儏乕僥傿 2009.03.27 85->70
                                              //_union.Nrm.CalParm[68 - 1].c = 1; //2009.03.27 65->68
                                              gtt_Ctrl_flag.Wave_current_time = OFF;
            	                              gtt_Ctrl_flag.Condition_time_set = OFF;
                                              gtt_Ctrl_flag.Condition_change = OFF;
                                              gtt_Ctrl_flag.Hpi_control = true;
                                            }
                        	        }
#endif

                                        break;
                         case CRATER_WELD:
#if 0 //2019.06.03
                                        PLS_OUT = OFF; //2009.03.17
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 _union.Nrm.CalParm[65 - 1].c = 1;
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 _union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        
                                        _union.Nrm.CalParm[68 - 1].c = 0; //2009.04.03
                                        //_union.Nrm.CalParm[65 - 1].c = 0; //2009.02.28
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        
                                        if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.02.10僄僉僗僷乕僩影霓帋尡梡
                                        {
                                            //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCratCurr , gtt_Internal_pack.Data.In.usWeldingCratVolt);
                                            ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
                                        } else {
                                               //***** 弌椡曗惓 2009.02.16*****
                                             //if (gss_Select_dital[P_OUTPUT_SELECT] == true)
                                             if (gtt_Ctrl_flag.Disp_adjust == ON) //2009.03.16
                                             {
                                               {
                                                 short pss_Output_current;
                                                 unsigned char puc_Correct_flag;
                                                 short pss_Output_difference_work;
                                                 gss_Output_difference = gtt_Internal_pack.Data.In.usWeldingCratCurr - gss_Current_work;
                                                 if (gss_Output_difference < 0)
                                                 {
                                                     pss_Output_difference_work = gss_Output_difference * -1;
                                                 } else {
                                                     pss_Output_difference_work = gss_Output_difference;
                                                 }
                                                 if (pss_Output_difference_work < 10)
                                                 {
                                                     puc_Correct_flag = ON;
                                                 } else {
                                                     puc_Correct_flag = OFF;
                                                     gf_Output_correct_value = 0;
                                                 }
                                                 if (gss_Output_difference == 0)
                                                 {
                                                     puc_Correct_flag = OFF;
                                                 }
                                                 if (gtt_Ctrl_flag.Output_correct == ON && puc_Correct_flag == ON)
                                                 {
                                                     gtt_Ctrl_flag.Output_correct = OFF;
                                                     gf_Output_correct_value = gf_Output_correct_value + (float)gss_Output_difference / 8;
                                                 }
                                                 pss_Output_current = gtt_Internal_pack.Data.In.usWeldingCratCurr + (short)gf_Output_correct_value;
                                                 //ctlclsWeldCondSet( pss_Output_current , gtt_Internal_pack.Data.In.usWeldingCratVolt); //俙忦審
                                                 ctlclsWeldCondSet( current_table_data_member(pss_Output_current) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //俙忦審 2010.02.19
                                                }
                                              } else {
                                                if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.03.14
                                                {
                                                    if (gtt_Internal_pack.Data.In.sDownSlopTime > 0) //2009.03.26
                                                    {
                                                        //ctlclsWeldCondSet( gf_Down_slop_base_curr , gtt_Internal_pack.Data.In.usWeldingCratVolt);
                                                        ctlclsWeldCondSet( current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
                                                    } else {
                                                        //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCratCurr , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2009.03.26
                                                        ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
                                                    }
                                                } else {
                                                   //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCratCurr , gtt_Internal_pack.Data.In.usWeldingCratVolt);
                                                   ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
                                                }
                                              }
                                        }
                                        
                                        sspdSend();
                                        
                                        IMJTOCR4  = 0x05; //2006.2.9 妱嫋
#else
                                        switch (guc_Method_condition_data) //俵俬倃梡慖戰俽倂 2009.03.27
                                        {
                                            case STD_DC_METHOD:
                                            case STD_HAND_METHOD:
                                            case EXP_DC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                            case STD_AC_METHOD:
                                            case EXP_AC_METHOD:
                                                 //_union.Nrm.CalParm[65 - 1].c = 1;
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            case STD_MIX_METHOD:
                                                 //mix_ctrl_member(); //俵俬倃弌椡偺屇傃弌偟
                                                 //_union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //俙俠廃攇悢偺斀塮 2009.12.29
                                                 break;
                                            default:
                                                 //_union.Nrm.CalParm[65 - 1].c = 0;
                                                 break;
                                        }
                                        
                                        _union.Nrm.CalParm[68 - 1].c = 0; //2009.04.03
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        
                                        if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == EXP_AC_METHOD) //2009.02.10僄僉僗僷乕僩影霓帋尡梡
                                        {
                                            //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCratCurr; //2019.06.03
                                        } else {
                                               //***** 弌椡曗惓 2009.02.16*****
                                             if (gtt_Ctrl_flag.Disp_adjust == ON) //2009.03.16
                                             {
                                               {
                                                 short pss_Output_current;
                                                 unsigned char puc_Correct_flag;
                                                 short pss_Output_difference_work;
                                                 gss_Output_difference = gtt_Internal_pack.Data.In.usWeldingCratCurr - gss_Current_work;
                                                 if (gss_Output_difference < 0)
                                                 {
                                                     pss_Output_difference_work = gss_Output_difference * -1;
                                                 } else {
                                                     pss_Output_difference_work = gss_Output_difference;
                                                 }
                                                 if (pss_Output_difference_work < 10)
                                                 {
                                                     puc_Correct_flag = ON;
                                                 } else {
                                                     puc_Correct_flag = OFF;
                                                     gf_Output_correct_value = 0;
                                                 }
                                                 if (gss_Output_difference == 0)
                                                 {
                                                     puc_Correct_flag = OFF;
                                                 }
                                                 if (gtt_Ctrl_flag.Output_correct == ON && puc_Correct_flag == ON)
                                                 {
                                                     gtt_Ctrl_flag.Output_correct = OFF;
                                                     gf_Output_correct_value = gf_Output_correct_value + (float)gss_Output_difference / 8;
                                                 }
                                                 pss_Output_current = gtt_Internal_pack.Data.In.usWeldingCratCurr + (short)gf_Output_correct_value;
                                                 //ctlclsWeldCondSet( current_table_data_member(pss_Output_current) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //俙忦審 2010.02.19
					    		   MtoC[PRE_CURR_DATA] = pss_Output_current; //2019.06.03
                                                }
                                              } else {
                                                if (gtt_Ctrl_flag.Variable_crater_repaet == true && guc_Crater_mode_counter == SEQUENCE_CRATER_REPEAT) //2009.03.14
                                                {
                                                    if (gtt_Internal_pack.Data.In.sDownSlopTime > 0) //2009.03.26
                                                    {
                                                        //ctlclsWeldCondSet( current_table_data_member((short)gf_Down_slop_base_curr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gf_Down_slop_base_curr; //2019.06.03
                                                    } else {
                                                        //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCratCurr; //2019.06.03
                                                    }
                                                } else {
                                                   //ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCratCurr) , gtt_Internal_pack.Data.In.usWeldingCratVolt); //2010.02.19
					    		   MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCratCurr; //2019.06.03
                                                }
                                              }
                                        }

#endif
                              break;
                         case HAND_STICK:
                                        PLS_OUT = OFF; //2009.03.17
                                        ctlclsDrctSet();
                                        IMJTOCR4  = 0x07;                              //2006.2.15 妱嬛
                                        _union.Nrm.CalParm[65 - 1].c = 0; //2009.03.27 
                                        wcndSend();                                    //梟愙忦審俢俽俹傊揮憲
                                        //***** 傾乕僋僪儔僀僽傪娷傓弌椡惂屼 2009.03.17 *****
                                        {
                                          if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2010.02.19 暯嬒抣
                                          {
                                          
                                              //揹埑偑侾俆倁埲忋
                                              if (gtt_Fpga.Volt_result >= 150)
                                              {
                                                  //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                  ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                              } else if (gtt_Fpga.Volt_result < 50) {  //揹埑偑俆倁埲壓
                                                  //ctlclsWeldCondSet( 50 , gtt_Internal_pack.Data.In.usWeldingVolt); //50A弌椡
                                                  ctlclsWeldCondSet( current_table_data_member(50) , gtt_Internal_pack.Data.In.usWeldingVolt); //50A弌椡 2010.02.19
                                              } else if (gtt_Fpga.Volt_result < 150) { //揹埑偑侾俆倁埲壓
                                                    if (gtt_Ctrl_flag.Arc_drive == ON)
                                                    {
                                                        short A_work;
                                                        A_work = gtt_Internal_pack.Data.In.usWeldingCurr + (short)((float)gtt_Internal_pack.Data.In.usWeldingCurr * (float)gss_Select_dital[P_ARC_DRIVE] / 100.0);
                                                        if (A_work >= MAX_CURRENT_HAND) //2010.02.10
                                                        {
                                                            A_work = MAX_CURRENT_HAND;  //2010.02.10
                                                        }
                                                        //ctlclsWeldCondSet( A_work , gtt_Internal_pack.Data.In.usWeldingVolt);
                                                        ctlclsWeldCondSet( current_table_data_member(A_work) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                                    } else {
                                                        //ctlclsWeldCondSet( gtt_Internal_pack.Data.In.usWeldingCurr , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審
                                                        ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                                    }
                                              }
                                          } else { //幚岠抣慖戰偺応崌偼偙偪傜傪幚峴偡傞傛偆偵曄峏 2010.02.19
                                              //揹埑偑侾俆倁埲忋
                                              if (gtt_Fpga.Volt_result_rms >= 22500) //150 * 150
                                              {
                                                  ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                              } else if (gtt_Fpga.Volt_result_rms < 2500) {  //揹埑偑俆倁埲壓 50 * 50
                                                  ctlclsWeldCondSet( current_table_data_member(50) , gtt_Internal_pack.Data.In.usWeldingVolt); //50A弌椡 2010.02.19
                                              } else if (gtt_Fpga.Volt_result_rms < 22500) { //揹埑偑侾俆倁埲壓 150 * 150
                                                    if (gtt_Ctrl_flag.Arc_drive == ON)
                                                    {
                                                        short A_work;
                                                        A_work = gtt_Internal_pack.Data.In.usWeldingCurr + (short)((float)gtt_Internal_pack.Data.In.usWeldingCurr * (float)gss_Select_dital[P_ARC_DRIVE] / 100.0);
                                                        if (A_work >= MAX_CURRENT_HAND) //2010.02.10
                                                        {
                                                            A_work = MAX_CURRENT_HAND;  //2010.02.10
                                                        }
                                                        ctlclsWeldCondSet( current_table_data_member(A_work) , gtt_Internal_pack.Data.In.usWeldingVolt); //2010.02.19
                                                    } else {
                                                        ctlclsWeldCondSet( current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr) , gtt_Internal_pack.Data.In.usWeldingVolt); //俙忦審 2010.02.19
                                                    }
                                              }
                                          }
                                        }
                                        //*****************************************************
                                        sspdSend();
                                        IMJTOCR4  = 0x05; //2006.2.9 妱嫋
                                        break;
                         default:
                                        break;
                     }
                     gtt_Ctrl_flag.Table_data_output_execution = OFF; //2007.1.12
                 }
            } else { //2008.11.06
#if 0 //2009.03.16
                 if (gtt_Ctrl_flag.Crater_pulse_non == ON && gss_Select_dital[P_CRATER_DC] == ON && guc_Pulse_mode_data == 0x05) //2008.11.06
                 {
                     if (DC_PMODE == 2) DC_PMODE = 1;
                 }
#endif
                 gtt_En.ss_En_a_output = 0; //2008.11.14 僗儘乕僟僂儞拞乮捈棳嬫娫乯偺俤俶斾棪傪侽亾偵妋掕偡傞丅
            }
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_table_data_read_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

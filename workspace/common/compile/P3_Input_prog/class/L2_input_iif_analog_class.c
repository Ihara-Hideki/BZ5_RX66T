//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//Å@Åyä÷êîñºÅz
//Å@Å@Å@ÇâÇéÇêÇïÇîÅQÇâÇâÇÜÅQÇÅÇéÇÅÇåÇèÇáÅQÇÉÇåÇÅÇìÇì
//Å@Åyä÷êîÉåÉxÉãÅz
//Å@Å@Å@ÇkÇdÇuÇdÇkÅFÇQ
//  Åyã@î\ê‡ñæÅz
//      ÇhÇhÇeÉAÉiÉçÉOì¸óÕ
//  Åyà¯êîÅz
//      Ç»Çµ
//  ÅyñﬂÇËílÅz
//      Ç»Çµ  
//  ÅyîıçlÅz
//      Ç»Çµ
//  ÅyçXêVóöóÅz
//      2009.09.24  H.Ihara
//
//            Copyright(C)2009 Panasonic Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

// A/Dïœä∑ç≈ëÂì¸óÕìdà≥
//
#define AD15V   0   // ÇPÇTÇu
#define AD12V   1   // ÇPÇQÇu
#define AD10V   2   // ÇPÇOÇu



//ïœä∑åvéZÇÃäÓì_íl
#define AD_MIN_VALUE          9
#define AD15V_MID_VALUE     297
#define AD12V_MID_VALUE     253
#define AD10V_MID_VALUE     214

//çÇê∏ìxï‚ê≥ Åiéwóﬂìdó¨ÅEéwóﬂìdà≥Åj
#define AD15V_A_HI_ACCURACY_MID_VALUE     387 
#define AD12V_A_HI_ACCURACY_MID_VALUE     323 
#define AD10V_A_HI_ACCURACY_MID_VALUE     272 
#define AD15V_B_HI_ACCURACY_MID_VALUE     201 
#define AD12V_B_HI_ACCURACY_MID_VALUE     163 
#define AD10V_B_HI_ACCURACY_MID_VALUE     137 


//ï‚ê≥ 2009.10.20
#define PLUS_4PRE           (float)1.04
#define PLUS_2PRE           (float)1.02
#define ZERO                (float)1.00
#define MINUS_2PRE          (float)0.98
#define MINUS_4PRE          (float)0.96


#define YD350GZ4            1
#define YD500GZ4            0


extern  sint        WireSpd_Offset; // 2008.11.27

void input_iif_analog_class(void)
{
#if 0	// EXTERNAL IIF NEW	2011.02.21 by @Tny

    unsigned char  puc_Index;
    unsigned short pss_Ad_mid_value;
    float          pf_Coefficient;
    float          pf_Work;
    float          pf_C;
    unsigned char  puc_Iif_dsw_data;

    float          pf_Iif_analog_revise[5]; //2009.11.13
    //signed short     pss_Iif_analog_revise[5]; //2009.11.11

    //ï‚ê≥ílåàíË
    for (puc_Index = 1 ; puc_Index <= 4 ; puc_Index++)
    {
#if 0 //2009.11.11 del
         if (InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] <= 1024)
         {
             pf_Iif_analog_revise[puc_Index] = PLUS_4PRE;
         }
         if (InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] <= 820)
         {
             pf_Iif_analog_revise[puc_Index] = PLUS_2PRE;
         }
         if (InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] <= 615)
         {
             pf_Iif_analog_revise[puc_Index] = ZERO;
         }
         if (InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] <= 410)
         {
             pf_Iif_analog_revise[puc_Index] = MINUS_2PRE;
         }
         if (InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] <= 205)
         {
             pf_Iif_analog_revise[puc_Index] = MINUS_4PRE;
         }
#endif
         //pss_Iif_analog_revise[puc_Index] = (InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] - 512) / 51; //2009.11.11
         //pss_Iif_analog_revise[puc_Index] = (short)((float)(InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] - 512) / 42.5); //2009.11.12
         pf_Iif_analog_revise[puc_Index] = 1.00 + ((float)(short)(((short)InternalPackIif.Data.To.us_Iif_analog_revise[puc_Index] - 512) / 42.5) * 0.005); //2009.11.12
         gf_Iif_analog_revise[puc_Index] = pf_Iif_analog_revise[puc_Index]; //testóp 2009.11.13
    }

    //if(gb_IIF_Select){  // IIFê⁄ë±ÇämîF
    if((gb_IIF_Select == true)&&(gb_Iif_Input)&&(gtt_Ctrl_flag.Iif_enable == true)&&(gtt_Ctrl_flag.Set_screen_on_off == OFF) && (gtt_Ctrl_flag.Iif_first_rcv == ON)) //IIFê⁄ë±ämîF 2009.11.13
    {
        for (puc_Index = 1 ; puc_Index <= 3 ; puc_Index++)
        {
             //<><><><><><><><><><><><><><><><><><><><> ónê⁄ìdó¨éwóﬂíl <><><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_PR_CUR)
             {

                 //ÇcÇrÇvÇ…ÇÊÇÈéwóﬂílÇÃê∏ìxëIë
                 puc_Iif_dsw_data = InternalPackIif.Data.To.t_Iif_dsw.ALL;
                 switch (puc_Index)
                 {
                     case 1:
                          break;
                     case 2:
                          puc_Iif_dsw_data = puc_Iif_dsw_data >> 2;
                          break;
                     case 3:
                          puc_Iif_dsw_data = puc_Iif_dsw_data >> 4;
                          break;
                     default:
                          break;
                 }
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
#if YD350GZ4
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          switch (puc_Iif_dsw_data)
                          {
                              case 0: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.7248;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 15.0;
                                break;
                              case 1: //â∫çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD15V_A_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 2.3674;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 15.0;
                                } else {
                                    pf_Coefficient   = 1.1373;
                                    pss_Ad_mid_value = AD15V_A_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 175.0;
                                }
                                break;
                              case 2: //è„çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD15V_B_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 1.2038;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 15.0;
                                } else {
                                    pf_Coefficient   = 2.2011;
                                    pss_Ad_mid_value = AD15V_B_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 175.0;
                                }
                                break;
                              default: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.7248;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 15.0;
                                break;
                          }
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          switch (puc_Iif_dsw_data)
                          {
                              case 0: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.4565;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 15.0;
                                break;
                              case 1: //â∫çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD12V_A_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 1.9661;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 15.0;
                                } else {
                                    pf_Coefficient   = 0.9905;
                                    pss_Ad_mid_value = AD12V_A_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 175.0;
                                }
                                break;
                              case 2: //è„çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD12V_B_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 0.9630;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 15.0;
                                } else {
                                    pf_Coefficient   = 1.9077;
                                    pss_Ad_mid_value = AD12V_B_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 175.0;
                                }
                                break;
                              default: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.4565;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 15.0;
                                break;
                          }
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          switch (puc_Iif_dsw_data)
                          {
                              case 0: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.2265;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 15.0;
                                break;
                              case 1: //â∫çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD10V_A_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 1.6451;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 15.0;
                                } else {
                                    pf_Coefficient   = 0.8438;
                                    pss_Ad_mid_value = AD10V_A_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 175.0;
                                }
                                break;
                              case 2: //è„çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD10V_B_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 0.8025;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 15.0;
                                } else {
                                    pf_Coefficient   = 1.6142;
                                    pss_Ad_mid_value = AD10V_B_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 175.0;
                                }
                                break;
                              default: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.2265;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 15.0;
                                break;
                          }
                          break;
                     default:
                          break;
                 }
#endif
#if YD500GZ4
#endif
                 //ç≈èIílÇÃéZèo
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value);
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index];
                 //gtt_Internal_pack.Data.In.usWeldingCurr = (unsigned short)(pf_Work / pf_Coefficient + pf_C);    //2009.11.12 del
                 gtt_Internal_pack.Data.In.usWeldingCurr = (unsigned short)(pf_Work / pf_Coefficient + pf_C + 0.5); //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gtt_Internal_pack.Data.In.usWeldingCurr > PR_CUR_MAX_VALUE)
                 {
                     gtt_Internal_pack.Data.In.usWeldingCurr = PR_CUR_MAX_VALUE;
                 } else if (gtt_Internal_pack.Data.In.usWeldingCurr < PR_CUR_MIN_VALUE) {
                     gtt_Internal_pack.Data.In.usWeldingCurr = PR_CUR_MIN_VALUE;
                 }
             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

             //<><><><><><><><><><><><><><><><><><><><> ónê⁄ìdà≥éwóﬂíl <><><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_PR_VLT)
             {
                 //ÇcÇrÇvÇ…ÇÊÇÈéwóﬂílÇÃê∏ìxëIë
                 puc_Iif_dsw_data = InternalPackIif.Data.To.t_Iif_dsw.ALL;
                 switch (puc_Index)
                 {
                     case 1:
                          break;
                     case 2:
                          puc_Iif_dsw_data = puc_Iif_dsw_data >> 2;
                          break;
                     case 3:
                          puc_Iif_dsw_data = puc_Iif_dsw_data >> 4;
                          break;
                     default:
                          break;
                 }
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          pf_Coefficient = 1.2840;
                          pss_Ad_mid_value = AD_MIN_VALUE;
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          pf_Coefficient = 1.0843;
                          pss_Ad_mid_value = AD_MIN_VALUE;
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          pf_Coefficient = 0.9131;
                          pss_Ad_mid_value = AD_MIN_VALUE;
                          break;
                     default:
                          break;
                 }

#if YD350GZ4
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          switch (puc_Iif_dsw_data)
                          {
                              case 0: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.2840;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 50;
                                break;
                              case 1: //â∫çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD15V_A_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 1.8939;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 50;
                                } else {
                                    pf_Coefficient   = 0.7961;
                                    pss_Ad_mid_value = AD15V_A_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 250;
                                }
                                break;
                              case 2: //è„çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD15V_B_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 0.9630;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 50;
                                } else {
                                    pf_Coefficient   = 1.5408;
                                    pss_Ad_mid_value = AD15V_B_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 250;
                                }
                                break;
                              default: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.2840;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 50;
                                break;
                          }
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          switch (puc_Iif_dsw_data)
                          {
                              case 0: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.0843;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 50;
                                break;
                              case 1: //â∫çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD12V_A_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 1.5729;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 50;
                                } else {
                                    pf_Coefficient   = 0.6934;
                                    pss_Ad_mid_value = AD12V_A_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 250;
                                }
                                break;
                              case 2: //è„çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD12V_B_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 0.7704;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 50;
                                } else {
                                    pf_Coefficient   = 1.3354;
                                    pss_Ad_mid_value = AD12V_B_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 250;
                                }
                                break;
                              default: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 1.0843;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 50;
                                break;
                          }
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          switch (puc_Iif_dsw_data)
                          {
                              case 0: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 0.9131;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 50;
                                break;
                              case 1: //â∫çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD10V_A_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 1.3161;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 50;
                                } else {
                                    pf_Coefficient   = 0.5906;
                                    pss_Ad_mid_value = AD10V_A_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 250;
                                }
                                break;
                              case 2: //è„çÇê∏ìx
                                if (InternalPackIif.Data.To.us_Analog_data[puc_Index] < AD10V_B_HI_ACCURACY_MID_VALUE)
                                {
                                    pf_Coefficient   = 0.6420;
                                    pss_Ad_mid_value = AD_MIN_VALUE;
                                    pf_C             = 50;
                                } else {
                                    pf_Coefficient   = 1.1299;
                                    pss_Ad_mid_value = AD10V_B_HI_ACCURACY_MID_VALUE;
                                    pf_C             = 250;
                                }
                                break;
                              default: //ê∏ìxï‚ê≥Ç»Çµ
                                pf_Coefficient = 0.9131;
                                pss_Ad_mid_value = AD_MIN_VALUE;
                                pf_C             = 50;
                                break;
                          }
                          break;
                     default:
                          break;
                 }
#endif
#if YD500GZ4
#endif
                 //ç≈èIílÇÃéZèo
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value); //2009.11.11 del
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index]; //2009.11.11 del
#if 0 // 2009.11.12 del
                 gtt_Internal_pack.Data.In.usWeldingVolt = (unsigned short)(pf_Work / pf_Coefficient + pf_C);
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gtt_Internal_pack.Data.In.usWeldingVolt > PR_VLT_MAX_VALUE)
                 {
                     gtt_Internal_pack.Data.In.usWeldingVolt = PR_VLT_MAX_VALUE;
                 } else if (gtt_Internal_pack.Data.In.usWeldingVolt < PR_VLT_MIN_VALUE) {
                     gtt_Internal_pack.Data.In.usWeldingVolt = PR_VLT_MIN_VALUE;
                 }
#endif
                 //gus_Display_main_preset_voltage = (unsigned short)(pf_Work / pf_Coefficient + pf_C);   //2009.11.12 del
                 gus_Display_main_preset_voltage = (unsigned short)(pf_Work / pf_Coefficient + pf_C + 0.5); //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gus_Display_main_preset_voltage > PR_VLT_MAX_VALUE)
                 {
                     gus_Display_main_preset_voltage = PR_VLT_MAX_VALUE;
                 } else if (gus_Display_main_preset_voltage < PR_VLT_MIN_VALUE) {
                     gus_Display_main_preset_voltage = PR_VLT_MIN_VALUE;
                 }

             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
             
             //<><><><><><><><><><><><><><><><><><><><> àÍå≥ìdà≥éwóﬂíl <><><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_OK_VLT)
             {
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          pf_Coefficient = 2.9480;
                          pss_Ad_mid_value = AD15V_MID_VALUE;
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          pf_Coefficient = 2.4894;
                          pss_Ad_mid_value = AD12V_MID_VALUE;
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          pf_Coefficient = 2.0963;
                          pss_Ad_mid_value = AD10V_MID_VALUE;
                          break;
                     default:
                          break;
                 }
                 //ç≈èIílÇÃéZèo
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value); //2009.11.11 del
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index]; //2009.11.11 del
                 //gs_Okcv_adjust_data = (short)(pf_Work / pf_Coefficient);       //2009.11.12 del
                 gs_Okcv_adjust_data = (short)(pf_Work / pf_Coefficient + 0.5);   //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gs_Okcv_adjust_data > OK_VLT_MAX_VALUE)
                 {
                     gs_Okcv_adjust_data = OK_VLT_MAX_VALUE;
                 } else if (gs_Okcv_adjust_data < OK_VLT_MIN_VALUE) {
                     gs_Okcv_adjust_data = OK_VLT_MIN_VALUE;
                 }
             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

             //<><><><><><><><><><><><><><><><><><><><><> ónÇØçûÇ›í≤êÆ <><><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_PENET)
             {
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          pf_Coefficient = 9.630;
                          pss_Ad_mid_value = AD15V_MID_VALUE;
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          pf_Coefficient = 8.132;
                          pss_Ad_mid_value = AD12V_MID_VALUE;
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          pf_Coefficient = 6.848;
                          pss_Ad_mid_value = AD10V_MID_VALUE;
                          break;
                     default:
                          break;
                 }
                 //ç≈èIílÇÃéZèo
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value); //2009.11.11 del
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index]; //2009.11.11 del
                 //gss_Select_dital[P_PENETRATION] = (short)(pf_Work / pf_Coefficient);       //2009.11.12 del
                 gss_Select_dital[P_PENETRATION] = (short)(pf_Work / pf_Coefficient + 0.5);   //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gss_Select_dital[P_PENETRATION] < gtt_Dital_attribute[P_PENETRATION].ss_Min)
                 {
                     gss_Select_dital[P_PENETRATION] = gtt_Dital_attribute[P_PENETRATION].ss_Min;
                 }
                 if (gss_Select_dital[P_PENETRATION] > gtt_Dital_attribute[P_PENETRATION].ss_Max)
                 {
                     gss_Select_dital[P_PENETRATION] = gtt_Dital_attribute[P_PENETRATION].ss_Max;
                 }
                 //íçÅFV5Ç÷ÇÃèëÇ´çûÇ›ÇÕpr_generator_memeber()Ç≈çsÇÌÇÍÇÈ
             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

             //<><><><><><><><><><><><><><><><><><><> ÉèÉCÉÑëóããó î˜í≤êÆ <><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_FD_RT)
             {
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          pf_Coefficient = 5.778;
                          pss_Ad_mid_value = AD15V_MID_VALUE;
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          pf_Coefficient = 4.8792;
                          pss_Ad_mid_value = AD12V_MID_VALUE;
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          pf_Coefficient = 4.1088;
                          pss_Ad_mid_value = AD10V_MID_VALUE;
                          break;
                     default:
                          break;
                 }
                 //ç≈èIílÇÃéZèo
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value); //2009.11.11 del
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index]; //2009.11.11 del
                 //gss_Select_dital[P_FEED_RATE] = (short)(pf_Work / pf_Coefficient);      //2009.11.12 del
                 gss_Select_dital[P_FEED_RATE] = (short)(pf_Work / pf_Coefficient + 0.5);  //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gss_Select_dital[P_FEED_RATE] < gtt_Dital_attribute[P_FEED_RATE].ss_Min)
                 {
                     gss_Select_dital[P_FEED_RATE] = gtt_Dital_attribute[P_FEED_RATE].ss_Min;
                 }
                 if (gss_Select_dital[P_FEED_RATE] > gtt_Dital_attribute[P_FEED_RATE].ss_Max)
                 {
                     gss_Select_dital[P_FEED_RATE] = gtt_Dital_attribute[P_FEED_RATE].ss_Max;
                 }
                 WireSpd_Offset = gss_Select_dital[P_FEED_RATE];
             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

             //<><><><><><><><><><><><><><><><><><><><><> îgå`êßå‰ÇP <><><><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_WCTRL1)
             {
                 PNORMAL     pNrm = &_union.Nrm;
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          pf_Coefficient = 2.9182;
                          pss_Ad_mid_value = AD15V_MID_VALUE;
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          pf_Coefficient = 2.4642;
                          pss_Ad_mid_value = AD12V_MID_VALUE;
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          pf_Coefficient = 2.0752;
                          pss_Ad_mid_value = AD10V_MID_VALUE;
                          break;
                     default:
                          break;
                 }
                 //ç≈èIílÇÃéZèo
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value); //2009.11.11 del
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index]; //2009.11.11 del
                 //gss_Select_dital[P_WAVE_CONTROL1] = (short)(pf_Work / pf_Coefficient);     //2009.11.12 del
                 gss_Select_dital[P_WAVE_CONTROL1] = (short)(pf_Work / pf_Coefficient + 0.5); //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gss_Select_dital[P_WAVE_CONTROL1] < gtt_Dital_attribute[P_WAVE_CONTROL1].ss_Min)
                 {
                     gss_Select_dital[P_WAVE_CONTROL1] = gtt_Dital_attribute[P_WAVE_CONTROL1].ss_Min;
                 }
                 if (gss_Select_dital[P_WAVE_CONTROL1] > gtt_Dital_attribute[P_WAVE_CONTROL1].ss_Max)
                 {
                     gss_Select_dital[P_WAVE_CONTROL1] = gtt_Dital_attribute[P_WAVE_CONTROL1].ss_Max;
                 }
                 //íçÅFV32Ç÷ÇÃèëÇ´çûÇ›ÇÕpr_generator_memeber()Ç≈çsÇÌÇÍÇÈ
                 _union.Nrm.CalParm[WAVE_CONTROL1_2_NO - 1].c = pWT->CalParm[WAVE_CONTROL1_2_NO -1].c;
                 _union.Nrm.CalParm[WAVE_CONTROL1_2_NO - 1].c += (float)gss_Select_dital[P_WAVE_CONTROL1] * WAVE_CONTROL1;
             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

             //<><><><><><><><><><><><><><><><><><><><><> îgå`êßå‰ÇQ <><><><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_WCTRL2)
             {
                 PNORMAL     pNrm = &_union.Nrm;
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          pf_Coefficient = 2.9182;
                          pss_Ad_mid_value = AD15V_MID_VALUE;
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          pf_Coefficient = 2.4642;
                          pss_Ad_mid_value = AD12V_MID_VALUE;
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          pf_Coefficient = 2.0752;
                          pss_Ad_mid_value = AD10V_MID_VALUE;
                          break;
                     default:
                          break;
                 }
                 //ç≈èIílÇÃéZèo
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value); //2009.11.11 del
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index]; //2009.11.11 del
                 //gss_Select_dital[P_WAVE_CONTROL2] = (short)(pf_Work / pf_Coefficient);      //2009.11.12 del
                 gss_Select_dital[P_WAVE_CONTROL2] = (short)(pf_Work / pf_Coefficient + 0.5);  //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gss_Select_dital[P_WAVE_CONTROL2] < gtt_Dital_attribute[P_WAVE_CONTROL2].ss_Min)
                 {
                     gss_Select_dital[P_WAVE_CONTROL2] = gtt_Dital_attribute[P_WAVE_CONTROL2].ss_Min;
                 }
                 if (gss_Select_dital[P_WAVE_CONTROL2] > gtt_Dital_attribute[P_WAVE_CONTROL2].ss_Max)
                 {
                     gss_Select_dital[P_WAVE_CONTROL2] = gtt_Dital_attribute[P_WAVE_CONTROL2].ss_Max;
                 }
                 //íçÅFV34Ç÷ÇÃèëÇ´çûÇ›ÇÕpr_generator_memeber()Ç≈çsÇÌÇÍÇÈ
             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

             //<><><><><><><><><><><><><><><><><><><> ÉèÉCÉÑëóããë¨ìxí≤êÆ <><><><><><><><><><><><><><><><><><>
             if (guc_Analog_port[0][puc_Index] == IIF_ANALOG_WIACDC)
             {
                 PNORMAL     pNrm = &_union.Nrm;
                 //ëIëÇµÇΩìdà≥ê›íËÇ…ëŒÇ∑ÇÈåWêîÇÃåàíË
                 switch (InternalPackIif.Data.To.uc_Iif_volt_jumper)
                 {
                     case AD15V: //ÇPÇTÇuê›íËéû
                          pf_Coefficient = 5.7780;
                          pss_Ad_mid_value = AD15V_MID_VALUE;
                          break;
                     case AD12V: //ÇPÇQÇuê›íËéû
                          pf_Coefficient = 4.8792;
                          pss_Ad_mid_value = AD12V_MID_VALUE;
                          break;
                     case AD10V: //ÇPÇOÇuê›íËéû
                          pf_Coefficient = 4.1088;
                          pss_Ad_mid_value = AD10V_MID_VALUE;
                          break;
                     default:
                          break;
                 }
                 //ç≈èIílÇÃéZèo
                 pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value - gss_Iif_analog_shift[puc_Index]) * pf_Iif_analog_revise[puc_Index]; //2009.11.13
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value + pss_Iif_analog_revise[puc_Index]); //2009.11.11
                 //pf_Work = (float)((short)InternalPackIif.Data.To.us_Analog_data[puc_Index] - pss_Ad_mid_value); //2009.11.11 del
                 //pf_Work = pf_Work * pf_Iif_analog_revise[puc_Index]; //2009.11.11 del
                 //gss_Select_dital[P_WIRACDC] = (short)(pf_Work / pf_Coefficient);      //2009.11.12 del
                 gss_Select_dital[P_WIRACDC] = (short)(pf_Work / pf_Coefficient + 0.5);  //2009.11.12
                 //ç≈ëÂÅAç≈è¨É`ÉFÉbÉN
                 if (gss_Select_dital[P_WIRACDC] < gtt_Dital_attribute[P_WIRACDC].ss_Min)
                 {
                     gss_Select_dital[P_WIRACDC] = gtt_Dital_attribute[P_WIRACDC].ss_Min;
                 }
                 if (gss_Select_dital[P_WIRACDC] > gtt_Dital_attribute[P_WIRACDC].ss_Max)
                 {
                     gss_Select_dital[P_WIRACDC] = gtt_Dital_attribute[P_WIRACDC].ss_Max;
                 }
                 gsf_Acc3 = (float)gss_Select_dital[P_WIRACDC] * WIRACDC;
                 gss_Acc3 = (short)(gsf_Acc3);
             }
             //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

        }
    }

#endif 	// EXTERNAL IIF NEW	2011.02.21 by @Tny

return;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_input_iif_analog_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

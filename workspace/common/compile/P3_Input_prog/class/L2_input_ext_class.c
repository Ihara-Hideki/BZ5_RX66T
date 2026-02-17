//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚‰‚‚‚•‚”Q‚…‚˜‚”Q‚ƒ‚Œ‚‚“‚“
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚Q
//  y‹@”\à–¾z
//      ŠO•”“ü—Í
//  yˆø”z
//      ‚È‚µ
//  y–ß‚è’lz
//      ‚È‚µ
//  y”õlz
//      ‚È‚µ
//  yXV—š—ğz
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
#include "iodefine.h"
#include "devdrv_bsc.h"
#include "rza_io_regrw.h"

void input_ext_class(void)
{
     unsigned char puc_Chattering_check_no;

     int sts; //2007.3.9

     unsigned short pus_Rpm_work;//2007.3.15

     unsigned char  puc_Index;   //2008.09.01
     unsigned char  puc_Port_set_flag; //2008.09.09
     unsigned char  puc_Ext_select_sw; //2008.09.09
     unsigned char  puc_Iif_set_flag;  //2011.02.21 EXTERNAL IIF NEW


     /************************ ŠO•”“ü—Í{ƒƒ{ƒbƒg“ü—Í *************************/
     //ƒg[ƒ`ƒXƒCƒbƒ`“ü—Í

//----- Phase7 & Phase13 by @Tny 2008/09/10 -----
#if true
if(gtt_Dsw.Sw.No7 == false){ // DSW1-8‚ªOFF‚È‚ç‚ÎŠm”F
#endif
//--------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny 2011.03.02 del
	if((gb_IIF_Select == true)&&(gb_Iif_Input)){
	}
	else{
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
#define ASOTEST		0	//ASOTEST=1 ‚É‚ÄASG1Ú‘±ƒf[ƒ^‘—M‚É‚àŠO•”TS‚ª—LŒø‚Æ‚È‚éB
#if ASOTEST
     //if (/*ComuniPack.Data.bRS232Connection == false &&*/ ComuniPack.Data.bRS422Connection == false && gtt_Ctrl_flag.Ts_cancel == OFF) // ‚q‚r‚Q‚R‚Q‚ƒA‚q‚r‚S‚Q‚Q‰ñüØ’f
     //if (gtt_Ctrl_flag.Ts_cancel == OFF) // ‚r‚f‚P‚ÆŠO•”ƒg[ƒ`‚r‚v‚ğ“¯‚Ég—p‚·‚é‚½‚ßã‹Ls‚ğíœ‚µAC³‚µ‚½ 2007.12.19
#else
     //if (ComuniPack.Data.bRS232Connection == false && ComuniPack.Data.bRS422Connection == false && gtt_Ctrl_flag.Ts_cancel == OFF) // ‚q‚r‚Q‚R‚Q‚ƒA‚q‚r‚S‚Q‚Q‰ñüØ’f
     if (guc_Robot_connect_flag == false && gtt_Ctrl_flag.Ts_cancel == OFF) // 2008.10.03
#endif
     {
        puc_Chattering_check_no = EXT_TS_NO;
        //gtt_Ext_input.Data[puc_Chattering_check_no] = TS;
        gtt_Ext_input.Data[puc_Chattering_check_no] = (GPIO.PPR1 & 0x0001);
        chattering_check_member(puc_Chattering_check_no);
        if((gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)&&(gtt_Ctrl_flag.Stick_start == OFF))	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
        {
            gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = true;

            //ƒŠƒ‚ƒRƒ“Ä¶ƒ‚[ƒh‚Å‚ƒ‚ˆ‚Éƒf[ƒ^‚ª‚È‚¢ê‡A‚Ü‚½‚Í‚b‚g‘I‘ğ’†‚Ìê‡‚Í‚s‚r“ü—Í‚Í–³Œø 2009.03.30
            if (guc_Sequence_mode == IDLING) //2009.12.25 Ä¶‚ªŠm’è‚µ‚È‚¢ó‘Ô‚Å‚Í‚s‚r@‚n‚m‚Í‚Å‚«‚È‚¢B
            {
                if (gtt_Ctrl_flag.Remo_play_mode == ON && (gtt_Ctrl_flag.No_ch_data == ON || gtt_Ctrl_flag.Remo_play_ch_select == OFF))
                {
                    gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
                }
            }

            // *** 2008.07.30’Ç‰Á@ƒA[ƒNƒXƒ|ƒbƒg—p ***
            if (guc_Crater_mode_counter ==  SEQUENCE_ARC_SPOT) //2009.03.06
            //if (guc_Crater_mode_counter ==  SEQUENCE_NON && gss_Select_dital[P_ARC_SPOT_SET] == ON) //2008.10.21
            {
                if (gtt_Ctrl_flag.Arc_spot_time_up == true)
                {
		    gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
                }
            }
            // ****************************************
            //Œ»óƒe[ƒuƒ‹‚ª‚È‚¢‚Ì‚ÅAíœ 2009.01.28
            //if (guc_Remo_table_check_flag == false) //2008.03.03
            //{
	    //gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
	    //}
        } else {
            gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false; //‚o‚b’ÊMƒg[ƒ`‚r‚v‚ª‚‚e‚e‚Å‚«‚È‚¢‚Ì‚Å
                                                                                 //‰º‹Lƒg[ƒ`‚r‚v‚n‚e‚e‚ğˆê’èŠÔó‚¯æ‚ç‚È‚¢‚Æíœ‚µ
                                                                                 //–{s‚ğ•œŠˆ 2007.12.19
        //}
       // ************* ƒg[ƒ`‚r‚v‚‚†‚†‚ğˆê’èŠÔó‚¯æ‚ç‚È‚¢@2007.2.24 *************@2007.12.12“à•”‚ÉˆÚ“®
       //if (gtt_Ctrl_flag.Toch_sw_off_delay_time == ON)
       //{
       //    if (gtt_Ctrl_counter.Toch_sw_off_delay_time <= 0)
       //    {
       //        gtt_Ctrl_flag.Toch_sw_off_delay_time = OFF;
       //        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = OFF;
       //    } else {
       //        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw = ON;
       //    }
       // }
       // ***************************************************************************** 
            //*** 2008.07.30’Ç‰Á@ƒA[ƒNƒXƒ|ƒbƒg—p ***
            if (guc_Crater_mode_counter ==  SEQUENCE_ARC_SPOT) //2009.03.06
            //if (guc_Crater_mode_counter ==  SEQUENCE_NON && gss_Select_dital[P_ARC_SPOT_SET] == ON) //2008.10.21
            {
                gtt_Ctrl_flag.Arc_spot_time_up = false;
            }
            // ****************************************
       }
//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
         //<><> IIF INPUT 2008.10.03 <><>
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_TS)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = true;
                        // *** 2008.07.30’Ç‰Á@ƒA[ƒNƒXƒ|ƒbƒg—p ***
                        if (guc_Crater_mode_counter ==  SEQUENCE_ARC_SPOT)
                        {
                            if (gtt_Ctrl_flag.Arc_spot_time_up == true)
                            {
		                gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
                            }
                        }
                        // ****************************************
                        if (guc_Remo_table_check_flag == false) //2008.03.03
                        {
		            gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false;
	                }
                 } else {
                        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false; //‚o‚b’ÊMƒg[ƒ`‚r‚v‚ª‚‚e‚e‚Å‚«‚È‚¢‚Ì‚Å
                        if (guc_Crater_mode_counter ==  SEQUENCE_ARC_SPOT)
                        {
                            gtt_Ctrl_flag.Arc_spot_time_up = false;
                        }
                 }
             }
         }
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------
         //ƒXƒeƒBƒbƒNƒ`ƒFƒbƒN“ü—Í
//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
         //<><> IIF INPUT 2008.10.03 <><>
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  if (guc_In_port[0][puc_Index] == IIF_IN_STICK_CHECK_COMMAND) break;
             }
             if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
             {
                 gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = true;
             } else {
                 gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false;
             }
         }
//----- Phase26 by @Tny 2008/10/23 -----
#if true
        else{
            if(guc_Robot_connect_flag == false){ // ƒƒ{ƒbƒgÚ‘±ó‘Ô‚Å‚È‚¢H
                gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false;
            }
        }
#endif
#else	// EXTERNAL IIF NEW 2011.02.21 by @Tny
		if(guc_Robot_connect_flag == false){ // ƒƒ{ƒbƒgÚ‘±ó‘Ô‚Å‚È‚¢H
			gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false;
		}
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------
//--------------------------------------------
#if 1 //2009.12.18
     } else { //2009.12.15 ƒg[ƒ`ƒXƒCƒbƒ`“ü—ÍƒLƒƒƒ“ƒZƒ‹‚Ìˆ— ƒGƒ‰[‚P•œ‹AŒãƒKƒX‚ªˆêu‚n‚m‚·‚é‚Ì‚ğ–h‚®B
        if (gtt_Ctrl_flag.Ts_cancel == ON)
        {
            puc_Chattering_check_no = EXT_TS_NO;
            gtt_Ext_input.Data[puc_Chattering_check_no] = TS;
            chattering_check_member(puc_Chattering_check_no);
        }
#endif
     }
#if 0	// EXTERNAL IIF NEW 2010.09.17 by @Tny 2011.03.02 del
	}
#endif	// EXTERNAL IIF NEW 2010.09.17 by @Tny
}

     //ƒCƒ“ƒ`ƒ“ƒO‚r‚v“ü—Í
#if 0 //ƒn[ƒhƒEƒFƒA‚É‚æ‚éƒCƒ“ƒ`ƒ“ƒO‚Í–³‚­‚È‚Á‚½‚Ì‚Åíœ 2008.09.11
     if (ComuniPack.Data.bRS232Connection == false && ComuniPack.Data.bRS422Connection == false) // ‚q‚r‚Q‚R‚Q‚ƒA‚q‚r‚S‚Q‚Q‰ñüØ’f
     {
        puc_Chattering_check_no = EXT_INCHING_NO;
        gtt_Ext_input.Data[puc_Chattering_check_no] = INCHING;
        chattering_check_member(puc_Chattering_check_no);
        if (gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)
        {
            gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on     = ON;
	    gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect = OFF;
            
        } else {
            gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on     = OFF;
	    gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect = OFF;
        }

     }
#endif
//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
         //<><> IIF INPUT 2008.09.09 <><>
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  guc_Controller_inc_sw_cancel = OFF; //2008.10.06
                  if (guc_In_port[0][puc_Index] == IIF_IN_WIRE_CHECK)
                  {
                      puc_Port_set_flag = ON;
                      guc_Controller_inc_sw_cancel = ON; //2008.10.06
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                        guc_Inching_sw_flag = ON;
                 } else {
                        guc_Inching_sw_flag = OFF;
                 }
                 if (guc_Inching_sw_flag != guc_Inching_sw_flag_bkup)
                 {
                     guc_Inching_sw_flag_bkup = guc_Inching_sw_flag;
   	                 guc_Sw_rewrite_check_flag = 2; //•\¦‚ÌXV‚Ì‚½‚ß
                 }
             }
         }
     /*************************************************************************/
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------




     /************************* ŠO•”“ü—Í‚Ì‚İ‚Ì‚à‚Ì ****************************/
//#if 0 //2008.07.29ƒV[ƒPƒ“ƒXÀŒ±‚Ì‚½‚ßˆêíœ      Phase8(Debug) by 2008/09/12 @Tny @@@@@@@@@@@@@@@@@@@@@@@@@
#if 1 //2008.09.11ƒV[ƒPƒ“ƒXÀŒ±I—¹‚Ì‚½‚ß•œ‹A

     //ƒT[ƒ}ƒ‹“ü—Í
     puc_Chattering_check_no = EXT_THP_NO;
     gtt_Ext_input.Data[puc_Chattering_check_no] = THP;
     chattering_check_member(puc_Chattering_check_no);
     if (gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)
     {
//2006.11.28         gtt_Internal_pack.Data.In.Temp = true;
         gtt_Internal_pack.Data.In.Temp = false;
     } else {
//2006.11.28         gtt_Internal_pack.Data.In.Temp = false;
         gtt_Internal_pack.Data.In.Temp = true;
     }
#endif
     // **** 2008.07.29 ƒV[ƒPƒ“ƒXÀŒ±‚Ì‚½‚ß’Ç‰ÁiÀŒ±I—¹Œã‚Ííœ‚·‚é‚±‚Æj***
//----- Phase14(Debug) by @Tny 2008/09/19 ----- @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#if false
     puc_Chattering_check_no = EXT_THP_NO;
     gtt_Ext_input.Data[puc_Chattering_check_no] = THP;
     chattering_check_member(puc_Chattering_check_no);
     if (gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)
     {
         gtt_Ctrl_flag.Initial_arc_start = false;                    //‰Šú’Z—‚Å–{—nÚ‚Ö
     } else {
         gtt_Ctrl_flag.Initial_arc_start = true;                     //‰Šú’Z—‚Å–{—nÚ‚Ö
     }
#endif
     // ************************************************************************



     //”ñí’â~“ü—Í
     puc_Chattering_check_no = EXT_EMG_NO;
     gtt_Ext_input.Data[puc_Chattering_check_no] = EMG;
     chattering_check_member(puc_Chattering_check_no);
     if (gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)
     {
         //gtt_Internal_pack.Data.In.Emergency = true; //2007.1.17íœˆÚA
         gtt_Internal_pack.Data.In.Emergency = false; //2007.1.16˜_—‚ª‹t“]‚µ‚Ä‚¢‚½‚Ì‚ÅC³ 2007.1.17ˆÚA
     } else {
         //gtt_Internal_pack.Data.In.Emergency = false; //2007.1.17íœˆÚA
         gtt_Internal_pack.Data.In.Emergency = true;  //2007.1.16˜_—‚ª‹t“]‚µ‚Ä‚¢‚½‚Ì‚ÅC³ 2007.1.17ˆÚA
     }

//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
         //<><> IIF INPUT 2008.09.08 <><>
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  if (guc_In_port[0][puc_Index] == IIF_IN_EMERGENCY_STOP_ERR) break;
             }
//----- Phase25 by @Tny 2008/10/22 -----
#if true
            if(puc_Index <= 8){ // ‚h‚h‚e‚É“–ŠYM†‚ªİ’è‚³‚ê‚Ä‚¢‚½H
#endif
//--------------------------------------------
             if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
             {
                 gtt_Internal_pack.Data.In.Emergency = false;
             } else {
                 gtt_Internal_pack.Data.In.Emergency = true;
             }
//----- Phase25 by @Tny 2008/10/22 -----
#if true
            }
#endif
//--------------------------------------------
         }
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------


// Phase7(Debug) 2008/09/10 @Tny    @@@@@@@@@@@@@@@@@@@@
//
#if false


     //”ñí’â~‚Q“ü—Í 2007.2.9
     if (gtt_Ctrl_flag.Emg2_cancel == OFF) //2007.3.14 ‚o‚n”Å‚æ‚èˆÚA
     {
         puc_Chattering_check_no = EXT_EMG2_NO;
         gtt_Ext_input.Data[puc_Chattering_check_no] = EMG2;
         chattering_check_member(puc_Chattering_check_no);
         if (gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)
         {
             gtt_Internal_pack.Data.In.Emergency2 = false;
         } else {
             gtt_Internal_pack.Data.In.Emergency2 = true;
         }
     }


#endif


     //ˆê’â~‚P“ü—Í
     puc_Chattering_check_no = EXT_OUT_SIDE1_NO;
     gtt_Ext_input.Data[puc_Chattering_check_no] = OUT_SIDE1;
     chattering_check_member(puc_Chattering_check_no);
     if (gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)
     {
         //gtt_Internal_pack.Data.In.Outside1 = true; //2007.1.17íœˆÚA
         gtt_Internal_pack.Data.In.Outside1 = false;  //2007.1.16˜_—‚ª‹t“]‚µ‚Ä‚¢‚½‚Ì‚ÅC³ 2007.1.17ˆÚA
     } else {
         //gtt_Internal_pack.Data.In.Outside1 = false; //2007.1.17íœˆÚA
         gtt_Internal_pack.Data.In.Outside1 = true;   //2007.1.16˜_—‚ª‹t“]‚µ‚Ä‚¢‚½‚Ì‚ÅC³ 2007.1.17ˆÚA
     }

//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
         //<><> IIF INPUT 2008.09.01 <><>
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  if (guc_In_port[0][puc_Index] == IIF_IN_OUTSIDE_STOP1_ERR) break;
             }
//----- Phase25 by @Tny 2008/10/22 -----
#if true
            if(puc_Index <= 8){ // ‚h‚h‚e‚É“–ŠYM†‚ªİ’è‚³‚ê‚Ä‚¢‚½H
#endif
//--------------------------------------------
             if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
             {
                 gtt_Internal_pack.Data.In.Outside1 = false;
             } else {
                 gtt_Internal_pack.Data.In.Outside1 = true;
             }
//----- Phase25 by @Tny 2008/10/22 -----
#if true
            }
#endif
//--------------------------------------------
         }
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------

     //ˆê’â~‚Q“ü—Í
     puc_Chattering_check_no = EXT_OUT_SIDE2_NO;
     gtt_Ext_input.Data[puc_Chattering_check_no] = OUT_SIDE2;
     chattering_check_member(puc_Chattering_check_no);
     if (gtt_Ext_input.Flag[puc_Chattering_check_no] == ON)
     {
         //gtt_Internal_pack.Data.In.Outside2 = true; //2007.1.17íœˆÚA
         gtt_Internal_pack.Data.In.Outside2 = false;  //2007.1.16˜_—‚ª‹t“]‚µ‚Ä‚¢‚½‚Ì‚ÅC³ 2007.1.17ˆÚA
     } else {
         //gtt_Internal_pack.Data.In.Outside2 = false; //2007.1.17íœˆÚA
         gtt_Internal_pack.Data.In.Outside2 = true;   //2007.1.16˜_—‚ª‹t“]‚µ‚Ä‚¢‚½‚Ì‚ÅC³ 2007.1.17ˆÚA
     }

//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
         //<><> IIF INPUT 2008.09.01 <><>
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  if (guc_In_port[0][puc_Index] == IIF_IN_OUTSIDE_STOP2_ERR) break;
             }
//----- Phase25 by @Tny 2008/10/22 -----
#if true
            if(puc_Index <= 8){ // ‚h‚h‚e‚É“–ŠYM†‚ªİ’è‚³‚ê‚Ä‚¢‚½H
#endif
//--------------------------------------------
             if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
             {
                 gtt_Internal_pack.Data.In.Outside2 = false;
             } else {
                 gtt_Internal_pack.Data.In.Outside2 = true;
             }
//----- Phase25 by @Tny 2008/10/22 -----
#if true
            }
#endif
//--------------------------------------------
         }
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------

     
     //ƒKƒX‚n‚m–½—ß 2008.09.08
//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
         //<><> IIF INPUT 2008.09.09 <><>
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  guc_Controller_gas_sw_cancel = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_GAS_CHECK)
                  {
                      puc_Port_set_flag = ON;
                      guc_Controller_gas_sw_cancel = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                        if (guc_Gas_check_cancel_flag == false) //2008.10.06 ‚X‚O•b‚Ü‚½‚Íˆê’U—nÚó‘Ô‚É‚È‚Á‚½‚çˆê’UOFF‚É‚È‚é‚Ü‚Åó‚¯•t‚¯‚È‚¢B
                        {
                            guc_Gas_on_off_flag = ON;
                        }
                 } else {
                        guc_Gas_on_off_flag = OFF;
                        guc_Gas_check_cancel_flag = false; //2008.10.06 ƒXƒCƒbƒ`‚ªˆê’UOFF‚ÅÄ“xó•t
                 }
                 if (guc_Gas_on_off_flag != guc_Gas_on_off_flag_bkup)
                 {
                     guc_Gas_on_off_flag_bkup = guc_Gas_on_off_flag;
   	                 guc_Sw_rewrite_check_flag = 2; //•\¦‚ÌXV‚Ì‚½‚ß
                 }
             }
         }
     
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------

//--------------------------------------------------
#if 0	// EXTERNAL IIF NEW 2011.02.21 by @Tny
     // *************************************************************************
     // **************** ŠO•”‘I‘ğƒ†ƒjƒbƒgÚ‘±ˆ— 2008.09.09 ********************
         if((gb_IIF_Select == true)&&(gb_Iif_Input))    // Phase26 by @Tny 2008/10/23
         {
             //CNT
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_CNT)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                        gtt_Ctrl_flag.Ext_select_cnt = ON;
                        if (guc_Select_counter != MODE_PLAY)	// BP4 Phase6 by @Tny 2009/01/27
                        {
                            guc_Select_counter = MODE_PLAY;		// BP4 Phase6 by @Tny 2009/01/27
                        }
                        if (gtt_Ctrl_flag.Ext_select_init == OFF)
                        {
                            gtt_Ctrl_flag.Ext_select_init = ON;
                            gtt_Ctrl_flag.Ext_select_end  = OFF;
                            gtt_Ctrl_flag.Play = ON;
                            guc_Ch_no = 0;
                            guc_Ch_no_bkup = 0;
                        }
                 } else {
                        gtt_Ctrl_flag.Ext_select_init = OFF;
                        gtt_Ctrl_flag.Ext_select_cnt = OFF;
                        if (gtt_Ctrl_flag.Ext_select_end == OFF)
                        {
                            guc_Select_counter = MODE_WELDING;	// BP4 Phase6 by @Tny 2009/01/27
                            gtt_Ctrl_flag.Ext_select_end  = ON;
                        }
                 }
                 if (gtt_Ctrl_flag.Ext_select_cnt != gtt_Ctrl_flag.Ext_select_cnt_bkup)
                 {
                     gtt_Ctrl_flag.Ext_select_cnt_bkup = gtt_Ctrl_flag.Ext_select_cnt;
   	                 guc_Sw_rewrite_check_flag = 2; //•\¦‚ÌXV‚Ì‚½‚ß
                 }
             }
             //EXT1
             puc_Ext_select_sw = 0x00;
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_SW1)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x01;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xfe;
                 }
             }
             //EXT2
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_SW2)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x02;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xfd;
                 }
             }
             //EXT3
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_SW3)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x04;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xfb;
                 }
             }
             //EXT4
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_SW4)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x08;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xf7;
                 }
             }
             //EXT5
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_SW5)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x10;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xef;
                 }
             }
             //EXT6
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_SW6)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                       puc_Ext_select_sw = puc_Ext_select_sw | 0x20;
                 } else {
                       puc_Ext_select_sw = puc_Ext_select_sw & 0xdf;
                 }
             }
             //STB
             for (puc_Index = 1 ; puc_Index <= 8 ; puc_Index++)
             {
                  puc_Port_set_flag = OFF;
                  if (guc_In_port[0][puc_Index] == IIF_IN_EXT_SELECT_STB)
                  {
                      puc_Port_set_flag = ON;
                      break;
                  }
             }
             if (puc_Port_set_flag == ON)
             {
                 if (((guc_Iif_bit_input >> (puc_Index - 1)) & 0x01) == 0x01)
                 {
                       if (guc_Write_check_flag[puc_Ext_select_sw] == true)
                       {
                           guc_Ch_no = puc_Ext_select_sw;
//----- Phase22 by @Tny 2008/10/07 -----
#if true
                        if((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK)){
                    	    gus_Pre_display_timer = 500;
                        }
#endif
//--------------------------------------------
                       }
                 }
             }

         }
//----- Phase26 by @Tny 2008/10/23 -----
#if true
        else{
            gtt_Ctrl_flag.Ext_select_init   = OFF;
            gtt_Ctrl_flag.Ext_select_cnt    = OFF;
            if(gtt_Ctrl_flag.Ext_select_end == OFF){
                guc_Select_counter				= MODE_WELDING;	// BP4 Phase6 by @Tny 2009/01/27
                gtt_Ctrl_flag.Ext_select_end    = ON;
            }
        }
#endif
//--------------------------------------------
#endif	// EXTERNAL IIF NEW 2011.02.21 by @Tny
//--------------------------------------------------


     /*************************************************************************/

#if 0 //2019.04.02 del ihara
     // ************** ’Z—‰ñ”‚Ìæ“¾ 2007.3.2’Ç‰Á 2007.3.5ˆÚ“®*****************
            if (gtt_Fpga.Short_counter >= 100)
            {
               
                    sts = PushDI(); //2007.3.9
                    _hpiSetAddress( 0x00000198 );
                    gus_Imprudence_work = _hpiGet();
                    PopEI(sts);//2007.3.9

                    if (gus_Imprudence_bkup <= gus_Imprudence_work)
                    {
                        gtt_Internal_pack.Data.Out.ucImprudence = (unsigned char)(gus_Imprudence_work - gus_Imprudence_bkup);
                    } else {
                        gtt_Internal_pack.Data.Out.ucImprudence = (unsigned char)(gus_Imprudence_work + (0xffff - gus_Imprudence_bkup));
                    }

                gtt_Fpga.Short_counter = 0;
                gus_Imprudence_bkup = gus_Imprudence_work;
            }
     // ****************************************************************************

     // ************** ƒ‚[ƒ^‰ñ“]”‚Ìæ“¾ 2007.3.15’Ç‰Á ****************************
     if (gtt_Fpga.Rpm_counter >= 16)
     {
         sts = PushDI(); //2007.3.9
//           _hpiSetAddress( 0x00000229 );
         _hpiSetAddress( 0x0000027F );//2008.09.11 ƒ‚[ƒ^‰ñ“]”‘—óMƒAƒhƒŒƒX•ÏX
         pus_Rpm_work = _hpiGet();
         PopEI(sts);//2007.3.9
         gtt_Fpga.Rpm_avg_counter++;
         gul_Rpm_buff = gul_Rpm_buff + (unsigned long)pus_Rpm_work;
         
         if (gtt_Fpga.Rpm_avg_counter >= 30)
         {
             //gtt_Internal_pack.Data.Out.usMotorRPM2 = (unsigned short)((float)(gul_Rpm_buff / (unsigned long)gtt_Fpga.Rpm_avg_counter) * 0.651);
             gtt_Internal_pack.Data.Out.usMotorRPM2 = (unsigned short)((float)(gul_Rpm_buff / (unsigned long)gtt_Fpga.Rpm_avg_counter) * 0.0814 * 10.0); //2007.3.19 ŒW”•ÏX
             gtt_Fpga.Rpm_avg_counter = 0;
             gul_Rpm_buff = 0;
         }
         gtt_Fpga.Rpm_counter = 0;
     }
     // **************************************************************************
#endif
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_input_ext_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

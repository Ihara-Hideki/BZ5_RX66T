//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚…‚Q‚‡‚…‚‚…‚’‚‚”‚‚’Q‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      ‚d‚m”ä—¦‚ÌZo
//  yˆø”z
//      ‚È‚µ
//  y–ß‚è’lz
//      ‚È‚µ  
//  y”õlz
//      ‚È‚µ
//  yXV—š—ğz
//      2008.09.26  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
extern int DC_PMODE;
extern  CTLCLS      _ctlcls;
//extern WELDCODE DC_WELDCODE;
//extern  int         DC_PMODE;
void en_generator_member(unsigned short pus_Amp , unsigned char puc_En_no)
{
PCTLCLS     pCTL = &_ctlcls;
PENTBL      pENTBL; //2008.09.19
PA2STBL     pTBL; //2008.09.30

PNORMAL     pNrm = &_union.Nrm; //2008.11.11


//***** ‚d‚m”ä—¦ƒfƒtƒHƒ‹ƒgZo—p 2008.09.16 *****
signed short pss_En_duty_adjustment;
signed short pss_Wf_index_work; //2008.11.11
float        pf_Limit_work;     //2008.11.11
//***********************************************


    switch( DC_PMODE )
    {
        case 2://’Z—
            pTBL = &pWT->A2S_Short;
            pENTBL = pWT->pENTBL_Short;
            break;
        case 1://ƒpƒ‹ƒX
        default:
            pTBL = &pWT->A2S_Pulse;
            pENTBL = pWT->pENTBL_Pulse;
            break;
    }

    gss_WFe_Sirei_W = GetAmp2Wire( pus_Amp , pTBL );
    if( gss_WFe_Sirei_W < 0 )
        gss_WFe_Sirei_W = 0;
    else if( gss_WFe_Sirei_W > 25400 )  //2008.11.11
        gss_WFe_Sirei_W = 25400;        //2008.11.11
//  ¬”‘æ‚Q‚ğlÌŒÜ“ü‚µ‚Ä¬”‘æ‚P‚ÉŠÛ‚ß‚é
    pss_Wf_index_work = ( gss_WFe_Sirei_W + 50 ) / 200;       // ( 0.001+0.05 )¨ 0.1 m/min 2008.11.11
    
    //***** ‚d‚m”ä—¦ƒfƒtƒHƒ‹ƒg‚ÌZo 2008.09.19 *****
    //if (pCTL->WFe_Sirei_W > pENTBL->ENdef_Calc_Wf2) // Wf > JUDG2
    //if (pCTL->WFe_Sirei_W > pENTBL->ENdef_Calc_Wf2 || gtt_Ctrl_flag.AC_control == false) // Wf > JUDG2
    //if (gss_WFe_Sirei_W > pENTBL->ENdef_Calc_Wf2 || gtt_Ctrl_flag.AC_control == false) // Wf > JUDG2
    if (pENTBL->TEN_Data[ pss_Wf_index_work ] != 0)
    {
        gtt_En.ss_En_def = (signed short)((float)pENTBL->TEN_Data[ pss_Wf_index_work ] * 0.001 / (1.0 / (float)pENTBL->V13_Data[ pss_Wf_index_work ]));
        
        if (gtt_En.ss_En_def >= pENTBL->ENdef_Max)
        {
            gtt_En.ss_En_def = pENTBL->ENdef_Max;
        }
        if (gtt_En.ss_En_def < pENTBL->ENdef_Min)
        {
            gtt_En.ss_En_def = pENTBL->ENdef_Min;
        }
    } else {
        gtt_En.ss_En_def = 0;
    }

    //if (pENTBL->ENdef_Calc_Wf2 >= gss_WFe_Sirei_W && gtt_Ctrl_flag.AC_control == true)
    //if (gtt_Ctrl_flag.AC_control == true) //2008.11.11
    if (gtt_Ctrl_flag.AC_control == true || puc_En_no == EN_Q) //2008.11.28
    {
        switch (puc_En_no)
        {
            case EN_INIT:
                 pss_En_duty_adjustment = gtt_Ditail_work.ss_En_duty_init_adjustment;
                 break;
            case EN_MAIN:
                 pss_En_duty_adjustment = gtt_Ditail_work.ss_En_duty_main_adjustment;
                 break;
            case EN_CRATER:
                 pss_En_duty_adjustment = gtt_Ditail_work.ss_En_duty_crat_adjustment;
                 break;
            case EN_WAVE:  //2008.10.10
                 pss_En_duty_adjustment = gtt_Ditail_work.ss_En_duty_main_adjustment;
                 break;
            case EN_START: //2008.10.10
                 pss_En_duty_adjustment = gtt_Ditail_work.ss_En_duty_main_adjustment;
                 break;
            case EN_Q: //2008.11.28
                 pss_En_duty_adjustment = gtt_Ditail_work.ss_En_duty_qes_adjustment;
                 break;
                 
        }

        if (guc_Robot_connect_flag == true) //2008.10.03 ƒƒ{ƒbƒgÚ‘±‘Î‰
        {
            pss_En_duty_adjustment = gtt_Internal_pack.Data.In.ss_En_duty_adjustment;
        }
        if (pss_En_duty_adjustment >= pENTBL->EN1_Max_Limit)
        {
            pss_En_duty_adjustment = pENTBL->EN1_Max_Limit;
        }
        if (pss_En_duty_adjustment <= pENTBL->EN1_Min_Limit)
        {
            pss_En_duty_adjustment = pENTBL->EN1_Min_Limit;
        }
        if (gss_WFe_Sirei_W > pENTBL->EN1_Wf_Limit) // Wf > JUDG2
        {
            pss_En_duty_adjustment = 0;
        }

        gtt_En.ss_En_a = (sint)(gtt_En.ss_En_def + pss_En_duty_adjustment);
        if (gtt_En.ss_En_a >= pENTBL->ENa_Max)
        {
            gtt_En.ss_En_a = pENTBL->ENa_Max;
        }
      
        //*** 2008.12.11 ***
#if 0   //ŒW”‚ªŠÔ‚É‡‚í‚È‚¢‚Ì‚Åˆêíœ 2008.12.12
        if (gss_WFe_Sirei_W > (signed short)pENTBL->Wf_max_limit)
        {
            if (gtt_En.ss_En_a < (signed short)pENTBL->ENa_ac_limit)
            {
                gtt_En.ss_En_a = 0;
            }
        }
#endif
        //******************
        //*** 2009.01.08 ***
        if ((gss_WFe_Sirei_W >= (signed short)pENTBL->Wf_max_limit) || (gtt_En.ss_En_a < (signed short)pENTBL->ENa_ac_limit))
        {
          
           gtt_En.ss_En_a = 0;
          
        }
        //******************

        if (gtt_En.ss_En_a < pENTBL->ENa_Min)
        {
            gtt_En.ss_En_a = 0;
        }
    } else {
      //<><><>’¼—¬‹æŠÔˆ—iˆ—‚Pj<><><>
      gtt_En.ss_En_a = 0;
    }

    if (guc_Robot_connect_flag == true) //2008.11.28 ƒƒ{ƒbƒgÚ‘±‘Î‰
    { 
        if (puc_En_no == EN_Q) //ˆêŒ³“dˆ³–â‚¢‡‚í‚¹
        {
            if (gtt_Internal_pack.Data.In.uc_Q_En_0_mode == 0x01)
            {
               gtt_En.ss_En_a = 0;
            }
        } else {
            if (gtt_Internal_pack.Data.In.uc_En_0_mode == 0x01)
            {
               gtt_En.ss_En_a = 0;
            }
        }
    }

    //gtt_En.ss_AC_DCstart_Tim_Def = (pENTBL->AC_DCstart_Tim_Def / 10); //‚c‚b‹æŠÔ‚ÌƒfƒtƒHƒ‹ƒg’l 2008.10.14
    //gtt_En.ss_AC_DCstart_Tim_Max = (pENTBL->AC_DCstart_Tim_Max / 10); //‚c‚b‹æŠÔ”÷’²Å‘å’l     2008.10.14
    gtt_En.ss_AC_DCstart_Tim_Def = pENTBL->AC_DCstart_Tim_Def; //‚c‚b‹æŠÔ‚ÌƒfƒtƒHƒ‹ƒg’l 2008.10.14 2008.11.26 10->1ms‚É•ÏX
    gtt_En.ss_AC_DCstart_Tim_Max = pENTBL->AC_DCstart_Tim_Max; //‚c‚b‹æŠÔ”÷’²Å‘å’l     2008.10.14 2008.11.26 10->1ms‚É•ÏX
    //gtt_Dital_attribute[P_DC_CONTROL_TIME].ss_Max  = gtt_En.ss_AC_DCstart_Tim_Max;  //Ú×‚Ì‚c‚b‹æŠÔ”÷’²Å‘å’l‚ğƒe[ƒuƒ‹’l‚É•ÏX 2008.10.14
    //gtt_Dital_attribute[P_DC_CONTROL_TIME].ss_Max  = gtt_En.ss_AC_DCstart_Tim_Max / 10;  //2009.03.16 del

    //‚d‚m”ä—¦‚É‚æ‚éˆêŒ³“dˆ³’²®’l‚ÌZo OK
#if 0 //2008.12.16@Vd—l‚Ì‚½‚ßíœ
    if (gtt_En.ss_En_a >= 30) //EN‚ª‚R‚O“ˆÈã‚Ìê‡
    {
        gtt_En.sc_Va = gtt_Okcv.Okcv_real_p[pus_Amp / 2] * (gtt_En.ss_En_a - 30) / 20;
    }
    if (gtt_En.ss_En_a < 30 && gtt_En.ss_En_a > 0) //EN‚ª0%<ENa<30%
    {
        gtt_En.sc_Va = gtt_Okcv.Okcv_real_m[pus_Amp / 2] * (30 - gtt_En.ss_En_a) / 20;
    }
    if (gtt_En.ss_En_a == 0) //EN‚ª0%
    {
        gtt_En.sc_Va = gtt_Okcv.Okcv_real_0[pus_Amp / 2];
    }
#endif
    if (gtt_En.ss_En_a != 0) //2008.12.16 Vd—l
    {
        if (pss_En_duty_adjustment >= 0)
        {
            gtt_En.sc_Va = gtt_Okcv.Okcv_real_p[pus_Amp / 2] * pss_En_duty_adjustment / 20;
        } else {
            gtt_En.sc_Va = gtt_Okcv.Okcv_real_m[pus_Amp / 2] * (pss_En_duty_adjustment * -1) / 20; //2008.12.19â‘Î’l‚É•ÏX
        }
    } else {
        gtt_En.sc_Va = gtt_Okcv.Okcv_real_0[pus_Amp / 2];
    }


    switch (puc_En_no) //
    {
       case EN_INIT:
            gtt_En.ss_En_a_init   = gtt_En.ss_En_a;
            gtt_En.ss_En_def_init = gtt_En.ss_En_def; //2008.11.28
            gtt_En.sc_Va_init     = gtt_En.sc_Va;
            break;
       case EN_MAIN:
            gtt_En.ss_En_a_main   = gtt_En.ss_En_a;
            gtt_En.ss_En_def_main = gtt_En.ss_En_def; //2008.11.28
            gtt_En.sc_Va_main     = gtt_En.sc_Va;
            break;
       case EN_CRATER:
            gtt_En.ss_En_a_crater = gtt_En.ss_En_a;
            gtt_En.ss_En_def_crater = gtt_En.ss_En_def; //2008.11.28
            gtt_En.sc_Va_crater   = gtt_En.sc_Va;
       case EN_WAVE: //2008.10.10
            gtt_En.ss_En_a_wave   = gtt_En.ss_En_a;
            gtt_En.ss_En_def_wave = gtt_En.ss_En_def; //2008.11.28
            gtt_En.sc_Va_wave     = gtt_En.sc_Va;
            break;
       case EN_START://2008.10.10
            gtt_En.ss_En_a_start  = gtt_En.ss_En_a;
            gtt_En.ss_En_def_start = gtt_En.ss_En_def; //2008.11.28
            gtt_En.sc_Va_start    = gtt_En.sc_Va;
            break;
       case EN_Q:   //2008.11.28ˆêŒ³“dˆ³–â‚¢‡‚í‚¹—p
            gtt_En.ss_En_a_qes    = gtt_En.ss_En_a;
            gtt_En.sc_Va_qes      = gtt_En.sc_Va;
            break;
       default:
            break;
    }
    

}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_en_generator_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

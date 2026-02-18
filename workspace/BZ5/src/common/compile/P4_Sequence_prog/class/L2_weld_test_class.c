//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚—‚…‚Œ‚„Q‚”‚…‚“‚”Q‚ƒ‚Œ‚‚“‚“
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚Q
//  y‹@”\à–¾z
//      —nÚ{HÀŒ±g—p
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


extern unsigned char weld_hfix_abs_tbl;
extern unsigned char weld_hfix_rel_tbl;



PWELDTABLE      GetWeldTable( void );




void weld_test_class(void)
{
     unsigned int  index;
     unsigned long i;
     float         puf_V_data_work;
   
     unsigned int   *aa;
     float   *pp;

     int sts; //2007.3.9
               //************* DSP‚©‚ç‚R‚O‚O‚OŒÂ‚Ìƒf[ƒ^‚ğ‰ñû‚·‚é–½—ßˆ— **************
                //if (guc_Sequence_mode == MAIN_WELD) //2006.12.13 “c’†‚³‚ñ‚Ì—v¿‚Å—nÚ’†ˆÈŠO‚Å‚àƒf[ƒ^‚ª‰ñûo—ˆ‚é‚æ‚¤‚É‚·‚é
                //{
                    if (guc_Dsp_sampling_flag == ON)
                    {
                        guc_Dsp_sampling_flag = OFF;
                    //sts = PushDI(); //2007.3.9 2019.04.02 del ihara
	                _hpiSetAddress( 0x0000006D );
	                //_hpiPut((ushort)(0x0008));//DSP”gŒ`æ‚ğ’Z—‚É“¯Šú‚³‚¹‚é
	                _hpiPut((ushort)(0x0002));//DSP”gŒ`æ‚ğ’Z—‚É“¯Šú‚³‚¹‚é 2007.5.8•ÏX
                    //PopEI(sts);//2007.3.9 2019.04.02 del ihara
                    }
                //}
               //************************************************************************

               //****** ‚o‚b‚É‚c‚r‚o‚Ìƒf[ƒ^‚R‚O‚O‚OŒÂ‚ğ“]‘—‚·‚éˆ— 2006.2.22 **********
                if (guc_Dsp_pc_data_flag == ON)
                {
                   if (guc_A6_stop_flag == ON)
                   {
                       index = 0;
                       //sts = PushDI(); //2007.3.9 2007.3.19íœ
                       do {
		            if(timer_10ms > 1){
		               _hpiSetAddress( 0x00000D00 + index );
		               precurr = _hpiGet();
		               _hpiSetAddress( 0x00001900 + index );
		               currfb = _hpiGet();
		               _hpiSetAddress( 0x00002500 + index );
		               voltfb = _hpiGet();
		               _hpiSetAddress( 0x00003100 + index );
		               pwm = _hpiGet();
                               PC_Send_F5();
                               timer_10ms = 0;
                               index++;
                            }
                      } while (index < 3000);

                       index = 0;
#if 0
                       do {
		            if(timer_10ms > 1){
                            precurr = (unsigned int)Int_test[index];
                            index++;
		            currfb = (unsigned int)Int_test[index];
                            index++;
		            voltfb = (unsigned int)Int_test[index];
                            index++;
		            pwm = (unsigned int)Int_test[index];
                            index++;
                               PC_Send_F5();
                               timer_10ms = 0;
                            }
                      } while (index < 100);
#endif

                      //PopEI(sts);//2007.3.9 2007.3.19íœ
                      guc_A6_stop_flag = OFF;
                      guc_Dsp_pc_data_flag = OFF;
                  }
                }
                //************************************************************************

               //****** ‚o‚b‚É”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚ğ“]‘—‚·‚éˆ— 2008.06.03 **********
                if (guc_Half_pc_data_flag == ON)
                {
                   PPARMTBL    pTbl;
                   PNORMAL     pNrm = &_union.Nrm;
                   sint   *pAbs = (sint*)_union.Nrm.WeldParm_Abs;
                   pWT = GetWeldTable( );
                   if (guc_A6_stop_flag == ON)
                   {
                       index = 0;
                       do {
		            	if(timer_50ms > 1){
                           gus_Half_pc_data = _union.Nrm.WeldParm_Abs[index];
                           PC_Send_F6();
                           timer_50ms = 0;
                           index++;
                        }
                       } while (index < 378);
                       
                       guc_A6_stop_flag = OFF;
                       guc_Half_pc_data_flag = OFF;
                  }
                }
                //************************************************************************

                //********** ”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚Ì‚PA‚Q‚ğÅ‘å30ŒÂ‚o‚b‚©‚ç‘‚«Š·‚¦‚é ************
                if (guc_Dsp_write_flag == ON)
                {
                    PPARMTBL    pTbl;
                    PNORMAL     pNrm = &_union.Nrm;
                    sint   *pAbs = (sint*)_union.Nrm.WeldParm_Abs;
                    pWT = GetWeldTable( );
                    //IMJTICR4  = 0x07; //    
                    //xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_2LEN );
                    xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_3LEN );//2007.2.13•ÏX
#if 0
                    for (i = 1;i < 31; i++)
                    {
                         if (data_no[i] != 0)
                         {
                             _union.Nrm.WeldParm_Abs[data_no[i] - 1] = data[i];
                         }
                    }
#endif

                    for (i = 1;i < 379; i++)   //2007.1.24
                    {
                         if (data_no[i] == 0) break;

                          _union.Nrm.WeldParm_Abs[data_no[i] - 1] = data[i];
                    }



                    //hpiWrite( hpicmdOUTWLDADJST , (pusint)&pAbs[ 0 ] );  //”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‘—M 2019.04.02 del ihara
                    //hpiWrite( hpicmdOUTWLDADJST2, (pusint)&pAbs[ WLDADJST_1LEN ] );//”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚Q‘—M 2019.04.02 del ihara
#if 1
                    //hpiWrite( hpicmdOUTWLDADJST3, (pusint)&pAbs[ WLDADJST_2LEN ] );//”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚R‘—M 2007.2.13 ‚c‚r‚o‘¤–¢Š®¬‚Ì‚½‚ß“®ì‚³‚¹‚È‚¢B 2019.04.02 del ihara
#endif
                    //IMJTICR4  = 0x05; //
                    guc_Dsp_write_flag = OFF;

                    for (i = 1;i <379; i++)   //2007.1.24
                    {
                         data_no[i] = 0;
                    }

                }
                //************************************************************************

                //************** ‰Â•Ïƒpƒ‰ƒ[ƒ^‚ğÅ‘å24ŒÂ‚o‚b‚©‚ç‘‚«Š·‚¦‚é **************
                if (guc_V_dsp_write_flag == ON)
                {
                    PPARMTBL    pTbl;
                    PNORMAL     pNrm = &_union.Nrm;
                    pWT = GetWeldTable( );
                    //_ACC = 0;
                    //IMJTOCR4  = 0x07; //2006.2.15 Š„‹Ö@ihara    
                    xmemcpy( pNrm->CalParm , pWT->CalParm , sizeof( pWT->CalParm ) );
                    for (i = 1;i < 25; i++)
                    {
                         if (v_data_no[i] != 0)
                         {
                             _union.Nrm.CalParm[v_data_no[i] -1 ].min = (float)v_data[i];
                             _union.Nrm.CalParm[v_data_no[i] -1 ].max = (float)v_data[i];
                             //if (v_data_no[i] == 12 || v_data_no[i] == 52)
                             if (v_data_no[i] == 9 || v_data_no[i] == 12 || v_data_no[i] == 38 || v_data_no[i] == 52 || v_data_no[i] == 53) //V9,V38,V53’Ç‰Á@2006.3.23@ˆäŒ´
                             {
                                 puf_V_data_work = (float)v_data[i];
                                 _union.Nrm.CalParm[v_data_no[i] -1 ].min = puf_V_data_work / 100.0;
                                 _union.Nrm.CalParm[v_data_no[i] -1 ].max = puf_V_data_work / 100.0;
                             }
                         }
                    }
                    //IMJTOCR4  = 0x05; //2006.2.9 Š„‹–@ihara
                    guc_V_dsp_write_flag = OFF;
                }
                //************************************************************************

                //************ DSP‚Ì“Á’èƒAƒhƒŒƒX‚©‚çƒf[ƒ^‚ğ“Ç‚İ‚İPC‚Ö“]‘— *************
                if (guc_Dsp_read_flag == ON)
                {
                    //sts = PushDI(); //2007.3.9 2019.04.02 del ihara
                    gul_Dsp_address4 = gul_Dsp_address4 | gul_Dsp_address3 | gul_Dsp_address2 | gul_Dsp_address1;
                    _hpiSetAddress( gul_Dsp_address4 );
                    gui_Send_work = _hpiGet();    //20060213
                    PC_Send_E5( );                //DSPŒŸ¸—p@2006.2.16@ihara@2007.2.21íœ
                    //PopEI(sts);//2007.3.9 2019.04.02 del ihara
                    gul_Dsp_address4 = 0;
                    gul_Dsp_address3 = 0;
                    gul_Dsp_address2 = 0;
                    gul_Dsp_address1 = 0;
                    guc_Dsp_read_flag = OFF;
                }
                //************************************************************************

                //**************** DSP‚Ì“Á’èƒAƒhƒŒƒX‚Ö‚Ìƒf[ƒ^‚Ì‘‚«‚İ *****************
                if (guc_Dsp_one_write_flag == ON)
                {
                    gul_Dsp_write_address4 = gul_Dsp_write_address4 | gul_Dsp_write_address3 | gul_Dsp_write_address2 | gul_Dsp_write_address1;
                    gus_Dsp_write_data2    = gus_Dsp_write_data2 | gus_Dsp_write_data1;
                    //sts = PushDI(); //2007.3.9 2019.04.02 del ihara
                    _hpiSetAddress( gul_Dsp_write_address4 );
                    _hpiPut( gus_Dsp_write_data2 );
                    //PopEI(sts);//2007.3.9 2019.04.02 del ihara
                    gul_Dsp_write_address4 = 0;
                    gul_Dsp_write_address3 = 0;
                    gul_Dsp_write_address2 = 0;
                    gul_Dsp_write_address1 = 0;
                    gus_Dsp_write_data2    = 0;
                    gus_Dsp_write_data1    = 0;
                    guc_Dsp_one_write_flag = OFF;
                }
                //************************************************************************
              
                //************** ƒƒ{ƒbƒg‚©‚ç“Á’è‚Ì”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚ğ‘‚«Š·‚¦ ************
                //if (guc_Hfix_rewrite_check_flag == 2 && ComuniPack.Data.bRS422Connection)
                if (guc_Hfix_rewrite_check_flag == 2 && guc_Robot_connect_flag == true) //2008.10.03
                {
                    PNORMAL     pNrm = &_union.Nrm;
                    sint   *pAbs = (sint*)_union.Nrm.WeldParm_Abs;
                  if (gtt_Internal_rewrite_data.Hfix_no != 0)//2009.07.15 H”Ô†‚ª‚O‚Ì‚Í“®ì‚µ‚È‚¢
                  {
                    _union.Nrm.WeldParm_Abs[gtt_Internal_rewrite_data.Hfix_no - 1] = gtt_Internal_rewrite_data.Hfix_data;

                    //hpiWrite( hpicmdOUTWLDADJST , (pusint)&pAbs[ 0 ] );  //”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‘—M 2019.04.02 del ihara
                    //hpiWrite( hpicmdOUTWLDADJST2, (pusint)&pAbs[ WLDADJST_1LEN ] );//”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚Q‘—M 2019 04.02 del ihara
#if 1
                    //hpiWrite( hpicmdOUTWLDADJST3, (pusint)&pAbs[ WLDADJST_2LEN ] );//”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚R‘—M 2007.2.13 ‚c‚r‚o‘¤–¢Š®¬‚Ì‚½‚ß“®ì‚³‚¹‚È‚¢B 2019.04.02 del ihara
#endif
                  }
                    guc_Hfix_rewrite_check_flag = 0;
                }
                //************************************************************************

                //************** ƒƒ{ƒbƒg‚©‚ç“Á’è‚Ì‰Â•Ïƒpƒ‰ƒ[ƒ^‚ğ‘‚«Š·‚¦‚é ************
                //if (guc_Val_rewrite_check_flag0 == 2 && ComuniPack.Data.bRS422Connection)
                if (guc_Val_rewrite_check_flag0 == 2 && guc_Robot_connect_flag == true) //2008.10.03
                {

                    PNORMAL     pNrm = &_union.Nrm;

                  if (gtt_Internal_rewrite_data.Val_no0 != 0) //2009.07.15 ‚u”Ô†‚ª‚O‚Ì‚Í“®ì‚µ‚È‚¢
                  {
                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].a;
                    aa = &gtt_Internal_rewrite_data.Val_a_data0;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].b;
                    aa = &gtt_Internal_rewrite_data.Val_b_data0;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                    aa = &gtt_Internal_rewrite_data.Val_c_data0;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].min;
                    aa = &gtt_Internal_rewrite_data.Val_min_data0;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].max;
                    aa = &gtt_Internal_rewrite_data.Val_max_data0;
                    xmemcpy( pp , aa , 4);

                    //‰Á‘¬“x’²® 2007.2.6
                    switch (gtt_Internal_rewrite_data.Val_no0)
                    {
                       case 70:
                            gsf_Acc1 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            gss_Acc1 = (short)(gsf_Acc1 * 10.0);
                            break;
                       case 71:
                            //gsf_Acc2 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            //gss_Acc2 = (short)(gsf_Acc2 * 10.0);
                            gsf_Acc2 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            gss_Acc2 = (short)(gsf_Acc2); //2008.11.27•ÏX
                            break;
                       case 72:
                            //gsf_Acc3 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            //gss_Acc3 = (short)(gsf_Acc3 * 10.0);
                            gsf_Acc3 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            gss_Acc3 = (short)(gsf_Acc3); //2008.11.27•ÏX
                            break;
                       case 73:
                            gsf_Acc4 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            gss_Acc4 = (short)(gsf_Acc4 * 10.0);
                            break;
                       case 74:
                            gsf_Acc5 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            gss_Acc5 = (short)(gsf_Acc5 * 10.0);
                            break;
                       case 75:
                            gsf_Delay = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            gss_Delay = (short)gsf_Delay;
                            break;
                       case 76:
                            gsf_Re_start = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no0 -1 ].c;
                            gss_Re_start = (short)gsf_Re_start;
                            break;
                       default:
                            break;
                    }
                    gtt_Ctrl_flag.Hpi_control = true; //2008.11.29‰Â•Ïƒpƒ‰ƒ[ƒ^‚ğ‚g‚o‚h“]‘—‚·‚é
                  }
                    guc_Val_rewrite_check_flag0 = 0;
                }
                //if (guc_Val_rewrite_check_flag1 == 2 && ComuniPack.Data.bRS422Connection)
                if (guc_Val_rewrite_check_flag1 == 2 && guc_Robot_connect_flag == true) //2008.10.07
                {
                    PNORMAL     pNrm = &_union.Nrm;
                   
                  if (gtt_Internal_rewrite_data.Val_no1 != 0) //2009.07.15 ‚u”Ô†‚ª‚O‚Ì‚Í“®ì‚µ‚È‚¢
                  {
                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].a;
                    aa = &gtt_Internal_rewrite_data.Val_a_data1;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].b;
                    aa = &gtt_Internal_rewrite_data.Val_b_data1;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                    aa = &gtt_Internal_rewrite_data.Val_c_data1;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].min;
                    aa = &gtt_Internal_rewrite_data.Val_min_data1;
                    xmemcpy( pp , aa , 4);

                    pp = &_union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].max;
                    aa = &gtt_Internal_rewrite_data.Val_max_data1;
                    xmemcpy( pp , aa , 4);

                    //‰Á‘¬“x’²® 2007.2.6
                    switch (gtt_Internal_rewrite_data.Val_no1)
                    {
                       case 70:
                            gsf_Acc1 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            gss_Acc1 = (short)(gsf_Acc1 * 10.0);
                            break;
                       case 71:
                            //gsf_Acc2 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            //gss_Acc2 = (short)(gsf_Acc2 * 10.0);
                            gsf_Acc2 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            gss_Acc2 = (short)(gsf_Acc2); //2008.11.27•ÏX
                            break;
                       case 72:
                            //gsf_Acc3 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            //gss_Acc3 = (short)(gsf_Acc3 * 10.0);
                            gsf_Acc3 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            gss_Acc3 = (short)(gsf_Acc3); //2008.11.27•ÏX
                            break;
                       case 73:
                            gsf_Acc4 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            gss_Acc4 = (short)(gsf_Acc4 * 10.0);
                            break;
                       case 74:
                            gsf_Acc5 = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            gss_Acc5 = (short)(gsf_Acc5 * 10.0);
                            break;
                       case 75:
                            gsf_Delay = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            gss_Delay = (short)gsf_Delay;
                            break;
                       case 76:
                            gsf_Re_start = _union.Nrm.CalParm[gtt_Internal_rewrite_data.Val_no1 -1 ].c;
                            gss_Re_start = (short)gsf_Re_start;
                            break;
                       default:
                            break;
                    }

                    gtt_Ctrl_flag.Hpi_control = true; //2008.11.29‰Â•Ïƒpƒ‰ƒ[ƒ^‚ğ‚g‚o‚h“]‘—‚·‚é
                  }
                    guc_Val_rewrite_check_flag1 = 0;
                }
                //************************************************************************
                
                //******************** ”¼ŒÅ’èA‰Â•Ïƒf[ƒ^‚ğƒŠƒZƒbƒg‚·‚é ******************
                if (guc_Hfix_val_reset_flag == ON)     // ”¼ŒÅ’èA‰Â•Ïƒf[ƒ^ƒŠƒZƒbƒg
                {
                    PPARMTBL    pTbl;
                    PNORMAL     pNrm = &_union.Nrm;
                    sint   *pAbs = (sint*)_union.Nrm.WeldParm_Abs;
                    pWT = GetWeldTable( );
        
                    //”¼ŒÅ’èƒpƒ‰ƒ[ƒ^ƒŠƒZƒbƒg
                    //xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_2LEN );
                    xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_3LEN ); //2007.2.13•ÏX
                    //hpiWrite( hpicmdOUTWLDADJST , (pusint)&pAbs[ 0 ] );  //”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‘—M 2019.04.02 del ihara
                    //hpiWrite( hpicmdOUTWLDADJST2, (pusint)&pAbs[ WLDADJST_1LEN ] );//”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚Q‘—M 2019.04.02 del ihara
#if 1
                    //hpiWrite( hpicmdOUTWLDADJST3, (pusint)&pAbs[ WLDADJST_2LEN ] );//”¼ŒÅ’èƒpƒ‰ƒ[ƒ^‚R‘—M 2007.2.13 ‚c‚r‚o‘¤–¢Š®¬‚Ì‚½‚ß“®ì‚³‚¹‚È‚¢B 2019.04.02 del ihara
#endif

                    //‰Â•Ïƒpƒ‰ƒ[ƒ^ƒŠƒZƒbƒg
                    xmemcpy( pNrm->CalParm , pWT->CalParm , sizeof( pWT->CalParm ) );

                    guc_Hfix_val_reset_flag = OFF;
                }
                //************************************************************************

                //************** PC‚©‚ç“Á’è‚Ì‰Â•Ïƒpƒ‰ƒ[ƒ^‚ğ‘‚«Š·‚¦‚é ************ 2007.1.26ˆÚA’Ç‰Á
                if (guc_PC_V_dsp_write_flag == ON)
                {
                    PNORMAL     pNrm = &_union.Nrm;

                    PC_v_data_a_result        = (PC_v_data_a4)        & 0x000000ff;
                    PC_v_data_a_result       |= (PC_v_data_a3 << 8)   & 0x0000ff00; 
                    PC_v_data_a_result       |= (PC_v_data_a2 << 16)  & 0x00ff0000; 
                    PC_v_data_a_result       |= (PC_v_data_a1 << 24)  & 0xff000000; 
                    pp = &_union.Nrm.CalParm[PC_v_data_no -1 ].a;
                    aa = &PC_v_data_a_result;
                    xmemcpy( pp , aa , 4);

                    PC_v_data_b_result        = (PC_v_data_b4)        & 0x000000ff;
                    PC_v_data_b_result       |= (PC_v_data_b3 << 8)   & 0x0000ff00; 
                    PC_v_data_b_result       |= (PC_v_data_b2 << 16)  & 0x00ff0000; 
                    PC_v_data_b_result       |= (PC_v_data_b1 << 24)  & 0xff000000; 
                    pp = &_union.Nrm.CalParm[PC_v_data_no -1 ].b;
                    aa = &PC_v_data_b_result;
                    xmemcpy( pp , aa , 4);

                    PC_v_data_c_result        = (PC_v_data_c4)        & 0x000000ff;
                    PC_v_data_c_result       |= (PC_v_data_c3 << 8)   & 0x0000ff00; 
                    PC_v_data_c_result       |= (PC_v_data_c2 << 16)  & 0x00ff0000; 
                    PC_v_data_c_result       |= (PC_v_data_c1 << 24)  & 0xff000000; 
                    pp = &_union.Nrm.CalParm[PC_v_data_no -1 ].c;
                    aa = &PC_v_data_c_result;
                    xmemcpy( pp , aa , 4);

                    PC_v_data_min_result        = (PC_v_data_min4)        & 0x000000ff;
                    PC_v_data_min_result       |= (PC_v_data_min3 << 8)   & 0x0000ff00; 
                    PC_v_data_min_result       |= (PC_v_data_min2 << 16)  & 0x00ff0000; 
                    PC_v_data_min_result       |= (PC_v_data_min1 << 24)  & 0xff000000; 
                    pp = &_union.Nrm.CalParm[PC_v_data_no -1 ].min;
                    aa = &PC_v_data_min_result;
                    xmemcpy( pp , aa , 4);

                    PC_v_data_max_result        = (PC_v_data_max4)        & 0x000000ff;
                    PC_v_data_max_result       |= (PC_v_data_max3 << 8)   & 0x0000ff00; 
                    PC_v_data_max_result       |= (PC_v_data_max2 << 16)  & 0x00ff0000; 
                    PC_v_data_max_result       |= (PC_v_data_max1 << 24)  & 0xff000000; 
                    pp = &_union.Nrm.CalParm[PC_v_data_no -1 ].max;
                    aa = &PC_v_data_max_result;
                    xmemcpy( pp , aa , 4);

                    guc_PC_V_dsp_write_flag = OFF;

                }
                //************************************************************************

                //****************** ‚O‚˜‚U‚XƒRƒ}ƒ“ƒh‚Ì‘‚«Š·‚¦ 2009.07.13 ***************
                if (guc_0x69_rewrite_check_flag1 == 2)
                {
                    PNORMAL     pNrm = &_union.Nrm;
                    //ƒpƒ‹ƒXü”g””½‰f i’¼Ú”½‰f‚·‚éj2009.07.13
                    _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;

                    //ƒpƒ‹ƒX•”½‰fi’¼Ú”½‰f‚·‚éj2009.07.13
                    _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;
                    

                    guc_0x69_rewrite_check_flag1 = 0;
                    gtt_Ctrl_flag.Hpi_control = true;

                }
                  



                //************************************************************************

                //****************** ”÷’²®€–Ú‚PC‚Q‚Ì‘‚«Š·‚¦ 2007.2.5 *****************
                //if (guc_Adj1_rewrite_check_flag == 2 || guc_Adj2_rewrite_check_flag == 2)
                //if (guc_Adj1_rewrite_check_flag == 2 || guc_Adj2_rewrite_check_flag == 2 || guc_Exd_adj1_rewrite_check_flag == 2 || guc_Exd_adj2_rewrite_check_flag == 2) //2008.10.07
                if (gtt_Ctrl_flag.Rob_pram_refresh == ON || guc_Adj1_rewrite_check_flag == 2 || guc_Adj2_rewrite_check_flag == 2 || guc_Exd_adj1_rewrite_check_flag == 2 || guc_Exd_adj2_rewrite_check_flag == 2) //2009.07.17
                {
                    PPARMTBL    pTbl;
                    PNORMAL     pNrm = &_union.Nrm;
                    sint   *pAbs = (sint*)_union.Nrm.WeldParm_Abs;
                    pWT = GetWeldTable( );
        
#if 0 //2009.07.23 test del

                    gtt_Ctrl_flag.Rob_pram_refresh = OFF; //2009.07.17

                    //”¼ŒÅ’èƒpƒ‰ƒ[ƒ^ƒŠƒZƒbƒg
                    //xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_2LEN );
                    xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_3LEN ); //2007.2.13•ÏX
                    //‰Â•Ïƒpƒ‰ƒ[ƒ^ƒŠƒZƒbƒg
                    xmemcpy( pNrm->CalParm , pWT->CalParm , sizeof( pWT->CalParm ) );

                    //–{ƒ\ƒtƒg‚Í‚f‚y‚S‚ğŒ³‚Éì¬ 2009.07.13
                    //‚h‚c@‚O‚˜‚O‚SC‚O‚˜‚O‚TC‚O‚˜‚O‚U‚Ì‚u”Ô†‚Í‘¼‚Ì•Ï”‚Æd‚È‚Á‚Ä‚¢‚é‚Ì‚ÅAíœ‚·‚éBi‚`‚y‚SC‚f‚y‚S‚Å‚Í‚à‚Æ‚à‚Æg—p‚µ‚È‚¢j

                    //<><><><><> Šeƒpƒ‰ƒ[ƒ^ÀŒø”½‰fˆ— 2009.06.29 <><><><><>
                    //‚h‚c@‚O‚˜‚O‚P ‚r‚o“d—¬
                     //_union.Nrm.CalParm[SP_I_NO -1 ].c       += gtt_Internal_pack.Data.In.Sp_current;    //‚r‚o“d—¬ 2009.07.08 del
                     _union.Nrm.CalParm[SP_I2_NO -1 ].c      += gtt_Internal_pack.Data.In.Sp_current;    //‚r‚o“d—¬ 2008.11.27’Ç‰Á

                    //‚h‚c@‚O‚˜‚O‚Q ‚r‚oŠÔ
                     _union.Nrm.CalParm[SP_T_NO -1 ].c       += gtt_Internal_pack.Data.In.Sp_time;       //‚r‚oŠÔ
                    
                    //‚h‚c@‚O‚˜‚O‚R ‚d‚k‚h
                     _union.Nrm.CalParm[ELI_NO -1 ].c        += gtt_Internal_pack.Data.In.Eli;           //‚d‚k‚h

                    //‚h‚c@‚O‚˜‚O‚S dô“dˆ³’l
                     //_union.Nrm.CalParm[MTS_V_NO -1 ].c      += gtt_Internal_pack.Data.In.Mts_v;         //dô“dˆ³’l 2009.07.07 del

                    //‚h‚c@‚O‚˜‚O‚T dô“dˆ³‚n‚mŠÔ
                     //_union.Nrm.CalParm[MTS_ONTIME_NO -1 ].c += gtt_Internal_pack.Data.In.Mts_ontime;    //dô“dˆ³‚n‚mŠÔ 2009.07.07 del
                    
                    //‚h‚c@‚O‚˜‚O‚U dô“dˆ³üŠú
                     //_union.Nrm.CalParm[MTS_CYCLE_NO -1 ].c  += gtt_Internal_pack.Data.In.Mts_cycle;     //dô“dˆ³üŠú 2009.07.07 del
                    
                    //‚h‚c@‚O‚˜‚O‚V ŠJn‚c‚bŠÔ
                    //gtt_Ditail_work.us_DC_control_timer      = gtt_Internal_pack.Data.In.Stdc_time;      //ŠJn‚c‚bŠÔ

                    //‚h‚c@‚O‚˜‚O‚W ƒzƒbƒg“dˆ³”÷’²®
		             //_union.Nrm.CalParm[HOTVLT_NO -1 ].c     += gtt_Internal_pack.Data.In.vVhotAdj;     // ƒzƒbƒg“dˆ³’²® 2009.07.08 del
		             _union.Nrm.CalParm[HOTVLT2_NO -1 ].c    += gtt_Internal_pack.Data.In.vVhotAdj;     // ƒzƒbƒg“dˆ³’²®
                    
                    //‚h‚c@‚O‚˜‚O‚X ‚e‚s‚sƒŒƒxƒ‹’²®
                    {
                                //signed short work;
                                //signed short work1;
                                signed int work;    //2009.07.10
                                signed int work1;   //2009.07.10
                                //H51 ‚e‚s‚sƒŒƒxƒ‹’²®
                                work  = _union.Nrm.WeldParm_Abs[FTTLVL_NO - 1];
                                work1 = work + gtt_Internal_pack.Data.In.vFttAdj;
                                if (work1 < 0x00DA)
                                {
                                    work1 = 0x00DA;
                                } else if (work1 > 0x6666) {
                                    work1 = 0x6666;
                                }
                                //_union.Nrm.WeldParm_Abs[FTTLVL_NO - 1]  = work1;
                                _union.Nrm.WeldParm_Abs[FTTLVL_NO - 1]  = (short)work1; //2009.07.10
                                //H92 ‚e‚s‚sƒŒƒxƒ‹’²®‚Q
                                work  = _union.Nrm.WeldParm_Abs[FTTLVL2_NO - 1];
                                work1 = work + gtt_Internal_pack.Data.In.vFttAdj;
                                if (work1 < 0x00DA)
                                {
                                    work1 = 0x00DA;
                                } else if (work1 > 0x6666) {
                                    work1 = 0x6666;
                                }
                                //_union.Nrm.WeldParm_Abs[FTTLVL2_NO - 1]  = work1;
                                _union.Nrm.WeldParm_Abs[FTTLVL2_NO - 1]  = (short)work1; //2009.07.10
                    }
                    
                    //‚h‚c@‚O‚˜‚O‚` ƒo[ƒ“ƒoƒbƒNŠÔ’²®
                    {
                                //signed short work;
                                //signed short work1;
                                signed int work;
                                signed int work1;
#if 0 //2009.07.08 del
                                //H61 ƒo[ƒ“ƒoƒbƒNŠÔ’²®
                                work  = _union.Nrm.WeldParm_Abs[BBKTIME_NO - 1];
                                work1 = work + gtt_Internal_pack.Data.In.vBarnBackAdj;
                                if (work1 < 0x0032)
                                {
                                    work1 = 0x0032;
                                } else if (work1 > 0x7530) {
                                    work1 = 0x7530;
                                }
                                _union.Nrm.WeldParm_Abs[BBKTIME_NO - 1] = work1;
#endif
                                //H105 ƒo[ƒ“ƒoƒbƒNŠÔ’²®‚Q
                                work  = _union.Nrm.WeldParm_Abs[BBKTIME2_NO - 1];
                                work1 = work + gtt_Internal_pack.Data.In.vBarnBackAdj;
                                if (work1 < 0x0032)
                                {
                                    work1 = 0x0032;
                                } else if (work1 > 0x7530) {
                                    work1 = 0x7530;
                                }
                                //_union.Nrm.WeldParm_Abs[BBKTIME2_NO - 1] = work1;
                                _union.Nrm.WeldParm_Abs[BBKTIME2_NO - 1] = (short)work1; //2009.07.10
                                //H10 ƒo[ƒ“ƒoƒbƒNŠÔ’²®‚R
                                work  = _union.Nrm.WeldParm_Abs[BBKTIME3_NO - 1];
                                work1 = work + gtt_Internal_pack.Data.In.vBarnBackAdj;
                                if (work1 < 0x0032)
                                {
                                    work1 = 0x0032;
                                } else if (work1 > 0x7530) {
                                    work1 = 0x7530;
                                }
                                //_union.Nrm.WeldParm_Abs[BBKTIME3_NO - 1] = work1;
                                _union.Nrm.WeldParm_Abs[BBKTIME3_NO - 1] = (short)work1; //2009.07.10
                    }

                    //‚h‚c@‚O‚˜‚O‚a ƒƒCƒ„ƒXƒ[ƒ_ƒEƒ“’²®
                    gss_Adj_slow_down = gtt_Internal_pack.Data.In.vSldnAdj;

                    //‚h‚c@‚O‚˜‚O‚b ‚h‚r‚k‚P’²®
                      // V32 ‚h‚r‚k‚P’²®
                    //_union.Nrm.CalParm[WAVE_CONTROL1_NO - 1].c   += gtt_Internal_pack.Data.In.vIsl1Adj; //2009.07.08 del
                      // V45 ‚h‚r‚k‚P’²®‚Q
                    _union.Nrm.CalParm[WAVE_CONTROL1_2_NO - 1].c += gtt_Internal_pack.Data.In.vIsl1Adj;
                    
                    //‚h‚c@‚O‚˜‚O‚c ‚h‚r‚k‚Q’²®
                    _union.Nrm.CalParm[ISL2_NO -1 ].c           += gtt_Internal_pack.Data.In.vIsl2Adj;// ’Z—“d—¬Œù”z‚Q’²®
                    
                    //‚h‚c@‚O‚˜‚O‚d ‚h‚`‚b’²®
                     _union.Nrm.CalParm[92 - 1].c                += gtt_Internal_pack.Data.In.vIacAdj;
                    
                    //‚h‚c@‚O‚˜‚O‚e ‚h‚r‚b’²®
                    _union.Nrm.CalParm[ISC_NO - 1].c             += gtt_Internal_pack.Data.In.vIscAdj;
                    
                    //‚h‚c@‚O‚˜‚P‚O ‚h‚o’²®
                    if (guc_Pulse_mode_data == 0x03 || guc_Pulse_mode_data == 0x05)
                    {
                        _union.Nrm.CalParm[PULSE_PEAK_CUR_NO - 1].c += gtt_Internal_pack.Data.In.vIpAdj;
                    }

                    //‚h‚c@‚O‚˜‚P‚P ‚h‚a’²®
                    if (guc_Pulse_mode_data == 0x03 || guc_Pulse_mode_data == 0x05)
                    {
                        _union.Nrm.CalParm[PULSE_BASE_CUR_NO - 1].c += gtt_Internal_pack.Data.In.vIb1Adj;
                    }

                    //‚h‚c@‚O‚˜‚P‚Q –³Œø
                    
                    //‚h‚c@‚O‚˜‚P‚R ƒpƒ‹ƒXƒs[ƒN—§‚¿ã‚ª‚è”÷’²®
                    _union.Nrm.CalParm[PRISE_NO - 1].c              += gtt_Internal_pack.Data.In.vIprAdj;
                    
                    //‚h‚c@‚O‚˜‚P‚S ƒpƒ‹ƒXƒs[ƒN—§‚¿‰º‚ª‚è”÷’²®
                    _union.Nrm.CalParm[PFALL_NO - 1].c              += gtt_Internal_pack.Data.In.vIpfAdj;
                    
                    //‚h‚c@‚O‚˜‚P‚T ƒXƒ^[ƒgƒs[ƒN“d—¬”÷’²®
                    //_union.Nrm.WeldParm_Abs[INIT_IP_NO - 1]         += gtt_Internal_pack.Data.In.vIniIpAdj;
                                     { //2009.07.03
                                       //signed short work;
                                       //signed short work1;
                                       signed int work;        //2009.07.10
                                       signed int work1;       //2009.07.10
                                       work  = pWT->WeldParm.Parm[INIT_IP_NO -1];
                                       work1 = work + gtt_Internal_pack.Data.In.vIniIpAdj;
                                       if (work1 < 0x01b4)
                                       {
                                           work1 = 0x01b4;
                                       } else if (work1 > 0x6666) {
                                           work1 = 0x6666;
                                       }
                                       //_union.Nrm.WeldParm_Abs[INIT_IP_NO - 1] = work1;
                                       _union.Nrm.WeldParm_Abs[INIT_IP_NO - 1] = (short)work1; //2009.07.10
                                     }
                    //‚h‚c@‚O‚˜‚P‚U ƒXƒ^[ƒgƒx[ƒX“d—¬”÷’²®
                    //_union.Nrm.WeldParm_Abs[INIT_IB_NO - 1]         += gtt_Internal_pack.Data.In.vIniIbAdj;
                                     { //2009.07.03
                                       //signed short work;
                                       //signed short work1;
                                       signed int work;        //2009.07.10
                                       signed int work1;       //2009.07.10
                                       work  = pWT->WeldParm.Parm[INIT_IB_NO -1];
                                       work1 = work + gtt_Internal_pack.Data.In.vIniIbAdj;
                                       if (work1 < 0x01b4)
                                       {
                                           work1 = 0x01b4;
                                       } else if (work1 > 0x6666) {
                                           work1 = 0x6666;
                                       }
                                       //_union.Nrm.WeldParm_Abs[INIT_IB_NO - 1] = work1;
                                       _union.Nrm.WeldParm_Abs[INIT_IB_NO - 1] = (short)work1; //2009.07.10
                                     }
                    //‚h‚c@‚O‚˜‚P‚V ƒpƒ‹ƒX‘æ‚Qƒx[ƒX“d—¬”÷’²®
                    //_union.Nrm.CalParm[PULSE_BASE_CUR2_NO - 1].c    += gtt_Internal_pack.Data.In.vIb2Adj; // del 2009.07.14
                    
                    //‚h‚c@‚O‚˜‚P‚W ƒpƒ‹ƒX—§‚¿ã‚ª‚èŠÔ”÷’²®
                    _union.Nrm.CalParm[PULSE_RISE_CUR_NO - 1].c     += gtt_Internal_pack.Data.In.vTiprAdj;

                    //‚h‚c@‚O‚˜‚P‚X ƒpƒ‹ƒX—§‚¿‰º‚ª‚èŠÔ”÷’²®
                    _union.Nrm.CalParm[PULSE_FALL_CUR_NO - 1].c     += gtt_Internal_pack.Data.In.vTipfAdj;
                    
                    //‚h‚c@‚O‚˜‚P‚` ƒpƒ‹ƒXƒs[ƒN—§‚¿ã‚ª‚èŠÔ”÷’²®
                    if (guc_Pulse_mode_data == 0x03 || guc_Pulse_mode_data == 0x05)
                    {
                        _union.Nrm.CalParm[PULSE_WIDTH_NO - 1].c += gtt_Internal_pack.Data.In.vTipAdj;
                    }
                    
                    //‚h‚c@‚O‚˜‚P‚a ’Z—‰ŠúŠÔ’²®
                    _union.Nrm.CalParm[PENETRATION_NO - 1].c         += gtt_Internal_pack.Data.In.vTsoAdj;

                    //‚h‚c@‚O‚˜‚P‚b ƒzƒbƒg“d—¬’²®
                    {
                             //signed short work;
                             //signed short work1;
                             unsigned int work; //2009.07.09
                             unsigned int work1; //2009.07.09
                             //H36
                             work  = pWT->WeldParm.Parm[HOTCUR_NO -1];
                             work1 = work + gtt_Internal_pack.Data.In.vIhotAdj;
                             if (work1 < 0x1111)
                             {
                                 work1 = 0x1111;
                             } else if (work1 > 0x6666) {
                                 work1 = 0x6666;
                             }
                             //_union.Nrm.WeldParm_Abs[HOTCUR_NO - 1] = work1;
                             _union.Nrm.WeldParm_Abs[HOTCUR_NO - 1] = (short)work1; //2009.07.09
                    }

                    //‚h‚c@‚O‚˜‚P‚c ƒzƒbƒgƒ^ƒCƒ€’²®
                    {
                             //signed short work;
                             //signed short work1;
                             signed int work;       //2009.07.10
                             signed int work1;      //2009.07.10
                             //H38
#if 0 //2009.07.08 del
                             work  = pWT->WeldParm.Parm[HOTTM_NO -1];
                             work1 = work + gtt_Internal_pack.Data.In.vHotTime * HOTTM;
                             if (work1 < 0x0032)
                             {
                                 work1 = 0x0032;
                             } else if (work1 > 0x1388) {
                                 work1 = 0x1388;
                             }
                             _union.Nrm.WeldParm_Abs[HOTTM_NO - 1] = work1;
#endif
                             //H83
                             work  = pWT->WeldParm.Parm[HOTTM2_NO -1];
                             work1 = work + gtt_Internal_pack.Data.In.vHotTime * HOTTM2;
                             if (work1 < 0x0032)
                             {
                                 work1 = 0x0032;
                             } else if (work1 > 0x1388) {
                                 work1 = 0x1388;
                             }
                             //_union.Nrm.WeldParm_Abs[HOTTM2_NO - 1] = work1;
                             _union.Nrm.WeldParm_Abs[HOTTM2_NO - 1] = (short)work1; //2009.07.10
                    }

                    //‚h‚c@‚O‚˜‚P‚d ƒA[ƒNƒXƒ^[ƒg‚Éƒpƒ‹ƒXˆó‰Á‚Ì‚n‚m^‚n‚e‚e‚ğ‘I‘ğ‚·‚é
                    if (gtt_Internal_pack.Data.In.vStartPulse == 0)
                    {
                        _union.Nrm.WeldParm_Abs[STARTPLS_NO - 1] = 0;
                    }
                    if (gtt_Internal_pack.Data.In.vStartPulse == 1)
                    {
                        _union.Nrm.WeldParm_Abs[STARTPLS_NO - 1] = 1;
                    }
                    if (gtt_Internal_pack.Data.In.vStartPulse == 2) //2009.07.10
                    {
                         _union.Nrm.WeldParm_Abs[STARTPLS_NO - 1] = (unsigned char)pWT->WeldParm.Parm[STARTPLS_NO -1];
                    }
                    if (guc_Method_condition_data == 0x01 && guc_Pulse_mode_data == 0x03) //ƒpƒ‹ƒX–³‚µ‚b‚n‚Q‚Ìê‡
                    {
                        _union.Nrm.WeldParm_Abs[STARTPLS_NO - 1] = 0;
                    }
                    if ((guc_Method_condition_data == 0x02 || guc_Method_condition_data == 0x03) && (guc_Pulse_mode_data == 0x05 || guc_Pulse_mode_data == 0x85)) //ƒpƒ‹ƒX—L‚è‚l‚`‚f^‚l‚h‚f
                    {
                        _union.Nrm.WeldParm_Abs[STARTPLS_NO - 1] = 1;
                    }

                    //‚h‚c@‚O‚˜‚P‚e ƒA[ƒNƒGƒ“ƒh‚Ìƒpƒ‹ƒX‚ ‚è‚È‚µ‘I‘ğ
                    if (gtt_Internal_pack.Data.In.vEndPulse == 0)
                    {
                        _union.Nrm.WeldParm_Abs[ENDPLS_NO - 1] = 0;
                        _union.Nrm.WeldParm_Abs[ENDPLS2_NO - 1] = 0;
                    }
                    if (gtt_Internal_pack.Data.In.vEndPulse == 1)
                    {
                        _union.Nrm.WeldParm_Abs[ENDPLS_NO - 1] = 1;
                        _union.Nrm.WeldParm_Abs[ENDPLS2_NO - 1] = 1;
                    }
                    if (gtt_Internal_pack.Data.In.vEndPulse == 2) //2009.07.10
                    {
                        _union.Nrm.WeldParm_Abs[ENDPLS_NO - 1] = (unsigned char)pWT->WeldParm.Parm[ENDPLS_NO -1];
                        _union.Nrm.WeldParm_Abs[ENDPLS2_NO - 1] = (unsigned char)pWT->WeldParm.Parm[ENDPLS2_NO -1];
                    }
                    if (guc_Method_condition_data == 0x01 && guc_Pulse_mode_data == 0x03) //ƒpƒ‹ƒX–³‚µ‚b‚n‚Q‚Ìê‡
                    {
                         _union.Nrm.WeldParm_Abs[ENDPLS_NO - 1] = 0;
                         _union.Nrm.WeldParm_Abs[ENDPLS2_NO - 1] = 0;
                    }
                    
                    //‚h‚c@‚O‚˜‚Q‚O ƒA[ƒNƒXƒ^[ƒg‚Ìƒpƒ‹ƒXü”g”‚ğ’²®
                    //_union.Nrm.WeldParm_Abs[INIT_PFRQ3_NO - 1] += gtt_Internal_pack.Data.In.vIniPulseFreqAdj;
#if 0 //del 2009.07.14
                                     { //2009.07.03
                                       //signed short work;
                                       //signed short work1;
                                       signed int work;      //2009.07.10
                                       signed int work1;     //2009.07.10
                                       work  = pWT->WeldParm.Parm[INIT_PFRQ3_NO -1];
                                       work1 = work + gtt_Internal_pack.Data.In.vIniPulseFreqAdj;
                                       if (work1 < 0x000A)
                                       {
                                           work1 = 0x000A;
                                       } else if (work1 > 0x03e8) {
                                           work1 = 0x03e8;
                                       }
                                       //_union.Nrm.WeldParm_Abs[INIT_PFRQ3_NO - 1] = work1;
                                       _union.Nrm.WeldParm_Abs[INIT_PFRQ3_NO - 1] = (short)work1; //2009.07.10
                                     }
#endif
                    //‚h‚c@‚O‚˜‚Q‚P ƒpƒ‹ƒX—nÚ‚ÌƒA[ƒNƒuƒ[—}§§Œä
                    {
                             //signed short work;
                             //signed short work1;
                             signed int work;    //2009.07.10
                             signed int work1;   //2009.07.10
                             //H132
                             work  = pWT->WeldParm.Parm[PCTRLBLOW_NO -1];
                             work1 = (work * gtt_Internal_pack.Data.In.vPctrlBlowAdj) / 10;
                             if (work1 <= 0x0000)
                             {
                                 work1 = 0x0000;
                             } else if (work1 >= 0x7FFF) {
                                 work1 = 0x7FFF;
                             }
                             //_union.Nrm.WeldParm_Abs[PCTRLBLOW_NO - 1] = work1;
                             _union.Nrm.WeldParm_Abs[PCTRLBLOW_NO - 1] = (short)work1; //2009.07.10
                    }
                    
                    //‚h‚c@‚O‚˜‚Q‚Q ‘—‹‹—Ê’²®
                    //WireSpd_Offset = gtt_Internal_pack.Data.In.vWirSpdAdj; //del 2009.07.14
                    
                    //‚h‚c@‚O‚˜‚Q‚R ƒXƒ^[ƒgƒXƒ[ƒv”÷’²®
#if 0 //del 2009.07.14
                    gsf_Acc2 = gtt_Internal_pack.Data.In.vWirSpdAdj;
                    gss_Acc2 = (short)(gsf_Acc2);
#endif

                    //‚h‚c@‚O‚˜‚Q‚S ƒXƒ^[ƒgƒ^ƒCƒ€
                    gsf_Delay = gtt_Internal_pack.Data.In.vWirStrDelayAdj;
                    gss_Delay = (short)gsf_Delay;
                    
                    //‚h‚c@‚O‚˜‚Q‚T ƒlƒbƒNŒŸo‚n‚m^‚n‚e‚e‚ÆƒŒƒxƒ‹’²®
                    //‰Â•Ï
#if 0 //2009.07.08 del
                    _union.Nrm.CalParm[NECKLVL_NO - 1].c = pWT->CalParm[NECKLVL_NO -1].c;
                    _union.Nrm.CalParm[NECKLVL_NO - 1].c += (float)gtt_Internal_pack.Data.In.vNeckLvlAdj * NECKLVL;
#endif
                    //”¼ŒÅ’è
                    {
                            //signed short work;
                            //signed short work1;
                            signed int work;     //2009.07.10
                            signed int work1;    //2009.07.10
                            //H166
                            work  = pWT->WeldParm.Parm[NECKLVL2_NO -1];
                            work1 = work + (signed short)(gtt_Internal_pack.Data.In.vNeckLvlAdj * NECKLVL2);
                            if (work1 < 0x0034)
                            {
                                work1 = 0x0034;
                            } else if (work1 > 0x7AE1) {
                                work1 = 0x7AE1;
                            }
                            //_union.Nrm.WeldParm_Abs[NECKLVL2_NO - 1] = work1;
                            _union.Nrm.WeldParm_Abs[NECKLVL2_NO - 1] = (short)work1; //2009.07.10
                    }

                    //‚h‚c@‚O‚˜‚Q‚U
#if 0 //del 2009.07.14
                    gsf_Acc3 = gtt_Internal_pack.Data.In.vWirAcDcAdj;
                    gss_Acc3 = (short)(gsf_Acc3);
#endif
                    
                    //‚h‚c@‚O‚˜‚Q‚V ƒo[ƒ“ƒoƒbƒNƒpƒ‹ƒX
#if 0 //del 2009.07.14
                    {
                             //signed short work;
                             //signed short work1;
                             signed int work;    //2009.07.10
                             signed int work1;   //2009.07.10
                             //H104
                             work  = pWT->WeldParm.Parm[BBK_PULSE_NO -1];
                             work1 = work + gtt_Internal_pack.Data.In.vBbkPulseAdj;
                             if (work1 < 0x0000)
                             {
                                 work1 = 0x0000;
                             } else if (work1 > 0x000A) {
                                 work1 = 0x000A;
                             }
                             //_union.Nrm.WeldParm_Abs[BBK_PULSE_NO - 1] = work1;
                             _union.Nrm.WeldParm_Abs[BBK_PULSE_NO - 1] = (short)work1; //2009.07.10
                    }
                    {
                             //signed short work;
                             //signed short work1;
                             signed int work;          //2009.07.10
                             signed int work1;         //2009.07.10
                             //H60
                             work  = pWT->WeldParm.Parm[BBK_PULSE2_NO -1];
                             work1 = work + gtt_Internal_pack.Data.In.vBbkPulseAdj;
                             if (work1 < 0x0000)
                             {
                                 work1 = 0x0000;
                             } else if (work1 > 0x000A) {
                                 work1 = 0x000A;
                             }
                             //_union.Nrm.WeldParm_Abs[BBK_PULSE2_NO - 1] = work1;
                             _union.Nrm.WeldParm_Abs[BBK_PULSE2_NO - 1] = (short)work1; //2009.07.10
                    }
#endif

                    //‚h‚c@‚O‚˜‚Q‚W Œğ—¬ü”g” 2009.07.14
                    //_union.Nrm.CalParm[13 - 1].c = gtt_Internal_pack.Data.In.usAcFreq; //‚`‚bü”g””½‰f
                    _union.Nrm.CalParm[13 - 1].c = ac_frequency_limit_member(gtt_Internal_pack.Data.In.usAcFreq); //‚`‚bü”g”‚Ì”½‰f 2009.12.29
                    
                    //‚h‚c@‚O‚˜‚Q‚X ƒNƒŠ[ƒjƒ“ƒO• 2009.07.14
                    _union.Nrm.CalParm[85 - 1].c = gtt_Internal_pack.Data.In.ucCleaningDuty;

                    //‚h‚c@‚O‚˜‚Q‚` ‚l‚h‚w@‚s‚h‚fü”g” 2009.07.14
                    _union.Nrm.CalParm[66 - 1].c = (float)gtt_Internal_pack.Data.In.ucMixFreq / 10;

                    //‚h‚c@‚O‚˜‚Q‚a ‚l‚h‚wi‚`‚bj”ä—¦ 2009.07.14
                    _union.Nrm.CalParm[67 - 1].c = gtt_Internal_pack.Data.In.ucMixAcRatio;

                    //‚h‚c@‚O‚˜‚Q‚b ‚s‚h‚f@ƒzƒbƒg“d—¬’²®@L2_rob_pc_re_rcv_class“à‚Åæ‚è‚İŠ®—¹B2009.07.13
                    //‚h‚c@‚O‚˜‚Q‚c ‚s‚h‚f@ƒzƒbƒgŠÔ’²®@L2_rob_pc_re_rcv_class“à‚Åæ‚è‚İŠ®—¹B2009.07.13
                    //‚h‚c@‚O‚˜‚Q‚d ƒzƒbƒgƒXƒ[ƒv@@@@@L2_rob_pc_re_rcv_class“à‚Åæ‚è‚İŠ®—¹B2009.07.13

                    gtt_Ctrl_flag.Hpi_control = true; //‰Â•Ïƒpƒ‰ƒ[ƒ^“]‘—ƒtƒ‰ƒO
                    
#endif //2009.07.23 test del
                    if (guc_Adj1_rewrite_check_flag == 2)
                    {
                        guc_Adj1_rewrite_check_flag = 0;
                    }

                    if (guc_Adj2_rewrite_check_flag == 2)
                    {
                        guc_Adj2_rewrite_check_flag = 0;
                    }
                    if (guc_Exd_adj1_rewrite_check_flag == 2) //2008.10.07’Ç‰Á
                    {
                        guc_Exd_adj1_rewrite_check_flag = 0;
                    }

                    if (guc_Exd_adj2_rewrite_check_flag == 2)
                    {
                        guc_Exd_adj2_rewrite_check_flag = 0;
                    }

                    gtt_Ctrl_flag.Hpi_control = true; //2008.11.29‰Â•Ïƒpƒ‰ƒ[ƒ^‚ğ‚g‚o‚h“]‘—‚·‚é
                 }
                 //***********************************************************************

                //************* Šg’£—nÚ”÷’²ƒpƒ‰ƒ[ƒ^ŒÂ•Ê‘‚«Š·‚¦ 2007.5.29 *************
#if 0
                if (guc_Exd_adj1_rewrite_check_flag == 2)
                {
                    PPARMTBL    pTbl;
                    PNORMAL     pNrm = &_union.Nrm;
                    //‰Â•Ïƒpƒ‰ƒ[ƒ^‚Ì‘‚«Š·‚¦iŒÂ•Ê‘‚«Š·‚¦‚Ì‚½‚ßƒŠƒZƒbƒg‚Ís‚í‚È‚¢j
                    switch (gtt_Internal_pack.Data.In.Id_no)
                    {
                            case 1:
                                 _union.Nrm.CalParm[SP_I_NO -1 ].c       += gtt_Internal_pack.Data.In.Sp_current;    //‚r‚o“d—¬
                                 break;
                            case 2:
                                 _union.Nrm.CalParm[SP_T_NO -1 ].c       += gtt_Internal_pack.Data.In.Sp_time;       //‚r‚oŠÔ
                                 break;
                            case 3:
                                 _union.Nrm.CalParm[ELI_NO -1 ].c        += gtt_Internal_pack.Data.In.Eli;           //‚d‚k‚h
                                 break;
                            case 4:
                                 _union.Nrm.CalParm[MTS_V_NO -1 ].c      += gtt_Internal_pack.Data.In.Mts_v;         //dô“dˆ³’l
                                 break;
                            case 5:
                                 _union.Nrm.CalParm[MTS_ONTIME_NO -1 ].c += gtt_Internal_pack.Data.In.Mts_ontime;    //dô“dˆ³‚n‚mŠÔ
                                 break;
                            case 6:
                                 _union.Nrm.CalParm[MTS_CYCLE_NO -1 ].c  += gtt_Internal_pack.Data.In.Mts_cycle;     //dô“dˆ³üŠú
                                 break;
                            default:
                                 break;
                    }
                    if (guc_Exd_adj1_rewrite_check_flag == 2)
                    {
                        guc_Exd_adj1_rewrite_check_flag = 0;
                    }
                 }
#endif
                 //***********************************************************************

                //************* Šg’£—nÚ”÷’²ƒpƒ‰ƒ[ƒ^ŒÂ•ÊEˆêŠ‡‘‚«Š·‚¦ 2007.5.29 *************
#if 0
                if (guc_Exd_adj1_rewrite_check_flag == 2 || guc_Exd_adj2_rewrite_check_flag == 2) //2007.5.30•ÏX
                //if (guc_Exd_adj2_rewrite_check_flag == 2)
                {
                    PPARMTBL    pTbl;
                    PNORMAL     pNrm = &_union.Nrm;
                    pWT = GetWeldTable( ); //2007.5.30’Ç‰Á
        
                    //‰Â•Ïƒpƒ‰ƒ[ƒ^ƒŠƒZƒbƒg
                    xmemcpy( pNrm->CalParm , pWT->CalParm , sizeof( pWT->CalParm ) );
                 
                    //‰Â•Ïƒpƒ‰ƒ[ƒ^‚Ì‘‚«Š·‚¦
                     _union.Nrm.CalParm[SP_I_NO -1 ].c       += gtt_Internal_pack.Data.In.Sp_current;    //‚r‚o“d—¬
                     _union.Nrm.CalParm[SP_T_NO -1 ].c       += gtt_Internal_pack.Data.In.Sp_time;       //‚r‚oŠÔ
                     _union.Nrm.CalParm[ELI_NO -1 ].c        += gtt_Internal_pack.Data.In.Eli;           //‚d‚k‚h
                     _union.Nrm.CalParm[MTS_V_NO -1 ].c      += gtt_Internal_pack.Data.In.Mts_v;         //dô“dˆ³’l
                     _union.Nrm.CalParm[MTS_ONTIME_NO -1 ].c += gtt_Internal_pack.Data.In.Mts_ontime;    //dô“dˆ³‚n‚mŠÔ
                     _union.Nrm.CalParm[MTS_CYCLE_NO -1 ].c  += gtt_Internal_pack.Data.In.Mts_cycle;     //dô“dˆ³üŠú

                    if (guc_Exd_adj1_rewrite_check_flag == 2) //2007.5.30’Ç‰Á
                    {
                        guc_Exd_adj1_rewrite_check_flag = 0;
                    }

                    if (guc_Exd_adj2_rewrite_check_flag == 2)
                    {
                        guc_Exd_adj2_rewrite_check_flag = 0;
                    }
                 }
#endif
                 //***********************************************************************

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_weld_test_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

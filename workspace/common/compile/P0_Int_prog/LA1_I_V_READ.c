//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　Ｉ＿Ｖ＿Ｒｅａｄ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－１
//  【機能説明】
//      
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
//#define __FPGA_PROG
#include  "custom.h"

void I_V_READ(unsigned int xui_Sampling)
{
     unsigned char puc_Reg; //2007.3.2追加

	//2019.05.30
	gtt_Fpga.Curr_ad = MfmC[CURR_FB_DATA];
	gtt_Fpga.Volt_ad = MfmC[VOLT_FB_DATA];


	int rc1,rc2;
        //rc1 = ReadAmpFifo(&gtt_Fpga.Curr_ad);//2019.03.15 ihara del              //FPGAサンプリングデータ　電流A/D値取得
        //rc2 = ReadVoltFifo(&gtt_Fpga.Volt_ad);//2019.03.15 ihara del                  //FPGAサンプリングデータ　電圧A/D値取得
        if ((rc1 < 0)||(rc2 < 0))                          //バッファフル　であれば０未満の値
        {
//2009.03.11           fpgaFifoInit(100);                              //100usec毎のサンプリングで再設定
           //fpgaFifoInit(70);  //2019.03.15 ihara del                            //100usec毎のサンプリングで再設定 //2009.03.11
           gtt_Fpga.Curr_buff = 0;
           gtt_Fpga.Curr_counter = 0;
           gtt_Fpga.Volt_buff = 0;
           gtt_Fpga.Volt_counter = 0;

           gtt_Fpga.Curr_buff_rms = 0; //2009.03.26
           gtt_Fpga.Volt_buff_rms = 0; //2009.03.26
           

        } else {
           if (rc1 > 0)
           {
//2006.11.28 換算値修正               gtt_Fpga.Curr_buff = gtt_Fpga.Curr_buff + (((long)gtt_Fpga.Curr_ad * 750) / 2048);
//2008.1.30 換算値修正               gtt_Fpga.Curr_buff = gtt_Fpga.Curr_buff + (((long)gtt_Fpga.Curr_ad * 1250) / 2048);
//2009.03.11 換算方法修正               gtt_Fpga.Curr_buff = gtt_Fpga.Curr_buff + (((long)gtt_Fpga.Curr_ad * 750) / 2048);
               if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
               {
                   gtt_Fpga.Curr_buff = gtt_Fpga.Curr_buff + (((long)gtt_Fpga.Curr_ad)); //2009.03.11
                   gtt_Fpga.Curr_counter++;
               } else { //2009.03.26 実効値
//2010.03.03Del                   //gtt_Fpga.Curr_buff_rms = gtt_Fpga.Curr_buff_rms + (double)((double)gtt_Fpga.Curr_ad * (double)gtt_Fpga.Curr_ad); //2009.03.26
//2010.03.03Del                   float pf_Curr_ad_work;
//2010.03.03Del//2010.01.14                   pf_Curr_ad_work = (((float)gtt_Fpga.Curr_ad * 750) / 2048) * 0.982421875; //2009.03.27  0.982421875:1006/1024
//2010.03.03Del                   pf_Curr_ad_work = (((float)gtt_Fpga.Curr_ad * 750) / 2048) * 0.966796875; //2010.01.14  0.966796875:990/1024
//2010.03.03Del                   gtt_Fpga.Curr_buff_rms = gtt_Fpga.Curr_buff_rms + (double)(pf_Curr_ad_work * pf_Curr_ad_work); //2009.03.26 2009.03.27

                   gtt_Fpga.Curr_buff_rms = gtt_Fpga.Curr_buff_rms + (double)((double)gtt_Fpga.Curr_ad * (double)gtt_Fpga.Curr_ad); //2010.03.03
                   gtt_Fpga.Curr_counter++;
               }

               //******* 2007.3.14 ＰＯ版より移植********
               gtt_Fpga.Curr_buff_unb = gtt_Fpga.Curr_buff_unb + (((long)gtt_Fpga.Curr_ad * 1250) / 2048);
               gtt_Fpga.Curr_counter_unb++;
               //**************************
           }
           if (rc2 > 0)
           {
//2006.11.28 換算値修正               gtt_Fpga.Volt_buff = gtt_Fpga.Volt_buff + (((long)gtt_Fpga.Volt_ad * 750) / 2048);
//2009.03.11 換算方法修正               gtt_Fpga.Volt_buff = gtt_Fpga.Volt_buff + (((long)gtt_Fpga.Volt_ad * 625) / 2048);
//2009.03.16               gtt_Fpga.Volt_buff = gtt_Fpga.Volt_buff + ((long)gtt_Fpga.Volt_ad);//2009.03.11
               if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
               {
                   gtt_Fpga.Volt_buff = gtt_Fpga.Volt_buff + ((long)gtt_Fpga.Volt_ad);//2009.03.16
                   gtt_Fpga.Volt_counter++;
               } else { //2009.03.26 実効値
//2010.03.03Del                   float pf_Volt_ad_work;
//2010.03.03Del
//2010.03.03Del                   pf_Volt_ad_work = (((float)gtt_Fpga.Volt_ad * 625) / 2048) * 1.0; //2010.01.15 係数不要
//2010.03.03Del//2010.01.15                   pf_Volt_ad_work = (((float)gtt_Fpga.Volt_ad * 625) / 2048) * 0.982421875; //2009.03.27  0.982421875:1006/1024
//2010.03.03Del                   //gtt_Fpga.Volt_buff_rms = gtt_Fpga.Volt_buff_rms + (double)((double)gtt_Fpga.Volt_ad * (double)gtt_Fpga.Volt_ad);//2009.03.26
//2010.03.03Del                   gtt_Fpga.Volt_buff_rms = gtt_Fpga.Volt_buff_rms + (double)(pf_Volt_ad_work * pf_Volt_ad_work);//2009.03.26

                   gtt_Fpga.Volt_buff_rms = gtt_Fpga.Volt_buff_rms + (double)((double)gtt_Fpga.Volt_ad * (double)gtt_Fpga.Volt_ad);//2010.03.03
                   gtt_Fpga.Volt_counter++;
               }
           }
        }
        if (gtt_Fpga.Curr_counter >= xui_Sampling)
        {

//2009.03.11 換算方法修正            gtt_Fpga.Curr_result = (unsigned short)(gtt_Fpga.Curr_buff / gtt_Fpga.Curr_counter);
//2009.03.15            gtt_Fpga.Curr_result = (unsigned short)(  ((float)(gtt_Fpga.Curr_buff) *750*1006) / ((float)(gtt_Fpga.Curr_counter)* 2048 *1024) +0.5  ) ;//2009.03.11

           if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
           {

//2009.04.14
//(2009.04.11)BP_CTOFFSET_1+++++
               gtt_Fpga.Curr_result = (unsigned short)(
//2010.01.14              (((float)(gtt_Fpga.Curr_buff) *750*(1006 - gtt_Special_menu.ss_Service_data[S_OUTPUT_ADJ_GEIN] - (gss_Output_gein*5))) 
//20110921_1+++++
//D            		  (((float)(gtt_Fpga.Curr_buff) *750*( 990 - gtt_Special_menu.ss_Service_data[S_OUTPUT_ADJ_GEIN] - (gss_Output_gein*5))) 
            		  (((float)(gtt_Fpga.Curr_buff) *750*(1006 - gtt_Special_menu.ss_Service_data[S_OUTPUT_ADJ_GEIN] - (gss_Output_gein*5))) 
//20110921_1-----
  						/ ((float)(gtt_Fpga.Curr_counter)* 2048 *1024))
            			+(float)0.5 //桁落ち防止
//2010.01.14						- (1+((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2)) //サービスマンメニューオフセット補正
//20110921_1+++++
//d						- (0.5+((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2)) //サービスマンメニューオフセット補正
						- (1.0+((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2)) //サービスマンメニューオフセット補正
//20110921_1-----
						- ((float)gss_Ct_offset * 0.2) //ＤＳＷオフセット補正分調整
            		  ) ;
				if(gtt_Fpga.Curr_result<0){gtt_Fpga.Curr_result=0;}//0補正
				if(gtt_Fpga.Curr_result>999){gtt_Fpga.Curr_result=999;}//999補正 //2010.03.05
//(2009.04.11)BP_CTOFFSET_1-----

               gtt_Fpga.Curr_buff = 0;
               gtt_Fpga.Curr_counter = 0;
           } else { //2009.03.26 実効値
//2010.03.03Del               //gtt_Fpga.Curr_result_rms = (double)(
//2010.03.03Del               //				  (float)((double)((gtt_Fpga.Curr_buff_rms) *750*1006) 
//2010.03.03Del               //					/  (double)((double)(gtt_Fpga.Curr_counter)* 2048 *1024))
//2010.03.03Del               //				   );
//2010.03.03Del               
//2010.03.03Del               gtt_Fpga.Curr_result_rms = gtt_Fpga.Curr_buff_rms / gtt_Fpga.Curr_counter; //2009.03.27
//2010.03.03Del               //				   );

               /* 実効値算出の後、オフセット調整分を加算する。本来SQRTの後加算するべきであるが、
                  本箇所にて処理する。誤差発生するが、利用頻度少ないため問題ないとする。
                  平均値処理では、SHORTキャストの前に桁落ち防止のための+0.5を行うが、
                  実効値算出では、double2乗のまま、バッファをもつため、本箇所で桁落ち処理は行わない。*/
               gtt_Fpga.Curr_result_rms =  //2010.03.03追加 2010.03.04変更
                     (double)(gtt_Fpga.Curr_buff_rms 
                            *((750.0/2048.0)
                             *(750.0/2048.0)
//20110921_1+++++
//d                             *(( 990.0 - gtt_Special_menu.ss_Service_data[S_OUTPUT_ADJ_GEIN] - (gss_Output_gein*5)) /1024.0)
//d                             *(( 990.0 - gtt_Special_menu.ss_Service_data[S_OUTPUT_ADJ_GEIN] - (gss_Output_gein*5)) /1024.0)
                             *((1006.0 - gtt_Special_menu.ss_Service_data[S_OUTPUT_ADJ_GEIN] - (gss_Output_gein*5)) /1024.0)
                             *((1006.0 - gtt_Special_menu.ss_Service_data[S_OUTPUT_ADJ_GEIN] - (gss_Output_gein*5)) /1024.0)
//20110921_1-----
                             ) / gtt_Fpga.Curr_counter)
                        - ((double)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (double)0.2) //サービスマンメニューオフセット補正
                        - ((double)gss_Ct_offset * (double)0.2);//ＤＳＷオフセット補正分調整

               if(gtt_Fpga.Curr_result_rms<0){gtt_Fpga.Curr_result_rms=0;}//0補正、補正の結果負数をとる可能性があるため。
               if(gtt_Fpga.Curr_result_rms>(999*999)){gtt_Fpga.Curr_result_rms=(999*999);}//2010.03.05

               gtt_Fpga.Curr_buff_rms = 0;
               gtt_Fpga.Curr_counter = 0;
           }
        }
        if (gtt_Fpga.Volt_counter >= xui_Sampling)
        //if (gtt_Fpga.Volt_counter >= xui_Sampling / gss_Select_dital[P_VOLTAGE_SAMPLING]) //2009.02.10　エキスパートモードテスト（溶接電圧速度を上げる試験)
        {
//2009.03.11 換算方法修正            gtt_Fpga.Volt_result = (unsigned short)(gtt_Fpga.Volt_buff / gtt_Fpga.Volt_counter);
           if (gss_Select_dital[P_CURR_DISPLAY] == false) // 2009.03.26 平均値
           {
               gtt_Fpga.Volt_result = (unsigned short)( (((float)(gtt_Fpga.Volt_buff)*625) / ((float)(gtt_Fpga.Volt_counter)*2048))+0.5);//2009.03.11

               if(gtt_Fpga.Volt_result<0){gtt_Fpga.Volt_result=0;}//0補正、2010.03.05
               if(gtt_Fpga.Volt_result>(625)){gtt_Fpga.Volt_result=(625);}//2010.03.05

               gtt_Fpga.Volt_buff = 0;
               gtt_Fpga.Volt_counter = 0;
           } else { //2009.03.26 実効値
               //gtt_Fpga.Volt_result_rms = (double)( (((gtt_Fpga.Volt_buff_rms)*625) / ((double)(gtt_Fpga.Volt_counter)*2048)));//2009.03.11
//2010.03.03Del               gtt_Fpga.Volt_result_rms = gtt_Fpga.Volt_buff_rms / gtt_Fpga.Volt_counter;//2009.03.27

               gtt_Fpga.Volt_result_rms = (double)(gtt_Fpga.Volt_buff_rms * ((625.0/2048.0)*(625.0/2048.0))/ gtt_Fpga.Volt_counter);//2010.03.03

               if(gtt_Fpga.Volt_result_rms<0){gtt_Fpga.Volt_result_rms=0;}//0補正、2010.03.05
               if(gtt_Fpga.Volt_result_rms>(625*625)){gtt_Fpga.Volt_result_rms=(625*625);}//2010.03.05

               gtt_Fpga.Volt_buff_rms = 0;
               gtt_Fpga.Volt_counter = 0;
           }
        }

        if (gtt_Fpga.Curr_counter_unb>= xui_Sampling / 20) //2007.3.14 ＰＯ版より移植
        {
            gtt_Fpga.Curr_result_unb = (unsigned short)(gtt_Fpga.Curr_buff_unb / gtt_Fpga.Curr_counter_unb);
            gtt_Fpga.Curr_buff_unb = 0;
            gtt_Fpga.Curr_counter_unb = 0;
        }

   return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA1_I_V_READ.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

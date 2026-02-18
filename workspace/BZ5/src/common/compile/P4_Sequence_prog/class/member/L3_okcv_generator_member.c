//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｏｋｃｖ＿ｇｅｎｅｒａｔｏｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      一元電圧算出
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
extern int DC_PMODE;
//extern WELDCODE DC_WELDCODE;
void okcv_generator_member()
{
     unsigned short pus_Amp;
     unsigned short max_current;
     int            psi_Speed_work;

     max_current = MAX_CURRENT_ABS; //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS

     if((MAX_CURRENT_ABS % 4) != 0){//端数が出る場合は、１データ多く送信 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
         max_current = max_current + 4;
     }

     //<><><><><><><><><><> 一元テーブルの作成 <><><><><><><><><><>
     //ロボットからの指令値で採用するデータ　２Ａ刻み
     for (pus_Amp = 0 ; pus_Amp <= MAX_CURRENT ; pus_Amp+=2)
     {
         int a;
         PWELDTABLE  pWT = GetWeldTable();
         PA2STBL     pTBL;
         //PENTBL      pENTBL; //2008.09.24
         //pTBL            = &pWT->A2S_Short;
         switch( DC_PMODE )
         {
            case 2://短絡
                 pTBL = &pWT->A2S_Short;
                 //pENTBL = pWT->pENTBL_Short; //2008.09.24
                 break;
            case 1://パルス
            default:
                 pTBL = &pWT->A2S_Pulse;
                 //pENTBL = pWT->pENTBL_Pulse;
                 break;
         } 

        if(pus_Amp == MAX_CURRENT_ABS){ //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
           a = 0;
	    }
         gtt_Okcv.Okcv_real[pus_Amp / 2] = (unsigned char)(WF2Volt(GetAmp2Wire(pus_Amp,pTBL)) / 2);         //電流値からワイヤ速度を検索し、更に電圧を求め格納する

         //ＥＮ時の一元電圧算出
         if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85)
         {
             //gtt_Okcv.Okcv_real_p[pus_Amp / 2] = (unsigned char)(WF_EN_Volt(GetAmp2Wire(pus_Amp,pTBL),EN_VOLT_P));         //電流値からワイヤ速度を検索し、更に電圧を求め格納する
             //gtt_Okcv.Okcv_real_m[pus_Amp / 2] = (unsigned char)(WF_EN_Volt(GetAmp2Wire(pus_Amp,pTBL),EN_VOLT_M));         //電流値からワイヤ速度を検索し、更に電圧を求め格納する
             //gtt_Okcv.Okcv_real_0[pus_Amp / 2] = (unsigned char)(WF_EN_Volt(GetAmp2Wire(pus_Amp,pTBL),EN_VOLT_0));         //電流値からワイヤ速度を検索し、更に電圧を求め格納する
             gtt_Okcv.Okcv_real_p[pus_Amp / 2] = (char)(WF_EN_Volt(GetAmp2Wire(pus_Amp,pTBL),EN_VOLT_P));         //電流値からワイヤ速度を検索し、更に電圧を求め格納する 2008.12.26
             gtt_Okcv.Okcv_real_m[pus_Amp / 2] = (char)(WF_EN_Volt(GetAmp2Wire(pus_Amp,pTBL),EN_VOLT_M));         //電流値からワイヤ速度を検索し、更に電圧を求め格納する 2008.12.26
             gtt_Okcv.Okcv_real_0[pus_Amp / 2] = (char)(WF_EN_Volt(GetAmp2Wire(pus_Amp,pTBL),EN_VOLT_0));         //電流値からワイヤ速度を検索し、更に電圧を求め格納する 2008.12.26
         }
         //注意：2008.09.26
         //一元化電圧はテーブル値の１／２を格納し、実使用時は２倍しているが、
         //ＥＮ一元化電圧はそのままの値を使用している。
         //一元化電圧をテーブル値の１／２にしたのは、ＧＢ２を踏襲したもので、
         //ロボットに転送する一元化電圧が１／２されたものであることと２Ａ刻みで有ることを受けた物



         psi_Speed_work            = GetAmp2Wire(pus_Amp,pTBL);                                             //電流値からワイヤ速度を検索し、格納する
         gtt_Okcv.Sb0[pus_Amp + 1]     = (unsigned char)(psi_Speed_work & 0x00ff);
         gtt_Okcv.Sb0[pus_Amp] = (unsigned char)(psi_Speed_work >> 8 & 0x00ff);

         if (gtt_Ctrl_flag.Crater_pulse_non == ON)// && guc_Pulse_mode_data == 0x05)// && gss_Select_dital[P_CRATER_DC] == ON) //2008.11.06
         {
	     if (DC_PMODE == 1) //2008.11.07
	     {
                 pTBL = &pWT->A2S_Short;
                 DC_PMODE = 2;
                 gtt_Okcv.Okcv_crater_short[pus_Amp / 2] = (unsigned char)(WF2Volt(GetAmp2Wire(pus_Amp,pTBL)) / 2);         //電流値からワイヤ速度を検索し、更に電圧を求め格納する
                 DC_PMODE = 1;
             } else {
		 gtt_Okcv.Okcv_crater_short[pus_Amp / 2] = (unsigned char)(WF2Volt(GetAmp2Wire(pus_Amp,pTBL)) / 2);         //電流値からワイヤ速度を検索し、更に電圧を求め格納する
	     }
         }
         




     }
#if G3_NEW_COM


#else
     //一元化電圧要求でロボットに返すデータ　４Ａ刻み
     for (pus_Amp = 0 ; pus_Amp <= MAX_CURRENT_ABS ; pus_Amp+=4) //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
     {
         int  a;
         PWELDTABLE  pWT = GetWeldTable();
         PA2STBL     pTBL;
         //pTBL            = &pWT->A2S_Short;
         switch( DC_PMODE )
         {
            case 2://短絡
                 pTBL = &pWT->A2S_Short;
                 break;
            case 1://パルス
            default:
                 pTBL = &pWT->A2S_Pulse;
                 break;
         } 

         if(pus_Amp == MAX_CURRENT_ABS){ //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		    a = 0;
	     }
         gtt_Okcv.Okcv[pus_Amp / 4] = (unsigned char)(WF2Volt(GetAmp2Wire(pus_Amp,pTBL)) / 2);         //電流値からワイヤ速度を検索し、更に電圧を求め格納する
     }
     //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif
     gtt_Okcv.New_calc = ON;

}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_okcv_generator_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍａｇ＿ｃｔｒｌ＿ｍｅｍｏｒｙ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      ＭＡＧ系制御変数初期化
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

void mag_ctrl_memory_member(void)
{
     unsigned int i;
 
     gtt_Ctrl_word.Mg_ctrl_code        = ON;
     gtt_Ctrl_word.Gas_ctrl_code       = OFF;
     gtt_Ctrl_word.Motor_ctrl_code     = OFF;
     gtt_Ctrl_word.Inverter_ctrl_code  = OFF;
     gtt_Ctrl_word.Welder_ctrl_code    = OFF;
     gtt_Ctrl_word.Hf_ctrl_code        = OFF;
     gtt_Ctrl_word.Fan_ctrl_code       = ON;
     gtt_Ctrl_word.Sequence_ctrl_code  = OFF;

     gtt_Ctrl_flag.Inching             = OFF;
     gtt_Ctrl_flag.Motor_off           = OFF;
     gtt_Ctrl_flag.Weld_end            = OFF;
     gtt_Ctrl_flag.Arc_err             = OFF;
     gtt_Ctrl_flag.Emg_err             = OFF;
     gtt_Ctrl_flag.Burn_back           = OFF;
     gtt_Ctrl_flag.Water_err           = OFF;
     gtt_Ctrl_flag.Dsp_ready           = OFF;
     gtt_Ctrl_flag.Welder_init_execution = ON;
     gtt_Ctrl_flag.Fan_off             = OFF;
     gtt_Ctrl_flag.Table_data_output   = OFF;
     gtt_Ctrl_flag.Table_data_output1  = OFF;

     gtt_Ctrl_flag.Second_output_err   = OFF; //二次出力異常初期化　2007.1.19　2007.1.26移植追加


     gtt_Ctrl_counter.Motor_off        = 0;
     gtt_Ctrl_counter.Emg_err          = 0;
     gtt_Ctrl_counter.Water_err        = 0;
     gtt_Ctrl_counter.Welder_init_execution = 0;

     gtt_Ctrl_flag.Initial_arc_start   = OFF;
     gtt_Ctrl_flag.Lift_up_cd          = OFF;        //2008.10.08
     gtt_Ctrl_flag.Start_process_end   = OFF; //2009.04.03

//--------------------------------------------------------------------
// BP4 田中追加　2009.04.06 CTOFFSET
	gtt_DSPCToffset = 0;			//DSP自動オフセット調整値
//--------------------------------------------------------------------

     guc_Sequence_mode                 = IDLING;

     for (i = 0 ; i < ARRAY_WIDTH ; i++)
     {
        gtt_Ext_input.Data[i]      = OFF;
        gtt_Ext_input.Data_bkup[i] = OFF;
        gtt_Ext_input.Counter[i]   = 0;
        gtt_Ext_input.Flag[i]      = OFF;
     }

     p6  = (BitSwitch *)(&P6DATA);      //
     p9  = (BitSwitch *)(&P9DATA);      //
     p10 = (BitSwitch *)(&P10DATA);     //
     p11 = (BitSwitch *)(&P11DATA);     //
     p13 = (BitSwitch *)(&P13DATA);     //
     p22 = (BitSwitch *)(&P22DATA);     //


//------ Phase17 by @Tny 2008/09/24 ------
#if true
    // 本体電源起動時のＦＡＮ制御は「弱（FAN2：Ｒ８側ＦＡＮ＝ＯＮ）」で７分間に設定
    gtt_Ctrl_flag.Fan_off           = ON; //2008.11.20 OFF->ON
    gtt_Ctrl_word.Fan_ctrl_code     = OFF;
    //guc_R8_control.Bit1Sw.R8_Fan    = true; //2008.11.14 del
    //FAN2                            = ON;   //2008.11.14 del
#endif
//---------------------------------------------------------------------


     //ダミー送給量による初期化
     for (i = 0 ; i < (MAX_CURRENT_ABS << 1) + 4 ; i++) //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
     {
          gtt_Okcv.Sb0[i] = 0;
     }


#if G3_NEW_COM
//   IdentificationCode  = 0xA0;      // 機種番号　５００ＢＰ４ 2009.12.28 500BP4
     IdentificationCode  = 0x53;      // 機種番号 YC-300BP4コード	機種別コードを「YC-300BP4」にする	2011.10.31
#else
     IdentificationCode  = 0x16;      // 機種番号　３５０ＧＢ２
#endif

     //読み出しテーブルの初期値
#if 0
            gtt_Internal_pack.Data.In.fWireDiameter.ALL = 0x05;      // ワイヤ径
            gtt_Internal_pack.Data.In.fWelding.ALL      = 0x01;      // 溶接法
            gtt_Internal_pack.Data.In.fWireMaterial.ALL = 0x01;      // ワイヤ材質
            gtt_Internal_pack.Data.In.fWireSelect.ALL   = 0x03;      // 突き出し長

            gtt_Table_key.Wire_material  = 0x01;
            gtt_Table_key.Welding_method = 0x01;
            gtt_Table_key.Pulse_mode     = 0x03;
            gtt_Table_key.Pulse_type     = 0x00;
            gtt_Table_key.Wire_diameter  = 0x05;
            gtt_Table_key.Wire_ext       = 0x03;

#endif


             isContArc = 0;         //通常スタート時（繰り返し溶接ではない） 2007.1.12REPEAT
             isEnbDelay = 1;        //モータディレイセット                   2007.1.12REPEAT

     guc_Program_ver_flag = ON;  //2007.2.13追加 起動時プログラム番号を表示する
     gtt_R8_com.Work = 0xff;     //2007.2.13追加　スペースで初期化

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_mag_ctrl_memory_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

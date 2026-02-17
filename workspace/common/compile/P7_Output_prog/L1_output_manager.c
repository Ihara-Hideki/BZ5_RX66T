//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｏｕｔｐｕｔ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      出力管理
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

//2019.07.04
#include "iodefine.h"
#include "devdrv_bsc.h"
#include "rza_io_regrw.h"

void output_manager(void)
{

                                                   
     output_ext_class(gtt_Ctrl_word,gtt_Ctrl_word_bkup);
     //output_r8_class(guc_Sequence_mode , gui_Err_code); 2019.05.30 ihara del
     gtt_Ctrl_word_bkup = gtt_Ctrl_word;     //コントロールワードのバックアップ取得
     
     //if (gtt_Internal_pack.Data.In.usPulseFreq <= 50) //2009.04.11
     //if (gtt_Internal_pack.Data.In.usPulseFreq <= 40) //2010.01.20
     if (gtt_Internal_pack.Data.In.usPulseFreq <= 25) //2011.11.14
     {
         if (gtt_Ctrl_flag.Dsp_pulse_out == ON)
         {
             PLS_OUT = ON;
         } else {
             PLS_OUT = OFF;
         }
     }

     //ＭＳ制御 2019.07.03
     if (gtt_Ctrl_flag.Ms_time == false)
     {
	 gtt_Ctrl_flag.Ms_time = true;
	 gtt_Ctrl_counter.Ms_time = 6000;
     }
     else if (gtt_Ctrl_counter.Ms_time <= 0)
     {
	 MS_ON;
     }

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	{ // 2019.08.21
		MtoC[P_GAIN_DATA] = gss_Select_dital[P_EXECUTE_VOLTAGE_C];
		MtoC[I_GAIN_DATA] = gss_Select_dital[P_EXTARNAL_LEVEL_C];
	}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_output_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

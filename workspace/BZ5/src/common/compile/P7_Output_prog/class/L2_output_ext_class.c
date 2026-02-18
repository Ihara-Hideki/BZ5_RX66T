//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｏｕｔｐｕｔ＿ｅｘｔ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      外部出力
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

void output_ext_class(Bit16 xtt_Ctrl_word , Bit16 xtt_Ctrl_word_bkup)
{
     //output_mg_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup);  //2008.07.28 ＭＧはなくなったので削除 2008.09.11
     output_gas_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup); //2008.07.28 シーケンス実験のため削除
     output_hf_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup); //2009.01.31
     output_fan_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup); //2008.07.28 シーケンス実験のため削除
     output_motor_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup);
     output_inverter_ctrl_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup);
     //output_welder_ctrl_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup); 2019.05.30 ihara del
     output_stick_ctrl_member(xtt_Ctrl_word,xtt_Ctrl_word_bkup);

     output_err_alarm_member(); //2008.07.28 シーケンス実験のため削除 ->2008.10.30復活
     output_cd_member();


	//溶接電流指令値送信 2019.05.30
	//MtoC[PRE_CURR_DATA] = gtt_Internal_pack.Data.In.usWeldingCurr;


     //*** 2008.07.28 シーケンス実験のため追加 ***
#if 0
     switch(guc_Sequence_mode)
     {
        case PRE_FLOW:
             p10_0 = OFF;
             p10_1 = ON;
             p10_2 = ON;
             p10_3 = ON;
             p10_4 = ON;
             p10_5 = ON;
             break;
         case SLOW_DOWN:
             p10_0 = ON;
             p10_1 = OFF;
             p10_2 = ON;
             p10_3 = ON;
             p10_4 = ON;
             p10_5 = ON;
             break;
         case INITIAL_WELD:
             p10_0 = ON;
             p10_1 = ON;
             p10_2 = OFF;
             p10_3 = ON;
             p10_4 = ON;
             p10_5 = ON;
             break;
         case MAIN_WELD:
             p10_0 = ON;
             p10_1 = ON;
             p10_2 = ON;
             p10_3 = OFF;
             p10_4 = ON;
             p10_5 = ON;
             break;
         case CRATER_WELD:
             p10_0 = ON;
             p10_1 = ON;
             p10_2 = ON;
             p10_3 = ON;
             p10_4 = OFF;
             p10_5 = ON;
             break;
         case AFTER_FLOW:
             p10_0 = ON;
             p10_1 = ON;
             p10_2 = ON;
             p10_3 = ON;
             p10_4 = ON;
             p10_5 = OFF;
             break;
         default:
             p10_0 = ON;
             p10_1 = ON;
             p10_2 = ON;
             p10_3 = ON;
             p10_4 = ON;
             p10_5 = ON;
             break;
     }
#endif
  
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_output_ext_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｏｕｔｐｕｔ＿ｉｎｖｅｒｔｅｒ＿ｃｔｒｌ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      インバータ起動
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

void output_inverter_ctrl_member(Bit16 xtt_Ctrl_word , Bit16 xtt_Ctrl_word_bkup)
{
     unsigned short int pui_Inverter_ctrl;

     pui_Inverter_ctrl = 0x0000;       //2006.8.30 clear

     if (xtt_Ctrl_word.Inverter_ctrl_code != xtt_Ctrl_word_bkup.Inverter_ctrl_code) //前回の状態と比較
     {
         if (xtt_Ctrl_word.Inverter_ctrl_code)      //溶接電源制御コードチェック
         {
             //インバータ起動
             //pui_Inverter_ctrl = 0x0001;
		MtoC[INVERTER_CTRL1] = 1; //2019.05.30
         } else {
             //インバータ停止
             //pui_Inverter_ctrl = 0x0000;
		MtoC[INVERTER_CTRL1] = 0; //2019.05.30
         }
	 //IMJTOCR4  = 0x07; //2006.2.15 割禁　ihara     
         //hpiWrite( hpicmdOUTWLDOUT , &pui_Inverter_ctrl);   //DSPに送信 2019.04.02 del ihara
	 //IMJTOCR4  = 0x05; //2006.2.9 割許　ihara     
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_output_inverter_ctrl_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

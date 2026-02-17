//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｏｕｔｐｕｔ＿ｓｔｉｃｋ＿ｃｔｒｌ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      スティックチェック（溶接電源動作指令）
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

void output_stick_ctrl_member(Bit16 xtt_Ctrl_word , Bit16 xtt_Ctrl_word_bkup)
{
     unsigned short int pui_Stick_ctrl;  //タッチ

     pui_Stick_ctrl = 0x0000;         //2006.8.30 clear

     if (xtt_Ctrl_word.Stick_check_code != xtt_Ctrl_word_bkup.Stick_check_code) //前回の状態と比較
     {
         if (xtt_Ctrl_word.Stick_check_code)      //溶接電源制御コードチェック
         {
             //スティックチェック開始
                      //LED4 = ON;
             pui_Stick_ctrl = 0x0008;
             if (xtt_Ctrl_word.Stick_release_code == ON)
             {
                 //pui_Stick_ctrl = 0x0004;
                 pui_Stick_ctrl = 0x0008; //2009.12.08
             }
         } else {
             //スティックチェック終了
             pui_Stick_ctrl = 0x0000;
         }
	 IMJTOCR4  = 0x07; //2006.2.15 割禁　ihara     
	 //IMJTICR4  = 0x07; //2006.2.15 割禁　ihara     
         //hpiWrite( hpicmdOUTWLDMOV , &pui_Stick_ctrl);   //DSPに送信 2019.04.02 del ihara
	 IMJTOCR4  = 0x05; //2006.2.9 割許　ihara     
	 //IMJTICR4  = 0x05; //2006.2.9 割許　ihara     
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_output_stick_ctrl_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

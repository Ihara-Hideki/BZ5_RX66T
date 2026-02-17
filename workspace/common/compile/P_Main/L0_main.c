//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍａｉｎ
//　【関数レベル】
//　　　ＬＥＶＥＬ：０
//  【機能説明】
//      メイン関数
//  【引数】
//      なし
//  【戻り値】
//      なし
//  【備考】
//      ＹＤ－４５０ＧＺ３用
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  【変数説明】
//   x1x2x3_Cccc_ccc  x1:(g)グローバル変数  (p)ローカル変数　(x)関数の引数
//                    x2:(u)unsigned        (s)signed        (t)構造体
//                    x3:(b)ubool,bit (c)char (y)byte (i)int (l)long (f)float (t)struct
//                    C :大文字
//                    c :小文字
//                    構造体のメンバーは名称のみとする
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#define  __MAIN_PROG

//path INCLUDE = C:\GZWORK\Development\M32_NEW\compile\H

#include    "custom.h"

#if 0
void L0_main(void)
{
                                  WDG_Clear();

	initial_manager();                             //YD-400GZ3システム初期化

                                  WDG_Clear();
	LED5 = ON;//LED11 = ON;




       //２００６．１２．１５　バックＲＡＭテスト
        //ComuniPack.Data.From.BackUp.usWeldTimerL = test_counter;
        test_flag = OFF;
        
        //<><><>  2009.04.14 <><><>
        input_dsw_class();//2009.04.14 田中追加

        gss_Ct_offset = 0;
        
        if (gtt_Dsw.Sw.No8  == ON) gss_Ct_offset = 0x01;
        if (gtt_Dsw.Sw.No9 == ON)  gss_Ct_offset = gss_Ct_offset | 0x02;
        if (gtt_Dsw.Sw.No10 == ON) gss_Ct_offset = gss_Ct_offset | 0x04;
        if (gtt_Dsw.Sw.No11 == ON) gss_Ct_offset = gss_Ct_offset * -1;
      
        gss_Output_gein = 0;
        
        if (gtt_Dsw.Sw.No12  == ON) gss_Output_gein = 0x01;
        if (gtt_Dsw.Sw.No13 == ON)  gss_Output_gein = gss_Output_gein | 0x02;
        if (gtt_Dsw.Sw.No14 == ON)  gss_Output_gein = gss_Output_gein | 0x04;
        if (gtt_Dsw.Sw.No15 == ON)  gss_Output_gein = gss_Output_gein * -1;
        //<><><><><><><><><><><><><>
      

	FOREVER{
	        //LED4 = ON;//LED11 = ON;
                com_rcv_manager();                     //通信受信管理

	                          WDG_Clear();

                input_manager();                       //入力管理

	                          WDG_Clear();

//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.10
				if((gb_ServiceMenu == false)&&(gb_RescueMenu == false)){	// サービスマン・モード／レスキュー・モードではない？
//--------------------------------------------------------------------

//----- Phase14 by @Tny 2008/09/19 -----
#if true	// <--- true = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
					sequence_manager();                   //シーケンス管理

                    WDG_Clear();
#endif
//--------------------------------------------

//----- Phase7 & Phase13 by @Tny 2008/09/10 -----
#if true
                // DSW1-8がOFF、IIFが未接続、またはIIFが接続、認識確認、データ受信の場合にエラー確認
                if((gtt_Dsw.Sw.No7 == false)&&((gb_Iif_BuiltIn == false)||((gb_Iif_BuiltIn)&&(gb_IIF_Select)&&(gb_Iif_Input)))){

//----- Phase13 & Phase14 by @Tny 2008/09/19 -----
#if false
                    // 初期シーケンス待ち時間を経過した？
                    if(guc_Init_wait_sequence <= 0){
                        sequence_manager();                //シーケンス管理
                        WDG_Clear();
                    }
#endif
//--------------------------------------------
//2008.10.21
                    error_manager();                       //エラー管理
                }
#endif
//--------------------------------------------

	                          WDG_Clear();
//--------------------------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
				}
//--------------------------------------------------------------------


                com_snd_manager();                     //通信送信管理

                                  WDG_Clear();

                memory_manager();                      //メモリ管理

                                  WDG_Clear();

                output_manager();                      //出力管理

                                  WDG_Clear();

                sequence_stop_manager();               //シーケンス停止管理

                                  WDG_Clear();


       }
}
#endif
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L0_main.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

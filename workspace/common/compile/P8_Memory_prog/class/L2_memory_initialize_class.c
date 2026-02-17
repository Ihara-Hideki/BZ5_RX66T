//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍｅｍｏｒｙ＿ｉｎｉｔｉａｌｉｚｅ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      溶接機のメモリを初期化する。
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2008.08.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

void memory_initialize_class(unsigned char level)
{
     unsigned char puc_Index;

     if((level == 1)||(level == 3)) //ユーザ特殊パラメータ・０ｃｈ詳細データ    Phase24 by @Tny 2008/10/17
     {
         //ユーザ特殊パラメータ
         for (puc_Index = 0 ; puc_Index < USER_PARAMETER_NO ; puc_Index++)
         {
              gtt_Special_menu.ss_User_param[puc_Index] = 0;
         }
         //詳細データ
         for (puc_Index = 0 ; puc_Index < SELECT_DITAL_MAX ; puc_Index++)
         {
              gss_Select_dital[puc_Index] = gtt_Dital_attribute[puc_Index].ss_Init; //2008.10.16
              //ditail_set_member(puc_Index); //2008.10.16 2009.03.07 del
         }
         guc_Pass_word = 123; //2008.09.10
         gss_Select_dital[P_INPUT_PASS_WORD] = guc_Pass_word; //2008.09.10
         gss_Select_dital[P_CHENGE_PASS_WORD] = guc_Pass_word; //2008.09.10
         memory_write_member(0);
     }
     if((level == 2)||(level == 3)) //サービスマンデータ    Phase24 by @Tny 2008/10/17
     {
         for (puc_Index = 0 ; puc_Index < SERVICE_DATA_NO ; puc_Index++)
         {
              gtt_Special_menu.ss_Service_data[puc_Index] = 0;
         }
     }
     if (level == 3) //オール初期化（ユーザ特殊パラメータ、サービスマンデータ、全ｃｈの電流、電圧、詳細データ）
     {
//--------- Phase24 by @Tny 2008/10/17 --------
#if true
        unsigned char   i;
        for(i=1;i<CH;i++){  // CH1-CH16
            ch_rec_class((i + MEMORY_DELETE_CH));  // 記憶チャンネル削除識別子の付加
        }
#endif
//---------------------------------------------
//----- Phase22 by @Tny 2008/10/07 -----
#if true
        { // IIF設定データの初期化
            unsigned char i;
			for(i=0;i<=10;i++){	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.14 by @Tny
                guc_Out_port[0][i]      = 0;
                guc_In_port[0][i]       = 0;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
                guc_In_port[1][i]       = 0; //2009.11.27 IIF NEW
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                guc_Analog_port[0][i]   = 0;
            }
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
//@@@@@ 	if(gb_External_IIF == true){		// 外部拡張ユニット接続フラグ（true=外部拡張ユニット／false=ＩＩＦ）
	#if true	// ↓ EXTERNAL IIF NEW	2011.02.24 by @Tny	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
				guc_In_port[0][ 1] = IIF_INPUT_BIN1;		//再生ｃｈバイナリ１
				guc_In_port[0][ 2] = IIF_INPUT_BIN2;		//再生ｃｈバイナリ２
				guc_In_port[0][ 3] = IIF_INPUT_BIN3;		//再生ｃｈバイナリ３
				guc_In_port[0][ 4] = IIF_INPUT_BIN4;		//再生ｃｈバイナリ４
				guc_In_port[0][ 5] = IIF_INPUT_BIN5;		//再生ｃｈバイナリ５
				guc_In_port[0][ 6] = IIF_INPUT_BIN6;		//再生ｃｈバイナリ６
				guc_In_port[0][ 7] = IIF_INPUT_CNT;			//入力許可信号
				guc_In_port[0][ 8] = IIF_INPUT_STB;		    //ストローブ信号
				guc_In_port[0][ 9] = IIF_INPUT_TSW;			//トーチＳＷ
				guc_In_port[0][10] = IIF_INPUT_NO_USE;		//未使用
	#else
				guc_In_port[0][1] = IIF_INPUT_BIN1;			//再生ｃｈバイナリ１
				guc_In_port[0][2] = IIF_INPUT_BIN2;			//再生ｃｈバイナリ２
				guc_In_port[0][3] = IIF_INPUT_BIN3;			//再生ｃｈバイナリ３
				guc_In_port[0][4] = IIF_INPUT_BIN4;			//再生ｃｈバイナリ４
				guc_In_port[0][5] = IIF_INPUT_BIN5;			//再生ｃｈバイナリ５
				guc_In_port[0][6] = IIF_INPUT_CNT;			//入力許可信号
				guc_In_port[0][7] = IIF_INPUT_STB;		    //ストローブ信号
				guc_In_port[0][8] = IIF_INPUT_TSW;		    //トーチＳＷ
	#endif	// ↑ EXTERNAL IIF NEW	2011.02.24 by @Tny

     for(i = 1 ; i <= 10 ; i++){	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
          guc_In_port_ch[0][i]  = guc_In_port[0][i];
          dummy_access = 1;
          guc_In_port_ch[1][i]  = guc_In_port[1][i] = 0;	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
          dummy_access = 1;
     }
//@@@@@ 	}
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
        }
#endif
//--------------------------------------------
        //オールリセットをすると温度異常を無効にする 2009.04.10
        gtt_Ctrl_flag.Temp_err_set = OFF;
        gus_Temp_err_set           = OFF;
        gus_Temp_err_set_work      = OFF;
        gtt_Ctrl_flag.Temp_err     = OFF;



     }

     //イニシャライズ後必ずライトすること。2008.09.10

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_memory_initialize_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

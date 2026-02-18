//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ＣｈｅｃｋＣＭＤ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－１
//  【機能説明】
//      ロボット通信コマンドチェック
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

//void CheckCMD(signed char Number)
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
//IIF NEW
void CheckCMD(unsigned char Number)
{
    if(gb_IIF_Select){  // IIF接続を確認
    	switch(Number){
    		case 0x81:  // 通信ACK
    			IIF_Recv_81();
    			RCV_Mode = DLE_mode;    // Next RCV_Mode
    			break;
    		case 0x82:  // 通信NAK
    			IIF_Recv_82();
    			RCV_Mode = DLE_mode;    // Next RCV_Mode
    			break;
    		case 0x84:  // 状態要求 2009.10.14
    		case 0x85:  // 相互動作確認 2009.10.14
    		case 0x86:  // GoodMorning
#if true // ↓ EXTERNAL IIF NEW	2010.09.01 by @Tny
    		case 0x87:  // GoodMorning
#endif // ↑ EXTERNAL IIF NEW	2010.09.01 by @Tny
    			DATA_Length_RX = 1;     // 付随データ:１
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0x8A:  //ＩＮＰＵＴデータ
#if true 	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
    			DATA_Length_RX = 2;     // 付随データ:2
#else
    			DATA_Length_RX = 1;     // 付随データ:1
#endif
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
                break;
    		case 0x8B:  //ＡＮＡＬＯＧデータ
    			DATA_Length_RX = 3;     // 付随データ:3
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0x8C:  //アナログ入力補正データ
    			DATA_Length_RX = 8;     // 付随データ:8
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0x8D:  //ＤＳＷデータ
    			DATA_Length_RX = 2;     // 付随データ:2
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA0:  //ＯＵＴＰＵＴ割付用
    			DATA_Length_RX = 2;     // 付随データ:2
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA1:  //ＩＮＰＵＴ割付用
    			DATA_Length_RX = 2;     // 付随データ:2
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA2:  //ＡＮＡＬＯＧ割付用
    			DATA_Length_RX = 2;     // 付随データ:2
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA3:  //ＯＵＴＰＵＴチャンネル名（機能名編集用）
    			DATA_Length_RX = 7;     // 付随データ:7
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA4:  //ＩＮＰＵＴチャンネル名（機能名編集用）
    			DATA_Length_RX = 7;     // 付随データ:7
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA5:  //ＡＮＡＬＯＧチャンネル名（機能名編集用）
    			DATA_Length_RX = 7;     // 付随データ:7
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA6:  //ＯＵＴＰＵＴ名編集リセット
    			DATA_Length_RX = 1;     // 付随データ:1
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA7:  //ＩＮＰＵＴ名編集リセット
    			DATA_Length_RX = 1;     // 付随データ:1
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA8:  //ＡＮＡＬＯＧ名編集リセット
    			DATA_Length_RX = 1;     // 付随データ:1
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xA9:  //現状ＯＵＴＰＵＴ名要求
    			DATA_Length_RX = 1;     // 付随データ:1
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xAA:  //現状ＩＮＰＵＴ名要求
    			DATA_Length_RX = 1;     // 付随データ:1
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xAB:  //現状ＡＮＡＬＯＧ名要求
    			DATA_Length_RX = 1;     // 付随データ:1
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xB0:  //入力論理式データ　エリア１
    			DATA_Length_RX = 64;    // 付随データ:64
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xB1:  //入力論理式データ　エリア２
    			DATA_Length_RX = 64;    // 付随データ:64
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xB2:  //入力論理式データ　エリア３
    			DATA_Length_RX = 64;    // 付随データ:64
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xB3:  //入力論理式データ　出力端子
    			DATA_Length_RX = 80;    // 付随データ:80
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xB4:  //入力配線式データ
    			DATA_Length_RX = 64;    // 付随データ:64
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0xB5:  //アナログ入力補正データ
    			DATA_Length_RX = 5;     // 付随データ:5
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		default:
    			DATA_Length_RX = 0;     // 付随データ無し
    			RCV_Mode = DLE_mode;    // Next RCV_Mode
    	}
    }
    else{
		//---------------------------------
		// ロボット通信時の不具合を修正。（コマンド解析部が旧仕様のままだった）	2011.10.31
		//---------------------------------
    	switch(Number){
    		case 0x41:/*通信ACK*/
    			GD2_Recv_41();
    			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
    			break;
    		case 0x42:/*通信NAK*/
    			GD2_Recv_42();
    			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
    			break;
    		case 0x47:/*機種別ｺｰﾄﾞ要求*/
    		case 0x48:/*一元化電圧ﾃﾞｰﾀ送信要求*/
    		case 0x49:/*送給量ﾃﾞｰﾀ送信要求*/
    		case 0x4A:/*GoodMorning*/
    		case 0x4F:/*動作状態要求*/
    		case 0x52:/*Password 1*/
    		case 0x53:/*Password 2*/
    		case 0x67:/**/
    		case 0x68:
    			DATA_Length_RX = 1;/*付随データ１*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
            case 0x69: //2009.07.13
    			DATA_Length_RX = 7;/*付随データ7*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x6B:/* 2009.07.13 */
    			DATA_Length_RX = 2;/*付随データ2*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
            case 0x6C:
    		case 0x71:
    		case 0x89: //2007.2.9
    			DATA_Length_RX = 1;/*付随データ１*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x81:
    		case 0x82:
    		case 0x86:
    			DATA_Length_RX = 1;/*付随データ１*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x62:
    			DATA_Length_RX = 3;/*付随データ３*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x61:
    		case 0x84: /*2007.4.17*/
            case 0x8A: /*2007.5.11*/
    			DATA_Length_RX = 4;/*付随データ４*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x64:
    		case 0x83:
    			DATA_Length_RX = 5;/*付随データ５*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x63:
    		case 0x87:
    		case 0x88:
    			DATA_Length_RX = 6;/*付随データ６*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x85:
    			DATA_Length_RX = 21;/*付随データ21*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8B: /*2007.5.11*/
    			DATA_Length_RX = 10;/*付随データ21*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8C: /*2008.10.03*/
    			//DATA_Length_RX = 5;/*付随データ5*/
    			DATA_Length_RX = 6;/*付随データ6 2008.11.28*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8D: /*2008.10.03*/
    			//DATA_Length_RX = 1;/*付随データ1*/
    			DATA_Length_RX = 4;/*付随データ4 2008.11.28*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8E: /*2008.10.03*/
    			DATA_Length_RX = 1;/*付随データ1*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		default:
    			DATA_Length_RX = 0;/*付随データ無し*/
    			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
    	}
    }
}
#else
void CheckCMD(unsigned char Number)
{
//--------- IIF by @Tny 2008/08/26 ------------
#if true
    if(gb_IIF_Select){  // IIF接続を確認
    	switch(Number){
    		case 0x81:  // 通信ACK
    			GD2_Recv_41();
    			RCV_Mode = DLE_mode;    // Next RCV_Mode
    			break;
    		case 0x82:  // 通信NAK
    			GD2_Recv_42();
    			RCV_Mode = DLE_mode;    // Next RCV_Mode
    			break;
    		case 0x86:  // GoodMorning
    			DATA_Length_RX = 1;     // 付随データ:１
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		case 0x84:  //
    			DATA_Length_RX = 0;     // 付随データ無し
    			RCV_Mode = SUM_mode;    // Next RCV_Mode
    			break;
    		case 0x8A:
    		case 0x8B:
    			DATA_Length_RX = 7;     // 付随データ:7
    			RCV_Mode = DATA_mode;   // Next RCV_Mode
    			break;
    		default:
    			DATA_Length_RX = 0;     // 付随データ無し
    			RCV_Mode = DLE_mode;    // Next RCV_Mode
    	}
    }
    else{
    	switch(Number){
    		case 0x41:/*通信ACK*/
    			GD2_Recv_41();
    			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
    			break;
    		case 0x42:/*通信NAK*/
    			GD2_Recv_42();
    			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
    			break;
    		case 0x47:/*機種別ｺｰﾄﾞ要求*/
    		case 0x48:/*一元化電圧ﾃﾞｰﾀ送信要求*/
    		case 0x49:/*送給量ﾃﾞｰﾀ送信要求*/
    		case 0x4A:/*GoodMorning*/
    		case 0x4F:/*動作状態要求*/
    		case 0x52:/*Password 1*/
    		case 0x53:/*Password 2*/
    		case 0x67:/**/
    		case 0x68:
    			DATA_Length_RX = 1;/*付随データ１*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
            case 0x69: //2009.07.13
    			DATA_Length_RX = 7;/*付随データ7*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x6B:/* 2009.07.13 */
    			DATA_Length_RX = 2;/*付随データ2*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
            case 0x6C:
    		case 0x71:
    		case 0x89: //2007.2.9
    			DATA_Length_RX = 1;/*付随データ１*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x81:
    		case 0x82:
    		case 0x86:
    			DATA_Length_RX = 1;/*付随データ１*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x62:
    			DATA_Length_RX = 3;/*付随データ３*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x61:
    		case 0x84: /*2007.4.17*/
            case 0x8A: /*2007.5.11*/
    			DATA_Length_RX = 4;/*付随データ４*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x64:
    		case 0x83:
    			DATA_Length_RX = 5;/*付随データ５*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x63:
    		case 0x87:
    		case 0x88:
    			DATA_Length_RX = 6;/*付随データ６*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x85:
    			DATA_Length_RX = 21;/*付随データ21*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8B: /*2007.5.11*/
    			DATA_Length_RX = 10;/*付随データ21*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8C: /*2008.10.03*/
    			//DATA_Length_RX = 5;/*付随データ5*/
    			DATA_Length_RX = 6;/*付随データ6 2008.11.28*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8D: /*2008.10.03*/
    			//DATA_Length_RX = 1;/*付随データ1*/
    			DATA_Length_RX = 4;/*付随データ4 2008.11.28*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;
    		case 0x8E: /*2008.10.03*/
    			DATA_Length_RX = 1;/*付随データ1*/
    			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
    			break;

    		default:
    			DATA_Length_RX = 0;/*付随データ無し*/
    			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
    	}
    }
#else
	switch(Number){
		case 0x41:/*通信ACK*/
			GD2_Recv_41();
			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
			break;
		case 0x42:/*通信NAK*/
			GD2_Recv_42();
			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
			break;
		case 0x47:/*機種別ｺｰﾄﾞ要求*/
		case 0x48:/*一元化電圧ﾃﾞｰﾀ送信要求*/
		case 0x49:/*送給量ﾃﾞｰﾀ送信要求*/
		case 0x4A:/*GoodMorning*/
		case 0x4F:/*動作状態要求*/
		case 0x52:/*Password 1*/
		case 0x53:/*Password 2*/
		case 0x67:/**/
		case 0x68:
        case 0x6C:
		case 0x71:
		case 0x89: //2007.2.9
			DATA_Length_RX = 1;/*付随データ１*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x81:
		case 0x82:
		case 0x86:
			DATA_Length_RX = 1;/*付随データ１*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x62:
			DATA_Length_RX = 3;/*付随データ３*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x61:
		case 0x84: /*2007.4.17*/
        case 0x8A: /*2007.5.11*/
			DATA_Length_RX = 4;/*付随データ４*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x64:
		case 0x83:
			DATA_Length_RX = 5;/*付随データ５*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x63:
		case 0x87:
		case 0x88:
			DATA_Length_RX = 6;/*付随データ６*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x85:
			DATA_Length_RX = 21;/*付随データ21*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		case 0x8B: /*2007.5.11*/
			DATA_Length_RX = 10;/*付随データ21*/
			RCV_Mode = DATA_mode;/*Next RCV_Mode*/
			break;
		default:
			DATA_Length_RX = 0;/*付随データ無し*/
			RCV_Mode = DLE_mode;/*Next RCV_Mode*/
	}
#endif
//--------------------------------------------
}
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA1_CheckCMD.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

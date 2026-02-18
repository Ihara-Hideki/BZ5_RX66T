/********************************************************/
/*-- Function     	: ＲＳ４２２関連処理				*/
/*-  File Name		: GD2Snd3.c							*/
/*	 Create Date	: 00/04/13							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/*	 Note			: ＲＳ４２２ポートにデータを書き出す*/
/*					: だけのルーチン					*/
/********************************************************/
#define	__RS422__
#include	"custom.h"

/********************************************************/
/*-- Function     	: ＡＣＫ返信						*/
/*-  Function Name	: GD2_Send_A1						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_A1( void )
{
	DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＮＵＫ返信						*/
/*-  Function Name	: GD2_Send_A1						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_A2( void )
{
	DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: Busy返信							*/
/*-  Function Name	: GD2_Send_A3						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_A3( void )
{
	DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 機種識別ｺｰﾄﾞROMﾊﾞｰｼｮﾝ				*/
/*-  Function Name	: GD2_Send_B1						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_B1( void )
{
//  IdentificationCode = 0xA0;         //2009.12.28 YC-500BP4コード
    IdentificationCode = 0x53;         //2009.07.10 YC-300BP4コード		機種別コードを「YC-300BP4」にする	2011.10.31
    ComuniPack.Data.From.ucModelCode = IdentificationCode;  // 機種別コード

	DATA_Length_TX = 3;/*付随データ 3*/
	Txd_DATA[ 0 ] = ComuniPack.Data.From.ucModelCode;
	Txd_DATA[ 1 ] = (ComuniPack.Data.From.sRomVersion[0] + 0x30);
	Txd_DATA[ 2 ] = (ComuniPack.Data.From.sRomVersion[1] + 0x30);
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 機種識別ｺｰﾄﾞROMﾊﾞｰｼｮﾝ				*/
/*-  Function Name	: GD2_Send_B3						*/
/*	 Create Date	: 2006/12/18						*/
/*	 Author			: With) Ihara   					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_B3( void ) //G3_NEW_COM
{

    ComuniPack.Data.From.ucModelCode = IdentificationCode;           // 機種別コード

	DATA_Length_TX = 14;/*付随データ 3*/
	Txd_DATA[ 0 ]  = ComuniPack.Data.From.ucModelCode;
	Txd_DATA[ 1 ]  = (ComuniPack.Data.From.sRomVersion[0]);// + 0x30);    //ROMver　上位
	Txd_DATA[ 2 ]  = (ComuniPack.Data.From.sRomVersion[1]);// + 0x30);    //ROMver　中位
	Txd_DATA[ 3 ]  = (ComuniPack.Data.From.sRomVersion[2]);// + 0x30);    //ROMver　下位

	Txd_DATA[ 4 ]  = (ComuniPack.Data.From.Kind_code);// + 0x30);         //種別（Ｄ：ＭＡＧ　Ｃ：ＴＩＧ）

	Txd_DATA[ 5 ]  = (ComuniPack.Data.From.Capacity_code[0]);// + 0x30);  //定格出力　一の位
	Txd_DATA[ 6 ]  = (ComuniPack.Data.From.Capacity_code[1]);// + 0x30);  //定格出力　十の位
	Txd_DATA[ 7 ]  = (ComuniPack.Data.From.Capacity_code[2]);// + 0x30);  //定格出力　百の位
    
	Txd_DATA[ 8 ]  = (ComuniPack.Data.From.Model_code[0]);// + 0x30);     //機種（例ＧＺ３：Ｇ）
	Txd_DATA[ 9 ]  = (ComuniPack.Data.From.Model_code[1]);// + 0x30);     //機種（例ＧＺ３：Ｚ）
	Txd_DATA[ 10 ] = (ComuniPack.Data.From.Model_code[2]);// + 0x30);     //機種（例ＧＺ３：３）
    
	Txd_DATA[ 11 ] = (ComuniPack.Data.From.Special_code[0]);// + 0x30);   //特殊品（例ＴＡＥ：Ｔ）標準品はスペース
	Txd_DATA[ 12 ] = (ComuniPack.Data.From.Special_code[1]);// + 0x30);   //特殊品（例ＴＡＥ：Ａ）標準品はスペース
	Txd_DATA[ 13 ] = (ComuniPack.Data.From.Special_code[2]);// + 0x30);   //特殊品（例ＴＡＥ：Ｅ）標準品はスペース
    
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: PASSWORD							*/
/*-  Function Name	: GD2_Send_B2						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_B2( void )
{
	DATA_Length_TX = 1;/*付随データ 1*/
	Txd_DATA[ 0 ] = ComuniPack.Data.From.ucPassword;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 溶接出力（電流,電圧,短絡回数）	*/
/*-  Function Name	: GD2_Send_C1						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_C1( void )
{
	DATA_Length_TX = 5;/*付随データ 1*/
	Txd_DATA[ 0 ] = (unsigned char)(ComuniPack.Data.From.usWeldingOutCurr & 0x00ff);						// 溶接電流(下位)
	Txd_DATA[ 1 ] = (unsigned char)((unsigned int)((ComuniPack.Data.From.usWeldingOutCurr & 0xff00)>> 8));	// 溶接電流(上位)
	Txd_DATA[ 2 ] = (unsigned char)(ComuniPack.Data.From.usWeldingOutVolt & 0x00ff);							// 溶接電圧(下位)
	Txd_DATA[ 3 ] = (unsigned char)((unsigned int)((ComuniPack.Data.From.usWeldingOutVolt & 0xff00) >> 8));	// 溶接電圧(上位)
	Txd_DATA[ 4 ] = ComuniPack.Data.From.ucImprudence;														// 短絡回数
	return( 0 );
}
/********************************************************/
/*-- Function     	: モータ状態（電流値、回転数）		*/
/*-  Function Name	: GD2_Send_C2						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_C2( void )
{
	DATA_Length_TX = 2;/*付随データ 2*/
	Txd_DATA[ 0 ] = ComuniPack.Data.From.ucMotorCurr;	// モータ電流
	Txd_DATA[ 1 ] = ComuniPack.Data.From.ucMotorRPM;	// モータ回転数
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: モータ状態（電流値、回転数）		*/
/*-  Function Name	: GD2_Send_C2						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_C3( void )
{
	DATA_Length_TX = 3;/*付随データ 2*/
	Txd_DATA[ 0 ] = ComuniPack.Data.From.ucMotorCurr2;									// モータ電流
	Txd_DATA[ 1 ] = (unsigned char)(ComuniPack.Data.From.usMotorRPM2 & 0x00ff);			// モータ回転数（下位）
	Txd_DATA[ 2 ] = (unsigned char)((ComuniPack.Data.From.usMotorRPM2 & 0xff00) >> 8);	// モータ回転数(上位）
	return( 0 ) ;

}
/********************************************************/
/*-- Function     	: 異常検出状態						*/
/*-  Function Name	: GD2_Send_C4						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_C4( void )
{
	DATA_Length_TX = 3;/*付随データ 3*/
	Txd_DATA[ 0 ] = ComuniPack.Data.From.fErrorCode1.ALL;
	Txd_DATA[ 1 ] =	ComuniPack.Data.From.fErrorCode2.ALL;
	Txd_DATA[ 2 ] = ComuniPack.Data.From.fErrorCode3.ALL;

        gtt_Ctrl_flag.ErrorCode_snd = OFF;    //データの格納が終わったのでＯＦＦする。２００６．１１．９

	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 溶接電源検出状態					*/
/*-  Function Name	: GD2_Send_C5						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_C5( void )
{
	DATA_Length_TX = 1;/*付随データ 1*/
	Txd_DATA[ 0 ] = ComuniPack.Data.From.fPowerStatus.ALL;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 一元化電圧データ送信				*/
/*-  Function Name	: GD2_Send_D1						*/
/*	 Create Date	: 2001/04/12						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_D1( void )
{
	register unsigned char *table_adr;

#if G3_NEW_COM
	if(TableData_exit == OFF){
		DATA_Length_TX = 2;
		Txd_DATA[ 0 ] = 1;
	}
	else{
		if((MAX_CURRENT_ABS % 2) != 0){                  //端数が出る場合は、１データ多く送信 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS  
			DATA_Length_TX = ((MAX_CURRENT_ABS >>1) + 3);// 付随データ 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
			Txd_DATA[ 0 ] = (unsigned char)((MAX_CURRENT_ABS >> 1) + 2); //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		}
		else{
			DATA_Length_TX = ((MAX_CURRENT_ABS >>1) + 2);//付随データ 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
			Txd_DATA[ 0 ] = (unsigned char)((MAX_CURRENT_ABS >> 1) + 1); //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		}
	}
#else
	if(TableData_exit == OFF){
		DATA_Length_TX = 2;
		Txd_DATA[ 0 ] = 1;
	}
	else{
		if((MAX_CURRENT_ABS % 4) != 0){//端数が出る場合は、１データ多く送信 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
			DATA_Length_TX = ((MAX_CURRENT_ABS >>2) + 3);//付随データ 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
			Txd_DATA[ 0 ] = (unsigned char)((MAX_CURRENT_ABS >> 2) + 2); //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		}
		else{
			DATA_Length_TX = ((MAX_CURRENT_ABS >>2) + 2);//付随データ 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
			Txd_DATA[ 0 ] = (unsigned char)((MAX_CURRENT_ABS >> 2) + 1); //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		}
	}
#endif

#if 0
	table_adr = &co2_ms_solid_06;	// Dummy
	if(data_count_tx > 0){
		Txd_DATA[ data_count_tx ] = *( OKCV + (data_count_tx -1 )) ;
	}
#endif

#if G3_NEW_COM
	if(data_count_tx > 0){
		Txd_DATA[ data_count_tx ] = gtt_Okcv.Okcv_real[data_count_tx -1];
	}
#else
	if(data_count_tx > 0){
		Txd_DATA[ data_count_tx ] = gtt_Okcv.Okcv[data_count_tx -1];
	}
#endif
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 送給量データ送信					*/
/*-  Function Name	: GD2_Send_D1						*/
/*	 Create Date	: 2001/04/12						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_D2( void )
{
	register unsigned char *table_adr;

    unsigned int puc_Max_current;

    puc_Max_current = (unsigned int)((MAX_CURRENT_ABS + 2) / 2); //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS

	if(TableData_exit == OFF){
		DATA_Length_TX = 4;
		Txd_DATA[ 0 ] = 1;
		Txd_DATA[ 1 ] = 0;
	}
	else{
#if G3_NEW_COM
		DATA_Length_TX = (unsigned int)((MAX_CURRENT_ABS)+ 4);//付随データ 1 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		Txd_DATA[ 0 ] = (unsigned char)(puc_Max_current & 0xff);
		Txd_DATA[ 1 ] = (unsigned char)(puc_Max_current >> 8);
#else
		DATA_Length_TX = (unsigned int)((MAX_CURRENT_ABS << 1)+ 4);//付随データ 1 2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		Txd_DATA[ 0 ] = (unsigned char)((MAX_CURRENT_ABS + 1) & 0xff); //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
		Txd_DATA[ 1 ] = (unsigned char)((MAX_CURRENT_ABS + 1) >> 8);   //2010.01.18 MAX_CURRENT->MAX_CURRENT_ABS
#endif
	}

#if 1
	if(data_count_tx > 1 ){
		if(data_count_tx % 2){/*奇数*/
			Txd_DATA[ data_count_tx ] = gtt_Okcv.Sb0[data_count_tx -3];
		}
		else{
			Txd_DATA[ data_count_tx ] = gtt_Okcv.Sb0[data_count_tx -1];
		}
	}
#endif


#if 0
	table_adr = &co2_ms_solid_06;	// Dummy
	if(data_count_tx > 1 ){
		if(data_count_tx % 2){/*奇数*/
			Txd_DATA[ data_count_tx ] = *( SB0 + (data_count_tx -3 )) ;
		}
		else{
			Txd_DATA[ data_count_tx ] = *( SB0 + (data_count_tx -1 )) ;
		}
	}
#endif
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: テーブルデータ送信				*/
/*-  Function Name	: GD2_Send_E1						*/
/*	 Create Date	: 2006/12/18						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_E1( void )
{
    unsigned int i;
    unsigned int index;

   
	DATA_Length_TX = (gui_Table_code_counter * 8) + 1;/*付随データ 1*/
	Txd_DATA[ 0 ] = gui_Table_code_counter;

       
    for (i = 0 ; i <= gui_Table_code_counter ; i++)
    {
        index = i * 8;

        Txd_DATA[index+1] = gtt_Table_code[i].Material;           //材質
        Txd_DATA[index+2] = gtt_Table_code[i].Method;             //溶接法
        Txd_DATA[index+3] = gtt_Table_code[i].Pulse_mode;         //溶接種別フラグ（短絡／パルス）
        Txd_DATA[index+4] = gtt_Table_code[i].Pulse_type;         //パルスタイプ
        Txd_DATA[index+5] = gtt_Table_code[i].Wire;               //ワイヤ径
        Txd_DATA[index+6] = gtt_Table_code[i].Extension;          //突き出し長
        Txd_DATA[index+7] = gtt_Table_code[i].Reserved1;          //予約
        Txd_DATA[index+8] = gtt_Table_code[i].Reserved2;          //予約
     }
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: テーブルデータ送信				*/
/*-  Function Name	: GD2_Send_E2						*/
/*	 Create Date	: 2006/12/21						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_E2( void )
{
    unsigned int i;
    unsigned int index;
    unsigned int pui_Len;

   
	DATA_Length_TX = (gui_Sp_table_code_counter * 17) + 1;/*付随データ 1*/
	Txd_DATA[ 0 ] = gui_Sp_table_code_counter;

       
    for (i = 0 ; i <= gui_Sp_table_code_counter ; i++)
    {
        index = i * 17;

        Txd_DATA[index+1] = gtt_Sp_table_code[i].Kind;            //０１：材質　０２溶接法
        Txd_DATA[index+2] = gtt_Sp_table_code[i].Code;            //コード
        for (pui_Len = 0 ; pui_Len <= 14 ; pui_Len++)
        {
             Txd_DATA[index+(pui_Len + 3)] = gtt_Sp_table_code[i].Name[pui_Len];// + 0x30;  //コメント
        }
     }
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 問い合わせに対する回答  	        */
/*-  Function Name	: GD2_Send_E3						*/
/*	 Create Date	: 2008/10/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_E3( void )
{
	DATA_Length_TX = 3;/*付随データ 1*/
	Txd_DATA[ 0 ] = (unsigned char)(ComuniPack.Data.From.uc_En_a);						// ＥＮ比率計算結果
	Txd_DATA[ 1 ] = (unsigned char)(ComuniPack.Data.From.us_En_Okcv & 0x00ff);							// ＥＮ比率計算後一元化電圧(下位)
	Txd_DATA[ 2 ] = (unsigned char)((unsigned int)((ComuniPack.Data.From.us_En_Okcv & 0xff00) >> 8));	// ＥＮ比率計算後一元化電圧(上位)
	return( 0 ) ;
}

//--------- EXTERNAL IIF NEW by @Tny 2011/02/21 ------------
#if false //2009.10.15 del IIF NEW	← IIF NEW	2010.09.01 by @Tny
/********************************************************/
/*-- Function     	: OUTPUTデータ送信					*/
/*-  Function Name	: GD2_Send_20						*/
/*	 Create Date	: 2008/08/26						*/
/*	 Author			: With) @Tny            			*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_20( void )
{
	DATA_Length_TX = 1; // 付随データ：1

//--------- IIF(Debug) by @Tny 2008/08/28 ------------
#if false
	if(gb_IIF_DebugFlag1)   Txd_DATA[ 0 ] = 0x01;
    else                    Txd_DATA[ 0 ] = 0x00;
#else
    Txd_DATA[ 0 ] = guc_Iif_output;
#endif
//--------------------------------------------
//----- Phase4 by @Tny 2008/09/08 -----
#if true
    gus_Iif_comunication_timer  = 2000; // 200msec
	gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
#endif
//--------------------------------------------
return(0);
}
/********************************************************/
/*-- Function     	: 入力ポート設定データ送信			*/
/*-  Function Name	: GD2_Send_30						*/
/*	 Create Date	: 2008/08/26						*/
/*	 Author			: With) @Tny            			*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Send_30( void )
{
	DATA_Length_TX = 1; // 付随データ：1
	Txd_DATA[ 0 ] = 0x00;

return(0);
}
#endif
//--------------------------------------------


/********************************************************/
/*-- Function     	: 送信コマンド記憶					*/
/*-  Function Name	: GD2_Send_CMD()					*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
void GD2_Send_CMD( unsigned char CMD_CODE )
{
	if(ComuniPack.Data.bRS422Connection){	// 回線は開いている？
//--------- IIF by @Tny 2008/08/26 ------------
#if true
        if(gb_IIF_Select){  // IIF接続を確認
    		switch(CMD_CODE){
    			case 0x11:
    					GD2_ACK_count++;
    				break;
    			case 0x12:
    					GD2_NAK_count++;
    				break;
    			case 0x13:
    					GD2_Busy_count++;
    				break;
    			default:
    					Txd_CMD[ SND_CMD_Position ] = CMD_CODE;
    					SND_CMD_Position++;
    					if ( SND_CMD_Position >= TXB_BUFFER_MAX ) {
    						SND_CMD_Position = 0 ;
    					}
    		}
        }
        else{
    		switch(CMD_CODE){
    			case 0xA1:
    					GD2_ACK_count++;
    				break;
    			case 0xA2:
    					GD2_NAK_count++;
    				break;
    			case 0xA3:
    					GD2_Busy_count++;
    				break;
    			default:
    					Txd_CMD[ SND_CMD_Position ] = CMD_CODE;
    					SND_CMD_Position++;
    					if ( SND_CMD_Position >= TXB_BUFFER_MAX ) {
    						SND_CMD_Position = 0 ;
    					}
    		}
        }
#else
		switch(CMD_CODE){
			case 0xA1:
					GD2_ACK_count++;
				break;
			case 0xA2:
					GD2_NAK_count++;
				break;
			case 0xA3:
					GD2_Busy_count++;
				break;
			default:
					Txd_CMD[ SND_CMD_Position ] = CMD_CODE;
					SND_CMD_Position++;
					if ( SND_CMD_Position >= TXB_BUFFER_MAX ) {
						SND_CMD_Position = 0 ;
					}
		}
#endif
//--------------------------------------------
	}
}

//------------------------
//  End of GD2Snd3.c
//------------------------

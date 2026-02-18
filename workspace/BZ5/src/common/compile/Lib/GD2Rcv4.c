/********************************************************/
/*-- Function     	: ＲＳ４２２関連処理				*/
/*-  File Name		: GD2Rcv.c							*/
/*	 Create Date	: 00/04/13							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/*	 Note			: ＲＳ４２２ポートにデータを書き出す*/
/*					: だけのルーチン					*/
/********************************************************/
#define	__RS422__
#include	"custom.h"

/* 関数名のつけ方 */
/* Send_xx */
/*      xx は１６進数３０～６Ｆ */
/********************************************************/
/*-- Function     	: ＡＣＫ受信						*/
/*-  Function Name	: GD2_Recv_41						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_41( void )
{
	SND_Mode = DLE_mode_SD;
	WAIT_SD_count	= 0;
	if ( SND_CMD_Position != SND_CMD_Proc ) {	
			SND_CMD_Proc++;
		if ( SND_CMD_Proc >= TXB_BUFFER_MAX ) {
			SND_CMD_Proc = 0 ;
		}
	}
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＮＡＫ受信						*/
/*-  Function Name	: GD2_Recv_42						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_42( void )
{
	SND_Mode = DLE_mode_SD;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 機種別コード要求					*/
/*-  Function Name	: GD2_Recv_47						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_47( void )
{
	//GD2_Send_CMD(0xB1); //機種別ｺｰﾄﾞ送信
	GD2_Send_CMD(0xB3); //機種別ｺｰﾄﾞ送信
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 一元化電圧データ送信要求			*/
/*-  Function Name	: GD2_Recv_48						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_48( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
        gtt_Okcv.Request1 = ON;
	//GD2_Send_CMD(0xd1);
        
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 送給量データ送信要求				*/
/*-  Function Name	: GD2_Recv_49						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_49( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
        gtt_Okcv.Request2 = ON;
	//GD2_Send_CMD(0xd2);
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: Good Morning						*/
/*-  Function Name	: GD2_Recv_4A						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_4A( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
	ComuniPack.Data.bRS422Connection	= true;	// ＲＳ４２２側回線接続状態

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 動作状態要求						*/
/*-  Function Name	: GD2_Recv_4A						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_4F( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
	if(a == 0xc4){	GD2_Send_CMD(0xc4);}
	if(a == 0xc5){	GD2_Send_CMD(0xc5);}
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: PASSWORD1                         */
/*-  Function Name	: GD2_Recv_52						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_52( void )
{
#if G3_NEW_COM
	GD2_Pass1 = Rxd_DATA[0];
	ComuniPack.Data.From.ucPassword = (GD2_Pass1 | 0x55) & (~GD2_Pass1 | 0xAA);		// パスワード変換後データ 2006.12.18 0x55　EXOR　PASSWORD1
#else
	GD2_Pass1 = Rxd_DATA[0];
	ComuniPack.Data.From.ucPassword = (GD2_Pass1 | 0xAA) & (~GD2_Pass1 | 0x55);		// パスワード変換後データ
#endif

	GD2_Send_CMD( 0xb2 );/*パスワード送信*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: PASSWORD2							*/
/*-  Function Name	: GD2_Recv_53						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_53( void )
{
	GD2_Pass2 = Rxd_DATA[ 0 ];
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 溶接出力指令（電流電圧）			*/
/*-  Function Name	: GD2_Recv_61						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_61( void )
{
	ComuniPack.Data.To.usWeldingCurr = ((ushort)Rxd_DATA[0] + ((ushort)Rxd_DATA[1] << 8));
	ComuniPack.Data.To.usWeldingVolt = ((ushort)Rxd_DATA[2] + ((ushort)Rxd_DATA[3] << 8));
	ComuniPack.Data.To.iRecvCommand	 = 61;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ﾜｲﾔ径、材質、初期データ			*/
/*-  Function Name	: GD2_Recv_62						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_62( void )
{
	ComuniPack.Data.To.fWireDiameter.Bit4Sw.fLower	= (Rxd_DATA[0] & 0x0f0) >> 4;
	ComuniPack.Data.To.fWelding.Bit4Sw.fLower 		= (Rxd_DATA[0] & 0x0f);
	ComuniPack.Data.To.fWireMaterial.Bit4Sw.fLower	= (Rxd_DATA[1] & 0x0f0) >> 4;
	ComuniPack.Data.To.fWireSelect.Bit4Sw.fLower	= (Rxd_DATA[1] & 0x0f);
	ComuniPack.Data.To.fInitialSelect1.ALL			= Rxd_DATA[2];
	ComuniPack.Data.To.iRecvCommand	 				= 62;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 				= true;	// 受信データ更新フラグの更新

        gtt_Okcv.New_calc = OFF;

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 波形制御パラメータ				*/
/*-  Function Name	: GD2_Recv_63						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_63( void )
{
	ComuniPack.Data.To.vIscAdj	=	Rxd_DATA[1];	// 短絡電流屈曲点微調整
	ComuniPack.Data.To.vIsl1Adj	=	Rxd_DATA[2];	// 短絡電流第１勾配微調整
	ComuniPack.Data.To.vIsl2Adj	=	Rxd_DATA[3];	// 短絡電流第２勾配微調整
	ComuniPack.Data.To.vIacAdj	=	Rxd_DATA[5];	// アーク再生直後電流微調整
	ComuniPack.Data.To.iRecvCommand	 = 63;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ｽﾀｰﾄ終了条件設定					*/
/*-  Function Name	: GD2_Recv_64						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_64( void )
{
	ComuniPack.Data.To.vVhotAdj		=	Rxd_DATA[1];	// ホット電圧微調整
	ComuniPack.Data.To.vSldnAdj		=	Rxd_DATA[2];	// スローダウン速度微調整
	ComuniPack.Data.To.vFttAdj		=	Rxd_DATA[3];	// ＦＴＴレベル微調整
	ComuniPack.Data.To.vBarnBackAdj	=	Rxd_DATA[4];	// バーンバック時間微調整
	ComuniPack.Data.To.iRecvCommand	 = 64;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 溶接電源動作指令					*/
/*-  Function Name	: GD2_Recv_67						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_67( void )
{
	ComuniPack.Data.To.fWelderCommand.ALL	= Rxd_DATA[0];
	ComuniPack.Data.To.iRecvCommand	 		= 67;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 		= true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 溶接電源チェック					*/
/*-  Function Name	: GD2_Recv_68						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_68( void )
{
	ComuniPack.Data.To.fWelderCheck.ALL = Rxd_DATA[0];
	ComuniPack.Data.To.iRecvCommand	 = 68;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 溶接出力指令等        			*/
/*-  Function Name	: GD2_Recv_69						*/
/*	 Create Date	: 2009/07/13						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_69( void )
{
	ComuniPack.Data.To.usWeldingCurr = ((ushort)Rxd_DATA[0] + ((ushort)Rxd_DATA[1] << 8));
	ComuniPack.Data.To.usIP          = ((ushort)Rxd_DATA[2] + ((ushort)Rxd_DATA[3] << 8));
	ComuniPack.Data.To.usPulseFreq   = ((ushort)Rxd_DATA[4] + ((ushort)Rxd_DATA[5] << 8));
    ComuniPack.Data.To.usPulseDuty  = Rxd_DATA[6] * 5; //５％刻み
	ComuniPack.Data.To.iRecvCommand	 = 69;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
    guc_0x69_rewrite_check_flag1 = 1;         
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: コントロール   					*/
/*-  Function Name	: GD2_Recv_6B						*/
/*	 Create Date	: 2009/07/13						*/
/*	 Author			: With) H.ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_6B( void )
{
	ComuniPack.Data.To.fControl.ALL  = Rxd_DATA[0];
    ComuniPack.Data.To.ucImprudenceVolt = Rxd_DATA[1];
	ComuniPack.Data.To.iRecvCommand	 = 0x6B;	    // 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: パルスモード設定					*/
/*-  Function Name	: GD2_Recv_6C						*/
/*	 Create Date	: 2006/12/21						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_6C( void )
{
     if (guc_Sequence_mode == IDLING) //2009.07.27 溶接中は溶接条件を変更できない
     {
	ComuniPack.Data.To.fPulseMode.ALL = Rxd_DATA[0];
	ComuniPack.Data.To.iRecvCommand	 = 0x6C;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新

        gtt_Okcv.New_calc = OFF;                    //2007.1.9追加
      }
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 製品検査用						*/
/*-  Function Name	: GD2_Recv_68						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_71( void )
{
	ComuniPack.Data.To.fLotCheck.ALL = Rxd_DATA[0];
	ComuniPack.Data.To.iRecvCommand	 = 71;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新

	if((Rxd_DATA[ 0 ] & 0x01) != 1){ //2007.7.23追加
		Check_G2_Send_OFF = OFF;	//製品検査用 Ver 1.11
	}else{
		Check_G2_Send_OFF = ON;	    //製品検査用 Ver 1.11
	}


	return( 0 ) ;
}

#if G3_NEW_COM
/********************************************************/
/*-- Function     	: テーブル内容要求					*/
/*-  Function Name	: GD2_Recv_81						*/
/*	 Create Date	: 2006/12/18						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_81( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
	GD2_Send_CMD(0xE1); //テーブル内容の送信
	ComuniPack.Data.To.iRecvCommand	 = 81;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 特殊テーブル内容要求				*/
/*-  Function Name	: GD2_Recv_82						*/
/*	 Create Date	: 2006/12/19						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_82( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
	GD2_Send_CMD(0xE2); //特殊テーブル内容の送信
	ComuniPack.Data.To.iRecvCommand	 = 82;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: ﾜｲﾔ径、材質、初期データ			*/
/*-  Function Name	: GD2_Recv_83						*/
/*	 Create Date	: 2006/12/21						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_83( void )
{
	ComuniPack.Data.To.fWireMaterial.ALL   = Rxd_DATA[0];   //ワイヤ材質
	ComuniPack.Data.To.fWelding.ALL        = Rxd_DATA[1];   //溶接法
	ComuniPack.Data.To.fWireDiameter.ALL   = Rxd_DATA[2];   //ワイヤ径
	ComuniPack.Data.To.fWireSelect.ALL     = Rxd_DATA[3];   //突き出し長
	ComuniPack.Data.To.fInitialSelect1.ALL = Rxd_DATA[4];   //一元／個別選択
	ComuniPack.Data.To.iRecvCommand        = 83;            // 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData         = true;	        // 受信データ更新フラグの更新
    gtt_Okcv.New_calc = OFF;
    guc_Method_rewrite_check_flag          = 1;              // 0:書き換え無しｏｒ書き換え終了 1:書き換えのため受信済み　溶接条件データ書き換え確認フラグ 2007.7.6追加
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 半固定データの書き換え			*/
/*-  Function Name	: GD2_Recv_84						*/
/*	 Create Date	: 2006/12/22						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_84( void )
{
#if 0
    gtt_Com_rewrite_data.Hfix_no           = Rxd_DATA[0];
    gtt_Com_rewrite_data.Hfix_data         = (unsigned short)(Rxd_DATA[1]) & 0x00ff;
    gtt_Com_rewrite_data.Hfix_data         |= ((unsigned short)(Rxd_DATA[2]) << 8) & 0xff00;
#endif
    gtt_Com_rewrite_data.Hfix_no           = (unsigned short)(Rxd_DATA[0]) & 0x00ff;
    gtt_Com_rewrite_data.Hfix_no           |= (unsigned short)(Rxd_DATA[1] << 8) & 0xff00;
    gtt_Com_rewrite_data.Hfix_data         = (unsigned short)(Rxd_DATA[2]) & 0x00ff;
    gtt_Com_rewrite_data.Hfix_data         |= ((unsigned short)(Rxd_DATA[3]) << 8) & 0xff00;
	ComuniPack.Data.To.iRecvCommand        = 84;            // 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData         = true;	        // 受信データ更新フラグの更新
    guc_Hfix_rewrite_check_flag            = 1;             // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 半固定データ書き換え確認フラグ
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 可変データの書き換え			　　*/
/*-  Function Name	: GD2_Recv_85						*/
/*	 Create Date	: 2006/12/22						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_85( void )
{
    if (gtt_Com_rewrite_data.Bank == 0)
    {
        gtt_Com_rewrite_data.Val_no0            = Rxd_DATA[0];
        //a
        gtt_Com_rewrite_data.Val_a_data0        =   (unsigned int)(Rxd_DATA[1])         & 0x000000ff;
        gtt_Com_rewrite_data.Val_a_data0        |= ((unsigned int)(Rxd_DATA[2]) << 8)   & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_a_data0        |= ((unsigned int)(Rxd_DATA[3]) << 16)  & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_a_data0        |= ((unsigned int)(Rxd_DATA[4]) << 24)  & 0xff000000; 
        //b
        gtt_Com_rewrite_data.Val_b_data0        =   (unsigned int)(Rxd_DATA[5])         & 0x000000ff;
        gtt_Com_rewrite_data.Val_b_data0        |= ((unsigned int)(Rxd_DATA[6]) << 8)   & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_b_data0        |= ((unsigned int)(Rxd_DATA[7]) << 16)  & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_b_data0        |= ((unsigned int)(Rxd_DATA[8]) << 24)  & 0xff000000; 
        //c
        gtt_Com_rewrite_data.Val_c_data0        =   (unsigned int)(Rxd_DATA[9])         & 0x000000ff;
        gtt_Com_rewrite_data.Val_c_data0        |= ((unsigned int)(Rxd_DATA[10]) << 8)  & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_c_data0        |= ((unsigned int)(Rxd_DATA[11]) << 16) & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_c_data0        |= ((unsigned int)(Rxd_DATA[12]) << 24) & 0xff000000; 
        //min
        gtt_Com_rewrite_data.Val_min_data0      =   (unsigned int)(Rxd_DATA[13])        & 0x000000ff;
        gtt_Com_rewrite_data.Val_min_data0      |= ((unsigned int)(Rxd_DATA[14]) << 8)  & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_min_data0      |= ((unsigned int)(Rxd_DATA[15]) << 16) & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_min_data0      |= ((unsigned int)(Rxd_DATA[16]) << 24) & 0xff000000; 
        //max
        gtt_Com_rewrite_data.Val_max_data0      =   (unsigned int)(Rxd_DATA[17])        & 0x000000ff;
        gtt_Com_rewrite_data.Val_max_data0      |= ((unsigned int)(Rxd_DATA[18]) << 8)  & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_max_data0      |= ((unsigned int)(Rxd_DATA[19]) << 16) & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_max_data0      |= ((unsigned int)(Rxd_DATA[20]) << 24) & 0xff000000; 
 
        guc_Val_rewrite_check_flag0             = 1;             // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
        gtt_Com_rewrite_data.Bank = 1;
    } else {
        gtt_Com_rewrite_data.Val_no1            = Rxd_DATA[0];
        //a
        gtt_Com_rewrite_data.Val_a_data1        =   (unsigned int)(Rxd_DATA[1])         & 0x000000ff;
        gtt_Com_rewrite_data.Val_a_data1        |= ((unsigned int)(Rxd_DATA[2]) << 8)   & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_a_data1        |= ((unsigned int)(Rxd_DATA[3]) << 16)  & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_a_data1        |= ((unsigned int)(Rxd_DATA[4]) << 24)  & 0xff000000; 
        //b
        gtt_Com_rewrite_data.Val_b_data1        =   (unsigned int)(Rxd_DATA[5])         & 0x000000ff;
        gtt_Com_rewrite_data.Val_b_data1        |= ((unsigned int)(Rxd_DATA[6]) << 8)   & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_b_data1        |= ((unsigned int)(Rxd_DATA[7]) << 16)  & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_b_data1        |= ((unsigned int)(Rxd_DATA[8]) << 24)  & 0xff000000; 
        //c
        gtt_Com_rewrite_data.Val_c_data1        =   (unsigned int)(Rxd_DATA[9])         & 0x000000ff;
        gtt_Com_rewrite_data.Val_c_data1        |= ((unsigned int)(Rxd_DATA[10]) << 8)  & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_c_data1        |= ((unsigned int)(Rxd_DATA[11]) << 16) & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_c_data1        |= ((unsigned int)(Rxd_DATA[12]) << 24) & 0xff000000; 
        //min
        gtt_Com_rewrite_data.Val_min_data1      =   (unsigned int)(Rxd_DATA[13])        & 0x000000ff;
        gtt_Com_rewrite_data.Val_min_data1      |= ((unsigned int)(Rxd_DATA[14]) << 8)  & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_min_data1      |= ((unsigned int)(Rxd_DATA[15]) << 16) & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_min_data1      |= ((unsigned int)(Rxd_DATA[16]) << 24) & 0xff000000; 
        //max
        gtt_Com_rewrite_data.Val_max_data1      =   (unsigned int)(Rxd_DATA[17])        & 0x000000ff;
        gtt_Com_rewrite_data.Val_max_data1      |= ((unsigned int)(Rxd_DATA[18]) << 8)  & 0x0000ff00; 
        gtt_Com_rewrite_data.Val_max_data1      |= ((unsigned int)(Rxd_DATA[19]) << 16) & 0x00ff0000; 
        gtt_Com_rewrite_data.Val_max_data1      |= ((unsigned int)(Rxd_DATA[20]) << 24) & 0xff000000; 

        guc_Val_rewrite_check_flag1             = 1;             // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 可変データ書き換え確認フラグ
        gtt_Com_rewrite_data.Bank = 0;
   }


	ComuniPack.Data.To.iRecvCommand        = 84;            // 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData         = true;	        // 受信データ更新フラグの更新
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 半固定、可変データリセット		*/
/*-  Function Name	: GD2_Recv_86						*/
/*	 Create Date	: 2006/12/22						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_86( void )
{
//--------- IIF by @Tny 2008/08/26 ------------
#if true
    if(gb_IIF_Select){  // IIF接続を確認
        //
        // IIF Good Morning
        //
    	unsigned char a;
	    a = Rxd_DATA[ 0 ];
    	ComuniPack.Data.bRS422Connection	= true;	// ＲＳ４２２側回線接続状態
    }
    else{
    	unsigned char a;
	    a = Rxd_DATA[ 0 ];
        guc_Hfix_val_reset_flag                = ON;  // 半固定、可変データリセット
    }
#else
	unsigned char a;
	a = Rxd_DATA[ 0 ];
    guc_Hfix_val_reset_flag                = ON;  // 半固定、可変データリセット
#endif
//--------------------------------------------
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 微調整項目１設定　　　　　　　　　*/
/*-  Function Name	: GD2_Recv_87						*/
/*	 Create Date	: 2006/12/22						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_87( void )
{
	ComuniPack.Data.To.vTsoAdj  =   Rxd_DATA[0];    // 短絡初期時間調整
	ComuniPack.Data.To.vIscAdj	=	Rxd_DATA[1];	// 短絡電流屈曲点微調整
	ComuniPack.Data.To.vIsl1Adj	=	Rxd_DATA[2];	// 短絡電流第１勾配微調整
	ComuniPack.Data.To.vIsl2Adj	=	Rxd_DATA[3];	// 短絡電流第２勾配微調整
    ComuniPack.Data.To.vTspAdj  =   Rxd_DATA[4];    // 突っ掛かり防止時間調整
	ComuniPack.Data.To.vIacAdj	=	Rxd_DATA[5];	// アーク再生直後電流微調整
	ComuniPack.Data.To.iRecvCommand	 = 87;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
    guc_Adj1_rewrite_check_flag             = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目１書き換え確認フラグ 2007.2.5追加
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 微調整項目２設定					*/
/*-  Function Name	: GD2_Recv_88						*/
/*	 Create Date	: 2006/12/22						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_88( void )
{
	ComuniPack.Data.To.vIhotAdj     =   Rxd_DATA[0];    // ホット電流調整
	ComuniPack.Data.To.vVhotAdj		=	Rxd_DATA[1];	// ホット電圧微調整
	ComuniPack.Data.To.vHotTime     =   Rxd_DATA[2];    // ホットタイム
	ComuniPack.Data.To.vSldnAdj		=	Rxd_DATA[3];	// スローダウン速度微調整
	ComuniPack.Data.To.vFttAdj		=	Rxd_DATA[4];	// ＦＴＴレベル微調整
	ComuniPack.Data.To.vBarnBackAdj	=	Rxd_DATA[5];	// バーンバック時間微調整
	ComuniPack.Data.To.iRecvCommand	 = 88;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
    guc_Adj2_rewrite_check_flag             = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＣＯ２テーブル切替				*/
/*-  Function Name	: GD2_Recv_89						*/
/*	 Create Date	: 2007/02/09						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_89( void ) //2007.2.9
{
	ComuniPack.Data.To.vTableChange  =   Rxd_DATA[0];    // ＣＯ２テーブル切り替え　０：ＣＯ２　１：ＨＧ－ＣＯ２
	ComuniPack.Data.To.iRecvCommand	 = 89;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
    guc_Table_change_flag            = 1;       // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み テーブル切り替え確認フラグ 2007.2.9
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 拡張溶接微調パラメータ            */
/*-  Function Name	: GD2_Recv_8A						*/
/*	 Create Date	: 2007/05/11						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_8A( void ) //2007.5.11　2007.5.29変更
{
   unsigned short pus_Id_work;
   unsigned short pus_Data_work;

    pus_Id_work     = (unsigned short)(Rxd_DATA[0]) & 0x00ff;        // 受信データ書き込み ID下位
    pus_Id_work    |= (unsigned short)(Rxd_DATA[1] << 8) & 0xff00;   // 受信データ書き込み ID上位
    ComuniPack.Data.To.Id_no = pus_Id_work;                          // ＩＤ番号の取得

    pus_Data_work   = (unsigned short)(Rxd_DATA[2]) & 0x00ff;        // 受信データ書き込み DATA下位
    pus_Data_work  |= (unsigned short)(Rxd_DATA[3] << 8) & 0xff00;   // 受信データ書き込み DATA上位

    switch (pus_Id_work)
    {
            case 1:
                 ComuniPack.Data.To.Sp_current      = (short)pus_Data_work; //ＳＰ電流
                 break;
            case 2:
                 ComuniPack.Data.To.Sp_time         = (short)pus_Data_work; //ＳＰ時間
                 break;
            case 3:
                 ComuniPack.Data.To.Eli             = (short)pus_Data_work; //ＥＬＩ
                 break;
            case 4:
                 //ComuniPack.Data.To.Mts_v           = (short)pus_Data_work; //重畳電圧値 del 2009.07.14
                 break;
            case 5:
                 //ComuniPack.Data.To.Mts_ontime      = (short)pus_Data_work; //重畳電圧ＯＮ時間 del 2009.07.14
                 break;
            case 6:
                 //ComuniPack.Data.To.Mts_cycle       = (short)pus_Data_work; //重畳電圧周期 del 2009.07.14
                 break;
            case 7://2009.07.10
                 //ComuniPack.Data.To.Stdc_time       = (short)pus_Data_work; //開始ＤＣ時間 2009.01.26 del 2009.07.14
                 break;
            case 0x08: //2009.07.10
	             ComuniPack.Data.To.vVhotAdj        = (short)pus_Data_work;  // ホット電圧微調整
                 break;
            case 0x09: //2009.07.10
	             ComuniPack.Data.To.vFttAdj	        = (short)pus_Data_work;  // ＦＴＴレベル微調整
                 break;
            case 0x0a: //2009.07.10
	             ComuniPack.Data.To.vBarnBackAdj	= (short)pus_Data_work;  // バーンバック時間微調整
                 break;
            case 0x0b: //2009.07.10
	             ComuniPack.Data.To.vSldnAdj		= (short)pus_Data_work;  // スローダウン速度微調整
                 break;
            case 0x0c: //2009.07.10
	             ComuniPack.Data.To.vIsl1Adj        = (short)pus_Data_work;  // 短絡電流第１勾配微調整
                 break;
            case 0x0d: //2009.07.10
	             ComuniPack.Data.To.vIsl2Adj        = (short)pus_Data_work;	// 短絡電流第２勾配微調整
                 break;
            case 0x0e: //2009.07.10
	             ComuniPack.Data.To.vIacAdj         = (short)pus_Data_work;  // アーク再生直後電流微調整
                 break;
            case 0x0f: //2009.07.10
	             ComuniPack.Data.To.vIscAdj         = (short)pus_Data_work;	// 短絡電流屈曲点微調整
                 break;
            case 0x10: //2009.07.10
                 ComuniPack.Data.To.vIpAdj          = (short)pus_Data_work; // パルスピーク電流微調整
                 break;
            case 0x11: //2009.07.10
                 ComuniPack.Data.To.vIb1Adj         = (short)pus_Data_work; // パルス第１ベース電流微調整
                 break;
            case 0x12: //2009.07.10
                 //無効
                 break;
            case 0x13: //2009.07.10
                 ComuniPack.Data.To.vIprAdj         = (short)pus_Data_work; //パルスピーク立ち上がり微調整
                 break;
            case 0x14: //2009.07.10
                 ComuniPack.Data.To.vIpfAdj         = (short)pus_Data_work; //パルスピーク立ち下がり微調整
                 break;
            case 0x15: //2009.07.10
                 ComuniPack.Data.To.vIniIpAdj       = (short)pus_Data_work; //スタートピーク電流微調整
                 break;
            case 0x16: //2009.07.10
                 ComuniPack.Data.To.vIniIbAdj       = (short)pus_Data_work; //スタートベース電流微調整
                 break;
            case 0x17: //2009.07.10
                 ComuniPack.Data.To.vIb2Adj         = (short)pus_Data_work; //パルス第２ベース電流微調整
                 break;
            case 0x18: //2009.07.10
                 ComuniPack.Data.To.vTiprAdj        = (short)pus_Data_work; //パルス立ち上がり時間微調整
                 break;
            case 0x19: //2009.07.10
                 ComuniPack.Data.To.vTipfAdj        = (short)pus_Data_work; //パルス立ち下がり時間微調整
                 break;
            case 0x1A: //2009.07.10
                 ComuniPack.Data.To.vTipAdj         = (short)pus_Data_work; //パルスピーク立ち上がり時間微調整
                 break;
            case 0x1B: //2009.07.10
                 ComuniPack.Data.To.vTsoAdj         = (short)pus_Data_work; //短絡初期時間調整
                 break;
            case 0x1C: //2009.07.10
                 ComuniPack.Data.To.vIhotAdj        = (short)pus_Data_work; //ホット電流調整
                 break;
            case 0x1d: //2009.07.10
                 ComuniPack.Data.To.vHotTime        = (short)pus_Data_work; //ホットタイム
                 break;
            case 0x1e: //2009.07.10
                 ComuniPack.Data.To.vStartPulse     = (short)pus_Data_work; //スタートパルス有り無し
                 break;
            case 0x1f: //2009.07.10
                 ComuniPack.Data.To.vEndPulse       = (short)pus_Data_work; //エンドパルス有り無し
                 break;
            case 0x20: //2009.07.10
                 ComuniPack.Data.To.vIniPulseFreqAdj= (short)pus_Data_work; //イニシャルパルス周波数
                 break;
            case 0x21: //2009.07.10
                 ComuniPack.Data.To.vPctrlBlowAdj   = (short)pus_Data_work; //アークブロー抑制制御
                 break;
            case 0x22: //2009.07.10
                 ComuniPack.Data.To.vWirSpdAdj      = (short)pus_Data_work; //ワイヤスピード微調整
                 break;
            case 0x23: //2009.07.10
                 ComuniPack.Data.To.vWirStrAccAdj   = (short)pus_Data_work; //スタートスロープ微調整
                 break;
            case 0x24: //2009.07.10
                 ComuniPack.Data.To.vWirStrDelayAdj = (short)pus_Data_work; //ワイヤスタートディレイ微調整
                 break;
            case 0x25: //2009.07.10
                 ComuniPack.Data.To.vNeckLvlAdj     = (short)pus_Data_work; //ネックレベル微調整 
                 break;
            case 0x26: //2009.07.10
                 ComuniPack.Data.To.vWirAcDcAdj     = (short)pus_Data_work; //加速度３
                 break;
            case 0x27: //2009.07.10
                 ComuniPack.Data.To.vBbkPulseAdj    = (short)pus_Data_work; //バーンバックパルス
                 break;
            case 0x28: //2009.07.10
                 ComuniPack.Data.To.usAcFreq        = (short)pus_Data_work; //交流周波数
                 break;
            case 0x29: //2009.07.10
                 ComuniPack.Data.To.ucCleaningDuty  = (short)pus_Data_work; //クリーニング幅
                 break;
            case 0x2A: //2009.07.10
                 ComuniPack.Data.To.ucMixFreq       = (short)pus_Data_work; //MIX TIG周波数
                 break;
            case 0x2B: //2009.07.10 gtt_Internal_pack側はcharなので注意が必要
                 ComuniPack.Data.To.ucMixAcRatio    = (short)pus_Data_work; //MIX(AC)比率
                 break;
            case 0x2C: //2009.07.10
                 ComuniPack.Data.To.vIhotAdj_tig    = (short)pus_Data_work; //ホット電流調整（ＴＩＧ系）
                 break;
            case 0x2D: //2009.07.10
                 ComuniPack.Data.To.vHotTime_tig    = (short)pus_Data_work; //ホット時間調整（ＴＩＧ系）
                 break;
            case 0x2E: //2009.07.10
                 ComuniPack.Data.To.vHotSlop_tig    = (short)pus_Data_work; //ホットスロープ（ＴＩＧ系）
                 break;
            default:
                 break;
    }
    guc_Exd_adj1_rewrite_check_flag    = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 拡張溶接微調パラメータ一括        */
/*-  Function Name	: GD2_Recv_8B						*/
/*	 Create Date	: 2007/05/11						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_8B( void ) //2007.5.11 2007.5.29変更
{
    unsigned char i;
    unsigned char puc_counter;
    unsigned short pus_Id_work;
    unsigned short pus_Data_work;


    puc_counter = Rxd_DATA[0];
    for (i = 0; i < puc_counter ; i+=4)
    {
         pus_Id_work     = (unsigned short)(Rxd_DATA[i+1]) & 0x00ff;        // 受信データ書き込み ID下位
         pus_Id_work    |= (unsigned short)(Rxd_DATA[i+2] << 8) & 0xff00;   // 受信データ書き込み ID上位
         pus_Data_work   = (unsigned short)(Rxd_DATA[i+3]) & 0x00ff;        // 受信データ書き込み DATA下位
         pus_Data_work  |= (unsigned short)(Rxd_DATA[i+4] << 8) & 0xff00;   // 受信データ書き込み DATA上位
    
         switch (pus_Id_work)
         {
                 case 1:
                      ComuniPack.Data.To.Sp_current      = (short)pus_Data_work; //ＳＰ電流
                      break;
                 case 2:
                      ComuniPack.Data.To.Sp_time         = (short)pus_Data_work; //ＳＰ時間
                      break;
                 case 3:
                      ComuniPack.Data.To.Eli             = (short)pus_Data_work; //ＥＬＩ
                      break;
                 case 4:
                      //ComuniPack.Data.To.Mts_v           = (short)pus_Data_work; //重畳電圧値 del 2009.07.14 
                      break;
                 case 5:
                      //ComuniPack.Data.To.Mts_ontime      = (short)pus_Data_work; //重畳電圧ＯＮ時間 del 2009.07.14
                      break;
                 case 6:
                      //ComuniPack.Data.To.Mts_cycle       = (short)pus_Data_work; //重畳電圧周期 del 2009.07.14
                      break;
                 case 7: //2009.07.10
                      //ComuniPack.Data.To.Stdc_time       = (short)pus_Data_work; //開始ＤＣ時間 2009.01.26 del 2009.07.14
                      break;
                 case 0x08: //2009.07.10
	                  ComuniPack.Data.To.vVhotAdj        = (short)pus_Data_work;  // ホット電圧微調整
                      break;
                 case 0x09: //2009.07.10
	                  ComuniPack.Data.To.vFttAdj	     = (short)pus_Data_work;  // ＦＴＴレベル微調整
                      break;
                 case 0x0a: //2009.07.10
	                  ComuniPack.Data.To.vBarnBackAdj	 = (short)pus_Data_work;  // バーンバック時間微調整
                      break;
                 case 0x0b: //2009.07.10
	                  ComuniPack.Data.To.vSldnAdj		 = (short)pus_Data_work;  // スローダウン速度微調整
                      break;
                 case 0x0c: //2009.07.10
	                  ComuniPack.Data.To.vIsl1Adj        = (short)pus_Data_work;  // 短絡電流第１勾配微調整
                      break;
                 case 0x0d: //2009.07.10
	                  ComuniPack.Data.To.vIsl2Adj        = (short)pus_Data_work;	// 短絡電流第２勾配微調整
                      break;
                 case 0x0e: //2009.07.10
	                  ComuniPack.Data.To.vIacAdj         = (short)pus_Data_work;  // アーク再生直後電流微調整
                      break;
                 case 0x0f: //2009.07.10
	                  ComuniPack.Data.To.vIscAdj         = (short)pus_Data_work;	// 短絡電流屈曲点微調整
                      break;
                 case 0x10: //2009.07.10
                      ComuniPack.Data.To.vIpAdj          = (short)pus_Data_work; // パルスピーク電流微調整
                      break;
                 case 0x11: //2009.07.10
                      ComuniPack.Data.To.vIb1Adj         = (short)pus_Data_work; // パルス第１ベース電流微調整
                      break;
                 case 0x12: //2009.07.10
                      //無効
                      break;
                 case 0x13: //2009.07.10
                      ComuniPack.Data.To.vIprAdj         = (short)pus_Data_work; //パルスピーク立ち上がり微調整
                      break;
                 case 0x14: //2009.07.10
                      ComuniPack.Data.To.vIpfAdj         = (short)pus_Data_work; //パルスピーク立ち下がり微調整
                      break;
                 case 0x15: //2009.07.10
                      ComuniPack.Data.To.vIniIpAdj       = (short)pus_Data_work; //スタートピーク電流微調整
                      break;
                 case 0x16: //2009.07.10
                      ComuniPack.Data.To.vIniIbAdj       = (short)pus_Data_work; //スタートベース電流微調整
                      break;
                 case 0x17: //2009.07.10
                      ComuniPack.Data.To.vIb2Adj         = (short)pus_Data_work; //パルス第２ベース電流微調整
                      break;
                 case 0x18: //2009.07.10
                      ComuniPack.Data.To.vTiprAdj        = (short)pus_Data_work; //パルス立ち上がり時間微調整
                      break;
                 case 0x19: //2009.07.10
                      ComuniPack.Data.To.vTipfAdj        = (short)pus_Data_work; //パルス立ち下がり時間微調整
                      break;
                 case 0x1A: //2009.07.10
                      ComuniPack.Data.To.vTipAdj         = (short)pus_Data_work; //パルスピーク立ち上がり時間微調整
                      break;
                 case 0x1B: //2009.07.10
                      ComuniPack.Data.To.vTsoAdj         = (short)pus_Data_work; //短絡初期時間調整
                      break;
                 case 0x1C: //2009.07.10
                      ComuniPack.Data.To.vIhotAdj        = (short)pus_Data_work; //ホット電流調整
                      break;
                 case 0x1d: //2009.07.10
                      ComuniPack.Data.To.vHotTime        = (short)pus_Data_work; //ホットタイム
                      break;
                 case 0x1e: //2009.07.10
                      ComuniPack.Data.To.vStartPulse     = (short)pus_Data_work; //スタートパルス有り無し
                      break;
                 case 0x1f: //2009.07.10
                      ComuniPack.Data.To.vEndPulse       = (short)pus_Data_work; //エンドパルス有り無し
                      break;
                 case 0x20: //2009.07.10
                      ComuniPack.Data.To.vIniPulseFreqAdj= (short)pus_Data_work; //イニシャルパルス周波数
                      break;
                 case 0x21: //2009.07.10
                      ComuniPack.Data.To.vPctrlBlowAdj   = (short)pus_Data_work; //アークブロー抑制制御
                      break;
                 case 0x22: //2009.07.10
                      ComuniPack.Data.To.vWirSpdAdj      = (short)pus_Data_work; //ワイヤスピード微調整
                      break;
                 case 0x23: //2009.07.10
                      ComuniPack.Data.To.vWirStrAccAdj   = (short)pus_Data_work; //スタートスロープ微調整
                      break;
                 case 0x24: //2009.07.10
                      ComuniPack.Data.To.vWirStrDelayAdj = (short)pus_Data_work; //ワイヤスタートディレイ微調整
                      break;
                 case 0x25: //2009.07.10
                      ComuniPack.Data.To.vNeckLvlAdj     = (short)pus_Data_work; //ネックレベル微調整 
                      break;
                 case 0x26: //2009.07.10
                      ComuniPack.Data.To.vWirAcDcAdj     = (short)pus_Data_work; //加速度３
                      break;
                 case 0x27: //2009.07.10
                      ComuniPack.Data.To.vBbkPulseAdj    = (short)pus_Data_work; //バーンバックパルス
                      break;
                 case 0x28: //2009.07.10
                      ComuniPack.Data.To.usAcFreq        = (short)pus_Data_work; //交流周波数
                      break;
                 case 0x29: //2009.07.10
                      ComuniPack.Data.To.ucCleaningDuty  = (short)pus_Data_work; //クリーニング幅
                      break;
                 case 0x2A: //2009.07.10
                      ComuniPack.Data.To.ucMixFreq       = (short)pus_Data_work; //MIX TIG周波数
                      break;
                 case 0x2B: //2009.07.10 gtt_Internal_pack側はcharなので注意が必要
                      ComuniPack.Data.To.ucMixAcRatio    = (short)pus_Data_work; //MIX(AC)比率
                      break;
                 case 0x2C: //2009.07.10
                      ComuniPack.Data.To.vIhotAdj_tig    = (short)pus_Data_work; //ホット電流調整（ＴＩＧ系）
                      break;
                 case 0x2D: //2009.07.10
                      ComuniPack.Data.To.vHotTime_tig    = (short)pus_Data_work; //ホット時間調整（ＴＩＧ系）
                      break;
                 case 0x2E: //2009.07.10
                      ComuniPack.Data.To.vHotSlop_tig    = (short)pus_Data_work; //ホットスロープ（ＴＩＧ系）
                      break;
                 default:
                      break;
         }
    }
    guc_Exd_adj2_rewrite_check_flag    = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み 微調項目２書き換え確認フラグ 2007.2.5追加
	return( 0 ) ;
}

/********************************************************/
/*-- Function :  溶接出力指令（電流電圧+ＥＮ比率調整量）*/
/*-  Function Name	: GD2_Recv_8C						*/
/*	 Create Date	: 2008/10/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_8C( void )
{
	ComuniPack.Data.To.usWeldingCurr = ((ushort)Rxd_DATA[0] + ((ushort)Rxd_DATA[1] << 8));
	ComuniPack.Data.To.usWeldingVolt = ((ushort)Rxd_DATA[2] + ((ushort)Rxd_DATA[3] << 8));
    ComuniPack.Data.To.ss_En_duty_adjustment = (signed short)(Rxd_DATA[4]);
    ComuniPack.Data.To.uc_En_0_mode  = Rxd_DATA[5]; //2008.11.28
	ComuniPack.Data.To.iRecvCommand	 = 0x8C;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function       : ＥＮ比率計算結果問い合わせ        */
/*-  Function Name	: GD2_Recv_8D						*/
/*	 Create Date	: 2008/10/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_8D( void )
{
	ComuniPack.Data.To.us_Q_WeldingCurr        = ((ushort)Rxd_DATA[0] + ((ushort)Rxd_DATA[1] << 8)); //2008.11.28
    ComuniPack.Data.To.ss_Q_en_duty_adjustment = (signed short)(Rxd_DATA[2]); //2008.11.28
    ComuniPack.Data.To.uc_Q_En_0_mode            = Rxd_DATA[3]; //2008.11.28
	gtt_En.uc_En_inquiry                     = 1; //2008.11.28
	ComuniPack.Data.To.iRecvCommand	 = 0x8D;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}

/********************************************************/
/*-- Function       : ＡＣ判別                          */
/*-  Function Name	: GD2_Recv_8E						*/
/*	 Create Date	: 2008/10/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char GD2_Recv_8E( void )
{
	//guc_Ac_distinction = Rxd_DATA[0];
	if (Rxd_DATA[0] == 0x01)
    {
        guc_Pulse_mode_data = guc_Pulse_mode_data | 0x80; //ＡＣモード
    } else {
        guc_Pulse_mode_data = guc_Pulse_mode_data & 0x7f; //ＤＣモード
    }
	ComuniPack.Data.To.iRecvCommand	 = 0x8E;		// 受信コマンド（データ更新判別用）の記憶
	ComuniPack.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}



#endif

//------------------------
//  End of GD2Rcv4.c
//------------------------

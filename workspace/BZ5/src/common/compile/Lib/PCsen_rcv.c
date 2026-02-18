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


/********************************************************/
/*-- Function     	: 待機中信号						*/
/*-  Function Name	: PC_Send_A6						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_A6( void )
{
	long Current ;
	unsigned char *p ;

	TX1[ TXB1_Position ].Comm = 0xA6 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ROMバージョン						*/
/*-  Function Name	: PC_Send_F2						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_B1( void )
{
	long Current ;
	unsigned char *p ;

	TX1[ TXB1_Position ].Comm = 0xB1 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;

	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

        TX1[ TXB1_Position ].Data = IdentificationCode; /*機種別コード*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (ComuniPack.Data.From.sRomVersion[0]);/*バージョン*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}


	TX1[ TXB1_Position ].Data = (ComuniPack.Data.From.sRomVersion[1] + 0x30);/*バージョン*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 溶接出力							*/
/*-  Function Name	: PC_Send_F2						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_C1( void )
{
	unsigned short Current ;
	unsigned char *p ;

	TX1[ TXB1_Position ].Comm = 0xC1 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x06 ;/*付随データ数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x02 ;/*サンプリング数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.usWeldingOutCurr & 0xff00) >> 8); /*溶接電流(上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.usWeldingOutCurr & 0x00ff); /*溶接電流（下位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.usWeldingOutVolt & 0xff00) >> 8); /*溶接電圧（上位）2007.3.30 usWeldingVolt->usWeldingOutVolt*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.usWeldingOutVolt & 0x00ff); /*溶接電圧（下位）2007.3.30 usWeldingVolt->usWeldingOutVolt*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = ComuniPack.Data.From.ucImprudence;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x12 ;/*SUMチェック*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: モータ出力						*/
/*-  Function Name	: PC_Send_C2						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_C2( void )
{
	long Current ;

	TX1[ TXB1_Position ].Comm = 0xC2 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x03 ;/*付随データ数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x02 ;/*サンプリング数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = ComuniPack.Data.From.ucMotorCurr2; /*モータ電流 2007.3.30 .ucMotorCurrを.ucMotorCurr2に変更*/ 
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = ComuniPack.Data.From.ucMotorRPM; /*モータ回転数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x00;/*SUMチェック*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 溶接時間出力						*/
/*-  Function Name	: PC_Send_C2						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_C3( void )
{
	long Current ;

	TX1[ TXB1_Position ].Comm = 0xC3 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x07 ;/*付随データ数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWeldTimes >> 8);/*溶接回数上位*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWeldTimes & 0x00ff);/*溶接回数下位*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWeldTimerIndividual >> 8);/*溶接時間個別（上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWeldTimerIndividual & 0x00ff);/*溶接時間個別（下位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	//TX1[ TXB1_Position ].Data = (unsigned char)ComuniPack.Data.From.BackUp.usWeldTimerH; 溶接時間総合（上位)
	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.BackUp.usWeldTimer >> 16) & 0x000000ff);/*溶接時間総合（上位）2007.3.30*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	//TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWeldTimerL >> 8); 溶接時間総合（中位)
	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.BackUp.usWeldTimer >> 8) & 0x000000ff);/*溶接時間総合（中位） 2007.3.30*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	//TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWeldTimerL & 0x00ff); 溶接時間総合（下位）
	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWeldTimer & 0x000000ff);/*溶接時間総合（下位）2007.3.30*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x14 ;/*SUMチェック*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 電源異常内容出力					*/
/*-  Function Name	: PC_Send_C2						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_C4( void )
{
	long Current ;

	TX1[ TXB1_Position ].Comm = 0xC4 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x03 ;/*付随データ数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = ComuniPack.Data.From.fErrorCode1.ALL;/*溶接,送給異常検出*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = ComuniPack.Data.From.fErrorCode2.ALL;/*電源異常検出 2007.4.6変更*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = ComuniPack.Data.From.fErrorCode3.ALL;/*異常・停止信号検出 2007.4.6変更*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x14 ;/*SUMチェック*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 溶接時間出力						*/
/*-  Function Name	: PC_Send_C2						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_C5( void )
{
	long Current ;

	TX1[ TXB1_Position ].Comm = 0xC5 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x04 ;/*付随データ数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.BackUp.usWireFeed >> 24) & 0xff);/*送給量（最上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.BackUp.usWireFeed >> 16) & 0xff);/*送給量（上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.BackUp.usWireFeed >> 8) & 0xff);/*送給量（中位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.BackUp.usWireFeed & 0xff);/*送給量（下位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x15 ;/*SUMチェック*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 溶接電流電圧指示値				*/
/*-  Function Name	: PC_Send_D1						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_D1( void )
{
	long Current ;
	unsigned char *p ;

	TX1[ TXB1_Position ].Comm = 0xD1 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x04 ;/*付随データ数*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.usWeldingCurr >> 8);/*溶接電流(上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.usWeldingCurr & 0x00ff);/*溶接電流（下位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.usWeldingVolt >> 8);/*溶接電圧（上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.usWeldingVolt & 0x00ff) ;/*溶接電圧（下位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x15 ;/*SUMチェック*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＣＫデータ送信					*/
/*-  Function Name	: PC_Send_E8						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_E8( void )
{

	TX1[ TXB1_Position ].Comm = 0xE8 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;

	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;

}

/*チェッカー用通信コマンド*/

/********************************************************/
/*-- Function     	: Ia0								*/
/*-  Function Name	: PC_Send_E1						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_E1( void )
{

	TX1[ TXB1_Position ].Comm = 0xE1 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((ComuniPack.Data.From.usWeldingOutCurr & 0xff00) >> 8);/*溶接電流(上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(ComuniPack.Data.From.usWeldingOutCurr & 0x00ff);/*溶接電流（下位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;

}
/********************************************************/
/*-- Function     	: Ia1,Aw,Va0,Va1,Vw	,Vp				*/
/*-  Function Name	: PC_Send_E2						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_E2( void )
{

	TX1[ TXB1_Position ].Comm = 0xE2 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0;	// @@@@@ (unsigned char)(AD1DT0 >> 2); Ia1
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0;	// @@@@@ (unsigned char)(AD0DT0 >> 2); Aw
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0;	// @@@@@ (unsigned char)(AD1DT1 >> 2); Va0
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0;	// @@@@@ (unsigned char)(AD1DT3 >> 2); Va1
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(AD0DT1 >> 2);/*Vw*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}


	TX1[ TXB1_Position ].Data = (unsigned char)(AD0DT2 >> 2);/*Vp*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;

}

/********************************************************/
/*-- Function     	: AN7,AN8,AN9,AN10					*/
/*-  Function Name	: PC_Send_E3						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_E3( void )
{

	TX1[ TXB1_Position ].Comm = 0xE3 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(AD0DT3 >> 2);/*AN7*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(AD0DT4 >> 2);/*AN8*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(AD0DT5 >> 2);/*AN9*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(AD0DT6 >> 2);/*AN10*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;

}
/********************************************************/
/*-- Function     	: CN13,CN9,CN17						*/
/*-  Function Name	: PC_Send_E4						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_E4( void )
{

	TX1[ TXB1_Position ].Comm = 0xE4 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = ( P4DATA & 0x4d);/*CN13*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = 0x00; // @@@@@@ P16DATA; CN9
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = P13DATA;/*CN17*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;

}


/********************************************************/
/*-- Function     	: Ia0								*/
/*-  Function Name	: PC_Send_E1						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_E5( void )
{

	TX1[ TXB1_Position ].Comm = 0xE5 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((gui_Send_work & 0xff00) >> 8);/*溶接電流(上位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)(gui_Send_work & 0x00ff);/*溶接電流（下位）*/
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;

}



/********************************************************/
/*-- Function     	: Ia0								*/
/*-  Function Name	: PC_Send_E1						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_F5( void )
{

	TX1[ TXB1_Position ].Comm = 0xF5 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((precurr & 0xff00) >> 8);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}
	TX1[ TXB1_Position ].Data = (unsigned char)(precurr & 0x00ff);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}


	TX1[ TXB1_Position ].Data = (unsigned char)((currfb & 0xff00) >> 8);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}
	TX1[ TXB1_Position ].Data = (unsigned char)(currfb & 0x00ff);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}


	TX1[ TXB1_Position ].Data = (unsigned char)((voltfb & 0xff00) >> 8);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}
	TX1[ TXB1_Position ].Data = (unsigned char)(voltfb & 0x00ff);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}


	TX1[ TXB1_Position ].Data = (unsigned char)((pwm & 0xff00) >> 8);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}
	TX1[ TXB1_Position ].Data = (unsigned char)(pwm & 0x00ff);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	return( 0 ) ;

}


/********************************************************/
/*-- Function     	: 半固定パラメータ返信				*/
/*-  Function Name	: PC_Send_F6						*/
/*	 Create Date	: 08/06/03							*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Send_F6( void )
{

	TX1[ TXB1_Position ].Comm = 0xF6 ;
	TX1[ TXB1_Position ].Data = 0x00 ;
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x02 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x02 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}

	TX1[ TXB1_Position ].Data = (unsigned char)((gus_Half_pc_data & 0xff00) >> 8);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}
	TX1[ TXB1_Position ].Data = (unsigned char)(gus_Half_pc_data & 0x00ff);
	TX1[ TXB1_Position ].SendInfo1.Status.Status = 0x04 ;
	TX1[ TXB1_Position ].SendInfo1.Status.BackupStatus = 0x01 ;
	TX1[ TXB1_Position ].ACK = 0x41 ;
	TXB1_Position++ ;
	/* カウンタが最大値に達したか？ */
	if ( TXB1_Position >= TXB_BUFFER_MAX ) {
		/* 最大値に達したときはカウンタをゼロクリアする */
		TXB1_Position = 0 ;
	}
	return( 0 ) ;
}


/********************************************************/
/*-- Function     	: クレータ電流指令値(下位)			*/
/*-  Function Name	: PC_Recv_B3						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Recv_B3( void )
{
	sio_table_flagPC = ON;
	sio_table_count = 0;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: クレータ電流指令値(下位)			*/
/*-  Function Name	: PC_Recv_B3						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Recv_B4( void )
{
	sio_table_flagPC = OFF;
	return( 0 ) ;
}

/*チェッカー用通信コマンド*/
/********************************************************/
/*-- Function     	: CN17								*/
/*-  Function Name	: PC_Recv_E1						*/
/*	 Create Date	: 99/11/19							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char PC_Recv_E1( void )
{
	RD1.Buf[ 1 ] = RCV1[ RXB1_Proc_Position ].Command[ 1 ] ;
//	P6DATA = ((RD1.Data & 0x77) | P6DATA);
	return( 0 ) ;
}

//------------------------
//  End of GD2Rcv4.c
//------------------------

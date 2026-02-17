/********************************************************/
/*-- Function     	: ＲＳ４２２関連処理				*/
/*-  File Name		: IIFRcv.c							*/
/*	 Create Date	: 09/09/25							*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/*	 Note			: ＲＳ４２２ポートにデータを書き出す*/
/*					: だけのルーチン					*/
/********************************************************/
// IIF NEW	2010.09.01 by @Tny
#define	__RS422__
#include	"custom.h"

/* 関数名のつけ方 */
/* Send_xx */
/*      xx は１６進数３０～６Ｆ */
/********************************************************/
/*-- Function     	: ＡＣＫ受信						*/
/*-  Function Name	: IFF_Recv_81						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_81( void )
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
/*-  Function Name	: IIF_Recv_82						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_82( void )
{
	SND_Mode = DLE_mode_SD;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 通信ＢＵＳＹ  					*/
/*-  Function Name	: IIF_Recv_83						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_83( void )
{
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 送信要求      					*/
/*-  Function Name	: IIF_Recv_84						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_84( void )
{
    //GD2_Send_CMD(0x30);		    // 入力ポート設定データ送信
    gus_Iif_Detect_Timer    = 50000;   // IIF接続確認時間カウンタ：５秒
    gus_Iif_comunication_timer  = 2000;     // 200msec
	gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
    { // 表示データのバックアップ
      if(gus_Iif_BuiltIn != IIF_BUILT_IN_RENEWAL){  // Phase7 & Phase8 & Phase13 & Phase32 by 2008/09/10-2008.11.26 @Tny
#if 0 //del 2009.10.29 IIF NEW
         short   i;
         for(i=0;i<18;i++){
             BackUp16LedData[i] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
         }
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 0]  = 'I';  // Phase16 by @Tny 2008/09/22
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 1]  = '/';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 2]  = 'F';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 3]  = ' ';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 4]  = 'W';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 5]  = 'A';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 6]  = 'S';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 7]  = ' ';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 8]  = 'B';
         ComuniPackRemo.Data.From.uc_Com_16led_data[ 9]  = 'U';
         ComuniPackRemo.Data.From.uc_Com_16led_data[10]  = 'I';
         ComuniPackRemo.Data.From.uc_Com_16led_data[11]  = 'L';
         ComuniPackRemo.Data.From.uc_Com_16led_data[12]  = 'T';
         ComuniPackRemo.Data.From.uc_Com_16led_data[13]  = ' ';
         ComuniPackRemo.Data.From.uc_Com_16led_data[14]  = 'I';
         ComuniPackRemo.Data.From.uc_Com_16led_data[15]  = ('N'|0x80);
#endif
         gus_Iff_Detect_disp_timer   = 50000;                // 5sec
         gus_Iif_BuiltIn             = IIF_BUILT_IN_RENEWAL; // IIF接続記録識別子のセット
         gus_Iif_BuiltIn_write       = true;                 // IIF接続フラグの保存要求
         //REMO_Send_CMD(0x20); //2009.10.29 IIF NEW
      } else {
        if(gb_Iif_comuni_failed){ }
      }
    }
    gb_Iif_comuni_failed        = false;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 相互動作確認  					*/
/*-  Function Name	: IIF_Recv_85						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_85( void )
{
    guc_Sw_rewrite_check_flag = 2; //2009.10.14
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: Good Morning						*/
/*-  Function Name	: IIF_Recv_86						*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_86( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
	ComuniPack.Data.bRS422Connection	= true;	// ＲＳ４２２側回線接続状態 2009.10.14

	return( 0 ) ;
}
#if true // ↓ EXTERNAL IIF NEW	2010.09.01 by @Tny
/********************************************************/
/*-- Function     	: Good Morning						*/
/*-  Function Name	: IIF_Recv_87						*/
/*	 Create Date	: 2010/09/01						*/
/*	 Author			: With) M.Tanigawa					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_87( void )
{
	unsigned char a;
	a = Rxd_DATA[ 0 ];
	ComuniPack.Data.bRS422Connection	= true;	// ＲＳ４２２側回線接続状態

	return( 0 ) ;
}
#endif // ↑ EXTERNAL IIF NEW	2010.09.01 by @Tny
/********************************************************/
/*-- Function     	: ＩＮＰＵＴデータ      			*/
/*-  Function Name	: IIF_Recv_8A						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_8A( void )
{
  if(gb_Iif_comuni_failed == false){	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
//	ComuniPackIif.Data.To.uc_Iif_input_data = Rxd_DATA[0];
//	ComuniPackIif.Data.To.uc_Iif_input_data = (~(Rxd_DATA[0]));	// 2011.02.24 by @Tny
	ComuniPackIif.Data.To.us_Iif_input_data = ((~(Rxd_DATA[0] + (Rxd_DATA[1] << 8))) & 0x03ff);	// 2011.02.24 by @Tny	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny

	ComuniPackIif.Data.To.iRecvCommand	= 0x8A;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData   = true;	// 受信データ更新フラグの更新
    //if(gb_Iif_comuni_failed == false){
    //   GD2_Send_CMD(0x20); // OUTPUTデータ送信
    //}
    gus_Iif_comunication_timer  = 2000; // 200msec
	gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
    if(gb_Iif_Input == false) guc_Init_wait_sequence  = 20000;     // 初期シーケンス待ち時間：2sec
    gb_Iif_Input    = true; // IIFデータ受信フラグ
    gus_Iif_Detect_Timer    = 50000;   // IIF接続確認時間カウンタ：５秒
    gtt_Ctrl_flag.Iif_first_rcv = ON; //2009.10.20
  }// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＮＡＬＯＧデータ      			*/
/*-  Function Name	: IIF_Recv_8B						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_8B( void )
{
    unsigned char puc_Ch_no;
    puc_Ch_no = Rxd_DATA[ 0 ];
	ComuniPackIif.Data.To.us_Analog_data[puc_Ch_no] = ((ushort)Rxd_DATA[1] + ((ushort)Rxd_DATA[2] << 8));
	ComuniPackIif.Data.To.iRecvCommand	 = 0x8B;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＮＡＬＯＧ入力補正量データ      */
/*-  Function Name	: IIF_Recv_8C						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_8C( void )
{
	ComuniPackIif.Data.To.us_Iif_analog_revise[1] = ((ushort)Rxd_DATA[0] + ((ushort)Rxd_DATA[1] << 8));
	ComuniPackIif.Data.To.us_Iif_analog_revise[2] = ((ushort)Rxd_DATA[2] + ((ushort)Rxd_DATA[3] << 8));
	ComuniPackIif.Data.To.us_Iif_analog_revise[3] = ((ushort)Rxd_DATA[4] + ((ushort)Rxd_DATA[5] << 8));
	ComuniPackIif.Data.To.us_Iif_analog_revise[4] = ((ushort)Rxd_DATA[6] + ((ushort)Rxd_DATA[7] << 8));
	ComuniPackIif.Data.To.iRecvCommand	 = 0x8C;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＤＳＷデータ                      */
/*-  Function Name	: IIF_Recv_8D						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_8D( void )
{
	ComuniPackIif.Data.To.t_Iif_dsw.ALL      = Rxd_DATA[0];
	ComuniPackIif.Data.To.uc_Iif_volt_jumper = Rxd_DATA[1];
	ComuniPackIif.Data.To.iRecvCommand	 = 0x8D;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＯＵＴＰＵＴ割付用（ＰＣ）        */
/*-  Function Name	: IIF_Recv_A0						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A0( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA0;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＩＮＰＵＴ割付用（ＰＣ）          */
/*-  Function Name	: IIF_Recv_A1						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A1( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA1;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＮＡＬＯＧ割付用（ＰＣ）        */
/*-  Function Name	: IIF_Recv_A2						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A2( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA2;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＯＵＴＰＵＴチャンネル名（ＰＣ）  */
/*-  Function Name	: IIF_Recv_A3						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A3( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA3;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＩＮＰＵＴチャンネル名（ＰＣ）    */
/*-  Function Name	: IIF_Recv_A4						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A4( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA4;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＮＡＬＯＧチャンネル名（ＰＣ）  */
/*-  Function Name	: IIF_Recv_A5						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A5( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA5;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＯＵＴＰＵＴ名編集リセット（ＰＣ）*/
/*-  Function Name	: IIF_Recv_A6						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A6( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA6;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＩＮＰＵＴ名編集リセット（ＰＣ）  */
/*-  Function Name	: IIF_Recv_A7						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A7( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA7;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＮＡＬＯＧ名編集リセット（ＰＣ）*/
/*-  Function Name	: IIF_Recv_A8						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A8( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA8;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 現状ＯＵＴＰＵＴ名要求（ＰＣ）    */
/*-  Function Name	: IIF_Recv_A9						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_A9( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xA9;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 現状ＩＮＰＵＴ名要求（ＰＣ）      */
/*-  Function Name	: IIF_Recv_AA						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_AA( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xAA;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 現状ＡＮＡＬＯＧ名要求（ＰＣ）    */
/*-  Function Name	: IIF_Recv_AB						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_AB( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xAB;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ　エリア１（ＰＣ）*/
/*-  Function Name	: IIF_Recv_B0						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_B0( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xB0;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ　エリア２（ＰＣ）*/
/*-  Function Name	: IIF_Recv_B1						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_B1( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xB1;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ　エリア３（ＰＣ）*/
/*-  Function Name	: IIF_Recv_B2						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_B2( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xB2;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ　出力端子（ＰＣ）*/
/*-  Function Name	: IIF_Recv_B3						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_B3( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xB3;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力配線データ（ＰＣ）            */
/*-  Function Name	: IIF_Recv_B4						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_B4( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xB4;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: アナログ入力補正データ（ＰＣ）    */
/*-  Function Name	: IIF_Recv_B5						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_B5( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xB5;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ要求（ＰＣ）      */
/*-  Function Name	: IIF_Recv_B6						*/
/*	 Create Date	: 2009/09/25						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Recv_B6( void )
{
	ComuniPackIif.Data.To.iRecvCommand	 = 0xB6;	// 受信コマンド（データ更新判別用）の記憶
	ComuniPackIif.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}



//------------------------
//  End of GD2Rcv4.c
//------------------------

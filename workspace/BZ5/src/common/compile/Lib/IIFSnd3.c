/********************************************************/
/*-- Function     	: ＲＳ４２２関連処理				*/
/*-  File Name		: IIFSnd3.c	    					*/
/*	 Create Date	: 09/09/29							*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/*	 Note			: ＲＳ４２２ポートにデータを書き出す*/
/*					: だけのルーチン					*/
/********************************************************/
// IIF NEW	2010.09.01 by @Tny
#define	__RS422__
#include	"custom.h"


/********************************************************/
/*-- Function     	: ＡＣＫ返信						*/
/*-  Function Name	: IIF_Send_11						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara	    				*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_11( void )
{
	DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＮＡＫ返信						*/
/*-  Function Name	: IIF_Send_12						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_12( void )
{
	DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 通信Ｂｕｓｙ送信  				*/
/*-  Function Name	: IIF_Send_13						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_13( void )
{
	DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 送信要求  						*/
/*-  Function Name	: IIF_Send_14						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_14( void )
{
	DATA_Length_TX = 1;/*付随データ1*/
    Txd_DATA[ 0 ]  = 0x01;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 相互動作確認送信					*/
/*-  Function Name	: IIF_Send_15						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_15( void )
{
	DATA_Length_TX = 1;/*付随データ1*/
    Txd_DATA[ 0 ]  = 0x01;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＯＵＴＰＵＴデータ送信		    */
/*-  Function Name	: IIF_Send_20						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_20( void )
{
	DATA_Length_TX = 1;/*付随データ 1*/
        Txd_DATA[0] = ComuniPackIif.Data.From.uc_Iif_output_data;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＯＵＴＰＵＴチャンネル名送信(PC)  */
/*--                : 割付内容確認用                    */
/*-  Function Name	: IIF_Send_40						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_40( void )
{
	DATA_Length_TX = 8;/*付随データ 8*/
    Txd_DATA[0] = 0x00;
    Txd_DATA[1] = 0x00;
    Txd_DATA[2] = 0x00;
    Txd_DATA[3] = 0x00;
    Txd_DATA[4] = 0x00;
    Txd_DATA[5] = 0x00;
    Txd_DATA[6] = 0x00;
    Txd_DATA[7] = 0x00;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＩＮＰＵＴチャンネル名送信(PC)    */
/*--                : 割付内容確認用                    */
/*-  Function Name	: IIF_Send_41						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_41( void )
{
	DATA_Length_TX = 8;/*付随データ 8*/
    Txd_DATA[0] = 0x00;
    Txd_DATA[1] = 0x00;
    Txd_DATA[2] = 0x00;
    Txd_DATA[3] = 0x00;
    Txd_DATA[4] = 0x00;
    Txd_DATA[5] = 0x00;
    Txd_DATA[6] = 0x00;
    Txd_DATA[7] = 0x00;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＮＡＬＯＧチャンネル名送信(PC)  */
/*--                : 割付内容確認用                    */
/*-  Function Name	: IIF_Send_42						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_42( void )
{
	DATA_Length_TX = 8;/*付随データ 8*/
    Txd_DATA[0] = 0x00;
    Txd_DATA[1] = 0x00;
    Txd_DATA[2] = 0x00;
    Txd_DATA[3] = 0x00;
    Txd_DATA[4] = 0x00;
    Txd_DATA[5] = 0x00;
    Txd_DATA[6] = 0x00;
    Txd_DATA[7] = 0x00;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＯＵＴＰＵＴチャンネル名送信(PC)  */
/*--                : 機能内容確認用                    */
/*-  Function Name	: IIF_Send_43						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_43( void )
{
	DATA_Length_TX = 7;/*付随データ 7*/
    Txd_DATA[0] = 0x00;
    Txd_DATA[1] = 0x00;
    Txd_DATA[2] = 0x00;
    Txd_DATA[3] = 0x00;
    Txd_DATA[4] = 0x00;
    Txd_DATA[5] = 0x00;
    Txd_DATA[6] = 0x00;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＩＮＰＵＴチャンネル名送信(PC)    */
/*--                : 機能内容確認用                    */
/*-  Function Name	: IIF_Send_44						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_44( void )
{
	DATA_Length_TX = 7;/*付随データ 7*/
    Txd_DATA[0] = 0x00;
    Txd_DATA[1] = 0x00;
    Txd_DATA[2] = 0x00;
    Txd_DATA[3] = 0x00;
    Txd_DATA[4] = 0x00;
    Txd_DATA[5] = 0x00;
    Txd_DATA[6] = 0x00;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＡＮＡＬＯＧチャンネル名送信(PC)  */
/*--                : 機能内容確認用                    */
/*-  Function Name	: IIF_Send_45						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_45( void )
{
	DATA_Length_TX = 7;/*付随データ 7*/
    Txd_DATA[0] = 0x00;
    Txd_DATA[1] = 0x00;
    Txd_DATA[2] = 0x00;
    Txd_DATA[3] = 0x00;
    Txd_DATA[4] = 0x00;
    Txd_DATA[5] = 0x00;
    Txd_DATA[6] = 0x00;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ送信(PC)          */
/*--                : エリア１                          */
/*-  Function Name	: IIF_Send_50						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_50( void )
{
    unsigned char puc_Index;
	DATA_Length_TX = 64;/*付随データ 64*/
    for (puc_Index = 0 ; puc_Index <= DATA_Length_TX ; puc_Index++)
    {
         Txd_DATA[puc_Index] = 0x00;
    }
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ送信(PC)          */
/*--                : エリア２                          */
/*-  Function Name	: IIF_Send_51						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_51( void )
{
    unsigned char puc_Index;
	DATA_Length_TX = 64;/*付随データ 64*/
    for (puc_Index = 0 ; puc_Index <= DATA_Length_TX ; puc_Index++)
    {
         Txd_DATA[puc_Index] = 0x00;
    }
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ送信(PC)          */
/*--                : エリア３                          */
/*-  Function Name	: IIF_Send_52						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_52( void )
{
    unsigned char puc_Index;
	DATA_Length_TX = 64;/*付随データ 64*/
    for (puc_Index = 0 ; puc_Index <= DATA_Length_TX ; puc_Index++)
    {
         Txd_DATA[puc_Index] = 0x00;
    }
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力論理式データ送信(PC)          */
/*--                : 出力端子                          */
/*-  Function Name	: IIF_Send_53						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_53( void )
{
    unsigned char puc_Index;
	DATA_Length_TX = 80;/*付随データ 80*/
    for (puc_Index = 0 ; puc_Index <= DATA_Length_TX ; puc_Index++)
    {
         Txd_DATA[puc_Index] = 0x00;
    }
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 入力配線データ送信(PC)            */
/*-  Function Name	: IIF_Send_54						*/
/*	 Create Date	: 2009/09/29						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char IIF_Send_54( void )
{
    unsigned char puc_Index;
	DATA_Length_TX = 64;/*付随データ 80*/
    for (puc_Index = 0 ; puc_Index <= DATA_Length_TX ; puc_Index++)
    {
         Txd_DATA[puc_Index] = 0x00;
    }
	return( 0 ) ;
}



//------------------------
//  End of IIFSnd3.c
//------------------------

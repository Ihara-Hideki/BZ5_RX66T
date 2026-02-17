/********************************************************/
/*-- Function     	: ＲＳ４２２関連処理				*/
/*-  File Name		: REMORcv.c							*/
/*	 Create Date	: 07/12/03							*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/*	 Note			: ＲＳ４２２ポートにデータを書き出す*/
/*					: だけのルーチン					*/
/********************************************************/
#define	__RS422__
#include	"custom.h"


//-------------------------------------------------------------------
// 新通信仕様	2019.09.02
//-------------------------------------------------------------------
///---------------------------------------
/// 通信ＡＣＫ
///---------------------------------------
unsigned char REMO_Recv_11( void )
{
	RE_SND_Mode = DLE_mode_SD;
	RE_WAIT_SD_count	= 0;

//----- Phase13 by @Tny 2008/09/18 -----
#if true
    if(RE_Txd_CMD[RE_SND_CMD_Proc] == 0x23){
        if(guc_Error_return_LED_control_A > 0){
            --guc_Error_return_LED_control_A;    // 「エラー復帰時ＬＥＤ表示制御インデックス：Ａ」の更新
        }
        else if(gb_Error_Display_Sending){   // エラー情報の送信要求がある？
        	gb_Error_blink  = true;     		// エラー点滅制御要求フラグ：セット		Phase27 by @Tny 2008.10.31  2008.11.17移植
            gb_Error_Display_Sending = false;    // エラー情報送信要求フラグ：クリア
        }
    }
#endif
//--------------------------------------------

	if ( RE_SND_CMD_Position != RE_SND_CMD_Proc ) {	
			RE_SND_CMD_Proc++;
		if ( RE_SND_CMD_Proc >= TXB_BUFFER_MAX ) {
			RE_SND_CMD_Proc = 0 ;
		}
	}

return(0);
}
///---------------------------------------
/// 通信ＮＡＫ
///---------------------------------------
unsigned char REMO_Recv_12( void )
{
	RE_SND_Mode = DLE_mode_SD;

return(0);
}
///---------------------------------------
/// Ｇｏｏｄ Ｍｏｒｎｉｎｇ
///---------------------------------------
unsigned char REMO_Recv_20( void )
{
	ComuniPackRemo.Data.bRS422Connection	= true;	// ＲＳ４２２側回線接続状態

return(0);
}
///---------------------------------------
/// スイッチデータ
///				8byte(１スイッチ／bit 0:OFF/1:ON = 64スイッチ分)
///---------------------------------------
unsigned char REMO_Recv_30( void )
{

return(0);
}
///---------------------------------------
/// ＪＯＧデータ
///				3byte(１ＪＯＧ／バイト －１：左回り／０：停止／１：右回り = 3JOG分)
///---------------------------------------
unsigned char REMO_Recv_31( void )
{

return(0);
}
///---------------------------------------
/// タッチパネル
///				12byte
///---------------------------------------
unsigned char REMO_Recv_32( void )
{

return(0);
}
///---------------------------------------
/// キーボード
///				4byte(スキャンコード)
///---------------------------------------
unsigned char REMO_Recv_40( void )
{

return(0);
}
///---------------------------------------
/// マウス
///				5byte(仮)
///---------------------------------------
unsigned char REMO_Recv_41( void )
{

return(0);
}
///---------------------------------------
/// バーコード
///				20byte
///---------------------------------------
unsigned char REMO_Recv_50( void )
{

return(0);
}
///---------------------------------------
/// QRコード
///				128byte
///---------------------------------------
unsigned char REMO_Recv_51( void )
{

return(0);
}
///---------------------------------------
/// RFID
///				20byte
///---------------------------------------
unsigned char REMO_Recv_52( void )
{

return(0);
}
///---------------------------------------
/// アナログ入力
///				4byte(2byte/CH = 2CH分)
///---------------------------------------
unsigned char REMO_Recv_60( void )
{

return(0);
}
///---------------------------------------
/// デジタル入力
///				2byte(１スイッチ／bit 0:OFF/1:ON = 16スイッチ分)
///---------------------------------------
unsigned char REMO_Recv_61( void )
{

return(0);
}
//-------------------------------------------------------------------
// 				2019.09.02
//-------------------------------------------------------------------

/* 関数名のつけ方 */
/* Send_xx */
/*      xx は１６進数３０～６Ｆ */
/********************************************************/
/*-- Function     	: ＡＣＫ受信						*/
/*-  Function Name	: REMO_Recv_80						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_80( void )
{
	RE_SND_Mode = DLE_mode_SD;
	RE_WAIT_SD_count	= 0;

//----- Phase13 by @Tny 2008/09/18 -----
#if true
    if(RE_Txd_CMD[RE_SND_CMD_Proc] == 0x23){
        if(guc_Error_return_LED_control_A > 0){
            --guc_Error_return_LED_control_A;    // 「エラー復帰時ＬＥＤ表示制御インデックス：Ａ」の更新
        }
        else if(gb_Error_Display_Sending){   // エラー情報の送信要求がある？
        	gb_Error_blink  = true;     		// エラー点滅制御要求フラグ：セット		Phase27 by @Tny 2008.10.31  2008.11.17移植
            gb_Error_Display_Sending = false;    // エラー情報送信要求フラグ：クリア
        }
    }
#endif
//--------------------------------------------

	if ( RE_SND_CMD_Position != RE_SND_CMD_Proc ) {	
			RE_SND_CMD_Proc++;
		if ( RE_SND_CMD_Proc >= TXB_BUFFER_MAX ) {
			RE_SND_CMD_Proc = 0 ;
		}
	}
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＮＡＫ受信						*/
/*-  Function Name	: REMO_Recv_81						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_81( void )
{
	RE_SND_Mode = DLE_mode_SD;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 相互動作確認受信					*/
/*-  Function Name	: REMO_Recv_82						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_82( void )
{
	RE_SND_Mode = DLE_mode_SD;
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: Good Morning						*/
/*-  Function Name	: REMO_Recv_83						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_83( void )
{
	unsigned char a;
	a = RE_Rxd_DATA[ 0 ];
	ComuniPackRemo.Data.bRS422Connection	= true;	// ＲＳ４２２側回線接続状態

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: DPS+Ver番号受信					*/
/*-  Function Name	: REMO_Recv_84						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_84( void )
{
	ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_upper      = RE_Rxd_DATA[ 0 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_mid        = RE_Rxd_DATA[ 1 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_lower      = RE_Rxd_DATA[ 2 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_upper      = RE_Rxd_DATA[ 3 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_mid        = RE_Rxd_DATA[ 4 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_lower      = RE_Rxd_DATA[ 5 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_upper16    = RE_Rxd_DATA[ 6 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_mid16      = RE_Rxd_DATA[ 7 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Dps_no_lower16    = RE_Rxd_DATA[ 8 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_upper16    = RE_Rxd_DATA[ 9 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_mid16      = RE_Rxd_DATA[ 10 ];
	ComuniPackRemo.Data.To.Dps_Ver.uc_Ver_no_lower16    = RE_Rxd_DATA[ 11 ];
    //guc_Dps_rewrite_check_flag    = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み


//@@@@@@@@@@@@@@@@@@@@@@@@@@@
// 2019.08.30
guc_Machine_no_flag = 0;
guc_Initial_display_flag = false;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@


	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: アナログ値受信        			*/
/*-  Function Name	: REMO_Recv_8A						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_8A( void )
{
    union { // ワード転送時の変換処理
        unsigned char   ByteData[2];
        unsigned short  WordData;
    } Data;

    unsigned char RemoInput_work;


#if true
	gus_RemoInput[0] = (unsigned short)RE_Rxd_DATA[0];

    RemoInput_work = (unsigned char)gus_RemoInput[0];

//   ***** ＢＰＲ１とＢＰＲ４の判別 2009.03.28 ******
        if ((gus_RemoInput[0] & 0x0080) == 0x0000) //NO11 connect
        //if ((RemoInput_work & 0x80) == 0x00) //NO11 connect
        {
            gtt_Ctrl_flag.Remo_controller_no = BPR4; //1set
        } else {
            gtt_Ctrl_flag.Remo_controller_no = BPR1; //2set
            if ((gus_RemoInput[0] & 0x0020) == 0x0020)
            {
                gtt_Ctrl_flag.Remo_controller_no = NO_CONNECT; //0set
            }
        }
        //ＢＰＲ４ＮＯ１１の断線確認
        if (gss_Select_dital[P_REMOCON_SELECT] == false) //ＢＰＲ４選択
        {
            if (gtt_Ctrl_flag.Remo_controller_no == BPR1)
            {
                gtt_Ctrl_flag.Remo_controller_no = NO_CONNECT; //0set
            }
        } else { //2009.03.30
            if (gtt_Ctrl_flag.Remo_controller_no == BPR4)
            {
                gtt_Ctrl_flag.Remo_controller_no = NO_CONNECT; //0set
            }
        }

        if(gtt_Ctrl_flag.Remo_controller_no == NO_CONNECT) // リモコン接続状態確認：非接続？
        {
	        if(gtt_Ctrl_flag.RemoteController == BPR4 || gtt_Ctrl_flag.RemoteController == BPR1) // リモコンが途中で抜かれた？
                {
		// 各電流指令値を最低値（４Ａ）にする
			unsigned short	Data = 4; //2010.01.21 4A->5Aに変更	// 2011.12.07  5A->4A <500A->300A>
            //**** 最低電流セット 2010.01.21 *****************************************
            if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
            {
                Data = MIN_CURRENT;
            }
            if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD)
           	{
               	//Data = MIN_CURRENT_AC_MIX;
               	Data = MIN_CURRENT_AC; //2011.10.01
            }
            if (guc_Method_condition_data == STD_HAND_METHOD)
            {
                Data = MIN_CURRENT_HAND;
            }
            //************************************************************************

			gtt_Internal_pack.Data.In.usWeldingCurr		= Data;
			gtt_Internal_pack.Data.In.usWeldingCratCurr	= Data;
			gtt_Internal_pack.Data.In.usWeldingInitCurr	= Data;
			gtt_Internal_pack.Data.In.usIP			= Data;

            gtt_Ctrl_flag.Remo_play_mode = OFF; //2009.03.31
            gtt_Ctrl_flag.Param_change = ON; //【ＮＯ３３】2010.03.10
		}
		gtt_Ctrl_flag.RemoteController	= NO_CONNECT;
	} else{
                if (gtt_Ctrl_flag.RemoteController == NO_CONNECT)
                {
                          gus_RemoInput[5] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[6] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[7] = 2048; //2009.03.31 1024->2048
                          gus_RemoInput[8] = 2048; //2009.03.31 1024->2048
                }
                if (gtt_Ctrl_flag.Remo_controller_no == BPR4)
                {
		    gtt_Ctrl_flag.RemoteController = BPR4;
                }
                if (gtt_Ctrl_flag.Remo_controller_no == BPR1)
                {
		    gtt_Ctrl_flag.RemoteController = BPR1;
                }
                
	}

	Data.ByteData[0] = RE_Rxd_DATA[1];
	Data.ByteData[1] = RE_Rxd_DATA[2];
	gus_RemoInput[1] = Data.WordData;

	Data.ByteData[0] = RE_Rxd_DATA[3];
	Data.ByteData[1] = RE_Rxd_DATA[4];
	gus_RemoInput[2] = Data.WordData;

	Data.ByteData[0] = RE_Rxd_DATA[5];
	Data.ByteData[1] = RE_Rxd_DATA[6];
	gus_RemoInput[3] = Data.WordData;

	Data.ByteData[0] = RE_Rxd_DATA[7];
	Data.ByteData[1] = RE_Rxd_DATA[8];
	gus_RemoInput[4] = Data.WordData;
#else
	ComuniPackRemo.Data.To.Analog.uc_No          =  RE_Rxd_DATA[0];
	ComuniPackRemo.Data.To.Analog.uc_Data_uppre  =  RE_Rxd_DATA[1];
	ComuniPackRemo.Data.To.Analog.uc_Data_lowre  =  RE_Rxd_DATA[2];

	{
		unsigned char vID = ComuniPackRemo.Data.To.Analog.uc_No;
	    Data.ByteData[0] = RE_Rxd_DATA[1];
  	Data.ByteData[1] = RE_Rxd_DATA[2];
		if(vID < 10){
		    gus_RemoInput[vID] = Data.WordData;
		}
	}
#endif


//	ComuniPackRemo.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＳＷ状態受信　        			*/
/*-  Function Name	: REMO_Recv_8B						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_8B( void )
{
//----- Phase21 by @Tny 2008/10/03 -----
#if true
    //if((guc_Initial_display_flag)&&(gb_Memory_copy_recv_ended == false)){   // 初期処理等が終了すればＪＯＧの受信を行う。
    if((guc_Initial_display_flag)){   // 初期処理等が終了すればＪＯＧの受信を行う。2009.03.16 
    	ComuniPackRemo.Data.To.t_Sw.uc_Group[0]    =  RE_Rxd_DATA[0];
	    ComuniPackRemo.Data.To.t_Sw.uc_Group[1]    =  RE_Rxd_DATA[1];
    	ComuniPackRemo.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
        guc_Sw_rewrite_check_flag    = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
    }
#endif
//--------------------------------------------
//----- Phase30 by @Tny 2008/11/25 -----
#if false //2009.01.09とりあえず番号が確定していないのでfalse
	if(guc_Sequence_mode != IDLING){
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No2	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5	= false;
//  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7	= false;
//  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 = false;
	}
#endif
//--------------------------------------------
//---------------------------------------
// リモコン接続時は以下のＳＷは効かないようにする	BP4 Phase11 by @Tny 2009.02.19
	if(gtt_Ctrl_flag.RemoteController){
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5	= false;	// 初期電流設定ＳＷ
		//ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7	= false;	// 溶接電流設定ＳＷ 2009.03.09.NO5
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9	= false;	// クレータ電流設定ＳＷ
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 = false;	// クレータ選択ＳＷ
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No13 = false;	// パルス選択ＳＷ
	}
//---------------------------------------

#if true // ↓ EXTERNAL IIF NEW	2011.02.24 by @Tny
	if(gtt_Ctrl_flag.Ext_select_cnt == ON){		// 入力許可信号がアクティブ？
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No2	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5	= false;
	  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7	= false;
	  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No13 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No14 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No15 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No16 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 = false;	// ＪＯＧ決定キー無効化
	}
#endif // ↑ EXTERNAL IIF NEW	2011.02.24 by @Tny

//-----------------------------------------------------------------------------------------------------------------------------------------------
// <NAVI Enhancements(Phase 1)> 2011.10.26 by @Tny
//
	if(
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No2)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No13)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No14)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No15)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No16)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17)
	){
		gtt_Navi.b_Navi_Disp	= false;	// ナビ表示フラグ：非表示
	}
//-----------------------------------------------------------------------------------------------------------------------------------------------

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＪＯＧ読み込み                    */
/*-  Function Name	: REMO_Recv_8C						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_8C( void )
{
    unsigned char Dummy;

#if true // ↓ EXTERNAL IIF NEW	2011.02.24 by @Tny
	if(gtt_Ctrl_flag.Ext_select_cnt != ON){		// 入力許可信号がアクティブでない？
#endif // ↑ EXTERNAL IIF NEW	2011.02.24 by @Tny
    //if((guc_Initial_display_flag)&&(gb_Memory_copy_recv_ended == false)){   // 初期処理等が終了すればＪＯＧの受信を行う。
    if((guc_Initial_display_flag)){   // 初期処理等が終了すればＪＯＧの受信を行う。2009.03.16
        Dummy = Rxd_DATA[0];
        ComuniPackRemo.Data.To.Jog.uc_Jog1 = RE_Rxd_DATA[1];
        guc_V_max = OFF; //2009.03.13
        if (ComuniPackRemo.Data.To.Jog.uc_Jog1 != 0) //ＪＯＧ１　Ｖ＿ＭＡＸ発動 2008.12.22
        {
            //gtt_Ctrl_counter.us_Jog1_timer = 20; //200ms
            gtt_Ctrl_counter.us_Jog1_timer = 5; //50ms
            gtt_Ctrl_counter.sc_Jog1++;
            //if (gtt_Ctrl_counter.sc_Jog1 > 15)
            if (gtt_Ctrl_counter.sc_Jog1 > 5) //2009.03.13 V_MAX感度アップ
            {
                //gtt_Ctrl_counter.sc_Jog1 = 15;
                gtt_Ctrl_counter.sc_Jog1 = 5; //2009.03.13 V_MAX感度アップ
                
                //ComuniPackRemo.Data.To.Jog.uc_Jog1 = ComuniPackRemo.Data.To.Jog.uc_Jog1 * 4;
                ComuniPackRemo.Data.To.Jog.uc_Jog1 = ComuniPackRemo.Data.To.Jog.uc_Jog1 * 10; //2009.03.13 V_MAX感度アップ
                guc_V_max = ON; //2009.03.13 V_MAX発動
            }
        }

        Dummy = Rxd_DATA[2];
        ComuniPackRemo.Data.To.Jog.uc_Jog2 = RE_Rxd_DATA[3];
        if (ComuniPackRemo.Data.To.Jog.uc_Jog2 != 0) //ＪＯＧ2　Ｖ＿ＭＡＸ発動 2008.12.22
        {
            //gtt_Ctrl_counter.us_Jog2_timer = 20; //200ms
            gtt_Ctrl_counter.us_Jog2_timer = 5; //50ms
            gtt_Ctrl_counter.sc_Jog2++;
            //if (gtt_Ctrl_counter.sc_Jog2 > 15)
            if (gtt_Ctrl_counter.sc_Jog2 > 5) //2009.03.13 V_MAX感度アップ
            {
                //gtt_Ctrl_counter.sc_Jog2 = 15;
                gtt_Ctrl_counter.sc_Jog2 = 5; //2009.03.13 V_MAX感度アップ
                //ComuniPackRemo.Data.To.Jog.uc_Jog2 = ComuniPackRemo.Data.To.Jog.uc_Jog2 * 4;
                ComuniPackRemo.Data.To.Jog.uc_Jog2 = ComuniPackRemo.Data.To.Jog.uc_Jog2 * 10; //2009.03.13 V_MAX感度アップ
                guc_V_max = ON; //2009.03.13 V_MAX発動
            }
        }
        guc_Jog_rewrite_check_flag    = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
    }
#if true // ↓ EXTERNAL IIF NEW	2011.02.24 by @Tny
	}
#endif // ↑ EXTERNAL IIF NEW	2011.02.24 by @Tny

	return( 0 ) ;
}


//------ Phase3 by @Tny 2008/09/05 ------
#if false	// BP4 phase13 by @Tny 2009.02.23
/********************************************************/
/*-- Function     	: ＥＥＰＲＯＭ書き込みデータ        */
/*-  Function Name	: REMO_Recv_90						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_90( void )
{
    unsigned short   i,Val,RX_Index = 0;
    union { // ワード転送時の変換処理
        unsigned char   ByteData[2];
        unsigned short  WordData;
    } Data;

    Val              = RE_Rxd_DATA[RX_Index++]; // 格納領域識別子
    Data.ByteData[1] = RE_Rxd_DATA[RX_Index++];
    Data.ByteData[0] = RE_Rxd_DATA[RX_Index++];
    Val = Data.WordData;    // 転送最大パケット数
    Data.ByteData[1] = RE_Rxd_DATA[RX_Index++];
    Data.ByteData[0] = RE_Rxd_DATA[RX_Index++];
    Val = Data.WordData;    // 転送パケット番号

    for(i=((32/FRAM_PAKECT) * (gus_Fram_Page - 1));i<((32/FRAM_PAKECT) * gus_Fram_Page);i++){
        *(gt_Memory_copy_area_Rx[gtt_Ctrl_counter.Memory_copy_area_no] + i) = RE_Rxd_DATA[RX_Index++];   // 記憶データ
    }
    ++guc_Fram_Phase;

return( 0 ) ;
}

/********************************************************/
/*-- Function     	: ＥＥＰＲＯＭ操作データ            */
/*-  Function Name	: REMO_Recv_91						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara                     */
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_91( void )
{
    unsigned char    Val;

    Val = RE_Rxd_DATA[0];  // ステータス

    switch(guc_Fram_Phase){
        case 1:{
                if(gtt_Ctrl_flag.Memory_copy_vector == false){
                    ++guc_Fram_Phase;
                    gus_Fram_Packet_Wait = 10; // 10msec
                }
                else{
                    if(Val == 0x80){ // 識別子は「ＦＲＡＭには何も書かれていない」？
                        guc_Fram_Phase = 9; // 読み込み不可のため中断
                    }
                    if(Val != gtt_Ctrl_counter.Memory_copy_area_no){ // 識別子は「選択されている記録エリア番号」ではない？
                        guc_Fram_Phase = 11; // 指定読み込み領域と記憶されている領域と違うため中断
                    }
                    else{
                        ++guc_Fram_Phase;
                        gus_Fram_Packet_Wait = 10; // 10msec
                    }
                }
                break;}
        case 3:{
                if(gtt_Ctrl_flag.Memory_copy_vector == false){
                    if(Val != 0x40){ // 識別子は「書き込み失敗」
                        ++guc_Fram_Phase;
                    }
                    else{
                        if(++guc_Fram_tx_error < 3){ // メモリ転送失敗カウンタ：失敗が合計３回未満
                            --guc_Fram_Phase; // そのパケットを再トライ
                        }
                        else{
                            guc_Fram_Phase = 11; // メモリ転送失敗
                        }
                    }
                }
                else{
                    ++guc_Fram_Phase;
                }
                break;}
        case 5:{
                if(gtt_Ctrl_flag.Memory_copy_vector == false){
                    if(Val != 0x40){ // 識別子は「書き込み失敗」
                        ++guc_Fram_Phase;
                    }
                    else{
                        if(++guc_Fram_tx_error < 3){ // メモリ転送失敗カウンタ：失敗が合計３回未満
                            guc_Fram_Phase = 0; // 最初から再トライ
                        }
                        else{
                            guc_Fram_Phase = 11; // メモリ転送失敗
                        }
                    }
                }
                else{
                    ++guc_Fram_Phase;
                }
                break;}
        case 12:{ // 指定読み込み領域と記憶されている領域と違うため中断 or メモリ転送失敗
                ++guc_Fram_Phase;
                break;}
        }

return( 0 ) ;
}
#endif
//---------------------------------------------------------------------

/********************************************************/
/*-- Function     	: ＳＷ状態受信　        			*/
/*-  Function Name	: REMO_Recv_A1						*/
/*	 Create Date	: 2009/01/09						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Recv_A1( void )
{
//----- Phase21 by @Tny 2008/10/03 -----
#if true
    //if((guc_Initial_display_flag)&&(gb_Memory_copy_recv_ended == false)){   // 初期処理等が終了すればＪＯＧの受信を行う。
    if((guc_Initial_display_flag)){   // 初期処理等が終了すればＪＯＧの受信を行う。2009.03.16
    	ComuniPackRemo.Data.To.t_Sw.uc_Group[0]    =  RE_Rxd_DATA[0];
	    ComuniPackRemo.Data.To.t_Sw.uc_Group[1]    =  RE_Rxd_DATA[1];
	    ComuniPackRemo.Data.To.t_Sw.uc_Group[2]    =  RE_Rxd_DATA[2];
    	ComuniPackRemo.Data.To.bChangeData	 = true;	// 受信データ更新フラグの更新
        guc_Sw_rewrite_check_flag    = 1;    // 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
    }
#endif
//--------------------------------------------
//--------------------------------------------------------------------
//BP4 Phase13 by @Tny 2009.02.23
	else{
		if(guc_Initial_display_flag == false){
	    	ComuniPackRemo.Data.To.t_Sw.uc_Group[1]	=  (RE_Rxd_DATA[1] & 0x0c);
			if((ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 == true)&&(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 == true)){
		        guc_Sw_rewrite_check_flag	= 1;	// 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
			}
			else{
				ComuniPackRemo.Data.To.t_Sw.uc_Group[1]	= 0;
			}
		    ComuniPackRemo.Data.To.t_Sw.uc_Group[2] =  (RE_Rxd_DATA[2] & 0x02);
			if(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 == true){
		        guc_Sw_rewrite_check_flag	= 1;	// 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
			}
		}
	}

	// サービスマンメニュー要求、又はレスキュー処理要求がある？
	if((gb_ServiceMenu)||(gb_RescueMenu)){
		//ＪＯＧスイッチ以外のスイッチ入力は全て無効
    	ComuniPackRemo.Data.To.t_Sw.uc_Group[0]	= 0;
	    ComuniPackRemo.Data.To.t_Sw.uc_Group[1]	= 0;
	    ComuniPackRemo.Data.To.t_Sw.uc_Group[2] = (RE_Rxd_DATA[2] & 0x02);
    	ComuniPackRemo.Data.To.bChangeData		= false;	// 受信データ更新フラグの更新
//		guc_Sw_rewrite_check_flag				= 0;		// 0:書き換え無し 1:書き換えのため受信済み 2:内部変数に受信内容を転送済み
		if(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 == false){	// ＪＯＧキーが離された？
//--------------------------------------------------------------------
// BP4 Phase16 by @Tny 2009.03.12
			if(gb_JogLock){// ＪＯＧ決定キー無効化フラグ：無効中？
				gb_2Line_FirstDisplay	= false;// 初回二行目表示フラグをＯＦＦ
			}
//--------------------------------------------------------------------
			gb_JogLock	= false;		// ＪＯＧ決定キー無効化フラグ：無効
		}
		else if(gb_JogLock){// ＪＯＧ決定キー無効化フラグ：無効中？
			ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 = false;	// ＪＯＧ決定キー無効化
		}
	}
//--------------------------------------------------------------------
//----- Phase30 by @Tny 2008/11/25 -----
#if false //2009.01.09とりあえず番号が確定していないのでfalse
	if(guc_Sequence_mode != IDLING){
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No2	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5	= false;
//  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7	= false;
//  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 = false;
	}
#endif
//--------------------------------------------

#if true // ↓ EXTERNAL IIF NEW	2011.02.24 by @Tny
	if(gtt_Ctrl_flag.Ext_select_cnt == ON){		// 入力許可信号がアクティブ？
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No2	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5	= false;
	  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7	= false;
	  	ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9	= false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No13 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No14 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No15 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No16 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17 = false;
		ComuniPackRemo.Data.To.t_Sw.Sw_bit.No18 = false;	// ＪＯＧ決定キー無効化
	}
#endif // ↑ EXTERNAL IIF NEW	2011.02.24 by @Tny

//-----------------------------------------------------------------------------------------------------------------------------------------------
// <NAVI Enhancements(Phase 1)> 2011.10.26 by @Tny
//
	if(
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No1)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No2)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No3)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No4)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No5)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No6)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No7)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No8)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No9)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No10)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No11)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No12)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No13)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No14)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No15)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No16)||
		(ComuniPackRemo.Data.To.t_Sw.Sw_bit.No17)
	){
		gtt_Navi.b_Navi_Disp	= false;	// ナビ表示フラグ：非表示
	}
//-----------------------------------------------------------------------------------------------------------------------------------------------

	return( 0 ) ;
}

//------------------------
//  End of REMORcv4.c
//------------------------

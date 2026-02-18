/********************************************************/
/*-- Function     	: ＲＳ４２２関連処理				*/
/*-  File Name		: REMOSnd3.c						*/
/*	 Create Date	: 00/04/13							*/
/*	 Author			: With) S.Yonemori					*/
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
unsigned char REMO_Send_91( void )
{
	RE_DATA_Length_TX = 0;/*付随データ無し*/

return(0);
}
///---------------------------------------
/// 通信ＮＡＫ
///---------------------------------------
unsigned char REMO_Send_92( void )
{
	RE_DATA_Length_TX = 0;/*付随データ無し*/

return(0);
}
///---------------------------------------
/// 画面表示
///			8Byte(画面番号n、画面番号n-n、画面番号n-n-n、画面番号n-n-n-n、… 画面番号n-n-n-n-n-n-n-n)
///---------------------------------------
unsigned char REMO_Send_A0( void )
{
	RE_DATA_Length_TX = 8;/*付随データ 8*/

return(0);
}
///---------------------------------------
/// 文字表示
//			2byte(X),2byte(Y),1byte(Size),4byte(Color),1byte(文字数),256("文字列")
///---------------------------------------
unsigned char REMO_Send_A1( void )
{
    RE_Txd_DATA[ 9] = 128;	// 文字数 @@@@@@@@
	RE_DATA_Length_TX = (10 + RE_Txd_DATA[ 9]);/*付随データ 10+n*/

return(0);
}
///---------------------------------------
/// 部品表示
///			2byte(X),2byte(Y),2byte(部品番号)
///---------------------------------------
unsigned char REMO_Send_A2( void )
{
	RE_DATA_Length_TX = 6;/*付随データ 8*/

return(0);
}
///---------------------------------------
/// ポート出力
///			1byte(出力ポート番号),1byte(出力データ 0:OFF/1:ON)
///---------------------------------------
unsigned char REMO_Send_B0( void )
{
	RE_DATA_Length_TX = 2;/*付随データ 8*/

return(0);
}
///---------------------------------------
/// 汎用（用途未定)
///			64yte(汎用データ)
///---------------------------------------
unsigned char REMO_Send_C0( void )
{
	RE_DATA_Length_TX = 64;/*付随データ 64*/

return(0);
}
//-------------------------------------------------------------------
// 				2019.09.02
//-------------------------------------------------------------------



/********************************************************/
/*-- Function     	: ＡＣＫ返信						*/
/*-  Function Name	: REMO_Send_11						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara	    				*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_11( void )
{
	RE_DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＮＡＫ返信						*/
/*-  Function Name	: REMO_Send_12						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_12( void )
{
	RE_DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 通信Ｂｕｓｙ送信  				*/
/*-  Function Name	: REMO_Send_13						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_13( void )
{
	RE_DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 送信要求  						*/
/*-  Function Name	: REMO_Send_15						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_15( void )
{
	RE_DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: 相互動作確認送信					*/
/*-  Function Name	: REMO_Send_16						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_16( void )
{
	RE_DATA_Length_TX = 0;/*付随データ無し*/
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: １６ｓｅｇＬＥＤデータ送信		*/
/*-  Function Name	: REMO_Send_20						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_20( void )
{
    unsigned char i;

	//RE_DATA_Length_TX = 13;/*付随データ 1*/
	RE_DATA_Length_TX = 18;/*付随データ 1 2008.07.18変更*/
 
//----- Phase21 by @Tny 2008/10/03 -----
#if true //2009.03.16 del
//if(gb_Memory_copy_recv_ended){
if(0){ //2009.03.17 
    RE_Txd_DATA[ 0] = 'C';
    RE_Txd_DATA[ 1] = 'M';
    RE_Txd_DATA[ 2] = 'P';
    RE_Txd_DATA[ 3] = ('L' | 0x80);;
    RE_Txd_DATA[ 4] = ' ';
    RE_Txd_DATA[ 5] = 'P';
    RE_Txd_DATA[ 6] = 'O';
    RE_Txd_DATA[ 7] = 'W';
    RE_Txd_DATA[ 8] = 'E';
    RE_Txd_DATA[ 9] = 'R';
    RE_Txd_DATA[10] = ' ';
    RE_Txd_DATA[11] = 'O';
    RE_Txd_DATA[12] = 'F';
    RE_Txd_DATA[13] = 'F';
    RE_Txd_DATA[14] = ' ';
    RE_Txd_DATA[15] = ' ';
    RE_Txd_DATA[16] = ' ';
    RE_Txd_DATA[17] = ' ';
}
else{
    //for (i = 0; i < 13; i++)
    for (i = 0; i < 18; i++) //2008.07.18変更
    {
//----- Phase7 by @Tny 2008/09/10 -----
#if true
        if((gub_System_err == ON) || (gb_15SEG_LED_Error_Disp_Hold)){   // エラー発生？ 又はエラー表示データ送信中 Phase15 by @Tny 2008/09/19
//----- Phase29 by @Tny 2008/11/21 -----
#if true
			if((guc_Error_code != PRI_LOW_VOLTAGE_ERR) || ((guc_Error_code == PRI_LOW_VOLTAGE_ERR)&&(gus_Pri_volt_err_timer <= 0))){
#endif
//--------------------------------------------
            RE_Txd_DATA[ i ] = guc_Error_Display[guc_Error_code][i];
//----- Phase15 by @Tny 2008/09/19 -----
#if true
            gb_15SEG_LED_Error_Disp_Hold    = true;   // エラー表示データ送信中フラグ
#endif
//--------------------------------------------
//----- Phase29 by @Tny 2008/11/21 -----
#if true
			}
			else{
	            if(gss_Select_dital[P_SUB_MONITOR] <= 0){
	                RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
	            }
	            else{
	                if(((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK_PULSE)) || ((gtt_End_welding_display.bProc1) && (gus_Pre_display_timer <= 0))){    // Phase19 by @Tny 2008/09/26
	                    if(i < 16)  RE_Txd_DATA[ i ] = guc_Sub_16Led_display[i];
	                    else        RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
	                }
	                else{
	                    RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
	                }
	            }
			}
#endif
//--------------------------------------------
        }
        else{
//----- Phase11 by @Tny 2008/09/16 -----
#if true
            if(gss_Select_dital[P_SUB_MONITOR] <= 0){
                RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
            }
            else{
                if(((guc_Sequence_mode > IDLING) && (guc_Sequence_mode < BURN_BACK_PULSE)) || ((gtt_End_welding_display.bProc1) && (gus_Pre_display_timer <= 0))){    // Phase19 by @Tny 2008/09/26
                    if(i < 16)  RE_Txd_DATA[ i ] = guc_Sub_16Led_display[i];
                    else        RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
                }
                else{
                    RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_16led_data[i];
                }
            }
#endif
//--------------------------------------------
        }
#endif
//--------------------------------------------
    }
}
#endif
//--------------------------------------------
//----- Phase13 by @Tny 2008/09/18 -----
#if true
        if(gb_Error_blink){
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_off_flag = 1;       // 点滅表示の有り無し
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_time     = 10;      // 点滅時点灯時間
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_off_time    = 10;      // 点滅時消灯時間
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_times       = 100;     // 点滅繰り返し回数
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no          = 8;       // 表示するブロック番号（７セグ）
            REMO_Send_CMD(0x23);
            gb_Error_blink  = false; // エラー点滅制御要求フラグの初期化
        }
#endif
//--------------------------------------------

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ７ｓｅｇＬＥＤデータ送信 			*/
/*-  Function Name	: REMO_Send_21						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_21( void )
{
    unsigned char i;
//----- Phase7 by @Tny 2008/09/10 -----
#if true
    unsigned char Data[8];
    if(gub_System_err == ON){   // エラー発生？
        Data[0] = 'E';
        Data[1] = 'r';
        Data[2] = 'r';
        Data[3] = 0;
        Data[4] = (guc_Error_code / 10);
        Data[5] = (guc_Error_code % 10);
    }
#endif
//--------------------------------------------

	RE_DATA_Length_TX = 7;/*付随データ 1*/
//----- Phase21 by @Tny 2008/10/03 -----
#if true //2009.03.16 del
//if(gb_Memory_copy_recv_ended){
if(0){
    for(i = 0; i < 7; i++){
        RE_Txd_DATA[i] = '-';
    }
}
else{
    for (i = 0; i < 7; i++)
    {
//----- Phase7 by @Tny 2008/09/10 -----
#if true
        if(gub_System_err == ON){   // エラー発生？
//----- Phase29 by @Tny 2008/11/21 -----
#if true
			if((guc_Error_code != PRI_LOW_VOLTAGE_ERR) || ((guc_Error_code == PRI_LOW_VOLTAGE_ERR)&&(gus_Pri_volt_err_timer <= 0))){
             	RE_Txd_DATA[ i ] = Data[i];
			}
			else{
             	RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_7led_data[i];
			}
#endif
//--------------------------------------------
        }
        else{
             RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_7led_data[i];
        }
#endif
//--------------------------------------------
    }
}
#endif
//--------------------------------------------

	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: ＬＥＤデータ送信	     			*/
/*-  Function Name	: REMO_Send_22						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_22( void )
{
	RE_DATA_Length_TX = 2;/*付随データ 1*/

    RE_Txd_DATA[ 0 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[0];
    RE_Txd_DATA[ 1 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[1];
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: ＬＥＤ表示制御送信（点滅）		*/
/*-  Function Name	: REMO_Send_23						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_23( void )
{
//----- Phase13 by @Tny 2008/09/18 -----
#if false // Phase27 by @Tny 2008.10.31 2008.11.17移植
    if(guc_Error_return_LED_control_A > 0){
        unsigned char   Index = guc_Error_return_LED_control_A;
        ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no             = Index;
        ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_off_flag    = gtt_LED_control_backup[Index].uc_Proc;
        ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_time        = gtt_LED_control_backup[Index].uc_ON_Time;
        ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_off_time       = gtt_LED_control_backup[Index].uc_OFF_Time;
        ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_times          = gtt_LED_control_backup[Index].uc_vCount;
    }
#endif
//--------------------------------------------
	RE_DATA_Length_TX = 5;/*付随データ 1*/
    RE_Txd_DATA[ 0 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no;
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
    //<><> 2009.11.19 IIF NEW <><>
    if (gtt_Ctrl_flag.Blink_reset == ON)
    {
        RE_Txd_DATA[ 0 ] = 0x00;
        gtt_Ctrl_flag.Blink_reset_one_shot = ON;
    }
    //<><><><><><><><><><><><><><>
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
    RE_Txd_DATA[ 1 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_off_flag;
    RE_Txd_DATA[ 2 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_time;
    RE_Txd_DATA[ 3 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_off_time;
    RE_Txd_DATA[ 4 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_times;
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: ＬＥＤ表示制御送信（ロール）  	*/
/*-  Function Name	: REMO_Send_24						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_24( void )
{
	RE_DATA_Length_TX = 0;/*付随データ 1*/
	return( 0 ) ;
}
//------ Phase3 by @Tny 2008/09/05 ------
#if false //2009.03.16 del
/********************************************************/
/*-- Function     	: ＥＥＰＲＯＭ書き込みデータ送信	*/
/*-  Function Name	: REMO_Send_30						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_30( void )
{
   short   i,TX_Index = 0;
    union { // ワード転送時の変換処理
        unsigned char   ByteData[2];
        unsigned short  WordData;
    } Data;

    //付随データ
	RE_DATA_Length_TX = (32/FRAM_PAKECT+5);
    // 格納領域識別子
    RE_Txd_DATA[TX_Index++]  = gtt_Ctrl_counter.Memory_copy_area_no;
    // 転送最大パケット数
    Data.WordData   = gt_Memory_copy_area_length[gtt_Ctrl_counter.Memory_copy_area_no];
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[0];
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[1];
    // 転送パケット番号
    Data.WordData   = gus_Fram_Page;
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[0];
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[1];

    for(i=((32/FRAM_PAKECT) * (gus_Fram_Page - 1));i<((32/FRAM_PAKECT) * gus_Fram_Page);i++){
        RE_Txd_DATA[TX_Index++] = *(gt_Memory_copy_area_Tx[gtt_Ctrl_counter.Memory_copy_area_no] + i);   // 記憶データの設定
    }

return( 0 ) ;
}

/********************************************************/
/*-- Function     	: ＥＥＰＲＯＭ操作データ送信		*/
/*-  Function Name	: REMO_Send_31						*/
/*	 Create Date	: 2007/12/03						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_31( void )
{
    short TX_Index = 0;
    union { // ワード転送時の変換処理
        unsigned char   ByteData[2];
        unsigned short  WordData;
    } Data;

	RE_DATA_Length_TX   = 5;        // 付随データ：5
    if(gtt_Ctrl_flag.Memory_copy_vector == false){
        if(gb_Fram_Proc){
            RE_Txd_DATA[TX_Index++]  = 0x10;     // 書き込み終了コマンド
        }
        else{
            RE_Txd_DATA[TX_Index++]  = 0x01;     // 書き込み要求コマンド
        }
    }
    else{
        if(gb_Fram_Proc){
            RE_Txd_DATA[TX_Index++]  = 0x20;     // 読み出し終了コマンド
        }
        else{
            RE_Txd_DATA[TX_Index++]  = 0x02;     // 読み出し要求コマンド
        }
    }
    // 転送最大パケット数
    Data.WordData   = gt_Memory_copy_area_length[gtt_Ctrl_counter.Memory_copy_area_no];
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[0];
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[1];
    // 転送パケット番号
    Data.WordData   = gus_Fram_Page;
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[0];
    RE_Txd_DATA[TX_Index++]  = Data.ByteData[1];


return( 0 ) ;
}
#endif
//---------------------------------------------------------------------
/********************************************************/
/*-- Function     	: 溶接状態データ送信	        	*/
/*-  Function Name	: REMO_Send_32						*/
/*	 Create Date	: 2008/01/22						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_32( void )
{
	RE_DATA_Length_TX = 1;/*付随データ 1*/
    if (gtt_Ctrl_flag.Pre_set == ON)
    {
        RE_Txd_DATA[ 0 ] = guc_Sequence_mode | 0x80;
    } else {
        RE_Txd_DATA[ 0 ] = guc_Sequence_mode;
    }
	return( 0 ) ;
}

//------ Phase31 by @Tny 2008.11.25 -----------------------------------
#if true
/********************************************************/
/*-- Function     	: ７セグ点滅停止要求送信	       	*/
/*-  Function Name	: REMO_Send_33						*/
/*	 Create Date	: 2008/11/25						*/
/*	 Author			: With) M.Tanigawa 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_33( void )
{
	RE_DATA_Length_TX	= 1;	// 付随データ：1
	RE_Txd_DATA[0]		= 0;
	return( 0 ) ;
}
#endif
//---------------------------------------------------------------------
/********************************************************/
/*-- Function     	: ＬＣＤ１行目データ送信      		*/
/*-  Function Name	: REMO_Send_34						*/
/*	 Create Date	: 2009/01/09						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_34( void )
{
    unsigned char i;

	RE_DATA_Length_TX = 16;/*付随データ*/

#if 0 //2009.03.16 del 
if(gb_Memory_copy_recv_ended){
    RE_Txd_DATA[ 0] = 'C';
    RE_Txd_DATA[ 1] = 'M';
    RE_Txd_DATA[ 2] = 'P';
    RE_Txd_DATA[ 3] = ('L' | 0x80);;
    RE_Txd_DATA[ 4] = ' ';
    RE_Txd_DATA[ 5] = 'P';
    RE_Txd_DATA[ 6] = 'O';
    RE_Txd_DATA[ 7] = 'W';
    RE_Txd_DATA[ 8] = 'E';
    RE_Txd_DATA[ 9] = 'R';
    RE_Txd_DATA[10] = ' ';
    RE_Txd_DATA[11] = 'O';
    RE_Txd_DATA[12] = 'F';
    RE_Txd_DATA[13] = 'F';
    RE_Txd_DATA[14] = ' ';
    RE_Txd_DATA[15] = ' ';
    RE_Txd_DATA[16] = ' ';
    RE_Txd_DATA[17] = ' ';
} else {
#endif
    for (i = 0; i < 16; i++) //2008.07.18変更
    {
        if((gub_System_err == ON) || (gb_15SEG_LED_Error_Disp_Hold)){   // エラー発生？ 又はエラー表示データ送信中 Phase15 by @Tny 2008/09/19
			if((guc_Error_code != PRI_LOW_VOLTAGE_ERR) || ((guc_Error_code == PRI_LOW_VOLTAGE_ERR)&&(gus_Pri_volt_err_timer <= 0))){
            RE_Txd_DATA[ i ] = guc_Error_Display[guc_Error_code][i];
            gb_15SEG_LED_Error_Disp_Hold    = true;   // エラー表示データ送信中フラグ
			} else {
	          RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_lcd_data1[i];
			}
        } else {
            RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_lcd_data1[i];
        }
    }
//} 2009.03.16 del
        if(gb_Error_blink){
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_off_flag = 1;       // 点滅表示の有り無し
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_time     = 10;      // 点滅時点灯時間
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_off_time    = 10;      // 点滅時消灯時間
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_times       = 100;     // 点滅繰り返し回数
            ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no          = 8;       // 表示するブロック番号（７セグ）
            REMO_Send_CMD(0x23);
            gb_Error_blink  = false; // エラー点滅制御要求フラグの初期化
        }
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＬＣＤ２行目データ送信      		*/
/*-  Function Name	: REMO_Send_35						*/
/*	 Create Date	: 2009/01/09						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_35( void )
{
    unsigned char i;

	RE_DATA_Length_TX = 16;/*付随データ*/
 
    for (i = 0; i < 16; i++) //2008.07.18変更
    {
         RE_Txd_DATA[ i ] = ComuniPackRemo.Data.From.uc_Com_lcd_data2[i];
    }
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＬＣＤ表示制御データ送信   		*/
/*-  Function Name	: REMO_Send_36						*/
/*	 Create Date	: 2009/01/09						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_36( void )	// BP4 Phase4 by @Tny 2009.01.15
{

    union { // ワード転送時の変換処理
        unsigned char   ByteData[2];
        unsigned short  WordData;
    } Data;

	RE_DATA_Length_TX = 6;/*付随データ 1*/
    RE_Txd_DATA[ 0 ] = ComuniPackRemo.Data.From.t_Lcd_cntrol_data1.uc_Line_no;
    Data.WordData	 = ComuniPackRemo.Data.From.t_Lcd_cntrol_data1.us_Blink_on_off_flag;
    RE_Txd_DATA[ 1 ] = Data.ByteData[1];	// 2019.06.10	to RZ
    RE_Txd_DATA[ 2 ] = Data.ByteData[0];	// 2019.06.10	to RZ
//    RE_Txd_DATA[ 1 ] = Data.ByteData[0];
//    RE_Txd_DATA[ 2 ] = Data.ByteData[1];
    RE_Txd_DATA[ 3 ] = ComuniPackRemo.Data.From.t_Lcd_cntrol_data1.uc_Blink_on_time;
    RE_Txd_DATA[ 4 ] = ComuniPackRemo.Data.From.t_Lcd_cntrol_data1.uc_Blink_off_time;
    RE_Txd_DATA[ 5 ] = ComuniPackRemo.Data.From.t_Lcd_cntrol_data1.uc_Blink_times;

	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＬＣＤコントラストデータ送信 		*/
/*-  Function Name	: REMO_Send_37						*/
/*	 Create Date	: 2009/01/09						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_37( void )
{
	//-----------------------------------------------------------
	//BP4 Phase9 by @Tny 2009.02.16
	RE_DATA_Length_TX = 1;										// 付随データ = 1
	RE_Txd_DATA[ 0 ] = ComuniPackRemo.Data.From.uc_Lcd_Bright;	// コントラストデータ
	//-----------------------------------------------------------
	return( 0 ) ;
}
/********************************************************/
/*-- Function     	: ＬＥＤデータ送信	     			*/
/*-  Function Name	: REMO_Send_38						*/
/*	 Create Date	: 2009/01/09						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_38( void )
{
	RE_DATA_Length_TX = 6;/*付随データ 1*/

    RE_Txd_DATA[ 0 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[0];
    RE_Txd_DATA[ 1 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[1];
    RE_Txd_DATA[ 2 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[2];
    RE_Txd_DATA[ 3 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[3];
    RE_Txd_DATA[ 4 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[4];
    RE_Txd_DATA[ 5 ] = ComuniPackRemo.Data.From.t_Led.uc_Led[5];
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: ＬＥＤデータ送信	     			*/
/*-  Function Name	: REMO_Send_39						*/
/*	 Create Date	: 2009/01/09						*/
/*	 Author			: With) H.Ihara 					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
unsigned char REMO_Send_39( void )
{
	RE_DATA_Length_TX = 6;/*付随データ 1*/

ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no;

    RE_Txd_DATA[ 0 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data3.uc_Led[0];
    RE_Txd_DATA[ 1 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data3.uc_Led[1];
    RE_Txd_DATA[ 2 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data3.uc_Led[2];
    RE_Txd_DATA[ 3 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data3.uc_Led[3];
    RE_Txd_DATA[ 4 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data3.uc_Led[4];
    RE_Txd_DATA[ 5 ] = ComuniPackRemo.Data.From.t_Led_cntrol_data3.uc_Led[5];
	return( 0 ) ;
}

/********************************************************/
/*-- Function     	: 送信コマンド記憶					*/
/*-  Function Name	: REMO_Send_CMD()					*/
/*	 Create Date	: 2001/04/11						*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: None								*/
/*	 Corrector		:									*/
/********************************************************/
void REMO_Send_CMD( unsigned char CMD_CODE )
{
	if((ComuniPackRemo.Data.bRS422Connection)||(gb_Ping_to_Controller)){	// 回線は開いている？またはコントローラ未接続確認実行？ Phase26 by @Tny 2008/10/23
		switch(CMD_CODE){
			case REMOACK_SD:
					REMO_ACK_count++;
				break;
			case REMONAK_SD:
					REMO_NAK_count++;
				break;
			case 0x13:
					REMO_Busy_count++;
				break;
			default:
                if((guc_Fram_Phase <= 0)||(CMD_CODE == 0x30)||(CMD_CODE == 0x31)){ //2009.03.16 移動

					RE_Txd_CMD[ RE_SND_CMD_Position ] = CMD_CODE;
					RE_SND_CMD_Position++;
					if ( RE_SND_CMD_Position >= TXB_BUFFER_MAX ) {
						RE_SND_CMD_Position = 0 ;
					}
                }
//----- Phase21 by @Tny 2008/10/03 -----
#if false //2009.03.16 del
                if(gus_Display_command_stop <= 0){
// Phase2(Debug) 2008/09/02 @Tny
//
#if false //2009.03.16 del
                if((guc_Fram_Phase <= 0)||(CMD_CODE == 0x30)||(CMD_CODE == 0x31)){

					RE_Txd_CMD[ RE_SND_CMD_Position ] = CMD_CODE;
					RE_SND_CMD_Position++;
					if ( RE_SND_CMD_Position >= TXB_BUFFER_MAX ) {
						RE_SND_CMD_Position = 0 ;
					}

}
#endif
//---------------------------------------------------------------------
//----- Phase13 by @Tny 2008/09/18 -----
#if false  // Phase27 by @Tny 2008.10.31 2008.11.17移植
                    if(CMD_CODE == 0x23){   // ＬＥＤ表示制御コマンド？
                        // 通常制御なら制御状態を記憶する
                        if((gb_Error_blink == false)&&(guc_Error_return_LED_control_A <= 0)){
                            if((gtt_Internal_pack.Data.Out.fErrorCode1.ALL == 0)&&(gtt_Internal_pack.Data.Out.fErrorCode2.ALL == 0)&&(gtt_Internal_pack.Data.Out.fErrorCode3.ALL == 0)){
                                unsigned char   Index = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Block_no;
                                //if(Index > 0){
                                if(Index > 0 && Index <= 8){ //2008.10.29変更
                                    gtt_LED_control_backup[Index].uc_Proc       = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_off_flag;
                                    gtt_LED_control_backup[Index].uc_ON_Time    = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_on_time;
                                    gtt_LED_control_backup[Index].uc_OFF_Time   = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_off_time;
                                    gtt_LED_control_backup[Index].uc_vCount     = ComuniPackRemo.Data.From.t_Led_cntrol_data1.uc_Blink_times;
                                }
                                else{
                                    unsigned char i;
                                    for(i=0;i<10;i++){
                                        gtt_LED_control_backup[i].uc_Proc       = 0;
                                        gtt_LED_control_backup[i].uc_ON_Time    = 0;
                                        gtt_LED_control_backup[i].uc_OFF_Time   = 0;
                                        gtt_LED_control_backup[i].uc_vCount     = 0;
                                    }
                                }
                            }
                        }
                    }
#endif
//--------------------------------------------
                }
#endif
//--------------------------------------------

		}
	}
}

//------------------------
//  End of REMOSnd3.c
//------------------------

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｔ＿ｒｏｂ＿ｃｏｍ＿ｒｃｖ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－０
//  【機能説明】
//      ロボット通信受信割り込み
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
//#define	__CPU_EXTERNAL_COMUNICATION_PROG


#include  "custom.h"

void int_rob_com_rcv(void)
{
	static long		i = 0;

	uchar 	RCV_CMD;	// 受信データ
	uchar	CMD;		// 処理用コマンドワーク


    //************ パリティ、フレーミングエラー検出　2007.2.26 ****************
    if (( S0RCNT & 0x01 ) != 0x00)               //ロボット通信（ＲＳ４２２）エラー確認
    {
       if ((S0RCNT & 0x04) == 0x04)
       {
         // パリティーエラー発生
         gtt_Ctrl_counter.Com_err_parity++;
       }
       if ((S0RCNT & 0x02) == 0x02)
       {
          // フレーミングエラー発生
         gtt_Ctrl_counter.Com_err_framing++;
       }
       if ((S0RCNT & 0x08) == 0x08)
       {
          // オーバーランエラー発生
       }
//----- Phase4 by @Tny 2008/09/08 -----
#if true
       RCV_CMD    = S0RXB;  // ダミーリード
       S0RCNT     = 0x00;
       S0RCNT     = 0x10;
#endif
//--------------------------------------------
    }
    //*************************************************************************

	if((S0RCNT & 0x20) == 0x20){	// データがバッファに存在するとき
		RCV_CMD = S0RXB;			// データレジスタからデータを入力する
// --Ｇ２用-- 
		switch(RCV_Mode){	// 受信モード
			case DLE_mode:{		// DLE受信モード
							if(RCV_CMD == DLE){
								RCV_Mode = CMD_mode;	// コマンド受信モードへ移行
							}
							data_count_rx	= 0;
							SUM_ADD_RxData	= 0;
							RCV_Position	= 0;
							DLE_check_flag	= false;
							break;
						}
			case CMD_mode:{		// コマンド受信モード
							if(ComuniPack.Data.bRS422Connection){	// 回線は開いている？
								CMD_DATA_RX 	= RCV_CMD;			// コマンドの取得
								SUM_ADD_RxData += (uchar)RCV_CMD;	// SUM値更新
								CheckCMD(CMD_DATA_RX);				// コマンド解析処理(コマンドと付随データ数のチェック)
							}
							else{	// まだ回線は開いていない。
								if(RCV_CMD == GOODMORNING){	// 受信コマンドは「ＧｏｏｄＭｏｒｎｉｎｇコマンド」？
		                           if((gb_ServiceMenu == false)&&(gb_RescueMenu == false)) //2010.03.23
                                   {
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                                    gb_IIF_Select   = false;            // IFF非接続を確認
#endif
//--------------------------------------------
                                    guc_Robot_connect_flag = true;      //ロボット接続を確認 2008.10.03
									CMD_DATA_RX 	= RCV_CMD;			// コマンドの取得
									SUM_ADD_RxData += (uchar)RCV_CMD;	// SUM値更新
									CheckCMD(CMD_DATA_RX);				// コマンド解析処理(コマンドと付随データ数のチェック)
                                    } //2010.03.23
								}else{
//--------- IIF by @Tny 2008/08/26 ------------
#if true
								    if(RCV_CMD == 0x86){    // 受信コマンドは「ＩＩＦ用ＧｏｏｄＭｏｒｎｉｎｇコマンド」？
//----- Phase4 by @Tny 2008/09/08 -----
#if true
                                        gus_Iif_comunication_timer  = 2000; // 200msec
										gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
#endif
//--------------------------------------------
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
										gb_External_IIF	= false;			// 外部拡張ユニット接続フラグ（true=外部拡張ユニット／false=ＩＩＦ）
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                                        gb_IIF_Select   = true;             // IIF接続を確認
                                        guc_Robot_connect_flag = false;     //ロボット非接続を確認 2008.10.03
    									CMD_DATA_RX 	= RCV_CMD;			// コマンドの取得
	    								SUM_ADD_RxData += (uchar)RCV_CMD;	// SUM値更新
		    							CheckCMD(CMD_DATA_RX);				// コマンド解析処理(コマンドと付随データ数のチェック)
                                    }
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
								    else if(RCV_CMD == 0x87){ // 受信コマンドは「外部拡張ユニット用ＧｏｏｄＭｏｒｎｉｎｇコマンド」？
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 5)>	2011.10.26 by @Tny
										if(gb_Iif_Disconnect == false){		// ＩＩＦ切断フラグ：切断未確定
//-------------------------------------------------
										gb_External_IIF				= true;		// 外部拡張ユニット接続フラグ（true=外部拡張ユニット／false=ＩＩＦ）
										gtt_Ctrl_counter.uc_Iif_no	= 1;		// INPUT PORT設定画面に固定
										#if true	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
										    gb_Iif_BuiltIn          = true;
									    	guc_Init_wait_sequence  = 100000;    // 初期シーケンス待ち時間：10sec
										#endif
//-----------------------------------------------------------
#if false	// ↓ <<< EXTERNAL IIF NEW >>> 2011.10.07 by @Tny
										// ↓ EXTERNAL IIF NEW	2011.02.24 by @Tny
										if( // 接続端子を固定化されているかどうか確認する
											(guc_In_port[0][1] != IIF_INPUT_BIN1)||			//再生ｃｈバイナリ１
											(guc_In_port[0][2] != IIF_INPUT_BIN2)||			//再生ｃｈバイナリ２
											(guc_In_port[0][3] != IIF_INPUT_BIN3)||			//再生ｃｈバイナリ３
											(guc_In_port[0][4] != IIF_INPUT_BIN4)||			//再生ｃｈバイナリ４
											(guc_In_port[0][5] != IIF_INPUT_BIN5)||			//再生ｃｈバイナリ５
											(guc_In_port[0][6] != IIF_INPUT_GP_IN1)||		//汎用入力１
											(guc_In_port[0][7] != IIF_INPUT_CNT)||			//入力許可信号
											(guc_In_port[0][8] != IIF_INPUT_STB)		    //ストローブ信号
										){ // 接続端子を固定化する
										// ↑ EXTERNAL IIF NEW	2011.02.24 by @Tny
										// ↓ EXTERNAL IIF NEW	2011.02.24 by @Tny
											guc_In_port[0][1] = IIF_INPUT_BIN1;			//再生ｃｈバイナリ１
											guc_In_port[0][2] = IIF_INPUT_BIN2;			//再生ｃｈバイナリ２
											guc_In_port[0][3] = IIF_INPUT_BIN3;			//再生ｃｈバイナリ３
											guc_In_port[0][4] = IIF_INPUT_BIN4;			//再生ｃｈバイナリ４
											guc_In_port[0][5] = IIF_INPUT_BIN5;			//再生ｃｈバイナリ５
											guc_In_port[0][6] = IIF_INPUT_GP_IN1;		//汎用入力１
											guc_In_port[0][7] = IIF_INPUT_CNT;			//入力許可信号
											guc_In_port[0][8] = IIF_INPUT_STB;		    //ストローブ信号
										// ↑ EXTERNAL IIF NEW	2011.02.24 by @Tny
											{ // 接続端子を全てＡ接点とする
												ushort	i;
												for(i=1;i<=8;i++){
													guc_In_port[1][i]	= 0;	// Ａ接点
												}
											}
											// 変更データを記憶する（？）
											gtt_Ctrl_flag.Param_change = ON;
										}
#endif	// ↑ <<< EXTERNAL IIF NEW >>> 2011.10.07 by @Tny
//-----------------------------------------------------------
//----- Phase4 by @Tny 2008/09/08 -----
#if true
                                        gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
#endif
//--------------------------------------------
                                        gb_IIF_Select   = true;             // IIF接続を確認
                                        guc_Robot_connect_flag = false;     //ロボット非接続を確認 2008.10.03
    									CMD_DATA_RX 	= RCV_CMD;			// コマンドの取得
	    								SUM_ADD_RxData += (uchar)RCV_CMD;	// SUM値更新
		    							CheckCMD(CMD_DATA_RX);				// コマンド解析処理(コマンドと付随データ数のチェック)
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 5)>	2011.10.26 by @Tny
										}
//-------------------------------------------------
                                    }
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                                    else{
									    RCV_Mode = DLE_mode;	// ＧｏｏｄＭｏｒｎｉｎｇ以外は受け付けない　→　DLE受信モードへ移行
                                    }
#else
									RCV_Mode = DLE_mode;	// ＧｏｏｄＭｏｒｎｉｎｇ以外は受け付けない　→　DLE受信モードへ移行
#endif
//--------------------------------------------
								}
							}
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                            if(gb_IIF_Select == false){  // IFF非接続を確認
                                if (CMD_DATA_RX == 0x8B) //2007.5.11
                                {
                                    guc_Variable_length_flag = ON;
                                }
                            }
#else
                            if (CMD_DATA_RX == 0x8B) //2007.5.11
                            {
                                guc_Variable_length_flag = ON;
                            }
#endif
//--------------------------------------------
							break;
						}
			case DATA_mode:{	// データ部受信モード
							if((RCV_CMD == DLE) && (DLE_check_flag == false)){	// データ部内でのDLEコードを受信？
								DLE_check_flag = true;	// 次データはデータ本体
							}
							else{	// データ本体を取得
								SUM_ADD_RxData += (uchar)RCV_CMD;	// SUM値更新
								Rxd_DATA[RCV_Position] = RCV_CMD;	// データの保管
								RCV_Position++;						// 受信バッファのインデックス更新
								data_count_rx++;					// データ受信数の更新
								DLE_check_flag = false;				// データ部内でのDLEコード受信判定フラグの初期化
							}

                            if (guc_Variable_length_flag == ON) //2007.5.11
                            {
                                DATA_Length_RX = RCV_CMD + 1;
                                guc_Variable_length_flag = OFF;
                            }

							if(data_count_rx >= DATA_Length_RX){	// 指定データ数を受信完了？
								RCV_Mode = SUM_mode;					// チェックサム値受信モードへ移行
							}
							break;
						}
			case SUM_mode:{		// チェックサム値受信モード
							if(RCV_CMD == SUM_ADD_RxData){	// 受信データ（受信したチェックサム値）と内部で算出したチェックサム値は同じ？
								if(sio_table_flag == false){
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                                    if(gb_IIF_Select){  // IIF接続を確認
//										if(CMD_DATA_RX == 0x84){    // 入力ポート設定データ送信要求コマンド？	EXTERNAL IIF NEW	2011.02.23 by @Tny
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
                                        gus_Iif_comunication_timer  = 2000; // 200msec
										gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
  									    (FromIIF[CMD_DATA_RX])();	// 付随データに対する処理を行う。
    								    GD2_Send_CMD(0x11);	        	// ACKチェック一致：ACK返信
#else
                                        if(CMD_DATA_RX == 0x84){    // 入力ポート設定データ送信要求コマンド？
    									    GD2_Send_CMD(0x30);		    // 入力ポート設定データ送信
//----- Phase11 by @Tny 2008/09/16 -----
#if true
                                            gus_Iif_Detect_Timer    = 50000;   // IIF接続確認時間カウンタ：５秒
#endif
//--------------------------------------------
//----- Phase4 by @Tny 2008/09/08 : Phase7 by 2008/09/10 @Tny -----
#if true
                                            gus_Iif_comunication_timer  = 2000;     // 200msec
											gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
                                            { // 表示データのバックアップ
//                                              if((gtt_Dsw.Sw.No7)||(gus_Iif_BuiltIn != IIF_BUILT_IN_RENEWAL)){  // Phase7 & Phase8 & Phase13 by 2008/09/10 @Tny
                                                if(gus_Iif_BuiltIn != IIF_BUILT_IN_RENEWAL){  // Phase7 & Phase8 & Phase13 & Phase32 by 2008/09/10-2008.11.26 @Tny
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
                                                    gus_Iff_Detect_disp_timer   = 50000;                // 5sec
                                                    gus_Iif_BuiltIn             = IIF_BUILT_IN_RENEWAL; // IIF接続記録識別子のセット
                                                    gus_Iif_BuiltIn_write       = true;                 // IIF接続フラグの保存要求
                                                    //REMO_Send_CMD(0x20);
                                                    REMO_Send_CMD(0x35); //2009.01.13
                                                }
                                                else{
                                                    if(gb_Iif_comuni_failed){
//--------- Phase20by @Tny 2008/10/01 --------
#if false
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 0]  = 'I';  // Phase16 by @Tny 2008/09/22
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 1]  = '/';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 2]  = 'F';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 3]  = ' ';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 4]  = 'L';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 5]  = 'I';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 6]  = 'N';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 7]  = 'K';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 8]  = ' ';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[ 9]  = 'R';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[10]  = 'E';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[11]  = 'V';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[12]  = 'I';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[13]  = 'V';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[14]  = 'A';
                                                        ComuniPackRemo.Data.From.uc_Com_16led_data[15]  = ('L'|0x80);
                                                        gus_Iff_Detect_disp_timer   = 30000;    // 3sec
#endif
//--------------------------------------------
                                                    }
                                                }
                                            }
                                            gb_Iif_comuni_failed        = false;
#endif
//--------------------------------------------
                                        }
                                        else if(CMD_DATA_RX == 0x8A){   // 入力データ送信コマンド？
//--------- Phase4 by @Tny 2008/09/08 --------
#if true
                                            union{
                                    	        unsigned char   Byte[2];
                                                unsigned short  Word;
                                            } ConvertData;
                                            guc_Iif_bit_input   = Rxd_DATA[0]; // Bit-Inputデータ @Tny
                                            // A/Dデータ Ch#1
                                            ConvertData.Byte[0] = Rxd_DATA[1];
                                            ConvertData.Byte[1] = Rxd_DATA[2];
                                            gus_Iif_ad_input[0] = ConvertData.Word;
                                            // A/Dデータ Ch#2
                                            ConvertData.Byte[0] = Rxd_DATA[3];
                                            ConvertData.Byte[1] = Rxd_DATA[4];
                                            gus_Iif_ad_input[1] = ConvertData.Word;
                                            // A/Dデータ Ch#3
                                            ConvertData.Byte[0] = Rxd_DATA[5];
                                            ConvertData.Byte[1] = Rxd_DATA[6];
                                            gus_Iif_ad_input[2] = ConvertData.Word;
                                            if(gb_Iif_comuni_failed == false){
        									    GD2_Send_CMD(0x20); // OUTPUTデータ送信
                                            }
#endif
//--------------------------------------------
//----- Phase4 by @Tny 2008/09/08 -----
#if true
                                            gus_Iif_comunication_timer  = 2000; // 200msec
											gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
#endif
//--------------------------------------------
//----- Phase12 by @Tny 2008/09/17 -----
#if true
                                            if(gb_Iif_Input == false) guc_Init_wait_sequence  = 20000;     // 初期シーケンス待ち時間：2sec
#endif
//--------------------------------------------
//----- Phase7 by @Tny 2008/09/08 -----
#if true
                                            gb_Iif_Input    = true; // IIFデータ受信フラグ
#endif
//--------------------------------------------
//----- Phase11 by @Tny 2008/09/16 -----
#if true
                                            gus_Iif_Detect_Timer    = 50000;   // IIF接続確認時間カウンタ：５秒
#endif
//--------------------------------------------
                                        }
                                        else{
//----- Phase4 by @Tny 2008/09/08 -----
#if true
                                            gus_Iif_comunication_timer  = 2000; // 200msec
											gus_Iif_comunication_timer  = 10000; // 200msec	// 200msec->1sec <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
#endif
//--------------------------------------------
    									    (FromGD2[CMD_DATA_RX])();	// 付随データに対する処理を行う。
	    								    GD2_Send_CMD(0x11);	        	// ACKチェック一致：ACK返信
                                        }
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                                    }
                                    else{
									    (FromGD2[CMD_DATA_RX])();	// 付随データに対する処理を行う。
									    GD2_Send_CMD(GD2ACK_SD);		// ACKチェック一致：ACK返信
                                    }
#else
									(FromGD2[CMD_DATA_RX])();	// 付随データに対する処理を行う。
									GD2_Send_CMD(GD2ACK_SD);		// ACKチェック一致：ACK返信
#endif
//--------------------------------------------
                                    gtt_Ctrl_counter.Com_err_parity   = 0; //2007.2.26追加
                                    gtt_Ctrl_counter.Com_err_framing = 0; //2007.2.26追加
								}
								else{
									switch(CMD_DATA_RX){
										case 0x48:	// 一元化データは許可 / コントローラに送信しないものは許可
										case 0x49:	// 送給量データは許可
												{
													(FromGD2[CMD_DATA_RX])();	// 付随データに対する処理を行う。
													GD2_Send_CMD(GD2ACK_SD);	// ACKチェック一致：ACK返信
                                                    gtt_Ctrl_counter.Com_err_parity   = 0; //2007.2.26追加
                                                    gtt_Ctrl_counter.Com_err_framing = 0; //2007.2.26追加
													break;
												}
										default:{
													GD2_Send_CMD(GD2Busy_SD);	// 送給装置側データ送信中付き:Busy返信
													break;
												}
									}
								}
							}
							else{
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                                if(gb_IIF_Select){  // IIF接続を確認
								    GD2_Send_CMD(0x12);     // SUMチェック不一致：NAK返信
                                }
                                else{
    								GD2_Send_CMD(GD2NAK_SD);	// SUMチェック不一致：NAK返信
                                }
#else
								GD2_Send_CMD(GD2NAK_SD);	// SUMチェック不一致：NAK返信
#endif
//--------------------------------------------
							}
							RCV_Mode = DLE_mode;	// DLE受信モードへ移行
							break;
						}
			default:	{
							RCV_Mode = DLE_mode;	// DLE受信モードへ移行
							break;
						}
		}
	}
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA0_int_rob_com_rcv.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

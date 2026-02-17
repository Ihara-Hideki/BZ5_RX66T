//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｔ＿ｐｃ＿ｃｏｍ＿ｒｃｖ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－０
//  【機能説明】
//      ＰＣ通信受信割り込み
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

char 	TOGLE_FLAG;
void int_pc_com_rcv(void)
{
	unsigned char	RCV_CMD;		/* 受信データ */
	unsigned char	CMD;			/* 処理用コマンドワーク */
        unsigned char   RCV_WORK;

	RCV_CMD  = 0;            //2006.8.30 clear
	CMD      = 0;            //2006.8.30 clear
        RCV_WORK = 0;            //2006.8.30 clear


	/* データがバッファに存在するとき */
	if((S2RCNT & 0x20) == 0x20){
		/* データレジスタからデータを入力する */
		RCV_CMD = (unsigned char)S2RXB;
		/* 受信完了 */
		SI23STAT = (SI23STAT & 0x0b);

		/* すでにおきた？ */
		if(ComuniPack.Data.bRS232Connection){
			/* すでにおきている */
			if((sio_table_flagPC == ON) && (sio_table_count <= TABLEDATA)){
				//*(&wd_wp_table + sio_table_count) = RCV_CMD; //2019.03.15 ihara del
				sio_table_count++;
			}
			else{
				for(;;){
					/* フラグが１バイト目データ受信の時 */
					if ( TOGLE_FLAG == false ) {
						/* １バイトデータ４１の時 */
						if ( RCV_CMD == 0x47 ) {
							PC_Send_B1( ) ;
							PC_Send_D1( ) ;
							PC_ps_av_flag2 = ON;
							TX1[ TXB1_Proc_Position ].ACK = 0xEB ;
							break ;
						}
						if ( RCV_CMD == 0x46 ) {/*WeldKeeper END*/
							TX1[ TXB1_Proc_Position ].ACK = 0xEB ;
							ComuniPack.Data.bRS232Connection = false;
							break ;
						}
						if ( RCV_CMD == 0xEB ) {/* ACK応答 */
							TX1[ TXB1_Proc_Position ].ACK = 0xEB ;
							break ;
						}
						if ( RCV_CMD == 0xDB ) {/* NAK応答 */
							TX1[ TXB1_Proc_Position ].ACK = 0xDB ;
							break ;
						}
						if ( RCV_CMD == 0x4B ) {/* １バイトデータ４Ｂの時 *//*溶接回数リセット*/
							//ComuniPack.Data.From.BackUp.usWeldTimes = 0;
                                                        gtt_Ctrl_flag.Total_weld_count_reset = ON; //2007.4.5
							TX1[ TXB1_Proc_Position ].ACK = 0xEB ;
							break ;
						}
						if ( RCV_CMD == 0x4C ) {/* １バイトデータ４Ｃの時 *//*溶接時間リセット*/
                                                        //２００６．１２．１５　バックＲＡＭテスト
                                                        //test_counter = 0;;
                                                        gtt_Ctrl_flag.Total_weld_time_reset = ON;//2007.3.30

							TX1[ TXB1_Proc_Position ].ACK = 0xEB ;
							break ;
						}
						if ( RCV_CMD == 0x4D ) {/* １バイトデータ４Ｄの時 *//*ワイヤ総送給量リセット*/
							//ComuniPack.Data.From.BackUp.usWireFeed = 0;
                                                        gtt_Ctrl_flag.Total_wire_feed_reset = ON;//2007.4.5
							TX1[ TXB1_Proc_Position ].ACK = 0xEB ;
							break ;
						}
						if ( RCV_CMD == 0xBB ) {/* １バイトデータ４４の時 */
							PC_Send_E8( ) ;
							break ;
						}
						if ( RCV_CMD == 0x00 ) {	/* １バイトデータが「ブレイク信号」の時 */
							/* なにもせずに終了 */
							break ;
						}
						RCV1[ RXB1_Position ].Command[ 0 ] = RCV_CMD ;
						TOGLE_FLAG = true;
						break ;
					}
					else{
						/* フラグが２バイト目データ受信の時 */
								RCV1[ RXB1_Position ].Command[ 1 ] = RCV_CMD ;

								/* ＡＣＫを送出 */
								PC_Send_E8( ) ;

								CMD = RCV1[ RXB1_Position ].Command[ 0 ] ;

								if(CMD == 0xb3){
									PC_Recv_B3();
								}
								if(CMD == 0xb4){
									PC_Recv_B4();
								}
								if(CMD == 0xE1){
									PC_Recv_E1();
								}
                                                                if (CMD == 0xFC){
                                                                   if (RCV1[RXB1_Position].Command[1] == 1)
                                                                   {
                                                                       com_ts = ON;
                                                                   } else {
                                                                       com_ts = OFF;
                                                                   }
								}
                                                                if (CMD == 0xFE){
                                                                    RCV_WORK = RCV1[RXB1_Position].Command[1];

                                                                    com_current = (short int)RCV_WORK * 2;
	                                                            ComuniPack.Data.To.usWeldingCurr = com_current;
                                                                    PC_Send_D1();
                                                                }
                                                                if (CMD == 0xFD){
                                                                    RCV_WORK = RCV1[RXB1_Position].Command[1];

                                                                    com_voltage = (short int)RCV_WORK * 2;
	                                                            ComuniPack.Data.To.usWeldingVolt = com_voltage;
                                                                    PC_Send_D1();
                                                                }
                                                                //if (CMD == 0xFB){     //ロボット解除選択
                                                                //   if (RCV1[RXB1_Position].Command[1] == 1)
                                                                //   {
                                                                       //ROBOT = OFF;
                                                                //   } else {
                                                                       //ROBOT = ON;
                                                                //   }
								//}
                                                                if (CMD == 0xFB){     //リトラクト選択
                                                                   if (RCV1[RXB1_Position].Command[1] == 1)
                                                                   {
                                                                       ComuniPack.Data.To.fWelderCheck.Bit1Sw.Motor_on = ON;
		                                                       ComuniPack.Data.To.fWelderCheck.Bit1Sw.Motor_conect = ON;
                                                                   } else {
                                                                       ComuniPack.Data.To.fWelderCheck.Bit1Sw.Motor_on = OFF;
		                                                       ComuniPack.Data.To.fWelderCheck.Bit1Sw.Motor_conect = OFF;
                                                                   }
								}
#if 0
                                                                if (CMD == 0xF0){     //インチング選択
                                                                   if (RCV1[RXB1_Position].Command[1] == 1)
                                                                   {
                                                                       ComuniPack.Data.To.fWelderCheck.Bit1Sw.Motor_on = ON;
                                                                   } else {
                                                                       ComuniPack.Data.To.fWelderCheck.Bit1Sw.Motor_on = OFF;
                                                                   }
		                                                   ComuniPack.Data.To.fWelderCheck.Bit1Sw.Motor_conect = OFF;
								}
#endif
                                                                if (CMD == 0xF0){   //半固定パラメータＰＣ送信指令
                                                                   if (RCV1[RXB1_Position].Command[1] == 1)
                                                                   {
                                                                       guc_Half_pc_data_flag = ON;
                                                                   }
								}
                                                                
                                                                
                                                                if (CMD == 0xFA){   //サンプリング開始
                                                                   if (RCV1[RXB1_Position].Command[1] == 1)
                                                                   {
                                                                       guc_Dsp_sampling_flag = ON;
                                                                   }
								}
                                                                if (CMD == 0xF9){   //ＰＣデータ回収
                                                                   if (RCV1[RXB1_Position].Command[1] == 1)
                                                                   {
                                                                       guc_Dsp_pc_data_flag = ON;
                                                                   }
								}
                                                                //半固定パラメータ
                                                                if (CMD == 0xF8){   //データ番号の取得下位
                                                                    data_no_counter++;
                                                                    data_no[data_no_counter] = RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xFF){   //データ番号の取得上位 2008.02.21
                                                                    data_no[data_no_counter] = data_no[data_no_counter] | (unsigned short)RCV1[RXB1_Position].Command[1] << 8;
                                                                }
                                                                
                                                                if (CMD == 0xF7){  //データ下位。
                                                                    data[data_no_counter] = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xF6){  //データ上位。
                                                                    data[data_no_counter] = data[data_no_counter] | (unsigned int)RCV1[RXB1_Position].Command[1] << 8;
                                                                    //if (data_no_counter >= 30) { data_no_counter = 0; } 2007.1.24削除 2007.1.26削除内容の移植
                                                                }
                                                                if (CMD == 0xF5){  //書き込み許可信号
                                                                    guc_Dsp_write_flag = 1;
                                                                    data_no_counter = 0;  //2007.1.24 2007.1.26移植追加
                                                                }


                                                                //可変パラメータ
                                                                if (CMD == 0xF4){   //データ番号の取得
                                                                    v_data_no_counter++;
                                                                    v_data_no[v_data_no_counter] = RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xF3){  //データ下位。
                                                                    v_data[v_data_no_counter] = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xF2){  //データ上位。
                                                                    v_data[v_data_no_counter] = v_data[v_data_no_counter] | (unsigned int)RCV1[RXB1_Position].Command[1] << 8;
                                                                    if (v_data_no_counter >= 24) { v_data_no_counter = 0; }
                                                                }
                                                                if (CMD == 0xF1){  //書き込み許可信号
                                                                    guc_V_dsp_write_flag = 1;
                                                                }
                                        
                                                                //可変パラメータ 2007.1.26移植追加
                                                                if (CMD == 0x90){   //データ番号の取得
                                                                    PC_v_data_no = RCV1[RXB1_Position].Command[1];
                                                                }
                                                                //a
                                                                if (CMD == 0x91){  //データ４（最下位）
                                                                    PC_v_data_a4 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x92){  //データ３
                                                                    PC_v_data_a3 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x93){  //データ２
                                                                    PC_v_data_a2 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x94){  //データ１（最上位）
                                                                    PC_v_data_a1 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                //b
                                                                if (CMD == 0x95){  //データ４（最下位）
                                                                    PC_v_data_b4 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x96){  //データ３
                                                                    PC_v_data_b3 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x97){  //データ２
                                                                    PC_v_data_b2 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x98){  //データ１（最上位）
                                                                    PC_v_data_b1 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                //c
                                                                if (CMD == 0x99){  //データ４（最下位）
                                                                    PC_v_data_c4 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x9A){  //データ３
                                                                    PC_v_data_c3 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x9B){  //データ２
                                                                    PC_v_data_c2 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x9C){  //データ１（最上位）
                                                                    PC_v_data_c1 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                //min
                                                                if (CMD == 0x9D){  //データ４（最下位）
                                                                    PC_v_data_min4 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x9E){  //データ３
                                                                    PC_v_data_min3 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0x9F){  //データ２
                                                                    PC_v_data_min2 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xA0){  //データ１（最上位）
                                                                    PC_v_data_min1 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                //max
                                                                if (CMD == 0xA1){  //データ４（最下位）
                                                                    PC_v_data_max4 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xA2){  //データ３
                                                                    PC_v_data_max3 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xA3){  //データ２
                                                                    PC_v_data_max2 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xA4){  //データ１（最上位）
                                                                    PC_v_data_max1 = (unsigned int)RCV1[RXB1_Position].Command[1];
                                                                }
                                                                if (CMD == 0xA5){  //書き込み許可信号
                                                                    guc_PC_V_dsp_write_flag = 1;
                                                                }


                                                                //DSP　特定アドレスデータ読み込み
                                                                if (CMD == 0xEF){
                                                                    gul_Dsp_address4 = (unsigned long)(RCV1[RXB1_Position].Command[1] << 24) & 0xff000000;
                                                                }
                                                                if (CMD == 0xEE){
                                                                    gul_Dsp_address3 = (unsigned long)(RCV1[RXB1_Position].Command[1] << 16) & 0x00ff0000;
                                                                }
                                                                if (CMD == 0xED){
                                                                    gul_Dsp_address2 = (unsigned long)(RCV1[RXB1_Position].Command[1] << 8)  & 0x0000ff00;
                                                                }
                                                                if (CMD == 0xEC){
                                                                    gul_Dsp_address1 = (unsigned long)(RCV1[RXB1_Position].Command[1])       & 0x000000ff;
                                                                }
                                                                if (CMD == 0xEA){  //DPSデータ読み込み開始信号
                                                                    guc_Dsp_read_flag = 1;
                                                                }
                                                                
                                                                
                                                                //DSP　特定アドレス　データ書き込み
                                                                //書き込みデータ
                                                                if (CMD == 0xDF){//上位
                                                                    gus_Dsp_write_data2 = (unsigned short)(RCV1[RXB1_Position].Command[1] << 8) & 0xff00;
                                                                }
                                                                if (CMD == 0xDE){//下位
                                                                    gus_Dsp_write_data1 = (unsigned short)(RCV1[RXB1_Position].Command[1]) & 0x00ff;
                                                                }
                                                                //書き込みアドレス
                                                                if (CMD == 0xDD){
                                                                    gul_Dsp_write_address4 = (unsigned long)(RCV1[RXB1_Position].Command[1] << 24) & 0xff000000;
                                                                }
                                                                if (CMD == 0xDC){
                                                                    gul_Dsp_write_address3 = (unsigned long)(RCV1[RXB1_Position].Command[1] << 16) & 0x00ff0000;
                                                                }
                                                                if (CMD == 0xDA){
                                                                    gul_Dsp_write_address2 = (unsigned long)(RCV1[RXB1_Position].Command[1] << 8)  & 0x0000ff00;
                                                                }
                                                                if (CMD == 0xD9){
                                                                    gul_Dsp_write_address1 = (unsigned long)(RCV1[RXB1_Position].Command[1])       & 0x000000ff;
                                                                }
                                                                if (CMD == 0xD8){  //DPS データ書き込み信号
                                                                    guc_Dsp_one_write_flag = 1;
                                                                }

                                                              
								/* カウンタ＋１ */
								RXB1_Position++ ;
								RXB1_Proc_Position++ ;

								/* バッファの終端に達したか？ */
								if ( RXB1_Position >= RXB_BUFFER_MAX ) {
									RXB1_Position = 0 ;
									RXB1_Proc_Position = 0 ;
								}
								TOGLE_FLAG = false ;
					}
					break ;
				}
			}
		 }
		 else{
			/* まだおやすみちゅう */
			/* 入力されたコマンドが「おはよう」？ */
			if ( RCV_CMD == 0x47 ) {/*ｳｪﾙﾄﾞｷｰﾊﾟｰ機種別要求*/
				PC_Send_B1( ) ;
				PC_Send_D1( ) ;
				PC_ps_av_flag2 = ON;
				ComuniPack.Data.bRS232Connection = true;
			}
			if ( RCV_CMD == 0xBB ) {
				/* 「おはよう」が入力された */
				PC_Send_E8( ) ;
				ComuniPack.Data.bRS232Connection = true;
			}
			if ( RCV_CMD == 0xF1 ) {
				/* 「おはよう」が入力された */
				PC_Send_E8( ) ;
			}
		}
	}
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA0_int_pc_com_rcv.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

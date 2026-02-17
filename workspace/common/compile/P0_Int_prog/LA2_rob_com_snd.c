//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｒｏｂ＿ｃｏｍ＿ｓｎｄ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－２
//  【機能説明】
//      ロボット送信処理（実体）
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


void rob_com_snd(void)
{
     static long   i = 0;
     uchar  SND_DATA;                            // 送信データ
     SND_DATA = 0; //2006.8.30 clear

   FOREVER{
             if((S0TCNT & 0x04) != 0x00)         // 送信レジスタにデータがあるか？
             {
                 break;
             }

             if((S0RCNT & 0x20) != 0x00)         // 受信レジスタにデータがあるか？
             {
                 break;                          // データがあるならスルー
             }

#if true
             if(++i < 5)
             {
               P9DATA = (P9DATA | 0x01);
             } else if(i < 11) {
               P9DATA = (P9DATA & 0xfe);
             } else {
               i = 0;
             }
#endif

// --Ｇ２用--
             if(((SND_Mode == DLE_mode_SD) || (SND_Mode == WAIT_mode_SD)) && ((GD2_ACK_count != 0) || (GD2_NAK_count != 0 )|| (GD2_Busy_count != 0 )))
             {
               switch(ACK_SND_Mode)// ACK,NAK優先で送信
               {
                      case DLE_mode_SD:
                              S0TXB          = DLE;
                              ACK_SND_Mode   = CMD_mode_SD;
                              data_count_tx  = 0;
                              SUM_ADD_TxData = 0;
                              break;
                      case CMD_mode_SD:
                              if(GD2_NAK_count != 0)
                              {
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                                // IIF接続を確認
                                if(gb_IIF_Select)   S0TXB = 0x12;
                                else                S0TXB = GD2NAK_SD;
#else
                                 S0TXB = GD2NAK_SD;
#endif
//--------------------------------------------
                                 GD2_NAK_count--;
                              } else if(GD2_Busy_count != 0) {
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                                // IIF接続を確認
                                if(gb_IIF_Select)   S0TXB = 0x13;
                                else                S0TXB = GD2Busy_SD;
#else
                                 S0TXB = GD2Busy_SD;
#endif
//--------------------------------------------
                                 GD2_Busy_count--;
                              } else {
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                                // IIF接続を確認
                                if(gb_IIF_Select)   S0TXB = 0x11;
                                else                S0TXB = GD2ACK_SD;
#else
                                 S0TXB = GD2ACK_SD;
#endif
//--------------------------------------------
                                 GD2_ACK_count--;
                              }
                              ACK_SND_Mode = DLE_mode_SD;
                              break;
                       default:
                              ACK_SND_Mode = DLE_mode_SD;
                           break;
               }
             } else if(SND_CMD_Position != SND_CMD_Proc) {
                       switch(SND_Mode)
                       {
                              case DLE_mode_SD:
                                      S0TXB            = DLE;
                                      SND_Mode         = CMD_mode_SD;
                                      data_count_tx    = 0;
                                      SUM_ADD_TxData   = 0;
                                      DLE_check_flagSD = false;
                                      break;
                              case CMD_mode_SD:
                                      CMD_DATA_TX      = Txd_CMD[SND_CMD_Proc];
                                      SUM_ADD_TxData  += CMD_DATA_TX;                    // SUMチェック用加算
                                      S0TXB            = CMD_DATA_TX;
                                      SND_Mode         = DATA_mode_SD;
                                      break;
                              case DATA_mode_SD:
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
                                      if(gb_IIF_Select){  // IIF接続を確認 2009.11.25 IIF NEW
                                         (ToIIF[CMD_DATA_TX])();
                                      } else {
                                         (ToGD2[CMD_DATA_TX])();
                                      }
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
                                      SND_DATA         = Txd_DATA[data_count_tx];
                                      if((SND_DATA == DLE) && (DLE_check_flagSD == false))
                                      {
                                        DLE_check_flagSD = ON;
                                        S0TXB            = SND_DATA;                     // データの送信
                                      } else {
                                        SUM_ADD_TxData  += (uchar)SND_DATA;              // SUMチェック用加算
                                        S0TXB            = SND_DATA;                     // データの送信
                                        DLE_check_flagSD = OFF;
                                        data_count_tx++;
                                        if(data_count_tx >= DATA_Length_TX)
                                        {
                                           SND_Mode      = SUM_mode_SD;
                                        }
                                      }
                                      break;
                              case SUM_mode_SD:
                                      S0TXB              = SUM_ADD_TxData;
//--------- IIF by @Tny 2008/08/26 ------------
#if true
                                        if(gb_IIF_Select){  // IIF接続を確認
//                                            if((CMD_DATA_TX == 0x30)||(CMD_DATA_TX == 0x20)){ // 送信コマンドが「OUTPUTデータ」「入力ポート設定データ」？
                                            if(CMD_DATA_TX != 0x86){ // 送信コマンドが「IIF用ＧＭ」以外？
                                                // ＡＣＫ受信は行わないので次の送信処理の移行処理を行う
                                            	SND_Mode = DLE_mode_SD;
                                            	WAIT_SD_count	= 0;
                                            	if(SND_CMD_Position != SND_CMD_Proc){
                                           			SND_CMD_Proc++;
                                            		if(SND_CMD_Proc >= TXB_BUFFER_MAX){
                                            			SND_CMD_Proc = 0;
                                            		}
                                            	}
                                            }
                                            else{
                                                SND_Mode           = WAIT_mode_SD;
                                                SND_Timer          = 0;
                                                WAIT_SD_count++;
                                            }
                                        }
                                        else{
                                            SND_Mode           = WAIT_mode_SD;
                                            SND_Timer          = 0;
                                            WAIT_SD_count++;
                                        }
#else
                                      SND_Mode           = WAIT_mode_SD;
                                      SND_Timer          = 0;
                                      WAIT_SD_count++;
#endif
//--------------------------------------------
                                      break;
                              case WAIT_mode_SD:
                                      //if(SND_Timer >= 10)
                                      if(SND_Timer >= 100) //2009.10.01
                                      //if(SND_Timer >= 200) //プロトコルアナライザーテスト用
                                      {
                                         SND_Mode = DLE_mode_SD;
                                         if((TPX_G2_Send_OFF == ON) || (Check_G2_Send_OFF == ON))
                                         {
                                            GD2_Recv_41();
                                         }
                                      }
                                      if(WAIT_SD_count > 2)                              // リトライ３回でタイムアウト
                                      {
                                         RS422ErrorFlag = 0x07;

#if true	// エラー処理（後日メイン側へ移動）
                                         ComuniPack.Data.bRS422Connection = false;
                                         guc_Robot_connect_flag = false;      //ロボット接続を確認 2008.10.03

                                         SND_CMD_Position = 0;
                                         SND_CMD_Proc     = 0;
                                         GD2_ACK_count    = 0;
                                         GD2_NAK_count    = 0;
                                         GD2_Busy_count   = 0;
                                         WAIT_SD_count    = 0;
                                         //RS422ErrorFlag   = 0x00; 2007.1.16 削除　この行があるとリトライエラーが出力されないため 2007.1.17削除移植
#endif
                                      }
                                      break;
                              default:
                                      SND_Mode = DLE_mode_SD;
                                      break;
                       }
             }
             break;
          }
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA2_rob_com_snd.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

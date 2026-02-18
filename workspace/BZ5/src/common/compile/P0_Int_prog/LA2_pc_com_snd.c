//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｐｃ＿ｃｏｍ＿ｓｎｄ
//　【関数レベル】
//　　　ＬＥＶＥＬ：ＡＬＬ－２
//  【機能説明】
//      ＰＣ送信処理（実体）
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


static ubool		ComProc;
void pc_com_snd( void )
{
     static short UnResponceCounter = 0;
     static char  NAK_Count = 0;
     static char  RetryFlag = false;    // 再挑戦フラグ

     for ( ; ; )
     {
          // 送信レジスタにデータがあるか？
          if (( S2TCNT & 0x04 ) != 0x00)
          {
              // データがある
              break;
          }

          // 受信レジスタにデータがあるとき
          if (( S2RCNT & 0x20 ) != 0x00)
          {
              // データがある
              break;
          }

          // 送信用バッファにデータがある時
          if (TXB1_Proc_Position != TXB1_Position)
          {
             switch (TX1[ TXB1_Proc_Position ].SendInfo1.Status.Status)
            {
                     case 0x04:                                      // データを送信する
                          S2TXB = TX1[ TXB1_Proc_Position ].Data;
                          TXB1_Proc_Position++;
                          if (TXB1_Proc_Position >= TXB_BUFFER_MAX)
                          {
                              TXB1_Proc_Position = 0;
                          }
                          ComProc = true;
                          break;
                     case 0x03:                                      // コマンド／データ未送信
                     case 0x02:                                      // コマンド未送信
                                                                     // コマンドを送信する
                          S2TXB = TX1[ TXB1_Proc_Position ].Comm;
                          TXB1_Proc_Position++;
                          if (TXB1_Proc_Position >= TXB_BUFFER_MAX)
                          {
                              TXB1_Proc_Position = 0;
                          }
                          break ;
                     case 0x01:                                      // データ未送信
                                                                     // データを送信する
                          S2TXB = TX1[ TXB1_Proc_Position ].Data;
                                                                     // ステータスをデータ送信済みにする
                          TX1[ TXB1_Proc_Position ].SendInfo1.Status.Status = TX1[ TXB1_Proc_Position ].SendInfo1.Status.Status & 0x02;
                          break;
                     case 0x00:                                      // 送信完了ＡＣＫ待ち
                          TXB1_Proc_Position++;
                          if (TXB1_Proc_Position >= TXB_BUFFER_MAX)
                          {
                              TXB1_Proc_Position = 0;
                          }
                          break ;
            }
          } else {
            if(ComProc)
            {
               ubool a = false;
               ComProc = true;
            }
          }
     break;
     }

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of LA2_pc_com_snd.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

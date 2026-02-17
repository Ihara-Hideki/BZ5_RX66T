///<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｏｕｔｐｕｔ＿ｒ８＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      Ｒ８出力
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
#include  "custom.h"

void output_r8_class(unsigned char puc_Sequence_mode , unsigned int pui_Err_code)
{
//		"0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F, ,L,c,P,H,S,n,o,-,U,r"
                              // 0     1     2     3     4     5     6     7     8     9
     static uchar LED7Seg[] = { 0x01, 0x4f, 0x12, 0x06, 0x4c, 0x24, 0x20, 0x0f, 0x00, 0x04,
                              // A     b     C     d     E     F    "  "   L     c     P
                                0x08, 0x60, 0x31, 0x42, 0x30, 0x38, 0xff, 0x71, 0x72, 0x18,
                              // H     S     n     o     -     U     r
                                0x48, 0x24, 0x6a, 0x62, 0xfe, 0x41, 0x7a };

     unsigned short pus_Dec100;
     unsigned short pus_Dec10;
     unsigned short pus_Dec1;
     unsigned short pus_Work;
     unsigned char puc_Dps100; //2007.6.28追加
     unsigned char puc_Dps10;  //2007.6.28追加
     unsigned char puc_Dps1;   //2007.6.28追加
     unsigned char puc_Ver100; //2007.6.28追加
     unsigned char puc_Ver10;  //2007.6.28追加
     unsigned char puc_Ver1;   //2007.6.28追加



     pui_Err_code = pui_Err_code & 0x000000ff;
     pus_Dec10 = (unsigned short)pui_Err_code / 10;
     pus_Dec1  = (unsigned short)(pui_Err_code - (pus_Dec10 * 10));

     if (guc_Program_ver_flag == ON) //2007.2.13 プログラムＶｅｒ表示機能追加
     {

#if 0      //2007.6.28削除
           pus_Work   = M32_PROGRAM_VER;
           pus_Dec100 = (unsigned short)pus_Work / 100;
           pus_Dec10  = (unsigned short)((pus_Work - (pus_Dec100 * 100)) / 10);
           pus_Dec1   = (unsigned short)(pus_Work - ((pus_Dec100 * 100) + (pus_Dec10 * 10)));
#endif
           puc_Dps100 = guc_Attribute_dps_no[0] - 0x30;  //2007.6.28追加
           puc_Dps10  = guc_Attribute_dps_no[1] - 0x30;  //2007.6.28追加
           puc_Dps1   = guc_Attribute_dps_no[2] - 0x30;  //2007.6.28追加
           puc_Ver100 = guc_Attribute_version[0] - 0x30; //2007.6.28追加
           puc_Ver10  = guc_Attribute_version[1] - 0x30; //2007.6.28追加
           puc_Ver1   = guc_Attribute_version[2] - 0x30; //2007.6.28追加
      

           if (gtt_Ctrl_flag.Ver_disp_chenge_timing ==  OFF)
           {   
               gtt_Ctrl_flag.Ver_disp_chenge_timing = ON;
               gtt_Ctrl_counter.Ver_disp_chenge_timing = VER_DISP_CHENGE_TIMING_TIME;
           } else if (gtt_Ctrl_counter.Ver_disp_chenge_timing <= 0) {
             switch (gtt_Ctrl_counter.Ver_disp_chenge)
             {
                     //2007.4.5 テーブルのＶｅｒ表示追加
                     case 0:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース 2007.6.28追加
                          gtt_Ctrl_counter.Ver_disp_chenge = 1;
                          break;
                     case 1:
                          gtt_R8_com.Work = LED7Seg[puc_Dps100];  //DPS_NO 100桁目  2007.6.28追加
                          gtt_Ctrl_counter.Ver_disp_chenge = 2;
                          break;
                     case 2:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 3;
                          break;
                     case 3:
                          gtt_R8_com.Work = LED7Seg[puc_Dps10];     //DPS_NO 10桁目　2007.6.28追加  
                          gtt_Ctrl_counter.Ver_disp_chenge = 4;
                          break;
                     case 4:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 5;
                          break;
                     case 5:
                          gtt_R8_com.Work = LED7Seg[puc_Dps1];     //DPS_NO 1桁目　2007.6.28追加  
                          gtt_Ctrl_counter.Ver_disp_chenge = 6;
                          break;
                     case 6:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 7;
                          break;
                     case 7:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 8;
                          break;
                     case 8:
                          gtt_R8_com.Work = LED7Seg[puc_Ver100];
                          gtt_Ctrl_counter.Ver_disp_chenge = 9;
                          break;
                     case 9:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 10;
                          break;
                     case 10:
                          gtt_R8_com.Work = LED7Seg[puc_Ver10];
                          gtt_Ctrl_counter.Ver_disp_chenge = 11;
                          break;
                     case 11:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 12;
                          break;
                     case 12:
                          gtt_R8_com.Work = LED7Seg[puc_Ver1];
                          gtt_Ctrl_counter.Ver_disp_chenge = 13;
                          break;
                     case 13:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 14;
                          break;
                     case 14:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 15;
                          break;
                     case 15:
                          gtt_R8_com.Work = LED7Seg[13];       //d
                          gtt_Ctrl_counter.Ver_disp_chenge = 16;
                          break;
                     case 16:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 17;
                          break;
                     case 17:
                          gtt_R8_com.Work = LED7Seg[WLDTBL_VERSION[0] - 0x30];
                          gtt_Ctrl_counter.Ver_disp_chenge = 18;
                          break;
                     case 18:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 19;
                          break;
                     case 19:
                          gtt_R8_com.Work = LED7Seg[WLDTBL_VERSION[1] - 0x30];
                          gtt_Ctrl_counter.Ver_disp_chenge = 20;
                          break;
                     case 20:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 21;
                          break;
                     case 21:
                          gtt_R8_com.Work = LED7Seg[WLDTBL_VERSION[2] - 0x30];
                          gtt_Ctrl_counter.Ver_disp_chenge = 22;
                          break;
                     case 22:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 23;
                          break;
                     case 23:
                          gtt_R8_com.Work = LED7Seg[WLDTBL_VERSION[3] - 0x30];
                          gtt_Ctrl_counter.Ver_disp_chenge = 24;
                          break;
                     case 24:
                          gtt_R8_com.Work = LED7Seg[16];       //スペース
                          gtt_Ctrl_counter.Ver_disp_chenge = 25;
                          break;
                     case 25:
                          guc_Program_ver_flag = OFF;
                          break;
                     default:
                          break;
             }
             gtt_Ctrl_flag.Ver_disp_chenge_timing = OFF;
           }
     } else {
       if (gub_System_err == ON)
       {
           if (gtt_Ctrl_flag.Err_disp_chenge_timing ==  OFF)
           {   
               gtt_Ctrl_flag.Err_disp_chenge_timing = ON;
               gtt_Ctrl_counter.Err_disp_chenge_timing = ERR_DISP_CHENGE_TIMING_TIME;
           } else if (gtt_Ctrl_counter.Err_disp_chenge_timing <= 0) {
             switch (gtt_Ctrl_counter.Err_disp_chenge)
             {
                     case 0:
                          gtt_R8_com.Work = LED7Seg[14];
                          gtt_Ctrl_counter.Err_disp_chenge = 1;
                          break;
                     case 1:
                          gtt_R8_com.Work = LED7Seg[pus_Dec10];
                          gtt_Ctrl_counter.Err_disp_chenge = 2;
                          break;
                     case 2:
                          gtt_R8_com.Work = LED7Seg[pus_Dec1];
                          gtt_Ctrl_counter.Err_disp_chenge = 0;
                          break;
                     default:
                          break;
             }
             gtt_Ctrl_flag.Err_disp_chenge_timing = OFF;
           }
       } else {
         gtt_R8_com.Work = (unsigned short)LED7Seg[puc_Sequence_mode];
       }
     }


     //１０ｍｓ間隔送信部（Ｒ８に対し送信を行う）
     if (gtt_Ctrl_flag.R8_send ==  OFF)
     {
         gtt_Ctrl_flag.R8_send = ON;
         gtt_Ctrl_counter.R8_send = R8_SEND_TIMING_TIME;
     } else if (gtt_Ctrl_counter.R8_send <= 0) {
//----- Phase5 by @Tny 2008/09/09 -----
#if true
            if(gb_R8_comuni == false){
                S4TXB = gtt_R8_com.Work;
                gb_R8_comuni    = true; // 次回は制御データ
            }
            else{
                S4TXB = ((guc_R8_control.ALL & 0x0f) | 0x80);
                gb_R8_comuni    = false; // 次回は7SEGデータ
            }
#endif
//--------------------------------------------
             gtt_R8_com.Rx_write_position = 0;
             gtt_Ctrl_flag.R8_send = OFF;
       
             gtt_internal_r8.Com_check = ON;  //Ｒ８との通信が正常かどうかをチェックする。チェック開始。

     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_output_r8_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

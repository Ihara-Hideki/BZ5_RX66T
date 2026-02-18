//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｔａｂｌｅ＿ｋｅｙ＿ｃｈａｎｇｅ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      テーブル読み込み用キーのＧＢ２からＴＡＷＥＲＳへの変換
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

extern int DC_PMODE;
extern WELDCODE DC_WELDCODE; //2007.2.9
//void table_key_change_member(void)
void table_key_change_member(unsigned char xuc_Sequence_mode) //2007.2.9
{
     //unsigned char cmp1,cmp2,cmp3,cmp4,cmp5,cmp6;
     //unsigned char cmp1_bkup,cmp2_bkup,cmp3_bkup,cmp4_bkup,cmp5_bkup,cmp6_bkup;
     unsigned char cmp1,cmp2,cmp3,cmp4,cmp5,cmp6,cmp7; //2008.10.08
     unsigned char cmp1_bkup,cmp2_bkup,cmp3_bkup,cmp4_bkup,cmp5_bkup,cmp6_bkup,cmp7_bkup; //2008.10.08

//******************** ＣＯ２テーブルの切り替え 2007.2.9 ***********************************
     if (xuc_Sequence_mode == IDLING && (gtt_Table_key.Welding_method == 0x01 || gtt_Table_key.Welding_method == 0x10) && guc_Table_change_flag == 2)
     {
         guc_No_table = OFF;       //2007.2.9
         if (gtt_Internal_pack.Data.In.vTableChange == 0x00) //CO2へ切り替え
         {
             gtt_Table_key.Welding_method = 0x01;
             DC_WELDCODE.material  = gtt_Table_key.Wire_material;
             DC_WELDCODE.method    = gtt_Table_key.Welding_method;
             DC_WELDCODE.pulseMode = gtt_Table_key.Pulse_mode;
             DC_WELDCODE.pulseType = gtt_Table_key.Pulse_type;
             DC_WELDCODE.wire      = gtt_Table_key.Wire_diameter;
             DC_WELDCODE.extension = gtt_Table_key.Wire_ext;
             DC_WELDCODE.dummy1    = 0x00;
             DC_WELDCODE.dummy2    = 0x00;
             GetWeldTable( );
             if (guc_No_table == OFF)
             {
                 gtt_Internal_pack.Data.In.fWelding.ALL = 0x01;   // 溶接法
                 ComuniPack.Data.To.fWelding.ALL        = 0x01;   //溶接法
             } else {
                 gtt_Table_key.Welding_method = 0x10;
                 DC_WELDCODE.material  = gtt_Table_key.Wire_material;
                 DC_WELDCODE.method    = gtt_Table_key.Welding_method;
                 DC_WELDCODE.pulseMode = gtt_Table_key.Pulse_mode;
                 DC_WELDCODE.pulseType = gtt_Table_key.Pulse_type;
                 DC_WELDCODE.wire      = gtt_Table_key.Wire_diameter;
                 DC_WELDCODE.extension = gtt_Table_key.Wire_ext;
                 DC_WELDCODE.dummy1    = 0x00;
                 DC_WELDCODE.dummy2    = 0x00;
                 GetWeldTable( );
                 guc_No_table = OFF;
             }
         }

         if (gtt_Internal_pack.Data.In.vTableChange == 0x01) //HG-CO2へ切り替え
         {
             gtt_Table_key.Welding_method = 0x10;
             DC_WELDCODE.material  = gtt_Table_key.Wire_material;
             DC_WELDCODE.method    = gtt_Table_key.Welding_method;
             DC_WELDCODE.pulseMode = gtt_Table_key.Pulse_mode;
             DC_WELDCODE.pulseType = gtt_Table_key.Pulse_type;
             DC_WELDCODE.wire      = gtt_Table_key.Wire_diameter;
             DC_WELDCODE.extension = gtt_Table_key.Wire_ext;
             DC_WELDCODE.dummy1    = 0x00;
             DC_WELDCODE.dummy2    = 0x00;
             GetWeldTable( );
             if (guc_No_table == OFF)
             {
                 gtt_Internal_pack.Data.In.fWelding.ALL = 0x10;   // 溶接法
                 ComuniPack.Data.To.fWelding.ALL        = 0x10;   //溶接法
             } else {
                 gtt_Table_key.Welding_method = 0x01;
                 DC_WELDCODE.material  = gtt_Table_key.Wire_material;
                 DC_WELDCODE.method    = gtt_Table_key.Welding_method;
                 DC_WELDCODE.pulseMode = gtt_Table_key.Pulse_mode;
                 DC_WELDCODE.pulseType = gtt_Table_key.Pulse_type;
                 DC_WELDCODE.wire      = gtt_Table_key.Wire_diameter;
                 DC_WELDCODE.extension = gtt_Table_key.Wire_ext;
                 DC_WELDCODE.dummy1    = 0x00;
                 DC_WELDCODE.dummy2    = 0x00;
                 GetWeldTable( );
                 guc_No_table = OFF;
             }
         }
         guc_Table_change_flag = 0;
     }
//********************************************************************************************
#if G3_NEW_COM
     cmp1 = gtt_Internal_pack.Data.In.fWireMaterial.ALL;                    // ワイヤ材質
     cmp2 = gtt_Internal_pack.Data.In.fWelding.ALL;                         // 溶接法
     cmp3 = gtt_Internal_pack.Data.In.fWireDiameter.ALL;                    // ワイヤ径
     cmp4 = gtt_Internal_pack.Data.In.fWireSelect.ALL;                      // 突き出し長
     cmp5 = (gtt_Internal_pack.Data.In.fPulseMode.ALL >> 4) & 0x0f;         // パルスモード設定
     cmp6 = (gtt_Internal_pack.Data.In.fPulseMode.ALL)      & 0x0f;         // パルスタイプ
     cmp7 = guc_Pulse_mode_data; //2008.10.08

     cmp1_bkup = gtt_Table_key.Wire_material_bkup;            // ワイヤ材質
     cmp2_bkup = gtt_Table_key.Welding_method_bkup;           // 溶接法
     cmp3_bkup = gtt_Table_key.Wire_diameter_bkup;            // ワイヤ径
     cmp4_bkup = gtt_Table_key.Wire_ext_bkup;                 // 突き出し長
     cmp5_bkup = gtt_Table_key.Pulse_mode_bkup;               // 溶接種別フラグ
     cmp6_bkup = gtt_Table_key.Pulse_type_bkup;               // パルスタイプ
     cmp7_bkup = guc_Pulse_mode_data_bkup; //2008.10.08


     //if (cmp1 != cmp1_bkup || cmp2 != cmp2_bkup || cmp3 != cmp3_bkup || cmp4 != cmp4_bkup || cmp5 != cmp5_bkup || cmp6 != cmp6_bkup)
     if (cmp1 != cmp1_bkup || cmp2 != cmp2_bkup || cmp3 != cmp3_bkup || cmp4 != cmp4_bkup || cmp5 != cmp5_bkup || cmp6 != cmp6_bkup || cmp7 != cmp7_bkup) //2008.10.08
     {

         gtt_Table_key.Wire_material_bkup  = cmp1;            // ワイヤ材質
         gtt_Table_key.Welding_method_bkup = cmp2;            // 溶接法
         gtt_Table_key.Wire_diameter_bkup  = cmp3;            // ワイヤ径
         gtt_Table_key.Wire_ext_bkup       = cmp4;            // 突き出し長
         gtt_Table_key.Pulse_mode_bkup     = cmp5;            // 溶接種別フラグ
         gtt_Table_key.Pulse_type_bkup     = cmp6;            // パルスタイプ
         guc_Pulse_mode_data_bkup          = cmp7;            // 2008.10.08

         gtt_Table_key.Wire_material  = cmp1;            // ワイヤ材質
         gtt_Table_key.Welding_method = cmp2;            // 溶接法
         gtt_Table_key.Wire_diameter  = cmp3;            // ワイヤ径
         gtt_Table_key.Wire_ext       = cmp4;            // 突き出し長


         //溶接種別フラグの変換
#if 0 //2009.07.23 del
         switch (cmp5)
         {
                case 0x01:  //短絡
                     gtt_Table_key.Pulse_mode = 0x03;
                     gtt_Table_key.Pulse_mode = gtt_Table_key.Pulse_mode | (guc_Pulse_mode_data & 0x80); //AC時８ビット目ＯＮ　2008.09.12
                     DC_PMODE = 2;
                     break;
                case 0x00:  //パルス
                     gtt_Table_key.Pulse_mode = 0x05;
                     gtt_Table_key.Pulse_mode = gtt_Table_key.Pulse_mode | (guc_Pulse_mode_data & 0x80); //AC時８ビット目ＯＮ　2008.09.12
                     DC_PMODE = 1;
                     break;
                default:
                     gtt_Table_key.Pulse_mode = 0x03;
                     DC_PMODE = 2;
                     break;
         }
#endif 
//<><><><><><><><><><><> 2009.07.23 <><><><><><><><><><><><>
                     gtt_Table_key.Pulse_mode = 0x05;
                     gtt_Table_key.Pulse_mode = gtt_Table_key.Pulse_mode | (guc_Pulse_mode_data & 0x80); //AC時８ビット目ＯＮ　2008.09.12
                     DC_PMODE = 1;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

         //パルスタイプの変換
         switch (cmp6)
         {
                case 0x03:  //通常パルス
                     gtt_Table_key.Pulse_type = 0x00;
                     break;
                case 0x04:  //ディップパルス
                     gtt_Table_key.Pulse_type = 0x01;
                     break;
                default:
                     gtt_Table_key.Pulse_type = 0x00;
                     break;
         }
         
         gtt_Table_key.Change_flag = ON;                      //テーブル変更を通知
     } else {
         gtt_Okcv.New_calc = ON;
     }
#else
     cmp1 = gtt_Internal_pack.Data.In.fWireDiameter.ALL;      // ワイヤ径
     cmp2 = gtt_Internal_pack.Data.In.fWelding.ALL;           // 溶接法
     cmp3 = gtt_Internal_pack.Data.In.fWireMaterial.ALL;      // ワイヤ材質
     cmp4 = gtt_Internal_pack.Data.In.fWireSelect.ALL;        // 突き出し長
     if (gtt_Dsw.Sw.No3 == 0)                                 // 溶接種別フラグ
     {
         cmp5 = 0x03;
     } else {
         cmp5 = 0x05;
     }

     if (gtt_Dsw.Sw.No4 == 0)                                 // パルスタイプ
     {
         cmp6 = 0x00;
     } else {
         cmp6 = 0x01;
     }

     cmp1_bkup = gtt_Table_key.Wire_diameter_bkup;            // ワイヤ径
     cmp2_bkup = gtt_Table_key.Welding_method_bkup;           // 溶接法
     cmp3_bkup = gtt_Table_key.Wire_material_bkup;            // ワイヤ材質
     cmp4_bkup = gtt_Table_key.Wire_ext_bkup;                 // 突き出し長
     cmp5_bkup = gtt_Table_key.Pulse_mode;                    // 溶接種別フラグ
     cmp6_bkup = gtt_Table_key.Pulse_type;                    // パルスタイプ


     
     if (cmp1 != cmp1_bkup || cmp2 != cmp2_bkup || cmp3 != cmp3_bkup || cmp4 != cmp4_bkup || cmp5 != cmp5_bkup || cmp6 != cmp6_bkup)
     {

         gtt_Table_key.Wire_diameter_bkup  = cmp1;            // ワイヤ径
         gtt_Table_key.Welding_method_bkup = cmp2;            // 溶接法
         gtt_Table_key.Wire_material_bkup  = cmp3;            // ワイヤ材質
         gtt_Table_key.Wire_ext_bkup       = cmp4;            // 突き出し長
         gtt_Table_key.Pulse_mode_bkup     = cmp5;            // 溶接種別フラグ
         gtt_Table_key.Pulse_type_bkup     = cmp6;            // パルスタイプ

         //ワイヤ径の変換
         switch (cmp1)
         {
                case 0x00:  //0.6mm
                     gtt_Table_key.Wire_diameter = 0x01;
                     break;
                case 0x01:  //0.8mm
                     gtt_Table_key.Wire_diameter = 0x02;
                     break;
                case 0x02:  //0.9mm
                     gtt_Table_key.Wire_diameter = 0x03;
                     break;
                case 0x03:  //1.0mm
                     gtt_Table_key.Wire_diameter = 0x04;
                     break;
                case 0x04:  //1.2mm
                     gtt_Table_key.Wire_diameter = 0x05;
                     break;
                case 0x05:  //1.4mm
                     gtt_Table_key.Wire_diameter = 0x06;
                     break;
                case 0x06:  //1.6mm
                     gtt_Table_key.Wire_diameter = 0x07;
                     break;
                default:
                     gtt_Table_key.Wire_diameter = 0x05;
                     break;
         }

         //溶接法の変換
         switch (cmp2)
         {
                case 0x00:  //CO2
                     if (gtt_Dsw.Sw.No2 == 0)
                     {
                         gtt_Table_key.Welding_method = 0x01;  //ＣＯ２
                     } else {
                         gtt_Table_key.Welding_method = 0x10;  //新ＣＯ２　暫定で割り当て
                     }
                     break;
                case 0x01:  //MAG(80:20)
                     if (gtt_Dsw.Sw.No2 == 0)
                     {
                         gtt_Table_key.Welding_method = 0x02;  //MAG
                     } else {
                         gtt_Table_key.Welding_method = 0x07;  //SP-MAG2
                     }
                     break;
                case 0x02:  //MIG
                     if (gtt_Dsw.Sw.No2 == 0)
                     {
                         gtt_Table_key.Welding_method = 0x03;  //MIG
                     } else {
                         gtt_Table_key.Welding_method = 0x11;  //特殊モード 暫定で割り当て
                     }
                     break;
                case 0x03:  //PULSE MAG
                     gtt_Table_key.Welding_method = 0x02;
                     break;
                case 0x04:  //PULSE MIG
                     gtt_Table_key.Welding_method = 0x03;
                     break;
                case 0x05:  //PULSE CO2
                     gtt_Table_key.Welding_method = 0x01;
                     break;
                case 0x06:  //MAG2(90:10)
                     gtt_Table_key.Welding_method = 0x04;
                     break;
                case 0x07:  //other
                     gtt_Table_key.Welding_method = 0x07;
                     break;
                default:
                     gtt_Table_key.Welding_method = 0x01;
                     break;
         }
         
         //材質の変換
         switch (cmp3)
         {
                case 0x00:  //軟鋼
                     if (gtt_Dsw.Sw.No1 == 0)
                     {
                         gtt_Table_key.Wire_material = 0x01;  //軟鋼
                     } else {
                         gtt_Table_key.Wire_material = 0x65;  //CO2φ1.2 Revision
                     }
                     break;
                case 0x01:  //ステンレス
                     if (gtt_Dsw.Sw.No1 == 0)
                     {
                         gtt_Table_key.Wire_material = 0x02;  //ステンレス
                     } else {
                         gtt_Table_key.Wire_material = 0xFF;  //Stell:NewCo2 JWS
                     }
                     break;
                case 0x02:  //硬質アルミ
                     gtt_Table_key.Wire_material = 0x03;
                     break;
                case 0x03:  //軟質アルミ
                     gtt_Table_key.Wire_material = 0x04;
                     break;
                case 0x04:  //軟鋼ＦＣＷ
                     gtt_Table_key.Wire_material = 0x05;
                     break;
                case 0x05:  //ＳＵＳＦＣＷ
                     gtt_Table_key.Wire_material = 0x06;
                     break;
                case 0x06:  //亜鉛メッキ
                     gtt_Table_key.Wire_material = 0x07;
                     break;
                case 0x07:  //チタン
                     gtt_Table_key.Wire_material = 0x08;
                     break;
                default:
                     gtt_Table_key.Wire_material = 0x01;
                     break;
         }
 
         //突き出し長の変換
         switch (cmp4)
         {
                case 0x00:  //半自動
                     gtt_Table_key.Wire_ext = 0x00;
                     break;
                case 0x01:  //10mm
                     gtt_Table_key.Wire_ext = 0x01;
                     break;
                case 0x02:  //12mm
                     gtt_Table_key.Wire_ext = 0x02;
                     break;
                case 0x03:  //15mm
                     gtt_Table_key.Wire_ext = 0x03;
                     break;
                case 0x04:  //20mm
                     gtt_Table_key.Wire_ext = 0x04;
                     break;
                case 0x05:  //Reseved
                     gtt_Table_key.Wire_ext = 0x05;
                     break;
                case 0x06:  //25mm
                     gtt_Table_key.Wire_ext = 0x06;
                     break;
                case 0x07:  //30mm
                     gtt_Table_key.Wire_ext = 0x07;
                     break;
                default:
                     gtt_Table_key.Wire_material = 0x01;
                     break;
         }

         //溶接種別フラグの変換
         switch (cmp5)
         {
                case 0x03:  //短絡
                     gtt_Table_key.Pulse_mode = 0x03;
                     DC_PMODE = 2;
                     break;
                case 0x05:  //パルス
                     gtt_Table_key.Pulse_mode = 0x05;
                     DC_PMODE = 1;
                     break;
                default:
                     gtt_Table_key.Pulse_mode = 0x03;
                     DC_PMODE = 2;
                     break;
         }

         //パルスタイプの変換
         switch (cmp6)
         {
                case 0x00:  //通常パルス
                     gtt_Table_key.Pulse_type = 0x00;
                     break;
                case 0x01:  //ディップパルス
                     gtt_Table_key.Pulse_type = 0x01;
                     break;
                default:
                     gtt_Table_key.Pulse_type = 0x00;
                     break;
         }
         


         gtt_Table_key.Change_flag = ON;                      //テーブル変更を通知
     } else {
         gtt_Okcv.New_calc = ON;
     }
#endif
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_table_key_change_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

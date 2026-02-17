//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｔａｂｅｌ＿ｃｏｄｅ＿ｒｅａｄ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      本溶接機が持つ全ての溶接条件テーブルコードを読み込む
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
extern  WELDCODE    DC_WELDCODE;
//extern  PWELDTABLE  getWeldTablePtr( void );

void table_code_read_member(void)
{
     PWELDTABLE  pWT = getWeldTablePtr( );
     PWELDCODE   pCode;
     int         Cnt;
     int         Material_counter;
     int         Method_counter;
     int         Pulse_mode_counter;
     int         Pulse_type_counter;
     int         Wire_counter;
     int         Extension_counter;
     int         Reserved1_counter;
     int         Reserved2_counter;
     unsigned char   Material_value;
     unsigned char   Method_value;
     unsigned char   Pulse_mode_value;
     unsigned char   Pulse_type_value;
     unsigned char   Wire_value;
     unsigned char   Extension_value;
     unsigned char   Reserved1_value;
     unsigned char   Reserved2_value;

     unsigned char   Material_min;
     unsigned char   Method_min;
     unsigned char   Pulse_mode_min;
     unsigned char   Pulse_type_min;
     unsigned char   Wire_min;
     unsigned char   Extension_min;
     unsigned char   Reserved1_min;
     unsigned char   Reserved2_min;


     unsigned char i,s,t,j;

     unsigned char puc_DC_DP_flag; //2008.09.12
     unsigned char puc_AC_AP_flag; //2008.09.12

     unsigned char puc_Combination_check_flag; //2008.09.18
     unsigned char puc_Index;                  //2008.09.18



     puc_DC_DP_flag = false;       //2008.09.12
     puc_AC_AP_flag = false;       //2008.09.12



     i = 0;
     s = 0;
     t = 0;
     j = 0;


     Material_counter = 0;
     Method_counter = 0;
     Pulse_mode_counter = 0;
     Pulse_type_counter = 0;
     Wire_counter = 0;
     Extension_counter = 0;
     Reserved1_counter = 0;
     Reserved2_counter = 0;



     Material_value    = 0;
     Method_value      = 0;
     Pulse_mode_value  = 0;
     Pulse_type_value  = 0;
     Wire_value        = 0;
     Extension_value   = 0;
     Reserved1_value   = 0;
     Reserved2_value   = 0;

     Material_min    = 0;
     Method_min      = 0;
     Pulse_mode_min  = 0;
     Pulse_type_min  = 0;
     Wire_min        = 0;
     Extension_min   = 0;
     Reserved1_min   = 0;
     Reserved2_min   = 0;


     gui_Table_code_counter = 0;

     for(  Cnt = 0 ; Cnt <=TBLCNT ; Cnt++)// , ++pTbl )
     {
        pCode = &pWT->WeldCode;
        if (pCode->material == 0xFF && pCode->method == 0xFF && pCode->wire == 0xFF && pCode->extension) break;
    
        gtt_Table_code[gui_Table_code_counter].Material    = pCode->material;           //材質
        gtt_Table_code[gui_Table_code_counter].Method      = pCode->method;             //溶接法
        gtt_Table_code[gui_Table_code_counter].Pulse_mode  = pCode->pulseMode;                   //溶接種別フラグ（短絡／パルス）
        gtt_Table_code[gui_Table_code_counter].Pulse_type  = pCode->pulseType;          //パルスタイプ
        gtt_Table_code[gui_Table_code_counter].Wire        = pCode->wire;               //ワイヤ径
        gtt_Table_code[gui_Table_code_counter].Extension   = pCode->extension;          //突き出し長
        gtt_Table_code[gui_Table_code_counter].Reserved1   = 0x00;                              //予約
        gtt_Table_code[gui_Table_code_counter].Reserved2   = 0x00;                              //予約
        gui_Table_code_counter++;
        pWT++;                                          //次のテーブルへ
     }
     




     Material_counter = gui_Table_code_counter;
     Method_counter = gui_Table_code_counter;
     Pulse_mode_counter = gui_Table_code_counter;
     Pulse_type_counter = gui_Table_code_counter; 
     Wire_counter = gui_Table_code_counter;
     Extension_counter = gui_Table_code_counter;
     Reserved1_counter = gui_Table_code_counter;
     Reserved2_counter = gui_Table_code_counter;


     for ( Cnt = 0 ; Cnt < gui_Table_code_counter ; Cnt++)
     {
         gtt_Remo_table_code_work.Material[Cnt] = gtt_Table_code[Cnt].Material;
         gtt_Remo_table_code_work.Method[Cnt] = gtt_Table_code[Cnt].Method;
         gtt_Remo_table_code_work.Pulse_mode[Cnt] = gtt_Table_code[Cnt].Pulse_mode;
         gtt_Remo_table_code_work.Pulse_type[Cnt] = gtt_Table_code[Cnt].Pulse_type;
         gtt_Remo_table_code_work.Wire[Cnt] = gtt_Table_code[Cnt].Wire;
         gtt_Remo_table_code_work.Extension[Cnt] = gtt_Table_code[Cnt].Extension;
         gtt_Remo_table_code_work.Reserved1[Cnt] = gtt_Table_code[Cnt].Reserved1;
         gtt_Remo_table_code_work.Reserved2[Cnt] = gtt_Table_code[Cnt].Reserved2;
     }


     for ( i = 0 ; i < Material_counter-1 ; i++)
     {
         Material_min = gtt_Remo_table_code_work.Material[i];
         s = i;
         for (j = i + 1 ; j < Material_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Material[j]<Material_min)
              {
                  Material_min = gtt_Remo_table_code_work.Material[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Material[i];
              gtt_Remo_table_code_work.Material[i] = gtt_Remo_table_code_work.Material[s];
              gtt_Remo_table_code_work.Material[s] = t;
      }
     for ( i = 0 ; i < Method_counter-1 ; i++)
     {
         Method_min = gtt_Remo_table_code_work.Method[i];
         s = i;
         for (j = i + 1 ; j < Method_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Method[j]<Method_min)
              {
                  Method_min = gtt_Remo_table_code_work.Method[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Method[i];
              gtt_Remo_table_code_work.Method[i] = gtt_Remo_table_code_work.Method[s];
              gtt_Remo_table_code_work.Method[s] = t;
      }
     for ( i = 0 ; i < Pulse_mode_counter-1 ; i++)
     {
         Pulse_mode_min = gtt_Remo_table_code_work.Pulse_mode[i];
         s = i;
         for (j = i + 1 ; j < Pulse_mode_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Pulse_mode[j]<Pulse_mode_min)
              {
                  Pulse_mode_min = gtt_Remo_table_code_work.Pulse_mode[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Pulse_mode[i];
              gtt_Remo_table_code_work.Pulse_mode[i] = gtt_Remo_table_code_work.Pulse_mode[s];
              gtt_Remo_table_code_work.Pulse_mode[s] = t;
      }
     for ( i = 0 ; i < Pulse_type_counter-1 ; i++)
     {
         Pulse_type_min = gtt_Remo_table_code_work.Pulse_type[i];
         s = i;
         for (j = i + 1 ; j < Pulse_type_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Pulse_type[j] < Pulse_type_min)
              {
                  Pulse_type_min = gtt_Remo_table_code_work.Pulse_type[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Pulse_type[i];
              gtt_Remo_table_code_work.Pulse_type[i] = gtt_Remo_table_code_work.Pulse_type[s];
              gtt_Remo_table_code_work.Pulse_type[s] = t;
      }
     for ( i = 0 ; i < Wire_counter-1 ; i++)
     {
         Wire_min = gtt_Remo_table_code_work.Wire[i];
         s = i;
         for (j = i + 1 ; j < Wire_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Wire[j] < Wire_min)
              {
                  Wire_min = gtt_Remo_table_code_work.Wire[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Wire[i];
              gtt_Remo_table_code_work.Wire[i] = gtt_Remo_table_code_work.Wire[s];
              gtt_Remo_table_code_work.Wire[s] = t;
      }
     for ( i = 0 ; i < Extension_counter-1 ; i++)
     {
         Extension_min = gtt_Remo_table_code_work.Extension[i];
         s = i;
         for (j = i + 1 ; j < Extension_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Extension[j] < Extension_min)
              {
                  Extension_min = gtt_Remo_table_code_work.Extension[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Extension[i];
              gtt_Remo_table_code_work.Extension[i] = gtt_Remo_table_code_work.Extension[s];
              gtt_Remo_table_code_work.Extension[s] = t;
      }
     for ( i = 0 ; i < Reserved1_counter-1 ; i++)
     {
         Reserved1_min = gtt_Remo_table_code_work.Reserved1[i];
         s = i;
         for (j = i + 1 ; j < Reserved1_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Reserved1[j] < Reserved1_min)
              {
                  Reserved1_min = gtt_Remo_table_code_work.Reserved1[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Reserved1[i];
              gtt_Remo_table_code_work.Reserved1[i] = gtt_Remo_table_code_work.Reserved1[s];
              gtt_Remo_table_code_work.Reserved1[s] = t;
      }
     for ( i = 0 ; i < Reserved2_counter-1 ; i++)
     {
         Reserved2_min = gtt_Remo_table_code_work.Reserved2[i];
         s = i;
         for (j = i + 1 ; j < Reserved2_counter ; j++)
         {
              if (gtt_Remo_table_code_work.Reserved2[j] < Reserved2_min)
              {
                  Reserved2_min = gtt_Remo_table_code_work.Reserved2[j];
                  s = j;
              }
         }
              t = gtt_Remo_table_code_work.Reserved2[i];
              gtt_Remo_table_code_work.Reserved2[i] = gtt_Remo_table_code_work.Reserved2[s];
              gtt_Remo_table_code_work.Reserved2[s] = t;
      }


#if 1

     Material_value    =  gtt_Remo_table_code_work.Material[0];
     Method_value      =  gtt_Remo_table_code_work.Method[0];
     Pulse_mode_value  =  gtt_Remo_table_code_work.Pulse_mode[0];
     Pulse_type_value  =  gtt_Remo_table_code_work.Pulse_type[0];
     Wire_value        =  gtt_Remo_table_code_work.Wire[0];
     Extension_value   =  gtt_Remo_table_code_work.Extension[0];
     Reserved1_value   =  gtt_Remo_table_code_work.Reserved1[0];
     Reserved2_value   =  gtt_Remo_table_code_work.Reserved2[0];


#endif

#if 0
     Material_value    =  0x00;
     Method_value      =  0x00;
     Pulse_mode_value  =  0x00;
     Pulse_type_value  =  0x00;
     Wire_value        =  0x00;
     Extension_value   =  0x00;
     Reserved1_value   =  0x00;
     Reserved2_value   =  0x00;
#endif
             gtt_Remo_table_code.Material[0] = gtt_Remo_table_code_work.Material[0];
             gtt_Remo_table_code.Method[0] = gtt_Remo_table_code_work.Method[0];
             gtt_Remo_table_code.Pulse_mode[0] = gtt_Remo_table_code_work.Pulse_mode[0];
             gtt_Remo_table_code.Pulse_type[0] = gtt_Remo_table_code_work.Pulse_type[0];
             gtt_Remo_table_code.Wire[0] = gtt_Remo_table_code_work.Wire[0];
             gtt_Remo_table_code.Extension[0] = gtt_Remo_table_code_work.Extension[0];
             gtt_Remo_table_code.Reserved1[0] = gtt_Remo_table_code_work.Reserved1[0];
             gtt_Remo_table_code.Reserved2[0] = gtt_Remo_table_code_work.Reserved2[0];





     Material_counter = 0;
     Method_counter = 0;
     Pulse_mode_counter = 0;
     Pulse_type_counter = 0; 
     Wire_counter = 0;
     Extension_counter = 0;
     Reserved1_counter = 0;
     Reserved2_counter = 0;



     for ( Cnt = 0 ; Cnt < 20 ; Cnt++)
     {
         if (Material_value != gtt_Remo_table_code_work.Material[Cnt])
         {
             Material_counter++;
             Material_value = gtt_Remo_table_code_work.Material[Cnt];
             gtt_Remo_table_code.Material[Material_counter] = gtt_Remo_table_code_work.Material[Cnt];
         }
         if (Method_value != gtt_Remo_table_code_work.Method[Cnt])
         {
             Method_counter++;
             Method_value = gtt_Remo_table_code_work.Method[Cnt];
             gtt_Remo_table_code.Method[Method_counter] = gtt_Remo_table_code_work.Method[Cnt];
         }
         //if (Pulse_mode_value != gtt_Remo_table_code_work.Pulse_mode[Cnt])
         //{
         //    Pulse_mode_counter++;
         //    Pulse_mode_value = gtt_Remo_table_code_work.Pulse_mode[Cnt];
         //    gtt_Remo_table_code.Pulse_mode[Pulse_mode_counter] = gtt_Remo_table_code_work.Pulse_mode[Cnt];
         //}
#if 0
         if (Pulse_mode_value != gtt_Remo_table_code_work.Pulse_mode[Cnt]) //2008.02.08
         {
             //if (gtt_Remo_table_code_work.Pulse_mode[Cnt] != 0x07)
             if (gtt_Remo_table_code_work.Pulse_mode[Cnt] != 0x07 && gtt_Remo_table_code_work.Pulse_mode[Cnt] != 0x87) //2008.09.12
             {
             	Pulse_mode_counter++;
             	Pulse_mode_value = gtt_Remo_table_code_work.Pulse_mode[Cnt];
             	gtt_Remo_table_code.Pulse_mode[Pulse_mode_counter] = gtt_Remo_table_code_work.Pulse_mode[Cnt];
             }
             if (gtt_Remo_table_code_work.Pulse_mode[Cnt] == 0x07) //2008.09.12
             {
                 puc_DC_DP_flag = true;
             }
             if (gtt_Remo_table_code_work.Pulse_mode[Cnt] == 0x87) //2008.09.12
             {
                 puc_AC_AP_flag = true;
             }
         }
#endif
         if (Pulse_mode_value != gtt_Remo_table_code_work.Pulse_mode[Cnt]) //2008.02.08
         {
             	Pulse_mode_counter++;
             	Pulse_mode_value = gtt_Remo_table_code_work.Pulse_mode[Cnt];
             	gtt_Remo_table_code.Pulse_mode[Pulse_mode_counter] = gtt_Remo_table_code_work.Pulse_mode[Cnt];
         }




         if (Pulse_type_value != gtt_Remo_table_code_work.Pulse_type[Cnt])
         {
             Pulse_type_counter++;
             Pulse_type_value = gtt_Remo_table_code_work.Pulse_type[Cnt];
             gtt_Remo_table_code.Pulse_type[Pulse_type_counter] = gtt_Remo_table_code_work.Pulse_type[Cnt];
         }
         if (Wire_value != gtt_Remo_table_code_work.Wire[Cnt])
         {
             Wire_counter++;
             Wire_value = gtt_Remo_table_code_work.Wire[Cnt];
             gtt_Remo_table_code.Wire[Wire_counter] = gtt_Remo_table_code_work.Wire[Cnt];
         }
         if (Extension_value != gtt_Remo_table_code_work.Extension[Cnt])
         {
             Extension_counter++;
             Extension_value = gtt_Remo_table_code_work.Extension[Cnt];
             gtt_Remo_table_code.Extension[Extension_counter] = gtt_Remo_table_code_work.Extension[Cnt];
         }
         if (Reserved1_value != gtt_Remo_table_code_work.Reserved1[Cnt])
         {
             Reserved1_counter++;
             Reserved1_value = gtt_Remo_table_code_work.Reserved1[Cnt];
             gtt_Remo_table_code.Reserved1[Reserved1_counter] = gtt_Remo_table_code_work.Reserved1[Cnt];
         }
         if (Reserved2_value != gtt_Remo_table_code_work.Reserved2[Cnt])
         {
             Reserved2_counter++;
             Reserved2_value = gtt_Remo_table_code_work.Reserved2[Cnt];
             gtt_Remo_table_code.Reserved2[Reserved2_counter] = gtt_Remo_table_code_work.Reserved2[Cnt];
         }
     }




     gtt_Ctrl_counter.uc_Pulse_mode_check = 0;
//----- Phase15 by @Tny 2008/09/19 -----
#if true
    puc_Combination_check_flag = 0; //2008.09.19誤った値が入って、検索チェックできないことがあるので、一旦クリアする。
#endif
//--------------------------------------------


     for (puc_Index = 0 ; puc_Index <= 6 ; puc_Index++)
     {
          if (gtt_Remo_table_code.Pulse_mode[puc_Index] == 0x00) break;
          if (gtt_Remo_table_code.Pulse_mode[puc_Index] == 0x03) puc_Combination_check_flag = puc_Combination_check_flag | 0x20;
          if (gtt_Remo_table_code.Pulse_mode[puc_Index] == 0x05) puc_Combination_check_flag = puc_Combination_check_flag | 0x10;
          if (gtt_Remo_table_code.Pulse_mode[puc_Index] == 0x07) puc_Combination_check_flag = puc_Combination_check_flag | 0x08;
          if (gtt_Remo_table_code.Pulse_mode[puc_Index] == 0x83) puc_Combination_check_flag = puc_Combination_check_flag | 0x04;
          if (gtt_Remo_table_code.Pulse_mode[puc_Index] == 0x85) puc_Combination_check_flag = puc_Combination_check_flag | 0x02;
          if (gtt_Remo_table_code.Pulse_mode[puc_Index] == 0x87) puc_Combination_check_flag = puc_Combination_check_flag | 0x01;
    }
     //1
     if (puc_Combination_check_flag == 1) gtt_Ctrl_counter.uc_Pulse_mode_check = 3;
     //2
     if (puc_Combination_check_flag == 2) gtt_Ctrl_counter.uc_Pulse_mode_check = 1;
     //3
     if (puc_Combination_check_flag == 3) gtt_Ctrl_counter.uc_Pulse_mode_check = 3;
     //4
     if (puc_Combination_check_flag == 4) gtt_Ctrl_counter.uc_Pulse_mode_check = 2;
     //5
     if (puc_Combination_check_flag == 5) gtt_Ctrl_counter.uc_Pulse_mode_check = 3;
     //6
     if (puc_Combination_check_flag == 6) gtt_Ctrl_counter.uc_Pulse_mode_check = 3;
     //7
     if (puc_Combination_check_flag == 7) gtt_Ctrl_counter.uc_Pulse_mode_check = 3;
     //8
     if (puc_Combination_check_flag == 8) gtt_Ctrl_counter.uc_Pulse_mode_check = 12;
     //9
     if (puc_Combination_check_flag == 9) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //10
     if (puc_Combination_check_flag == 10) gtt_Ctrl_counter.uc_Pulse_mode_check = 13;
     //11
     if (puc_Combination_check_flag == 11) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //12
     if (puc_Combination_check_flag == 12) gtt_Ctrl_counter.uc_Pulse_mode_check = 14;
     //13
     if (puc_Combination_check_flag == 13) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //14
     if (puc_Combination_check_flag == 14) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //15
     if (puc_Combination_check_flag == 15) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //16
     if (puc_Combination_check_flag == 16) gtt_Ctrl_counter.uc_Pulse_mode_check = 4;
     //17
     if (puc_Combination_check_flag == 17) gtt_Ctrl_counter.uc_Pulse_mode_check = 7;
     //18
     if (puc_Combination_check_flag == 18) gtt_Ctrl_counter.uc_Pulse_mode_check = 5;
     //19
     if (puc_Combination_check_flag == 19) gtt_Ctrl_counter.uc_Pulse_mode_check = 7;
     //20
     if (puc_Combination_check_flag == 20) gtt_Ctrl_counter.uc_Pulse_mode_check = 6;
     //21
     if (puc_Combination_check_flag == 21) gtt_Ctrl_counter.uc_Pulse_mode_check = 7;
     //22
     if (puc_Combination_check_flag == 22) gtt_Ctrl_counter.uc_Pulse_mode_check = 7;
     //23
     if (puc_Combination_check_flag == 23) gtt_Ctrl_counter.uc_Pulse_mode_check = 7;
     //24
     if (puc_Combination_check_flag == 24) gtt_Ctrl_counter.uc_Pulse_mode_check = 4;
     //25
     if (puc_Combination_check_flag == 25) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //26
     if (puc_Combination_check_flag == 26) gtt_Ctrl_counter.uc_Pulse_mode_check = 13;
     //27
     if (puc_Combination_check_flag == 27) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //28
     if (puc_Combination_check_flag == 28) gtt_Ctrl_counter.uc_Pulse_mode_check = 14;
     //29
     if (puc_Combination_check_flag == 29) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //30
     if (puc_Combination_check_flag == 30) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //31
     if (puc_Combination_check_flag == 31) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //32
     if (puc_Combination_check_flag == 32) gtt_Ctrl_counter.uc_Pulse_mode_check = 8;
     //33
     if (puc_Combination_check_flag == 33) gtt_Ctrl_counter.uc_Pulse_mode_check = 11;
     //34
     if (puc_Combination_check_flag == 34) gtt_Ctrl_counter.uc_Pulse_mode_check = 9;
     //35
     if (puc_Combination_check_flag == 35) gtt_Ctrl_counter.uc_Pulse_mode_check = 11;
     //36
     if (puc_Combination_check_flag == 36) gtt_Ctrl_counter.uc_Pulse_mode_check = 10;
     //37
     if (puc_Combination_check_flag == 37) gtt_Ctrl_counter.uc_Pulse_mode_check = 11;
     //38
     if (puc_Combination_check_flag == 38) gtt_Ctrl_counter.uc_Pulse_mode_check = 11;
     //39
     if (puc_Combination_check_flag == 39) gtt_Ctrl_counter.uc_Pulse_mode_check = 11;
     //40
     if (puc_Combination_check_flag == 40) gtt_Ctrl_counter.uc_Pulse_mode_check = 12;
     //41
     if (puc_Combination_check_flag == 41) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //42
     if (puc_Combination_check_flag == 42) gtt_Ctrl_counter.uc_Pulse_mode_check = 13;
     //43
     if (puc_Combination_check_flag == 43) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //44
     if (puc_Combination_check_flag == 44) gtt_Ctrl_counter.uc_Pulse_mode_check = 14;
     //45
     if (puc_Combination_check_flag == 45) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //46
     if (puc_Combination_check_flag == 46) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //47
     if (puc_Combination_check_flag == 47) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //48
     if (puc_Combination_check_flag == 48) gtt_Ctrl_counter.uc_Pulse_mode_check = 12;
     //49
     if (puc_Combination_check_flag == 49) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //50
     if (puc_Combination_check_flag == 50) gtt_Ctrl_counter.uc_Pulse_mode_check = 12;
     //51
     if (puc_Combination_check_flag == 51) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //52
     if (puc_Combination_check_flag == 52) gtt_Ctrl_counter.uc_Pulse_mode_check = 14;
     //53
     if (puc_Combination_check_flag == 53) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //54
     if (puc_Combination_check_flag == 54) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //55
     if (puc_Combination_check_flag == 55) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //56
     if (puc_Combination_check_flag == 56) gtt_Ctrl_counter.uc_Pulse_mode_check = 12;
     //57
     if (puc_Combination_check_flag == 57) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //58
     if (puc_Combination_check_flag == 58) gtt_Ctrl_counter.uc_Pulse_mode_check = 13;
     //59
     if (puc_Combination_check_flag == 59) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //60
     if (puc_Combination_check_flag == 60) gtt_Ctrl_counter.uc_Pulse_mode_check = 14;
     //61
     if (puc_Combination_check_flag == 61) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //62
     if (puc_Combination_check_flag == 62) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;
     //63
     if (puc_Combination_check_flag == 63) gtt_Ctrl_counter.uc_Pulse_mode_check = 15;


     switch (gtt_Ctrl_counter.uc_Pulse_mode_check) //Pulse_modeを直接書き換えると判断分が誤動作するので、Pulse_mode_checkに変更した 2008.09.16
     {
          //gtt_Remo_table_code.Pulse_modeの配列を１つづつ増やす（ずらす）
          case 0:
               break;
          case 1: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x85;
               gtt_Remo_table_code.Pulse_mode[1] = 0x00;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 2: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x83;
               gtt_Remo_table_code.Pulse_mode[1] = 0x00;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 3: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x83;
               gtt_Remo_table_code.Pulse_mode[1] = 0x85;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 4: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x05;
               gtt_Remo_table_code.Pulse_mode[1] = 0x00;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 5: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x05;
               gtt_Remo_table_code.Pulse_mode[1] = 0x85;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 6: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x05;
               gtt_Remo_table_code.Pulse_mode[1] = 0x83;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 7: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x05;
               gtt_Remo_table_code.Pulse_mode[1] = 0x83;
               gtt_Remo_table_code.Pulse_mode[2] = 0x85;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 8: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x00;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 9: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x85;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 10: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x83;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 11: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x83;
               gtt_Remo_table_code.Pulse_mode[2] = 0x85;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 12: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x05;
               gtt_Remo_table_code.Pulse_mode[2] = 0x00;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 13: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x05;
               gtt_Remo_table_code.Pulse_mode[2] = 0x85;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 14: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x05;
               gtt_Remo_table_code.Pulse_mode[2] = 0x83;
               gtt_Remo_table_code.Pulse_mode[3] = 0x00;
               break;
          case 15: 
               gtt_Remo_table_code.Pulse_mode[0] = 0x03;
               gtt_Remo_table_code.Pulse_mode[1] = 0x05;
               gtt_Remo_table_code.Pulse_mode[2] = 0x83;
               gtt_Remo_table_code.Pulse_mode[3] = 0x85;
               break;
          default:
               break;
     }



            //<><><><><>2008.03.03<><><><><>
            guc_Remo_table_check_flag = false;
            for (Cnt = 0 ; Cnt < gui_Table_code_counter ; Cnt++) //2007.12.14変更
            {
                 if (gtt_Table_code[Cnt].Material == guc_Material_condition_data)
                 {
                     if (gtt_Table_code[Cnt].Method == guc_Method_condition_data)
                     {
                         if (gtt_Table_code[Cnt].Wire == guc_Wire_condition_data)
                         {
                          if (gtt_Table_code[Cnt].Extension == guc_Ext_condition_data) //2008.11.10
                          {
                             if (guc_Pulse_mode_data & 0x80)
                             {
                                 //if(gtt_Table_code[Cnt].Pulse_mode == guc_Pulse_mode_data || gtt_Table_code[Cnt].Pulse_mode == 0x07) //2008.02.08　0x07を認識させる
                                 //if(gtt_Table_code[Cnt].Pulse_mode == guc_Pulse_mode_data || gtt_Table_code[Cnt].Pulse_mode == 0x07 || gtt_Table_code[Cnt].Pulse_mode == 0x87) //2008.09.12 0x07,0x87を認識させる
                                 if(gtt_Table_code[Cnt].Pulse_mode == guc_Pulse_mode_data || gtt_Table_code[Cnt].Pulse_mode == 0x87) //2008.09.17 0x87を認識させる
                                 {
                                    //if (gtt_Table_code[Cnt].Pulse_type == (unsigned char)gss_Select_dital[0]) //パルスタイプを先に選択した後、溶接条件を選択すること。
                                    if (gtt_Table_code[Cnt].Pulse_type == 0) //2008.03.27中川さん要請で変更
                                    {
                                        guc_Remo_table_check_flag = true;
                                    }
                                 } 
                             } else {
                                 if(gtt_Table_code[Cnt].Pulse_mode == guc_Pulse_mode_data || gtt_Table_code[Cnt].Pulse_mode == 0x07) //2008.09.17 0x07を認識させる
                                 {
                                    if (gtt_Table_code[Cnt].Pulse_type == 0) //2008.03.27中川さん要請で変更
                                    {
                                        guc_Remo_table_check_flag = true;
                                        if (gtt_Table_code[Cnt].Pulse_mode == 0x07) //2008.11.06
                                        {
                                            gtt_Ctrl_flag.Crater_pulse_non = ON;
                                        } else {
                                            gtt_Ctrl_flag.Crater_pulse_non = OFF;
                                        }
                                    }
                                 } 
                             }
                          }
                         }
                     }
                  }
             }
             //<><><><><><><><><><><><><><><>



     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_table_code_read_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

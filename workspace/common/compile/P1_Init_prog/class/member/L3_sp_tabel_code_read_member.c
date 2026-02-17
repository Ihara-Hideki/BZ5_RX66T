//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｓｐ＿ｔａｂｅｌ＿ｃｏｄｅ＿ｒｅａｄ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      本溶接機が持つ全ての特殊テーブルを読み込む
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

void sp_table_code_read_member(void)
{
     PWELDNAME   pTbl = WLDNAMETBL_PTR;
     int         Cnt, Len;
     char        *pName;

     //if( isNewWeldTable( ) )
     //{
        for( Cnt = 0 ; Cnt <= WELDNAME_TBLCNT ; Cnt++ , ++pTbl )
        {
            if (pTbl->Kind == 0x00 && pTbl->Code == 0x00) break;

            gtt_Sp_table_code[gui_Sp_table_code_counter].Kind = pTbl->Kind;
            gtt_Sp_table_code[gui_Sp_table_code_counter].Code = pTbl->Code;
            pName = pTbl->Name;
            //for( Len = 0 ; Len <= WELDNAMELEN / 2 ; Len++ )
            for( Len = 0 ; Len <= 14 ; Len++ )
            {
                 gtt_Sp_table_code[gui_Sp_table_code_counter].Name[Len] = *(pName + Len);
            }
            gui_Sp_table_code_counter++;
        }
     //}
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_sp_table_code_read_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

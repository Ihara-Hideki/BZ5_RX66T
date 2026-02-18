//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚ƒ‚ˆ‚‚”‚”‚…‚’‚‰‚‚‡Q‚ƒ‚ˆ‚…‚ƒ‚‹Q‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      ŠO•”“ü—Íƒ`ƒƒƒ^ƒŠƒ“ƒOƒ`ƒFƒbƒN
//  yˆø”z
//      ‚È‚µ
//  y–ß‚è’lz
//      ‚È‚µ  
//  y”õlz
//      ‚È‚µ
//  yXV—š—ğz
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

void chattering_check_member(unsigned char xuc_Chattering_check_no)
{
     if (gtt_Ext_input.Data[xuc_Chattering_check_no] != gtt_Ext_input.Data_bkup[xuc_Chattering_check_no])
     {
         if (gtt_Ext_input.Counter[xuc_Chattering_check_no] > EXT_INPUT_COUNT)
         //if (gtt_Ext_input.Counter[xuc_Chattering_check_no] > 80)
         {
             gtt_Ext_input.Flag[xuc_Chattering_check_no]      = gtt_Ext_input.Data[xuc_Chattering_check_no];
             gtt_Ext_input.Data_bkup[xuc_Chattering_check_no] = gtt_Ext_input.Data[xuc_Chattering_check_no];
         }
         gtt_Ext_input.Counter[xuc_Chattering_check_no]++;
     } else {
         gtt_Ext_input.Counter[xuc_Chattering_check_no] = 0;
     }
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_chattering_check_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

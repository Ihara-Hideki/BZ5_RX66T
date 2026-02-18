//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚‰‚‰‚†Q‚‚‚‚Œ‚‚‡Q‚“‚ˆ‚‰‚†‚”Q‚‚…‚‚‚’‚™Q‚ƒ‚Œ‚‚“‚“
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚Q
//  y‹@”\à–¾z
//      ‚h‚h‚e‚ÌƒAƒiƒƒOƒ|[ƒg‚Ì‚O‚u“ü—Í‚ÌƒVƒtƒg—Ê‚ğ‹L‰¯‚·‚éB
//  yˆø”z
//      ‚È‚µ
//  y–ß‚è’lz
//      ‚È‚µ  
//  y”õlz
//      ‚È‚µ
//  yXV—š—ğz
//      2009.11.16  H.Ihara
//
//            Copyright(C)2009 Panasonic Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"
// EXTERNAL IIF NEW	2011.02.21 by @Tny
void iif_analog_shift_memory_class(unsigned char flag)
{
     if (flag == 1) //WRITE
     {
         gss_Iif_analog_shift_memory[1] = gss_Iif_analog_shift[1];
         dummy_access = 1;
         gss_Iif_analog_shift_memory[2] = gss_Iif_analog_shift[2];
         dummy_access = 1;
         gss_Iif_analog_shift_memory[3] = gss_Iif_analog_shift[3];
         dummy_access = 1;
     }
     if (flag == 0) //READ
     {
         gss_Iif_analog_shift[1] = gss_Iif_analog_shift_memory[1];
         dummy_access = 1;
         gss_Iif_analog_shift[2] = gss_Iif_analog_shift_memory[2];
         dummy_access = 1;
         gss_Iif_analog_shift[3] = gss_Iif_analog_shift_memory[3];
         dummy_access = 1;
     }
      
     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_iif_analog_shift_memory_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

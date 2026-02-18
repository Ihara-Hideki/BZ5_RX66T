//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚“‚…‚‘‚•‚…‚‚ƒ‚…Q‚‚‚‚‚‡‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚P
//  y‹@”\à–¾z
//      ƒV[ƒPƒ“ƒXŠÇ—
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

void sequence_manager(void)
{


#if 0
     //<><><><>ŒJ‚è•Ô‚µ—nÚ—p<><><><><> REPEAT 2007.1.12  2007.1.22íœ 2007.1.26ˆÚAiíœ“à—e‚ğˆÚAj
     if (gtt_Ctrl_counter.Repeat_weld > 0 && gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == true)
     {
         gtt_Ctrl_flag.Repeat_weld = ON;
         gtt_Ctrl_counter.Repeat_weld = 0;
     } else {
         gtt_Ctrl_flag.Repeat_weld = OFF;
     }
     //<><><><><><><><><><><><><><><><>
#endif
     guc_Sequence_mode = mag_sequence_dicision_class(guc_Sequence_mode);
     gtt_Ctrl_word     = weld_class(guc_Sequence_mode,gtt_Ctrl_word);
     table_access_class(false , guc_Sequence_mode); //2019.05.29 ihara del 2019.06.03 iki
     ext_device_ctrl_class(guc_Sequence_mode);

     //weld_test_class();




     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_sequence_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

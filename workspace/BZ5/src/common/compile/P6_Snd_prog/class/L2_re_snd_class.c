//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚’‚…Q‚“‚‚„Q‚ƒ‚Œ‚‚“‚“
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚Q
//  y‹@”\à–¾z
//      ƒƒ{ƒbƒg‘—M •@‚o‚bi‚r‚fƒVƒŠ[ƒYj‘—M
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

void re_snd_class (void)
{

        //************************************* ‹@í•\¦ **************************************
        if (ComuniPackRemo.Data.bRS422Connection == true && guc_Machine_no_flag == false)
        {
           guc_Machine_no_flag = true;

           ComuniPackRemo.Data.From.uc_Com_16led_data[0]  = 's';
           ComuniPackRemo.Data.From.uc_Com_16led_data[1]  = 't';
           ComuniPackRemo.Data.From.uc_Com_16led_data[2]  = 'd';
           ComuniPackRemo.Data.From.uc_Com_16led_data[3]  = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[4]  = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[5]  = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[6]  = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[7]  = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[8]  = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[9]  = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[10] = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[11] = ' ';
           ComuniPackRemo.Data.From.uc_Com_16led_data[12] = ' ';


           REMO_Send_CMD(0x20);
            
        }

        //********************** *******************************
        if(Timer._100m != gtt_Ctrl_counter.Backup_100m && ComuniPackRemo.Data.bRS422Connection)	// 100m•bŒo‰ß‚µ‚½H
        {
           REMO_Send_CMD(0x21);
           gtt_Ctrl_counter.Backup_100m = Timer._100m;
        }
        





        //*************************************************************************************

     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_rob_snd_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

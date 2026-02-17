//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚†‚‰‚˜Q‚„‚‚”‚Q‚”‚’‚‚‚“‚†‚…‚’Q‚‚…‚‚‚‚…‚’
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚R
//  y‹@”\à–¾z
//      ŒÅ’èƒf[ƒ^“]‘—
//  yˆø”z
//      ‚È‚µ
//  y–ß‚è’lz
//      ‚È‚µ  
//  y”õlz
//      ‚g‚o‚hƒ‰ƒCƒuƒ‰ƒŠ[g—p
//  yXV—š—ğz
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include  "custom.h"

//extern void xmemset(void *dst, int dat, size_t lgh);
//extern void xmemcpy(void *dst, const void *soc, size_t lgh);


extern unsigned char weld_fix_tbl;
extern unsigned char srv_fix_tbl;

void fix_data_transfer_member(void)
{
     unsigned int i;

     i = 0;                  //2006.8.30 clear

     //xmemcpy ((unsigned char *)_union.Init.WldParm, &weld_fix_tbl,(100 * 2)); 2019.04.02 del ihara
     //hpiWrite( hpicmdOUTWLDINIT , _union.Init.WldParm );                                 //ŒÅ’èƒpƒ‰ƒ[ƒ^‚c‚r‚o‚É“]‘— 2019.04.02 del ihara
#if 0
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
     for(i=0;i<0xffff;i++){WDG_Clear();}
#endif
     //xmemcpy ((unsigned char *)_union.Init.SrvParm, &srv_fix_tbl,(100*2)); 2019.04.02 del ihara
     Set_DCRPM( (psint)&_union.Init.SrvParm[ 98 ] , (psint)&_union.Init.SrvParm[ 99 ] ); //ƒT[ƒ{ŒÅ’èƒpƒ‰ƒ[ƒ^
     //hpiWrite( hpicmdOUTSRVINIT , _union.Init.SrvParm ); 2019.04.02 del ihara
     WDG_Clear();
     for(i=0;i<0xffff;i++){
         WDG_Clear();
     }
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_fix_data_transfer_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

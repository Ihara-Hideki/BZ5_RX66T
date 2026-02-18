//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yŠÖ”–¼z
//@@@‚…‚’‚’Q‚Œ‚…‚–‚…‚Œ‚RQ‚ƒ‚Œ‚‚“‚“
//@yŠÖ”ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚Q
//  y‹@”\à–¾z
//      ‚k‚d‚u‚d‚k‚RƒGƒ‰[i‚l‚fQ‚n‚e‚e¨“dŒ¹‚n‚e‚ej
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
#include "custom.h"

unsigned int err_level3_class(void)
{
     unsigned char puc_Err_code;
     unsigned int  pui_Err_code;

     puc_Err_code = 0;       //2006.8.30 clear
     pui_Err_code = 0;       //2006.8.30 clear


	// Phase28 by Tny 2008.11.21
    if(gtt_Ctrl_flag.Welder_init_execution == OFF) puc_Err_code = emg_err_member(puc_Err_code);  //”ñí’â~

//---------------------------------------------
#if true	// <--- true = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny


#if 1

     puc_Err_code = cd_err_member(puc_Err_code);                 //“d—¬ŒŸoˆÙí
     if(gtt_Ctrl_flag.Welder_init_execution == OFF) puc_Err_code = primary_voltage_err_member(puc_Err_code);    //ˆêŸ“dˆ³ˆÙí
#endif

     puc_Err_code = second_voltage_err_member(puc_Err_code);     //“ñŸ‰ß“dˆ³ˆÙí 2008.11.17

//2008.3.21 ƒAƒ“ƒoƒ‰ƒ“ƒXƒGƒ‰[–³Œø‰»
     puc_Err_code = primary_current_err_member(puc_Err_code);    //ˆêŸ“d—¬‚e‚a’lˆÙí‚µ‚Ä•œŠˆ 2008.11.17
     puc_Err_code = com_err_member(puc_Err_code);                //’ÊMˆÙí
#if true
     puc_Err_code = motor_current_err_member(puc_Err_code);      //ƒ‚[ƒ^‰ñ“]ˆÙíiƒ‚[ƒ^‰ß“d—¬ˆÙíj2007.3.22@LEVEL3
#endif


#endif
//---------------------------------------------


//-------------------------------------------------------------------------
// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
//
	if(gb_Iif_comuni_failed){
		puc_Err_code = IIF_CONNECT_ERR;
	}
//-------------------------------------------------------------------------
     if (puc_Err_code > 0)
     {
        pui_Err_code = ERR_LEVEL3_ADD_CODE | ((unsigned int)puc_Err_code & 0x00ff); //•t‰ÁƒR[ƒh˜AŒ‹
     } else {
        pui_Err_code = ERR_LEVEL3_NON_CODE & ((unsigned int)puc_Err_code);          //•t‰ÁƒR[ƒhíœ
     }
        
     return(pui_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_err_level3_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

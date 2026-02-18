//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｓｔｉｃｋ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      スティックチェック
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


#if true	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
unsigned char stick_err_member(unsigned char xuc_Err_code)
{
	unsigned char puc_Err_code = xuc_Err_code;	// 現状の継承

	if((gtt_Ctrl_flag.Stick_start == ON) && (gtt_Ctrl_flag.Stick_end == ON)){
		if(gtt_Ctrl_flag.Stick_snd_set == OFF){
			if(gtt_Ctrl_flag.Stick_on_off_check == OFF){	// ＯＮでスティック検知（2011.10.28時点で判定が逆でした）	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
				ComuniPack.Data.From.fErrorCode1.Bit1Sw.b2 = ON;
				gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = OFF;
				if(guc_Robot_connect_flag == false){	// ロボット接続時はエラー表示を行わない  <EXTERNAL IIF NEW(Phase 12)> 2011.11.18
					puc_Err_code = ERR_CLEAR;	//異常解除
				}
			}
			else{
				ComuniPack.Data.From.fErrorCode1.Bit1Sw.b2 = OFF;
				gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON;
				LED4 = ON; //test 2009.07.24
				if(guc_Robot_connect_flag == false){	// ロボット接続時はエラー表示を行わない  <EXTERNAL IIF NEW(Phase 12)> 2011.11.18
					puc_Err_code = STICK_ERR;	//スティック検知
				}
			}
			gtt_Ctrl_flag.Stick_snd_set = ON;
		}
		else{
			if(gtt_Ctrl_flag.Stick_on_off_check == OFF){	// ＯＮでスティック検知（2011.10.28時点で判定が逆でした）	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
				if(guc_Robot_connect_flag == false){	// ロボット接続時はエラー表示を行わない  <EXTERNAL IIF NEW(Phase 12)> 2011.11.18
					puc_Err_code = ERR_CLEAR;	//異常解除
				}
			}
			else{
				LED4 = ON; //test 2009.07.24
				if(guc_Robot_connect_flag == false){	// ロボット接続時はエラー表示を行わない  <EXTERNAL IIF NEW(Phase 12)> 2011.11.18
					puc_Err_code = STICK_ERR;	//スティック検知
				}
			}
		}
	}
	else{
		gtt_Ctrl_flag.Stick_snd_set	= OFF;
		if(guc_Robot_connect_flag == false){	// ロボット接続時はエラー表示を行わない  <EXTERNAL IIF NEW(Phase 12)> 2011.11.18
			puc_Err_code = ERR_CLEAR;	//異常解除
		}
	}
	return(puc_Err_code);
}
#else
void stick_err_member(void)
{
     if (gtt_Ctrl_flag.Stick_start == ON && gtt_Ctrl_flag.Stick_end == ON)
     {
         if (gtt_Ctrl_flag.Stick_snd_set == OFF)
         {
             if (gtt_Ctrl_flag.Stick_on_off_check == OFF)
             {
                 //ComuniPack.Data.From.fErrorCode1.Bit1Sw.b0 = ON;
                 //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b0 = OFF;
                 ComuniPack.Data.From.fErrorCode1.Bit1Sw.b2 = ON;             //2009.07.14
                 gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = OFF;      //2009.07.14
             } else {
                 //ComuniPack.Data.From.fErrorCode1.Bit1Sw.b0 = OFF;
                 //gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b0 = ON;
                 ComuniPack.Data.From.fErrorCode1.Bit1Sw.b2 = OFF;            //2009.07.14
                 gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b2 = ON;       //2009.07.14
                 LED4 = ON; //test 2009.07.24  
             }
             gtt_Ctrl_flag.Stick_snd_set = ON;
         }
     } else {
         gtt_Ctrl_flag.Stick_snd_set      = OFF;
         //gtt_Ctrl_flag.Stick_on_off_check = OFF; 2007.3.23
     }
     return;
}
#endif
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_stick_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

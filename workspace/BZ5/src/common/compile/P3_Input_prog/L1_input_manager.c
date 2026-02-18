//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｐｕｔ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      入力管理
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

void input_manager(void)
{
     //input_r8_class(); 2019.04.02 del ihara

//2006.11.28 復活
#if true	// <--- ture = not Debug!!  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
	input_ext_class();
#endif


     //input_dsw_class(); 2009.04.14
//--------- Phase4 by @Tny 2008/09/08 --------
#if false //2019.04.02 ihara false
     input_ext_vr_class();
#endif
//--------------------------------------------

//--------- Phase8 by @Tny 2008/09/12 --------
#if false //2019.04.02 ihara false
    if(gus_Iif_Detect_Timer <= 0){   // IIF接続確認時間カウンタ
        if(gb_IIF_Select == false){  // まだ、IIF接続の確認が出来ていない？
            if(gus_Iif_BuiltIn != 0){ // IIFは非接続ではない？
//--------- Phase13 by @Tny 2008/09/18 --------
#if true
                gb_Iif_BuiltIn          = false;
#endif
//--------------------------------------------
                gus_Iif_BuiltIn         = 0;    // IIFは非接続
                gus_Iif_BuiltIn_write   = true; // IIF接続フラグの保存要求
            }
			else{	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
				gb_Iif_BuiltIn          = false;
			}
//-------------------------------------------------
// <EXTERNAL IIF NEW(Phase 5)>	2011.10.26 by @Tny
			gb_Iif_Disconnect	= true;			// ＩＩＦ切断フラグ：切断確定
//-------------------------------------------------
        }
    }
#endif
//--------------------------------------------
     //input_fpga_class();    未作成

#if false // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny  2019.04.02 ihara false
    if (gb_IIF_Select == true) //IIF NEW
    {
		if((gb_ServiceMenu)||(gb_RescueMenu)){	// レスキュー＆サービスマン・モード時はＩＩＦの入力は無効とする  <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
		}
		else{
	        if (ComuniPackIif.Data.To.bChangeData == true)
	        {
		        InternalPackIif.Data.To.us_Iif_input_data        =  ComuniPackIif.Data.To.us_Iif_input_data;	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
		        InternalPackIif.Data.To.us_Analog_data[1]        =  ComuniPackIif.Data.To.us_Analog_data[1];
		        InternalPackIif.Data.To.us_Analog_data[2]        =  ComuniPackIif.Data.To.us_Analog_data[2];
		        InternalPackIif.Data.To.us_Analog_data[3]        =  ComuniPackIif.Data.To.us_Analog_data[3];
		        InternalPackIif.Data.To.us_Analog_data[4]        =  ComuniPackIif.Data.To.us_Analog_data[4];
		        InternalPackIif.Data.To.us_Iif_analog_revise[1]  =  ComuniPackIif.Data.To.us_Iif_analog_revise[1];
		        InternalPackIif.Data.To.us_Iif_analog_revise[2]  =  ComuniPackIif.Data.To.us_Iif_analog_revise[2];
		        InternalPackIif.Data.To.us_Iif_analog_revise[3]  =  ComuniPackIif.Data.To.us_Iif_analog_revise[3];
		        InternalPackIif.Data.To.us_Iif_analog_revise[4]  =  ComuniPackIif.Data.To.us_Iif_analog_revise[4];
		        InternalPackIif.Data.To.t_Iif_dsw.ALL            =  ComuniPackIif.Data.To.t_Iif_dsw.ALL;
		        InternalPackIif.Data.To.uc_Iif_volt_jumper       =  ComuniPackIif.Data.To.uc_Iif_volt_jumper;
	                gtt_Ctrl_flag.Iif_first_rcv                      =  ON;
	            input_iif_class();
	            input_iif_analog_class();
	            ComuniPackIif.Data.To.bChangeData = false;
	        }
			else{	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
				input_iif_class();
			}
		}
    }
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_input_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

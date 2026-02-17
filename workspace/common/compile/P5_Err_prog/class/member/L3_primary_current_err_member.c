//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｐｒｉｍａｒｙ＿ｃｕｒｒｅｎｔ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      一次電流異常（ツインインバータアンバランスエラー）
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
#include "custom.h"

#define VP_ERROR 1

unsigned char primary_current_err_member(unsigned char xuc_Err_code)
{

//<><><><><>本ファイルは2007.1.26ファイルごと移植<><><><><><>
    unsigned int pui_Max,pui_Min;
    unsigned char puc_Err_code;

    unsigned int pui_Unbalance_rate;

    unsigned short pus_Unbalance_max_rate;
    unsigned short pus_Unbalance_min_rate;



    pui_Max        = 0;                //2006.8.30 clear
    pui_Min        = 0;                //2006.8.30 clear
    puc_Err_code   = xuc_Err_code;        //2006.9.8 現状の継承

    
    if(gtt_Ctrl_flag.Primary_current_err == ON) //2008.11.17
    {
       puc_Err_code = PRI_OVER_CURRENT_ERR;      //一次過電流検出
    }

//*********************************** アンバランス検出を電流領域で変更する 2007.2.10 ********************************
#if 0  //2008.11.17アンバランスエラー関連全削除
    if(guc_Sequence_mode == MAIN_WELD) //溶接期間中の判定値をセット
    {

#if 0
       //<><><><><> 2007.3.14 ＰＯより移植   2007.3.19　無効化（田中さん要望）<><><><><>
       //if (gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd == ON && gtt_Fpga.Curr_result_unb >=5 && gtt_internal_r8.Ex_data != 0)  //ロボットに動作することを知らせるためだけに使用する。
       if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == ON && gtt_Fpga.Curr_result_unb >=5 && gtt_internal_r8.Ex_data != 0)  //2007.3.15変更
       {
               if(gtt_Ctrl_flag.Pri_curr_fb1_err_unb == OFF)
               {
                  gtt_Ctrl_flag.Pri_curr_fb1_err_unb = ON;
                  gtt_Ctrl_counter.Pri_curr_fb1_err_unb = PRI_CURR_FB_ERR_UNB_TIME;
	       } else if(gtt_Ctrl_counter.Pri_curr_fb1_err_unb <= 0) {
                         puc_Err_code = PRI_CURR_FB1_ERR;
                         return (puc_Err_code);
               }
           
       } else {
             gtt_Ctrl_flag.Pri_curr_fb1_err_unb = OFF;
       }
       //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#endif

#if 0 //AZ3はツインインバータではないのでアンバランスエラーは要らない。2008.10.20
       if (gtt_Fpga.Curr_result >= UNBALANCE_DETECT_CURRENT_HI) //アンバランス電流検出の判定　１００Ａ以上
       {
           pus_Unbalance_max_rate = UNBALANCE_MAX_RATE_HI;
           pus_Unbalance_min_rate = UNBALANCE_MIN_RATE_HI;
       } 
       if (gtt_Fpga.Curr_result < UNBALANCE_DETECT_CURRENT_HI && gtt_Fpga.Curr_result >= UNBALANCE_DETECT_CURRENT_MD) //アンバランス電流検出の判定　１００Ａ未満　７０Ａ以上
       {
           pus_Unbalance_max_rate = UNBALANCE_MAX_RATE_MD;
           pus_Unbalance_min_rate = UNBALANCE_MIN_RATE_MD;
       } 
       if (gtt_Fpga.Curr_result < UNBALANCE_DETECT_CURRENT_MD && gtt_Fpga.Curr_result >= UNBALANCE_DETECT_CURRENT_LO) //アンバランス電流検出の判定　７０Ａ未満　４０Ａ以上　（４０Ａ未満は検出を行わない）
       {
           pus_Unbalance_max_rate = UNBALANCE_MAX_RATE_LO;
           pus_Unbalance_min_rate = UNBALANCE_MIN_RATE_LO;
       } 
       if (gtt_Fpga.Curr_result >= UNBALANCE_DETECT_CURRENT_LO) //４０Ａ以上で検出（４０Ａ未満では検出を行わない）
       {
           pui_Unbalance_rate = (unsigned int)(((float)(gtt_Fpga.Curr_result - gtt_internal_r8.Pri_curr_fb1) / (float)gtt_Fpga.Curr_result) * 100.0);

           //<><><><><><>起動時０．４秒検出2007.4.17  →　2007.5.10　１．０秒に変更<><><><><><>
           //if (gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw == ON && gtt_Ctrl_flag.Pri_curr_fb1_err_04_check == OFF)
           if (gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd == ON && gtt_Ctrl_flag.Pri_curr_fb1_err_04_check == OFF) //2007.7.10トーチｓｗからCDに変更
           {
               if(gtt_Ctrl_flag.Pri_curr_fb1_start_err == OFF)
               {
                  gtt_Ctrl_flag.Pri_curr_fb1_start_err = ON;
                  gtt_Ctrl_counter.Pri_curr_fb1_start_err = PRI_CURR_FB_START_ERR_TIME;
	            } else if(gtt_Ctrl_counter.Pri_curr_fb1_start_err <= 0) {

                   if (pui_Unbalance_rate <= 5.0 || pui_Unbalance_rate >= 95.0)
                   {
                       puc_Err_code = PRI_CURR_FB1_ERR;
                   }
                   gtt_Ctrl_flag.Pri_curr_fb1_err_04_check = ON;
               }
               
            }
            if (gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd == OFF) //2007.7.10トーチｓｗからCDに変更
            {
                gtt_Ctrl_flag.Pri_curr_fb1_err_04_check = OFF;
                gtt_Ctrl_flag.Pri_curr_fb1_start_err = OFF;
            }
            //<><><><><><><><><><><><><><><><><><><><><><><><><><>



           if (pui_Unbalance_rate <= pus_Unbalance_min_rate || pui_Unbalance_rate >= pus_Unbalance_max_rate) //2007.1.24MAX側の符号変更
           {
               if(gtt_Ctrl_flag.Pri_curr_fb1_err == OFF)
               {
                  gtt_Ctrl_flag.Pri_curr_fb1_err = ON;
                  gtt_Ctrl_counter.Pri_curr_fb1_err = PRI_CURR_FB_ERR_TIME;
	           } else if(gtt_Ctrl_counter.Pri_curr_fb1_err <= 0) {
                         puc_Err_code = PRI_CURR_FB1_ERR;
               }
           } else {
             gtt_Ctrl_flag.Pri_curr_fb1_err = OFF;
           }



       } else {
         gtt_Ctrl_flag.Pri_curr_fb1_err = OFF;
         gtt_Ctrl_flag.Pri_curr_fb1_err_04_check = OFF; //2007.7.6追加
         gtt_Ctrl_flag.Pri_curr_fb1_start_err = OFF;    //2007.7.6追加
       }
#endif
    } else {
      gtt_Ctrl_flag.Pri_curr_fb1_err = OFF;
      gtt_Ctrl_flag.Pri_curr_fb1_err_04_check = OFF; //2007.7.6追加
      gtt_Ctrl_flag.Pri_curr_fb1_start_err = OFF;    //2007.7.6追加
    }

#if 0
    if(guc_Sequence_mode == MAIN_WELD) //溶接期間中の判定値をセット
    {

       if (gtt_Fpga.Curr_result >= UNBALANCE_DETECT_CURRENT) //アンバランス電流検出最低値の判定　出力２００Ａ以上で検出を行う。2007.1.18 １００以上で検出を行うに変更2007.1.26
       {
           pui_Unbalance_rate = (unsigned int)(((float)(gtt_Fpga.Curr_result - gtt_internal_r8.Pri_curr_fb1) / (float)gtt_Fpga.Curr_result) * 100.0);
           if (pui_Unbalance_rate <= UNBALANCE_MIN_RATE || pui_Unbalance_rate >= UNBALANCE_MAX_RATE) //2007.1.24MAX側の符号変更
           {
               if(gtt_Ctrl_flag.Pri_curr_fb1_err == OFF)
               {
                  gtt_Ctrl_flag.Pri_curr_fb1_err = ON;
                  gtt_Ctrl_counter.Pri_curr_fb1_err = PRI_CURR_FB_ERR_TIME;
	           } else if(gtt_Ctrl_counter.Pri_curr_fb1_err <= 0) {
                         puc_Err_code = PRI_CURR_FB1_ERR;
               }
           } else {
                  gtt_Ctrl_flag.Pri_curr_fb1_err = OFF;
           }
       } else {
              gtt_Ctrl_flag.Pri_curr_fb1_err = OFF;
       }
    } else {
           gtt_Ctrl_flag.Pri_curr_fb1_err = OFF;
    }
#endif

#if 0
       //<><><><><> ＦＢ１の判定 <><><><><>
       if (gtt_internal_r8.Pri_curr_fb1 <= PRI_CURR_FB_MIN || gtt_internal_r8.Pri_curr_fb1 >= PRI_CURR_FB_MAX)
       {
          if(gtt_Ctrl_flag.Pri_curr_fb1_err == OFF)
          {
             gtt_Ctrl_flag.Pri_curr_fb1_err = ON;
             gtt_Ctrl_counter.Pri_curr_fb1_err = PRI_CURR_FB_ERR_TIME;
	  } else if(gtt_Ctrl_counter.Pri_curr_fb1_err <= 0) {
             puc_Err_code = PRI_CURR_FB1_ERR;
          }
       } else {
         gtt_Ctrl_flag.Pri_curr_fb1_err = OFF;
       }
       //<><><><><> ＦＢ２の判定 <><><><><>
       if (gtt_internal_r8.Pri_curr_fb2 <= PRI_CURR_FB_MIN || gtt_internal_r8.Pri_curr_fb2 >= PRI_CURR_FB_MAX)
       {
          if(gtt_Ctrl_flag.Pri_curr_fb2_err == OFF)
          {
             gtt_Ctrl_flag.Pri_curr_fb2_err = ON;
             gtt_Ctrl_counter.Pri_curr_fb2_err = PRI_CURR_FB_ERR_TIME;
	  } else if(gtt_Ctrl_counter.Pri_curr_fb2_err <= 0) {
             puc_Err_code = PRI_CURR_FB2_ERR;
          }
       } else {
         gtt_Ctrl_flag.Pri_curr_fb2_err = OFF;
       }
    }
#endif

#endif
    return (puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_primary_current_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

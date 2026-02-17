//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｉｔｉａｌ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      各種初期化
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
//#pragma      keyword asm on
#include    "custom.h"

#include "r_typedefs.h"
#include "port_init.h"
#include "iodefine.h"
#include "devdrv_bsc.h"
#include "rza_io_regrw.h"

#include "stdint.h"

#ifdef __CC_ARM
#pragma arm section code   = "CODE_RESET"
#pragma arm section rodata = "CONST_RESET"
#pragma arm section rwdata = "DATA_RESET"
#pragma arm section zidata = "BSS_RESET"
#endif



void initial_manager(void)
{



    /* ==== Start clock supply of the peripheral functions ==== */
    STB_Init();

    /* This source code be enabled to use the SDRAM. */
    /* Note: If the two serial flash memory be connected (8-bit access used), */
    /* this source code can not be enabled due to conflict with the pin for SDRAM control. */

    /* ==== PORT setting ==== */
    //PORT_Init(); ihara del 2019.05.28
     ini_io_class();                       //Ｉ／Ｏ初期化

    /* ==== BSC setting ==== */
    /* Initialize the CS0 spaces */	// 2019.05.27
    R_BSC_Init((uint8_t)(BSC_AREA_CS0 | BSC_AREA_CS1));

    /* ==== INTC setting ==== */
    R_INTC_Init();

    /* ==== Initial setting of the level 2 cache ==== */
    L2CacheInit();

    /* ==== Initial setting of the level 1 cache ==== */
    L1CacheInit();

    /* ==== Vector base address setting ==== */
    VbarInit();

    __enable_irq();         /* Enable IRQ interrupt */
    __enable_fiq();         /* Enable FIQ interrupt */

    /* ==== Initialize Terminal ==== */
    /* SCIF 0ch */
    /* P1 clock=66.67MHz CKS=0 SCBRR=17 Bit rate error=0.46% => Baud rate=115200bps */
//  IoInitScif0();
    IoInitScif4();

#ifdef __CC_ARM
    /* ==== Function call of main function ==== */
    $Super$$main();
#endif

     //unsigned short int pui_Motor_ctrl; //2007.3.22							2019.03.26 del ihara

     //pui_Motor_ctrl = 0x0001;          //2007.3.22 							2019.03.26 del ihara


     //   gus_cRTC_AdjustCount    = 0;    // RTC周波数測定用カウンタ					2019.03.26 del ihara
     //   gul_vRTC_FrequencyCount = 0;    // RTC周波数カウンタ						2019.03.26 del ihara

     //ini_ad_class();                       //ＡＤ初期化						2019.03.26 del ihara

     //ini_timer_class();                    //タイマの初期化						2019.03.26 del ihara

     //ini_interrupt_setting_class();        //割り込み順位設定						2019.03.26 del ihara

     //ini_memory_class();                   //変数初期化							2019.03.26 del ihara

     //ini_table_code_read_class();         //本溶接機が持つ全ての条件テーブルと特殊テーブルを読み込む	2019.03.26 del ihara

     //ini_fpga_dsp_class();                 //ＦＰＧＡ、ＤＳＰ初期化　起動				2019.03.26 del ihara

     //int_permit_class();                   		//割り込み許可					2019.03.26 del ihara
     
     //hpiWrite( hpicmdOUTSRVSEQ , &pui_Motor_ctrl);   //DSPに送信 2007.3.22				2019.03.26 del ihara


#if false //2019.03.26 del ihara
    // RTC初期化の確認
    {
        ubool    ErrorFlag = false;
        // RTC初期化開始
        if(RTC_Reset(true)){ // 初期化に失敗？
            ErrorFlag = true;
            //while(true); 2008.10.30 del
        }
        else{
            gus_RTC_ReNew = RTC_RENEWAL;    // RTC初期化済みを記憶

            gb_RTC_Debug_Sec    = false;            // ＲＴＣ動作確認用フラグ（秒）
            gus_RTC_cDebug_1    = 0;                // ＲＴＣ動作確認用カウンタ＃１
        }
    }
#endif


#if false //2019.03.26 del ihara
    if(gtt_Error_History.Record_identifier != ERROR_INFO_RENEWAL){ // 記録識別子がセットされていない？（＝初期化されていない？）
        gtt_Error_History.History_rec_index = 0;                    // 記録インデックスの初期化
        gtt_Error_History.Full_history_rec  = false;                // 全記録エリア使用フラグの初期化
        gtt_Error_History.Start_record      = false;                // 記録開始フラグの初期化
        gtt_Error_History.Record_identifier = ERROR_INFO_RENEWAL;   // 記録識別子のセット
        gb_Error_History_Write              = true;                 // エラー履歴テーブル保存の要求
    }
#endif


#if false //2019.03.26 del ihara
    ini_com_set_class();                  //通信設定 2007.7.10追加
    guc_R8_control.Bit1Sw.R8_Fan    = true; //2008.11.14追加
    FAN2                            = ON;   //2008.11.14追加
#endif


	com_memory_member(1);	// 2019.05.30

	guc_Controller_gas_sw_cancel = OFF;	// 2019.06.03

}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_initial_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

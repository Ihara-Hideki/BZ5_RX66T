//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　ｃｕｓｔｏｍ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－０
//  【ヘッダ説明】
//      溶接機固有ヘッダ
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#ifndef	__YD400GZ3_H
//-------------------------------------------------
#define	__YD400GZ3_H
#define	__M32186
#define __DEBUG		// デバッグ中！！
					// 「Fix Me!!」も確認すること！！


// 2019.09.02
#define __NEWCOM_PROTOCOL


#define G3_NEW_COM 1
#define TBLCNT              72
//#define REMO_TBLCNT         20
#define REMO_TBLCNT         15 //2008.07.18　２０も要らないと判断し１５に変更
#define WELDNAME_TBLCNT     32


//#define NAVITBLCNT          105 //2009.01.14 BP4 2009.03.18 100->105
#define NAVITBLCNT          125 //2010.03.03 105->125

// Phase2 @Tny
//
#define FRAM_PAKECT         4   // 32/n = TX Byte

#define CPU_di( )               ( DI_imask( ) )//2007.3.9追加
#define CPU_ei( )               ( EI_imask( ) )//2007.3.9追加

// 基本define宣言
//
#define	true            1
#define	false           0
#define ON              true
#define OFF             false
#define	FOREVER		for(;;)
#define	NUL             0
#define WDT_ADDR        0x00170000l
#define WDG_Clear()     (*((unsigned short int *)WDT_ADDR) = 0x0001)
#define ARRAY_WIDTH     30

//----- Phase22 by @Tny 2008/10/07 -----
#if true
//#define CH 17           //メモリ記憶用ｃｈ数  16->17 記憶チャンネルは１～１６であるため
#define CH 51           //メモリ記憶用ｃｈ数  16->17 記憶チャンネルは１～１６であるため  2009.03.16 ５０チャンネルに変更
#endif
//--------------------------------------------
//#define SELECT_DITAL_MAX          50 //詳細メニューの最大値
//#define SELECT_DITAL_MAX          85 //詳細メニューの最大値 2008.10.10
//#define SELECT_DITAL_MAX          32 //詳細メニューの最大値 2008.10.10 2009.03.16 2010.03.03 30->32
#define SELECT_DITAL_MAX          33 //詳細メニューの最大値 2008.10.10 2009.03.16 2010.03.03 30->32		<IIF NEW> 32->33 2011.10.07
//#define SELECT_DITAL_MAX          12 //詳細メニューの最大値 BP4 Phase3 by @Tny 2009.01.15

//特殊パラメータ
#define USER_PARAMETER_NO        100 //2008.10.30 10 -> 100
//サービスマン
#define SERVICE_DATA_NO          30 //2008.09.02 暫定個数 2008.10.30 3->10		BP4 Phase13 by @Tny 2009.02.23
//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
//#define RESCUE_DATA_NO			5
//#define RESCUE_DATA_NO			6
#define RESCUE_DATA_NO			7	// 「交流波形出力モード」追加	2011.11.08
//---------------------------------------------------

//20110916_1+++++
 //<><><><><> 出力電流上下限値 2011.09.16 <><><><><>
//#define     MAX_CURRENT_VAL           300	    // 2011.09.16 500BP4 DC,AC_STD,AC_HARD,MIX
#define     MAX_CURRENT_VAL           400	    // 2011.09.16 500BP4 DC,AC_STD,AC_HARD,MIX			2019.08.21
#define     MAX_CURRENT_AC_SOFT_VAL   200       // 2011.09.16 500BP4 AC_SOFT
#define     MAX_CURRENT_HAND_VAL      250       // 2011.09.16 500BP4 HAND
//#define     MIN_CURRENT_VAL             4       // 2011.09.16 500BP4 DC
#define     MIN_CURRENT_VAL             1       // 2011.09.16 500BP4 DC								2019.08.21
#define     MIN_CURRENT_AC_HARD_VAL    20       // 2011.09.30 AC_HARD
//#define     MIN_CURRENT_AC_VAL         10       // 2011.09.16 AC_STD,AC_SOFT,MIX
#define     MIN_CURRENT_AC_VAL          1       // 2011.09.16 AC_STD,AC_SOFT,MIX					2019.08.21
#define     MIN_CURRENT_HAND_VAL        4       // 2011.09.16 500BP4 HAND		10->4 2012.05.30

//d －－－－－－－－参考 300BP4－－－－－－－－－－－－－－－
//d  //<><><><><> 出力電流上下限値 2010.03.10 by @Tny【ＮＯ１５】(2010.01.12) <><><><><>
//d  #define     MAX_CURRENT_VAL			300			// 300BP4 DC,AC_STD,AC_HARD,MIX
//d  #define     MAX_CURRENT_AC_SOFT		200			// 300BP4 AC_SOFT
//d  #define     MAX_CURRENT_HAND		250			// 300BP4 HAND
//d  #define     MIN_CURRENT				  4			// 300BP4 DC
//d  #define     MIN_CURRENT_AC			 10			// 300BP4 AC_STD,AC_SOFT
//d  #define     MIN_CURRENT_AC_HARD		 20			// 300BP4 AC_HARD
//d  #define     MIN_CURRENT_AC_MIX		 10			// 300BP4 AC,MIX
//d  #define     MIN_CURRENT_HAND		  4			// 300BP4 HAND
//d  //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//d  
//d  //<><><><><> 出力電流上下限値 2010.01.12 <><><><><>
//d  #define     MAX_CURRENT_VAL           500	    // 2010.01.12 500BP4 DC,AC_STD,AC_HARD,MIX
//d  #define     MAX_CURRENT_AC_SOFT_VAL   330       // 2010.01.12 500BP4 AC_SOFT
//d  #define     MAX_CURRENT_HAND_VAL      400       // 2010.01.12 500BP4 HAND
//d  #define     MIN_CURRENT_VAL             5       // 2010.01.12 500BP4 DC
//d  #define     MIN_CURRENT_AC_MIX_VAL     20       // 2010.01.12 500BP4 AC,MIX
//d  #define     MIN_CURRENT_HAND_VAL       10       // 2010.01.12 500BP4 HAND
//d  //<><><><><><><><><><><><><><><><><><><><><><><><><>
//20110916_1-----



//ＥＮ一元化関連
#define EN_VOLT_P           0 //＋電圧値
#define EN_VOLT_M           1 //－電圧値
#define EN_VOLT_0           2 //ＥＮ０％時電圧値
#define EN_INIT             0 //初期電流のＥＮ比率 2008.10.01
#define EN_MAIN             1 //本電流のＥＮ比率 2008.10.01
#define EN_CRATER           2 //クレータ電流のＥＮ比率 2008.10.01
#define EN_WAVE             3 //ローパルス電流のＥＮ比率 2008.10.10
#define EN_START            4 //スタート電流のＥＮ比率 2008.10.10
#define EN_Q                5 //一元電圧問い合わせＥＮ比率 2008.11.28

//BP4用詳細メニュー番号 Phase4,Phase5,Phase6,Phase7 by @Tny 2009.01.15-2009.02-16
#define P_DC_TIG_START      0 //P00
#define P_HOT_CURR_LEVEL    1 //P01
#define P_VOLT_DISPLAY      2 //P02
#define P_CRATER_ENDING     3 //P03
#define P_ELECTRODE_SHORT	4 //P04
#define P_DISPLAY_HOLD_TIME 5 //P05
#define P_AC_ARC_RECOVERY   6 //P06
#define P_NOW_DATE_TIME     7 //P07
#define P_DATE_TIME_DISPLAY 8 //P08
#define P_CURR_DISPLAY      9 //P09
#define P_DENBOU           10 //P10
#define P_ARC_DRIVE        11 //P11
#define P_WELD_NAME        12 //P12 2009.03.07
#define P_LCD_BRIGHT       13 //P13 2009.03.07
#define P_EXTARNAL_LEVEL_A 14 //P14 2009.03.07 エキスパートモード
#define P_EXTARNAL_MASK_TIME 15 //P15 2010.01.08 エキスパートモードマスク時間
#define P_REMOCON_SELECT   16 //P16 2009.03.07
#define P_VARIABLE_CRATER_REPEAT 17 //P17 2009.03.14
#define P_MAX_OUTPUT       18 //P18 2010.01.08 by @Tny
#define P_MILD_PULSE       19 //P19 2010.01.20 by @Tny
#define P_AC_FRQ_DISP      20 //P20 2010.01.20 by @Tny
#define P_ARC_ASSIST       21 //P21 2010.02.25

//#define P_SOFT_START_TIME   22 //P22 2011.10.01 ソフトスタート時間		「ソフトスタート時間」削除 2011.10.31
//#define P_EXECUTE_VOLTAGE_A 23 //P23 2010.02.25 エキスパートモード実験用 2009.03.07
#define P_DETAIL_DISPLAY    22 //P22 2011.10.03		「ソフトスタート時間」削除に伴う変更 2011.10.31
#if true	// <IIF NEW>
	#define P_IIF_SELECT		23 //P23 <IIF NEW> 2009.11.17 by @Tny	「ソフトスタート時間」削除に伴う変更  	2011.10.31
	#define P_SOFT_START_TIME   24 //P24 2011.10.01 ソフトスタート時間		「ソフトスタート時間」削除に伴う変更 2011.10.31
	#define P_EXECUTE_VOLTAGE_C 25 //P25 2010.02.25 エキスパートモード実験用
	#define P_EXTARNAL_LEVEL_C  26 //P25 2010.02.25 エキスパートモード実験用
	#define P_VOLTAGE_SAMPLING  27 //P26 2010.02.25 エキスパートモード実験用
	#define P_INPUT_PASS_WORD   28 //P27 2010.02.25
	#define P_CHENGE_PASS_WORD  29 //P28 2010.02.25
	#define P_CONTROLLER_LOCK   20 //P29 2010.02.25
	#define P_SUB_MONITOR       31 //P30 2010.02.25
	#define P_ADJUST_ITEM       32 //P31 2010.02.25
#else
	#define P_EXECUTE_VOLTAGE_C 24 //P24 2010.02.25 エキスパートモード実験用
	#define P_EXTARNAL_LEVEL_C  25 //P25 2010.02.25 エキスパートモード実験用
	#define P_VOLTAGE_SAMPLING  26 //P26 2010.02.25 エキスパートモード実験用
	#define P_INPUT_PASS_WORD  27 //P27 2010.02.25
	#define P_CHENGE_PASS_WORD 28 //P28 2010.02.25
	#define P_CONTROLLER_LOCK  29 //P29 2010.02.25
	#define P_SUB_MONITOR      30 //P30 2010.02.25
	#define P_ADJUST_ITEM      31 //P31 2010.02.25
#endif

#if 0 //2010.02.25 番号の変更
#define P_OUTPUT_SELECT     20 //P20 2009.02.16 出力補正有無選択
#define P_EXECUTE_VOLTAGE_A 21 //P21 2009.02.13 エキスパートモード実験用 2009.03.07
#define P_EXECUTE_VOLTAGE_C 22 //P22 2009.02.13 エキスパートモード実験用
//#define P_EXTARNAL_LEVEL_A  22 //P22 2009.02.13 エキスパートモード実験用
#define P_EXTARNAL_LEVEL_C  24 //P24 2009.02.13 エキスパートモード実験用
#define P_VOLTAGE_SAMPLING  25 //P25 2009.02.13 エキスパートモード実験用

#define P_INPUT_PASS_WORD  26 //P26 2009.03.16
#define P_CHENGE_PASS_WORD 27 //P27
#define P_CONTROLLER_LOCK  28 //P28
#define P_SUB_MONITOR      29 //P29
#define P_ADJUST_ITEM      30 //P30
#endif

//--------------------------------------------------------------------
// サービスマン・メニュー番号		BP4 Phase14 by @Tny 2009.02.24	BP4 Phase16 by @Tny 2003.03.10
#define S_PASSWORD			 0 // S00
//#define S_PRI_FLOW_TIME	 1 // S01
#define S_DC_TIG_EN_HOT_I	 1 // S01
#define S_DC_TIG_EN_HOT_T	 2 // S02
#define S_DC_TIG_EN_HOT_ST   3 // S03
#define S_DC_TIG_EP_HOT_I	 4 // S04
#define S_DC_TIG_EP_HOT_T	 5 // S05
#define S_DC_TIG_EP_HOT_ST   6 // S06
#define S_AC_MIX_HOT_I		 7 // S07 2009.04.03
#define S_AC_MIX_HOT_T1		 8 // S08 2009.04.03
#define S_AC_MIX_HOT_T2		 9 // S09 2009.04.03
#define S_AC_MIX_HOT_ST		10 // S10 2009.04.03
#define S_MAX_SPOT_TIME		11 // S11
#define S_LINE_VOLT_OFFSET	12 // S12
#define S_CURRENT_ADJUST	13 // S13
#define S_CT_OFFSET			14 // S14
#define S_VT_OFFSET			15 // S15
#define S_E_L_SHORT_LEVEL	16 // S16
#define S_DISP_ADJUST		17 // S17
#define S_OUTPUT_ADJ_GEIN	18 // S18 2009.04.03
//#define S_AFTER_FLOW_TIME	19 // S19
#define S_ERROR_HIS_CLEAR	19 // S19

//--------------------------------------------------------------------

//--------------------------------------------------------------------
// レスキュー・メニュー番号		BP4 by @Tny 2009.04.8
#define R_PASSWORD			 0 // R00
#define R_ERROR_HIS			 1 // R01
#define R_REC_LOCK			 2 // R02
#define R_RAM_ALL_CLEAR		 3 // R03
#define R_EXT_SW			 4 // R04	2010.01.20 by @Tny
#define R_ARC_ERR_PRE_CHECK  5 // R05 2010.02.25
#define R_AC_WAVE_OUT_MODE	 6 // R06 「交流波形出力モード」追加	2011.11.08
//--------------------------------------------------------------------



//詳細メニュー番号 2008.09.10
#if 0 //2009.03.16 del
#define P_SLOW_DOWN         0 //P00
#define P_HOT_VOLTAGE       1 //P01
#define P_FTT_VOLTAGE       2 //P02
#define P_BURNBACK_TIME     3 //P03
#define P_PENETRATION       4 //P04
#define P_PRE_FLOW_TIME     5 //P05
#define P_AFTER_FLOW_TIME   6 //P06
#define P_PULSE_PEAK_CUR    7 //P07
#define P_PULSE_BASE_CUR    8 //P08
#define P_PULSE_RISE_CUR    9 //P09
#define P_PULSE_FALL_CUR   10 //P10
#define P_FEED_RATE        11 //P11
#define P_PULSE_START_VOLT 12 //P12
#define P_WAVE_CONTROL1    13 //P13
#define P_PULSE_FREQ       14 //P14
#define P_PULSE_WIDTH      15 //P15
#define P_ARC_SPOT_TIME    16 //P16
#define P_LOW_PULSE_SET    17 //P17
#define P_LOW_PULSE_LEVEL  18 //P18
#define P_LOW_PULSE_VOLT   19 //P19
#define P_LOW_PULSE_FREQ   20 //P20
#define P_LOW_PULSE_DUTY   21 //P21
#define P_LOW_PULSE_DELAY  22 //P22
#define P_EN_DUTY          23 //P23
#define P_EN_DUTY_INIT     24 //P24
#define P_EN_DUTY_CRATER   25 //P25
                              //P26
                              //P27
#define P_EP_START_TIME    28 //P28
#define P_EN_CUR           29 //P29
#define P_LOW_PULSE_SLOP   30 //P30
#define P_SPECIAL_SPEC     31 //P31
#define P_CRATER_REPEAT    32 //P32
                              //P33
                              //P34
#define P_BURNBACK2        35 //P35
#define P_INPLSE_START_SW  36 //P36
#define P_WELD_ENDING      37 //P37
#define P_DC_CONTROL_TIME  38 //P38 2008.09.22 交流時直流制御区間
#define P_ARC_SPOT_SET     39 //P39 2008.10.21追加
#define P_CRATER_DC        40 //P40 2008.11.06
                              //P41
                              //P42
                              //P43
                              //P44
                              //P45
                              //P46
                              //P47
                              //P48
                              //P49

#define P_INPUT_PASS_WORD  50 //P50
#define P_CHENGE_PASS_WORD 51 //P51
#define P_CONTROLLER_LOCK  52 //P52
#define P_SUB_MONITOR      53 //P53
#define P_ADJUST_ITEM      54 //P54
#define P_WAVE_CONTROL2    55 //P55
#define P_START_TIME       56 //P56
#define P_HOT_TIME         57 //P57
#define P_CDM              58 //P58
#define P_ELI              59 //P59
#define P_HOT_CUR          60 //P60
#define P_IAC              61 //P61
#define P_INIT_IB          62 //P62
#define P_INIT_IP          63 //P63
#define P_PRISE            64 //P64
#define P_PFALL            65 //P65
#define P_ISC              66 //P66
#define P_SP_I             67 //P67
#define P_SP_T             68 //P68
#define P_TS0              69 //P69
#define P_ENDPLS           70 //P70
#define P_INIT_PFRQ        71 //P71
#define P_NECKLVL          72 //P72
#define P_PCTRLBLOW        73 //P73
#define P_STARTPLS         74 //P74
#define P_WIRACDC          75 //P75
#define P_SA_LEVEL         76 //P76
#define P_AS_LEVEL         77 //P77
#define P_START_CTRL       78 //P78
#define P_START_CTRL_LEVEL 79 //P79
#define P_START_CTRL_VOLT  80 //P80
#define P_START_CTRL_TIME  81 //P81
                              //P82
                              //P83
                              //P84
                              //P85
                              //P86
                              //P87
                              //P88
                              //P89
                              //P90
#endif
#define ROBOT_CONNECT      91 //ロボット接続の表示 2008.10.03


#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	//<><><><><><><><><><> ＩＩＦ関連設定 <><><><><><><><><><>
	//IIF NEW
	//<><><> 各入力の番号 <><><>
	//アナログ入力
	#define IIF_ANALOG_SERECT		11+1  // アナログ入力選択項目数
	#define IIF_ANALOG_NO_USE        0
	#define IIF_ANALOG_PR_CUR        1    //溶接電流指令値
	#define IIF_ANALOG_PR_VLT        2    //溶接電圧指令値
	#define IIF_ANALOG_OK_VLT        3    //一元電圧指令値
	#define IIF_ANALOG_PENET         4    //溶け込み調整
	#define IIF_ANALOG_FD_RT         5    //ワイヤ送給量微調整
	#define IIF_ANALOG_WCTRL1        6    //波形制御１
	#define IIF_ANALOG_WCTRL2        7    //波形制御２
	#define IIF_ANALOG_WIACDC        8    //ワイヤ送給速度調整
	//接点入力	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
	#define IIF_INPUT_NO_USE         0
	#define IIF_INPUT_TSW            1    //トーチＳＷ
	#define IIF_INPUT_GAS_CK         2    //ガスチェック
	#define IIF_INPUT_STKSET         3    //スティックチェック
	#define IIF_INPUT_EM_STP         4    //非常停止
	#define IIF_INPUT_BIN1           5    //再生ｃｈバイナリ１
	#define IIF_INPUT_BIN2           6    //再生ｃｈバイナリ２
	#define IIF_INPUT_BIN3           7    //再生ｃｈバイナリ３
	#define IIF_INPUT_BIN4           8    //再生ｃｈバイナリ４
	#define IIF_INPUT_BIN5           9    //再生ｃｈバイナリ５
	#define IIF_INPUT_BIN6          10    //再生ｃｈバイナリ６
	#define IIF_INPUT_CNT           11    //入力許可信号
	#define IIF_INPUT_STB           12    //ストローブ信号
	#define IIF_INPUT_STOP1         13    //一時停止１
	#define IIF_INPUT_STOP2         14    //一時停止２
	#define IIF_INPUT_WIR_CK        15    //インチング
	#define IIF_INPUT_RETRCT        16    //リトラクト
	#define IIF_INPUT_OKCVON        17    //一元／個別
	#define IIF_INPUT_GP_IN1        18    //汎用入力１
	#define IIF_INPUT_GP_IN2        19    //汎用入力２
	#define IIF_INPUT_GP_IN3        20    //汎用入力３
	#define IIF_INPUT_BIN7          21    //再生ｃｈバイナリ７
	//接点出力
	#define IIF_OUTPUT_NO_USE        0
	#define IIF_OUTPUT_CURDET        1    //電流検出
	#define IIF_OUTPUT_ARCOUT        2    //アーク切れ異常
	#define IIF_OUTPUT_STKOUT        3    //スティック異常
	#define IIF_OUTPUT_ERR           4    //エラー
	#define IIF_OUTPUT_ALM           5    //アラーム
	#define IIF_OUTPUT_WELD          6    //溶接中
	#define IIF_OUTPUT_GAS_ON        7    //ガス動作確認
	#define IIF_OUTPUT_GP_OT1        8    //汎用出力１
	#define IIF_OUTPUT_GP_OT2        9    //汎用出力２
	#define IIF_OUTPUT_GP_OT3       10    //汎用出力３
	//<><><> 最大値、最小値 <><><>
	//最大値
	#define PR_CUR_MAX_VALUE       350    //溶接電流指令値
	#define PR_VLT_MAX_VALUE       500    //溶接電圧指令値
	#define OK_VLT_MAX_VALUE        98    //一元電圧指令値
	//最小値
	#define PR_CUR_MIN_VALUE        15    //溶接電流指令値
	#define PR_VLT_MIN_VALUE        50    //溶接電圧指令値
	#define OK_VLT_MIN_VALUE       -98    //一元電圧指令値
	//<><><>><><><><><><><><><><><><><><><><><><><><><><><><>
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny


//#define P_INIT_CURR_ON     28 //P28
//#define P_REFERENCE_VOLT1  37 //P37
//#define P_REFERENCE_VOLT2  38 //P38




#include        <stdio.h>       // 標準ヘッダファイル（標準入出力処理系）
#include        <stdlib.h>      // 標準ヘッダファイル（標準処理系）
#include        <string.h>      // 標準ヘッダファイル（文字列／メモリ操作系）
#if false
#include        <math.h>        // 算術演算用ヘッダファイル
#include        <float.h>       // 実数値用ヘッダファイル

#endif

typedef unsigned short                       ushort;
typedef unsigned char                        uchar;
typedef unsigned long                        ulong;
typedef unsigned char                        ubool;
typedef volatile unsigned char               *PVUB;
typedef volatile unsigned short int          *PVUW;
typedef	unsigned short int                   usint;   // 符号なし短整数型
typedef	short int                            sint;    // 符号付き短整数型
typedef	long                                 lint;    // 符号付き長整数
typedef	unsigned long                        ulint;   // 符号なし長整数
typedef unsigned char                        *puchar; // 符号なし文字型
typedef short int                            *psint;  // 符号付き短整数型
typedef unsigned short int                   *pusint; // 符号なし短整数型
typedef unsigned int                         *puint;  // 符号なし整数型
typedef long                                 *plint;  // 符号付き長整数
typedef unsigned long                        *pulint; // 符号なし長整数

// メモリスイッチ構造体
//
typedef union{
	uchar	ALL;
	struct{	// １ビットスイッチ
		ubool	b7		:	1;	// MSB
		ubool	b6		:	1;
		ubool	b5		:	1;
		ubool	b4		:	1;
		ubool	b3		:	1;
		ubool	b2		:	1;
		ubool	b1		:	1;
		ubool	b0		:	1;	// LSB
	} Bit1Sw;
	struct{	// ４ビットスイッチ
		uchar	fUpper  :	4;	// MSB 4bit
		uchar	fLower  :	4;	// LSB 4bit
	} Bit4Sw;
} BitSwitch;

typedef union{
	uchar	ALL;
	struct{	// １ビットスイッチ
		ubool	Toch_sw		:	1;	// MSB
		ubool	b6		:	1;
		ubool	Stick_check	:	1;
		ubool	Stick_release	:	1;
		ubool	b3		:	1;
		ubool	b2		:	1;
		ubool	b1		:	1;
		//ubool	b0		:	1;	// LSB
		ubool	Elrod_check		:	1;	// LSB 2009.07.14 STICK命令で代用するので今後使用しない。
	} Bit1Sw;
} WelderCommand; //溶接電源動作指令

typedef union{
	uchar	ALL;
	struct{	// １ビットスイッチ
		ubool	b7		:	1;	// MSB
		ubool	b6		:	1;
		ubool	b5		:	1;
		ubool	b4		:	1;
		ubool	b3		:	1;
		ubool	Motor_conect	:	1;
		ubool	Motor_on	:	1;
		ubool	Gas_on		:	1;	// LSB
	} Bit1Sw;
} WelderCheck;  //溶接電源チェック

typedef union{
	uchar	ALL;
	struct{	// １ビットスイッチ
		ubool	b7		:	1;	// MSB
		ubool	Cd       	:	1;
		ubool	b5		:	1;
		ubool	b4		:	1;
		ubool	b3		:	1;
		ubool	b2              :       1;
		ubool	b1	        :       1;
		ubool	b0		:	1;	// LSB
	} Bit1Sw;
} PowerStatus;  //溶接電源状態

//<><><> 2009.07.13 <><><>
typedef union{
    uchar   ALL;
	struct{	// １ビットスイッチ
		ubool	Pulse_ctrl   :   1;	// MSB
		ubool	Elrod_check  :   1;
		ubool	b5           :   1;
		ubool	b4           :   1;
		ubool	b3           :   1;
		ubool	Ac_recovery  :   1;
		ubool	Ep_start     :   1;
		ubool	Hf_ctrl	     :   1;	// LSB
	} Bit1Sw;
} Control;      //コントロール
//<><><><><><><><><><><><><>


//コントロールワード：gui_Ctrl_word
// 15:シーケンス停止  　14:            13:            12:                 11:                10:             9:           8:スティック＆リリース
//  7:スティック・タッチ 6:ＦＡＮ制御   5:高周波制御   4:溶接電源動作指令  3:インバータ制御   2:モータ制御   1:ガス制御   0:ＭＧ制御
//<><><><><> 2007.3.28 bit変数をunsigned　charに変更<><><><><>
typedef struct{
        ubool    Mg_ctrl_code;
        ubool    Gas_ctrl_code;
        ubool    Motor_ctrl_code;
        ubool    Inverter_ctrl_code;
        ubool    Welder_ctrl_code;
        ubool    Hf_ctrl_code;
        ubool    Fan_ctrl_code;
        ubool    Stick_check_code;
        ubool    Stick_release_code;
        ubool    A10;
        ubool    A11;
        ubool    A12;
        ubool    A13;
        ubool    A14;
        ubool    A15;
        ubool    Sequence_ctrl_code;
}Bit16;

//<><><><><><><><><><> 内部動作の流れを制御するフラグ群 <><><><><><><><><><>
typedef struct{
        ubool    Welder_init_execution;
        ubool    Inching;
        ubool    Inching_end; //2007.3.22
        ubool    Motor_off;
        ubool    Weld_end;
        ubool    Burn_back;
        ubool    Dsp_ready;
        ubool    Arc_err;
        ubool    Emg_err;
        ubool    Gas_err;
        ubool    Water_err;
        ubool    Arc_start_err;
        ubool    Arc_start_err1; //2007.1.19追加 2007.1.26移植追加
        ubool    Arc_start_err2; //2007.1.19追加 2007.1.26移植追加
        ubool    Arc_start_err_set;
        ubool    Temp_err;
        ubool    Temp_err_set; //2009.03.13
        ubool    Second_currnt_err;
        ubool    Second_currnt_err_set;
        ubool    Second_output_err; //2007.1.19追加 2007.1.26移植追加
        ubool    Vp_err;
        ubool    Ts_cancel;
        ubool    Fan_off;
        ubool    Table_data_output;
        ubool    Table_data_output1;
        ubool    Table_data_output_execution; //2007.1.12
        ubool    Stick_start;
        ubool    Stick_end;
        ubool    Stick_on_off_check;
        ubool    Stick_snd_set;
        ubool    Arc;
        ubool    R8_rcv;
        ubool    R8_send;
        ubool    Err_disp_chenge_timing;
        ubool    Ver_disp_chenge_timing;  //2007.2.13追加
        ubool    Pri_curr_fb1_err;
        ubool    Pri_curr_fb1_err_unb;  //2007.3.14 ＰＯ版より移植
        ubool    Pri_curr_fb2_err;
        ubool    R8_com_err;
        ubool    ErrorCode_set;
        ubool    ErrorCode_snd;
        ubool    Slow_down;
        ubool    Initial_arc_start;
        ubool    Pre_flow;
        ubool    Pre_flow_time;
        ubool    After_flow;                //2007.12.11
        ubool    After_flow_time;           //2007.12.11
        ubool    Motor_delay;
        ubool    Motor_delay_end;
        ubool    Motor_current_err;
        ubool    Repeat_weld;//REPEAT 2007.1.12
        ubool    Toch_sw_off_delay_time;//2007.2.24追加
        ubool    Stick_check_delay_time;//2007.2.24追加
        ubool    Pri_volt_err_com_delay;//2007.3.6追加 2007.3.13移植
        ubool    Pri_volt_err_com_delay_set_flag;//2007.3.6追加 2007.3.13移植
        ubool    Emg2_cancel;//2007.3.14 ＰＯ版より移植
        ubool    Motor_off_slop;//2007.3.20
        ubool    Total_weld_time_reset;//2007.3.30
        ubool    Total_weld_count_reset;//2007.4.5
        ubool    Total_wire_feed_reset;//2007.4.5
        ubool    Rs232_start;  //2007.4.2
        ubool    Rs232_init;  //2007.4.2
        ubool    Pri_curr_fb1_start_err; //2007.4.17
        ubool    Pri_curr_fb1_err_04_check; //2007.4.17
        ubool    Second_voltage_err;  //二次過電圧異常 2008.11.17
        ubool    Primary_current_err; //１次過電流異常 2008.11.17

        //<><><>モータエラー関連 2007.8.1<><><>
        ubool    Motor_encoder_err;
        ubool    Motor_lock_err;
        ubool    Motor_circuit_break;
        ubool    Motor_circuit_err;
        ubool    Motor_err;

        //<><><> リモコン関連 <><><><><><><><><>
        ubool    Pre_set; //指令値を調整中であることを知らせる。2008.01.22

        //初期電流＋ローパルス関連
        ubool    Init_current_time;  //2008.02.27
		ubool    Wave_current_time;  //2008.02.27
        ubool    Condition_time_set; //2008.02.27
        ubool    Condition_change;   //2008.02.27
        
        ubool	Weld_end_disp; //2008.03.03
        
        ubool    Srt1;//2008.03.11

        //<><><> シーケンス制御関連 <><><><><><><><>
        ubool    Sequence_crater;//2008.07.29
        ubool    Arc_spot_time;
        ubool    Arc_spot_time_up;
        ubool    Crater_repeat_time;
        ubool    Crater_repeat;
        ubool    After_flow_stop;
        ubool    Start_time; //2008.08.05

        //<><><> 選択関連 2008.08.07 <><><><><><><><>
        ubool    Param_change;
        ubool    Play;
        ubool    Rec;
        ubool    Yes;
        ubool    Rec_display;
        ubool    Del; //2008.09.09
        ubool    Delete; //2008.09.09

        //<><><> 表示制御関連 <><><>
        ubool    Revers_time; //2008.08.19
        ubool    Ch_app;      //2008.08.19
        ubool    Set_screen_on_off; //2008.08.22
        ubool    Robot_connect_time; //2008.10.06

        //<><><> 設定メニュー関連 <><><>
        //***ユーザー***
        //全パラメータリセット関連
        ubool    User_all_parameter_reset;
        ubool    User_all_parameter_reset_exe; //2008.09.04
        //共通
        ubool    Set_key;
        //ＩＩＦ設定関連
        ubool    Out_function_set_ready;
        ubool    In_function_set_ready; //2008.08.25
        ubool    Analog_function_set_ready; //2008.08.25
        //カレンダー関連
        ubool    Calender_set_ready;   //2008.08.25
        ubool    Calender_init;        //2008.10.06 カレンダーの初期化用
        //メモリーコピー関連
        ubool Memory_copy_vector; //2008.08.29

        //一時停止入力時の制御フラグ 2008.09.01
        ubool Err_level1;
        //エラーレベル２時の制御フラグ 2008.11.17
        ubool Err_level2;
        
        //サービスマン関連
        ubool Service_man; //2008.09.02
        ubool Pass_word_err; //2008.09.02
        ubool Service_reset1; //2008.09.02
        ubool Service_reset2; //2008.09.02
        ubool Service_reset1_exe; //2008.09.04
        ubool Service_reset2_exe; //2008.09.04
        ubool Clr_time;       //2008.09.03

        //ガス制御
        ubool Gas_limit_timer;      //2008.09.08

        //外部選択ユニット関連
        ubool Ext_select_cnt;       //2008.09.09
        ubool Ext_select_cnt_bkup;  //2008.09.09
        ubool Ext_select_init;      //2008.09.09
        ubool Ext_select_end;       //2008.09.09

        //詳細メニューパスワード
        ubool Dital_pass_lock;      //2008.09.10


        //交流時直流制御区間制御関連 2008.09.22
        ubool AC_control;
        ubool DC_control_timer;
        ubool Dc_control_timer_end;
        ubool Dc_control_timer_one_shot;


        ubool Lift_up_cd; //2008.10.08

        ubool Slow_start; //2008.10.08 インチングスロースタートフラグ

        ubool Arc_out_err; //2008.10.21 溶接中アーク切れ時の対応

        ubool Crater_pulse_non; //2008.11.06クレータ中パルス有り無しを決定するフラグ


        //突き出し長設定関連 2008.11.10
        ubool Ext_condition_set_ready;

        //起動時のモータディレイ時の加速度 2008.11.17
        ubool Motor_acc1;

        //インパルススタートスイッチ 2008.11.26
        ubool Inplse_start_sw;

        //ＨＰＩ転送行うためのフラグ 2008.11.29
        ubool Hpi_control;

        //バーンバックをＡＣにするかどうかの判定フラグ 2008.12.11
        ubool Burnback_ac;

        //第２バーンバック有り無し選択フラグ 2008.12.11
        ubool Burn_back2;

        //第２バーンバック終了フラグ（第２バーンバック中にスティックチェックをＤＳＰに送るのを防ぐため） 2008.12.11
        ubool Burn_back2_dsp_end;

        //2009.01.28
        ubool Current_set_out1;
        ubool Current_set_out2;


        //***** 高周波関連 2009.01.31 *****
        ubool Hf_2sec_timer;                    //２秒タイマ
        ubool Hf_30sec_timer;                   //３０秒タイマ
        ubool Hf_30sec_interval_timer;          //間欠動作までインターバルタイマ
        ubool Hf_intermittent_on;               //間欠起動タイマ
        ubool Hf_intermittent_off;              //間欠起動タイマ
        ubool Hf_exec;                          //高周波起動フラグ
        ubool Hf_intermittent_set;              //間欠動作許可フラグ

        //***** スロープ関連 2009.02.02 *****
        ubool Up_slop_curr_end;
        ubool Up_slop_time_end;
        ubool Up_slop_time;
        ubool Down_slop_curr_end;
        ubool Down_slop_time_end;
        ubool Down_slop_time;

        //***** クレータリピートＷクリック関連 2009.02.05*****
        ubool W_click_timer;
        ubool Crater_repeat_end;
        ubool W_click_end; //2009.02.25

        ubool Output_correct; //2009.02.16


        //ＭＩＸ関連 2009.02.17
        ubool    Mix_wave_current_time;
        ubool    Mix_condition_time_set;
        ubool    Mix_condition_change;

        ubool    After_flow_check; //2009.02.18

        ubool    Blink_set; //2009.02.19


        //エキスパートモード関連 2009.02.20
        ubool Ref_voltage;
        ubool Ref_voltage_result;
        ubool Cal;
        ubool hugou;
        ubool Ref_voltage_add_start; //2010.01.12

        //クレータ時トーチスイッチ引き上げによって再度トーチを接近した場合の処理フラグ
        ubool Re_crater; //2009.02.25

        //直流手溶接関連 2009.03.06
        ubool Hand_stick_ready_time;
        ubool Hand_stick_start;
        ubool Hand_restart; //2009.03.30
        ubool Hand_restart_wait; //2009.03.30

        //ハード電検 2009.03.07
        ubool Hard_cd;

        //可変反復関連 2009.03.14
        ubool Cr_ts_check;
        ubool Cr_ts_check2;
        ubool Cr_ts_check3; //2009.07.31

        //電極短絡関連 2009.03.16
        ubool Arc_short;

        //出力電流補正選択 2009.03.16
        ubool Disp_adjust;

        //可変反復選択 2009.03.16
        ubool Variable_crater_repaet;

        //アークドライブ関連 2009.03.17
        ubool Arc_drive_mask_time;
        ubool Arc_drive;

        //パルス表示関連 2009.03.23
        ubool Base_avr_result;
        ubool Peak_avr_result;
        ubool Base_read_delay; //2009.03.24
        ubool Peak_read_delay; //2009.03.24

        //リモコン再生関連
        ubool Remo_controller_no; //2009.03.28
        ubool Remo_play_sw;       //2009.03.28
        ubool Remo_play_on;       //2009.03.28
        ubool Remo_play_mode;     //2009.03.30
        ubool No_ch_data;         //2009.03.30
        ubool Remo_play_ch_select;//2009.03.30

        //溶接終了電流表示キャンセル
        ubool End_welding_display_cansel;

        //ＤＳＰパルス信号 2009.04.03
        ubool Dsp_pulse_out;
        
        //スタート処理終了信号 2009.04.03
        ubool Start_process_end;
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
		ubool RemoteController;	// リモコン接続フラグ
//---------------------------------------

        ubool UnConnect_false; //2009.07.14

        ubool Rob_pram_refresh; //2009.07.17

        ubool Method_rcv_flag; //2009.07.17

        ubool Err_gas;         //2009.07.27

        ubool Crater_curr_start; //2009.08.03


        ubool Err_ts_cansel;     //2009.12.18
        ubool Ts_on_err_timer;   //2009.12.18
        ubool Ts_on_err;         //2009.12.18

        ubool Ac_freq_jog;       //2010.01.20

        ubool Variable_crater_re_crater; //可変クレータ反復時、溶接途中（クレータ、ダウンスロープ）でアーク切れを起こした時用のフラグ 2010.02.19

        ubool Detail_display;    //2011.10.03

        ubool Pl_pram_jog;       //2011.10.03

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
        ubool Iif_enable;                  //ＩＩＦが有効かどうかの判定フラグ
        ubool Iif_first_rcv;               //ＩＩＦから最初の受信があったかどうかの判定フラグ
        ubool Iif_set;                     //
        ubool In_ab_set_ready;             //
        ubool Blink_reset;                 //
        ubool Blink_reset1;                //
        ubool Blink_reset_one_shot;        //
        ubool Iif_connect_err;             //
        ubool Calibration_set;             //
        ubool Iif_analog_shift_memory;     //
        ubool One_shot_sw_rewrite_check;   //
        ubool Stb_sw_on;                   //
        ubool Stb_set;                     //
        ubool In_function_no_one_shot;     //
        ubool Iif_output_data_one_shot;    //
        ubool Blink_reset_one_shot_04;     //
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny



        ubool uc_One_shot_voltage;         //2013.02.13		2013_02_13_500BP4より移植　2014.06.11

//-------------------------------------------------------------
// 2019.09.04
	ubool ComSend;						// 送信タイミングフラグ
//-------------------------------------------------------------

	ubool Ms_time;				//2019.07.03
}CtrlFlag;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><> 内部動作の流れを制御するカウンタ群 <><><><><><><><><><>
typedef struct{
        unsigned int Motor_off;
        unsigned int Emg_err;
        unsigned int Gas_err;
        unsigned int Water_err;
        unsigned int Temp_err;
        unsigned int Vp_err;
        unsigned int Extout_counter;
        unsigned long Backup_100m;
        unsigned long Backup_200m; //2007.3.29
        unsigned long Backup_300m; //2009.12.17
        unsigned long Backup_500m;
        unsigned long Backup_50m;  //2009.02.23
        unsigned long Backup_10m;  //2009.03.17 
        unsigned int Table_data_output;
        unsigned int Table_data_output1;
        unsigned int Welder_init_execution; //2007.1.22 intに変更 2007.1.26移植変更
        unsigned char Ts_check;
        unsigned int  Fan_off;
//------ Phase9 by @Tny 2008/09/12 ------
#if true
        unsigned int  Fan_A_off;
#endif
//---------------------------------------------------------------------
        unsigned int  Arc_start_err;
        unsigned int  R8_send;
        unsigned int  Err_disp_chenge_timing;
        unsigned int  Err_disp_chenge;
        unsigned int  Ver_disp_chenge_timing; //2007.2.13追加
        unsigned int  Ver_disp_chenge;        //2007.2.13追加
        unsigned int  Pri_curr_fb1_err;
        unsigned int  Pri_curr_fb1_err_unb; //2007.3.14 ＰＯ版より移植
        unsigned int  Pri_curr_fb2_err;
        unsigned int  R8_com_err;
        unsigned int  Pre_flow_time;
        unsigned int  After_flow_time; //2007.12.11
        unsigned int  Motor_delay;
        unsigned int  Motor_current_err;
        unsigned int  Repeat_weld;//REPEAT 2007.1.12
        unsigned int  Cd_check;   //2007.1.24 2007.1.26移植追加
        unsigned int  Toch_sw_off_delay_time; //2007.2.24 追加
        unsigned int  Stick_check_delay_time; //2007.2.24 追加
        unsigned char Com_err_parity;         //2007.2.26 追加
        unsigned char Com_err_framing;        //2007.2.26 追加
        unsigned char Com_remo_err_parity;    //2007.12.03 追加
        unsigned char Com_remo_err_framing;   //2007.12.03 追加
        unsigned char Pri_volt_err_com_delay; //2007.3.6追加 2007.3.13移植
        unsigned char Total_weld_time;        //2007.3.30
        unsigned int Pri_curr_fb1_start_err; //2007.4.17 2007.7.10 char -> intに変更

        //<><><>モータエラー関連 2007.8.1<><><>
        unsigned int  Motor_encoder_err;
        unsigned int  Motor_lock_err;
        unsigned int  Motor_circuit_break;
        unsigned int  Motor_circuit_err;
        unsigned int  Motor_err;

        //初期電流＋ローパルス関連
        unsigned short Init_current_time; //2008.02.27
        unsigned short Wave_current_time; //2008.02.27

        //unsigned short Frequence_time;    //2008.02.27
        //unsigned short A_condition_time;  //2008.02.27
        //unsigned short B_condition_time;  //2008.02.27
        //unsigned short Frequence_set_time;    //2008.02.27
        //unsigned short A_condition_set_time;  //2008.02.27
        //unsigned short B_condition_set_time;  //2008.02.27
        
        //2009.03.27 unsigned short -> unsigned long
        unsigned long Frequence_time;    //2008.02.27
        unsigned long A_condition_time;  //2008.02.27
        unsigned long B_condition_time;  //2008.02.27
        unsigned long Frequence_set_time;    //2008.02.27
        unsigned long A_condition_set_time;  //2008.02.27
        unsigned long B_condition_set_time;  //2008.02.27
        
        
        unsigned short Avr_result; //2008.03.03
        unsigned short Base_avr_result; //2009.03.23
        unsigned short Peak_avr_result; //2009.03.23
        unsigned short Weld_end_disp;   //2008.03.03
        
        unsigned short Srt1; //2008.03.11


        //<><><>シーケンス制御関連<><><>
        unsigned int   Arc_spot_time; //2008.07.30
        unsigned int   Crater_repeat_time;
        unsigned int   Start_time; //2008.08.05

        //<><><> 表示制御関連 <><><>
        unsigned int   Revers_time; //2008.08.19
        unsigned char  uc_Robot_connect_time; //2008.10.06

        //<><><> 設定メニュー関連 <><><>
        //***ユーザー***
        //特殊パラメータ関連
        unsigned char  uc_User_menu_no;
        unsigned short us_User_parameter_no;
        //ＩＩＦ設定関連
        unsigned char  uc_Iif_no;
        unsigned char  uc_Out_port_no;
        unsigned char  uc_Out_function_no;
        unsigned char  uc_In_port_no;
        unsigned char  uc_In_function_no;
        unsigned char  uc_Analog_port_no;
        unsigned char  uc_Analog_function_no;
        //カレンダー関連
        unsigned char  uc_Calender_no;    //2008.08.25
        unsigned char  uc_Year_set_data;  //2008.08.25
        unsigned char  uc_Month_set_data; //2008.08.25
        unsigned char  uc_Day_set_data;   //2008.08.25
        unsigned char  uc_Hour_set_data;  //2008.08.25
        unsigned char  uc_Mint_set_data;  //2008.08.25
//------ Phase8 by @Tny 2008/09/11 ------
#if true
        //エラー履歴表示関連
        unsigned char  uc_Error_history_no;
        ubool            b_Error_information;
#endif
//---------------------------------------------------------------------
        //メモリコピー関連
        unsigned char Memory_copy_area_no; //2008.08.29

        //サービスマン関連
        unsigned char Pass_word_check; //2008.09.02
        unsigned char Pass_word_ok;    //2008.09.02
        unsigned char  uc_Service_menu_no; //2008.09.02
        unsigned short us_Service_data_no; //2008.09.02
        unsigned char uc_Service_reset_no; //2008.09.02
        unsigned char uc_Clr_time;       //2008.09.03

        //ガス制御
        unsigned short Gas_limit_timer;      //2008.09.08

        //テーブル初期処理（どのようなテーブルが入っているか、選別し並べ替えをする処理に使用する）
        unsigned char uc_Pulse_mode_check;     //テーブル内容抽出のためのカウンタ 2008.09.16


        //交流時直流制御区間制御関連 2008.09.22
         unsigned short us_DC_control_timer;

        //突き出し長設定関連 2008.11.10
        unsigned char  uc_Ext_condition_data;

        unsigned short Second_currnt_err_timer; //2008.12.04

        //ＪＯＧ　Ｖ＿ＭＡＸ発動 2008.12.22
        char sc_Jog1;
        char sc_Jog2;
        unsigned short us_Jog1_timer;
        unsigned short us_Jog2_timer;

        //***** 高周波関連タイマ 2009.01.31 *****
        short Hf_2sec_timer;                    //２秒タイマ
        short Hf_30sec_timer;                   //３０秒タイマ
        short Hf_30sec_interval_timer;          //間欠動作までインターバルタイマ
        short Hf_intermittent_on;               //間欠起動タイマ
        short Hf_intermittent_off;              //間欠起動タイマ
        

        //***** スロープ関連 2009.02.02 *****
        unsigned short Up_slop_time;
        unsigned short Down_slop_time;
        
        //***** クレータリピートＷクリック関連 2009.02.05*****
        unsigned short W_click_timer;


        unsigned short Output_correct; //2009.02.16


        //ＭＩＸ関連 2009.02.17
        //unsigned short Mix_wave_current_time;
        //unsigned short Mix_frequence_time;
        //unsigned short Mix_A_condition_time;
        //unsigned short Mix_B_condition_time;
        //unsigned short Mix_frequence_set_time;
        //unsigned short Mix_A_condition_set_time;
        //unsigned short Mix_B_condition_set_time;

        //2009.03.27 unsigned short -> unsigned long
        unsigned long Mix_wave_current_time;
        unsigned long Mix_frequence_time;
        unsigned long Mix_A_condition_time;
        unsigned long Mix_B_condition_time;
        unsigned long Mix_frequence_set_time;
        unsigned long Mix_A_condition_set_time;
        unsigned long Mix_B_condition_set_time;


        //エキスパートモード関連 2009.02.20
        short Ref_voltage;
        unsigned short Ref_voltage_add_count; //2010.01.12

        unsigned short Hpi;


        //直流手溶接関連 2009.03.06
        short Hand_stick_ready_time;
        short Hand_restart_wait; //2009.03.30

        //電極短絡チェック 2009.03.13
        short Electrode_short_check;

        //可変反復関連 2009.03.14
        short Cr_ts_check;
        short Cr_ts_check2;

        //アークドライブ関連 2009.03.17
        char Arc_drive_mask_time;

        //パルス表示関連 2009.03.24
        char Base_read_delay;
        char Peak_read_delay;
        
        //リモコン再生関連
        short Remo_play_sw; //2009.03.28

        //エラー時ガス処理関連
        short Err_gas;      //2009.07.27

        //トーチＳＷ再起動関連
        short Ts_on_err_timer; //2009.12.18

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
        unsigned char  uc_Iif_ab_set; 			//
        unsigned char  uc_Iif_set;    			//
        short          ss_Blink_reset; 			//
        short          Blink_reset_one_shot_04; //
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny


		unsigned short	us_One_shot_voltage;	//<><><> 電極短絡の回避 2014.06.24 <><><>

	short Ms_time;		//2019.07.03

/*****************************************/
}CtrlCounter;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><><><><><><><> ＥＮ比率関連の変数群 2008.09.22 <><><><><><><><><><>
typedef struct{
    float	f_AC_Frq_ENa1_A;	//周波数定数b算出用EN比率範囲１での定数A
    float	f_AC_Frq_ENa1_B;	//周波数定数b算出用EN比率範囲１での定数B
    float	f_AC_Frq_ENa1_C;	//周波数定数b算出用EN比率範囲１での定数C
    float	f_AC_Frq_ENa2_A;	//周波数定数b算出用EN比率範囲２での定数A
    float	f_AC_Frq_ENa2_B;	//周波数定数b算出用EN比率範囲２での定数B
    float	f_AC_Frq_ENa2_C;	//周波数定数b算出用EN比率範囲２での定数C
    sint	ss_AC_DCstart_Tim_Def;	//ｱｰｸｽﾀｰﾄ直流制御区間微調量ﾃﾞﾌｫﾙﾄ値 (単位：ms)
    sint	ss_AC_DCstart_Tim_Max;	//ｱｰｸｽﾀｰﾄ直流制御区間微調量MAX値 (単位：ms)
    sint    ss_En_def;
    sint    ss_En_a;
    sint    ss_En_a_init;
    sint    ss_En_a_main;
    sint    ss_En_a_crater;
    sint    ss_En_a_wave;     //2008.10.10
    sint    ss_En_a_start;    //2008.10.10
    sint    ss_En_a_qes;      //2008.11.28
    sint    ss_En_a_output;
    sint    ss_En_def_init;   //2008.11.28
    sint    ss_En_def_main;   //2008.11.28
    sint    ss_En_def_crater; //2008.11.28
    sint    ss_En_def_wave;   //2008.11.28
    sint    ss_En_def_start;  //2008.11.28
    signed char sc_Va;
    signed char sc_Va_init;
    signed char sc_Va_main;
    signed char sc_Va_crater;
    signed char sc_Va_wave;   //2008.10.10
    signed char sc_Va_start;  //2008.10.10
    signed char sc_Va_qes;    //2008.11.28
    unsigned char uc_En_inquiry; //2008.10.03 ロボットからのＥＮ比率計算結果問い合わせ変数
    unsigned char uc_Com_en_inquiry; //2008.12.01 ロボットからのＥＮ比率計算結果問い合わせ変数
}En;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><>  詳細のワーク変数群 2008.10.09 <><><><><><><><><><>
typedef struct{
    unsigned short us_Pre_flow_time;    //P05
    unsigned short us_After_flow_time;  //P06
    signed short   ss_Arc_spot_time;    //P16 2008.10.10 2009.03.16 unsigned -> signed
    unsigned short us_Wave_current_time;//P22 2008.10.14
    signed short   ss_En_duty_main_adjustment;//P23 2008.10.14
    signed short   ss_En_duty_init_adjustment;//P23 2008.10.14
    signed short   ss_En_duty_crat_adjustment;//P23 2008.10.14
    signed short   ss_En_duty_qes_adjustment; //2008.11.28
    unsigned short us_Display_time;     //P37 2008.10.14
    unsigned short us_DC_control_timer; //P38 2008.10.14
    unsigned short us_Start_ctrl_timer; //P81 2008.10.16
}DitailWork;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><> FPGA内部のデータ（A/D値）取り込み関連の変数群  <><><><><><><>
typedef struct{
        unsigned short Curr_ad;
        unsigned long  Curr_buff;
        unsigned int   Curr_counter;
        unsigned short Curr_result;
        unsigned short Volt_ad;
        unsigned long  Volt_buff;
        unsigned int   Volt_counter;
        unsigned short Volt_result;
        unsigned int   Short_counter; //短絡回数のカウンター　短絡回数は実際にはＤＳＰから取得するが便宜上ここに配置する 2007.3.2
  
        unsigned long  Curr_buff_unb;    //2007.3.14　ＰＯ版より移植
        unsigned int   Curr_counter_unb; //2007.3.14　ＰＯ版より移植
        unsigned short Curr_result_unb;  //2007.3.14　ＰＯ版より移植
 
        unsigned char  Rpm_counter;      //2007.3.15
        unsigned char  Rpm_avg_counter;  //2007.3.15

        //実効値計算関連
        double Curr_buff_rms; //2009.03.26
        double Volt_buff_rms; //2009.03.26
        double Curr_result_rms; //2009.03.26
        double Volt_result_rms; //2009.03.26
}Fpga;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//<><><><><><><><><><><> テーブルキー変換関連の変数群 <><><><><><><><><><><>
typedef struct{
        unsigned char  Wire_diameter;
        unsigned char  Welding_method;
        unsigned char  Wire_material;
        unsigned char  Wire_ext;
        unsigned char  Pulse_mode;
        unsigned char  Pulse_type;
        unsigned char  Wire_diameter_bkup;
        unsigned char  Welding_method_bkup;
        unsigned char  Wire_material_bkup;
        unsigned char  Wire_ext_bkup;
        unsigned char  Pulse_mode_bkup;
        unsigned char  Pulse_type_bkup;
        unsigned char  Change_flag;
}TableKey;
typedef struct{
        unsigned char  New_calc;
        unsigned char  Request1;
        unsigned char  Send1;
        unsigned char  Request2;
        unsigned char  Send2;
        unsigned char  Okcv[260];      //2009.12.28 500BP4
        unsigned char  Okcv_real[260]; //2009.12.28 500BP4
        char  Okcv_real_p[260];        //2009.12.28 500BP4
        char  Okcv_real_m[260];        //2009.12.28 500BP4
        char  Okcv_real_0[260];        //2009.12.28 500BP4
        char  Okcv_crater_short[260];  //2009.12.28 500BP4
        unsigned short Sb0[1040];      //2009.12.28 500BP4
        signed   int   Okcv_ref;
}Okcv;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//<><><><><><><><><><><><><> Ｒ８通信関連の変数群 <><><><><><><><><><><><><>
typedef union{ //Ｒ８からの受信分
	uchar	ALL[6];
	struct{
           struct{
                  ubool    b5                     :  1;
                  ubool    non2                   :  1;
                  ubool    b4                     :  1;
                  ubool    b3                     :  1;
                  ubool    b2                     :  1;
                  ubool    non1                   :  1;
                  ubool    b1                     :  1;
                  ubool    b0                     :  1;
           } Sp_data;                  //６ｂｉｔスイッチ
           uchar Ex_data;              //外部選択ユニット
           unsigned short Pri_curr_fb1;//一次電流ＦＢ値１
           unsigned short Pri_curr_fb2;//一次電流ＦＢ値２
	}Data;
} RcvPacket;  
typedef struct{ //Ｍ３２内部使用分
           struct{
                  ubool    b5                     :  1;
                  ubool    non2                   :  1;
                  ubool    b4                     :  1;
                  ubool    b3                     :  1;
                  ubool    b2                     :  1;
                  ubool    non1                   :  1;
                  ubool    b1                     :  1;
                  ubool    b0                     :  1;
           } Sp_data;
        uchar Ex_data;
        unsigned short Pri_curr_fb1;
        unsigned short Pri_curr_fb2;
        unsigned long  Pri_curr_fb1_work;
        unsigned long  Pri_curr_fb2_work;
        unsigned short Sum_counter;
                  ubool Com_check                 :  1;
} InputR8;
typedef struct{ //Ｒ８との通信に使用する変数
        unsigned char   Rx_buffer[10];
        unsigned char   Rx_write_position;
        unsigned short  Work;

} R8Com;


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//<><><><><><><><><><><><><> 外部入力関連の変数群 <><><><><><><><><><><><><>
typedef struct{
        unsigned char Data[ARRAY_WIDTH];
        unsigned char Data_bkup[ARRAY_WIDTH];
        unsigned char Counter[ARRAY_WIDTH];
        unsigned char Flag[ARRAY_WIDTH];
} ExtInput;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><><><><><><><><><><> ＤＳＷ関連の変数群 <><><><><><><><><><><><><>
typedef union{ //ＤＳＷの内容
	unsigned short ALL;
	struct{
              ubool    No15                   :  1;
              ubool    No14                   :  1;
              ubool    No13                   :  1;
              ubool    No12                   :  1;
              ubool    No11                   :  1;
              ubool    No10                   :  1;
              ubool    No9                    :  1;
              ubool    No8                    :  1;
              ubool    No7                    :  1;
              ubool    No6                    :  1;
              ubool    No5                    :  1;
              ubool    No4                    :  1;
              ubool    No3                    :  1;
              ubool    No2                    :  1;
              ubool    No1                    :  1;
              ubool    No0                    :  1;
	}Sw;
} Dsw;  
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><> ＡＤ４（一次入力電圧）関連の変数群 <><><><><><><><><>
typedef struct{
        unsigned int Result;
        unsigned int Buffer;
        unsigned short Counter;
} Vp;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><> ＡＤ０（モータ電流）関連の変数群 <><><><><><><><><>
typedef struct{
        //unsigned int Result;
        //unsigned int Buffer;
        int Result;     //2007.1.15 signed に変更 2007.1.17移植
        int Buffer;     //2007.1.15 signed に変更 2007.1.17移植
        unsigned short Counter;
      
        int Center_result;  //2007.3.20
        int Center_buffer;  //2007.3.20
        unsigned short Center_counter; //2007.3.20
} Mc;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><><><><><><> 溶接条件テーブルコード関連の変数群 <><><><><><><><><>
typedef struct{
        unsigned char Material;          //材質
        unsigned char Method;           //溶接法
        unsigned char Pulse_mode;        //溶接種別フラグ（短絡／パルス）
        unsigned char Pulse_type;        //パルスタイプ
        unsigned char Wire;              //ワイヤ径
        unsigned char Extension;         //突き出し長
        unsigned char Reserved1;         //予約
        unsigned char Reserved2;         //予約
} Table_Code;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><> リモコン選択用溶接条件テーブルコード関連の変数群 <><><><><><>
typedef struct{
        unsigned char Material[REMO_TBLCNT];         //材質
        unsigned char Method[REMO_TBLCNT];           //溶接法
        unsigned char Pulse_mode[REMO_TBLCNT];       //溶接種別フラグ（短絡／パルス）
        unsigned char Pulse_type[REMO_TBLCNT];       //パルスタイプ
        unsigned char Wire[REMO_TBLCNT];             //ワイヤ径
        unsigned char Extension[REMO_TBLCNT];        //突き出し長
        unsigned char Reserved1[REMO_TBLCNT];        //予約
        unsigned char Reserved2[REMO_TBLCNT];        //予約

        //*** 2008.07.18追加 ***
        unsigned char Control1_mode[REMO_TBLCNT];    //制御１
        unsigned char Control2_mode[REMO_TBLCNT];    //制御２
        unsigned char Control3_mode[REMO_TBLCNT];    //制御３

} REMO_Table_Code;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><> 特殊条件テーブルコード関連の変数群 <><><><><><><><><>
typedef struct{
        unsigned char Kind;              //01:材質 02:溶接法
        unsigned char Code;              //コード
        unsigned char Name[16];          //コメント
} Sp_Table_Code;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><> 半固定、可変データ書き換え関連の変数群 <><><><><><><><><>
typedef struct{
        //半固定データ
        //unsigned char  Hfix_no;           //半固定データ番号
        unsigned short Hfix_no;           //半固定データ番号 2007.4.16変更
        unsigned short Hfix_data;         //データ
        //可変データ
        unsigned char  Val_no0;            //可変データ番号
        unsigned int   Val_a_data0;        //ａデータ
        unsigned int   Val_b_data0;        //ｂデータ
        unsigned int   Val_c_data0;        //ｃデータ
        unsigned int   Val_min_data0;      //ｍｉｎデータ
        unsigned int   Val_max_data0;      //ｍａｘデータ
        unsigned char  Val_no1;            //可変データ番号
        unsigned int   Val_a_data1;        //ａデータ
        unsigned int   Val_b_data1;        //ｂデータ
        unsigned int   Val_c_data1;        //ｃデータ
        unsigned int   Val_min_data1;      //ｍｉｎデータ
        unsigned int   Val_max_data1;      //ｍａｘデータ
        unsigned char  Bank;               //バンク切り替えフラグ

} Com_Data;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><>リモコン用　各種設定＋電圧表示＋波形制御　2008.02.25<><><><><><>
typedef struct{
        unsigned char Select_counter;
        struct {
                //各種設定関連
                signed char Parameter_set_counter;
                unsigned char Parameter_set_flag;
                signed short Parameter_set[20];
                //電圧表示関連
                unsigned char Voltage_display_flag;
                //波形制御関連
                unsigned char Wave_control_flag;
        }Item;
} Parameter;
//


typedef struct{
        //ユーザーパラメータ
        signed short ss_User_param[USER_PARAMETER_NO];
        //サービスマンデータ
        signed short ss_Service_data[SERVICE_DATA_NO];
//--------------------------------------------------------------------
//BP4 Phase14 by @Tny 2009.02.24
        signed short ss_Rescue_data[RESCUE_DATA_NO];
//--------------------------------------------------------------------
} Special_menu;

typedef struct{
        unsigned char  uc_Year_data;  //2008.08.25
        unsigned char  uc_Month_data; //2008.08.25
        unsigned char  uc_Day_data;   //2008.08.25
        unsigned char  uc_Hour_data;  //2008.08.25
        unsigned char  uc_Mint_data;  //2008.08.25
        unsigned char  uc_Sec_data;   //2008.08.25
        unsigned char  Leap_year;  //閏年 2008.08.25
        unsigned char  Leap_month; //閏月 2008.08.25
} Calender;

//Ｐメニューの属性
typedef struct{
        short ss_Max;
        short ss_Min;
        short ss_Notch;
        unsigned char uc_Point;
        short ss_Init;
} Dital_attribute;


typedef struct{
        unsigned char uc_Key_counter;
        signed char sc_Jog_counter;		// 2019.06.10	+signed
        unsigned char uc_Material_address;
        unsigned char uc_Material_set;
        unsigned char uc_Thickness_address;
        unsigned char uc_Thickness_set;
        unsigned char uc_Thickness_search;
        unsigned char uc_Joint_address;
        unsigned char uc_Joint_set;
        unsigned char uc_Joint_search;
        unsigned char uc_Direction_address;
        unsigned char uc_Direction_set;
        unsigned char uc_Direction_search;
        unsigned char uc_Pulse_address;
        unsigned char uc_Pulse_set;
        unsigned char uc_Pulse_search;

        unsigned char uc_Cansel;

        unsigned char uc_Jog_set_key; //2009.01.16
      
        unsigned char uc_Navi_limit;  //2010.01.21
//-----------------------------------------------------------------------------------------------------------------------------------------------
// <NAVI Enhancements(Phase 1)> 2011.10.26 by @Tny
		unsigned short	us_Gas_Navi;			// ガス流量
		unsigned short	us_Filler_navi;			// フィラー径
		unsigned short	us_Electroad_navi;		// 電極径
		unsigned short	us_El_rd_angle_navi;	// 電極先端角度
		ubool			b_Navi_Disp;			// ナビ表示フラグ
//-----------------------------------------------------------------------------------------------------------------------------------------------

} NAVI;


//<><><><><><><><><><><><><><><><><><><><><><><> 内部使用関連の変数群 <><><><><><><><><><><><><><><><><><><><><><><>
struct gtt_Internal_pack{
       struct{
                ubool            bRS422Connection;          // ＲＳ４２２側回線接続状態
                ubool            bRS232Connection;          // ＲＳ２３２ｃ側回線接続状態
          struct{
                ubool            bChangeData;               // 受信データ更新フラグ
                uchar           iRecvCommand;              // 受信コマンド（データ更新判別用）
                sint            usWeldingCurr;             // 出力電流指令値
                sint            usWeldingCurr_bkup;        // 出力電流指令値のバックアップ 2008.10.20追加
                sint            usWeldingVolt;             // 出力電圧指令値
                sint            usWeldingInitCurr;         // 初期出力電流指令値 2008.02.22
                sint            usWeldingInitVolt;         // 初期出力電圧指令値 2008.02.22
                sint            usWeldingCratCurr;         // クレータ出力電流指令値 2008.02.22
                sint            usWeldingCratVolt;         // クレータ出力電圧指令値 2008.02.22
                sint            usWeldingWaveCurr;         // 波形制御　Ｂ条件　出力電流指令値 2008.02.26
                sint            usWeldingWaveVolt;         // 波形制御　Ｂ条件　出力電圧指令値 2008.02.26
                sint            usWeldingStartCurr;        // 波形制御　スタート条件　出力電流指令値 2008.08.05
                sint            usWeldingStartVolt;        // 波形制御　スタート条件　出力電圧指令値 2008.08.05
                BitSwitch       fWireDiameter;             // ワイヤ径
                BitSwitch       fWelding;                  // 溶接法
                BitSwitch       fWireMaterial;             // ワイヤ材質
                BitSwitch       fWireSelect;               // ワイヤ種
                BitSwitch       fInitialSelect1;           // 初期データ設定１
                float            vTsoAdj;                   // 短絡初期時間調整
                float            vIscAdj;                   // 短絡電流屈折値調整
                float            vIsl1Adj;                  // 短絡電流勾配１調整
                float            vIsl2Adj;                  // 短絡電流勾配２調整
                char             vTspAdj;                   // 突っ掛かり防止時間調整
                float            vIacAdj;                   // アーク電流屈折値調整 2009.07.10 char->float
                short            vIhotAdj;                  // ホット電流調整
                float            vVhotAdj;                  // ホット電圧調整 2007.2.5変更
                short            vSldnAdj;                  // ワイヤスローダウン調整
                short            vFttAdj;                   // ＦＴＴレベル調整
                short            vBarnBackAdj;              // バーンバック時間調整
                WelderCommand   fWelderCommand;            // 溶接電源動作指令
                WelderCheck     fWelderCheck;              // 溶接電源チェック
                Control         fControl;                  // コントロール（ロボット通信で使用）2009.07.13
#if 0 //2009.03.18 unsigned -> signed
                ushort          usIP;                      // パルスピーク指令電流
                ushort          usIB;                      // パルスベース指令電流
                ushort          usPulseFreq;               // パルス指令周波数
                ushort          usPulseDuty;               // パルス指令幅
                ushort          usAcFreq;                  // 交流周波数
                uchar           ucCleaningDuty;            // クリーニング幅
                uchar           ucMixFreq;                 // MIX TIG周波数
                uchar           ucMixAcRatio;              // MIX(AC)比率
#endif
                short          usIP;                      // パルスピーク指令電流
                short          usIB;                      // パルスベース指令電流
                short          usPulseFreq;               // パルス指令周波数
                short          usPulseDuty;               // パルス指令幅
                short          usAcFreq;                  // 交流周波数
                char           ucCleaningDuty;            // クリーニング幅
                //char           ucMixFreq;                 // MIX TIG周波数
                short          ucMixFreq;                 // MIX TIG周波数 2009.03.31
                char           ucMixAcRatio;              // MIX(AC)比率

                //BitSwitch       fControl;                  // コントロール 2009.07.13 del
                short           ucImprudenceVolt;          // 電極短絡電圧指令値 2009.07.15 uchar->short
                BitSwitch       fPulseMode;                // パルスモード設定
                //char            vHotTime;                  // ホットタイム 2007.2.5変更
                short           vHotTime;                  // ホットタイム
                short           vIniIpAdj;                 // スタートピーク電流微調整   2009.06.26 char->short
                short           vIniIbAdj;                 // スタートベース電流微調整   2009.06.26 char->short
                float           vIpAdj;                    // パルスピーク電流微調整     2009.06.25 char->float
                float           vIb1Adj;                   // パルス第１ベース電流微調整 2009.06.25 char->float
                float           vIb2Adj;                   // パルス第２ベース電流微調整 2009.06.30 char->float
                float           vIprAdj;                   // パルスピーク立ち上がり微調整 2009.06.25 char->float
                float           vIpfAdj;                   // パルスピーク立ち下がり微調整 2009.06.25 char->float
                float           vTiprAdj;                  // パルス立ち上がり時間微調整         2009.06.25 char->float
                float           vTipAdj;                   // パルスピーク立ち上がり時間微調整   2009.06.25 char->float
                float           vTipfAdj;                  // パルス立ち下がり時間微調整         2009.06.25 char->float
                char            vPulseFreqAdj;             // パルス周波数微調整
                short           vStartPulse;               // スタートパルス有り無し     2009.06.26 追加
                short           vEndPulse;                 // エンドパルス有り無し       2009.06.26 追加
                short           vIniPulseFreqAdj;          // イニシャルパルス周波数     2009.06.26 追加
                short           vPctrlBlowAdj;             // アークブロー抑制制御       2009.06.26 追加
                short           vWirSpdAdj;                // ワイヤスピード微調整       2009.06.26 追加
                float           vWirStrAccAdj;             // スタートスロープ微調整     2009.06.26 追加 2009.06.30 short->float
                float           vWirStrDelayAdj;           // ワイヤスタートディレイ微調整     2009.06.26 追加 2009.06.30 short->float
                short           vNeckLvlAdj;               // ネックレベル微調整         2009.06.26 追加
                float           vWirAcDcAdj;               // 加速度３                   2009.06.26 追加 2009.06.30 short->float
                short           vBbkPulseAdj;           // バーンバックパルス         2009.06.29 追加
                char            vLowPulseAB_LevelGap;      // 簡易ローパルス：Ａ条件Ｂ条件レベル差
                char            vLowPulseAB_TimeRatio;     // 簡易ローパルス：Ａ条件Ｂ条件時間比率
                char            vLowPulseFreq;             // 簡易ローパルス：周波数
                char            vLowPulseStartTimeAdj;     // 簡易ローパルス開始時間微調整
                char            vPulseStartSlope;          // パルススタートスロープ
                char            vPulseExecSlope;           // パルス指令値切り替えスロープ
                char            vPulsePerformance;         // パルス応答性
                BitSwitch       fLotCheck;                 // 製品検査用
                char            vAfterFlowAddTime;         // アフターフロー時間加算値
                ushort          vCheck;                    // バックアップメモリ確認用エリア
                ubool            Emergency;                 //非常停止入力                  （外部入力のみ）
                ubool            Emergency2;                //非常停止２入力                （外部入力のみ）2007.2.9
                ubool            Outside1;                  //一時停止１（ガス減圧異常）入力（外部入力のみ）
                ubool            Outside2;                  //一時停止２（水回路異常）入力　（外部入力のみ）
                ubool            Temp;                      //サーマル　　　　　　　　　　　（外部入力のみ）
                char            vTableChange;              //テーブル切り替えコマンド 2007.2.9
                sint            usWeldingCurr_bk_up;       // 出力電流指令値 2007.2.19 インチング速度変更用バックアップ
                sint            usWeldingVolt_bk_up;       // 出力電圧指令値 2007.2.19 インチング速度変更用バックアップ
                sint            usWeldingCurr_pc_bk_up;    // 出力電流指令値 2007.4.6 ＳＧ１用バックアップ
                sint            usWeldingVolt_pc_bk_up;    // 出力電圧指令値 2007.4.6 ＳＧ１用バックアップ

                short           sPreFlowTime;              // プリフロー時間       2009.01.13
                short           sAfterFlowTime;            // アフターフロー時間   2009.01.13
                short           sUpSlopTime;               // アップスロープ時間   2009.01.13
                short           sDownSlopTime;             // ダウンスロープ時間   2009.01.13
                
                //<><><> TIG系調整パラメータ変数 2009.07.10 <><><>
                short           vIhotAdj_tig;              // ホット電流調整（ＴＩＧ系）
                short           vHotTime_tig;              // ホット時間調整（ＴＩＧ系）
                short           vHotSlop_tig;              // ホットスロープ（ＴＩＧ系）
                //<><><><><><><><><><><><><><><><><><><><><><><><>

                //<><><> 拡張溶接微調パラメータ変数 2007.5.29 <><><>
                unsigned short  Id_no;                     //ＩＤ番号
                float           Sp_current;                //ＳＰ電流
                float           Sp_time;                   //ＳＰ時間
                float           Eli;                       //ＥＬＩ
                float           Mts_v;                     //重畳電圧値
                float           Mts_ontime;                //重畳電圧ＯＮ時間
                float           Mts_cycle;                 //重畳電圧周期
                //<><><><><><><><><><><><><><><><><><><><><><><><><>

                sint            ss_En_duty_adjustment;     //ロボットから送られてきたＥＮ調整量 2008.10.03
	        unsigned short us_Q_WeldingCurr;        //2008.11.28
                short          ss_Q_en_duty_adjustment; //2008.11.28
                unsigned char  uc_Q_En_0_mode;          //2008.11.28
                unsigned char  uc_En_0_mode;            //2008.11.28

          } In;
          struct{
                uchar           ucModelCode;               // 機種別コード
                uchar           sRomVersion[2];            // ROMバージョン
                uchar           ucPassword;                // パスワード変換後データ
                ushort          usWeldingCurr;             // 出力電流指令値
                ushort          usWeldingVolt;             // 出力電圧指令値
                ushort          usWeldingOutCurr;          // 出力電流値
                ushort          usWeldingOutVolt;          // 出力電圧値
                uchar		ucImprudence;              // 短絡回数
                uchar           ucMotorCurr;               // モータ電流値
                uchar           ucMotorRPM;                // モータ回転数
                uchar           ucMotorCurr2;              // モータ電流値２
                ushort          usMotorRPM2;               // モータ回転数２
                BitSwitch       fErrorCode1;               // 異常検出状態（溶接・送給系）
                BitSwitch       fErrorCode2;               // 異常検出状態（電源系）
                BitSwitch       fErrorCode3;               // 異常検出状態（異常・停止信号検出系）
                PowerStatus     fPowerStatus;              // 溶接電源状態
                ushort          usIP;                      // パルスピーク電流
                ushort          usIB;                      // パルスベース電流
                ushort          usPulseFreq;               // パルス周波数
                BitSwitch       fArcStartStatus;           // アークスタート状態

                uchar       uc_En_a;                //ＥＮ比率計算結果     2008.10.03
                ushort      us_En_Okcv;             //ＥＮ比率計算後一元化 2008.10.03

                struct{
                      ushort          usWeldTimes;            // 溶接回数
                      ushort          usWeldTimerIndividual;  // 溶接時間(個別)
                      unsigned int    usWeldTimer;           // 溶接時間 2007.3.30
                      ulong           usWireFeed;             // ワイヤ総送給量
                      ushort          vCheck;                 // バックアップメモリ確認用エリア
                }BackUp;
          } Out;

        } Data;
};

//----- Phase6 by @Tny 2008/09/10 -----
#if true
#define MAX_ERROR_INFOMATION    99      // 記録情報量：９９件
#define ERROR_INFO_RENEWAL      0x55aa  // 記録識別子
#define IIF_BUILT_IN_RENEWAL    0x55aa  // 記録識別子
struct gtt_Error_History{   // エラー履歴テーブルの構造体
    unsigned char   vStart;             // 開始エリア
    unsigned short  Record_identifier;  // 記録識別子
    ubool            Start_record;       // 記録開始フラグ
    unsigned short  History_rec_index;  // 記録インデックス
    ubool            Full_history_rec;   // 全記録エリア使用フラグ
    struct{
        unsigned short  Error_No;           // エラー番号
        unsigned char   Year;               // 発生日時（年）
        unsigned char   Month;              // 発生日時（月）
        unsigned char   Day;                // 発生日時（日）
        unsigned char   Hour;               // 発生日時（時）
        unsigned char   Minute;             // 発生日時（分）
        unsigned char   Second;             // 発生日時（秒）
    } Info[MAX_ERROR_INFOMATION];       // 記録情報
    unsigned char   vEnd;               // 終了アリア
};
#endif
//--------------------------------------------

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>




#ifdef __MAIN_PROG
        uchar          IdentificationCode;      // 機種番号
	    extern void Hardware_Initialize(void);  // システム初期化メイン外部参照宣言
        //extern void WeldAdjOut_Proc( int ); //ihara 2005.12.27

//        const unsigned char   guc_Attribute_dps_no[3]         = "188";  //DPS番号 2007.6.28追加
//        const unsigned char   guc_Attribute_dps_no[3]         = "288";  //DPS番号 2008.4.1 YD-350AZR本番機 & YD-350GBR本番機、予備機
//        const unsigned char   guc_Attribute_dps_no[3]         = "388";  //DPS番号 2008.4.1 YD-350AZR予備機
//        const unsigned char   guc_Attribute_dps_no[3]         = "052";  //DPS番号 2009.12.28 500BP4 2010.03.25 復帰
          const unsigned char   guc_Attribute_dps_no[3]         = "048";  //DPS番号 2011.09.28 300BP4
//        const unsigned char   guc_Attribute_dps_no[3]         = "C33";  //DPS番号 500BP4田中テスト　2010.03.23
//2010.02.10        const unsigned char   guc_Attribute_dps_no[3]         = "052";  //2010.02.06 製品審査用
//        const unsigned char   guc_Attribute_version[3]        = "F28";  //ROMver　（３文字）;//2009.12.28 500BP4 2010.03.24 試験版F28
//        const unsigned char   guc_Attribute_version[3]        = "103";  //ROMver　（３文字）;//2010.03.25 復帰 2010.04.08 Ver101 2010.11.02 Ver102	 2011.09.01 Ver103
//        const unsigned char   guc_Attribute_version[3]        = "E07";  //ROMver　（３文字）;//2011.10.04 試験版E07
//        const unsigned char   guc_Attribute_version[3]        = "F02";  //ROMver　（３文字）;//2011.10.07 試験版F02	EXTERNAL IIF NEW
//        const unsigned char   guc_Attribute_version[3]        = "F03";  //ROMver　（３文字）;//2011.10.12 試験版F03	<EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
//        const unsigned char   guc_Attribute_version[3]        = "F04";  //ROMver　（３文字）;//2011.10.13 試験版F04	<EXTERNAL IIF NEW(Phase 4)>	2011.10.13 by @Tny
//        const unsigned char   guc_Attribute_version[3]        = "F05";  //ROMver　（３文字）;//2011.10.26 試験版F05	<EXTERNAL IIF NEW(Phase 5)><NAVI Enhancements(Phase 1)>	2011.10.26	/	<NAVI Enhancements(Phase 2)> 2011.10.27
//        const unsigned char   guc_Attribute_version[3]        = "F06";  //ROMver　（３文字）;//2011.10.26 試験版F06	<EXTERNAL IIF NEW(Phase 5)><NAVI Enhancements(Phase 1)>	2011.10.26	/	<NAVI Enhancements(Phase 2)> 2011.10.27 / 「微弱モード」の追加	2011.10.28
//        const unsigned char   guc_Attribute_version[3]        = "F07";  //ROMver　（３文字）;//2011.10.31 試験版F07	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
//        const unsigned char   guc_Attribute_version[3]        = "F08";  //ROMver　（３文字）;//2011.10.31 試験版F08	FPGA変更
//        const unsigned char   guc_Attribute_version[3]        = "F09";  //ROMver　（３文字）;//2011.10.31 試験版F09	ロボット通信不具合対応 2011.10.31
//        const unsigned char   guc_Attribute_version[3]        = "F10";  //ROMver　（３文字）;//2011.11.07 試験版F10	ロボット通信不具合対応
//        const unsigned char   guc_Attribute_version[3]        = "F11";  //ROMver　（３文字）;//2011.11.07 試験版F11	サービスマンメニューに「交流波形出力モード」を追加	2011.11.08
//        const unsigned char   guc_Attribute_version[3]        = "F12";  //ROMver　（３文字）;//2011.11.07 試験版F12	マイルドパルス変更（DSP）
//        const unsigned char   guc_Attribute_version[3]        = "F14";  //ROMver　（３文字）;//2011.11.14 試験版F14	DSPパルス切替周波数変更。
//		  const unsigned char   guc_Attribute_version[3]        = "F15";  //ROMver　（３文字）;//2011.11.16 試験版F15	Err05表示＆記憶遅延時間変更
//        const unsigned char   guc_Attribute_version[3]        = "F16";  //ROMver　（３文字）;//2011.11.18 試験版F16	<EXTERNAL IIF NEW(Phase 12)> 2011.11.18
//        const unsigned char   guc_Attribute_version[3]        = "200";  //ROMver　（３文字）;//2011.11.22 Ver2.00 FIX UP
//        const unsigned char   guc_Attribute_version[3]        = "2F2";  //ROMver　（３文字）;//2011.12.08
//        const unsigned char   guc_Attribute_version[3]        = "200";  //ROMver　（３文字）;//2011.12.08 Ver2.00 FIX UP
//        const unsigned char   guc_Attribute_version[3]        = "201";  //ROMver　（３文字）;//2012.02.08 Ver2.01 FIX UP
//          const unsigned char   guc_Attribute_version[3]        = "202";  //ROMver　（３文字）;//2012.05.23 Ver2.02
          const unsigned char   guc_Attribute_version[3]        = "203";  //ROMver　（３文字）;//2014.06.11 Ver2.03
        //<><> BP4に変更 2009.07.10 <><><>
        const unsigned char   guc_Attribute_kind_code         = 'C';    //種別（Ｄ：ＭＡＧ　Ｃ：ＴＩＧ　１文字）
//      const unsigned char   guc_Attribute_capacity_code[3]  = "500";  //定格出力　（３文字）2009.12.28 500BP4
        const unsigned char   guc_Attribute_capacity_code[3]  = "300";  //定格出力　（３文字）//2011.09.28 300BP4
        const unsigned char   guc_Attribute_model_code[3]     = "BP4";  //機種（３文字）
        const unsigned char   guc_Attribute_special_code[3]   = "   ";  //特殊品（３文字）：標準品はスペース３個
        //<><><><><><><><><><><><><><><><>
        //const unsigned char   guc_Attribute_kind_code         = 'D';    //種別（Ｄ：ＭＡＧ　Ｃ：ＴＩＧ　１文字）
        //const unsigned char   guc_Attribute_capacity_code[3]  = "350";  //定格出力　（３文字）
        //const unsigned char   guc_Attribute_model_code[3]     = "AZ3";  //機種（３文字）
        //const unsigned char   guc_Attribute_special_code[3]   = "   ";  //特殊品（３文字）：標準品はスペース３個

        BitSwitch	*p6;
        BitSwitch	*p9;
        BitSwitch	*p10;
        BitSwitch	*p11;
        BitSwitch	*p13;
        BitSwitch	*p22;

        Bit16           gtt_Ctrl_word;
        Bit16           gtt_Ctrl_word_bkup;
        CtrlFlag        gtt_Ctrl_flag;
        CtrlCounter     gtt_Ctrl_counter;
        Fpga            gtt_Fpga;
        TableKey        gtt_Table_key;
        Okcv            gtt_Okcv;
        RcvPacket       gtt_rcv_r8;
        InputR8         gtt_internal_r8;
        ExtInput        gtt_Ext_input;
        R8Com           gtt_R8_com;
        Dsw             gtt_Dsw;
        Vp              gtt_Vp;
        Mc              gtt_Motor_current;

        Table_Code      gtt_Table_code[TBLCNT];
        REMO_Table_Code gtt_Remo_table_code; //2007.12.05
        REMO_Table_Code gtt_Remo_table_code_work; //2007.12.05
        Sp_Table_Code   gtt_Sp_table_code[WELDNAME_TBLCNT];
        Com_Data        gtt_Com_rewrite_data;
        Com_Data        gtt_Internal_rewrite_data;
        Parameter       gtt_Parameter; //2008.08.06復帰
        Special_menu    gtt_Special_menu; //2008.08.22
        
        Calender        gtt_Calender;      //2008.08.25
        Dital_attribute gtt_Dital_attribute[SELECT_DITAL_MAX+1]; //2008.08.27   // Phase11 by @Tny 2008/09/16
        unsigned char   guc_Write_check_flag[CH]; //2008.09.09
   
        En              gtt_En; //2008.09.22
        DitailWork      gtt_Ditail_work; //2008.10.09
        NAVI            gtt_Navi; //2009.01.15

//---------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23
        Dital_attribute gtt_Service_attribute[SERVICE_DATA_NO];
//---------------------------------------------------
//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
        Dital_attribute gtt_Rescue_attribute[RESCUE_DATA_NO];
//---------------------------------------------------
	    struct          gtt_Internal_pack	gtt_Internal_pack;// 内部用データ・パッケージ

#else
        extern const char       DPS[];                     // ソフトウェア管理番号
        extern const char       Version[];                 // バージョン番号
        extern const long       DataTime;                  // 最終更新日
        extern const long       BuildRelease;              // ビルド番号
        //extern const uchar      IdentificationCode;        // 機種番号
        extern uchar      IdentificationCode;        // 機種番号

        extern const unsigned char   guc_Attribute_dps_no[];         //DPS番号 2007.6.28追加
        extern const unsigned char   guc_Attribute_version[];        //ROMver　（３文字）;
        extern const unsigned char   guc_Attribute_kind_code;        //種別（Ｄ：ＭＡＧ　Ｃ：ＴＩＧ　１文字）
        extern const unsigned char   guc_Attribute_capacity_code[];  //定格出力　（３文字）
        extern const unsigned char   guc_Attribute_model_code[];     //機種（３文字）
        extern const unsigned char   guc_Attribute_special_code[];   //特殊品（３文字）：標準品はスペース３個


        extern void xmemset(void *dst, int dat, size_t lgh);
        extern void xmemcpy(void *dst, const void *soc, size_t lgh);
        extern BitSwitch	*p6;
        extern BitSwitch	*p9;
        extern BitSwitch	*p10;
        extern BitSwitch	*p11;
        extern BitSwitch	*p13;
        extern BitSwitch	*p22;

        extern Bit16           gtt_Ctrl_word;
        extern Bit16           gtt_Ctrl_word_bkup;
        extern CtrlFlag        gtt_Ctrl_flag;
        extern CtrlCounter     gtt_Ctrl_counter;
        extern Fpga            gtt_Fpga;
        extern TableKey        gtt_Table_key;
        extern Okcv            gtt_Okcv;
        extern RcvPacket       gtt_rcv_r8;
        extern InputR8         gtt_internal_r8;
        extern ExtInput        gtt_Ext_input;
        extern R8Com           gtt_R8_com;
        extern Dsw             gtt_Dsw;
        extern Vp              gtt_Vp;
        extern Mc              gtt_Motor_current;
        extern Table_Code      gtt_Table_code[];
        extern REMO_Table_Code gtt_Remo_table_code; //2007.12.05
        extern REMO_Table_Code gtt_Remo_table_code_work; //2007.12.05
        extern Sp_Table_Code   gtt_Sp_table_code[];
        extern Com_Data        gtt_Com_rewrite_data;
        extern Com_Data        gtt_Internal_rewrite_data;
	extern struct	gtt_Internal_pack	gtt_Internal_pack;// 内部用データ・パッケージ
        extern Parameter       gtt_Parameter; //2008.02.25
        extern Parameter       gtt_Parameter_ch[CH]; //2008.08.07
        extern Special_menu    gtt_Special_menu; //2008.08.22
        extern Special_menu    gtt_Special_menu_ch[CH]; //2008.08.22
        extern Calender        gtt_Calender;         //2008.08.25
        extern Dital_attribute gtt_Dital_attribute[SELECT_DITAL_MAX+1]; //2008.08.27    // Phase11 by @Tny 2008/09/16
        extern unsigned char   guc_Write_check_flag[CH]; //2008.09.09
        extern En              gtt_En; //2008.09.22
        extern DitailWork      gtt_Ditail_work; //2008.10.09
        extern NAVI            gtt_Navi; //2009.01.15

//---------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23
        extern Dital_attribute gtt_Service_attribute[SERVICE_DATA_NO];
//---------------------------------------------------
//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
        extern Dital_attribute gtt_Rescue_attribute[RESCUE_DATA_NO];
//---------------------------------------------------


#endif



//
//	その他のヘッダファイル
//
#include        "SfrRegister.h"        // 内部レジスタアドレス定義部
#include        "com.h"                // 通信・ヘッダ部

#include        "weldtable.h"
#include        "wipcb.h"
#include        "sipcb.h"
#include        "inout.h"
#include        "ifdefine.h"

#include        "FPGA.h"               // ＦＰＧＡ制御系ヘッダ部
#include        "hpiDSP.h"             // ＤＳＰ－ＨＰＩ制御系ヘッダ部
#include        "Timer.h"              // フリーラン・タイマーヘッダ部
#include        "ExternFunc.h"         // その他の外部モジュール参照宣言部
#include        "moddef.h"
#include        "dpr.h"


//#include        "iodefine.h" 			//2019.04.02

//--------- RTC by @Tny 2008/08/28 ------------
#if true
    #include    "I2C_RTC.h" // Ｉ２Ｃ－ＲＴＣヘッダ
#endif
//--------------------------------------------

#ifndef __GLOBAL
	#include "extern.h"
#endif

//-------------------------------------------------
#endif	// __YD400GZ3_H

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of custom.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

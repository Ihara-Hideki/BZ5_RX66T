//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　ｃｏｍ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－１
//  【ヘッダ説明】
//      通信定義
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

#ifndef	__CPU_EXTERNAL_COMUNICATION_H
//-------------------------------------------------
#define	__CPU_EXTERNAL_COMUNICATION_H
//-------------------------------------------------

// define宣言部
//robot
#define		DLE				0xf0	// 送信開始コマンド
#define		GOODMORNING		0x4A	// ＧｏｏｄＭｏｒｎｉｎｇコマンド
#define		GD2ACK_SD		0xA1	//0xA1	// 送信用ACK
#define		GD2NAK_SD		0xA2	//0xA2	// 送信用NAK
#define		GD2Busy_SD		0xA3	//0xA3	// 送信用Busy
//remo
// 2019.09.02
//----------------------
#ifdef __NEWCOM_PROTOCOL
	#define		RE_GOODMORNING	0x20	// ＧｏｏｄＭｏｒｎｉｎｇコマンド
	#define		REMOACK_SD		0x91	//送信用ACK
	#define		REMONAK_SD		0x92	//送信用NAK
	#define		REMOBusy_SD		0x93	//送信用Busy
//----------------------
#else
	#define		RE_GOODMORNING	0x83	// ＧｏｏｄＭｏｒｎｉｎｇコマンド
	#define		REMOACK_SD		0x11	//0xA1	// 送信用ACK
	#define		REMONAK_SD		0x12	//0xA2	// 送信用NAK
	#define		REMOBusy_SD		0x13	//0xA3	// 送信用Busy
#endif
//----------------------
#define		BUFF			1030		// 送受信バッファ数
#define		BUFF2			 200		// 送受信バッファ数
// 受信系
#define 	DLE_mode		0x01	// ＤＬＥモード
#define 	CMD_mode		0x02	// ＣＭＤモード
#define 	DATA_mode		0x03	// ＤＡＴＡモード
#define 	SUM_mode		0x04	// ＳＵＭモード
// 送信系
#define 	DLE_mode_SD		0x01	// ＤＬＥモード
#define 	CMD_mode_SD		0x02	// ＣＭＤモード
#define 	DATA_mode_SD	0x03	// ＤＡＴＡモード
#define 	SUM_mode_SD		0x04	// ＳＵＭモード
#define 	WAIT_mode_SD	0x05	// ACK,NAK待ちモード

#define		OKCV			(table_adr + 0x0000)
#define		SB0				(table_adr + 0x0080)
#define		TABLEDATA		(short)(2816+2)		/*送信データ数*/
#define		TXB_BUFFER_MAX	BUFF2
#define		RXB_BUFFER_MAX	BUFF2

// 通信データのパッケージ
//
struct ComuniPack{
	struct{
		ubool	bRS422Connection;	// ＲＳ４２２側回線接続状態
		ubool	bRS232Connection;	// ＲＳ２３２ｃ側回線接続状態
		struct{	// ホストから受け取ったデータのパッケージ
			ubool		bChangeData;			// 受信データ更新フラグ
			uchar		iRecvCommand;			// 受信コマンド（データ更新判別用）
			ushort		usWeldingCurr;			// 出力電流指令値
			ushort		usWeldingVolt;			// 出力電圧指令値
			BitSwitch	fWireDiameter;			// ワイヤ径
			BitSwitch	fWelding;				// 溶接法
			BitSwitch	fWireMaterial;			// ワイヤ材質
			BitSwitch	fWireSelect;			// ワイヤ種
			BitSwitch	fInitialSelect1;		// 初期データ設定１
			short		vTsoAdj;				// 短絡初期時間調整   2009.06.26 char->short
			short		vIscAdj;				// 短絡電流屈折値調整 2009.06.26 char->short
			short		vIsl1Adj;				// 短絡電流勾配１調整 2009.06.29 char->short
			short		vIsl2Adj;				// 短絡電流勾配２調整 2009.06.29 char->short
			char		vTspAdj;				// 突っ掛かり防止時間調整
			short		vIacAdj;				// アーク電流屈折値調整  2009.06.26 char->short
			short		vIhotAdj;				// ホット電流調整     2009.06.26 char->short
			short		vVhotAdj;				// ホット電圧調整     2009.06.26 char->short
			short		vSldnAdj;				// ワイヤスローダウン調整 2009.06.29 char->short
			short		vFttAdj;				// ＦＴＴレベル調整       2009.06.29 char->short
			short		vBarnBackAdj;			// バーンバック時間調整   2009.06.29 char->short
			WelderCommand	fWelderCommand;			// 溶接電源動作指令
			WelderCheck	fWelderCheck;			// 溶接電源チェック
            Control     fControl;               // コントロール（ロボット通信で使用）2009.07.13
			ushort		usIP;					// パルスピーク指令電流
			ushort		usIB;					// パルスベース指令電流
			ushort		usPulseFreq;			// パルス指令周波数
			ushort		usPulseDuty;			// パルス指令幅
			short		usAcFreq;				// 交流周波数             2009.07.10 ushort->short
			short		ucCleaningDuty;			// クリーニング幅         2009.07.10 uchar->short
			short		ucMixFreq;				// MIX TIG周波数          2009.07.10 uchar->short
			short		ucMixAcRatio;			// MIX(AC)比率            2009.07.10 uchar->short
			//BitSwitch	fControl;				// コントロール           2009.07.13 del
			short		ucImprudenceVolt;		// 電極短絡電圧指令値     2009.07.15 uchar->short
			BitSwitch	fPulseMode;				// パルスモード設定
			short		vHotTime;				// ホットタイム               2009.06.26 char->short
			short		vIniIpAdj;				// スタートピーク電流微調整   2009.06.26 char->short
			short		vIniIbAdj;				// スタートベース電流微調整   2009.06.26 char->short
			short		vIpAdj;					// パルスピーク電流微調整     2009.06.25 char->short
			short		vIb1Adj;				// パルス第１ベース電流微調整 2009.06.25 char->short
			short		vIb2Adj;				// パルス第２ベース電流微調整
			short		vIprAdj;				// パルスピーク立ち上がり微調整 2009.06.25 char->short
			short		vIpfAdj;				// パルスピーク立ち下がり微調整 2009.06.25 char->short
			short		vTiprAdj;				// パルス立ち上がり時間微調整           2009.06.26 char->short
			short		vTipAdj;				// パルスピーク立ち上がり時間微調整     2009.06.26 char->short
			short		vTipfAdj;				// パルス立ち下がり時間微調整           2009.06.26 char->short
			char		vPulseFreqAdj;			// パルス周波数微調整
            short       vStartPulse;            // スタートパルス有り無し     2009.06.26 追加
            short       vEndPulse;              // エンドパルス有り無し       2009.06.26 追加
            short       vIniPulseFreqAdj;       // イニシャルパルス周波数     2009.06.26 追加
            short       vPctrlBlowAdj;          // アークブロー抑制制御       2009.06.26 追加
            short       vWirSpdAdj;             // ワイヤスピード微調整       2009.06.26 追加
            short       vWirStrAccAdj;          // スタートスロープ微調整     2009.06.26 追加
            short       vWirStrDelayAdj;        // ワイヤスタートディレイ微調整     2009.06.26 追加
            short       vNeckLvlAdj;            // ネックレベル微調整         2009.06.26 追加
            short       vWirAcDcAdj;            // 加速度３                   2009.06.26 追加
            short       vBbkPulseAdj;           // バーンバックパルス         2009.06.29 追加
			char		vLowPulseAB_LevelGap;	// 簡易ローパルス：Ａ条件Ｂ条件レベル差
			char		vLowPulseAB_TimeRatio;	// 簡易ローパルス：Ａ条件Ｂ条件時間比率
			char		vLowPulseFreq;			// 簡易ローパルス：周波数
			char		vLowPulseStartTimeAdj;	// 簡易ローパルス開始時間微調整
			char		vPulseStartSlope;		// パルススタートスロープ
			char		vPulseExecSlope;		// パルス指令値切り替えスロープ
			char		vPulsePerformance;		// パルス応答性
			BitSwitch	fLotCheck;				// 製品検査用
			char		vAfterFlowAddTime;		// アフターフロー時間加算値
			ushort		vCheck;					// バックアップメモリ確認用エリア
            char        vTableChange;           //テーブル切り替えコマンド 2007.2.9
            //<><><> TIG系調整パラメータ変数 2009.07.10 <><><>
            short       vIhotAdj_tig;           // ホット電流調整（ＴＩＧ系）
            short       vHotTime_tig;           // ホット時間調整（ＴＩＧ系）
            short       vHotSlop_tig;           // ホットスロープ（ＴＩＧ系）
            //<><><><><><><><><><><><><><><><><><><><><><><><>
            //<><><> 拡張溶接微調パラメータ変数 2007.5.29 <><><>
            unsigned short Id_no;               //ＩＤ番号
            short       Sp_current;             //ＳＰ電流
            short       Sp_time;                //ＳＰ時間
            short       Eli;                    //ＥＬＩ
            short       Mts_v;                  //重畳電圧値
            short       Mts_ontime;             //重畳電圧ＯＮ時間
            short       Mts_cycle;              //重畳電圧周期
            //<><><><><><><><><><><><><><><><><><><><><><><><><>

            sint           ss_En_duty_adjustment;     //ロボットから送られてきたＥＮ調整量 2008.10.03
	        unsigned short us_Q_WeldingCurr;        //2008.11.28
            short          ss_Q_en_duty_adjustment; //2008.11.28
            unsigned char  uc_Q_En_0_mode;          //2008.11.28
            unsigned char  uc_En_0_mode;            //2008.11.28
            
		} To;
		struct{	// ホストへ送るデータのパッケージ
			uchar		ucModelCode;			// 機種別コード
			//uchar		sRomVersion[2];			// ROMバージョン
			uchar		sRomVersion[3];			// ROMバージョン 2006.12.18 G3_NEW_COM Ihara
			uchar		ucPassword;				// パスワード変換後データ
 
            //<><><><><> G3_NEW_COM Ihara 2006.12.18<><><><><>
            uchar       Kind_code;
            uchar       Capacity_code[3];
            uchar       Model_code[3];
            uchar       Special_code[3];
            //<><><><><><><><><><><><><><><><><><><><><><><><>

			ushort		usWeldingCurr;			// 出力電流指令値
			ushort		usWeldingVolt;			// 出力電圧指令値
			ushort		usWeldingOutCurr;		// 出力電流値
			ushort		usWeldingOutVolt;		// 出力電圧値
			uchar		ucImprudence;			// 短絡回数
			uchar		ucMotorCurr;			// モータ電流値
			uchar		ucMotorRPM;				// モータ回転数
			uchar		ucMotorCurr2;			// モータ電流値２
			ushort		usMotorRPM2;			// モータ回転数２
			BitSwitch	fErrorCode1;			// 異常検出状態（溶接・送給系）
			BitSwitch	fErrorCode2;			// 異常検出状態（電源系）
			BitSwitch	fErrorCode3;			// 異常検出状態（異常・停止信号検出系）
			PowerStatus	fPowerStatus;			// 溶接電源状態
			ushort		usIP;				// パルスピーク電流
			ushort		usIB;				// パルスベース電流
			ushort		usPulseFreq;			// パルス周波数
			BitSwitch	fArcStartStatus;		// アークスタート状態
            
            uchar       uc_En_a;                //ＥＮ比率計算結果     2008.10.03
            ushort      us_En_Okcv;             //ＥＮ比率計算後一元化 2008.10.03

			struct{
				ushort		usWeldTimes;			// 溶接回数
				ushort		usWeldTimerIndividual;	// 溶接時間(個別)
				//ushort		usWeldTimerL;			// 溶接時間(L)
				//ushort		usWeldTimerH;			// 溶接時間(H)
                                unsigned int    usWeldTimer;           // 溶接時間 2007.3.30
				ulong		usWireFeed;				// ワイヤ総送給量
				ushort		vCheck;					// バックアップメモリ確認用エリア
			}BackUp;
		} From;
	} Data;
};



//<><><><><><><><><><>ＤＰＳ＋ＶＥＲ番号<><><><><><><><><><>
typedef struct{
        unsigned char uc_Dps_no_upper;         //ＤＰＳ番号上位
        unsigned char uc_Dps_no_mid;           //ＤＰＳ番号中位
        unsigned char uc_Dps_no_lower;         //ＤＰＳ番号下位
        unsigned char uc_Ver_no_upper;         //Ｖｅｒ番号上位
        unsigned char uc_Ver_no_mid;           //Ｖｅｒ番号中位
        unsigned char uc_Ver_no_lower;         //Ｖｅｒ番号下位
        unsigned char uc_Dps_no_upper16;       //ＤＰＳ番号上位
        unsigned char uc_Dps_no_mid16;         //ＤＰＳ番号中位
        unsigned char uc_Dps_no_lower16;       //ＤＰＳ番号下位
        unsigned char uc_Ver_no_upper16;       //Ｖｅｒ番号上位
        unsigned char uc_Ver_no_mid16;         //Ｖｅｒ番号中位
        unsigned char uc_Ver_no_lower16;       //Ｖｅｒ番号下位
        unsigned char uc_Dps_no_upper32;       //ＤＰＳ番号上位
        unsigned char uc_Dps_no_mid32;         //ＤＰＳ番号中位
        unsigned char uc_Dps_no_lower32;       //ＤＰＳ番号下位
        unsigned char uc_Ver_no_upper32;       //Ｖｅｒ番号上位
        unsigned char uc_Ver_no_mid32;         //Ｖｅｒ番号中位
        unsigned char uc_Ver_no_lower32;       //Ｖｅｒ番号下位
} DPS_VER;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><>アナログデータ<><><><><><><><><><><>
typedef struct{
	          unsigned char uc_No;
	          unsigned char uc_Data_uppre;
	          unsigned char uc_Data_lowre;
} ANALOG;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><>ＳＷデータ<><><><><><><><><><><><>
typedef union{	// 2019.05.29(RZ用に変更)
	          //unsigned char uc_Group[2];
	          unsigned char uc_Group[3]; //2009.01.09
        struct {
               ubool No1                   : 1;
               ubool No2                   : 1;
               ubool No3                   : 1;
               ubool No4                   : 1;
               ubool No5                   : 1;
               ubool No6                   : 1;
               ubool No7                   : 1;
               ubool No8                   : 1;

               ubool No9                   : 1;
               ubool No10                  : 1;
               ubool No11                  : 1;
               ubool No12                  : 1;
               ubool No13                  : 1;
               ubool No14                  : 1;
               ubool No15                  : 1;
               ubool No16                  : 1;

               //***** BP2用 2009.01.09 *****
               ubool No17                  : 1;
               ubool No18                  : 1;
               ubool No19                  : 1;
               ubool No20                  : 1;
               ubool No21                  : 1;
               ubool No22                  : 1;
               ubool No23                  : 1;
               ubool No24                  : 1;
               //****************************
        } Sw_bit;
} SW;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><>アナログデータ<><><><><><><><><><><>
typedef struct{
              unsigned char uc_Jog1;
              unsigned char uc_Jog2;
} JOG;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><>ＬＥＤデータ<><><><><><><><><><><>
typedef union{ // 2019.05.29	(RZ用に対応)
        unsigned char uc_Led[6];
        struct {
              //*** BP3の配置 2009.01.09***
              //group1
              ubool  Seg_led1_current_set           : 1; //７ｓｅｇＬＥＤ１　電流－設定
              ubool  Seg_led1_current_out           : 1; //７ｓｅｇＬＥＤ１　電流－出力
              ubool  Pulse_duty                    : 1; //パルス設定－パルス幅
              ubool  Pulse_frequency               : 1; //パルス設定－パルス周波数
              ubool  Seg_led2_second                : 1; //７ｓｅｇＬＥＤ２　秒（時間）
              ubool  Seg_led2_frequency             : 1; //７ｓｅｇＬＥＤ２　Ｈｚ（周波数）
              ubool  Seg_led2_duty                  : 1; //７ｓｅｇＬＥＤ２　％（比率）
              ubool  Seg_led2_voltage               : 1; //７ｓｅｇＬＥＤ２　Ｖ（電圧）
 
              //group2
              ubool  Pre_flow_select               : 1; //プリフロー選択
              ubool  Init_weld_current_select      : 1; //初期電流選択
              ubool  Up_slop_select                : 1; //アップスロープ選択
              ubool  Pulse_current_select          : 1; //パルス電流選択
              ubool  Main_weld_current_select      : 1; //溶接電流選択
              ubool  Down_slop_spot_select         : 1; //ダウンスロープ＆スポット時間選択
              ubool  Crater_current_select         : 1; //クレータ電流選択
              ubool  After_flow_select             : 1; //アフターフロー選択

              //group3
              ubool  Ac_std_select                 : 1; //ＡＣ標準波形選択
              ubool  Ac_hard_select                : 1; //ＡＣハード波形選択
              ubool  Ac_soft_select                : 1; //ＡＣソフト波形選択
              ubool  Group3_dummy3                 : 1; //LED42
              ubool  Cleaning_width_select         : 1; //クリーニング幅選択
              ubool  Ac_frequency_select           : 1; //交流周波数選択
              ubool  Group3_dummy2                 : 1; //LED45
              ubool  Group3_dummy1                 : 1; //LED46
              
              //group4
              ubool  Mix_frequency                 : 1; //ＭＩＸ周波数
              ubool  Dc_duty                       : 1; //直流比率
              ubool  Temp_abnormal                 : 1; //温度異常
              ubool  Gas                           : 1; //ガス点検
              ubool  Weld_mode_select              : 1; //溶接モード選択
              ubool  Ply_mode_select               : 1; //再生モード選択
              ubool  Rec_mode_select               : 1; //記憶モード選択
              ubool  Ditail_mode_select            : 1; //詳細モード選択

              //group5（溶接法）
              ubool  Standard_dc_tig_select        : 1; //標準　直流ＴＩＧ
              ubool  Standard_ac_tig_select        : 1; //標準　交流ＴＩＧ
              ubool  Standard_mix_tig_select       : 1; //標準　ＭＩＸＴＩＧ
              ubool  Standard_dc_hand_select       : 1; //標準　直流手溶接
              ubool  Navi_select                   : 1; //ナビゲーション
              ubool  Group5_dummy1                 : 1; //LED12
              //ubool  Quick_dc_tig_select           : 1; //クイック　直流ＴＩＧ
              //ubool  Quick_ac_tig_select           : 1; //クイック　交流ＴＩＧ
              ubool  Expert_dc_tig_select          : 1; //エキスパート　直流ＴＩＧ
              ubool  Expert_ac_tig_select          : 1; //エキスパート　交流ＴＩＧ

              //group6
              ubool  Crater_non_select             : 1; //クレータ無し選択      2009.01.10
              ubool  Crater_select                 : 1; //クレータ有り選択      2009.01.10
              ubool  Repeat_select                 : 1; //反復選択              2009.01.10
              ubool  Spot_select                   : 1; //スポット選択          2009.01.10
              ubool  Pulse_non_select              : 1; //パルス選択（パルス無）2009.01.10
              ubool  Pulse_select                  : 1; //パルス選択（パルス有）2009.01.10
              ubool  Group6_dummy2                 : 1; //LED21
              ubool  Group6_dummy1                 : 1; //LED22

       } Data;
} LED;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//*****************************　ＬＥＤ表示制御*************************
typedef struct{
        unsigned char uc_Block_no;             //表示するブロック番号
        unsigned char uc_Blink_on_off_flag;    //点滅表示の有り無し
        unsigned char uc_Blink_on_time;        //点滅時点灯時間
        unsigned char uc_Blink_off_time;       //点滅時消灯時間
        unsigned char uc_Blink_times;          //点滅繰り返し回数
}LED_CONTROL_DATA1;
//**********************************************************************

//*****************　ＬＥＤ表示制御（ロール制御）***********************
typedef struct{
        unsigned char uc_Roll_speed;           //ロール速度
        unsigned char uc_Roll_space;           //ロール間スペース個数
        unsigned char uc_Roll_times;           //ロール繰り返し回数
}LED_CONTROL_DATA2;
//**********************************************************************

//******************　ＬＥＤ表示制御（点滅制御）************************
//BP3用 2009.01.09
typedef union{ // 2019.05.29	(RZ用に対応)
        unsigned char uc_Led[6];
        struct {
              //データ　１：点滅　０：点灯
              //group1
              ubool  Seg_led1_current_set          : 1; //７ｓｅｇＬＥＤ１　電流－設定
              ubool  Seg_led1_current_out          : 1; //７ｓｅｇＬＥＤ１　電流－出力
              ubool  Pulse_duty                    : 1; //パルス設定－パルス幅
              ubool  Pulse_frequency               : 1; //パルス設定－パルス周波数
              ubool  Seg_led2_second               : 1; //７ｓｅｇＬＥＤ２　秒（時間）
              ubool  Seg_led2_frequency            : 1; //７ｓｅｇＬＥＤ２　Ｈｚ（周波数）
              ubool  Seg_led2_duty                 : 1; //７ｓｅｇＬＥＤ２　％（比率）
              ubool  Seg_led2_voltage              : 1; //７ｓｅｇＬＥＤ２　Ｖ（電圧）

              //group2
              ubool  Pre_flow_select               : 1; //プリフロー選択
              ubool  Init_weld_current_select      : 1; //初期電流選択
              ubool  Up_slop_select                : 1; //アップスロープ選択
              ubool  Pulse_current_select          : 1; //パルス電流選択
              ubool  Main_weld_current_select      : 1; //溶接電流選択
              ubool  Down_slop_spot_select         : 1; //ダウンスロープ＆スポット時間選択
              ubool  Crater_current_select         : 1; //クレータ電流選択
              ubool  After_flow_select             : 1; //アフターフロー選択

              //group3
              ubool  Ac_std_select                 : 1; //ＡＣ標準波形選択
              ubool  Ac_hard_select                : 1; //ＡＣハード波形選択
              ubool  Ac_soft_select                : 1; //ＡＣソフト波形選択
              ubool  Group3_dummy3                 : 1; //LED42
              ubool  Cleaning_width_select         : 1; //クリーニング幅選択
              ubool  Ac_frequency_select           : 1; //交流周波数選択
              ubool  Group3_dummy2                 : 1; //LED45
              ubool  Group3_dummy1                 : 1; //LED46
              
              //group4
              ubool  Mix_frequency                 : 1; //ＭＩＸ周波数
              ubool  Dc_duty                       : 1; //直流比率
              ubool  Temp_abnormal                 : 1; //温度異常
              ubool  Gas                           : 1; //ガス点検
              ubool  Weld_mode_select              : 1; //溶接モード選択
              ubool  Ply_mode_select               : 1; //再生モード選択
              ubool  Rec_mode_select               : 1; //記憶モード選択
              ubool  Ditail_mode_select            : 1; //詳細モード選択

              //group5（溶接法）
              ubool  Standard_dc_tig_select        : 1; //標準　直流ＴＩＧ
              ubool  Standard_ac_tig_select        : 1; //標準　交流ＴＩＧ
              ubool  Standard_mix_tig_select       : 1; //標準　ＭＩＸＴＩＧ
              ubool  Standard_dc_hand_select       : 1; //標準　直流手溶接
              ubool  Navi_select                   : 1; //ナビゲーション
              ubool  Group5_dummy1                 : 1; //LED12
              //ubool  Quick_dc_tig_select           : 1; //クイック　直流ＴＩＧ
              //ubool  Quick_ac_tig_select           : 1; //クイック　交流ＴＩＧ
              ubool  Expert_dc_tig_select          : 1; //エキスパート　直流ＴＩＧ
              ubool  Expert_ac_tig_select          : 1; //エキスパート　交流ＴＩＧ

              //group6
              ubool  Crater_non_select             : 1; //クレータ無し選択      2009.01.10
              ubool  Crater_select                 : 1; //クレータ有り選択      2009.01.10
              ubool  Repeat_select                 : 1; //反復選択              2009.01.10
              ubool  Spot_select                   : 1; //スポット選択          2009.01.10
              ubool  Pulse_non_select              : 1; //パルス選択（パルス無）2009.01.10
              ubool  Pulse_select                  : 1; //パルス選択（パルス有）2009.01.10
              ubool  Group6_dummy2                 : 1; //LED21
              ubool  Group6_dummy1                 : 1; //LED22


       } Data;
}LED_CONTROL_DATA3;
//**********************************************************************

//*****************************　ＬＣＤ表示制御 BP4 Phase4 by @Tny 2009.01.15 *************************
typedef struct{
        unsigned char  uc_Line_no;              //表示する行番号
        unsigned short us_Blink_on_off_flag;    //点滅表示の有り無し
        unsigned char  uc_Blink_on_time;        //点滅時点灯時間
        unsigned char  uc_Blink_off_time;       //点滅時消灯時間
        unsigned char  uc_Blink_times;          //点滅繰り返し回数
}LCD_CONTROL_DATA1;
//******************************************************************************************************


struct ComuniPackRemo{
	struct{
		ubool	bRS422Connection;	// ＲＳ４２２側回線接続状態
		struct{	// ホストから受け取ったデータのパッケージ
			ubool		bChangeData;			// 受信データ更新フラグ
            DPS_VER     Dps_Ver;
            ANALOG      Analog;
            SW          t_Sw;
            JOG         Jog;
		} To;
		struct{	// ホストへ送るデータのパッケージ
            unsigned char uc_Com_16led_data[18];
            unsigned char uc_Com_lcd_data1[17]; //ＬＣＤ　１行目データ 2009.01.09	16->17	2010.05.12 by @Tny
            unsigned char uc_Com_lcd_data2[17]; //ＬＣＤ　２行目データ 2009.01.09	16->17	2010.05.12 by @Tny
            unsigned char uc_Com_7led_data[7];
            LED           t_Led;
            LED_CONTROL_DATA1 t_Led_cntrol_data1;
            LED_CONTROL_DATA3 t_Led_cntrol_data3; //2009.01.09
            LCD_CONTROL_DATA1 t_Lcd_cntrol_data1; //BP4 Phase4 by @Tny 2009.01.15
			unsigned char uc_Lcd_Bright;		  //BP4 Phase9 by @Tny 2009.02.16
		} From;
	} Data;
};

struct InternalPackRemo{
	struct{
		ubool	bRS422Connection;	// ＲＳ４２２側回線接続状態
		struct{	// ホストから受け取ったデータのパッケージ
			ubool		bChangeData;			// 受信データ更新フラグ
            DPS_VER     Dps_Ver;
            ANALOG      Analog;
            SW          t_Sw;
            JOG         Jog;
		} To;
		struct{	// ホストへ送るデータのパッケージ
            unsigned char uc_Com_16led_data[18];
            unsigned char uc_Com_lcd_data1[17]; //ＬＣＤ　１行目データ 2009.01.09	16->17	2010.05.12 by @Tny
            unsigned char uc_Com_lcd_data2[17]; //ＬＣＤ　２行目データ 2009.01.09	16->17	2010.05.12 by @Tny
            unsigned char uc_Com_7led_data[7];
            LED           t_Led;
            LED_CONTROL_DATA1 t_Led_cntrol_data1;
            LED_CONTROL_DATA3 t_Led_cntrol_data3; //2009.01.09
            LCD_CONTROL_DATA1 t_Lcd_cntrol_data1; //BP4 Phase4 by @Tny 2009.01.15
		} From;
	} Data;
};




#if true // ↓ EXTERNAL IIF NEW		2011.02.21 by @Tny
//<><><><><><><><>アナログ入力補正データ<><><><><><><><><><>
typedef struct{
	          unsigned short us_Ch1;
	          unsigned short us_Ch2;
	          unsigned short us_Ch3;
	          unsigned short us_Ch4;
} IIF_ANALOG_REVISE;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><> ＩＩＦ＿ＤＳＷ <><><><><><><><><><><>
typedef union{ //ＤＳＷの内容
	unsigned char ALL;
	struct{
              ubool    No8                    :  1;
              ubool    No7                    :  1;
              ubool    No6                    :  1;
              ubool    No5                    :  1;
              ubool    No4                    :  1;
              ubool    No3                    :  1;
              ubool    No2                    :  1;
              ubool    No1                    :  1;
	}Sw;
} IIF_DSW;  
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
struct ComuniPackIif{
	struct{
		ubool	bRS422Connection;	// ＲＳ４２２側回線接続状態
		struct{	// ホストから受け取ったデータのパッケージ
			ubool		bChangeData;			// 受信データ更新フラグ
			uchar		iRecvCommand;			// 受信コマンド（データ更新判別用）
            unsigned short       us_Iif_input_data;	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
            unsigned short       us_Analog_data[4];
            unsigned short       us_Iif_analog_revise[5];
            IIF_DSW              t_Iif_dsw;
            unsigned char        uc_Iif_volt_jumper;
		} To;
		struct{	// ホストへ送るデータのパッケージ
            unsigned char        uc_Iif_output_data;
		} From;
	} Data;
};

struct InternalPackIif{
	struct{
		ubool	bRS422Connection;	// ＲＳ４２２側回線接続状態
		struct{	// ホストから受け取ったデータのパッケージ
			ubool		bChangeData;			// 受信データ更新フラグ
			uchar		iRecvCommand;			// 受信コマンド（データ更新判別用）
            unsigned short       us_Iif_input_data;	// 	<<<EXTERNAL IIF NEW>>>	１０ビット対応	2011.10.07 by @Tny
            unsigned short       us_Analog_data[4];
            unsigned short       us_Iif_analog_revise[5];
            IIF_DSW              t_Iif_dsw;
            unsigned char        uc_Iif_volt_jumper;
		} To;
		struct{	// ホストへ送るデータのパッケージ
            unsigned char        uc_Iif_output_data;
		} From;
	} Data;
};
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny



// 通信送信用フォーマット
struct Tx {
	unsigned char		Comm;
	unsigned char		Data;
	unsigned char		ACK;
	union SendInfo{
		unsigned short		ALL;
		struct{
			unsigned char		TimeOut			: 2;
			unsigned char		NAK				: 2;
			unsigned short		BackupStatus	: 6;
			unsigned short		Status			: 6;
		} Status;
	} SendInfo1;
};
struct RCV1{
	unsigned char Command[ 4 ] ;	/* データ */
	unsigned char Length ;			/* 長さ */
	unsigned char Rest ;			/* 残り */
} ;

union RDU1{
	short				Data;
	unsigned char		Buf[2];
};

#ifdef	__CPU_EXTERNAL_COMUNICATION_PROG
	//-------------------------------------------------
	// 通信クラスタ・モジュール系外部参照用宣言
	//
	extern unsigned char (*FromGD2[])(void);
	extern unsigned char (*ToGD2[])(void);
	extern unsigned char (*FromREMO[])(void);
	extern unsigned char (*ToREMO[])(void);
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	extern unsigned char (*FromIIF[])(void); //2009.09.29
	extern unsigned char (*ToIIF[])(void);   //2009.09.29
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

	//unsigned char (*ToGD2[256])(void);
	//unsigned char (*FromGD2[256])(void);
	//-------------------------------------------------
	// 通信クラスタ・データ系実体用宣言
	//
	union			RDU1			RD1;
	struct			RCV1			RCV1[RXB_BUFFER_MAX];
	struct			ComuniPack		ComuniPack;	// 通信用データ・パッケージ
	struct			ComuniPackRemo	ComuniPackRemo;	// 通信用データ・パッケージ
	struct			InternalPackRemo	InternalPackRemo;	// 通信用データ・パッケージ
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	struct			ComuniPackIif	ComuniPackIif;	    // IIF用データ・パッケージ
	struct			InternalPackIif	InternalPackIif;	// IIF用データ・パッケージ
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
	struct			gtt_Internal_pack	gtt_Internal_pack;// 内部用データ・パッケージ
	//struct			Tx				TX0[ TXB_BUFFER_MAX] ;
	//struct			Tx				TX2[ TXB_BUFFER_MAX] ;
	struct			Tx				TX1[ TXB_BUFFER_MAX] ;
    //LED             t_Led;
//robot & PC
	uchar						Rxd_DATA[BUFF];	// 受信バッファ
	uchar						Txd_CMD[BUFF];	// 送信コマンドバッファ
	uchar						Txd_DATA[BUFF];	// 送信バッファ
	uchar						RCV_Mode;
	uchar						SND_Mode;
	uchar						CMD_DATA_RX;
	uchar						SUM_ADD_RxData;
	uchar						SUM_ADD_TxData;
	uchar						RCV_Position;
	uchar						DATA_Length_RX;
	uchar						GD2_ACK_count;
	uchar						GD2_NAK_count;
	uchar						GD2_Busy_count;
	ushort						SND_CMD_Position;
	ushort						SND_CMD_Proc;
	ushort						data_count_tx;
	ushort						DATA_Length_TX;
	ubool						DLE_check_flag;
	ubool						DLE_check_flagSD;
	ubool						sio_table_flag;
	uchar						SND_Timer;
	uchar						WAIT_SD_count;
	uchar						RS422ErrorFlag;
	uchar						motor_rpm;
	uchar						TableData_exit;
	short						MAX_CURRENT;
    short                       MAX_CURRENT_AC_SOFT;  // 2009.12.29 500BP4 AC_SOFT
    short                       MAX_CURRENT_HAND;     // 2009.12.29 500BP4 HAND
    short                       MIN_CURRENT;          // 2009.12.29 500BP4 DC
    short                       MIN_CURRENT_AC;       // 2009.12.29 500BP4 AC,MIX 2011.10.01
    short                       MIN_CURRENT_AC_HARD;  // 2011.10.01
    short                       MIN_CURRENT_HAND;     // 2009.12.29 500BP4 HAND
    short                       MAX_CURRENT_ABS;      // 2010.01.18 500BP4 絶対値
	uchar						GD2_Pass1;
	uchar						GD2_Pass2;
	ushort						TXB1_Position;
	ushort						TXB1_Proc_Position;
	ushort						RXB1_Position;
	ushort						RXB1_Proc_Position;
	uchar						SoutPC_No;
	uchar						Checker_flag;
	uchar						data_count_rx;
	uchar						ACK_SND_Mode;
	uchar						CMD_DATA_TX;
	uchar						TPX_G2_Send_OFF;
	uchar						Check_G2_Send_OFF;
	uchar						sio_table_flagPC;
	short						sio_table_count;
	uchar						PC_ps_av_flag2;
	extern unsigned char		wd_wp_table;

//remo
	uchar						RE_Rxd_DATA[BUFF2];	// 受信バッファ
	uchar						RE_Txd_CMD[BUFF2];	// 送信コマンドバッファ
	uchar						RE_Txd_DATA[BUFF2];	// 送信バッファ
	uchar						RE_RCV_Mode;
	uchar						RE_SND_Mode;
	uchar						RE_CMD_DATA_RX;
	uchar						RE_SUM_ADD_RxData;
	uchar						RE_SUM_ADD_TxData;
	ushort						RE_RCV_Position;	// 2019.09.02
	ushort						RE_DATA_Length_RX;	// 2019.09.02
	uchar						REMO_ACK_count;
	uchar						REMO_NAK_count;
	uchar						REMO_Busy_count;
	ushort						RE_SND_CMD_Position;
	ushort						RE_SND_CMD_Proc;
	ushort						RE_data_count_tx;
	ushort						RE_DATA_Length_TX;
	ubool						RE_DLE_check_flag;
	ubool						RE_DLE_check_flagSD;
	uchar						RE_SND_Timer;
	uchar						RE_WAIT_SD_count;
	uchar						RE_RS422ErrorFlag;
	uchar						RE_Checker_flag;
	ushort						RE_data_count_rx;	// 2019.09.03
	uchar						RE_ACK_SND_Mode;
	uchar						RE_CMD_DATA_TX;
	uchar						TPX_REMO_Send_OFF;
	uchar						Check_REMO_Send_OFF;




        void    CheckCMD(unsigned char Number);
        void    RE_CheckCMD(unsigned char Number);



#else
	//-------------------------------------------------
	// 通信クラスタ・データ系外部参照用宣言
	//
#ifndef  __COM_TEBLE
	extern unsigned char (*ToGD2[])(void);
	extern unsigned char (*FromGD2[])(void);
	extern unsigned char (*ToREMO[])(void);
	extern unsigned char (*FromREMO[])(void);
#if true // ↓ EXTERNAL IIF NEWW	2011.02.21 by @Tny
	extern unsigned char (*FromIIF[])(void); //2009.09.29
	extern unsigned char (*ToIIF[])(void);   //2009.09.29
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
#endif
	extern struct	ComuniPack		ComuniPack;	// 通信用データ・パッケージ
	extern struct	ComuniPackRemo	ComuniPackRemo;	// 通信用データ・パッケージ
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	extern struct	ComuniPackIif	ComuniPackIif;	    // IIF用データ・パッケージ
	extern struct	InternalPackIif	InternalPackIif;	// IIF用データ・パッケージ
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
	extern struct	InternalPackRemo	InternalPackRemo;	// 通信用データ・パッケージ
	//extern struct	gtt_Internal_pack	gtt_Internal_pack;// 内部用データ・パッケージ
	extern union       RDU1                 RD1;
	extern struct      RCV1                 RCV1[RXB_BUFFER_MAX];
	//extern struct      Tx                   TX0[ TXB_BUFFER_MAX] ;
	//extern struct      Tx                   TX2[ TXB_BUFFER_MAX] ;
	extern struct      Tx                   TX1[ TXB_BUFFER_MAX] ;
    //extern LED             t_Led;
	extern uchar				Rxd_DATA[BUFF];	// 受信バッファ
	extern uchar				Txd_CMD[BUFF];	// 送信コマンドバッファ
	extern uchar				Txd_DATA[BUFF];	// 送信バッファ
	extern uchar				RCV_Mode;
	extern uchar				SND_Mode;
	extern uchar				CMD_DATA_RX;
	extern uchar				SUM_ADD_RxData;
	extern uchar				SUM_ADD_TxData;
	extern uchar				RCV_Position;
	extern uchar				DATA_Length_RX;
	extern uchar				GD2_ACK_count;
	extern uchar				GD2_NAK_count;
	extern uchar				GD2_Busy_count;
	extern ushort				SND_CMD_Position;
	extern ushort				SND_CMD_Proc;
	extern ushort				data_count_tx;
	extern ushort				DATA_Length_TX;
	extern ubool					DLE_check_flag;
	extern ubool					DLE_check_flagSD;
	extern ubool					sio_table_flag;
	extern uchar				SND_Timer;
	extern uchar				WAIT_SD_count;
	extern uchar				RS422ErrorFlag;
	extern uchar				motor_rpm;
	extern uchar				TableData_exit;
	extern short				MAX_CURRENT;
    extern short                MAX_CURRENT_AC_SOFT;  // 2009.12.29 500BP4 AC_SOFT
    extern short                MAX_CURRENT_HAND;     // 2009.12.29 500BP4 HAND
    extern short                MIN_CURRENT;          // 2009.12.29 500BP4 DC
    extern short                MIN_CURRENT_AC;       // 2009.12.29 500BP4 AC,MIX 2011.10.01
    extern short                MIN_CURRENT_AC_HARD;  // 2011.10.01
    extern short                MIN_CURRENT_HAND;     // 2009.12.29 500BP4 HAND
    extern short                MAX_CURRENT_ABS;      // 2010.01.18 500BP4 絶対値
	extern uchar				GD2_Pass1;
	extern uchar				GD2_Pass2;
	extern ushort				TXB1_Position;
	extern ushort				TXB1_Proc_Position;
	extern ushort				RXB1_Position;
	extern ushort				RXB1_Proc_Position;
	extern uchar				SoutPC_No;
	extern uchar				Checker_flag;
	extern uchar				data_count_rx;
	extern uchar				ACK_SND_Mode;
	extern uchar				CMD_DATA_TX;
	extern uchar				TPX_G2_Send_OFF;
	extern uchar				Check_G2_Send_OFF;
	extern uchar				sio_table_flagPC;
	extern short				sio_table_count;
	extern uchar				PC_ps_av_flag2;

	extern unsigned char		wd_wp_table;


//remo
	extern uchar					RE_Rxd_DATA[BUFF2];	// 受信バッファ
	extern uchar					RE_Txd_CMD[BUFF2];	// 送信コマンドバッファ
	extern uchar					RE_Txd_DATA[BUFF2];	// 送信バッファ
	extern uchar					RE_RCV_Mode;
	extern uchar					RE_SND_Mode;
	extern uchar					RE_CMD_DATA_RX;
	extern uchar					RE_SUM_ADD_RxData;
	extern uchar					RE_SUM_ADD_TxData;
	extern ushort					RE_RCV_Position;	// 2019.09.03
	extern ushort					RE_DATA_Length_RX;	// 2019.09.03
	extern uchar					REMO_ACK_count;
	extern uchar					REMO_NAK_count;
	extern uchar					REMO_Busy_count;
	extern ushort					RE_SND_CMD_Position;
	extern ushort					RE_SND_CMD_Proc;
	extern ushort					RE_data_count_tx;
	extern ushort					RE_DATA_Length_TX;
	extern ubool						RE_DLE_check_flag;
	extern ubool						RE_DLE_check_flagSD;
	extern uchar					RE_SND_Timer;
	extern uchar					RE_WAIT_SD_count;
	extern uchar					RE_RS422ErrorFlag;
	extern uchar					RE_Checker_flag;
	extern ushort					RE_data_count_rx;	// 2019.09.03
	extern uchar					RE_ACK_SND_Mode;
	extern uchar					RE_CMD_DATA_TX;
	extern uchar					TPX_REMO_Send_OFF;
	extern uchar					Check_REMO_Send_OFF;



	//-------------------------------------------------
	// 通信クラスタ・モジュール系外部参照用宣言
	//
	extern ubool    Cpu_ExtComChangeData(void);	// 通信クラスタ受信データ更新確認モジュール
	//extern void		RS_Proc(void);				// ＲＳ送信処理
	extern void    int_com_proc(void);				// ＲＳ送信処理
	extern void    pc_com_snd(void) ;
	extern void    rob_com_snd(void) ;
	extern void    re_com_snd(void) ;
	extern void    Snd_ACK(void);				// ＡＣＫデータ送信
	extern void    Snd_NAK(void);				// ＮＡＫデータ送信
    //extern void    CheckCMD(signed char Number);
    extern void    CheckCMD(unsigned char Number);
    extern void    RE_CheckCMD(unsigned char Number);
	extern uchar   StaticDmy(void);			// ダミー処理
        extern void    Cpu_ExtComInitial(ubool AllInitial);


#endif	// __CPU_EXTERNAL_COMUNICATION_PROG
	extern unsigned char PC_Send_A6(void);
	extern unsigned char PC_Send_B1(void);
	extern unsigned char PC_Send_C1(void);
	extern unsigned char PC_Send_C2(void);
	extern unsigned char PC_Send_C3(void);
	extern unsigned char PC_Send_C4(void);
	extern unsigned char PC_Send_C5(void);
	extern unsigned char PC_Send_D1(void);
	extern unsigned char PC_Send_E1(void);
	extern unsigned char PC_Send_E2(void);
	extern unsigned char PC_Send_E3(void);
	extern unsigned char PC_Send_E4(void);
	extern unsigned char PC_Send_E5(void); //DSP検査用　2006.2.16　井原
	extern unsigned char PC_Send_E8(void);
	extern unsigned char PC_Send_F5(void); //DSP検査用　2006.2.22　井原
	extern unsigned char PC_Recv_B3(void);
	extern unsigned char PC_Recv_B4(void);
	extern unsigned char PC_Recv_E1(void);


//<><><><><><><> 新モニタソフト用2007.1.19 <><><><><><><><> 2007.1.26移植追加
	extern unsigned char PC_Recv_90(void);
	extern unsigned char PC_Recv_91(void);
	extern unsigned char PC_Recv_92(void);
	extern unsigned char PC_Recv_93(void);
	extern unsigned char PC_Recv_94(void);
	extern unsigned char PC_Recv_95(void);
	extern unsigned char PC_Recv_96(void);
	extern unsigned char PC_Recv_97(void);
	extern unsigned char PC_Recv_98(void);
	extern unsigned char PC_Recv_99(void);
	extern unsigned char PC_Recv_9A(void);
	extern unsigned char PC_Recv_9B(void);
	extern unsigned char PC_Recv_9C(void);
	extern unsigned char PC_Recv_9D(void);
	extern unsigned char PC_Recv_9E(void);
	extern unsigned char PC_Recv_9F(void);
	extern unsigned char PC_Recv_A0(void);
	extern unsigned char PC_Recv_A1(void);
	extern unsigned char PC_Recv_A2(void);
	extern unsigned char PC_Recv_A3(void);
	extern unsigned char PC_Recv_A4(void);
	extern unsigned char PC_Recv_A5(void);
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//--------- IIF by @Tny 2008/08/26 ------------
#if true
	extern unsigned char GD2_Send_20(void);
	extern unsigned char GD2_Send_30(void);
#endif
//--------------------------------------------
	extern unsigned char GD2_Send_11(void);
	extern unsigned char GD2_Send_21(void);
	extern unsigned char GD2_Send_A1(void);
	extern unsigned char GD2_Send_A2(void);
	extern unsigned char GD2_Send_B1(void);
	extern unsigned char GD2_Send_B2(void);
	extern unsigned char GD2_Send_B3(void); //G3_NEW_COM 2006.12.18 Ihara
	extern unsigned char GD2_Send_C1(void);
	extern unsigned char GD2_Send_C2(void);
	extern unsigned char GD2_Send_C3(void);
	extern unsigned char GD2_Send_C4(void);
	extern unsigned char GD2_Send_C5(void);
	extern unsigned char GD2_Send_D1(void);
	extern unsigned char GD2_Send_D2(void);
	extern unsigned char GD2_Send_E1(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Send_E2(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Send_E3(void); //AZ3用 2008.10.03
	extern unsigned char GD2_Recv_41(void);
	extern unsigned char GD2_Recv_42(void);
	extern unsigned char GD2_Recv_47(void);
	extern unsigned char GD2_Recv_48(void);
	extern unsigned char GD2_Recv_49(void);
	extern unsigned char GD2_Recv_4A(void);
	extern unsigned char GD2_Recv_4F(void);
	extern unsigned char GD2_Recv_52(void);
	extern unsigned char GD2_Recv_53(void);
	extern unsigned char GD2_Recv_61(void);
	extern unsigned char GD2_Recv_62(void);
	extern unsigned char GD2_Recv_63(void);
	extern unsigned char GD2_Recv_64(void);
	extern unsigned char GD2_Recv_67(void);
	extern unsigned char GD2_Recv_68(void);
	extern unsigned char GD2_Recv_69(void); //2009.07.14
	extern unsigned char GD2_Recv_6B(void); //2009.07.14
	extern unsigned char GD2_Recv_6C(void); //G3_NEW_COM 2007.01.08
	extern unsigned char GD2_Recv_71(void);
	extern unsigned char GD2_Recv_81(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_82(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_83(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_84(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_85(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_86(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_87(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_88(void); //G3_NEW_COM 2006.12.22
	extern unsigned char GD2_Recv_89(void); //G3_NEW_COM 2007.2.9
	extern unsigned char GD2_Recv_8A(void); //G3_NEW_COM 2007.5.11
	extern unsigned char GD2_Recv_8B(void); //G3_NEW_COM 2007.5.11
	extern unsigned char GD2_Recv_8C(void); //AZ3用 2008.10.03
	extern unsigned char GD2_Recv_8D(void); //AZ3用 2008.10.03
	extern unsigned char GD2_Recv_8E(void); //AZ3用 2008.10.03

	extern void GD2_Send_CMD(uchar CMD_CODE);


// 2019.09.02
//----------------------
//#ifdef __NEWCOM_PROTOCOL
	extern unsigned char REMO_Send_91(void);
	extern unsigned char REMO_Send_92(void);
	extern unsigned char REMO_Send_A0(void);
	extern unsigned char REMO_Send_A1(void);
	extern unsigned char REMO_Send_A2(void);
	extern unsigned char REMO_Send_B0(void);
	extern unsigned char REMO_Send_C0(void);
//#endif
//----------------------

	extern unsigned char REMO_Send_11(void);
	extern unsigned char REMO_Send_12(void);
	extern unsigned char REMO_Send_13(void);
	extern unsigned char REMO_Send_15(void);
	extern unsigned char REMO_Send_16(void);
	extern unsigned char REMO_Send_20(void);
	extern unsigned char REMO_Send_21(void);
	extern unsigned char REMO_Send_22(void);
	extern unsigned char REMO_Send_23(void);
	extern unsigned char REMO_Send_24(void);
	//extern unsigned char REMO_Send_30(void); 2009.03.16 del
	//extern unsigned char REMO_Send_31(void); 2009.03.16 del
	extern unsigned char REMO_Send_32(void);
	extern unsigned char REMO_Send_33(void);	// Phase31 by @Tny 2008.11.25
	extern unsigned char REMO_Send_34(void);	// 2009.01.09
	extern unsigned char REMO_Send_35(void);	// 2009.01.09
	extern unsigned char REMO_Send_36(void);	// 2009.01.09
	extern unsigned char REMO_Send_37(void);	// 2009.01.09
	extern unsigned char REMO_Send_38(void);	// 2009.01.09
	extern unsigned char REMO_Send_39(void);	// 2009.01.09


// 2019.09.02
//----------------------
//#ifdef __NEWCOM_PROTOCOL
	extern unsigned char REMO_Recv_11(void);
	extern unsigned char REMO_Recv_12(void);
	extern unsigned char REMO_Recv_20(void);
	extern unsigned char REMO_Recv_30(void);
	extern unsigned char REMO_Recv_31(void);
	extern unsigned char REMO_Recv_32(void);
	extern unsigned char REMO_Recv_40(void);
	extern unsigned char REMO_Recv_41(void);
	extern unsigned char REMO_Recv_50(void);
	extern unsigned char REMO_Recv_51(void);
	extern unsigned char REMO_Recv_52(void);
	extern unsigned char REMO_Recv_60(void);
	extern unsigned char REMO_Recv_61(void);
//#endif
//----------------------
	extern unsigned char REMO_Recv_80(void);
	extern unsigned char REMO_Recv_81(void);
	extern unsigned char REMO_Recv_82(void);
	extern unsigned char REMO_Recv_83(void);
	extern unsigned char REMO_Recv_84(void);
	extern unsigned char REMO_Recv_8A(void);
	extern unsigned char REMO_Recv_8B(void);
	extern unsigned char REMO_Recv_8C(void);
	extern unsigned char REMO_Recv_90(void);
	extern unsigned char REMO_Recv_91(void);
	extern unsigned char REMO_Recv_A1(void);    // 2009.01.09
	extern void REMO_Send_CMD(uchar CMD_CODE);

//-------------------------------------------------
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	extern unsigned char IIF_Send_11(void);
	extern unsigned char IIF_Send_12(void);
	extern unsigned char IIF_Send_13(void);
	extern unsigned char IIF_Send_14(void);
	extern unsigned char IIF_Send_15(void);
	extern unsigned char IIF_Send_20(void);
	extern unsigned char IIF_Send_40(void);
	extern unsigned char IIF_Send_41(void);
	extern unsigned char IIF_Send_42(void);
	extern unsigned char IIF_Send_43(void);
	extern unsigned char IIF_Send_44(void);
	extern unsigned char IIF_Send_45(void);
	extern unsigned char IIF_Send_50(void);
	extern unsigned char IIF_Send_51(void);
	extern unsigned char IIF_Send_52(void);
	extern unsigned char IIF_Send_53(void);
	extern unsigned char IIF_Send_54(void);

	extern unsigned char IIF_Recv_81(void);
	extern unsigned char IIF_Recv_82(void);
	extern unsigned char IIF_Recv_83(void);
	extern unsigned char IIF_Recv_84(void);
	extern unsigned char IIF_Recv_85(void);
	extern unsigned char IIF_Recv_87(void);
	extern unsigned char IIF_Recv_86(void);
	extern unsigned char IIF_Recv_8A(void);
	extern unsigned char IIF_Recv_8B(void);
	extern unsigned char IIF_Recv_8C(void);
	extern unsigned char IIF_Recv_8D(void);
	extern unsigned char IIF_Recv_A0(void);
	extern unsigned char IIF_Recv_A1(void);
	extern unsigned char IIF_Recv_A2(void);
	extern unsigned char IIF_Recv_A3(void);
	extern unsigned char IIF_Recv_A4(void);
	extern unsigned char IIF_Recv_A5(void);
	extern unsigned char IIF_Recv_A6(void);
	extern unsigned char IIF_Recv_A7(void);
	extern unsigned char IIF_Recv_A8(void);
	extern unsigned char IIF_Recv_A9(void);
	extern unsigned char IIF_Recv_AA(void);
	extern unsigned char IIF_Recv_AB(void);
	extern unsigned char IIF_Recv_B0(void);
	extern unsigned char IIF_Recv_B1(void);
	extern unsigned char IIF_Recv_B2(void);
	extern unsigned char IIF_Recv_B3(void);
	extern unsigned char IIF_Recv_B4(void);
	extern unsigned char IIF_Recv_B5(void);
	extern unsigned char IIF_Recv_B6(void);
#endif	// ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

//-------------------------------------------------

#endif	// __CPU_EXTERNAL_COMUNICATION_H






//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of com.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

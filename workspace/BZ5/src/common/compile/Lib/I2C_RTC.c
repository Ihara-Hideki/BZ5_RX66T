//--------------------------------------------------------------------------
//
// 【ＡＺ３用】　Ｉ２Ｃ－ＲＴＣモジュール部[I2C_RTC.c]
//
//             Original : 2008-08-27(Wed) : M.Tanigawa
//
// Copyright(C)2008 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//--------------------------------------------------------------------------
#define	__I2C_RTC_PROG

#include    "custom.h"
#include "r_typedefs.h"
#include "stdint.h"
#include "iodefine.h"
#include "dev_drv.h"            /* Device Driver common header */

//----------------------------------------------------------------------------------------
//------------------------------ ハードウェア(CPU)依存部 ---------------------------------
//----------------------------------------------------------------------------------------

//--------------------------------------------
//------------ I2C-RTC制御モジュール ---------
//--------------------------------------------

// I2C信号宣言部：ハードウェア仕様に合わせること
//
// 【注意】
//
//  (M32186 : P73(xx1xxxxxB)=SCL / P72(xxx1xxxxB)=SDA　※１：両ポートはポート初期化時に入力モードで０(Low)をセットしておくこと)
//  (                                                  ※２：P73,P72は初期化時に"0"（Ｌｏｗ）にすること                       )
//
//	P7DIR  = 0x00 ;	// P7DIR	: 0000 0000 :         BLCK,       *WAIT,         SDA,         SCL, IFNMI_ST[1], IFNMI_ST[2], IFNMI_ST[3], IFNMI_ST[4]
//
#define		SCL_H		(P7DIR = ((P7DIR & ~(0x10)) | 0x00))	// SCL Clock信号をＨｉにする	（当該ポートを入力モードにすることで信号をＨｉにする）
#define		SCL_L		(P7DIR = ((P7DIR |  (0x10)) | 0x00))	// SCL Clock信号をＬｏｗにする	（当該ポートを出力モードにすることで信号をＬｏｗにする）
#define		SDA_H		(P7DIR = ((P7DIR & ~(0x20)) | 0x00))	// SDA Data信号をＨｉにする		（当該ポートを入力モードにすることで信号をＨｉにする）
#define		SDA_L		(P7DIR = ((P7DIR |  (0x20)) | 0x00))	// SDA Data信号をＬｏｗにする	（当該ポートを出力モードにすることで信号をＬｏｗにする）
#define		I2C_ACK		(P7DATA & 0x10)							// SCL Clock信号を確認することでACKを確認したことと同等とする
#define		SDA			(P7DATA & 0x20)							// SDA Data信号の入力ポート
#define		PORT_INIT	(P7DATA = (P7DATA & ~(0x30)))			// SCL/SDAともにＬｏｗとする（出力時の絶対条件として当該データレジスタのポートは０(Low)とする）

// Wait系宣言部
//
#if true
    #define		WR_CYC				0		// ページ書き込み後の待ち時間	(forループで10ms以上になるよう調整すること)
    #define		CYCLE				3		// [SCL]パルス幅 (forループで約10uSになるよう調整すること) 2009.12.08 3(312kHz)に変更
#else
	#define		WR_CYC				50000	// ページ書き込み後の待ち時間	(forループで10ms以上になるよう調整すること)
	#define		CYCLE				20	  	// [SCL]パルス幅				(forループで約10uSになるよう調整すること)
#endif

// ライブラリ内部専用モジュール宣言
//
static void I2Cwait(unsigned int Count);
static void I2Cwrite(ubool Sw, uchar Data);
static void I2Cread(ubool Sw, uchar *Data, ubool EOM);
static void I2Cstart(ubool rw, uchar	Command);
static void I2Cstop(void);

/***
**  ID     = I2C_RTC
**  name   = Ｉ２Ｃ－ＲＴＣアクセス・メイン処理
**  func   = Ｉ２Ｃ－ＲＴＣへの読み込み／書き込みを行う（メイン処理部）
**  called = void I2C_RTC(ubool Sw, uchar *MemAddress, uchar RTC_Command, ushort Length);
**  io     = Sw				: ubool   : 動作フラグ（true:読み込み／false:書き込み）
**           MemAddress		: *uchar : 転送元／転送先データエリアの先頭アドレス
**           RTC_Command	: uchar  : RTC制御コマンド
**           Length			: ushort  : 転送バイト長
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 本処理はＩ／Ｏポート方式で行うため、他の割り込みは禁止にしておくこと。
**  date   = 2007/08/24 by 谷川まさや
***/
void I2C_RTC(ubool Sw, uchar *MemAddress, uchar RTC_Command, ushort Length)
{
	ushort	iOffset = 0;
    ubool    bCommandSend = false;
    ubool    bShiftSelect;

	WDG_Clear();

    switch(RTC_Command){
        case STATUS_1:      {bShiftSelect = true    ;break;}    // ステータスレジスタ１のアクセス
        case STATUS_2:      {bShiftSelect = true    ;break;}    // ステータスレジスタ２のアクセス
        case RTC_DATA_1:    {bShiftSelect = false   ;break;}    // リアルタイムデータ１のアクセス
        case RTC_DATA_2:    {bShiftSelect = false   ;break;}    // リアルタイムデータ２のアクセス
        case RTC_INT1:      {bShiftSelect = true    ;break;}    // ＩＮＴ１レジスタのアクセス
        case RTC_INT2:      {bShiftSelect = true    ;break;}    // ＩＮＴ２レジスタのアクセス
        case CLOCK_ADJUST:  {bShiftSelect = false   ;break;}    // クロック補正レジスタのアクセス
        case FREE:          {bShiftSelect = true    ;break;}    // フリーレジスタのアクセス
    }
#if false	//	2019.05.30	true
    // 割り込み禁止
    //CPU_di();
	// データ処理終了までの処理ループ
	while(true){
		// I2C-Bus起動
		//
		I2Cstart(Sw,RTC_Command);	// I2C-Bus起動（アドレス設定）＋Ｒ／Ｗ＋ＲＴＣコマンドを送信

		// データ処理終了まで or アクセス・エリアがページの範囲を超えるまでの処理ループ
		while(true){
            if(bCommandSend == false){
                I2Cwrite(true, Sw | ((RTC_Command << 1) & 0x0e) | 0x60);	// ０１１０＊＊＊スレーブと、コマンド番号と、Ｒ／Ｗ
                bCommandSend = true;
            }
            else{
    			if(Sw == RTC_READ){	// Readモード？
    				if(iOffset == (Length - 1)){ // 最終バイトを受信する？
    					I2Cread(bShiftSelect, (MemAddress + iOffset), true);	// 最後はACK　”Ｈ”で終了
    				}
    				else{
    					I2Cread(bShiftSelect, (MemAddress + iOffset), false);
    				}
    			}
    			else{	// Writeモード
    				I2Cwrite(bShiftSelect, *(MemAddress + iOffset));
    			}

                // 転送数の確認
    			if(++iOffset >= Length){ // 指定転送分実行した?
    				break;
    			}
            }
		}

		I2Cstop();			// I2C-Bus停止
		if(Sw == RTC_WRITE){// Writeモード？
			I2Cwait(WR_CYC);				// I2C-EEPROMの書き込み動作待ち
		}

		if(iOffset >= Length){ // 所定データ数分処理が終了？
			break;
		}
	}
    // 割り込み許可
    //CPU_ei();
#else
	{
		if((Sw == RTC_READ)&&(RTC_Command == RTC_DATA_1))
		{
			do{
			//RTC.RCR2 &= ~0x01;	// RTC停止
			RTC.RCR1 &= ~0x90;	// 桁上げ割り込み発生：イネーブル
			//*(MemAddress + 0) = (((RTC.RYRCNT & 0x0F000) >> 12 * 1000) + ((RTC.RYRCNT & 0x00F00) >> 8 * 100) + ((RTC.RYRCNT & 0x000F0) >> 4 * 10) + (RTC.RYRCNT & 0x000F)); // 年
			*(MemAddress + 0) = (RTC.RYRCNT & 0x000FF); // 年
			*(MemAddress + 1) = (RTC.RMONCNT & 0x0001F); // 月
			*(MemAddress + 2) = (RTC.RDAYCNT & 0x000FF); // 日
			*(MemAddress + 3) = 0;
			*(MemAddress + 4) = (RTC.RHRCNT & 0x000FF); // 時
			*(MemAddress + 5) = (RTC.RMINCNT & 0x000FF); // 分
			*(MemAddress + 6) = (RTC.RSECCNT & 0x000FF); // 秒
			//RTC.RCR2 |= 0x01;	// RTC動作
			} while((RTC.RCR1 & 0x80) != 0);
		}
		else if((Sw == RTC_WRITE)&&(RTC_Command == RTC_DATA_1))
		{
			RTC.RCR2 &= ~0x01;	// RTC停止
			RTC.RYRCNT	= (0x2000 + *(MemAddress + 0));	// 年+2000
			RTC.RMONCNT	= (*(MemAddress + 1));				// 月
			RTC.RDAYCNT	= (*(MemAddress + 2));				// 日
			RTC.RHRCNT	= (*(MemAddress + 4));				// 時
			RTC.RMINCNT	= (*(MemAddress + 5));				// 分
			RTC.RSECCNT	= (*(MemAddress + 6));				// 秒
			RTC.RCR2 |= 0x01;	// RTC動作
		}
	}
#endif
}
/***
**  ID     = I2Cwait
**  name   = Ｉ２Ｃ－ＲＴＣ書き込み処理待ち用ウェイト処理
**  func   = Ｉ２Ｃ－ＲＴＣの書き込み動作を待つ為のウエイト処理を行う
**  called = static void I2Cwait(unsigned int Count);
**  io     = Count			: uint    : 待ち時間
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2007/08/24 by 谷川まさや
***/
static void I2Cwait(unsigned int Count)
{
	unsigned int	cWait = Count;

	while(cWait) cWait--;
}
/***
**  ID     = I2Cwrite
**  name   = Ｉ２Ｃ－ＲＴＣ１バイト書き込み処理
**  func   = Ｉ２Ｃ－ＲＴＣへ１バイト分データを書き込む
**  called = static void I2Cwrite(ubool Sw, uchar Data);
**  io     = Sw         	: ubool    : 転送方法（true:MSB First / false LSB First）
**           Data			: uchar   : 送信データ
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2007/08/24 by 谷川まさや
***/
static void I2Cwrite(ubool Sw, uchar Data)
{
	uchar	i;
	uchar	dat = Data;

	PORT_INIT;
	I2Cwait(CYCLE);
	for(i=0; i<=7; i++){ // 8Bit
		if(Sw){
    		if (dat & 0x80) SDA_H;
	    	else			SDA_L;
            dat = (dat << 1);
        }
		else{
    		if (dat & 0x01) SDA_H;
	    	else			SDA_L;
            dat = (dat >> 1);
        }
		I2Cwait(CYCLE);
		SCL_H;
		I2Cwait(CYCLE);
		while(I2C_ACK == 0);
		SCL_L;
	}
	SDA_H;
	I2Cwait(CYCLE);
	SCL_H;			// ＡＣＫ受信
	I2Cwait(CYCLE);
	SCL_L;
	SDA_L;			// ストップコンディションとなるのを防止
}
/***
**  ID     = I2Cread
**  name   = Ｉ２Ｃ－ＲＴＣ１バイト読み込み処理
**  func   = Ｉ２Ｃ－ＲＴＣへ１バイト分データを読み込む
**  called = static void I2Cread(ubool Sw, uchar *Data, ubool EOM)
**  io     = Sw         	: ubool   : 転送方法（true:MSB First / false LSB First）
**           Data			: *uchar : 受信データを格納するエリア
**           EOM			: ubool   : 最終バイトの受信である場合はtrueを指定、通常はfalse
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2007/08/24 by 谷川まさや
***/
static void I2Cread(ubool Sw, uchar *Data, ubool EOM)
{
	uchar	i;
	uchar	dat = 0;

	PORT_INIT;
	SDA_H;
	I2Cwait(CYCLE);
	for(i=0; i<=7; i++){ // 8bit
		SCL_H;
		if(Sw){
    		dat = (dat << 1);
	    	if(SDA) dat = (dat | 0x01);
        }
        else{
    		dat = (dat >> 1);
	    	if(SDA) dat = (dat | 0x80);
        }
		I2Cwait(CYCLE);
		while(I2C_ACK == 0);
		SCL_L;
		I2Cwait(CYCLE);
	}
	if(EOM) SDA_H;
	else	SDA_L;	// ＡＣＫ　最終は、”Ｈ”で終了
	I2Cwait(CYCLE);
	SCL_H;
	I2Cwait(CYCLE);
	SCL_L;
	*Data = dat;	// 指定エリアへのデータ・セット
}
/***
**  ID     = I2Cstart
**  name   = I2C-Bus起動処理
**  func   = I2C-Busデバイスのスタートコンディション（デバイスアドレス設定）を行う
**  called = static void I2Cstart(ubool rw, uchar Command);
**  io     = rw			: ubool   : 動作モード　false = write ／ true = read
**           Command	: uchar  : コマンド番号
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2008/08/27 by 谷川まさや
***/
static void I2Cstart(ubool rw, uchar Command)
{
	SCL_H;
	SDA_H;
	I2Cwait(CYCLE);
	SDA_L;					// スタート
	I2Cwait(CYCLE);
	SCL_L;
//	I2Cwrite(true, rw | ((Command << 1) & 0x0e) | 0x60);	// ０１１０＊＊＊スレーブと、コマンド番号と、Ｒ／Ｗ
}
/***
**  ID     = I2Cstop
**  name   = I2C-Bus停止処理
**  func   = I2C-Busデバイスのストップコンディションを行う
**  called = static void I2Cstop(void);
**  io     = none
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2007/08/24 by 谷川まさや
***/
static void I2Cstop(void)
{
	SCL_L;
	SDA_L;
	I2Cwait(CYCLE);
	SCL_H;
	I2Cwait(CYCLE);
	SDA_H;
	I2Cwait(CYCLE);
}
/***
**  ID     = I2Creset
**  name   = I2C-Busリセット処理
**  func   = I2C-Busデバイスのリセットを行う（必要無し？）
**  called = static void I2Creset(void);
**  io     = none
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2007/08/24 by 谷川まさや
***/
void I2Creset(void)
{
	uchar	i;

	for (i=0; i<9; i++){
		SDA_L;
		I2Cwait(CYCLE);
		SCL_L;
		I2Cwait(CYCLE);
		SCL_H;
		I2Cwait(CYCLE);
		SDA_H;
		I2Cwait(CYCLE);
	}
}
/***
**  ID     = RTC_Reset
**  name   = RTC初期化処理
**  func   = I2C-RTCデバイスの初期化処理を行う
**  called = ubool RTC_Reset(ubool Sw);
**  io     = Sw			: ubool   : 動作モード　false = 時刻設定無し ／ true = 時刻設定有り
**  return = ubool		: 正常終了時 ＝ false ／ 異常終了 ＝ true
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2008/08/27 by 谷川まさや
***/
ubool RTC_Reset(ubool Sw)
{
    ubool    Proc    = true;
    ubool    Ret     = false;
    uchar   cError  = 0;
    uchar   Data[10];

#if true
    // ステータスレジスタ１の読み込み
    Data[0] = 0;
    I2C_RTC(RTC_READ, Data, STATUS_1, STATUS_1_LENGTH);
    // (12/24 = 1) ?
    //if((Data[0] & 0x40) == 0x40){ // 既に設定済み？
    if((Data[0] & 0x42) == 0x40){ // 既に設定済み？
        // 設定時刻の読み込み（リアルタイムデータ１）
        I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
        gtt_Calender.uc_Year_data   = ((((Data[0] & 0xf0) >> 4) * 10) + (Data[0] & 0x0f));// 年の書式変更
        gtt_Calender.uc_Month_data  = ((((Data[1] & 0x10) >> 4) * 10) + (Data[1] & 0x0f));// 月の書式変更
        gtt_Calender.uc_Day_data    = ((((Data[2] & 0x30) >> 4) * 10) + (Data[2] & 0x0f));// 日の書式変更
        gtt_Calender.uc_Hour_data   = ((((Data[4] & 0x30) >> 4) * 10) + (Data[4] & 0x0f));// 時の書式変更
        gtt_Calender.uc_Mint_data   = ((((Data[5] & 0x70) >> 4) * 10) + (Data[5] & 0x0f));// 分の書式変更
        gtt_Calender.uc_Sec_data    = ((((Data[6] & 0x70) >> 4) * 10) + (Data[6] & 0x0f));// 秒の書式変更
        // 補正処理の初期化
        RTC_Adjust(false);
    }
    else{
        while(Proc){
            // ステータスレジスタ１への書き込み(イニシャライズ：RESET=1）
            Data[0] = 0x80; // RESET=1
            I2C_RTC(RTC_WRITE, Data, STATUS_1, STATUS_1_LENGTH);
            // ステータスレジスタ１の読み込み
            Data[0] = 0;
            I2C_RTC(RTC_READ, Data, STATUS_1, STATUS_1_LENGTH);
            // (POC = 0) & (BLD = 0) ?
            if((Data[0] & 0x03) == 0x00){ // 次処理へ進む
                // 時刻設定の処理確認
                if(Sw == false) break;  // RTC初期化処理の終了
                while(true){
                    // ステータスレジスタ１への書き込み(24時間表示設定：12/24=1）
                    Data[0] = 0x60; // 12/24=1 : SC0 = 1(Debug)
                    I2C_RTC(RTC_WRITE, Data, STATUS_1, STATUS_1_LENGTH);
                    // ステータスレジスタ１の読み込み
                    Data[0] = 0;
                    I2C_RTC(RTC_READ, Data, STATUS_1, STATUS_1_LENGTH);
                    // (12/24 = 1) ?
                    if((Data[0] & 0x40) == 0x40){
                        // 時刻の初期化
                        gtt_Calender.uc_Year_data   = 8; //2008.10.30 1->8
                        gtt_Calender.uc_Month_data  = 1;
                        gtt_Calender.uc_Day_data    = 1;
                        gtt_Calender.uc_Hour_data   = 0;
                        gtt_Calender.uc_Mint_data   = 0;
                        gtt_Calender.uc_Sec_data    = 0;
                        Data[0] = (((gtt_Calender.uc_Year_data / 10) << 4) | (gtt_Calender.uc_Year_data % 10));     // 年の書式変更
                        Data[1] = (((gtt_Calender.uc_Month_data / 10) << 4) | (gtt_Calender.uc_Month_data % 10));   // 月の書式変更
                        Data[2] = (((gtt_Calender.uc_Day_data / 10) << 4) | (gtt_Calender.uc_Day_data % 10));       // 日の書式変更
                        Data[3] = 0;                                                                                // 曜日指定（未使用）
                        Data[4] = (((gtt_Calender.uc_Hour_data / 10) << 4) | (gtt_Calender.uc_Hour_data % 10));     // 時の書式変更
                        Data[5] = (((gtt_Calender.uc_Mint_data / 10) << 4) | (gtt_Calender.uc_Mint_data % 10));     // 分の書式変更
                        Data[6] = (((gtt_Calender.uc_Sec_data / 10) << 4) | (gtt_Calender.uc_Sec_data % 10));       // 秒の書式変更
                        // 時刻設定
                        I2C_RTC(RTC_WRITE, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                        // 設定時刻の読み込み（リアルタイムデータ１）
                        I2C_RTC(RTC_READ, Data, RTC_DATA_1, RTC_DATA_1_LENGTH);
                        // 設定時刻の読み込み（リアルタイムデータ２）
                        I2C_RTC(RTC_READ, Data, RTC_DATA_2, RTC_DATA_2_LENGTH);
                        // ステータスレジスタ２の読み込み
                        I2C_RTC(RTC_READ, Data, STATUS_2, STATUS_2_LENGTH);
                        // (TEST = 0) ?
                        if((Data[0] & 0x01) == 0x00){
                            Data[0] = 0;
                            // クロック補正レジスタの書き込み
                            I2C_RTC(RTC_WRITE, Data, CLOCK_ADJUST, CLOCK_ADJUST_LENGTH);
                            // 補正処理の初期化
                            RTC_Adjust(false);
                            Proc = false;   // RTC初期化処理の終了
                        }
                        else{
                            // 異常処理回数の確認
                            if(++cError >= 5){ // 5回以上正常に設定できなかった？
                                Ret  = true;    // 異常終了
                                Proc = false;   // 処理中断
                            }
                        }
                        break;  // (TEST = 1) ならもう一度、イニシャライズ処理から始める
                    }
                    else{
                        // (POC = 0) & (BLD = 0) ?
                        if(Data[0] & 0x03){
                            // 異常処理回数の確認
                            if(++cError >= 5){ // 5回以上正常に設定できなかった？
                                Ret  = true;    // 異常終了
                                Proc = false;   // 処理中断
                            }
                            break; // もう一度、イニシャライズ処理から始める
                        }
                    }
                }
            }
            // 異常処理回数の確認
            if(++cError >= 5){ // 5回以上正常に設定できなかった？
                Ret  = true;    // 異常終了
                Proc = false;   // 処理中断
                break;
            }
        }
    }
#endif
return(Ret);
}
/***
**  ID     = RTC_Adjust
**  name   = RTC補正処理
**  func   = I2C-RTCデバイスの周波数補正処理を行う
**  called = void RTC_Reset(ubool Sw);
**  io     = Sw			: ubool   : 動作モード　false = 初期化 ／ true = 通常処理
**  io     = none
**  return = none
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2008/09/01 by 谷川まさや
***/
void RTC_Adjust(ubool Sw)
{
    if(Sw){
        if(++gus_cRTC_AdjustCount >= 20){ // 1Hz×20＝２０秒相当経過した？
            uchar   Data[10];
            unsigned char   Val;

            // ステータスレジスタ２：割り込み停止
            Data[0] = 0;
            // ステータスレジスタ２の書き込み
            I2C_RTC(RTC_WRITE, Data, STATUS_2, STATUS_2_LENGTH);
            // 補正値の算出
            if(gul_vRTC_FrequencyCount > RTC_FrequencyCountModel){ // ＲＴＣの動作が遅れているとき
                Val = (char)(
                                  (((float)(gul_vRTC_FrequencyCount - RTC_FrequencyCountModel)) / RTC_FrequencyCountModel)
                                / (((float)gul_vRTC_FrequencyCount / RTC_FrequencyCountModel) * AdjustMinimumResolution)
                            );
                if(Val <= 62){
                    Data[0] = (Val & 0x7f);
                    // クロック補正レジスタの書き込み
                    I2C_RTC(RTC_WRITE, Data, CLOCK_ADJUST, CLOCK_ADJUST_LENGTH);
                }
            }
            else if(gul_vRTC_FrequencyCount < RTC_FrequencyCountModel){ // ＲＴＣの動作が進んでいるとき
                Val = (char)(
                                  (((float)(RTC_FrequencyCountModel - gul_vRTC_FrequencyCount)) / RTC_FrequencyCountModel)
                                / (((float)gul_vRTC_FrequencyCount / RTC_FrequencyCountModel) * AdjustMinimumResolution)
                            );
                if(Val <= 64){
                    Data[0] = ((128 - Val) & 0x7f);
                    // クロック補正レジスタの書き込み
                    I2C_RTC(RTC_WRITE, Data, CLOCK_ADJUST, CLOCK_ADJUST_LENGTH);
                }
            }
            // RTC周波数測定用カウンタ
            gus_cRTC_AdjustCount    = 0;
            // RTC周波数カウンタ
            gul_vRTC_FrequencyCount = 0;
            // ＩＮＴ２レジスタのアクセス：１Ｈｚ出力
            Data[0] = 0x80;
            // ＩＮＴ２レジスタのアクセスの書き込み
            I2C_RTC(RTC_WRITE, Data, RTC_INT2, RTC_INT2_LENGTH_B);
            // ステータスレジスタ２：INT2周波数設定出力許可
            Data[0] = 0x08;
            // ステータスレジスタ２の書き込み
            I2C_RTC(RTC_WRITE, Data, STATUS_2, STATUS_2_LENGTH);
            // RTC周波数測定用カウンタ
            gus_cRTC_AdjustCount    = 0;
            // RTC周波数カウンタ
            gul_vRTC_FrequencyCount = 0;
        }
    }
    else{
        uchar   Data[10];

        // RTC周波数測定用カウンタ
        gus_cRTC_AdjustCount    = 0;
        // RTC周波数カウンタ
        gul_vRTC_FrequencyCount = 0;
        // ＩＮＴ２レジスタのアクセス：１Ｈｚ出力
        Data[0] = 0x80;
        // ＩＮＴ２レジスタのアクセスの書き込み
        I2C_RTC(RTC_WRITE, Data, RTC_INT2, RTC_INT2_LENGTH_B);
        // ステータスレジスタ２：INT2周波数設定出力許可
        Data[0] = 0x08;
        // ステータスレジスタ２の書き込み
        I2C_RTC(RTC_WRITE, Data, STATUS_2, STATUS_2_LENGTH);
        // RTC周波数測定用カウンタ
        gus_cRTC_AdjustCount    = 0;
        // RTC周波数カウンタ
        gul_vRTC_FrequencyCount = 0;
    }
}
//------------------------
//  End of I2C_RTC.c
//------------------------

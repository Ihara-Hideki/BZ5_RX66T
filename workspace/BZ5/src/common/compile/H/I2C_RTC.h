//--------------------------------------------------------------------------
//
// 【ＡＺ３用】　Ｉ２Ｃ－ＲＴＣヘッダ部[I2C_RTC.h]
//
//             Original : 2008-08-27(Wed) : M.Tanigawa
//
// Copyright(C)2008 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//--------------------------------------------------------------------------
#ifndef	__I2C_RTC_H
//-------------------------------------------------
#define	__I2C_RTC_H

// 外部参照可能 define宣言
//
#define		RTC_READ			true
#define		RTC_WRITE			false
#define		RTC_RENEWAL 		0x55AA	// RTC初期化済み識別子

// ＲＴＣコマンド宣言
//
#define		STATUS_1			0x00    // ステータスレジスタ１のアクセス
#define		STATUS_2			0x01    // ステータスレジスタ２のアクセス
#define		RTC_DATA_1			0x02    // リアルタイムデータ１のアクセス
#define		RTC_DATA_2			0x03    // リアルタイムデータ２のアクセス
#define		RTC_INT1   			0x04    // ＩＮＴ１レジスタのアクセス
#define		RTC_INT2   			0x05    // ＩＮＴ２レジスタのアクセス
#define		CLOCK_ADJUST		0x06    // クロック補正レジスタのアクセス
#define		FREE        		0x07    // フリーレジスタのアクセス

// ＲＴＣコマンドに対するデータ長の宣言
//
#define		STATUS_1_LENGTH		0x01    // ステータスレジスタ１のデータ長
#define		STATUS_2_LENGTH		0x01    // ステータスレジスタ２のデータ長
#define		RTC_DATA_1_LENGTH	0x07    // リアルタイムデータ１のデータ長
#define		RTC_DATA_2_LENGTH	0x03    // リアルタイムデータ２のデータ長
#define		RTC_INT1_LENGTH_A	0x03    // ＩＮＴ１レジスタ（パターン#1）のデータ長
#define		RTC_INT1_LENGTH_B	0x01    // ＩＮＴ１レジスタ（パターン#2）のデータ長
#define		RTC_INT2_LENGTH_A	0x03    // ＩＮＴ２レジスタ（パターン#1）のデータ長
#define		RTC_INT2_LENGTH_B	0x01    // ＩＮＴ２レジスタ（パターン#2）のデータ長
#define		CLOCK_ADJUST_LENGTH	0x01    // クロック補正レジスタのデータ長
#define		FREE_LENGTH       	0x01    // フリーレジスタのデータ長

// ＲＴＣ補正用データ宣言
//
#define     RTC_FrequencyCountModel 200000      // 目標発信周波数カウンタ値：１Ｈｚ×２０＝２０秒
#define     AdjustMinimumResolution 0.000003052 // 最小分解能：３．０５２ppm(10^-6)

// 外部参照可能モジュール宣言
//
#ifdef	__I2C_RTC_PROG
    ubool RTC_Reset(ubool Sw);
	void I2Creset();
    void RTC_Adjust(ubool Sw);
	void I2C_RTC(ubool Sw, uchar *MemAddress, uchar RTC_Command, ushort Length);
#else
    extern ubool RTC_Reset(ubool Sw);
	extern void I2Creset();
    extern void RTC_Adjust(ubool Sw);
	extern void I2C_RTC(ubool Sw, uchar *MemAddress, uchar RTC_Command, ushort Length);
#endif
//-------------------------------------------------
#endif	// __I2C_RTC_H
//------------------------
//  End of I2C_RTC.h
//------------------------

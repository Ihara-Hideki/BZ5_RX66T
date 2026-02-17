//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　ｆｐｇａ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－１
//  【ヘッダ説明】
//      ＦＰＧＡ関連定義
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#ifndef	__FPGA_H
//-------------------------------------------------
#define	__FPGA_H

// 使用変数の宣言(実体宣言用or外部参照用)
#ifdef __FPGA_PROG
	// 使用変数実体宣言部
	//
	uchar			*pFPGA_PROG;
	ushort			*pFPGA_CTRL;
	volatile ushort	*pFIFO_AMP;
	volatile ushort	*pFIFO_VOLT;
	volatile ushort	*pFIFO_CTL;
	volatile ushort	*pDATSAMPLINGTIME;
#else
	// 外部参照可能モジュール宣言部
	//
	extern int	initFPGA(void);					// ＦＰＧＡ初期化処理
	extern void fpgaFifoInit(int Time);			// FPGA-FIFO 初期化処理
	extern void fpgaErrorReset(void);			// FPGA-FIFO エラーリセット処理
	extern int	ReadAmpFifo(ushort *pData);		// FPGA-FIFO 電流FIFO リード処理
	extern int	ReadVoltFifo(ushort *pData);	// FPGA-FIFO 電圧FIFO リード処理

	// 外部参照可能変数宣言部
	//
	extern uchar			*pFPGA_PROG;
	extern ushort 			*pFPGA_CTRL;
	extern volatile ushort	*pFIFO_AMP;
	extern volatile ushort	*pFIFO_VOLT;
	extern volatile ushort	*pFIFO_CTL;
	extern volatile ushort	*pDATSAMPLINGTIME;
#endif

//-------------------------------------------------
#endif	// __FPGA_H
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of fpga.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

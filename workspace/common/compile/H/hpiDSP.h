//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　ｈｐｉＤＳＰ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－１
//  【ヘッダ説明】
//      ＤＳＰ－ＨＰＩ制御定義
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#ifndef	__HPI_DSP_H
//-------------------------------------------------
#define	__HPI_DSP_H

#define     WLDADJST_1LEN     126                       // 半固定パラメータの長さ：１２６Ｗ
#define     WLDADJST_2LEN     ( WLDADJST_1LEN * 2 )     // ２５２Ｗ
#define     WLDADJST_3LEN     ( WLDADJST_1LEN * 3 )     // ３７８Ｗ 2007.2.13追加

//*** 可変パラメータ３２追加 2008.09.03 ***
#define     CALPARM_1LEN            64
#define     CALPARM_2LEN            32
#define     CALPARM_CNT             ( CALPARM_1LEN + CALPARM_2LEN )


/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      Ｉ／Ｆタスク  電源投入時用                                          */
/*  [データ説明]                                                            */
/*      usint       WldParm[ 100 ]          溶接固定パラメータ              */
/*      usint       SrvParm[ 100 ]          サーボ固定パラメータ            */
/*--------------------------------------------------------------------------*/
typedef struct
{
    usint   WldParm[ 100 ];
    usint   SrvParm[ 100 ];
}INIT , *PINIT;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      Ｉ／Ｆタスク  計算用                                                */
/*  [データ説明]                                                            */
/*      float   a                                                           */
/*      float   b                                                           */
/*      float   c                                                           */
/*      float   min         最小値                                          */
/*      float   max         最大値                                          */
/*--------------------------------------------------------------------------*/
typedef struct
{
    float   a;
    float   b;
    float   c;
    float   min;
    float   max;
}CALPARM , *PCALPARM;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*     Ｉ／Ｆタスク  通常処理用                                             */
/*  [データ説明]                                                            */
/*      usint   WeldParm_Abs[  ]        半固定パラメータ（絶対値）          */
/*      usint   WeldParm_Rel[  ]        半固定パラメータ（相対値）          */
/*      CALPARM CalParm[  ]             可変パラメータ                      */
/*      float   CalOffset[  ]           可変パラメータ C値オフセット        */
/*--------------------------------------------------------------------------*/
typedef struct
{
    //usint   WeldParm_Abs[ WLDADJST_2LEN ];    // 126→252Wに変更  2004. 9.29
    //usint   WeldParm_Rel[ WLDADJST_2LEN ];
    //usint   WeldParm_Wrk[ WLDADJST_2LEN ];
    usint   WeldParm_Abs[ WLDADJST_3LEN ];    // 126→378Wに変更  2007.2.13
    usint   WeldParm_Rel[ WLDADJST_3LEN ];
    usint   WeldParm_Wrk[ WLDADJST_3LEN ];
    //CALPARM CalParm[ 70 ];
    //float   CalOffset[ 70 ];        // 2004.09.13

    //*** 可変パラメータ３２追加 2008.09.03 ***
    CALPARM CalParm[ CALPARM_CNT ];
    float   CalOffset[ CALPARM_CNT ];

}NORMAL,*PNORMAL;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      Ｉ／Ｆタスク用データ（電源投入時/通常処理）                         */
/*  [データ説明]                                                            */
/*       INIT       Init        電源投入時                                  */
/*       NORMAL     Nrm         通常処理                                    */
/*--------------------------------------------------------------------------*/
typedef union
{
    INIT    Init;
    NORMAL  Nrm;
}UNIONDATA,*PUNIONDATA;

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      Ｉ／Ｆタスク用制御データ                                            */
/*  [データ説明]                                                            */
/*      char        SrvStatus       サーボ状態                              */
/*                                  ０＝サーボOFF                           */
/*                                  １＝サーボON中(サーボONタスク起動中)    */
/*                                  ２＝サーボON完了                        */
/*      char        WeldStatus      溶接状態                                */
/*                                  ０＝溶接していない                      */
/*                                  １＝スローダウン中                      */
/*                                  ２＝本溶接中                            */
/*      char        MotorStatus     送給状態                                */
/*                                  ０＝送給しいない                        */
/*                                  １＝スローダウン中                      */
/*                                  ２＝送給中                              */
/*--------------------------------------------------------------------------*/
typedef struct
{
    char    SrvStatus;
    char    WeldStatus;
    char    MotorStatus;
    char    Dmy;
}IFCTL , *PIFCTL;

#ifdef __HPI_DSP_PROG
// 使用変数の宣言(実体宣言用or外部参照用)
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ＤＰＲＡＭ（ＤＳＰ）                                                */
/*--------------------------------------------------------------------------*/
#define     IF_WELDCMD          0x00000080  //I/FCPU→DSP溶接コマンド領域
#define     DSP_WELDCMD         0x00000100  //DPS→I/FCPU溶接コマンド領域
#define     IF_SRVCMD           0x00000180  //I/FCPU→DSPサーボコマンド領域
#define     DSP_SRVCMD          0x00000188  //DPS→I/FCPUサーボコマンド領域
#define     SRVSPDCOND          0x00000190  //サーボ速度指令
#define     WELDOUTSTS          0x00000198  //溶接出力状態
#define     SRVPLSCNT           0x000001A0  //サーボパルスカウンタ/モータ電流
#define     WCONDFLAG           0x000001A8  //溶接条件指令：有効バッファ番号
#define     WELDCOND_0          0x000001A9  //溶接条件指令(０番)
#define     WELDCOND_1          0x000001E9  //溶接条件指令(１番)


#define     WELDCOND_2_0        0x00000229  //溶接条件指令２(０番) 2008.09.03
#define     WELDCOND_2_1        0x00000249  //溶接条件指令２(１番) 2008.09.03

	// 使用変数実体宣言部
	//
//#ifdef __HPI_DSP_PROG
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ｈｐｉ（ＤＳＰ）ドライバ                                            */
/*  [使用状況]                                                              */
/*      静的        電源投入時から                                          */
/*--------------------------------------------------------------------------*/
	uchar	hpiFlag;	// ＨＰＩドライバＯｐｅｎフラグ
						//  ０＝初期状態（ リセット前 ）
						//  １＝リセット後（DSP-WDG無効区間）
						//  ２＝ＤＳＰ初期化完了受信後（DSP-WDG有効区間）
	ushort	hpiIntrWork[ 128 ];
	int		isCD;		// ０＝トーチＯＮ後、一度も電流検出なし
	int		isCD_bkup;	// 2006.2.8 ihara
/*--------------------------------------------------------------------------*/
/*  [データ説明]                                                            */
/*      usint   OUTPUT                  出力状態（現在状態）                */
/*                                          d7､d8=未使用                    */
/*                                          d5=ガスバルブ１,d4=ガスバルブ２ */
/*                                          d3=未使用      ,d2=主電源制御   */
/*                                          d1=プッシュプル１,d0=プッシュプル２ */
/*      usint   WLDPWR                  溶接電源動作指令(現在状態)          */
/*                                          d0:溶接起動指令                 */
/*                                          d1:リフトアップEI/DI            */
/*      usint   WLDPWR_Old              溶接電源動作指令(前回状態)          */
/*      usint   WLDINERR                溶接異常検出                        */
/*                                          d0:アーク                       */
/*                                          d1:スティック                   */
/*      usint   WLDINPWRERR             溶接電源異常検出                    */
/*                                          d1:2次過電流異常                */
/*      usint   WLDINCUR                溶接電流検出                        */
/*                                          d0:電流検出                     */
/*                                          d1:リフトアップ                 */
/*                                          d1:リフトダウン                 */
/*      usint   SRVPWR                  サーボ電源                          */
/*                                          d0:サーボ                       */
/*      usint   SRVCTL                  サーボ制御指令(現在状態)            */
/*                                          d0:モータ回転                   */
/*                                          d1:モータ回転方向               */
/*      usint   SRVCTL_Old              サーボ制御指令(前回状態)            */
/*      usint   SRVFEADBACK             サーボフィードバック                */
/*                                          d0:サーボ                       */
/*                                          d1:モータ                       */
/*      usint   SRVINERR                サーボエラー（エラーコード格納)     */
/*      usint   INB                     今回周辺入力状態(チャタリング)      */
/*      usint   IOB1                    前回周辺入力状態(チャタリング)      */
/*      usint   IOB2                    前々回周辺入力状態(チャタリング)    */
/*                                        d0:サーマル１                     */
/*                                        d1:サーマル２                     */
/*                                        d2:１次過電圧                     */
/*                                        d3:欠相異常                       */
/*                                        d15:ＰＲＳＴ                      */
/*      usint   INB_Old                 チャタリング結果(前回)              */
/*      usint   wspdBuff[ 8 ]           DSP送信用バッファ(サーボ速度制御)   */
/*      usint   wcondBuff[ 64 ]         DSP送信用バッファ(溶接制御タスク)   */
/*                                      ★初期化時にエラー&バージョン情報を送信するのに使う*/
/*      usint   CONDAMP                 電流指令値                          */
/*      usint   CONDVOLT                電圧指令値                          */
/*      usint   CONDWELDSPD             溶接速度                            */
/*      usint   CONDWIRESPD             ワイヤ速度指令                      */
/*      sint    Adjust_A                電流補正値                          */
/*      sint    Adjust_V                電圧補正値                          */
/*      usint   CmdData_26[ 10 ]        溶接設定データ１                    */
/*      usint   WELDSEQ1                溶接シーケンス１                    */
/*      usint   MAIN_POWER              主電源制御                          */
/*--------------------------------------------------------------------------*/
	ushort	OUTPUT;
	ushort	WLDPWR;
	ushort	WLDPWR_Old;
	ushort	WLDINERR;
	ushort	WLDINPWRERR;
	ushort	WLDINCUR;
	ushort	SRVPWR;
	ushort	SRVCTL;
	ushort	SRVCTL_Old;
	ushort	SRVFEADBACK;
	ushort	SRVINERR;
	ushort	INB;
	ushort	IOB1;
	ushort	IOB2;
	ushort	INB_Old;
// @-R040301RTW <ALT1> 2004.07.05 溶接データ記録コマンド62h受信領域
	ushort	QualityMonCond[ 27 ];   // 品質モニタ条件ラッチデータ
	ushort	WLDRECDATA[ 8 ];        // 溶接データ記録ラッチデータ
	ushort	CONDAMP;
	ushort	CONDVOLT;
	ushort	CONDWELDSPD;
	ushort	CONDWIRESPD;
	short	Adjust_A;
	short	Adjust_V;
	ushort	CmdData_26[ 10 ];       // 溶接設定データ１
	ushort	WELDSEQ1;
	ushort	MAIN_POWER;
	ushort	LastSend_11;

	// 外部参照可能モジュール宣言部
	extern void		_hpiClearHINT(void);
	extern void		_hpiSetAddress(long dspPtr);
	extern ushort	_hpiGet(void);
	extern usint	_hpiGet_Next(void);
	extern void		_hpiPut(usint Data);
	extern void		_hpiPut_Next(usint Data);
	extern void		_hpiRead(pusint pRec , int Cnt);
	extern usint	_hpiRead_sum(pusint pRec , int Cnt);
	extern void		_hpiWrite(pusint pRec , int Cnt);
	extern void		_hpiWrite_Next(pusint pRec , int Cnt);
	extern usint	_hpiWrite_Next_sum(pusint pRec , int Cnt);
	extern int		get_imask(void);
	//
//	extern void		asnsCD(void);
#else
	extern ushort	OUTPUT;
	extern ushort	WLDPWR;
	extern ushort	WLDPWR_Old;
	extern ushort	WLDINERR;
	extern ushort	WLDINPWRERR;
	extern ushort	WLDINCUR;
	extern ushort	SRVPWR;
	extern ushort	SRVCTL;
	extern ushort	SRVCTL_Old;
	extern ushort	SRVFEADBACK;
	extern ushort	SRVINERR;
	extern ushort	INB;
	extern ushort	IOB1;
	extern ushort	IOB2;
	extern ushort	INB_Old;
	extern ushort	QualityMonCond[ 27 ];   // 品質モニタ条件ラッチデータ
	extern ushort	WLDRECDATA[ 8 ];        // 溶接データ記録ラッチデータ
	extern ushort	CONDAMP;
	extern ushort	CONDVOLT;
	extern ushort	CONDWELDSPD;
	extern ushort	CONDWIRESPD;
	extern short	Adjust_A;
	extern short	Adjust_V;
	extern ushort	CmdData_26[ 10 ];       // 溶接設定データ１
	extern ushort	WELDSEQ1;
	extern ushort	MAIN_POWER;
	extern ushort	LastSend_11;

	extern void		_hpiClearHINT(void);
	extern void		_hpiSetAddress(long dspPtr);
	extern ushort	_hpiGet(void);
	extern usint	_hpiGet_Next(void);
	extern void		_hpiPut(usint Data);
	extern void		_hpiPut_Next(usint Data);
	extern void		_hpiRead(pusint pRec , int Cnt);
	extern usint	_hpiRead_sum(pusint pRec , int Cnt);
	extern void		_hpiWrite(pusint pRec , int Cnt);
	extern void		_hpiWrite_Next(pusint pRec , int Cnt);
	extern usint	_hpiWrite_Next_sum(pusint pRec , int Cnt);
	extern int		get_imask(void);
	// 外部参照可能モジュール宣言部
	//
	extern void	hpiOpen(void);							// ＨＰＩドライバのＯｐｅｎ処理
	extern int	hpiInit(void);							// ＨＰＩ－ＤＰＲのクリア処理
	extern int	hpiDownLoad(void);						// ＤＳＰプログラムのダウンロード処理
	extern void	hpiBoot(void);							// ＤＳＰプログラムのブート処理
	extern void hpiWrite(int CmdNo , pusint pRec);		// コマンド領域にデータを書き込む
	extern void hpiStsWrite(int StsNo , pusint pRec);	// ステータス領域にデータを書き込む
	extern void hpiStsRead(int StsNo , pusint pRec);	// ステータス領域からデータを読み込む
	extern void hpiWcondWrite(pusint pRec);				// 溶接条件専用書込み
	extern void hpiIntr(void);							// 受信割込み：エントリ

	// 外部参照可能変数宣言部
	//
        extern  UNIONDATA   _union;
	extern  PWELDTABLE  pWT;

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ｈｐｉ（ＤＳＰ）ドライバ                                            */
/*  [使用状況]                                                              */
/*      静的        電源投入時から                                          */
/*--------------------------------------------------------------------------*/
	extern uchar	hpiFlag;		// ＨＰＩドライバＯｐｅｎフラグ
									//  ０＝初期状態（ リセット前 ）
									//  １＝リセット後（DSP-WDG無効区間）
									//  ２＝ＤＳＰ初期化完了受信後（DSP-WDG有効区間）
	extern ushort	hpiIntrWork[ 128 ];
	extern int	isCD;				// ０＝トーチＯＮ後、一度も電流検出なし
	extern int	isCD_bkup;			// 2006.2.8

/*--------------------------------------------------------------------------*/
/*  [データ説明]                                                            */
/*      usint   OUTPUT                  出力状態（現在状態）                */
/*                                          d7､d8=未使用                    */
/*                                          d5=ガスバルブ１,d4=ガスバルブ２ */
/*                                          d3=未使用      ,d2=主電源制御   */
/*                                          d1=プッシュプル１,d0=プッシュプル２ */
/*      usint   WLDPWR                  溶接電源動作指令(現在状態)          */
/*                                          d0:溶接起動指令                 */
/*                                          d1:リフトアップEI/DI            */
/*      usint   WLDPWR_Old              溶接電源動作指令(前回状態)          */
/*      usint   WLDINERR                溶接異常検出                        */
/*                                          d0:アーク                       */
/*                                          d1:スティック                   */
/*      usint   WLDINPWRERR             溶接電源異常検出                    */
/*                                          d1:2次過電流異常                */
/*      usint   WLDINCUR                溶接電流検出                        */
/*                                          d0:電流検出                     */
/*                                          d1:リフトアップ                 */
/*                                          d1:リフトダウン                 */
/*      usint   SRVPWR                  サーボ電源                          */
/*                                          d0:サーボ                       */
/*      usint   SRVCTL                  サーボ制御指令(現在状態)            */
/*                                          d0:モータ回転                   */
/*                                          d1:モータ回転方向               */
/*      usint   SRVCTL_Old              サーボ制御指令(前回状態)            */
/*      usint   SRVFEADBACK             サーボフィードバック                */
/*                                          d0:サーボ                       */
/*                                          d1:モータ                       */
/*      usint   SRVINERR                サーボエラー（エラーコード格納)     */
/*      usint   INB                     今回周辺入力状態(チャタリング)      */
/*      usint   IOB1                    前回周辺入力状態(チャタリング)      */
/*      usint   IOB2                    前々回周辺入力状態(チャタリング)    */
/*                                        d0:サーマル１                     */
/*                                        d1:サーマル２                     */
/*                                        d2:１次過電圧                     */
/*                                        d3:欠相異常                       */
/*                                        d15:ＰＲＳＴ                      */
/*      usint   INB_Old                 チャタリング結果(前回)              */
/*      usint   wspdBuff[ 8 ]           DSP送信用バッファ(サーボ速度制御)   */
/*      usint   wcondBuff[ 64 ]         DSP送信用バッファ(溶接制御タスク)   */
/*                                      ★初期化時にエラー&バージョン情報を送信するのに使う*/
/*      usint   CONDAMP                 電流指令値                          */
/*      usint   CONDVOLT                電圧指令値                          */
/*      usint   CONDWELDSPD             溶接速度                            */
/*      usint   CONDWIRESPD             ワイヤ速度指令                      */
/*      sint    Adjust_A                電流補正値                          */
/*      sint    Adjust_V                電圧補正値                          */
/*      usint   CmdData_26[ 10 ]        溶接設定データ１                    */
/*      usint   WELDSEQ1                溶接シーケンス１                    */
/*      usint   MAIN_POWER              主電源制御                          */
/*--------------------------------------------------------------------------*/
#if 0
	extern ushort	OUTPUT;
	extern ushort	WLDPWR;
	extern ushort	WLDPWR_Old;
	extern ushort	WLDINERR;
	extern ushort	WLDINPWRERR;
	extern ushort	WLDINCUR;
	extern ushort	SRVPWR;
	extern ushort	SRVCTL;
	extern ushort	SRVCTL_Old;
	extern ushort	SRVFEADBACK;
	extern ushort	SRVINERR;
	extern ushort	INB;
	extern ushort	IOB1;
	extern ushort	IOB2;
	extern ushort	INB_Old;
// @-R040301RTW <ALT1> 2004.07.05 溶接データ記録コマンド62h受信領域
	extern ushort	QualityMonCond[ 27 ];   // 品質モニタ条件ラッチデータ
	extern ushort	WLDRECDATA[ 8 ];        // 溶接データ記録ラッチデータ
	extern ushort	CONDAMP;
	extern ushort	CONDVOLT;
	extern ushort	CONDWELDSPD;
	extern ushort	CONDWIRESPD;
	extern short	Adjust_A;
	extern short	Adjust_V;
	extern ushort	CmdData_26[ 10 ];       // 溶接設定データ１
	extern ushort	WELDSEQ1;
	extern ushort	MAIN_POWER;
	extern ushort	LastSend_11;

	extern  usint   SAMPLING_M;     //溶接データ記録：マクロ周期／５０
	extern  usint   SAMPLING_N;     //品質モニタ：平均化時間／５０
	extern  usint   SAMPLING_L;     //溶接データ記録：マクロ周期（１秒間の移動積算回数）

#endif

#endif

//-------------------------------------------------
#endif	// __HPI_DSP_H
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of hpiDSP.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

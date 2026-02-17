//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　ｉｎｏｕｔ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－１
//  【ヘッダ説明】
//      入出力定義
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
int     Input( void );
//void    Output( usint Status , int MainPower , int _15V );
void    _200VOut( int OnOff );
//void    Output_P9( int Status );

#if 0
typedef struct {
		char	b0:1;
		char	b1:1;
		char	b2:1;
		char	b3:1;
		char	b4:1;
		char	b5:1;
		char	b6:1;
		char	b7:1;
}bit_def;
typedef union {
	char	byte;
	bit_def bit;
} byte_def;
#endif
/*------------------------------------------------------
	Port P0 register
------------------------------------------------------*/
#define		p6_0			(*p6).Bit1Sw.b7			/* Port P6_0 register */
#define		p6_1			(*p6).Bit1Sw.b6			/* Port P6_1 register */
#define		p6_2			(*p6).Bit1Sw.b5			/* Port P6_2 register */
#define		p6_3			(*p6).Bit1Sw.b4			/* Port P6_3 register */
#define		p6_4			(*p6).Bit1Sw.b3			/* Port P6_4 register */
#define		p6_5			(*p6).Bit1Sw.b2			/* Port P6_5 register */
#define		p6_6			(*p6).Bit1Sw.b1			/* Port P6_6 register */
#define		p6_7			(*p6).Bit1Sw.b0			/* Port P6_7 register */

#define		p9_0			(*p9).Bit1Sw.b7			/* Port P9_0 register */
#define		p9_1			(*p9).Bit1Sw.b6			/* Port P9_1 register */
#define		p9_2			(*p9).Bit1Sw.b5			/* Port P9_2 register */
#define		p9_3			(*p9).Bit1Sw.b4			/* Port P9_3 register */
#define		p9_4			(*p9).Bit1Sw.b3			/* Port P9_4 register */
#define		p9_5			(*p9).Bit1Sw.b2			/* Port P9_5 register */
#define		p9_6			(*p9).Bit1Sw.b1			/* Port P9_6 register */
#define		p9_7			(*p9).Bit1Sw.b0			/* Port P9_7 register */

#define		p10_0			(*p10).Bit1Sw.b7		/* Port P10_0 register */
#define		p10_1			(*p10).Bit1Sw.b6		/* Port P10_1 register */
#define		p10_2			(*p10).Bit1Sw.b5		/* Port P10_2 register */
#define		p10_3			(*p10).Bit1Sw.b4		/* Port P10_3 register */
#define		p10_4			(*p10).Bit1Sw.b3		/* Port P10_4 register */
#define		p10_5			(*p10).Bit1Sw.b2		/* Port P10_5 register */
#define		p10_6			(*p10).Bit1Sw.b1		/* Port P10_6 register */
#define		p10_7			(*p10).Bit1Sw.b0		/* Port P10_7 register */

#define		p11_0			(*p11).Bit1Sw.b7		/* Port P11_0 register */
#define		p11_1			(*p11).Bit1Sw.b6		/* Port P11_1 register */
#define		p11_2			(*p11).Bit1Sw.b5		/* Port P11_2 register */
#define		p11_3			(*p11).Bit1Sw.b4		/* Port P11_3 register */
#define		p11_4			(*p11).Bit1Sw.b3		/* Port P11_4 register */
#define		p11_5			(*p11).Bit1Sw.b2		/* Port P11_5 register */
#define		p11_6			(*p11).Bit1Sw.b1		/* Port P11_6 register */
#define		p11_7			(*p11).Bit1Sw.b0		/* Port P11_7 register */

#define		p13_0			(*p13).Bit1Sw.b7		/* Port P13_0 register */
#define		p13_1			(*p13).Bit1Sw.b6		/* Port P13_1 register */
#define		p13_2			(*p13).Bit1Sw.b5		/* Port P13_2 register */
#define		p13_3			(*p13).Bit1Sw.b4		/* Port P13_3 register */
#define		p13_4			(*p13).Bit1Sw.b3		/* Port P13_4 register */
#define		p13_5			(*p13).Bit1Sw.b2		/* Port P13_5 register */
#define		p13_6			(*p13).Bit1Sw.b1		/* Port P13_6 register */
#define		p13_7			(*p13).Bit1Sw.b0		/* Port P13_7 register */

#define		p22_0			(*p22).Bit1Sw.b7		/* Port P13_0 register */
#define		p22_1			(*p22).Bit1Sw.b6		/* Port P13_1 register */
#define		p22_2			(*p22).Bit1Sw.b5		/* Port P13_2 register */
#define		p22_3			(*p22).Bit1Sw.b4		/* Port P13_3 register */
#define		p22_4			(*p22).Bit1Sw.b3		/* Port P13_4 register */
#define		p22_5			(*p22).Bit1Sw.b2		/* Port P13_5 register */
#define		p22_6			(*p22).Bit1Sw.b1		/* Port P13_6 register */
#define		p22_7			(*p22).Bit1Sw.b0		/* Port P13_7 register */

#define GZ3_NEW 0
#define GZ3_NEW_NEW 1

#if GZ3_NEW

#define         THP                     p6_1        
#define         TS                      p6_2           /*トーチＳＷ*/
#define         GAS                     p9_5         /*ガス起動*/
#define         FAN                     p9_6         /*ファン１起動*/
#define         MG_SW                   p9_7         /*ＭＳ*/
#define         LED4                    p10_7         
#define         LED5                    p11_2        
#define         LED10                   p22_4        

#endif


#if GZ3_NEW_NEW
//入力
#define         THP                     p13_0        //サーマルＳＷ
#define         EMG                     p13_1        //非常停止
#define         OUT_SIDE1               p13_3        //一時停止１ 2009.09.29 OUT_SIDE2とポート入れ替え
#define         OUT_SIDE2               p13_2        //一時停止２ 2009.09.29 OUT_SIDE1とポート入れ替え
//#define         TS                      p13_4        //トーチＳＷ
#define         TS                      p22_1        //トーチＳＷ 2008.08.27変更
//#define         INCHING                 p13_5        //インチングＳＷ ハードウェアによるインチングは無くなったので削除 2008.09.11
#define         EMG2                    p6_2         //非常停止２ 2007.2.9
//出力
#define         GAS                     p10_0        //ガス起動
//#define         FAN1                    p10_1        //ファン１起動
//#define         FAN2                    p10_5        //ファン２起動
//#define         FAN1                    p10_5        //ファン１起動 2009.02.05
//#define         FAN2                    p10_1        //ファン２起動 2009.02.05
//#define         FAN1                    p10_1        //ファン１起動 2010.01.14
#define         FAN2                    p10_1        //ファン２起動 2012.02.08　ポート変更p9_6->p10_1＋FAN1制御中止
//#define         FAN2                    p9_6        //ファン２起動 2010.01.14
#define         CD_OUT                  p10_2        //電検外部出力
#define         ERR_OUT                 p10_3        //エラー外部出力
#define         ALRM_OUT                p10_4        //アラーム外部出力
#define         PLS_OUT                 p10_5        //パルス出力 2009.03.17
//#define         MG_SW                   p9_6        //ＭＳ
//#define         START1                  p9_6         //コンデンサ放電リレー 2008.09.11
//#define         START2                  p22_0        //コンデンサ充電リレー 2008.09.11

//#define         START2                  p9_6         //コンデンサ放電リレー 2008.09.12 ポート入れ替え（タナカさん要請分）
//#define         START1                  p22_0        //コンデンサ充電リレー 2008.09.12 ポート入れ替え（タナカさん要請分）

//2009.01.28
//#define         START1                  p9_6         //コンデンサ放電リレー 2008.09.12 ポート入れ替え（タナカさん要請分） 2010.01.18 del
//#define         START2                  p22_0        //コンデンサ充電リレー 2008.09.12 ポート入れ替え（タナカさん要請分）
#define         HF_OUT                  p22_0        //高周波出力ポート 2009.01.31



#define         LED4                    p9_5         
#define         LED5                    p11_2        
#define         LED10                   p22_4        

#endif

//<><><><><><><><><><> ＩＯポート設定 <><><><><><><><><><> 2019.05.29
//input
#define	TS1			GPIO.PPR1 & 0x0001
#define	TS2			GPIO.PPR1 & 0x0002

//output
#define HF_ON			GPIO.P1 |=  0x0008
#define HF_OFF			GPIO.P1 &= ~0x0008

#define HF_CTRL_ON		GPIO.P2 |=  0x0010
#define HF_CTRL_OFF		GPIO.P2 &= ~0x0010

//2019.07.03
#define MS_ON			GPIO.P2 |=  0x0008
#define MS_OFF			GPIO.P2 &= ~0x0008

#define GAS_ON			GPIO.P1 |=  0x0040
#define GAS_OFF			GPIO.P1 &= ~0x0040



//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><><><><><><> ＤＰ　ＲＡＭ設定 <><><><><><><><><><>　2019.05.29
//RZ->C28
#define	PRE_CURR_DATA		10	//溶接電流指令値
#define INVERTER_CTRL1		11	//溶接起動信号1
#define INVERTER_CTRL2		12	//溶接起動信号2
#define SEQUENCE_NO			13	//シーケンス番号
#define PULSE_15KHZ			14	//１５ｋＨｚパルス起動信号
#define EN_EP_START			15	//ＥＮ／ＥＰスタート信号
#define HOT_CURR_DATA		16	//ホット電流値指令値
#define AC_FRQ_DATA			17	//交流周波数
#define FAN1				18	//ファン１
#define FAN2				19	//ファン２
#define FAN3				20	//ファン３
#define FAN4				21	//ファン４
#define FAN5				22	//ファン５
#define FAN6				23	//ファン６
#define SP	                24	//重畳起動信号
#define P_GAIN_DATA			25	//比例ゲイン
#define I_GAIN_DATA         26	//積分ゲイン
#define D_GAIN_DATA         27	//微分ゲイン
#define DC_AC_CTRL			28	//ＤＣ溶接、ＡＣ溶接の指示 2019.06.13
#define EP_RATIO			29	//EP比率　クリーニング幅   2019.06.13

#define AC_WAVE_DATA		100	//交流波形データ

//C28->RZ
#define CURR_FB_DATA		10	//溶接電流ＦＢデータ
#define CURR_FB_HP_DATA	    11	//高精度溶接電流ＦＢデータ　High precision（高精度）
#define VOLT_FB_DATA		12	//溶接電圧ＦＢデータ
#define PRI_VOLT1_DATA		13	//一次電圧１
#define PRI_VOLT2_DATA		14	//一次電圧２
#define PRI_VOLT3_DATA		15	//一次電圧３
#define THERMAL1_DATA		16	//サーマル１
#define THERMAL2_DATA		17	//サーマル２
#define THERMAL3_DATA		18	//サーマル３
#define HD_CD				19	//ハード電検

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>




//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of inout.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

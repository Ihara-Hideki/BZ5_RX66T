//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｉ＿ｉｏ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      Ｉ／Ｏ初期化
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
//#include  "custom.h"
#include "iodefine.h"
#include "devdrv_bsc.h"
#include "rza_io_regrw.h"




#define BIT0_SET (0x0001)
#define BIT0_CLR (~0x0001)

#define BIT1_SET (0x0002)
#define BIT1_CLR (~0x0002)

#define BIT2_SET (0x0004)
#define BIT2_CLR (~0x0004)

#define BIT3_SET (0x0008)
#define BIT3_CLR (~0x0008)

#define BIT4_SET (0x0010)
#define BIT4_CLR (~0x0010)

#define BIT5_SET (0x0020)
#define BIT5_CLR (~0x0020)

#define BIT6_SET (0x0040)
#define BIT6_CLR (~0x0040)

#define BIT7_SET (0x0080)
#define BIT7_CLR (~0x0080)

#define BIT8_SET (0x0100)
#define BIT8_CLR (~0x0100)

#define BIT9_SET (0x0200)
#define BIT9_CLR (~0x0200)

#define BIT10_SET (0x0400)
#define BIT10_CLR (~0x0400)

#define BIT11_SET (0x0800)
#define BIT11_CLR (~0x0800)

#define BIT12_SET (0x1000)
#define BIT12_CLR (~0x1000)

#define BIT13_SET (0x2000)
#define BIT13_CLR (~0x2000)

#define BIT14_SET (0x4000)
#define BIT14_CLR (~0x4000)

#define BIT15_SET (0x8000)
#define BIT15_CLR (~0x8000)

void ini_io_class(void)
{

	//*********** ポート設定 **********
	//port0
		//初期化
                GPIO.PIBC0 = 0x0000;
                //GPIO.PBDC0 = 0x0000;
		//GPIO.PM0   = 0xffff;
		GPIO.PMC0  = 0x0000;
		//GPIO.PIPC0 = 0x0000;
                //ポートモードレジスタ	0:出力 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      0      0      0      0      0      0      0      0      0      0      0      1      1      1      1
		//GPIO.PM0	 = 0x000f;
		//GPIO.PBDC0 = 0x000f;
		//ポートモード制御レジスタ   0:ポートモード 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0
		//         -      -      -      -      -      -      -      -      -      -      -      -      in     in     in     in
		//port00
		//入力モード
		GPIO.PIBC0 = 0x000f;
		

	//port1
		//初期化
                GPIO.PIBC1 = 0x0000;
                GPIO.PBDC1 = 0x0000;
		GPIO.PM1   = 0xffff;
		GPIO.PMC1  = 0x0000;
		GPIO.PIPC1 = 0x0000;

		//設定
                //ポートモードレジスタ	0:出力 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         1      1      1      1      1      1      1      1      0      0      0      0      0      1      1      1
		
		//ポートモード制御レジスタ   0:ポートモード 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   0      1      1      1      1      1      0      0      0      0      0      0      0      0      0      0
		//         in     AN6    AN5    AN4    AN3    AN2    in     in     out    out    out    out    out    in     in     in

		//port10  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC10_SHIFT,   GPIO_PBDC1_PBDC10);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC10_SHIFT,     GPIO_PFC1_PFC10);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE10_SHIFT,   GPIO_PFCE1_PFCE10);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE10_SHIFT, GPIO_PFCAE1_PFCAE10);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC10_SHIFT,   GPIO_PIPC1_PIPC10);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC10_SHIFT,     GPIO_PMC1_PMC10);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM10_SHIFT,       GPIO_PM1_PM10);
    		RZA_IO_RegWrite_16(&GPIO.PIBC1,  1, GPIO_PIBC1_PIBC10_SHIFT,   GPIO_PIBC1_PIBC10);
	        
		//port11  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC11_SHIFT,   GPIO_PBDC1_PBDC11);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC11_SHIFT,     GPIO_PFC1_PFC11);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE11_SHIFT,   GPIO_PFCE1_PFCE11);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE11_SHIFT, GPIO_PFCAE1_PFCAE11);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC11_SHIFT,   GPIO_PIPC1_PIPC11);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC11_SHIFT,     GPIO_PMC1_PMC11);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM11_SHIFT,       GPIO_PM1_PM11);
    		RZA_IO_RegWrite_16(&GPIO.PIBC1,  1, GPIO_PIBC1_PIBC11_SHIFT,   GPIO_PIBC1_PIBC11);

		//port12  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC12_SHIFT,   GPIO_PBDC1_PBDC12);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC12_SHIFT,     GPIO_PFC1_PFC12);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE12_SHIFT,   GPIO_PFCE1_PFCE12);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE12_SHIFT, GPIO_PFCAE1_PFCAE12);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC12_SHIFT,   GPIO_PIPC1_PIPC12);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC12_SHIFT,     GPIO_PMC1_PMC12);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM12_SHIFT,       GPIO_PM1_PM12);

		//port13  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC13_SHIFT,   GPIO_PBDC1_PBDC13);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC13_SHIFT,     GPIO_PFC1_PFC13);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE13_SHIFT,   GPIO_PFCE1_PFCE13);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE13_SHIFT, GPIO_PFCAE1_PFCAE13);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC13_SHIFT,   GPIO_PIPC1_PIPC13);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC13_SHIFT,     GPIO_PMC1_PMC13);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    0, GPIO_PM1_PM13_SHIFT,       GPIO_PM1_PM13);

		//port14  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC14_SHIFT,   GPIO_PBDC1_PBDC14);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC14_SHIFT,     GPIO_PFC1_PFC14);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE14_SHIFT,   GPIO_PFCE1_PFCE14);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE14_SHIFT, GPIO_PFCAE1_PFCAE14);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC14_SHIFT,   GPIO_PIPC1_PIPC14);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC14_SHIFT,     GPIO_PMC1_PMC14);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    0, GPIO_PM1_PM14_SHIFT,       GPIO_PM1_PM14);

		//port15  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC15_SHIFT,   GPIO_PBDC1_PBDC15);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC15_SHIFT,     GPIO_PFC1_PFC15);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE15_SHIFT,   GPIO_PFCE1_PFCE15);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE15_SHIFT, GPIO_PFCAE1_PFCAE15);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC15_SHIFT,   GPIO_PIPC1_PIPC15);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC15_SHIFT,     GPIO_PMC1_PMC15);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM15_SHIFT,       GPIO_PM1_PM15);		//2019.07.24 horie 初期Hインピーダンス設定
	   		//RZA_IO_RegWrite_16(&GPIO.P1,     0, GPIO_P1_P15_SHIFT,         GPIO_P1_P15);		//2019.07.24 horie 初期Hインピーダンス設定

		//port16  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC16_SHIFT,   GPIO_PBDC1_PBDC16);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC16_SHIFT,     GPIO_PFC1_PFC16);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE16_SHIFT,   GPIO_PFCE1_PFCE16);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE16_SHIFT, GPIO_PFCAE1_PFCAE16);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC16_SHIFT,   GPIO_PIPC1_PIPC16);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC16_SHIFT,     GPIO_PMC1_PMC16);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    0, GPIO_PM1_PM16_SHIFT,       GPIO_PM1_PM16);

		//port17  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC17_SHIFT,   GPIO_PBDC1_PBDC17);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC17_SHIFT,     GPIO_PFC1_PFC17);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE17_SHIFT,   GPIO_PFCE1_PFCE17);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE17_SHIFT, GPIO_PFCAE1_PFCAE17);
    		RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC17_SHIFT,   GPIO_PIPC1_PIPC17);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC17_SHIFT,     GPIO_PMC1_PMC17);
    		RZA_IO_RegWrite_16(&GPIO.PM1,    0, GPIO_PM1_PM17_SHIFT,       GPIO_PM1_PM17);

		//port18  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC18_SHIFT,   GPIO_PBDC1_PBDC18);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC18_SHIFT,     GPIO_PFC1_PFC18);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE18_SHIFT,   GPIO_PFCE1_PFCE18);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE18_SHIFT, GPIO_PFCAE1_PFCAE18);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC18_SHIFT,   GPIO_PIPC1_PIPC18);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC18_SHIFT,     GPIO_PMC1_PMC18);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM18_SHIFT,       GPIO_PM1_PM18);

		//port19  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC19_SHIFT,   GPIO_PBDC1_PBDC19);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC19_SHIFT,     GPIO_PFC1_PFC19);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE19_SHIFT,   GPIO_PFCE1_PFCE19);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE19_SHIFT, GPIO_PFCAE1_PFCAE19);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC19_SHIFT,   GPIO_PIPC1_PIPC19);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC19_SHIFT,     GPIO_PMC1_PMC19);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM19_SHIFT,       GPIO_PM1_PM19);

		//port110  port AN2
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC110_SHIFT,   GPIO_PBDC1_PBDC110);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC110_SHIFT,     GPIO_PFC1_PFC110);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE110_SHIFT,   GPIO_PFCE1_PFCE110);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE110_SHIFT, GPIO_PFCAE1_PFCAE110);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC110_SHIFT,   GPIO_PIPC1_PIPC110);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   1, GPIO_PMC1_PMC110_SHIFT,     GPIO_PMC1_PMC110);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM110_SHIFT,       GPIO_PM1_PM110);

		//port111  port AN3
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC111_SHIFT,   GPIO_PBDC1_PBDC111);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC111_SHIFT,     GPIO_PFC1_PFC111);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE111_SHIFT,   GPIO_PFCE1_PFCE111);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE111_SHIFT, GPIO_PFCAE1_PFCAE111);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC111_SHIFT,   GPIO_PIPC1_PIPC111);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   1, GPIO_PMC1_PMC111_SHIFT,     GPIO_PMC1_PMC111);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM111_SHIFT,       GPIO_PM1_PM111);

		//port112  port AN4
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC112_SHIFT,   GPIO_PBDC1_PBDC112);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC112_SHIFT,     GPIO_PFC1_PFC112);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE112_SHIFT,   GPIO_PFCE1_PFCE112);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE112_SHIFT, GPIO_PFCAE1_PFCAE112);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC112_SHIFT,   GPIO_PIPC1_PIPC112);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   1, GPIO_PMC1_PMC112_SHIFT,     GPIO_PMC1_PMC112);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM112_SHIFT,       GPIO_PM1_PM112);

		//port113  port AN5
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC113_SHIFT,   GPIO_PBDC1_PBDC113);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC113_SHIFT,     GPIO_PFC1_PFC113);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE113_SHIFT,   GPIO_PFCE1_PFCE113);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE113_SHIFT, GPIO_PFCAE1_PFCAE113);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC113_SHIFT,   GPIO_PIPC1_PIPC113);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   1, GPIO_PMC1_PMC113_SHIFT,     GPIO_PMC1_PMC113);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM113_SHIFT,       GPIO_PM1_PM113);

		//port114  port AN6
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC114_SHIFT,   GPIO_PBDC1_PBDC114);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC114_SHIFT,     GPIO_PFC1_PFC114);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE114_SHIFT,   GPIO_PFCE1_PFCE114);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE114_SHIFT, GPIO_PFCAE1_PFCAE114);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC114_SHIFT,   GPIO_PIPC1_PIPC114);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   1, GPIO_PMC1_PMC114_SHIFT,     GPIO_PMC1_PMC114);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM114_SHIFT,       GPIO_PM1_PM114);

		//port115  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC1,  0, GPIO_PBDC1_PBDC115_SHIFT,   GPIO_PBDC1_PBDC115);
    		RZA_IO_RegWrite_16(&GPIO.PFC1,   0, GPIO_PFC1_PFC115_SHIFT,     GPIO_PFC1_PFC115);
    		RZA_IO_RegWrite_16(&GPIO.PFCE1,  0, GPIO_PFCE1_PFCE115_SHIFT,   GPIO_PFCE1_PFCE115);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE1, 0, GPIO_PFCAE1_PFCAE115_SHIFT, GPIO_PFCAE1_PFCAE115);
    		//RZA_IO_RegWrite_16(&GPIO.PIPC1,  1, GPIO_PIPC1_PIPC115_SHIFT,   GPIO_PIPC1_PIPC115);
    		RZA_IO_RegWrite_16(&GPIO.PMC1,   0, GPIO_PMC1_PMC115_SHIFT,     GPIO_PMC1_PMC115);
    		//RZA_IO_RegWrite_16(&GPIO.PM1,    1, GPIO_PM1_PM115_SHIFT,       GPIO_PM1_PM115);


	//port2
		//初期化
#if 0
                GPIO.PIBC2 = 0x0000;
                GPIO.PBDC2 = 0x0000;
		GPIO.PM2   = 0xffff;
		GPIO.PMC2  = 0x0000;
		GPIO.PIPC2 = 0x0000;
                //ポートモードレジスタ	0:出力(ポートなし） 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      0      0      0      0      0      0      0      0      0      0      0      1      1      1      1
		GPIO.PM2	 = 0x000f;
		
		//ポートモード制御レジスタ   0:ポートモード（ポートなし） 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   0      0      0      0      0      0      1      1      1      1      0      0      0      0      1      0
		//         -      -      -      -      -      -      A0     *RD    *CS    *WR    out    out    in     in     IRQ6   in
		GPIO.PMC2 = 0x03c2;
	//port3
		//初期化
                GPIO.PIBC3 = 0x0000;
                GPIO.PBDC3 = 0x0000;
		GPIO.PM3   = 0xffff;
		GPIO.PMC3  = 0x0000;
		GPIO.PIPC3 = 0x0000;
                //ポートモードレジスタ	0:出力(ポートなし） 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0
		GPIO.PM3	 = 0x0000;
		
		//ポートモード制御レジスタ   0:ポートモード（ポートなし） 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   1      1      1      1      1      1      1      1      1      1      1      1      1      1      1      1
		//         A16    A15    A14    A13    A12    A11    A10    A09    A08    A07    A06    A05    A04    A03    A02    A01
		GPIO.PMC3 = 0xffff;

	//port4
		//初期化
                GPIO.PIBC4 = 0x0000;
                GPIO.PBDC4 = 0x0000;
		GPIO.PM4   = 0xffff;
		GPIO.PMC4  = 0x0000;
		GPIO.PIPC4 = 0x0000;
                //ポートモードレジスタ	0:出力(ポートなし） 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      0      0      0      0      0      0      0      0      0      0      0      0      0      1      0
		GPIO.PM4	 = 0x0002;
		
		//ポートモード制御レジスタ   0:ポートモード（ポートなし） 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   0      0      0      0      0      0      0      0      1      1      1      1      1      1      0      1
		//         -      -      -      -      -      -      -      -      SPBIO  SPBIO  SPBSSL SPBCLK SPBIO  SPBIO  in     A17
		GPIO.PMC4 = 0x00fd;

	//port5
		//初期化
                GPIO.PIBC5 = 0x0000;
                GPIO.PBDC5 = 0x0000;
		GPIO.PM5   = 0xffff;
		GPIO.PMC5  = 0x0000;
		GPIO.PIPC5 = 0x0000;
                //ポートモードレジスタ	0:出力(ポートなし） 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0
		GPIO.PM5	 = 0x0000;
		
		//ポートモード制御レジスタ   0:ポートモード（ポートなし） 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   1      1      1      1      1      1      1      1      1      1      1      1      1      1      1      1
		//         D15    D14    D13    D12    D11    D10    D09    D08    D07    D06    D05    D04    D03    D02    D01    D00
		GPIO.PMC5 = 0xffff;
#endif

	//port6
		//初期化
                GPIO.PIBC6 = 0x0000;
                GPIO.PBDC6 = 0x0000;
		GPIO.PM6   = 0xffff;
		GPIO.PMC6  = 0x0000;
		GPIO.PIPC6 = 0x0000;
                //ポートモードレジスタ	0:出力(ポートなし） 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      1      0      1      0      1      0      0      1      0      1      0      0      1      1      1
		
		//ポートモード制御レジスタ   0:ポートモード（ポートなし） 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   1      1      0      0      0      0      0      0      0      0      0      0      0      0      0      0
		//         TxD0   RxD0   out    in     out    in     out    out    in     out    in     out    out    in     in     in

		//port60  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC60_SHIFT,   GPIO_PBDC6_PBDC60);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC60_SHIFT,     GPIO_PFC6_PFC60);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE60_SHIFT,   GPIO_PFCE6_PFCE60);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE60_SHIFT, GPIO_PFCAE6_PFCAE60);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC60_SHIFT,   GPIO_PIPC6_PIPC60);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC60_SHIFT,     GPIO_PMC6_PMC60);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM60_SHIFT,       GPIO_PM6_PM60);

		//port61  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC61_SHIFT,   GPIO_PBDC6_PBDC61);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC61_SHIFT,     GPIO_PFC6_PFC61);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE61_SHIFT,   GPIO_PFCE6_PFCE61);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE61_SHIFT, GPIO_PFCAE6_PFCAE61);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC61_SHIFT,   GPIO_PIPC6_PIPC61);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC61_SHIFT,     GPIO_PMC6_PMC61);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM61_SHIFT,       GPIO_PM6_PM61);

		//port62  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC62_SHIFT,   GPIO_PBDC6_PBDC62);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC62_SHIFT,     GPIO_PFC6_PFC62);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE62_SHIFT,   GPIO_PFCE6_PFCE62);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE62_SHIFT, GPIO_PFCAE6_PFCAE62);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC62_SHIFT,   GPIO_PIPC6_PIPC62);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC62_SHIFT,     GPIO_PMC6_PMC62);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM62_SHIFT,       GPIO_PM6_PM62);

		//port63  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC63_SHIFT,   GPIO_PBDC6_PBDC63);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC63_SHIFT,     GPIO_PFC6_PFC63);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE63_SHIFT,   GPIO_PFCE6_PFCE63);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE63_SHIFT, GPIO_PFCAE6_PFCAE63);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC63_SHIFT,   GPIO_PIPC6_PIPC63);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC63_SHIFT,     GPIO_PMC6_PMC63);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM63_SHIFT,       GPIO_PM6_PM63);

		//port64  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC64_SHIFT,   GPIO_PBDC6_PBDC64);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC64_SHIFT,     GPIO_PFC6_PFC64);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE64_SHIFT,   GPIO_PFCE6_PFCE64);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE64_SHIFT, GPIO_PFCAE6_PFCAE64);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC64_SHIFT,   GPIO_PIPC6_PIPC64);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC64_SHIFT,     GPIO_PMC6_PMC64);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM64_SHIFT,       GPIO_PM6_PM64);

		//port65  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC65_SHIFT,   GPIO_PBDC6_PBDC65);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC65_SHIFT,     GPIO_PFC6_PFC65);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE65_SHIFT,   GPIO_PFCE6_PFCE65);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE65_SHIFT, GPIO_PFCAE6_PFCAE65);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC65_SHIFT,   GPIO_PIPC6_PIPC65);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC65_SHIFT,     GPIO_PMC6_PMC65);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM65_SHIFT,       GPIO_PM6_PM65);

		//port66  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC66_SHIFT,   GPIO_PBDC6_PBDC66);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC66_SHIFT,     GPIO_PFC6_PFC66);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE66_SHIFT,   GPIO_PFCE6_PFCE66);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE66_SHIFT, GPIO_PFCAE6_PFCAE66);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC66_SHIFT,   GPIO_PIPC6_PIPC66);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC66_SHIFT,     GPIO_PMC6_PMC66);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM66_SHIFT,       GPIO_PM6_PM66);

		//port67  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC67_SHIFT,   GPIO_PBDC6_PBDC67);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC67_SHIFT,     GPIO_PFC6_PFC67);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE67_SHIFT,   GPIO_PFCE6_PFCE67);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE67_SHIFT, GPIO_PFCAE6_PFCAE67);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC67_SHIFT,   GPIO_PIPC6_PIPC67);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC67_SHIFT,     GPIO_PMC6_PMC67);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM67_SHIFT,       GPIO_PM6_PM67);

		//port68  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC68_SHIFT,   GPIO_PBDC6_PBDC68);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC68_SHIFT,     GPIO_PFC6_PFC68);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE68_SHIFT,   GPIO_PFCE6_PFCE68);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE68_SHIFT, GPIO_PFCAE6_PFCAE68);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC68_SHIFT,   GPIO_PIPC6_PIPC68);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC68_SHIFT,     GPIO_PMC6_PMC68);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM68_SHIFT,       GPIO_PM6_PM68);

		//port69  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC69_SHIFT,   GPIO_PBDC6_PBDC69);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC69_SHIFT,     GPIO_PFC6_PFC69);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE69_SHIFT,   GPIO_PFCE6_PFCE69);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE69_SHIFT, GPIO_PFCAE6_PFCAE69);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC69_SHIFT,   GPIO_PIPC6_PIPC69);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC69_SHIFT,     GPIO_PMC6_PMC69);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM69_SHIFT,       GPIO_PM6_PM69);

		//port610  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC610_SHIFT,   GPIO_PBDC6_PBDC610);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC610_SHIFT,     GPIO_PFC6_PFC610);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE610_SHIFT,   GPIO_PFCE6_PFCE610);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE610_SHIFT, GPIO_PFCAE6_PFCAE610);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC610_SHIFT,   GPIO_PIPC6_PIPC610);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC610_SHIFT,     GPIO_PMC6_PMC610);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM610_SHIFT,       GPIO_PM6_PM610);

		//port611  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC611_SHIFT,   GPIO_PBDC6_PBDC611);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC611_SHIFT,     GPIO_PFC6_PFC611);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE611_SHIFT,   GPIO_PFCE6_PFCE611);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE611_SHIFT, GPIO_PFCAE6_PFCAE611);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC611_SHIFT,   GPIO_PIPC6_PIPC611);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC611_SHIFT,     GPIO_PMC6_PMC611);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM611_SHIFT,       GPIO_PM6_PM611);

		//port612  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC612_SHIFT,   GPIO_PBDC6_PBDC612);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC612_SHIFT,     GPIO_PFC6_PFC612);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE612_SHIFT,   GPIO_PFCE6_PFCE612);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE612_SHIFT, GPIO_PFCAE6_PFCAE612);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC612_SHIFT,   GPIO_PIPC6_PIPC612);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC612_SHIFT,     GPIO_PMC6_PMC612);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM612_SHIFT,       GPIO_PM6_PM612);

		//port613  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC613_SHIFT,   GPIO_PBDC6_PBDC613);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC613_SHIFT,     GPIO_PFC6_PFC613);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE613_SHIFT,   GPIO_PFCE6_PFCE613);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 0, GPIO_PFCAE6_PFCAE613_SHIFT, GPIO_PFCAE6_PFCAE613);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC613_SHIFT,   GPIO_PIPC6_PIPC613);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   0, GPIO_PMC6_PMC613_SHIFT,     GPIO_PMC6_PMC613);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM613_SHIFT,       GPIO_PM6_PM613);

		//port614  port RxD0
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC614_SHIFT,   GPIO_PBDC6_PBDC614);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC614_SHIFT,     GPIO_PFC6_PFC614);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE614_SHIFT,   GPIO_PFCE6_PFCE614);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 1, GPIO_PFCAE6_PFCAE614_SHIFT, GPIO_PFCAE6_PFCAE614);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC614_SHIFT,   GPIO_PIPC6_PIPC614);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   1, GPIO_PMC6_PMC614_SHIFT,     GPIO_PMC6_PMC614);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    1, GPIO_PM6_PM614_SHIFT,       GPIO_PM6_PM614);

		//port615  port TxD0
    		RZA_IO_RegWrite_16(&GPIO.PBDC6,  0, GPIO_PBDC6_PBDC615_SHIFT,   GPIO_PBDC6_PBDC615);
    		RZA_IO_RegWrite_16(&GPIO.PFC6,   0, GPIO_PFC6_PFC615_SHIFT,     GPIO_PFC6_PFC615);
    		RZA_IO_RegWrite_16(&GPIO.PFCE6,  0, GPIO_PFCE6_PFCE615_SHIFT,   GPIO_PFCE6_PFCE615);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE6, 1, GPIO_PFCAE6_PFCAE615_SHIFT, GPIO_PFCAE6_PFCAE615);
    		RZA_IO_RegWrite_16(&GPIO.PIPC6,  1, GPIO_PIPC6_PIPC615_SHIFT,   GPIO_PIPC6_PIPC615);
    		RZA_IO_RegWrite_16(&GPIO.PMC6,   1, GPIO_PMC6_PMC615_SHIFT,     GPIO_PMC6_PMC615);
    		RZA_IO_RegWrite_16(&GPIO.PM6,    0, GPIO_PM6_PM615_SHIFT,       GPIO_PM6_PM615);


#if 0
	//port7
		//初期化
                GPIO.PIBC7 = 0x0000;
                GPIO.PBDC7 = 0x0000;
		GPIO.PM7   = 0xffff;
		GPIO.PMC7  = 0x0000;
		GPIO.PIPC7 = 0x0000;
                //ポートモードレジスタ	0:出力(ポートなし） 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      0      0      0      0      1      1      0      0      0      0      1      0      0      0      1
		GPIO.PM7	 = 0x0611;
		
		//ポートモード制御レジスタ   0:ポートモード（ポートなし） 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   0      0      0      0      1      1      0      0      0      0      0      1      0      0      1      0
		//         -      -      -      -      TxD3   RxD3   in     out    out    out    out    *WAIT  out    out    *CS1   in
		GPIO.PMC7 = 0x0c12;
#endif

	//port8
		//初期化
                GPIO.PIBC8 = 0x0000;
                GPIO.PBDC8 = 0x0000;
		GPIO.PM8   = 0xffff;
		GPIO.PMC8  = 0x0000;
		GPIO.PIPC8 = 0x0000;
                //ポートモードレジスタ	0:出力 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         1      1      0      1      1      0      1      1      0      0      0      0      1      1      1      0
		
		//ポートモード制御レジスタ   0:ポートモード 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   1      0      1      1      0      1      1      0      0      0      0      0      0      0      0      0
		//         RxD1   in     TxD4   RxD4   in     TxD2   RxD2   in     out    out    out    out    in     in     in     out

		//12,13は別の場所で設定されているので、ここで設定しないこと

		//port80  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC80_SHIFT,   GPIO_PBDC8_PBDC80);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC80_SHIFT,     GPIO_PFC8_PFC80);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE80_SHIFT,   GPIO_PFCE8_PFCE80);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE80_SHIFT, GPIO_PFCAE8_PFCAE80);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC80_SHIFT,   GPIO_PIPC8_PIPC80);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC80_SHIFT,     GPIO_PMC8_PMC80);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    0, GPIO_PM8_PM80_SHIFT,       GPIO_PM8_PM80);

		//port81  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC81_SHIFT,   GPIO_PBDC8_PBDC81);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC81_SHIFT,     GPIO_PFC8_PFC81);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE81_SHIFT,   GPIO_PFCE8_PFCE81);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE81_SHIFT, GPIO_PFCAE8_PFCAE81);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC81_SHIFT,   GPIO_PIPC8_PIPC81);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC81_SHIFT,     GPIO_PMC8_PMC81);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM81_SHIFT,       GPIO_PM8_PM81);

		//port82  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC82_SHIFT,   GPIO_PBDC8_PBDC82);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC82_SHIFT,     GPIO_PFC8_PFC82);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE82_SHIFT,   GPIO_PFCE8_PFCE82);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE82_SHIFT, GPIO_PFCAE8_PFCAE82);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC82_SHIFT,   GPIO_PIPC8_PIPC82);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC82_SHIFT,     GPIO_PMC8_PMC82);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM82_SHIFT,       GPIO_PM8_PM82);

		//port83  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC83_SHIFT,   GPIO_PBDC8_PBDC83);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC83_SHIFT,     GPIO_PFC8_PFC83);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE83_SHIFT,   GPIO_PFCE8_PFCE83);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE83_SHIFT, GPIO_PFCAE8_PFCAE83);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC83_SHIFT,   GPIO_PIPC8_PIPC83);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC83_SHIFT,     GPIO_PMC8_PMC83);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM83_SHIFT,       GPIO_PM8_PM83);

		//port84  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC84_SHIFT,   GPIO_PBDC8_PBDC84);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC84_SHIFT,     GPIO_PFC8_PFC84);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE84_SHIFT,   GPIO_PFCE8_PFCE84);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE84_SHIFT, GPIO_PFCAE8_PFCAE84);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC84_SHIFT,   GPIO_PIPC8_PIPC84);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC84_SHIFT,     GPIO_PMC8_PMC84);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    0, GPIO_PM8_PM84_SHIFT,       GPIO_PM8_PM84);

		//port85  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC85_SHIFT,   GPIO_PBDC8_PBDC85);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC85_SHIFT,     GPIO_PFC8_PFC85);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE85_SHIFT,   GPIO_PFCE8_PFCE85);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE85_SHIFT, GPIO_PFCAE8_PFCAE85);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC85_SHIFT,   GPIO_PIPC8_PIPC85);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC85_SHIFT,     GPIO_PMC8_PMC85);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    0, GPIO_PM8_PM85_SHIFT,       GPIO_PM8_PM85);

		//port86  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC86_SHIFT,   GPIO_PBDC8_PBDC86);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC86_SHIFT,     GPIO_PFC8_PFC86);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE86_SHIFT,   GPIO_PFCE8_PFCE86);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE86_SHIFT, GPIO_PFCAE8_PFCAE86);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC86_SHIFT,   GPIO_PIPC8_PIPC86);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC86_SHIFT,     GPIO_PMC8_PMC86);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    0, GPIO_PM8_PM86_SHIFT,       GPIO_PM8_PM86);

		//port87  port output
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC87_SHIFT,   GPIO_PBDC8_PBDC87);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC87_SHIFT,     GPIO_PFC8_PFC87);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE87_SHIFT,   GPIO_PFCE8_PFCE87);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE87_SHIFT, GPIO_PFCAE8_PFCAE87);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC87_SHIFT,   GPIO_PIPC8_PIPC87);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC87_SHIFT,     GPIO_PMC8_PMC87);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    0, GPIO_PM8_PM87_SHIFT,       GPIO_PM8_PM87);

		//port83  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC88_SHIFT,   GPIO_PBDC8_PBDC88);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC88_SHIFT,     GPIO_PFC8_PFC88);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE88_SHIFT,   GPIO_PFCE8_PFCE88);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE88_SHIFT, GPIO_PFCAE8_PFCAE88);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC88_SHIFT,   GPIO_PIPC8_PIPC88);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC88_SHIFT,     GPIO_PMC8_PMC88);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM88_SHIFT,       GPIO_PM8_PM88);

		//port89  port RxD0
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC89_SHIFT,   GPIO_PBDC8_PBDC89);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   1, GPIO_PFC8_PFC89_SHIFT,     GPIO_PFC8_PFC89);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  1, GPIO_PFCE8_PFCE89_SHIFT,   GPIO_PFCE8_PFCE89);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE89_SHIFT, GPIO_PFCAE8_PFCAE89);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC89_SHIFT,   GPIO_PIPC8_PIPC89);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   1, GPIO_PMC8_PMC89_SHIFT,     GPIO_PMC8_PMC89);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM89_SHIFT,       GPIO_PM8_PM89);

		//port810  port TxD0
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC810_SHIFT,   GPIO_PBDC8_PBDC810);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   1, GPIO_PFC8_PFC810_SHIFT,     GPIO_PFC8_PFC810);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  1, GPIO_PFCE8_PFCE810_SHIFT,   GPIO_PFCE8_PFCE810);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE810_SHIFT, GPIO_PFCAE8_PFCAE810);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC810_SHIFT,   GPIO_PIPC8_PIPC810);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   1, GPIO_PMC8_PMC810_SHIFT,     GPIO_PMC8_PMC810);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    0, GPIO_PM8_PM810_SHIFT,       GPIO_PM8_PM810);

		//port811  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC811_SHIFT,   GPIO_PBDC8_PBDC811);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC811_SHIFT,     GPIO_PFC8_PFC811);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE811_SHIFT,   GPIO_PFCE8_PFCE811);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE811_SHIFT, GPIO_PFCAE8_PFCAE811);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC811_SHIFT,   GPIO_PIPC8_PIPC811);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC811_SHIFT,     GPIO_PMC8_PMC811);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM811_SHIFT,       GPIO_PM8_PM811);

		//port812  別の場所で設定している
		//port813  別の場所で設定している

		//port814  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC814_SHIFT,   GPIO_PBDC8_PBDC814);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC814_SHIFT,     GPIO_PFC8_PFC814);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  0, GPIO_PFCE8_PFCE814_SHIFT,   GPIO_PFCE8_PFCE814);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE814_SHIFT, GPIO_PFCAE8_PFCAE814);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC814_SHIFT,   GPIO_PIPC8_PIPC814);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   0, GPIO_PMC8_PMC814_SHIFT,     GPIO_PMC8_PMC814);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM814_SHIFT,       GPIO_PM8_PM814);

		//port815  port RxD1
    		RZA_IO_RegWrite_16(&GPIO.PBDC8,  0, GPIO_PBDC8_PBDC815_SHIFT,   GPIO_PBDC8_PBDC815);
    		RZA_IO_RegWrite_16(&GPIO.PFC8,   0, GPIO_PFC8_PFC815_SHIFT,     GPIO_PFC8_PFC815);
    		RZA_IO_RegWrite_16(&GPIO.PFCE8,  1, GPIO_PFCE8_PFCE815_SHIFT,   GPIO_PFCE8_PFCE815);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE8, 0, GPIO_PFCAE8_PFCAE815_SHIFT, GPIO_PFCAE8_PFCAE815);
    		RZA_IO_RegWrite_16(&GPIO.PIPC8,  1, GPIO_PIPC8_PIPC815_SHIFT,   GPIO_PIPC8_PIPC815);
    		RZA_IO_RegWrite_16(&GPIO.PMC8,   1, GPIO_PMC8_PMC815_SHIFT,     GPIO_PMC8_PMC815);
    		RZA_IO_RegWrite_16(&GPIO.PM8,    1, GPIO_PM8_PM815_SHIFT,       GPIO_PM8_PM815);

	//port9
		//初期化
                GPIO.PIBC9 = 0x0000;
                GPIO.PBDC9 = 0x0000;
		GPIO.PM9   = 0xffff;
		GPIO.PMC9  = 0x0000;
		GPIO.PIPC9 = 0x0000;
                //ポートモードレジスタ	0:出力 1:入力
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//         0      0      0      0      0      0      0      0      0      0      1      1      1      1      1      0
		
		//ポートモード制御レジスタ   0:ポートモード 1:兼用モード
		//         15     14     13     12     11     10     09     08     07     06     05     04     03     02     01     00
		//	   0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      1
		//         -      -      -      -      -      -      -      -      -      -      in     in     in     in     in     TxD1

		//port90  port TxD1
    		RZA_IO_RegWrite_16(&GPIO.PBDC9,  0, GPIO_PBDC9_PBDC90_SHIFT,   GPIO_PBDC9_PBDC90);
    		RZA_IO_RegWrite_16(&GPIO.PFC9,   0, GPIO_PFC9_PFC90_SHIFT,     GPIO_PFC9_PFC90);
    		RZA_IO_RegWrite_16(&GPIO.PFCE9,  1, GPIO_PFCE9_PFCE90_SHIFT,   GPIO_PFCE9_PFCE90);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE9, 0, GPIO_PFCAE9_PFCAE90_SHIFT, GPIO_PFCAE9_PFCAE90);
    		RZA_IO_RegWrite_16(&GPIO.PIPC9,  1, GPIO_PIPC9_PIPC90_SHIFT,   GPIO_PIPC9_PIPC90);
    		RZA_IO_RegWrite_16(&GPIO.PMC9,   1, GPIO_PMC9_PMC90_SHIFT,     GPIO_PMC9_PMC90);
    		RZA_IO_RegWrite_16(&GPIO.PM9,    0, GPIO_PM9_PM90_SHIFT,       GPIO_PM9_PM90);

		//port91  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC9,  0, GPIO_PBDC9_PBDC91_SHIFT,   GPIO_PBDC9_PBDC91);
    		RZA_IO_RegWrite_16(&GPIO.PFC9,   0, GPIO_PFC9_PFC91_SHIFT,     GPIO_PFC9_PFC91);
    		RZA_IO_RegWrite_16(&GPIO.PFCE9,  0, GPIO_PFCE9_PFCE91_SHIFT,   GPIO_PFCE9_PFCE91);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE9, 0, GPIO_PFCAE9_PFCAE91_SHIFT, GPIO_PFCAE9_PFCAE91);
    		RZA_IO_RegWrite_16(&GPIO.PIPC9,  1, GPIO_PIPC9_PIPC91_SHIFT,   GPIO_PIPC9_PIPC91);
    		RZA_IO_RegWrite_16(&GPIO.PMC9,   0, GPIO_PMC9_PMC91_SHIFT,     GPIO_PMC9_PMC91);
    		RZA_IO_RegWrite_16(&GPIO.PM9,    1, GPIO_PM9_PM91_SHIFT,       GPIO_PM9_PM91);

		//port92  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC9,  0, GPIO_PBDC9_PBDC92_SHIFT,   GPIO_PBDC9_PBDC92);
    		RZA_IO_RegWrite_16(&GPIO.PFC9,   0, GPIO_PFC9_PFC92_SHIFT,     GPIO_PFC9_PFC92);
    		RZA_IO_RegWrite_16(&GPIO.PFCE9,  0, GPIO_PFCE9_PFCE92_SHIFT,   GPIO_PFCE9_PFCE92);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE9, 0, GPIO_PFCAE9_PFCAE92_SHIFT, GPIO_PFCAE9_PFCAE92);
    		RZA_IO_RegWrite_16(&GPIO.PIPC9,  1, GPIO_PIPC9_PIPC92_SHIFT,   GPIO_PIPC9_PIPC92);
    		RZA_IO_RegWrite_16(&GPIO.PMC9,   0, GPIO_PMC9_PMC92_SHIFT,     GPIO_PMC9_PMC92);
    		RZA_IO_RegWrite_16(&GPIO.PM9,    1, GPIO_PM9_PM92_SHIFT,       GPIO_PM9_PM92);

		//port93  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC9,  0, GPIO_PBDC9_PBDC93_SHIFT,   GPIO_PBDC9_PBDC93);
    		RZA_IO_RegWrite_16(&GPIO.PFC9,   0, GPIO_PFC9_PFC93_SHIFT,     GPIO_PFC9_PFC93);
    		RZA_IO_RegWrite_16(&GPIO.PFCE9,  0, GPIO_PFCE9_PFCE93_SHIFT,   GPIO_PFCE9_PFCE93);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE9, 0, GPIO_PFCAE9_PFCAE93_SHIFT, GPIO_PFCAE9_PFCAE93);
    		RZA_IO_RegWrite_16(&GPIO.PIPC9,  1, GPIO_PIPC9_PIPC93_SHIFT,   GPIO_PIPC9_PIPC93);
    		RZA_IO_RegWrite_16(&GPIO.PMC9,   0, GPIO_PMC9_PMC93_SHIFT,     GPIO_PMC9_PMC93);
    		RZA_IO_RegWrite_16(&GPIO.PM9,    1, GPIO_PM9_PM93_SHIFT,       GPIO_PM9_PM93);

		//port94  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC9,  0, GPIO_PBDC9_PBDC94_SHIFT,   GPIO_PBDC9_PBDC94);
    		RZA_IO_RegWrite_16(&GPIO.PFC9,   0, GPIO_PFC9_PFC94_SHIFT,     GPIO_PFC9_PFC94);
    		RZA_IO_RegWrite_16(&GPIO.PFCE9,  0, GPIO_PFCE9_PFCE94_SHIFT,   GPIO_PFCE9_PFCE94);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE9, 0, GPIO_PFCAE9_PFCAE94_SHIFT, GPIO_PFCAE9_PFCAE94);
    		RZA_IO_RegWrite_16(&GPIO.PIPC9,  1, GPIO_PIPC9_PIPC94_SHIFT,   GPIO_PIPC9_PIPC94);
    		RZA_IO_RegWrite_16(&GPIO.PMC9,   0, GPIO_PMC9_PMC94_SHIFT,     GPIO_PMC9_PMC94);
    		RZA_IO_RegWrite_16(&GPIO.PM9,    1, GPIO_PM9_PM94_SHIFT,       GPIO_PM9_PM94);

		//port95  port input
    		RZA_IO_RegWrite_16(&GPIO.PBDC9,  0, GPIO_PBDC9_PBDC95_SHIFT,   GPIO_PBDC9_PBDC95);
    		RZA_IO_RegWrite_16(&GPIO.PFC9,   0, GPIO_PFC9_PFC95_SHIFT,     GPIO_PFC9_PFC95);
    		RZA_IO_RegWrite_16(&GPIO.PFCE9,  0, GPIO_PFCE9_PFCE95_SHIFT,   GPIO_PFCE9_PFCE95);
    		RZA_IO_RegWrite_16(&GPIO.PFCAE9, 0, GPIO_PFCAE9_PFCAE95_SHIFT, GPIO_PFCAE9_PFCAE95);
    		RZA_IO_RegWrite_16(&GPIO.PIPC9,  1, GPIO_PIPC9_PIPC95_SHIFT,   GPIO_PIPC9_PIPC95);
    		RZA_IO_RegWrite_16(&GPIO.PMC9,   0, GPIO_PMC9_PMC95_SHIFT,     GPIO_PMC9_PMC95);
    		RZA_IO_RegWrite_16(&GPIO.PM9,    1, GPIO_PM9_PM95_SHIFT,       GPIO_PM9_PM95);

//<><><><><><><><><><><><><><><><><><><><><><><><><><> バス設定 2019.05.28 <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
    /* ==== BSC settings ==== */

    /* ---- P5_0 : D0 to P5_15 : D15 ---- */
    /* Port initialize */
    GPIO.PIBC5 = 0x0000u;
    GPIO.PBDC5 = 0x0000u;
    GPIO.PM5   = 0xFFFFu;
    GPIO.PMC5  = 0x0000u;
    GPIO.PIPC5 = 0x0000u;
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Enable                    */
    GPIO.PBDC5  = 0xFFFFu;
    GPIO.PFC5   = 0x0000u;
    GPIO.PFCE5  = 0x0000u;
    GPIO.PFCAE5 = 0x0000u;
    GPIO.PIPC5  = 0xFFFFu;
    GPIO.PMC5   = 0xFFFFu;



    /* ---- P2_3 : ＭＳ制御ピンとして使用する 2019.07.04---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC23_SHIFT,   GPIO_PIBC2_PIBC23);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC23_SHIFT,   GPIO_PBDC2_PBDC23);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM23_SHIFT,       GPIO_PM2_PM23);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC23_SHIFT,     GPIO_PMC2_PMC23);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC23_SHIFT,   GPIO_PIPC2_PIPC23);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC23_SHIFT,   GPIO_PBDC2_PBDC23);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC23_SHIFT,     GPIO_PFC2_PFC23);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE23_SHIFT,   GPIO_PFCE2_PFCE23);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 1, GPIO_PFCAE2_PFCAE23_SHIFT, GPIO_PFCAE2_PFCAE23);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC23_SHIFT,   GPIO_PIPC2_PIPC23);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC23_SHIFT,     GPIO_PMC2_PMC23);
    RZA_IO_RegWrite_16(&GPIO.PM2,    0, GPIO_PM2_PM23_SHIFT,       GPIO_PM2_PM23);

    /* ---- P2_4 : WE0# / DQMLL 高周波制御ピンとして使用する 2019.05.30---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC24_SHIFT,   GPIO_PIBC2_PIBC24);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC24_SHIFT,   GPIO_PBDC2_PBDC24);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM24_SHIFT,       GPIO_PM2_PM24);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC24_SHIFT,     GPIO_PMC2_PMC24);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC24_SHIFT,   GPIO_PIPC2_PIPC24);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC24_SHIFT,   GPIO_PBDC2_PBDC24);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC24_SHIFT,     GPIO_PFC2_PFC24);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE24_SHIFT,   GPIO_PFCE2_PFCE24);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 1, GPIO_PFCAE2_PFCAE24_SHIFT, GPIO_PFCAE2_PFCAE24);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC24_SHIFT,   GPIO_PIPC2_PIPC24);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC24_SHIFT,     GPIO_PMC2_PMC24);
    RZA_IO_RegWrite_16(&GPIO.PM2,    0, GPIO_PM2_PM24_SHIFT,       GPIO_PM2_PM24);

    /* ---- P2_9 : A0 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC29_SHIFT,   GPIO_PIBC2_PIBC29);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC29_SHIFT,   GPIO_PBDC2_PBDC29);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM29_SHIFT,       GPIO_PM2_PM29);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC29_SHIFT,     GPIO_PMC2_PMC29);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC29_SHIFT,   GPIO_PIPC2_PIPC29);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC29_SHIFT,   GPIO_PBDC2_PBDC29);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC29_SHIFT,     GPIO_PFC2_PFC29);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE29_SHIFT,   GPIO_PFCE2_PFCE29);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE29_SHIFT, GPIO_PFCAE2_PFCAE29);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC29_SHIFT,   GPIO_PIPC2_PIPC29);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC29_SHIFT,     GPIO_PMC2_PMC29);

    /* ---- P3_0 : A1 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC30_SHIFT,   GPIO_PIBC3_PIBC30);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC30_SHIFT,   GPIO_PBDC3_PBDC30);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM30_SHIFT,       GPIO_PM3_PM30);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC30_SHIFT,     GPIO_PMC3_PMC30);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC30_SHIFT,   GPIO_PIPC3_PIPC30);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC30_SHIFT,   GPIO_PBDC3_PBDC30);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC30_SHIFT,     GPIO_PFC3_PFC30);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE30_SHIFT,   GPIO_PFCE3_PFCE30);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE30_SHIFT, GPIO_PFCAE3_PFCAE30);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC30_SHIFT,   GPIO_PIPC3_PIPC30);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC30_SHIFT,     GPIO_PMC3_PMC30);

    /* ---- P3_1 : A2 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC31_SHIFT,   GPIO_PIBC3_PIBC31);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC31_SHIFT,   GPIO_PBDC3_PBDC31);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM31_SHIFT,       GPIO_PM3_PM31);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC31_SHIFT,     GPIO_PMC3_PMC31);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC31_SHIFT,   GPIO_PIPC3_PIPC31);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC31_SHIFT,   GPIO_PBDC3_PBDC31);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC31_SHIFT,     GPIO_PFC3_PFC31);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE31_SHIFT,   GPIO_PFCE3_PFCE31);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE31_SHIFT, GPIO_PFCAE3_PFCAE31);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC31_SHIFT,   GPIO_PIPC3_PIPC31);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC31_SHIFT,     GPIO_PMC3_PMC31);

    /* ---- P3_2 : A3 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC32_SHIFT,   GPIO_PIBC3_PIBC32);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC32_SHIFT,   GPIO_PBDC3_PBDC32);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM32_SHIFT,       GPIO_PM3_PM32);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC32_SHIFT,     GPIO_PMC3_PMC32);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC32_SHIFT,   GPIO_PIPC3_PIPC32);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC32_SHIFT,   GPIO_PBDC3_PBDC32);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC32_SHIFT,     GPIO_PFC3_PFC32);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE32_SHIFT,   GPIO_PFCE3_PFCE32);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE32_SHIFT, GPIO_PFCAE3_PFCAE32);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC32_SHIFT,   GPIO_PIPC3_PIPC32);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC32_SHIFT,     GPIO_PMC3_PMC32);

    /* ---- P3_3 : A4 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC33_SHIFT,   GPIO_PIBC3_PIBC33);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC33_SHIFT,   GPIO_PBDC3_PBDC33);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM33_SHIFT,       GPIO_PM3_PM33);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC33_SHIFT,     GPIO_PMC3_PMC33);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC33_SHIFT,   GPIO_PIPC3_PIPC33);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC33_SHIFT,   GPIO_PBDC3_PBDC33);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC33_SHIFT,     GPIO_PFC3_PFC33);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE33_SHIFT,   GPIO_PFCE3_PFCE33);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE33_SHIFT, GPIO_PFCAE3_PFCAE33);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC33_SHIFT,   GPIO_PIPC3_PIPC33);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC33_SHIFT,     GPIO_PMC3_PMC33);

    /* ---- P3_4 : A5 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC34_SHIFT,   GPIO_PIBC3_PIBC34);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC34_SHIFT,   GPIO_PBDC3_PBDC34);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM34_SHIFT,       GPIO_PM3_PM34);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC34_SHIFT,     GPIO_PMC3_PMC34);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC34_SHIFT,   GPIO_PIPC3_PIPC34);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC34_SHIFT,   GPIO_PBDC3_PBDC34);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC34_SHIFT,     GPIO_PFC3_PFC34);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE34_SHIFT,   GPIO_PFCE3_PFCE34);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE34_SHIFT, GPIO_PFCAE3_PFCAE34);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC34_SHIFT,   GPIO_PIPC3_PIPC34);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC34_SHIFT,     GPIO_PMC3_PMC34);

    /* ---- P3_5 : A6 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC35_SHIFT,   GPIO_PIBC3_PIBC35);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC35_SHIFT,   GPIO_PBDC3_PBDC35);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM35_SHIFT,       GPIO_PM3_PM35);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC35_SHIFT,     GPIO_PMC3_PMC35);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC35_SHIFT,   GPIO_PIPC3_PIPC35);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC35_SHIFT,   GPIO_PBDC3_PBDC35);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC35_SHIFT,     GPIO_PFC3_PFC35);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE35_SHIFT,   GPIO_PFCE3_PFCE35);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE35_SHIFT, GPIO_PFCAE3_PFCAE35);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC35_SHIFT,   GPIO_PIPC3_PIPC35);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC35_SHIFT,     GPIO_PMC3_PMC35);

    /* ---- P3_6 : A7 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC36_SHIFT,   GPIO_PIBC3_PIBC36);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC36_SHIFT,   GPIO_PBDC3_PBDC36);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM36_SHIFT,       GPIO_PM3_PM36);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC36_SHIFT,     GPIO_PMC3_PMC36);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC36_SHIFT,   GPIO_PIPC3_PIPC36);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC36_SHIFT,   GPIO_PBDC3_PBDC36);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC36_SHIFT,     GPIO_PFC3_PFC36);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE36_SHIFT,   GPIO_PFCE3_PFCE36);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE36_SHIFT, GPIO_PFCAE3_PFCAE36);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC36_SHIFT,   GPIO_PIPC3_PIPC36);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC36_SHIFT,     GPIO_PMC3_PMC36);

    /* ---- P3_7 : A8 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC37_SHIFT,   GPIO_PIBC3_PIBC37);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC37_SHIFT,   GPIO_PBDC3_PBDC37);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM37_SHIFT,       GPIO_PM3_PM37);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC37_SHIFT,     GPIO_PMC3_PMC37);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC37_SHIFT,   GPIO_PIPC3_PIPC37);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC37_SHIFT,   GPIO_PBDC3_PBDC37);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC37_SHIFT,     GPIO_PFC3_PFC37);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE37_SHIFT,   GPIO_PFCE3_PFCE37);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE37_SHIFT, GPIO_PFCAE3_PFCAE37);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC37_SHIFT,   GPIO_PIPC3_PIPC37);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC37_SHIFT,     GPIO_PMC3_PMC37);

    /* ---- P3_8 : A9 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC38_SHIFT,   GPIO_PIBC3_PIBC38);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC38_SHIFT,   GPIO_PBDC3_PBDC38);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM38_SHIFT,       GPIO_PM3_PM38);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC38_SHIFT,     GPIO_PMC3_PMC38);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC38_SHIFT,   GPIO_PIPC3_PIPC38);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC38_SHIFT,   GPIO_PBDC3_PBDC38);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC38_SHIFT,     GPIO_PFC3_PFC38);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE38_SHIFT,   GPIO_PFCE3_PFCE38);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE38_SHIFT, GPIO_PFCAE3_PFCAE38);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC38_SHIFT,   GPIO_PIPC3_PIPC38);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC38_SHIFT,     GPIO_PMC3_PMC38);

    /* ---- P3_9 : A10 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC39_SHIFT,   GPIO_PIBC3_PIBC39);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC39_SHIFT,   GPIO_PBDC3_PBDC39);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM39_SHIFT,       GPIO_PM3_PM39);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC39_SHIFT,     GPIO_PMC3_PMC39);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC39_SHIFT,   GPIO_PIPC3_PIPC39);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC39_SHIFT,   GPIO_PBDC3_PBDC39);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC39_SHIFT,     GPIO_PFC3_PFC39);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE39_SHIFT,   GPIO_PFCE3_PFCE39);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE39_SHIFT, GPIO_PFCAE3_PFCAE39);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC39_SHIFT,   GPIO_PIPC3_PIPC39);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC39_SHIFT,     GPIO_PMC3_PMC39);

    /* ---- P3_10 : A11 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC310_SHIFT,   GPIO_PIBC3_PIBC310);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC310_SHIFT,   GPIO_PBDC3_PBDC310);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM310_SHIFT,       GPIO_PM3_PM310);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC310_SHIFT,     GPIO_PMC3_PMC310);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC310_SHIFT,   GPIO_PIPC3_PIPC310);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC310_SHIFT,   GPIO_PBDC3_PBDC310);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC310_SHIFT,     GPIO_PFC3_PFC310);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE310_SHIFT,   GPIO_PFCE3_PFCE310);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE310_SHIFT, GPIO_PFCAE3_PFCAE310);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC310_SHIFT,   GPIO_PIPC3_PIPC310);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC310_SHIFT,     GPIO_PMC3_PMC310);

    /* ---- P3_11 : A12 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC311_SHIFT,   GPIO_PIBC3_PIBC311);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC311_SHIFT,   GPIO_PBDC3_PBDC311);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM311_SHIFT,       GPIO_PM3_PM311);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC311_SHIFT,     GPIO_PMC3_PMC311);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC311_SHIFT,   GPIO_PIPC3_PIPC311);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC311_SHIFT,   GPIO_PBDC3_PBDC311);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC311_SHIFT,     GPIO_PFC3_PFC311);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE311_SHIFT,   GPIO_PFCE3_PFCE311);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE311_SHIFT, GPIO_PFCAE3_PFCAE311);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC311_SHIFT,   GPIO_PIPC3_PIPC311);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC311_SHIFT,     GPIO_PMC3_PMC311);

    /* ---- P3_12 : A13 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC312_SHIFT,   GPIO_PIBC3_PIBC312);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC312_SHIFT,   GPIO_PBDC3_PBDC312);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM312_SHIFT,       GPIO_PM3_PM312);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC312_SHIFT,     GPIO_PMC3_PMC312);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC312_SHIFT,   GPIO_PIPC3_PIPC312);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC312_SHIFT,   GPIO_PBDC3_PBDC312);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC312_SHIFT,     GPIO_PFC3_PFC312);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE312_SHIFT,   GPIO_PFCE3_PFCE312);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE312_SHIFT, GPIO_PFCAE3_PFCAE312);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC312_SHIFT,   GPIO_PIPC3_PIPC312);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC312_SHIFT,     GPIO_PMC3_PMC312);

    /* ---- P3_13 : A14 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC313_SHIFT,   GPIO_PIBC3_PIBC313);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC313_SHIFT,   GPIO_PBDC3_PBDC313);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM313_SHIFT,       GPIO_PM3_PM313);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC313_SHIFT,     GPIO_PMC3_PMC313);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC313_SHIFT,   GPIO_PIPC3_PIPC313);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC313_SHIFT,   GPIO_PBDC3_PBDC313);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC313_SHIFT,     GPIO_PFC3_PFC313);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE313_SHIFT,   GPIO_PFCE3_PFCE313);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE313_SHIFT, GPIO_PFCAE3_PFCAE313);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC313_SHIFT,   GPIO_PIPC3_PIPC313);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC313_SHIFT,     GPIO_PMC3_PMC313);

    /* ---- P3_14 : A15 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC314_SHIFT,   GPIO_PIBC3_PIBC314);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC314_SHIFT,   GPIO_PBDC3_PBDC314);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM314_SHIFT,       GPIO_PM3_PM314);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC314_SHIFT,     GPIO_PMC3_PMC314);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC314_SHIFT,   GPIO_PIPC3_PIPC314);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC314_SHIFT,   GPIO_PBDC3_PBDC314);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC314_SHIFT,     GPIO_PFC3_PFC314);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE314_SHIFT,   GPIO_PFCE3_PFCE314);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE314_SHIFT, GPIO_PFCAE3_PFCAE314);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC314_SHIFT,   GPIO_PIPC3_PIPC314);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC314_SHIFT,     GPIO_PMC3_PMC314);

    /* ---- P3_15 : A16 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC3,  0, GPIO_PIBC3_PIBC315_SHIFT,   GPIO_PIBC3_PIBC315);
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC315_SHIFT,   GPIO_PBDC3_PBDC315);
    RZA_IO_RegWrite_16(&GPIO.PM3,    1, GPIO_PM3_PM315_SHIFT,       GPIO_PM3_PM315);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   0, GPIO_PMC3_PMC315_SHIFT,     GPIO_PMC3_PMC315);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  0, GPIO_PIPC3_PIPC315_SHIFT,   GPIO_PIPC3_PIPC315);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC3,  0, GPIO_PBDC3_PBDC315_SHIFT,   GPIO_PBDC3_PBDC315);
    RZA_IO_RegWrite_16(&GPIO.PFC3,   0, GPIO_PFC3_PFC315_SHIFT,     GPIO_PFC3_PFC315);
    RZA_IO_RegWrite_16(&GPIO.PFCE3,  0, GPIO_PFCE3_PFCE315_SHIFT,   GPIO_PFCE3_PFCE315);
    RZA_IO_RegWrite_16(&GPIO.PFCAE3, 0, GPIO_PFCAE3_PFCAE315_SHIFT, GPIO_PFCAE3_PFCAE315);
    RZA_IO_RegWrite_16(&GPIO.PIPC3,  1, GPIO_PIPC3_PIPC315_SHIFT,   GPIO_PIPC3_PIPC315);
    RZA_IO_RegWrite_16(&GPIO.PMC3,   1, GPIO_PMC3_PMC315_SHIFT,     GPIO_PMC3_PMC315);

    /* ---- P4_0 : A17 ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC4,  0, GPIO_PIBC4_PIBC40_SHIFT,   GPIO_PIBC4_PIBC40);
    RZA_IO_RegWrite_16(&GPIO.PBDC4,  0, GPIO_PBDC4_PBDC40_SHIFT,   GPIO_PBDC4_PBDC40);
    RZA_IO_RegWrite_16(&GPIO.PM4,    1, GPIO_PM4_PM40_SHIFT,       GPIO_PM4_PM40);
    RZA_IO_RegWrite_16(&GPIO.PMC4,   0, GPIO_PMC4_PMC40_SHIFT,     GPIO_PMC4_PMC40);
    RZA_IO_RegWrite_16(&GPIO.PIPC4,  0, GPIO_PIPC4_PIPC40_SHIFT,   GPIO_PIPC4_PIPC40);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC4,  0, GPIO_PBDC4_PBDC40_SHIFT,   GPIO_PBDC4_PBDC40);
    RZA_IO_RegWrite_16(&GPIO.PFC4,   0, GPIO_PFC4_PFC40_SHIFT,     GPIO_PFC4_PFC40);
    RZA_IO_RegWrite_16(&GPIO.PFCE4,  0, GPIO_PFCE4_PFCE40_SHIFT,   GPIO_PFCE4_PFCE40);
    RZA_IO_RegWrite_16(&GPIO.PFCAE4, 0, GPIO_PFCAE4_PFCAE40_SHIFT, GPIO_PFCAE4_PFCAE40);
    RZA_IO_RegWrite_16(&GPIO.PIPC4,  1, GPIO_PIPC4_PIPC40_SHIFT,   GPIO_PIPC4_PIPC40);
    RZA_IO_RegWrite_16(&GPIO.PMC4,   1, GPIO_PMC4_PMC40_SHIFT,     GPIO_PMC4_PMC40);
 
    /* ---- P2_6 : RD/WR# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC26_SHIFT,   GPIO_PIBC2_PIBC26);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC26_SHIFT,   GPIO_PBDC2_PBDC26);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM26_SHIFT,       GPIO_PM2_PM26);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC26_SHIFT,     GPIO_PMC2_PMC26);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC26_SHIFT,   GPIO_PIPC2_PIPC26);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC26_SHIFT,   GPIO_PBDC2_PBDC26);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC26_SHIFT,     GPIO_PFC2_PFC26);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE26_SHIFT,   GPIO_PFCE2_PFCE26);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE26_SHIFT, GPIO_PFCAE2_PFCAE26);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC26_SHIFT,   GPIO_PIPC2_PIPC26);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC26_SHIFT,     GPIO_PMC2_PMC26);

    /* ---- P2_7 : CS0# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC27_SHIFT,   GPIO_PIBC2_PIBC27);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC27_SHIFT,   GPIO_PBDC2_PBDC27);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM27_SHIFT,       GPIO_PM2_PM27);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC27_SHIFT,     GPIO_PMC2_PMC27);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC27_SHIFT,   GPIO_PIPC2_PIPC27);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC27_SHIFT,   GPIO_PBDC2_PBDC27);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC27_SHIFT,     GPIO_PFC2_PFC27);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE27_SHIFT,   GPIO_PFCE2_PFCE27);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE27_SHIFT, GPIO_PFCAE2_PFCAE27);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC27_SHIFT,   GPIO_PIPC2_PIPC27);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC27_SHIFT,     GPIO_PMC2_PMC27);

    /* ---- P2_8 : RD# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC2,  0, GPIO_PIBC2_PIBC28_SHIFT,   GPIO_PIBC2_PIBC28);
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC28_SHIFT,   GPIO_PBDC2_PBDC28);
    RZA_IO_RegWrite_16(&GPIO.PM2,    1, GPIO_PM2_PM28_SHIFT,       GPIO_PM2_PM28);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   0, GPIO_PMC2_PMC28_SHIFT,     GPIO_PMC2_PMC28);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  0, GPIO_PIPC2_PIPC28_SHIFT,   GPIO_PIPC2_PIPC28);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC2,  0, GPIO_PBDC2_PBDC28_SHIFT,   GPIO_PBDC2_PBDC28);
    RZA_IO_RegWrite_16(&GPIO.PFC2,   0, GPIO_PFC2_PFC28_SHIFT,     GPIO_PFC2_PFC28);
    RZA_IO_RegWrite_16(&GPIO.PFCE2,  0, GPIO_PFCE2_PFCE28_SHIFT,   GPIO_PFCE2_PFCE28);
    RZA_IO_RegWrite_16(&GPIO.PFCAE2, 0, GPIO_PFCAE2_PFCAE28_SHIFT, GPIO_PFCAE2_PFCAE28);
    RZA_IO_RegWrite_16(&GPIO.PIPC2,  1, GPIO_PIPC2_PIPC28_SHIFT,   GPIO_PIPC2_PIPC28);
    RZA_IO_RegWrite_16(&GPIO.PMC2,   1, GPIO_PMC2_PMC28_SHIFT,     GPIO_PMC2_PMC28);


    /* ---- P7_1 : CS1# ---- */
    /* Port initialize */
    RZA_IO_RegWrite_16(&GPIO.PIBC7,  0, GPIO_PIBC7_PIBC71_SHIFT,   GPIO_PIBC7_PIBC71);
    RZA_IO_RegWrite_16(&GPIO.PBDC7,  0, GPIO_PBDC7_PBDC71_SHIFT,   GPIO_PBDC7_PBDC71);
    RZA_IO_RegWrite_16(&GPIO.PM7,    1, GPIO_PM7_PM71_SHIFT,       GPIO_PM7_PM71);
    RZA_IO_RegWrite_16(&GPIO.PMC7,   0, GPIO_PMC7_PMC71_SHIFT,     GPIO_PMC7_PMC71);
    RZA_IO_RegWrite_16(&GPIO.PIPC7,  0, GPIO_PIPC7_PIPC71_SHIFT,   GPIO_PIPC7_PIPC71);
    /* Port mode : Multiplex mode                     */
    /* Port function setting : 1st multiplex function */
    /* I/O control mode : Peripheral function         */
    /* Bidirectional mode : Disable                   */
    RZA_IO_RegWrite_16(&GPIO.PBDC7,  0, GPIO_PBDC7_PBDC71_SHIFT,   GPIO_PBDC7_PBDC71);
    RZA_IO_RegWrite_16(&GPIO.PFC7,   0, GPIO_PFC7_PFC71_SHIFT,     GPIO_PFC7_PFC71);
    RZA_IO_RegWrite_16(&GPIO.PFCE7,  0, GPIO_PFCE7_PFCE71_SHIFT,   GPIO_PFCE7_PFCE71);
    RZA_IO_RegWrite_16(&GPIO.PFCAE7, 0, GPIO_PFCAE7_PFCAE71_SHIFT, GPIO_PFCAE7_PFCAE71);
    RZA_IO_RegWrite_16(&GPIO.PIPC7,  1, GPIO_PIPC7_PIPC71_SHIFT,   GPIO_PIPC7_PIPC71);
    RZA_IO_RegWrite_16(&GPIO.PMC7,   1, GPIO_PMC7_PMC71_SHIFT,     GPIO_PMC7_PMC71);

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

        return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_ini_io_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　Ｔｉｍｅｒ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－１
//  【ヘッダ説明】
//      タイマ関連定義
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#ifndef	__TIMER_H
//-------------------------------------------------
#define	__TIMER_H

#define  CD_TIME  1000
//#define MOTOR_OFF_TIME 2000   //2000 * 5ms = 10000ms 2007.1.17削除移植
//#define MOTOR_OFF_TIME 380   //380 * 5ms = 1900ms 2007.1.17変更 2007.1.17移植
//#define MOTOR_OFF_TIME 800   //800 * 5ms = 4000ms 2007.1.17変更 2007.1.17移植 //2007.5.8 test
#define MOTOR_OFF_TIME 5   //5 * 5ms = 25ms 2019.05.30
//#define MOTOR_OFF_TIME 100   //800 * 5ms = 4000ms 2007.1.17変更 2007.1.17移植 //2007.5.8 test 
//#define MOTOR_OFF_TIME 10   //10 * 5ms = 50ms 2009.02.25 


//#define  PRE_FLOW_TIME 30
#define  PRE_FLOW_TIME 50   //2006.12.8 ihara
#define  AFTER_FLOW_TIME 100

struct Timer{
	unsigned long	_BaseClock;
	unsigned long	_100u;
	unsigned long	_1m;
	unsigned long	_10m;
	unsigned long	_50m;
	unsigned long	_100m;
	unsigned long	_200m;
        unsigned long   _300m; //2009.12.17
	unsigned long	_500m;
	unsigned long	_ADtimer;
};


#if 1 //2019.04.08 サンプルコードからコピー
/* チャンネル */
enum TIMER_CH {
	TIMER_CH0 = 0,
	TIMER_CH1 = 1,
};

/* 動作モード */
enum TIMER_MODE {
	TIMER_MODE_INTERVAL = 0,
	TIMER_MODE_FREERUN  = 1,
};

/* エラーコード */
enum TIMER_ERROR_CODE {
	TIMER_ERR_NONE = 0,
	TIMER_ERR_NO_SUPPORT = -1,

	TIMER_ERR_ILLIGAL_ARGUMENT = -10,
};

/* プロトタイプ宣言 */
int timer_init(void);
int timer_set(unsigned int ch, unsigned int mode, unsigned int cycle);
int timer_stop(unsigned int ch);
int timer_start(unsigned int ch);
int timer_get_int_count(unsigned long *count, unsigned int ch);


void timer_wait(unsigned long delay);

#endif


// 使用変数の宣言(実体宣言用or外部参照用)
#ifdef __TIMER_PROG
	// 使用変数実体宣言部
	//
	struct				Timer	Timer;		// タイマデータ
#else
	// 外部参照可能モジュール宣言部
	//

	// 外部参照可能変数宣言部
	//
	extern struct		Timer	Timer;		// タイマデータ
#endif

//-------------------------------------------------
#endif	// __TIMER_H
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of Timer.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

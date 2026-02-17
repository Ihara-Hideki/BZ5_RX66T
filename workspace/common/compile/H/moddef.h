//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　ｍｏｄｄｅｆ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－１
//  【ヘッダ説明】
//      各種状態コード定義
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


#if 0  //2007.6.28削除　ロボットに転送するＶｅｒと一元化するため
//---------------------------------- Ｍ３２プログラムＶｅｒ ----------------------------------------------
#define M32_PROGRAM_VER               (unsigned short)000      //2007.2.13追加 2007.2.16変更 2007.2.17変更 
                                                               //2007.2.19変更
                                                               //2007.3.1変更
                                                               //2007.3.2変更
                                                               //2007.3.14変更
                                                               //2007.3.15変更
                                                               //2007.3.19変更
                                                               //2007.3.20変更
                                                               //2007.3.22変更 モータエラー変更
                                                               //2007.3.22 FIX Ver0.00 不具合があったのでのＦＩＸ取り下げ
                                                               //2007.3.23
                                                               //2007.3.28 FIX Ver0.00
//--------------------------------------------------------------------------------------------------------
#endif



#define ERR_MASK_TIME                  (unsigned int)20		
#define POWER_TIME                     (unsigned int)20         //5mS* 20  =  100mS
#define WATER_TIME                     (unsigned int)20         //5mS* 20  =  100mS
#define GAS_TIME                       (unsigned int)20         //5mS* 20  =  100mS
#define THP_TIME                       (unsigned int)36         //5mS* 36  =  180mS
#define EMG_TIME                       (unsigned int)20         //5mS* 20  =  100mS
//#define VP_TIME	                       (unsigned int)100         //5mS* 60  =  300mS  2007.2.13 500msに変更
#define VP_TIME	                       (unsigned int)60         //5mS* 60  =  300mS  2007.2.13 500msに変更 2007.3.6 300msに戻す。2007.3.13移植
//#define ARC_START_TIME                 (unsigned int)800        //5mS* 800 = 4000mS 2007.1.18削除移植 
#define ARC_START_TIME                 (unsigned int)40         //5mS* 40  =  200mS  //2007.1.18変更移植
#define FAN_OFF_TIME                   (unsigned int)840        //500mS * 840 = 420S
//------ Phase9 by @Tny 2008/09/12 ------
#if true
#define FAN_A_OFF_TIME                 (unsigned int)5          //100mS * 30 = 3S 2008.12.18 30->5
#endif
//---------------------------------------------------------------------

#define START_UNIT_DELAY_TIME          (unsigned short)10       //100μｓ／count 2008.11.14 1ms

#define TABLE_DATA_OUTPUT_TIME         (unsigned int)50         //0.1mS * 50 = 5mS
#define R8_SEND_TIMING_TIME            (unsigned int)100        //0.1mS * 100 = 10mS
#define ERR_DISP_CHENGE_TIMING_TIME    (unsigned int) 200       //5mS * 200 = 1000mS
#define VER_DISP_CHENGE_TIMING_TIME    (unsigned int) 60        //5mS * 200 = 1000mS 2007.2.13追加 　2007.4.5　６０に変更  2007.4.6　４０に変更
#define SOC_LEVEL_200                  (unsigned short)364      //(420A)

#define TOCH_SW_OFF_DELAY_TIME         (unsigned int)150        //1mS * 150 = 150mS 2007.2.24追加
#define STICK_CHECK_DELAY_TIME         (unsigned int)200        //1mS * 200 = 200mS 2007.2.24追加

#define PRI_VOLT_ERR_COM_DELAY_TIME    (unsigned char)100       //10mS * 150 = 1500mS 2007.3.6追加　100に変更2007.3.13 2007.3.13移植

#define COM_ERR_COUNT                  (unsigned char)5         //パリティー、フレーミングエラー検出回数 2007.2.26追加


//#define CD_CHECK_TIME                  (unsigned int)700        //700ms  2007.1.24 2007.1.26移植追加
//#define CD_CHECK_TIME                  (unsigned int)500        //500ms  2009.02.18 
#define CD_CHECK_TIME                  (unsigned int)25         //25ms  2009.03.17 
#define CD_CHECK_TIME2                 (unsigned int)100        //100ms 2010.02.18 
//#define CD_CHECK_TIME                  (unsigned int)2000        //2000ms  2009.02.18 
//#define PRI_CURR_FB_COUNTER            (unsigned short)50     //一次電流ＦＢ値平均回数（一回のＲ８との通信間隔は１０ｍＳなので５００ｍＳ後に確定する）2007.1.26移植削除
#define PRI_CURR_FB_COUNTER            (unsigned short)20       //一次電流ＦＢ値平均回数（一回のＲ８との通信間隔は１０ｍＳなので２００ｍＳ後に確定する）2007.1.18 2007.1.26移植変更
#define PRI_CURR_FB_MIN                (unsigned short)50       //一次電流ＦＢ値最低値
#define PRI_CURR_FB_MAX                (unsigned short)1000     //一次電流ＦＢ値最大値
//#define PRI_CURR_FB_ERR_TIME           (unsigned int)200      //5mS * 200 = 1000mS
#define PRI_CURR_FB_ERR_TIME           (unsigned int)300        //5mS * 300 = 1500mS 2007.7.10変更
#define PRI_CURR_FB_ERR_UNB_TIME       (unsigned int)6          //5mS * 6 = 30mS   2007.3.14　ＰＯ版より移植
#define R8_COM_ERR_TIME                (unsigned int)100        //5mS * 100 = 500mS

//#define PRI_CURR_FB_START_ERR_TIME     (unsigned char)80        //5mS * 80 = 400mS  2007.4.17
//#define PRI_CURR_FB_START_ERR_TIME     (unsigned char)200       //5mS * 200 = 1000mS  2007.5.10
#define PRI_CURR_FB_START_ERR_TIME     (unsigned int)300        //5mS * 300 = 1500mS  2007.7.10変更 char→intに変更
#define CT_ERR_MASK_TIME               (unsigned int)200        //5mS * 200 = 1000mS  2008.10.20 追加



#define UNBALANCE_DETECT_CURRENT_HI    (unsigned short)100      //200A　2007.1.18 100A 2007.1.24 2007.1.26移植追加　2007.2.10変更
#define UNBALANCE_DETECT_CURRENT_MD    (unsigned short)70       //70A　2007.2.10追加
#define UNBALANCE_DETECT_CURRENT_LO    (unsigned short)40       //40A　2007.2.10追加
#define UNBALANCE_MIN_RATE_HI          (unsigned int)30         //40%   2007.1.18  30% 2007.1.24 2007.1.26移植追加　2007.2.10変更
#define UNBALANCE_MAX_RATE_HI          (unsigned int)70         //60%   2007.1.18  70% 2007.1.24 2007.1.26移植追加　2007.2.10変更
#define UNBALANCE_MIN_RATE_MD          (unsigned int)20         //20%   2007.2.10追加
#define UNBALANCE_MAX_RATE_MD          (unsigned int)80         //80%   2007.2.10追加
#define UNBALANCE_MIN_RATE_LO          (unsigned int)10         //10%   2007.2.10追加
#define UNBALANCE_MAX_RATE_LO          (unsigned int)90         //90%   2007.2.10追加

#define VP_AVG_COUNTER                 (unsigned short)100      //一次入力電圧平均回数

//#define MOTOR_CURRENT_AVG_COUNTER      (unsigned short)100      //モータ電流平均回数
#define MOTOR_CURRENT_AVG_COUNTER      (unsigned short)5000     //モータ電流平均回数      2007.1.15　５０回に変更 2007.1.17移植 　　2007.3.20　５００回に変更ｰ>５０００回に変更
//#define MOTOR_CURRENT_ERR_LEVEL        (unsigned int)500        //モータ電流エラーレベル
#define MOTOR_CURRENT_ERR_LEVEL        (int)327                 //モータ電流エラーレベル  2007.1.15　とりあえず２５０に変更 2007.1.17移植
                                                                //１０Ａ＝２Ｖ（４０９ｂｉｔ）　現在±６．１Ａ検出される。250    2007.3.22 327
#define MOTOR_CURRENT_ERR_TIME         (unsigned int)100        //5mS* 100 = 500mS
#define MOTOR_CURRENT_CENTER           (int)512                 //モータ電流Ａ／Ｄ値センター 2007.1.15 2007.1.17移植

#define MOTOR_CURR_BIT                 (float)0.244             //モータ電流のＡ／Ｄ読み値はｂｉｔ当たり０．０２４４Ａであるが、ロボットへの送信値は
                                                                //１ｂｉｔ当たり０．１Ａであるので予め１０倍した値にした。　2007.3.1追加

#define REPEAT_WELD_TIME               (unsigned int)20         //100mS* 20 = 2000mS   REPEAT 2007.1.12

//#define GAS_LIMIT_TIME                 (unsigned short)900      //100mS* 900 = 90000mS ガスチェック時間９０秒
#define GAS_LIMIT_TIME                 (unsigned short)600      //100mS* 600 = 60000mS ガスチェック時間６０秒　2008.11.25

#define VOLTAGE_DETECT_ERROR_LEVEL 0x10    //電圧検出異常レベル


//高周波関連 2009.01.31
#define HF_2SEC_TIME                   (short)200               // 200 * 10ms =  2000ms
#define HF_30SEC_TIME                  (short)3000              //3000 * 10ms = 30000ms
#define HF_30SEC_INTERVAL_TIME         (short)200               // 200 * 10ms =  2000ms
#define HF_INTERMITTENT_TIME           (short)100               // 100 * 10ms =  1000ms

//Ｗクリック関連 2009.02.05
#define W_CLICK_TIME                   (short)50                //  50 * 10ms =   500ms


//エキスパートモード関連 2009.02.10
#define V_LIMIT_VALUE                  (float)0.33
#define A_VALUE                        (float)-0.007246
#define C_VALUE                        (float)1.14492

//電極短絡チェック 2009.03.13
#define ELECTRODE_SHORT_CHECK_TIME     (short)100               //100 * 10ms = 1000ms

//可変反復ＴＳチェック 2009.03.14
#define TS_CHECK_TIME                  (short)50                //50 * 10ms  = 500ms

#if 001
#define SOC_LEVEL_350                  (unsigned short)390	/*(460A)	300A =260data	460A = 390*/
#define SOC_LEVEL_350L                 (unsigned short)350	/*(450A)	300A =260data	460A = 390*/
#else
#define SOC_LEVEL_350                  (unsigned short)420	/*(450A)	300A =260data	460A = 390*/
#endif
#define SOC_LEVEL_500	               (unsigned short)477	/*(550A)		*/
#define SOC_TIME		       (unsigned char)40	/*5mS* 40= 200mS	*/
#define SOC_TIME_L		       (unsigned char)200	/*5mS* 20= 100mS	*/

#if 000
#define VP_MIN_IDL		(unsigned short)420	/*待機中低電圧検出レベル(200V) = 165V	*/
#define VP_MAX_IDL		(unsigned short)740	/*溶接中過電圧検出レベル(200V) = 240V	*/
#define VP_MIN_WEL		(unsigned short)420 /*待機中低電圧検出レベル(200V) = 165V	*/
#define VP_MAX_WEL		(unsigned short)740	/*溶接中過電圧検出レベル(200V) = 240V	*/
#else
#define VP_MIN_IDL		(unsigned short)478 /*待機中低電圧検出レベル(200V) = 170V 2007.07.24修正*/
#define VP_MAX_IDL		(unsigned short)732 /*溶接中過電圧検出レベル(200V) = 253V 2008.11.27 720 ->732*/
#define VP_MIN_WEL		(unsigned short)478 /*待機中低電圧検出レベル(200V) = 170V 2007.07.24修正*/
#define VP_MAX_WEL		(unsigned short)732 /*溶接中過電圧検出レベル(200V) = 253V 2008.11.27 720 ->732*/
/*#define VP_MIN_IDL		(unsigned short)400 待機中低電圧検出レベル(200V) = 170V 2007.07.24修正　　実験用 2009.02.09*/
/*#define VP_MAX_IDL		(unsigned short)800 溶接中過電圧検出レベル(200V) = 253V 2008.11.27 720 ->732 実験用 2009.02.09*/
/*#define VP_MIN_WEL		(unsigned short)400 待機中低電圧検出レベル(200V) = 170V 2007.07.24修正 実験用 2009.02.09*/
/*#define VP_MAX_WEL		(unsigned short)800 溶接中過電圧検出レベル(200V) = 253V 2008.11.27 720 ->732 実験用 2009.02.09*/
#endif


//*********************************** 微調整項目１，２係数 2007.2.5 ***************************************
//AZ3より詳細データの係数もここに記載する。
#define TS0             (float)100.0        //短絡初期時間調整係数
#define ISC             (float)1.0          //短絡電流屈折値調整係数 2.0→1.0に変更　2007.5.11
#define ISL1            (float)1.0          //短絡電流勾配１調整係数 2.0→1.0に変更　2007.5.11
#define ISL2            (float)1.0          //短絡電流勾配２調整係数 2.0→1.0に変更　2007.5.11

#define HOTCUR          (float)43.69        //ホット電流調整係数     52.4272(2A)→26.2136(1A)に変更　2007.5.11  2008.10.24   2008.11.26 100->43.69に変更
#define HOTVLT          (float)0.1          //ホット電圧調整係数
#define HOTTM           (short)50           //ホット時間調整係数                  2008.10.24   2008.11.26 1->50に変更
#define HOTTM2          (short)50           //ホット時間２調整係数 2008.10.16     2008.10.24   2008.11.26 1->50に変更
#define WIRSLDN         (short)100          //ワイヤスローダウン調整係数
#define FTTLVL          (float)43.69        //ＦＴＴレベル調整係数   52.4272(2A)→26.2136(1A)に変更　2007.5.11  2008.11.26 43.69に変更
#define BBKTIME         (short)100          //バーンバック時間調整係数

#define PENETRATION     (float)100.0        //溶け込み調整             V5  2008.10.09 2008.10.24
#define PULSE_PEAK_CUR  (float)1.0          //パルスピーク電流調整     V18 2008.10.09
#define PULSE_BASE_CUR  (float)1.0          //パルスベース電流調整     V20 2008.10.09
#define PULSE_RISE_CUR  (float)0.1          //パルス立ち上がり調整     V27 2008.10.09 2008.10.24
#define PULSE_FALL_CUR  (float)0.1          //パルス立ち下がり調整     V28 2008.10.09 2008.10.24
#define PULSE_START_VOLT (float)0.1         //パルススタート電圧調整   V57 2008.10.09 2008.10.24
#define WAVE_CONTROL1   (float)1.0          //波形制御                 V32 2008.10.10
#define PULSE_FREQ      (float)1.0          //パルス周波数             V13 2008.10.10 2008.10.24  2008.11.26 10.0->1.0に変更
#define PULSE_WIDTH     (float)10.0         //パルスピーク時間調整     V15 2008.10.10   2008.11.26 1.0 -> 10.0に変更
#define EN_CUR          (float)1.0          //ＥＮ電流微調整           V84 2008.10.14
#define WAVE_CONTROL2   (float)1.0          //波形制御2                V34 2008.10.14
#define INIT_IB         (float)43.69        //スタートベース調整値     V108 2008.10.16    2008.10.24  2008.11.26 100->43.69
#define INIT_IP         (float)43.69        //スタートピーク調整値     V107 2008.10.16  2008.10.24  2008.11.26 100->43.69
#define PRISE           (float)10.0         //パルスライズ時間調整     V14 2008.10.16     2008.10.24
#define PFALL           (float)10.0         //パルスフォール時間調整   V15 2008.10.16     2008.10.24
#define INIT_PFRQ       (float)1.0          //アークスタート時のパルス周波数調整 H63  2008.10.16    2008.10.24 2008.11.26 100.0->1.0
#define INIT_PFRQ2      (float)1.0          //アークスタート時のパルス周波数調整 H113 2008.10.16    2008.10.24 2008.11.26 100.0->1.0
#define NECKLVL         (float)0.01         //ネック検出ＯＮ／ＯＦＦと検出レベル調整 V52 2008.10.16 2008.10.24 2008.11.26 0.1->0.01
#define NECKLVL2        (float)5.24288      //ネック検出ＯＮ／ＯＦＦと検出レベル調整 H166 2008.11.26
#define SA_LEVEL        (float)0.1          //ＳＡレベル、延長対応用   V53 2008.10.16               2008.10.24
#define SA_LEVEL2       (float)0.1          //ＳＡレベル、延長対応用   V55 2008.11.26
#define AS_LEVEL        (float)0.1          //ＡＳレベル、延長対応用   V9  2008.10.16               2008.10.24
#define AS_LEVEL2       (float)0.1          //ＡＳレベル、延長対応用   V54 2008.11.26
#define START_TIME      (float)1.0          //送給ディレイ時間 2008.10.24 2008.11.26 10.0->1.0
#define IAC             (float)43.69        //ＩＡＣ 2008.11.26

//*********************************** 拡張溶接微調パラメータ係数 2007.5.29 *********************************
//AZ3より詳細データの係数もここに記載する。
#define SP_I            (float)1.0          //ＳＰ電流係数
#define SP_I2           (float)1.0          //ＳＰ電流係数     2008.11.26
#define SP_T            (float)10.0         //ＳＰ時間係数     2008.10.24  2008.11.26 1.0->10.0
#define ELI             (float)1.0          //ＥＬＩ係数
#define MTS_V           (float)0.05         //重畳電圧値係数
#define MTS_ONTIME      (float)10.0         //重畳電圧ＯＮ時間係数
#define MTS_CYCLE       (float)10.0         //重畳電圧周期


//2007.2.5時点　可変パラメータ
#define TS0_NO              (unsigned short)5   //パラメータ５
#define ISC_NO              (unsigned short)36  //パラメータ３６
#define ISL1_NO             (unsigned short)32  //パラメータ３２
#define ISL2_NO             (unsigned short)34  //パラメータ３４
#define HOTVLT_NO           (unsigned short)56  //パラメータ５６
#define HOTVLT2_NO          (unsigned short)57  //パラメータ５７ 2008.11.26追加
#define PENETRATION_NO      (unsigned short)5   //パラメータ５ 2008.10.09
#define PULSE_PEAK_CUR_NO   (unsigned short)18  //パルスピーク電流調整   2008.10.09
#define PULSE_BASE_CUR_NO   (unsigned short)20  //パルスベース電流調整   2008.10.09
#define PULSE_RISE_CUR_NO   (unsigned short)27  //パルス立ち上がり調整   2008.10.09
#define PULSE_FALL_CUR_NO   (unsigned short)28  //パルス立ち下がり調整   2008.10.09
#define PULSE_START_VOLT_NO (unsigned short)57  //パルススタート電圧調整 2008.10.09
#define WAVE_CONTROL1_NO    (unsigned short)32  //波形制御               2008.10.10
#define WAVE_CONTROL1_2_NO  (unsigned short)45  //波形制御               2008.11.26
#define PULSE_FREQ_NO       (unsigned short)13  //パルス周波数           2008.10.10
#define PULSE_WIDTH_NO      (unsigned short)15  //パルスピーク時間調整   2008.10.10
#define EN_CUR_NO           (unsigned short)84  //ＥＮ電流微調整         2008.10.14
#define WAVE_CONTROL2_NO    (unsigned short)34  //波形制御2              2008.10.14
#define PRISE_NO            (unsigned short)14  //パルスライズ時間調整   2008.10.16
#define PFALL_NO            (unsigned short)16  //パルスフォール時間調整 2008.10.16
#define NECKLVL_NO          (unsigned short)52  //ネック検出ＯＮ／ＯＦＦと検出レベル調整 2008.10.16
#define SA_LEVEL_NO         (unsigned short)53  //ＳＡレベル、延長対応用 2008.10.16
#define SA_LEVEL2_NO        (unsigned short)55  //ＳＡレベル、延長対応用 2008.11.26
#define AS_LEVEL_NO         (unsigned short)9   //ＡＳレベル、延長対応用 2008.10.16
#define AS_LEVEL2_NO        (unsigned short)54  //ＡＳレベル、延長対応用 2008.11.26


//2007.2.5時点　半固定パラメータ
#define HOTCUR_NO           (unsigned short)36  //パラメータ３６
#define HOTTM_NO            (unsigned short)38  //パラメータ３８
#define HOTTM2_NO           (unsigned short)83  //パラメータ８３　2008.10.16
#define FTTLVL_NO           (unsigned short)51  //パラメータ５１
#define FTTLVL2_NO          (unsigned short)92  //パラメータ９２
#define BBKTIME_NO          (unsigned short)61  //パラメータ６１
#define BBKTIME2_NO         (unsigned short)105 //パラメータ１０５ 2008.11.26追加
#define BBKTIME3_NO         (unsigned short)10  //パラメータ１０   2008.11.26追加
#define INIT_IB_NO          (unsigned short)108 //パラメータ１０８ 2008.10.16
#define INIT_IP_NO          (unsigned short)107 //パラメータ１０７ 2008.10.16
#define ENDPLS_NO           (unsigned short)82  //パラメータ８２ 2008.10.16
#define ENDPLS2_NO          (unsigned short)85  //パラメータ８５ 2008.11.27
#define INIT_PFRQ_NO        (unsigned short)63  //パラメータ６３ 2008.10.16
#define INIT_PFRQ2_NO       (unsigned short)113 //パラメータ１１３ 2008.10.16
#define INPLSE_START_SW_NO  (unsigned short)317 //パラメータ３１７ 2008.11.26
#define CDM_NO              (unsigned short)316 //パラメータ３１６ 2008.11.26
#define IAC_NO              (unsigned short)315 //パラメータ３１５ 2008.11.26
#define NECKLVL2_NO         (unsigned short)166 //ネック検出ＯＮ／ＯＦＦと検出レベル調整 2008.11.26
#define PCTRLBLOW_NO        (unsigned short)132 //アークブロー抑制制御 2008.11.26
#define STARTPLS_NO         (unsigned short)84  //パラメータ８４ 2008.11.27
#define BURNBACK_AC_NO      (unsigned short)366 //パラメータ３３６ 2008.12.11

//2007.5.29時点　拡張溶接微調パラメータ
#define SP_I_NO         (unsigned short)61  //ＳＰ電流係数　　　　　パラメータ６１（ＩＤ：０００１）
#define SP_T_NO         (unsigned short)63  //ＳＰ時間係数　　　　　パラメータ６３（ＩＤ：０００２）
#define ELI_NO          (unsigned short)8   //ＥＬＩ係数　　　　　　パラメータ８　（ＩＤ：０００３）
#define MTS_V_NO        (unsigned short)57  //重畳電圧値係数　　　　パラメータ５７（ＩＤ：０００４）
#define MTS_ONTIME_NO   (unsigned short)16  //重畳電圧ＯＮ時間係数　パラメータ１６（ＩＤ：０００５）
#define MTS_CYCLE_NO    (unsigned short)17  //重畳電圧周期　　　　　パラメータ１７（ＩＤ：０００６）
#define SP_I2_NO        (unsigned short)7   //ＳＰ電流係数　　　　　パラメータ７　（ＩＤ：？？？？） 2008.11.26

//*********************************************************************************************************


//********************************************* 名称定数 **************************************************
/*     welding_method_setting_data       7:    6:MIG  5:MAG  4:CO2   3:   2:   1:    0:   */
#define  CO2             0x10
#define  MAG             0x20
#define  MIG             0x40
/*     wire_diameter_setting_data       7:    6:   5:   4:   3:0.8mm  2:0.9mm  1:1.0mm  0:1.2mm */
#define  D12MM            0x01
#define  D10MM            0x02
#define  D09MM            0x04
#define  D08MM            0x08
/*     wire_material_setting_data      7:   6:  5:  4:SP  3:ｽﾃﾝﾚｽFCW  2:ｽﾃﾝﾚｽ  1:軟鋼FCW  0:軟鋼*/
#define  STEEL           0x01
#define  FCW_STEEL       0x02
#define  SUS             0x04
#define  FCW_SUS         0x08
#define  SP              0x10
/*     okcv_setting_data     7:  6:  5:  4:  3:  2:  1:個別  0:一元*/
//#define  OKCV            0x01
//#define  INDE            0x02

//***************************** 時間定数 *******************************
#define _1msec 10
#define _2msec 20
#define _5msec 50
#define _10msec 100
#define _20msec 200
#define _30msec 300
#define _40msec 400
#define _50msec 500
#define _100msec 1000
#define _200msec 2000
#define _300msec 3000
#define _400msec 4000
#define _500msec 5000
#define _1000msec 10000
#define _2000msec 20000
#define _3000msec 30000
#define _4000msec 40000
#define _3800msec 43000
#define _5000msec 50000
#define _6000msec 60000
#define _30000msec 300000
#define _60000msec 600000
//**********************************************************************

//************************* エラーコード一覧 ***************************
/*エラーコード一覧*/
#define EMERGENCY_STOP_ERR      1    /*非常停止*/
#define SEC_OVER_CURRENT_ERR    2    /*二次過電流異常*/
#define ABNORMAL_TEMP_ERR       3    /*温度上昇異常*/
#define PRI_OVER_VOLTAGE_ERR    4    /*一次過電圧異常*/
#define PRI_LOW_VOLTAGE_ERR     5    /*一次低電圧異常*/
#define ARC_START_ERR           6    /*アークスタート異常*/
#define START_UP_SIGNAL_ERR     7    /*トーチスイッチ異常*/
#define CURRENT_DETECT_ERR      8    /*電流検出異常*/
#define PRI_SHUT_DOWN           9    /*瞬停異常*/
#define OUTSIDE_STOP1_ERR      10    /*外部一時停止１*/
#define OUTSIDE_STOP2_ERR      11    /*外部一時停止２*/
/*#define VOID12_ERR             12    空き*/
#define PRI_OVER_CURRENT_ERR   12    /*一次過電流異常 2008.11.17*/
/*#define VOID13_ERR             13    空き*/
#define SEC_OVER_VOLTAGE_ERR   13    /*二次過電圧異常 2008.11.17*/
#define RS422_SENDING_ERR      14    /*４２２シリアル通信送信エラー*/
#define RS422_PARITY_ERR       15    /*４２２シリアル通信パリティーエラー*/
#define RS422_OVER_RUN_ERR     16    /*４２２シリアル通信オーバーランエラー*/
#define RS422_TIME_OUT_ERR     17    /*４２２シリアル通信タイムアウトエラー*/
#define ELROD_SHORT_ERR        18    /*電極短絡異常 2009.07.24新規追加*/
#define VOID19_ERR             19    /*空き*/
#define VOID20_ERR             20    /*空き*/
#define VOID21_ERR             21    /*空き*/
#define SYSTEM_BREAK_ERR       22    /*システムブレイク*/
#define VOID23_ERR             23    /*空き*/
#define VOID24_ERR             24    /*空き*/
#define ENCODER_DETECT_ERR     25    /*エンコーダ検出異常*/
#define MORTOR_STOP_ERR        26    /*モータ停止異常*/
#define MORTOR_CONTROL_ERR     27    /*モータ回転異常*/
#define WATCH_DOG_TIMER_ERR    28    /*ウォッチドックタイマエラー*/
#define RS422_COMMAND_ERR      29    /*４２２シリアル通信コマンドエラー*/
#define RS422_RECV_ERR         30    /*４２２シリアル通信受信エラー*/
#define VOID31_ERR             31    /*?*/
#define VOID32_ERR             32    /*?*/
#define SYSTEM_ERR             50    /*プロセス間(26A-62P間)通信エラー*/
#define REST62P_ERR            51    /*６２Ｐ不測リセットエラー*/
#define REST26A_ERR            52    /*２６Ａ不測リセットエラー*/
#define ERR_CLEAR               0    //異常解除

#define RS422_OVR_ERR          60
#define RS422_PTY_ERR          61
#define RS422_FLM_ERR          62
#define RS232_OVR_ERR          63
#define RS232_PTY_ERR          64
#define RS232_FLM_ERR          65
#define STICK_ERR              66                //スティック発生
#define ARC_ERR                67
#define PRI_CURR_FB1_ERR       68      //2007.1.18復活 2007.1.26移植復活
//#define PRI_CURR_FB2_ERR       69
//#define PRI_CURR_FB1_ERR       1       //動作確認のため一時的に非常停止と同じ割り当てとする（2006.11.9）2007.1.18削除 2007.1.26移植削除
#define PRI_CURR_FB2_ERR       1       //動作確認のため一時的に非常停止と同じ割り当てとする（2006.11.9）
#define R8_COM_ERR             70      //2007.1.15復活 2007.1.17移植
#define EMERGENCY2_STOP_ERR    80     /*非常停止2 2007.2.9*/
#define CONTROLLER_NON_CONNECT 81       // コントローラ未接続（短絡子無し）  Phase26 by @Tny 2008.10.23
#define IIF_CONNECT_ERR		 	82		// ＩＩＦの接続異常（一旦認識されたＩＩＦの接続が何らかの理由で切断した場合に発生） EXTERNAL IIF NEW 2011.02.21 by @Tny
//#define R8_COM_ERR             1       //動作確認のため一時的に非常停止と同じ割り当てとする（2006.11.9）
//#define R8_COM_ERR             0       //SG1による３０００個データ回収を行うと動作するのでエラー無しを割り当てる（2006.11.27）
//----------------------------------------------------------------------
#define ERR_LEVEL0_ADD_CODE    0x0000      //エラーレベル０付加コード
#define ERR_LEVEL1_ADD_CODE    0x0100      //エラーレベル１付加コード
#define ERR_LEVEL2_ADD_CODE    0x0200      //エラーレベル２付加コード
#define ERR_LEVEL3_ADD_CODE    0x0300      //エラーレベル３付加コード
#define ERR_LEVEL0_NON_CODE    0xFFFF      //エラーレベル０削除コード
#define ERR_LEVEL1_NON_CODE    0xEFFF      //エラーレベル１削除コード 11101111 11111111
#define ERR_LEVEL2_NON_CODE    0xDFFF      //エラーレベル２削除コード 11011111 11111111
#define ERR_LEVEL3_NON_CODE    0xCFFF      //エラーレベル３削除コード 11001111 11111111
#define ERR_LEVEL0             0           //エラーレベル０
#define ERR_LEVEL1             1           //エラーレベル１
#define ERR_LEVEL2             2           //エラーレベル２
#define ERR_LEVEL3             3           //エラーレベル３
//**********************************************************************

//************************ 溶接シーケンス一覧 **************************
#define IDLING                0   //待機中
#define PRE_FLOW              1   //プリフロ－中
//#define SLOW_DOWN             2   //スロ－ダウン・シ－ケンス
#define HF_CTRL               2   //高周波 2009.01.31
#define INITIAL_DELAY         3   //スタ－ト制御（１）中
#define MAIN_SLOPE_WELD       4   //本溶接スロープ中
#define INITIAL_WELD          5   //初期制御中
//#define INITOMAIN_SLOPE       6   //初期溶接から本溶接へのスロープ
#define UP_SLOPE              6   //初期溶接から本溶接へのスロープ 2009.02.02
#define MAIN_WELD             7   //本溶接中
#define HOLD_WELD             8   //自己保持中
//#define HOLDTOCRA_SLOPE       9   //本溶接からクレータ溶接へのスロープ
#define DOWN_SLOPE            9   //本溶接からクレータ溶接へのスロープ 2009.02.02
#define CRATER_WELD          10   //クレ－タ中
//#define ARC_SPOT_WELD        11   //ア－クスポット中
#define HAND_STICK           11   //直流手溶接 2009.03.06
//#define BURN_BACK_DELAY		12  バ－ンバック中
#define BURN_BACK            12   //バ－ンバック中*
#define BURN_BACK_PULSE      13   //パルス破断中
#define AFTER_FLOW           14   //アフタ－フロ－中
#define IDLING2              15   //待機中
#define START_WELD           16   //スタート溶接 2008.08.05
//**********************************************************************

//**************************** 制御法一覧 ******************************
#define	NO_SELF_HOLD          1  //制御法　自己保持無し
#define	ARC_SPOT              2  //制御法　ア－クスポット
#define	SELF_HOLD             3  //制御法　自己保持有り
#define	PULSE_SELF_HOLD       4  //制御法　パルス自己保持有りVer 0.3
#define	INI_SELF_HOLD         5  //制御法　自己保持有り
#define	CRTRT_SELF_HOLD       6  //制御法　自己保持有り
#define	CRTRT_INISELF_HOLD    7  //制御法　初期有り、クレータリピート
//**********************************************************************

//****************** BP4シーケンスコード一覧 2009.01.13 ****************
#define NO_SET_DATA                   0x0000 //選択なし 2009.01.16
#define PREFLOW_SET_DATA              0x0001 //プリフロー
#define INIT_WELD_CURRENT_SET_DATA    0x0002 //初期電流
#define UPSLOP_SET_DATA               0x0004 //アップスロープ
#define MAIN_WELD_CURRENT_SET_DATA    0x0008 //溶接電流
#define DOWNSLOP_SET_DATA             0x0010 //ダウンスロープ
#define CRATER_WELD_CURRENT_SET_DATA  0x0020 //クレータ電流
#define AFTERFLOW_SET_DATA            0x0040 //アフターフロー
#define PULSE_ITEM_SET_DATA           0x0080 //パルス項目
#define AC_TIG_ITEM_SET_DATA          0x0100 //交流ＴＩＧ設定項目 2009.01.19
#define MIX_TIG_ITEM_SET_DATA         0x0200 //ＭＩＸＴＩＧ設定項目 2009.01.19
//**********************************************************************

//******************** BP4溶接法コード一覧 2009.01.13 ******************
#define STD_DC_METHOD                 0    //スタンダード 直流ＴＩＧ
#define STD_AC_METHOD                 1    //スタンダード 交流ＴＩＧ
#define STD_MIX_METHOD                2    //スタンダード ＭＩＸＴＩＧ
#define STD_HAND_METHOD               3    //スタンダード 直流手溶接
//#define QIK_DC_METHOD                 4    //クイック　直流ＴＩＧ
//#define QIK_AC_METHOD                 5    //クイック　交流ＴＩＧ
#define NAVI_METHOD                   4    //ナビゲーション
#define EXP_DC_METHOD                 5    //エキスパート　直流ＴＩＧ
#define EXP_AC_METHOD                 6    //エキスパート　交流ＴＩＧ
//**********************************************************************

//**************** ＢＰ４パルス関連コード一覧 2009.02.12 ***************
#define PULSE_ITEM_CURRENT            1    //パルス電流
#define PULSE_ITEM_DUTY               2    //パルス幅
#define PULSE_ITEM_FREQUENCY          0    //パルス周波数
//**********************************************************************

//************** ＢＰ４リモコン関連コード一覧 2009.03.28 ***************
#define NO_CONNECT                    0
#define BPR1                          1
#define BPR4                          2
//**********************************************************************

//***************************** ＤＳＷ設定一覧 *************************
#define V10_CONTROL  0x40          /*リモコン１０Ｖ制御*/
#define V12_CONTROL  0x80          /*リモコン１２Ｖ制御*/
#define V15_CONTROL  0x00          /*リモコン１５Ｖ制御*/
#define PLAY_RECD_ON 0x10          /*ＤＳＷによる再生モード選択*/
#define NO_REMOCON   0x08          /*リモコン有り無し　ＯＮでなし*/

#define ON_ON_DWLIMIT     560      //ＤＳＷ１：ＯＮ　　ＤＳＷ２：ＯＮ　　下限 2009.04.20 610->560
#define ON_ON_UPLIMIT     672      //ＤＳＷ１：ＯＮ　　ＤＳＷ２：ＯＮ　　上限 2009.04.20 670->672
#define OFF_ON_DWLIMIT    682      //ＤＳＷ１：ＯＦＦ　ＤＳＷ２：ＯＮ　　下限 2009.04.20 700->682
#define OFF_ON_UPLIMIT    770      //ＤＳＷ１：ＯＦＦ　ＤＳＷ２：ＯＮ　　上限 2009.04.20 760->770
#define ON_OFF_DWLIMIT    810      //ＤＳＷ１：ＯＮ　　ＤＳＷ２：ＯＦＦ　下限 2009.04.20 830->810
#define ON_OFF_UPLIMIT    900      //ＤＳＷ１：ＯＮ　　ＤＳＷ２：ＯＦＦ　上限 2009.04.20 890->900
#define OFF_OFF_DWLIMIT   960      //ＤＳＷ１：ＯＦＦ　ＤＳＷ２：ＯＦＦ　下限 2009.04.20 950->960
//**********************************************************************

//************************ Ｒ８からの入力データ ************************
#define WELD_IN2_CODE     0x80          //非常停止（治具端子）
#define WELD_IN3_CODE     0x40          //一時停止１（治具端子）
#define WELD_IN4_CODE     0xc0          //一時停止２（治具端子）
#define WELD_IN6_CODE     0x20          //インチング・リトラクト用モータ起動
#define WELD_IN7_CODE     0xa0          //インチング（ＯＦＦ）・リトラクト（ＯＮ）選択
#define WELD_IN8_CODE     0x60          //予備
#define EXT_IN1_CODE      0xe0          //予備
#define EXT_IN2_CODE      0x10          //予備
#define EXT_IN3_CODE      0x90          //予備
//**********************************************************************

//************************* Ｒ８への出力データ *************************
//  xxxx xfI-  : (x)データ列　(f)ｏｎ・ｏｆｆフラグ　(I)割り込み信号　(-)不定

#define EXTOUT_LED_CODE      0x02       //ＬＥＤ　０～Ｆまでの表示 0000 001- 
#define WELD_OUT3_CODE       0x82       //電流検出（治具端子）     1000 001-
#define WELD_OUT4_CODE       0x8a       //エラー（治具端子）       1000 101-
#define WELD_OUT5_CODE       0x92       //アラーム（治具端子）     1001 001-
#define WELD_OUT6_CODE       0x9a       //予備（治具端子）         1001 101-
#define WELD_OUT7_CODE       0xa2       //予備                     1010 001-
#define EXTOUT1_CODE         0xaa       //ＥＸＴＯＵＴ１           1010 101-
#define EXTOUT2_CODE         0xb2       //ＥＸＴＯＵＴ２           1011 001-
#define EXTOUT3_CODE         0xba       //ＥＸＴＯＵＴ３           1011 101-
#define EXTOUT_INT_OFF_CODE  0x00       //次の出力準備を行う       0000 000-
#define ADD_EXTOUT_ON_CODE   0x40       //ＯＮデータ付加           0000 010-
#define ADD_EXTOUT_OFF_CODE  0xfb       //ＯＦＦデータ付加         1111 101-
//**********************************************************************

//********************** チャタリングチェック関連 **********************
#define EXT_TS_NO            1          //外部入力　ＴＳのチャタリングチェック番号
#define EXT_THP_NO           2          //外部入力　サーマルチャタリングチェック番号
#define EXT_EMG_NO           3          //外部入力　非常停止ＳＷチャタリングチェック番号
#define EXT_OUT_SIDE1_NO     4          //外部入力　一時停止１チャタリングチェック番号
#define EXT_OUT_SIDE2_NO     5          //外部入力　一時停止２チャタリングチェック番号
#define EXT_INCHING_NO       6          //外部入力　インチングＳＷチャタリングチェック番号
#define EXT_EMG2_NO          7          //外部入力　非常停止２ＳＷチャタリングチェック番号 2007.2.9
//#define EXT_INPUT_COUNT     10          //チャタリング防止回数
#define EXT_INPUT_COUNT     80          //チャタリング防止回数 20mS相当 2008.10.30 80
//**********************************************************************

#define AVR_RESULT_COUNT     10          //2008.03.03 測定電流、電圧平均回数  2009.03.17 2->10 2009.03.17 10->40 2009.03.23 40->10
#define AVR_RESULT_COUNT2    40         //2009.02.24 測定電流、電圧平均回数 2009.03.17 20->40 2009.03.17 40->80  2009.03.23 80->40
#define AVR_RESULT_COUNT3    80         //2009.02.24 測定電流、電圧平均回数 2009.04.11

//******************** コントローラ関連 2008.07.18 *********************
#define CONTROL2_COUNT       5 //項目の個数
#define CONTROL3_COUNT       5 //項目の個数 2008.08.21
#define SEQUENCE_NON               0 //AZ 0:NON（クレータ無）
#define SEQUENCE_CRATER            1 //   1:CRT (クレータ有)
#define SEQUENCE_CRATER_REPEAT     2 //   2:クレータ反復 2009.02.05
//#define SEQUENCE_INIT_CRATER       2 //   2:ICR (初期クレータ（パルス時：クレータパルス無））
//#define SEQUENCE_INIT_CRATER_PULSE 3 //   3:ICP (パルス時初期クレータ（クレータパルス有））
//#define SEQUENCE_ARC_SPOT          4 //   4:SPT (アークスポット)
#define SEQUENCE_ARC_SPOT          3 //   3:SPT (アークスポット) //2009.03.06

#define PARAMETER_MAX             14 //
#define REVERS_TIME          200 //ＣＨ表示リバースタイム 2008.08.19 400→200に変更 2008.09.04

//*************************** 設定関連 **********************************
//<><>ユーザー<><>
//共通
//#define USER_MENU_COUNT           6 //2008.08.22
#define USER_MENU_COUNT           7 //2008.11.10
//特殊パラメータ
//#define USER_PARAMETER_NO        10
//#define USER_PARAMETER_MAX         32767
//#define USER_PARAMETER_MIN        -32767
#define USER_PARAMETER_MAX         999 //2008.10.31 田中さん了承で変更
#define USER_PARAMETER_MIN        -999 //2008.10.31 田中さん了承で変更
//#define PASS_WORD_NO              9 //パスワード入力のためのパラメータ番号　試験のため現在９　最終仕様は９９９ 2008.09.02
#define PASS_WORD_NO              99 //パスワード入力のためのパラメータ番号　試験のため現在９　最終仕様は９９ 2008.10.30
#define PASS1                     333
#define PASS2                     444
#define PASS3                     555

//ＩＩＦ 
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	#define OUT_FUNCTION_NO_MAX			10						//
	#define IN_FUNCTION_NO_MAX			21						//
	#define ANALOG_FUNCTION_NO_MAX		8						//
#else
	#define OUT_FUNCTION_NO_MAX			3						//９→３に変更 2008.09.01
	#define IN_FUNCTION_NO_MAX			17						//2008.08.25  ９→１７に変更 2008.09.01
	#define ANALOG_FUNCTION_NO_MAX		6						//2008.08.25   ９→６に変更 2008.09.01
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
#define ANALOG_FUNC_CUR_15V       1 //アナログ入力ファンクションＮＯ１　電流指令値１５Ｖ 2008.09.03
#define ANALOG_FUNC_CUR_12V       2 //アナログ入力ファンクションＮＯ２　電流指令値１２Ｖ 2008.09.03
#define ANALOG_FUNC_CUR_10V       3 //アナログ入力ファンクションＮＯ３　電流指令値１０Ｖ 2008.09.03
#define ANALOG_FUNC_VLT_15V       4 //アナログ入力ファンクションＮＯ４　電圧指令値１５Ｖ 2008.09.03
#define ANALOG_FUNC_VLT_12V       5 //アナログ入力ファンクションＮＯ５　電圧指令値１２Ｖ 2008.09.03
#define ANALOG_FUNC_VLT_10V       6 //アナログ入力ファンクションＮＯ６　電圧指令値１０Ｖ 2008.09.03

//突き出し長 2008.11.10
#define EXT_CONDITION_MAX_ITEM    7

//サービスマン
#define SERVICE_MENU_COUNT        2 //2008.09.03
//#define SERVICE_DATA_NO           3 //2008.09.02 暫定個数
#define SERVICE_DATA_MAX        100 //2008.09.02 暫定数
#define SERVICE_DATA_MIN       -100 //2008.09.02 暫定数
#define CLR_TIME                200 //2008.09.03
//***********************ＩＩＦ設定関連 2008.09.01 **********************
//OUTPUT FUNCTION NAME
#define IIF_OUT_NO_USE              0 //未使用
#define IIF_OUT_CURRENT_DETECT      1 //電流検出
#define IIF_OUT_STICK_CHECK         2 //スティック検出結果
#define IIF_OUT_IDLING_CHECK        3 //待機中
//INPUT FUNCTION NAME
#define IIF_IN_NO_USE               0 //未使用
#define IIF_IN_EMERGENCY_STOP_ERR   1 //非常停止
#define IIF_IN_OUTSIDE_STOP1_ERR    2 //一時停止１
#define IIF_IN_OUTSIDE_STOP2_ERR    3 //一時停止２
#define IIF_IN_GAS_CHECK            4 //ガスチェック
#define IIF_IN_WIRE_CHECK           5 //インチング
#define IIF_IN_STICK_CHECK_COMMAND  6 //スティックチェック命令
#define IIF_IN_TS                   7 //トーチスイッチ
#define IIF_IN_EXT_SELECT_SW1      10 //外部選択ユニットビット１
#define IIF_IN_EXT_SELECT_SW2      11 //外部選択ユニットビット２
#define IIF_IN_EXT_SELECT_SW3      12 //外部選択ユニットビット３
#define IIF_IN_EXT_SELECT_SW4      13 //外部選択ユニットビット４
#define IIF_IN_EXT_SELECT_SW5      14 //外部選択ユニットビット５
#define IIF_IN_EXT_SELECT_SW6      15 //外部選択ユニットビット６
#define IIF_IN_EXT_SELECT_CNT      16 //外部選択ユニットコントロール信号
#define IIF_IN_EXT_SELECT_STB      17 //外部選択ユニットストローブ信号
//ANALOG FUNCTION NAME
#define IIF_AG_NO_USE               0 //未使用
#define IIF_AG_PRE_CURRENT_15V      1 //電流指令値１５Ｖ
#define IIF_AG_PRE_CURRENT_12V      2 //電流指令値１２Ｖ
#define IIF_AG_PRE_CURRENT_10V      3 //電流指令値１０Ｖ
#define IIF_AG_PRE_VOLTAGE_15V      4 //電圧指令値１５Ｖ
#define IIF_AG_PRE_VOLTAGE_12V      5 //電圧指令値１２Ｖ
#define IIF_AG_PRE_VOLTAGE_10V      6 //電圧指令値１０Ｖ
//***********************************************************************

//******************* ＥＮ比率計算関連 2008.09.16 ***********************
#define WF_MAX  20000 //送給量最大値
#define EN_MIN  10    //ＥＮ比率最小値 
#define EN_MAX  50    //ＥＮ比率最大値
//***********************************************************************

//--------- Phase13 by @Tny 2008/09/18 --------
#if true
#define WRITE_WELD_CH               99  // 溶接条件の記録上限チャンネル番号 / 記憶最大チャンネル数を９９へ Phase21 by @Tny 2008/10/03
#define WRITE_IIF_CH                201 // IIF接続記録識別子の記録
#define WRITE_ERROR_HISTORY_CH      202 // エラー履歴テーブルの記録
#define WRITE_WELD_COND_NAME_CH		203 // 溶接条件名の記録	// BP4 Phase6 by @Tny 2009/01/27
#define WRIGHT_LCD_BRIGHT_CH		204 // ＬＣＤコントラスト値の記録	// BP4 Phase9 by @Tny 2009.02.16
#endif
//--------------------------------------------


//--------- Phase21 by @Tny 2008/10/02 --------
#if true
// メモリ転送エリア項目数
//
#define MEMORY_COPY_MAX_ITEM    2

// 記憶チャンネル削除識別子
//
#define MEMORY_DELETE_CH        100

// メモリ転送後表示コマンド送信停止時間
//
#define DISPLAY_STOP            500    // 0.5sec
#endif
//--------------------------------------------
//----- Phase29 by @Tny 2008/11/21 -----
#if true
#define PRI_VOLT_LOW_TIME		1800	// 一次電圧低異常検知ディレイタイマー：1000msec 2009.03.13 1000->1500に変更		2011.11.16 1500->1800に変更
#endif
//--------------------------------------------
//--------------------------------------------
// BP4 Phase5 by @Tny 2009.01.21
#define DoubleQuotationCommaPosition	124
#define SingleQuotationCommaPosition	128
#define DeletePosition					147
#define DoubleQuotationCommaCode		0x22	// "
#define SingleQuotationCommaCode		0x27	// '
#define DeleteCode						0x7F	// ←
#define SelectCode						0xFF	// 
#define StringInputEndCharacter			'#'
//--------------------------------------------

//--------------------------------------------
// BP4 Phase6 by @Tny 2009.01.27
#define MODE_WELDING	0	// 溶接モード
#define MODE_DETAILS	3	// 詳細モード
#define	MODE_PLAY		1	// 再生モード
#define	MODE_RECORD		2	// 記憶モード
#define	MODE_MAX		3	// 最大モード数
//--------------------------------------------
//--------------------------------------------
// BP4 Phase10 by @Tny 2009.02.18
//#define	REMO8_AD_CONVERTER	(15.0/ 1024.0)	// リモコンＡ／Ｄ入力値→電圧値変換係数（３．３Ｖ＝１０２４）
// BP4 Phase11 by @Tny 2009.02.19
//#define	REMO8_AD_CONVERTER	(930.0 / 300.0)		// リモコンＡ／Ｄ入力値→電流指令値
//#define	REMO8_AD_CONVERTER	(920.0 / 300.0)		// リモコンＡ／Ｄ入力値→電流指令値 2009.04.08 930.0->920.0
//#define	REMO8_AD_CONVERTER	(920.0 / 500.0)		// リモコンＡ／Ｄ入力値→電流指令値 2010.01.12 300.0->500.0
//#define	REMO8_AD_CONVERTER	(880.0 / 495.0)		    // リモコンＡ／Ｄ入力値→電流指令値 2010.02.04 係数変更
#define	REMO8_AD_CONVERTER	(920.0 / 300.0)		// リモコンＡ／Ｄ入力値→電流指令値 2011.12.07 <500A->300A>
#define REMO8_AD_MIN   20                           // リモコンＡ／Ｄ入力値最低値 2010.02.04
#define REMO8_AD_MAX  900                           // リモコンＡ／Ｄ入力値最大値 2010.02.04
#define REMO8_C        11.112                       // リモコンＡ／Ｄ入力値変換式Ｃ値 2010.02.04
//--------------------------------------------

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of moddef.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

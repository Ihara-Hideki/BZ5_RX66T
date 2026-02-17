/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接種別毎の溶接条件テーブル                                        */
/*  [最終更新日]                                                            */
/*      2004. 6. 9  R040301RTW-TAWERS       西川                            */
/*      2004. 9. 3  R040701RTW-TAWERS       田中                            */
/*      2004. 9.29  R040701RTW-TAWERS       田中    [半固定2]               */
/*      2004.10.13  R040701RTW-TAWERS       西川    NY20041013              */
/*      2005.09.27  R050902RK1-溶接条件設定拡張     津田                    */
/*--------------------------------------------------------------------------*/
// @-R050902RK1
//#define TBLCNT              72 2006.12.18 custom.h に移動
#define WELDNAMELEN         16
//#define WELDNAME_TBLCNT     32
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接種別コード                                                      */
/*  [データ説明]                                                            */
/*      uchar       material                材質                            */
/*      uchar       method                  溶接法                          */
/*      uchar       pulseCode               パルスモード                    */
/*      uchar       pulseType               パルスタイプ                    */
/*      uchar       wire                    ワイヤ径　　　　　　　　        */
/*      uchar       extension               突き出し長                      */
/*      uchar       dummy1                  予約                            */
/*      uchar       dummy2                  予約                            */
/*--------------------------------------------------------------------------*/
typedef struct
{
        uchar       material;
        uchar       method;
        uchar       pulseMode;
        uchar       pulseType;
        uchar       wire;
        uchar       extension;
        uchar       dummy1;
        uchar       dummy2;
}WELDCODE , *PWELDCODE;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ送給速度テーブル                                              */
/*  [データ説明]                                                            */
/*      usint       Speed[ 256 ]            送給テーブル( 0.001 m/min )     */
/*                                              [ xx ]  xxは、2A単位        */
/*--------------------------------------------------------------------------*/
typedef struct
{
        usint       Speed[ 256 ];
}A2STBL , *PA2STBL;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      一元電圧テーブル                                                    */
/*  [データ説明]                                                            */
/*      usint       Volt[ 256 ]             送給テーブル( 0.1 V )           */
/*                                              [ xx ]  xxは、0.1m/min単位  */
/*--------------------------------------------------------------------------*/
typedef struct
{
        usint       Volt[ 256 ];
}S2VTBL , *PS2VTBL;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      半固定パラメータテーブル                                            */
/*  [データ説明]                                                            */
/*      usint       Parm[ 252 ]              パラメータ（絶対値）           */
/*--------------------------------------------------------------------------*/
typedef struct
{
//  usint   Parm[ 126 ];// @-R040701RTW     ２５６→１２６変更
//    usint   Parm[ 252 ];// 2004. 9.29
    usint   Parm[ 378 ];// 2007. 2.13   252→378に変更
}WELDPARM , *PWELDPARM;

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      可変パラーメータ係数テーブル                                        */
/*  [データ説明]                                                            */
/*      float       a                       係数ａ                          */
/*      float       b                       係数ｂ                          */
/*      float       c                       係数ｃ                          */
/*      float       min                     係数ｍｉｎ                      */
/*      float       max                     係数ｍａｘ                      */
/*--------------------------------------------------------------------------*/
typedef struct
{
        float       a;
        float       b;
        float       c;
        float       min;
        float       max;
}DCCALPARM , *PDCCALPARM;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      パルス/短絡用テーブル（予約）                                       */
/*  [データ説明]                                                            */
/*      usint       Data[ 256 ]         予約                                */
/*--------------------------------------------------------------------------*/
typedef struct
{// @-R040701RTW
    usint       Data[ 256 ];
}DMYTBL , *PDMYTBL;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      パラメータテーブル（パルス/短絡）                                   */
/*  [データ説明]                                                            */
/*      usint       SlowDown                スローダウン( 0.001 m/min )     */
/*      usint       acc1                    送給加速度１( 0.1 )             */
/*                                              トーチＯＮ用                */
/*      usint       acc2                    加速度２                        */
/*                                              初期短絡用                  */
/*      usint       acc3                    加速度３                        */
/*                                              条件変更用                  */
/*      usint       acc4                    加速度４                        */
/*                                              クレータ用                  */
/*      usint       acc5                    加速度５                        */
/*                                              トーチＯＦＦ用              */
/*      usint       Delay                   送給ディレイ                    */
/*      usint       ContArc                 連続アークスタート時間          */
/*      usint       Dmy                     予約  × １２                   */
/*--------------------------------------------------------------------------*/
typedef struct
{// @-R040701RTW
        usint       SlowDown;
        usint       acc1;
        usint       acc2;
        usint       acc3;
        usint       acc4;
        usint       acc5;
        usint       Delay;
        usint       ContArc;    // NY20041013
        usint       Dmy1;
        usint       Dmy2;
        usint       Dmy3;
        usint       Dmy4;
        usint       Dmy5;
        usint       Dmy6;
        usint       Dmy7;
        usint       Dmy8;
        usint       Dmy9;
        usint       Dmy10;
        usint       Dmy11;
        usint       Dmy12;
}PARMTBL , *PPARMTBL;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件テーブル　　　　　　                                        */
/*  [データ説明]                                                            */
/*      WELDCODE    WeldCode                溶接種別コード                  */
/*                                          パルス溶接用                    */
/*      A2STBL      A2S_Pulse                 ワイヤ送給テーブル            */
/*      V2STBL      V2S_Pulse                 一元電圧テーブル              */
/*      DMYTBL      Pls_Table               パルス用テーブル（予約）        */
/*                                          短絡溶接用                      */
/*      A2STBL      A2S_Short                 ワイヤ送給テーブル            */
/*      V2STBL      V2S_Short                 一元電圧テーブル              */
/*      DMYTBL      Short_Table             短絡用テーブル(予約）           */
/*      WELDPARM    WeldParm                半固定パラメータ                */
/*      DCCALPARM   CalParm[ 64 ]           可変パラメータ係数              */
/*      PARMTBL     ParmTbl_Pls             パラメータテーブル（パルス）    */
/*      PARMTBL     ParmTbl_Short           パラメータテーブル（短絡）      */
/*--------------------------------------------------------------------------*/
#if 0
typedef struct
{
    sint        EN_P[256];              //2008.09.24
    sint        EN_M[256];              //2008.09.24
    sint        EN_0[256];              //2008.09.24
    sint	ENdef_Calc_Wf1;		//①ﾃﾞﾌｫﾙﾄEN比率算出用送給範囲１判定値 (単位：0.001m/min)
    float	ENdef_Calc_Wf1_a;	//②ﾃﾞﾌｫﾙﾄEN比率算出用送給範囲１での定数a
    float	ENdef_Calc_Wf1_b;	//③ﾃﾞﾌｫﾙﾄEN比率算出用送給範囲１での定数b
    sint	ENdef_Calc_Wf2;		//④ﾃﾞﾌｫﾙﾄEN比率算出用送給範囲２判定値 (単位：0.001m/min)
    float	ENdef_Calc_Wf2_a;	//⑤ﾃﾞﾌｫﾙﾄEN比率算出用送給範囲２での定数a
    float	ENdef_Calc_Wf2_b;	//⑥ﾃﾞﾌｫﾙﾄEN比率算出用送給範囲２での定数b
    sint	EN1_Min_Limit;		//⑦EN調整値 内部ﾘﾐｯﾄ(最小値) (単位：%)
    sint	EN1_Max_Limit;		//⑧EN調整値 内部ﾘﾐｯﾄ(最大値) (単位：%)
    float	AC_Frq_ENa1_A;		//⑨周波数定数b算出用EN比率範囲１での定数A
    float	AC_Frq_ENa1_B;		//⑩周波数定数b算出用EN比率範囲１での定数B
    float	AC_Frq_ENa1_C;		//⑪周波数定数b算出用EN比率範囲１での定数C
    float	AC_Frq_ENa2_A;		//⑫周波数定数b算出用EN比率範囲２での定数A
    float	AC_Frq_ENa2_B;		//⑬周波数定数b算出用EN比率範囲２での定数B
    float	AC_Frq_ENa2_C;		//⑭周波数定数b算出用EN比率範囲２での定数C
    sint	AC_DCstart_Tim_Def;	//⑮ｱｰｸｽﾀｰﾄ直流制御区間微調量ﾃﾞﾌｫﾙﾄ値 (単位：ms)
    sint	AC_DCstart_Tim_Max;	//⑯ｱｰｸｽﾀｰﾄ直流制御区間微調量MAX値 (単位：ms)
}ENTBL,*PENTBL;
#endif

//新交流テーブル 2008.11.11
typedef struct
{
    sint    EN_P[128]; //2008.12.01 256->128
    sint    EN_M[128]; //2008.12.01 256->128
    sint    EN_0[128]; //2008.12.01 256->128
    sint	dummy1;		        //①予備
    float	ENdef_Max;	        //②デフォルトＥＮ比率ENdefMax（単位：％）
    float	ENdef_Min;	        //③デフォルトＥＮ比率ENdefMin（単位：％）
    sint	EN1_Wf_Limit;		//④ＥＮ調整値無効送給量（単位：0.001m/min）
    float	ENa_Max;	        //⑤ＥＮ比率ENaMax（単位：％）
    float	ENa_Min;	        //⑥ＥＮ比率ENaMin（単位：％）
    sint	EN1_Min_Limit;		//⑦EN調整値 内部ﾘﾐｯﾄ(最小値) (単位：%)
    sint	EN1_Max_Limit;		//⑧EN調整値 内部ﾘﾐｯﾄ(最大値) (単位：%)
    float	dummy9;		        //⑨予備
    float	dummy10;		    //⑩予備
    float	dummy11;		    //⑪予備
    float	dummy12;		    //⑫予備
    float	dummy13;		    //⑬予備
    float	dummy14;		    //⑭予備
    sint	AC_DCstart_Tim_Def;	//⑮ｱｰｸｽﾀｰﾄ直流制御区間微調量ﾃﾞﾌｫﾙﾄ値 (単位：ms)
    sint	AC_DCstart_Tim_Max;	//⑯ｱｰｸｽﾀｰﾄ直流制御区間微調量MAX値 (単位：ms)
    sint    V13_Data[128];      //⑰Ｖ１３テーブル //2008.12.01 256->128
    sint    V15_Data[128];      //⑱Ｖ１５テーブル //2008.12.01 256->128
    sint    V18_Data[128];      //⑲Ｖ１８テーブル //2008.12.01 256->128
    sint    V20_Data[128];      //⑳Ｖ２０テーブル //2008.12.01 256->128
    sint    V84_Data[128];      //(21)Ｖ８４テーブル //2008.12.01 256->128
    sint    TEN_Data[128];      //(22)ＥＮ時間(ＴＥＮ) //2008.12.01 256->128
    float   a1;                 //単位時間（１秒）当たりの熱量Ｑｔ（１ｓ）算出用２次式定数ａ１
    float   b1;                 //単位時間（１秒）当たりの熱量Ｑｔ（１ｓ）算出用２次式定数ｂ１
    float   c1;                 //単位時間（１秒）当たりの熱量Ｑｔ（１ｓ）算出用２次式定数ｃ１
    float   ALPH1;              //周波数算出２次式定数ａ２（ａ３）算出用２次式定数α１
    float   BETA1;              //周波数算出２次式定数ａ２（ａ３）算出用２次式定数β１
    float   GAMM1;              //周波数算出２次式定数ａ２（ａ３）算出用２次式定数γ１
    float   ALPH2;              //周波数算出２次式定数ｂ２（ｂ３）算出用２次式定数α２
    float   BETA2;              //周波数算出２次式定数ｂ２（ｂ３）算出用２次式定数β２
    float   GAMM2;              //周波数算出２次式定数ｂ２（ｂ３）算出用２次式定数γ２
    float   ALPH3;              //周波数算出２次式定数ｃ２（ｃ３）算出用２次式定数α３
    float   BETA3;              //周波数算出２次式定数ｃ２（ｃ３）算出用２次式定数β３
    float   GAMM3;              //周波数算出２次式定数ｃ２（ｃ３）算出用２次式定数γ３
    float   Wf_max_limit;       //ＥＮａを０にする判定送給量 2008.12.11
    float   ENa_ac_limit;       //ＡＣとして成り立つＥＮａか判定する比率 2008.12.11
    float   Correct_a;          //交流パルスにおけるＥＮ比率０％時のＦＢ用設定電流補正　係数ａ 2008.12.24
    float   Correct_b;          //交流パルスにおけるＥＮ比率０％時のＦＢ用設定電流補正　定数ｂ 2008.12.24
    float   SP_PARAM17;         //予備
    float   SP_PARAM18;         //予備
    float   SP_PARAM19;         //予備
    float   SP_PARAM20;         //予備
}ENTBL,*PENTBL;

//<><><> 電流指令値テーブル 2010.02.19 <><><>
typedef struct
{
    short   CUR_DATA[640];
}CURTBL,*PCURTBL;


typedef struct
{
        WELDCODE    WeldCode;
        A2STBL      A2S_Pulse;
        S2VTBL      S2V_Pulse;
        //DMYTBL      Pls_Table; 2007.2.13削除
        A2STBL      A2S_Short;
        S2VTBL      S2V_Short;
        //DMYTBL      Short_Table; 2007.2.13削除
        WELDPARM    WeldParm;
        //DCCALPARM   CalParm[ 64 ];
        DCCALPARM   CalParm[ 96 ]; //2008.09.03　可変パラメータ９６個対応
        PARMTBL     ParmTbl_Pls;
        PARMTBL     ParmTbl_Short;

        PENTBL      pENTBL_Pulse; //2008.09.19
        PENTBL      pENTBL_Short; //2008.09.19

        PCURTBL     pCURTBL_Data; //2010.02.19
// @-R040701RTW
//      usint       SlowDown;
//      usint       acc1;
//      usint       acc2;
//      usint       acc3;
//      usint       acc4;
//      usint       acc5;
//      usint       acc6;
}WELDTABLE , *PWELDTABLE;



//BP4用ナビテーブル定義 2009.01.14
typedef struct
{
        uchar       material;
        uchar       thickness;
        uchar       joint;
        uchar       direction;
        uchar       pulse;
        uchar       dummy; //2009.03.18
}NAVICODE , *PNAVICODE;

// <NAVI Enhancements(Phase 1)> 2011.10.26
// ナビテーブルに「シールドガス」「フィラー径」「電極径」「電極先端角度」を追加
//
typedef struct
{
        unsigned short  Method;           // 溶接法
        unsigned short  Pre_flow;         // プリフロー時間
        unsigned short  After_flow;       // アフターフロー時間
        unsigned short  Up_slop;          // アップスロープ時間
        unsigned short  Down_slop;        // ダウンスロープ時間
        unsigned short  Init_current;     // 初期電流
        unsigned short  Main_current;     // 本溶接電流
        unsigned short  Crater_current;   // クレータ電流
        unsigned short  Pulse_current;    // パルス電流
        unsigned short  Pulse_duty;       // パルス幅
        unsigned short  Pulse_frequency;  // パルス周波数
        unsigned short  Crater_mode;      // クレータ有無（０：無 １：有）
        unsigned short  Pulse_mode;       // パルス有無（０：無 １：有）
        unsigned short  AC_wave;          // 交流波形（０：標準 １：ハード ２：ソフト）
        unsigned short  AC_cleaning_duty; // 交流ＴＩＧ設定 クリーニング幅
        unsigned short  AC_frequency;     // 交流ＴＩＧ設定 交流周波数
        unsigned short  MIX_frequency;    // ＭＩＸＴＩＧ設定 ＭＩＸ周波数
        unsigned short  MIX_duty;         // ＭＩＸＴＩＧ設定 直流比率
        unsigned short  Gas_navi;         // ガス流量     //
        unsigned short  Filler_navi;      // フィラー径   //
        unsigned short  Electroad_navi;   // 電極径       //
        unsigned short  El_rd_angle_navi; // 電極先端角度 //
}NAVICOND , *PNAVICOND;

typedef struct
{
        NAVICODE    NaviCode;
        NAVICOND    NaviCond;
}NAVITABLE , *PNAVITABLE;



/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接種別名称定義                                                    */
/*  [データ説明]                                                            */
/*      uchar       Kind                    種別(d0:材質、d1:溶接法)        */
/*      uchar       Code                    コード                          */
/*      char        Name[ 16 ]              名称                            */
/*--------------------------------------------------------------------------*/
typedef struct
{// @-R050902RK1
    uchar       Kind;
    uchar       Code;
    char        Name[ WELDNAMELEN ];
} WELDNAME , *PWELDNAME;

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      新・溶接条件テーブル                                                */
/*  [データ説明]                                                            */
/*      char        Type[ 16 ]              新／旧                          */
/*      char        *pVersion               バージョン                      */
/*      PWELDNAME   pNamTbl                 溶接種別名称定義テーブル        */
/*      PWELDTABLE  pWeldTable              旧・溶接条件テーブル            */
/*--------------------------------------------------------------------------*/
typedef struct
{// @-R050902RK1
    char        Type[ 16 ]; //　不要なので消す（アドレスを合わせるため）2006.12.19
    char        *pVersion;
    PWELDNAME   pNamTbl;
    PWELDTABLE  pWldTbl;
} NEW_WLDTBL , *PNEW_WLDTBL;

//------ Phase8 by @Tny 2008/09/11 ------
#if true
//#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x0070000 )
//#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x0070000 )
//#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x0080000 )
//#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x0080000 )
//#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x0082000 ) //2008.11.10
//#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x0082000 )  //2008.11.10
//#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x0084000 ) //2009.02.24
//#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x0084000 )  //2008.02.24
//#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x0094000 ) //2009.02.27
//#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x0094000 )  //2008.02.27
//#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x0096000 ) //2010.02.19
//#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x0096000 )  //2010.02.19
#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
	#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x00A2000 )
	#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x00A2000 )
#else
	#define WLDTBL_PTR      ( (PNEW_WLDTBL)0x0098000 ) //2011.09.21
	#define OLD_WLDTBL_PTR  ( (PWELDTABLE)0x0098000 )  //2011.09.21
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny
#endif

#define NEW_WLDTBL_PTR  ( (PWELDTABLE)( (lint)(WLDTBL_PTR->pWldTbl) ) )
#define WLDNAMETBL_PTR  ( (PWELDNAME)( (lint)(WLDTBL_PTR->pNamTbl) ) )
#define WLDTBL_VERSION  ( (char *)( (lint)(WLDTBL_PTR->pVersion) ) )

//#define TEST_PTR ((PENTBL)0x0090000) //2008.09.19

//#define NEW_WLDTBL_PTR  ( (PWELDTABLE)( (lint)(WLDTBL_PTR->pWldTbl) + 0x0070000 ) )
//#define WLDNAMETBL_PTR  ( (PWELDNAME)( (lint)(WLDTBL_PTR->pNamTbl) + 0x0070000 ) )
//#define WLDTBL_VERSION  ( (char *)( (lint)(WLDTBL_PTR->pVersion) + 0x0070000 ) )
/* end */

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      補間クラス                                                          */
/*  [最終更新日]                                                            */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*      2004.09.14  R040701RTW-TAWERS       西田    微調                    */
/*      2004.10.06  R040701RTW-TAWERS       上内    一元 <ALT3>             */
/*      2005. 2.21  可変パラメータ演算:ny050217.c   西川                    */
/*      2005.06.02  R050507RK1-TW_DIP_PULSE 津田                            */
/*      2005.10. 5  NY20051005              西川    可変パラメータの変更    */
/*		2006.02.27	KOWA20060227			古和(田中）　　可変パラメータの変更	*/
/*--------------------------------------------------------------------------*/
//#include    "typedef.h"
//#include    "xapidefs.h"
//#include    "xdefine.h"
//#include    "ifdata.h"
//#include    "dbg.h"

#include    "custom.h"
//#include    "C:\GZWORK\Development\M32_NEW\compile\H\custom.h"

// -----------------------------------
void    dbgWIP( void );
void    dbgSIP( void );
int     ctlclsSpeedGet_Siji( void );
static  float   ConvRpm( float Data );
// -----------------------------------
extern  int         _ACC;
extern  int         DC_PMODE;
extern  float       DC_RPM;
extern  WELDCODE    DC_WELDCODE;    // @-R050507RK1

extern  WIPCB       _wipcb;
extern  SIPCB       _sipcb;

/////////////////////////////////////////////////////////////////////////////
#define     SHIREITIME      0.005//指令周期（５ｍｓ）
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件計算用定数                                                  */
/*--------------------------------------------------------------------------*/
static  float   const   Conv_V      = { 2048.0 * 16.0 / 62.5 };         // 変換係数V
//20071130 static  float   const   Conv_A      = { 2048.0 * 16.0 / 1250.0  };       // 変換係数A
static  float   const   Conv_A      = { 2048.0 * 16.0 / 750.0  };       // 変換係数A
//20080222 static  float   const   Conv_T      = { 10.0        };                  // 変換係数T
//20080911 static  float   const   Conv_T      = { 20.0        };                  // 変換係数T
static  float   const   Conv_T      = { 12.5        };                  // 変換係数T
//20071130 static  float   const   ADUNIT_A      = { 1250.0 / 32752.0 };            // AD変換値分解能(電流)
static  float   const   ADUNIT_A      = { 750.0 / 32752.0 };            // AD変換値分解能(電流)

#define AD_V 62.5    //2009.01.08
#define AD_I 750.0   //2009.01.08

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ送給速度を求める                                              */
/*  [引数]                                                                  */
/*      int         Amp         指令電流値(2A刻み)                          */
/*      PA2STBL     pDat        ワイヤ送給速度テーブルポインタ(パルス/短絡) */
/*  [戻り値]                                                                */
/*      sint        WFe         ワイヤ送給速度（0.001m/min)                 */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*      2004.10.06  R040701RTW-TAWERS       上内    一元 <ALT3>             */
/*--------------------------------------------------------------------------*/
sint   GetAmp2Wire( sint Amp , PA2STBL pDat )
{
int     No;
int     Wk;
float   Wfe;

// @-R040701RTW [一元] <ALT3> 電流値の範囲チェック追加
    if( Amp < 0 )
        Amp = 0;
    else if( Amp > 510 )
        Amp = 510;

    No = Amp / 2;
    if( ( Amp % 2 ) == 0 )
    {
        Wfe = (float)pDat->Speed[ No ];
    }
    else
    {
        Wk = pDat->Speed[ No ] + pDat->Speed[ No + 1 ];
        Wfe = (float)Wk / 2.0;
        if( Wk % 2 )
            Wfe += 0.5;
    }
    return( (sint)Wfe );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ供給速度から電圧値を求める                                    */
/*  [引数]                                                                  */
/*      int         WF          ワイヤ送給速度( 0.001 )                     */
/*  [戻り値]                                                                */
/*      int         電圧( 0.1 )                                             */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.17  R040301RTW-TAWERS       西川                            */
/*--------------------------------------------------------------------------*/
int     WF2Volt( int WF )
{
int Work;

    if( WF < 0 )
        WF = 0;
    else if( WF > 25500 )
        WF = 25500;

//  小数第２を四捨五入して小数第１に丸める
    Work = ( WF + 50 ) / 100;       // ( 0.001+0.05 )→ 0.1 m/min

    if( DC_PMODE != 2 )
        return( pWT->S2V_Pulse.Volt[ Work ] );
    return( pWT->S2V_Short.Volt[ Work ] );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ供給速度からEN電圧値を求める                                  */
/*  [引数]                                                                  */
/*      int         WF          ワイヤ送給速度( 0.001 )                     */
/*  [戻り値]                                                                */
/*      int         電圧( 0.1 )                                             */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.17  R040301RTW-TAWERS       西川                            */
/*--------------------------------------------------------------------------*/
int     WF_EN_Volt( int WF , unsigned char en_sw)
{
int Work;

    PENTBL      pENTBL;
         switch( DC_PMODE )
         {
            case 2://短絡
                 pENTBL = pWT->pENTBL_Short;
                 break;
            case 1://パルス
            default:
                 pENTBL = pWT->pENTBL_Pulse;
                 break;
         } 

    if( WF < 0 )
        WF = 0;
    //else if( WF > 25500 )
    //    WF = 25500;
    else if( WF > 25400 )  //2008.11.11
        WF = 25400;        //2008.11.11

//  小数第２を四捨五入して小数第１に丸める
    //Work = ( WF + 50 ) / 100;       // ( 0.001+0.05 )→ 0.1 m/min
    Work = ( WF + 50 ) / 200;       // ( 0.001+0.05 )→ 0.1 m/min 2008.11.11

    if( en_sw == EN_VOLT_P )
    {
        return( pENTBL->EN_P[ Work ] );
    }
    if( en_sw == EN_VOLT_M )
    {
        return( pENTBL->EN_M[ Work ] );
    }
    
    return( pENTBL->EN_0[ Work ] );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      一元電圧ステップの目標値を求める                                    */
/*  [引数]                                                                  */
/*      int         Wfe         目標ワイヤ送給速度( 0.001 )                 */
/*      int         Volt        指令電圧( 0.1 )                             */
/*      PS2VTBL     pDat        一元電圧テーブルポインタ(パルス/短絡)       */
/*  [戻り値]                                                                */
/*      float       一元電圧ステップの目標値                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
static  float    GetVoltStep( int Wfe , int Volt , PS2VTBL pDat )
{
int Work;

    if( Wfe < 0 )
        Wfe = 0;
    else if( Wfe > 25500 )
        Wfe = 25500;

//  小数第２を四捨五入して小数第１に丸める
    Work = ( Wfe + 50 ) / 100;           // ( 0.001+0.05 )→ 0.1 m/min
    return( (float)( Volt -  pDat->Volt[ Work ] ) / 10 );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      加減速時間を求める(溶接制御)                                        */
/*  [引数]                                                                  */
/*      PWIPCB          pDat        補間クラスポインタ                      */
/*  [戻り値]                                                                */
/*      float       加減速時間                                              */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
static  float  timecnt_w( PWIPCB pDat )
{
float       Time;
float       acc = (float)_ACC/10;     // @-R040701RTW

    Time = ( pDat->WFe - pDat->WFs ) / acc;
    if( Time < 0 )
        Time = -Time;
    else if( Time == 0 )
        Time = 0.05;
    return( Time );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      加減速時間を求める(サーボ速度)                                      */
/*  [引数]                                                                  */
/*      PWIPCB          pDat        補間クラスポインタ                      */
/*  [戻り値]                                                                */
/*      float       加減速時間                                              */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
static  float  timecnt_s( PSIPCB pDat )
{
float       Time;
float       acc = (float)_ACC/10;   // @-R040701RTW

    Time = ( pDat->WFe - pDat->WFs ) / acc;
    if( Time < 0 )
        Time = -Time;
    else if( Time == 0 )
        Time = 0.05;
    return( Time );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      加減速分割数を求める                                                */
/*  [引数]                                                                  */
/*      float       T       時間                                            */
/*  [戻り値]                                                                */
/*      int         分割数                                                  */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
static  int    divcnt( float T )
{
int     N;

    N = T / SHIREITIME;
    if( N < 1 )
        N = 1;
    return( N );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      加減速の初期化(溶接制御)                                            */
/*  [引数]                                                                  */
/*      int     Wfe     ワイヤ送給速度指令値( 0.001 )                       */
/*      int     Ve      指令電圧値( 0.1 )                                   */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
static  void    w_Init( int Wfe , int Ve )
{
PWIPCB      pDat = &_wipcb;
//////////////////////////////
//  指示値の記憶
    pDat->WFe_Target = Wfe;
    pDat->Ve_Target  = Ve;
//////////////////////////////
//  初期演算
    pDat->WFs        = pDat->Wf;
    pDat->Vps        = pDat->Vp;
    pDat->Vss        = pDat->Vs;
    pDat->WFe        = (float)Wfe/1000;
    pDat->Ve         = (float)Ve/10;
    pDat->Vpe        = GetVoltStep( Wfe , Ve , &pWT->S2V_Pulse );
    pDat->Vse        = GetVoltStep( Wfe , Ve , &pWT->S2V_Short );
    pDat->T          = timecnt_w( pDat );
    pDat->N          = divcnt( pDat->T );
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      加減速の初期化(溶接制御)                                            */
/*  [引数]                                                                  */
/*      int     Wfe     ワイヤ送給速度指令値( 0.001 )                       */
/*      int     Ve      指令電圧値( 0.1 )                                   */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2008.12.02 電流補間を行うために作成 H.Ihara                         */
/*--------------------------------------------------------------------------*/
static  void    w_Init2( int Wfe , int Cre ,int Ve )
{
PWIPCB      pDat = &_wipcb;
//////////////////////////////
//  指示値の記憶
    pDat->WFe_Target = Wfe;
    pDat->Ve_Target  = Ve;
    //<><><>電流補間 2008.12.02 <><><>
    pDat->CRe_Target = Cre;
    //<><><><><><><><><><><><><><><>
//////////////////////////////
//  初期演算
    pDat->WFs        = pDat->Wf;
    pDat->Vps        = pDat->Vp;
    pDat->Vss        = pDat->Vs;
    pDat->WFe        = (float)Wfe/1000;
    pDat->Ve         = (float)Ve/10;
    pDat->Vpe        = GetVoltStep( Wfe , Ve , &pWT->S2V_Pulse );
    pDat->Vse        = GetVoltStep( Wfe , Ve , &pWT->S2V_Short );
    pDat->T          = timecnt_w( pDat );
    //pDat->N          = divcnt( pDat->T );
    pDat->N          = 1; //2009.03.24
    //<><><>電流補間 2008.12.02 <><><>
    pDat->CRs        = pDat->Cr;
    pDat->CRe        = (float)Cre; //2008.12.10追加
    //<><><><><><><><><><><><><><><>
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      加減速の初期化(サーボ速度)                                          */
/*  [引数]                                                                  */
/*      int     Wfe     ワイヤ送給速度指令値( 0.001 )                       */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*      2004.10.15  R040701RTW-TAWERS       西川    NY20041015              */
/*--------------------------------------------------------------------------*/
static  void    s_Init( int Wfe )
{
PSIPCB      pDat = &_sipcb;

//////////////////////////////
//  指示値の記憶
    pDat->WFe_Target = Wfe;
//////////////////////////////
//  初期演算
    pDat->WFs        = pDat->Wf;
    pDat->WFe        = (float)Wfe/1000;
    pDat->T          = timecnt_s( pDat );
    pDat->N          = divcnt( pDat->T );
    pDat->WFe_rpm    = (sint)ConvRpm( pDat->WFe );  // 2004. 9.22
//  NY20041015
    pDat->WFe_Siji   = (sint)ConvRpm( (float)ctlclsSpeedGet_Siji( ) / 1000 ); //2005.12.27 del 　　2007.5.8復帰
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      補間計算                                                            */
/*  [引数]                                                                  */
/*      float       Start   スタート値                                      */
/*      float       End     目標値                                          */
/*      int         N       総分割数                                        */
/*      int         k       分割数カウンタ                                  */
/*  [戻り値]                                                                */
/*      float       補間データ                                              */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
static  float   xx_Hokan( float Start , float End , int N , int k )
{
    return( End - ( ( End - Start ) * ( N - k ) / N ) );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      パルスモードの取得                                                  */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      float   パルスモード                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
static  float   GetPulseMode( void )
{// @-R040301RTW
    if( DC_PMODE != 2 )
        return( 1.0 );          //たなか
    return( 2.0 );              //たなか
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      パラメータP2の取得                                                  */
/*  [引数]                                                                  */
/*      float       Wf              WFの補間データ                          */
/*      float       Vp              パルス用電圧の補間データ                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
static  float   GetP2( float Wf , float Vp )
{// @-R040301RTW
int     Work;
float   vlt;

//  小数第２を四捨五入して小数第１に丸める
    Work = ( Wf + 0.05 ) * 10;      // ( 0.001+0.05 )→ 0.1 m/min
    vlt = (float)pWT->S2V_Pulse.Volt[ Work ] / 10;
    return( vlt + Vp );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      パラメータP3の取得                                                  */
/*  [引数]                                                                  */
/*      float       Wf              WFの補間データ                          */
/*      float       Vs              短絡用電圧の補間データ                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
static  float   GetP3( float Wf , float Vs )
{// @-R040301RTW
int Work;
float   vlt;

//  小数第２を四捨五入して小数第１に丸める
    Work = ( Wf + 0.05 ) * 10;                   // ( 0.001+0.05 )→ 0.1 m/min
    vlt = (float)pWT->S2V_Short.Volt[ Work ] / 10;
    return( vlt + Vs );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      可変パラメータ係数の計算                                            */
/*  [引数]                                                                  */
/*      int     ParmNo      パラメータ番号(０～ ）                          */
/*      float   Data        計算するデータ                                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*      2004.09.14  R040701RTW-TAWERS       西田    微調                    */
/*      2004.10.20  R040701RTW-TAWERS       西川    NY20041020              */
/*--------------------------------------------------------------------------*/
static  float   CalParm( int ParmNo , float Data )
{// @-R040301RTW
PCALPARM        pRec = &_union.Nrm.CalParm[ ParmNo ];
float           Offset = _union.Nrm.CalOffset[ ParmNo ];   // @-R040701RTW
float           Work;

//<><><>2008.03.27中川さん要請で追加<><><>
#if 0 //2008.10.27 削除
	if (ParmNo == 12 || ParmNo == 19)
    {
		if (ParmNo == 12)
    	{
        	Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c ) + gf_Frequence_adjust_data;
    	}
		if (ParmNo == 19)
    	{
        	Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c ) + gf_Base_adjust_data;
    	}
    } else {
        Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );
    }
#endif

    Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c ); //2008.10.27 復活
    if( Work < pRec->min )
        Work = pRec->min;
    else if( Work > pRec->max )
        Work = pRec->max;
//  NY20041020  微調の反映を変更
//                  リミット処理後に加算→再度、リミット処理
    Work += Offset;
    if( Work < pRec->min )
        Work = pRec->min;
    else if( Work > pRec->max )
        Work = pRec->max;
    return( Work );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      単位変換    V                                                       */
/*  [引数]                                                                  */
/*      float   Data        変換するデータ                                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調    static止め      */
/*--------------------------------------------------------------------------*/
//static  float   ConvV( float Data )
float   ConvV( float Data )
{// @-R040301RTW
    return( Data * Conv_V );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      単位変換    T                                                       */
/*  [引数]                                                                  */
/*      float   Data        変換するデータ                                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
static  float   ConvT( float Data )
{// @-R040301RTW
    return( Data / Conv_T );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      単位変換    A                                                       */
/*  [引数]                                                                  */
/*      float   Data        変換するデータ                                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調    static止め      */
/*--------------------------------------------------------------------------*/
//static  float   ConvA( float Data )
float   ConvA( float Data )
{// @-R040301RTW
    return( Data * Conv_A );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      単位変換    Rpm                                                     */
/*  [引数]                                                                  */
/*      float   Data        変換するデータ                                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
static  float   ConvRpm( float Data )
{// @-R040301RTW
    return( Data * DC_RPM );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      パラメータPkの計算                                                  */
/*  [引数]                                                                  */
/*      float   P1      パルスモード   1.0=パルス 2.0=短絡                  */
/*  [戻り値]                                                                */
/*      usint   パラメータPk                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*      2005. 2.21  可変パラメータ演算:ny050217.c   西川                    */
/*--------------------------------------------------------------------------*/
/* ===================================[ Parm1 ]============================ */
static  usint   CalcParm1( float P1 )
{// @-R040301RTW

//    P1 = CalParm( 0 , P1 );
    // 単位変換なし

    return( (sint)P1 );
}
/* ===================================[ Parm2 ]============================ */
static  usint   CalcParm2( float Wf , float Vp )
{// @-R040301RTW
float   P2;

    P2 = GetP2( Wf , Vp );
    P2 = CalParm( 1 , P2 );
    //v_test = (sint)P2;
    P2 = ConvV( P2 );
    return( (sint)P2 );
}
/* ===================================[ Parm3 ]============================ */
static  usint   CalcParm3( float Wf , float Vs )
{// @-R040301RTW
float   P3;

    P3 = GetP3( Wf , Vs );
    P3 = CalParm( 2 , P3 );
    P3 = ConvV( P3 );
    return( (sint)P3 );
}
/* ===================================[ Parm4 ]============================ *//* 時間関連パラメータ */
static  usint   CalcParm4( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 3 , WF );
//    rc = ConvT( rc );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm5 ]============================ */
static  usint   CalcParm5( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 4 , WF );
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm6 ]============================ */
static  usint   CalcParm6( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 5 , WF );
//    rc = ConvT( rc );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm7 ]============================ */
static  usint   CalcParm7( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 6 , WF );
//    rc = ConvT( rc );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm8 ]============================ */
static  usint   CalcParm8( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 7 , WF );
//    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm9 ]============================ */
static  usint   CalcParm9( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 8 , WF );
//    rc = ConvT( rc );
    rc = ConvV( rc );
    return( (sint)rc );
}
/* ===================================[ Parm10 ]=========================== */
static  usint   CalcParm10( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 9 , WF );
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm11 ]=========================== */
static  usint   CalcParm11( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 10 , WF );
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm12 ]=========================== */
static  usint   CalcParm12( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 11 , WF );
//    rc = ConvT( rc );
    rc = ConvV( rc );
    return( (sint)rc );
}
/* ===================================[ Parm13 ]=========================== */
static  usint   CalcParm13( float WF )
{// @-R040301RTW

PCALPARM        pRec = &_union.Nrm.CalParm[ 12 ]; //2008.09.22
float           work; //2008.09.22

float   rc;

    rc = CalParm( 12 , WF );
//2009.03.27    rc = ConvT( rc );

#if 0 //2009.03.27
       if (gtt_Ctrl_flag.AC_control == false || gtt_En.ss_En_a_output == 0) //2008.12.18
       {
           rc = CalParm( 12 , WF );	
       } else {
           rc = _union.Nrm.CalParm[ 12 ].c;
       }
#endif

    rc = (1.0 / rc) / (Conv_T / 1000000.0);
    return( (sint)rc );
}
/* ===================================[ Parm14 ]=========================== */
static  usint   CalcParm14( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 13 , WF );
    T1 = rc; //2008.11.26
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm15 ]=========================== */
static  usint   CalcParm15( float WF )
{// @-R040301RTW
float   rc;

    //if (gtt_Ctrl_flag.AC_control == false || gtt_En.ss_En_a == 0) //2008.11.11
    if (gtt_Ctrl_flag.AC_control == false || gtt_En.ss_En_a_output == 0) //2008.12.18
    {
        rc = CalParm( 14 , WF );	
    } else {
        rc = _union.Nrm.CalParm[ 14 ].c;
    }




    //rc = CalParm( 14 , WF ); 2008.11.11 del
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm16 ]=========================== */
static  usint   CalcParm16( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 15 , WF );
    T3 = rc; //2008.11.26
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm17 ]=========================== */
static  usint   CalcParm17( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 16 , WF );
    T4 = rc; //2008.11.26
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm18 ]=========================== */
static  usint   CalcParm18( float WF )
{// @-R040301RTW
float   rc;


    rc = CalParm( 17 , WF );//2009.02.23
//    rc = ConvT( rc );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm19 ]=========================== *//* 電流関連パラメータ */
static  usint   CalcParm19( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 18 , WF );
    Ib2 = rc;
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm20 ]=========================== */
static  usint   CalcParm20( float WF )
{// @-R040301RTW
float   rc;
//(2009.04.09)BP_V20_V71_3JICALC+++++
PCALPARM        pRec = &_union.Nrm.CalParm[ 19 ];
float           Offset = _union.Nrm.CalOffset[ 19 ];
float           Work;
float           Data;
//(2009.04.09)BP_V20_V71_3JICALC-----

//20110921_1+++++
//20110921_1del 
//20110921_1del //(2010.03.01)BP_V20_V71_2JI+++++
//20110921_1del //V20、V71のハード処理を2次式化し、2次式＋新テーブル方式とする。
//20110921_1del //DEL
//20110921_1del //DEL//(2009.04.09)BP_V20_V71_3JICALC+++++
//20110921_1del //DEL//Del    rc = CalParm( 19 , WF ); //2009.02.23
//20110921_1del //DEL//Del    //rc = CalParm( 19 , WF ); 2008.11.11
//20110921_1del //DEL//(2009.04.09)BP_V20_V71_3JICALC-----
//20110921_1del //DEL
//20110921_1del //DEL//(2009.04.09)BP_V20_V71_3JICALC+++++
//20110921_1del //DEL//■■■ﾊｰﾄﾞAC　→3次式CALC処理
//20110921_1del //DEL     if((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
//20110921_1del //DEL        && (guc_Ac_wave_counter == 1))/*ハードＡＣ*/
//20110921_1del //DEL        {
//20110921_1del //DEL			Data = WF;//WF=指令/100
//20110921_1del //DEL		//Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );
//20110921_1del //DEL		/*実験式3次式で近似 y = 10.278x3 + 17.135x2 + 46.29x + 4.2424*/
//20110921_1del //DEL		//	Work = ( 10.278 * Data * Data *Data) 
//20110921_1del //DEL		//		 + ( 17.135 * Data * Data ) 
//20110921_1del //DEL		//		 + ( 46.29 * Data ) 
//20110921_1del //DEL		//		 + ( 4.2424 );
//20110921_1del //DEL		/*5次式 y = -1.8931x5 + 3.0668x4 + 51.688x3 - 117.92x2 + 160.88x - 13.198*/
//20110921_1del //DEL	//2010.01.26		Work = ( -1.8931 * Data * Data *Data *Data *Data) 
//20110921_1del //DEL	//2010.01.26			 + ( 3.0668  * Data * Data *Data *Data) 
//20110921_1del //DEL	//2010.01.26			 + ( 51.688  * Data * Data *Data) 
//20110921_1del //DEL	//2010.01.26			 + ( -117.92 * Data * Data ) 
//20110921_1del //DEL	//2010.01.26			 + ( 160.88  * Data ) 
//20110921_1del //DEL	//2010.01.26			 + ( -13.198 );
//20110921_1del //DEL	/*2010.01.26 500BP4 5次式 y = -0.2362x5 + 1.3506x4 + 6.6915x3 - 33.044x2 + 83.863x - 10.497*/
//20110921_1del //DEL		Work = ( -0.2362 * Data * Data *Data *Data *Data) 
//20110921_1del //DEL			 + ( 1.3506  * Data * Data *Data *Data) 
//20110921_1del //DEL			 + ( 6.6915  * Data * Data *Data) 
//20110921_1del //DEL			 + ( -33.044 * Data * Data ) 
//20110921_1del //DEL			 + ( 83.863  * Data ) 
//20110921_1del //DEL			 + ( -10.497 );
//20110921_1del //DEL		//maxmin処理・ｵﾌｾｯﾄ加算処理
//20110921_1del //DEL    		if( Work < pRec->min )Work = pRec->min;
//20110921_1del //DEL    		else if( Work > pRec->max )Work = pRec->max;
//20110921_1del //DEL    		Work += Offset;
//20110921_1del //DEL    		if( Work < pRec->min )Work = pRec->min;
//20110921_1del //DEL		    else if( Work > pRec->max )Work = pRec->max;
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1+++++
//20110921_1del //DEL			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
//20110921_1del //DEL			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
//20110921_1del //DEL    		if( Work < pRec->min )Work = pRec->min;
//20110921_1del //DEL		    else if( Work > pRec->max )Work = pRec->max;
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1-----
//20110921_1del //DEL		//Work=ﾊｰﾄﾞ用指令値
//20110921_1del //DEL			rc = Work;
//20110921_1del //DEL		}else{
//20110921_1del //DEL//■■■DC、手棒、標準AC、MIX時、ソフトAC時　→通常CALC処理
//20110921_1del //DEL		    rc = CalParm( 19 , WF );
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1+++++
//20110921_1del //DEL			Work = rc;
//20110921_1del //DEL			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
//20110921_1del //DEL			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
//20110921_1del //DEL    		if( Work < pRec->min )Work = pRec->min;
//20110921_1del //DEL		    else if( Work > pRec->max )Work = pRec->max;
//20110921_1del //DEL			rc = Work;
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1-----
//20110921_1del //DEL		}
//20110921_1del //DEL//(2009.04.09)BP_V20_V71_3JICALC-----
//20110921_1del //DEL
//20110921_1del //DEL//(2010.03.01)BP_V20_V71_2JI-----
//20110921_1del 
//20110921_1del //(2010.03.01)BP_V20_V71_2JI+++++
//20110921_1del 	rc = CalParm( 19 , WF );
//20110921_1del 	Work = rc;
//20110921_1del 	Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
//20110921_1del 	Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
//20110921_1del 	if( Work < pRec->min )Work = pRec->min;
//20110921_1del 	else if( Work > pRec->max )Work = pRec->max;
//20110921_1del 	rc = Work; 
//20110921_1del //(2010.03.01)BP_V20_V71_2JI-----
//20110921_1del     rc = ConvA( rc );
//20110921_1del     return( (sint)rc );
//20110921_1del 
//20110921_1del 
//20110921_1del 

//(2009.04.09)BP_V20_V71_3JICALC+++++
//■■■ﾊｰﾄﾞAC　→3次式CALC処理
     if((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
        && (guc_Ac_wave_counter == 1))/*ハードＡＣ*/
        {
			Data = WF;//WF=指令/100
		//Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );
		/*実験式3次式で近似 y = 10.278x3 + 17.135x2 + 46.29x + 4.2424*/
		//	Work = ( 10.278 * Data * Data *Data) 
		//		 + ( 17.135 * Data * Data ) 
		//		 + ( 46.29 * Data ) 
		//		 + ( 4.2424 );
		/*5次式 y = -1.8931x5 + 3.0668x4 + 51.688x3 - 117.92x2 + 160.88x - 13.198*/
			Work = ( -1.8931 * Data * Data *Data *Data *Data) 
				 + ( 3.0668  * Data * Data *Data *Data) 
				 + ( 51.688  * Data * Data *Data) 
				 + ( -117.92 * Data * Data ) 
				 + ( 160.88  * Data ) 
				 + ( -13.198 );
		//maxmin処理・ｵﾌｾｯﾄ加算処理
    		if( Work < pRec->min )Work = pRec->min;
    		else if( Work > pRec->max )Work = pRec->max;
    		Work += Offset;
    		if( Work < pRec->min )Work = pRec->min;
		    else if( Work > pRec->max )Work = pRec->max;
//(2009.04.11)BP_CTOFFSET_1+++++
			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    		if( Work < pRec->min )Work = pRec->min;
		    else if( Work > pRec->max )Work = pRec->max;
//(2009.04.11)BP_CTOFFSET_1-----
		//Work=ﾊｰﾄﾞ用指令値
			rc = Work;
		}else{
//■■■DC、手棒、標準AC、MIX時、ソフトAC時　→通常CALC処理
		    rc = CalParm( 19 , WF );
//(2009.04.11)BP_CTOFFSET_1+++++
			Work = rc;
			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    		if( Work < pRec->min )Work = pRec->min;
		    else if( Work > pRec->max )Work = pRec->max;
			rc = Work;
//(2009.04.11)BP_CTOFFSET_1-----
		}
//(2009.04.09)BP_V20_V71_3JICALC-----
    rc = ConvA( rc );
    return( (sint)rc );

//20110921_1-----

}
/* ===================================[ Parm21 ]=========================== */
static  usint   CalcParm21( float WF )
{// NY20051005
float   P2;

    P2 = GetP2( WF , 0 );
    P2 = CalParm( 1 , P2 );
    P2 = ConvV( P2 );
    return( (sint)P2 );
}
/* ===================================[ Parm22 ]=========================== */
static  usint   CalcParm22( float WF )
{// NY20051005
float   P3;

    P3 = GetP3( WF , 0 );
    P3 = CalParm( 2 , P3 );
    P3 = ConvV( P3 );
    return( (sint)P3 );
}
/* ===================================[ Parm23 ]=========================== */
static  usint   CalcParm23( float WF )
{// @-R040301RTW
//KOWA20060227+++++
float   rc;
#if 0
Dfloat   rc,rc1,rc2;
Dint        dat;
D
D//(2004.09.27)+++++
D//D    rc = CalParm( 19 , WF );
D    rc = CalParm( 18 , WF );
D//(2004.09.27)-----
D    rc1 = CalParm( 17 , WF );
D    rc2 = CalParm( 15 , WF );
D    rc = (rc - rc1) * 1024.0  / rc2;
D    rc = ConvA( rc );
D    dat = (int)rc >> 16;
D    return( (sint)dat );
#endif
    rc = CalParm( 22 , WF );
    rc = ConvT( rc );
    return( (sint)rc );
//KOWA20060227-----
}
/* ===================================[ Parm24 ]=========================== */
static  usint   CalcParm24( float WF )
{// @-R040301RTW
//KOWA20060227+++++
float   rc;
#if 0
Dfloat   rc,rc1,rc2;
Dint        dat;
D
D//(2004.09.27)+++++
D//D    rc = CalParm( 19 , WF );
D    rc = CalParm( 18 , WF );
D//(2004.09.27)-----
D    rc1 = CalParm( 17 , WF );
D    rc2 = CalParm( 15 , WF );
D    rc = (rc - rc1) * 1024.0  / rc2;
D    rc = ConvA( rc );
D    dat = (int)rc & 0x0000FFFF;
D    return( (sint)dat );
#endif
    rc = CalParm( 23 , WF );
	rc = rc * DC_RPM;
    return( (sint)rc );
//KOWA20060227-----
}
/* ===================================[ Parm25 ]=========================== */
/*
static  usint   CalcParm25( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int        dat;

    rc = CalParm( 18 , WF );
    rc1 = CalParm( 19 , WF );
    rc2 = CalParm( 16 , WF );
    rc = (rc - rc1) * 1024.0  / rc2;
    rc = ConvA( rc );
    dat = (int)rc >> 16;
    return( (sint)dat );
}
*/
static  usint   CalcParm25( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int		dat;

//(2004.07.01)+++++
//    rc = CalParm( 18 , WF );
//    rc1 = CalParm( 19 , WF );
    //rc = CalParm( 19 , WF ); 2008.11.14 del
    //if (gtt_Ctrl_flag.AC_control == false) //2008.11.14
    //if (gtt_Ctrl_flag.AC_control == false || gtt_En.ss_En_a == 0) //2008.11.17
    if (gtt_Ctrl_flag.AC_control == false || gtt_En.ss_En_a_output == 0) //2008.12.18
    {
        rc = CalParm( 19 , WF );	
    } else {
        rc = _union.Nrm.CalParm[ 19 ].c;
    }

    rc1 = CalParm( 18 , WF );
//(2004.07.01)-----
    rc2 = CalParm( 16 , WF );
//(2004.12.17)+++++
    rc2 = ConvT( rc2 );
//(2004.12.17)-----
	rc = (rc - rc1) * 1024.0  / rc2;
    rc = ConvA( rc );
	dat = (int)rc >> 16;
    return( (sint)dat );
}
/* ===================================[ Parm26 ]=========================== */
/*
static  usint   CalcParm26( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int        dat;

    rc = CalParm( 18 , WF );
    rc1 = CalParm( 19 , WF );
    rc2 = CalParm( 16 , WF );
    rc = (rc - rc1) * 1024.0  / rc2;
    rc = ConvA( rc );
    dat = (int)rc & 0x0000FFFF;
    return( (sint)dat );
}
*/
static  usint   CalcParm26( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int		dat;

//(2004.07.01)+++++
//    rc = CalParm( 18 , WF );
//    rc1 = CalParm( 19 , WF );
    //rc = CalParm( 19 , WF ); 2008.11.14
    //if (gtt_Ctrl_flag.AC_control == false) //2008.11.14
    //if (gtt_Ctrl_flag.AC_control == false || gtt_En.ss_En_a == 0) //2008.11.17
    if (gtt_Ctrl_flag.AC_control == false || gtt_En.ss_En_a_output == 0) //2008.12.18
    {
        rc = CalParm( 19 , WF );	
    } else {
        rc = _union.Nrm.CalParm[ 19 ].c;
    }
    rc1 = CalParm( 18 , WF );
//(2004.07.01)-----
    rc2 = CalParm( 16 , WF );
//(2004.12.17)+++++
    rc2 = ConvT( rc2 );
//(2004.12.17)-----
	rc = (rc - rc1) * 1024.0  / rc2;
    rc = ConvA( rc );
	dat = (int)rc & 0x0000FFFF;
    return( (sint)dat );
}
/* ===================================[ Parm27 ]=========================== */
static  usint   CalcParm27( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 26 , WF );
//    rc = ConvA( rc );
    rc = rc * 32;
    return( (sint)rc );
}
/* ===================================[ Parm28 ]=========================== */
static  usint   CalcParm28( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 27 , WF );
//    rc = ConvA( rc );
    rc = rc * 32;
    return( (sint)rc );
}
/* ===================================[ Parm29 ]=========================== *//* 電圧関連パラメータ */
static  usint   CalcParm29( float WF )
{// @-R040301RTW    この計算は、NORMARL-PULSE／DIP-PULSEの切替に
// @-R050507RK1     使用しているので変更しないで下さい（池田より）
//--float   rc;
//--
//--rc = CalParm( 28 , WF );
//--//  rc = ConvV( rc );
//--return( (sint)rc );
    return( DC_WELDCODE.pulseType );
}
/* ===================================[ Parm30 ]=========================== */
static  usint   CalcParm30( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 29 , WF );
//    rc = ConvV( rc );
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm31 ]=========================== */
static  usint   CalcParm31( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 30 , WF );
//    rc = ConvV( rc );
    rc = ConvT( rc );
    return( (sint)rc );
}
/* ===================================[ Parm32 ]=========================== */
static  usint   CalcParm32( float WF )
{// @-R040301RTW
float   rc,rc1;
int        dat;

    rc = CalParm( 31 , WF );
    rc1 =  rc / (1000.0 / Conv_T);
    if (rc1 < ADUNIT_A)
    {
        dat = 0;
    }
    else
    {
        dat = (int)(rc1 / ADUNIT_A);
    }
    return( (sint)dat );
}
/* ===================================[ Parm33 ]=========================== */
static  usint   CalcParm33( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int        dat;

    rc = CalParm( 31 , WF );
    rc1 =  rc / (1000.0 / Conv_T);
    if (rc1 < ADUNIT_A)
    {
        rc2 = rc1 * 10.0 * Conv_A;
    }
    else
    {
        dat = (int)(rc1 / ADUNIT_A);
        rc2 = ((rc1 / ADUNIT_A) - dat) * 10.0;
    }
    return( (sint)rc2 );
}
/* ===================================[ Parm34 ]=========================== */
static  usint   CalcParm34( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int        dat;

    rc = CalParm( 33 , WF );
    if (rc < 0)
    {
        rc1 = rc *  -1.0;
    }
    else
    {
        rc1 = rc;
    }
    rc2 =  rc1 / (1000.0 / Conv_T);
    if (rc2 < ADUNIT_A)
    {
        dat = 0;
    }
    else
    {
        dat = (int)(rc2 / ADUNIT_A);
    }
//(2004.06.18)+++++
    if (rc < 0)
    {
        dat = dat * (-1);
    }
//(2004.06.18)-----
    return( (sint)dat );
}
/* ===================================[ Parm35 ]=========================== */
static  usint   CalcParm35( float WF )
{// @-R040301RTW
float   rc,rc1,rc2,rc3;
int        dat;

    rc = CalParm( 33 , WF );
    if (rc < 0)
    {
        rc1 = rc *  -1.0;
    }
    else
    {
        rc1 = rc;
    }
    rc2 =  rc1 / (1000.0 / Conv_T);
    if (rc2 < ADUNIT_A)
    {
        rc3 = rc2 * 10.0 * Conv_A;
    }
    else
    {
        dat = (int)(rc2 / ADUNIT_A);
        rc3 = ((rc2 / ADUNIT_A) - dat) * 10.0;
    }
//(2004.06.18)+++++
    if (rc < 0)
    {
        rc3 = rc3 * (-1.0);
    }
//(2004.06.18)-----
    return( (sint)rc3 );
}
/* ===================================[ Parm36 ]=========================== *//* 特殊パラメータ */
static  usint   CalcParm36( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 35 , WF );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm37 ]=========================== */
static  usint   CalcParm37( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 36 , WF );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm38 ]=========================== */
static  usint   CalcParm38( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 37 , WF );
    rc = ConvV( rc );
    return( (sint)rc );
}
/* ===================================[ Parm39 ]=========================== */
static  usint   CalcParm39( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 38 , WF );
    // 単位変換なし
    return( (sint)rc );
}
/* ===================================[ Parm40 ]=========================== */
static  usint   CalcParm40( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 39 , WF );
    // 単位変換なし
    return( (sint)rc );
}
/* ===================================[ Parm41 ]=========================== */
static  usint   CalcParm41( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 40 , WF );
    rc = rc * 1000.0 / Conv_T;
    return( (sint)rc );
}
/* ===================================[ Parm42 ]=========================== */
static  usint   CalcParm42( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 41 , WF );
    rc = ConvV( rc );
    return( (sint)rc );
}
/* ===================================[ Parm43 ]=========================== */
static  usint   CalcParm43( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 42 , WF );
    rc = ConvV( rc );
    return( (sint)rc );
}
/* ===================================[ Parm44 ]=========================== */
static  usint   CalcParm44( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 43 , WF );
    rc = ConvV( rc );
    return( (sint)rc );
}
//(2004.06.22)+++++[S]
/* ===================================[ Parm45 ]=========================== */
static  usint   CalcParm45( float WF )
{// @-R040301RTW
float   rc,rc1;
int		dat;

    rc = CalParm( 44 , WF );
	rc1 =  rc / (1000.0 / Conv_T);
	if (rc1 < ADUNIT_A)
	{
		dat = 0;
	}
	else
	{
		dat = (int)(rc1 / ADUNIT_A);
	}
    return( (sint)dat );
}
/* ===================================[ Parm46 ]=========================== */
static  usint   CalcParm46( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int		dat;

    rc = CalParm( 45 , WF );
	rc1 =  rc / (1000.0 / Conv_T);
	if (rc1 < ADUNIT_A)
	{
		rc2 = rc1 * 10.0 * Conv_A;
	}
	else
	{
		dat = (int)(rc1 / ADUNIT_A);
		rc2 = ((rc1 / ADUNIT_A) - dat) * 10.0;
	}
    return( (sint)rc2 );
}
/* ===================================[ Parm47 ]=========================== */
static  usint   CalcParm47( float WF )
{// @-R040301RTW
float   rc,rc1,rc2;
int		dat;

    rc = CalParm( 46 , WF );
	if (rc < 0)
	{
		rc1 = rc *  -1.0;
	}
	else
	{
		rc1 = rc;
	}
	rc2 =  rc1 / (1000.0 / Conv_T);
	if (rc2 < ADUNIT_A)
	{
		dat = 0;
	}
	else
	{
		dat = (int)(rc2 / ADUNIT_A);
	}
	if (rc < 0)
	{
		dat = dat * (-1);
	}
    return( (sint)dat );
}
/* ===================================[ Parm48 ]=========================== */
static  usint   CalcParm48( float WF )
{// @-R040301RTW
float   rc,rc1,rc2,rc3;
int		dat;

    rc = CalParm( 47 , WF );
	if (rc < 0)
	{
		rc1 = rc *  -1.0;
	}
	else
	{
		rc1 = rc;
	}
	rc2 =  rc1 / (1000.0 / Conv_T);
	if (rc2 < ADUNIT_A)
	{
		rc3 = rc2 * 10.0 * Conv_A;
	}
	else
	{
		dat = (int)(rc2 / ADUNIT_A);
		rc3 = ((rc2 / ADUNIT_A) - dat) * 10.0;
	}
	if (rc < 0)
	{
		rc3 = rc3 * (-1.0);
	}
    return( (sint)rc3 );
}
/* ===================================[ Parm49 ]=========================== */
static  usint   CalcParm49( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 48 , WF );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm50 ]=========================== */
static  usint   CalcParm50( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 49 , WF );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm51 ]=========================== */
static  usint   CalcParm51( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 50 , WF );
    rc = ConvA( rc );
    return( (sint)rc );
}
/* ===================================[ Parm52 ]=========================== */
static  usint   CalcParm52( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 51 , WF );
    rc = ConvV( rc );
    return( (sint)rc );
}
/* ===================================[ Parm53 ]=========================== */
static  usint   CalcParm53( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 52 , WF );
    rc = ConvV( rc );
    return( (sint)rc );
}
/* ===================================[ Parm54 ]=========================== */
static  usint   CalcParm54( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 53 , WF );
//(2004.09.24)+++++
//    rc = ConvT( rc );
    rc = ConvV( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm55 ]=========================== */
static  usint   CalcParm55( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 54 , WF );
//(2004.09.24)+++++
//    rc = ConvT( rc );
    rc = ConvV( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
//(2004.06.22)-----[E]
/* ===================================[ Parm56 ]=========================== */
static  usint   CalcParm56( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 55 , WF );
//(2004.09.24)+++++
    rc = ConvV( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm57 ]=========================== */
static  usint   CalcParm57( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 56 , WF );
//(2004.09.24)+++++
    rc = ConvV( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm58 ]=========================== */
static  usint   CalcParm58( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 57 , WF );
//(2004.09.24)+++++
    rc = ConvV( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm59 ]=========================== */
static  usint   CalcParm59( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 58 , WF );
//(2004.09.24)+++++
    rc = ConvV( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm60 ]=========================== */
static  usint   CalcParm60( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 59 , WF );
//(2004.09.24)+++++
    rc = ConvV( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm61 ]=========================== */
static  usint   CalcParm61( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 60 , WF );
//(2004.09.24)+++++
    rc = ConvA( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm62 ]=========================== */
static  usint   CalcParm62( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 61 , WF );
//(2004.09.24)+++++
    rc = ConvA( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm63 ]=========================== */
static  usint   CalcParm63( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 62 , WF );
//(2004.09.24)+++++
    rc = ConvT( rc );
//(2004.09.24)-----
    return( (sint)rc );
}
/* ===================================[ Parm64 ]=========================== */
static  usint   CalcParm64( float WF )
{// @-R040301RTW
float   rc;

    rc = CalParm( 63 , WF );
//(2005.02.17)+++++
//(2004.09.24)+++++
//    rc = ConvT( rc );
//    rc = ConvV( rc );     NY20051006
    rc = ConvA( rc );   // NY20051006
//(2004.09.24)-----
//(2005.02.17)-----
    return( (sint)rc );
}

//可変パラメータ３２追加 2008.09.03
/* ===================================[ Parm65 ]=========================== */
static  usint   CalcParm65( float WF )
{
float   rc;

    rc = CalParm( 64 , WF );

    if (guc_Method_condition_data == EXP_DC_METHOD || guc_Method_condition_data == STD_DC_METHOD) //2009.02.18
    {
	if (guc_Pulse_mode_counter == 0) //2009.02.27
	{
            rc = 0;
        }
    }

    if (guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_AC_METHOD) //2009.02.18
    {
        rc = 1;
    }

    return( (sint)rc );
}
/* ===================================[ Parm66 ]=========================== */
static  usint   CalcParm66( float WF )
{
float   rc;

    rc = CalParm( 65 , WF );
//2009.03.27    rc = ConvT( rc );
    rc = (1.0 / rc) / (Conv_T / 1000000.0);
    return( (sint)rc );
}
/* ===================================[ Parm67 ]=========================== */
static  usint   CalcParm67( float WF )
{
float   rc;

    rc = CalParm( 66 , WF );
	rc = 1024.0*(100.0-rc)/100.0;
    return( (sint)rc );
}
/* ===================================[ Parm68 ]=========================== */
static  usint   CalcParm68( float WF )
{
float   rc;

    rc = CalParm( 67 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm69 ]=========================== */
static  usint   CalcParm69( float WF )
{
float   rc;

    rc = CalParm( 68 , WF );
//2009.03.27    rc = ConvT( rc );
    rc = (1.0 / rc) / (Conv_T / 1000000.0);
    return( (sint)rc );
}
/* ===================================[ Parm70 ]=========================== */
static  usint   CalcParm70( float WF )
{
float   rc;

    rc = CalParm( 69 , WF );
	rc = 1024.0*(100.0-rc)/100.0;
    return( (sint)rc );
}
/* ===================================[ Parm71 ]=========================== */
static  usint   CalcParm71( float WF )
{
float   rc;
//(2009.04.09)BP_V20_V71_3JICALC+++++
PCALPARM        pRec = &_union.Nrm.CalParm[ 70 ];
float           Offset = _union.Nrm.CalOffset[ 70 ];
float           Work;
float           Data;
//(2009.04.09)BP_V20_V71_3JICALC-----

//20110921_1+++++
//20110921_1del 
//20110921_1del //(2010.03.01)BP_V20_V71_2JI+++++
//20110921_1del //V20、V71のハード処理を2次式化し、2次式＋新テーブル方式とする。
//20110921_1del //DEL
//20110921_1del //DEL    rc = CalParm( 70 , WF );//一旦calcを通してmaxminにより指令を受信する。
//20110921_1del //DEL
//20110921_1del //DEL
//20110921_1del //DEL
//20110921_1del //DEL//(2009.04.09)BP_V20_V71_3JICALC+++++
//20110921_1del //DEL//■■■ﾊｰﾄﾞAC　→3次式CALC処理
//20110921_1del //DEL     if((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
//20110921_1del //DEL        && (guc_Ac_wave_counter == 1))/*ハードＡＣ*/
//20110921_1del //DEL        {
//20110921_1del //DEL			Data = rc/100;//可変のWF相当値算出し変数とする。
//20110921_1del //DEL		//Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );
//20110921_1del //DEL		/*実験式3次式で近似 y = 10.278x3 + 17.135x2 + 46.29x + 4.2424*/
//20110921_1del //DEL		//	Work = ( 10.278 * Data * Data *Data) 
//20110921_1del //DEL		//		 + ( 17.135 * Data * Data ) 
//20110921_1del //DEL		//		 + ( 46.29 * Data ) 
//20110921_1del //DEL		//		 + ( 4.2424 );
//20110921_1del //DEL		/*5次式 y = -1.8931x5 + 3.0668x4 + 51.688x3 - 117.92x2 + 160.88x - 13.198*/
//20110921_1del //DEL	//2010.01.26		Work = ( -1.8931 * Data * Data *Data *Data *Data) 
//20110921_1del //DEL	//2010.01.26			 + ( 3.0668  * Data * Data *Data *Data) 
//20110921_1del //DEL	//2010.01.26			 + ( 51.688  * Data * Data *Data) 
//20110921_1del //DEL	//2010.01.26			 + ( -117.92 * Data * Data ) 
//20110921_1del //DEL	//2010.01.26			 + ( 160.88  * Data ) 
//20110921_1del //DEL	//2010.01.26			 + ( -13.198 );
//20110921_1del //DEL	/*2010.01.26 500BP4 5次式 y = -0.2362x5 + 1.3506x4 + 6.6915x3 - 33.044x2 + 83.863x - 10.497*/
//20110921_1del //DEL		Work = ( -0.2362 * Data * Data *Data *Data *Data) 
//20110921_1del //DEL			 + ( 1.3506  * Data * Data *Data *Data) 
//20110921_1del //DEL			 + ( 6.6915  * Data * Data *Data) 
//20110921_1del //DEL			 + ( -33.044 * Data * Data ) 
//20110921_1del //DEL			 + ( 83.863  * Data ) 
//20110921_1del //DEL			 + ( -10.497 );
//20110921_1del //DEL		//maxmin処理・ｵﾌｾｯﾄ加算処理
//20110921_1del //DEL    		if( Work < 1 )Work = 1;
//20110921_1del //DEL    		else if( Work > 750 )Work = 750;
//20110921_1del //DEL    		Work += Offset;
//20110921_1del //DEL    		if( Work < 1 )Work = 1;
//20110921_1del //DEL    		else if( Work > 750 )Work = 750;
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1+++++
//20110921_1del //DEL			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
//20110921_1del //DEL			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
//20110921_1del //DEL    		if( Work < 1 )Work = 1;
//20110921_1del //DEL    		else if( Work > 750 )Work = 750;
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1-----
//20110921_1del //DEL			rc = Work; //Work=ﾊｰﾄﾞ用指令値
//20110921_1del //DEL		}else{
//20110921_1del //DEL//■■■DC、手棒、標準AC、MIX時、ソフトAC時　→通常2次式CALC処理
//20110921_1del //DEL//　一旦rc に指令電流値が保管される。
//20110921_1del //DEL			Data = rc/100;//可変のWF相当値を算出し変数とする。
//20110921_1del //DEL			Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );
//20110921_1del //DEL    		if( Work < 1 )Work = 1;
//20110921_1del //DEL    		else if( Work > 750 )Work = 750;
//20110921_1del //DEL			Work += Offset;
//20110921_1del //DEL    		if( Work < 1 )Work = 1;
//20110921_1del //DEL    		else if( Work > 750 )Work = 750;
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1+++++
//20110921_1del //DEL			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
//20110921_1del //DEL			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
//20110921_1del //DEL    		if( Work < 1 )Work = 1;
//20110921_1del //DEL    		else if( Work > 750 )Work = 750;
//20110921_1del //DEL//(2009.04.11)BP_CTOFFSET_1-----
//20110921_1del //DEL			rc = Work; //Work=ﾊｰﾄﾞ以外指令値
//20110921_1del //DEL		}
//20110921_1del //DEL//(2009.04.09)BP_V20_V71_3JICALC-----
//20110921_1del //(2010.03.01)BP_V20_V71_2JI-----
//20110921_1del 
//20110921_1del //(2010.03.08)+++++
//20110921_1del //(2010.03.08)//(2010.03.01)BP_V20_V71_2JI+++++
//20110921_1del //(2010.03.08)	rc = CalParm( 71 - 1 , WF );
//20110921_1del //(2010.03.08)	Work = rc;
//20110921_1del //(2010.03.08)	Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
//20110921_1del //(2010.03.08)	Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
//20110921_1del //(2010.03.08)	if( Work < pRec->min )Work = pRec->min;
//20110921_1del //(2010.03.08)	else if( Work > pRec->max )Work = pRec->max;
//20110921_1del //(2010.03.08)	rc = Work; 
//20110921_1del //(2010.03.08)//(2010.03.01)BP_V20_V71_2JI-----
//20110921_1del 
//20110921_1del 	rc = CalParm( 71 - 1 , WF );
//20110921_1del 
//20110921_1del 	Data = rc/100;//可変のWF相当値を算出し変数とする。
//20110921_1del 	Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );//２次式算出
//20110921_1del     if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
//20110921_1del 
//20110921_1del 	Work += Offset;
//20110921_1del     if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
//20110921_1del 
//20110921_1del 	Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
//20110921_1del 	Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
//20110921_1del     if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
//20110921_1del 
//20110921_1del 	rc = Work;
//20110921_1del //(2010.03.08)-----
//20110921_1del 
//20110921_1del     rc = ConvA( rc );
//20110921_1del     return( (sint)rc );
//20110921_1del 

    rc = CalParm( 70 , WF );//一旦calcを通してmaxminにより指令を受信する。

//(2009.04.09)BP_V20_V71_3JICALC+++++
//■■■ﾊｰﾄﾞAC　→3次式CALC処理
     if((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
        && (guc_Ac_wave_counter == 1))/*ハードＡＣ*/
        {
			Data = rc/100;//可変のWF相当値算出し変数とする。
		//Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );
		/*実験式3次式で近似 y = 10.278x3 + 17.135x2 + 46.29x + 4.2424*/
		//	Work = ( 10.278 * Data * Data *Data) 
		//		 + ( 17.135 * Data * Data ) 
		//		 + ( 46.29 * Data ) 
		//		 + ( 4.2424 );
		/*5次式 y = -1.8931x5 + 3.0668x4 + 51.688x3 - 117.92x2 + 160.88x - 13.198*/
			Work = ( -1.8931 * Data * Data *Data *Data *Data) 
				 + ( 3.0668  * Data * Data *Data *Data) 
				 + ( 51.688  * Data * Data *Data) 
				 + ( -117.92 * Data * Data ) 
				 + ( 160.88  * Data ) 
				 + ( -13.198 );
		//maxmin処理・ｵﾌｾｯﾄ加算処理
    		if( Work < 1 )Work = 1;
    		else if( Work > 750 )Work = 750;
    		Work += Offset;
    		if( Work < 1 )Work = 1;
    		else if( Work > 750 )Work = 750;
//(2009.04.11)BP_CTOFFSET_1+++++
			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    		if( Work < 1 )Work = 1;
    		else if( Work > 750 )Work = 750;
//(2009.04.11)BP_CTOFFSET_1-----
			rc = Work; //Work=ﾊｰﾄﾞ用指令値
		}else{
//■■■DC、手棒、標準AC、MIX時、ソフトAC時　→通常2次式CALC処理
//　一旦rc に指令電流値が保管される。
			Data = rc/100;//可変のWF相当値を算出し変数とする。
			Work = ( pRec->a * Data * Data ) + ( pRec->b * Data ) + ( pRec->c );
    		if( Work < 1 )Work = 1;
    		else if( Work > 750 )Work = 750;
			Work += Offset;
    		if( Work < 1 )Work = 1;
    		else if( Work > 750 )Work = 750;
//(2009.04.11)BP_CTOFFSET_1+++++
			Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
			Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    		if( Work < 1 )Work = 1;
    		else if( Work > 750 )Work = 750;
//(2009.04.11)BP_CTOFFSET_1-----
			rc = Work; //Work=ﾊｰﾄﾞ以外指令値
		}
//(2009.04.09)BP_V20_V71_3JICALC-----
    rc = ConvA( rc );
    return( (sint)rc );

//20110921_1-----

}
/* ===================================[ Parm72 ]=========================== */
static  usint   CalcParm72( float WF )
{
float   rc;

    //rc = CalParm( 71 , WF ); //2010.01.20 del

    //<><><><><> マイルドパルス傾度指定 2010.01.20 <><><><><>
    switch (gss_Select_dital[P_MILD_PULSE])
    {
       case 0: //傾度０
              rc = CalParm( 71 , WF );
              break;
       case 1: //傾度１
              rc = 6250;
              break;
       case 2: //傾度２
              rc = 18750;
              break;
       case 3: //傾度３
              rc = 31250;
              break;
       default:
              break;
    }
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>

    rc = ConvT( rc ); //2010.01.12
    return( (sint)rc );
}
/* ===================================[ Parm73 ]=========================== */
static  usint   CalcParm73( float WF )
{
float   rc;

    //rc = CalParm( 72 , WF ); //2010.01.20 del
    //<><><><><> マイルドパルス傾度指定 2010.01.20 <><><><><>
    switch (gss_Select_dital[P_MILD_PULSE])
    {
       case 0: //傾度０
              rc = CalParm( 72 , WF );//2010.03.09　誤記修正。71→72
              break;
       case 1: //傾度１
              rc = 6250;
              break;
       case 2: //傾度２
              rc = 18750;
              break;
       case 3: //傾度３
              rc = 31250;
              break;
       default:
              break;
    }
    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><>

    rc = ConvT( rc ); //2010.01.12
    return( (sint)rc );
}
/* ===================================[ Parm74 ]=========================== */
static  usint   CalcParm74( float WF )
{
float   rc;

    rc = CalParm( 73 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm75 ]=========================== */
static  usint   CalcParm75( float WF )
{
float   rc;

    rc = CalParm( 74 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm76 ]=========================== */
static  usint   CalcParm76( float WF )
{
float   rc;

    rc = CalParm( 75 , WF );
    rc = ConvA( rc ); //2010.01.21
    return( (sint)rc );
}
/* ===================================[ Parm77 ]=========================== */
static  usint   CalcParm77( float WF )
{
float   rc;

    rc = CalParm( 76 , WF );
    rc = ConvA( rc ); //2010.02.04
    return( (sint)rc );
}
/* ===================================[ Parm78 ]=========================== */
static  usint   CalcParm78( float WF )
{
float   rc;
float   rc1;//2010.03.01+++++ 田中換算追加
int     dat;//2010.03.01+++++ 田中換算追加

#if 0 //井原さん作成、コメント化しベースをきれいに残す。
    //<><><> アークアシスト機能 2010.03.01 <><><>
    rc = CalParm( 77 , WF );
    switch (gss_Select_dital[P_ARC_ASSIST])
    {
            case -4:
                  rc = rc - 200.0;
                  break;
            case -3:
                  rc = rc - 150.0;
                  break;
            case -2:
                  rc = rc - 100.0;
                  break;
            case -1:
                  rc = rc - 50.0;
                  break;
            case  0: //（標準）
                  rc = rc + 0.0;
                  break;
            case  1:
                  rc = rc + 50.0;
                  break;
            case  2:
                  rc = rc + 100.0;
                  break;
            case  3:
                  rc = rc + 150.0;
                  break;
            case  4:
                  rc = rc + 200.0;
                  break;
            default:
                  break;
    }
    if (rc > pWT->CalParm[78 - 1].max) rc = pWT->CalParm[78 - 1].max;
    if (rc < pWT->CalParm[78 - 1].min) rc = pWT->CalParm[78 - 1].min;
    
    if (gss_Select_dital[P_ARC_ASSIST] == -5) rc = 0;
    if (gss_Select_dital[P_ARC_ASSIST] ==  5) rc = 60000;
    //<><><><><><><><><><><><><><><><><><><><><><>
#endif

//2010.03.02 田中検討用追記
//2010.03.03 田中変更
//2010.03.05 田中変更
	rc = CalParm( 77 , WF );
	if((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
		&& (guc_Ac_wave_counter == 1))/*ハードＡＣ*/
	{/*========ハードAC時処理=======*/
		switch (gss_Select_dital[P_ARC_ASSIST]){
//2011.09.28+++++
//300BP4用
// 300BP4用波形アシストパラメータ
// ｱｼｽﾄ= 0：前300BP4(V1.06)、500BP4のｱｼｽﾄ5
//      -1：500BP4のｱｼｽﾄ 0
//      -2：500BP4のｱｼｽﾄ-5
//  -3～-5：300BP4で新規に作成した値
//   1～ 5：0と同波形（最大傾度）。
		case  5:rc=60000;  break;//5
		case  4:rc=60000;  break;//4
		case  3:rc=60000;  break;//4
		case  2:rc=60000;  break;//3
		case  1:rc=60000;  break;//2
		case  0:break;//rc=60000;  break;//1 ※=0で最大（旧標準波形）
		case -1:rc=600;    break;//500BP4の0
		case -2:rc=300;    break;//500BP4の-5
		case -3:rc=300- 60;break;//
		case -4:rc=300-120;break;//
		case -5:rc=300-180;break;//MIN調整

//D 500BP4参考
//D		case  5:rc=60000;      break;//MAX調整
//D		case  4:rc=600 + 600.0;break;
//D		case  3:rc=600 + 450.0;break;
//D		case  2:rc=600 + 300.0;break;
//D		case  1:rc=600 + 150.0;break;
//D		case  0:break;//rc=600 +     0;break;//rcを利用
//D		case -1:rc=600 -  60.0;break;
//D		case -2:rc=600 - 120.0;break;
//D		case -3:rc=600 - 180.0;break;
//D		case -4:rc=600 - 240.0;break;
//D		case -5:rc=300;        break;//MIN調整
//2011.09.28-----
		default:break;
		}
	}else{/*========ハードAC以外時処理（標準、ソフト、MIX、DC)=======*/
		switch (gss_Select_dital[P_ARC_ASSIST]){
//2011.09.28+++++
//300BP4用
//300BP4用
// 300BP4用波形アシストパラメータ
// ｱｼｽﾄ= 0：前300BP4(V1.06)、500BP4のｱｼｽﾄ5
//      -1：500BP4のｱｼｽﾄ-1
//      -2：500BP4のｱｼｽﾄ-5
//  -3～-5：300BP4で新規に作成した値
//   1～ 5：0と同波形（最大傾度）。
		case  5:rc=60000;  break;//5
		case  4:rc=60000;  break;//4
		case  3:rc=60000;  break;//4
		case  2:rc=60000;  break;//3
		case  1:rc=60000;  break;//2
		case  0:break;//rc=60000;  break;//1 ※=0で最大（旧標準波形）
		case -1:rc=600;    break;//500BP4の-1
		case -2:rc=300;    break;//500BP4の-5
		case -3:rc=300- 60;break;//
		case -4:rc=300-120;break;//
		case -5:rc=300-180;break;//MIN調整

//D 500BP4参考
//D		case  5:rc=60000;      break;//5
//D		case  4:rc=600 + 850.0;break;//4
//D		case  3:rc=600 + 600.0;break;//4
//D		case  2:rc=600 + 450.0;break;//3
//D		case  1:rc=600 + 300.0;break;//2
//D		case  0:rc=600 + 150.0;break;//1
//D		case -1:break;//rc=600 +     0;break;//rcを利用
//D		case -2:rc=600 -  60.0;break;//-1
//D		case -3:rc=600 - 120.0;break;//-2
//D		case -4:rc=600 - 180.0;break;//-3
//D//		case -4:rc=600 - 240.0;break;//-4
//D		case -5:rc=300;        break;//-5
//2011.09.28-----
		default:break;
		}
	}
    if (rc > pWT->CalParm[78 - 1].max) rc = pWT->CalParm[78 - 1].max;
    if (rc < pWT->CalParm[78 - 1].min) rc = pWT->CalParm[78 - 1].min;

//2010.03.01+++++ 田中換算追加
// A/ms を換算する。
//　例）550A/ms → 550/(1000/12.5)/(750.0 / 32752.0)=300dec
//　　　最大値　***/(1000/12.5)/(750.0/32752.0)=7FF0hex
//　　　　　　　***=7FF0hex * (1000/12.5) * (750/32752) = 60000
//    rc = CalParm( 77 , WF );
    rc1 =  rc / (1000.0 / Conv_T);
    if (rc1 < ADUNIT_A)
    {
        dat = 0;
    }
    else
    {
        dat = (int)(rc1 / ADUNIT_A);
    }
	rc=dat;
//2010.03.01----- 田中換算追加
    return( (sint)rc );
}
/* ===================================[ Parm79 ]=========================== */
static  usint   CalcParm79( float WF )
{
float   rc;
//2010.03.09    rc = CalParm( 78 , WF );
//2010.03.09    return( (sint)rc );
float           Work;
float           Data;
float   rc_V20;
PCALPARM        pRec_V20 = &_union.Nrm.CalParm[ 19 ];
float           Offset_V20 = _union.Nrm.CalOffset[ 19 ];
float   rc_V71;
PCALPARM        pRec_V71 = &_union.Nrm.CalParm[ 70 ];
float           Offset_V71 = _union.Nrm.CalOffset[ 70 ];
float   rc_mildpls_tm;

//---------------------------------覚書き４．０Ｈｚ以下のマイルドパルス---------------------------------
//DSPにより作成する
//32Rは傾きを算出しDSPにV79,V81を通して送信する。
//算出は、(IP-IB)/ﾏｲﾙﾄﾞ時間 にて作成する。100us(12.5X8)換算とする。
//DSPは、32R指令変化に対して、制限をかけることで、ﾏｲﾙﾄﾞﾊﾟﾙｽの傾きを実現する。
//よって、傾き制限不要な箇所（スタート中等）では、傾きを立てておく（ﾏｲﾙﾄﾞ無効)必要あり。
//同じ理由で、DSPパルスの場合は、本傾きを無効（最大値）としておく必要あり。
//
//＜注意＞
//32Rパルス中のIP指令とIB指令の設定方法を十分考慮する必要あり。
//　通常のIB指令(V20)は32Rパルス中は動いている。
//　通常のIP指令(V71)は32Rパルス中は現状では、設定されていない。
//ｱｯﾌﾟｽﾛｰﾌﾟ、ﾀﾞｳﾝｽﾛｰﾌﾟとの関連。何をIP指令、IB指令として用いるか。
//ﾏｲﾙﾄﾞ時間はﾊﾟﾙｽﾋﾟｰｸ時間、ﾊﾟﾙｽﾍﾞｰｽ時間より短い必要あり。クリップ処理追加のこと。
//---------------------------------------------------------------------------------------------------

//---------------------------------IB作成---------------------------------
	rc_V20 = current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr);//パルスベース電流指令値設定
	Data = rc_V20/100;//可変のWF相当値を算出し変数とする。
	Work = ( pRec_V20->a * Data * Data ) + ( pRec_V20->b * Data ) + ( pRec_V20->c );//２次式算出
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += Offset_V20;
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
	Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	rc_V20 = Work;//IB
//---------------------------------IP作成---------------------------------
	rc_V71 =current_table_data_member(gtt_Internal_pack.Data.In.usIP);//パルスピーク電流指令値設定
	Data = rc_V71/100;//可変のWF相当値を算出し変数とする。
	Work = ( pRec_V71->a * Data * Data ) + ( pRec_V71->b * Data ) + ( pRec_V71->c );//２次式算出
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += Offset_V71;
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
	Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	rc_V71 = Work;//IP
//---------------------------------マイルドパルス立上り時間作成---------------------------------
//ﾏｲﾙﾄﾞﾊﾟﾙｽ立上り時間≦直流パルスピーク時間の関係必要。後日処理追加のこと。
    switch (gss_Select_dital[P_MILD_PULSE]){
       case 0: /*傾度０*/  rc_mildpls_tm = CalParm( 79 - 1 , WF );break;/*[us]*/
       case 1: /*傾度１*/  rc_mildpls_tm = 6250;break;/*[us]*/
       case 2: /*傾度２*/  rc_mildpls_tm = 18750;break;/*[us]*/
       case 3: /*傾度３*/  rc_mildpls_tm = 31250;break;/*[us]*/
       default:break;
    }
//20110829_1+++++
//--------------------------------パルス周期制限---------------------------------
//  パルス周期によりマイルドパルスデータ（時間）を制限する。パルス周期≧マイルドパルス時間とする。
//　4.0Hz以下マイルドパルス動作時、
//　DSPは、現在の指令が、IP指令かIB指令かを認識できず、
//　ターゲット指令＞現指令 を比較し、UPSLP傾度、DOWNSLP傾度を切り替えている。
//　よって、IP<IB のような場合、UP側とDOWN側の傾度を反転して送信する。
	if(rc_V71 >= rc_V20){//IP>IBの場合
		Work = 100000 * (float)gtt_Internal_pack.Data.In.usPulseDuty / (float)gtt_Internal_pack.Data.In.usPulseFreq;//= 1000000[us]/(Pulse_freq[10Hz]/10)*(Pulse_duty[%]/100)
	}else{ //IP<IBの場合
		Work = 100000 * (100.0 - (float)gtt_Internal_pack.Data.In.usPulseDuty) / (float)gtt_Internal_pack.Data.In.usPulseFreq;
	}
//（参考）
//     _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;
//     _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;
	if(rc_mildpls_tm > Work){
		rc_mildpls_tm = Work;
	}
//20110829_1-----
//---------------------------------マイルドパルス立上り傾度作成---------------------------------
//　＝（ＩＰ－ＩＢ）／立上り時間　にて算出する。絶対値化（整数）の必要あり。
//　Conv_Tの際、100us毎の傾きに換算すること。
	if(rc_mildpls_tm < (Conv_T * 8.0)){//立上り時間小さい場合（０含む）の処理
		Data = 32752.0;//最大立上り傾度
	}else{
		Data  = ((rc_V20 - rc_V71) * Conv_A ) / (rc_mildpls_tm / (Conv_T * 8.0));//Adat/100us の単位系とする。
	}
	if(Data < 0){Data = -1.0 * Data;}//絶対値化、必ず正数を送信すること。
	if(Data < 1.0){Data = 1.0;}//最低値=1.0
//20110829_1+++++
	if (guc_Pulse_mode_data == 0x00){//パルス無し時
		Data = 32752.0;//最大立上り傾度
	}
//20110829_1-----
	rc=Data;
//20110829_1+++++
//d	rc=32752;//2010.03.18 動作未確定のため処理無効とする。
//20110829_1-----
    return( (sint)rc );
}
/* ===================================[ Parm80 ]=========================== */
static  usint   CalcParm80( float WF )
{
float   rc;
float   rc1;//2010.03.01+++++ 田中換算追加
int     dat;//2010.03.01+++++ 田中換算追加

#if 0 //井原さん作成、コメント化しベースをきれいに残す。
    //<><><> アークアシスト機能 2010.03.01 <><><>
    rc = CalParm( 79 , WF );
    switch (gss_Select_dital[P_ARC_ASSIST])
    {
            case -4:
                  rc = rc - 200.0;
                  break;
            case -3:
                  rc = rc - 150.0;
                  break;
            case -2:
                  rc = rc - 100.0;
                  break;
            case -1:
                  rc = rc - 50.0;
                  break;
            case  0: //（標準）
                  rc = rc + 0.0;
                  break;
            case  1:
                  rc = rc + 50.0;
                  break;
            case  2:
                  rc = rc + 100.0;
                  break;
            case  3:
                  rc = rc + 150.0;
                  break;
            case  4:
                  rc = rc + 200.0;
                  break;
            default:
                  break;
    }
    if (rc > pWT->CalParm[80 - 1].max) rc = pWT->CalParm[80 - 1].max;
    if (rc < pWT->CalParm[80 - 1].min) rc = pWT->CalParm[80 - 1].min;
    
    if (gss_Select_dital[P_ARC_ASSIST] == -5) rc = 0;
    if (gss_Select_dital[P_ARC_ASSIST] ==  5) rc = 60000;
    //<><><><><><><><><><><><><><><><><><><><><><>
#endif

//2010.03.02 田中検討用追記
//2010.03.03 田中変更
//2010.03.05 田中変更
	rc = CalParm( 79 , WF );
	if((guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD)
		&& (guc_Ac_wave_counter == 1))/*ハードＡＣ*/
	{/*========ハードAC時処理=======*/
		switch (gss_Select_dital[P_ARC_ASSIST]){
//2011.09.28+++++
//300BP4用
//300BP4用
// 300BP4用波形アシストパラメータ
// ｱｼｽﾄ= 0：前300BP4(V1.06)、500BP4のｱｼｽﾄ5
//      -1：500BP4のｱｼｽﾄ 0
//      -2：500BP4のｱｼｽﾄ-5
//  -3～-5：300BP4で新規に作成した値
//   1～ 5：0と同波形（最大傾度）。
		case  5:rc=60000;  break;//5
		case  4:rc=60000;  break;//4
		case  3:rc=60000;  break;//4
		case  2:rc=60000;  break;//3
		case  1:rc=60000;  break;//2
		case  0:break;//rc=60000;  break;//1 ※=0で最大（旧標準波形）
		case -1:rc=600;    break;//500BP4の0
		case -2:rc=300;    break;//500BP4の-5
		case -3:rc=300- 60;break;//
		case -4:rc=300-120;break;//
		case -5:rc=300-180;break;//MIN調整

//D 500BP4参考
//D		case  5:rc=60000;      break;//MAX調整
//D		case  4:rc=600 + 600.0;break;
//D		case  3:rc=600 + 450.0;break;
//D		case  2:rc=600 + 300.0;break;
//D		case  1:rc=600 + 150.0;break;
//D		case  0:break;//rc=600 +     0;break;//rcを利用
//D		case -1:rc=600 -  60.0;break;
//D		case -2:rc=600 - 120.0;break;
//D		case -3:rc=600 - 180.0;break;
//D		case -4:rc=600 - 240.0;break;
//D		case -5:rc=300;        break;//MIN調整
//2011.09.28-----
		default:break;
		}
	}else{/*========ハードAC以外時処理（標準、ソフト、MIX、DC)=======*/
		switch (gss_Select_dital[P_ARC_ASSIST]){
//2011.09.28+++++
//300BP4用
//300BP4用
// 300BP4用波形アシストパラメータ
// ｱｼｽﾄ= 0：前300BP4(V1.06)、500BP4のｱｼｽﾄ5
//      -1：500BP4のｱｼｽﾄ-1
//      -2：500BP4のｱｼｽﾄ-5
//  -3～-5：300BP4で新規に作成した値
//   1～ 5：0と同波形（最大傾度）。
		case  5:rc=60000;  break;//5
		case  4:rc=60000;  break;//4
		case  3:rc=60000;  break;//4
		case  2:rc=60000;  break;//3
		case  1:rc=60000;  break;//2
		case  0:break;//rc=60000;  break;//1 ※=0で最大（旧標準波形）
		case -1:rc=600;    break;//500BP4の-1
		case -2:rc=300;    break;//500BP4の-5
		case -3:rc=300- 60;break;//
		case -4:rc=300-120;break;//
		case -5:rc=300-180;break;//MIN調整

//D 500BP4参考
//D		case  5:rc=60000;      break;//5
//D		case  4:rc=600 + 850.0;break;//4
//D		case  3:rc=600 + 600.0;break;//4
//D		case  2:rc=600 + 450.0;break;//3
//D		case  1:rc=600 + 300.0;break;//2
//D		case  0:rc=600 + 150.0;break;//1
//D		case -1:break;//rc=600 +     0;break;//rcを利用
//D		case -2:rc=600 -  60.0;break;//-1
//D		case -3:rc=600 - 120.0;break;//-2
//D		case -4:rc=600 - 180.0;break;//-3
//D//		case -4:rc=600 - 240.0;break;//-4
//D		case -5:rc=300;        break;//-5
//2011.09.28-----
		default:break;
		}
	}
    if (rc > pWT->CalParm[80 - 1].max) rc = pWT->CalParm[80 - 1].max;
    if (rc < pWT->CalParm[80 - 1].min) rc = pWT->CalParm[80 - 1].min;

//2010.03.01+++++ 田中換算追加
// A/ms を換算する。
//　例）550A/ms → 550/(1000/12.5)/(750.0 / 32752.0)=300dec
//　　　最大値　***/(1000/12.5)/(750.0/32752.0)=7FF0hex
//　　　　　　　***=7FF0hex * (1000/12.5) * (750/32752) = 60000
//    rc = CalParm( 79 , WF );
    rc1 =  rc / (1000.0 / Conv_T);
    if (rc1 < ADUNIT_A)
    {
        dat = 0;
    }
    else
    {
        dat = (int)(rc1 / ADUNIT_A);
    }
	rc=dat;
//2010.03.01----- 田中換算追加
    return( (sint)rc );
}
/* ===================================[ Parm81 ]=========================== */
static  usint   CalcParm81( float WF )
{
float   rc;
//2010.03.09    rc = CalParm( 80 , WF );
//2010.03.09    return( (sint)rc );
float           Work;
float           Data;
float   rc_V20;
PCALPARM        pRec_V20 = &_union.Nrm.CalParm[ 19 ];
float           Offset_V20 = _union.Nrm.CalOffset[ 19 ];
float   rc_V71;
PCALPARM        pRec_V71 = &_union.Nrm.CalParm[ 70 ];
float           Offset_V71 = _union.Nrm.CalOffset[ 70 ];
float   rc_mildpls_tm;
//---------------------------------IB作成---------------------------------
	rc_V20 = current_table_data_member(gtt_Internal_pack.Data.In.usWeldingCurr);//パルスベース電流指令値設定
	Data = rc_V20/100;//可変のWF相当値を算出し変数とする。
	Work = ( pRec_V20->a * Data * Data ) + ( pRec_V20->b * Data ) + ( pRec_V20->c );//２次式算出
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += Offset_V20;
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
	Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	rc_V20 = Work;//IB
//---------------------------------IP作成---------------------------------
	rc_V71 =current_table_data_member(gtt_Internal_pack.Data.In.usIP);//パルスピーク電流指令値設定
	Data = rc_V71/100;//可変のWF相当値を算出し変数とする。
	Work = ( pRec_V71->a * Data * Data ) + ( pRec_V71->b * Data ) + ( pRec_V71->c );//２次式算出
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += Offset_V71;
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	Work += ((float)gtt_Special_menu.ss_Service_data[S_CT_OFFSET] * (float)0.2);
	Work += ((float)gss_Ct_offset * 0.2);//ＤＳＷ調整分
    if( Work < 0.1 ){Work = 0.1;}else if( Work > 700.0 ){Work = 700.0;} //max/min
	rc_V71 = Work;//IP
//---------------------------------マイルドパルス立上り時間作成---------------------------------
//ﾏｲﾙﾄﾞﾊﾟﾙｽ立上り時間≦直流パルスピーク時間の関係必要。後日処理追加のこと。
    switch (gss_Select_dital[P_MILD_PULSE]){
       case 0: /*傾度０*/  rc_mildpls_tm = CalParm( 81 - 1 , WF );break;/*[us]*/
       case 1: /*傾度１*/  rc_mildpls_tm = 6250;break;/*[us]*/
       case 2: /*傾度２*/  rc_mildpls_tm = 18750;break;/*[us]*/
       case 3: /*傾度３*/  rc_mildpls_tm = 31250;break;/*[us]*/
       default:break;
    }
//20110829_1+++++
//--------------------------------パルス周期制限---------------------------------
//  パルス周期によりマイルドパルスデータ（時間）を制限する。パルス周期≧マイルドパルス時間とする。
//　4.0Hz以下マイルドパルス動作時、
//　DSPは、現在の指令が、IP指令かIB指令かを認識できず、
//　ターゲット指令＞現指令 を比較し、UPSLP傾度、DOWNSLP傾度を切り替えている。
//　よって、IP<IB のような場合、UP側とDOWN側の傾度を反転して送信する。
	if(rc_V71 >= rc_V20){//IP>IBの場合
		Work = 100000 * (100.0 - (float)gtt_Internal_pack.Data.In.usPulseDuty) / (float)gtt_Internal_pack.Data.In.usPulseFreq;
	}else{ //IP<IBの場合
		Work = 100000 * (float)gtt_Internal_pack.Data.In.usPulseDuty / (float)gtt_Internal_pack.Data.In.usPulseFreq;//= 1000000[us]/(Pulse_freq[10Hz]/10)*(Pulse_duty[%]/100)
	}
//（参考）
//     _union.Nrm.CalParm[69 - 1].c = (float)gtt_Internal_pack.Data.In.usPulseFreq / 10;
//     _union.Nrm.CalParm[70 - 1].c = gtt_Internal_pack.Data.In.usPulseDuty;
	if(rc_mildpls_tm > Work){
		rc_mildpls_tm = Work;
	}
//20110829_1-----
//---------------------------------マイルドパルス立上り傾度作成---------------------------------
//　＝（ＩＰ－ＩＢ）／立上り時間　にて算出する。絶対値化（整数）の必要あり。
//　Conv_Tの際、100us毎の傾きに換算すること。
	if(rc_mildpls_tm < (Conv_T * 8.0)){//立上り時間小さい場合（０含む）の処理
		Data = 32752.0;//最大立上り傾度
	}else{
		Data  = ((rc_V20 - rc_V71) * Conv_A ) / (rc_mildpls_tm / (Conv_T * 8.0));//Adat/100us の単位系とする。
	}
	if(Data < 0){Data = -1.0 * Data;}//絶対値化、必ず正数を送信すること。
	if(Data < 1.0){Data = 1.0;}//最低値=1.0
//20110829_1+++++
	if (guc_Pulse_mode_data == 0x00){//パルス無し時
		Data = 32752.0;//最大立上り傾度
	}
//20110829_1-----
	rc=Data;
//20110829_1+++++
//d	rc=32752;//2010.03.10 動作未確定のため処理無効とする。
//20110829_1-----
    return( (sint)rc );
}
/* ===================================[ Parm82 ]=========================== */
static  usint   CalcParm82( float WF )
{
float   rc;

    rc = CalParm( 81 , WF );
    rc = ConvA( rc ); //2010.03.01 田中追加
    return( (sint)rc );
}
/* ===================================[ Parm83 ]=========================== */
static  usint   CalcParm83( float WF )
{
float   rc;

    rc = CalParm( 82 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm84 ]=========================== */
static  usint   CalcParm84( float WF )
{
float   rc;

    rc = CalParm( 83 , WF ); //2009.02.23


    //rc = CalParm( 83 , WF ); 2008.11.11
//(2008.08.29)TEST+++++
    rc = ConvA( rc );
//(2008.08.29)TEST-----
    return( (sint)rc );
}
/* ===================================[ Parm85 ]=========================== */
static  usint   CalcParm85( float WF )
{
float   rc;

    rc = CalParm( 84 , WF );
	rc = 1024.0*(100.0-rc)/100.0;
    return( (sint)rc );
}
/* ===================================[ Parm86 ]=========================== */
static  usint   CalcParm86( float WF )
{
float   rc;

    rc = CalParm( 85 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm87 ]=========================== */
static  usint   CalcParm87( float WF )
{
float   rc;

    rc = CalParm( 86 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm88 ]=========================== */
static  usint   CalcParm88( float WF )
{
float   rc;

    rc = CalParm( 87 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm89 ]=========================== */
static  usint   CalcParm89( float WF )
{
float   rc;

    rc = CalParm( 88 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm90 ]=========================== */
static  usint   CalcParm90( float WF )
{
float   rc;
//PWIPCB  pIP = &_wipcb;//test

    //rc = CalParm( 89 , WF ); 2008.12.02 del
    //<><><>電流補間 2008.12.02<><><>
      //rc = WF; //WFはここではpIP->Cr
      rc = WF * gf_Frq_data; //WFはここではpIP->Cr 2008.12.16変更
      rc = ConvA(rc);
      //rc = pIP->CRe_Target; //test
    //<><><><><><><><><><><><><><><>
    return( (sint)rc );
}
/* ===================================[ Parm90_1]=========================== */
static  usint   CalcParm90_1( float CR , float WF ) //2008.12.24
{
float   rc;

      rc = CR * gf_Frq_data;
      if ((guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85) && gtt_En.ss_En_a_output == 0)
      {
           if (WF < gf_Wf_max_limit)
           {
               rc = CR * (gf_Correct_a * WF + gf_Correct_b);
           }
      }

      rc = ConvA(rc);
    return( (sint)rc );
}
/* ===================================[ Parm91 ]=========================== */
static  usint   CalcParm91( float WF )
{
float   rc;

    rc = CalParm( 90 , WF );
    rc = ConvV(rc); //2008.12.12
    return( (sint)rc );
}
/* ===================================[ Parm92 ]=========================== */
static  usint   CalcParm92( float WF )
{
float   rc;

    rc = CalParm( 91 , WF );
    rc = ConvA( rc );//2008.12.15
    return( (sint)rc );
}
/* ===================================[ Parm93 ]=========================== */
static  usint   CalcParm93( float WF )
{
float   rc;

    rc = CalParm( 92 , WF );
//2010.03.09    rc = (rc * 256) * AD_I/AD_V; //2009.01.09
    rc = ConvT( rc ); //2010.03.09
    return( (sint)rc );
}
/* ===================================[ Parm94 ]=========================== */
static  usint   CalcParm94( float WF )
{
float   rc;

    rc = CalParm( 93 , WF );
    rc = ConvT( rc ); //2010.03.09
    return( (sint)rc );
}
/* ===================================[ Parm95 ]=========================== */
static  usint   CalcParm95( float WF )
{
float   rc;

    rc = CalParm( 94 , WF );
    return( (sint)rc );
}
/* ===================================[ Parm96 ]=========================== */
static  usint   CalcParm96( float WF )
{
float   rc;

    rc = CalParm( 95 , WF );
    return( (sint)rc );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件パラメータセット用テーブル                                  */
/*  [データ説明]                                                            */
/*      usint           (*pProc)( float )   パラメータセット関数ポインタ    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    usint   (*pProc)( float );
}CALLDEF;

static  CALLDEF const   pCallTable[ ] =
{
    NULL      , 
    NULL      , 
    NULL      , 
    CalcParm4 , 
    CalcParm5 , 
    CalcParm6 , 
    CalcParm7 , 
    CalcParm8 , 
    CalcParm9 , 
    CalcParm10 , 
    CalcParm11 , 
    CalcParm12 , 
    CalcParm13 , 
    CalcParm14 , 
    CalcParm15 , 
    CalcParm16 , 
    CalcParm17 , 
    CalcParm18 , 
    CalcParm19 , 
    CalcParm20 , 
    CalcParm21 , 
    CalcParm22 , 
    CalcParm23 , 
    CalcParm24 , 
    CalcParm25 , 
    CalcParm26 , 
    CalcParm27 , 
    CalcParm28 , 
    CalcParm29 , 
    CalcParm30 , 
    CalcParm31 , 
    CalcParm32 , 
    CalcParm33 , 
    CalcParm34 , 
    CalcParm35 , 
    CalcParm36 , 
    CalcParm37 , 
    CalcParm38 , 
    CalcParm39 , 
    CalcParm40 , 
    CalcParm41 , 
    CalcParm42 , 
    CalcParm43 , 
    CalcParm44 , 
    CalcParm45 , 
    CalcParm46 , 
    CalcParm47 , 
    CalcParm48 , 
    CalcParm49 , 
    CalcParm50 , 
    CalcParm51 , 
    CalcParm52 , 
    CalcParm53 , 
    CalcParm54 , 
    CalcParm55 , 
    CalcParm56 , 
    CalcParm57 , 
    CalcParm58 , 
    CalcParm59 , 
    CalcParm60 , 
    CalcParm61 , 
    CalcParm62 , 
    CalcParm63 , 
    CalcParm64 , 
//可変パラメータ３２追加 2008.09.03
    CalcParm65 , 
    CalcParm66 , 
    CalcParm67 , 
    CalcParm68 , 
    CalcParm69 , 
    CalcParm70 , 
    CalcParm71 , 
    CalcParm72 , 
    CalcParm73 , 
    CalcParm74 , 
    CalcParm75 , 
    CalcParm76 , 
    CalcParm77 , 
    CalcParm78 , 
    CalcParm79 , 
    CalcParm80 , 
    CalcParm81 , 
    CalcParm82 , 
    CalcParm83 , 
    CalcParm84 , 
    CalcParm85 , 
    CalcParm86 , 
    CalcParm87 , 
    CalcParm88 , 
    CalcParm89 , 
    CalcParm90 , 
    CalcParm91 , 
    CalcParm92 , 
    CalcParm93 , 
    CalcParm94 , 
    CalcParm95 , 
    CalcParm96   

};

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件補間計算                                                    */
/*  [引数]                                                                  */
/*      PWIPCB      pIP     溶接条件補間構造体                              */
/*      pusint      pBuff   補間データ格納アドレス                          */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
static  void    WeldCondHokan( PWIPCB pIP , pusint pBuff )
{// @-R040301RTW
int i;

    pIP->Wf = xx_Hokan( pIP->WFs , pIP->WFe , pIP->N , pIP->K );    // ＷＦ補間
    pIP->Vp = xx_Hokan( pIP->Vps , pIP->Vpe , pIP->N , pIP->K );    // Ｖｐ補間
    pIP->Vs = xx_Hokan( pIP->Vss , pIP->Vse , pIP->N , pIP->K );    // Ｖｓ補間
    //<><><>電流補間 2008.12.02<><><>
    pIP->Cr = xx_Hokan( pIP->CRs , pIP->CRe , pIP->N , pIP->K );    // ＣＲ補間
    //<><><><><><><><><><><><><><><>

    pBuff[ 0 ] = CalcParm1( GetPulseMode( ) );
    pBuff[ 1 ] = CalcParm2( pIP->Wf , pIP->Vp );
    pBuff[ 2 ] = CalcParm3( pIP->Wf , pIP->Vs );
#if 0
    for( i=3 ; i < 64 ; ++i )
    {
        pBuff[ i ] = pCallTable[ i ].pProc( pIP->Wf );
    }
#endif
    for( i=3 ; i < CALPARM_1LEN ; ++i )
    {
        pBuff[ i ] = pCallTable[ i ].pProc( pIP->Wf );
        //test_Buff[i] = pCallTable[ i ].pProc( pIP->Wf ); //2008.09.16 test
    }

    //*** 可変パラメータ３２追加 2008.09.03 ***
    for( i = CALPARM_1LEN ; CALPARM_CNT > i ; ++i )
    {
        pBuff[ i ] = pCallTable[ i ].pProc( pIP->Wf );
        //test_Buff[i] = pCallTable[ i ].pProc( pIP->Wf ); //2008.09.16 test
    }

    //<><><>電流補間 2008.12.02<><><>
    //pBuff[ 89 ] = CalcParm90( pIP->Cr );
    pBuff[ 89 ] = CalcParm90_1( pIP->Cr , pIP->Wf); //2008.12.24
    //<><><><><><><><><><><><><><><>
    
    //**** test 2009.02.28 ******
    if (pBuff[65 - 1] == 0)
    {
        //LED4 = ON;
    } else {
        //LED4 = OFF;
    }



    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ速度補間計算                                                  */
/*  [引数]                                                                  */
/*      PSIPCB      pIP     ワイヤ速度補間構造体                            */
/*      pusint      pBuff   補間データ格納アドレス                          */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*      2004.10.15  R040701RTW-TAWERS       西川    NY20041015              */
/*--------------------------------------------------------------------------*/
static  void    WeldSpeedHokan( PSIPCB pIP , pusint pBuff )
{// @-R040301RTW
float   rc;

    pIP->Wf = xx_Hokan( pIP->WFs , pIP->WFe , pIP->N , pIP->K );    // ＷＦ補間
    rc = ConvRpm( pIP->Wf );

    pBuff[ 0 ] = (sint)rc;
    pBuff[ 1 ] = pIP->WFe_rpm;
    pBuff[ 2 ] = pIP->WFe_Siji;     // NY20041015
    pBuff[ 3 ] = 
    pBuff[ 4 ] = 
    pBuff[ 5 ] = 0;
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      補間クラスの初期化(溶接制御)                                        */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
void    wipInit( void )
{
    xmemset( &_wipcb , 0 , sizeof( WIPCB ) );
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      補間クラスの初期化(サーボ速度)                                      */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
void    sipInit( void )
{
    xmemset( &_sipcb , 0 , sizeof( SIPCB ) );
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      補間クラスの再計算処理（溶接制御）                                  */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.15  R040301RTW-TAWERS       西川                            */
/*--------------------------------------------------------------------------*/
void    wipReCalc( void )
{
PWIPCB  pIP = &_wipcb;

    pIP->WFe_Target = 
    pIP->Ve_Target  = 0;
    //<><><>電流補間 2008.12.02<><><>
    pIP->CRe_Target = 0;
    //<><><><><><><><><><><><><><><>
    return;
}
void    wipReset( void )
{
PWIPCB  pIP = &_wipcb;

    pIP->Wf         =
    pIP->Vp         =
    pIP->Vs         = 0;

    //<><><>電流補間 2008.12.02<><><>
    pIP->Cr         = 0;
    //<><><><><><><><><><><><><><><>
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      補間クラスの再計算処理（サーボ速度）                                */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.15  R040301RTW-TAWERS       西川                            */
/*--------------------------------------------------------------------------*/
void    sipReCalc( void )
{
PSIPCB  pIP = &_sipcb;

    pIP->WFe_Target = 0;
    return;
}
void    sipReset( void )
{
PSIPCB  pIP = &_sipcb;

    pIP->Wf         = 0;
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件補間                                                        */
/*  [引数]                                                                  */
/*      sint    WF      ワイヤ速度(0.001m/min)                              */
/*      usint   Volt    電圧(0.1V)                                          */
/*      pusint  pBuff   溶接条件補間データ格納アドレス                      */
/*  [戻り値]                                                                */
/*      int     ０：補間した、１：補間していない                            */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
int     wipIP( sint WF , sint Volt , pusint pBuff )
{// @-R040301RTW
PWIPCB  pIP = &_wipcb;

    //if (gss_En_a != gss_En_a_bkup)
    //{
    //    gss_En_a_bkup = gss_En_a;
    //	WeldCondHokan( pIP , pBuff );
    //    return( 0 );
    //if (gtt_Ctrl_flag.Hpi_control == true) //2008.11.29 可変パラメータに関するデータが変化した場合ＨＰＩ転送を行う。

    //if (gtt_Ctrl_flag.Hpi_control == true && (guc_Sequence_mode > SLOW_DOWN && guc_Sequence_mode < BURN_BACK)) //2008.12.04可変パラメータに関するデータが変化した場合ＨＰＩ転送を行う。
    //{
    //    gtt_Ctrl_flag.Hpi_control = false;
    //  	WeldCondHokan( pIP , pBuff );
    //    return( 0 );
    //} else {
	if(  ( pIP->WFe_Target != WF )
           ||( pIP->Ve_Target != Volt ) )       // 目標値が変わったか？
        {
            w_Init( WF , Volt );               // 初期計算
            
            pIP->K = 1;
            dbgWIP( );
        }
        else
        {
            if( pIP->K >= pIP->N )              // 補間終了？
            {
                if (gtt_Ctrl_flag.Dc_control_timer_end == ON && gtt_Ctrl_flag.Dc_control_timer_one_shot == OFF)
                {
                    WeldCondHokan( pIP , pBuff );
                    gtt_Ctrl_flag.Dc_control_timer_one_shot = ON;
                    return(0);
                }
                //***** 2008.12.08　電流目標値が変わっていない状態で溶接中変化があった場合のみ転送 *****
                if (gtt_Ctrl_flag.Hpi_control == true) //可変パラメータに関するデータが変化した場合ＨＰＩ転送を行う。 2008.12.08場所変更
                {
                    gtt_Ctrl_flag.Hpi_control = false;
                    WeldCondHokan( pIP , pBuff );
                    return( 0 );
                }
                //**************************************************************************************
                return( 1 );                    // 補間していない
            }
             ++pIP->K;
        }
        WeldCondHokan( pIP , pBuff );
        return( 0 );
    //}

#if 0

    if(  ( pIP->WFe_Target != WF )
       ||( pIP->Ve_Target != Volt ) )       // 目標値が変わったか？
    {
        w_Init( WF , Volt );               // 初期計算
        pIP->K = 1;
        dbgWIP( );
    }
    else
    {
        if( pIP->K >= pIP->N )              // 補間終了？
            return( 1 );                    // 補間していない
        ++pIP->K;
    }
    WeldCondHokan( pIP , pBuff );
    return( 0 );
#endif

}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件補間                                                        */
/*  [引数]                                                                  */
/*      sint    WF      ワイヤ速度(0.001m/min)                              */
/*      usint   Volt    電圧(0.1V)                                          */
/*      pusint  pBuff   溶接条件補間データ格納アドレス                      */
/*  [戻り値]                                                                */
/*      int     ０：補間した、１：補間していない                            */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      電流補間のためｗ＿Ｉｎｉｔ２に変更 2008.12.02 H.Ihara               */
/*--------------------------------------------------------------------------*/
int     wipIP2( sint WF , sint CR , sint Volt , pusint pBuff )
{// @-R040301RTW
PWIPCB  pIP = &_wipcb;

    //if (gtt_Ctrl_flag.Hpi_control == true) //2008.11.29 可変パラメータに関するデータが変化した場合ＨＰＩ転送を行う。
    //{
    //    gtt_Ctrl_flag.Hpi_control = false;
    //	WeldCondHokan( pIP , pBuff );
    //    return( 0 );
    //} else { 2008.12.10 変更のため上記削除
	if(  ( pIP->WFe_Target != WF )
           ||( pIP->Ve_Target != Volt ) )       // 目標値が変わったか？
        {
            //w_Init( WF , Volt );               // 初期計算
            //<><><>電流補間 2008.12.02<><><>
            w_Init2( WF , CR ,Volt );               // 初期計算
            //<><><><><><><><><><><><><><><>
            pIP->K = 1;
            dbgWIP( );
        }
        else
        {
            if( pIP->K >= pIP->N )              // 補間終了？
            {
                if (gtt_Ctrl_flag.Dc_control_timer_end == ON && gtt_Ctrl_flag.Dc_control_timer_one_shot == OFF)
                {
                    WeldCondHokan( pIP , pBuff );
                    gtt_Ctrl_flag.Dc_control_timer_one_shot = ON;
                    return(0);
                }
                //***** 2008.12.08　電流目標値が変わっていない状態で溶接中変化があった場合のみ転送 2008.12.10移植*****
                if (gtt_Ctrl_flag.Hpi_control == true) //可変パラメータに関するデータが変化した場合ＨＰＩ転送を行う。 2008.12.08場所変更
                {
                    gtt_Ctrl_flag.Hpi_control = false;
                    WeldCondHokan( pIP , pBuff );
                    return( 0 );
                }
                //**************************************************************************************
                return( 1 );                    // 補間していない
            }
             ++pIP->K;
        }
        WeldCondHokan( pIP , pBuff );
        return( 0 );
    //}
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ速度補間                                                      */
/*  [引数]                                                                  */
/*      sint    WF      ワイヤ速度(0.001m/min)                              */
/*      pusint  pBuff   溶接条件補間データ格納アドレス                      */
/*  [戻り値]                                                                */
/*      int     ０：補間した、１：補間していない                            */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.14  R040301RTW-TAWERS       細井                            */
/*--------------------------------------------------------------------------*/
int sipIP( sint WF , pusint pBuff )
{// @-R040301RTW
PSIPCB  pIP = &_sipcb;

    if( pIP->WFe_Target != WF )             // 目標値が変わったか？
    {
        s_Init( WF );                      // 初期計算
        pIP->K = 1;
        dbgSIP( );
    }
    else
    {
        if( pIP->K >= pIP->N )              // 補間終了？
            return( 1 );                    // 補間していない
        ++pIP->K;
    }
    WeldSpeedHokan( pIP , pBuff );
    return( 0 );
}

/* ================================================================
        補間テストルーチン
   =============================================================== */
// -----------------------------------------------------
static  void    DBG( char c1 , char c2 , float F )
{
lint    D = F * 1000;

    //dbgWrite( c1 , c2 , ( D >>16 )&0xffff, D & 0xffff );
}
// -----------------------------------------------------
void    dbgWIP( void )
{
PWIPCB      pDat = &_wipcb;

         DBG( 'W','I', pDat->WFs );
         DBG( 'W','0', pDat->Vps );
         DBG( 'W','1', pDat->Vss );
         DBG( 'W','2', pDat->WFe );
         DBG( 'W','3', pDat->Ve  );
         DBG( 'W','4', pDat->Vpe );
         DBG( 'W','5', pDat->Vse );
         DBG( 'W','6', pDat->T   );
    //dbgWrite( 'W','7', pDat->N , 0 );
}
// -----------------------------------------------------
void    dbgSIP( void )
{
PSIPCB      pDat = &_sipcb;

         DBG( 'S','I', pDat->WFs );
         DBG( 'S','0', pDat->WFe );
         DBG( 'S','1', pDat->T   );
    //dbgWrite( 'S','2', pDat->N , 0 );
}
/* -----------------------------------------------------
static  void    nyCalParmInit( int No )
{
    _union.Nrm.CalParm[ No ].a   = 0.0;
    _union.Nrm.CalParm[ No ].b   = 1.0;
    _union.Nrm.CalParm[ No ].c   = 0.0;
    _union.Nrm.CalParm[ No ].min = -99990.0;
    _union.Nrm.CalParm[ No ].max =  99999.0;
}
 -----------------------------------------------------
static  void    NY( float f )
{                                           // 実行結果 
    dbgMon( 'N',':' , (int)f );             // 0000
    dbgMon( '1',':' , (usint)((int)f) );    // 0000
    dbgMon( '2',':' , (sint)f );            // FF9C
    dbgMon( '3',':' , (sint)((int)f) );     // FF9C
}
 -----------------------------------------------------
void    nyTest( char C )
{
    switch( C )
    {
        case '0':
            wipInit( );
            pWT = (PWELDTABLE)0x001A0000;
            nyCalParmInit( 1 );
            nyCalParmInit( 2 );
            nyCalParmInit( 3 );
            nyCalParmInit( 4 );
            nyCalParmInit( 5 );
            wipIP( 10000 , 100 , wcondBuff );
            break;
        case '1':
            wipIP( 10000 , 100 , wcondBuff );
            break;
        case '2':
            NY( -100.0 );
            break;
        default:
            break;
    }
}
 ----------------------------------------------------------------- */
/* end */

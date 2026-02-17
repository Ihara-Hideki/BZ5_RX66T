/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ＩＦタスク                                                          */
/*  [最終更新日]                                                            */
/*      2004. 5.27  R040301RTW-TAWERS       西川                            */
/*      2004. 7.13  R040301RTW-TAWERS       田中    <ALT1>                  */
/*      2004. 9.22  R040701RTW-TAWERS       田中                            */
/*      2004. 9.28  R040701RTW-TAWERS       田中    <ALT1-HD>               */
/*      2004.10.13  R040701RTW-TAWERS       西田    [ｵｰﾄｴｸｽﾃﾝｼｮﾝ]           */
/*      2005. 1. 7  R0501XXRK1-その他       西川                            */
/*      2005.06.02  R050507RK1-TW_DIP_PULSE 津田                            */
/*      2005.09.27  R050902RK1-溶接条件設定拡張     津田                    */
/*--------------------------------------------------------------------------*/
//#include    "typedef.h"
//#include    "xapidefs.h"
//#include    "xdefine.h"
//#include    "xobjdef.h"
//#include    "apkernel.h"

//#include    "ifc.h"
//#include    "ifcdef.h"
//#include    "regset.h"
//#include    "adrm32r.h"
//#include    "dpr.h"
//#include    "ifdata.h"
//#include    "inout.h"

//#include    "dbg.h"
//#include    "SampleFile.h"

#include "custom.h"


// -----------------------------
//#define     TBLCNT      2
//#define     TBLCNT      40      // 2004. 9.29     // @-R050204RK1
// -----------------------------
int     initFPGA( void );
int     initDSP( void );
extern  void    ifTASK_Proc( void );
void    download( void );
void    samplingStart( int Mode );
void    asnsInit( void );
// @-R050902RK1
PWELDTABLE  getWeldTablePtr( void );
int     isNewWeldTable( void );
// -----------------------------
//extern  XEVENT      ifEvent; 2005.12.27 del
//extern  DEF_THREAD  tim_DefThread; 2005.12.27 del

//extern  XTHREAD     timThread; 2005.12.27 del
extern  int         _ACC;
extern  int         DC_PMODE;
extern  WELDCODE    DC_WELDCODE;
//extern  int         DC_DELAY;//2004.10.12
//extern  int         DC_ACC[ 5 ];
//extern  int         DC_SLOW;
extern  sint        G_Bunsi;
extern  sint        G_Bunbo;
extern  float       DC_RPM;
extern  sint        WeldMonOffset_A;
extern  sint        WeldMonOffset_V;
// @-R040701RTW<ALT1-HD>
//extern  pusint      pFIFO_AMP;     2005.12.27 del
//extern  pusint      pFIFO_VOLT;       ""
//extern  pusint      pFIFO_CTL;        ""
//extern  pusint      pDATSAMPLINGTIME; ""
//extern  unsigned char * pFPGA_PROG;   ""
//extern  pusint      pFPGA_CTRL;       ""
// -----------------------------
#define     IFERR_FPGAINIT      0x0001
#define     IFERR_DSPINIT       0x0002
// -----------------------------
static  const   char    FPGAVer[ ]      = { "1.00" };
static  const   char    WELDDATVer[ ]   = { "0.10" };
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ＤＳＰ送信パラメータ                                                */
/*--------------------------------------------------------------------------*/
static  usint   const   Data_IFREADY[ ] =
{
    0x0000
};
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      初期化完了送信データ                                                */
/*--------------------------------------------------------------------------*/
static  usint   const   InitEndData[ ] =
{
    0x0000
};
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ速度計算用定数                                                */
/*--------------------------------------------------------------------------*/
//                                         減速比                ロール径
//static  float   const   DC_RPM      = { (-80.0 / 3.0) * 4.0 / (    0.04   * 3.141592654 ) };
static  float   const   DC_ROLL  = 0.04;
static  float   const   DC_PAI   = 3.141592654;
static  float   const   DC_4TEI  = 4.0;
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件テーブルの有効／無効判定関数                                */
/*  [引数]                                                                  */
/*      PWELDCODE   pTbl            溶接条件テーブル                        */
/*  [戻り値]                                                                */
/*      lint        0:無効          1:有効                                  */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2005.06.02  R050507RK1-TW_DIP_PULSE 津田                            */
/*--------------------------------------------------------------------------*/
static  lint    chkWeldCodeEnb( PWELDCODE pTbl )
{
    if( ( pTbl->pulseMode & 0x01 ) == 0 )
        return( 0 );
    if( ( pTbl->pulseMode & ( 0x02 | 0x04 ) ) == 0 )
        return( 0 );
    return( 1 );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件テーブルの先頭アドレス取得                                  */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.21  R040301RTW-TAWERS       田中                            */
/*      2005.06.02  R050507RK1-TW_DIP_PULSE 津田                            */
/*      2005.09.27  R050902RK1-溶接条件設定拡張     津田                    */
/*--------------------------------------------------------------------------*/
PWELDTABLE      GetWeldTable( void )
{// @-R040301RTW
// @-R050902RK1
//--PWELDTABLE  pTbl = (PWELDTABLE)0x001A0000;
PWELDTABLE  pTbl = getWeldTablePtr( );
PWELDCODE   pCode = &DC_WELDCODE;
int         Cnt;

    for(  Cnt=TBLCNT ; Cnt ; --Cnt , ++pTbl )
    {
// @-R050507RK1
        if( chkWeldCodeEnb( &pTbl->WeldCode ) == 0 )
            continue;
        if( pCode->material != pTbl->WeldCode.material )
            continue;
        if( pCode->method != pTbl->WeldCode.method )
            continue;
        //直流・交流の判別 2008.09.12
        if( (pCode->pulseMode & 0x80) != (pTbl->WeldCode.pulseMode & 0x80))
            continue;
// @-R050507RK1
        if( pCode->pulseType != pTbl->WeldCode.pulseType )
            continue;
        if( pCode->wire != pTbl->WeldCode.wire )
            continue;
        if( pCode->extension != pTbl->WeldCode.extension )
            continue;

              if (gtt_Table_key.Welding_method == 0x02)            // 溶接法
               {
                   LED10 = ON;
               } else {
                   LED10 = OFF;
               }

        return( pTbl );
    }
// @-R050902RK1
//--return( (PWELDTABLE)0x001A0000 );
    guc_No_table = ON;       //2007.2.9
    return( getWeldTablePtr( ) );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      データ更新                                                          */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      溶接条件テーブル(pWT)が更新されたら呼び出すこと                     */
/*  [更新履歴]                                                              */
/*      2004. 6.23  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004. 9. 3  R040701RTW-TAWERS       田中                            */
/*      2004. 9.29  R040701RTW-TAWERS       田中    [半固定2]               */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*--------------------------------------------------------------------------*/
void    DataUpdate( void )
{// @-R040301RTW
PPARMTBL    pTbl;
PNORMAL     pNrm = &_union.Nrm;

    pWT = GetWeldTable( );
// @-R040701RTW<溶接条件ﾃｰﾌﾞﾙ変更>
//  switch( DC_PMODE )
//  {
//      case 2://短絡
//          pTbl = &pWT->ParmTbl_Short;
//          break;
//      case 1://パルス
//      default:
//          pTbl = &pWT->ParmTbl_Pls;
//          break;
//  }
//  _ACC = DC_ACC[ 0 ]  = pTbl->acc1;
//  DC_ACC[ 1 ]  = pTbl->acc2;
//  DC_ACC[ 2 ]  = pTbl->acc3;
//  DC_ACC[ 3 ]  = pTbl->acc4;
//  DC_ACC[ 4 ]  = pTbl->acc5;
//  DC_SLOW      = pTbl->SlowDown;
    _ACC = 0;
    xmemcpy( pNrm->CalParm , pWT->CalParm , sizeof( pWT->CalParm ) );

// @-R040701RTW[半固定2]
//    xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_2LEN );
    xmemcpy( pNrm->WeldParm_Abs , pWT->WeldParm.Parm , sizeof( usint ) * WLDADJST_3LEN ); //2007.2.13変更
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      通常処理の初期化                                                    */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.31  R040301RTW-TAWERS       田中                            */
/*      2004. 9.22  R040701RTW-TAWERS       田中    <ALT1>                  */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*      2005.09.27  R050902RK1-溶接条件設定拡張     津田                    */
/*--------------------------------------------------------------------------*/
void    NormalInit( void )
{// @-R040301RTW

    xmemset( &_union , 0 , sizeof( UNIONDATA ) );
    wipInit( );
    sipInit( );
    DC_PMODE = 2;
//  DC_DELAY = 0;   //R040701RTW<溶接条件ﾃｰﾌﾞﾙ変更>
    //SAMPLING_M = 2; 2005.12.27 del
    //SAMPLING_N = 10; 2005.12.27 del
    //SAMPLING_L = 1000 / ( SAMPLING_M * 50 ); 2005.12.27 del
    //Adjust_A = 0;           // @-R040701RTW <ALT1> 2019.04.02 del ihara
    //Adjust_V = 0;                                  2019.04.02 del ihara
    {//     ＩＦ標準値セット
// @-R050902RK1
//--PWELDTABLE   pTbl = (PWELDTABLE)0x001A0000;
PWELDTABLE   pTbl = getWeldTablePtr( );
        DC_WELDCODE = pTbl->WeldCode;
        DataUpdate( );
    }
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      DC_RPMのセット                                                      */
/*  [引数]                                                                  */
/*      psint   pBunsi      ギヤ比 分子                                     */
/*      psint   pBunbo             分母                                     */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.24  R040301RTW-TAWERS       西川                            */
/*--------------------------------------------------------------------------*/
void    Set_DCRPM( psint pBunsi , psint pBunbo )
{
int     Bunsi , Bunbo;
    if( *pBunbo == 0 )
    {
        Bunsi = -80;
        Bunbo =   3;
    }
    else
    {
        Bunsi = *pBunsi;
        Bunbo = *pBunbo;
    }
    G_Bunsi = Bunsi;
    G_Bunbo = Bunbo;
    DC_RPM = ( (float)Bunsi / (float)Bunbo ) * DC_4TEI / ( DC_ROLL * DC_PAI );
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      バージョン情報をセット                                              */
/*  [引数]                                                                  */
/*      pusint  pBuff   バージョン格納ポインタ                              */
/*      puchar  pVer    バージョンポインタ                                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 7.13  R040301RTW-TAWERS       田中    <ALT1>                  */
/*--------------------------------------------------------------------------*/
static  void    SetVersion( pusint pBuff , puchar pVer )
{// @-R040301RTW
    pBuff[ 0 ] = pVer[ 1 ] * 256 + pVer[ 0 ];
    pBuff[ 1 ] = pVer[ 3 ] * 256 + pVer[ 2 ];
}
#if false
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      エラー情報をセット                                                  */
/*  [引数]                                                                  */
/*      int     Init        初期化エラー情報                                */
/*      usint   DSP         DSPから受信したエラー情報                       */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 7.13  R040301RTW-TAWERS       田中    <ALT1>                  */
/*      2005.09.27  R050902RK1-溶接条件設定拡張     津田                    */
/*--------------------------------------------------------------------------*/
static  void    IFREADYmainsend( int Init , usint DSP )
{// @-R040301RTW
usint   Error = 0;

    if( Init & IFERR_FPGAINIT )
        Error = 0x1001;
    else if( Init & IFERR_DSPINIT )
        Error = 0x1002;
    else if( DSP )
        Error = 0x2001;
    wcondBuff[ 0 ] = Error;
    SetVersion( &wcondBuff[ 1 ] ,(puchar)0x00010002 );
    SetVersion( &wcondBuff[ 3 ] ,(puchar)0x00040002 );
    SetVersion( &wcondBuff[ 5 ] ,(puchar)FPGAVer );
// @-R050902RK1
    if( isNewWeldTable( ) )
        SetVersion( &wcondBuff[ 7 ] , (puchar)WLDTBL_VERSION );
    else
        SetVersion( &wcondBuff[ 7 ] ,(puchar)WELDDATVer );
    ifdprWrite( ifdprcmdIFREADY , wcondBuff );
    return;
}
#endif
#if false
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      新/旧ハード切替え                                                   */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 9.28  R040701RTW-TAWERS       田中    <ALT1-HD>               */
/*--------------------------------------------------------------------------*/
static  void    H_W_Check( void )
{// @-R040701RTW
usint   DipSw;
usint   Cmd , Parm;

    while( 1 )
    {
        if( *( (pusint)0x00101000 ) == 0x0139 )
        {
            DipSw = *( (pusint)0x00101002 );
            break;
        }
        while( ifcRead( &ifFIFO , &Cmd , &Parm ) == 0 )
        {
            WDG_Clear( );
            if( Cmd == fifoDOWNLOAD )
            {
                download( );
            }
        }
        XEvWait( &ifEvent , FALSE , 1 );
        XEvClear( &ifEvent );
        WDG_Clear( );
    }
dbgMon( 'I' , 'F' , 0xff00|DipSw );
    WDG_Clear( );
    if( DipSw & 0x01 )
    {// 旧Ｈ／Ｗ
        pFIFO_AMP  = (pusint)0x00140030;
        pFIFO_VOLT = (pusint)0x00140032;
        pFIFO_CTL  = (pusint)0x00140040;
        pDATSAMPLINGTIME = (pusint)0x00140042;
        pFPGA_PROG = (unsigned char * )0x00140001;
        pFPGA_CTRL = (pusint)0x00140100;
    }
    else
    {// 新Ｈ／Ｗ
        pFIFO_AMP  = (pusint)0x00160030;
        pFIFO_VOLT = (pusint)0x00160032;
        pFIFO_CTL  = (pusint)0x00160040;
        pDATSAMPLINGTIME = (pusint)0x00160042;
        pFPGA_PROG = (unsigned char * )0x00160001;
        pFPGA_CTRL = (pusint)0x00160100;
    }
    return;
}
#endif
#if false
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ＩＦタスク：初期化用Ｗａｉｔ関数                                    */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      int     コマンド番号                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6. 1  R040301RTW-TAWERS       西川                            */
/*      2004.10.13  R040701RTW-TAWERS       西田    [ｵｰﾄｴｸｽﾃﾝｼｮﾝ]           */
/*--------------------------------------------------------------------------*/
static  int     initWait( void )
{
usint   Cmd , Parm;

    while( 1 )
    {
        while( ifcRead( &ifFIFO , &Cmd , &Parm ) == 0 )
        {
            WDG_Clear( );
            switch( Cmd )
            {
                case fifoMAINREADY:
                    if( ifErrorStatus )
                    {
                        IFREADYmainsend( ifErrorStatus , 0 );
                    }
                    else
                    {
                        hpiWrite( hpicmdIFREADY , &Parm );
                    }
                    WDG_Clear( );
                    break;
                case fifoDSPREADY:
                    IFREADYmainsend( ifErrorStatus , Parm );
                    WDG_Clear( );
                    break;
                case fifoWLDINIT:
                    hpiWrite( hpicmdOUTWLDINIT , _union.Init.WldParm );
// @-R040701RTW [ｵｰﾄｴｸｽﾃﾝｼｮﾝ]
///                    WDG_Clear( );
///                    snsInit( );
                    WDG_Clear( );
                    WeldMonOffset_A = (sint)_union.Init.WldParm[ 88-1 ];
                    WeldMonOffset_V = (sint)_union.Init.WldParm[ 89-1 ];
                    WDG_Clear( );
                    break;
                case fifoSRVINIT:
                    Set_DCRPM( (psint)&_union.Init.SrvParm[ 98 ] , (psint)&_union.Init.SrvParm[ 99 ] );
                    hpiWrite( hpicmdOUTSRVINIT , _union.Init.SrvParm );
                    WDG_Clear( );
                    break;
                case fifoDSPINITEND:
                    return( Cmd );
                case fifoDOWNLOAD:
                    download( );
                    break;

                default:
                    break;
            }
        }
        XEvWait( &ifEvent , FALSE , 1 );
        XEvClear( &ifEvent );
        WDG_Clear( );
    }
    return( fifoNOP );
}
#endif
#if false
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ＩＦタスクメイン：電源投入～メインレディ受信～初期化完了            */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.27  R040301RTW-TAWERS       西川                            */
/*      2004. 7.13  R040301RTW-TAWERS       田中    <ALT1>                  */
/*--------------------------------------------------------------------------*/
void    ifTASK_Init( void )
{
    ifErrorStatus = 0;
dbgMon( 'I' , 'F' , 0xffff );
    WDG_Clear( );
    H_W_Check( );
    WDG_Clear( );
// @-R0501XXRK1
    //Output( 0 , 0 , 1 );    // P10Xデータの初期化 2006.8.29 ihara
    WDG_Clear( );
    FPGA_DSP( );
    while( 1 )
    {
        switch( initWait( ) )
        {
            case fifoDSPINITEND:
                // DSP-WDG起動
                *(puchar)P11DATA |= 0x08;         // P114 = 1
                ifdprWrite( ifdprcmdINITEND , (pusint)InitEndData );
                return;
            default:
                break;
        }
    }
    return;
}
#endif
#if false
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ＩＦタスクメイン                                                    */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.27  R040301RTW-TAWERS       西川                            */
/*      2004. 9.22  R040701RTW-TAWERS       田中                            */
/*      2005. 4.22  R050309RK1-TAWERSｱｰｸｾﾝｻ   西川                          */
/*      2005.07.15  R050701RK1-TW溶接記録2  津田                            */
/*--------------------------------------------------------------------------*/
void    ifTASK( void )
{
    WDG_Clear( );
dbgMon( 'Z' , 'Z' , 0x0000 );
// @-R040701RTW
//  while( ( Input( ) & 0x0008 ) == 0 )
//  while( Input( ) & 0x0008 )
//  {
//      usint   Cmd , Parm;
//      while( ifcRead( &ifFIFO , &Cmd , &Parm ) == 0 )
//      {
//          WDG_Clear( );
//          if( Cmd == fifoDOWNLOAD )
//          {
//              download( );
//          }
//      }
//      XEvWait( &ifEvent , FALSE , 1 );
//      XEvClear( &ifEvent );
//      WDG_Clear( );
//  }
//dbgMon( 'Z' , 'Z' , 0x8000 );
    WDG_Clear( );
// @-R050701RK1
//--initFile( );
    initFile_PowerOn( );
    WDG_Clear( );
    ifTASK_Init( );
    WDG_Clear( );
    NormalInit( );
    WDG_Clear( );
    asnsInit( );        // @-R050309RK1
    WDG_Clear( );
    samplingStart( 0 ); // NY20041013
    WDG_Clear( );

    XThInit( &timThread , &tim_DefThread );
    XThEnter( &timThread , 0 , 0 , THREAD_ACTIVE );
    WDG_Clear( );

dbgMon( 'Z' , 'Z' , 0xffff );
    ifTASK_Proc( );
    XThStop( );
}
#endif
/* end */

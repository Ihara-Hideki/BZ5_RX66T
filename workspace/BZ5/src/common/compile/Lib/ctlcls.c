/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      制御クラス                                                          */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*      2004. 8.25  R040701RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004.09.14  R040701RTW-TAWERS       西田    微調                    */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*      2005.04.20  R050404RK1-TWﾜｲﾔ送給係数微調    西田                    */
/*--------------------------------------------------------------------------*/
#define		__CTLCLS_PROG
#include	"custom.h"

extern  int         DC_PMODE;
extern  int         DC_SLOW_Offset;     // @-R040701RTW
extern  int         _ACC;
extern  int         DC_ACC_Offset[ 5 ];
//extern  int         DelayTimer;
extern  int         DC_DELAY_Offset;
//extern  int         isEnbDelay;
extern  sint        WireSpd_Offset; // @-R050404RK1
extern  CTLCLS      _ctlcls;
extern  IFCTL       _ifctl;
extern  int			isCRATER;
//-------------------------------
extern  void	DSPSendTimeInit( void );
//extern  sint	GetAmp2Wire( sint Amp , PA2STBL pDat );
extern	int		GetWeldStatus( void );
extern	int		GetMotorStatus( void );
//extern	void	SetWeldStatus( int Sts );
//extern	void	SetMotorStatus( int Sts );
//extern	int		WF2Volt( int WF );


/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件テーブルのパラメータテーブルポインタの取得                  */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*--------------------------------------------------------------------------*/
PPARMTBL    GetPrmTblPrt( void )
{// @-R040701RTW
PPARMTBL     pTbl;

    switch( DC_PMODE )
    {
        case 2://短絡
            pTbl = &pWT->ParmTbl_Short;
            break;
        case 1://パルス
        default:
            pTbl = &pWT->ParmTbl_Pls;
            break;
    }
    return( pTbl );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件テーブルから加速度を取得する                                */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      usint   加速度                                                      */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*--------------------------------------------------------------------------*/
static  usint   Get_WldTblAcc( sint No )
{// @-R040701RTW
PPARMTBL     pTbl;

usint pus_Acc_return;

    pTbl = GetPrmTblPrt( );
    switch( No )
    {
//2007.2.6変更
#if 1
        case 0:     // 送給加速度１（トーチON用）
            if (gss_Acc1 >= 0)
            {
                pus_Acc_return = pTbl->acc1 + (usint)gss_Acc1;
            } else {
                if (pTbl->acc1 >= (usint)(gss_Acc1 * -1))
                {
                    pus_Acc_return = pTbl->acc1 - (usint)(gss_Acc1 * -1);
                } else {
                    pus_Acc_return = 0;
                }
            }
            return(pus_Acc_return);
        case 1:     // 送給加速度２（初回短絡用）
            if (gss_Acc2 >= 0)
            {
                pus_Acc_return = pTbl->acc2 + (usint)gss_Acc2;
            } else {
                if (pTbl->acc2 >= (usint)(gss_Acc2 * -1))
                {
                    pus_Acc_return = pTbl->acc2 - (usint)(gss_Acc2 * -1);
                } else {
                    pus_Acc_return = 0;
                }
            }
            return(pus_Acc_return);
        case 2:     // 送給加速度３（条件変更用）
            if (gss_Acc3 >= 0)
            {
                pus_Acc_return = pTbl->acc3 + (usint)gss_Acc3;
            } else {
                if (pTbl->acc3 >= (usint)(gss_Acc3 * -1))
                {
                    pus_Acc_return = pTbl->acc3 - (usint)(gss_Acc3 * -1);
                } else {
                    pus_Acc_return = 0;
                }
            }
            return(pus_Acc_return);
        case 3:     // 送給加速度４（クレータ用）
            if (gss_Acc4 >= 0)
            {
                pus_Acc_return = pTbl->acc4 + (usint)gss_Acc4;
            } else {
                if (pTbl->acc4 >= (usint)(gss_Acc4 * -1))
                {
                    pus_Acc_return = pTbl->acc4 - (usint)(gss_Acc4 * -1);
                } else {
                    pus_Acc_return = 0;
                }
            }
            return(pus_Acc_return);
        case 4:     // 送給加速度５（トーチOFF用）
            if (gss_Acc5 >= 0)
            {
                pus_Acc_return = pTbl->acc5 + (usint)gss_Acc5;
            } else {
                if (pTbl->acc5 >= (usint)(gss_Acc5 * -1))
                {
                    pus_Acc_return = pTbl->acc5 - (usint)(gss_Acc5 * -1);
                } else {
                    pus_Acc_return = 0;
                }
            }
            return(pus_Acc_return);
#else
        case 0:     // 送給加速度１（トーチON用）
            return( pTbl->acc1 );
        case 1:     // 送給加速度２（初回短絡用）
            return( pTbl->acc2 );
        case 2:     // 送給加速度３（条件変更用）
            return( pTbl->acc3 );
        case 3:     // 送給加速度４（クレータ用）
            return( pTbl->acc4 );
        case 4:     // 送給加速度５（トーチOFF用）
            return( pTbl->acc5 );
#endif
        default:
            break;
   }
    return( 0 );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件テーブルからスローダウン値を取得する                        */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      usint   スローダウン値                                              */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*--------------------------------------------------------------------------*/
static  usint   Get_WldTblSlow( void )
{// @-R040701RTW
    //return( GetPrmTblPrt( )->SlowDown ); 2007.2.5 削除

    //************ スローダウン値の微調整　2007.2.5追加 ******************
    //usint Work;
    short Work;
    Work = GetPrmTblPrt( )->SlowDown;
    
    //if (gss_Adj_slow_down >= 0)
    //{
    //    Work += (usint)gss_Adj_slow_down;
    //} else {
    //    Work -= (usint)(gss_Adj_slow_down * -1);
        Work += gss_Adj_slow_down;
    //}
    //if (Work < 1000)
    //{
    //    Work = 1000;
    //}
    //if (Work < 100)
    //{
    //    Work = 100;
    //}
    //<><><> スローダウンリミッタ 2008.11.26 <><><>
    if (Work > 6000)
    {
        Work = 6000;
    }
    if (Work < 500)
    {
        Work = 500;
    }
    // 100 -> 0.1m/min


    return(Work);
    //*********************************************************************
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件テーブルから 送給ディレイ時間を取得する                     */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      usint   送給ディレイ時間                                            */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*      2004.10.13  R040701RTW-TAWERS       西川    NY20041013              */
/*--------------------------------------------------------------------------*/
static  usint   Get_WldTblDelay( void )
{// @-R040701RTW
int     Time;

    if( isEnbDelay != 1 )  //2006.12.11 test 削除 2007.1.12REPEAT
        return( 0 );       //2006.12.11 test 削除 2007.1.12REPEAT
//2006.2.6変更
#if 1
    if (gss_Delay >= 0)
    {
        Time = GetPrmTblPrt( )->Delay + (usint)gss_Delay;
        Time += DC_DELAY_Offset;
    } else {
        if (GetPrmTblPrt( )->Delay >= (usint)(gss_Delay * -1))
        {
            Time = GetPrmTblPrt( )->Delay - (usint)(gss_Delay * -1);
            Time += DC_DELAY_Offset;
        } else {
            Time = 0;
            Time += DC_DELAY_Offset;
        }
    }

#else

    Time = GetPrmTblPrt( )->Delay;
    Time += DC_DELAY_Offset;
#endif
    if( Time < 0 )
        Time = 0;
    else if( Time > 2000 )
        Time = 2000;
    return( Time );
}
#if 0000
//2007.2.6追加
// ----------------------------------[ 連続アークスタート時間取得 ]------
static  int     getContArcTime( void )      // return＝１ｍＳ
{
PPARMTBL    pTBL = GetPrmTblPrt( );
int         time;

    time = GetPrmTblPrt( )->ContArc;
//    time += ContArc_Offset;
    if( time < 1 )
        time = 1;
    else if( time > 50 )
        time = 50;
    return( time * 100 );   // ０．１秒→１ｍＳ
}
#endif
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      送給加速度の取得関数                                                */
/*  [引数]                                                                  */
/*      int         No          送給加速度番号（０～４）                    */
/*  [戻り値]                                                                */
/*      int         送給加速度                                              */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調                    */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*--------------------------------------------------------------------------*/
static  int    getACCValue( int No )
{// @-R040701RTW
int RC;
int acc;

// @-R040701RTW<溶接条件ﾃｰﾌﾞﾙ変更>
    acc = Get_WldTblAcc( No );
//  RC = DC_ACC[ No ] + DC_ACC_Offset[ No ];
    RC = acc + DC_ACC_Offset[ No ];             // 加速度(0.1)＋オフセット(0.1)
    if( RC < 1 )            // リミット値 0.1～99.9
        RC = 1;
    else if( RC > 999 )
        RC = 999;
    return( RC );
}

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      スローダウン速度の取得関数                                          */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      int         スローダウン速度                                        */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調                    */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*--------------------------------------------------------------------------*/
static  int    getSLOWValue( void )
{// @-R040701RTW
int RC;
int slow;

// @-R040701RTW<溶接条件ﾃｰﾌﾞﾙ変更>
    slow = Get_WldTblSlow( );
//  RC = DC_SLOW + DC_SLOW_Offset;
    RC = slow + DC_SLOW_Offset;       // スローダウン速度(0.001m/min)＋オフセット(0.001m/min)
    if( RC < 500 )            // リミット値 0.500～6.000
        RC = 500;
    else if( RC > 6000 )
        RC = 6000;
    return( RC );
}

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      制御クラスの初期化                                                  */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
void    ctlclsInit( void )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;

    xmemset( pCTL , 0 , sizeof(CTLCLS) );
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接中の加速度セット                                                */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調                    */
/*--------------------------------------------------------------------------*/
static  void    Set_WeldAcc( void )
{// @-R040701RTW
    if( isCRATER == 0 )
        _ACC = getACCValue( 2 );
    else
        _ACC = getACCValue( 3 );
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ送給速度 に 係数演算する                                      */
/*  [引数]                                                                  */
/*      sint        WF          係数演算する前のWF(0.001m/min)              */
/*  [戻り値]                                                                */
/*      sint        係数演算後のWF                                          */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2005.04.20  R050404RK1-TWﾜｲﾔ送給係数微調    西田                    */
/*--------------------------------------------------------------------------*/
static  sint    GetWireSpd( sint WF )
{// @-R050404RK1
lint rc;

    rc = ((100 + WireSpd_Offset) * WF) / 100;
    if( rc < 1 )   // 0.250
        rc = 1;
    else if( rc > 23000 ) // 23.000
        rc = 23000;
    return( rc );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件セット                                                      */
/*  [引数]                                                                  */
/*      usint       Amp         指令電流                                    */
/*      usint       Volt        指令電圧                                    */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004.10. 4  R040701RTW-TAWERS       田中    <補正>                  */
/*      2005.04.20  R050404RK1-TWﾜｲﾔ送給係数微調    西田                    */
/*--------------------------------------------------------------------------*/
void    ctlclsWeldCondSet( sint Amp , sint Volt )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;
PIFCTL      pIFC = &_ifctl;
PA2STBL     pTBL;
sint        amp , volt;

#if 0
PENTBL      pENTBL; //2008.09.19



float a;
float b;
signed short pss_En_duty_adjustment;
#endif



//pENTBL = pWT->pTEST1;

// @-R040701RTW<補正>
    //amp  = Amp  + Adjust_A;  //電流の補整値 2019.04.02 del ihara
    //volt = Volt + Adjust_V;  //電圧の補整値 2019.04.02 del ihara
    if( amp < 0 )
        amp = 0;
    else if( amp > 1000 )
        amp = 1000;
    if( volt < 0 )
        volt = 0;
    else if( volt > 1000 )
        volt = 1000;
//=============================

gss_Pre_current = amp; //2009.12.29 交流周波数制限を行うためリアルタイムに電流指令値を取得する。


    DelayTimer = 0;
    switch( DC_PMODE )
    {
        case 2://短絡
            pTBL = &pWT->A2S_Short;
            //pENTBL = pWT->pENTBL_Short;
            break;
        case 1://パルス
        default:
            pTBL = &pWT->A2S_Pulse;
            //pENTBL = pWT->pENTBL_Pulse;
            break;
    }
// @-R040701RTW<補正>
    pCTL->WFe_Sirei_W = pCTL->WFe_Sirei_S = GetAmp2Wire( amp , pTBL );
    pCTL->V_Sirei = volt;

    //<><><>電流補間 2008.12.02<><><>
    pCTL->CRe_Sirei_W = amp;
    //<><><><><><><><><><><><><><><>

// @-R050404RK1
    pCTL->WFe_Sirei_S = GetWireSpd( pCTL->WFe_Sirei_S );
    if( GetWeldStatus( ) == 2 )                     //本溶接中
    {
        Set_WeldAcc( );                             //加速度セット      // @-R040701RTW
        pCTL->WFe_Target_W = pCTL->WFe_Sirei_W;     //指令値を目標値にセット
        pCTL->V_Target = pCTL->V_Sirei;
        pCTL->WFe_Target_S = pCTL->WFe_Sirei_S;
        //<><><>電流補間 2008.12.02<><><>
        pCTL->CRe_Target_W = pCTL->CRe_Sirei_W;     //指令値を目標値にセット
        //<><><><><><><><><><><><><><><>
        DSPSendTimeInit( );                         //タイマ再設定
    }
    else
    {
        if( GetMotorStatus( ) == 2 )                //送給中
        {
            Set_WeldAcc( );                         //加速度セット      // @-R040701RTW
            pCTL->WFe_Target_S = pCTL->WFe_Sirei_S; //指令値を目標値にセット
            DSPSendTimeInit( );                     //タイマ再設定
        }
    }

    //***** ＥＮ比率デフォルトの算出 2008.09.19 *****
#if 0
    Fq_test = pCTL->WFe_Sirei_W;
    if (pCTL->WFe_Sirei_W > pENTBL->ENdef_Calc_Wf2) // Wf > JUDG2
    //if (pCTL->WFe_Sirei_W > pENTBL->ENdef_Calc_Wf2 || gtt_Ctrl_flag.AC_control == false) // Wf > JUDG2
    {
        gss_En_def = 0;
        gss_En_a = 0;
    } else {
        if ((pCTL->WFe_Sirei_W > pENTBL->ENdef_Calc_Wf1) && (pCTL->WFe_Sirei_W <= pENTBL->ENdef_Calc_Wf2)) // JUDG1 < Wf <= JUDG2
        {
            gss_En_def = (sint)(pENTBL->ENdef_Calc_Wf2_a * (float)pCTL->WFe_Sirei_W + pENTBL->ENdef_Calc_Wf2_b);
        }
        if (pCTL->WFe_Sirei_W <= pENTBL->ENdef_Calc_Wf1) //JUDG >= Wf
        {
            gss_En_def = (sint)(pENTBL->ENdef_Calc_Wf1_a * (float)pCTL->WFe_Sirei_W + pENTBL->ENdef_Calc_Wf1_b);
        }
        
        if (gss_En_def >= EN_MAX)
        {
            gss_En_def = EN_MAX;
        }
        if (gss_En_def < EN_MIN)
        {
            gss_En_def = 0;
        }
    }

    if (pENTBL->ENdef_Calc_Wf2 >= pCTL->WFe_Sirei_W)
    //if (pENTBL->ENdef_Calc_Wf2 >= pCTL->WFe_Sirei_W && gtt_Ctrl_flag.AC_control == true)
    {
        pss_En_duty_adjustment = gss_Select_dital[P_EN_DUTY];
        if (pss_En_duty_adjustment >= pENTBL->EN1_Max_Limit)
        {
            pss_En_duty_adjustment = pENTBL->EN1_Max_Limit;
        }
        if (pss_En_duty_adjustment <= pENTBL->EN1_Min_Limit)
        {
            pss_En_duty_adjustment = pENTBL->EN1_Min_Limit;
        }
    } else {
        pss_En_duty_adjustment = 0;
    }
    gss_En_a = (sint)(gss_En_def + pss_En_duty_adjustment);
    if (gss_En_a >= EN_MAX)
    {
        gss_En_a = EN_MAX;
    }
    if (gss_En_a < EN_MIN)
    {
        gss_En_a = 0;
    }

    gtt_En.f_AC_Frq_ENa1_A = pENTBL->AC_Frq_ENa1_A;
    gtt_En.f_AC_Frq_ENa1_B = pENTBL->AC_Frq_ENa1_B;
    gtt_En.f_AC_Frq_ENa1_C = pENTBL->AC_Frq_ENa1_C;
    gtt_En.f_AC_Frq_ENa2_A = pENTBL->AC_Frq_ENa2_A;
    gtt_En.f_AC_Frq_ENa2_B = pENTBL->AC_Frq_ENa2_B;
    gtt_En.f_AC_Frq_ENa2_C = pENTBL->AC_Frq_ENa2_C;
#endif
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ速度セット                                                    */
/*  [引数]                                                                  */
/*      sint        Speed       速度(0.01)                                  */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
void    ctlclsSrvSet( sint Speed )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;
PIFCTL      pIFC = &_ifctl;

    DelayTimer = 0;
    pCTL->WFe_Sirei_S = Speed * 10;
    if( GetWeldStatus( ) == 2 )                     //本溶接中
    {
        pCTL->WFe_Target_S = pCTL->WFe_Sirei_S;     //目標値セット
        DSPSendTimeInit( );                         //タイマ再設定
    }
    else
    {
        if( GetMotorStatus( ) == 2 )                //送給中
        {
            pCTL->WFe_Target_S = pCTL->WFe_Sirei_S; //目標値セット
            DSPSendTimeInit( );                     //タイマ再設定
        }
    }
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件スタート                                                    */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004.09.14  R040701RTW-TAWERS       西田    微調                    */
/*--------------------------------------------------------------------------*/
void    ctlclsWeldStart( void )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;
// @-R040701RTW
//usint       WF = DC_SLOW;   //スローダウン値ｾｯﾄ
usint       WF = (usint)getSLOWValue( );   //スローダウン値ｾｯﾄ
usint       Flag = 0;

//@-R040701RTW
    isCRATER = 0;                                   //CRATER実行中フラグ０クリア
    _ACC = getACCValue( 0 );                        //スローダウン中の加速度セット

#if 0 //2009.02.20
    if( pCTL->WFe_Sirei_W < WF )                    //本溶接速度＜スローダウン値
    {
        pCTL->WFe_Target_W  = pCTL->WFe_Sirei_W;    //目標値を本溶接速度にする
        Flag = 1;
    }
    if( pCTL->WFe_Sirei_S < WF )                    //本溶接速度＜スローダウン値
    {
        pCTL->WFe_Target_S  = pCTL->WFe_Sirei_S;    //目標値を本溶接速度にする
        Flag = 1;
    }
    if( Flag == 0 )
    {
        pCTL->WFe_Target_W = pCTL->WFe_Target_S = WF;
    }
#endif
    pCTL->WFe_Target_W  = pCTL->WFe_Sirei_W;    //目標値を本溶接速度にする 2009.02.20
    pCTL->V_Target = WF2Volt( WF );
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ速度スタート                                                  */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調                    */
/*--------------------------------------------------------------------------*/
void    ctlclsSrvStart( void )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;

    _ACC = getACCValue( 2 );     //本溶接中の加速度をセット  //  @-R040701RTW
    pCTL->WFe_Target_S = pCTL->WFe_Sirei_S;
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ストップ処理                                                        */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調                    */
/*--------------------------------------------------------------------------*/
void    ctlclsStop( void )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;
int         WF = 0;

    _ACC = getACCValue( 4 );             //加速度セット      // @-R040701RTW
    pCTL->WFe_Target_W = WF;
    pCTL->WFe_Target_S = WF;
    pCTL->V_Target = WF2Volt( WF );

    //<><><>電流補間 2008.12.16<><><>
    pCTL->CRe_Target_W = 0;
    //<><><><><><><><><><><><><><><>


    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      Delay                                                               */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      サーボのみ：スローダウンから本溶接の間可変に時間をあける            */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6.22  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
void    ctlclsDelayTimer( void )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;

    if( ( GetWeldStatus( ) == 2 ) && ( GetMotorStatus( ) == 2 ) )//本溶接中
    {
        pCTL->WFe_Target_S = pCTL->WFe_Sirei_S;
        DSPSendTimeInit( );     //タイマ再設定
    }
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      初期短絡                                                            */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*      2004. 8.27  R040701RTW-TAWERS       田中                            */
/*      2004.09.15  R040701RTW-TAWERS       西田    微調                    */
/*      2004.10.12  R040701RTW-TAWERS       田中    <溶接条件ﾃｰﾌﾞﾙ変更>     */
/*--------------------------------------------------------------------------*/
void    ctlclsElectrode( void )
{// @-R040301RTW
PCTLCLS     pCTL = &_ctlcls;
int         Dtime;

    if( ( GetWeldStatus( ) == 1 ) && ( GetMotorStatus( ) == 1 ) )//スローダウン中
    {
        _ACC = getACCValue( 1 );    //加速度セット  // @-R040701RTW
        Dtime = Get_WldTblDelay( ); // @-R040701RTW<溶接条件ﾃｰﾌﾞﾙ変更> 
        pCTL->WFe_Target_W = pCTL->WFe_Sirei_W;
        pCTL->V_Target = pCTL->V_Sirei;
        
        //<><><>電流補間 2008.12.02<><><>
        pCTL->CRe_Target_W = pCTL->CRe_Sirei_W;     //指令値を目標値にセット
        //<><><><><><><><><><><><><><><>
        
        if( Dtime == 0 )
        {
            pCTL->WFe_Target_S = pCTL->WFe_Sirei_S;
        }
        DSPSendTimeInit( );     //タイマ再設定
        SetWeldStatus( 2 );     //本溶接中へ
        SetMotorStatus( 2 );    //送給中へ
        DelayTimer = Dtime;     // @-R040701RTW<溶接条件ﾃｰﾌﾞﾙ変更> 
        gtt_Ctrl_flag.Motor_acc1 = ON; //2008.11.17モータの加速のみ遅れてセットする。（モータディレイ回避のため
        gss_Motor_acc1 = _ACC;         //2008.11.17
    }
    return;
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      モータ回転方向チェック                                              */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      int     方向同じ＝０、方向違う＝１                                  */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6. 4  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
int    ctlclsDrctCheck( void )
{
#if 0 //2019.04.02 del ihara
/////int     Data = SRVCTL & 0x01;
int     Data = SRVCTL & 0x02;// 2004.10.15

    if( Data )
        Data = 1;
    else
        Data = -1;
    if( Data == _ctlcls.Drct )
        return( 0 );
#endif
    return( 1 );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ方向設定                                                      */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 6. 4  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
void    ctlclsDrctSet( void )
{
#if 0 //2019.04.02 del ihara
int     Data = SRVCTL & 0x02;

    if( Data )
        _ctlcls.Drct = -1;
    else
        _ctlcls.Drct = 1;
    return;
#endif
}

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件：ワイヤ速度目標値取得                                      */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
sint    ctlclsWeldGet( void )
{// @-R040301RTW
PCTLCLS     pCtl = &_ctlcls;

    return( pCtl->WFe_Target_W * (sint)pCtl->Drct );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件：溶接電流目標値取得                                        */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2008.12.02 H.ihara                                                  */
/*--------------------------------------------------------------------------*/
sint    ctlclsWeldGet2( void )
{// @-R040301RTW
PCTLCLS     pCtl = &_ctlcls;

    return( pCtl->CRe_Target_W);
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件：電圧目標値取得                                            */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
sint   ctlclsVoltGet( void )
{// @-R040301RTW
PCTLCLS     pCtl = &_ctlcls;

    return( pCtl->V_Target * pCtl->Drct );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      サーボ速度：ワイヤ速度目標値取得                                    */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      なし                                                                */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004. 5.26  R040301RTW-TAWERS       田中                            */
/*--------------------------------------------------------------------------*/
sint    ctlclsSpeedGet( void )
{// @-R040301RTW
PCTLCLS     pCtl = &_ctlcls;

    return( pCtl->WFe_Target_S * pCtl->Drct );
}
// -------------------------[ 絶対値を返す ]--------------------------------*/
sint    ctlclsSpeedGet_ABS( void )
{
PCTLCLS     pCtl = &_ctlcls;

    return( pCtl->WFe_Target_S );
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      サーボ速度：メインからの指示の取得                                  */
/*  [引数]                                                                  */
/*      なし                                                                */
/*  [戻り値]                                                                */
/*      int     サーボ速度( 0.001 m/min )                                   */
/*  [出力]                                                                  */
/*      なし                                                                */
/*  [特記事項]                                                              */
/*      なし                                                                */
/*  [更新履歴]                                                              */
/*      2004.10.15  R040701RTW-TAWERS       西川    NY20041015              */
/*--------------------------------------------------------------------------*/
int     ctlclsSpeedGet_Siji( void )
{
PCTLCLS     pCTL = &_ctlcls;

    return( pCTL->WFe_Sirei_S );
}


/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件送信                                                        */
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
void    wcndSend( void )
{
sint	WF	= ctlclsWeldGet();
sint	Volt	= ctlclsVoltGet();
    //<><><>電流補間 2008.12.02<><><>
sint	CR	= ctlclsWeldGet2();
    //<><><><><><><><><><><><><><><>

#if 0
    if( wipIP(WF, Volt, wcondBuff ) == 0 )
        hpiWcondWrite( wcondBuff );
#endif

#if 1
    //<><><>電流補間 2008.12.02<><><>
    //if( wipIP(WF, Volt, wcondBuff ) == 0 )
    if( wipIP2(WF, CR , Volt, wcondBuff ) == 0 )
    //<><><><><><><><><><><><><><><>
    {
        //hpiWcondWrite( wcondBuff ); 2019.04.02 del ihara
        return;
    } else {
      if (guc_Pulse_mode_data == 0x83 || guc_Pulse_mode_data == 0x85) //2008.11.14
      {  
        if (guc_Sequence_mode == MAIN_WELD || guc_Sequence_mode == START_WELD || guc_Sequence_mode == INITIAL_WELD)
        {
            if (gtt_Ctrl_flag.DC_control_timer == OFF)
            {
                gtt_Ctrl_flag.DC_control_timer = ON;
                //gtt_Ctrl_counter.us_DC_control_timer = gss_Select_dital[P_DC_CONTROL_TIME];
                gtt_Ctrl_counter.us_DC_control_timer = gtt_En.ss_AC_DCstart_Tim_Def + gtt_Ditail_work.us_DC_control_timer; //2008.10.14
            } else if (gtt_Ctrl_counter.us_DC_control_timer <= 0) {
                gtt_Ctrl_flag.AC_control = true;
                gtt_Ctrl_flag.Dc_control_timer_end = ON;  //2008.10.08
            }
        }
      }
    }
#endif
}
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ワイヤ速度送信                                                      */
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
void    sspdSend( void )
{

#if 1 //2008.09.22削除
    if( sipIP( ctlclsSpeedGet( ) , wspdBuff ) == 0 )
        //hpiStsWrite( hpistsOUTSRVSPD , wspdBuff ); 2019.04.02 del ihara
    return;
#endif

    //***** ＥＮ比率０％（交流時の直流制御区間）*****
#if 0
    if( sipIP( ctlclsSpeedGet( ) , wspdBuff ) == 0 )
    {
        hpiStsWrite( hpistsOUTSRVSPD , wspdBuff );
        return;
    } else {
        if (guc_Sequence_mode == MAIN_WELD || guc_Sequence_mode == START_WELD || guc_Sequence_mode == INITIAL_WELD)
        {
            if (gtt_Ctrl_flag.DC_control_timer == OFF)
            {
                gtt_Ctrl_flag.DC_control_timer = ON;
                gtt_Ctrl_counter.us_DC_control_timer = gss_Select_dital[P_DC_CONTROL_TIME];
            } else if (gtt_Ctrl_counter.us_DC_control_timer <= 0) {
                gtt_Ctrl_flag.AC_control = true;
            }
        }
    }
#endif


}


/* end */

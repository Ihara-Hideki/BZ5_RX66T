/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      制御クラス                                                          */
/*  [データ説明]                                                            */
/*      sint        WFe_Sirei_W         ワイヤ速度指令値(溶接条件)          */
/*      sint        WFe_Target_W        ワイヤ速度目標値(溶接条件)          */
/*      sint        V_Sirei             電圧指令値(溶接条件)                */
/*      sint        V_Target            電圧目標値(溶接条件)                */
/*      sint        WFe_Sirei_S         ワイヤ速度指令値(サーボ速度)        */
/*      sint        WFe_Target_S        ワイヤ速度目標値(サーボ速度)        */
/*      int         Drct                ワイヤ回転方向 １＝正方向           */
/*                                                     -1＝逆方向           */
/*--------------------------------------------------------------------------*/
typedef struct
{
    sint    WFe_Sirei_W;
    sint    WFe_Target_W;
    sint    V_Sirei;
    sint    V_Target;
    sint    WFe_Sirei_S;
    sint    WFe_Target_S;
    int     Drct;
    //<><><>電流補間 2008.12.02<><><>
    sint    CRe_Sirei_W;
    sint    CRe_Target_W;
    //<><><><><><><><><><><><><><><>
}CTLCLS , *PCTLCLS;

//
// End of IfDefine.h
//

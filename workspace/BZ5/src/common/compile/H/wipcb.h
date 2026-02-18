/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      溶接条件補間クラス                                                  */
/*  [データ説明]                                                            */
/*      sint        WFe_Target  ワイヤ送給速度目標値(0.001m/min)            */
/*      sint        Ve_Target   指令電圧目標値(0.1V)                        */
/*      float       Vpe         一元電圧ステップ(パルス)目標値              */
/*      float       Vse         一元電圧ステップ(短絡)目標値                */
/*      float       WFe         ワイヤ送給速度目標値                        */
/*      float       Ve          指令電圧目標値                              */
/*      float       Vps         一元電圧ステップ(パルス)スタート値          */
/*      float       Vss         一元電圧ステップ(短絡)スタート値            */
/*      float       WFs         ワイヤ送給速度スタート値                    */
/*      float       Vp          加減速中の一元電圧ステップ(パルス)          */
/*      float       Vs          加減速中の一元電圧ステップ(短絡)            */
/*      float       Wf          加減速中ワイヤ送給速度                      */
/*      float       T           加減速時間                                  */
/*      int         N           加減速分割数                                */
/*      int         K           加減速分割数(０≦K≦N-1)                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    sint    WFe_Target;
    sint    Ve_Target;
    float   Vpe;
    float   Vse;
    float   WFe;
    float   Ve;
    float   Vps;
    float   Vss;
    float   WFs;
    float   Vp;
    float   Vs;
    float   Wf;
    float   T;
    int     N;
    int     K;

    //<><><>電流補間 2008.12.02<><><>
    sint    CRe_Target;
    float   CRe;
    float   CRs;
    float   Cr;
    //<><><><><><><><><><><><><><><>

}WIPCB,*PWIPCB;

/* end */

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｉｎｐｕｔ＿ｅｘｔ＿ｖｒ＿ｃｌａｓｓ
//　【関数レベル】
//　　　ＬＥＶＥＬ：２
//  【機能説明】
//      外部ＶＲ入力
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
#include  "custom.h"
//--------- Phase4 by @Tny 2008/09/08 --------
#if true

// A/D変換最大入力電圧
//
#define AD15V   1   // １５Ｖ
#define AD12V   2   // １２Ｖ
#define AD10V   3   // １０Ｖ

// 算出補正加算数
//
#define SHIFT_AW     30.0   // 電流値用
#define SHIFT_VW     49.0   // 電圧値用

// プライベート関数宣言
//
static signed short MakeIffAd2Okcv(unsigned short Data);
static unsigned short MakeIffAd2Curr(unsigned char Sw, unsigned short Data);
static unsigned short MakeIffAd2Volt(unsigned char Sw, unsigned short Data);
void input_ext_vr_class(void)
{
    if(gb_IIF_Select){  // IIF接続を確認
        unsigned short  iADport;
        ubool            Proc;

        // 電流指令値の確定
        Proc    = false;
        for(iADport=0;iADport<3;iADport++){
            switch(guc_Analog_port[0][iADport+1]){
                case    1:{ // １５Ｖ系電流指令
                            gtt_Internal_pack.Data.In.usWeldingCurr = MakeIffAd2Curr(AD15V,gus_Iif_ad_input[iADport]);
                            Proc = true;
                            break;}
                case    2:{ // １２Ｖ系電流指令
                            gtt_Internal_pack.Data.In.usWeldingCurr = MakeIffAd2Curr(AD12V,gus_Iif_ad_input[iADport]);
                            Proc = true;
                            break;}
                case    3:{ // １０Ｖ系電流指令
                            gtt_Internal_pack.Data.In.usWeldingCurr = MakeIffAd2Curr(AD10V,gus_Iif_ad_input[iADport]);
                            Proc = true;
                            break;}
            }
            if(Proc) break; // 電流指令値確定済み
        }

        // 電圧指令値の確定
        Proc    = false;
        for(iADport=0;iADport<3;iADport++){
            switch(guc_Analog_port[0][iADport+1]){
                case    4:{ // １５Ｖ系電圧指令
                            if(guc_Okcv_select_flag == true){ //一元電圧選択
                                gs_Okcv_adjust_data = MakeIffAd2Okcv(gus_Iif_ad_input[iADport]);
                            }
                            else{
                                gtt_Internal_pack.Data.In.usWeldingVolt = MakeIffAd2Volt(AD15V,gus_Iif_ad_input[iADport]);
                            }
                            Proc = true;
                            break;}
                case    5:{ // １２Ｖ系電圧指令
                            if(guc_Okcv_select_flag == true){ //一元電圧選択
                                gs_Okcv_adjust_data = MakeIffAd2Okcv(gus_Iif_ad_input[iADport]);
                            }
                            else{
                                gtt_Internal_pack.Data.In.usWeldingVolt = MakeIffAd2Volt(AD12V,gus_Iif_ad_input[iADport]);
                            }
                            Proc = true;
                            break;}
                case    6:{ // １０Ｖ系電圧指令
                            if(guc_Okcv_select_flag == true){ //一元電圧選択
                                gs_Okcv_adjust_data = MakeIffAd2Okcv(gus_Iif_ad_input[iADport]);
                            }
                            else{
                                gtt_Internal_pack.Data.In.usWeldingVolt = MakeIffAd2Volt(AD10V,gus_Iif_ad_input[iADport]);
                            }
                            Proc = true;
                            break;}
            }
            if(Proc) break; // 電圧指令値確定済み
        }
    }
return;
}
/***
**  ID     = MakeIffAd2Okcv
**  name   = 一元化電圧指令値用差分算出処理
**  func   = ＩＩＦからのＡ／Ｄ値から一元化電圧指令値用差分値を算出する
**  called = static signed short MakeIffAd2Volt(unsigned short Data)
**  io     = Data       : ushrt : Ａ／Ｄ変換値
**  return = uchar		: 変換後の電圧指令値
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2008/09/08 by 谷川まさや
***/
static signed short MakeIffAd2Okcv(unsigned short Data)
{
    unsigned short  Val = Data; // A/D変換値の読み取り
    signed short    Ret = 0;

    // A/D入力値の上下限値設定
    //
    if(Val > 446)       Val = 446;  // 14V相当  223 = 7V相当
    else if(Val <= 0)   Val = 0;    //  0V相当

    // Ａ／Ｄ値から電圧指令値の算出
    //
    if(((signed short)Val - 223) >= 0){
        Ret = (signed short)(((float)Val - 223.0) * (120.0 / (446.0 - 223.0)) + 0.5);
    }
    else{
        Ret = (signed short)(((float)Val - 223.0) * (120.0 / (446.0 - 223.0)) - 0.5);
    }

    // 算出した電圧指令値の有効範囲確認
    //
    if(Ret > 120)           Ret = 120;  // MAX : +12.0V
    else if(Ret <= -120)    Ret = -120; // MIN : -12.0V

return(Ret);
}
/***
**  ID     = MakeIffAd2Curr
**  name   = 電流指令値算出処理
**  func   = ＩＩＦからのＡ／Ｄ値から電流指令値を算出する
**  called = static unsigned short MakeIffAd2Curr(unsigned char Sw, unsigned short Data)
**  io     = Sw         : uchar : 変換最大入力電圧（１５Ｖ／１２Ｖ／１０Ｖ）
**           Data       : ushrt : Ａ／Ｄ変換値
**  return = uchar		: 変換後の電流指令値
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2008/09/08 by 谷川まさや
***/
static unsigned short MakeIffAd2Curr(unsigned char Sw, unsigned short Data)
{
    unsigned short  Val = Data; // A/D変換値の読み取り
    unsigned short  Ret = 0;

    // A/D入力値の上下限値設定
    //
    if(Val > 500)       Val = 500;
    else if(Val <= 0)   Val = 0;

    // Ａ／Ｄ値から電流指令値の算出
    //
    switch(Sw){
        case    AD15V:{ Ret = (unsigned short)(((float)Val * 44.0 / 64.0) + SHIFT_AW);   break;}    // 43 -> 45 -> 46 -> 44
        case    AD12V:{ Ret = (unsigned short)(((float)Val * 55.0 / 64.0) + SHIFT_AW);   break;}    // 51 -> 54 -> 56 -> 55
        case    AD10V:{ Ret = (unsigned short)(((float)Val * 66.0 / 64.0) + SHIFT_AW);   break;}    // 61 -> 65 -> 66
    }

    // 算出した電流指令値の有効範囲確認
    //
    if(Ret > 350)       Ret = 350;  // MAX : 350A
    else if(Ret <= 30)  Ret = 30;   // MIN :  30A

return(Ret);
}
/***
**  ID     = MakeIffAd2Volt
**  name   = 電圧指令値算出処理
**  func   = ＩＩＦからのＡ／Ｄ値から電圧指令値を算出する
**  called = static unsigned short MakeIffAd2Volt(unsigned char Sw, unsigned short Data)
**  io     = Sw         : uchar : 変換最大入力電圧（１５Ｖ／１２Ｖ／１０Ｖ）
**           Data       : ushrt : Ａ／Ｄ変換値
**  return = uchar		: 変換後の電圧指令値
**  using  =                                   :     /          : 
**  common =                                   :        :   :
**  note   = 
**  date   = 2008/09/08 by 谷川まさや
***/
static unsigned short MakeIffAd2Volt(unsigned char Sw, unsigned short Data)
{
    unsigned short  Val = Data; // A/D変換値の読み取り
    unsigned short  Ret = 0;

    // A/D入力値の上下限値設定
    //
    if(Val > 500)       Val = 500;
    else if(Val <= 0)   Val = 0;

    // Ａ／Ｄ値から電圧指令値の算出
    //
    switch(Sw){
#if true
        case    AD15V:{ Ret = (unsigned short)((float)Val * 0.75 + SHIFT_VW);   break;}
        case    AD12V:{ Ret = (unsigned short)((float)Val * 0.92 + SHIFT_VW);   break;}
        case    AD10V:{ Ret = (unsigned short)((float)Val * 1.14 + SHIFT_VW);   break;}
#else
        case    AD15V:{ Ret = (unsigned short)((float)Val *  5.0 /  8.0 + SHIFT_VW + 0.5);   break;}
        case    AD12V:{ Ret = (unsigned short)((float)Val * 11.0 / 16.0 + SHIFT_VW + 0.5);   break;}
        case    AD10V:{ Ret = (unsigned short)((float)Val * 27.0 / 32.0 + SHIFT_VW + 0.5);   break;}
#endif
    }

    // 算出した電圧指令値の有効範囲確認
    //
    if(Ret > 400)       Ret = 400;  // MAX : 40.0V
    else if(Ret <= 50)  Ret =  50;  // MIN :  5.0V

return(Ret);
}

#endif
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L2_input_ext_vr_class.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

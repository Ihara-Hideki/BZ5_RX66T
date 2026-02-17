//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｍｏｔｏｒ＿ｃｕｒｒｅｎｔ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      モータ過電流異常
//  【引数】
//      なし
//  【戻り値】
//      なし  
//  【備考】
//      なし
//  【更新履歴】
//      2006.12.22  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#include "custom.h"

//<><><><><><><><><><> 2007.8.1 <><><><><><><><><><><><>

#define MOTOR_ERR0 1
#define MOTOR_ERR1 1 //エンコーダ異常
#define MOTOR_ERR2 1 //モータロック
#define MOTOR_ERR3 1 //モータ断線
#define MOTOR_ERR4 0 //モータ回路異常 （今回実装見送り、試験未、2007.8.2）
#define MOTOR_ERR5 0 //モータ異常 （今回実装見送り、試験未、2007.8.2）

//1A指令の無負荷インチングにて、6.1rpm/0.2A実測
//指令電流1A以上にて有効。1A設定のインチング可能なため。
//電流閾値最低値は0.2A。1A指令負荷無しインチングにて0.2A実測のため。
//モータロック　チップ溶着のような場合、モータはすべって空転するので判定できない。

//エンコーダ異常関連
#define MOTOR_ENCODER_ERR____PRE_CURRENT_LEVEL        1  //1A 指令電流値1A以上で有効
#define MOTOR_ENCODER_ERR____MOTOR_CURRENT_LEVEL      8  //0.2A（1dat=0.00244A) 最大回転となりさらに電流は伸びる
#define MOTOR_ENCODER_ERR____MOTOR_RPM_LEVEL          1  //1rpm（整数）
#define MOTOR_ENCODER_ERR_TIME                     1000  // 5s （* 5ms）
//モータロック関連
#define MOTOR_LOCK_ERR____PRE_CURRENT_LEVEL           1  //1A 指令電流値1A以上で有効
#define MOTOR_LOCK_ERR____MOTOR_CURRENT_LEVEL        40  //1A モータロックの場合さらに電流が伸びる
#define MOTOR_LOCK_ERR____MOTOR_RPM_LEVEL             1  //1rpm（整数）
#define MOTOR_LOCK_ERR_TIME                        1000  // * 5ms
//モータ断線
#define MOTOR_CIRCUIT_BREAK____PRE_CURRENT_LEVEL      1 //1A 指令電流値1A以上で有効
#define MOTOR_CIRCUIT_BREAK____MOTOR_CURRENT_LEVEL    4 //0.1A
#define MOTOR_CIRCUIT_BREAK_TIME                   1000 // * 5ms

//モータ回路異常 （今回実装見送り 2007.8.2 ）
//#define MOTOR_CIRCUIT_ERR____MOTOR_CURRENT_LEVEL      4
//#define MOTOR_CIRCUIT_ERR_TIME                     1000 // * 5ms

//モータ異常 （今回実装見送り 2007.8.2 ）
//#define MOTOR_ERR____MOTOR_RPM_LEVEL                  0
//#define MOTOR_ERR_TIME                             200 // 1s（テスト）　* 5ms

//<><><><><><><><><><><><><><><><><><><><><><><><><><><>




unsigned char motor_current_err_member(unsigned char xuc_Err_code)
{
    unsigned char puc_Err_code;

    puc_Err_code   = xuc_Err_code;        //2006.9.8 現状の継承

#if MOTOR_ERR0
    //if(gtt_Motor_current.Result >= MOTOR_CURRENT_ERR_LEVEL) //2005.1.15 下記に変更　2007.1.17削除移植
    if(gtt_Motor_current.Result >= MOTOR_CURRENT_ERR_LEVEL && gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == ON) //2007.1.17移植
    {
        if(gtt_Ctrl_flag.Motor_current_err == OFF)
        {
           gtt_Ctrl_flag.Motor_current_err = ON;
           gtt_Ctrl_counter.Motor_current_err = MOTOR_CURRENT_ERR_TIME;
        } else if(gtt_Ctrl_counter.Motor_current_err <= 0) {
           puc_Err_code = MORTOR_CONTROL_ERR;   //モータ回転異常（過電流異常扱い2006.12.22時点）
        }
    } else {
      gtt_Ctrl_flag.Motor_current_err = OFF;
    }
#endif



    //<><><><><><><><><><><><><><><><><><><><><><><><> 新規モータ異常検出2007.8.1 <><><><><><><><><><><><><><><><><><><><><><><>
#if MOTOR_ERR1
    //エンコーダ異常　2007.8.1
    // <<<                        モータＯＮ                    >>>    <<<                   モータ指令値（電流指令値）                              >>>    <<<                      モータ電流値（直値）                    >>>    <<<                           モータ回転数                                >>>
    if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == ON && gtt_Internal_pack.Data.In.usWeldingCurr >= MOTOR_ENCODER_ERR____PRE_CURRENT_LEVEL && gtt_Motor_current.Result >= MOTOR_ENCODER_ERR____MOTOR_CURRENT_LEVEL && gtt_Internal_pack.Data.Out.usMotorRPM2 <= MOTOR_ENCODER_ERR____MOTOR_RPM_LEVEL)
    {
        if(gtt_Ctrl_flag.Motor_encoder_err == OFF)
        {
           gtt_Ctrl_flag.Motor_encoder_err = ON;
           gtt_Ctrl_counter.Motor_encoder_err = MOTOR_ENCODER_ERR_TIME;
        } else if(gtt_Ctrl_counter.Motor_encoder_err <= 0) {
           puc_Err_code = MORTOR_CONTROL_ERR;   //モータ回転異常（過電流異常扱い2006.12.22時点）
        }
    } else {
      gtt_Ctrl_flag.Motor_encoder_err = OFF;
    }
#endif


#if MOTOR_ERR2
    //モータロック　2007.8.1
    // <<<                        モータＯＮ                    >>>    <<<                   モータ指令値（電流指令値）                           >>>    <<<                      モータ電流値（直値）                 >>>    <<<                           モータ回転数                              >>>
    if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == ON && gtt_Internal_pack.Data.In.usWeldingCurr >= MOTOR_LOCK_ERR____PRE_CURRENT_LEVEL && gtt_Motor_current.Result >= MOTOR_LOCK_ERR____MOTOR_CURRENT_LEVEL && gtt_Internal_pack.Data.Out.usMotorRPM2 <= MOTOR_LOCK_ERR____MOTOR_RPM_LEVEL)
    {
        if(gtt_Ctrl_flag.Motor_lock_err == OFF)
        {
           gtt_Ctrl_flag.Motor_lock_err = ON;
           gtt_Ctrl_counter.Motor_lock_err = MOTOR_LOCK_ERR_TIME;
        } else if(gtt_Ctrl_counter.Motor_lock_err <= 0) {
           puc_Err_code = MORTOR_CONTROL_ERR;   //モータ回転異常（過電流異常扱い2006.12.22時点）
        }
    } else {
      gtt_Ctrl_flag.Motor_lock_err = OFF;
    }
#endif


#if MOTOR_ERR3
    //モータ断線　2007.8.1
    // <<<                        モータＯＮ                    >>>    <<<                   モータ指令値（電流指令値）                                >>>    <<<                      モータ電流値（直値）                      >>>
    if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == ON && gtt_Internal_pack.Data.In.usWeldingCurr >= MOTOR_CIRCUIT_BREAK____PRE_CURRENT_LEVEL && gtt_Motor_current.Result <= MOTOR_CIRCUIT_BREAK____MOTOR_CURRENT_LEVEL)
    {
        if(gtt_Ctrl_flag.Motor_circuit_break == OFF)
        {
           gtt_Ctrl_flag.Motor_circuit_break = ON;
           gtt_Ctrl_counter.Motor_circuit_break = MOTOR_CIRCUIT_BREAK_TIME;
        } else if(gtt_Ctrl_counter.Motor_circuit_break <= 0) {
           puc_Err_code = MORTOR_CONTROL_ERR;   //モータ回転異常（過電流異常扱い2006.12.22時点）
        }
    } else {
      gtt_Ctrl_flag.Motor_circuit_break = OFF;
    }
#endif


#if MOTOR_ERR4
    //モータ回路異常　2007.8.1
    // <<<                        モータＯＦＦ                   >>>    <<<                      モータ電流値（直値）                      >>>
    if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == OFF && gtt_Motor_current.Result >= MOTOR_CIRCUIT_ERR____MOTOR_CURRENT_LEVEL)
    {
        if(gtt_Ctrl_flag.Motor_circuit_err == OFF)
        {
           gtt_Ctrl_flag.Motor_circuit_err = ON;
           gtt_Ctrl_counter.Motor_circuit_err = MOTOR_CIRCUIT_ERR_TIME;
        } else if(gtt_Ctrl_counter.Motor_circuit_err <= 0) {
           puc_Err_code = MORTOR_CONTROL_ERR;   //モータ回転異常（過電流異常扱い2006.12.22時点）
        }
    } else {
      gtt_Ctrl_flag.Motor_circuit_err = OFF;
    }
#endif


#if MOTOR_ERR5
    //モータ異常　2007.8.1
    // <<<                        モータＯＦＦ                   >>>    <<<                            モータ回転数                        >>>
    if(gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on == OFF && gtt_Internal_pack.Data.Out.usMotorRPM2 > MOTOR_ERR____MOTOR_RPM_LEVEL)
    {
        if(gtt_Ctrl_flag.Motor_err == OFF)
        {
           gtt_Ctrl_flag.Motor_err = ON;
           gtt_Ctrl_counter.Motor_err = MOTOR_ERR_TIME;
        } else if(gtt_Ctrl_counter.Motor_err <= 0) {
           puc_Err_code = MORTOR_CONTROL_ERR;   //モータ回転異常（過電流異常扱い2006.12.22時点）
        }
    } else {
      gtt_Ctrl_flag.Motor_err = OFF;
    }
#endif

    //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>




    return (puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_motor_current_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｃｏｍ＿ｅｒｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      通信異常
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

unsigned char com_err_member(unsigned char xuc_Err_code)
{
    unsigned char puc_Err_code;

    puc_Err_code = xuc_Err_code;          //2006.9.8 現状の継承

    //********** パリティ、フレーミングエラー検出方法変更 2007.2.26 ***********
    if (( S0RCNT & 0x01 ) != 0x00)               //ロボット通信（ＲＳ４２２）エラー確認
    {
       if ((S0RCNT & 0x08) == 0x08)
       {
          // オーバーランエラー発生
          puc_Err_code = RS422_OVR_ERR;
          gtt_Internal_pack.Data.bRS422Connection =  false;
          ComuniPack.Data.bRS422Connection        =  false;
          guc_Robot_connect_flag = false; //2008.10.03
       } 
    }
    if (gtt_Ctrl_counter.Com_err_parity > COM_ERR_COUNT) 
    {
       // パリティーエラー発生
        puc_Err_code = RS422_PTY_ERR;
        gtt_Internal_pack.Data.bRS422Connection =  false;
        ComuniPack.Data.bRS422Connection        =  false;
        guc_Robot_connect_flag = false; //2008.10.03
    }
    if (gtt_Ctrl_counter.Com_err_framing > COM_ERR_COUNT)
    {
        // フレーミングエラー発生
        puc_Err_code = RS422_FLM_ERR;
        gtt_Internal_pack.Data.bRS422Connection =  false;
        ComuniPack.Data.bRS422Connection        =  false;
        guc_Robot_connect_flag = false; //2008.10.03
    }
    //***************************************************************************

    if (RS422ErrorFlag == 0x07)
    {
        puc_Err_code = RS422_TIME_OUT_ERR;       //４２２シリアル通信タイムアウトエラー 物理的回線の切断
    }

#if true // ↓ EXTERNAL IIF NEW	2011.02.21 by @Tny
    if (gtt_Ctrl_flag.Iif_connect_err == true)   //2009.10.29 IIF NEW
    {
        puc_Err_code = IIF_CONNECT_ERR;          //ＩＩＦ接続エラー
        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Toch_sw     = false; //NO1.起動入力
        guc_Gas_on_off_flag                                         = OFF;   //NO2.ガス制御
        guc_Inching_sw_flag                                         = OFF;   //NO3.インチング
        gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_on      = OFF;   //NO4.リトラクト
        gtt_Internal_pack.Data.In.fWelderCheck.Bit1Sw.Motor_conect  = OFF;   //NO4
        gtt_Internal_pack.Data.In.fWelderCommand.Bit1Sw.Stick_check = false; //NO5.スティック指令
        //NO6.一元個別は設定なので対象外。
        gtt_Internal_pack.Data.In.Outside1                          = false; //NO7.一時停止１
        gtt_Internal_pack.Data.In.Outside2                          = false; //NO8.一時停止２
        gtt_Internal_pack.Data.In.Emergency                         = false; //NO9.非常停止
        //NO10～NO16はｃｈ再生設定なので対象外
        guc_General1_input                                          = OFF;   //NO17.汎用入力１
        guc_General2_input                                          = OFF;   //NO18.汎用入力２
        guc_General3_input                                          = OFF;   //NO19.汎用入力３
    }
#endif // ↑ EXTERNAL IIF NEW	2011.02.21 by @Tny

#if 0
    if (( S0RCNT & 0x01 ) != 0x00)               //ロボット通信（ＲＳ４２２）エラー確認
    {
       if ((S0RCNT & 0x08) == 0x08)
       {
          // オーバーランエラー発生
          puc_Err_code = RS422_OVR_ERR;
          gtt_Internal_pack.Data.bRS422Connection =  false;
          ComuniPack.Data.bRS422Connection        =  false; 
       }
       if ((S0RCNT & 0x04) == 0x04)
       {
          // パリティーエラー発生
          puc_Err_code = RS422_PTY_ERR;
          gtt_Internal_pack.Data.bRS422Connection =  false;
          ComuniPack.Data.bRS422Connection        =  false;
       }
       if ((S0RCNT & 0x02) == 0x02)
       {
          // フレーミングエラー発生
          puc_Err_code = RS422_FLM_ERR;
          gtt_Internal_pack.Data.bRS422Connection =  false;
          ComuniPack.Data.bRS422Connection        =  false;
       }
    }
#endif



    if ((S2RCNT & 0x01 ) != 0x00)                //ＰＣ通信（ＲＳ２３２Ｃ）エラー確認
    {
       if ((S2RCNT & 0x08) == 0x08)
       {
          // オーバーランエラー発生
          puc_Err_code = RS232_OVR_ERR;
          gtt_Internal_pack.Data.bRS232Connection = false;
          ComuniPack.Data.bRS232Connection        = false;
       }
       if ((S2RCNT & 0x04) == 0x04)
       {
          // パリティーエラー発生
          puc_Err_code = RS232_PTY_ERR;
          gtt_Internal_pack.Data.bRS232Connection = false;
          ComuniPack.Data.bRS232Connection        = false;
       }
       if ((S2RCNT & 0x02) == 0x02)
       {
          // フレーミングエラー発生
          puc_Err_code = RS232_FLM_ERR;
          gtt_Internal_pack.Data.bRS232Connection = false;
          ComuniPack.Data.bRS232Connection        = false;
       }
    }

    if ( gtt_internal_r8.Com_check == ON){      //Ｒ８通信エラー確認 2007.1.17移植削除 //2009.04.20復活
    //if ( gtt_internal_r8.Com_check == ON && gtt_Dsw.Sw.No15 == OFF){ //Ｒ８通信エラー確認 PCへ3000個のデータを送信する際エラーが発生するのを防ぐ2007.1.17 2007.1.17移植 2009.04.20削除
        if(gtt_Ctrl_flag.R8_com_err == OFF){
           gtt_Ctrl_flag.R8_com_err = ON;
           gtt_Ctrl_counter.R8_com_err = R8_COM_ERR_TIME;
        } else if(gtt_Ctrl_counter.R8_com_err <= 0){
          puc_Err_code = R8_COM_ERR;           //Ｒ８との通信異常
        }
    } else {
      gtt_Ctrl_flag.R8_com_err = OFF;
    }
    
    return (puc_Err_code);
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_com_err_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

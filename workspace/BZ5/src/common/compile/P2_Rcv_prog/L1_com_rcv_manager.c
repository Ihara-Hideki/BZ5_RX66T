//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｃｏｍ＿ｒｃｖ＿ｍａｎａｇｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：１
//  【機能説明】
//      通信受信管理
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


//struct	ComuniPackRemo	ComuniPackRemo;

void com_rcv_manager(void)
{
//----- Phase9 by @Tny 2008/09/16 -----
#if true
        //if(gub_System_err != ON){   // エラーは発生していない？
        if(gub_System_err != ON || guc_Robot_connect_flag == true){//2008.12.04
            rob_pc_re_rcv_class();
        }
        else{
            ComuniPackRemo.Data.To.Jog.uc_Jog1 = 0;
            ComuniPackRemo.Data.To.Jog.uc_Jog2 = 0;
        }
#endif
//--------------------------------------------


//--------- IIF(Phase15 Re Makeing) by @Tny 2008/08/28 2008/09/19 ------------
#if false //2009.10.15del IIF NEW	← EXTERNAL IIF NEW	2011.02.21 by @Tny
    {
        unsigned short  iPort;

        for(iPort=0; iPort<8; iPort++){ // 全ＩＩＦ出力ポート検索
            switch(guc_Out_port[0][(iPort+1)]){
                case    0:{ // 当該ポートは未使用
                            guc_Iif_output = (guc_Iif_output & (~(0x01 << iPort)));
                            break;}
                case    1:{ // 当該ポートは電検状態信号
                            if(gtt_Internal_pack.Data.Out.fPowerStatus.Bit1Sw.Cd == ON) guc_Iif_output = (guc_Iif_output | (0x01 << iPort));
                            else                                                        guc_Iif_output = (guc_Iif_output & (~(0x01 << iPort)));
                            break;}
                case    2:{ // 当該ポートはスティック検知信号
                            if(gtt_Internal_pack.Data.Out.fErrorCode1.Bit1Sw.b0 == ON)  guc_Iif_output = (guc_Iif_output | (0x01 << iPort));
                            else                                                        guc_Iif_output = (guc_Iif_output & (~(0x01 << iPort)));
                            break;}
                case    3:{ // 当該ポートはアイドリング状態信号
                            if(guc_Sequence_mode == IDLING)                             guc_Iif_output = (guc_Iif_output | (0x01 << iPort));
                            else                                                        guc_Iif_output = (guc_Iif_output & (~(0x01 << iPort)));
                            break;}
            }
        }
    }
#endif
//--------------------------------------------


     return;
}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L1_com_rcv_manager.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

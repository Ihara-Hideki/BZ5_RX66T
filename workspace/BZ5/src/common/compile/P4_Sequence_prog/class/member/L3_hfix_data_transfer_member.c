//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【関数名】
//　　　ｈｆｉｘ＿ｄａｔａ＿ｔｒａｎｓｆｅｒ＿ｍｅｍｂｅｒ
//　【関数レベル】
//　　　ＬＥＶＥＬ：３
//  【機能説明】
//      半固定データ転送
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

//	標準関数の代替機能

void xmemset(void *dst, int dat, size_t lgh)
{
	char	*pd = dst;

	for(;lgh;--lgh)	*(pd++) = (char)dat;
}
void xmemcpy(void *dst, const void *soc, size_t lgh)
{
	char		*pd = dst;
	const char	*ps = soc;

	for(;lgh;--lgh){
		*(pd++) = *(ps++);
	}
}

int	xmemcmp(const char*dst,const char*soc, size_t lgh)
{
	while( (*soc==*dst) && ((--lgh) != 0) )
	{
		++soc;
		++dst;
	}
	return	(lgh);
}


//extern unsigned char weld_hfix_abs_tbl;
//extern unsigned char weld_hfix_rel_tbl;
extern WELDCODE DC_WELDCODE;
void hfix_data_transfer_member(ubool xub_Initial_hfix)
{
        unsigned int i;
        sint   *pAbs = (sint*)_union.Nrm.WeldParm_Abs;

        short        pss_Index;          //2010.02.19
        PCURTBL      pCURTBL;            //2010.02.19



        i = 0;                  //2006.8.30 clear

#define ASOTEST		0	//ASOTEST=1 にて、CO2 φ1.2 ext15　にデータ固定する。
#if ASOTEST
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x01;
            DC_WELDCODE.pulseMode = 0x03;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05;
            DC_WELDCODE.extension = 0x03;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
#else
            //DC_WELDCODE.material  = gtt_Table_key.Wire_material;
            //DC_WELDCODE.method    = gtt_Table_key.Welding_method;
            //DC_WELDCODE.pulseMode = gtt_Table_key.Pulse_mode;
            //DC_WELDCODE.pulseType = gtt_Table_key.Pulse_type;
            //DC_WELDCODE.wire      = gtt_Table_key.Wire_diameter;
            //DC_WELDCODE.extension = gtt_Table_key.Wire_ext;
            //DC_WELDCODE.dummy1    = 0x00;
            //DC_WELDCODE.dummy2    = 0x00;
         //直流手溶接を含めたアクセス 2009.03.07

#if 0 //2009.03.27 del
         if (guc_Method_condition_data == STD_AC_METHOD || guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD)
         {
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x06;
            DC_WELDCODE.pulseMode = 0x05;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05; //AC
            DC_WELDCODE.extension = 0x04;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
         } 
         if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
         {
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x06;
            DC_WELDCODE.pulseMode = 0x05;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05;   //DC
            DC_WELDCODE.extension = 0x03;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
         }
         if (guc_Method_condition_data == STD_HAND_METHOD)
         {
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x06;
            DC_WELDCODE.pulseMode = 0x05;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05;
            DC_WELDCODE.extension = 0x02;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
         }
#endif
         //***** 新テーブルコード 2009.03.27 *****
         //直流手溶接
         if (guc_Method_condition_data == STD_HAND_METHOD)
         {
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x06;
            DC_WELDCODE.pulseMode = 0x05;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05;
            DC_WELDCODE.extension = 0x02;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
            //LED4 = OFF; //2009.07.23 test
         }
         //標準直流・エキスパート直流
         if (guc_Method_condition_data == STD_DC_METHOD || guc_Method_condition_data == EXP_DC_METHOD)
         {
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x06;
            DC_WELDCODE.pulseMode = 0x05;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05;
            DC_WELDCODE.extension = 0x03;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
            //LED4 = OFF; //2009.07.23 test
         }
         //エキスパート交流・ＭＩＸ（交流波形標準のみのもの）
         if (guc_Method_condition_data == EXP_AC_METHOD || guc_Method_condition_data == STD_MIX_METHOD)
         {
            DC_WELDCODE.material  = 0x01;
            DC_WELDCODE.method    = 0x06;
            DC_WELDCODE.pulseMode = 0x05;
            DC_WELDCODE.pulseType = 0x00;
            DC_WELDCODE.wire      = 0x05;
            DC_WELDCODE.extension = 0x04;
            DC_WELDCODE.dummy1    = 0x00;
            DC_WELDCODE.dummy2    = 0x00;
            //LED4 = OFF; //2009.07.23 test
         }
         //交流（標準・ソフト・ハード）
         if (guc_Method_condition_data == STD_AC_METHOD)
         {
            switch (guc_Ac_wave_counter)
            {
               case 0: //標準
                       DC_WELDCODE.material  = 0x01;
                       DC_WELDCODE.method    = 0x06;
                       DC_WELDCODE.pulseMode = 0x05;
                       DC_WELDCODE.pulseType = 0x00;
                       DC_WELDCODE.wire      = 0x05;
                       DC_WELDCODE.extension = 0x04;
                       DC_WELDCODE.dummy1    = 0x00;
                       DC_WELDCODE.dummy2    = 0x00;
            //LED4 = ON; //2009.07.23 test
                       break;
               case 1: //ハード
                       DC_WELDCODE.material  = 0x01;
                       DC_WELDCODE.method    = 0x06;
                       DC_WELDCODE.pulseMode = 0x05;
                       DC_WELDCODE.pulseType = 0x00;
                       DC_WELDCODE.wire      = 0x05;
                       DC_WELDCODE.extension = 0x06;
                       DC_WELDCODE.dummy1    = 0x00;
                       DC_WELDCODE.dummy2    = 0x00;
            //LED4 = OFF; //2009.07.23 test
                       break;
               case 2: //ソフト
                       DC_WELDCODE.material  = 0x01;
                       DC_WELDCODE.method    = 0x06;
                       DC_WELDCODE.pulseMode = 0x05;
                       DC_WELDCODE.pulseType = 0x00;
                       DC_WELDCODE.wire      = 0x05;
                       DC_WELDCODE.extension = 0x05;
                       DC_WELDCODE.dummy1    = 0x00;
                       DC_WELDCODE.dummy2    = 0x00;
            //LED4 = OFF; //2009.07.23 test
                       break;
                default:
                       DC_WELDCODE.material  = 0x01;
                       DC_WELDCODE.method    = 0x06;
                       DC_WELDCODE.pulseMode = 0x05;
                       DC_WELDCODE.pulseType = 0x00;
                       DC_WELDCODE.wire      = 0x05;
                       DC_WELDCODE.extension = 0x04;
                       DC_WELDCODE.dummy1    = 0x00;
                       DC_WELDCODE.dummy2    = 0x00;
            //LED4 = OFF; //2009.07.23 test
                       break;
            }
         }

#endif


            DataUpdate( );

            //<><><> 電流指令値テーブルデータのコピー 2010.02.19 <><><>
            pCURTBL    = pWT->pCURTBL_Data;  //2010.02.20
            for ( pss_Index = 0 ; pss_Index < 639 ; pss_Index++ )
            {
                  gss_Current_table_data[pss_Index] = pCURTBL->CUR_DATA[pss_Index];
            }
            //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


        //<><><><><>繰り返し溶接を実現するため<><><><><> REPEAT 2007.1.12
        isContArc = 0;
        WeldAdjOut_Proc( isContArc );           //半固定パラメータのＤＳＰへの再送

#if 0
        if (xub_Initial_hfix == true)
        {
            hpiWrite( hpicmdOUTWLDADJST2, (pusint)&pAbs[ WLDADJST_1LEN ] );//半固定パラメータ２送信
            hpiWrite( hpicmdOUTWLDADJST , (pusint)&pAbs[ 0 ] );  //半固定パラメータ送信
        } else {
            IMJTOCR4  = 0x07; //2006.2.15 割禁　ihara     
            hpiWrite( hpicmdOUTWLDADJST , (pusint)&pAbs[ 0 ] );  //半固定パラメータ送信
            hpiWrite( hpicmdOUTWLDADJST2, (pusint)&pAbs[ WLDADJST_1LEN ] );//半固定パラメータ２送信
            IMJTOCR4  = 0x05; //2006.2.9 割許　ihara
        }
#endif
        //<><><><><><><><><><><><><><><><><><><><><><><>

}
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of L3_hfix_data_transfer_member.c
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

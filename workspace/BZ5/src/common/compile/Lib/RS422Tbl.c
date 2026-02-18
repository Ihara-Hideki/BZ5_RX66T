/********************************************************/
/*-- Function     	: ÇqÇrÇSÇQÇQÉRÉ}ÉìÉhÉeÅ[ÉuÉã		*/
/*-  File Name		: RS422TBL.h						*/
/*	 Create Date	: 00/04/13							*/
/*	 Author			: With) S.Yonemori					*/
/*	 Comment		: 									*/
/*	 Corrector		:									*/
/********************************************************/
#define  __COM_TEBLE
#include	"custom.h"

/* ÇfÇcÇQÅ®ónê⁄ã@ ÉRÉ}ÉìÉh */
extern unsigned char (*FromGD2[ 256 ])( void ) = {
	StaticDmy,		/* 00 */
	StaticDmy,		/* 01 */
	StaticDmy,		/* 02 */
	StaticDmy,		/* 03 */
	StaticDmy,		/* 04 */
	StaticDmy,		/* 05 */
	StaticDmy,		/* 06 */
	StaticDmy,		/* 07 */
	StaticDmy,		/* 08 */
	StaticDmy,		/* 09 */
	StaticDmy,		/* 0A */
	StaticDmy,		/* 0B */
	StaticDmy,		/* 0C */
	StaticDmy,		/* 0D */
	StaticDmy,		/* 0E */
	StaticDmy,		/* 0F */

	StaticDmy,		/* 10 */
	StaticDmy,		/* 11 */
	StaticDmy,		/* 12 */
	StaticDmy,		/* 13 */
	StaticDmy,		/* 14 */
	StaticDmy,		/* 15 */
	StaticDmy,		/* 16 */
	StaticDmy,		/* 17 */
	StaticDmy,		/* 18 */
	StaticDmy,		/* 19 */
	StaticDmy,		/* 1A */
	StaticDmy,		/* 1B */
	StaticDmy,		/* 1C */
	StaticDmy,		/* 1D */
	StaticDmy,		/* 1E */
	StaticDmy,		/* 1F */

	StaticDmy,		/* 20 */
	StaticDmy,		/* 21 */
	StaticDmy,		/* 22 */
	StaticDmy,		/* 23 */
	StaticDmy,		/* 24 */
	StaticDmy,		/* 25 */
	StaticDmy,		/* 26 */
	StaticDmy,		/* 27 */
	StaticDmy,		/* 28 */
	StaticDmy,		/* 29 */
	StaticDmy,		/* 2A */
	StaticDmy,		/* 2B */
	StaticDmy,		/* 2C */
	StaticDmy,		/* 2D */
	StaticDmy,		/* 2E */
	StaticDmy,		/* 2F */

	StaticDmy,		/* 30 */
	StaticDmy,		/* 31 */
	StaticDmy,		/* 32 */
	StaticDmy,		/* 33 */
	StaticDmy,		/* 34 */
	StaticDmy,		/* 35 */
	StaticDmy,		/* 36 */
	StaticDmy,		/* 37 */
	StaticDmy,		/* 38 */
	StaticDmy,		/* 39 */
	StaticDmy,		/* 3A */
	StaticDmy,		/* 3B */
	StaticDmy,		/* 3C */
	StaticDmy,		/* 3D */
	StaticDmy,		/* 3E */
	StaticDmy,		/* 3F */

	StaticDmy,		/* 40 */
	GD2_Recv_41,	/* 41 */
	GD2_Recv_42,	/* 42 */
	StaticDmy,		/* 43 */
	StaticDmy,		/* 44 */
	StaticDmy,		/* 45 */
	StaticDmy,		/* 46 */
	GD2_Recv_47,	/* 47 */
	GD2_Recv_48,	/* 48 */
	GD2_Recv_49,	/* 49 */
	GD2_Recv_4A,	/* 4A */
	StaticDmy,		/* 4B */
	StaticDmy,		/* 4C */
	StaticDmy,		/* 4D */
	StaticDmy,		/* 4E */
	GD2_Recv_4F,	/* 4F */

	StaticDmy,		/* 50 */
	StaticDmy,		/* 51 */
	GD2_Recv_52,	/* 52 */
	GD2_Recv_53,	/* 53 */
	StaticDmy,		/* 54 */
	StaticDmy,		/* 55 */
	StaticDmy,		/* 56 */
	StaticDmy,		/* 57 */
	StaticDmy,		/* 58 */
	StaticDmy,		/* 59 */
	StaticDmy,		/* 5A */
	StaticDmy,		/* 5B */
	StaticDmy,		/* 5C */
	StaticDmy,		/* 5D */
	StaticDmy,		/* 5E */
	StaticDmy,		/* 5F */

	StaticDmy,		/* 60 */
	GD2_Recv_61,	/* 61 */
	GD2_Recv_62,	/* 62 */
	GD2_Recv_63,	/* 63 */
	GD2_Recv_64,	/* 64 */
	StaticDmy,		/* 65 */
	StaticDmy,		/* 66 */
	GD2_Recv_67,	/* 67 */
	GD2_Recv_68,	/* 68 */
	GD2_Recv_69,	/* 69 2009.07.13*/
	StaticDmy,		/* 6A */
	GD2_Recv_6B,	/* 6B 2009.07.13*/
    GD2_Recv_6C,    /* 6C */
	StaticDmy,		/* 6D */
	StaticDmy,		/* 6E */
	StaticDmy,		/* 6F */

	StaticDmy,		/* 70 */
	GD2_Recv_71,	/* 71 */
	StaticDmy,		/* 72 */
	StaticDmy,		/* 73 */
	StaticDmy,		/* 74 */
	StaticDmy,		/* 75 */
	StaticDmy,		/* 76 */
	StaticDmy,		/* 77 */
	StaticDmy,		/* 78 */
	StaticDmy,		/* 79 */
	StaticDmy,		/* 7A */
	StaticDmy,		/* 7B */
	StaticDmy,		/* 7C */
	StaticDmy,		/* 7D */
	StaticDmy,		/* 7E */
	StaticDmy,		/* 7F */

    StaticDmy,		/* 80 */
	GD2_Recv_81,	/* 81 */
	GD2_Recv_82,	/* 82 */
	GD2_Recv_83,	/* 83 */
	GD2_Recv_84,	/* 84 */
	GD2_Recv_85,	/* 85 */
	GD2_Recv_86,	/* 86 */
	GD2_Recv_87,	/* 87 */
	GD2_Recv_88,	/* 88 */
	GD2_Recv_89,	/* 89 2007.2.9*/
	GD2_Recv_8A,	/* 8A 2007.5.11*/
	GD2_Recv_8B,	/* 8B 2007.5.11*/
	GD2_Recv_8C,	/* 8C 2008.12.01*/
	GD2_Recv_8D,	/* 8D 2008.12.01*/
	GD2_Recv_8E,	/* 8E 2008.12.01*/
	StaticDmy,		/* 8F */

	StaticDmy,		/* 90 */
	StaticDmy,		/* 91 */
	StaticDmy,		/* 92 */
	StaticDmy,		/* 93 */
	StaticDmy,		/* 94 */
	StaticDmy,		/* 95 */
	StaticDmy,		/* 96 */
	StaticDmy,		/* 97 */
	StaticDmy,		/* 98 */
	StaticDmy,		/* 99 */
	StaticDmy,		/* 9A */
	StaticDmy,		/* 9B */
	StaticDmy,		/* 9C */
	StaticDmy,		/* 9D */
	StaticDmy,		/* 9E */
	StaticDmy,		/* 9F */

	StaticDmy,		/* A0 */
	StaticDmy,		/* A1 */
	StaticDmy,		/* A2 */
	StaticDmy,		/* A3 */
	StaticDmy,		/* A4 */
	StaticDmy,		/* A5 */
	StaticDmy,		/* A6 */
	StaticDmy,		/* A7 */
	StaticDmy,		/* A8 */
	StaticDmy,		/* A9 */
	StaticDmy,		/* AA */
	StaticDmy,		/* AB */
	StaticDmy,		/* AC */
	StaticDmy,		/* AD */
	StaticDmy,		/* AE */
	StaticDmy,		/* AF */

	StaticDmy,		/* B0 */
	StaticDmy,		/* B1 */
	StaticDmy,		/* B2 */
	StaticDmy,		/* B3 */
	StaticDmy,		/* B4 */
	StaticDmy,		/* B5 */
	StaticDmy,		/* B6 */
	StaticDmy,		/* B7 */
	StaticDmy,		/* B8 */
	StaticDmy,		/* B9 */
	StaticDmy,		/* BA */
	StaticDmy,		/* BB */
	StaticDmy,		/* BC */
	StaticDmy,		/* BD */
	StaticDmy,		/* BE */
	StaticDmy,		/* BF */

	StaticDmy,		/* C0 */
	StaticDmy,		/* C1 */
	StaticDmy,		/* C2 */
	StaticDmy,		/* C3 */
	StaticDmy,		/* C4 */
	StaticDmy,		/* C5 */
	StaticDmy,		/* C6 */
	StaticDmy,		/* C7 */
	StaticDmy,		/* C8 */
	StaticDmy,		/* C9 */
	StaticDmy,		/* CA */
	StaticDmy,		/* CB */
	StaticDmy,		/* CC */
	StaticDmy,		/* CD */
	StaticDmy,		/* CE */
	StaticDmy,		/* CF */

	StaticDmy,		/* D0 */
	StaticDmy,		/* D1 */
	StaticDmy,		/* D2 */
	StaticDmy,		/* D3 */
	StaticDmy,		/* D4 */
	StaticDmy,		/* D5 */
	StaticDmy,		/* D6 */
	StaticDmy,		/* D7 */
	StaticDmy,		/* D8 */
	StaticDmy,		/* D9 */
	StaticDmy,		/* DA */
	StaticDmy,		/* DB */
	StaticDmy,		/* DC */
	StaticDmy,		/* DD */
	StaticDmy,		/* DE */
	StaticDmy,		/* DF */

	StaticDmy,		/* E0 */
	StaticDmy,		/* E1 */
	StaticDmy,		/* E2 */
	StaticDmy,		/* E3 */
	StaticDmy,		/* E4 */
	StaticDmy,		/* E5 */
	StaticDmy,		/* E6 */
	StaticDmy,		/* E7 */
	StaticDmy,		/* E8 */
	StaticDmy,		/* E9 */
	StaticDmy,		/* EA */
	StaticDmy,		/* EB */
	StaticDmy,		/* EC */
	StaticDmy,		/* ED */
	StaticDmy,		/* EE */
	StaticDmy,		/* EF */

	StaticDmy,		/* F0 */
	StaticDmy,		/* F1 */
	StaticDmy,		/* F2 */
	StaticDmy,		/* F3 */
	StaticDmy,		/* F4 */
	StaticDmy,		/* F5 */
	StaticDmy,		/* F6 */
	StaticDmy,		/* F7 */
	StaticDmy,		/* F8 */
	StaticDmy,		/* F9 */
	StaticDmy,		/* FA */
	StaticDmy,		/* FB */
	StaticDmy,		/* FC */
	StaticDmy,		/* FD */
	StaticDmy,		/* FE */
	StaticDmy,		/* FF */

} ;

/* ónê⁄ã@Å®ÇfÇcÇQ */
extern unsigned char (*ToGD2[ 256 ])( void ) = {
	StaticDmy,		/* 00 */
	StaticDmy,		/* 01 */
	StaticDmy,		/* 02 */
	StaticDmy,		/* 03 */
	StaticDmy,		/* 04 */
	StaticDmy,		/* 05 */
	StaticDmy,		/* 06 */
	StaticDmy,		/* 07 */
	StaticDmy,		/* 08 */
	StaticDmy,		/* 09 */
	StaticDmy,		/* 0A */
	StaticDmy,		/* 0B */
	StaticDmy,		/* 0C */
	StaticDmy,		/* 0D */
	StaticDmy,		/* 0E */
	StaticDmy,		/* 0F */

	StaticDmy,		/* 10 */
	StaticDmy,   	/* 11 */
	StaticDmy,		/* 12 */
	StaticDmy,		/* 13 */
	StaticDmy,		/* 14 */
	StaticDmy,		/* 15 */
	StaticDmy,		/* 16 */
	StaticDmy,		/* 17 */
	StaticDmy,		/* 18 */
	StaticDmy,		/* 19 */
	StaticDmy,		/* 1A */
	StaticDmy,		/* 1B */
	StaticDmy,		/* 1C */
	StaticDmy,		/* 1D */
	StaticDmy,		/* 1E */
	StaticDmy,		/* 1F */

//--------- IIF by @Tny 2008/08/26 ------------
#if false	// EXTERNAL IIF NEW	Del 2010.09.01 by @Tny
	GD2_Send_20,	/* 20 */
#else
	StaticDmy,		/* 20 */
#endif
//--------------------------------------------
	StaticDmy,      /* 21 */
	StaticDmy,		/* 22 */
	StaticDmy,		/* 23 */
	StaticDmy,		/* 24 */
	StaticDmy,		/* 25 */
	StaticDmy,		/* 26 */
	StaticDmy,		/* 27 */
	StaticDmy,		/* 28 */
	StaticDmy,		/* 29 */
	StaticDmy,		/* 2A */
	StaticDmy,		/* 2B */
	StaticDmy,		/* 2C */
	StaticDmy,		/* 2D */
	StaticDmy,		/* 2E */
	StaticDmy,		/* 2F */

//--------- IIF by @Tny 2008/08/26 ------------
#if false	// EXTERNAL IIF NEW	Del 2010.09.01 by @Tny
	GD2_Send_30,	/* 30 */
#else
	StaticDmy,		/* 30 */
#endif
//--------------------------------------------
	StaticDmy,		/* 31 */
	StaticDmy,		/* 32 */
	StaticDmy,		/* 33 */
	StaticDmy,		/* 34 */
	StaticDmy,		/* 35 */
	StaticDmy,		/* 36 */
	StaticDmy,		/* 37 */
	StaticDmy,		/* 38 */
	StaticDmy,		/* 39 */
	StaticDmy,		/* 3A */
	StaticDmy,		/* 3B */
	StaticDmy,		/* 3C */
	StaticDmy,		/* 3D */
	StaticDmy,		/* 3E */
	StaticDmy,		/* 3F */

	StaticDmy,		/* 40 */
	StaticDmy,		/* 41 */
	StaticDmy,		/* 42 */
	StaticDmy,		/* 43 */
	StaticDmy,		/* 44 */
	StaticDmy,		/* 45 */
	StaticDmy,		/* 46 */
	StaticDmy,		/* 47 */
	StaticDmy,		/* 48 */
	StaticDmy,		/* 49 */
	StaticDmy,		/* 4A */
	StaticDmy,		/* 4B */
	StaticDmy,		/* 4C */
	StaticDmy,		/* 4D */
	StaticDmy,		/* 4E */
	StaticDmy,		/* 4F */

	StaticDmy,		/* 50 */
	StaticDmy,		/* 51 */
	StaticDmy,		/* 52 */
	StaticDmy,		/* 53 */
	StaticDmy,		/* 54 */
	StaticDmy,		/* 55 */
	StaticDmy,		/* 56 */
	StaticDmy,		/* 57 */
	StaticDmy,		/* 58 */
	StaticDmy,		/* 59 */
	StaticDmy,		/* 5A */
	StaticDmy,		/* 5B */
	StaticDmy,		/* 5C */
	StaticDmy,		/* 5D */
	StaticDmy,		/* 5E */
	StaticDmy,		/* 5F */

	StaticDmy,		/* 60 */
	StaticDmy,		/* 61 */
	StaticDmy,		/* 62 */
	StaticDmy,		/* 63 */
	StaticDmy,		/* 64 */
	StaticDmy,		/* 65 */
	StaticDmy,		/* 66 */
	StaticDmy,		/* 67 */
	StaticDmy,		/* 68 */
	StaticDmy,		/* 69 */
	StaticDmy,		/* 6A */
	StaticDmy,		/* 6B */
	StaticDmy,		/* 6C */
	StaticDmy,		/* 6D */
	StaticDmy,		/* 6E */
	StaticDmy,		/* 6F */

	StaticDmy,		/* 70 */
	StaticDmy,		/* 71 */
	StaticDmy,		/* 72 */
	StaticDmy,		/* 73 */
	StaticDmy,		/* 74 */
	StaticDmy,		/* 75 */
	StaticDmy,		/* 76 */
	StaticDmy,		/* 77 */
	StaticDmy,		/* 78 */
	StaticDmy,		/* 79 */
	StaticDmy,		/* 7A */
	StaticDmy,		/* 7B */
	StaticDmy,		/* 7C */
	StaticDmy,		/* 7D */
	StaticDmy,		/* 7E */
	StaticDmy,		/* 7F */

	StaticDmy,		/* 80 */
	StaticDmy,		/* 81 */
	StaticDmy,		/* 82 */
	StaticDmy,		/* 83 */
	StaticDmy,		/* 84 */
	StaticDmy,		/* 85 */
	StaticDmy,		/* 86 */
	StaticDmy,		/* 87 */
	StaticDmy,		/* 88 */
	StaticDmy,		/* 89 */
	StaticDmy,		/* 8A */
	StaticDmy,		/* 8B */
	StaticDmy,		/* 8C */
	StaticDmy,		/* 8D */
	StaticDmy,		/* 8E */
	StaticDmy,		/* 8F */

	StaticDmy,		/* 90 */
	StaticDmy,		/* 91 */
	StaticDmy,		/* 92 */
	StaticDmy,		/* 93 */
	StaticDmy,		/* 94 */
	StaticDmy,		/* 95 */
	StaticDmy,		/* 96 */
	StaticDmy,		/* 97 */
	StaticDmy,		/* 98 */
	StaticDmy,		/* 99 */
	StaticDmy,		/* 9A */
	StaticDmy,		/* 9B */
	StaticDmy,		/* 9C */
	StaticDmy,		/* 9D */
	StaticDmy,		/* 9E */
	StaticDmy,		/* 9F */

	StaticDmy,		/* A0 */
	GD2_Send_A1,	/* A1 */
	GD2_Send_A2,	/* A2 */
	StaticDmy,		/* A3 */
	StaticDmy,		/* A4 */
	StaticDmy,		/* A5 */
	StaticDmy,		/* A6 */
	StaticDmy,		/* A7 */
	StaticDmy,		/* A8 */
	StaticDmy,		/* A9 */
	StaticDmy,		/* AA */
	StaticDmy,		/* AB */
	StaticDmy,		/* AC */
	StaticDmy,		/* AD */
	StaticDmy,		/* AE */
	StaticDmy,		/* AF */

	StaticDmy,		/* B0 */
	GD2_Send_B1,	/* B1 */
	GD2_Send_B2,	/* B2 */
	GD2_Send_B3,	/* B3 */
	StaticDmy,		/* B4 */
	StaticDmy,		/* B5 */
	StaticDmy,		/* B6 */
	StaticDmy,		/* B7 */
	StaticDmy,		/* B8 */
	StaticDmy,		/* B9 */
	StaticDmy,		/* BA */
	StaticDmy,		/* BB */
	StaticDmy,		/* BC */
	StaticDmy,		/* BD */
	StaticDmy,		/* BE */
	StaticDmy,		/* BF */

	StaticDmy,		/* C0 */
	GD2_Send_C1,	/* C1 */
	GD2_Send_C2,	/* C2 */
	GD2_Send_C3,	/* C3 */
	GD2_Send_C4,	/* C4 */
	GD2_Send_C5,	/* C5 */
	StaticDmy,		/* C6 */
	StaticDmy,		/* C7 */
	StaticDmy,		/* C8 */
	StaticDmy,		/* C9 */
	StaticDmy,		/* CA */
	StaticDmy,		/* CB */
	StaticDmy,		/* CC */
	StaticDmy,		/* CD */
	StaticDmy,		/* CE */
	StaticDmy,		/* CF */

	StaticDmy,		/* D0 */
	GD2_Send_D1,	/* D1 */
	GD2_Send_D2,	/* D2 */
	StaticDmy,		/* D3 */
	StaticDmy,		/* D4 */
	StaticDmy,		/* D5 */
	StaticDmy,		/* D6 */
	StaticDmy,		/* D7 */
	StaticDmy,		/* D8 */
	StaticDmy,		/* D9 */
	StaticDmy,		/* DA */
	StaticDmy,		/* DB */
	StaticDmy,		/* DC */
	StaticDmy,		/* DD */
	StaticDmy,		/* DE */
	StaticDmy,		/* DF */

	StaticDmy,		/* E0 */
	GD2_Send_E1,	/* E1 */
	GD2_Send_E2,	/* E2 */
	GD2_Send_E3,	/* E3 2008.12.01*/
	StaticDmy,		/* E4 */
	StaticDmy,		/* E5 */
	StaticDmy,		/* E6 */
	StaticDmy,		/* E7 */
	StaticDmy,		/* E8 */
	StaticDmy,		/* E9 */
	StaticDmy,		/* EA */
	StaticDmy,		/* EB */
	StaticDmy,		/* EC */
	StaticDmy,		/* ED */
	StaticDmy,		/* EE */
	StaticDmy,		/* EF */

	StaticDmy,		/* F0 */
	StaticDmy,		/* F1 */
	StaticDmy,		/* F2 */
	StaticDmy,		/* F3 */
	StaticDmy,		/* F4 */
	StaticDmy,		/* F5 */
	StaticDmy,		/* F6 */
	StaticDmy,		/* F7 */
	StaticDmy,		/* F8 */
	StaticDmy,		/* F9 */
	StaticDmy,		/* FA */
	StaticDmy,		/* FB */
	StaticDmy,		/* FC */
	StaticDmy,		/* FD */
	StaticDmy,		/* FE */
	StaticDmy		/* FF */

} ;


/* ÉäÉÇÉRÉìÅ®ónê⁄ã@ ÉRÉ}ÉìÉh */
extern unsigned char (*FromREMO[ 256 ])( void ) = {
	StaticDmy,		/* 00 */
	StaticDmy,		/* 01 */
	StaticDmy,		/* 02 */
	StaticDmy,		/* 03 */
	StaticDmy,		/* 04 */
	StaticDmy,		/* 05 */
	StaticDmy,		/* 06 */
	StaticDmy,		/* 07 */
	StaticDmy,		/* 08 */
	StaticDmy,		/* 09 */
	StaticDmy,		/* 0A */
	StaticDmy,		/* 0B */
	StaticDmy,		/* 0C */
	StaticDmy,		/* 0D */
	StaticDmy,		/* 0E */
	StaticDmy,		/* 0F */

	StaticDmy,		/* 10 */
	REMO_Recv_11,	/* 11 */	// 2019.09.02
	REMO_Recv_12,	/* 12 */	// 2019.09.02
	StaticDmy,		/* 13 */
	StaticDmy,		/* 14 */
	StaticDmy,		/* 15 */
	StaticDmy,		/* 16 */
	StaticDmy,		/* 17 */
	StaticDmy,		/* 18 */
	StaticDmy,		/* 19 */
	StaticDmy,		/* 1A */
	StaticDmy,		/* 1B */
	StaticDmy,		/* 1C */
	StaticDmy,		/* 1D */
	StaticDmy,		/* 1E */
	StaticDmy,		/* 1F */

	REMO_Recv_20,	/* 20 */	// 2019.09.02
	StaticDmy,		/* 21 */
	StaticDmy,		/* 22 */
	StaticDmy,		/* 23 */
	StaticDmy,		/* 24 */
	StaticDmy,		/* 25 */
	StaticDmy,		/* 26 */
	StaticDmy,		/* 27 */
	StaticDmy,		/* 28 */
	StaticDmy,		/* 29 */
	StaticDmy,		/* 2A */
	StaticDmy,		/* 2B */
	StaticDmy,		/* 2C */
	StaticDmy,		/* 2D */
	StaticDmy,		/* 2E */
	StaticDmy,		/* 2F */

	REMO_Recv_30,	/* 30 */	// 2019.09.02
	REMO_Recv_31,	/* 31 */	// 2019.09.02
	REMO_Recv_32,	/* 32 */	// 2019.09.02
	StaticDmy,		/* 33 */
	StaticDmy,		/* 34 */
	StaticDmy,		/* 35 */
	StaticDmy,		/* 36 */
	StaticDmy,		/* 37 */
	StaticDmy,		/* 38 */
	StaticDmy,		/* 39 */
	StaticDmy,		/* 3A */
	StaticDmy,		/* 3B */
	StaticDmy,		/* 3C */
	StaticDmy,		/* 3D */
	StaticDmy,		/* 3E */
	StaticDmy,		/* 3F */

	REMO_Recv_40,	/* 40 */	// 2019.09.02
	REMO_Recv_41,  	/* 41 */	// 2019.09.02
	StaticDmy,  	/* 42 */
	StaticDmy,		/* 43 */
	StaticDmy,		/* 44 */
	StaticDmy,		/* 45 */
	StaticDmy,		/* 46 */
	StaticDmy,      /* 47 */
	StaticDmy,      /* 48 */
	StaticDmy,      /* 49 */
	StaticDmy,      /* 4A */
	StaticDmy,		/* 4B */
	StaticDmy,		/* 4C */
	StaticDmy,		/* 4D */
	StaticDmy,		/* 4E */
	StaticDmy,      /* 4F */

	REMO_Recv_50,	/* 50 */	// 2019.09.02
	REMO_Recv_51,	/* 51 */	// 2019.09.02
	REMO_Recv_52,   /* 52 */	// 2019.09.02
	StaticDmy,      /* 53 */
	StaticDmy,		/* 54 */
	StaticDmy,		/* 55 */
	StaticDmy,		/* 56 */
	StaticDmy,		/* 57 */
	StaticDmy,		/* 58 */
	StaticDmy,		/* 59 */
	StaticDmy,		/* 5A */
	StaticDmy,		/* 5B */
	StaticDmy,		/* 5C */
	StaticDmy,		/* 5D */
	StaticDmy,		/* 5E */
	StaticDmy,		/* 5F */

	REMO_Recv_60,	/* 60 */	// 2019.09.02
	REMO_Recv_61,   /* 61 */	// 2019.09.02
	StaticDmy,      /* 62 */
	StaticDmy,      /* 63 */
	StaticDmy,      /* 64 */
	StaticDmy,		/* 65 */
	StaticDmy,		/* 66 */
	StaticDmy,      /* 67 */
	StaticDmy,      /* 68 */
	StaticDmy,		/* 69 */
	StaticDmy,		/* 6A */
	StaticDmy,		/* 6B */
    StaticDmy,      /* 6C */
	StaticDmy,		/* 6D */
	StaticDmy,		/* 6E */
	StaticDmy,		/* 6F */

	StaticDmy,		/* 70 */
	StaticDmy,      /* 71 */
	StaticDmy,		/* 72 */
	StaticDmy,		/* 73 */
	StaticDmy,		/* 74 */
	StaticDmy,		/* 75 */
	StaticDmy,		/* 76 */
	StaticDmy,		/* 77 */
	StaticDmy,		/* 78 */
	StaticDmy,		/* 79 */
	StaticDmy,		/* 7A */
	StaticDmy,		/* 7B */
	StaticDmy,		/* 7C */
	StaticDmy,		/* 7D */
	StaticDmy,		/* 7E */
	StaticDmy,		/* 7F */

    REMO_Recv_80,	/* 80 */
	REMO_Recv_81,	/* 81 */
	REMO_Recv_82,	/* 82 */
	REMO_Recv_83,	/* 83 */
	REMO_Recv_84,	/* 84 */
	StaticDmy,   	/* 85 */
	StaticDmy,      /* 86 */
	StaticDmy,      /* 87 */
    StaticDmy,      /* 88 */
	StaticDmy,      /* 89 */
	REMO_Recv_8A,	/* 8A */
	REMO_Recv_8B,	/* 8B */
	REMO_Recv_8C,	/* 8C */
	StaticDmy,		/* 8D */
	StaticDmy,		/* 8E */
	StaticDmy,		/* 8F */

	//REMO_Recv_90,	/* 90 */    // FRAM(Phase2) 2008/09/02 @Tny		BP4 Phase13 by @Tny 2009.02.23
	//REMO_Recv_91,	/* 91 */    // FRAM(Phase2) 2008/09/02 @Tny		BP4 Phase13 by @Tny 2009.02.23
	StaticDmy,		/* 90 */
	StaticDmy,		/* 91 */
	StaticDmy,		/* 92 */
	StaticDmy,		/* 93 */
	StaticDmy,		/* 94 */
	StaticDmy,		/* 95 */
	StaticDmy,		/* 96 */
	StaticDmy,		/* 97 */
	StaticDmy,		/* 98 */
	StaticDmy,		/* 99 */
	StaticDmy,		/* 9A */
	StaticDmy,		/* 9B */
	StaticDmy,		/* 9C */
	StaticDmy,		/* 9D */
	StaticDmy,		/* 9E */
	StaticDmy,		/* 9F */

	StaticDmy,		/* A0 */
	REMO_Recv_A1,	/* A1 2009.01.09*/
	StaticDmy,		/* A2 */
	StaticDmy,		/* A3 */
	StaticDmy,		/* A4 */
	StaticDmy,		/* A5 */
	StaticDmy,		/* A6 */
	StaticDmy,		/* A7 */
	StaticDmy,		/* A8 */
	StaticDmy,		/* A9 */
	StaticDmy,		/* AA */
	StaticDmy,		/* AB */
	StaticDmy,		/* AC */
	StaticDmy,		/* AD */
	StaticDmy,		/* AE */
	StaticDmy,		/* AF */

	StaticDmy,		/* B0 */
	StaticDmy,		/* B1 */
	StaticDmy,		/* B2 */
	StaticDmy,		/* B3 */
	StaticDmy,		/* B4 */
	StaticDmy,		/* B5 */
	StaticDmy,		/* B6 */
	StaticDmy,		/* B7 */
	StaticDmy,		/* B8 */
	StaticDmy,		/* B9 */
	StaticDmy,		/* BA */
	StaticDmy,		/* BB */
	StaticDmy,		/* BC */
	StaticDmy,		/* BD */
	StaticDmy,		/* BE */
	StaticDmy,		/* BF */

	StaticDmy,		/* C0 */
	StaticDmy,		/* C1 */
	StaticDmy,		/* C2 */
	StaticDmy,		/* C3 */
	StaticDmy,		/* C4 */
	StaticDmy,		/* C5 */
	StaticDmy,		/* C6 */
	StaticDmy,		/* C7 */
	StaticDmy,		/* C8 */
	StaticDmy,		/* C9 */
	StaticDmy,		/* CA */
	StaticDmy,		/* CB */
	StaticDmy,		/* CC */
	StaticDmy,		/* CD */
	StaticDmy,		/* CE */
	StaticDmy,		/* CF */

	StaticDmy,		/* D0 */
	StaticDmy,		/* D1 */
	StaticDmy,		/* D2 */
	StaticDmy,		/* D3 */
	StaticDmy,		/* D4 */
	StaticDmy,		/* D5 */
	StaticDmy,		/* D6 */
	StaticDmy,		/* D7 */
	StaticDmy,		/* D8 */
	StaticDmy,		/* D9 */
	StaticDmy,		/* DA */
	StaticDmy,		/* DB */
	StaticDmy,		/* DC */
	StaticDmy,		/* DD */
	StaticDmy,		/* DE */
	StaticDmy,		/* DF */

	StaticDmy,		/* E0 */
	StaticDmy,		/* E1 */
	StaticDmy,		/* E2 */
	StaticDmy,		/* E3 */
	StaticDmy,		/* E4 */
	StaticDmy,		/* E5 */
	StaticDmy,		/* E6 */
	StaticDmy,		/* E7 */
	StaticDmy,		/* E8 */
	StaticDmy,		/* E9 */
	StaticDmy,		/* EA */
	StaticDmy,		/* EB */
	StaticDmy,		/* EC */
	StaticDmy,		/* ED */
	StaticDmy,		/* EE */
	StaticDmy,		/* EF */

	StaticDmy,		/* F0 */
	StaticDmy,		/* F1 */
	StaticDmy,		/* F2 */
	StaticDmy,		/* F3 */
	StaticDmy,		/* F4 */
	StaticDmy,		/* F5 */
	StaticDmy,		/* F6 */
	StaticDmy,		/* F7 */
	StaticDmy,		/* F8 */
	StaticDmy,		/* F9 */
	StaticDmy,		/* FA */
	StaticDmy,		/* FB */
	StaticDmy,		/* FC */
	StaticDmy,		/* FD */
	StaticDmy,		/* FE */
	StaticDmy,		/* FF */

} ;

/* ónê⁄ã@Å®ÇfÇcÇQ */
extern unsigned char (*ToREMO[ 256 ])( void ) = {
	StaticDmy,		/* 00 */
	StaticDmy,		/* 01 */
	StaticDmy,		/* 02 */
	StaticDmy,		/* 03 */
	StaticDmy,		/* 04 */
	StaticDmy,		/* 05 */
	StaticDmy,		/* 06 */
	StaticDmy,		/* 07 */
	StaticDmy,		/* 08 */
	StaticDmy,		/* 09 */
	StaticDmy,		/* 0A */
	StaticDmy,		/* 0B */
	StaticDmy,		/* 0C */
	StaticDmy,		/* 0D */
	StaticDmy,		/* 0E */
	StaticDmy,		/* 0F */

	StaticDmy,		/* 10 */
	REMO_Send_11,	/* 11 */
	REMO_Send_12,	/* 12 */
	REMO_Send_13,	/* 13 */
	StaticDmy,		/* 14 */
	REMO_Send_15,	/* 15 */
	REMO_Send_16,	/* 16 */
	StaticDmy,		/* 17 */
	StaticDmy,		/* 18 */
	StaticDmy,		/* 19 */
	StaticDmy,		/* 1A */
	StaticDmy,		/* 1B */
	StaticDmy,		/* 1C */
	StaticDmy,		/* 1D */
	StaticDmy,		/* 1E */
	StaticDmy,		/* 1F */

	REMO_Send_20,	/* 20 */
	REMO_Send_21,	/* 21 */
	REMO_Send_22,	/* 22 */
	REMO_Send_23,	/* 23 */
	REMO_Send_24,	/* 24 */
	StaticDmy,		/* 25 */
	StaticDmy,		/* 26 */
	StaticDmy,		/* 27 */
	StaticDmy,		/* 28 */
	StaticDmy,		/* 29 */
	StaticDmy,		/* 2A */
	StaticDmy,		/* 2B */
	StaticDmy,		/* 2C */
	StaticDmy,		/* 2D */
	StaticDmy,		/* 2E */
	StaticDmy,		/* 2F */

	//REMO_Send_30,	/* 30 */
	//REMO_Send_31,	/* 31 */
	StaticDmy,		/* 30 2009.03.16 del*/
	StaticDmy,		/* 31 2009.03.16 del*/
	REMO_Send_32,	/* 32 */
	REMO_Send_33,	/* 33 */	// Phase31 by @Tny 2008.11.25
	REMO_Send_34,	/* 34 2009.01.09*/
	REMO_Send_35,	/* 35 2009.01.09*/
	REMO_Send_36,	/* 36 2009.01.09*/
	REMO_Send_37,	/* 37 2009.01.09*/
	REMO_Send_38,	/* 38 2009.01.09*/
	REMO_Send_39,	/* 39 2009.01.09*/
	StaticDmy,		/* 3A */
	StaticDmy,		/* 3B */
	StaticDmy,		/* 3C */
	StaticDmy,		/* 3D */
	StaticDmy,		/* 3E */
	StaticDmy,		/* 3F */

	StaticDmy,		/* 40 */
	StaticDmy,		/* 41 */
	StaticDmy,		/* 42 */
	StaticDmy,		/* 43 */
	StaticDmy,		/* 44 */
	StaticDmy,		/* 45 */
	StaticDmy,		/* 46 */
	StaticDmy,		/* 47 */
	StaticDmy,		/* 48 */
	StaticDmy,		/* 49 */
	StaticDmy,		/* 4A */
	StaticDmy,		/* 4B */
	StaticDmy,		/* 4C */
	StaticDmy,		/* 4D */
	StaticDmy,		/* 4E */
	StaticDmy,		/* 4F */

	StaticDmy,		/* 50 */
	StaticDmy,		/* 51 */
	StaticDmy,		/* 52 */
	StaticDmy,		/* 53 */
	StaticDmy,		/* 54 */
	StaticDmy,		/* 55 */
	StaticDmy,		/* 56 */
	StaticDmy,		/* 57 */
	StaticDmy,		/* 58 */
	StaticDmy,		/* 59 */
	StaticDmy,		/* 5A */
	StaticDmy,		/* 5B */
	StaticDmy,		/* 5C */
	StaticDmy,		/* 5D */
	StaticDmy,		/* 5E */
	StaticDmy,		/* 5F */

	StaticDmy,		/* 60 */
	StaticDmy,		/* 61 */
	StaticDmy,		/* 62 */
	StaticDmy,		/* 63 */
	StaticDmy,		/* 64 */
	StaticDmy,		/* 65 */
	StaticDmy,		/* 66 */
	StaticDmy,		/* 67 */
	StaticDmy,		/* 68 */
	StaticDmy,		/* 69 */
	StaticDmy,		/* 6A */
	StaticDmy,		/* 6B */
	StaticDmy,		/* 6C */
	StaticDmy,		/* 6D */
	StaticDmy,		/* 6E */
	StaticDmy,		/* 6F */

	StaticDmy,		/* 70 */
	StaticDmy,		/* 71 */
	StaticDmy,		/* 72 */
	StaticDmy,		/* 73 */
	StaticDmy,		/* 74 */
	StaticDmy,		/* 75 */
	StaticDmy,		/* 76 */
	StaticDmy,		/* 77 */
	StaticDmy,		/* 78 */
	StaticDmy,		/* 79 */
	StaticDmy,		/* 7A */
	StaticDmy,		/* 7B */
	StaticDmy,		/* 7C */
	StaticDmy,		/* 7D */
	StaticDmy,		/* 7E */
	StaticDmy,		/* 7F */

	StaticDmy,		/* 80 */
	StaticDmy,		/* 81 */
	StaticDmy,		/* 82 */
	StaticDmy,		/* 83 */
	StaticDmy,		/* 84 */
	StaticDmy,		/* 85 */
	StaticDmy,		/* 86 */
	StaticDmy,		/* 87 */
	StaticDmy,		/* 88 */
	StaticDmy,		/* 89 */
	StaticDmy,		/* 8A */
	StaticDmy,		/* 8B */
	StaticDmy,		/* 8C */
	StaticDmy,		/* 8D */
	StaticDmy,		/* 8E */
	StaticDmy,		/* 8F */

	StaticDmy,		/* 90 */
	REMO_Send_91,	/* 91 */	// 2019.09.02
	REMO_Send_92,	/* 92 */	// 2019.09.02
	StaticDmy,		/* 93 */
	StaticDmy,		/* 94 */
	StaticDmy,		/* 95 */
	StaticDmy,		/* 96 */
	StaticDmy,		/* 97 */
	StaticDmy,		/* 98 */
	StaticDmy,		/* 99 */
	StaticDmy,		/* 9A */
	StaticDmy,		/* 9B */
	StaticDmy,		/* 9C */
	StaticDmy,		/* 9D */
	StaticDmy,		/* 9E */
	StaticDmy,		/* 9F */

	REMO_Send_A0,	/* A0 */	// 2019.09.02
	REMO_Send_A1,   /* A1 */	// 2019.09.02
	REMO_Send_A2,   /* A2 */	// 2019.09.02
	StaticDmy,		/* A3 */
	StaticDmy,		/* A4 */
	StaticDmy,		/* A5 */
	StaticDmy,		/* A6 */
	StaticDmy,		/* A7 */
	StaticDmy,		/* A8 */
	StaticDmy,		/* A9 */
	StaticDmy,		/* AA */
	StaticDmy,		/* AB */
	StaticDmy,		/* AC */
	StaticDmy,		/* AD */
	StaticDmy,		/* AE */
	StaticDmy,		/* AF */

	REMO_Send_B0,	/* B0 */	// 2019.09.02
	StaticDmy,      /* B1 */
	StaticDmy,      /* B2 */
	StaticDmy,      /* B3 */
	StaticDmy,		/* B4 */
	StaticDmy,		/* B5 */
	StaticDmy,		/* B6 */
	StaticDmy,		/* B7 */
	StaticDmy,		/* B8 */
	StaticDmy,		/* B9 */
	StaticDmy,		/* BA */
	StaticDmy,		/* BB */
	StaticDmy,		/* BC */
	StaticDmy,		/* BD */
	StaticDmy,		/* BE */
	StaticDmy,		/* BF */

	REMO_Send_C0,	/* C0 */	// 2019.09.02
	StaticDmy,      /* C1 */
	StaticDmy,      /* C2 */
	StaticDmy,      /* C3 */
	StaticDmy,      /* C4 */
	StaticDmy,      /* C5 */
	StaticDmy,		/* C6 */
	StaticDmy,		/* C7 */
	StaticDmy,		/* C8 */
	StaticDmy,		/* C9 */
	StaticDmy,		/* CA */
	StaticDmy,		/* CB */
	StaticDmy,		/* CC */
	StaticDmy,		/* CD */
	StaticDmy,		/* CE */
	StaticDmy,		/* CF */

	StaticDmy,		/* D0 */
	StaticDmy,      /* D1 */
	StaticDmy,      /* D2 */
	StaticDmy,		/* D3 */
	StaticDmy,		/* D4 */
	StaticDmy,		/* D5 */
	StaticDmy,		/* D6 */
	StaticDmy,		/* D7 */
	StaticDmy,		/* D8 */
	StaticDmy,		/* D9 */
	StaticDmy,		/* DA */
	StaticDmy,		/* DB */
	StaticDmy,		/* DC */
	StaticDmy,		/* DD */
	StaticDmy,		/* DE */
	StaticDmy,		/* DF */

	StaticDmy,		/* E0 */
	StaticDmy,      /* E1 */
	StaticDmy,      /* E2 */
	StaticDmy,		/* E3 */
	StaticDmy,		/* E4 */
	StaticDmy,		/* E5 */
	StaticDmy,		/* E6 */
	StaticDmy,		/* E7 */
	StaticDmy,		/* E8 */
	StaticDmy,		/* E9 */
	StaticDmy,		/* EA */
	StaticDmy,		/* EB */
	StaticDmy,		/* EC */
	StaticDmy,		/* ED */
	StaticDmy,		/* EE */
	StaticDmy,		/* EF */

	StaticDmy,		/* F0 */
	StaticDmy,		/* F1 */
	StaticDmy,		/* F2 */
	StaticDmy,		/* F3 */
	StaticDmy,		/* F4 */
	StaticDmy,		/* F5 */
	StaticDmy,		/* F6 */
	StaticDmy,		/* F7 */
	StaticDmy,		/* F8 */
	StaticDmy,		/* F9 */
	StaticDmy,		/* FA */
	StaticDmy,		/* FB */
	StaticDmy,		/* FC */
	StaticDmy,		/* FD */
	StaticDmy,		/* FE */
	StaticDmy		/* FF */

} ;


#if true // Å´ EXTERNAL IIF NEW	2011.02.21 by @Tny
/* ÇhÇhÇeÅ®ónê⁄ã@ ÉRÉ}ÉìÉh */
extern unsigned char (*FromIIF[ 192 ])( void ) = {
	StaticDmy,		// 00
	StaticDmy,		// 01
	StaticDmy,		// 02
	StaticDmy,		// 03
	StaticDmy,		// 04
	StaticDmy,		// 05
	StaticDmy,		// 06
	StaticDmy,		// 07
	StaticDmy,		// 08
	StaticDmy,		// 09
	StaticDmy,		// 0A
	StaticDmy,		// 0B
	StaticDmy,		// 0C
	StaticDmy,		// 0D
	StaticDmy,		// 0E
	StaticDmy,		// 0F

	StaticDmy,		// 10
	StaticDmy,		// 11
	StaticDmy,		// 12
	StaticDmy,		// 13
	StaticDmy,		// 14
	StaticDmy,		// 15
	StaticDmy,		// 16
	StaticDmy,		// 17
	StaticDmy,		// 18
	StaticDmy,		// 19
	StaticDmy,		// 1A
	StaticDmy,		// 1B
	StaticDmy,		// 1C
	StaticDmy,		// 1D
	StaticDmy,		// 1E
	StaticDmy,		// 1F

	StaticDmy,		// 20
	StaticDmy,		// 21
	StaticDmy,		// 22
	StaticDmy,		// 23
	StaticDmy,		// 24
	StaticDmy,		// 25
	StaticDmy,		// 26
	StaticDmy,		// 27
	StaticDmy,		// 28
	StaticDmy,		// 29
	StaticDmy,		// 2A
	StaticDmy,		// 2B
	StaticDmy,		// 2C
	StaticDmy,		// 2D
	StaticDmy,		// 2E
	StaticDmy,		// 2F

	StaticDmy,		// 30
	StaticDmy,		// 31
	StaticDmy,		// 32
	StaticDmy,		// 33
	StaticDmy,		// 34
	StaticDmy,		// 35
	StaticDmy,		// 36
	StaticDmy,		// 37
	StaticDmy,		// 38
	StaticDmy,		// 39
	StaticDmy,		// 3A
	StaticDmy,		// 3B
	StaticDmy,		// 3C
	StaticDmy,		// 3D
	StaticDmy,		// 3E
	StaticDmy,		// 3F

	StaticDmy,		// 40
	StaticDmy,	    // 41
	StaticDmy,	    // 42
	StaticDmy,		// 43
	StaticDmy,		// 44
	StaticDmy,		// 45
	StaticDmy,		// 46
	StaticDmy,      // 47
	StaticDmy,      // 48
	StaticDmy,      // 49
	StaticDmy,      // 4A
	StaticDmy,		// 4B
	StaticDmy,		// 4C
	StaticDmy,		// 4D
	StaticDmy,		// 4E
	StaticDmy,      // 4F

	StaticDmy,		// 50
	StaticDmy,		// 51
	StaticDmy,      // 52
	StaticDmy,      // 53
	StaticDmy,		// 54
	StaticDmy,		// 55
	StaticDmy,		// 56
	StaticDmy,		// 57
	StaticDmy,		// 58
	StaticDmy,		// 59
	StaticDmy,		// 5A
	StaticDmy,		// 5B
	StaticDmy,		// 5C
	StaticDmy,		// 5D
	StaticDmy,		// 5E
	StaticDmy,		// 5F

	StaticDmy,		// 60
	StaticDmy,      // 61
	StaticDmy,      // 62
	StaticDmy,      // 63
	StaticDmy,      // 64
	StaticDmy,		// 65
	StaticDmy,		// 66
	StaticDmy,      // 67
	StaticDmy,      // 68
	StaticDmy,		// 69
	StaticDmy,		// 6A
	StaticDmy,		// 6B
    StaticDmy,      // 6C
	StaticDmy,		// 6D
	StaticDmy,		// 6E
	StaticDmy,		// 6F

	StaticDmy,		// 70
	StaticDmy,      // 71
	StaticDmy,		// 72
	StaticDmy,		// 73
	StaticDmy,		// 74
	StaticDmy,		// 75
	StaticDmy,		// 76
	StaticDmy,		// 77
	StaticDmy,		// 78
	StaticDmy,		// 79
	StaticDmy,		// 7A
	StaticDmy,		// 7B
	StaticDmy,		// 7C
	StaticDmy,		// 7D
	StaticDmy,		// 7E
	StaticDmy,		// 7F

    StaticDmy,		// 80
	IIF_Recv_81,	// 81
	IIF_Recv_82,	// 82
	IIF_Recv_83,	// 83
	IIF_Recv_84,	// 84
	IIF_Recv_85,	// 85
	IIF_Recv_86,	// 86
	IIF_Recv_87,    // 87	// Å© EXTERNAL IIF NEW	2010.09.01 by @Tny
	StaticDmy,      // 88
	StaticDmy,      // 89
	IIF_Recv_8A,	// 8A
	IIF_Recv_8B,	// 8B
	IIF_Recv_8C,	// 8C
	IIF_Recv_8D,	// 8D
	StaticDmy,      // 8E
	StaticDmy,		// 8F

	StaticDmy,		// 90
	StaticDmy,		// 91
	StaticDmy,		// 92
	StaticDmy,		// 93
	StaticDmy,		// 94
	StaticDmy,		// 95
	StaticDmy,		// 96
	StaticDmy,		// 97
	StaticDmy,		// 98
	StaticDmy,		// 99
	StaticDmy,		// 9A
	StaticDmy,		// 9B
	StaticDmy,		// 9C
	StaticDmy,		// 9D
	StaticDmy,		// 9E
	StaticDmy,		// 9F

	IIF_Recv_A0,    // A0
	IIF_Recv_A1,    // A1
	IIF_Recv_A2,    // A2
	IIF_Recv_A3,    // A3
	IIF_Recv_A4,    // A4
	IIF_Recv_A5,    // A5
	IIF_Recv_A6,    // A6
	IIF_Recv_A7,    // A7
	IIF_Recv_A8,    // A8
	IIF_Recv_A9,	// A9
	IIF_Recv_AA,	// AA
	IIF_Recv_AB,	// AB
	StaticDmy,		// AC
	StaticDmy,		// AD
	StaticDmy,		// AE
	StaticDmy,		// AF

	IIF_Recv_B0,    // B0
	IIF_Recv_B1,    // B1
	IIF_Recv_B2,    // B2
	IIF_Recv_B3,    // B3
	IIF_Recv_B4,    // B4
	IIF_Recv_B5,    // B5
	IIF_Recv_B6,	// B6
	StaticDmy,		// B7
	StaticDmy,		// B8
	StaticDmy,		// B9
	StaticDmy,		// BA
	StaticDmy,		// BB
	StaticDmy,		// BC
	StaticDmy,		// BD
	StaticDmy,		// BE
	StaticDmy,		// BF

//	StaticDmy,		// C0
//	StaticDmy,		// C1
//	StaticDmy,		// C2
//	StaticDmy,		// C3
//	StaticDmy,		// C4
//	StaticDmy,		// C5
//	StaticDmy,		// C6
//	StaticDmy,		// C7
//	StaticDmy,		// C8
//	StaticDmy,		// C9
//	StaticDmy,		// CA
//	StaticDmy,		// CB
//	StaticDmy,		// CC
//	StaticDmy,		// CD
//	StaticDmy,		// CE
//	StaticDmy,		// CF

//	StaticDmy,		// D0
//	StaticDmy,		// D1
//	StaticDmy,		// D2
//	StaticDmy,		// D3
//	StaticDmy,		// D4
//	StaticDmy,		// D5
//	StaticDmy,		// D6
//	StaticDmy,		// D7
//	StaticDmy,		// D8
//	StaticDmy,		// D9
//	StaticDmy,		// DA
//	StaticDmy,		// DB
//	StaticDmy,		// DC
//	StaticDmy,		// DD
//	StaticDmy,		// DE
//	StaticDmy,		// DF

//	StaticDmy,		// E0
//	StaticDmy,		// E1
//	StaticDmy,		// E2
//	StaticDmy,		// E3
//	StaticDmy,		// E4
//	StaticDmy,		// E5
//	StaticDmy,		// E6
//	StaticDmy,		// E7
//	StaticDmy,		// E8
//	StaticDmy,		// E9
//	StaticDmy,		// EA
//	StaticDmy,		// EB
//	StaticDmy,		// EC
//	StaticDmy,		// ED
//	StaticDmy,		// EE
//	StaticDmy,		// EF

//	StaticDmy,		// F0
//	StaticDmy,		// F1
//	StaticDmy,		// F2
//	StaticDmy,		// F3
//	StaticDmy,		// F4
//	StaticDmy,		// F5
//	StaticDmy,		// F6
//	StaticDmy,		// F7
//	StaticDmy,		// F8
//	StaticDmy,		// F9
//	StaticDmy,		// FA
//	StaticDmy,		// FB
//	StaticDmy,		// FC
//	StaticDmy,		// FD
//	StaticDmy,		// FE
//	StaticDmy,		// FF

} ;

/* ónê⁄ã@Å®ÇhÇhÇe */
extern unsigned char (*ToIIF[ 96 ])( void ) = { //ÉÅÉÇÉäè¡îÔÇîÇØÇÈÇΩÇﬂñ¢égópÉGÉäÉAï™çÌèú 256->96Ç…ïœçX
	StaticDmy,		// 00
	StaticDmy,		// 01
	StaticDmy,		// 02
	StaticDmy,		// 03
	StaticDmy,		// 04
	StaticDmy,		// 05
	StaticDmy,		// 06
	StaticDmy,		// 07
	StaticDmy,		// 08
	StaticDmy,		// 09
	StaticDmy,		// 0A
	StaticDmy,		// 0B
	StaticDmy,		// 0C
	StaticDmy,		// 0D
	StaticDmy,		// 0E
	StaticDmy,		// 0F

	StaticDmy,		// 10
	IIF_Send_11,   	// 11
	IIF_Send_12,	// 12
	IIF_Send_13,    // 13
	IIF_Send_14,	// 14
	IIF_Send_15,	// 15
	StaticDmy,		// 16
	StaticDmy,		// 17
	StaticDmy,		// 18
	StaticDmy,		// 19
	StaticDmy,		// 1A
	StaticDmy,		// 1B
	StaticDmy,		// 1C
	StaticDmy,		// 1D
	StaticDmy,		// 1E
	StaticDmy,		// 1F

	IIF_Send_20,	// 20 2009.11.04
	StaticDmy,      // 21
	StaticDmy,		// 22
	StaticDmy,		// 23
	StaticDmy,		// 24
	StaticDmy,		// 25
	StaticDmy,		// 26
	StaticDmy,		// 27
	StaticDmy,		// 28
	StaticDmy,		// 29
	StaticDmy,		// 2A
	StaticDmy,		// 2B
	StaticDmy,		// 2C
	StaticDmy,		// 2D
	StaticDmy,		// 2E
	StaticDmy,		// 2F

	StaticDmy,		// 30
	StaticDmy,		// 31
	StaticDmy,		// 32
	StaticDmy,		// 33
	StaticDmy,		// 34
	StaticDmy,		// 35
	StaticDmy,		// 36
	StaticDmy,		// 37
	StaticDmy,		// 38
	StaticDmy,		// 39
	StaticDmy,		// 3A
	StaticDmy,		// 3B
	StaticDmy,		// 3C
	StaticDmy,		// 3D
	StaticDmy,		// 3E
	StaticDmy,		// 3F

	IIF_Send_40,    // 40
	IIF_Send_41,    // 41
	IIF_Send_42,	// 42
	IIF_Send_43,    // 43
	IIF_Send_44,    // 44
	IIF_Send_45,    // 45
	StaticDmy,		// 46
	StaticDmy,		// 47
	StaticDmy,		// 48
	StaticDmy,		// 49
	StaticDmy,		// 4A
	StaticDmy,		// 4B
	StaticDmy,		// 4C
	StaticDmy,		// 4D
	StaticDmy,		// 4E
	StaticDmy,		// 4F

	IIF_Send_50,    // 50
	IIF_Send_51,	// 51
	IIF_Send_52,    // 52
	IIF_Send_53,    // 53
	IIF_Send_54,    // 54
	StaticDmy,		// 55
	StaticDmy,		// 56
	StaticDmy,		// 57
	StaticDmy,		// 58
	StaticDmy,		// 59
	StaticDmy,		// 5A
	StaticDmy,		// 5B
	StaticDmy,		// 5C
	StaticDmy,		// 5D
	StaticDmy,		// 5E
	StaticDmy,		// 5F

//  StaticDmy,		// 60
//  StaticDmy,		// 61
//  StaticDmy,		// 62
//  StaticDmy,		// 63
//  StaticDmy,		// 64
//  StaticDmy,		// 65
//  StaticDmy,		// 66
//  StaticDmy,		// 67
//  StaticDmy,		// 68
//  StaticDmy,		// 69
//  StaticDmy,		// 6A
//  StaticDmy,		// 6B
//  StaticDmy,		// 6C
//  StaticDmy,		// 6D
//  StaticDmy,		// 6E
//  StaticDmy,		// 6F

//  StaticDmy,		// 70
//  StaticDmy,		// 71
//  StaticDmy,		// 72
//  StaticDmy,		// 73
//  StaticDmy,		// 74
//  StaticDmy,		// 75
//  StaticDmy,		// 76
//  StaticDmy,		// 77
//  StaticDmy,		// 78
//  StaticDmy,		// 79
//  StaticDmy,		// 7A
//  StaticDmy,		// 7B
//  StaticDmy,		// 7C
//  StaticDmy,		// 7D
//  StaticDmy,		// 7E
//  StaticDmy,		// 7F

//	StaticDmy,		// 80
//	StaticDmy,		// 81
//	StaticDmy,		// 82
//	StaticDmy,		// 83
//	StaticDmy,		// 84
//	StaticDmy,		// 85
//	StaticDmy,		// 86
//	StaticDmy,		// 87
//	StaticDmy,		// 88
//	StaticDmy,		// 89
//	StaticDmy,		// 8A
//	StaticDmy,		// 8B
//	StaticDmy,		// 8C
//	StaticDmy,		// 8D
//	StaticDmy,		// 8E
//	StaticDmy,		// 8F

//	StaticDmy,		// 90
//	StaticDmy,		// 91
//	StaticDmy,		// 92
//	StaticDmy,		// 93
//	StaticDmy,		// 94
//	StaticDmy,		// 95
//	StaticDmy,		// 96
//	StaticDmy,		// 97
//	StaticDmy,		// 98
//	StaticDmy,		// 99
//	StaticDmy,		// 9A
//	StaticDmy,		// 9B
//	StaticDmy,		// 9C
//	StaticDmy,		// 9D
//	StaticDmy,		// 9E
//	StaticDmy,		// 9F

//	StaticDmy,		// A0
//	StaticDmy,		// A1
//	StaticDmy,		// A2
//	StaticDmy,		// A3
//	StaticDmy,		// A4
//	StaticDmy,		// A5
//	StaticDmy,		// A6
//	StaticDmy,		// A7
//	StaticDmy,		// A8
//	StaticDmy,		// A9
//	StaticDmy,		// AA
//	StaticDmy,		// AB
//	StaticDmy,		// AC
//	StaticDmy,		// AD
//	StaticDmy,		// AE
//	StaticDmy,		// AF

//	StaticDmy,		// B0
//	StaticDmy,		// B1
//	StaticDmy,		// B2
//	StaticDmy,		// B3
//	StaticDmy,		// B4
//	StaticDmy,		// B5
//	StaticDmy,		// B6
//	StaticDmy,		// B7
//	StaticDmy,		// B8
//	StaticDmy,		// B9
//	StaticDmy,		// BA
//	StaticDmy,		// BB
//	StaticDmy,		// BC
//	StaticDmy,		// BD
//	StaticDmy,		// BE
//	StaticDmy,		// BF

//	StaticDmy,		// C0
//	StaticDmy,		// C1
//	StaticDmy,		// C2
//	StaticDmy,		// C3
//	StaticDmy,		// C4
//	StaticDmy,		// C5
//	StaticDmy,		// C6
//	StaticDmy,		// C7
//	StaticDmy,		// C8
//	StaticDmy,		// C9
//	StaticDmy,		// CA
//	StaticDmy,		// CB
//	StaticDmy,		// CC
//	StaticDmy,		// CD
//	StaticDmy,		// CE
//	StaticDmy,		// CF

//	StaticDmy,		// D0
//	StaticDmy,		// D1
//	StaticDmy,		// D2
//	StaticDmy,		// D3
//	StaticDmy,		// D4
//	StaticDmy,		// D5
//	StaticDmy,		// D6
//	StaticDmy,		// D7
//	StaticDmy,		// D8
//	StaticDmy,		// D9
//	StaticDmy,		// DA
//	StaticDmy,		// DB
//	StaticDmy,		// DC
//	StaticDmy,		// DD
//	StaticDmy,		// DE
//	StaticDmy,		// DF

//	StaticDmy,		// E0
//	StaticDmy,		// E1
//	StaticDmy,		// E2
//	StaticDmy,		// E3
//	StaticDmy,		// E4
//	StaticDmy,		// E5
//	StaticDmy,		// E6
//	StaticDmy,		// E7
//	StaticDmy,		// E8
//	StaticDmy,		// E9
//	StaticDmy,		// EA
//	StaticDmy,		// EB
//	StaticDmy,		// EC
//	StaticDmy,		// ED
//	StaticDmy,		// EE
//	StaticDmy,		// EF

//	StaticDmy,		// F0
//	StaticDmy,		// F1
//	StaticDmy,		// F2
//	StaticDmy,		// F3
//	StaticDmy,		// F4
//	StaticDmy,		// F5
//	StaticDmy,		// F6
//	StaticDmy,		// F7
//	StaticDmy,		// F8
//	StaticDmy,		// F9
//	StaticDmy,		// FA
//	StaticDmy,		// FB
//	StaticDmy,		// FC
//	StaticDmy,		// FD
//	StaticDmy,		// FE
//	StaticDmy,		// FF
} ;
#endif // Å™ EXTERNAL IIF NEW	2011.02.21 by @Tny



uchar StaticDmy( void )
{
	return(false);
}

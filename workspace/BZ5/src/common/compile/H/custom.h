//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//�@�y�w�b�_���z
//�@�@�@������������
//�@�y�w�b�_���x���z
//�@�@�@�k�d�u�d�k�F�g�|�O
//  �y�w�b�_�����z
//      �n�ڋ@�ŗL�w�b�_
//  �y���l�z
//      �Ȃ�
//  �y�X�V�����z
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#ifndef	__YD400GZ3_H
//-------------------------------------------------
#define	__YD400GZ3_H
#define	__M32186
#define __DEBUG		// �f�o�b�O���I�I
					// �uFix Me!!�v���m�F���邱�ƁI�I


// 2019.09.02
#define __NEWCOM_PROTOCOL


#define G3_NEW_COM 1
#define TBLCNT              72
//#define REMO_TBLCNT         20
#define REMO_TBLCNT         15 //2008.07.18�@�Q�O���v��Ȃ��Ɣ��f���P�T�ɕύX
#define WELDNAME_TBLCNT     32


//#define NAVITBLCNT          105 //2009.01.14 BP4 2009.03.18 100->105
#define NAVITBLCNT          125 //2010.03.03 105->125

// Phase2 @Tny
//
#define FRAM_PAKECT         4   // 32/n = TX Byte

#define CPU_di( )               ( DI_imask( ) )//2007.3.9�ǉ�
#define CPU_ei( )               ( EI_imask( ) )//2007.3.9�ǉ�

// ��{define�錾
//
#define	true            1
#define	false           0
#define ON              true
#define OFF             false
#define	FOREVER		for(;;)
#define	NUL             0
#define WDT_ADDR        0x00170000l
#define WDG_Clear()     (*((unsigned short int *)WDT_ADDR) = 0x0001)
#define ARRAY_WIDTH     30

//----- Phase22 by @Tny 2008/10/07 -----
#if true
//#define CH 17           //�������L���p������  16->17 �L���`�����l���͂P�`�P�U�ł��邽��
#define CH 51           //�������L���p������  16->17 �L���`�����l���͂P�`�P�U�ł��邽��  2009.03.16 �T�O�`�����l���ɕύX
#endif
//--------------------------------------------
//#define SELECT_DITAL_MAX          50 //�ڍ׃��j���[�̍ő�l
//#define SELECT_DITAL_MAX          85 //�ڍ׃��j���[�̍ő�l 2008.10.10
//#define SELECT_DITAL_MAX          32 //�ڍ׃��j���[�̍ő�l 2008.10.10 2009.03.16 2010.03.03 30->32
#define SELECT_DITAL_MAX          33 //�ڍ׃��j���[�̍ő�l 2008.10.10 2009.03.16 2010.03.03 30->32		<IIF NEW> 32->33 2011.10.07
//#define SELECT_DITAL_MAX          12 //�ڍ׃��j���[�̍ő�l BP4 Phase3 by @Tny 2009.01.15

//����p�����[�^
#define USER_PARAMETER_NO        100 //2008.10.30 10 -> 100
//�T�[�r�X�}��
#define SERVICE_DATA_NO          30 //2008.09.02 �b��� 2008.10.30 3->10		BP4 Phase13 by @Tny 2009.02.23
//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
//#define RESCUE_DATA_NO			5
//#define RESCUE_DATA_NO			6
#define RESCUE_DATA_NO			7	// �u�𗬔g�`�o�̓��[�h�v�ǉ�	2011.11.08
//---------------------------------------------------

//20110916_1+++++
 //<><><><><> �o�͓d���㉺���l 2011.09.16 <><><><><>
//#define     MAX_CURRENT_VAL           300	    // 2011.09.16 500BP4 DC,AC_STD,AC_HARD,MIX
#define     MAX_CURRENT_VAL           400	    // 2011.09.16 500BP4 DC,AC_STD,AC_HARD,MIX			2019.08.21
#define     MAX_CURRENT_AC_SOFT_VAL   200       // 2011.09.16 500BP4 AC_SOFT
#define     MAX_CURRENT_HAND_VAL      250       // 2011.09.16 500BP4 HAND
//#define     MIN_CURRENT_VAL             4       // 2011.09.16 500BP4 DC
#define     MIN_CURRENT_VAL             1       // 2011.09.16 500BP4 DC								2019.08.21
#define     MIN_CURRENT_AC_HARD_VAL    20       // 2011.09.30 AC_HARD
//#define     MIN_CURRENT_AC_VAL         10       // 2011.09.16 AC_STD,AC_SOFT,MIX
#define     MIN_CURRENT_AC_VAL          1       // 2011.09.16 AC_STD,AC_SOFT,MIX					2019.08.21
#define     MIN_CURRENT_HAND_VAL        4       // 2011.09.16 500BP4 HAND		10->4 2012.05.30

//d �|�|�|�|�|�|�|�|�Q�l 300BP4�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
//d  //<><><><><> �o�͓d���㉺���l 2010.03.10 by @Tny�y�m�n�P�T�z(2010.01.12) <><><><><>
//d  #define     MAX_CURRENT_VAL			300			// 300BP4 DC,AC_STD,AC_HARD,MIX
//d  #define     MAX_CURRENT_AC_SOFT		200			// 300BP4 AC_SOFT
//d  #define     MAX_CURRENT_HAND		250			// 300BP4 HAND
//d  #define     MIN_CURRENT				  4			// 300BP4 DC
//d  #define     MIN_CURRENT_AC			 10			// 300BP4 AC_STD,AC_SOFT
//d  #define     MIN_CURRENT_AC_HARD		 20			// 300BP4 AC_HARD
//d  #define     MIN_CURRENT_AC_MIX		 10			// 300BP4 AC,MIX
//d  #define     MIN_CURRENT_HAND		  4			// 300BP4 HAND
//d  //<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//d  
//d  //<><><><><> �o�͓d���㉺���l 2010.01.12 <><><><><>
//d  #define     MAX_CURRENT_VAL           500	    // 2010.01.12 500BP4 DC,AC_STD,AC_HARD,MIX
//d  #define     MAX_CURRENT_AC_SOFT_VAL   330       // 2010.01.12 500BP4 AC_SOFT
//d  #define     MAX_CURRENT_HAND_VAL      400       // 2010.01.12 500BP4 HAND
//d  #define     MIN_CURRENT_VAL             5       // 2010.01.12 500BP4 DC
//d  #define     MIN_CURRENT_AC_MIX_VAL     20       // 2010.01.12 500BP4 AC,MIX
//d  #define     MIN_CURRENT_HAND_VAL       10       // 2010.01.12 500BP4 HAND
//d  //<><><><><><><><><><><><><><><><><><><><><><><><><>
//20110916_1-----



//�d�m�ꌳ���֘A
#define EN_VOLT_P           0 //�{�d���l
#define EN_VOLT_M           1 //�|�d���l
#define EN_VOLT_0           2 //�d�m�O�����d���l
#define EN_INIT             0 //�����d���̂d�m�䗦 2008.10.01
#define EN_MAIN             1 //�{�d���̂d�m�䗦 2008.10.01
#define EN_CRATER           2 //�N���[�^�d���̂d�m�䗦 2008.10.01
#define EN_WAVE             3 //���[�p���X�d���̂d�m�䗦 2008.10.10
#define EN_START            4 //�X�^�[�g�d���̂d�m�䗦 2008.10.10
#define EN_Q                5 //�ꌳ�d���₢���킹�d�m�䗦 2008.11.28

//BP4�p�ڍ׃��j���[�ԍ� Phase4,Phase5,Phase6,Phase7 by @Tny 2009.01.15-2009.02-16
#define P_DC_TIG_START      0 //P00
#define P_HOT_CURR_LEVEL    1 //P01
#define P_VOLT_DISPLAY      2 //P02
#define P_CRATER_ENDING     3 //P03
#define P_ELECTRODE_SHORT	4 //P04
#define P_DISPLAY_HOLD_TIME 5 //P05
#define P_AC_ARC_RECOVERY   6 //P06
#define P_NOW_DATE_TIME     7 //P07
#define P_DATE_TIME_DISPLAY 8 //P08
#define P_CURR_DISPLAY      9 //P09
#define P_DENBOU           10 //P10
#define P_ARC_DRIVE        11 //P11
#define P_WELD_NAME        12 //P12 2009.03.07
#define P_LCD_BRIGHT       13 //P13 2009.03.07
#define P_EXTARNAL_LEVEL_A 14 //P14 2009.03.07 �G�L�X�p�[�g���[�h
#define P_EXTARNAL_MASK_TIME 15 //P15 2010.01.08 �G�L�X�p�[�g���[�h�}�X�N����
#define P_REMOCON_SELECT   16 //P16 2009.03.07
#define P_VARIABLE_CRATER_REPEAT 17 //P17 2009.03.14
#define P_MAX_OUTPUT       18 //P18 2010.01.08 by @Tny
#define P_MILD_PULSE       19 //P19 2010.01.20 by @Tny
#define P_AC_FRQ_DISP      20 //P20 2010.01.20 by @Tny
#define P_ARC_ASSIST       21 //P21 2010.02.25

//#define P_SOFT_START_TIME   22 //P22 2011.10.01 �\�t�g�X�^�[�g����		�u�\�t�g�X�^�[�g���ԁv�폜 2011.10.31
//#define P_EXECUTE_VOLTAGE_A 23 //P23 2010.02.25 �G�L�X�p�[�g���[�h�����p 2009.03.07
#define P_DETAIL_DISPLAY    22 //P22 2011.10.03		�u�\�t�g�X�^�[�g���ԁv�폜�ɔ����ύX 2011.10.31
#if true	// <IIF NEW>
	#define P_IIF_SELECT		23 //P23 <IIF NEW> 2009.11.17 by @Tny	�u�\�t�g�X�^�[�g���ԁv�폜�ɔ����ύX  	2011.10.31
	#define P_SOFT_START_TIME   24 //P24 2011.10.01 �\�t�g�X�^�[�g����		�u�\�t�g�X�^�[�g���ԁv�폜�ɔ����ύX 2011.10.31
	#define P_EXECUTE_VOLTAGE_C 25 //P25 2010.02.25 �G�L�X�p�[�g���[�h�����p
	#define P_EXTARNAL_LEVEL_C  26 //P25 2010.02.25 �G�L�X�p�[�g���[�h�����p
	#define P_VOLTAGE_SAMPLING  27 //P26 2010.02.25 �G�L�X�p�[�g���[�h�����p
	#define P_INPUT_PASS_WORD   28 //P27 2010.02.25
	#define P_CHENGE_PASS_WORD  29 //P28 2010.02.25
	#define P_CONTROLLER_LOCK   20 //P29 2010.02.25
	#define P_SUB_MONITOR       31 //P30 2010.02.25
	#define P_ADJUST_ITEM       32 //P31 2010.02.25
#else
	#define P_EXECUTE_VOLTAGE_C 24 //P24 2010.02.25 �G�L�X�p�[�g���[�h�����p
	#define P_EXTARNAL_LEVEL_C  25 //P25 2010.02.25 �G�L�X�p�[�g���[�h�����p
	#define P_VOLTAGE_SAMPLING  26 //P26 2010.02.25 �G�L�X�p�[�g���[�h�����p
	#define P_INPUT_PASS_WORD  27 //P27 2010.02.25
	#define P_CHENGE_PASS_WORD 28 //P28 2010.02.25
	#define P_CONTROLLER_LOCK  29 //P29 2010.02.25
	#define P_SUB_MONITOR      30 //P30 2010.02.25
	#define P_ADJUST_ITEM      31 //P31 2010.02.25
#endif

#if 0 //2010.02.25 �ԍ��̕ύX
#define P_OUTPUT_SELECT     20 //P20 2009.02.16 �o�͕␳�L���I��
#define P_EXECUTE_VOLTAGE_A 21 //P21 2009.02.13 �G�L�X�p�[�g���[�h�����p 2009.03.07
#define P_EXECUTE_VOLTAGE_C 22 //P22 2009.02.13 �G�L�X�p�[�g���[�h�����p
//#define P_EXTARNAL_LEVEL_A  22 //P22 2009.02.13 �G�L�X�p�[�g���[�h�����p
#define P_EXTARNAL_LEVEL_C  24 //P24 2009.02.13 �G�L�X�p�[�g���[�h�����p
#define P_VOLTAGE_SAMPLING  25 //P25 2009.02.13 �G�L�X�p�[�g���[�h�����p

#define P_INPUT_PASS_WORD  26 //P26 2009.03.16
#define P_CHENGE_PASS_WORD 27 //P27
#define P_CONTROLLER_LOCK  28 //P28
#define P_SUB_MONITOR      29 //P29
#define P_ADJUST_ITEM      30 //P30
#endif

//--------------------------------------------------------------------
// �T�[�r�X�}���E���j���[�ԍ�		BP4 Phase14 by @Tny 2009.02.24	BP4 Phase16 by @Tny 2003.03.10
#define S_PASSWORD			 0 // S00
//#define S_PRI_FLOW_TIME	 1 // S01
#define S_DC_TIG_EN_HOT_I	 1 // S01
#define S_DC_TIG_EN_HOT_T	 2 // S02
#define S_DC_TIG_EN_HOT_ST   3 // S03
#define S_DC_TIG_EP_HOT_I	 4 // S04
#define S_DC_TIG_EP_HOT_T	 5 // S05
#define S_DC_TIG_EP_HOT_ST   6 // S06
#define S_AC_MIX_HOT_I		 7 // S07 2009.04.03
#define S_AC_MIX_HOT_T1		 8 // S08 2009.04.03
#define S_AC_MIX_HOT_T2		 9 // S09 2009.04.03
#define S_AC_MIX_HOT_ST		10 // S10 2009.04.03
#define S_MAX_SPOT_TIME		11 // S11
#define S_LINE_VOLT_OFFSET	12 // S12
#define S_CURRENT_ADJUST	13 // S13
#define S_CT_OFFSET			14 // S14
#define S_VT_OFFSET			15 // S15
#define S_E_L_SHORT_LEVEL	16 // S16
#define S_DISP_ADJUST		17 // S17
#define S_OUTPUT_ADJ_GEIN	18 // S18 2009.04.03
//#define S_AFTER_FLOW_TIME	19 // S19
#define S_ERROR_HIS_CLEAR	19 // S19

//--------------------------------------------------------------------

//--------------------------------------------------------------------
// ���X�L���[�E���j���[�ԍ�		BP4 by @Tny 2009.04.8
#define R_PASSWORD			 0 // R00
#define R_ERROR_HIS			 1 // R01
#define R_REC_LOCK			 2 // R02
#define R_RAM_ALL_CLEAR		 3 // R03
#define R_EXT_SW			 4 // R04	2010.01.20 by @Tny
#define R_ARC_ERR_PRE_CHECK  5 // R05 2010.02.25
#define R_AC_WAVE_OUT_MODE	 6 // R06 �u�𗬔g�`�o�̓��[�h�v�ǉ�	2011.11.08
//--------------------------------------------------------------------



//�ڍ׃��j���[�ԍ� 2008.09.10
#if 0 //2009.03.16 del
#define P_SLOW_DOWN         0 //P00
#define P_HOT_VOLTAGE       1 //P01
#define P_FTT_VOLTAGE       2 //P02
#define P_BURNBACK_TIME     3 //P03
#define P_PENETRATION       4 //P04
#define P_PRE_FLOW_TIME     5 //P05
#define P_AFTER_FLOW_TIME   6 //P06
#define P_PULSE_PEAK_CUR    7 //P07
#define P_PULSE_BASE_CUR    8 //P08
#define P_PULSE_RISE_CUR    9 //P09
#define P_PULSE_FALL_CUR   10 //P10
#define P_FEED_RATE        11 //P11
#define P_PULSE_START_VOLT 12 //P12
#define P_WAVE_CONTROL1    13 //P13
#define P_PULSE_FREQ       14 //P14
#define P_PULSE_WIDTH      15 //P15
#define P_ARC_SPOT_TIME    16 //P16
#define P_LOW_PULSE_SET    17 //P17
#define P_LOW_PULSE_LEVEL  18 //P18
#define P_LOW_PULSE_VOLT   19 //P19
#define P_LOW_PULSE_FREQ   20 //P20
#define P_LOW_PULSE_DUTY   21 //P21
#define P_LOW_PULSE_DELAY  22 //P22
#define P_EN_DUTY          23 //P23
#define P_EN_DUTY_INIT     24 //P24
#define P_EN_DUTY_CRATER   25 //P25
                              //P26
                              //P27
#define P_EP_START_TIME    28 //P28
#define P_EN_CUR           29 //P29
#define P_LOW_PULSE_SLOP   30 //P30
#define P_SPECIAL_SPEC     31 //P31
#define P_CRATER_REPEAT    32 //P32
                              //P33
                              //P34
#define P_BURNBACK2        35 //P35
#define P_INPLSE_START_SW  36 //P36
#define P_WELD_ENDING      37 //P37
#define P_DC_CONTROL_TIME  38 //P38 2008.09.22 �𗬎�����������
#define P_ARC_SPOT_SET     39 //P39 2008.10.21�ǉ�
#define P_CRATER_DC        40 //P40 2008.11.06
                              //P41
                              //P42
                              //P43
                              //P44
                              //P45
                              //P46
                              //P47
                              //P48
                              //P49

#define P_INPUT_PASS_WORD  50 //P50
#define P_CHENGE_PASS_WORD 51 //P51
#define P_CONTROLLER_LOCK  52 //P52
#define P_SUB_MONITOR      53 //P53
#define P_ADJUST_ITEM      54 //P54
#define P_WAVE_CONTROL2    55 //P55
#define P_START_TIME       56 //P56
#define P_HOT_TIME         57 //P57
#define P_CDM              58 //P58
#define P_ELI              59 //P59
#define P_HOT_CUR          60 //P60
#define P_IAC              61 //P61
#define P_INIT_IB          62 //P62
#define P_INIT_IP          63 //P63
#define P_PRISE            64 //P64
#define P_PFALL            65 //P65
#define P_ISC              66 //P66
#define P_SP_I             67 //P67
#define P_SP_T             68 //P68
#define P_TS0              69 //P69
#define P_ENDPLS           70 //P70
#define P_INIT_PFRQ        71 //P71
#define P_NECKLVL          72 //P72
#define P_PCTRLBLOW        73 //P73
#define P_STARTPLS         74 //P74
#define P_WIRACDC          75 //P75
#define P_SA_LEVEL         76 //P76
#define P_AS_LEVEL         77 //P77
#define P_START_CTRL       78 //P78
#define P_START_CTRL_LEVEL 79 //P79
#define P_START_CTRL_VOLT  80 //P80
#define P_START_CTRL_TIME  81 //P81
                              //P82
                              //P83
                              //P84
                              //P85
                              //P86
                              //P87
                              //P88
                              //P89
                              //P90
#endif
#define ROBOT_CONNECT      91 //���{�b�g�ڑ��̕\�� 2008.10.03


#if true // �� EXTERNAL IIF NEW	2011.02.21 by @Tny
	//<><><><><><><><><><> �h�h�e�֘A�ݒ� <><><><><><><><><><>
	//IIF NEW
	//<><><> �e���͂̔ԍ� <><><>
	//�A�i���O����
	#define IIF_ANALOG_SERECT		11+1  // �A�i���O���͑I�����ڐ�
	#define IIF_ANALOG_NO_USE        0
	#define IIF_ANALOG_PR_CUR        1    //�n�ړd���w�ߒl
	#define IIF_ANALOG_PR_VLT        2    //�n�ړd���w�ߒl
	#define IIF_ANALOG_OK_VLT        3    //�ꌳ�d���w�ߒl
	#define IIF_ANALOG_PENET         4    //�n�����ݒ���
	#define IIF_ANALOG_FD_RT         5    //���C�������ʔ�����
	#define IIF_ANALOG_WCTRL1        6    //�g�`����P
	#define IIF_ANALOG_WCTRL2        7    //�g�`����Q
	#define IIF_ANALOG_WIACDC        8    //���C���������x����
	//�ړ_����	// <EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
	#define IIF_INPUT_NO_USE         0
	#define IIF_INPUT_TSW            1    //�g�[�`�r�v
	#define IIF_INPUT_GAS_CK         2    //�K�X�`�F�b�N
	#define IIF_INPUT_STKSET         3    //�X�e�B�b�N�`�F�b�N
	#define IIF_INPUT_EM_STP         4    //����~
	#define IIF_INPUT_BIN1           5    //�Đ������o�C�i���P
	#define IIF_INPUT_BIN2           6    //�Đ������o�C�i���Q
	#define IIF_INPUT_BIN3           7    //�Đ������o�C�i���R
	#define IIF_INPUT_BIN4           8    //�Đ������o�C�i���S
	#define IIF_INPUT_BIN5           9    //�Đ������o�C�i���T
	#define IIF_INPUT_BIN6          10    //�Đ������o�C�i���U
	#define IIF_INPUT_CNT           11    //���͋��M��
	#define IIF_INPUT_STB           12    //�X�g���[�u�M��
	#define IIF_INPUT_STOP1         13    //�ꎞ��~�P
	#define IIF_INPUT_STOP2         14    //�ꎞ��~�Q
	#define IIF_INPUT_WIR_CK        15    //�C���`���O
	#define IIF_INPUT_RETRCT        16    //���g���N�g
	#define IIF_INPUT_OKCVON        17    //�ꌳ�^��
	#define IIF_INPUT_GP_IN1        18    //�ėp���͂P
	#define IIF_INPUT_GP_IN2        19    //�ėp���͂Q
	#define IIF_INPUT_GP_IN3        20    //�ėp���͂R
	#define IIF_INPUT_BIN7          21    //�Đ������o�C�i���V
	//�ړ_�o��
	#define IIF_OUTPUT_NO_USE        0
	#define IIF_OUTPUT_CURDET        1    //�d�����o
	#define IIF_OUTPUT_ARCOUT        2    //�A�[�N�؂�ُ�
	#define IIF_OUTPUT_STKOUT        3    //�X�e�B�b�N�ُ�
	#define IIF_OUTPUT_ERR           4    //�G���[
	#define IIF_OUTPUT_ALM           5    //�A���[��
	#define IIF_OUTPUT_WELD          6    //�n�ڒ�
	#define IIF_OUTPUT_GAS_ON        7    //�K�X����m�F
	#define IIF_OUTPUT_GP_OT1        8    //�ėp�o�͂P
	#define IIF_OUTPUT_GP_OT2        9    //�ėp�o�͂Q
	#define IIF_OUTPUT_GP_OT3       10    //�ėp�o�͂R
	//<><><> �ő�l�A�ŏ��l <><><>
	//�ő�l
	#define PR_CUR_MAX_VALUE       350    //�n�ړd���w�ߒl
	#define PR_VLT_MAX_VALUE       500    //�n�ړd���w�ߒl
	#define OK_VLT_MAX_VALUE        98    //�ꌳ�d���w�ߒl
	//�ŏ��l
	#define PR_CUR_MIN_VALUE        15    //�n�ړd���w�ߒl
	#define PR_VLT_MIN_VALUE        50    //�n�ړd���w�ߒl
	#define OK_VLT_MIN_VALUE       -98    //�ꌳ�d���w�ߒl
	//<><><>><><><><><><><><><><><><><><><><><><><><><><><><>
#endif // �� EXTERNAL IIF NEW	2011.02.21 by @Tny


//#define P_INIT_CURR_ON     28 //P28
//#define P_REFERENCE_VOLT1  37 //P37
//#define P_REFERENCE_VOLT2  38 //P38




#include        <stdio.h>       // �W���w�b�_�t�@�C���i�W�����o�͏����n�j
#include        <stdlib.h>      // �W���w�b�_�t�@�C���i�W�������n�j
#include        <string.h>      // �W���w�b�_�t�@�C���i������^����������n�j
#if false
#include        <math.h>        // �Z�p���Z�p�w�b�_�t�@�C��
#include        <float.h>       // �����l�p�w�b�_�t�@�C��

#endif

typedef unsigned short                       ushort;
typedef unsigned char                        uchar;
typedef unsigned long                        ulong;
typedef unsigned char                        ubool;
typedef volatile unsigned char               *PVUB;
typedef volatile unsigned short int          *PVUW;
typedef	unsigned short int                   usint;   // �����Ȃ��Z�����^
typedef	short int                            sint;    // �����t���Z�����^
typedef	long                                 lint;    // �����t��������
typedef	unsigned long                        ulint;   // �����Ȃ�������
typedef unsigned char                        *puchar; // �����Ȃ������^
typedef short int                            *psint;  // �����t���Z�����^
typedef unsigned short int                   *pusint; // �����Ȃ��Z�����^
typedef unsigned int                         *puint;  // �����Ȃ������^
typedef long                                 *plint;  // �����t��������
typedef unsigned long                        *pulint; // �����Ȃ�������

// �������X�C�b�`�\����
//
typedef union{
	uchar	ALL;
	struct{	// �P�r�b�g�X�C�b�`
		ubool	b7		:	1;	// MSB
		ubool	b6		:	1;
		ubool	b5		:	1;
		ubool	b4		:	1;
		ubool	b3		:	1;
		ubool	b2		:	1;
		ubool	b1		:	1;
		ubool	b0		:	1;	// LSB
	} Bit1Sw;
	struct{	// �S�r�b�g�X�C�b�`
		uchar	fUpper  :	4;	// MSB 4bit
		uchar	fLower  :	4;	// LSB 4bit
	} Bit4Sw;
} BitSwitch;

typedef union{
	uchar	ALL;
	struct{	// �P�r�b�g�X�C�b�`
		ubool	Toch_sw		:	1;	// MSB
		ubool	b6		:	1;
		ubool	Stick_check	:	1;
		ubool	Stick_release	:	1;
		ubool	b3		:	1;
		ubool	b2		:	1;
		ubool	b1		:	1;
		//ubool	b0		:	1;	// LSB
		ubool	Elrod_check		:	1;	// LSB 2009.07.14 STICK���߂ő�p����̂ō���g�p���Ȃ��B
	} Bit1Sw;
} WelderCommand; //�n�ړd������w��

typedef union{
	uchar	ALL;
	struct{	// �P�r�b�g�X�C�b�`
		ubool	b7		:	1;	// MSB
		ubool	b6		:	1;
		ubool	b5		:	1;
		ubool	b4		:	1;
		ubool	b3		:	1;
		ubool	Motor_conect	:	1;
		ubool	Motor_on	:	1;
		ubool	Gas_on		:	1;	// LSB
	} Bit1Sw;
} WelderCheck;  //�n�ړd���`�F�b�N

typedef union{
	uchar	ALL;
	struct{	// �P�r�b�g�X�C�b�`
		ubool	b7		:	1;	// MSB
		ubool	Cd       	:	1;
		ubool	b5		:	1;
		ubool	b4		:	1;
		ubool	b3		:	1;
		ubool	b2              :       1;
		ubool	b1	        :       1;
		ubool	b0		:	1;	// LSB
	} Bit1Sw;
} PowerStatus;  //�n�ړd�����

//<><><> 2009.07.13 <><><>
typedef union{
    uchar   ALL;
	struct{	// �P�r�b�g�X�C�b�`
		ubool	Pulse_ctrl   :   1;	// MSB
		ubool	Elrod_check  :   1;
		ubool	b5           :   1;
		ubool	b4           :   1;
		ubool	b3           :   1;
		ubool	Ac_recovery  :   1;
		ubool	Ep_start     :   1;
		ubool	Hf_ctrl	     :   1;	// LSB
	} Bit1Sw;
} Control;      //�R���g���[��
//<><><><><><><><><><><><><>


//�R���g���[�����[�h�Fgui_Ctrl_word
// 15:�V�[�P���X��~  �@14:            13:            12:                 11:                10:             9:           8:�X�e�B�b�N�������[�X
//  7:�X�e�B�b�N�E�^�b�` 6:�e�`�m����   5:�����g����   4:�n�ړd������w��  3:�C���o�[�^����   2:���[�^����   1:�K�X����   0:�l�f����
//<><><><><> 2007.3.28 bit�ϐ���unsigned�@char�ɕύX<><><><><>
typedef struct{
        ubool    Mg_ctrl_code;
        ubool    Gas_ctrl_code;
        ubool    Motor_ctrl_code;
        ubool    Inverter_ctrl_code;
        ubool    Welder_ctrl_code;
        ubool    Hf_ctrl_code;
        ubool    Fan_ctrl_code;
        ubool    Stick_check_code;
        ubool    Stick_release_code;
        ubool    A10;
        ubool    A11;
        ubool    A12;
        ubool    A13;
        ubool    A14;
        ubool    A15;
        ubool    Sequence_ctrl_code;
}Bit16;

//<><><><><><><><><><> ��������̗���𐧌䂷��t���O�Q <><><><><><><><><><>
typedef struct{
        ubool    Welder_init_execution;
        ubool    Inching;
        ubool    Inching_end; //2007.3.22
        ubool    Motor_off;
        ubool    Weld_end;
        ubool    Burn_back;
        ubool    Dsp_ready;
        ubool    Arc_err;
        ubool    Emg_err;
        ubool    Gas_err;
        ubool    Water_err;
        ubool    Arc_start_err;
        ubool    Arc_start_err1; //2007.1.19�ǉ� 2007.1.26�ڐA�ǉ�
        ubool    Arc_start_err2; //2007.1.19�ǉ� 2007.1.26�ڐA�ǉ�
        ubool    Arc_start_err_set;
        ubool    Temp_err;
        ubool    Temp_err_set; //2009.03.13
        ubool    Second_currnt_err;
        ubool    Second_currnt_err_set;
        ubool    Second_output_err; //2007.1.19�ǉ� 2007.1.26�ڐA�ǉ�
        ubool    Vp_err;
        ubool    Ts_cancel;
        ubool    Fan_off;
        ubool    Table_data_output;
        ubool    Table_data_output1;
        ubool    Table_data_output_execution; //2007.1.12
        ubool    Stick_start;
        ubool    Stick_end;
        ubool    Stick_on_off_check;
        ubool    Stick_snd_set;
        ubool    Arc;
        ubool    R8_rcv;
        ubool    R8_send;
        ubool    Err_disp_chenge_timing;
        ubool    Ver_disp_chenge_timing;  //2007.2.13�ǉ�
        ubool    Pri_curr_fb1_err;
        ubool    Pri_curr_fb1_err_unb;  //2007.3.14 �o�n�ł��ڐA
        ubool    Pri_curr_fb2_err;
        ubool    R8_com_err;
        ubool    ErrorCode_set;
        ubool    ErrorCode_snd;
        ubool    Slow_down;
        ubool    Initial_arc_start;
        ubool    Pre_flow;
        ubool    Pre_flow_time;
        ubool    After_flow;                //2007.12.11
        ubool    After_flow_time;           //2007.12.11
        ubool    Motor_delay;
        ubool    Motor_delay_end;
        ubool    Motor_current_err;
        ubool    Repeat_weld;//REPEAT 2007.1.12
        ubool    Toch_sw_off_delay_time;//2007.2.24�ǉ�
        ubool    Stick_check_delay_time;//2007.2.24�ǉ�
        ubool    Pri_volt_err_com_delay;//2007.3.6�ǉ� 2007.3.13�ڐA
        ubool    Pri_volt_err_com_delay_set_flag;//2007.3.6�ǉ� 2007.3.13�ڐA
        ubool    Emg2_cancel;//2007.3.14 �o�n�ł��ڐA
        ubool    Motor_off_slop;//2007.3.20
        ubool    Total_weld_time_reset;//2007.3.30
        ubool    Total_weld_count_reset;//2007.4.5
        ubool    Total_wire_feed_reset;//2007.4.5
        ubool    Rs232_start;  //2007.4.2
        ubool    Rs232_init;  //2007.4.2
        ubool    Pri_curr_fb1_start_err; //2007.4.17
        ubool    Pri_curr_fb1_err_04_check; //2007.4.17
        ubool    Second_voltage_err;  //�񎟉ߓd���ُ� 2008.11.17
        ubool    Primary_current_err; //�P���ߓd���ُ� 2008.11.17

        //<><><>���[�^�G���[�֘A 2007.8.1<><><>
        ubool    Motor_encoder_err;
        ubool    Motor_lock_err;
        ubool    Motor_circuit_break;
        ubool    Motor_circuit_err;
        ubool    Motor_err;

        //<><><> �����R���֘A <><><><><><><><><>
        ubool    Pre_set; //�w�ߒl�𒲐����ł��邱�Ƃ�m�点��B2008.01.22

        //�����d���{���[�p���X�֘A
        ubool    Init_current_time;  //2008.02.27
		ubool    Wave_current_time;  //2008.02.27
        ubool    Condition_time_set; //2008.02.27
        ubool    Condition_change;   //2008.02.27
        
        ubool	Weld_end_disp; //2008.03.03
        
        ubool    Srt1;//2008.03.11

        //<><><> �V�[�P���X����֘A <><><><><><><><>
        ubool    Sequence_crater;//2008.07.29
        ubool    Arc_spot_time;
        ubool    Arc_spot_time_up;
        ubool    Crater_repeat_time;
        ubool    Crater_repeat;
        ubool    After_flow_stop;
        ubool    Start_time; //2008.08.05

        //<><><> �I���֘A 2008.08.07 <><><><><><><><>
        ubool    Param_change;
        ubool    Play;
        ubool    Rec;
        ubool    Yes;
        ubool    Rec_display;
        ubool    Del; //2008.09.09
        ubool    Delete; //2008.09.09

        //<><><> �\������֘A <><><>
        ubool    Revers_time; //2008.08.19
        ubool    Ch_app;      //2008.08.19
        ubool    Set_screen_on_off; //2008.08.22
        ubool    Robot_connect_time; //2008.10.06

        //<><><> �ݒ胁�j���[�֘A <><><>
        //***���[�U�[***
        //�S�p�����[�^���Z�b�g�֘A
        ubool    User_all_parameter_reset;
        ubool    User_all_parameter_reset_exe; //2008.09.04
        //����
        ubool    Set_key;
        //�h�h�e�ݒ�֘A
        ubool    Out_function_set_ready;
        ubool    In_function_set_ready; //2008.08.25
        ubool    Analog_function_set_ready; //2008.08.25
        //�J�����_�[�֘A
        ubool    Calender_set_ready;   //2008.08.25
        ubool    Calender_init;        //2008.10.06 �J�����_�[�̏������p
        //�������[�R�s�[�֘A
        ubool Memory_copy_vector; //2008.08.29

        //�ꎞ��~���͎��̐���t���O 2008.09.01
        ubool Err_level1;
        //�G���[���x���Q���̐���t���O 2008.11.17
        ubool Err_level2;
        
        //�T�[�r�X�}���֘A
        ubool Service_man; //2008.09.02
        ubool Pass_word_err; //2008.09.02
        ubool Service_reset1; //2008.09.02
        ubool Service_reset2; //2008.09.02
        ubool Service_reset1_exe; //2008.09.04
        ubool Service_reset2_exe; //2008.09.04
        ubool Clr_time;       //2008.09.03

        //�K�X����
        ubool Gas_limit_timer;      //2008.09.08

        //�O���I�����j�b�g�֘A
        ubool Ext_select_cnt;       //2008.09.09
        ubool Ext_select_cnt_bkup;  //2008.09.09
        ubool Ext_select_init;      //2008.09.09
        ubool Ext_select_end;       //2008.09.09

        //�ڍ׃��j���[�p�X���[�h
        ubool Dital_pass_lock;      //2008.09.10


        //�𗬎����������Ԑ���֘A 2008.09.22
        ubool AC_control;
        ubool DC_control_timer;
        ubool Dc_control_timer_end;
        ubool Dc_control_timer_one_shot;


        ubool Lift_up_cd; //2008.10.08

        ubool Slow_start; //2008.10.08 �C���`���O�X���[�X�^�[�g�t���O

        ubool Arc_out_err; //2008.10.21 �n�ڒ��A�[�N�؂ꎞ�̑Ή�

        ubool Crater_pulse_non; //2008.11.06�N���[�^���p���X�L�薳�������肷��t���O


        //�˂��o�����ݒ�֘A 2008.11.10
        ubool Ext_condition_set_ready;

        //�N�����̃��[�^�f�B���C���̉����x 2008.11.17
        ubool Motor_acc1;

        //�C���p���X�X�^�[�g�X�C�b�` 2008.11.26
        ubool Inplse_start_sw;

        //�g�o�h�]���s�����߂̃t���O 2008.11.29
        ubool Hpi_control;

        //�o�[���o�b�N���`�b�ɂ��邩�ǂ����̔���t���O 2008.12.11
        ubool Burnback_ac;

        //��Q�o�[���o�b�N�L�薳���I���t���O 2008.12.11
        ubool Burn_back2;

        //��Q�o�[���o�b�N�I���t���O�i��Q�o�[���o�b�N���ɃX�e�B�b�N�`�F�b�N���c�r�o�ɑ���̂�h�����߁j 2008.12.11
        ubool Burn_back2_dsp_end;

        //2009.01.28
        ubool Current_set_out1;
        ubool Current_set_out2;


        //***** �����g�֘A 2009.01.31 *****
        ubool Hf_2sec_timer;                    //�Q�b�^�C�}
        ubool Hf_30sec_timer;                   //�R�O�b�^�C�}
        ubool Hf_30sec_interval_timer;          //�Ԍ�����܂ŃC���^�[�o���^�C�}
        ubool Hf_intermittent_on;               //�Ԍ��N���^�C�}
        ubool Hf_intermittent_off;              //�Ԍ��N���^�C�}
        ubool Hf_exec;                          //�����g�N���t���O
        ubool Hf_intermittent_set;              //�Ԍ����싖�t���O

        //***** �X���[�v�֘A 2009.02.02 *****
        ubool Up_slop_curr_end;
        ubool Up_slop_time_end;
        ubool Up_slop_time;
        ubool Down_slop_curr_end;
        ubool Down_slop_time_end;
        ubool Down_slop_time;

        //***** �N���[�^���s�[�g�v�N���b�N�֘A 2009.02.05*****
        ubool W_click_timer;
        ubool Crater_repeat_end;
        ubool W_click_end; //2009.02.25

        ubool Output_correct; //2009.02.16


        //�l�h�w�֘A 2009.02.17
        ubool    Mix_wave_current_time;
        ubool    Mix_condition_time_set;
        ubool    Mix_condition_change;

        ubool    After_flow_check; //2009.02.18

        ubool    Blink_set; //2009.02.19


        //�G�L�X�p�[�g���[�h�֘A 2009.02.20
        ubool Ref_voltage;
        ubool Ref_voltage_result;
        ubool Cal;
        ubool hugou;
        ubool Ref_voltage_add_start; //2010.01.12

        //�N���[�^���g�[�`�X�C�b�`�����グ�ɂ���čēx�g�[�`��ڋ߂����ꍇ�̏����t���O
        ubool Re_crater; //2009.02.25

        //������n�ڊ֘A 2009.03.06
        ubool Hand_stick_ready_time;
        ubool Hand_stick_start;
        ubool Hand_restart; //2009.03.30
        ubool Hand_restart_wait; //2009.03.30

        //�n�[�h�d�� 2009.03.07
        ubool Hard_cd;

        //�ϔ����֘A 2009.03.14
        ubool Cr_ts_check;
        ubool Cr_ts_check2;
        ubool Cr_ts_check3; //2009.07.31

        //�d�ɒZ���֘A 2009.03.16
        ubool Arc_short;

        //�o�͓d���␳�I�� 2009.03.16
        ubool Disp_adjust;

        //�ϔ����I�� 2009.03.16
        ubool Variable_crater_repaet;

        //�A�[�N�h���C�u�֘A 2009.03.17
        ubool Arc_drive_mask_time;
        ubool Arc_drive;

        //�p���X�\���֘A 2009.03.23
        ubool Base_avr_result;
        ubool Peak_avr_result;
        ubool Base_read_delay; //2009.03.24
        ubool Peak_read_delay; //2009.03.24

        //�����R���Đ��֘A
        ubool Remo_controller_no; //2009.03.28
        ubool Remo_play_sw;       //2009.03.28
        ubool Remo_play_on;       //2009.03.28
        ubool Remo_play_mode;     //2009.03.30
        ubool No_ch_data;         //2009.03.30
        ubool Remo_play_ch_select;//2009.03.30

        //�n�ڏI���d���\���L�����Z��
        ubool End_welding_display_cansel;

        //�c�r�o�p���X�M�� 2009.04.03
        ubool Dsp_pulse_out;
        
        //�X�^�[�g�����I���M�� 2009.04.03
        ubool Start_process_end;
//---------------------------------------
// BP4 Phase11 by @Tny 2009.02.19
		ubool RemoteController;	// �����R���ڑ��t���O
//---------------------------------------

        ubool UnConnect_false; //2009.07.14

        ubool Rob_pram_refresh; //2009.07.17

        ubool Method_rcv_flag; //2009.07.17

        ubool Err_gas;         //2009.07.27

        ubool Crater_curr_start; //2009.08.03


        ubool Err_ts_cansel;     //2009.12.18
        ubool Ts_on_err_timer;   //2009.12.18
        ubool Ts_on_err;         //2009.12.18

        ubool Ac_freq_jog;       //2010.01.20

        ubool Variable_crater_re_crater; //�σN���[�^�������A�n�ړr���i�N���[�^�A�_�E���X���[�v�j�ŃA�[�N�؂���N���������p�̃t���O 2010.02.19

        ubool Detail_display;    //2011.10.03

        ubool Pl_pram_jog;       //2011.10.03

#if true // �� EXTERNAL IIF NEW	2011.02.21 by @Tny
        ubool Iif_enable;                  //�h�h�e���L�����ǂ����̔���t���O
        ubool Iif_first_rcv;               //�h�h�e����ŏ��̎�M�����������ǂ����̔���t���O
        ubool Iif_set;                     //
        ubool In_ab_set_ready;             //
        ubool Blink_reset;                 //
        ubool Blink_reset1;                //
        ubool Blink_reset_one_shot;        //
        ubool Iif_connect_err;             //
        ubool Calibration_set;             //
        ubool Iif_analog_shift_memory;     //
        ubool One_shot_sw_rewrite_check;   //
        ubool Stb_sw_on;                   //
        ubool Stb_set;                     //
        ubool In_function_no_one_shot;     //
        ubool Iif_output_data_one_shot;    //
        ubool Blink_reset_one_shot_04;     //
#endif // �� EXTERNAL IIF NEW	2011.02.21 by @Tny



        ubool uc_One_shot_voltage;         //2013.02.13		2013_02_13_500BP4���ڐA�@2014.06.11

//-------------------------------------------------------------
// 2019.09.04
	ubool ComSend;						// ���M�^�C�~���O�t���O
//-------------------------------------------------------------

	ubool Ms_time;				//2019.07.03
}CtrlFlag;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><> ��������̗���𐧌䂷��J�E���^�Q <><><><><><><><><><>
typedef struct{
        unsigned int Motor_off;
        unsigned int Emg_err;
        unsigned int Gas_err;
        unsigned int Water_err;
        unsigned int Temp_err;
        unsigned int Vp_err;
        unsigned int Extout_counter;
        unsigned long Backup_100m;
        unsigned long Backup_200m; //2007.3.29
        unsigned long Backup_300m; //2009.12.17
        unsigned long Backup_500m;
        unsigned long Backup_50m;  //2009.02.23
        unsigned long Backup_10m;  //2009.03.17 
        unsigned int Table_data_output;
        unsigned int Table_data_output1;
        unsigned int Welder_init_execution; //2007.1.22 int�ɕύX 2007.1.26�ڐA�ύX
        unsigned char Ts_check;
        unsigned int  Fan_off;
//------ Phase9 by @Tny 2008/09/12 ------
#if true
        unsigned int  Fan_A_off;
#endif
//---------------------------------------------------------------------
        unsigned int  Arc_start_err;
        unsigned int  R8_send;
        unsigned int  Err_disp_chenge_timing;
        unsigned int  Err_disp_chenge;
        unsigned int  Ver_disp_chenge_timing; //2007.2.13�ǉ�
        unsigned int  Ver_disp_chenge;        //2007.2.13�ǉ�
        unsigned int  Pri_curr_fb1_err;
        unsigned int  Pri_curr_fb1_err_unb; //2007.3.14 �o�n�ł��ڐA
        unsigned int  Pri_curr_fb2_err;
        unsigned int  R8_com_err;
        unsigned int  Pre_flow_time;
        unsigned int  After_flow_time; //2007.12.11
        unsigned int  Motor_delay;
        unsigned int  Motor_current_err;
        unsigned int  Repeat_weld;//REPEAT 2007.1.12
        unsigned int  Cd_check;   //2007.1.24 2007.1.26�ڐA�ǉ�
        unsigned int  Toch_sw_off_delay_time; //2007.2.24 �ǉ�
        unsigned int  Stick_check_delay_time; //2007.2.24 �ǉ�
        unsigned char Com_err_parity;         //2007.2.26 �ǉ�
        unsigned char Com_err_framing;        //2007.2.26 �ǉ�
        unsigned char Com_remo_err_parity;    //2007.12.03 �ǉ�
        unsigned char Com_remo_err_framing;   //2007.12.03 �ǉ�
        unsigned char Pri_volt_err_com_delay; //2007.3.6�ǉ� 2007.3.13�ڐA
        unsigned char Total_weld_time;        //2007.3.30
        unsigned int Pri_curr_fb1_start_err; //2007.4.17 2007.7.10 char -> int�ɕύX

        //<><><>���[�^�G���[�֘A 2007.8.1<><><>
        unsigned int  Motor_encoder_err;
        unsigned int  Motor_lock_err;
        unsigned int  Motor_circuit_break;
        unsigned int  Motor_circuit_err;
        unsigned int  Motor_err;

        //�����d���{���[�p���X�֘A
        unsigned short Init_current_time; //2008.02.27
        unsigned short Wave_current_time; //2008.02.27

        //unsigned short Frequence_time;    //2008.02.27
        //unsigned short A_condition_time;  //2008.02.27
        //unsigned short B_condition_time;  //2008.02.27
        //unsigned short Frequence_set_time;    //2008.02.27
        //unsigned short A_condition_set_time;  //2008.02.27
        //unsigned short B_condition_set_time;  //2008.02.27
        
        //2009.03.27 unsigned short -> unsigned long
        unsigned long Frequence_time;    //2008.02.27
        unsigned long A_condition_time;  //2008.02.27
        unsigned long B_condition_time;  //2008.02.27
        unsigned long Frequence_set_time;    //2008.02.27
        unsigned long A_condition_set_time;  //2008.02.27
        unsigned long B_condition_set_time;  //2008.02.27
        
        
        unsigned short Avr_result; //2008.03.03
        unsigned short Base_avr_result; //2009.03.23
        unsigned short Peak_avr_result; //2009.03.23
        unsigned short Weld_end_disp;   //2008.03.03
        
        unsigned short Srt1; //2008.03.11


        //<><><>�V�[�P���X����֘A<><><>
        unsigned int   Arc_spot_time; //2008.07.30
        unsigned int   Crater_repeat_time;
        unsigned int   Start_time; //2008.08.05

        //<><><> �\������֘A <><><>
        unsigned int   Revers_time; //2008.08.19
        unsigned char  uc_Robot_connect_time; //2008.10.06

        //<><><> �ݒ胁�j���[�֘A <><><>
        //***���[�U�[***
        //����p�����[�^�֘A
        unsigned char  uc_User_menu_no;
        unsigned short us_User_parameter_no;
        //�h�h�e�ݒ�֘A
        unsigned char  uc_Iif_no;
        unsigned char  uc_Out_port_no;
        unsigned char  uc_Out_function_no;
        unsigned char  uc_In_port_no;
        unsigned char  uc_In_function_no;
        unsigned char  uc_Analog_port_no;
        unsigned char  uc_Analog_function_no;
        //�J�����_�[�֘A
        unsigned char  uc_Calender_no;    //2008.08.25
        unsigned char  uc_Year_set_data;  //2008.08.25
        unsigned char  uc_Month_set_data; //2008.08.25
        unsigned char  uc_Day_set_data;   //2008.08.25
        unsigned char  uc_Hour_set_data;  //2008.08.25
        unsigned char  uc_Mint_set_data;  //2008.08.25
//------ Phase8 by @Tny 2008/09/11 ------
#if true
        //�G���[����\���֘A
        unsigned char  uc_Error_history_no;
        ubool            b_Error_information;
#endif
//---------------------------------------------------------------------
        //�������R�s�[�֘A
        unsigned char Memory_copy_area_no; //2008.08.29

        //�T�[�r�X�}���֘A
        unsigned char Pass_word_check; //2008.09.02
        unsigned char Pass_word_ok;    //2008.09.02
        unsigned char  uc_Service_menu_no; //2008.09.02
        unsigned short us_Service_data_no; //2008.09.02
        unsigned char uc_Service_reset_no; //2008.09.02
        unsigned char uc_Clr_time;       //2008.09.03

        //�K�X����
        unsigned short Gas_limit_timer;      //2008.09.08

        //�e�[�u�����������i�ǂ̂悤�ȃe�[�u���������Ă��邩�A�I�ʂ����בւ������鏈���Ɏg�p����j
        unsigned char uc_Pulse_mode_check;     //�e�[�u�����e���o�̂��߂̃J�E���^ 2008.09.16


        //�𗬎����������Ԑ���֘A 2008.09.22
         unsigned short us_DC_control_timer;

        //�˂��o�����ݒ�֘A 2008.11.10
        unsigned char  uc_Ext_condition_data;

        unsigned short Second_currnt_err_timer; //2008.12.04

        //�i�n�f�@�u�Q�l�`�w���� 2008.12.22
        char sc_Jog1;
        char sc_Jog2;
        unsigned short us_Jog1_timer;
        unsigned short us_Jog2_timer;

        //***** �����g�֘A�^�C�} 2009.01.31 *****
        short Hf_2sec_timer;                    //�Q�b�^�C�}
        short Hf_30sec_timer;                   //�R�O�b�^�C�}
        short Hf_30sec_interval_timer;          //�Ԍ�����܂ŃC���^�[�o���^�C�}
        short Hf_intermittent_on;               //�Ԍ��N���^�C�}
        short Hf_intermittent_off;              //�Ԍ��N���^�C�}
        

        //***** �X���[�v�֘A 2009.02.02 *****
        unsigned short Up_slop_time;
        unsigned short Down_slop_time;
        
        //***** �N���[�^���s�[�g�v�N���b�N�֘A 2009.02.05*****
        unsigned short W_click_timer;


        unsigned short Output_correct; //2009.02.16


        //�l�h�w�֘A 2009.02.17
        //unsigned short Mix_wave_current_time;
        //unsigned short Mix_frequence_time;
        //unsigned short Mix_A_condition_time;
        //unsigned short Mix_B_condition_time;
        //unsigned short Mix_frequence_set_time;
        //unsigned short Mix_A_condition_set_time;
        //unsigned short Mix_B_condition_set_time;

        //2009.03.27 unsigned short -> unsigned long
        unsigned long Mix_wave_current_time;
        unsigned long Mix_frequence_time;
        unsigned long Mix_A_condition_time;
        unsigned long Mix_B_condition_time;
        unsigned long Mix_frequence_set_time;
        unsigned long Mix_A_condition_set_time;
        unsigned long Mix_B_condition_set_time;


        //�G�L�X�p�[�g���[�h�֘A 2009.02.20
        short Ref_voltage;
        unsigned short Ref_voltage_add_count; //2010.01.12

        unsigned short Hpi;


        //������n�ڊ֘A 2009.03.06
        short Hand_stick_ready_time;
        short Hand_restart_wait; //2009.03.30

        //�d�ɒZ���`�F�b�N 2009.03.13
        short Electrode_short_check;

        //�ϔ����֘A 2009.03.14
        short Cr_ts_check;
        short Cr_ts_check2;

        //�A�[�N�h���C�u�֘A 2009.03.17
        char Arc_drive_mask_time;

        //�p���X�\���֘A 2009.03.24
        char Base_read_delay;
        char Peak_read_delay;
        
        //�����R���Đ��֘A
        short Remo_play_sw; //2009.03.28

        //�G���[���K�X�����֘A
        short Err_gas;      //2009.07.27

        //�g�[�`�r�v�ċN���֘A
        short Ts_on_err_timer; //2009.12.18

#if true // �� EXTERNAL IIF NEW	2011.02.21 by @Tny
        unsigned char  uc_Iif_ab_set; 			//
        unsigned char  uc_Iif_set;    			//
        short          ss_Blink_reset; 			//
        short          Blink_reset_one_shot_04; //
#endif // �� EXTERNAL IIF NEW	2011.02.21 by @Tny


		unsigned short	us_One_shot_voltage;	//<><><> �d�ɒZ���̉�� 2014.06.24 <><><>

	short Ms_time;		//2019.07.03

/*****************************************/
}CtrlCounter;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><><><><><><><> �d�m�䗦�֘A�̕ϐ��Q 2008.09.22 <><><><><><><><><><>
typedef struct{
    float	f_AC_Frq_ENa1_A;	//���g���萔b�Z�o�pEN�䗦�͈͂P�ł̒萔A
    float	f_AC_Frq_ENa1_B;	//���g���萔b�Z�o�pEN�䗦�͈͂P�ł̒萔B
    float	f_AC_Frq_ENa1_C;	//���g���萔b�Z�o�pEN�䗦�͈͂P�ł̒萔C
    float	f_AC_Frq_ENa2_A;	//���g���萔b�Z�o�pEN�䗦�͈͂Q�ł̒萔A
    float	f_AC_Frq_ENa2_B;	//���g���萔b�Z�o�pEN�䗦�͈͂Q�ł̒萔B
    float	f_AC_Frq_ENa2_C;	//���g���萔b�Z�o�pEN�䗦�͈͂Q�ł̒萔C
    sint	ss_AC_DCstart_Tim_Def;	//������Ē��������Ԕ�������̫�Ēl (�P�ʁFms)
    sint	ss_AC_DCstart_Tim_Max;	//������Ē��������Ԕ�����MAX�l (�P�ʁFms)
    sint    ss_En_def;
    sint    ss_En_a;
    sint    ss_En_a_init;
    sint    ss_En_a_main;
    sint    ss_En_a_crater;
    sint    ss_En_a_wave;     //2008.10.10
    sint    ss_En_a_start;    //2008.10.10
    sint    ss_En_a_qes;      //2008.11.28
    sint    ss_En_a_output;
    sint    ss_En_def_init;   //2008.11.28
    sint    ss_En_def_main;   //2008.11.28
    sint    ss_En_def_crater; //2008.11.28
    sint    ss_En_def_wave;   //2008.11.28
    sint    ss_En_def_start;  //2008.11.28
    signed char sc_Va;
    signed char sc_Va_init;
    signed char sc_Va_main;
    signed char sc_Va_crater;
    signed char sc_Va_wave;   //2008.10.10
    signed char sc_Va_start;  //2008.10.10
    signed char sc_Va_qes;    //2008.11.28
    unsigned char uc_En_inquiry; //2008.10.03 ���{�b�g����̂d�m�䗦�v�Z���ʖ₢���킹�ϐ�
    unsigned char uc_Com_en_inquiry; //2008.12.01 ���{�b�g����̂d�m�䗦�v�Z���ʖ₢���킹�ϐ�
}En;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><>  �ڍׂ̃��[�N�ϐ��Q 2008.10.09 <><><><><><><><><><>
typedef struct{
    unsigned short us_Pre_flow_time;    //P05
    unsigned short us_After_flow_time;  //P06
    signed short   ss_Arc_spot_time;    //P16 2008.10.10 2009.03.16 unsigned -> signed
    unsigned short us_Wave_current_time;//P22 2008.10.14
    signed short   ss_En_duty_main_adjustment;//P23 2008.10.14
    signed short   ss_En_duty_init_adjustment;//P23 2008.10.14
    signed short   ss_En_duty_crat_adjustment;//P23 2008.10.14
    signed short   ss_En_duty_qes_adjustment; //2008.11.28
    unsigned short us_Display_time;     //P37 2008.10.14
    unsigned short us_DC_control_timer; //P38 2008.10.14
    unsigned short us_Start_ctrl_timer; //P81 2008.10.16
}DitailWork;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><> FPGA�����̃f�[�^�iA/D�l�j��荞�݊֘A�̕ϐ��Q  <><><><><><><>
typedef struct{
        unsigned short Curr_ad;
        unsigned long  Curr_buff;
        unsigned int   Curr_counter;
        unsigned short Curr_result;
        unsigned short Volt_ad;
        unsigned long  Volt_buff;
        unsigned int   Volt_counter;
        unsigned short Volt_result;
        unsigned int   Short_counter; //�Z���񐔂̃J�E���^�[�@�Z���񐔂͎��ۂɂ͂c�r�o����擾���邪�֋X�ケ���ɔz�u���� 2007.3.2
  
        unsigned long  Curr_buff_unb;    //2007.3.14�@�o�n�ł��ڐA
        unsigned int   Curr_counter_unb; //2007.3.14�@�o�n�ł��ڐA
        unsigned short Curr_result_unb;  //2007.3.14�@�o�n�ł��ڐA
 
        unsigned char  Rpm_counter;      //2007.3.15
        unsigned char  Rpm_avg_counter;  //2007.3.15

        //�����l�v�Z�֘A
        double Curr_buff_rms; //2009.03.26
        double Volt_buff_rms; //2009.03.26
        double Curr_result_rms; //2009.03.26
        double Volt_result_rms; //2009.03.26
}Fpga;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//<><><><><><><><><><><> �e�[�u���L�[�ϊ��֘A�̕ϐ��Q <><><><><><><><><><><>
typedef struct{
        unsigned char  Wire_diameter;
        unsigned char  Welding_method;
        unsigned char  Wire_material;
        unsigned char  Wire_ext;
        unsigned char  Pulse_mode;
        unsigned char  Pulse_type;
        unsigned char  Wire_diameter_bkup;
        unsigned char  Welding_method_bkup;
        unsigned char  Wire_material_bkup;
        unsigned char  Wire_ext_bkup;
        unsigned char  Pulse_mode_bkup;
        unsigned char  Pulse_type_bkup;
        unsigned char  Change_flag;
}TableKey;
typedef struct{
        unsigned char  New_calc;
        unsigned char  Request1;
        unsigned char  Send1;
        unsigned char  Request2;
        unsigned char  Send2;
        unsigned char  Okcv[260];      //2009.12.28 500BP4
        unsigned char  Okcv_real[260]; //2009.12.28 500BP4
        char  Okcv_real_p[260];        //2009.12.28 500BP4
        char  Okcv_real_m[260];        //2009.12.28 500BP4
        char  Okcv_real_0[260];        //2009.12.28 500BP4
        char  Okcv_crater_short[260];  //2009.12.28 500BP4
        unsigned short Sb0[1040];      //2009.12.28 500BP4
        signed   int   Okcv_ref;
}Okcv;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//<><><><><><><><><><><><><> �q�W�ʐM�֘A�̕ϐ��Q <><><><><><><><><><><><><>
typedef union{ //�q�W����̎�M��
	uchar	ALL[6];
	struct{
           struct{
                  ubool    b5                     :  1;
                  ubool    non2                   :  1;
                  ubool    b4                     :  1;
                  ubool    b3                     :  1;
                  ubool    b2                     :  1;
                  ubool    non1                   :  1;
                  ubool    b1                     :  1;
                  ubool    b0                     :  1;
           } Sp_data;                  //�U�������X�C�b�`
           uchar Ex_data;              //�O���I�����j�b�g
           unsigned short Pri_curr_fb1;//�ꎟ�d���e�a�l�P
           unsigned short Pri_curr_fb2;//�ꎟ�d���e�a�l�Q
	}Data;
} RcvPacket;  
typedef struct{ //�l�R�Q�����g�p��
           struct{
                  ubool    b5                     :  1;
                  ubool    non2                   :  1;
                  ubool    b4                     :  1;
                  ubool    b3                     :  1;
                  ubool    b2                     :  1;
                  ubool    non1                   :  1;
                  ubool    b1                     :  1;
                  ubool    b0                     :  1;
           } Sp_data;
        uchar Ex_data;
        unsigned short Pri_curr_fb1;
        unsigned short Pri_curr_fb2;
        unsigned long  Pri_curr_fb1_work;
        unsigned long  Pri_curr_fb2_work;
        unsigned short Sum_counter;
                  ubool Com_check                 :  1;
} InputR8;
typedef struct{ //�q�W�Ƃ̒ʐM�Ɏg�p����ϐ�
        unsigned char   Rx_buffer[10];
        unsigned char   Rx_write_position;
        unsigned short  Work;

} R8Com;


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>



//<><><><><><><><><><><><><> �O�����͊֘A�̕ϐ��Q <><><><><><><><><><><><><>
typedef struct{
        unsigned char Data[ARRAY_WIDTH];
        unsigned char Data_bkup[ARRAY_WIDTH];
        unsigned char Counter[ARRAY_WIDTH];
        unsigned char Flag[ARRAY_WIDTH];
} ExtInput;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><><><><><><><><><><> �c�r�v�֘A�̕ϐ��Q <><><><><><><><><><><><><>
typedef union{ //�c�r�v�̓��e
	unsigned short ALL;
	struct{
              ubool    No15                   :  1;
              ubool    No14                   :  1;
              ubool    No13                   :  1;
              ubool    No12                   :  1;
              ubool    No11                   :  1;
              ubool    No10                   :  1;
              ubool    No9                    :  1;
              ubool    No8                    :  1;
              ubool    No7                    :  1;
              ubool    No6                    :  1;
              ubool    No5                    :  1;
              ubool    No4                    :  1;
              ubool    No3                    :  1;
              ubool    No2                    :  1;
              ubool    No1                    :  1;
              ubool    No0                    :  1;
	}Sw;
} Dsw;  
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><> �`�c�S�i�ꎟ���͓d���j�֘A�̕ϐ��Q <><><><><><><><><>
typedef struct{
        unsigned int Result;
        unsigned int Buffer;
        unsigned short Counter;
} Vp;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><> �`�c�O�i���[�^�d���j�֘A�̕ϐ��Q <><><><><><><><><>
typedef struct{
        //unsigned int Result;
        //unsigned int Buffer;
        int Result;     //2007.1.15 signed �ɕύX 2007.1.17�ڐA
        int Buffer;     //2007.1.15 signed �ɕύX 2007.1.17�ڐA
        unsigned short Counter;
      
        int Center_result;  //2007.3.20
        int Center_buffer;  //2007.3.20
        unsigned short Center_counter; //2007.3.20
} Mc;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><><><><><><> �n�ڏ����e�[�u���R�[�h�֘A�̕ϐ��Q <><><><><><><><><>
typedef struct{
        unsigned char Material;          //�ގ�
        unsigned char Method;           //�n�ږ@
        unsigned char Pulse_mode;        //�n�ڎ�ʃt���O�i�Z���^�p���X�j
        unsigned char Pulse_type;        //�p���X�^�C�v
        unsigned char Wire;              //���C���a
        unsigned char Extension;         //�˂��o����
        unsigned char Reserved1;         //�\��
        unsigned char Reserved2;         //�\��
} Table_Code;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><> �����R���I��p�n�ڏ����e�[�u���R�[�h�֘A�̕ϐ��Q <><><><><><>
typedef struct{
        unsigned char Material[REMO_TBLCNT];         //�ގ�
        unsigned char Method[REMO_TBLCNT];           //�n�ږ@
        unsigned char Pulse_mode[REMO_TBLCNT];       //�n�ڎ�ʃt���O�i�Z���^�p���X�j
        unsigned char Pulse_type[REMO_TBLCNT];       //�p���X�^�C�v
        unsigned char Wire[REMO_TBLCNT];             //���C���a
        unsigned char Extension[REMO_TBLCNT];        //�˂��o����
        unsigned char Reserved1[REMO_TBLCNT];        //�\��
        unsigned char Reserved2[REMO_TBLCNT];        //�\��

        //*** 2008.07.18�ǉ� ***
        unsigned char Control1_mode[REMO_TBLCNT];    //����P
        unsigned char Control2_mode[REMO_TBLCNT];    //����Q
        unsigned char Control3_mode[REMO_TBLCNT];    //����R

} REMO_Table_Code;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><><><> ��������e�[�u���R�[�h�֘A�̕ϐ��Q <><><><><><><><><>
typedef struct{
        unsigned char Kind;              //01:�ގ� 02:�n�ږ@
        unsigned char Code;              //�R�[�h
        unsigned char Name[16];          //�R�����g
} Sp_Table_Code;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//<><><><><><><><> ���Œ�A�σf�[�^���������֘A�̕ϐ��Q <><><><><><><><><>
typedef struct{
        //���Œ�f�[�^
        //unsigned char  Hfix_no;           //���Œ�f�[�^�ԍ�
        unsigned short Hfix_no;           //���Œ�f�[�^�ԍ� 2007.4.16�ύX
        unsigned short Hfix_data;         //�f�[�^
        //�σf�[�^
        unsigned char  Val_no0;            //�σf�[�^�ԍ�
        unsigned int   Val_a_data0;        //���f�[�^
        unsigned int   Val_b_data0;        //���f�[�^
        unsigned int   Val_c_data0;        //���f�[�^
        unsigned int   Val_min_data0;      //�������f�[�^
        unsigned int   Val_max_data0;      //�������f�[�^
        unsigned char  Val_no1;            //�σf�[�^�ԍ�
        unsigned int   Val_a_data1;        //���f�[�^
        unsigned int   Val_b_data1;        //���f�[�^
        unsigned int   Val_c_data1;        //���f�[�^
        unsigned int   Val_min_data1;      //�������f�[�^
        unsigned int   Val_max_data1;      //�������f�[�^
        unsigned char  Bank;               //�o���N�؂�ւ��t���O

} Com_Data;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


//<><><><><>�����R���p�@�e��ݒ�{�d���\���{�g�`����@2008.02.25<><><><><><>
typedef struct{
        unsigned char Select_counter;
        struct {
                //�e��ݒ�֘A
                signed char Parameter_set_counter;
                unsigned char Parameter_set_flag;
                signed short Parameter_set[20];
                //�d���\���֘A
                unsigned char Voltage_display_flag;
                //�g�`����֘A
                unsigned char Wave_control_flag;
        }Item;
} Parameter;
//


typedef struct{
        //���[�U�[�p�����[�^
        signed short ss_User_param[USER_PARAMETER_NO];
        //�T�[�r�X�}���f�[�^
        signed short ss_Service_data[SERVICE_DATA_NO];
//--------------------------------------------------------------------
//BP4 Phase14 by @Tny 2009.02.24
        signed short ss_Rescue_data[RESCUE_DATA_NO];
//--------------------------------------------------------------------
} Special_menu;

typedef struct{
        unsigned char  uc_Year_data;  //2008.08.25
        unsigned char  uc_Month_data; //2008.08.25
        unsigned char  uc_Day_data;   //2008.08.25
        unsigned char  uc_Hour_data;  //2008.08.25
        unsigned char  uc_Mint_data;  //2008.08.25
        unsigned char  uc_Sec_data;   //2008.08.25
        unsigned char  Leap_year;  //�[�N 2008.08.25
        unsigned char  Leap_month; //�[�� 2008.08.25
} Calender;

//�o���j���[�̑���
typedef struct{
        short ss_Max;
        short ss_Min;
        short ss_Notch;
        unsigned char uc_Point;
        short ss_Init;
} Dital_attribute;


typedef struct{
        unsigned char uc_Key_counter;
        signed char sc_Jog_counter;		// 2019.06.10	+signed
        unsigned char uc_Material_address;
        unsigned char uc_Material_set;
        unsigned char uc_Thickness_address;
        unsigned char uc_Thickness_set;
        unsigned char uc_Thickness_search;
        unsigned char uc_Joint_address;
        unsigned char uc_Joint_set;
        unsigned char uc_Joint_search;
        unsigned char uc_Direction_address;
        unsigned char uc_Direction_set;
        unsigned char uc_Direction_search;
        unsigned char uc_Pulse_address;
        unsigned char uc_Pulse_set;
        unsigned char uc_Pulse_search;

        unsigned char uc_Cansel;

        unsigned char uc_Jog_set_key; //2009.01.16
      
        unsigned char uc_Navi_limit;  //2010.01.21
//-----------------------------------------------------------------------------------------------------------------------------------------------
// <NAVI Enhancements(Phase 1)> 2011.10.26 by @Tny
		unsigned short	us_Gas_Navi;			// �K�X����
		unsigned short	us_Filler_navi;			// �t�B���[�a
		unsigned short	us_Electroad_navi;		// �d�Ɍa
		unsigned short	us_El_rd_angle_navi;	// �d�ɐ�[�p�x
		ubool			b_Navi_Disp;			// �i�r�\���t���O
//-----------------------------------------------------------------------------------------------------------------------------------------------

} NAVI;


//<><><><><><><><><><><><><><><><><><><><><><><> �����g�p�֘A�̕ϐ��Q <><><><><><><><><><><><><><><><><><><><><><><>
struct gtt_Internal_pack{
       struct{
                ubool            bRS422Connection;          // �q�r�S�Q�Q������ڑ����
                ubool            bRS232Connection;          // �q�r�Q�R�Q��������ڑ����
          struct{
                ubool            bChangeData;               // ��M�f�[�^�X�V�t���O
                uchar           iRecvCommand;              // ��M�R�}���h�i�f�[�^�X�V���ʗp�j
                sint            usWeldingCurr;             // �o�͓d���w�ߒl
                sint            usWeldingCurr_bkup;        // �o�͓d���w�ߒl�̃o�b�N�A�b�v 2008.10.20�ǉ�
                sint            usWeldingVolt;             // �o�͓d���w�ߒl
                sint            usWeldingInitCurr;         // �����o�͓d���w�ߒl 2008.02.22
                sint            usWeldingInitVolt;         // �����o�͓d���w�ߒl 2008.02.22
                sint            usWeldingCratCurr;         // �N���[�^�o�͓d���w�ߒl 2008.02.22
                sint            usWeldingCratVolt;         // �N���[�^�o�͓d���w�ߒl 2008.02.22
                sint            usWeldingWaveCurr;         // �g�`����@�a�����@�o�͓d���w�ߒl 2008.02.26
                sint            usWeldingWaveVolt;         // �g�`����@�a�����@�o�͓d���w�ߒl 2008.02.26
                sint            usWeldingStartCurr;        // �g�`����@�X�^�[�g�����@�o�͓d���w�ߒl 2008.08.05
                sint            usWeldingStartVolt;        // �g�`����@�X�^�[�g�����@�o�͓d���w�ߒl 2008.08.05
                BitSwitch       fWireDiameter;             // ���C���a
                BitSwitch       fWelding;                  // �n�ږ@
                BitSwitch       fWireMaterial;             // ���C���ގ�
                BitSwitch       fWireSelect;               // ���C����
                BitSwitch       fInitialSelect1;           // �����f�[�^�ݒ�P
                float            vTsoAdj;                   // �Z���������Ԓ���
                float            vIscAdj;                   // �Z���d�����ܒl����
                float            vIsl1Adj;                  // �Z���d�����z�P����
                float            vIsl2Adj;                  // �Z���d�����z�Q����
                char             vTspAdj;                   // �˂��|����h�~���Ԓ���
                float            vIacAdj;                   // �A�[�N�d�����ܒl���� 2009.07.10 char->float
                short            vIhotAdj;                  // �z�b�g�d������
                float            vVhotAdj;                  // �z�b�g�d������ 2007.2.5�ύX
                short            vSldnAdj;                  // ���C���X���[�_�E������
                short            vFttAdj;                   // �e�s�s���x������
                short            vBarnBackAdj;              // �o�[���o�b�N���Ԓ���
                WelderCommand   fWelderCommand;            // �n�ړd������w��
                WelderCheck     fWelderCheck;              // �n�ړd���`�F�b�N
                Control         fControl;                  // �R���g���[���i���{�b�g�ʐM�Ŏg�p�j2009.07.13
#if 0 //2009.03.18 unsigned -> signed
                ushort          usIP;                      // �p���X�s�[�N�w�ߓd��
                ushort          usIB;                      // �p���X�x�[�X�w�ߓd��
                ushort          usPulseFreq;               // �p���X�w�ߎ��g��
                ushort          usPulseDuty;               // �p���X�w�ߕ�
                ushort          usAcFreq;                  // �𗬎��g��
                uchar           ucCleaningDuty;            // �N���[�j���O��
                uchar           ucMixFreq;                 // MIX TIG���g��
                uchar           ucMixAcRatio;              // MIX(AC)�䗦
#endif
                short          usIP;                      // �p���X�s�[�N�w�ߓd��
                short          usIB;                      // �p���X�x�[�X�w�ߓd��
                short          usPulseFreq;               // �p���X�w�ߎ��g��
                short          usPulseDuty;               // �p���X�w�ߕ�
                short          usAcFreq;                  // �𗬎��g��
                char           ucCleaningDuty;            // �N���[�j���O��
                //char           ucMixFreq;                 // MIX TIG���g��
                short          ucMixFreq;                 // MIX TIG���g�� 2009.03.31
                char           ucMixAcRatio;              // MIX(AC)�䗦

                //BitSwitch       fControl;                  // �R���g���[�� 2009.07.13 del
                short           ucImprudenceVolt;          // �d�ɒZ���d���w�ߒl 2009.07.15 uchar->short
                BitSwitch       fPulseMode;                // �p���X���[�h�ݒ�
                //char            vHotTime;                  // �z�b�g�^�C�� 2007.2.5�ύX
                short           vHotTime;                  // �z�b�g�^�C��
                short           vIniIpAdj;                 // �X�^�[�g�s�[�N�d��������   2009.06.26 char->short
                short           vIniIbAdj;                 // �X�^�[�g�x�[�X�d��������   2009.06.26 char->short
                float           vIpAdj;                    // �p���X�s�[�N�d��������     2009.06.25 char->float
                float           vIb1Adj;                   // �p���X��P�x�[�X�d�������� 2009.06.25 char->float
                float           vIb2Adj;                   // �p���X��Q�x�[�X�d�������� 2009.06.30 char->float
                float           vIprAdj;                   // �p���X�s�[�N�����オ������� 2009.06.25 char->float
                float           vIpfAdj;                   // �p���X�s�[�N��������������� 2009.06.25 char->float
                float           vTiprAdj;                  // �p���X�����オ�莞�Ԕ�����         2009.06.25 char->float
                float           vTipAdj;                   // �p���X�s�[�N�����オ�莞�Ԕ�����   2009.06.25 char->float
                float           vTipfAdj;                  // �p���X���������莞�Ԕ�����         2009.06.25 char->float
                char            vPulseFreqAdj;             // �p���X���g��������
                short           vStartPulse;               // �X�^�[�g�p���X�L�薳��     2009.06.26 �ǉ�
                short           vEndPulse;                 // �G���h�p���X�L�薳��       2009.06.26 �ǉ�
                short           vIniPulseFreqAdj;          // �C�j�V�����p���X���g��     2009.06.26 �ǉ�
                short           vPctrlBlowAdj;             // �A�[�N�u���[�}������       2009.06.26 �ǉ�
                short           vWirSpdAdj;                // ���C���X�s�[�h������       2009.06.26 �ǉ�
                float           vWirStrAccAdj;             // �X�^�[�g�X���[�v������     2009.06.26 �ǉ� 2009.06.30 short->float
                float           vWirStrDelayAdj;           // ���C���X�^�[�g�f�B���C������     2009.06.26 �ǉ� 2009.06.30 short->float
                short           vNeckLvlAdj;               // �l�b�N���x��������         2009.06.26 �ǉ�
                float           vWirAcDcAdj;               // �����x�R                   2009.06.26 �ǉ� 2009.06.30 short->float
                short           vBbkPulseAdj;           // �o�[���o�b�N�p���X         2009.06.29 �ǉ�
                char            vLowPulseAB_LevelGap;      // �ȈՃ��[�p���X�F�`�����a�������x����
                char            vLowPulseAB_TimeRatio;     // �ȈՃ��[�p���X�F�`�����a�������Ԕ䗦
                char            vLowPulseFreq;             // �ȈՃ��[�p���X�F���g��
                char            vLowPulseStartTimeAdj;     // �ȈՃ��[�p���X�J�n���Ԕ�����
                char            vPulseStartSlope;          // �p���X�X�^�[�g�X���[�v
                char            vPulseExecSlope;           // �p���X�w�ߒl�؂�ւ��X���[�v
                char            vPulsePerformance;         // �p���X������
                BitSwitch       fLotCheck;                 // ���i�����p
                char            vAfterFlowAddTime;         // �A�t�^�[�t���[���ԉ��Z�l
                ushort          vCheck;                    // �o�b�N�A�b�v�������m�F�p�G���A
                ubool            Emergency;                 //����~����                  �i�O�����͂̂݁j
                ubool            Emergency2;                //����~�Q����                �i�O�����͂̂݁j2007.2.9
                ubool            Outside1;                  //�ꎞ��~�P�i�K�X�����ُ�j���́i�O�����͂̂݁j
                ubool            Outside2;                  //�ꎞ��~�Q�i����H�ُ�j���́@�i�O�����͂̂݁j
                ubool            Temp;                      //�T�[�}���@�@�@�@�@�@�@�@�@�@�@�i�O�����͂̂݁j
                char            vTableChange;              //�e�[�u���؂�ւ��R�}���h 2007.2.9
                sint            usWeldingCurr_bk_up;       // �o�͓d���w�ߒl 2007.2.19 �C���`���O���x�ύX�p�o�b�N�A�b�v
                sint            usWeldingVolt_bk_up;       // �o�͓d���w�ߒl 2007.2.19 �C���`���O���x�ύX�p�o�b�N�A�b�v
                sint            usWeldingCurr_pc_bk_up;    // �o�͓d���w�ߒl 2007.4.6 �r�f�P�p�o�b�N�A�b�v
                sint            usWeldingVolt_pc_bk_up;    // �o�͓d���w�ߒl 2007.4.6 �r�f�P�p�o�b�N�A�b�v

                short           sPreFlowTime;              // �v���t���[����       2009.01.13
                short           sAfterFlowTime;            // �A�t�^�[�t���[����   2009.01.13
                short           sUpSlopTime;               // �A�b�v�X���[�v����   2009.01.13
                short           sDownSlopTime;             // �_�E���X���[�v����   2009.01.13
                
                //<><><> TIG�n�����p�����[�^�ϐ� 2009.07.10 <><><>
                short           vIhotAdj_tig;              // �z�b�g�d�������i�s�h�f�n�j
                short           vHotTime_tig;              // �z�b�g���Ԓ����i�s�h�f�n�j
                short           vHotSlop_tig;              // �z�b�g�X���[�v�i�s�h�f�n�j
                //<><><><><><><><><><><><><><><><><><><><><><><><>

                //<><><> �g���n�ڔ����p�����[�^�ϐ� 2007.5.29 <><><>
                unsigned short  Id_no;                     //�h�c�ԍ�
                float           Sp_current;                //�r�o�d��
                float           Sp_time;                   //�r�o����
                float           Eli;                       //�d�k�h
                float           Mts_v;                     //�d���d���l
                float           Mts_ontime;                //�d���d���n�m����
                float           Mts_cycle;                 //�d���d������
                //<><><><><><><><><><><><><><><><><><><><><><><><><>

                sint            ss_En_duty_adjustment;     //���{�b�g���瑗���Ă����d�m������ 2008.10.03
	        unsigned short us_Q_WeldingCurr;        //2008.11.28
                short          ss_Q_en_duty_adjustment; //2008.11.28
                unsigned char  uc_Q_En_0_mode;          //2008.11.28
                unsigned char  uc_En_0_mode;            //2008.11.28

          } In;
          struct{
                uchar           ucModelCode;               // �@��ʃR�[�h
                uchar           sRomVersion[2];            // ROM�o�[�W����
                uchar           ucPassword;                // �p�X���[�h�ϊ���f�[�^
                ushort          usWeldingCurr;             // �o�͓d���w�ߒl
                ushort          usWeldingVolt;             // �o�͓d���w�ߒl
                ushort          usWeldingOutCurr;          // �o�͓d���l
                ushort          usWeldingOutVolt;          // �o�͓d���l
                uchar		ucImprudence;              // �Z����
                uchar           ucMotorCurr;               // ���[�^�d���l
                uchar           ucMotorRPM;                // ���[�^��]��
                uchar           ucMotorCurr2;              // ���[�^�d���l�Q
                ushort          usMotorRPM2;               // ���[�^��]���Q
                BitSwitch       fErrorCode1;               // �ُ팟�o��ԁi�n�ځE�����n�j
                BitSwitch       fErrorCode2;               // �ُ팟�o��ԁi�d���n�j
                BitSwitch       fErrorCode3;               // �ُ팟�o��ԁi�ُ�E��~�M�����o�n�j
                PowerStatus     fPowerStatus;              // �n�ړd�����
                ushort          usIP;                      // �p���X�s�[�N�d��
                ushort          usIB;                      // �p���X�x�[�X�d��
                ushort          usPulseFreq;               // �p���X���g��
                BitSwitch       fArcStartStatus;           // �A�[�N�X�^�[�g���

                uchar       uc_En_a;                //�d�m�䗦�v�Z����     2008.10.03
                ushort      us_En_Okcv;             //�d�m�䗦�v�Z��ꌳ�� 2008.10.03

                struct{
                      ushort          usWeldTimes;            // �n�ډ�
                      ushort          usWeldTimerIndividual;  // �n�ڎ���(��)
                      unsigned int    usWeldTimer;           // �n�ڎ��� 2007.3.30
                      ulong           usWireFeed;             // ���C����������
                      ushort          vCheck;                 // �o�b�N�A�b�v�������m�F�p�G���A
                }BackUp;
          } Out;

        } Data;
};

//----- Phase6 by @Tny 2008/09/10 -----
#if true
#define MAX_ERROR_INFOMATION    99      // �L�^���ʁF�X�X��
#define ERROR_INFO_RENEWAL      0x55aa  // �L�^���ʎq
#define IIF_BUILT_IN_RENEWAL    0x55aa  // �L�^���ʎq
struct gtt_Error_History{   // �G���[�����e�[�u���̍\����
    unsigned char   vStart;             // �J�n�G���A
    unsigned short  Record_identifier;  // �L�^���ʎq
    ubool            Start_record;       // �L�^�J�n�t���O
    unsigned short  History_rec_index;  // �L�^�C���f�b�N�X
    ubool            Full_history_rec;   // �S�L�^�G���A�g�p�t���O
    struct{
        unsigned short  Error_No;           // �G���[�ԍ�
        unsigned char   Year;               // ���������i�N�j
        unsigned char   Month;              // ���������i���j
        unsigned char   Day;                // ���������i���j
        unsigned char   Hour;               // ���������i���j
        unsigned char   Minute;             // ���������i���j
        unsigned char   Second;             // ���������i�b�j
    } Info[MAX_ERROR_INFOMATION];       // �L�^���
    unsigned char   vEnd;               // �I���A���A
};
#endif
//--------------------------------------------

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>




#ifdef __MAIN_PROG
        uchar          IdentificationCode;      // �@��ԍ�
	    extern void Hardware_Initialize(void);  // �V�X�e�����������C���O���Q�Ɛ錾
        //extern void WeldAdjOut_Proc( int ); //ihara 2005.12.27

//        const unsigned char   guc_Attribute_dps_no[3]         = "188";  //DPS�ԍ� 2007.6.28�ǉ�
//        const unsigned char   guc_Attribute_dps_no[3]         = "288";  //DPS�ԍ� 2008.4.1 YD-350AZR�{�ԋ@ & YD-350GBR�{�ԋ@�A�\���@
//        const unsigned char   guc_Attribute_dps_no[3]         = "388";  //DPS�ԍ� 2008.4.1 YD-350AZR�\���@
//        const unsigned char   guc_Attribute_dps_no[3]         = "052";  //DPS�ԍ� 2009.12.28 500BP4 2010.03.25 ���A
          const unsigned char   guc_Attribute_dps_no[3]         = "048";  //DPS�ԍ� 2011.09.28 300BP4
//        const unsigned char   guc_Attribute_dps_no[3]         = "C33";  //DPS�ԍ� 500BP4�c���e�X�g�@2010.03.23
//2010.02.10        const unsigned char   guc_Attribute_dps_no[3]         = "052";  //2010.02.06 ���i�R���p
//        const unsigned char   guc_Attribute_version[3]        = "F28";  //ROMver�@�i�R�����j;//2009.12.28 500BP4 2010.03.24 ������F28
//        const unsigned char   guc_Attribute_version[3]        = "103";  //ROMver�@�i�R�����j;//2010.03.25 ���A 2010.04.08 Ver101 2010.11.02 Ver102	 2011.09.01 Ver103
//        const unsigned char   guc_Attribute_version[3]        = "E07";  //ROMver�@�i�R�����j;//2011.10.04 ������E07
//        const unsigned char   guc_Attribute_version[3]        = "F02";  //ROMver�@�i�R�����j;//2011.10.07 ������F02	EXTERNAL IIF NEW
//        const unsigned char   guc_Attribute_version[3]        = "F03";  //ROMver�@�i�R�����j;//2011.10.12 ������F03	<EXTERNAL IIF NEW(Phase 2)>	2011.10.12 by @Tny
//        const unsigned char   guc_Attribute_version[3]        = "F04";  //ROMver�@�i�R�����j;//2011.10.13 ������F04	<EXTERNAL IIF NEW(Phase 4)>	2011.10.13 by @Tny
//        const unsigned char   guc_Attribute_version[3]        = "F05";  //ROMver�@�i�R�����j;//2011.10.26 ������F05	<EXTERNAL IIF NEW(Phase 5)><NAVI Enhancements(Phase 1)>	2011.10.26	/	<NAVI Enhancements(Phase 2)> 2011.10.27
//        const unsigned char   guc_Attribute_version[3]        = "F06";  //ROMver�@�i�R�����j;//2011.10.26 ������F06	<EXTERNAL IIF NEW(Phase 5)><NAVI Enhancements(Phase 1)>	2011.10.26	/	<NAVI Enhancements(Phase 2)> 2011.10.27 / �u���ヂ�[�h�v�̒ǉ�	2011.10.28
//        const unsigned char   guc_Attribute_version[3]        = "F07";  //ROMver�@�i�R�����j;//2011.10.31 ������F07	<EXTERNAL IIF NEW(Phase 6)>	2011.10.30
//        const unsigned char   guc_Attribute_version[3]        = "F08";  //ROMver�@�i�R�����j;//2011.10.31 ������F08	FPGA�ύX
//        const unsigned char   guc_Attribute_version[3]        = "F09";  //ROMver�@�i�R�����j;//2011.10.31 ������F09	���{�b�g�ʐM�s��Ή� 2011.10.31
//        const unsigned char   guc_Attribute_version[3]        = "F10";  //ROMver�@�i�R�����j;//2011.11.07 ������F10	���{�b�g�ʐM�s��Ή�
//        const unsigned char   guc_Attribute_version[3]        = "F11";  //ROMver�@�i�R�����j;//2011.11.07 ������F11	�T�[�r�X�}�����j���[�Ɂu�𗬔g�`�o�̓��[�h�v��ǉ�	2011.11.08
//        const unsigned char   guc_Attribute_version[3]        = "F12";  //ROMver�@�i�R�����j;//2011.11.07 ������F12	�}�C���h�p���X�ύX�iDSP�j
//        const unsigned char   guc_Attribute_version[3]        = "F14";  //ROMver�@�i�R�����j;//2011.11.14 ������F14	DSP�p���X�ؑ֎��g���ύX�B
//		  const unsigned char   guc_Attribute_version[3]        = "F15";  //ROMver�@�i�R�����j;//2011.11.16 ������F15	Err05�\�����L���x�����ԕύX
//        const unsigned char   guc_Attribute_version[3]        = "F16";  //ROMver�@�i�R�����j;//2011.11.18 ������F16	<EXTERNAL IIF NEW(Phase 12)> 2011.11.18
//        const unsigned char   guc_Attribute_version[3]        = "200";  //ROMver�@�i�R�����j;//2011.11.22 Ver2.00 FIX UP
//        const unsigned char   guc_Attribute_version[3]        = "2F2";  //ROMver�@�i�R�����j;//2011.12.08
//        const unsigned char   guc_Attribute_version[3]        = "200";  //ROMver�@�i�R�����j;//2011.12.08 Ver2.00 FIX UP
//        const unsigned char   guc_Attribute_version[3]        = "201";  //ROMver�@�i�R�����j;//2012.02.08 Ver2.01 FIX UP
//          const unsigned char   guc_Attribute_version[3]        = "202";  //ROMver�@�i�R�����j;//2012.05.23 Ver2.02
          const unsigned char   guc_Attribute_version[3]        = "203";  //ROMver�@�i�R�����j;//2014.06.11 Ver2.03
        //<><> BP4�ɕύX 2009.07.10 <><><>
        const unsigned char   guc_Attribute_kind_code         = 'C';    //��ʁi�c�F�l�`�f�@�b�F�s�h�f�@�P�����j
//      const unsigned char   guc_Attribute_capacity_code[3]  = "500";  //��i�o�́@�i�R�����j2009.12.28 500BP4
        const unsigned char   guc_Attribute_capacity_code[3]  = "300";  //��i�o�́@�i�R�����j//2011.09.28 300BP4
        const unsigned char   guc_Attribute_model_code[3]     = "BP4";  //�@��i�R�����j
        const unsigned char   guc_Attribute_special_code[3]   = "   ";  //����i�i�R�����j�F�W���i�̓X�y�[�X�R��
        //<><><><><><><><><><><><><><><><>
        //const unsigned char   guc_Attribute_kind_code         = 'D';    //��ʁi�c�F�l�`�f�@�b�F�s�h�f�@�P�����j
        //const unsigned char   guc_Attribute_capacity_code[3]  = "350";  //��i�o�́@�i�R�����j
        //const unsigned char   guc_Attribute_model_code[3]     = "AZ3";  //�@��i�R�����j
        //const unsigned char   guc_Attribute_special_code[3]   = "   ";  //����i�i�R�����j�F�W���i�̓X�y�[�X�R��

        BitSwitch	*p6;
        BitSwitch	*p9;
        BitSwitch	*p10;
        BitSwitch	*p11;
        BitSwitch	*p13;
        BitSwitch	*p22;

        Bit16           gtt_Ctrl_word;
        Bit16           gtt_Ctrl_word_bkup;
        CtrlFlag        gtt_Ctrl_flag;
        CtrlCounter     gtt_Ctrl_counter;
        Fpga            gtt_Fpga;
        TableKey        gtt_Table_key;
        Okcv            gtt_Okcv;
        RcvPacket       gtt_rcv_r8;
        InputR8         gtt_internal_r8;
        ExtInput        gtt_Ext_input;
        R8Com           gtt_R8_com;
        Dsw             gtt_Dsw;
        Vp              gtt_Vp;
        Mc              gtt_Motor_current;

        Table_Code      gtt_Table_code[TBLCNT];
        REMO_Table_Code gtt_Remo_table_code; //2007.12.05
        REMO_Table_Code gtt_Remo_table_code_work; //2007.12.05
        Sp_Table_Code   gtt_Sp_table_code[WELDNAME_TBLCNT];
        Com_Data        gtt_Com_rewrite_data;
        Com_Data        gtt_Internal_rewrite_data;
        Parameter       gtt_Parameter; //2008.08.06���A
        Special_menu    gtt_Special_menu; //2008.08.22
        
        Calender        gtt_Calender;      //2008.08.25
        Dital_attribute gtt_Dital_attribute[SELECT_DITAL_MAX+1]; //2008.08.27   // Phase11 by @Tny 2008/09/16
        unsigned char   guc_Write_check_flag[CH]; //2008.09.09
   
        En              gtt_En; //2008.09.22
        DitailWork      gtt_Ditail_work; //2008.10.09
        NAVI            gtt_Navi; //2009.01.15

//---------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23
        Dital_attribute gtt_Service_attribute[SERVICE_DATA_NO];
//---------------------------------------------------
//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
        Dital_attribute gtt_Rescue_attribute[RESCUE_DATA_NO];
//---------------------------------------------------
	    struct          gtt_Internal_pack	gtt_Internal_pack;// �����p�f�[�^�E�p�b�P�[�W

#else
        extern const char       DPS[];                     // �\�t�g�E�F�A�Ǘ��ԍ�
        extern const char       Version[];                 // �o�[�W�����ԍ�
        extern const long       DataTime;                  // �ŏI�X�V��
        extern const long       BuildRelease;              // �r���h�ԍ�
        //extern const uchar      IdentificationCode;        // �@��ԍ�
        extern uchar      IdentificationCode;        // �@��ԍ�

        extern const unsigned char   guc_Attribute_dps_no[];         //DPS�ԍ� 2007.6.28�ǉ�
        extern const unsigned char   guc_Attribute_version[];        //ROMver�@�i�R�����j;
        extern const unsigned char   guc_Attribute_kind_code;        //��ʁi�c�F�l�`�f�@�b�F�s�h�f�@�P�����j
        extern const unsigned char   guc_Attribute_capacity_code[];  //��i�o�́@�i�R�����j
        extern const unsigned char   guc_Attribute_model_code[];     //�@��i�R�����j
        extern const unsigned char   guc_Attribute_special_code[];   //����i�i�R�����j�F�W���i�̓X�y�[�X�R��


        extern void xmemset(void *dst, int dat, size_t lgh);
        extern void xmemcpy(void *dst, const void *soc, size_t lgh);
        extern BitSwitch	*p6;
        extern BitSwitch	*p9;
        extern BitSwitch	*p10;
        extern BitSwitch	*p11;
        extern BitSwitch	*p13;
        extern BitSwitch	*p22;

        extern Bit16           gtt_Ctrl_word;
        extern Bit16           gtt_Ctrl_word_bkup;
        extern CtrlFlag        gtt_Ctrl_flag;
        extern CtrlCounter     gtt_Ctrl_counter;
        extern Fpga            gtt_Fpga;
        extern TableKey        gtt_Table_key;
        extern Okcv            gtt_Okcv;
        extern RcvPacket       gtt_rcv_r8;
        extern InputR8         gtt_internal_r8;
        extern ExtInput        gtt_Ext_input;
        extern R8Com           gtt_R8_com;
        extern Dsw             gtt_Dsw;
        extern Vp              gtt_Vp;
        extern Mc              gtt_Motor_current;
        extern Table_Code      gtt_Table_code[];
        extern REMO_Table_Code gtt_Remo_table_code; //2007.12.05
        extern REMO_Table_Code gtt_Remo_table_code_work; //2007.12.05
        extern Sp_Table_Code   gtt_Sp_table_code[];
        extern Com_Data        gtt_Com_rewrite_data;
        extern Com_Data        gtt_Internal_rewrite_data;
	extern struct	gtt_Internal_pack	gtt_Internal_pack;// �����p�f�[�^�E�p�b�P�[�W
        extern Parameter       gtt_Parameter; //2008.02.25
        extern Parameter       gtt_Parameter_ch[CH]; //2008.08.07
        extern Special_menu    gtt_Special_menu; //2008.08.22
        extern Special_menu    gtt_Special_menu_ch[CH]; //2008.08.22
        extern Calender        gtt_Calender;         //2008.08.25
        extern Dital_attribute gtt_Dital_attribute[SELECT_DITAL_MAX+1]; //2008.08.27    // Phase11 by @Tny 2008/09/16
        extern unsigned char   guc_Write_check_flag[CH]; //2008.09.09
        extern En              gtt_En; //2008.09.22
        extern DitailWork      gtt_Ditail_work; //2008.10.09
        extern NAVI            gtt_Navi; //2009.01.15

//---------------------------------------------------
// BP4 Phase13 by @Tny 2009.02.23
        extern Dital_attribute gtt_Service_attribute[SERVICE_DATA_NO];
//---------------------------------------------------
//---------------------------------------------------
// BP4 Phase14 by @Tny 2009.02.24
        extern Dital_attribute gtt_Rescue_attribute[RESCUE_DATA_NO];
//---------------------------------------------------


#endif



//
//	���̑��̃w�b�_�t�@�C��
//
#include        "SfrRegister.h"        // �������W�X�^�A�h���X��`��
#include        "com.h"                // �ʐM�E�w�b�_��

#include        "weldtable.h"
#include        "wipcb.h"
#include        "sipcb.h"
#include        "inout.h"
#include        "ifdefine.h"

#include        "FPGA.h"               // �e�o�f�`����n�w�b�_��
#include        "hpiDSP.h"             // �c�r�o�|�g�o�h����n�w�b�_��
#include        "Timer.h"              // �t���[�����E�^�C�}�[�w�b�_��
#include        "ExternFunc.h"         // ���̑��̊O�����W���[���Q�Ɛ錾��
#include        "moddef.h"
#include        "dpr.h"


//#include        "iodefine.h" 			//2019.04.02

//--------- RTC by @Tny 2008/08/28 ------------
#if true
    #include    "I2C_RTC.h" // �h�Q�b�|�q�s�b�w�b�_
#endif
//--------------------------------------------

#ifndef __GLOBAL
	#include "extern.h"
#endif

//+++++ [2026.02.20]+++++
	#include "ANALOG.h"
//----- [2026.02.20]-----

//-------------------------------------------------
#endif	// __YD400GZ3_H

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of custom.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

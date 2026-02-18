//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//@yƒwƒbƒ_–¼z
//@@@‚d‚˜‚”‚…‚’‚‚e‚•‚‚ƒ
//@yƒwƒbƒ_ƒŒƒxƒ‹z
//@@@‚k‚d‚u‚d‚kF‚g|‚P
//  yƒwƒbƒ_à–¾z
//      ŠO•”ƒ‚ƒWƒ…[ƒ‹QÆéŒ¾
//  y”õlz
//      ‚È‚µ
//  yXV—š—ğz
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
#ifndef	__EXTERN_FUNC_H
//-------------------------------------------------
#define	__EXTERN_FUNC_H

#ifndef __SUB_MODULES_PROG	// ƒTƒuEƒ‚ƒWƒ…[ƒ‹Œn
	extern void initDelay(int Time);		// w’èŠÔ‘Ò‚¿i‰Šú‰»—pjˆ—
#endif	// __INITIAL_PROG
/*-------------------------------------------------------------------------*/
//LEVEL1
extern void             com_rcv_manager(void);
extern void             com_snd_manager(void);
extern void             error_manager(void);
extern void             initial_manager(void);
extern void             input_manager(void);
extern void             output_manager(void);
extern void             sequence_manager(void);
extern void             sequence_stop_manager(void);
extern void             memory_manager(void); //2008.08.07
//LEVEL2
#if true	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
	extern unsigned int     err_level0_class(void);
#else
	extern void             err_level0_class(void);
#endif
extern unsigned int     err_level1_class(void);
extern unsigned int     err_level2_class(void);
extern unsigned int     err_level3_class(void);
extern Bit16            err_process_class(unsigned int, Bit16);
extern void             ini_ad_class(void);
extern void             ini_com_set_class(void);
extern void             ini_fpga_dsp_class(void);
extern void             ini_io_class(void);
extern void             ini_memory_class(void);
extern void             ini_timer_class(void);
extern void             ini_interrupt_setting_class(void);
extern void             input_dsw_class(void);
extern void             input_ext_class(void);
extern void             input_r8_class(void);
extern void             input_fpga_class(void);
extern void             int_permit_class(void);
extern unsigned char    mag_sequence_dicision_class(unsigned char);
extern void             output_ext_class(Bit16, Bit16);
extern void             output_r8_class(unsigned char , unsigned int);
extern void             pc_snd_class(void);
extern void             rob_snd_class(void);
extern void             rob_pc_re_rcv_class(void);
extern void             table_access_class(ubool, unsigned char);
extern Bit16            weld_class (unsigned char , Bit16);
extern void             weld_test_class(void);
extern void             ext_device_ctrl_class(unsigned char);
extern void             ini_table_code_read_class(void);
extern void             ch0_write_class(unsigned char); //2008.08.07
extern void             ch_play_class(unsigned char);   //2008.08.07
extern void             ch_rec_class(unsigned char);    //2008.08.07
extern void             memory_initialize_class(unsigned char); //2008.09.04
#if true // « EXTERNAL IIF NEW	2011.02.21 by @Tny
	extern void             input_iif_analog_class(void);					//
	extern void             input_iif_class(void);     					    //
	extern void             iif_analog_shift_memory_class(unsigned char);	//
#endif // ª EXTERNAL IIF NEW	2011.02.21 by @Tny

//LEVEL3
extern unsigned char    arc_start_err_member(unsigned char);
extern unsigned char    cd_err_member(unsigned char);
extern unsigned char    com_err_member(unsigned char);
extern void             com_memory_member(ubool AllInitial);
extern int              dsp_code_transfer_member(void);
extern unsigned char    emg_err_member(unsigned char);
extern void             fix_data_transfer_member(void);
extern int              fpga_code_transfer_member(void);
extern unsigned char    gas_err_member(unsigned char);
extern void             hfix_data_transfer_member(ubool);
extern void             ini_data_member(void);
extern void             ini_TIOP5_member(void);
extern void             ini_TOP10_member(void);
extern void             ini_TOP67_member(void);
extern void             mag_ctrl_memory_member(void);
extern void             output_gas_member(Bit16, Bit16);
extern void             output_hf_member(Bit16, Bit16); //2009.01.31
extern void             output_inverter_ctrl_member(Bit16, Bit16);
extern void             output_mg_member(Bit16, Bit16);
extern void             output_motor_member(Bit16 , Bit16);
extern void             output_welder_ctrl_member(Bit16, Bit16);
extern void             output_stick_ctrl_member(Bit16, Bit16);
extern void             output_fan_member(Bit16 , Bit16);
extern void             output_err_alarm_member(void);
extern void             output_cd_member(void);
extern void             pc_com_set_member(void);
extern void             r8_com_set_member(void);
extern unsigned char    primary_voltage_err_member(unsigned char);
extern unsigned char    primary_current_err_member(unsigned char);
extern unsigned char    motor_current_err_member(unsigned char);
extern void             rob_com_set_member(void);
extern void             re_com_set_member(void);
extern unsigned char    second_current_err_member(unsigned char);
extern unsigned char    second_voltage_err_member(unsigned char);     //“ñŸ‰ß“dˆ³ˆÙí 2008.11.17
#if true	// <EXTERNAL IIF NEW(Phase 3)>	2011.10.13 by @Tny
	extern unsigned char    stick_err_member(unsigned char);
#else
	extern void             stick_err_member(void);
#endif
extern void             table_data_read_member(ubool,unsigned char);
extern unsigned char    temp_err_member(unsigned char);
extern unsigned char    ts_err_member(unsigned char);
extern unsigned char    water_err_member(unsigned char);
extern void             chattering_check_member(unsigned char);
//extern void             table_key_change_member(void);
extern void             table_key_change_member(unsigned char); //2007.2.9
extern void             okcv_generator_member(void);
extern void             fan_ctrl_member(unsigned char);
extern void             gas_ctrl_member(void);
extern void             table_code_read_member(void);
extern void             sp_table_code_read_member(void);
//extern void             attribute_set_member(void);
extern void             memory_read_member(unsigned char);  //2008.08.07
extern void             memory_write_member(unsigned char); //2008.08.07
extern void             en_generator_member(unsigned short,unsigned char); //2008.09.26
//extern void             v_generator_member(unsigned short,unsigned short,short); //2008.11.13
extern void             v_generator_member(unsigned short,short,short,short); //2008.11.28
extern void             ditail_set_member(signed char);     //2008.10.16
extern void             mix_ctrl_member(void); //2009.02.17

extern unsigned char    elrod_short_err_member(unsigned char); //“d‹É’Z—ˆÙíiƒƒ{ƒbƒgÚ‘±‚Ì‚İj2009.07.24

extern float            ac_frequency_limit_member(short); //‚`‚bü”g”‚Ì§Œä 2010.01.07 2010.01.21•ÏX

extern short            current_table_data_member(short); //ŠO•”‚©‚ç“ü—Í‚³‚ê‚½—nÚ“d—¬w—ß’l‚©‚ç“à•”‚Åg—p‚·‚é—nÚ“d—¬w—ß’l‚É•ÏŠ·‚·‚éB2010.02.19

#if true // « EXTERNAL IIF NEW	2011.02.21 by @Tny
	extern void             port_use_check_member(void);        //2009.10.15 IIF NEW
#endif // ª EXTERNAL IIF NEW	2011.02.21 by @Tny

//LEVEL4
extern void             pc_com_memory_submember(void);
extern void             rob_com_memory_submember(void);
//LEVEL ALL
extern void             rob_com_proc(void);
extern void             pc_com_proc(void);
extern void             re_com_proc(void);
extern void             I_V_READ(unsigned int);
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
extern void NormalInit( void );
extern void WeldAdjOut_Proc( int ); //ihara 2005.12.27
extern void wipInit( void );
extern void sipInit( void );
extern void Set_DCRPM( psint, psint);
extern void ctlclsWeldStart( void );
extern void ctlclsElectrode( void );


extern sint		ctlclsWeldGet( void );
extern sint		ctlclsVoltGet( void );
extern sint             ctlclsSpeedGet( void );
extern int		wipIP( sint WF , sint Volt , pusint pBuff );
extern int              sipIP( sint WF , pusint pBuff );
extern PWELDTABLE  getWeldTablePtr( void );
extern void		ctlclsDrctSet( void );
extern void		ctlclsWeldCondSet( sint Amp , sint Volt );
extern sint		GetAmp2Wire( sint Amp , PA2STBL pDat );
extern void		SetWeldStatus( int Sts );
extern void		SetMotorStatus( int Sts );
extern void             ctlclsStop( void ); //2006.2.15
extern void             ctlclsSrvStart(void);

extern void             wipReCalc( void );
extern void             wipReset( void );
extern void             sipReCalc( void );
extern void             sipReset( void );

extern void    wcndSend( void );
extern void    sspdSend( void );
extern void    DataUpdate( void );

extern int     WF2Volt( int );
extern int     WF_EN_Volt( int , unsigned char ); //‚d‚mˆêŒ³“dˆ³’lê—p 2008.09.26

//<><><>“d—¬•âŠÔ 2008.12.02<><><>
extern int      wipIP2( sint WF , sint CR , sint Volt , pusint pBuff );
extern sint		ctlclsWeldGet2( void );
//<><><><><><><><><><><><><><><>


extern        PWELDTABLE  GetWeldTable(void );  //test •œ‹A@2006.10.25

extern void   ctlclsDelayTimer(void);


//2008.09.11 extern usint	wcondBuff[ 64 ]; 
extern usint	wcondBuff[ 96 ]; //2008.09.11 ‰Â•Ï‚Q‘Î‰‚Ì‚½‚ß—ÌˆæŠm•Û
extern  usint   wspdBuff[ 8 ];

extern int     PushDI( void );
extern void    PopEI( int );


// BP4 Phase5 by @Tny 2009.01.21
extern void InitialStringInput(ubool Sw, ubool Pass, const char *InitialString);	// BP4 Phase13 by @Tny 2009.02.23
extern void StringInput_Rcv(ubool Sw1, ubool Sw2, unsigned char *StringStorageArea, unsigned short Length);

//-------------------------------------------------
// <IIF NEW>	2009.11.27
extern ubool IIF_ChangeSetting(void);	// ‚h‚h‚eİ’è•ÏXŠm”Fˆ—
extern void IIF_RestoresSetting(void);	// ‚h‚h‚e‹Œİ’è•œ‹Aˆ—

#endif	// __EXTERN_FUNC_H
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of ExternFunc.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

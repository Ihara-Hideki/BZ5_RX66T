/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : r_cg_interrupt_handlers.h
* Version          : 1.0.151
* Device(s)        : R5F566TKGxFB
* Description      : This file declares interrupt handlers.
***********************************************************************************************************************/

#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* RIIC0 RXI0 */
void r_Config_RIIC0_receive_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(RIIC0,RXI0))));

/* RIIC0 TXI0 */
void r_Config_RIIC0_transmit_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(RIIC0,TXI0))));

/* SCI1 RXI1 */
void r_Config_SCI1_receive_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI1,RXI1))));

/* SCI1 TXI1 */
void r_Config_SCI1_transmit_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI1,TXI1))));

/* SCI5 RXI5 */
void r_Config_SCI5_receive_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI5,RXI5))));

/* SCI5 TXI5 */
void r_Config_SCI5_transmit_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI5,TXI5))));

/* SCI8 RXI8 */
void r_Config_SCI8_receive_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI8,RXI8))));

/* SCI8 TXI8 */
void r_Config_SCI8_transmit_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI8,TXI8))));

/* SCI9 RXI9 */
void r_Config_SCI9_receive_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI9,RXI9))));

/* SCI9 TXI9 */
void r_Config_SCI9_transmit_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI9,TXI9))));

/* TMR0 CMIA0 */
void r_Config_TMR0_TMR1_cmia0_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(TMR0,CMIA0))));

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

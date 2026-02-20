/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : Pin.c
* Version          : 1.0.2
* Device(s)        : R5F566TKGxFB
* Description      : This file implements SMC pin code generation.
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Pins_Create
* Description  : This function initializes Smart Configurator pins
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Pins_Create(void)
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    /* Set AN000 pin */
    PORT4.PMR.BYTE &= 0xFEU;
    PORT4.PDR.BYTE &= 0xFEU;
    MPC.P40PFS.BYTE = 0x80U;

    /* Set AN001 pin */
    PORT4.PMR.BYTE &= 0xFDU;
    PORT4.PDR.BYTE &= 0xFDU;
    MPC.P41PFS.BYTE = 0x80U;

    /* Set AN002 pin */
    PORT4.PMR.BYTE &= 0xFBU;
    PORT4.PDR.BYTE &= 0xFBU;
    MPC.P42PFS.BYTE = 0x80U;

    /* Set AN003 pin */
    PORT4.PMR.BYTE &= 0xF7U;
    PORT4.PDR.BYTE &= 0xF7U;
    MPC.P43PFS.BYTE = 0x80U;

    /* Set AN004 pin */
    PORTH.PMR.BYTE &= 0xFDU;
    PORTH.PDR.BYTE &= 0xFDU;
    MPC.PH1PFS.BYTE = 0x80U;

    /* Set AN005 pin */
    PORTH.PMR.BYTE &= 0xFBU;
    PORTH.PDR.BYTE &= 0xFBU;
    MPC.PH2PFS.BYTE = 0x80U;

    /* Set AN006 pin */
    PORTH.PMR.BYTE &= 0xF7U;
    PORTH.PDR.BYTE &= 0xF7U;
    MPC.PH3PFS.BYTE = 0x80U;

    /* Set AN007 pin */
    PORTH.PMR.BYTE &= 0xFEU;
    PORTH.PDR.BYTE &= 0xFEU;
    MPC.PH0PFS.BYTE = 0x80U;

    /* Set AN100 pin */
    PORT4.PMR.BYTE &= 0xEFU;
    PORT4.PDR.BYTE &= 0xEFU;
    MPC.P44PFS.BYTE = 0x80U;

    /* Set AN101 pin */
    PORT4.PMR.BYTE &= 0xDFU;
    PORT4.PDR.BYTE &= 0xDFU;
    MPC.P45PFS.BYTE = 0x80U;

    /* Set AN102 pin */
    PORT4.PMR.BYTE &= 0xBFU;
    PORT4.PDR.BYTE &= 0xBFU;
    MPC.P46PFS.BYTE = 0x80U;

    /* Set AN103 pin */
    PORT4.PMR.BYTE &= 0x7FU;
    PORT4.PDR.BYTE &= 0x7FU;
    MPC.P47PFS.BYTE = 0x80U;

    /* Set AN107 pin */
    PORTH.PMR.BYTE &= 0xEFU;
    PORTH.PDR.BYTE &= 0xEFU;
    MPC.PH4PFS.BYTE = 0x80U;

    /* Set DA0 pin */
    PORT6.PMR.BYTE &= 0xEFU;
    PORT6.PDR.BYTE &= 0xEFU;
    MPC.P64PFS.BYTE = 0x80U;

    /* Set DA1 pin */
    PORT6.PMR.BYTE &= 0xDFU;
    PORT6.PDR.BYTE &= 0xDFU;
    MPC.P65PFS.BYTE = 0x80U;

    /* Set MTIOC4A pin */
    MPC.P72PFS.BYTE = 0x01U;
    PORT7.PMR.BYTE |= 0x04U;

    /* Set RXD1 pin */
    MPC.PC3PFS.BYTE = 0x0AU;
    PORTC.PMR.BYTE |= 0x08U;

    /* Set RXD5 pin */
    MPC.PB6PFS.BYTE = 0x0AU;
    PORTB.PMR.BYTE |= 0x40U;

    /* Set RXD8 pin */
    MPC.PC0PFS.BYTE = 0x0AU;
    PORTC.PMR.BYTE |= 0x01U;

    /* Set RXD9 pin */
    MPC.PG0PFS.BYTE = 0x0AU;
    PORTG.PMR.BYTE |= 0x01U;

    /* Set SCL pin */
    MPC.PB1PFS.BYTE = 0x0FU;
    PORTB.PMR.BYTE |= 0x02U;

    /* Set SDA pin */
    MPC.PB2PFS.BYTE = 0x0FU;
    PORTB.PMR.BYTE |= 0x04U;

    /* Set TXD1 pin */
    PORTC.PODR.BYTE |= 0x10U;
    MPC.PC4PFS.BYTE = 0x0AU;
    PORTC.PDR.BYTE |= 0x10U;
    // PORTC.PMR.BIT.B4 = 1U; // Please set the PMR bit after TE bit is set to 1.

    /* Set TXD5 pin */
    PORTB.PODR.BYTE |= 0x20U;
    MPC.PB5PFS.BYTE = 0x0AU;
    PORTB.PDR.BYTE |= 0x20U;
    // PORTB.PMR.BIT.B5 = 1U; // Please set the PMR bit after TE bit is set to 1.

    /* Set TXD8 pin */
    PORTC.PODR.BYTE |= 0x02U;
    MPC.PC1PFS.BYTE = 0x0AU;
    PORTC.PDR.BYTE |= 0x02U;
    // PORTC.PMR.BIT.B1 = 1U; // Please set the PMR bit after TE bit is set to 1.

    /* Set TXD9 pin */
    PORTG.PODR.BYTE |= 0x02U;
    MPC.PG1PFS.BYTE = 0x0AU;
    PORTG.PDR.BYTE |= 0x02U;
    // PORTG.PMR.BIT.B1 = 1U; // Please set the PMR bit after TE bit is set to 1.

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}


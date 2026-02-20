/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : Config_SCI1.c
* Component Version: 1.12.0
* Device(s)        : R5F566TKGxFB
* Description      : This file implements device driver for Config_SCI1.
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
#include "Config_SCI1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_sci1_tx_address;                /* SCI1 transmit buffer address */
volatile uint16_t  g_sci1_tx_count;                   /* SCI1 transmit data number */
volatile uint8_t * gp_sci1_rx_address;                /* SCI1 receive buffer address */
volatile uint16_t  g_sci1_rx_count;                   /* SCI1 receive data number */
volatile uint16_t  g_sci1_rx_length;                  /* SCI1 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Create
* Description  : This function initializes the SCI1 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_Create(void)
{
    /* Cancel SCI stop state */
    MSTP(SCI1) = 0U;

    /* Set interrupt priority */
    IPR(SCI1, RXI1) = _0F_SCI_PRIORITY_LEVEL15;
    IPR(SCI1, TXI1) = _0F_SCI_PRIORITY_LEVEL15;

    /* Clear the control register */
    SCI1.SCR.BYTE = 0x00U;

    /* Set clock enable */
    SCI1.SCR.BYTE = _00_SCI_INTERNAL_SCK_UNUSED;

    /* Clear the SIMR1.IICM, SPMR.CKPH, and CKPOL bit, and set SPMR */
    SCI1.SIMR1.BIT.IICM = 0U;
    SCI1.SPMR.BYTE = _00_SCI_RTS | _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;

    /* Set control registers */
    SCI1.SMR.BYTE = _02_SCI_CLOCK_PCLK_16 | _00_SCI_MULTI_PROCESSOR_DISABLE | _00_SCI_STOP_1 | 
                    _00_SCI_PARITY_DISABLE | _00_SCI_DATA_LENGTH_8 | _00_SCI_ASYNCHRONOUS_OR_I2C_MODE;
    SCI1.SCMR.BYTE = _00_SCI_SERIAL_MODE | _00_SCI_DATA_INVERT_NONE | _00_SCI_DATA_LSB_FIRST | 
                     _10_SCI_DATA_LENGTH_8_OR_7 | _62_SCI_SCMR_DEFAULT;
    SCI1.SEMR.BYTE = _00_SCI_BIT_MODULATION_DISABLE | _08_SCI_6_BASE_CLOCK | _00_SCI_NOISE_FILTER_DISABLE | 
                     _00_SCI_LOW_LEVEL_START_BIT;

    /* Set bit rate */
    SCI1.BRR = 0x40U;

    /* Set RXD1 pin */
    MPC.PC3PFS.BYTE = 0x0AU;
    PORTC.PMR.BYTE |= 0x08U;

    /* Set TXD1 pin */
    MPC.PC4PFS.BYTE = 0x0AU;
    PORTC.PODR.BYTE |= 0x10U;
    PORTC.PDR.BYTE |= 0x10U;

    R_Config_SCI1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Start
* Description  : This function starts the SCI1 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI1, TXI1) = 0U;
    IR(SCI1, RXI1) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI1, TXI1) = 1U;
    ICU.GENBL0.BIT.EN2 = 1U;
    IEN(SCI1, RXI1) = 1U;
    ICU.GENBL0.BIT.EN3 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Stop
* Description  : This function stop the SCI1 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_Stop(void)
{
    /* Set TXD1 pin */
    PORTC.PMR.BYTE &= 0xEFU;

    /* Disable serial transmit */
    SCI1.SCR.BIT.TE = 0U;

    /* Disable serial receive */
    SCI1.SCR.BIT.RE = 0U;

    /* Disable SCI interrupt */
    SCI1.SCR.BIT.TIE = 0U;
    SCI1.SCR.BIT.RIE = 0U;
    IEN(SCI1, TXI1) = 0U;
    ICU.GENBL0.BIT.EN2 = 0U;
    IR(SCI1, TXI1) = 0U;
    IEN(SCI1, RXI1) = 0U;
    ICU.GENBL0.BIT.EN3 = 0U;
    IR(SCI1, RXI1) = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Serial_Receive
* Description  : This function receive SCI1data
* Arguments    : rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DMAC/DTC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DMAC/DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/

MD_STATUS R_Config_SCI1_Serial_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (1U > rx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_sci1_rx_count = 0U;
        g_sci1_rx_length = rx_num;
        gp_sci1_rx_address = rx_buf;
        SCI1.SCR.BIT.RIE = 1U;
        SCI1.SCR.BIT.RE = 1U;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Serial_Send
* Description  : This function transmits SCI1 data
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DMAC/DTC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DMAC/DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR or MD_ERROR
***********************************************************************************************************************/

MD_STATUS R_Config_SCI1_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (1U > tx_num)
    {
        status = MD_ARGERROR;
    }
    else if (0U == IEN(SCI1, TXI1))
    {
        status = MD_ERROR;
    }
    else
    {
        gp_sci1_tx_address = tx_buf;
        g_sci1_tx_count = tx_num;
        IEN(SCI1, TXI1) = 0U;
        SCI1.SCR.BYTE |= 0xA0U;

        /* Set TXD1 pin */
        PORTC.PMR.BYTE |= 0x10U;
        IEN(SCI1, TXI1) = 1U;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

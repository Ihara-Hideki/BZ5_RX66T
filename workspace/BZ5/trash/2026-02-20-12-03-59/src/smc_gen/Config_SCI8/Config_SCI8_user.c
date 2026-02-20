/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : Config_SCI8_user.c
* Component Version: 1.12.0
* Device(s)        : R5F566TKGxFB
* Description      : This file implements device driver for Config_SCI8.
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
#include "Config_SCI8.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_sci8_tx_address;                /* SCI8 transmit buffer address */
extern volatile uint16_t  g_sci8_tx_count;                   /* SCI8 transmit data number */
extern volatile uint8_t * gp_sci8_rx_address;                /* SCI8 receive buffer address */
extern volatile uint16_t  g_sci8_rx_count;                   /* SCI8 receive data number */
extern volatile uint16_t  g_sci8_rx_length;                  /* SCI8 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI8_Create_UserInit
* Description  : This function adds user code after initializing the SCI8 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI8_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI8_transmit_interrupt
* Description  : This function is TXI8 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void r_Config_SCI8_transmit_interrupt(void)
{
    if (0U < g_sci8_tx_count)
    {
        SCI8.TDR = *gp_sci8_tx_address;
        gp_sci8_tx_address++;
        g_sci8_tx_count--;
    }
    else
    {
        SCI8.SCR.BIT.TIE = 0U;
        SCI8.SCR.BIT.TEIE = 1U;
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI8_transmitend_interrupt
* Description  : This function is TEI8 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void r_Config_SCI8_transmitend_interrupt(void)
{
    /* Set TXD8 pin */
    PORTC.PMR.BYTE &= 0xFDU;

    SCI8.SCR.BIT.TIE = 0U;
    SCI8.SCR.BIT.TE = 0U;
    SCI8.SCR.BIT.TEIE = 0U;
    
    r_Config_SCI8_callback_transmitend();
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI8_receive_interrupt
* Description  : This function is RXI8 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void r_Config_SCI8_receive_interrupt(void)
{
    if (g_sci8_rx_length > g_sci8_rx_count)
    {
        *gp_sci8_rx_address = SCI8.RDR;
        gp_sci8_rx_address++;
        g_sci8_rx_count++;
    }
    
    if (g_sci8_rx_length <= g_sci8_rx_count)
    {
        /* All data received */
        SCI8.SCR.BIT.RIE = 0U;
        SCI8.SCR.BIT.RE = 0U;
        r_Config_SCI8_callback_receiveend();
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI8_receiveerror_interrupt
* Description  : This function is ERI8 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void r_Config_SCI8_receiveerror_interrupt(void)
{
    uint8_t err_type;
    
    r_Config_SCI8_callback_receiveerror();
    
    /* Clear overrun, framing and parity error flags */
    err_type = SCI8.SSR.BYTE;
    err_type &= 0xC7U;
    err_type |= 0xC0U;
    SCI8.SSR.BYTE = err_type;
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI8_callback_transmitend
* Description  : This function is a callback function when SCI8 finishes transmission
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

static void r_Config_SCI8_callback_transmitend(void)
{
    /* Start user code for r_Config_SCI8_callback_transmitend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI8_callback_receiveend
* Description  : This function is a callback function when SCI8 finishes reception
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

static void r_Config_SCI8_callback_receiveend(void)
{
    /* Start user code for r_Config_SCI8_callback_receiveend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI8_callback_receiveerror
* Description  : This function is a callback function when SCI8 reception encounters error
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

static void r_Config_SCI8_callback_receiveerror(void)
{
    /* Start user code for r_Config_SCI8_callback_receiveerror. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

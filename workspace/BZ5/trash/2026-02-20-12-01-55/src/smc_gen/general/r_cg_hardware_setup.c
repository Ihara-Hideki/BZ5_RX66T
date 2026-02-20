/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : r_cg_hardware_setup.c
* Version          : 1.0.151
* Device(s)        : R5F566TKGxFB
* Description      : Initialization file for code generation configurations.
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
#include "Config_MTU4.h"
#include "Config_TMR0_TMR1.h"
#include "Config_S12AD1.h"
#include "Config_S12AD0.h"
#include "Config_DA.h"
#include "Config_SCI1.h"
#include "Config_SCI5.h"
#include "Config_SCI8.h"
#include "Config_SCI9.h"
#include "Config_RIIC0.h"
#include "Config_PORT.h"
#include "r_smc_cgc.h"
#include "r_smc_interrupt.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_undefined_exception
* Description  : This function is undefined interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following function in the bootloader project. */
void r_undefined_exception(void)
{
    /* Start user code for r_undefined_exception. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

/***********************************************************************************************************************
* Function Name: R_Systeminit
* Description  : This function initializes every configuration
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Systeminit(void)
{
    /* Enable writing to registers related to operating modes, LPC, CGC and software reset */
    SYSTEM.PRCR.WORD = 0xA50BU;

    /* Enable writing to MPC pin function control registers */
    MPC.PWPR.BIT.B0WI = 0U;
    MPC.PWPR.BIT.PFSWE = 1U;

#if BSP_CFG_BOOTLOADER_PROJECT == 0
    /* Disable the following codes in the bootloader project. */
    /* Write 0 to the target bits in the POECR2 registers */
    POE.POECR2.WORD = 0x0000U;
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

    /* Initialize clocks settings */
    R_CGC_Create();

    /* Set peripheral settings */
    R_Config_PORT_Create();
    R_Config_MTU4_Create();
    R_Config_TMR0_TMR1_Create();
    R_Config_S12AD1_Create();
    R_Config_S12AD0_Create();
    R_Config_DA_Create();
    R_Config_SCI1_Create();
    R_Config_SCI5_Create();
    R_Config_SCI8_Create();
    R_Config_SCI9_Create();
    R_Config_RIIC0_Create();

    /* Set interrupt settings */
    R_Interrupt_Create();

#if BSP_CFG_BOOTLOADER_PROJECT == 0
    /* Disable the following codes in the bootloader project. */
    /* Register undefined interrupt */
    R_BSP_InterruptWrite(BSP_INT_SRC_UNDEFINED_INTERRUPT,(bsp_int_cb_t)r_undefined_exception);
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

    /* Register group BL0 interrupt TEI1 (SCI1) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI1_TEI1,(bsp_int_cb_t)r_Config_SCI1_transmitend_interrupt);

    /* Register group BL0 interrupt ERI1 (SCI1) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI1_ERI1,(bsp_int_cb_t)r_Config_SCI1_receiveerror_interrupt);

    /* Register group BL0 interrupt TEI5 (SCI5) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI5_TEI5,(bsp_int_cb_t)r_Config_SCI5_transmitend_interrupt);

    /* Register group BL0 interrupt ERI5 (SCI5) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI5_ERI5,(bsp_int_cb_t)r_Config_SCI5_receiveerror_interrupt);

    /* Register group BL1 interrupt TEI0 (RIIC0) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_TEI0,(bsp_int_cb_t)r_Config_RIIC0_transmitend_interrupt);

    /* Register group BL1 interrupt EEI0 (RIIC0) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_EEI0,(bsp_int_cb_t)r_Config_RIIC0_error_interrupt);

    /* Register group BL1 interrupt TEI8 (SCI8) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_SCI8_TEI8,(bsp_int_cb_t)r_Config_SCI8_transmitend_interrupt);

    /* Register group BL1 interrupt ERI8 (SCI8) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_SCI8_ERI8,(bsp_int_cb_t)r_Config_SCI8_receiveerror_interrupt);

    /* Register group BL1 interrupt TEI9 (SCI9) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_SCI9_TEI9,(bsp_int_cb_t)r_Config_SCI9_transmitend_interrupt);

    /* Register group BL1 interrupt ERI9 (SCI9) */
    R_BSP_InterruptWrite(BSP_INT_SRC_BL1_SCI9_ERI9,(bsp_int_cb_t)r_Config_SCI9_receiveerror_interrupt);

    /* Disable writing to MPC pin function control registers */
    MPC.PWPR.BIT.PFSWE = 0U;
    MPC.PWPR.BIT.B0WI = 1U;

    /* Enable protection */
    SYSTEM.PRCR.WORD = 0xA500U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

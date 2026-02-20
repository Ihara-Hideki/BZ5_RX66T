/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : Config_TMR0_TMR1.c
* Component Version: 1.10.0
* Device(s)        : R5F566TKGxFB
* Description      : This file implements device driver for Config_TMR0_TMR1.
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
#include "Config_TMR0_TMR1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TMR0_TMR1_Create
* Description  : This function initializes the TMR0 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_TMR0_TMR1_Create(void)
{
    /* Disable TMR0 interrupts */
    IEN(TMR0, CMIA0) = 0U;

    /* Cancel TMR module stop state */
    MSTP(TMR0) = 0U;

    /* Set timer counter control setting */
    TMR0.TCCR.BYTE = _18_TMR_CLK_TMR1_OVRF | _00_TMR_CLK_DISABLED;

    /* Set counter clear and interrupt */
    TMR0.TCR.BYTE = _40_TMR_CMIA_INT_ENABLE | _08_TMR_CNT_CLR_COMP_MATCH_A | _00_TMR_CMIB_INT_DISABLE | 
                    _00_TMR_OVI_INT_DISABLE;

    /* Set A/D trigger and output */
    TMR0.TCSR.BYTE = _00_TMR_AD_TRIGGER_DISABLE | _E0_TMR02_TCSR_DEFAULT;

    /* Set compare match value */
    TMR01.TCORA = _176F_TMR01_COMP_MATCH_VALUE_A;
    TMR01.TCORB = _0077_TMR01_COMP_MATCH_VALUE_B;

    /* Configure TMR0 interrupts */
    IPR(TMR0, CMIA0) = _0A_TMR_PRIORITY_LEVEL10;

    R_Config_TMR0_TMR1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TMR0_TMR1_Start
* Description  : This function starts the TMR0 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_TMR0_TMR1_Start(void)
{
    /* Enable TMR0 interrupt */
    IR(TMR0, CMIA0) = 0U;
    IEN(TMR0, CMIA0) = 1U;

    /* Start counting */
    TMR1.TCCR.BYTE = _08_TMR_CLK_SRC_PCLK | _00_TMR_PCLK_DIV_1;
}

/***********************************************************************************************************************
* Function Name: R_Config_TMR0_TMR1_Stop
* Description  : This function stops the TMR0 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_TMR0_TMR1_Stop(void)
{
    /* Disable TMR0 interrupt */
    IEN(TMR0, CMIA0) = 0U;

    /* Stop counting */
    TMR1.TCCR.BYTE = _00_TMR_CLK_DISABLED;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

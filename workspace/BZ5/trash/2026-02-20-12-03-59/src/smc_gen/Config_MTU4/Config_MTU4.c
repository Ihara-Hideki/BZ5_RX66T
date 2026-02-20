/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : Config_MTU4.c
* Component Version: 1.12.0
* Device(s)        : R5F566TKGxFB
* Description      : This file implements device driver for Config_MTU4.
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MTU4_Create
* Description  : This function initializes the MTU4 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU4_Create(void)
{
    /* Release MTU channel 4 from stop state */
    MSTP(MTU4) = 0U;

    /* Enable read/write to MTU4 registers */
    MTU.TRWERA.BIT.RWE = 1U;

    /* Stop MTU channel 4 counter */
    MTU.TSTRA.BIT.CST4 = 0U;

    /* Set A/D conversion signal output for ADSM0, ADSM1 pins */
    MTU.TADSTRGR0.BYTE = _00_MTU_TADSMEN_DISABLE;
    MTU.TADSTRGR1.BYTE = _00_MTU_TADSMEN_DISABLE;

    /* MTU channel 4 is used as PWM mode 1 */
    MTU.TSYRA.BIT.SYNC4 = 0U;
    MTU.TOERA.BYTE |= (_C2_MTU_OE4A_ENABLE);
    MTU4.TCR.BYTE = _05_MTU_PCLK_1024 | _00_MTU_CKEG_RISE | _20_MTU_CKCL_A;
    MTU4.TCR2.BYTE = _00_MTU_PCLK_1;
    MTU4.TIER.BYTE = _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                     _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU4.TMDR1.BYTE = _02_MTU_PWM1;
    MTU4.TIORH.BYTE = _01_MTU_IOA_LL | _60_MTU_IOB_HH;
    MTU4.TIORL.BYTE = _00_MTU_IOC_DISABLE;
    MTU4.TGRA = _FE83_TGRA4_VALUE;
    MTU4.TGRB = _7F41_TGRB4_VALUE;
    MTU4.TGRC = _0000_TGRC4_VALUE;
    MTU4.TGRD = _0000_TGRD4_VALUE;

    /* Disable read/write to MTU4 registers */
    MTU.TRWERA.BIT.RWE = 0U;

    /* Set MTIOC4A pin */
    MPC.P72PFS.BYTE = 0x01U;
    PORT7.PMR.BYTE |= 0x04U;

    R_Config_MTU4_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU4_Start
* Description  : This function starts the MTU4 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU4_Start(void)
{
    /* Start MTU channel 4 counter */
    MTU.TSTRA.BIT.CST4 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU4_Stop
* Description  : This function stops the MTU4 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU4_Stop(void)
{
    /* Stop MTU channel 4 counter */
    MTU.TSTRA.BIT.CST4 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

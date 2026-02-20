/*
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
* File Name        : Config_PORT.c
* Component Version: 2.4.1
* Device(s)        : R5F566TKGxFB
* Description      : This file implements device driver for Config_PORT.
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
#include "Config_PORT.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_PORT_Create
* Description  : This function initializes the PORT
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_PORT_Create(void)
{
    /* Set PORT1 registers */
    PORT1.PODR.BYTE = _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0;
    PORT1.ODR0.BYTE = _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT1.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT;
    PORT1.PCR.BYTE = _00_Pm0_PULLUP_OFF | _00_Pm1_PULLUP_OFF | _00_Pm5_PULLUP_OFF | _00_Pm6_PULLUP_OFF | 
                     _00_Pm7_PULLUP_OFF;
    PORT1.DSCR.BYTE = _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | _00_Pm4_HIDRV_OFF;
    PORT1.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm5_PIN_GPIO | 
                     _00_Pm6_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORT1.PDR.BYTE = _00_Pm0_MODE_INPUT | _00_Pm1_MODE_INPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _00_Pm5_MODE_INPUT | _00_Pm6_MODE_INPUT | _00_Pm7_MODE_INPUT;

    /* Set PORT2 registers */
    PORT2.PODR.BYTE = _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm5_OUTPUT_0 | _00_Pm6_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORT2.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT2.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORT2.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF | _00_Pm7_HIDRV_OFF;
    PORT2.PMR.BYTE = _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORT2.PDR.BYTE = _08_Pm3_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _40_Pm6_MODE_OUTPUT | 
                     _80_Pm7_MODE_OUTPUT;

    /* Set PORT3 registers */
    PORT3.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0;
    PORT3.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT3.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORT3.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF;
    PORT3.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO;
    PORT3.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT;

    /* Set PORT7 registers */
    PORT7.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm6_OUTPUT_0;
    PORT7.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT7.ODR1.BYTE = _00_Pm6_CMOS_OUTPUT;
    PORT7.PCR.BYTE = _00_Pm4_PULLUP_OFF | _00_Pm5_PULLUP_OFF;
    PORT7.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | _00_Pm6_HIDRV_OFF;
    PORT7.DSCR2.BYTE = _00_Pm1_LARGECUR_OFF | _00_Pm2_LARGECUR_OFF | _00_Pm3_LARGECUR_OFF | _00_Pm6_LARGECUR_OFF;
    PORT7.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO | 
                     _00_Pm6_PIN_GPIO;
    PORT7.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | _00_Pm4_MODE_INPUT | 
                     _00_Pm5_MODE_INPUT | _40_Pm6_MODE_OUTPUT;

    /* Set PORT8 registers */
    PORT8.ODR0.BYTE = _00_Pm2_CMOS_OUTPUT;
    PORT8.PCR.BYTE = _00_Pm0_PULLUP_OFF | _00_Pm1_PULLUP_OFF;
    PORT8.DSCR.BYTE = _00_Pm2_HIDRV_OFF;
    PORT8.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO;
    PORT8.PDR.BYTE = _00_Pm0_MODE_INPUT | _00_Pm1_MODE_INPUT;

    /* Set PORT9 registers */
    PORT9.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm5_OUTPUT_0 | 
                      _00_Pm6_OUTPUT_0;
    PORT9.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT9.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT;
    PORT9.PCR.BYTE = _00_Pm1_PULLUP_OFF;
    PORT9.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | _00_Pm4_HIDRV_OFF | 
                      _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF;
    PORT9.DSCR2.BYTE = _00_Pm0_LARGECUR_OFF | _00_Pm2_LARGECUR_OFF | _00_Pm3_LARGECUR_OFF | _00_Pm4_LARGECUR_OFF | 
                       _00_Pm5_LARGECUR_OFF;
    PORT9.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO;
    PORT9.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _00_Pm1_MODE_INPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _40_Pm6_MODE_OUTPUT;

    /* Set PORTC registers */
    PORTC.PODR.BYTE = _00_Pm2_OUTPUT_0 | _00_Pm5_OUTPUT_0 | _00_Pm6_OUTPUT_0;
    PORTC.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTC.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT;
    PORTC.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF;
    PORTC.PMR.BYTE = _00_Pm2_PIN_GPIO | _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO;
    PORTC.PDR.BYTE = _04_Pm2_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _40_Pm6_MODE_OUTPUT;

    /* Set PORTD registers */
    PORTD.ODR0.BYTE = _00_Pm3_CMOS_OUTPUT;
    PORTD.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORTD.PCR.BYTE = _00_Pm0_PULLUP_OFF | _00_Pm1_PULLUP_OFF | _00_Pm2_PULLUP_OFF;
    PORTD.DSCR.BYTE = _00_Pm3_HIDRV_OFF | _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF | _00_Pm7_HIDRV_OFF;
    PORTD.DSCR2.BYTE = _00_Pm3_LARGECUR_OFF;
    PORTD.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO;
    PORTD.PDR.BYTE = _00_Pm0_MODE_INPUT | _00_Pm1_MODE_INPUT | _00_Pm2_MODE_INPUT;

    /* Set PORTE registers */
    PORTE.PODR.BYTE = _00_Pm3_OUTPUT_0;
    PORTE.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTE.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT;
    PORTE.PCR.BYTE = _00_Pm5_PULLUP_OFF | _00_Pm6_PULLUP_OFF;
    PORTE.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm3_HIDRV_OFF | _00_Pm4_HIDRV_OFF;
    PORTE.PMR.BYTE = _00_Pm3_PIN_GPIO | _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO;
    PORTE.PDR.BYTE = _08_Pm3_MODE_OUTPUT | _00_Pm5_MODE_INPUT | _00_Pm6_MODE_INPUT;

    /* Set PORTF registers */
    PORTF.PCR.BYTE = _00_Pm0_PULLUP_OFF | _00_Pm1_PULLUP_OFF | _00_Pm2_PULLUP_OFF | _00_Pm3_PULLUP_OFF;
    PORTF.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO;
    PORTF.PDR.BYTE = _00_Pm0_MODE_INPUT | _00_Pm1_MODE_INPUT | _00_Pm2_MODE_INPUT | _00_Pm3_MODE_INPUT;

    /* Set PORTG registers */
    PORTG.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT;
    PORTG.PCR.BYTE = _00_Pm2_PULLUP_OFF;
    PORTG.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF;
    PORTG.PMR.BYTE = _00_Pm2_PIN_GPIO;
    PORTG.PDR.BYTE = _00_Pm2_MODE_INPUT;

    /* Set PORTK registers */
    PORTK.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0;
    PORTK.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT;
    PORTK.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF;
    PORTK.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO;
    PORTK.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT;

    R_Config_PORT_Create_UserInit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

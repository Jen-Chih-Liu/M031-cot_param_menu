/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 11 $
 * $Date: 18/07/26 12:22p $
 * @brief    Demonstrate how to implement a USB virtual com port device.
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "cot_menu.h"
#include "mainhmi.h"
#include <stdio.h>
#include <string.h>

int isEnterMenu = 0;

void EnterMainMenu(void)
{
    isEnterMenu = 1;
}

void ExitMainMenu(void)
{
    isEnterMenu = 0;
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HIRC clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Waiting for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Switch HCLK clock source to HIRC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Switch UART0 clock source to HIRC */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Enable UART0 clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Switch USB clock source to HIRC & USB Clock = HIRC / 1 */
    CLK_SetModuleClock(USBD_MODULE, CLK_CLKSEL0_USBDSEL_HIRC, CLK_CLKDIV0_USB(1));

    /* Enable USB clock */
    CLK_EnableModuleClock(USBD_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set PB multi-function pins for UART0 RXD=PB.12 and TXD=PB.13 */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk))
                    | (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}
int32_t main(void)
{
#if CRYSTAL_LESS
    uint32_t u32TrimInit;
#endif

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("+------------------------------------------------------------+\n");
    printf("|            NuMicro USB CDC One Port Sample Code            |\n");
    printf("+------------------------------------------------------------+\n");
	  int cmd = 0;
    int8_t musicMenuId, languageMenuId, moreSetMenuId;
    
    MainMenuCfg_t tMainMenu = {{"主菜单", "Main Menu"}, EnterMainMenu, ExitMainMenu, Hmi_LoadMainHmi, Hmi_MainTask};

    cotMenu_Init(&tMainMenu);
    
    while (1)
    {
        CLEAR();
        MOVETO(0, 0);

        if (!isEnterMenu)
        {
            printf("选择操作(0-进入主菜单; 1-退出): ");
            scanf(" %d", &cmd); // 空格作用是忽略上次的回车

            if (cmd == 0)
            {
                cotMenu_MainEnter();

                CLEAR();
                MOVETO(0, 0);
            }
            else if (cmd == 1)
            {
                break;
            }
        }

        cotMenu_Task();
    }

    cotMenu_DeInit();

while(1);
}



/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/


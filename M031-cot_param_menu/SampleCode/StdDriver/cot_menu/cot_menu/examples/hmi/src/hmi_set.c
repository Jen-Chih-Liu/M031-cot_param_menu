#include "hmi_set.h"
#include "hmi_more_set.h"
#include "cot_menu.h"
#include <stdio.h>
#include <string.h>


const MenuImage_t sgc_SettingImage = {
"$$$$$$$$$$",
"%"
};

static void OnLanguageFunction(void);
static void OnBluetoothFunction(void);
static void OnBatteryFunction(void);
static void OnStorageFunction(void);

/* 设置菜单 */
MenuList_t sg_SetMenuTable[] = 
{
    {{"语言", "Language"},   NULL, NULL, NULL, OnLanguageFunction, NULL},
    {{"蓝牙", "Bluetooth"},  NULL, NULL, NULL, OnBluetoothFunction, NULL},
    {{"电池", "Battery"},    NULL, NULL, NULL, OnBatteryFunction, NULL},
    {{"储存", "Store"},      NULL, NULL, NULL, OnStorageFunction, NULL},
    {{"更多", "More"},       Hmi_MoreSetEnter, Hmi_MoreSetExit, Hmi_MoreSetLoad, Hmi_MoreSetTask, NULL},
};

/* 设置菜单显示效果 */
static void ShowSetMenu(MenuShow_t *ptShowInfo)
{
    uint8_t showNum = 3;
    menusize_t  tmpselect;

    cotMenu_LimitShowListNum(ptShowInfo, &showNum);

    printf("\e[0;30;46m ------------- %s ------------- \e[0m\n", ptShowInfo->pszDesc);

    for (int i = 0; i < showNum; i++)
    {
        tmpselect = i + ptShowInfo->showBaseItem;

        if (tmpselect == ptShowInfo->selectItem)
        {
            printf("\e[0;30;47m %d. %-16s\e[0m |\n", tmpselect + 1, ptShowInfo->pszItemsDesc[tmpselect]);
        }
        else
        {
            printf("\e[7;30;47m %d. %-16s\e[0m |\n", tmpselect + 1, ptShowInfo->pszItemsDesc[tmpselect]);
        }
    }
}

void Hmi_SetEnter(void)
{
    cotMenu_Bind(sg_SetMenuTable, GET_MENU_NUM(sg_SetMenuTable), ShowSetMenu);
}

void Hmi_SetLoad(void)
{
    
}

void Hmi_SetExit(void)
{

}

void Hmi_SetTask(void)
{
    int cmd;

    printf("选择操作(0-返回; 1-返回主菜单; 2-进入; 3-下一个; 4-上一个): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车
 
    switch (cmd)
    {
    case 0:
        cotMenu_Exit(false);
        break;
    case 1:
        cotMenu_Reset();
        break;
    case 2:
        cotMenu_Enter();
        break;
    case 3:
        cotMenu_SelectNext(true);
        break;
    case 4:
        cotMenu_SelectPrevious(true);
        break;

    default:
        break;    
    }
}


static void OnLanguageFunction(void)
{
    int cmd;

    printf("--------------------------\n");
    printf("     语言功能测试界面\n");
    printf("--------------------------\n");
    
    printf("选择操作(0-中文; 1-English): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车

    if (cmd == 0)
    {
        cotMenu_SelectLanguage(0);
    }
    else
    {
        cotMenu_SelectLanguage(1);
    }

    cotMenu_Exit(0); // 切换后自动退出
}

static void OnBluetoothFunction(void)
{
    int cmd;

    printf("--------------------------\n");
    printf("     蓝牙功能测试界面\n");
    printf("--------------------------\n");

    printf("选择操作(0-退出): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车

    if (cmd == 0)
    {
        cotMenu_Exit(false);
    }
}

static void OnBatteryFunction(void)
{
    int cmd;

    printf("--------------------------\n");
    printf("     电池功能测试界面\n");
    printf("--------------------------\n");

    printf("选择操作(0-退出): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车

    if (cmd == 0)
    {
        cotMenu_Exit(false);
    }
}

static void OnStorageFunction(void)
{
    int cmd;

    printf("--------------------------\n");
    printf("     储存功能测试界面\n");
    printf("--------------------------\n");

    printf("选择操作(0-退出): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车

    if (cmd == 0)
    {
        cotMenu_Exit(false);
    }
}
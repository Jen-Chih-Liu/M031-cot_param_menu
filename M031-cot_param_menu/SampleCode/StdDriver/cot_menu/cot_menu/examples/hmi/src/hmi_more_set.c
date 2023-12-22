#include "hmi_more_set.h"
#include "cot_menu.h"
#include <stdio.h>
#include <string.h>


static void OnUpgradeFunction(void);
static void OnAboutMenuFunction(void);


/* 更多设置 */
MenuList_t sg_MoreSetMenuTable[] = 
{
    {{"升级", "Upgrade"}, NULL, NULL, NULL, OnUpgradeFunction, NULL},
    {{"关于", "About"},   NULL, NULL, NULL, OnAboutMenuFunction, NULL},
};

/* 更多设置菜单显示效果: 右侧弹出菜单效果 */
static void ShowMoreSetMenu(MenuShow_t *ptShowInfo)
{
    uint8_t showNum = 3;
    uint8_t showsubNum = 3;
    menusize_t  tmpselect;

    MenuShow_t tParentMenuShowInfo;

    if (cotMenu_QueryParentMenu(&tParentMenuShowInfo, 1) != 0)
    {
        return;
    }

    cotMenu_LimitShowListNum(&tParentMenuShowInfo, &showNum);
    cotMenu_LimitShowListNum(ptShowInfo, &showsubNum);

    printf("\e[0;30;46m ------------- %s ------------- \e[0m\n", tParentMenuShowInfo.pszDesc);

    for (int i = 0; i < showNum; i++)
    {
        tmpselect = i + tParentMenuShowInfo.showBaseItem;

        if (tmpselect == tParentMenuShowInfo.selectItem)
        {
            printf("\e[0;30;47m %d. %-16s\e[0m |", tmpselect + 1, tParentMenuShowInfo.pszItemsDesc[tmpselect]);
        }
        else
        {
            printf("\e[7;30;47m %d. %-16s\e[0m |", tmpselect + 1, tParentMenuShowInfo.pszItemsDesc[tmpselect]);
        }

        if (i < showsubNum)
        {
            tmpselect = i + ptShowInfo->showBaseItem;

            if (tmpselect == ptShowInfo->selectItem)
            {
                printf(" \e[0;30;47m %-14s\e[0m", ptShowInfo->pszItemsDesc[tmpselect]);
            }
            else
            {
                printf(" \e[7;30;47m %-14s\e[0m", ptShowInfo->pszItemsDesc[tmpselect]);
            }
        }

        printf("\n");
    }   
}

void Hmi_MoreSetEnter(void)
{
    cotMenu_Bind(sg_MoreSetMenuTable, GET_MENU_NUM(sg_MoreSetMenuTable), ShowMoreSetMenu);
}

void Hmi_MoreSetLoad(void)
{

}

void Hmi_MoreSetExit(void)
{

}

void Hmi_MoreSetTask(void)
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


static void OnUpgradeFunction(void)
{
    int cmd;

    printf("--------------------------\n");
    printf("     升级升级测试界面\n");
    printf("--------------------------\n");
    
    printf("选择操作(0-退出): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车

    if (cmd == 0)
    {
        cotMenu_Exit(false);
    }
}

static void OnAboutMenuFunction(void)
{
    int cmd;

    printf("--------------------------\n");
    printf("     关于菜单框架界面\n");
    printf("--------------------------\n");

    printf("选择操作(0-退出): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车

    if (cmd == 0)
    {
        cotMenu_Exit(false);
    }
}

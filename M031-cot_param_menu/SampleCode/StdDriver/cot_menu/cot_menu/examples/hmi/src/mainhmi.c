#include "mainhmi.h"
#include "hmi_camera.h"
#include "hmi_music.h"
#include "hmi_set.h"
#include "hmi_video.h"
#include "hmi_common.h"
#include "cot_menu.h"
#include <stdio.h>
#include <string.h>



/* 主菜单 */
MenuList_t sg_MainMenuTable[] = 
{
    {{"  音乐  ", "  Music "},  Hmi_MusicEnter, Hmi_MusicExit, Hmi_MusicLoad, Hmi_MusicTask, (MenuImage_t *)&sgc_MusicImage},
    
    {{"  视频  ", "  Video "},  NULL, Hmi_VideoExit, Hmi_VideoLoad, Hmi_VideoTask, (MenuImage_t *)&sgc_VideoImage},
    
    {{" 摄像机 ", " Camera "},  Hmi_CameraEnter, Hmi_CameraExit, Hmi_CameraLoad, Hmi_CameraTask, (MenuImage_t *)&sgc_CameraImage},
    
    {{"  设置  ", " Setting"},  Hmi_SetEnter, Hmi_SetExit, Hmi_SetLoad,   Hmi_SetTask, (MenuImage_t *)&sgc_SettingImage},
};



/* 主菜单显示效果 */
static void ShowMainMenu(MenuShow_t *ptShowInfo)
{
    uint8_t showNum = 3;
    MenuImage_t *pMenuImage;
    menusize_t  tmpselect;

    cotMenu_LimitShowListNum(ptShowInfo, &showNum);

    printf("\e[0;30;47m ------------- %s ------------- \e[0m\n", ptShowInfo->pszDesc);

    for (int i = 0; i < showNum; i++)
    {
        tmpselect = i + ptShowInfo->showBaseItem;
        pMenuImage = (MenuImage_t *)ptShowInfo->pItemsExData[tmpselect];

        if (tmpselect == ptShowInfo->selectItem)
        {
            printf("\e[0;30;47m %-10s \e[0m", pMenuImage->pImageFrame);
        }
        else
        {
            printf("\e[7;30;47m %-10s \e[0m", pMenuImage->pImageFrame);
        }
    }

    printf("\n");

    for (int i = 0; i < showNum; i++)
    {
        tmpselect = i + ptShowInfo->showBaseItem;
        pMenuImage = (MenuImage_t *)ptShowInfo->pItemsExData[tmpselect];

        if (tmpselect == ptShowInfo->selectItem)
        {
            printf("\e[0;30;47m %-s%-8s%-s \e[0m", pMenuImage->pImage, ptShowInfo->pszItemsDesc[tmpselect], pMenuImage->pImage);
        }
        else
        {
            printf("\e[7;30;47m %-s%-8s%-s \e[0m", pMenuImage->pImage, ptShowInfo->pszItemsDesc[tmpselect], pMenuImage->pImage);
        }
    }

    printf("\n");

    for (int i = 0; i < showNum; i++)
    {
        tmpselect = i + ptShowInfo->showBaseItem;
        pMenuImage = (MenuImage_t *)ptShowInfo->pItemsExData[tmpselect];

        if (tmpselect == ptShowInfo->selectItem)
        {
            printf("\e[0;30;47m %-10s \e[0m", pMenuImage->pImageFrame);
        }
        else
        {
            printf("\e[7;30;47m %-10s \e[0m", pMenuImage->pImageFrame);
        }
    }

    printf("\n");
}

void Hmi_LoadMainHmi(void)
{
    cotMenu_Bind(sg_MainMenuTable, GET_MENU_NUM(sg_MainMenuTable), ShowMainMenu);
}

void Hmi_MainTask(void)
{
    int cmd;

    printf("选择操作(0-退出主菜单; 2-进入; 3-下一个; 4-上一个; 5-快捷音乐; 6-快捷语言; 7-快捷更多设置): ");
    scanf(" %d", &cmd); // 空格作用是忽略上次的回车
 
    switch (cmd)
    {
    case 0:
        cotMenu_MainExit();
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

    case 5:
        cotMenu_ShortcutEnter(true, 1, 0);
        break;

    case 6:
        cotMenu_ShortcutEnter(true, 2, 3, 0);
        break;

    case 7:
        cotMenu_ShortcutEnter(true, 2, 3, 4);
        break;
        
    default:
        break;    
    }
            
}
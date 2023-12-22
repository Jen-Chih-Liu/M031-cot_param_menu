
/* 菜单显示效果图可看: 

https://blog.csdn.net/qq_24130227/article/details/121167276 

*/

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

int main(int argc, char **argv)
{
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

    return 0;
}
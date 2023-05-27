#include "MenuRAtoSQL.h"

CMenuBase * CMenuRAtoSQL::getNextMenu(int choice, bool & isExitSelected){
        CMenuBase *nextMenu = 0;

        switch (choice)
        {
            case 1:
            {
                nextMenu = new CMainMenu;
            }

        }

        return nextMenu;
    }
#include "MenuKeywords.h"

using namespace std;

CMenuKeywords::CMenuKeywords(){
        m_menuText = string("Application keywords (Help)\n"
            "For return to main menu write EXIT.\n");
}

CMenuBase * CMenuKeywords::getNextMenu(int choice, bool & isExitSelected){
        CMenuBase * nextMenu = nullptr;

        switch (choice)
        {
            case 1:
            {
                nextMenu = new CMainMenu;
                break;
            }
            default:{}

        }

        return nextMenu;
    }
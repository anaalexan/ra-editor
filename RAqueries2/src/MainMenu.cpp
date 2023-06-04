#include "MainMenu.h"

using namespace std;

CMainMenu::CMainMenu(){
        m_menuText = string("Main Menu\n"
            "1 - Run RA editor\n" 
            "2 - Translate RA to SQL\n"
            "3 - Application keywords (Help)\n"
            "4 - Exit\n"
            "Your selection: ");
}

CMenuBase * CMainMenu::getNextMenu(int choice, bool & isExitSelected){
        CMenuBase * nextMenu = nullptr;

        switch (choice){
            case 1:{
                nextMenu = new CMenuRAeditor;
                break;
            }
            case 2:{
                nextMenu = new CMenuRAtoSQL;
                break;
            }
            case 3:{
                nextMenu = new CMenuKeywords;
                break;
            }
            case 4:{
                isExitSelected = true;
                break;
            }
            default:{
                string sError = "Error. Please choose number from 1 to 4";
                throw sError;
            }
        }
        


    return nextMenu;
}
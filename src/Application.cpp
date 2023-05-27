#include "Application.h"

#include <iostream>
#include <string>

using namespace std;

void CApplication::run(){
    CMenuBase * aCurrentMenu = new CMainMenu;
    bool isExitSelected = false;
    while (!isExitSelected){
        aCurrentMenu->printText();

        int choice = 0;
        cin >> choice;

        CMenuBase * aNewMenuPointer = aCurrentMenu->getNextMenu(choice, isExitSelected);

        if (aNewMenuPointer)
        {
            delete aCurrentMenu;
            aCurrentMenu = aNewMenuPointer;
        }
    }
}
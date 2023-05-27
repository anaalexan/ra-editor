#include "Application.h"

#include <iostream>
#include <string>

using namespace std;

void CApplication::run(){
    CMenuBase * aCurrentMenu = new CMainMenu;
    bool isExitSelected = false;
    while (!isExitSelected){
        //aCurrentMenu->printText(); // potom zbytecny

        int choice;
        choice = aCurrentMenu->execute();

        CMenuBase * aNewMenuPointer = aCurrentMenu->getNextMenu(choice, isExitSelected);

        if (aNewMenuPointer)
        {
            delete aCurrentMenu;
            aCurrentMenu = aNewMenuPointer;
        }
    }
}
#include "Application.h"

#include <iostream>
#include <string>

using namespace std;

void CApplication::run(){
    CMenuBase * aCurrentMenu = new CMainMenu;
    bool isExitSelected = false;
    while (!isExitSelected){

        int choice;        
        
        try
            {
                choice = aCurrentMenu->execute();
               CMenuBase * aNewMenuPointer = aCurrentMenu->getNextMenu(choice, isExitSelected);
        
                delete aCurrentMenu;
                aCurrentMenu = aNewMenuPointer;
            }
            catch(string sError)
            {
                cerr << sError << endl;
            }     
    }
}
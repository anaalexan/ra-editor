#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MenuBase.h"
#include "MainMenu.h"

using namespace std;
/** Dervied class for menu of Keywords or Help. 
 * Menu will will display to user all keyword to control this aplication
  */
class CMenuKeywords : public CMenuBase{
    public:
        CMenuKeywords();
        /** 
         * {@inheritDoc}
        */
        virtual CMenuBase * getNextMenu(int choice, bool & isExitSelected) override;
};
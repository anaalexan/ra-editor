#pragma once

#include <iostream>
#include <string>

#include "MenuBase.h"
#include "MenuRAeditor.h"
#include "MenuRAtoSQL.h"
#include "MenuKeywords.h"

using namespace std;
/** Dervied class for main menu. First menu to display to user afrer run the aplication
 * Contains signpost to all function of this aplication
  */
class CMainMenu : public CMenuBase{
    public: 
        CMainMenu();
        /** 
         * {@inheritDoc}
        */
        virtual CMenuBase *getNextMenu(int choice, bool & isExitSelected) override;
};
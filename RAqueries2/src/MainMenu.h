#pragma once

#include <iostream>
#include <string>

#include "MenuBase.h"
#include "MenuRAeditor.h"
#include "MenuRAtoSQL.h"
#include "MenuKeywords.h"

using namespace std;

class CMainMenu : public CMenuBase{
    public: 
        CMainMenu();
        virtual CMenuBase *getNextMenu(int choice, bool& isExitSelected) override;
};
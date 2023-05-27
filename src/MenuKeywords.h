#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MenuBase.h"
#include "MainMenu.h"

using namespace std;

class CMenuKeywords : public CMenuBase{
    public:
        CMenuKeywords();
        virtual CMenuBase * getNextMenu(int choice, bool & isExitSelected) override;
};
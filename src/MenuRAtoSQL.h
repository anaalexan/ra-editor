#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MenuBase.h"
#include "MainMenu.h"

using namespace std;

class CMenuRAtoSQL : public CMenuBase{
    public:
        CMenuRAtoSQL(){};
        virtual CMenuBase * getNextMenu(int choice, bool& isExitSelected);
        
};
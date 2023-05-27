#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MenuBase.h"
#include "MainMenu.h"
#include "Variable.h"
#include "FileService.h"
#include "Keywords.h"

using namespace std;

class CMenuRAeditor : public CMenuBase{
        
    public:
        CMenuRAeditor();
        virtual CMenuBase *getNextMenu(int choice, bool& isExitSelected);
        virtual int execute();
    private:
        vector<CVariable> m_variables;
        EKeywords stringToEnum(const string & word);

};
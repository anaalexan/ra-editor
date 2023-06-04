#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "MenuBase.h"
#include "MainMenu.h"
#include "Variable.h"

using namespace std;
/** Dervied class for menu of Keywords or Help. 
 * In it user can translate expression in relational algebra into SQL
  */
class CMenuRAtoSQL : public CMenuBase{
    public:
        CMenuRAtoSQL();
        /** 
         * {@inheritDoc}
        */
        virtual CMenuBase * getNextMenu(int choice, bool& isExitSelected);

        //EKeywords stringToEnum(const string & word);

        /** 
         * {@inheritDoc}
        */
        int execute();

    private:
        /** @var vector of variables {@link #CVariable} imported by user */
        vector<CVariable> m_variables;
        
};
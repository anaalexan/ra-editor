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
/** Dervied class for menu of RA editor. 
 * Menu will process the keyword printed by user into console. And evaluate request from user
 * 
  */
class CMenuRAeditor : public CMenuBase{
        
    public:
        CMenuRAeditor();
        /** 
         * {@inheritDoc}
        */
        virtual CMenuBase *getNextMenu(int choice, bool& isExitSelected);
        /** 
         * {@inheritDoc}
        */
        virtual int execute();

        
    private:
        /** @var vector of variables {@link #CVariable} imported by user */
        vector<CVariable> m_variables;

        /**
	 * Method modify input string from user with keyword into enum
	 * @param[in] word string with keyword from input from user with request to process
     * @returns {@link #EKeywords} enum with keyword to process
	 */
        //EKeywords stringToEnum(const string & word);

        /**
	 * Method modify input string from user with keyword into enum
	 * @param[in] word string with word to process (usually path)
     * @returns same string but without without quotation marks
	    */
        string noQuots(string word);
        /**
	 * Method print result of expression evaluation (final relation) to console
	 * @param[in] data string with keyword from input from user with request to process
	    */
        void printResult(shared_ptr<CRelation> data);
};


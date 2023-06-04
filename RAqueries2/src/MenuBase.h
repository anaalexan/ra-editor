#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "Keywords.h"

using namespace std;
/** Base class for every menu in this aplication */
class CMenuBase{       
    public:
        CMenuBase(){ m_menuText = "error in constructor";}
        
        /**
	 * Method evaluate expression for 1 or 2(binary operator) operand/s
	 * @param[in] choice int from input by user with the number of next menu selected.
     * @param[in,out] isExitSelected bool with information wether exit was selected (true) or not
     * @returns next menu selected one of {@link #CMenuBase} classes
	 */
        virtual CMenuBase * getNextMenu(int choice, bool & isExitSelected) = 0;
        void printText(){
           cout << m_menuText << endl;
        }

        /**
	 * Method will print the text of menu to the user and read his choice from input
     * @returns number of the next menu selected by user
	 */
        virtual int execute(){
            printText();
            int choice = 0;
            cin >> choice;
            return choice;
        }
    protected:
        /** @var string with the information for the user displayed after openning the menu  */
        string m_menuText;

        /**
	 * Method modify input string from user with keyword into enum
	 * @param[in] word string with keyword from input from user with request to process
     * @returns {@link #EKeywords} enum with keyword to process
	 */
        EKeywords stringToEnum(const string & word){
            if(word == "EXIT"){
                return EKeywords::eEXIT;
            }
            if(word == "IMPORT"){
                return EKeywords::eIMPORT;
            }
            if(word == "PRINT"){
                return EKeywords::ePRINT;
            }
            if(word == "EXPORT"){
                return EKeywords::eEXPORT;
            }
            if(word == "TRANSLATE"){
                return EKeywords::eTRANSLATE;
            }
            return EKeywords::eNoMatch;
        }
        /**
	 * Method modify input string from user with keyword to upper case
	 * @param[in] input string with keyword from input from user with request to process
     * @returns {@link #EKeywords} same input string in upper case
	 */
        string toUpperCase(string input){
            for(auto i = input.begin(); i < input.end(); i++){
                std::transform(input.begin(), input.end(), input.begin(), ::toupper);
            }
            return input;
        }
        

};


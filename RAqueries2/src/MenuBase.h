#pragma once

#include <iostream>
#include <string>

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

};


#pragma once

#include <iostream>
#include <string>

using namespace std;

class CMenuBase{       
    public:
        CMenuBase(){ m_menuText = "error in constructor";}
        //virtual ~CMenuBase(){}
        virtual CMenuBase * getNextMenu(int choice, bool & isExitSelected) = 0;
        void printText(){
           cout << m_menuText << endl;
        }
        virtual int execute(){
            printText();
            int choice = 0;
            cin >> choice;
            return choice;
        }
    protected:
        string m_menuText;

};


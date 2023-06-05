
#include "MenuRAtoSQL.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include "Expression.h"
#include <algorithm>

using namespace std;

CMenuRAtoSQL::CMenuRAtoSQL(){
        m_menuText = string("Translator from relational algebra into SQL.\n"
        "For return to main menu write EXIT.\n"
        "Please write expression for translation:\n"
        "(name of the relation/tables should be inside quotation marks: \"Table1\").\n"
        );
}

CMenuBase * CMenuRAtoSQL::getNextMenu(int choice, bool & isExitSelected){
        CMenuBase *nextMenu = 0;

        switch (choice)
        {
            case 1:
            {
                nextMenu = new CMainMenu;
                isExitSelected = false;
            }

        }

        return nextMenu;
}

/*EKeywords CMenuRAtoSQL::stringToEnum(const string & word){
    if(word == "EXIT"){
        return EKeywords::eEXIT;
    }
    return EKeywords::eNoMatch;
}*/



int CMenuRAtoSQL::execute(){
    printText();
    
    bool exit = false;
    string line;
    getline(cin, line);
    

    while(exit != true){

        string line;
        getline(cin, line);
        stringstream ss(line);
        string key;
        getline(ss, key, ' '); 

        try{
            switch(stringToEnum(toUpperCase(key))){
                case(EKeywords::eEXIT):{
                    exit = true;
                    break;
                }
                default:{
                    if(line.size() == 0){
                        string sError = "Error. Please write expression for translation.";
                        throw  sError;
                    }
                    /*string exp;
                    getline(ss, exp, '\n');*/
                    CExpression expression(line, m_variables);
                    vector<string> res = expression.translateToSQL();
                    for(size_t i = 0; i < res.size(); i++){
                        cout << res[i];
                    }
                }
            }
        
        }catch (string str){
            cerr << str << endl;
        }
    }
    return 1; 
}


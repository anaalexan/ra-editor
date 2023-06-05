#include "MenuRAeditor.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>

#include "Expression.h"
#include "Variable.h"

using namespace std;
CMenuRAeditor::CMenuRAeditor(){
        m_menuText = string("RA editor\n"
            "For return to main menu write EXIT.\n");
}

void CMenuRAeditor::printResult(shared_ptr<CRelation> data) {
    
    if(data->m_rows.size() == 0){
        if(data->getPath().size() != 0){
            ifstream fin(data->getPath());
            string line, word;
            CRow row;
            if(!fin.is_open()){
                string sError = "Error. Cannot open file: " + data->getPath();
                throw  sError;
            }

            while (getline(fin, line)){
                if(line.size() == 0){
                    string sError = "Error. Empty file.";
                    throw sError;
                }
                cout << line << endl;
            }
            fin.close();
        }else{
            string sError = "Error. There is no information in this file/relation.";
            throw sError; 
        }
        
    }else{
        cout << "\n";
        for(size_t i = 0; i < data->m_rows.size(); i++){
            for(size_t j = 0; j < data->m_rows.begin()->m_values.size(); j++){
                if(j != 0){
                    cout << ",";
                }
                cout << data->m_rows[i].m_values[j];
                if(j == data->m_rows.begin()->m_values.size() - 1){
                    cout << "\n";
                }
            }
        }
        cout << "\n";
    }

}

string CMenuRAeditor::noQuots(string word){
    string newWord;
    for(size_t i = 0; i < word.size(); i++){
        while (word[i] == ' ' || word[i] == '\"' ){
            i++;
        }
        newWord.push_back(word[i]);
    }
    return newWord;
}

/*EKeywords CMenuRAeditor::stringToEnum(const string & word){
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
}*/

/*string toUpperCase(string input){
    for(auto i = input.begin(); i < input.end(); i++){
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    }
    return input;
}*/

int CMenuRAeditor::execute(){
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
                case(EKeywords::eIMPORT):{
                    string word, path;
                    getline(ss, word, ' ');
                    getline(ss, path, ' ');
                    CExpression expresion(path, m_variables);
                    CVariable var(word, make_shared<CExpression>(expresion));
                    m_variables.push_back(var);
                    break;
                }
                case(EKeywords::ePRINT):{
                    string exp;
                    getline(ss, exp, '\n');
                    CExpression expression(exp, m_variables);
                    shared_ptr<CRelation>  sptr = expression.evaluate();
                    printResult(sptr);

                    break;
                }
                case(EKeywords::eEXPORT):{
                    string exp,path;
                    size_t i = key.size()+1;
                    int cnt = 0;
                    while(line[i] != '>' && cnt == 0 && i < line.size()){
                        if(line[i] == '<'){
                            cnt++;
                        }
                        if(line[i] == '>'){
                            cnt--;
                        }
                        exp.push_back(line[i]);
                        i++;
                    }
                    if(line[i] != '>'){
                        string sError = "Error. There is no path to export (or missing simbol '>' befor path to export).";
                        throw  sError;
                    }
                    //skiping simbol "<"
                    i++;
                    
                    while(line[i] == ' ' && i < line.size()){
                        i++;
                    }

                    while(i < line.size()){
                        path.push_back(line[i]);
                        i++;
                    }
                    CExpression expression(exp, m_variables);
                    shared_ptr<CRelation>  sptr = expression.evaluate();

                    CFileService file;
                    sptr->setPath(noQuots(path));
                    file.exportToFile(sptr);

                    break;
                }
                case(EKeywords::eTRANSLATE):{
                    string exp;
                    getline(ss, exp, '\n');
                    CExpression expression(exp, m_variables);
                    vector<string> res = expression.translateToSQL();
                    for(size_t i = 0; i < res.size(); i++){
                        cout << res[i];
                    }
                    break;
                }
                default:{
                    if(line.size() == 0){
                        string sError = "Invalid command.";
                        throw  sError;
                    }
                    string exp;
                    size_t i = 0;
                    string name;
                    
                    //string into two parts separated by '='
                    while (line[i] != '=' && i < line.size()-1) {
                        i++;
                    }
                    if(line[i] != '='){
                        string sError = "Invalid command.";
                        throw  sError;
                    }
                    //first part befor '=' its the name of variable
                    bool space = false;
                    for(size_t j = 0; j < i; j++){
                        while (line[j] == ' '){
                            if(j == i-1){
                                space = true;
                                break;
                            }
                            j++;
                        }
                        if(space == true){
                            break;
                        }
                        name.push_back(line[j]);
                    }
                    //skip simbol '='
                    i++;
                    //second part after '=' its expression for the variable
                    while (i < line.size())
                    {
                        exp.push_back(line[i]);
                        i++;
                    }
                    //in case exp is empty, that means there was no '=' symbol, so invalid command
                    if(exp.size() != 0){
                        CExpression expression(exp, m_variables);
                        CVariable var(name, make_shared<CExpression>(expression));
                        m_variables.push_back(var);
                    }else{
                        string sError = "Invalid command.";
                        throw  sError;
                    }

                }

            }
        }catch (string str){
            cerr << str << endl;
        }   
    }
        return 1;
}

CMenuBase * CMenuRAeditor::getNextMenu(int choice, bool & isExitSelected){
    CMenuBase *nextMenu = 0;

    switch (choice)
        {
            case 1:
            {
                nextMenu = new CMainMenu;
                isExitSelected = false;
                break;
            }

        }

        return nextMenu;
    }
#include "MenuRAeditor.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include "CrossJoin.h"
#include "Difference.h"
#include "Intersection.h"
#include "Union.h"
#include "Rename.h"
#include "Projection.h"
#include "NaturalJoin.h"
#include "Selection.h"
#include "ThetaJoin.h"



#include "Expression.h"
#include "Variable.h"

using namespace std;

CMenuRAeditor::CMenuRAeditor(){
        m_menuText = string("RA editor\n"
            "For return to main menu write EXIT.\n");
}

void CMenuRAeditor::printResult(shared_ptr<CRelation> data) {
    for(size_t i = 0; i < data->m_rows.size(); i++)
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

EKeywords CMenuRAeditor::stringToEnum(const string & word){
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

string toUpperCase(string input){
    for(auto i = input.begin(); i < input.end(); i++){
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    }
    return input;
}


/*
import kart1 "/home/progtest/Downloads/kart1.csv"
import kart2 "/home/progtest/Downloads/kart2.csv"
res = kart1 kart2 x
export res > /home/progtest/Downloads/resKartnew.csv
print res

translate "/home/progtest/Downloads/kart1.csv" "/home/progtest/Downloads/kart2.csv" *

import LOD "lod.csv"
import REZERVACE "REZERVACE.csv"

translate "LOD" "REZERVACE" * "ZAKAZNIK" * (JMENO_Z=='Iásón') [JMENO_L]<JMENO_L,NAZEV_LOD> "IasonShips.csv" +



*/

int CMenuRAeditor::execute(){
    printText();
    
    bool exit = false;

    

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
                        if(line[i] == ' ' ){
                            i++;
                            continue;
                        }
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
                        throw  "Error. There is no path to export (or missing simbol '>' befor path to export).";
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
                        break;
                    }
                    string exp;
                    size_t i = 0;
                    string name;
                    
                    //string into two parts separated by '='
                    while (line[i] != '=') {
                        i++;
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
                        throw  "Invalid command.";
                    }

                }

            }
        }catch (string msg) {
            cerr << msg << endl;
        }
            
    }

    
        /*int choice = 0;
        cin >> choice;*/

        return 1;
}

CMenuBase * CMenuRAeditor::getNextMenu(int choice, bool & isExitSelected){
        CMenuBase *nextMenu = 0;


//testing if file service works properly

        /*CRelation relation("/home/progtest/Downloads/testInput.csv");
        CFileService file;
        shared_ptr<CRelation> sptr = make_shared<CRelation>(relation);
        file.importFromFile(sptr);

        relation.setPath("/home/progtest/Downloads/testOutput.csv");
        file.exportToFile(sptr);*/

// end of test
//**************************************

// testing if crossJoin work
/*CRelation rel1("/home/progtest/Downloads/rel1.csv");
CRelation rel2("/home/progtest/Downloads/rel2.csv");
CFileService file;
shared_ptr<CRelation> sptr1 = make_shared<CRelation>(rel1);
file.importFromFile(sptr1);
shared_ptr<CRelation> sptr2 = make_shared<CRelation>(rel2);
file.importFromFile(sptr2);*/

/*CCrossJoin spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);*/

/*CDifference rozdil;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = rozdil.evaluate(vec);
file.exportToFile(sptr);*/

/*CIntersection spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);*/

/*CUnion spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);*/

/*CRename rename("name,jmeno;surname,primeni");
vector<shared_ptr<CRelation>> vec = {sptr1};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = rename.evaluate(vec);
file.exportToFile(sptr);*/

/*CProjection project("name,tel,fam");
vector<shared_ptr<CRelation>> vec = {sptr1};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = project.evaluate(vec);
file.exportToFile(sptr);*/

/*CNaturalJoin spoj;
vector<shared_ptr<CRelation>> vec = {sptr1,sptr2};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = spoj.evaluate(vec);
file.exportToFile(sptr);*/




/*vector<CVariable> vec;
CExpression lodExp("\"lod1.csv\" \"lod2.csv\" x ", vec);
CVariable lod("LOD", make_shared<CExpression>(lodExp));
vec.push_back(lod);
CExpression RezervaceExp("\"rez1.csv\" \"rez2.csv\"  -", vec);
CVariable rezervace("REZERVACE", make_shared<CExpression>(RezervaceExp));
vec.push_back(rezervace);
CExpression zakaznikExp("\"zak1.csv\" \"zak2.csv\"  &", vec);
CVariable zakaznik("ZAKAZNIK", make_shared<CExpression>(RezervaceExp));
vec.push_back(zakaznik);


string exp = "LOD REZERVACE * ZAKAZNIK * [JMENO_L]<JMENO_L;NAZEV_LOD> \"IasonShips.csv\" +";
CExpression expression(exp, vec);
expression.evaluate();*/


/*CRelation rel1("/home/progtest/Downloads/bars.csv");
CFileService file;
shared_ptr<CRelation> sptr1 = make_shared<CRelation>(rel1);
file.importFromFile(sptr1);

CProjection vyber("bar");
vector<shared_ptr<CRelation>> vec = {sptr1};
CRelation res("/home/progtest/Downloads/res.csv");
shared_ptr<CRelation> sptr = make_shared<CRelation>(res);
sptr = vyber.evaluate(vec);
file.exportToFile(sptr);*/


///////////////////////////////
/*
CRelation rel1("/home/progtest/Downloads/bars.csv");
shared_ptr<CRelation> sptr1 = make_shared<CRelation>(rel1);
//file.importFromFile(sptr1);

CRelation rel2("/home/progtest/Downloads/barsAdres.csv");
shared_ptr<CRelation> sptr2 = make_shared<CRelation>(rel2);

CProjection projec("bar,beer,price");
vector<shared_ptr<CRelation>> vec = {sptr1};
shared_ptr<CRelation> sptr = projec.evaluate(vec);



CThetaJoin spoj("bar == name");
vec = {sptr, sptr2};
shared_ptr<CRelation>  sptrNew = spoj.evaluate(vec);

CFileService file;
sptrNew->setPath("/home/progtest/Downloads/res1.csv");

file.exportToFile(sptrNew);*/

/*vector<CVariable> vec;
CExpression kartExp("\"/home/progtest/Downloads/kart1.csv\" \ & ", vec);
CVariable kart("KART", make_shared<CExpression>(kartExp));
vec.push_back(kart);/
CExpression expression("\"/home/progtest/Downloads/theta1.csv\" \"/home/progtest/Downloads/theta2.csv\" * ", vec);
shared_ptr<CRelation>  sptrNew = expression.evaluate();


CFileService file;
sptrNew->setPath("/home/progtest/Downloads/resNatural.csv");
file.exportToFile(sptrNew);
*/





/*

CExpression RezervaceExp("\"rez1.csv\" \"rez2.csv\"  -", vec);
CVariable rezervace("REZERVACE", make_shared<CExpression>(RezervaceExp));
vec.push_back(rezervace);
CExpression zakaznikExp("\"zak1.csv\" \"zak2.csv\"  &", vec);
CVariable zakaznik("ZAKAZNIK", make_shared<CExpression>(RezervaceExp));
vec.push_back(zakaznik);


string exp = "LOD REZERVACE * ZAKAZNIK * [JMENO_L]<JMENO_L;NAZEV_LOD> \"IasonShips.csv\" +";
CExpression expression(exp, vec);
expression.evaluate();
*/


/*
import kart1 "/home/progtest/Downloads/kart1.csv"
import kart2 "/home/progtest/Downloads/kart2.csv"
end
res = kart1 kart2 x
print res

*/


//end of test


        switch (choice)
        {
            case 1:
            {
                nextMenu = new CMainMenu;
            }

        }

        return nextMenu;
    }
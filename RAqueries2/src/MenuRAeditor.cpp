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


#include "Expression.h"
#include "Variable.h"

using namespace std;

CMenuRAeditor::CMenuRAeditor(){
        m_menuText = string("RA editor\n"
            "For return to main menu write EXIT.\n");
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
    return EKeywords::eTRANSLATE;
}

string toUpperCase(string input){
    for(auto i = input.begin(); i < input.end(); i++){
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    }
    return input;
}

int CMenuRAeditor::execute(){
    printText();
    
    bool exit = false;

    /*while(exit != true){

        string line;
        getline(cin, line);
        stringstream ss(line);
        string key;
        getline(ss, key, ' '); 

        switch(stringToEnum(toUpperCase(key))){
            case(EKeywords::eEXIT):{
                exit = true;
                break;
            }
            case(EKeywords::eIMPORT):{
                string word,path;
                getline(ss, word, ' ');
                getline(ss, path, ' ');
                CVariable var(word, path);

                break;
            }
            case(EKeywords::ePRINT):{
                break;
            }
            case(EKeywords::eEXPORT):{
                break;
            }
            case(EKeywords::eTRANSLATE):{
                break;
            }
            default:{

            }

            

        }
            
    }*/
        

    //swtich case

    
        int choice = 0;
        cin >> choice;

        return choice;
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




vector<CVariable> vec;
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
expression.evaluate();





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
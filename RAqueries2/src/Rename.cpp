#include "Rename.h"
#include <iostream>
#include  <sstream>

using namespace std;

void CRename::parse(const string & columnNames){
    stringstream ss(columnNames);
    string line;
    while (getline(ss, line, ';')){
        stringstream s(line);
        string oldName;
        string newName;
        getline(s, oldName, ',');
        getline(s, newName, ',');
        pair<string,string> par = make_pair(oldName,newName);
        m_oldNewNames.push_back(par);
    }

}

pair<bool,string> CRename::toSQL(vector<pair<bool,string>> & relations, size_t & index){
    string str1 = "SELECT DISTINCT ";
    string names;
    for( size_t n = 0; n < m_oldNewNames.size(); n++){
        if(n != 0){
            names += ", ";
        }
        names += m_oldNewNames[n].first + " AS " + m_oldNewNames[n].first ;
    }

    string from = "\nFROM ";
    string name1;
    if(relations[0].first == false){
        name1 = relations[0].second;
    }else{
        name1 += "(" + relations[0].second + ")" + "AS TMP" + to_string(index++) + "\n";
    }
      
    string res = str1 + names + from + name1;
    bool isTMPres = true;
    return make_pair(isTMPres, res);
}

vector<string> CRename::relevantAtribute(vector<shared_ptr<CRelation>> & relations){
    vector<string> vec;
    for(size_t i = 0; i < m_oldNewNames.size(); i++){
        vec.push_back(m_oldNewNames[i].first);
    }
    return vec;
}

shared_ptr<CRelation> CRename::evaluateAtributes(vector<shared_ptr<CRelation>> & relations){

    shared_ptr<CRelation> sptr1;
    CRow row1;
    row1 = importAtributes(relations[0]);
    CRelation res;
    CRow row;
    bool isHere = false;
   
    size_t sizeRow = row1.m_values.size();
    size_t cntNewName = 0;
    for(size_t cnt = 0; cnt < sizeRow; cnt++){
        isHere == false;

        //copy new name for atributes that need to be changed,
        for( size_t n = 0; n < m_oldNewNames.size(); n++){
            if(m_oldNewNames[n].first == row1.m_values[cnt]){
                        
                row.m_values.push_back(m_oldNewNames[n].second);
                isHere = true;
                m_oldNewNames.erase(std::next(m_oldNewNames.begin(), n));
                break;
            }
            if(n == m_oldNewNames.size()-1){
                row.m_values.push_back(row1.m_values[cnt]);
            }
        }      
    }
    if(m_oldNewNames.size() != 0){
            
        string sError =  "Name, that you want to change:\n";
        for( size_t n = 0; n < m_oldNewNames.size(); n++){
            sError += m_oldNewNames[n].first;
            sError += "\n";
        }
        sError += " has not been found in the relation";
        throw sError;
    } 
    res.m_rows.push_back(row);

    return make_shared<CRelation>(res); 
}

/*virtual shared_ptr<CRelation> evaluate(const vector<vector<CRow>> & relations) override;
        virtual shared_ptr<CRelation> evaluate(const vector<string> & paths) override;*/

shared_ptr<CRelation> CRename::evaluate(vector<shared_ptr<CRelation>> & relations){
    shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
    CRelation res;
    /*bool isHere = false;
    CRow row;
   
        size_t sizeRow = sptr1->m_rows[0].m_values.size();
        size_t cntNewName = 0;
        //copy names of atributes into new relation
        for(size_t cnt = 0; cnt < sizeRow; cnt++){
            isHere == false;

            //copy new name for atributes that need to be changed,
            for( size_t n = 0; n < m_oldNewNames.size(); n++){
                if(m_oldNewNames[n].first == sptr1->m_rows[0].m_values[cnt]){
                    
                    row.m_values.push_back(m_oldNewNames[n].second);
                    isHere = true;
                    m_oldNewNames.erase(std::next(m_oldNewNames.begin(), n));
                    break;
                }
                if(n == m_oldNewNames.size()-1){
                    row.m_values.push_back(sptr1->m_rows[0].m_values[cnt]);
                }
            }
            
           
        }
        if(m_oldNewNames.size() != 0){

            cout << "Name, that you want to change: " << endl;
            for( size_t n = 0; n < m_oldNewNames.size(); n++){
                cout <<  "\"" << m_oldNewNames[n].first << "\"" << endl;
            }
            cout << " has not been found in the relation" << endl;
        } 
        
    

    res.m_rows.push_back(row);*/

    res = *evaluateAtributes(relations);
    //copy rest of the relation
    for(size_t i = 1; i < sptr1->m_rows.size(); i++){
        res.m_rows.push_back(sptr1->m_rows[i]);
    }
    return make_shared<CRelation>(res);

}


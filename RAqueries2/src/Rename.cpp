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

shared_ptr<CRelation> CRename::evaluate(vector<shared_ptr<CRelation>> & relations){

    bool isHere = false;
    for(size_t n = 0; n < m_oldNewNames.size(); n++){
        isHere = false;
        size_t sizeRow = relations[0]->m_rows[0].m_values.size();
        for(size_t cnt = 0; cnt < sizeRow; cnt++){
            if(m_oldNewNames[n].first == relations[0]->m_rows[0].m_values[cnt]){
                relations[0]->m_rows[0].m_values[cnt] = m_oldNewNames[n].second;
                isHere = true;
            }
            try{
                if(cnt == (sizeRow-1) && isHere == false){
                    throw 505;
                }
            }catch (...) {
                cout << "Name, that you want to change: " <<  "\"" << m_oldNewNames[n].first << "\" has not been found in the relation" << endl;
            }   
        }
    }
    return relations[0];

}
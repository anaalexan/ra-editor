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

/*virtual shared_ptr<CRelation> evaluate(const vector<vector<CRow>> & relations) override;
        virtual shared_ptr<CRelation> evaluate(const vector<string> & paths) override;*/

shared_ptr<CRelation> CRename::evaluate(vector<shared_ptr<CRelation>> & relations){
    shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
    CRelation res;
    bool isHere = false;
    for(size_t n = 0; n < m_oldNewNames.size(); n++){
        isHere = false;
        size_t sizeRow = sptr1->m_rows[0].m_values.size();

        //copy names of atributes into new relation
        for(size_t cnt = 0; cnt < sizeRow; cnt++){

            //copy new name for atributes that need to be changed,
            if(m_oldNewNames[n].first == sptr1->m_rows[0].m_values[cnt]){
                CRow row;
                row.m_values.push_back(m_oldNewNames[n].second);
                res.m_rows.push_back(row);
                isHere = true;
            }else{
                CRow row;
                row.m_values.push_back(sptr1->m_rows[0].m_values[cnt]);
                res.m_rows.push_back(row);
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
    //copy rest of the relation
    for(size_t i = 1; i < sptr1->m_rows.size(); i++){
        res.m_rows.push_back(sptr1->m_rows[i]);
    }
    return make_shared<CRelation>(res);

}


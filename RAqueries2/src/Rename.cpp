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
pair<bool,vector<string>> CRename::toSQL(const vector<pair<bool,vector<string>>> & relations, size_t & index){
    vector<string> newQuery;
    newQuery.push_back("SELECT DISTINCT ");
    string names,name1;
    for( size_t n = 0; n < m_oldNewNames.size(); n++){
        if(n != 0){
            names += ", ";
        }
        names += m_oldNewNames[n].first + " AS " + m_oldNewNames[n].second ;
    }
   
    newQuery[newQuery.size()-1] += names + "\n";
    //newQuery.push_back(names); 
    string from = "FROM ";
    newQuery.push_back(from);
    if(relations[0].first == false){
        newQuery[newQuery.size()-1] += relations[0].second[0] + "\n";
        //newQuery.push_back();
    }else{
        makeTmpSTR(newQuery, relations[0], index, name1);
    }
    
    return make_pair(true, newQuery);
}

vector<string> CRename::relevantAtribute(const vector<shared_ptr<CRelation>> & relations){
    vector<string> vec;
    if((relations[0]->getPath().size() != 0) || (relations[0]->m_rows[0].m_values.size() !=0 )){
        for(size_t i = 0; i < m_oldNewNames.size(); i++){
            vec.push_back(m_oldNewNames[i].first);
        }
    }
    return vec;
}

shared_ptr<CRelation> CRename::evaluateAtributes(const vector<shared_ptr<CRelation>> & relations){

    shared_ptr<CRelation> sptr1;
    CRow row1;
    row1 = importAtributes(relations[0]);
    CRelation res;
    CRow row;
   
    size_t sizeRow = row1.m_values.size();
    for(size_t cnt = 0; cnt < sizeRow; cnt++){

        //copy new name for atributes that need to be changed,
        for( size_t n = 0; n < m_oldNewNames.size(); n++){
            if(m_oldNewNames[n].first == row1.m_values[cnt]){
                        
                row.m_values.push_back(m_oldNewNames[n].second);
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


shared_ptr<CRelation> CRename::evaluate(const vector<shared_ptr<CRelation>> & relations){
    shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
    CRelation res;
    res = *evaluateAtributes(relations);
    //copy rest of the relation
    for(size_t i = 1; i < sptr1->m_rows.size(); i++){
        res.m_rows.push_back(sptr1->m_rows[i]);
    }
    return make_shared<CRelation>(res);

}


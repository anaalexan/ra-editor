#include "Operator.h"

string tab = "    ";

vector<string> COperator::relevantAtribute(vector<shared_ptr<CRelation>> & relations){
    vector<string> vec;
    return vec;
}

shared_ptr<CRelation> COperator::importRelation(shared_ptr<CRelation> relation){

    shared_ptr<CRelation> sptr1;
    
    if(relation->getPath().size() != 0){
        CFileService file;
        sptr1 = make_shared<CRelation>(relation->getPath());
        file.importFromFile(sptr1);
    }else{
        sptr1 = relation;
    }
    return sptr1;
}

CRow COperator::importAtributes(shared_ptr<CRelation> relation){

    CRow row;
    shared_ptr<CRelation> sptr1;
    if(relation->getPath().size() != 0){
        CFileService file;
        sptr1 = make_shared<CRelation>(relation->getPath());
        row = file.importAtriburesFromFile(sptr1);
    }else{
        row = relation->m_rows[0];
    }
    return row;
}

        

void COperator::makeTmpSTR(vector<string> & newQuery, pair<bool,vector<string>> & oldQuery, size_t & index, string & name){
    newQuery.push_back("\n");
    newQuery.push_back("( \n" );

    for (auto & element : oldQuery.second){
        newQuery.push_back(tab + element);
    }
    name = "TMP" + to_string(++index);
    newQuery.push_back(") AS " + name + "\n");
}
        

void COperator::operatorToString(vector<string> & newQuery, pair<bool,vector<string>> & relations, size_t & index, string & name){
            
    newQuery.push_back("SELECT DISTINCT *\n");
    newQuery.push_back("FROM ");
    if(relations.first == false){
        name = relations.second[0];
        newQuery[newQuery.size()-1] += name + "\n";
    }else{
        makeTmpSTR(newQuery, relations, index, name);
    }
}
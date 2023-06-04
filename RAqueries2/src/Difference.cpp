#include "Difference.h"
#include "UnionCompatible.h"
#include <iostream>


using namespace std;


pair<bool,vector<string>> CDifference::toSQL(const vector<pair<bool,vector<string>>> & relations, size_t & index){
    string name1, name2;
    vector<string> newQuery;
    operatorToString(newQuery, relations[0], index, name1);
    newQuery.push_back("MINUS\n");
    operatorToString(newQuery, relations[1], index, name2); 
    return make_pair(true, newQuery);
}

shared_ptr<CRelation> CDifference::evaluateAtributes(const vector<shared_ptr<CRelation>> & relations){

    shared_ptr<CRelation> sptr1;
    CRow row1;
    row1 = importAtributes(relations[0]);
    CRow row2;
    row2 = importAtributes(relations[1]);

    CUnionCompatible valid;
    if(!valid.isUnionCompatible(row1, row2)){
        string sError = "Error. Cannot evaluate Difference. Relations are not union compatible. Both relations should have the exact same attributes.";
        throw sError;
    }
    CRelation res;
    res.m_rows.push_back(row1);
    

    return make_shared<CRelation>(res); 
}

shared_ptr<CRelation> CDifference::evaluate(const vector<shared_ptr<CRelation>> & relations) {
    shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
    shared_ptr<CRelation> sptr2 = importRelation(relations[1]);
    
    CRelation res;

    CUnionCompatible valid;
    if(!valid.isUnionCompatible(sptr1->m_rows[0], sptr2->m_rows[0])){
        string sError = "Error. Cannot evaluate Difference. Relations are not union compatible. Both relations should have the exact same attributes.";
        throw sError;
    }

    
    bool same = false;
    int dif_cnt = 0;
    //first(0.) row it is the names of the atributes
     // copy 0.row into final relation 

    res.m_rows.push_back(sptr1->m_rows[0]);

    for(size_t row1 = 1; row1 < sptr1->m_rows.size(); row1++){
        same = false;
        dif_cnt = 0;
        for(size_t row2 = 1; row2 < sptr2->m_rows.size(); row2++){

            // it does not matter wich one relation we take or wich row in that relation, 
            // because thay should contain the same amount of words 
    
            for(size_t word = 0; word < sptr1->m_rows[0].m_values.size(); word++){
                string word1 = sptr1->m_rows[row1].m_values[word];
                string word2 = sptr2->m_rows[row2].m_values[word];
                if(word1 != word2){
                    
                    same = false;
                    break;;
                }else{
                    same = true;
                }

            }
            if(same == true){
                break;
            }
            dif_cnt++;
            if(dif_cnt == (sptr2->m_rows.size() - 1)){
                res.m_rows.push_back(sptr1->m_rows[row1]);

            }
        }
    }
    

    return make_shared<CRelation>(res);
}
#include "NaturalJoin.h"

#include <iostream>
#include  <sstream>

using namespace std;


shared_ptr<CRelation> CNaturalJoin::evaluate(vector<shared_ptr<CRelation>> & relations){
    shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
    shared_ptr<CRelation> sptr2 = importRelation(relations[1]);
    
    CRelation res;
    bool isHere = false;
    size_t rel1;
    size_t rel2;

    //looking for the common attribute between the relations
    for(size_t i = 0; i < sptr1->m_rows[0].m_values.size(); i++){
        for(size_t j = 0; j < sptr2->m_rows[0].m_values.size(); j++){
            if(sptr1->m_rows[0].m_values[i] == sptr2->m_rows[0].m_values[j]){
                rel1 = i;
                rel2 = j;
                isHere = true;
                break;
            }
        }
        if(isHere == true){
            break;
        }
        if(isHere == false && i == sptr1->m_rows[0].m_values.size() - 1){
            cout << "No common attribute has been found between the relations. Natural join cannot be evaluate." << endl;
            return nullptr;
        }
    }

    //copy the name of colomns from second relation
    res.m_rows.push_back(sptr1->m_rows[0]);

    //copy the name of colomns from second relation (exept the one common between first and second relation)
    for(size_t j = 0; j < sptr2->m_rows[0].m_values.size(); j++){
        if(j != rel2){
            res.m_rows[0].m_values.push_back(sptr2->m_rows[0].m_values[j]);
        }else{
            continue;
        }
    }
    for(size_t i = 1; i < sptr1->m_rows.size(); i++){
        for(size_t j = 1; j < sptr2->m_rows.size(); j++){
            string word1 = sptr1->m_rows[i].m_values[rel1];
            string word2 = sptr2->m_rows[j].m_values[rel2];
            if(word1 == word2){
                res.m_rows.push_back(sptr1->m_rows[i]);
                auto it = res.m_rows.end()-1; 
                for(size_t cnt = 0; cnt < sptr2->m_rows[0].m_values.size(); cnt++){
                    if(cnt != rel2){
                        
                        it->m_values.push_back(sptr2->m_rows[j].m_values[cnt]);
                    }else{
                        continue;
                    }
                }
            }
        }
    }
    return make_shared<CRelation>(res);
}   
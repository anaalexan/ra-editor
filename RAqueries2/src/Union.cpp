#include "Union.h"
#include "UnionCompatible.h"
#include <iostream>

using namespace std;

shared_ptr<CRelation> CUnion::evaluate(vector<shared_ptr<CRelation>> & relations){

    shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
    shared_ptr<CRelation> sptr2 = importRelation(relations[1]);
    
    CRelation res;

    CUnionCompatible valid;
    try{
        if(!valid.isUnionCompatible(sptr1, sptr2)){
            throw 505;
        }
    }catch (...) {
        cout << "Relations are not union compatible. Both relations should have the exact same attributes." << endl;
    }
    
    for(size_t i = 0; i < sptr1->m_rows.size(); i++){
        res.m_rows.push_back(sptr1->m_rows[i]);
    }

    bool same = false;
    int dif_cnt = 0;
    for(size_t row2 = 1; row2 < sptr2->m_rows.size(); row2++){
        same = false;
        dif_cnt = 0;
        for(size_t row1 = 1; row1 < sptr1->m_rows.size(); row1++){

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
            if(dif_cnt == (sptr1->m_rows.size() - 1)){
                res.m_rows.push_back(sptr2->m_rows[row2]);

            }
        }
    }
    return make_shared<CRelation>(res);
    
}


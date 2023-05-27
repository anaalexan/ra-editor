#include "Union.h"
#include "UnionCompatible.h"
#include <iostream>

using namespace std;

shared_ptr<CRelation> CUnion::evaluate(vector<shared_ptr<CRelation>> & relations){
    CRelation res;

    CUnionCompatible valid;
    try{
        if(!valid.isUnionCompatible(relations[0], relations[1])){
            throw 505;
        }
    }catch (...) {
        cout << "Relations are not union compatible. Both relations should have the exact same attributes." << endl;
    }
    
    for(size_t i = 0; i < relations[0]->m_rows.size(); i++){
        res.m_rows.push_back(relations[0]->m_rows[i]);
    }

    bool same = false;
    int dif_cnt = 0;
    for(size_t row2 = 1; row2 < relations[1]->m_rows.size(); row2++){
        same = false;
        dif_cnt = 0;
        for(size_t row1 = 1; row1 < relations[0]->m_rows.size(); row1++){

            // it does not matter wich one relation we take or wich row in that relation, 
            // because thay should contain the same amount of words 
    
            for(size_t word = 0; word < relations[0]->m_rows[0].m_values.size(); word++){
                string word1 = relations[0]->m_rows[row1].m_values[word];
                string word2 = relations[1]->m_rows[row2].m_values[word];
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
            if(dif_cnt == (relations[0]->m_rows.size() - 1)){
                res.m_rows.push_back(relations[1]->m_rows[row2]);

            }
        }
    }
    return make_shared<CRelation>(res);
    
}
#include "Intersection.h"

using namespace std;

shared_ptr<CRelation> CIntersection::evaluate(vector<shared_ptr<CRelation>> & relations){
    CRelation res;
    bool same = false;
    bool dif = false;
    int dif_cnt = 0;
    //first(0.) row it is the names of the atributes
     // copy 0.row into final relation 

    res.m_rows.push_back(relations[0]->m_rows[0]);

    for(size_t row1 = 1; row1 < relations[0]->m_rows.size(); row1++){
        same = false;
        dif_cnt = 0;
        for(size_t row2 = 1; row2 < relations[1]->m_rows.size(); row2++){

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
                res.m_rows.push_back(relations[0]->m_rows[row1]);
            }
                

            
        }
    }
    

    return make_shared<CRelation>(res);

}
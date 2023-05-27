

#include "CrossJoin.h"

using namespace std;


shared_ptr<CRelation> CCrossJoin::evaluate(vector<shared_ptr<CRelation>> & relations) {
    CRelation res;

    //copy first relation into final relation        
    for(size_t i = 0; i < relations[0]->m_rows.size(); i++){
        CRow row;
        for(size_t j = 0; j < relations[0]->m_rows[0].m_values.size(); j++){
           string word = relations[0]->m_rows[i].m_values[j];
           row.m_values.push_back(word);

        }
        if(i != 0){
            //copy rows from first relation, as many times as it has rows in second relation
                //rows2 = row in second relation
            for(size_t row2 = 0; row2 < size(relations[1]->m_rows[0].m_values); row2++){
                res.m_rows.push_back(row);
            }
        }else{
            //copy first row with the names of the columns (can by only one row)
            res.m_rows.push_back(row);
        }
    }

    for(size_t row = 0; row < res.m_rows.size(); row++){
        if(row != 0){
            for(size_t i = 1; i < relations[1]->m_rows.size(); i++){
                for(size_t row2 = 0; row2 < relations[1]->m_rows[0].m_values.size(); row2++){
                    res.m_rows[row].m_values.push_back(relations[1]->m_rows[i].m_values[row2]);
                    
                }
                if(i != relations[1]->m_rows.size()-1){
                    row++;
                }
            }
        }else{
            for(size_t row2 = 0; row2 < relations[1]->m_rows[0].m_values.size(); row2++){
                res.m_rows[0].m_values.push_back(relations[1]->m_rows[0].m_values[row2]);
            }
        }
        
        
    }
    return make_shared<CRelation>(res);
    
    // copy the name of the columns from both relation into final relation
         //from first relation
    /*for(size_t i = 0; i < size(relations[0]->m_rows); i++){
        string name = relations[0]->m_rows[i].m_name;
        CColumn resName(name);
        res.m_columns.push_back(resName);
    }
        //from second relation
    for(size_t j = 0; j < size(relations[1]->m_columns); j++){
        string name = relations[1]->m_columns[j].m_name;
        CColumn resName(name);
        res.m_columns.push_back(resName); 

    }
    //rows in first relation
    for(size_t row1 = 0; row1 < size(relations[0]->m_columns[0].m_values); row1++){

        //columns in final relation 
        for(size_t col = 0; col < size(res.m_columns); col++){

            //rows in second relation
            for(size_t row2 = 0; row2 < size(relations[1]->m_columns[0].m_values); row2++){
                size_t col2 = 0;
                if(col <= size(relations[0]->m_columns)-1){
                    //copy values from first relation
                    res.m_columns[col].m_values.push_back(relations[0]->m_columns[col].m_values[row1]);
                }
                else{
                    //for(size_t col2 = 0; col2 < size(relations[1]->m_columns); col2++){
                        //copy values from second relation

                        res.m_columns[col].m_values.push_back(relations[1]->m_columns[col2].m_values[row1]);
                        col2++;
                    //}
                }
            }
        }
    }*/


}
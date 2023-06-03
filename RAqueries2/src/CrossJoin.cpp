

#include "CrossJoin.h"
#include "FileService.h"
#include "Operator.h"

using namespace std;



pair<bool,vector<string>> CCrossJoin::toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index){
    string name1, name2;
    vector<string> newQuery;
    operatorToString(newQuery, relations[0], index, name1);
    size_t i = newQuery.size()-1;
    size_t j = newQuery[i].size()-1;
    newQuery[i][j] = ','; 
    string str2;
    if(relations[1].first == false){
        newQuery[newQuery.size()-1] += " " + relations[1].second[0] + "\n";
        //newQuery.push_back(" ");
        //newQuery.push_back(relations[1].second[0] + "\n");
    }else{
        makeTmpSTR(newQuery, relations[1], index, name2);
    }
    return make_pair(true, newQuery);
}
shared_ptr<CRelation> CCrossJoin::evaluateAtributes(vector<shared_ptr<CRelation>> & relations){

     shared_ptr<CRelation> sptr1;
     CRow row1;
     CRow row2;

     row1 = importAtributes(relations[0]);
     row2 = importAtributes(relations[1]);
     CRelation res;
     //copy the name of colomns from first relation
     res.m_rows.push_back(row1);
     //copy the name of colomns from second relation
     for(size_t j = 0; j < row2.m_values.size(); j++){
          res.m_rows[0].m_values.push_back(row2.m_values[j]);
     }

     return make_shared<CRelation>(res); 
}

shared_ptr<CRelation> CCrossJoin::evaluate(vector<shared_ptr<CRelation>> & relations) {
    shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
    shared_ptr<CRelation> sptr2 = importRelation(relations[1]);
    
    CRelation res;

    //copy first relation into final relation        
    for(size_t i = 0; i < sptr1->m_rows.size(); i++){
        CRow row;
        for(size_t j = 0; j < sptr1->m_rows[0].m_values.size(); j++){
           string word = sptr1->m_rows[i].m_values[j];
           row.m_values.push_back(word);

        }
        if(i != 0){
            //copy rows from first relation, as many times as it has rows in second relation
                //rows2 = row in second relation
            for(size_t row2 = 0; row2 < size(sptr2->m_rows[0].m_values); row2++){
                res.m_rows.push_back(row);
            }
        }else{
            //copy first row with the names of the columns (can be only one row)
            res.m_rows.push_back(row);
        }
    }

    for(size_t row = 0; row < res.m_rows.size(); row++){
        if(row != 0){
            for(size_t i = 1; i < sptr2->m_rows.size(); i++){
                for(size_t row2 = 0; row2 < sptr2->m_rows[0].m_values.size(); row2++){
                    res.m_rows[row].m_values.push_back(sptr2->m_rows[i].m_values[row2]);
                    
                }
                if(i != sptr2->m_rows.size()-1){
                    row++;
                }
            }
        }else{
            for(size_t row2 = 0; row2 < sptr2->m_rows[0].m_values.size(); row2++){
                res.m_rows[0].m_values.push_back(sptr2->m_rows[0].m_values[row2]);
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

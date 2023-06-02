#include "ThetaJoin.h"
#include "CompareOperator.h"
#include "StringConvert.h"

#include <iostream>
#include  <sstream>

using namespace std;

vector<string> CThetaJoin::relevantAtribute(vector<shared_ptr<CRelation>> & relations){
     vector<string> vec;
     vec.push_back(m_conditions.left);
     vec.push_back(m_conditions.right);
     return vec;
}


shared_ptr<CRelation> CThetaJoin::evaluateAtributes(vector<shared_ptr<CRelation>> & relations){

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

        

shared_ptr<CRelation> CThetaJoin::evaluate(vector<shared_ptr<CRelation>> & relations){
     shared_ptr<CRelation> sptr1 = importRelation(relations[0]);
     shared_ptr<CRelation> sptr2 = importRelation(relations[1]);
     CRelation res;

     //copy the name of colomns from second relation
     res.m_rows.push_back(sptr1->m_rows[0]);
     //copy the name of colomns from second relation
     for(size_t j = 0; j < sptr2->m_rows[0].m_values.size(); j++){
          res.m_rows[0].m_values.push_back(sptr2->m_rows[0].m_values[j]);
     }

     bool isHereL = false;
     size_t indexL;
     
     //checking if first relation contains the atribute from condition
     for(size_t j = 0; j < sptr1->m_rows[0].m_values.size(); j++){
          if(m_conditions.left == res.m_rows[0].m_values[j]){
               isHereL = true;
               indexL = j;
               break;
          }
          if(isHereL == false && j == sptr1->m_rows[0].m_values.size()-1){
                cout << "Name of the atribute: " <<  "\"" << m_conditions.left << "\" has not been found in the relation" << endl;
                return nullptr;
          }
     }

     bool isHereR = false;
     size_t indexR;
     //checking if second relation contains the atribute from condition
     for(size_t j = 0; j < sptr2->m_rows[0].m_values.size(); j++){
          if(m_conditions.right == sptr2->m_rows[0].m_values[j]){
               isHereR = true;
               indexR = j;
               break;
          }
          if(isHereR == false && j == sptr2->m_rows[0].m_values.size()-1){
                cout << "Name of the atribute: " <<  "\"" << m_conditions.right << "\" has not been found in the relation" << endl;
                return nullptr;
          }
     }
     
     CCompareOperator compare;
     CStringConvert convert;

     for(size_t i = 1; i < sptr1->m_rows.size(); i++){
        for(size_t j = 1; j < sptr2->m_rows.size(); j++){
          if(compare.evaluate(convert.whatType(sptr1->m_rows[i].m_values[indexL]), convert.whatType(sptr2->m_rows[j].m_values[indexR]), m_conditions.m_operator)){

               res.m_rows.push_back(sptr1->m_rows[i]);
               auto it = res.m_rows.end()-1; 
               for(size_t cnt = 0; cnt < sptr2->m_rows[0].m_values.size(); cnt++){    
                    it->m_values.push_back(sptr2->m_rows[j].m_values[cnt]);
               }
          }
        }
     }
     return make_shared<CRelation>(res);  
     
}
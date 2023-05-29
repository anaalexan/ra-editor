#pragma once

#include <vector>

#include "Relation.h"

using namespace std;    

class COperator{        
    public:
        enum EOperatorType{BINARY, UNARY} m_type;

        COperator (EOperatorType type) // Constructor
		:m_type(type){};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) = 0;
        
    //private:
        shared_ptr<CRelation> importRelation(shared_ptr<CRelation> relation){

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
        
};
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
    private:
        
};
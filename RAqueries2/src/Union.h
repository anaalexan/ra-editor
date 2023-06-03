#pragma once

#include "Operator.h"
#include "UnionCompatible.h"

using namespace std;

class CUnion : public COperator, public CUnionCompatible{    
    public:
        CUnion () // Constructor
		:COperator(EOperatorType::BINARY){};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;

        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;

        virtual pair<bool,string> toSQL(vector<pair<bool,string>> & relations, size_t index) override;
        
};
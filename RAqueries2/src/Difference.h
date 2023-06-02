#pragma once

#include "Operator.h"
#include "UnionCompatible.h"

using namespace std;

class CDifference : public COperator, public CUnionCompatible{
    public:
        CDifference () // Constructor
		:COperator(EOperatorType::BINARY){};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;
};
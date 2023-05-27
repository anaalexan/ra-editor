#pragma once

#include "Operator.h"

using namespace std;

class CCrossJoin : public COperator{
    public:
        CCrossJoin () // Constructor
		:COperator(EOperatorType::BINARY){};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
};
#pragma once

#include "Operator.h"

using namespace std;

class CCrossJoin : public COperator{
    public:
        CCrossJoin () // Constructor
		:COperator(EOperatorType::BINARY){};

        virtual shared_ptr<CRelation> evaluate(const vector<vector<CRow>> & relations) override;
        virtual shared_ptr<CRelation> evaluate(const vector<string> & paths) override;
};
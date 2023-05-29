#pragma once

#include "Operator.h"

using namespace std;

class CNaturalJoin : public COperator{
    public:
        CNaturalJoin () // Constructor
		:COperator(EOperatorType::BINARY){};

        virtual shared_ptr<CRelation> evaluate(const vector<vector<CRow>> & relations) override;
        virtual shared_ptr<CRelation> evaluate(const vector<string> & paths) override;
};
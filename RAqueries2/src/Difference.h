#pragma once

#include "Operator.h"
#include "UnionCompatible.h"

using namespace std;

class CDifference : public COperator, public CUnionCompatible{
    public:
        CDifference () // Constructor
		:COperator(EOperatorType::BINARY){};

        virtual shared_ptr<CRelation> evaluate(const vector<vector<CRow>> & relations) override;
        virtual shared_ptr<CRelation> evaluate(const vector<string> & paths) override;
};
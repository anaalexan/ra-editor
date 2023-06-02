#pragma once

#include "Operator.h"

using namespace std;

class CNaturalJoin : public COperator{
    public:
        CNaturalJoin () // Constructor
		:COperator(EOperatorType::BINARY){};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;

        virtual vector<string> relevantAtribute(vector<shared_ptr<CRelation>> & relations) override;

};
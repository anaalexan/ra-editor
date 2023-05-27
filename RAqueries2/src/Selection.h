#pragma once

#include "Operator.h"
#include "ConditionParser.h"

using namespace std;

class CSelection : public COperator{
    public:
        CSelection (const string & condition) // Constructor
		:COperator(EOperatorType::UNARY), m_conditions(){
            m_conditions = CConditionParser().parse(condition);
        };

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
    private:
        vector<string> m_conditions;
};
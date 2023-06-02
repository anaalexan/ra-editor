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

        ~CSelection() = default;
        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
        shared_ptr<CRelation> evaluate(const string & path);
    private:
        CConditionParser::CCondition m_conditions;

        string konstant(string word);

        virtual vector<string> relevantAtribute() override;
};
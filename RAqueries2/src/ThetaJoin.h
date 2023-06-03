#pragma once

#include "Operator.h"
#include "ConditionParser.h"

using namespace std;

class CThetaJoin : public COperator{
    public:
        CThetaJoin (const string & condition) // Constructor
		:COperator(EOperatorType::BINARY), m_conditions(){
            m_conditions = CConditionParser().parse(condition);
        };

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;

        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;

        virtual vector<string> relevantAtribute(vector<shared_ptr<CRelation>> & relations) override;

        virtual pair<bool,vector<string>> toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index) override;

        
    private:
        CConditionParser::CCondition m_conditions;
};


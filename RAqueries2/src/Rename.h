#pragma once

#include "Operator.h"
#include <string>

using namespace std;

class CRename : public COperator{        
    public:
        CRename (const string & columnNames) // Constructor
		:COperator(EOperatorType::UNARY), m_oldNewNames(){parse(columnNames);};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
    private:
        vector<pair<string,string>> m_oldNewNames;

        void parse(const string & columnNames);

        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;

        virtual vector<string> relevantAtribute(vector<shared_ptr<CRelation>> & relations) override;

        
};


#pragma once

#include "Operator.h"

using namespace std;

class CProjection : public COperator{
    public:
        CProjection (const string & columnNames) // Constructor
		:COperator(EOperatorType::UNARY), m_columnNames(){parse(columnNames);};

        ~CProjection() = default;

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
        shared_ptr<CRelation> evaluate(const string & path);

        virtual pair<bool,vector<string>> toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index) override;
    private:
        vector<string> m_columnNames;

        void parse(const string & columnNames);

        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;

        virtual vector<string> relevantAtribute(vector<shared_ptr<CRelation>> & relations) override;
};
#pragma once

#include "Operator.h"

using namespace std;

class CProjection : public COperator{
    public:
        CProjection (const string & columnNames) // Constructor
		:COperator(EOperatorType::UNARY), m_columnNames(){parse(columnNames);};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
    private:
        vector<string> m_columnNames;

        void parse(const string & columnNames);
};
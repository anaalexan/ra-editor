#pragma once

#include "Operator.h"

using namespace std;
/** Dervied class for  binary operator natural Join in relation algebra
 * Natural join combines tuples from different relations with at least one common attribute that exists between this two relations.     */
class CNaturalJoin : public COperator{
    public:
        CNaturalJoin () // Constructor
		:COperator(EOperatorType::BINARY){};
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluate(const vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluateAtributes(const vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointer of {@link #CRelation} class.
        */
        virtual vector<string> relevantAtribute(const vector<shared_ptr<CRelation>> & relations) override;

        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointer of {@link #CRelation} class.
        */
        virtual pair<bool,vector<string>> toSQL(const vector<pair<bool,vector<string>>> & relations, size_t & index) override;

};
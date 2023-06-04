#pragma once

#include "Operator.h"
#include "UnionCompatible.h"

using namespace std;
/** Dervied class for  binary operator Difference in relation algebra
 * It displays all rows from the first relation that are not present in the second relation.   */
class CDifference : public COperator, public CUnionCompatible{
    public:
        CDifference () // Constructor
		:COperator(EOperatorType::BINARY){};

        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointer of {@link #CRelation} class.
        */
        virtual pair<bool,vector<string>> toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index) override;
};
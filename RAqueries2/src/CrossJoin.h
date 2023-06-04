#pragma once

#include "Operator.h"

using namespace std;
/** Dervied class for  binary operator Cross join (or Cartesian product) in relation algebra
 * It Combines information of two different relations into one.    */
class CCrossJoin : public COperator{
    public:
        CCrossJoin () // Constructor
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
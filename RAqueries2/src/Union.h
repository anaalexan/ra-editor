#pragma once

#include "Operator.h"
#include "UnionCompatible.h"

using namespace std;

/** Dervied class for  binary operator union in relation algebra  */

class CUnion : public COperator, public CUnionCompatible{    
    public:
        CUnion () // Constructor
		:COperator(EOperatorType::BINARY){};

        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointers of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointers of {@link #CRelation} class. 
        */
        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * * {@inheritDoc}
         * @param[in] relations vector contains 2 pair of bool and vector of strings
        */
        virtual pair<bool,vector<string>> toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index) override;
        
};
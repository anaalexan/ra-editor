#pragma once

#include "Operator.h"
#include "ConditionParser.h"
#include "CompareOperator.h"

using namespace std;
/** Dervied class for  binary operator theta (conditioned) Join in relation algebra
 * Theta join combines tuples from different relations provided they satisfy the theta condition.     */
class CThetaJoin : public COperator, public CCompareOperator{
    public:
        CThetaJoin (const string & condition) // Constructor
		:COperator(EOperatorType::BINARY), m_conditions(){
            m_conditions = CConditionParser().parse(condition);
        };
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointers of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluate(const vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointers of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluateAtributes(const vector<shared_ptr<CRelation>> & relations) override;
    /** 
         * {@inheritDoc}
         * returs both operands from the condition (names of the atributes)
	 */
        virtual vector<string> relevantAtribute(const vector<shared_ptr<CRelation>> & relations) override;
/** 
         * {@inheritDoc}
         * @param[in] relations vector contains 2 shared pointers of {@link #CRelation} class.
        */
        virtual pair<bool,vector<string>> toSQL(const vector<pair<bool,vector<string>>> & relations, size_t & index) override;

        
    private:
    /** @var condition from input parsed and transformed into variables of {@link #CConditionParser::CCondition} class
     * both operand in condition are names of different attributes
    */
        CConditionParser::CCondition m_conditions;
};


#pragma once

#include "Operator.h"
#include "ConditionParser.h"
#include "CompareOperator.h"

using namespace std;
/** Dervied class for  unary operator Selection (conditioned) Join in relation algebra
 * It selects tuples that satisfy the given predicate from a relation. */
class CSelection : public COperator, public CCompareOperator{
    public:
        CSelection (const string & condition) // Constructor
		:COperator(EOperatorType::UNARY), m_conditions(){
            m_conditions = CConditionParser().parse(condition);
        };

        ~CSelection() = default;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluate(const vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual pair<bool,vector<string>> toSQL(const vector<pair<bool,vector<string>>> & relations, size_t & index) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */

        virtual shared_ptr<CRelation> evaluateAtributes(const vector<shared_ptr<CRelation>> & relations) override;

        /** 
         * {@inheritDoc}
         * returs one (in case that the other one is a constant) or both operands from the condition (name/s of the atributes)
        */
        virtual vector<string> relevantAtribute(const vector<shared_ptr<CRelation>> & relations) override;
    private:
        /**
	 * Method evaluate expression for 1 operand without any data only with the path to import this data
	 * @param[in] path path to the file contains relation to import.
     * @returns shared pointer of {@link #CRelation} class with the result of evaluation
	 */
        shared_ptr<CRelation> evaluate(const string & path);

        /** @var condition from input parsed and transformed into variables of {@link #CConditionParser::CCondition} class
     * left operand contain name of attribute, right operand can contain konstant or name of another attribute different from the left one
        */
        CConditionParser::CCondition m_conditions;
 /**
	 * Method modify string from input contains konstant value from format 'const' into const (cast of single quotation marks)
	 * @param[in] word string from the input contains konstant
     * @returns modifyed string without csingle quotation marks
	 */
        string konstant(string word);

        

        

        
};
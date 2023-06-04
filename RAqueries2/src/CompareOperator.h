#include "ConditionParser.h"
#include "StringConvert.h"

/** Class for evaluation of comparing operator with input string */
class CCompareOperator{
    protected:
        CCompareOperator() = default;

        /**
	 * Method evaluate comparison operator with input string from user
	 * @param[in] l left operand of comparison, can be int ,float, double or string  
     * @param[in] r right operand of comparison, can be int ,float, double or string  
     * @param[in] m_operator comparison operator (<,>,<=,>=, ==, !=)
     * @returns true if the result of a comparison is valid
	 */
        bool evaluate(CStringConvert::m_variant l, CStringConvert::m_variant r, CConditionParser::EOperatorType m_operator);
};


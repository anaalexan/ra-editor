#include "CompareOperator.h"

using namespace std;


bool CCompareOperator::evaluate(CStringConvert::m_variant l, CStringConvert::m_variant r, CConditionParser::EOperatorType m_operator){
        switch(m_operator){
            case(CConditionParser::EOperatorType::eEqual):
                return (l == r);
            case(CConditionParser::EOperatorType::eNotEqual):
                return (l != r);
            case(CConditionParser::EOperatorType::eLess):
                return (l < r);
            case(CConditionParser::EOperatorType::eLessOrEqual):
                return (l <= r);
            case(CConditionParser::EOperatorType::eGreater):
                return (l > r);
            case(CConditionParser::EOperatorType::eGreaterOrEqual):
                return (l >= r);
            default:
                return false;
        }
}

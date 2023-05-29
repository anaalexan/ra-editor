#include "ConditionParser.h"
#include "StringConvert.h"


class CCompareOperator{
    public:
        CCompareOperator() = default;
        bool evaluate(int l, int r, CConditionParser::EOperatorType m_operator);
        bool evaluate(double l, double r, CConditionParser::EOperatorType m_operator);
        bool evaluate(float l, float r, CConditionParser::EOperatorType m_operator);
        bool evaluate(string l, string r, CConditionParser::EOperatorType m_operator);
};


#pragma once

#include <string>
#include <vector>

using namespace std;

class CConditionParser{
    public:

        enum EOperatorType{
            eEqual = 1,
            eNotEqual = 2,
            eLess= 3,
            eLessOrEqual= 4,
            eGreater = 5,
            eGreaterOrEqual = 6,
            eNoMatch
        };
        struct CCondition{
            CConditionParser::EOperatorType m_operator;
            string left;
            string right;
        };

        CCondition parse(const string & condition); //TBD tokenizace

        CConditionParser::EOperatorType stringToEnum(const string & op);

};
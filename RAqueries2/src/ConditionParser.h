#pragma once

#include <string>
#include <vector>

using namespace std;
/** Class for the management of the condition */
class CConditionParser{
    public:
        /** @var enum for the different type of comparison operators */
        enum EOperatorType{
            eEqual = 1,
            eNotEqual = 2,
            eLess= 3,
            eLessOrEqual= 4,
            eGreater = 5,
            eGreaterOrEqual = 6,
            eNoMatch
        };
        /** nested class for the condition */
        struct CCondition{
            /** @var enum type of the comparison operators */
            CConditionParser::EOperatorType m_operator;
            /** @var left operand */
            string left;
            /** @var right operand */
            string right;
        };

        /**
	 * Method parse input string from user into condition {@link #CCondition} class
	 * @param[in] condition input string from user contains condition 
     * @returns condition parsed into variables in {@link #CCondition} class
	 */
        CCondition parse(const string & condition); 

        /**
	 * Method convert operator from input string from user into enum type
	 * @param[in] op operator from input string
     * @returns operator {@link #CConditionParser::EOperatorType} typu enum
	 */
        CConditionParser::EOperatorType stringToEnum(const string & op);

        /**
	 * Method convert enum type operator into string 
	 * @param[in] op operator {@link #CConditionParser::EOperatorType} typu enum
     * @returns string with comparison operator
	 */
        string enumTostring(CConditionParser::EOperatorType & op);

};
#pragma once

#include <string>
#include <memory>


using namespace std;

class CExpression;
/** Class for variable in expresion, may contains another expression inside  */
class CVariable{        
    public:
        CVariable(const string & name, const shared_ptr<CExpression> expression) 
        :m_name(name), m_expression(expression){};

        /** @var unique name of the variable */
        string m_name;

        /** @var shared pointr of {@link #CExpression} class may contain whole expression 
         * for this variable or only path for this exact relation  */
        shared_ptr<CExpression> m_expression;
};
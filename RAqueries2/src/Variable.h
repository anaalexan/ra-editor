#pragma once

#include <string>
#include <memory>


using namespace std;

class CExpression;

class CVariable{        
    public:
        CVariable(const string & name, const shared_ptr<CExpression> expression) 
        :m_name(name), m_expression(expression){};

        string m_name;
        shared_ptr<CExpression> m_expression;
};
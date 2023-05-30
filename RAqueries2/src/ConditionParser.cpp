#include "ConditionParser.h"

using namespace std;

CConditionParser::EOperatorType CConditionParser::stringToEnum(const string & op){
    if(op == "==") return eEqual;
    if(op == "!=") return eNotEqual;
    if(op == "<") return eLess;
    if(op == "<=") return eLessOrEqual;
    if(op == ">") return eGreater;
    if(op == ">=") return eGreaterOrEqual;
    return eNoMatch;
}


CConditionParser::CCondition CConditionParser::parse(const string & condition){
    CCondition con;

    size_t i = 0;
    string word;
    while(condition[i] != '>' && condition[i] != ' ' && condition[i] !=  '<' && condition[i] != '=' && condition[i] != '!'){
        word.push_back(condition[i]);
        i++;
    }
    if(condition[i] == '>' || condition[i] ==  '<' || condition[i] == '=' || condition[i] == '!' || condition[i] == ' '){
            
        con.left = word;
        word.clear();
        string op;
        while(condition[i] == ' '){
            i++;
        }
        while(condition[i] == '>' || condition[i] ==  '<' || condition[i] == '=' || condition[i] == '!'){
                
            op.push_back(condition[i]);
            i++;
        }
        con.m_operator = stringToEnum(op);
        op.clear();
    }
    while(condition[i] == ' '){
        i++;
    }
    while(i < condition.size()){
        word.push_back(condition[i]);
        i++;
    }
    con.right = word;
    return con;
}



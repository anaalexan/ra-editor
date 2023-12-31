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
string CConditionParser::enumTostring(CConditionParser::EOperatorType & op){
    if(op == eEqual) return "=";
    if(op == eNotEqual) return "!=";
    if(op == eLess) return "<";
    if(op == eLessOrEqual) return "<=";
    if(op == eGreater) return ">";
    if(op == eGreaterOrEqual) return ">=";
    return " ";
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
    if(con.m_operator != eEqual && con.m_operator != eNotEqual && con.m_operator != eLess && con.m_operator != eLessOrEqual 
    && con.m_operator != eGreater && con.m_operator != eGreaterOrEqual){
        string sError = "Error wrong comparison operator.\nIt should be one of: >, <, <=, >=, ==, !=";
        throw sError;
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



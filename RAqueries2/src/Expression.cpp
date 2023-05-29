
#include <sstream>
#include <cstdio> 
#include <iostream>

#include "Expression.h"
#include "KeyRA.h"
#include "Token.h"
#include "Variable.h"

#include "CrossJoin.h"
#include "Difference.h"
#include "Intersection.h"
#include "NaturalJoin.h"
#include "Projection.h"
#include "Rename.h"
#include "Selection.h"
#include "ThetaJoin.h"
#include "Union.h"


using namespace std;

EKeyRA CExpression::charToEnum(char c){
    if(c == 'x'){
        return EKeyRA::CrossJoin;
    }
    if(c == '-'){
        return EKeyRA::Difference;
    }
    if(c == '&'){
        return EKeyRA::Intersection;
    }
    if(c == '*'){
        return EKeyRA::NaturalJoin;
    }
    if(c == '['){
        return EKeyRA::Projection;
    }
    if(c == '<'){
        return EKeyRA::Rename;
    }
    if(c == '('){
        return EKeyRA::Selection;
    }
    if(c == '^'){
        return EKeyRA::ThetaJoin;
    }
    if(c == '+'){
        return EKeyRA::Union ;
    }
    if(c == ' '){
        return EKeyRA::Space ;
    }
    if(c == '\"'){
        return EKeyRA::Quots ;
    }
    return EKeyRA::NoMatch;
}

void CExpression::tokenize(const string & expression, const vector<CVariable> & variables){
    
    for(size_t i = 0; i < expression.size(); i++){
        switch(charToEnum(expression[i])){
            
            case(EKeyRA::CrossJoin):
            {
                CCrossJoin op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CCrossJoin>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Difference):
            {
                CDifference op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CDifference>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Intersection):
            {
                CIntersection op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CIntersection>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::NaturalJoin):
            {
                CNaturalJoin op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CNaturalJoin>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Projection):
            {
                i++;
                string columnNames;
                while(expression[i+1] != ']'){
                    columnNames.push_back(expression[i]);
                    i++;
                }
                i++;
                CProjection op(columnNames);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CProjection>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Rename):
            {
                i++;
                string columnNames;
                while(expression[i+1] != '>'){
                    columnNames.push_back(expression[i]);
                    i++;
                }
                i++;
                CRename op(columnNames);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CRename>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Selection):
            {
                i++;
                string condition;
                int cnt = 0;
                while(expression[i+1] != ')' && cnt == 0){
                    if(expression[i+1] == '('){
                        cnt++;
                    }
                    if(expression[i+1] == ')'){
                        cnt--;
                    }
                    condition.push_back(expression[i]);
                    i++;
                }
                i++;
                CSelection op(condition);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CSelection>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;

            }
            case(EKeyRA::ThetaJoin):
            {
                i++;
                while(expression[i] == ' '){
                    i++;
                }
                string condition;
                int cnt = 0;
                while(expression[i+1] != ')' && cnt == 0){
                    if(expression[i+1] == '('){
                        cnt++;
                    }
                    if(expression[i+1] == ')'){
                        cnt--;
                    }
                    condition.push_back(expression[i]);
                    i++;
                }
                i++;
                CThetaJoin op(condition);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CThetaJoin>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Union):
            {
                CUnion op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<CUnion>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Quots):
            {
                string path;
                i++;
                while(expression[i] != '"'){
                    path.push_back(expression[i]);
                    i++;
                }
                CRelation rel(path);
                CToken tok (CToken::ETokenType::RELATION, make_shared<CRelation>(rel)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Space):
            {
                break;
            }
            
            default:
            {
                string word;
                while(expression[i+1] != ' ' && expression[i+1] != '(' && expression[i+1] != '[' && expression[i+1] != '<' && expression[i+1] != '*'
                && expression[i+1] != '^' && expression[i+1] != '&' && expression[i+1] != '+' && expression[i+1] != '-' && expression[i+1] != 'x'){
                    word.push_back(expression[i]);
                    i++;
                }
                word.push_back(expression[i]);
                i++;
                bool isHere = false;
                for(size_t j = 0; j < variables.size(); j++){
                    if(variables[j].m_name == word){
                        isHere = true;
                        for(size_t t = 0; t < variables[j].m_expression->m_tokens.size(); t++){
                            m_tokens.push_back(variables[j].m_expression->m_tokens[t]);
                        }
                        break;
                    }
                    if(j == variables.size()-1 && isHere == false){
                        cout << "There is no variable with the name: " << word << endl;
                    }
                }

            }
        }
    }
    cout << "end" << endl;
}


shared_ptr<CRelation> CExpression::evaluate(){
    vector<shared_ptr<CRelation>> stack;
    for(size_t i = 0; i < m_tokens.size(); i++){
        if(m_tokens[i]->m_type ==  CToken::ETokenType::RELATION){
            stack.push_back(m_tokens[i]->m_relation);
        }
        if(m_tokens[i]->m_type ==  CToken::ETokenType::OPERATOR){
            vector<shared_ptr<CRelation>> relations;
            if(m_tokens[i]->m_operator->m_type == COperator::EOperatorType::BINARY){
                relations.push_back(*(stack.end()-2));
                relations.push_back(*(stack.end()-1));
            }
            if(m_tokens[i]->m_operator->m_type == COperator::EOperatorType::UNARY){
                
                relations.push_back(*(stack.end()-1));
            }
            
            shared_ptr<CRelation> res;
            res = m_tokens[i]->m_operator->evaluate(relations);
            stack.push_back(res);
        }
    }
    if(m_tokens.size() != 0 || stack.size() != 1){
        cout << "Error. Wrong number of operators or operands." << endl;
    }else{
        return stack[0];
    }
    
}
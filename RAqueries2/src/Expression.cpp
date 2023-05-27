
#include <sstream>
#include <cstdio> 

#include "Expression.h"
#include "KeyRA.h"
#include "Token.h"

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
    if(c == 'x'){
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
}

void CExpression::tokenize(const string & expression){
    string word;
    for(size_t i = 0; i < expression.size(); i++){
        switch(charToEnum(expression[i])){
            
            case(EKeyRA::CrossJoin):
            {
                CCrossJoin op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Difference):
            {
                CDifference op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Intersection):
            {
                CIntersection op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::NaturalJoin):
            {
                CNaturalJoin op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Projection):
            {
                i++;
                string columnNames;
                while(expression[i] != ']'){
                    columnNames.push_back(expression[i]);
                    i++;
                }
                i--;
                CProjection op(columnNames);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Rename):
            {
                i++;
                string columnNames;
                while(expression[i] != '>'){
                    columnNames.push_back(expression[i]);
                    i++;
                }
                i--;
                CRename op(columnNames);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Selection):
            {
                i++;
                string condition;
                int cnt = 0;
                while(expression[i] != ')' && cnt == 0){
                    if(expression[i] != '('){
                        cnt++;
                    }
                    if(expression[i] != ')'){
                        cnt--;
                    }
                    condition.push_back(expression[i]);
                    i++;
                }
                i--;
                CSelection op(condition);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;

            }
            case(EKeyRA::ThetaJoin):
            {
                i++;
                while(expression[i] == ' ' ){
                    i++;
                }
                string condition;
                int cnt = 0;
                while(expression[i] != ')' && cnt == 0){
                    if(expression[i] != '('){
                        cnt++;
                    }
                    if(expression[i] != ')'){
                        cnt--;
                    }
                    condition.push_back(expression[i]);
                    i++;
                }
                i--;
                CThetaJoin op(condition);
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Union):
            {
                CUnion op;
                CToken tok (CToken::ETokenType::OPERATOR, make_shared<COperator>(op)) ;
                m_tokens.push_back(make_shared<CToken>(tok));
                break;
            }
            case(EKeyRA::Space):
            {

                break;
            }
            default:
            {
                nevim
                word.push_back(expression[i]);
            }
        }
    }
}
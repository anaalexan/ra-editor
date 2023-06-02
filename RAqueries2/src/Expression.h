#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "Token.h"
#include "Relation.h"
#include "KeyRA.h"
#include "Operator.h"
//#include "Variable.h"

class CVariable;

class CExpression{
	public:
		CExpression (const string & expression, const vector<CVariable> & variables)
		:m_tokens(){tokenize(expression, variables);};

	    shared_ptr<CRelation> evaluate();

		vector<shared_ptr<CToken>> m_tokens;	
	private:
		EKeyRA charToEnum(char c);
		void tokenize(const string & expression, const vector<CVariable> & variables);

		vector<string> m_relevantAtribute;
		vector<string> findRelevantAtribute();

		
		
};
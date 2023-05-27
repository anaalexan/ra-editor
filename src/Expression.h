#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "Token.h"
#include "Relation.h"


class CExpression{
	public:
		CExpression (const string & expression)
		:m_tokens(){tokenize(expression);};

	    shared_ptr<CRelation> evaluate();		
	private:
		void tokenize(const string & expression);

		vector<shared_ptr<CToken>> m_tokens;

};
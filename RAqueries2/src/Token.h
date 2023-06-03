#pragma once

#include <string>
#include <memory>

#include "Relation.h"
#include "Operator.h"

using namespace std;

class CToken{		
	public:
		enum ETokenType{RELATION, OPERATOR} m_type;
		
		shared_ptr<CRelation> m_relation;
		shared_ptr<COperator> m_operator;

		

		CToken (ETokenType type, shared_ptr<CRelation> relation) // Constructor
		:m_type(type), m_relation(relation), m_operator(nullptr){};

		CToken (ETokenType type, shared_ptr<COperator> op) // Constructor
		:m_type(type), m_relation(nullptr), m_operator(op){};

		


	private:		
		
};
#pragma once

#include <string>
#include <memory>

#include "Relation.h"
#include "Operator.h"

using namespace std;
/** Class for token in expresion, can be either operator or operand */
class CToken{		
	public:
		/** @var enum says if its operator or operand */
		enum ETokenType{RELATION, OPERATOR} m_type;
		
		/** @var shared pointer of {@link #CRelation} class, uninitialized in case if token is operator */
		shared_ptr<CRelation> m_relation;
		/** @var shared pointer of one of the derivated class of {@link #COperator}, uninitialized in case if token is operand */
		shared_ptr<COperator> m_operator;

		

		CToken (ETokenType type, shared_ptr<CRelation> relation) // Constructor
		:m_type(type), m_relation(relation), m_operator(nullptr){};

		CToken (ETokenType type, shared_ptr<COperator> op) // Constructor
		:m_type(type), m_relation(nullptr), m_operator(op){};

				
		
};
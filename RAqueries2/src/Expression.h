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
/** Class for expression in relational algebra contains tokens with operators and operands to evaluate  */
class CExpression{
	public:
		CExpression (const string & expression, const vector<CVariable> & variables)
		:m_tokens(){tokenize(expression, variables);};

		/**
	 * Method evaluate expression in relational algebra. Take tokens from the stack and evaluate them one by one
     * @returns shared pointer of {@link #CRelation} with the result of evaluation in RA
	 */
	    shared_ptr<CRelation> evaluate();
		/**
	 * Method translate expression in relational algebra into SQL. The same principle like evaluation.
     * @returns vector of rows (string) with the translated expression into SQL
	 */
		vector<string> translateToSQL();
	/** @var vector shared pointers of tokens {@link #CToken} (operator/s and operand/s) from expression separated from input */
		vector<shared_ptr<CToken>> m_tokens;	

	private:

		
		/**
	 * Method parsing expression into single tokens of operator/s and operand/s 
	 * @param[in] expression input string from user with expression to evaluate
     *  @param[in,out] variables vector of variables {@link #CVariable}, may content another expression
	 */
		void tokenize(const string & expression, const vector<CVariable> & variables);
		/**
	 * Method looking for a relevant for expression atrubutes in the relations to import
	 * @returns vector of single atributes (string) from the relation/s
	 */
		vector<string> findRelevantAtribute();
		/**
	 * Method modify single char represent one RA operator into enum 
	 * * @param[in] c input char from expression from user 
	 * @returns enum type of RA operator 
	 */
		EKeyRA charToEnum(char c);
		/** @var a relevant for expression atrubutes in the relation/s to import*/
		vector<string> m_relevantAtribute;

		
		
};
#pragma once

#include <vector>

#include "Relation.h"
#include "FileService.h"

using namespace std;    

/** Base class for every operator in relational algebra */

class COperator{        
    public:
        enum EOperatorType{BINARY, UNARY} m_type;

        COperator (EOperatorType type) // Constructor
		:m_type(type){};

        /**
	 * Method evaluate expression for 1 or 2(binary operator) operand/s
	 * @param[in] relations vector contins 1 or 2 shared pointers of {@link #CRelation} class.
     * @returns shared pointer of {@link #CRelation} class with the result of evaluation
	 */
        virtual shared_ptr<CRelation> evaluate(const vector<shared_ptr<CRelation>> & relations) = 0;

        /**
	 * Method evaluate expression for 1 or 2(binary operator) operand/s only on atributes of relation/s
	 * @param[in] relations vector contins 1 or 2 shared pointers of {@link #CRelation} class.
     * @returns shared pointer of {@link #CRelation) class with the attribute result of evaluation
	 */
        virtual shared_ptr<CRelation> evaluateAtributes(const vector<shared_ptr<CRelation>> & relations) = 0;


        /**
	 * Method translate expression for 1 or 2(binary operator) operand/s 
	 * @param[in] relations vector contins 1 or 2 pair of bool(contains information if the relation is intermediate result(true) or not (false))
     * and vector of strings contains name or path of the relation(in case its a intermediate result) or rows with the previous evaluation.
     *  @param[in,out] index sequence number of intermidiate relults 
     * @returns pair of bool(intermediate result(true)) and vector of strings contains rows with the expression in SQL
	 */
        virtual pair<bool,vector<string>> toSQL(const vector<pair<bool,vector<string>>> & relations, size_t & index) = 0;

        /**
	 * Method returns relevant atribute for the specific operator
	 * @param[in] relations vector contins 1 or 2 shared pointers of {@link #CRelation} class.
     * @returns vector of strings contains relevant atribute for the specific operator
	 */
        virtual vector<string> relevantAtribute(const vector<shared_ptr<CRelation>> & relations);

         /**
	 * Method checks if specific relation has a path(so its a empty relation and it has need to import data from the path) or 
     * its an indermediate result with no path, but with the relation inside
	 * @param[in] relation shared pointer of {@link #CRelation} class.
     * @returns  shared pointer of {@link #CRelation} class with the same relation or with new uploaded data from the path
	 */
        shared_ptr<CRelation> importRelation(const shared_ptr<CRelation> & relation);

    /**
	 * Method checks if specific relation has a path(so its a empty relation and it has need to import data from the path) or 
     * its an indermediate result with no path, but with the relation inside
	 * @param[in] relations shared pointer of {@link #CRelation) class.
     * @returns  shared pointer of {@link #CRow} class with the row from same relation or with new uploaded data from the path
	 */
        CRow importAtributes(const shared_ptr<CRelation> & relation);

    protected:  
        /**
	 * Method create a vector of row newQuery with partial expression in SQL with an intermeduate result as an operand of the expression
	 * @param[in,out] newQuery vector of strings contains rows with partion result of expression in SQL
     * @param[in,out] oldQuery pair of bool and vector of strings contains result rows with the result of previous expression in SQL with the bool true
     * (intermediate result)
     * or just a name or path of the relation with the bool false(not intermediate result)
     * @param[in,out] index sequence number of intermidiate relults 
     * @param[in,out] name the name of a new intermediate result
	 */
        void makeTmpSTR(vector<string> & newQuery, const pair<bool,vector<string>> & oldQuery, size_t & index, string & name);
        
    /**
	 * Method create a vector of row newQuery with partial expression in SQL
     * no matter if its an intermediate result or the original relation
	 * @param[in,out] newQuery vector of strings contains rows with partion result of expression in SQL
     * @param[in,out] oldQuery pair of bool and vector of strings contains result rows with the result of previous expression in SQL with the bool true
     * (intermediate result)
     * or just a name or path of the relation with the bool false(not intermediate result)
     * @param[in,out] index sequence number of intermidiate relults 
     * @param[in,out] name the name of existed relation or new intermediate result
	 */
        void operatorToString(vector<string> & newQuery, const pair<bool,vector<string>> & oldQuery, size_t & index, string & name);
        
        
};
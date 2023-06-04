#pragma once

#include "Operator.h"

using namespace std;
/** Dervied class for unary operator Projection relation algebra
 * It projects column(s) that satisfy a given predicate. */
class CProjection : public COperator{
    public:
        CProjection (const string & columnNames) // Constructor
		:COperator(EOperatorType::UNARY), m_columnNames(){parse(columnNames);};

        ~CProjection() = default;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluate(const vector<shared_ptr<CRelation>> & relations) override;
        
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual pair<bool,vector<string>> toSQL(const vector<pair<bool,vector<string>>> & relations, size_t & index) override;

        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluateAtributes(const vector<shared_ptr<CRelation>> & relations) override;


        /** 
         * {@inheritDoc}
         * returs all the names of atribute that will be projected 
        */
        virtual vector<string> relevantAtribute(const vector<shared_ptr<CRelation>> & relations) override;
    private:
        /** @var vector of strings with all the names of atribute that will be projected  */
        vector<string> m_columnNames;
        /**
	 * Method parsing the input string from user into vector of strings 
	 * @param[in] columnNames input string from user contains column names to project separated by coma
	 */
        void parse(const string & columnNames);

         /**
	 * Method evaluate expression for 1 operand without any data only with the path to import this data
	 * @param[in] path path to the file contains relation to import.
     * @returns shared pointer of {@link #CRelation} class with the result of evaluation
	 */
        shared_ptr<CRelation> evaluate(const string & path);
        
};
#pragma once

#include "Operator.h"
#include <string>

using namespace std;
/** Dervied class for  unary operator Rename relation algebra
 * Change name of 0 to n atributes in the relation  */
class CRename : public COperator{        
    public:
        CRename (const string & columnNames) // Constructor
		:COperator(EOperatorType::UNARY), m_oldNewNames(){parse(columnNames);};
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual pair<bool,vector<string>> toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index) override;
        /** 
         * {@inheritDoc}
         * @param[in] relations vector contains 1 shared pointer of {@link #CRelation} class.
        */
        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) override;
        /** 
         * {@inheritDoc}
         * returs all the atributes to rename (old and new ones)
        */
        virtual vector<string> relevantAtribute(vector<shared_ptr<CRelation>> & relations) override;
    private:
        /** @var vector of pairs strings, first is old name to rename, second is new name to rename to */
        vector<pair<string,string>> m_oldNewNames;

        /**
	 * Method parse input string from user into into vector of pairs m_oldNewNames
	 * @param[in] columnNames input string from user contains column names to rename in format old name1, new name1;...; old nameN, new nameN
	 */
        void parse(const string & columnNames);

        

        
};


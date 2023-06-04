#pragma once

#include <vector>

#include "Relation.h"
#include "FileService.h"

using namespace std;    

class COperator{        
    public:
        enum EOperatorType{BINARY, UNARY} m_type;

        COperator (EOperatorType type) // Constructor
		:m_type(type){};

        virtual shared_ptr<CRelation> evaluate(vector<shared_ptr<CRelation>> & relations) = 0;

        virtual shared_ptr<CRelation> evaluateAtributes(vector<shared_ptr<CRelation>> & relations) = 0;
        virtual pair<bool,vector<string>> toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index) = 0;

        virtual vector<string> relevantAtribute(vector<shared_ptr<CRelation>> & relations);

        shared_ptr<CRelation> importRelation(shared_ptr<CRelation> relation);

        CRow importAtributes(shared_ptr<CRelation> relation);

        void makeTmpSTR(vector<string> & newQuery, pair<bool,vector<string>> & oldQuery, size_t & index, string & name);
        

        void operatorToString(vector<string> & newQuery, pair<bool,vector<string>> & relations, size_t & index, string & name);
        
        
};
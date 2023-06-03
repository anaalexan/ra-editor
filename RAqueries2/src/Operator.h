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

        virtual vector<string> relevantAtribute(vector<shared_ptr<CRelation>> & relations){
            vector<string> vec;
            return vec;
        }

        virtual pair<bool,string> toSQL(vector<pair<bool,string>> & relations, size_t & index) = 0;
        
    //private:

        virtual string operatorToString(pair<bool,string> & relations, size_t & index){
            string str = "SELECT DISTINCT * \nFROM ";
            if(relations.first == false){
                str += relations.second + "\n";
            }else{
                str += "(" + relations.second + ")" + "AS TMP" + to_string(index++) + "\n";
            }
            return str;
        }

        shared_ptr<CRelation> importRelation(shared_ptr<CRelation> relation){

            shared_ptr<CRelation> sptr1;
    
            if(relation->getPath().size() != 0){
                CFileService file;
                sptr1 = make_shared<CRelation>(relation->getPath());
                file.importFromFile(sptr1);
            }else{
                sptr1 = relation;
            }
            return sptr1;
        }

        CRow importAtributes(shared_ptr<CRelation> relation){

            CRow row;
            
            shared_ptr<CRelation> sptr1;
            if(relation->getPath().size() != 0){
                CFileService file;
                sptr1 = make_shared<CRelation>(relation->getPath());
                row = file.importAtriburesFromFile(sptr1);
            }else{
                row = relation->m_rows[0];
            }
            return row;
        }

        
        
};
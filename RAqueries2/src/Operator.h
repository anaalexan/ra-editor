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

        virtual pair<bool,vector<string>> toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index) = 0;
        
    

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
        //private:

        

        void makeTmpSTR(vector<string> & newQuery, pair<bool,vector<string>> & oldQuery, size_t & index, string & name){
            newQuery.push_back("\n");
            newQuery.push_back("( \n" );

            for (auto & element : oldQuery.second){
                if(oldQuery.second.size() > 5){
                    newQuery.push_back(tab + element);
                
                }else{
                    newQuery.push_back(element);
                }
            }
            name = "TMP" + to_string(++index);
            newQuery.push_back(") AS " + name + "\n");
        }
        

        void operatorToString(vector<string> & newQuery, pair<bool,vector<string>> & relations, size_t & index, string & name){
            
            newQuery.push_back("SELECT DISTINCT *\n");
            newQuery.push_back("FROM ");
            if(relations.first == false){
                name = relations.second[0];
                newQuery[newQuery.size()-1] += name + "\n";
                //newQuery.push_back(name + "\n");
            }else{
                makeTmpSTR(newQuery, relations, index, name);
            }
        }
        /*void makeSTR(string str, string & name, vector<string> & rows){
            rows.push_back("FROM " + str);
            name = str;
        }

        void makeTmpSTR(vector<string> & newQuery, size_t & index, string & name, vector<string> & oldQuery){
            newQuery.push_back("FROM (");
            for (auto & element : oldQuery){
                newQuery.push_back(tab + element);
            }
            name = "TMP" + to_string(++index);
            newQuery[newQuery.size() - 1] += ") AS " + name;
        }
        

        virtual vector<string> operatorToString(vector<string> & newQuery, pair<bool,vector<string>> & relations, size_t & index, string & name){
            
            newQuery.push_back("SELECT DISTINCT *");
            if(relations.first == false){
                makeSTR(newQuery[0], name, relations.second);
            }else{
                makeTmpSTR(newQuery, index, name, relations.second);
            }
            return newQuery;
        }*/

        /*string makeSTR(string str, size_t & index, string & name){
            name = str;
            string str1 = name;
            return str1;
        }

        string makeTmpSTR(string str, size_t & index, string & name){
            name = "TMP" + to_string(++index);
            string str1;
            str1 =  "(\n" + tab + str + ")" + " AS " + name + "\n";
            return str1;
        } */

        /*virtual string operatorToString(pair<bool,string> & relations, size_t & index, string & name){
            string sel = "SELECT DISTINCT * \nFROM ";
            //for()
            string str;
            if(relations.first == false){
                str = makeSTR(relations.second, index, name);
            }else{
                str = makeTmpSTR(relations.second, index, name);
            }
            string res = sel + str + "\n";
            return res;
        }*/

        string tab = "    ";

        
        
};
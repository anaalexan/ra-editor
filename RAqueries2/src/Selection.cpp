#include "Selection.h"
#include "CompareOperator.h"
#include "StringConvert.h"
#include <iostream>
#include  <sstream>
#include <fstream>
#include <variant>

using namespace std;



string CSelection::konstant(string word){
    string newWord;
    for(size_t i = 1; i < word.size()-1; i++){
        newWord.push_back(word[i]);
    }
    return newWord;
}

/*pair<bool,vector<string>> CRename::toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index){
    vector<string> newQuery;
    newQuery.push_back("SELECT DISTINCT ");
    string names,name1;
    for( size_t n = 0; n < m_oldNewNames.size(); n++){
        if(n != 0){
            names += ", ";
        }
        names += m_oldNewNames[n].first + " AS " + m_oldNewNames[n].second ;
    }
    string from = "\nFROM ";
    newQuery.push_back(names);
    newQuery.push_back(from);
    if(relations[0].first == false){
        newQuery.push_back(relations[0].second[0] + "\n");
    }else{
        makeTmpSTR(newQuery, relations[0].second, index, name1);
    }
    
    return make_pair(true, newQuery);
}*/

pair<bool,vector<string>> CSelection::toSQL(vector<pair<bool,vector<string>>> & relations, size_t & index){
    string name1;
    vector<string> newQuery;
    operatorToString(newQuery, relations[0], index, name1);
    newQuery.push_back("WHERE ");
    
    CConditionParser enumOperator;
    string conRight;
    if(m_conditions.right[0] == '\''){
        if(isdigit(m_conditions.right[1]) != 0){
            conRight = konstant(m_conditions.right);
        }else{
            conRight = m_conditions.right;  
        }
    }else{  
        conRight = name1 + "." + m_conditions.right; 
    }

    string condition = name1 + "." + m_conditions.left + " " + enumOperator.enumTostring(m_conditions.m_operator) + " " +  conRight;
    newQuery[newQuery.size()-1] += condition + "\n";
    //newQuery.push_back(condition + "\n");
    return make_pair(true, newQuery);
}

vector<string> CSelection::relevantAtribute(vector<shared_ptr<CRelation>> & relations){
    vector<string> vec;
    vec.push_back(m_conditions.left);
    if(m_conditions.right[0] != '\''){
        vec.push_back(m_conditions.right); 
    }
    return vec;
}

shared_ptr<CRelation> CSelection::evaluateAtributes(vector<shared_ptr<CRelation>> & relations){

    shared_ptr<CRelation> sptr1;

    CRow row1;
    row1 = importAtributes(relations[0]);
    CRelation res;
    res.m_rows.push_back(row1);
    return make_shared<CRelation>(res); 
}

shared_ptr<CRelation> CSelection::evaluate(const string & path){
    ifstream fin(path);
    string line, word;
    CRelation res;

    if(!fin.is_open()){
        string sError = "Error. Cannot open file: " + path;
        throw  sError;
    }
    
    getline(fin, line);
    CRow row;
    stringstream ss(line);
    while (getline(ss, word, ',')){
        //save name of atributes to project into final relation
        row.m_values.push_back(word);
    }
    res.m_rows.push_back(row);
    bool isHere = false;
    size_t indexL;
    //check if relation contains the atribute from condition
    for(size_t j = 0; j < res.m_rows[0].m_values.size(); j++){
        if(m_conditions.left == res.m_rows[0].m_values[j]){
            isHere = true;
            indexL = j;
            break;
        }
        if(isHere == false && j == res.m_rows[0].m_values.size()-1){
            string sError = "Error. Cannot evaluate Selection. Name of the atribute: " + m_conditions.left + " has not been found in the relation";
            throw  sError;
        }
    }
    string konst;
    size_t indexR;
    if(m_conditions.right[0] == '\''){
        konst = konstant(m_conditions.right);  
    }else{  
        for(size_t j = 0; j < res.m_rows[0].m_values.size(); j++){
            if(m_conditions.right == res.m_rows[0].m_values[j]){
                isHere = true;
                indexR = j;
                break;
            }

            if(isHere == false && j == res.m_rows[0].m_values.size()-1){

                string sError = "Error. Cannot evaluate Selection. Name of the atribute: " + m_conditions.right + " has not been found in the relation";
                throw  sError;
            }
        }
    }

    while(getline(fin, line)){
        CRow row;
        stringstream ss(line);
        while (getline(ss, word, ',')){
            //save name of atributes to project into final relation
            row.m_values.push_back(word);
        }
        CCompareOperator compare;
        CStringConvert convert;
        if(m_conditions.right[0] == '\''){
            CStringConvert::m_variant left_con = convert.whatType(row.m_values[indexL]);
            CStringConvert::m_variant right_con = convert.whatType(konst);
            if(compare.evaluate(left_con, right_con, m_conditions.m_operator)){
                res.m_rows.push_back(row);
            }
            
        }else{
            //check if current line meet condition
            CStringConvert::m_variant left_con = convert.whatType(row.m_values[indexL]);
            CStringConvert::m_variant right_con = convert.whatType(row.m_values[indexR]);
            if(compare.evaluate(left_con, right_con, m_conditions.m_operator)){
                res.m_rows.push_back(row);
            }
            
            

        }
    }
    fin.close();
    return make_shared<CRelation>(res);   

}

shared_ptr<CRelation> CSelection::evaluate(vector<shared_ptr<CRelation>> & relations){
    if(relations[0]->getPath().size() != 0){

        return evaluate(relations[0]->getPath());

    }else{

        CRelation res;
        bool isHere = false;
        size_t indexL;
        //check if relation contains the atribute from condition
        size_t rowSize = relations[0]->m_rows[0].m_values.size();
        for(size_t j = 0; j < rowSize; j++){
            string word = relations[0]->m_rows[0].m_values[j];
            if(m_conditions.left == word){
                isHere = true;
                indexL = j;
                break;
            }
            if(isHere == false && (j == rowSize -1)){
                string sError = "Error. Cannot evaluate Selection. Name of the atribute: " + m_conditions.left + " has not been found in the relation";
                throw  sError;
            }
        }
        //save name of atributes to project into final relation
        res.m_rows.push_back(relations[0]->m_rows[0]);
    
        string konst;
        CCompareOperator compare;
        CStringConvert convert;
        if(m_conditions.right[0] == '\''){
            konst = konstant(m_conditions.right);
            for(size_t j = 1; j < relations[0]->m_rows.size(); j++){
                CStringConvert::m_variant left_con = convert.whatType(relations[0]->m_rows[j].m_values[indexL]);
                CStringConvert::m_variant right_con = convert.whatType(konst);
                if(compare.evaluate(left_con, right_con, m_conditions.m_operator)){
                    res.m_rows.push_back(relations[0]->m_rows[j]);
                }
            }
        }else{
            size_t indexR;
            //check if relation contains the atribute from condition
            for(size_t j = 0; j < res.m_rows[0].m_values.size(); j++){
                if(m_conditions.right == res.m_rows[0].m_values[j]){
                    isHere = true;
                    indexR = j;
                    break;
                }
                if(isHere == false && j == res.m_rows[0].m_values.size()-1){
                    string sError = "Error. Cannot evaluate Selection. Name of the atribute: " + m_conditions.right + " has not been found in the relation";
                    throw  sError;
                }
            }
            for(size_t j = 1; j < relations[0]->m_rows.size(); j++){
                CStringConvert::m_variant left_con = convert.whatType(relations[0]->m_rows[j].m_values[indexL]);
                CStringConvert::m_variant right_con = convert.whatType(relations[0]->m_rows[j].m_values[indexR]);

                if(compare.evaluate(left_con, right_con, m_conditions.m_operator)){
                    res.m_rows.push_back(relations[0]->m_rows[j]);
                }
            }
        }
        return make_shared<CRelation>(res);  
    }  
}

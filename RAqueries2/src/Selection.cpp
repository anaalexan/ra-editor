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
    for(size_t i = i; i < word.size()-1; i++){
        newWord.push_back(word[i]);
    }
    return newWord;
}

shared_ptr<CRelation> CSelection::evaluate(const string & path){
    ifstream fin(path);
    string line, word;
    CRelation res;

    if(!fin.is_open()){
        cout << "Could not open file" << endl;
        return nullptr;
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
            cout << "Name of the atribute: " <<  "\"" << m_conditions.left << "\" has not been found in the relation" << endl;
            return nullptr;
        }
    }
    while(getline(fin, line)){
        CRow row;
        stringstream ss(line);
        while (getline(ss, word, ',')){
            //save name of atributes to project into final relation
            row.m_values.push_back(word);
        }
        string konst;
        CCompareOperator compare;
        CStringConvert convert;
        if(m_conditions.right[0] == '\''){
            konst = konstant(m_conditions.right);
            if(compare.evaluate(convert.whatType(konst), convert.whatType(row.m_values[indexL]), m_conditions.m_operator)){
                res.m_rows.push_back(row);
            }
            
        }else{
            size_t indexR;
            for(size_t j = 0; j < res.m_rows[0].m_values.size(); j++){
                if(m_conditions.right == res.m_rows[0].m_values[j]){
                    isHere = true;
                    indexR = j;
                    break;
                }
                if(isHere == false && j == res.m_rows[0].m_values.size()-1){
                    cout << "Name of the atribute: " <<  "\"" << m_conditions.right << "\" has not been found in the relation" << endl;
                    return nullptr;
                }
            }
            
            if(compare.evaluate(convert.whatType(m_conditions.right), convert.whatType(row.m_values[indexR]), m_conditions.m_operator)){
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
        for(size_t j = 0; j < relations[0]->m_rows[0].m_values.size(); j++){
            if(m_conditions.left == res.m_rows[0].m_values[j]){
                isHere = true;
                indexL = j;
                break;
            }
            if(isHere == false && j == relations[0]->m_rows[0].m_values.size()-1){
                cout << "Name of the atribute: " <<  "\"" << m_conditions.left << "\" has not been found in the relation" << endl;
                return nullptr;
            }
        }
        //save name of atributes to project into final relation
        res.m_rows.push_back(relations[0]->m_rows[0]);
    
        string konst;
        CCompareOperator compare;
        CStringConvert convert;
        if(m_conditions.right[0] == '\''){
            konst = konstant(m_conditions.right);
            for(size_t j = 0; j < res.m_rows.size(); j++){
                if(compare.evaluate(convert.whatType(konst), convert.whatType(res.m_rows[j].m_values[indexL]), m_conditions.m_operator)){
                    res.m_rows.push_back(res.m_rows[j]);
                }
            }
        }else{
            size_t indexR;
            for(size_t j = 0; j < res.m_rows[0].m_values.size(); j++){
                if(m_conditions.right == res.m_rows[0].m_values[j]){
                    isHere = true;
                    indexR = j;
                    break;
                }
                if(isHere == false && j == res.m_rows[0].m_values.size()-1){
                    cout << "Name of the atribute: " <<  "\"" << m_conditions.right << "\" has not been found in the relation" << endl;
                    return nullptr;
                }
            }
            for(size_t j = 0; j < res.m_rows.size(); j++){
                if(compare.evaluate(convert.whatType(m_conditions.right), convert.whatType(res.m_rows[j].m_values[indexR]), m_conditions.m_operator)){
                    res.m_rows.push_back(res.m_rows[j]);
                }
            }
        }
        return make_shared<CRelation>(res);  
    }  
}

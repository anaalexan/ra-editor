#include "Projection.h"
#include "FileService.h"
#include "Relation.h"
#include <iostream>
#include  <sstream>
#include <fstream>

using namespace std;

void CProjection::parse(const string & columnNames){
    stringstream ss(columnNames);
    string word;
    while (getline(ss, word, ',')){
        m_columnNames.push_back(word);
    }
}

pair<bool,string> CProjection::toSQL(vector<pair<bool,string>> & relations, size_t & index){
    string str1 = "SELECT DISTINCT ";
    string names;
    for( size_t n = 0; n < m_columnNames.size(); n++){
        if(n != 0){
            names += ", ";
        }
        names += m_columnNames[n];
    }

    string from = "\nFROM ";
    string name1;
    if(relations[0].first == false){
        name1 = relations[0].second;
    }else{
        name1 += "(" + relations[0].second + ")" + "AS TMP" + to_string(index++) + "\n";
    }
      
    string res = str1 + names + from + name1;
    bool isTMPres = true;
    return make_pair(isTMPres, res);
}

vector<string> CProjection::relevantAtribute(vector<shared_ptr<CRelation>> & relations){
    vector<string> vec;
    for(size_t i = 0; i < m_columnNames.size(); i++){
        vec.push_back(m_columnNames[i]);
    }
    return vec;
}

shared_ptr<CRelation> CProjection::evaluateAtributes(vector<shared_ptr<CRelation>> & relations){

    shared_ptr<CRelation> sptr1;

    CRow row1;
    row1 = importAtributes(relations[0]);
    CRelation res;

    bool isHere = false;
    CRow rowName;
    //search for an atributres for projection
    for(size_t i = 0; i < m_columnNames.size(); i++){
            
        isHere = false;
        for(size_t cnt = 0; cnt < row1.m_values.size(); cnt++){
            if(m_columnNames[i] == row1.m_values[cnt]){
                isHere = true;

                //copy name of the atribute into final relation
                rowName.m_values.push_back(row1.m_values[cnt]);
                   
                break;
            }
            if(cnt == row1.m_values.size() - 1 && isHere == false){
                string sError = "Error. Name of the column, that you want to project: "  + m_columnNames[i] + " has not been found in the relation";
                throw sError;
            }
        }
    }
    res.m_rows.push_back(rowName);
    return make_shared<CRelation>(res); 
}

shared_ptr<CRelation> CProjection::evaluate(const string & path){
    /*shared_ptr<CRelation> sptr1;
    CFileService file;
    sptr1 = make_shared<CRelation>(path);
    file.importFromFile(sptr1);*/
    ifstream fin(path);
    string line, word;
    CRelation res;

    if(!fin.is_open()){
        string sError = "Error. Cannot open file: " + path;
        throw  sError;
    }
    
    getline(fin, line);
    bool isHere = false;
    vector<size_t> indexes;
    CRow rowName;
    
    for(size_t i = 0; i < m_columnNames.size(); i++){
        stringstream ss(line);
        
        size_t idx = 0;
        while (getline(ss, word, ',')){
            
            if(word == m_columnNames[i]){

                //save indexes of atributes to project into vector 
                indexes.push_back(idx);
                //save name of atributes to project into final relation
                rowName.m_values.push_back(word);
                idx++;
                isHere = true;
                break;
            }else{
                idx++;
            }
            
        }
        if(isHere == false){
            string sError = "Error. Name of the column, that you want to project: "  + m_columnNames[i] + " has not been found in the relation";
            throw sError;
        }
        

    }
    res.m_rows.push_back(rowName);

    //no need to check first line for duplikates
    getline(fin, line);
    vector<string> vecLine;
    stringstream ss(line);

    //line from fin transform into vector
    while (getline(ss, word, ',')){
        vecLine.push_back(word);
    }
    CRow row;
    //create a single row from projection
    for(size_t i = 0; i < indexes.size(); i++){
        row.m_values.push_back(vecLine[indexes[i]]);
    }
    res.m_rows.push_back(row);

    while(getline(fin, line)){
        vector<string> vecLine;
        stringstream ss(line);

        //line from fin transform into vector
        while (getline(ss, word, ',')){
            vecLine.push_back(word);
        }
        CRow row;
        //create a single row from projection
        for(size_t i = 0; i < indexes.size(); i++){
            row.m_values.push_back(vecLine[indexes[i]]);
        }
        isHere = false;

        //cheking for duplicates rows
        size_t cntRows = res.m_rows.size();
        for(size_t i = 1; i < res.m_rows.size(); i++){
            size_t sizeRow = res.m_rows[i].m_values.size();
            string nevim = res.m_rows[i].m_values[0];
            for(size_t j = 0; j < sizeRow; j++){
                string word1 = res.m_rows[i].m_values[0];
                string word2 = row.m_values[0];
                if(word1 == word2){
                    if(res.m_rows[0].m_values.size() == 1){
                        isHere = true;
                    }else{
                        while((j+1) < res.m_rows[0].m_values.size()){
                            if(res.m_rows[i].m_values[j+1] == row.m_values[j+1]){
                                break;
                            }
                            j++;
                        }
                        
                        if(res.m_rows[i].m_values[j] != row.m_values[j]){
                            
                            break;
                        }
                        if(j == res.m_rows[0].m_values.size()-1){
                            isHere = true;
                        }
                    }
                }else{
                    break;
                }
            }
            if(isHere == true){
                break;
            }
            //save row into final relation if final relation does not contain  the same row
            if(isHere == false && i == res.m_rows.size()-1){
                res.m_rows.push_back(row);
                break;
            }
            
        }

    }
    fin.close();
    return make_shared<CRelation>(res);
}


shared_ptr<CRelation> CProjection::evaluate(vector<shared_ptr<CRelation>> & relations){
    
    if(relations[0]->getPath().size() != 0){

        return evaluate(relations[0]->getPath());

    }else{

        CRelation res;
        vector<size_t> indexes;
        bool isHere = false;
        CRow rowName;
        //search for an atributres for projection
        for(size_t i = 0; i < m_columnNames.size(); i++){
            
            isHere = false;
            for(size_t cnt = 0; cnt < relations[0]->m_rows[0].m_values.size(); cnt++){
                if(m_columnNames[i] == relations[0]->m_rows[0].m_values[cnt]){
                    isHere = true;

                    //copy name of the atribute into final relation
                    rowName.m_values.push_back(relations[0]->m_rows[0].m_values[cnt]);
                   

                    //save index for copyed atributes 
                    indexes.push_back(cnt);
                    break;
                }
                if(cnt == relations[0]->m_rows[0].m_values.size() - 1 && isHere == false){
                    string sError = "Error. Name of the column, that you want to project: "  + m_columnNames[i] + " has not been found in the relation";
                    throw sError;
                }
            }
        }
         res.m_rows.push_back(rowName);

    
        CRow row1;
        //create a single row from projection
        for(size_t idx = 0; idx < indexes.size(); idx++){
            row1.m_values.push_back(relations[0]->m_rows[1].m_values[indexes[idx]]);
        }
        
        res.m_rows.push_back(row1);


        for(size_t cntRow = 2; cntRow < relations[0]->m_rows.size(); cntRow++){
            CRow row;
            for(size_t idx = 0; idx < indexes.size(); idx++){
                row.m_values.push_back(relations[0]->m_rows[cntRow].m_values[indexes[idx]]);
            }
            isHere = false;
            //cheking for duplicates rows
            for(size_t i = 1; i < res.m_rows.size(); i++){
                for(size_t j = 0; j < res.m_rows[0].m_values.size(); j++){
                    if(res.m_rows[i].m_values[0] == row.m_values[0]){
                        if(res.m_rows[0].m_values.size()-1 == 0){
                            isHere = true;
                        }else{
                            while((j+1) < res.m_rows[0].m_values.size()){
                                if(res.m_rows[i].m_values[j+1] == row.m_values[j+1]){
                                    break;
                                }
                                j++;
                            }
                            if(res.m_rows[i].m_values[j] != row.m_values[j]){
                                
                                break;
                            }
                            if(j == res.m_rows[0].m_values.size()-1){
                                isHere = true;
                            }
                        }
                    }else{
                        break;
                    }
                }
                if(isHere == true){
                    break;
                }
                //save row into final relation if final relation does not already contain  the same row
                if(isHere == false && i == res.m_rows.size()-1){
                    res.m_rows.push_back(row);
                    break;
                }   
            }

        }
        
        return make_shared<CRelation>(res);
    }
}

        /*bool isHere = false;
        for(size_t i = 0; i < m_columnNames.size(); i++){
            CRow rowName;
            isHere = false;
            for(size_t cnt = 0; cnt < relations[0]->m_rows[0].m_values.size(); cnt++){
                if(m_columnNames[i] == relations[0]->m_rows[0].m_values[cnt]){
                    if(i != 0){
                        res.m_rows[0].m_values.push_back(relations[0]->m_rows[0].m_values[cnt]);
                    }else{
                        rowName.m_values.push_back(relations[0]->m_rows[0].m_values[cnt]);
                        res.m_rows.push_back(rowName);
                    }
                    for(size_t row_cnt = 1; row_cnt < relations[0]->m_rows.size(); row_cnt++){
                        string word = relations[0]->m_rows[row_cnt].m_values[cnt];
                        if(i != 0){
                            res.m_rows[row_cnt].m_values.push_back(word);

                        }else{
                        CRow col;
                        col.m_values.push_back(relations[0]->m_rows[row_cnt].m_values[cnt]);
                        res.m_rows.push_back(col);
                        }
                        isHere = true;

                    }
                    break;
                }
                if(cnt == relations[0]->m_rows[0].m_values.size() - 1 && isHere == false){
                    cout << "Name of the column, that you want to project: " <<  "\"" << m_columnNames[i] << "\" has not been found in the relation" << endl;
                }
            }
        }*/
        
  
#include <iostream>
#include <fstream>
#include <sstream>
#include "FileService.h"

using namespace std;

bool CFileService::exportToFile(shared_ptr<CRelation> data) {
    ofstream fout(data->getPath());
    if(!fout.is_open()){
        cout << "Could not open file" << endl;
        return false;
    }
    for(size_t i = 0; i < data->m_rows.size(); i++)
        for(size_t j = 0; j < data->m_rows.begin()->m_values.size(); j++){
            if(j != 0){
                fout << ",";
            }
            fout << data->m_rows[i].m_values[j];
            if(j == data->m_rows.begin()->m_values.size() - 1){
                fout << "\n";
            }
        }

    fout.close();
    return true;

}

CRow CFileService::importAtriburesFromFile(const shared_ptr<CRelation> & data){
    ifstream fin(data->getPath());
    string line, word;
    CRow row;

    if(!fin.is_open()){
        string sError = "Error. Cannot open file: " + data->getPath();
        throw  sError;
    }
    
    getline(fin, line);
    if(line.size() == 0){
        string sError = "Error. Empty file.";
        throw sError;
    }
    stringstream ss(line);
    while (getline(ss, word, ',')){
        row.m_values.push_back(word);
    }

    fin.close();
    return row;
}

bool CFileService::importFromFile(const shared_ptr<CRelation> & data){
    ifstream fin(data->getPath());
    string line, word;

    if(!fin.is_open()){
        string sError = "Error. Cannot open file: " + data->getPath();
        throw  sError;
    }
    size_t i = 0;
    while(getline(fin, line)){
        
        if(line.size() == 0 && i == 0){
            string sError = "Error. Empty file.";
            throw sError;
        }
        stringstream ss(line);
        CRow row;
        while (getline(ss, word, ',')){
            row.m_values.push_back(word);

        }
        data->m_rows.push_back(row);
        i++;
    }

    fin.close();
    return true;
}
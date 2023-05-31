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
                cout << ",";
            }
            fout << data->m_rows[i].m_values[j];
            cout << data->m_rows[i].m_values[j];
            if(j == data->m_rows.begin()->m_values.size() - 1){
                fout << "\n";
                cout << "\n";
            }
        }

    fout.close();
    return true;

}

bool CFileService::importFromFile(const shared_ptr<CRelation> data){
    ifstream fin(data->getPath());
    string line, word;

    if(!fin.is_open()){
        cout << "Could not open file" << endl;
        return false;
    }
    
    while(getline(fin, line)){
        size_t i = 0;
        stringstream ss(line);
        CRow row;
        while (getline(ss, word, ',')){
            row.m_values.push_back(word);

        }
        data->m_rows.push_back(row);
    }

    for (const auto & element : data->m_rows){
        
        for (const auto & element2 : element.m_values){
            cout << element2 << endl;
        }
    }

    fin.close();
    return true;
}
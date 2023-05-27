#include <iostream>
#include <fstream>
#include <sstream>
#include "FileService.h"

using namespace std;

bool CFileService::exportToFile(const shared_ptr<CRelation> data) {
    ofstream fout(data->getPath());
    if(!fout.is_open()){
        cout << "Could not open file" << endl;
        return false;
    }
    for(auto itName = data->m_columns.begin(); itName != data->m_columns.end(); itName++){
        if(itName != data->m_columns.begin()){
                fout << ",";
                cout << ",";
            }
            fout << itName->m_name;
            cout << itName->m_name;
    }
    fout << "\n";
    cout << "\n";
    for(size_t i = 0; i < data->m_columns.begin()->m_values.size(); i++)
        for(size_t j = 0; j < data->m_columns.size(); j++){
            if(j != 0){
                fout << ",";
                cout << ",";
            }
            fout << data->m_columns[j].m_values[i];
            cout << data->m_columns[j].m_values[i];
            if(j == data->m_columns.size() - 1){
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
    getline(fin, line);
    stringstream ss(line);
    //size_t i = 0; //column index
    while (getline(ss, word, ',')){

        //load name of each column
        CColumn name(word);
        data->m_columns.push_back(name);
        //data->m_columns[i].m_name = word;
        //i++;
    }
    
    while(getline(fin, line)){
        size_t i = 0;
        stringstream ss(line);
        while (getline(ss, word, ',')){
            data->m_columns[i].m_values.push_back(word);
            i++;
        }
    }

    for (const auto & element : data->m_columns){
        cout << element.m_name << endl;
        for (const auto & element2 : element.m_values){
            cout << element2 << endl;
        }
    }

    fin.close();
    return true;
}
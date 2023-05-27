#include "Projection.h"
#include <iostream>
#include  <sstream>

using namespace std;

void CProjection::parse(const string & columnNames){
    stringstream ss(columnNames);
    string word;
    while (getline(ss, word, ',')){
        m_columnNames.push_back(word);
    }
}

shared_ptr<CRelation> CProjection::evaluate(vector<shared_ptr<CRelation>> & relations){
    CRelation res;
    bool isHere = false;
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
    }
    return make_shared<CRelation>(res);
}
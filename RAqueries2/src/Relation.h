#pragma once

#include <vector>
#include <memory>

#include "Row.h"

using namespace std;

class CRelation{
    public:
        CRelation() = default;
        CRelation (const string & path) // Constructor
		:m_path(path), m_rows(){};
        
        
        string getPath(){return m_path;};
        void setPath(const string & path){m_path = path;};

        vector<CRow> m_rows;
    private:
        string m_path;
        

};


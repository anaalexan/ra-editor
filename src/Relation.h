#pragma once

#include <vector>
#include <memory>

#include "Column.h"

using namespace std;

class CRelation{
    public:
        CRelation() = default;
        CRelation (const string & path) // Constructor
		:m_path(path), m_columns(){};
        
        
        string getPath(){return m_path;};
        void setPath(const string & path){m_path = path;};

        vector<CColumn> m_columns;
    private:
        string m_path;
        

};


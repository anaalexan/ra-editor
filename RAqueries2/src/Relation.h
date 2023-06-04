#pragma once

#include <vector>
#include <memory>

#include "Row.h"

using namespace std;
/** Class for relation management  */
class CRelation{
    public:
        CRelation() = default;
        CRelation (const string & path) // Constructor
		:m_path(path), m_rows(){};
        
        /**
	    * Method get path from where the data imported */
        string getPath(){return m_path;};
        /**
	    * Method set new path to the file to export the data
        * @param[in] path new path to export data
        * */
        void setPath(const string & path){m_path = path;};

        /** @var vector of  each individualy row {@link #CRow} */
        vector<CRow> m_rows;
    private:
        /** @var path from where data was imported or will be exported*/
        string m_path;
        

};


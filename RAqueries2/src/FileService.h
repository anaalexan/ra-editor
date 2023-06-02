#pragma once

#include "Relation.h"

using namespace std;

class CFileService{
    public:
        CFileService() = default;
        bool exportToFile(shared_ptr<CRelation> data); 

        bool importFromFile(const shared_ptr<CRelation> data);

        CRow importAtriburesFromFile(const shared_ptr<CRelation> data);

};
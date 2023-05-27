#pragma once

#include "Relation.h"

using namespace std;

class CFileService{
    public:
        CFileService() = default;
        bool exportToFile(shared_ptr<CRelation> data);  //to csv

        // open file based on path in data

        // write from data to cells in file

        bool importFromFile(const shared_ptr<CRelation> data);   //only path

        // open file based on path in data

        // load cells from file to data object

};
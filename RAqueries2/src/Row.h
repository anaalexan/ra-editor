

#include <vector>
#include <string>


#pragma once
using namespace std;

/** Class for the row in the relation  */
class CRow{
    public:
    CRow()=default;
    /** @var vector of a single cells in the relation */
    vector<string> m_values;
};


#include <vector>
#include <string>


#pragma once
using namespace std;

class CColumn{
    public:
    CColumn(string name):m_name(name), m_values(){}
    string m_name;
    vector<string> m_values;
};
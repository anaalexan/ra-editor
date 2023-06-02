#include <string>
#include <variant>

#pragma once

using namespace std;

class CStringConvert{
    public:
        typedef variant<float, int, double, string> m_variant;

        bool isFloat(string str, float & floatCheck);
        bool isInt(string str, int & intCheck);
        bool isDouble(string str, double & doubleCheck);

        m_variant whatType(string str);

        //void remove_invisible (string & str);

        

};
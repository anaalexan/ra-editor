#include <string>
#include <variant>
#include <algorithm>
#include "StringConvert.h"


using namespace std;


bool CStringConvert::isFloat(string str, float & floatCheck) {
    try {
        floatCheck = stof(str);
        return true;
    }
    catch (...) {
        return false;
    }
}

bool CStringConvert::isInt(string str, int & intCheck) {
    try {
        intCheck = stoi(str);
        return true;
    }
    catch (...) {
        return false;
    }
}
bool CStringConvert::isDouble(string str,double & doubleCheck) {
    try {
        doubleCheck = stod(str);
        return true;
    }
    catch (...) {
        return false;
    }
}


CStringConvert::m_variant CStringConvert::whatType(string str){
    float fl;
    int it;
    double dbl;
    if(isFloat(str, fl)){
        return fl;
    }
    else if(isInt(str, it)){
        return it;
    
    }else if(isDouble(str, dbl)){
        return dbl;
        
    }else{
        return str;         
    }                                                                   
}
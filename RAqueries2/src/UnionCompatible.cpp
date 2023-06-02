#include "UnionCompatible.h"

using namespace std;

bool CUnionCompatible::isUnionCompatible(const CRow & left, const CRow & right) const{
    if(left.m_values.size() != right.m_values.size()){
        return false;
    }
    size_t r = 0;
    for(size_t l = 0; l < left.m_values.size(); l++){
        if(left.m_values[l] != right.m_values[r]){
            return false;
        }
        r++;
    }
    return true;
}


#include "UnionCompatible.h"

using namespace std;

bool CUnionCompatible::isUnionCompatible(const shared_ptr<CRelation> left, const shared_ptr<CRelation> right) const{
    if(left->m_rows[0].m_values.size() != right->m_rows[0].m_values.size()){
        return false;
    }
    size_t r = 0;
    for(size_t l = 0; l < left->m_rows[0].m_values.size(); l++){
        if(left->m_rows[0].m_values[l] != right->m_rows[0].m_values[r]){
            return false;
        }
        r++;
    }
    return true;
}


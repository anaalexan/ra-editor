#pragma once

#include "Relation.h"

using namespace std;

class CUnionCompatible{
    public:
        bool isUnionCompatible(const CRow & left, const CRow & right) const;
		//both relations have same number of columns, otherwise invalid expression
};
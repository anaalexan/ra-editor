#pragma once

#include "Relation.h"

using namespace std;

class CUnionCompatible{
    public:
        bool isUnionCompatible(const shared_ptr<CRelation> left, const shared_ptr<CRelation> right) const;
		//both relations have same number of columns, otherwise invalid expression
};
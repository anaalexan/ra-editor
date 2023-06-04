#pragma once

#include "Relation.h"

using namespace std;

/** Class for checking if the relations are union compatible or no  */
class CUnionCompatible{
    public:

    /**
	 * Method checks if both relations have same number of columns, otherwise invalid expression
	 * @param[in] left first row {@link #CRow} with the atributes of the first relation
     * @param[in] right first row {@link #CRow} with the atributes of the second relation
     * @returns true if relations are union compatible or false if not
	 */
        bool isUnionCompatible(const CRow & left, const CRow & right) const;
		
};
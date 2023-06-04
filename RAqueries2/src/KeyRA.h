#pragma once

using namespace std;
/** enum Class contains keywords relational algebra(RA) operators  */
enum class EKeyRA {
	CrossJoin = 'x',
	Difference = '-',
	Intersection = '&',
	NaturalJoin = '*',
	Projection = '[',
    Rename = '<',
    Selection = '(',
    ThetaJoin = '^',
    Union = '+',
    Space = ' ',
    Quots = '\"',
    NoMatch
	
};
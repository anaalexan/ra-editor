#pragma once

using namespace std;

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
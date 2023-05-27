#pragma once

using namespace std;

/* TODO convert to class with ENUM and MAP to store keyword in implementation readable and supported form (ie. not in clash with keywords of C++) 
with information about string to parse, for example INTERSECTION = "&" */
enum class EKeywords {
	IMPORT,
	PRINT,
	EXPORT,
	RENAME,
	UNION,
	INTERSECTION,
	CROSS,
	NATURAL_JOIN,
	THETA_JOIN,
	DIFFEREMCE,
	EXIT
};
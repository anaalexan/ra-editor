#pragma once

using namespace std;

/* TODO convert to class with ENUM and MAP to store keyword in implementation readable and supported form (ie. not in clash with keywords of C++) 
with information about string to parse, for example INTERSECTION = "&" */
enum class EKeywords {
	eEXIT,
	eIMPORT,
	ePRINT,
	eEXPORT,
	eTRANSLATE
	
};
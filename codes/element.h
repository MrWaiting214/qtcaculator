#ifndef _ELEMENT_H
#define _ELEMENT_H
#include <string>
using namespace std;
struct element
{
	string val;
	element *next;
	element():val("0"),next(NULL){}
	element(string x):val(x),next(NULL){}
	element(string x,element * next):val(x),next(next){}
}; 


#endif

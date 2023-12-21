#ifndef _ELEMENT_H
#define _ELEMENT_H
#include <string>
using namespace std;
template<class T> 
struct element
{
	T val;
	element<T> *next;
	element(T x):val(x),next(NULL){}
}; 


#endif

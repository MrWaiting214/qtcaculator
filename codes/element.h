#ifndef _ELEMENT_H
#define _ELEMENT_H
#include <string>
using namespace std;
template<class T> 
struct element//结构体模板实现的栈元素 
{
	T val;
	element<T> *next;
	element(T x):val(x),next(NULL){}
}; 


#endif

#ifndef _STACK_H
#define _STACK_H
#include "element.h"

class stack//Á´Õ»µÄ¶¨Òå 
{
	private:
		element *head;
	public:
		stack(); 
		void push(string x);
		string top();
		string pop();
		bool empty();
};

#endif

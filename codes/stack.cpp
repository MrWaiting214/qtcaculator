#include <iostream>
#include "stack.h"


stack::stack()
{
	head=new element;
}

bool stack::empty()
{
	if(head->next==NULL)return true;
	return false;
}

string stack::top()
{
	if(empty())throw"ÏÂÒç";
	return head->next->val;
}

string stack::pop()
{
	if(empty())throw"ÏÂÒç";
	string temp=head->next->val;
	head->next=head->next->next;
	return temp;
}
void stack::push(string x)
{
	element *ele = new element(x);
	ele->next=head->next;
	head->next=ele;
}

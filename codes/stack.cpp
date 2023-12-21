/*#include <iostream>
#include <string>
#include "element.h"
#include "stack.h"


template<class T>
void stack<T>::push(T x)
{
	element<T> *ele = new element<T>(x);
	ele->next=head;
	head=ele;
}
template<class T>
T stack<T>::top()
{
	if(empty())throw"ÏÂÒç";
	return head->val;
}
template<class T>
T stack<T>::pop()
{
	if(empty())throw"ÏÂÒç";
	T tempval=head->val;
	element<T> *temp=head;
	head=head->next;
	delete temp;
	return tempval;
}
template<class T>
bool stack<T>::empty()
{
	if(head==NULL)return true;
	return false;
}*/

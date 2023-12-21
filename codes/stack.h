#ifndef _STACK_H
#define _STACK_H
#include "element.h"
template<class T>
class stack//链栈的定义 
{
	private:
		element<T> *head;
	public:
		stack():head(NULL){};
		void push(T x);
		T top();
		T pop();
		bool empty();
};
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
	if(empty())throw"下溢";
	return head->val;
}
template<class T>
T stack<T>::pop()
{
	if(empty())throw"下溢";
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
}

#endif

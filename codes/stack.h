#ifndef _STACK_H
#define _STACK_H
#include "element.h"
template<class T>
class stack//模板类链栈
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
void stack<T>::push(T x)//入栈函数 
{
	element<T> *ele = new element<T>(x);
	ele->next=head;
	head=ele;
}
template<class T>
T stack<T>::top()//返回栈顶函数 
{
	if(empty())throw"下溢";
	return head->val;
}
template<class T>
T stack<T>::pop()//出栈函数 
{
	if(empty())throw"下溢";
	T tempval=head->val;
	element<T> *temp=head;
	head=head->next;
	delete temp;
	return tempval;
}
template<class T>
bool stack<T>::empty()//判空函数 
{
	if(head==NULL)return true;
	return false;
}

#endif

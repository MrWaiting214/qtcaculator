#ifndef _STACK_H
#define _STACK_H
#include "element.h"
template<class T>
class stack//ģ������ջ
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
void stack<T>::push(T x)//��ջ���� 
{
	element<T> *ele = new element<T>(x);
	ele->next=head;
	head=ele;
}
template<class T>
T stack<T>::top()//����ջ������ 
{
	if(empty())throw"����";
	return head->val;
}
template<class T>
T stack<T>::pop()//��ջ���� 
{
	if(empty())throw"����";
	T tempval=head->val;
	element<T> *temp=head;
	head=head->next;
	delete temp;
	return tempval;
}
template<class T>
bool stack<T>::empty()//�пպ��� 
{
	if(head==NULL)return true;
	return false;
}

#endif

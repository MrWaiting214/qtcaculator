#include <iostream>
#include "caculator.h"
#include "stack.h"

int caculator::getPriority(string operatr)
{
	if(operatr=="(")
	{
		return 0;
	}
	else if(operatr=="=")
	{
		return 1;
	}
	else if(operatr==")")
	{
		return 2;
	}
	else if(operatr=="+" || operatr=="-")
	{
		return 3;
	}
	else if(operatr=="*" || operatr=="/" || operatr=="%")
	{
		return 4;
	}
	else if(operatr=="^")
	{
		return 5;
	}
	return 0;
}

int caculator::getPriority(char operatr)
{
	if(operatr=='(')
	{
		return 0;
	}
	else if(operatr=='=')
	{
		return 1;
	}
	else if(operatr==')')
	{
		return 2;
	}
	else if(operatr=='+' || operatr=='-')
	{
		return 3;
	}
	else if(operatr=='*' || operatr=='/' || operatr=='%')
	{
		return 4;
	}
	else if(operatr=='^')
	{
		return 5;
	}
	return 0;
}
string caculator::toSuffix(string infix)
{
	stack st;
	string suffix="";
	for(int i=0;i<infix.length();i++)
	{
		if('0'<=infix[i] && infix[i]<= '9')
		{
			suffix+=infix[i];
		}
		else if(infix[i]=='(')
		{
			string temp="";
			temp+=infix[i];
			st.push(temp);
			cout<<"������ջ���ǣ�"<<infix[i]<<endl; 
		}
		else if(infix[i]==')')
		{
			while(!st.empty()) 
			{
				if(st.top()=="(")
				{
					cout<<"���ڳ�ջ���ǣ�"<<st.pop()<<endl;
					break;
				}
				string ccc=st.pop();
				suffix+=ccc;
				cout<<"���ڳ�ջ���ǣ�"<<ccc<<endl;
			}
		}
		else if(infix[i]=='+' || infix[i]=='-' || infix[i]=='=' || infix[i]=='/' || infix[i]=='*' || infix[i]=='%' || infix[i]=='^')
		{
			if(st.empty())
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
				cout<<"������ջ���ǣ�"<<infix[i]<<endl; 
			}
			else if(!st.empty() && (getPriority(st.top()) < getPriority(infix[i])))
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
				cout<<"������ջ���ǣ�"<<infix[i]<<endl; 
			}
			else if(!st.empty() && (getPriority(st.top()) >= getPriority(infix[i])))
			{
				while(!st.empty() && (getPriority(st.top()) >= getPriority(infix[i])))
				{
					string ccc=st.pop();
					suffix+=ccc;
					cout<<"���ڳ�ջ���ǣ�"<<ccc<<endl;
				}
				string temp="";
				temp+=infix[i];
				st.push(temp);
				cout<<"������ջ���ǣ�"<<infix[i]<<endl; 
			}
		}
	}
	while(!st.empty())
	{
		string ccc=st.pop();
		suffix+=ccc;
		cout<<"���ڳ�ջ���ǣ�"<<ccc<<endl;
	}
	return suffix;
}



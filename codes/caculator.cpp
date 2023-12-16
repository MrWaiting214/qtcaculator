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
			int temp=0;
			while(infix[i+temp]!='\0' && (('0'<=infix[i+temp] && infix[i+temp]<= '9') || (infix[i+temp+1]!='\0' && '0'<=infix[i+temp+1] && infix[i+temp+1]<= '9' && infix[i+temp]=='.')))
			{
				suffix+=infix[i+temp];
				temp++;
			}
			suffix+=" ";
			i+=temp-1;
		}
		else if(infix[i-1]=='(' && infix[i]=='-')
		{
			suffix+=infix[i];
			int temp=1;
			while(infix[i+temp]!='\0' && (('0'<=infix[i+temp] && infix[i+temp]<= '9') || (infix[i+temp+1]!='\0' && '0'<=infix[i+temp+1] && infix[i+temp+1]<= '9' && infix[i+temp]=='.')))
			{
				suffix+=infix[i+temp];
				temp++;
			}
			suffix+=" ";
			i+=temp-1;
		}
		else if(infix[i]=='(')
		{
			string temp="";
			temp+=infix[i];
			st.push(temp);
		}
		else if(infix[i]==')')
		{
			while(!st.empty()) 
			{
				if(st.top()=="(")
				{
					st.pop();
					break;
				}
				suffix+=st.pop();
				suffix+=" ";
			}
		}
		else if(infix[i]=='+' || (infix[i]=='-' && infix[i-1]!='(') || infix[i]=='=' || infix[i]=='/' || infix[i]=='*' || infix[i]=='%' || infix[i]=='^')
		{
			if(st.empty())
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
			}
			else if(!st.empty() && (getPriority(st.top()) < getPriority(infix[i])))
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
			}
			else if(!st.empty() && (getPriority(st.top()) >= getPriority(infix[i])))
			{
				while(!st.empty() && (getPriority(st.top()) >= getPriority(infix[i])))
				{
					suffix+=st.pop();
					suffix+=" ";
				}
				string temp="";
				temp+=infix[i];
				st.push(temp);
			}
		}
	}
	while(!st.empty())
	{
		suffix+=st.pop();
		suffix+=" ";
	}
	return suffix;
}



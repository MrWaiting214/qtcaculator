#include <iostream>
#include "caculator.h"
#include "stack.h" 
#include <math.h>
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
	if(infix=="")
	{
		return "";	
	}
	for(int i=0;i<infix.length()-1;i++)
	{
		if(!('0'<=infix[i] && infix[i]<= '9') && !('0'<=infix[i+1] && infix[i+1]<= '9') && !(infix[i+1]=='(' || infix[i+1]==')' || infix[i]=='(' || infix[i]==')'))
		{
			cout<<"表达式出错"<<endl;
			return "";
		}
	}
	stack<string> st;
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
		else if((i!=0 && infix[i-1]=='(' && infix[i]=='-') || (i==0 && infix[i]=='-'))
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
		else if((i!=0 && infix[i-1]=='(' && infix[i]=='+') || (i==0 && infix[i]=='+'))
		{
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
		else if((infix[i]=='+' && infix[i-1]!='(' && i!=0) || (infix[i]=='-' && infix[i-1]!='(' && i!=0) || infix[i]=='=' || infix[i]=='/' || infix[i]=='*' || infix[i]=='%' || infix[i]=='^')
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
		else
		{
			cout<<"表达式出错"<<endl;
			return "";
		}
	}
	while(!st.empty())
	{
		if(st.top()=="(")
		{
			cout<<"表达式出错"<<endl;
			return "";
		}
		suffix+=st.pop();
		suffix+=" ";
	}
	return suffix;
}
double caculator::strToDouble(string str)
{
	int i=0,j=-1;
	double val=0.0;
	double factor=1.0;
	if(str[0]=='-') factor=-1.0;
	if(factor==-1.0) i=1;
	while(str[i]!='.' && str[i]!='\0')
	{
		val=val*10+(str[i]-'0');
		i++;
	}
	if(str[i]=='.')
	{
		i++;
		while(str[i]!='\0')
		{
			val+=(str[i]-'0')*pow(10,j);
			j--;
			i++;
		}
	}
	return factor*val;
}
double caculator::suffixCacu(string suffix)
{
	
	stack<double>st;
	string str="";
	double temp1,temp2;
	int i=0,j=0;
	while(suffix[i]!='\0')
	{
		if(('0'<=suffix[i] && '9'>=suffix[i]) || (suffix[i]=='-' && suffix[i+1]!='\0' && suffix[i+1]!=' ') || suffix[i]=='.')
		{
			str+=suffix[i];
			if(suffix[i+1]=='\0' || suffix[i+1]==' ')
			{
				st.push(strToDouble(str));
				str="";
			}
		}
		else if(suffix[i]!=' ')
		{
			if(!st.empty())
			{
				temp2=st.pop();
			}
			if(!st.empty())
			{
				temp1=st.pop();
			}
			if(suffix[i]=='+')st.push(temp1+temp2);
			else if(suffix[i]=='-')st.push(temp1-temp2);
			else if(suffix[i]=='*')st.push(temp1*temp2);
			else if(suffix[i]=='/')st.push(temp1/temp2);
			else if(suffix[i]=='^')st.push(pow(temp1,temp2));
			else if(suffix[i]=='%')
			{
				if(temp1-(int)temp1!=0 || temp2-(int)temp2!=0)
				{
					cout<<"对非整数使用求余符号，计算出的结果是错误的！"<<endl; 
				}
				st.push(((int)temp1+(int)temp2)%(int)temp2);
			}
		}
		i++;
	}

	return st.top(); 
}
void caculator::caculate()
{
	string infix;
	string suffix;
	while(true)
	{
		cout<<"请输入你想计算的算式(输入'q'则退出)：";
		getline(cin,infix);
		if(infix=="q")
		{
			cout<<"欢迎下次使用！"<<endl;
			exit(0);
		}
		suffix=toSuffix(infix);
		if(suffix=="")
		{
			caculate();
		}
		cout<<"结果是："<<suffixCacu(suffix)<<endl;
	}
}

#include <iostream>
#include "caculator.h"
#include "stack.h" 
#include <math.h>
int caculator::getPriority(string operatr)//返回优先级 
{
	if(operatr=="(")//在这个程序中，左括号在栈里被视为优先级最低 
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

int caculator::getPriority(char operatr) //返回优先级函数的重载 
{
	if(operatr=='(')//在这个程序中，左括号在栈里被视为优先级最低 
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
string caculator::toSuffix(string infix)//转化前缀计算式为后缀计算式
{
	if(infix=="")//无效输入返回 
	{
		return "";	
	}
	for(int i=0;i<infix.length()-1;i++)//检验是否有运算符连续出现 
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
		if('0'<=infix[i] && infix[i]<= '9')//对数字字符的操作 
		{
			int temp=0;
			while(infix[i+temp]!='\0' && (('0'<=infix[i+temp] && infix[i+temp]<= '9') || (infix[i+temp+1]!='\0' && '0'<=infix[i+temp+1] && infix[i+temp+1]<= '9' && infix[i+temp]=='.')))//循环完成对数字字符串的截取，并将i跳至该字符串后 
			{
				suffix+=infix[i+temp];
				temp++;
			}
			suffix+=" ";
			i+=temp-1;
		}
		else if((i!=0 && infix[i-1]=='(' && infix[i]=='-') || (i==0 && infix[i]=='-'))//单独处理'-'作为负号的情况，大部分操作与对数字字符操作相同 
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
		else if((i!=0 && infix[i-1]=='(' && infix[i]=='+') || (i==0 && infix[i]=='+'))//单独处理'+'作为正号的情况，大部分操作与对数字字符操作相同 
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
		else if(infix[i]=='(')//左括号入栈 
		{
			string temp="";
			temp+=infix[i];
			st.push(temp);
		}
		else if(infix[i]==')')//出现右括号时，持续出栈直到栈顶为左括号或栈空，若遇到左括号左括号也需出栈，出栈过程中其他字符加入后缀计算式字符串 
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
		else if(infix[i]=='+' || infix[i]=='-' || infix[i]=='=' || infix[i]=='/' || infix[i]=='*' || infix[i]=='%' || infix[i]=='^')//处理各个运算符 
		{
			if(st.empty())//栈为空直接入栈 
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
			}
			else if(getPriority(st.top()) < getPriority(infix[i]))//若该字符比栈顶字符运算优先级低，直接入栈 
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
			}
			else if(getPriority(st.top()) >= getPriority(infix[i]))///若该字符比栈顶字符运算优先级高，持续出栈，并将出栈字符加入后缀计算式字符串，最后再把该字符入栈 
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
		else//出现非法字符 
		{
			cout<<"表达式出错"<<endl;
			return "";
		}
	}
	while(!st.empty())
	{
		if(st.top()=="(")//若栈中仍有括号，说明有多余括号，表达式有问题 
		{
			cout<<"表达式出错"<<endl;
			return "";
		}
		suffix+=st.pop();
		suffix+=" ";
	}
	return suffix;
}
double caculator::strToDouble(string str)//数字字符串转化为double
{
	int i=0,j=-1;
	double val=0.0;
	double factor=1.0;//因数 
	if(str[0]=='-') factor=-1.0;
	if(factor==-1.0) i=1;
	while(str[i]!='.' && str[i]!='\0')//首先计算非小数部分 
	{
		val=val*10+(str[i]-'0');
		i++;
	}
	if(str[i]=='.')//假设存在小数部分 
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
double caculator::suffixCacu(string suffix)//计算后缀计算式
{
	
	stack<double>st;
	string str="";
	double temp1,temp2;
	int i=0,j=0;
	while(suffix[i]!='\0')
	{
		if(('0'<=suffix[i] && '9'>=suffix[i]) || (suffix[i]=='-' && suffix[i+1]!='\0' && suffix[i+1]!=' ') || suffix[i]=='.')//截取字符串中的数字字符组成的子串 
		{
			str+=suffix[i];
			if(suffix[i+1]=='\0' || suffix[i+1]==' ')
			{
				st.push(strToDouble(str));//直接转化为double入栈 
				str="";
			}
		}
		else if(suffix[i]!=' ')//处理运算符，栈顶两个元素出栈，令第2个出栈的元素对第1个出栈的元素使用当前运算符，并将结果入栈 
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
			else if(suffix[i]=='/')
			{
				if(temp2==0)
				{
					cout<<"0不能做除数！"<<endl;
					return 3.1415926535;//返回特定值作为错误标志 
				}
				st.push(temp1/temp2);
			}
			else if(suffix[i]=='^')
			{
				st.push(pow(temp1,temp2));
			}
			else if(suffix[i]=='%')
			{
				if(temp2==0)
				{
					cout<<"不能对0求余！"<<endl;
					return 3.1415926535;//返回特定值作为错误标志 
				}
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
void caculator::caculate()//调用计算 
{
	string infix;
	string suffix;
	double ans; 
	while(true)
	{
		cout<<"请输入你想计算的算式(输入'q'则退出)：";
		getline(cin,infix);
		if(infix=="q")
		{
			cout<<"欢迎下次使用！"<<endl;
			system("pause");
			exit(0);
		}
		suffix=toSuffix(infix);
		if(suffix=="")//接收错误，重新输入 
		{
			caculate();
		}
		ans=suffixCacu(suffix);
		if(ans==3.1415926535)//接收错误，重新输入 
		{
			caculate();	
		}
		cout<<ans<<endl;
	}
}

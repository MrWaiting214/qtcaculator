#include <iostream>
#include "caculator.h"
#include "stack.h" 
#include <math.h>
int caculator::getPriority(string operatr)//�������ȼ� 
{
	if(operatr=="(")//����������У���������ջ�ﱻ��Ϊ���ȼ���� 
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

int caculator::getPriority(char operatr) //�������ȼ����������� 
{
	if(operatr=='(')//����������У���������ջ�ﱻ��Ϊ���ȼ���� 
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
string caculator::toSuffix(string infix)//ת��ǰ׺����ʽΪ��׺����ʽ
{
	if(infix=="")//��Ч���뷵�� 
	{
		return "";	
	}
	for(int i=0;i<infix.length()-1;i++)//�����Ƿ���������������� 
	{
		if(!('0'<=infix[i] && infix[i]<= '9') && !('0'<=infix[i+1] && infix[i+1]<= '9') && !(infix[i+1]=='(' || infix[i+1]==')' || infix[i]=='(' || infix[i]==')'))
		{
			cout<<"���ʽ����"<<endl;
			return "";
		}
	}
	stack<string> st; 
	string suffix="";
	for(int i=0;i<infix.length();i++)
	{
		if('0'<=infix[i] && infix[i]<= '9')//�������ַ��Ĳ��� 
		{
			int temp=0;
			while(infix[i+temp]!='\0' && (('0'<=infix[i+temp] && infix[i+temp]<= '9') || (infix[i+temp+1]!='\0' && '0'<=infix[i+temp+1] && infix[i+temp+1]<= '9' && infix[i+temp]=='.')))//ѭ����ɶ������ַ����Ľ�ȡ������i�������ַ����� 
			{
				suffix+=infix[i+temp];
				temp++;
			}
			suffix+=" ";
			i+=temp-1;
		}
		else if((i!=0 && infix[i-1]=='(' && infix[i]=='-') || (i==0 && infix[i]=='-'))//��������'-'��Ϊ���ŵ�������󲿷ֲ�����������ַ�������ͬ 
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
		else if((i!=0 && infix[i-1]=='(' && infix[i]=='+') || (i==0 && infix[i]=='+'))//��������'+'��Ϊ���ŵ�������󲿷ֲ�����������ַ�������ͬ 
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
		else if(infix[i]=='(')//��������ջ 
		{
			string temp="";
			temp+=infix[i];
			st.push(temp);
		}
		else if(infix[i]==')')//����������ʱ��������ջֱ��ջ��Ϊ�����Ż�ջ�գ�������������������Ҳ���ջ����ջ�����������ַ������׺����ʽ�ַ��� 
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
		else if(infix[i]=='+' || infix[i]=='-' || infix[i]=='=' || infix[i]=='/' || infix[i]=='*' || infix[i]=='%' || infix[i]=='^')//������������ 
		{
			if(st.empty())//ջΪ��ֱ����ջ 
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
			}
			else if(getPriority(st.top()) < getPriority(infix[i]))//�����ַ���ջ���ַ��������ȼ��ͣ�ֱ����ջ 
			{
				string temp="";
				temp+=infix[i];
				st.push(temp);
			}
			else if(getPriority(st.top()) >= getPriority(infix[i]))///�����ַ���ջ���ַ��������ȼ��ߣ�������ջ��������ջ�ַ������׺����ʽ�ַ���������ٰѸ��ַ���ջ 
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
		else//���ַǷ��ַ� 
		{
			cout<<"���ʽ����"<<endl;
			return "";
		}
	}
	while(!st.empty())
	{
		if(st.top()=="(")//��ջ���������ţ�˵���ж������ţ����ʽ������ 
		{
			cout<<"���ʽ����"<<endl;
			return "";
		}
		suffix+=st.pop();
		suffix+=" ";
	}
	return suffix;
}
double caculator::strToDouble(string str)//�����ַ���ת��Ϊdouble
{
	int i=0,j=-1;
	double val=0.0;
	double factor=1.0;//���� 
	if(str[0]=='-') factor=-1.0;
	if(factor==-1.0) i=1;
	while(str[i]!='.' && str[i]!='\0')//���ȼ����С������ 
	{
		val=val*10+(str[i]-'0');
		i++;
	}
	if(str[i]=='.')//�������С������ 
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
double caculator::suffixCacu(string suffix)//�����׺����ʽ
{
	
	stack<double>st;
	string str="";
	double temp1,temp2;
	int i=0,j=0;
	while(suffix[i]!='\0')
	{
		if(('0'<=suffix[i] && '9'>=suffix[i]) || (suffix[i]=='-' && suffix[i+1]!='\0' && suffix[i+1]!=' ') || suffix[i]=='.')//��ȡ�ַ����е������ַ���ɵ��Ӵ� 
		{
			str+=suffix[i];
			if(suffix[i+1]=='\0' || suffix[i+1]==' ')
			{
				st.push(strToDouble(str));//ֱ��ת��Ϊdouble��ջ 
				str="";
			}
		}
		else if(suffix[i]!=' ')//�����������ջ������Ԫ�س�ջ�����2����ջ��Ԫ�ضԵ�1����ջ��Ԫ��ʹ�õ�ǰ����������������ջ 
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
					cout<<"0������������"<<endl;
					return 3.1415926535;//�����ض�ֵ��Ϊ�����־ 
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
					cout<<"���ܶ�0���࣡"<<endl;
					return 3.1415926535;//�����ض�ֵ��Ϊ�����־ 
				}
				if(temp1-(int)temp1!=0 || temp2-(int)temp2!=0)
				{
					cout<<"�Է�����ʹ��������ţ�������Ľ���Ǵ���ģ�"<<endl; 
				}
				st.push(((int)temp1+(int)temp2)%(int)temp2);
			}
		}
		i++;
	}
	return st.top(); 
}
void caculator::caculate()//���ü��� 
{
	string infix;
	string suffix;
	double ans; 
	while(true)
	{
		cout<<"����������������ʽ(����'q'���˳�)��";
		getline(cin,infix);
		if(infix=="q")
		{
			cout<<"��ӭ�´�ʹ�ã�"<<endl;
			system("pause");
			exit(0);
		}
		suffix=toSuffix(infix);
		if(suffix=="")//���մ����������� 
		{
			caculate();
		}
		ans=suffixCacu(suffix);
		if(ans==3.1415926535)//���մ����������� 
		{
			caculate();	
		}
		cout<<ans<<endl;
	}
}

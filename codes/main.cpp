#include <iostream>
#include <string>
#include "element.h"
#include "stack.h"
#include "caculator.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) 
{
	caculator cc;
	string infix;
	string suffix;
	while(true)
	{
		cout<<"请输入你想计算的算式(输入'q'则退出)：";
		getline(cin,infix);
		if(infix=="q")
		{
			cout<<"欢迎下次使用！"<<endl;
			return 0;
		}
		suffix=cc.toSuffix(infix);
		cout<<suffix<<endl;
	}
	return 0;
}

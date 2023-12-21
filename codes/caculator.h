#ifndef _CACULATOR_H
#define _CACULATOR_H
#include <string>
using namespace std;
class caculator
{
	public:
		caculator(){};//无参构造 
		string toSuffix(string infix);//转化前缀计算式为后缀计算式 
		int getPriority(string operatr);//返回优先级 
		int getPriority(char operatr);//返回优先级函数的重载 
		double strToDouble(string str);//数字字符串转化为double 
		double suffixCacu(string suffix);//计算后缀计算式 
		void caculate();//调用计算 
};


#endif

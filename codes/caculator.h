#ifndef _CACULATOR_H
#define _CACULATOR_H
#include <string>
using namespace std;
class caculator
{
	public:
		caculator(){};//�޲ι��� 
		string toSuffix(string infix);//ת��ǰ׺����ʽΪ��׺����ʽ 
		int getPriority(string operatr);//�������ȼ� 
		int getPriority(char operatr);//�������ȼ����������� 
		double strToDouble(string str);//�����ַ���ת��Ϊdouble 
		double suffixCacu(string suffix);//�����׺����ʽ 
		void caculate();//���ü��� 
};


#endif

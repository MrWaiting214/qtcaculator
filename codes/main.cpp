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
	cout<<"����������������ʽ��";
	cin>>infix;
	suffix=cc.toSuffix(infix);
	cout<<suffix;
	return 0;
}

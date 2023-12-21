#include <iostream>
#include <string>
#include "element.h"
#include "stack.h"
#include "caculator.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) 
{
	string temp;
	caculator c;
	c.caculate();//调用计算器计算 
	system("pause");
	return 0;
}

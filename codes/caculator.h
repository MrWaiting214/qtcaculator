#ifndef _CACULATOR_H
#define _CACULATOR_H
#include <string>
using namespace std;
class caculator
{
	public:
		caculator(){};
		string toSuffix(string infix);
		int getPriority(string operatr);
		int getPriority(char operatr);
};


#endif

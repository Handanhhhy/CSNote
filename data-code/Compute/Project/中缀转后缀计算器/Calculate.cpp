#include "Calculate.h"


Calculate::Calculate(std::string str) :str(str), length(str.length())
{
}

Calculate::~Calculate()
{
}

void Calculate::conversion()
{
	bool flag = false;
	for (int i = 0; i < length; i++) {
		if (str[i] >= '0'&&str[i] <= '9') {
			int temp = 0, j = i;
			while (str[i] >= '0'&&str[i] <= '9') {
				temp = temp * 10 + str[i] - '0'; i++;
			}
			i--;
			this->suffix.push(temp + '0');
		}
		else if (str[i] == '(') {
			opStack.push(str[i]);
			flag = true;
		}
		else if (str[i] == ')') {
			while (opStack.getTopEle() != '(') {
				suffix.push(opStack.pop());
			}
			opStack.pop();
			flag = false;
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			if (isDeal(str[i]) && !flag) {
				while (opStack.getTopEle() != FLOWER) {
					suffix.push(opStack.pop());
				}
				opStack.push(str[i]);
			}
			else {
				opStack.push(str[i]);
			}
		}
	}
	while (opStack.getTopEle() != FLOWER) {
		suffix.push(opStack.pop());
	}
}
//返回true将之前的操作符压入suffix
bool Calculate::isDeal(char op)
{
	return priorities(op) < priorities(opStack.getTopEle()) ? true : false;
}
//优先级越高返回值越大 
int Calculate::priorities(char op)
{
	if (op == '+' || op == '-' || op == FLOWER) {
		return 1;
	}
	else if (op == '*' || op == '/' || op == '%') {
		return 2;
	}
	else if (op == '(') {
		return 0;
	}
}



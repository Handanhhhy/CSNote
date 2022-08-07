#pragma once
#include"Stack.h"
#include<string>
class Calculate
{
public:
	Calculate(std::string str);
	~Calculate();
	void conversion();
	bool isDeal(char op);
	int priorities(char op);
	template<typename T>
	T compute();
private:
	Stack<char> opStack;
	Stack<char> suffix;
	Stack<int> aim;

	std::string str;
	size_t length;
};

template<typename T>
T Calculate::compute()
{
	std::string temp = suffix.getStr();
	T result = 0, front = 0, behind = 0;
	for (char c : temp) {
		switch (c)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			behind = aim.pop();
			front = aim.pop();
			break;
		default:
			aim.push(c - '0');
			break;
		}
		switch (c)
		{
		case '+':
			result = front + behind;
			aim.push(result);
			break;
		case '-':
			result = front - behind;
			aim.push(result);
			break;
		case '*':
			result = front * behind;
			aim.push(result);
			break;
		case '/':
			result = front / behind;
			aim.push(result);
			break;
		}
	}
	return result;
}
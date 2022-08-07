#include<Windows.h>
#include"Calculate.h"
#include<iostream>
/*
*基于栈实现的简单计算器，使用算法：中缀表达式转化为后缀表达式，后缀表达式的计算
*/
int main() {

	Calculate c("9+(3*1)*3+10/2+2");
	c.conversion();
	std::cout << c.compute<int>() << std::endl;
	system("pause");
	return 0;
}
#include<Windows.h>
#include"Calculate.h"
#include<iostream>
/*
*����ջʵ�ֵļ򵥼�������ʹ���㷨����׺���ʽת��Ϊ��׺���ʽ����׺���ʽ�ļ���
*/
int main() {

	Calculate c("9+(3*1)*3+10/2+2");
	c.conversion();
	std::cout << c.compute<int>() << std::endl;
	system("pause");
	return 0;
}
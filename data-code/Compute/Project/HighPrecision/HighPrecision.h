#pragma once
#include<string>
class HighPrecision
{
public:
	HighPrecision(std::string strO, std::string strT);
	~HighPrecision();
	std::string add();
	std::string subtract();
	std::string multiply();
	std::string divide();
	std::string add(std::string strO,std::string strT);
	std::string subtract(std::string strO, std::string strT);
	std::string multiply(std::string strO, std::string strT);
	std::string divide(std::string strO, std::string strT);
	void setStr(std::string strO, std::string strT);
private:
	int compare();
	void init();
	void init(int);
	void Free();
	int compare(int a[], int b[]);
	void subtract(int a[], int b[]);
private:
	std::string strO;
	std::string strT;
	int *a;
	int *b;
	int lenO;
	int lenT;
	int len;
};


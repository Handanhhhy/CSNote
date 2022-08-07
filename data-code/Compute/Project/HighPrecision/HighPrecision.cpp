#include "HighPrecision.h"
#include<cstring>
//两个操作数均为正数
HighPrecision::HighPrecision(std::string strO, std::string strT)
{
	a = nullptr;
	b = nullptr;
	lenO = 0;
	lenT = 0;
	len = 0;
	setStr(strO, strT);
}

HighPrecision::~HighPrecision()
{
	Free();
}

std::string HighPrecision::add()
{
	init();
	for (int i = 0; i < len; i++) {
		a[i] += b[i];
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}
	while (a[len] == 0 && len > 1) {
		len--;
	}
	std::string temp;
	temp.resize(len + 1);
	for (int i = len, j = 0; i >= 0; i--) {
		temp[j++] = a[i] + '0';
	}
	return temp;
}

std::string HighPrecision::subtract()
{
	init();
	std::string temp;
	int j = 0;
	if (compare()) {
		for (int i = 0; i < len; i++) {
			a[i] -= b[i];
			if (a[i] < 0) {
				a[i] += 10;
				a[i + 1]--;
			}
		}
		while (a[len] == 0 && len > 1) {
			len--;
		}
		temp.resize(len + 1);
		for (int i = len; i >= 0; i--) {
			temp[j++] = a[i] + '0';
		}
	}
	else {
		for (int i = 0; i < len; i++) {
			b[i] -= a[i];
			if (b[i] < 0) {
				b[i] += 10;
				b[i + 1]--;
			}
		}
		while (b[len] == 0 && len > 1) {
			len--;
		}
		temp.resize(len + 2);
		temp[j++] = '-';
		for (int i = len; i >= 0; i--) {
			temp[j++] = b[i] + '0';
		}
	}
	return temp;
}

std::string HighPrecision::multiply()
{
	init();
	int *c = new int[lenO + lenT];
	memset(c, 0, sizeof(int)*(lenO + lenT));
	for (int i = 0; i < lenO; i++) {
		for (int j = 0; j < lenT; j++) {
			c[i + j] += a[i] * b[j];
			c[i + j + 1] += c[i + j] / 10;
			c[i + j] %= 10;
		}
	}
	int length = lenO + lenT;
	while (c[length - 1] == 0 && length > 1) {
		length--;
	}
	std::string temp;
	temp.resize(length );
	for (int i = length - 1, j = 0; i >= 0; i--) {
		temp[j++] = c[i] + '0';
	}
	delete[]c;
	return temp;
}

std::string HighPrecision::divide()
{
	init(0);
	if (compare(a, b) < 0) {
		return std::string("0");
	}
	else {
		int *c = new int[a[0] - b[0] + 2];
		int *temp = new int[b[0] + 1];
		memset(c, 0, sizeof(int)*(a[0] - b[0] + 2));	
		c[0] = a[0] - b[0] + 1;
		for (int i = c[0]; i > 0; i--) {
			memset(temp, 0, sizeof(int)*(b[0] + 1));
			for (int j = 1; j <= b[0]; j++) {
				temp[i + j - 1] = b[j];
			}
			temp[0] = b[0] + i - 1;
			while (compare(a, temp) >= 0) {
				c[i]++;
				subtract(a, temp);
			}
		}
		while (c[c[0]] == 0 && c[0] > 1) {
			c[0]--;
		}
		std::string res;
		res.resize(c[0] + 1);
		for (int i = c[0],j=0; i > 0; i--) {
			res[j++] = c[i] + '0';
		}
		if (c != nullptr) {
			delete c;
			c = nullptr;
		}
		if (temp != nullptr) {
			delete temp;
			temp = nullptr;
		}
		return res;
	}
}

void HighPrecision::setStr(std::string strO, std::string strT)
{
	Free();
	this->strO = strO;
	this->strT = strT;
	lenO = strO.length(), lenT = strT.length();
	len = (lenO > lenT ? lenO : lenT);
	a = new int[len + 1];
	b = new int[len + 1];
	memset(a, 0, sizeof(int)*(len + 1));
	memset(b, 0, sizeof(int)*(len + 1));
	for (int i = 0; i < lenO; i++) {
		a[i] = strO[lenO - i - 1] - '0';
	}
	for (int i = 0; i < lenT; i++) {
		b[i] = strT[lenT - i - 1] - '0';
	}
}

int HighPrecision::compare()
{
	if (strO >= strT) {
		return 1;
	}
	else {
		return 0;
	}
}

void HighPrecision::init()
{
	Free();
	lenO = strO.length(), lenT = strT.length();
	len = (lenO > lenT ? lenO : lenT);
	a = new int[len + 1];
	b = new int[len + 1];
	memset(a, 0, sizeof(int)*(len + 1));
	memset(b, 0, sizeof(int)*(len + 1));
	for (int i = 0; i < lenO; i++) {
		a[i] = strO[lenO - i - 1] - '0';
	}
	for (int i = 0; i < lenT; i++) {
		b[i] = strT[lenT - i - 1] - '0';
	}
}

void HighPrecision::init(int)
{
	Free();
	lenO = strO.length(), lenT = strT.length();
	len = (lenO > lenT ? lenO : lenT);
	a = new int[lenO + 1];
	b = new int[lenT + 1];
	memset(a, 0, sizeof(int)*(lenO + 1));
	memset(b, 0, sizeof(int)*(lenT + 1));
	a[0] = lenO; b[0] = lenT;
	for (int i = 1; i <= lenO; i++) {
		a[i] = strO[lenO - i] - '0';
	}
	for (int i = 1; i <= lenT; i++) {
		b[i] = strT[lenT - i] - '0';
	}
}

void HighPrecision::Free()
{
	if (a != nullptr) {
		delete[]a;
		a = nullptr;
	}
	if (b != nullptr) {
		delete[]b;
		b = nullptr;
	}
}

int HighPrecision::compare(int a[], int b[])
{
	if (a[0] > b[0]) {
		return 1;
	}
	else if (a[0] < b[0]) {
		return -1;
	}
	else {
		for (int i = a[0]; i > 0; i--) {
			if (a[i] > b[i]) {
				return 1;
			}
			else if (a[i] < b[i]) {
				return -1;
			}
		}
	}
	return 0;
}

void HighPrecision::subtract(int a[], int b[])
{
	for (int i = 1; i <= a[0]; i++) {
		a[i] -= b[i];
		if (a[i] < 0) {
			a[i] += 10;
			a[i + 1]--;
		}
	}
	while (a[a[0]] == 0 && a[0] > 1) {
		a[0]--;
	}
}

std::string HighPrecision::add(std::string strO, std::string strT)
{
	setStr(strO, strT);
	return add();
}

std::string HighPrecision::subtract(std::string strO, std::string strT)
{
	setStr(strO, strT);
	return subtract();
}

std::string HighPrecision::multiply(std::string strO, std::string strT)
{
	setStr(strO, strT);
	return multiply();
}

std::string HighPrecision::divide(std::string strO, std::string strT)
{
	setStr(strO, strT);
	return divide();
}


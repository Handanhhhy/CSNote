#include"HighPrecision.h"
#include<iostream>
using namespace std;

int main() {
	HighPrecision a("24", "5");
	cout <<a.multiply();
	system("pause");
	return 0;
}

//高精度除以低精度
//#include<iostream>
//#include<algorithm>
//using namespace std;
//
//int main() {
//
//	char a1[100], c1[100];
//	int a[100], c[100], lena, i, x = 0, lenc, b;
//	memset(a, 0, sizeof(a));
//	memset(c, 0, sizeof(c));
//	cin >> a1;  //输入高精度被除数 
//	cin >> b;    //输入低精度除数 
//	lena = strlen(a1);
//	for (i = 0; i <= lena - 1; i++)
//		a[i + 1] = a1[i] - 48;   //将高精度被除数放入a数组 
//	for (i = 1; i <= lena; i++)            //按位相除
//	{
//		c[i] = (x * 10 + a[i]) / b;
//		x = (x * 10 + a[i]) % b;
//	}
//	lenc = 1;
//	while (c[lenc] == 0 && lenc < lena)
//		lenc++;       //删除前导0
//	for (i = lenc; i <= lena; i++)
//		cout << c[i];
//	cout << endl;
//	system("pause");
//	return 0;
//}

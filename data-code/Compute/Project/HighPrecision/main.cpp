#include"HighPrecision.h"
#include<iostream>
using namespace std;

int main() {
	HighPrecision a("24", "5");
	cout <<a.multiply();
	system("pause");
	return 0;
}

//�߾��ȳ��Ե;���
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
//	cin >> a1;  //����߾��ȱ����� 
//	cin >> b;    //����;��ȳ��� 
//	lena = strlen(a1);
//	for (i = 0; i <= lena - 1; i++)
//		a[i + 1] = a1[i] - 48;   //���߾��ȱ���������a���� 
//	for (i = 1; i <= lena; i++)            //��λ���
//	{
//		c[i] = (x * 10 + a[i]) / b;
//		x = (x * 10 + a[i]) % b;
//	}
//	lenc = 1;
//	while (c[lenc] == 0 && lenc < lena)
//		lenc++;       //ɾ��ǰ��0
//	for (i = lenc; i <= lena; i++)
//		cout << c[i];
//	cout << endl;
//	system("pause");
//	return 0;
//}

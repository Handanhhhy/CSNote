#include<iostream>
#include<algorithm>
using namespace std;
const int N = 10;
int num[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
void my_swap(int &a, int &b) {
	int temp = a;
	a = b; b = temp;
}
void shell_sort(int a[], int len) {
	for (int gap = len >> 1; gap > 0; gap = gap >> 1) {
		for (int i = gap; i < len; i++) {
			int temp = a[i], j = -1;
			for (j = i - gap; j >= 0 && a[j] > temp; j -= gap)
				a[j + gap] = a[j];
			a[j + gap] = temp;
		}
	}
}
int main() {
	int len = (int) sizeof(num) / sizeof(*num);
	//bubble_sort(num, len);
	//selection_sort(num, len);
	//insertion_sort(num, len);
	shell_sort(num, len);
	return 0;
}
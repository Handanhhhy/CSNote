### LIS&LDS&LCS

#### 最长上升子序列(LIS)和最长下降子序列(LDS)

```C++
#include<cstdio>
#include<algorithm>
#include<utility>
using namespace std;
const int N = 100001;
int a[N], n, MAX = 50001, MIN = 1;
int i_dp[N], d_dp[N];
struct g_e_cmp
{
	bool operator()(int a, int b) {
		return a > b;
	}
};
pair<int, int> solve() {
	pair<int, int> res;
	fill(i_dp, i_dp + n + 1, MAX);
	fill(d_dp, d_dp + n + 1, MIN);
	for (int i = 0; i < n; i++) {
		*upper_bound(d_dp, d_dp + n, a[i], g_e_cmp()) = a[i];
		*lower_bound(i_dp, i_dp + n, a[i]) = a[i];
	}
	res.first = lower_bound(d_dp, d_dp + n, MIN, g_e_cmp()) - d_dp;
	res.second = lower_bound(i_dp, i_dp + n, MAX) - i_dp;
	return res;
}
int main() {
	while (scanf("%d", &a[n]) != EOF) n++;
	auto ans = solve();
	printf("%d\n%d", ans.first, ans.second);
	return 0;
}
```



#### 最长公共子序列(LCS)

洛谷[P1439  【模板】最长公共子序列   ](https://www.luogu.com.cn/problem/P1439)

`时间复杂度：nlogn`

思路:先记录下p1中对应元素出现的位置，然后将p2中与p1中相同的元素位置对应起来。也就是说将p2换成p1，p2中元素应该出现的位置坐标，然后进行最长上升子序列求解。

```c++
#include<iostream>
#include<algorithm>

using namespace std;
const int N = 1e5 + 1;
int n;
int p1[N], p2[N], map[N], s[N], dp[N];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p1[i];
		map[p1[i]] = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> p2[i];
		s[i] = map[p2[i]];
	}
	fill(dp, dp + n, N);
	for (int i = 0; i < n; i++) {
		*lower_bound(dp, dp + n, s[i]) = s[i];
	}
	cout << lower_bound(dp, dp + n, N) - dp;
	return 0;
}
```


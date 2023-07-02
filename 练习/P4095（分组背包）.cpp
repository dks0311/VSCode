#include<bits/stdc++.h>
inline int read(){
	int s = 0, f = 0; char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
	while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
	return f ? ~s + 1 : s;
}
inline int min(int x, int y){return x < y ? x : y;}
inline int max(int x, int y){return x > y ? x : y;}
const int N = 1e3 + 5;
int n, q, sum;
int a[N], b[N], c[N];
int dp1[N][N], dp2[N][N];
int main(){
	n = read();
	for(int i = 1; i <= n; ++ i)
		a[i] = read(), b[i] = read(), c[i] = read(),
		sum += a[i] * c[i];
	sum = min(sum, 1000);
	for(int i = 1; i <= n; ++ i){
		for(int j = 1; j <= sum; ++ j) dp1[i][j] = dp1[i - 1][j];
		int k = 1;
		for(; k << 1 <= c[i] + 1; k <<= 1)
			for(int j = sum; j >= a[i] * k; -- j)
				dp1[i][j] = max(dp1[i][j], dp1[i][j - a[i] * k] + b[i] * k);
		k = c[i] - k + 1;
		if(!k) continue;
		for(int j = sum; j >= a[i] * k; -- j)
			dp1[i][j] = max(dp1[i][j], dp1[i][j - a[i] * k] + b[i] * k);
	}
	for(int i = n; i; -- i){
		for(int j = 1; j <= sum; ++ j) dp2[i][j] = dp2[i + 1][j];
		int k = 1;
		for(; k << 1 <= c[i] + 1; k <<= 1)
			for(int j = sum; j >= a[i] * k; -- j)
				dp2[i][j] = max(dp2[i][j], dp2[i][j - a[i] * k] + b[i] * k);
		k = c[i] - k + 1;
		if(!k) continue;
		for(int j = sum; j >= a[i] * k; -- j)
			dp2[i][j] = max(dp2[i][j], dp2[i][j - a[i] * k] + b[i] * k);
	}
	for(int i = 1; i <= n; ++ i)
		for(int j = 1; j <= sum; ++ j)
			dp1[i][j] = max(dp1[i][j], dp1[i][j - 1]),
			dp2[i][j] = max(dp2[i][j], dp2[i][j - 1]);
	q = read();
	while(q --){
		int d = read() + 1, e = read();
		int ans = 0;
		for(int i = 0; i <= e; ++ i)
			ans = max(ans, dp1[d - 1][i] + dp2[d + 1][e - i]);
		printf("%d\n", ans);
	}
	return 0;
}
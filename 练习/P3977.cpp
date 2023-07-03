#include <bits/stdc++.h>
#define ui unsigned int
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int M = 1 << 6 | 5;
struct matrix{
	ui a[M][M];
	int lx, ly;
	matrix(){memset(a, 0, sizeof a); lx = ly = 0;}
	matrix(int _lx, int _ly){memset(a, 0, sizeof a); lx = _lx, ly = _ly;}
	matrix operator * (const matrix &b) const{
		matrix c = matrix(lx, b.ly);
		for(int i = 0; i < c.lx; ++ i)
			for(int j = 0; j < c.ly; ++ j)
				for(int k = 0; k < ly; ++ k)
					c.a[i][j] += a[i][k] * b.a[k][j];
		return c;
	}
};
int n, m;
std::vector<int> at[4];
bool check(int t, int s1, int s2){
	for(int i = 0; i < at[t].size(); ++ i)
		if(s2 >> at[t][i] & s1 || at[t][i] < 0 && s1 >> -at[t][i] & s2) return false;
	return true;
}
matrix ksm(matrix a, int b){
	matrix ans = a;
	-- b;
	while(b){
		if(b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}
main(){
	n = read(), m = read();
	int p = read(), k = read() + 1;
	for(int i = 1; i <= 3; ++ i)
		for(int j = 1; j <= p; ++ j)
			if(read() && (j != k || i != 2)) at[i].push_back(j - k);
	matrix t = matrix(1 << m, 1 << m);
	for(int s1 = 0; s1 < 1 << m; ++ s1){
		if(!check(2, s1, s1)) continue;
		for(int s2 = 0; s2 < 1 << m; ++ s2){
			if(!check(3, s2, s1) || !check(2, s2, s2) || !check(1, s1, s2)) continue;
			t.a[s1][s2] = 1;
		}
	}
	matrix ans = matrix(1 << m, 1);
	ans.a[0][0] = 1;
	t = ksm(t, n + 1);
	ans = t * ans;
	printf("%u", ans.a[0][0]);
	return 0;
}
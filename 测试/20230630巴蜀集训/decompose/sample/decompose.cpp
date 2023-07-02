#include <bits/stdc++.h>
namespace _default{
    using namespace std;
    #define lovely return
    #define _lzy_ 0
    #define LL long long
    #define int long long
    #define DB double
    #define PII std::pair<int, int>
    #define X first
    #define Y second
    #define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
    #define uf(i, x, y) for(int i = (x); i < (y); ++ i)
    #define dF(i, x, y) for(int i = (x); i >= (y); -- i)
    #define df(i, x, y) for(int i = (x); i > (y); -- i)
    #define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
    #define sett(x, y) memset(x, y, sizeof x)
    #define copy(x, y) memcpy(x, y, sizeof x)
    const int MOD = 1e9 + 7, INF = 1e18;
    const DB EPS = 1e-8;
    template<typename T> inline T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> inline void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0){putchar('-'); x = -x;}
        if(!x) putchar('0');
        while(x) st[++ top] = x % 10, x /= 10;
        while(top) putchar(st[top --] + 48);
        printf("%s", s);
    }
    template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
    template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
    template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
    template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
const int N = 1e5 + 5;
int n, m, L;
int head[N], ne[N], to[N], idx;
int fat[N];
int w[N][5], dp[N][5], f[N], s[N];
inline void Add(int u, int v){
	to[++ idx] = v, ne[idx] = head[u], head[u] = idx;
}
void DFS(int u, int fa){
	fat[u] = fa;
	ef(i, u){
		int v = to[i];
		DFS(v, u);
		s[u] += f[v];
	}
	dp[u][1] = s[u] + w[u][1];
	ef(i, u){
		int v = to[i];
		uF(j, 2, L) updmax(dp[u][j], s[u] - f[v] + dp[v][j - 1] + w[u][j]);
	}
	uF(i, 1, L) updmax(f[u], dp[u][i]);
}
bool flag = true;
struct Sec{
	int f[5][5];
	Sec(){sett(f, -0x40);}
	friend Sec operator + (const Sec &a, const Sec &b){
		Sec res;
		uF(i, 1, L) uF(j, 1, L) uF(k, 2, L)
			updmax(res.f[i][j], a.f[i][k] + b.f[k - 1][j]);
		uF(i, 1, L) uF(j, 1, L) uF(k, 1, L)
			updmax(res.f[i][j], a.f[i][1] + b.f[k][j]);
		return res;
	}
};
struct Node{
	Sec v;
	int l, r;
}tr[N << 2];
inline void Pushup(int p){
	tr[p].v = tr[p << 1].v + tr[p << 1 | 1].v;
}
void Build(int l, int r, int p){
	tr[p].l = l, tr[p].r = r;
	if(l == r){
		uF(i, 1, L) tr[p].v.f[i][i] = w[l][i];
		return;
	}
	int mid = l + r >> 1;
	Build(l, mid, p << 1);
	Build(mid + 1, r, p << 1 | 1);
	Pushup(p);
}
void Modify(int p, int x){
	if(tr[p].l == tr[p].r){
		uF(i, 1, L) tr[p].v.f[i][i] = w[tr[p].l][i];
		return;
	}
	int mid = tr[p].l + tr[p].r >> 1;
	if(x <= mid) Modify(p << 1, x);
	else Modify(p << 1 | 1, x);
	Pushup(p);
}
signed main(){
	freopen("decompose3.in", "r", stdin);
	freopen("decompose.out", "w", stdout);
	n = read<int>(), m = read<int>(), L = read<int>();
	uF(i, 2, n){
		int x = read<int>();
		Add(x, i);
		if(x != i - 1) flag = false;
	}
	uF(i, 1, n) uF(j, 1, L) w[i][j] = read<int>();
	if(flag){
		Build(1, n, 1);
		while(m --){
			int u = read<int>();
			uF(i, 1, L) w[u][i] = read<int>();
			Modify(1, u);
			int ans = -INF;
			uF(i, 1, L) updmax(ans, tr[1].v.f[i][1]);
			write(ans, "\n");
		}
		return 0;
	}
	sett(dp, -0x40); sett(f, -0x40);
	DFS(1, 0);
	while(m --){
		int u = read<int>();
		s[fat[u]] -= f[u], f[u] = -INF;
		uF(i, 1, L) dp[u][i] -= w[u][i], w[u][i] = read<int>(), dp[u][i] += w[u][i], updmax(f[u], dp[u][i]);
		while(fat[u]){
			int v = u; u = fat[u];
			s[u] += f[v], s[fat[u]] -= f[u], f[u] = -INF;
			memset(dp[u], -0x40, sizeof dp[u]); dp[u][1] = s[u] + w[u][1];
			uF(i, 2, L) updmax(dp[u][i], s[u] - f[v] + dp[v][i - 1] + w[u][i]);
			uF(i, 1, L) updmax(f[u], dp[u][i]);
		}
		write(f[1], "\n");
	}
    lovely _lzy_;
}

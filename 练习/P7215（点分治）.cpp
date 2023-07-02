#include <bits/stdc++.h>
namespace _default{
    using namespace std;
    #define lovely return
    #define _lzy_ 0
    #define LL long long
//    #define int long long
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
    const int MOD = 1e9 + 7;
    const DB EPS = 1e-8, INF = 0x3f3f3f3f;
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
const int N = 2e5 + 5;
int n, m, ans = INF;
int head[N], ne[N << 1], to[N << 1], idx;
int fa[N], sz[N], c[N], zx, msz = INF;
int dfn[N], tot;
bool vis[N], vv[N]; 
vector<int> city[N];
inline void Add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
void DFS(int u, int fa, int n){
	int mx = 0; sz[u] = 1;
	ef(i, u){
		int v = to[i];
		if(vv[v] || v == fa) continue;
		DFS(v, u, n);
		sz[u] += sz[v];
		updmax(mx, sz[v]);
	}
	updmax(mx, n - sz[u]);
	if(mx < msz) msz = mx, zx = u;
}
void DFS1(int u, int f){
	sz[u] = 1, dfn[u] = ++ tot;
	ef(i, u){
		int v = to[i];
		if(vv[v] || v == f) continue;
		fa[v] = u;
		DFS1(v, u);
		sz[u] += sz[v];
	}
}
int st[N], top;
inline int Calc(int u){
	vis[st[top = 1] = c[u]] = true;
	int res = 0;
	for(int k = 1; k <= top; ++ k){
		for(auto x : city[st[k]]){
			int v = x;
			if(v == u) continue;
			while(true){
				v = fa[v];
				if(dfn[v] < dfn[u] || dfn[v] >= dfn[u] + sz[u]){res = INF; break;}
				if(vis[c[v]]) break;
				st[++ top] = c[v], vis[c[v]] = true;
			}
			if(res == INF) break;
		}
		if(res == INF) break;
	}
	if(!res) res = top - 1;
	while(top) vis[st[top --]] = false;
	return res;
}
void DFZ(int u, int fa){
	vv[u] = true;
	ef(i, u){
		int v = to[i];
		if(vv[v]) continue;
		DFS(v, u, sz[v]);
		msz = INF, tot = dfn[v] - 1;
		DFS1(zx, 0);
		updmin(ans, Calc(zx));
		DFZ(zx, u);
	}
}
signed main(){
	n = read<int>(), m = read<int>();
	uf(i, 1, n){
		int u = read<int>(), v = read<int>();
		Add(u, v); Add(v, u);
	}
	uF(i, 1, n) c[i] = read<int>(), city[c[i]].push_back(i);
	DFS(1, 0, n);
	DFS1(zx, 0);
	updmin(ans, Calc(zx));
	DFZ(zx, 0);
	
	write(ans, "\n");
    lovely _lzy_;
}

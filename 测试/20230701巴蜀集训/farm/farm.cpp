#include <bits/stdc++.h>
namespace _default{
    using namespace std;
    #define lovely return
    #define _lzy_ 0
    #define LL long long
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
    const int MOD = 1e9 + 7, INF = 0x3f3f3f3f;
    const DB EPS = 1e-8;
    template<typename T> inline T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> inline void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0) putchar('-'), x = -x;
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
const int N = 5e5 + 5, M = 3e6 + 5;
int n;
pair<PII, int> tp[N];
namespace QUERY1{
	int head[N], ne[M], to[M], idx = 1;
	int flw[M], cst[M];
	int dis[N], pre[N];
	bool inque[N];
	int s, t;
	inline void Add_Edge(int u, int v, int w, int c){
		to[++ idx] = v, ne[idx] = head[u], head[u] = idx;
		flw[idx] = w, cst[idx] = c;
	}
	inline void Add(int u, int v, int w, int c){
		Add_Edge(u, v, w, c); Add_Edge(v, u, 0, -c);
	}
	inline bool SPFA(){
	    sett(dis, -0x40);
	    sett(pre, 0);
	    sett(inque, false);
	    dis[s] = 0, inque[s] = true;
	    std::queue<int> q;
	    q.push(s);
	    while(!q.empty()){
	        int u = q.front(); q.pop();
	        inque[u] = false;
	        ef(i, u){
	            int v = to[i];
	            if(!flw[i] || dis[v] >= dis[u] + cst[i]) continue;
	            dis[v] = dis[u] + cst[i], pre[v] = i;
	            if(!inque[v] && v != t) q.push(v);
	            inque[v] = true;
	        }
	    }
	    return dis[t] != dis[0];
	}
	inline int EK(){
	    int res = 0;
	    while(SPFA()){
	        int mn = INF;
	        for(int i = t; i != s; i = to[pre[i] ^ 1])
	            mn = min(mn, flw[pre[i]]);
	        for(int i = t; i != s; i = to[pre[i] ^ 1])
	            flw[pre[i]] -= mn, flw[pre[i] ^ 1] += mn;
	        res += mn * dis[t];
	    }
	    return res;
	}
	inline void Print(int u){
		if(u == t) return;
		if(u != s && u != 1) write(tp[u].Y, " ");
		ef(i, u) if(!flw[i]){Print(to[i]); break;}
	}
}
namespace QUERY2{
	int s, t, ss, tt;
	int head[N], to[M << 1], ne[M << 1], idx = 1;
	int flw[M << 1];
	int re[N], hgt[N], cur[N];
	inline void Add_Edge(int u, int v, int w){
	    to[++ idx] = v, ne[idx] = head[u], head[u] = idx;
	    flw[idx] = w;
	    return;
	}
	inline void Add(int u, int v, int w){
		Add_Edge(u, v, w); Add_Edge(v, u, 0);
	}
	inline bool BFS(int s, int t){
	    memset(hgt, -1, sizeof hgt);
	    for(int i = 1; i <= n + 4; ++ i) cur[i] = head[i];
	    hgt[s] = 0;
	    std::queue<int> q;
	    q.push(s);
	    while(!q.empty()){
	        int u = q.front(); q.pop();
	        for(int i = head[u]; i; i = ne[i]){
	            int v = to[i];
	            if(!flw[i] || hgt[v] != -1) continue;
	            hgt[v] = hgt[u] + 1;
	            q.push(v);
	        }
	    }
	    return hgt[t] != -1;
	}
	int DFS(int u, int ori, int s, int t){
	    if(u == t) return ori;
	    int rest = ori;
	    for(int i = cur[u]; i && rest; i = ne[i]){
	        cur[u] = i;
	        int v = to[i];
	        if(!flw[i] || hgt[v] != hgt[u] + 1) continue;
	        int delta = DFS(v, min(rest, flw[i]), s, t);
	        flw[i] -= delta, flw[i ^ 1] += delta;
	        rest -= delta;
	    }
	    return ori - rest;
	}
	inline int Dinic(int s, int t){
	    int res = 0;
	    while(BFS(s, t)) res += DFS(s, INF, s, t);
	    return res;
	}
	inline void Solve(){
		s = n + 1, t = n + 2, ss = n + 3, tt = n + 4;
		unordered_map<int, int> aa, bb, cc;
	    uF(i, 1, n){
			int x = tp[i].X.X, y = tp[i].X.Y;
			if(aa.count(x + y)){
				-- re[aa[x + y]], ++ re[i];
				Add(aa[x + y], i, INF);
			}
			if(bb.count(x - y)){
				-- re[bb[x - y]], ++ re[i];
				Add(bb[x - y], i, INF);
			}
			if(cc.count(x)){
				-- re[cc[x]], ++ re[i];
				Add(cc[x], i, INF);
			}
			aa[x + y] = i, bb[x - y] = i, cc[x] = i;
		}
	    for(int i = 1; i <= n; ++ i)
	        Add(s, i, INF), Add(i, t, INF);
	    int sum = 0;
	    for(int i = 1; i <= n; ++ i)
	        if(re[i] > 0) Add(ss, i, re[i]), Add(i, ss, 0), sum += re[i];
	        else if(re[i] < 0) Add(i, tt, -re[i]);
	    Add(t, s, INF);
	    Dinic(ss, tt);
	    int tmp = flw[idx];
	    flw[idx] = flw[idx - 1] = 0;
	    write(tmp - Dinic(t, s), "\n");
	}
}
signed main(){
	freopen("farm.in", "r", stdin);
	freopen("farm.out", "w", stdout);
	n = read<int>();
	uF(i, 1, n) tp[i].X.X = read<int>(), tp[i].X.Y = read<int>(), tp[i].Y = i;
	tp[++ n] = {{0, 0}, 0};
	sort(tp + 1, tp + n + 1, [](pair<PII, int> a, pair<PII, int> b){return a.X.Y < b.X.Y;});
	QUERY1::s = n + 1, QUERY1::t = n + 2;
	QUERY1::Add(QUERY1::s, 1, 1, 0);
	uF(i, 1, n) QUERY1::Add(i, QUERY1::t, 1, 0);
	unordered_map<int, int> aa, bb, cc;
	uF(i, 1, n){
		int x = tp[i].X.X, y = tp[i].X.Y;
		if(aa.count(x + y)) QUERY1::Add(aa[x + y], i, 1, 1);
		if(bb.count(x - y)) QUERY1::Add(bb[x - y], i, 1, 1);
		if(cc.count(x)) QUERY1::Add(cc[x], i, 1, 1);
		aa[x + y] = i, bb[x - y] = i, cc[x] = i;
	}
	write(QUERY1::EK(), "\n");
	QUERY1::Print(QUERY1::s);
	puts("");
	QUERY2::Solve();
    lovely _lzy_;
}

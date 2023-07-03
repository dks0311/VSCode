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
const int N = 205, M = 1e4 + 5;
int n, m, s, t;
int head[N], ne[M], to[M], idx = 1;
int flw[M];
int hgt[N], cur[N];
void Add_Edge(int u, int v, int w){
    to[++ idx] = v, ne[idx] = head[u], head[u] = idx;
    flw[idx] = w;
}
bool BFS(){
    memset(hgt, -1, sizeof hgt);
    queue<int> q;
    q.push(s);
    hgt[s] = 0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        cur[u] = head[u];
        ef(i, u){
            int v = to[i];
            if(!flw[i] || hgt[v] != -1) continue;
            hgt[v] = hgt[u] + 1;
            q.push(v);
        }
    }
    return hgt[t] != -1;
}
int DFS(int u, int ori){
    if(u == t) return ori;
    int rest = ori;
    for(int i = cur[u]; i; i = ne[i]){
        int v = to[cur[u] = i];
        if(!rest || !flw[i] || hgt[v] != hgt[u] + 1) continue;
        int delta = DFS(v, min(rest, flw[i]));
        flw[i] -= delta, flw[i ^ 1] += delta;
        rest -= delta;
    }
    return ori - rest;
}
int Dinic(){
    int res = 0;
    while(BFS()) res += DFS(s, INF);
    return res;
}
signed main(){
    n = read<int>(), m = read<int>(), s = read<int>(), t = read<int>();
    uF(i, 1, m){
        int u = read<int>(), v = read<int>(), w = read<int>();
        Add_Edge(u, v, w); Add_Edge(v, u, 0);
    }
    write(Dinic(), "\n");
    lovely _lzy_;
}
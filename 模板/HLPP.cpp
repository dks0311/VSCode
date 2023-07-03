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
const int N = 1205, M = 240005;
int n, m, s, t;
int head[N], ne[M], to[M], idx = 1;
int flw[M];
int extra[N], hgt[N], gap[N << 1];
bool inque[N];
inline void Add_Edge(int u, int v, int w){
    to[++ idx] = v, ne[idx] = head[u], head[u] = idx, flw[idx] = w;
}
inline bool BFS(){
    memset(hgt, -1, sizeof hgt);
    queue<int> q;
    q.push(t); hgt[t] = 0, gap[0] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        ef(i, u){
            int v = to[i];
            if(hgt[v] != -1 || flw[i]) continue;
            hgt[v] = hgt[u] + 1, ++ gap[hgt[v]];
            q.push(v);
        }
    }
    return hgt[s] != -1;
}
inline int HLPP(){
    if(!BFS()) return 0;
    -- gap[hgt[s]], ++ gap[n];
    hgt[s] = n, extra[s] = INF;
    priority_queue<PII> q;
    q.push((PII){n, s});
    while(!q.empty()){
        int u = q.top().Y; q.pop();
        inque[u] = false;
        int mn = INF;
        ef(i, u){   
            int v = to[i];
            if(!flw[i]) continue;
            if(hgt[u] != hgt[v] + 1) updmin(mn, hgt[v]);
            if(hgt[u] != hgt[v] + 1 && u != s) continue;
            int delta = min(extra[u], flw[i]);
            extra[u] -= delta, extra[v] += delta;
            flw[i] -= delta, flw[i ^ 1] += delta;
            if(v != s && v != t && !inque[v]) q.push((PII){hgt[v], v});
            inque[v] = true;
            if(!extra[u]) break;
        }
        if(extra[u] && u != s){
            if(!-- gap[hgt[u]])
                uF(i, 1, n) if(i != s && i != t && hgt[i] > hgt[u] && hgt[i] <= n) hgt[i] = n + 1;
            hgt[u] = mn + 1, ++ gap[hgt[u]];
            q.push((PII){hgt[u], u});
            inque[u] = true;
        }
    }
    return extra[t];
}
signed main(){
    n = read<int>(), m = read<int>(), s = read<int>(), t = read<int>();
    uF(i, 1, m){
        int u = read<int>(), v = read<int>(), w = read<int>();
        Add_Edge(u, v, w); Add_Edge(v, u, 0);
    }
    write(HLPP(), "\n");
    lovely _lzy_;
}
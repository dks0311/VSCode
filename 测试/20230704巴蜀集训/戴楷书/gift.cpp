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
    const int MOD = 1e9 + 7, INF = 0x3f3f3f3f;
    const DB EPS = 1e-8;
    template<typename T> T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0){putchar('-'); x = -x;}
        if(!x) putchar('0');
        while(x) st[++ top] = x % 10, x /= 10;
        while(top) putchar(st[top --] + 48);
        printf("%s", s);
    }
    template<typename T> void updmin(T &x, T y){if(x > y) x = y;}
    template<typename T> void updmax(T &x, T y){if(x < y) x = y;}
    template<typename T> void updadd(T &x, T y){(x += y % MOD) %= MOD;}
    template<typename T> void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
const int N = 3e5 + 5;
int n, m, q, tt[N], col[N], f[N][20], dpt[N];
int head[N], to[N], ne[N], idx;
bitset<1005> co[N];
void Add_Edge(int u, int v){
    to[++ idx] = v, ne[idx] = head[u], head[u] = idx;
}
void DFS(int u){
    uF(i, 1, 18) f[u][i] = f[f[u][i - 1]][i - 1];
    ef(i, u){
        int v = to[i];
        co[v] |= co[u], f[v][0] = u, dpt[v] = dpt[u] + 1;
        DFS(v);
    }
}
int lca(int u, int v){
    if(dpt[u] < dpt[v]) swap(u, v);
    dF(i, 18, 0) if(dpt[f[u][i]] >= dpt[v]) u = f[u][i];
    if(u == v) return u;
    dF(i, 18, 0) if(f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
int cnt[10], ans, p[10];
bitset<1005> cc[10];
void DFS1(int x, int k){
    if(x > m){
        int res = INF;
        uF(i, 1, k) updmin(res, cnt[i]);
        updmax(ans, res);
        return;
    }
    uF(i, 1, k){
        if(!cc[i][x]) continue;
        ++ cnt[i];
        DFS1(x + 1, k);
        -- cnt[i];
    }
    DFS1(x + 1, k);
}
signed main(){
    freopen("gift.in", "r", stdin);
    freopen("gift.out", "w", stdout);
    n = read<int>(), m = read<int>(), q = read<int>();
    if(!q) return 0;
    uF(i, 2, n){
        int x = read<int>();
        Add_Edge(x, i);
    }
    uF(i, 1, n) tt[i] = col[i] = read<int>();
    sort(tt + 1, tt + n + 1);
    m = unique(tt + 1, tt + n + 1) - tt - 1;
    uF(i, 1, n) col[i] = lower_bound(tt + 1, tt + m + 1, col[i]) - tt;
    uF(i, 1, n) co[i][col[i]] = 1;
    DFS(1);
    if(n <= 10 && q <= 10){
        while(q --){
            int k = read<int>(), l;
            uF(i, 1, k){
                p[i] = read<int>();
                if(i == 1) l = p[i];
                else l = lca(l, p[i]);
            }
            uF(i, 1, k){
                uF(j, 1, m) cc[i][j] = 0;
                for(int y = p[i]; y != f[l][0]; y = f[y][0]) cc[i][col[y]] = 1;
            }
            ans = 0;
            DFS1(1, k);
            write(ans * k, "\n");
        }
    }
    lovely _lzy_;
}
/*
5 3 4
1 2 2 1
2 3 1 3 1
2 3 4
3 5 2 2
4 3 4 2 5
2 2 2
*/
#include <bits/stdc++.h>
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
#define init(x, y) memset(x, y, sizeof x)
#define copy(x, y) memcpy(x, y, sizeof x)
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void write(T x, const char *s){
    static int st[40]; int top = 0;
    if(x < 0){putchar('-'); x = -x;}
    if(!x) putchar('0');
    while(x) st[++ top] = x % 10, x /= 10;
    while(top) putchar(st[top --] + 48);
    printf("%s", s);
}
template<typename T> inline T max(T x, T y){return x > y ? x : y;}
template<typename T> inline T min(T x, T y){return x < y ? x : y;}
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 3e5 + 5;
int n, m;
int head[N], ne[N << 1], to[N << 1], idx;
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
int dpt[N], maxdpt[N], son[N], sz[N];
int *dp[N], ad[N], ans[N << 2], *id = ans, res[N];
std::vector<PII> q[N];
void dfs(int u, int fa){
    dpt[u] = dpt[fa] + (sz[u] = 1);
    ef(i, u){
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if(maxdpt[v] > maxdpt[son[u]]) son[u] = v;
    }
    maxdpt[u] = maxdpt[son[u]] + 1;
}
void dfs1(int u, int fa){
    if(son[u]){
        dp[son[u]] = dp[u] + 1;
        dfs1(son[u], u);
        dp[u][0] = 0, ad[u] = ad[son[u]] + sz[son[u]] - 1;
    }
    ef(i, u){
        int v = to[i];
        if(v == fa || v == son[u]) continue;
        dp[v] = id, id += maxdpt[v];
        dfs1(v, u);
        ad[u] += ad[v] + sz[v] - 1;
        uF(j, 1, maxdpt[v]) dp[u][j] += dp[v][j - 1];
    }
    dp[u][0] = -ad[u];
    for(auto x : q[u])
        res[x.Y] = dp[u][min(x.X, maxdpt[u] - 1)] + ad[u] + (sz[u] - 1) * min(dpt[u] - 1, x.X);
}
signed main(){
    n = read<int>(), m = read<int>();
    uf(i, 1, n){
        int u = read<int>(), v = read<int>();
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    uF(i, 1, m){
        int u = read<int>(), k = read<int>();
        q[u].push_back((PII){k, i});
    }
    dp[1] = id, id += maxdpt[1];
    dfs1(1, 0);
    uF(i, 1, m) write(res[i], "\n");
    lovely _lzy_;
}
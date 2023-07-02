#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
// #define int long long
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
inline void updmin(int &x, int y){if(x > y) x = y;}
inline void updmax(int &x, int y){if(x < y) x = y;}
const int N = 105, M = 1 << 12 | 5;
int n, p, t;
int head[N], ne[N << 1], to[N << 1], idx;
int a[N][15], ex[M], _ex[M];
int dp[N][M], tmp[M], cst[N][M];
std::vector<int> in[M];
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
void dfs(int u, int fa){
    for(int s = 0; s < 1 << p; ++ s) dp[u][s] = cst[u][s] + ex[s];
    for(int i = head[u]; i; i = ne[i]){
        int v = to[i]; 
        if(v == fa) continue;
        dfs(v, u);
        memcpy(tmp, dp[u], sizeof tmp);
        memset(dp[u], 0x3f, sizeof dp[u]);
        for(int s = 0; s < 1 << p; ++ s){
            int k = in[s].size();
            for(int j = 0; j < k; ++ j){
                int _s = in[s][j];
                updmin(dp[u][s], tmp[_s] - ex[_s] + ex[s] + dp[v][s ^ _s]);
            }
        }
    }
}
signed main(){
    n = read(), p = read();
    for(int i = 1; i < n; ++ i){
        int u = read(), v = read();
        add(u, v); add(v, u);
    }
    for(int i = 1; i <= n; ++ i)
        for(int j = 0; j < p; ++ j) a[i][j] = read();
    t = read();
    for(int i = 1; i <= t; ++ i){
        int v = read(), k = read(), s = 0;
        for(int j = 1; j <= k; ++ j) s |= 1 << read() - 1;
        _ex[s] += -v;
    }
    for(int i = 0; i < 1 << p; ++ i)
        for(int j = 0; j < 1 << p; ++ j){
            if((i | j) != i) continue;
            in[i].push_back(j);
            ex[i] += _ex[j];
        }
    for(int u = 1; u <= n; ++ u)
        for(int i = 0; i < 1 << p; ++ i)
            for(int j = 0; j < p; ++ j)
                if(i >> j & 1) cst[u][i] += a[u][j];
    dfs(1, 0);
    printf("%d\n", -dp[1][(1 << p) - 1]);
    lovely _lzy_;
}
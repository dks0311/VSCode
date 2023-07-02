#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
const int MOD = 1e9 + 7;
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
inline void updadd(unsigned &x, int y){x = (int)(x + y) % MOD;}
inline void updmlt(int &x, int y){x = x * y % MOD;}
const int N = 1e5 + 5, M = 105;
int n, m;
int head[N], ne[N << 1], to[N << 1], idx;
unsigned dp[N][M][2][2], t[M][2][2];
int sz[N];
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
void dfs(int u, int fa){
    sz[u] = dp[u][0][0][0] = dp[u][1][0][1] = 1;
    for(int e = head[u]; e; e = ne[e]){
        int v = to[e];
        if(v == fa) continue;
        dfs(v, u);
        memcpy(t, dp[u], sizeof dp[u]);
        memset(dp[u], 0, sizeof dp[u]);
        for(int i = 0; i <= min(sz[u], m); ++ i){
            for(int j = 0; j <= min(sz[v], m - i); ++ j){
                updadd(dp[u][i + j][0][0], 1ll * (int)t[i][0][0] * (int)dp[v][j][1][0]); //没被听没放
                updadd(dp[u][i + j][1][0], 1ll * (int)t[i][1][0] * ((int)dp[v][j][1][1] + (int)dp[v][j][1][0])\
                + 1ll * (int)t[i][0][0] * (int)dp[v][j][1][1]); //被听了没放
                updadd(dp[u][i + j][0][1], 1ll * (int)t[i][0][1] * ((int)dp[v][j][0][0] + (int)dp[v][j][1][0])); //没被听放了
                updadd(dp[u][i + j][1][1], 1ll * (int)t[i][1][1] * ((int)dp[v][j][0][0] + (int)dp[v][j][0][1] + (int)dp[v][j][1][0] + (int)dp[v][j][1][1])\
                + 1ll * (int)t[i][0][1] * ((int)dp[v][j][0][1] + (int)dp[v][j][1][1])); //被听了也放了
            }
        }
        sz[u] += sz[v];
    }
}
signed main(){
    n = read(), m = read();
    for(int i = 1; i < n; ++ i){
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    printf("%u\n", ((int)dp[1][m][1][0] + (int)dp[1][m][1][1]) % MOD);
    lovely _lzy_;
}
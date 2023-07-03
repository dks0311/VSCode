#include <bits/stdc++.h>
#define int long long
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 1e2 + 5, MOD = 1e9 + 7;
int T, n;
int dp[N][N], c[N][N], sz[N], t[N];
int head[N], ne[N << 1], to[N << 1], pr[N << 1], idx;
char s[N];
void add(int u, int v, int p){to[++ idx] = v, ne[idx] = head[u], head[u] = idx, pr[idx] = p;}
void dfs(int u, int fa){
    sz[u] = dp[u][1] = 1;
    for(int i = head[u]; i; i = ne[i]){
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        memcpy(t, dp[u], sizeof dp[u]);
        memset(dp[u], 0, sizeof dp[u]);
        if(pr[i]){
            for(int k = 1; k <= sz[u]; ++ k)
                for(int j = k + 1; j <= k + sz[v]; ++ j)
                    (dp[u][j] += c[j - 1][k - 1] * c[sz[u] + sz[v] - j][sz[u] - k] % MOD * t[k] % MOD * dp[v][j - k] % MOD) %= MOD;
        }
        else{
            for(int k = 1; k <= sz[u]; ++ k)
                for(int j = k; j < k + sz[v]; ++ j)
                    (dp[u][j] += c[j - 1][k - 1] * c[sz[u] + sz[v] - j][sz[u] - k] % MOD * t[k] % MOD * (dp[v][sz[v]] - dp[v][j - k] + MOD) % MOD) %= MOD;
        }
        sz[u] += sz[v];
    }
    for(int i = 1; i <= sz[u]; ++ i) (dp[u][i] += dp[u][i - 1]) %= MOD;
}
main(){
    for(int i = 0; i <= 1e2; ++ i){
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++ j) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
    n = read();
    scanf("%s", s + 2);
    for(int i = 2; i <= n; ++ i){
        if(s[i] == '>') add(i, i >> 1, 0), add(i >> 1, i, 1);
        else add(i, i >> 1, 1), add(i >> 1, i, 0);
    }
    dfs(1, 0);
    printf("%lld\n", dp[1][n]);
    return 0;
}
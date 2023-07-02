#include <bits/stdc++.h>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 5e5 + 5, INF = 0x3f3f3f3f;
int n, d, m;
int dp1[N][25], dp2[N][25], t1[N], t2[N], w[N], ap[N];
int head[N], ne[N << 1], to[N << 1], idx;
void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
void dfs(int u, int fa){
    for(int i = 1; i <= d; ++ i) dp1[u][i] = w[u];
    if(ap[u]) dp1[u][0] = dp2[u][0] = w[u];
    dp1[u][d + 1] = INF;
    for(int i = head[u]; i; i = ne[i]){
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u);
        for(int j = 0; j <= d; ++ j)
            dp1[u][j] = min(dp1[u][j] + dp2[v][j],  dp2[u][j + 1] + dp1[v][j + 1]);
        for(int j = d; j >= 0; -- j) dp1[u][j] = min(dp1[u][j], dp1[u][j + 1]);
        dp2[u][0] = dp1[u][0];
        for(int j = 1; j <= d; ++ j) dp2[u][j] += dp2[v][j - 1];
        for(int j = 1; j <= d; ++ j) dp2[u][j] = min(dp2[u][j], dp2[u][j - 1]);
    }
}
int main(){
    n = read(), d = read();
    for(int i = 1; i <= n; ++ i) w[i] = read();
    m = read();
    for(int i = 1; i <= m; ++ i) ap[read()] = 1;
    for(int i = 1; i < n; ++ i){
        int u = read(), v = read();
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    printf("%d\n", dp1[1][0]);
    return 0;
}
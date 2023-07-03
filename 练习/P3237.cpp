#include <bits/stdc++.h>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 5e5 + 5;
int n, a[N], cnt[N];
double dp[N];
int head[N], ne[N << 1], to[N << 1], idx;
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
void dfs(int u, int fa, double now){
    dp[u] = now + log(a[u]);
    for(int i = head[u]; i; i = ne[i]) if(to[i] != fa) ++ cnt[u];
    for(int i = head[u]; i; i = ne[i]){
        int v = to[i];
        if(v == fa) continue;
        dfs(v, u, now + log(cnt[u]));
    }
}
int main(){
    n = read();
    for(int i = 1; i <= n; ++ i) a[i] = read();
    for(int i = 1; i < n; ++ i){
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    dfs(1, 0, 0);
    std::sort(dp + 1, dp + n + 1);
    int ans = 0;
    dp[n + 1] = 1e7;
    for(int i = 2, now = 1; i <= n + 1; ++ i, ++ now)
        if(dp[i] - dp[i - 1] > 1e-8) ans = max(ans, now), now = 0;
    printf("%d\n", n - ans);
    return 0;
}
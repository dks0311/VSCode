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
int n, s, rt, tp, ans = INF;
int head[N], ne[N << 1], to[N << 1], wgt[N << 1], idx;
int dis[N], f[N], d[N];
int q[N], hh, tt = 1, up;
bool ban[N];
inline void add(int u, int v, int w){to[++ idx] = v, wgt[idx] = w, ne[idx] = head[u], head[u] = idx;}
void dfs(int u, int fa){
    f[u] = fa;
    for(int i = head[u]; i; i = ne[i]){
        int v = to[i];
        if(v == fa) continue;
        dis[v] = dis[u] + wgt[i];
        dfs(v, u);
    }
}
int dfs1(int u, int fa){
    int res = 0;
    for(int i = head[u]; i; i = ne[i]){
        int v = to[i];
        if(v == fa || ban[v]) continue;
        d[v] = d[u] + wgt[i];
        res = max(res, dfs1(v, u));
    }
    return max(res, d[u]);
}
int main(){
    n = read(), s = read();
    for(int i = 1; i < n; ++ i){
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; ++ i) if(dis[rt] < dis[i]) rt = i;
    dis[rt] = 0;
    dfs(rt, 0);
    for(int i = 1; i <= n; ++ i) if(dis[tp] < dis[i]) tp = i;
    for(int u = tp; u; u = f[u]) ban[u] = true;
    for(int u = tp; u; u = f[u]) d[u] = dfs1(u, 0);
    up = tp, q[++ hh] = tp;
    for(int u = tp; u; u = f[u]){
        if(!f[up]) break;
        while(f[up] && dis[u] - dis[f[up]] <= s){
            up = f[up];
            while(hh >= tt && d[q[hh]] < d[up]) -- hh;
            q[++ hh] = up;
        }
        ans = min(ans, max(d[q[tt]], max(dis[tp] - dis[u], dis[up])));
        if(q[tt] == u) ++ tt;
    }
    printf("%d\n", ans);
    return 0;
}
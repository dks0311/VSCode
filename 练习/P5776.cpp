#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
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
const int N = 15, M = 1 << 12 | 5, INF = 0x3f3f3f3f;
int T, n, m;
int e[N][N][2];
int dp[M], f[M][N][N];
signed main(){
    T = read();
    while(T --){
        n = read(), m = read();
        memset(e, 0x3f, sizeof e);
        for(int i = 1; i <= m; ++ i){
            int u = read() - 1, v = read() - 1, w = read();
            if(w < e[u][v][0]) e[u][v][1] = e[u][v][0], e[u][v][0] = w;
            else updmin(e[u][v][1], w);
            e[v][u][0] = e[u][v][0], e[v][u][1] = e[u][v][1];
        }
        memset(dp, 0x3f, sizeof dp);
        memset(f, 0x3f, sizeof f);
        for(int i = 0; i < n; ++ i) dp[1 << i] = 0;
        for(int s = 1; s < 1 << n; ++ s){
            for(int u = 0; u < n; ++ u){
                if((s >> u & 1)) continue;
                for(int v = 0; v < n; ++ v){
                    if(!(s >> v & 1) || e[u][v][1] == INF) continue;
                    updmin(dp[s | 1 << u], dp[s] + e[u][v][0] + e[u][v][1]);
                }
            }
            for(int u = 0; u < n; ++ u){
                if((s >> u & 1)) continue;
                for(int v = 0; v < n; ++ v){
                    if(!(s >> v & 1)) continue;
                    for(int w = 0; w < n; ++ w){
                        if(!(s >> w & 1)) continue;
                        if(v != w) updmin(f[s][u][v], dp[s] + e[w][u][0]);
                        else updmin(f[s | 1 << u][u][v], dp[s] + e[w][u][0]);   
                    }
                }
            }
            for(int u = 0; u < n; ++ u)
                for(int v = 0; v < n; ++ v){
                    if(!(s >> v & 1) || u == v) continue;
                    for(int w = 0; w < n; ++ w){
                        if(s >> w & 1 || u == w) continue;
                        updmin(f[s | 1 << u][w][v], f[s][u][v] + e[u][w][0]);
                    }
                }
            for(int u = 0; u < n; ++ u){
                if(s >> u & 1) continue;
                for(int v = 0; v < n; ++ v){
                    if(!(s >> v & 1)) continue;
                    updmin(dp[s | 1 << u], f[s][u][v] + e[u][v][0]);
                }
            }
        }
        if(dp[(1 << n) - 1] == INF) puts("impossible");
        else printf("%d\n", dp[(1 << n) - 1]);
    }
    lovely _lzy_;
}
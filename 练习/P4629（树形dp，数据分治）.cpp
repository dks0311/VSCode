#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
// #define int long long
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
inline void updadd(int &x, int y){(x += y % MOD) %= MOD;}
inline void updmlt(int &x, int y){x += (y % MOD) % MOD;}
int n;
namespace case1{
    const int N = 1e5 + 5;
    int head[N], ne[N << 1], to[N << 1], idx;
    int c[N], d[N], ans;
    bool stm[N];
    inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
    void stimulate(int u){
        std::queue<int> q;
        q.push(u);
        ans += d[u], d[u] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int i = head[u]; i; i = ne[i]){
                int v = to[i];
                if(d[v]){
                    d[v] = max(d[v] - c[u], 0);
                    if(!d[v] && c[v]) q.push(v);
                }
            }
        }
    }
}
namespace case2{
    const int N = 2e3 + 5, M = 1e4 + 5;
    int head[N], ne[N << 1], to[N << 1], idx;
    int dp[N][2], f[M], tf[M], d[N], c[N];
    inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
    inline void dfs(int u, int fa){
        int sum = 0;
        for(int i = head[u]; i; i = ne[i])
            if(to[i] != fa){dfs(to[i], u); sum += c[to[i]];}
        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        for(int i = head[u]; i; i = ne[i]){
            int v = to[i];
            if(v == fa) continue;
            memcpy(tf, f, sizeof tf);
            memset(f, 0x3f, sizeof f);
            for(int i = 0; i <= sum; ++ i)
                updmin(f[i + c[v]], tf[i] + dp[v][0]), 
                updmin(f[i], tf[i] + dp[v][1]);
        }
        for(int i = 0; i <= sum; ++ i)
            updmin(dp[u][0], f[i] + max(0, d[u] - i)),
            updmin(dp[u][1], f[i] + max(0, d[u] - i - c[fa]));
    }
}
signed main(){
    n = read();
    if(n > 2000){
        using namespace case1;
        for(int i = 1; i <= n; ++ i) d[i] = read();
        for(int i = 1; i <= n; ++ i) c[i] = read();
        for(int i = 1; i < n; ++ i){
            int u = read(), v = read();
            add(u, v); add(v, u);
        }
        for(int i = 1; i <= n; ++ i) if(c[i] && d[i]) stimulate(i);
        for(int i = 1; i <= n; ++ i) ans += d[i];
        printf("%d\n", ans);
    }
    else{
        using namespace case2;
        for(int i = 1; i <= n; ++ i) d[i] = read();
        for(int i = 1; i <= n; ++ i) c[i] = read();
        for(int i = 1; i < n; ++ i){
            int u = read(), v = read();
            add(u, v); add(v, u);
        }
        memset(dp, 0x3f, sizeof dp);
        dfs(1, 0);
        printf("%d\n", dp[1][0]);
    }
    lovely _lzy_;
}
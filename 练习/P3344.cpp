#include <bits/stdc++.h>
#define lovely return
#define lzy 0
#define int long long
#define PII std::pair<int, int>
#define X first
#define Y second
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
const int N = 105, INF = 0x3f3f3f3f;
int n, m, r, cup, cdw, tot;
int dp[N][N][N];
typedef struct net_point{
    PII p; int c;
    bool operator < (const net_point &t) const{return p.X < t.p.X;}
}np;
np up[N], dw[N];
PII at[N];
bool av[N];
int dist(PII a, PII b){
    return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y);
}
signed main(){
    n = read(), m = read(), r = read();
    r = r * r;
    for(int i = 1; i <= n; ++ i) at[i] = (PII){read(), read()};
    for(int i = 1; i <= m; ++ i){
        int x = read(), y = read(), c = read();
        if(y < 0) dw[++ cdw] = (np){(PII){x, y}, c};
        else up[++ cup] = (np){(PII){x, y}, c};
        for(int j = 1; j <= n; ++ j) if(dist((PII){x, y}, at[j]) <= r) av[j] = true;
    }
    for(int i = 1; i <= m; ++ i)
        if(av[i]) at[++ tot] = at[i];
    std::sort(up + 1, up + cup + 1);
    std::sort(dw + 1, dw + cdw + 1);
    std::sort(at + 1, at + tot + 1);
    memset(dp, 0x3f, sizeof dp);
    dp[0][0][0] = 0;
    for(int i = 0; i < tot; ++ i){
        for(int j = 0; j <= cup; ++ j){
            for(int k = 0; k <= cdw; ++ k){
                if(j && dist(up[j].p, at[i + 1]) <= r) updmin(dp[i + 1][j][k], dp[i][j][k]);
                for(int l = j + 1; l <= cup; ++ l)
                    if(dist(up[l].p, at[i + 1]) <= r) updmin(dp[i + 1][l][k], dp[i][j][k] + up[l].c);
                if(k && dist(dw[k].p, at[i + 1]) <= r) updmin(dp[i + 1][j][k], dp[i][j][k]);
                for(int l = k + 1; l <= cdw; ++ l)
                    if(dist(dw[l].p, at[i + 1]) <= r) updmin(dp[i + 1][j][l], dp[i][j][k] + dw[l].c);
            }
        }
    }
    int ans = INF;
    for(int i = 0; i <= cup; ++ i)
        for(int j = 0; j <= cdw; ++ j) ans = min(ans, dp[tot][i][j]);
    printf("%d\n%d\n", tot, ans);
    lovely lzy;
}
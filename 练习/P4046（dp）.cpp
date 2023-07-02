#include <bits/stdc++.h>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 205, M = 1e3 + 5, INF = 0x3f3f3f3f;
int n, m;
int dp[N][N], tmp[N][N], dis[N][N], p[M];
int main(){
    n = read();
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++ j) dis[i][j] = read();
    int x;
    while(std::cin >> x) p[++ m] = x;
    memset(dp, 0x3f, sizeof dp);
    p[0] = 3;
    dp[1][2] = dp[2][1] = 0;
    for(int i = 1; i <= m; ++ i){
        memset(tmp, 0x3f, sizeof tmp);
        for(int j = 1; j <= n; ++ j){
            for(int k = 1; k <= n; ++ k){
                tmp[j][k] = min(tmp[j][k], dp[j][k] + dis[p[i - 1]][p[i]]);//j k p[i - 1] -> j k p[i]
                tmp[j][p[i - 1]] = min(tmp[j][p[i - 1]], dp[j][k] + dis[k][p[i]]);//j k p[i - 1] -> j p[i] p[i - 1]
                tmp[p[i - 1]][k] = min(tmp[p[i - 1]][k], dp[j][k] + dis[j][p[i]]);//j k p[i - 1] -> p[i] k p[i - 1]
            }
        }
        for(int j = 1; j <= n; ++ j)
            for(int k = 1; k <= n; ++ k) dp[j][k] = min(tmp[j][k], tmp[k][j]);
    }
    int ans = INF;
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++ j) ans = min(ans, dp[i][j]);
    printf("%d", ans);
    return 0;
}
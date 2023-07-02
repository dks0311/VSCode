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
const int N = 2e5 + 5;
int n, a[N], b[N], dpt[N];
int dp[N][20][2];
main(){
    n = read();
    for(int i = 1; i <= n; ++ i) a[i] = read();
    for(int i = 2; i <= n; ++ i) b[i] = read();
    for(int i = 2; i <= n; ++ i) dpt[i] = dpt[i >> 1] + b[i];
    for(int i = n; i >= 1; -- i){
        if(i << 1 > n){
            for(int j = 1; i >> j || i >> j - 1 == 1; ++ j)
                dp[i][j][0] = (dpt[i] - dpt[i >> j]) * a[i >> j],
                dp[i][j][1] = (dpt[i] + dpt[i >> j - 1 ^ 1] - (dpt[i >> j] << 1)) * a[i >> j - 1 ^ 1];
        }
        else if((i << 1 | 1) > n)
            for(int j = 1; i >> j || i >> j - 1 == 1; ++ j)
                dp[i][j][0] = (dpt[i << 1] - dpt[i]) * a[i << 1] + dp[i << 1][j + 1][0],
                dp[i][j][1] = (dpt[i << 1] - dpt[i]) * a[i << 1] + dp[i << 1][j + 1][1];
        else{
            for(int j = 1; i >> j || i >> j - 1 == 1; ++ j)
                dp[i][j][0] = min((dpt[i << 1 | 1] - dpt[i]) * a[i << 1 | 1] + dp[i << 1 | 1][1][1] + dp[i << 1][j + 1][0], (dpt[i << 1] - dpt[i]) * a[i << 1] + dp[i << 1][1][1] + dp[i << 1 | 1][j + 1][0]),
                dp[i][j][1] = min((dpt[i << 1 | 1] - dpt[i]) * a[i << 1 | 1] + dp[i << 1 | 1][1][1] + dp[i << 1][j + 1][1], (dpt[i << 1] - dpt[i]) * a[i << 1] + dp[i << 1][1][1] + dp[i << 1 | 1][j + 1][1]);
        }
    }
    int ans = 1e18;
    for(int i = 1; i <= n; ++ i){
        int res = dp[i][1][0];
        for(int j = i, u = i >> 1; j >> 1; j >>= 1, u >>= 1){
            if((j ^ 1) <= n)
                res += (dpt[j ^ 1] - dpt[u]) * a[j ^ 1] + dp[j ^ 1][2][0];
            else
                res += (dpt[u] - dpt[u >> 1]) * a[u >> 1];
        }
        ans = min(ans, res);
    }
    printf("%lld", ans);
    return 0;
}
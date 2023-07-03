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
const int N = 305;
int T, n, m, mod;
int dp[N][N], num[N], sum[N], c[N][N];
signed main(){
    T = read();
    while(T --){
        n = read(), m = read(), mod = read();
        for(int i = 0; i <= 300; ++ i){
            c[i][0] = c[i][i] = 1;
            for(int j = 1; j < i; ++ j) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
        memset(num, 0, sizeof num);
        for(int i = 1; i <= m; ++ i){
            int x = read(); x = read();
            ++ num[x];
        }
        sum[n + 1] = 0;
        for(int i = n; i; -- i) sum[i] = sum[i + 1] + num[i];
        bool flag = false;
        for(int i = 1; i <= n; ++ i) if(n - i + 1 < sum[i]){puts("NO"); flag = true; break;}
        if(flag) continue;
        memset(dp, 0, sizeof dp);
        dp[n + 1][0] = 1;
        for(int i = n; i; -- i)
            for(int j = sum[i]; j <= n - i + 1; ++ j)
                for(int k = num[i]; k <= j - sum[i + 1]; ++ k)
                    (dp[i][j] += dp[i + 1][j - k] * c[n - m - j + k + sum[i + 1]][k - num[i]] % mod) %= mod;
        printf("YES %lld\n", dp[1][n]);
    }
    return 0;
}
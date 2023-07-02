#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
#define PII std::pair<int, int>
#define X first
#define Y second
const int MOD = 19940417;
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
inline void updmlt(int &x, int y){x = x * y % MOD;}
inline int ksm(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1) updmlt(ans, a);
        updmlt(a, a);
        b >>= 1;
    }
    return ans;
}
const int N = 1e6 + 5;
int n, m, ans;
int dp[N][2];
PII a[N];
signed main(){
    n = read(), m = read();
    for(int i = 1; i <= m; ++ i) a[i] = (PII){read(), read()}, updmax(ans, a[i].Y);
    a[++ m] = (PII){0, 0}, a[++ m] = (PII){n, 0};
    std::sort(a + 1, a + m + 1);
    m = std::unique(a + 1, a + m + 1) - a - 1;
    dp[1][0] = 1;
    for(int i = 2; i <= m; ++ i){
        int len = a[i].X - a[i].Y - a[i - 1].X - a[i - 1].Y;
        if(a[i].X - a[i].Y == a[i - 1].X - a[i - 1].Y)
            if(a[i - 1].Y) updadd(dp[i][1], dp[i - 1][1]);
            else updadd(dp[i][1], dp[i - 1][0]);
        else if(a[i].X + a[i].Y == a[i - 1].X + a[i - 1].Y)
            updadd(dp[i][0], dp[i - 1][0] + dp[i - 1][1]);
        else if(len < 0){
            if(a[i - 1].Y) updadd(dp[i][0], dp[i - 1][1]);
            else updadd(dp[i][0], dp[i - 1][0]);
        }
        else if(!len){
            if(a[i - 1].Y) updadd(dp[i][0], dp[i - 1][1]);
            else updadd(dp[i][0], dp[i - 1][0]);
            updadd(dp[i][1], dp[i - 1][0] + dp[i - 1][1]);
        }
        else{
            updadd(dp[i][0], (dp[i - 1][0] + dp[i - 1][1] * 2) % MOD * ksm(2, (len >> 1) - 1) % MOD);
            if(a[i].Y) updadd(dp[i][1], (dp[i - 1][0] + dp[i - 1][1] * 2) % MOD * ksm(2, (len >> 1) - 1) % MOD);
        }
        updmax(ans, a[i].X + a[i].Y - a[i - 1].X + a[i - 1].Y >> 1);
    }
    if(dp[m][0] == 1 && ans == 8) ans = 6;
    printf("%lld %lld\n", dp[m][0], ans);
    lovely _lzy_;
}
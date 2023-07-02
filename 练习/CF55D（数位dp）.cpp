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
const int N = 2525;
int T;
int dp[20][N][50], dgt[20], cnt;
int num[50] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};
int _lcm[50][10];
int lzy[N];
int dfs(int pos, int now, int lcm, bool lmt){
    if(!pos) return now % num[lcm] == 0;
    if(!lmt && dp[pos][now][lcm] != -1) return dp[pos][now][lcm];
    int limit = lmt ? dgt[pos] : 9, res = 0;
    for(int i = 0; i <= limit; ++ i)
        res += dfs(pos - 1, (now * 10 + i) % 2520, _lcm[lcm][i], lmt && i == limit);
    if(!lmt) dp[pos][now][lcm] = res;
    return res;
}
int calc(int x){
    cnt = 0;
    while(x) dgt[++ cnt] = x % 10, x /= 10;
    return dfs(cnt, 0, 1, true);
}
main(){
    T = read();
    for(int i = 0; i < 49; ++ i) lzy[num[i]] = i;
    for(int i = 1; i < 49; ++ i)
        for(int j = 0; j < 10; ++ j) _lcm[i][j] = lzy[j ? num[i] * j / std::__gcd(num[i], j) : num[i]];
    memset(dp, -1, sizeof dp);
    while(T --){
        int l = read(), r = read();
        printf("%lld\n", calc(r) - calc(l - 1));
    }
    return 0;
}
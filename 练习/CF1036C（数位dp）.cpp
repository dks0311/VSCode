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
int T;
int dp[20][5], dgt[20], cnt;
int dfs(int pos, int ct, bool lmt){
    if(ct > 3) return 0;
    if(!pos) return 1;
    if(!lmt && dp[pos][ct] != -1) return dp[pos][ct];
    int limit = lmt ? dgt[pos] : 9, res = 0;
    for(int i = 0; i <= limit; ++ i)
        res += dfs(pos - 1, ct + (i > 0), lmt && i == limit);
    if(!lmt) dp[pos][ct] = res;
    return res;
}
int calc(int x){
    cnt = 0;
    while(x) dgt[++ cnt] = x % 10, x /= 10;
    return dfs(cnt, 0, true);
}
main(){
    T = read();
    memset(dp, -1, sizeof dp);
    while(T --){
        int l = read(), r = read();
        printf("%lld\n", calc(r) - calc(l - 1));
    }
    return 0;
}
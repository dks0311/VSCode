#include <bits/stdc++.h>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 2e3 + 5, MOD = 1e9 + 7;
int m, d;
int dp[N][N], dgt[N], cnt;
char s[N];
int dfs(int pos, int now, bool lmt){
    if(!cnt && !d) return 0;
    if(!pos) return now == 0;
    if(!lmt && dp[pos][now] != -1) return dp[pos][now];
    int limit = lmt ? dgt[pos] : 9, res = 0;
    if(cnt - pos & 1){
        if(d <= limit) res = dfs(pos - 1, (now * 10 + d) % m, lmt && d == limit);
    }
    else{
        for(int i = 0; i <= limit; ++ i)
            if(i != d && (pos != cnt || i)) (res += dfs(pos - 1, (now * 10 + i) % m, lmt && i == limit)) %= MOD;
    }
    if(!lmt) dp[pos][now] = res;
    return res;
}
int main(){
    m = read(), d = read();
    memset(dp, -1, sizeof dp);
    scanf("%s", s + 1);
    cnt = strlen(s + 1);
    for(int i = 1; i <= cnt; ++ i) dgt[i] = s[cnt - i + 1] - '0';
    -- dgt[1];
    for(int i = 1; i < cnt; ++ i)
        if(dgt[i] < 0) dgt[i] += 10, -- dgt[i + 1];
        else break;
    int res = dfs(cnt, 0, true);
    scanf("%s", s + 1);
    cnt = strlen(s + 1);
    for(int i = 1; i <= cnt; ++ i) dgt[i] = s[cnt - i + 1] - '0';
    res = (dfs(cnt, 0, true) - res + MOD) % MOD;
    printf("%d\n", res);
    return 0;
}
#include <bits/stdc++.h>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 1e3 + 5, MOD = 1e9 + 7;
int dp[N][11][11][2][2], dgt[N], cnt;
char s[N];
int dfs(int pos, int a, int b, int ok, int start, bool lmt){
    if(!pos) return ok;
    if(!lmt && dp[pos][a][b][ok][start] != -1) return dp[pos][a][b][ok][start];
    int limit = lmt ? dgt[pos] : 9, res = 0;
    for(int i = 0; i <= limit; ++ i)
        if(start || i) (res += dfs(pos - 1, b, i, ok || i == b || i == a, 1, lmt && i == limit)) %= MOD;
        else (res += dfs(pos - 1, a, b, 0, 0, lmt && i == lmt)) %= MOD;
    if(!lmt) dp[pos][a][b][ok][start] = res;
    return res;
}
int main(){
    memset(dp, -1, sizeof dp);
    scanf("%s", s + 1);
    cnt = strlen(s + 1);
    for(int i = 1; i <= cnt; ++ i) dgt[i] = s[cnt - i + 1] - '0';
    -- dgt[1];
    for(int i = 1; i < cnt; ++ i) if(dgt[i] < 0) dgt[i] += 10, -- dgt[i + 1]; else break;
    if(!dgt[cnt]) -- cnt;
    int res = dfs(cnt, 10, 10, 0, 0, true);
    scanf("%s", s + 1);
    cnt = strlen(s + 1);
    for(int i = 1; i <= cnt; ++ i) dgt[i] = s[cnt - i + 1] - '0';
    res = (dfs(cnt, 10, 10, 0, 0, true) - res + MOD) % MOD;
    printf("%lld", res);
    return 0;
}
#include <bits/stdc++.h>
#define int long long
#define PII std::pair<int, int>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 1 << 10 | 5, MOD = 998244353;
int l, r, k;
int dp[20][N], ct[20][N], dgt[20], cnt, num[20], cntt[N];
PII dfs(int pos, int state, bool lmt){
    if(!pos) return (PII){0, 1};
    if(!lmt && ct[pos][state] != -1) return (PII){dp[pos][state], ct[pos][state]};
    int limit = lmt ? dgt[pos] : 9, sum = 0, res = 0;
    for(int i = 0; i <= limit; ++ i){
        if(cntt[state | 1 << i] > k) continue;
        PII tmp = dfs(pos - 1, !state && !i ? state : state | 1 << i, lmt && i == limit);
        (sum += (tmp.first + i * num[pos - 1] * tmp.second % MOD) % MOD) %= MOD, (res += tmp.second) %= MOD;
    }
    if(!lmt) dp[pos][state] = sum, ct[pos][state] = res;
    return (PII){sum, res};
}
int calc(int x){
    cnt = 0;
    while(x) dgt[++ cnt] = x % 10, x /= 10, num[cnt] = num[cnt - 1] * 10 % MOD;
    return dfs(cnt, 0, true).first;
}
main(){
    l = read(), r = read(), k = read();
    num[0] = 1;
    memset(ct, -1, sizeof ct);
    for(int i = 0; i < 1 << 10; ++ i){
        int x = i;
        while(x) cntt[i] += x & 1, x >>= 1;
    }
    printf("%lld\n", (calc(r) - calc(l - 1) + MOD) % MOD);
    return 0;
}
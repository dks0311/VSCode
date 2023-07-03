#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
const int MOD = 1e9 + 7;
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
inline void updadd(int &x, int y){(x += y) %= MOD;}
inline void updmlt(int &x, int y){x = x * y % MOD;}
const int N = 1e5 + 5;
int n, l, r;
int dp[20][N], dgt[20], cnt;
std::vector<int> v;
char s[15];
bool ac[15];
int dfs(int pos, int now, bool lmt, bool start){
    if(!pos) return !now;
    if(!lmt && start && dp[pos][now] != -1) return dp[pos][now];
    int limit = lmt ? dgt[pos] : 9, res = 0;
    if(!start && v[0]) res += dfs(pos - 1, 0, lmt && limit == 0, false);
    for(int i = 0; i < v.size() && v[i] <= limit; ++ i)
        res += dfs(pos - 1, (now * 10 + v[i]) % n, lmt && v[i] == limit, start || v[i] > 0);
    if(!lmt && start) dp[pos][now] = res;
    return res;
}
inline int calc(int x){
    cnt = 0;
    while(x) dgt[++ cnt] = x % 10, x /= 10;
    return dfs(cnt, 0, true, false);
}
signed main(){
    n = read(), l = read(), r = read();
    scanf("%s", s); int len = strlen(s);
    std::sort(s, s + len);
    for(int i = 0; i < len; ++ i){v.push_back(s[i] - '0'); ac[s[i] - '0'] = true;}
    if(n <= 100000){
        memset(dp, -1, sizeof dp);
        printf("%lld\n", calc(r) - calc(l - 1));
    }
    else{
        int ans = 0;
        for(int i = 1; i * n <= r; ++ i){
            if(i * n < l) continue;
            int x = i * n; bool flag = true;
            while(x){
                if(!ac[x % 10]){flag = false; break;}
                x /= 10;
            }
            if(flag) ++ ans;
        }
        printf("%lld\n", ans);
    }
    lovely _lzy_;
}
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
const int N = 505, MOD = 999911659;
int n, p, T, g[N], dp[10][N], t[10][N], pos[N], ad, st_pos, st_value;
inline int ksm(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}
inline int c(int n, int m){
    int res_fz = 1, res_fm = 1;
    for(int i = n; i > n - m; -- i) res_fz = i % MOD * res_fz % MOD;
    for(int i = 2; i <= m; ++ i) (res_fm *= i % MOD) %= MOD;
    return res_fz * ksm(res_fm, MOD - 2) % MOD;
}
signed main(){
    n = read(), p = read();
    if(p == 1){printf("%lld\n", c(n + 9 - 1, 9 - 1)); return 0;}
    for(int i = 1, now = 1; i <= p << 1; ++ i, now = (now * 10 + 1) % p){
        if(pos[(now * 10 + 1) % p]) ad = now;
        if(pos[now]){T = i - pos[now], st_pos = pos[now], st_value = now; break;}
        pos[now] = i;
    }
    for(int i = 1, now = st_value; i <= T; ++ i, now = (now * 10 + 1) % p) g[now] = 1;
    for(int i = 0; i < p; ++ i) g[i] = g[i] * (int)((n - st_pos + 1ll) / T);
    for(int i = 1, now = st_value; i <= (n - st_pos + 1) % T; ++ i, now = (now * 10 + 1) % p){
        if((n - st_pos + 1) % T == i) ad = now;
        ++ g[now];
    }
    for(int i = 0, now = 0; i < st_pos; ++ i, now = (now * 10 + 1) % p) ++ g[now];
    dp[0][ad] = 1;
    for(int i = 0; i < p; ++ i){
        memcpy(t, dp, sizeof t);
        for(int l = 1; l <= 8; ++ l){
            int tmp = c(g[i] + l - 1, l);
            for(int j = 0; j + l <= 8; ++ j){
                for(int k = 0; k < p; ++ k){
                    (dp[j + l][(k + i * l) % p] += t[j][k] * tmp % MOD) %= MOD;
                }
            }
        }
    }
    printf("%lld\n", dp[8][0]);
    return 0;
}
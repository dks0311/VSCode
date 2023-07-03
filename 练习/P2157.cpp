/*
author: 牛肉爱吃dks
starting time: 2023.06.08 14:18:50
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define LL long long
#define int long long
#define DB double
#define PII std::pair<int, int>
#define X first
#define Y second
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
#define uf(i, x, y) for(int i = (x); i < (y); ++ i)
#define dF(i, x, y) for(int i = (x); i >= (y); -- i)
#define df(i, x, y) for(int i = (x); i > (y); -- i)
#define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
#define init(x, y) memset(x, y, sizeof x)
#define copy(x, y) memcpy(x, y, sizeof x)
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void read(T &x){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    x = f ? ~s + 1 : s;
}
template<typename T> inline void write(T x, const char *s){
    static int st[40]; int top = 0;
    if(x < 0){putchar('-'); x = -x;}
    if(!x) putchar('0');
    while(x) st[++ top] = x % 10, x /= 10;
    while(top) putchar(st[top --] + 48);
    printf("%s", s);
}
template<typename T> inline T max(T x, T y){return x > y ? x : y;}
template<typename T> inline T min(T x, T y){return x < y ? x : y;}
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 1e3 + 5, INF = 0x3f3f3f3f;
int T, n;
int t[N], b[N];
int dp[N][260][20];
signed main(){
    T = read<int>();
    while(T --){
        n = read<int>();
        uF(i, 1, n) t[i] = read<int>(), b[i] = read<int>();
        uF(i, 1, n) if(i + b[i] > n) b[i] = n - i;
        init(dp, 0x3f);
        dp[1][0][7] = 0;
        uF(i, 1, n) uf(s, 0, 1 << 8) uF(j, -8, 7){
            int tmp = dp[i][s][j + 8];
            if(s & 1) updmin(dp[i + 1][s >> 1][j - 1 + 8], tmp);
            else{
                int mn = INF;
                uF(k, 0, 7){
                    if(s >> k & 1) continue;
                    if(i + k > mn) break;
                    updmin(mn, i + k + b[i + k]);
                    updmin(dp[i][s | 1 << k][k + 8], tmp + (i + j ? t[i + j] ^ t[i + k] : 0));
                }
            }
        }
        int res = INF;
        uF(i, -8, -1) updmin(res, dp[n + 1][0][i + 8]);
        printf("%d\n", res);
    }
    lovely _lzy_;
}
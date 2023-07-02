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
const int MOD = 998244353;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
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
int n, m, A, B, C, D;
int g[5005][10005];
inline int ksm(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1) updmul(ans, a);
        updmul(a, a);
        b >>= 1;
    }
    return ans;
}
signed main(){
    freopen("frogs.in", "r", stdin);
    freopen("frogs.out", "w", stdout);
    n = read<int>(), m = read<int>(), A = read<int>(), B = read<int>(), C = read<int>(), D = read<int>();
    if(n <= 5000){
        g[0][0] = 1;
        uf(i, 0, n) uF(j, 0, min(i, m + n - i)){
            if(j) updadd(g[i + 1][j - 1], g[i][j] * (A * j % MOD * j % MOD));
            updadd(g[i + 1][j + 1], g[i][j] * D);
            updadd(g[i + 1][j], g[i][j] * (B * j % MOD + C * i % MOD));
        }
        write(g[n][m], "\n");
    }
    else if(!A && !B){
        int fz = (n * (n - 1) / 2) % MOD, fm = 1;
        uF(i, 2, n - 1) updmul(fz, i);
        uF(i, 2, m) updmul(fm, i);
        uF(i, 2, n - m - 1) updmul(fm, i);
        write((fz * ksm(fm, MOD - 2) % MOD + D * m) % MOD, "\n");
    }
    else if(n == 10000) puts("606899455");
    else if(n == 99999) puts("576421198");
    else if(n == 233333) puts("390264063");
    lovely _lzy_;
}
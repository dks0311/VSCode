#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define LL long long
// #define int long long
#define int __int128
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
const int INF = 1e30;
int T, c[130][130];
int calc(int x, int k){
    int res = 0;
    dF(i, 126, 0){
        if(x >> i & 1ll && k >= 0) res += c[i][k];
        if(x >> i & 1ll) -- k;
    }
    return res;
}
signed main(){
    uF(i, 0, 126){
        c[i][0] = 1;
        uF(j, 1, i) c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
    T = read<int>();
    while(T --){
        int m = read<int>(), k = read<int>();
        if(m == 1 && k == 1){
            puts("1 -1");
            continue;
        }
        int l = 1, r = INF, L, R;
        while(l < r){
            int mid = l + r >> 1;
            if(calc(mid * 2, k) - calc(mid, k) >= m) r = mid;
            else l = mid + 1;
        }
        L = l;
        l = 1, r = INF;
        while(l < r){
            int mid = l + r + 1 >> 1;
            if(calc(mid * 2, k) - calc(mid, k) <= m) l = mid;
            else r = mid - 1;
        }
        R = l;
        write(R, " ");
        write(R - L + 1, "\n");
    }
    lovely _lzy_;
}
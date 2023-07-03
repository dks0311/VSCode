#include <bits/stdc++.h>
namespace _default{
    using namespace std;
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
    #define sett(x, y) memset(x, y, sizeof x)
    #define copy(x, y) memcpy(x, y, sizeof x)
    const int MOD = 1e9 + 7;
    const DB EPS = 1e-8;
    template<typename T> inline T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> inline void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0){putchar('-'); x = -x;}
        if(!x) putchar('0');
        while(x) st[++ top] = x % 10, x /= 10;
        while(top) putchar(st[top --] + 48);
        printf("%s", s);
    }
    template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
    template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
    template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
    template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
const int N = 2e5 + 5;
const DB le10 = log(10);
int n, m, a[N];
DB b[N];
DB t[N];
inline void Add(int x, DB y){for(; x <= n; x += x & -x) t[x] += y;}
inline DB Query(int x){
    DB res = 0;
    for(; x; x -= x & -x) res += t[x];
    return res;
}
int Calc(DB x){
    // printf("%.3lf\n", exp(x));
    DB t = floor(x / le10 + 1e-8);
    // printf("%.3lf\n", t);
    // printf("ans:");
    return (int)(exp(x - t * le10) + 1e-8);
}
signed main(){
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    n = read<int>(), m = read<int>();
    uF(i, 1, n) a[i] = read<int>(), b[i] = log(a[i]);
    if(n <= 1000 && m <= 1000){
        while(m --){
            int opt = read<int>(), l = read<int>(), r = read<int>();
            if(opt == 1){
                int t = read<int>();
                if(t) sort(b + l, b + r + 1);
                else sort(b + l, b + r + 1, [](DB a, DB b){return a > b;});
            }
            else{
                DB res = 0;
                uF(i, l, r) res += b[i];
                write(Calc(res), "\n");
            }
        }
    }
    else{
        uF(i, 1, n) Add(i, b[i]);
        while(m --){
            int opt = read<int>(), l = read<int>(), r = read<int>();
            write(Calc(Query(r) - Query(l - 1)), "\n");
        }
    }
    lovely _lzy_;
}
/*
10 11
1 5 10 3 9 2 8 6 4 7
2 5 8
1 1 3 0
2 2 6
1 6 8 1
2 1 10
2 4 9
1 2 5 0
1 4 8 1
1 3 6 0
2 1 10
2 3 8
*/
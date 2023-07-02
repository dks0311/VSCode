#include <bits/stdc++.h>
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
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 5e3 + 5;
int n, m, km;
PII opt[N], g[N];
int f[N], ans[N];
bool del[N];
signed main(){
    n = read<int>(), m = read<int>(), km = read<int>();
    uF(i, 1, n) g[i].X = read<int>(), g[i].Y = read<int>();
    uF(i, 1, m){
        opt[i].X = read<int>(), opt[i].Y = read<int>();
        if(opt[i].X == 1) del[opt[i].Y] = true;
    }
    uF(i, 1, n){
        if(del[i]) continue;
        dF(j, km, g[i].X * g[i].Y)
            updmax(f[j], f[j - g[i].X * g[i].Y] + g[i].Y);
    }
    memset(ans, -1, sizeof ans);
    dF(i, m, 1){
        if(opt[i].X == 2) ans[i] = f[opt[i].Y];
        else{
            int k = opt[i].Y;
            dF(j, km, g[k].X * g[k].Y)
                updmax(f[j], f[j - g[k].X * g[k].Y] + g[k].Y);
        }
    }
    uF(i, 1, m) if(ans[i] != -1) write(ans[i], "\n");
    lovely _lzy_;
}
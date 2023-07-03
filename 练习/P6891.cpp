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
    const DB EPS = 1e-8, INF = 0x3f3f3f3f;
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
const int N = 1e6 + 5;
int n, m, a[N], b[N], ans[N];
PII f[N][2];
signed main(){
    n = read<int>(), m = n << 1;
    uF(i, 1, m) a[i] = read<int>();
    uF(i, 1, m) b[i] = read<int>();
    f[1][0] = {1, 1}, f[1][1] = {0, 0};
    uF(i, 2, m){
    	f[i][0] = f[i][1] = {INF, -INF};
    	if(a[i] >= a[i - 1]) updmin(f[i][0].X, f[i - 1][0].X), updmax(f[i][0].Y, f[i - 1][0].Y);
    	if(a[i] >= b[i - 1]) updmin(f[i][0].X, f[i - 1][1].X), updmax(f[i][0].Y, f[i - 1][1].Y);
    	if(b[i] >= a[i - 1]) updmin(f[i][1].X, f[i - 1][0].X), updmax(f[i][1].Y, f[i - 1][0].Y);
    	if(b[i] >= b[i - 1]) updmin(f[i][1].X, f[i - 1][1].X), updmax(f[i][1].Y, f[i - 1][1].Y);
    	++ f[i][0].X, ++ f[i][0].Y;
	}
	int cur = n, cs = INF;
	dF(i, m, 1){
		if(f[i][0].X <= cur && f[i][0].Y >= cur && a[i] <= cs) -- cur, cs = a[i];
		else if(f[i][1].X <= cur && f[i][1].Y >= cur && b[i] <= cs) ans[i] = 1, cs = b[i];
		else{
			puts("-1");
			return 0;
		}
	}
	uF(i, 1, m) putchar(ans[i] ? 'B' : 'A');
	puts("");
    lovely _lzy_;
}

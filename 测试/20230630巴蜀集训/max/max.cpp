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
    const int MOD = 1e9 + 7, INF = 1e18;
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
const int N = 1 << 11 | 5;
int n, m, c, ans, maxn;
int p[45][15][5];
int dp[45][N][35], f[45][N][35];
vector<int> sub[N];
signed main(){
//	freopen("max.in", "r", stdin);
//	freopen("max.out", "w", stdout);
	n = read<int>(), m = read<int>(), c = read<int>(); maxn = m * c;
	uf(i, 0, m) uF(j, 1, n) uF(k, 0, c) p[j][i][k] = read<int>();
	uF(i, 1, n) f[i][0][0] = 1;
	uF(i, 1, n) uf(s, 1, 1 << m)
		dF(j, m - 1, 0) if(s >> j & 1){
			uF(k, 0, maxn - c) uF(l, 0, c)
			updadd(f[i][s][k + l], f[i][s ^ 1 << j][k] * p[i][j][l]);
			break;
		}
	uF(i, 1, n) uF(s, 0, 1 << m) uF(j, 1, maxn) updadd(f[i][s][j], f[i][s][j - 1]);
	uf(i, 0, 1 << m) uF(j, 0, i) if((i | j) == i) sub[i].push_back(j);
	uF(i, 0, maxn) dp[0][0][i] = 1;
	uF(i, 1, n) uf(s, 0, 1 << m) for(auto ss : sub[s])
		uF(j, 0, maxn) updadd(dp[i][s][j], dp[i - 1][s ^ ss][j] * f[i][ss][j]);
	uF(i, 1, maxn) updadd(ans, (dp[n][(1 << m) - 1][i] - dp[n][(1 << m) - 1][i - 1] + MOD) * i);
	write(ans);
    lovely _lzy_;
}

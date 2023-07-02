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
const int N = 2005, M = 1e7;
int n, m, k;
int mu[M + 10], sm[M + 10], kk[M + 10], tot;
bool Not_Prime[M + 10];
vector<int> p;
unordered_map<int, int> ttm;
struct lzy{
	int n, m, k;
	friend bool operator < (const lzy &a, const lzy &b){
		if(a.n != b.n) return a.n < b.n;
		else if(a.m != b.m) return a.m < b.m;
		else return a.k < b.k;
	}
};
map<lzy, int> ans;
void xxs(){
	mu[1] = 1;
	uF(i, 2, M){
		if(!Not_Prime[i]){
			p.push_back(i);
			mu[i] = -1;
		}
		for(auto j : p){
			if(i * j > M) break;
			Not_Prime[i * j] = true;
			if(i % j == 0) break;
			mu[i * j] = -mu[i];
		}
	}
	uF(i, 1, M) sm[i] = sm[i - 1] + mu[i];
}
int getmu(int n){
    if(n <= M) return sm[n];
    if(ttm.count(n)) return ttm[n];
    long long res = 1;
    for(int l = 2, r; l <= n; l = r + 1){
        r = n / (n / l);
        res -= 1ll * (r - l + 1) * getmu(n / l);
    }
    return ttm[n] = res;
}
inline int g(int x, int n){
	return (int)n / (int)(n / x);
}
int Calc(int n, int m, int k){
	if(!n || !m) return 0;
	lzy tmp = (lzy){n, m, k};
	if(ans.count(tmp)) return ans[tmp];
	int res = 0;
	if(k == 1){
		int maxn = min(n, m);
		for(int l = 1, r; l <= maxn; l = r + 1){
			r = min(maxn, min(n / (n / l), m / (m / l)));
			res += (getmu(r) - getmu(l - 1)) * (n / l) * (m / l);
		}
		ans[(lzy){m, n, k}] = res;
	}
	else for(int i = 1; i <= tot && kk[i] <= k; ++ i) if(k % kk[i] == 0)
		res += Calc(m / kk[i], n, kk[i]) * mu[kk[i]];
	return ans[tmp] = res;
}
signed main(){
	freopen("cyclic.in", "r", stdin);
	freopen("cyclic.out", "w", stdout);
	n = read<int>(), m = read<int>(), k = read<int>();
	xxs();
	uF(i, 1, k) if(k % i == 0) kk[++ tot] = i;
	write(Calc(n, m, k));
    lovely _lzy_;
}

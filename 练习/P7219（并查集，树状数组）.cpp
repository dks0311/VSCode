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
const int N = 2e5 + 5;
struct DSU{
	int fa[N];
	inline void Init(int n){uF(i, 1, n + 1) fa[i] = i;}
	int Get_Father(int u){return u == fa[u] ? u : (fa[u] = Get_Father(fa[u]));}
	inline void Merge(int u, int v){fa[Get_Father(u)] = Get_Father(v);}
}lt, rt;
int n, m, ans;
vector<PII> star[N];
vector<int> boat[N];
int t[N];
inline void Add(int x, int y){for(; x <= n; x += x & -x) t[x] += y;}
inline int Query(int x){int res = 0; for(; x; x -= x & -x) res += t[x]; return res;}
signed main(){
	n = read<int>();
	uF(i, 1, n){
		int x = read<int>();
		boat[x].push_back(i);
	}
	m = read<int>();
	uF(i, 1, m){
		int x = read<int>(), y = read<int>(), c = read<int>();
		star[y].push_back({x, c});
	}
	lt.Init(n), rt.Init(n);
	uF(i, 1, n){
		for(auto p : star[i]){
			int tmp = Query(p.X);
			if(tmp >= p.Y) ans += p.Y;
			else{
				ans += tmp;
				Add(lt.Get_Father(p.X) + 1, p.Y - tmp);
				Add(rt.Get_Father(p.X), tmp - p.Y);
			}
		}
		for(auto x : boat[i])
			lt.fa[x] = x - 1, rt.fa[x]  = x + 1;
	}
	write(ans, "\n");
    lovely _lzy_;
}

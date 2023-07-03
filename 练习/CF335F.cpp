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
const int N = 5e5 + 5;
struct Pie{
	int w, cnt;
	Pie(int _w = 0, int _cnt = 0) : w(_w), cnt(_cnt){}
}p[N];
int n, a[N], tot;
int st[N], top;
signed main(){
	n = read<int>();
	int sum = 0, res = 0;
	uF(i, 1, n) a[i] = read<int>(), res += a[i];
	sort(a + 1, a + n + 1, [](int a, int b){return a > b;});
	for(int i = 1, cnt = 1; i <= n; ++ i, ++ cnt)
		if(a[i] != a[i + 1]) p[++ tot] = Pie(a[i], cnt), cnt = 0;
	priority_queue<int, vector<int>, greater<int> > q;
	uF(i, 1, tot){
		int tmp = min(p[i].cnt, sum - 1ll * (int)q.size() * 2);
		uF(j, 1, tmp) st[++ top] = p[i].w;
		tmp = min(sum, p[i].cnt) - tmp;
		for(int j = 1; j <= tmp; j += 2){
			int w = q.top(); q.pop();
			if(p[i].w > w){
				st[++ top] = p[i].w;
				if(j < tmp) st[++ top] = p[i].w;
			}
			else{
				st[++ top] = w;
				if(1ll * p[i].w * 2 > w && j < tmp)
					st[++ top] = 1ll * p[i].w * 2 - w;
			}
		}
		while(top) q.push(st[top --]);
		sum += p[i].cnt; 
	}
	while(!q.empty()) res -= q.top(), q.pop();
	write(res);
    lovely _lzy_;
}

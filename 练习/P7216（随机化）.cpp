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
struct Meat{
	int x1, y1, x2, y2;
	Meat(int _x1 = 0, int _y1 = 0, int _x2 = 0, int _y2 = 0) : x1(_x1), y1(_y1), x2(_x2), y2(_y2){}
};
Meat a[N], b[5];
int n, k;
Meat jiao(Meat a, Meat b){
	Meat res;
	res = Meat(max(a.x1, b.x1), max(a.y1, b.y1), min(a.x2, b.x2), min(a.y2, b.y2));
	if(res.x1 > res.x2 || res.y1 > res.y2) return Meat();
	return res;
}
signed main(){
	srand(time(0));
	n = read<int>(), k = read<int>();
	uF(i, 1, n)
		a[i].x1 = read<int>(), a[i].y1 = read<int>(),
		a[i].x2 = read<int>(), a[i].y2 = read<int>();
	uF(i, 1, n) swap(a[i], a[rand() % n + 1]);
	while(true){
		uF(i, 1, k) b[i] = a[i];
		bool ff = true;
		uF(i, k + 1, n){
			bool flag = false;
			uF(j, 1, k){
				Meat t = jiao(a[i], b[j]);
				if(t.x1){b[j] = t, flag = true; break;}
			}
			if(!flag){swap(a[i], a[rand() % (i - 1) + 1]); ff = false; break;}
		}
		if(ff) break;
	}
	uF(i, 1, k) printf("%d %d\n", b[i].x1, b[i].y1);
    lovely _lzy_;
}

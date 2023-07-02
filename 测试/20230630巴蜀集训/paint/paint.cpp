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
const int N = 2e5 + 5;
int n, m, k, ans;
PII p[N];
int xx[N], sx;
vector<PII> pu[N], pd[N];
struct Segment_Tree{
	struct Node{
		int l, r, mx, cov;
	};
	inline void Cov(int p, int x){
		tr[p].mx = tr[p].Cov = x;
	}
	inline void Pushdown(int p){
		if(tr[p].cov != -1){
			Cov(p << 1, tr[p].cov);
			Cov(p << 1 | 1, tr[p].cov);
			tr[p].cov = -1;
		}
	}
	inline void pushup(int p){
		tr[p].mx = max(tr[p << 1].mx, tr[p << 1 | 1].mx);
	}
	void Build(int l, int r, int p){
		tr[p].l = l, tr[p].r = r;
		if(l == r) return;
		int mid = l + r >> 1;
		Build(l, mid, p << 1);
		Build(mid + 1, r, p << 1 | 1);
	}
	inline void Section_Modify_Cov(int l, int r, int p, int x){
		if(l <= tr[p].l && tr[p].r <= r){Cov(p, x); return;}
		Pushdown(p);
		int mid = tr[p].l + tr[p].r >> 1;
		if(l <= mid) Section_Modify_Cov(l, r, p << 1, x);
		if(r > mid) Section_Modify_Cov(l, r, p << 1 | 1, x);
		Pushup(p);
	}
};
signed main(){
//	freopen("paint.in", "r", stdin);
//	freopen("painr.out", "w", stdout);
	srand(time(0));
	n = read<int>(), m = read<int>(), k = read<int>();
	uF(i, 1, k) p[i].X = xx[i] = read<int>(), p[i].Y = read<int>();
	
	uF(i, 1, k)
		if(p[i].Y <= m >> 1) pd.push_back(p[i]);
		else pu.push_back(p[i]);
	sort(xx + 1, xx + k + 1);
	sx = unique(xx + 1, xx + k + 1) - xx - 1;
	sort(p + 1, p + k + 1);
	k = unique(p + 1, p + k + 1) - p - 1;
	Build(1, sx, 1);
	uF(i, 1, sx){
		
	}
    lovely _lzy_;
}

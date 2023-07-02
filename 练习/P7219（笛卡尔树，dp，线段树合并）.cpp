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
int n, m, a[N];
int son[N][2], rt[N], st[N], top;
vector<PII> star[N];
struct Segment_Tree{
	struct node{
		int ls, rs, mx, add;
		node(){ls = rs = mx = add = 0;}
	}tr[N * 20];
	int idx;
	Segment_Tree(){idx = 0;}
	inline void Pushup(int u){
		tr[u].mx = max(tr[tr[u].ls].mx, tr[tr[u].rs].mx);
	}
	inline void Add(int u, int x){
		tr[u].mx += x, tr[u].add += x;
	}
	inline void Pushdown(int u){
		if(tr[u].add){
			Add(tr[u].ls, tr[u].add);
			Add(tr[u].rs, tr[u].add);
			tr[u].add = 0;
		}
	}
	inline void Section_Add(int l, int r, int L, int R, int u, int x){
		if(L <= l && r <= R){
			Add(u, x);
			return;
		}
		Pushdown(u);
		int mid = l + r >> 1;
		if(L <= mid) Section_Add(l, mid, L, R, tr[u].ls, x);
		if(R > mid) Section_Add(mid + 1, r, L, R, tr[u].rs, x);
		Pushup(u);
	}
	inline int Merge(int l, int r, int u, int v){
		if(!u || !v) return u + v;
		updmax(tr[u].mx, tr[v].mx);
		Pushdown(u); Pushdown(v);
		int mid = l + r >> 1;
		tr[u].ls = Merge(l, mid, tr[u].ls, tr[v].ls);
		tr[u].rs = Merge(mid + 1, r, tr[u].rs, tr[v].rs);
		Pushup(u);
		return u;
	}
	inline int Section_Query(int l, int r, int L, int R, int u){
//		printf("%d %d %d %d\n", l, r, L, R);
//		return 0;
		if(L <= l && r <= R) return tr[u].mx;
		Pushdown(u);
		int mid = l + r >> 1, res = 0;
		if(L <= mid) updmax(res, Section_Query(l, mid, L, R, tr[u].ls));
		if(R > mid) updmax(res, Section_Query(mid + 1, r, L, R, tr[u].rs));
		return res;
	}
	inline void Insert(int l, int r, int &u, int x, int y){
		if(!u) u = ++ idx;
		if(l == r){
			updmax(tr[u].mx, y);
			return;
		}
		Pushdown(u);
		int mid = l + r >> 1;
		if(x <= mid) Insert(l, mid, tr[u].ls, x, y);
		else Insert(mid + 1, r, tr[u].rs, x, y);
		Pushup(u);
	}
}lzy;
inline int Merge(int u, int v, int h){
	if(!u || !v) return u + v;
	int vu = lzy.Section_Query(1, n, 1, h, u);
	int vv = lzy.Section_Query(1, n, 1, h, v);
	lzy.Section_Add(1, n, h + 1, n, u, vv);
	lzy.Section_Add(1, n, h + 1, n, v, vu);
	vu = lzy.Section_Query(1, n, 1, h, u);
	vv = lzy.Section_Query(1, n, 1, h, v);
	int rt = lzy.Merge(1, n, u, v);
	lzy.Insert(1, n, rt, h, vu + vv);
	return rt;
}
void DFS(int u){
//	printf("1   %d\n", u);
	if(!u) return;
	DFS(son[u][0]);
	DFS(son[u][1]);
	for(auto x : star[u])
		lzy.Insert(1, n, rt[u], x.X, x.Y);
	rt[u] = Merge(rt[u], rt[son[u][0]], a[u]);
//	printf("2   %d\n", u);
	rt[u] = Merge(rt[u], rt[son[u][1]], a[u]);
}
signed main(){
	n = read<int>();
	int sum = 0;
	uF(i, 1, n) a[i] = read<int>();
	m = read<int>();
	uF(i, 1, m){
		int x = read<int>(), y = read<int>(), c = read<int>();
		star[x].push_back({y, c}); sum += c;
	}
	uF(i, 1, n){
		while(top && a[st[top]] < a[i]) -- top;
		son[i][0] = son[st[top]][1], son[st[top]][1] = i, st[++ top] = i;
	}
//	uF(i, 1, top) printf("%d ", st[i]);
//	puts("");
//	uF(i, 0, n) printf("%d: %d %d\n", i, son[i][0], son[i][1]);
	DFS(son[0][1]);
//	puts("114514");
	write(sum - lzy.Section_Query(1, n, 1, n, rt[son[0][1]]));
    lovely _lzy_;
}

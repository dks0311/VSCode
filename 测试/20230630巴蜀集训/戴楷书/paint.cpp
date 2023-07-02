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
int xx[N];
PII p[N];
vector<int> pp[N];
priority_queue<int> q, del;
struct Node{
	int ls, rs, key, val;
	Node(int _key = 0, int _val = 0) : ls(0), rs(0), key(_key), val(_val){}
}tr[N];
int idx, root;
inline int New_Node(int val){
	tr[++ idx] = Node(rand(), val);
	return idx;
}
inline void Split(int val, int p, int &u, int &v){
	if(!p) u = v = 0;
	else{
		if(tr[p].val <= val){
			u = p;
			Split(val, tr[p].rs, tr[u].rs, v);
		}
		else{
			v = p;
			Split(val, tr[p].ls, u, tr[v].ls);
		}
	}
	
}
inline int Merge(int u, int v){
	if(!u || !v) return u + v;
	if(tr[u].key > tr[v].key){
		tr[u].rs = Merge(tr[u].rs, v);
		return u;
	}
	else{
		tr[v].ls = Merge(u, tr[v].ls);
		return v;
	}
}
inline int Get_Prev(int val){
	int u, v; Split(val - 1, root, u, v);
	int p = u;
	while(tr[p].rs) p = tr[p].rs;
	int res = tr[p].val;
	root = Merge(u, v);
	return res;
}
inline int Get_Next(int val){
	int u, v; Split(val, root, u, v);
	int p = v;
	while(tr[p].ls) p = tr[p].ls;
	int res = tr[p].val;
	root = Merge(u, v);
	return res;
}
inline void Insert(int val){
//	puts("114514");
//	printf("root:%d\n", root);
	int u, v, w; Split(val, root, u, w); Split(val - 1, u, u, v);
	if(!v && val && val != m){
		root = Merge(u, Merge(v, w));
		int x = Get_Next(val), y = Get_Prev(val);
		del.push(x - y);
		q.push(x - val); q.push(val - y);
		Split(val, root, u, w); Split(val - 1, u, u, v);
	}
	root = Merge(Merge(u, v), Merge(New_Node(val), w));
}
signed main(){
	freopen("paint.in", "r", stdin);
	freopen("painr.out", "w", stdout);
	srand(time(0));
	n = read<int>(), m = read<int>(), k = read<int>();
	uF(i, 1, k) p[i].X = xx[i] = read<int>(), p[i].Y = read<int>();
	sort(xx + 1, xx + k + 1);
	int sx = unique(xx + 1, xx + k + 1) - xx - 1;
	uF(i, 1, k) pp[lower_bound(xx + 1, xx + sx + 1, p[i].X) - xx].push_back(p[i].Y);
	sort(p + 1, p + k + 1);
	k = unique(p + 1, p + k + 1) - p - 1;
	xx[sx + 1] = n;
	uF(l, 1, sx){
		uF(i, 0, idx) tr[i] = Node();
		root = idx = 0;
		Insert(0); Insert(m);
//		printf("l:%d", l);
		uF(r, l, sx){
//			printf("%d %d\n", l, r);
//			printf("l:%d r:%d\n", xx[l], xx[r]);
			for(auto ppp : pp[r]) Insert(ppp);
			while(q.top() == del.top()) q.pop(), del.pop();
			updmax(ans, xx[r + 1] - xx[l - 1] + q.top());
		}
	}
	write(ans * 2);
    lovely _lzy_;
}

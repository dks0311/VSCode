#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int s = 0, f = 0; char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
	while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
	return f ? ~s + 1 : s;
}
inline void write(int x, const char *s = ""){
	static int st[55]; int top = 0;
	if(x < 0) x = -x, putchar('-');
	if(!x) putchar('0');
	while(x) st[++ top] = x % 10, x /= 10;
	while(top) putchar(st[top --] + 48);
}
#define PII pair<int, int>
#define X first
#define Y second
const int INF = 0x3f3f3f3f;
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
const int N = 5e5 + 5;
int n, m, b[N << 1];
PII a[N];
struct Node{
	int l, r, mx, add;
	Node(){l = r = mx = add = 0;}
}tr[N << 3];
inline void Pushup(int p){
	tr[p].mx = max(tr[p << 1].mx, tr[p << 1 | 1].mx);
}
inline void Add(int p, int x){tr[p].mx += x, tr[p].add += x;}
inline void Pushdown(int p){
	if(tr[p].add){
		Add(p << 1, tr[p].add);
		Add(p << 1 | 1, tr[p].add);
		tr[p].add = 0;
	}
}
void Build(int l, int r, int p){
	tr[p].l = l, tr[p].r = r;
	if(l == r) return;
	int mid = l + r >> 1;
	Build(l, mid, p << 1);
	Build(mid + 1, r, p << 1 | 1);
}
void Section_Modify_Add(int l, int r, int p, int x){
	if(l <= tr[p].l && tr[p].r <= r){Add(p, x); return;}
	Pushdown(p);
	int mid = tr[p].l + tr[p].r >> 1;
	if(l <= mid) Section_Modify_Add(l, r, p << 1, x);
	if(r > mid) Section_Modify_Add(l, r, p << 1 | 1, x);
	Pushup(p);
}
int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++ i) b[i - 1 << 1 | 1] = a[i].X = read(), b[i << 1] = a[i].Y = read();
	sort(b + 1, b + n + n + 1);
	int tot = unique(b + 1, b + n + n + 1) - b - 1;
	sort(a + 1, a + n + 1, [](PII a, PII b){return a.Y - a.X < b.Y - b.X;});
	for(int i = 1; i <= n; ++ i)
		a[i].X = lower_bound(b + 1, b + tot + 1, a[i].X) - b,
		a[i].Y = lower_bound(b + 1, b + tot + 1, a[i].Y) - b;
	Build(1, tot, 1);
	int ans = INF;
	for(int l = 1, r = 1; r <= n; ++ r){
		Section_Modify_Add(a[r].X, a[r].Y, 1, 1);
		while(tr[1].mx >= m){
			updmin(ans, b[a[r].Y] - b[a[r].X] - b[a[l].Y] + b[a[l].X]);
			Section_Modify_Add(a[l].X, a[l].Y, 1, -1), ++ l;
		}
	}
	write(ans == INF ? -1 : ans);
	return 0;
}

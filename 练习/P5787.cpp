#include <bits/stdc++.h>
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
#define init(x, y) memset(x, y, sizeof x)
#define copy(x, y) memcpy(x, y, sizeof x)
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void write(T x, const char *s){
    static int st[40]; int top = 0;
    if(x < 0){putchar('-'); x = -x;}
    if(!x) putchar('0');
    while(x) st[++ top] = x % 10, x /= 10;
    while(top) putchar(st[top --] + 48);
    printf("%s", s);
}
template<typename T> inline T max(T x, T y){return x > y ? x : y;}
template<typename T> inline T min(T x, T y){return x < y ? x : y;}
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 1e5 + 5, M = 2e5 + 5;
int n, m, k;
int fa[M], sz[M], st[M], top;
int get(int u){return u == fa[u] ? u : get(fa[u]);}
inline void merge(int u, int v){
    u = get(u), v = get(v);
    if(u == v) return;
    if(sz[u] > sz[v]) std::swap(u, v);
    fa[u] = v, st[++ top] = u, sz[v] += sz[u];
}
struct node{
    int l, r;
    std::vector<PII> e;
    node(){l = r = 0;}
    node(int _l, int _r){l = _l, r = _r;}
}tr[N << 2];
void build(int l, int r, int p){
    tr[p] = node(l, r);
    if(l == r) return;
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
}
void insert(int l, int r, int p, PII e){
    if(l > r) return;
    if(l <= tr[p].l && tr[p].r <= r){tr[p].e.push_back(e); return;}
    int mid = tr[p].l + tr[p].r >> 1;
    if(l <= mid) insert(l, r, p << 1, e);
    if(r > mid) insert(l, r, p << 1 | 1, e);
}
void calc(int p, bool flag){
    int tmp = top;
    uf(i, 0, tr[p].e.size()){
        int u = tr[p].e[i].X, v = tr[p].e[i].Y;
        if(get(u) == get(v)) flag = false;
        else merge(u, v + n), merge(u + n, v);
    }
    if(!flag){
        uF(i, tr[p].l, tr[p].r) puts("No");
        while(top > tmp) fa[st[top --]] = st[top];
        return;
    }
    if(tr[p].l == tr[p].r){puts("Yes"); return;}
    calc(p << 1, flag);
    calc(p << 1 | 1, flag);
    while(top > tmp) fa[st[top --]] = st[top];
}
signed main(){
    n = read<int>(), m = read<int>(), k = read<int>();
    uF(i, 1, n + n) fa[i] = i, sz[i] = 1;
    build(1, k, 1);
    while(m --){
        int u = read<int>(), v = read<int>(), l = read<int>() + 1, r = read<int>();
        insert(l, r, 1, (PII){u, v});
    }
    calc(1, true);
    lovely _lzy_;
}
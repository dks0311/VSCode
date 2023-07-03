/*
author: 牛肉爱吃dks
starting time: 2023.06.06 19:35:34
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define ll long long
#define int long long
#define DB double
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
#define uf(i, x, y) for(int i = (x); i < (y); ++ i)
#define dF(i, x, y) for(int i = (x); i >= (y); -- i)
#define df(i, x, y) for(int i = (x); i > (y); -- i)
#define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void read(T &x){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    x = f ? ~s + 1 : s;
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
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmul(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
template<typename T> void debug(const char *s, T *a, int l, int r){
    printf("%s:\n", s);
    uF(i, l, r) std::cout << a[i] << " ";
    puts("");
}
const int N = 1e5 + 5, INF = 123456789123456789;
int n, m;
int head[N], ne[N << 1], to[N << 1], wgt[N << 1], idx;
int sz[N], son[N], fat[N], dpt[N], dis[N];
int top[N], l2t[N], t2l[N], tot;
inline void add(int u, int v, int w){to[++ idx] = v, ne[idx] = head[u], head[u] = idx, wgt[idx] = w;}
void dfs1(int u, int fa){
    sz[u] = 1, fat[u] = fa, dpt[u] = dpt[fa] + 1;
    ef(i, u){
        int v = to[i];
        if(v == fa) continue;
        dis[v] = dis[u] + wgt[i];
        dfs1(v, u); sz[u] += sz[v];
        if(sz[son[u]] < sz[v]) son[u] = v;
    }
}
void dfs2(int u, int t){
    top[u] = t, t2l[u] = ++ tot, l2t[tot] = u;
    if(son[u]) dfs2(son[u], t);
    ef(i, u) if(to[i] != son[u] && to[i] != fat[u]) dfs2(to[i], to[i]);
}
inline int lca(int u, int v){
    while(top[u] != top[v])
        dpt[top[u]] > dpt[top[v]] ? u = fat[top[u]] : v = fat[top[v]];
    return dpt[u] < dpt[v] ? u : v;
}
typedef struct segment{int k, b;}seg;
struct node{
    int l, r, mn;
    seg s;
    node(){l = r = 0, s = (seg){0, mn = INF};}
}tr[N << 3];
inline int v(seg s, int x){return s.k * dis[l2t[x]] + s.b;}
inline void pushup(int p){
    tr[p].mn = min(min(v(tr[p].s, tr[p].l), v(tr[p].s, tr[p].r)), min(tr[p << 1].mn, tr[p << 1 | 1].mn));
}
void build(int l, int r, int p){
    tr[p].l = l, tr[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    pushup(p);
}
void insert(int l, int r, int p, seg s){
    if(!tr[p].l) return;
    int mid = tr[p].l + tr[p].r >> 1;
    if(l > tr[p].l || tr[p].r > r){
        if(l <= mid) insert(l, r, p << 1, s);
        if(r > mid) insert(l, r, p << 1 | 1, s);
        pushup(p);
        return;
    }
    if(v(s, mid) < v(tr[p].s, mid)) std::swap(s, tr[p].s);
    if(v(s, tr[p].l) < v(tr[p].s, tr[p].l)) insert(l, r, p << 1, s);
    if(v(s, tr[p].r) < v(tr[p].s, tr[p].r)) insert(l, r, p << 1 | 1, s); 
    pushup(p);
}
int query(int l, int r, int p){
    if(l <= tr[p].l && tr[p].r <= r) return tr[p].mn;
    int mid = tr[p].l + tr[p].r >> 1, res = INF;
    if(l <= mid) updmin(res, query(l, r, p << 1));
    if(r > mid) updmin(res, query(l, r, p << 1 | 1));
    updmin(res, min(v(tr[p].s, max(tr[p].l, l)), v(tr[p].s, min(tr[p].r, r))));
    return res;
}
signed main(){
    n = read<int>(), m = read<int>();
    uf(i, 1, n){
        int u = read<int>(), v = read<int>(), w = read<int>();
        add(u, v, w); add(v, u, w);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, n, 1);
    while(m --){
        int opt = read<int>();
        if(opt == 1){
            int s = read<int>(), t = read<int>(), a = read<int>(), b = read<int>();
            int u = s, l = lca(s, t);
            seg sg = (seg){-a, a * dis[s] + b};
            while(top[u] != top[l]) insert(t2l[top[u]], t2l[u], 1, sg), u = fat[top[u]];
            insert(t2l[l], t2l[u], 1, sg);
            u = t, sg = (seg){a, a * dis[s] - 2 * a * dis[l] + b};
            while(top[u] != top[l]) insert(t2l[top[u]], t2l[u], 1, sg), u = fat[top[u]];
            insert(t2l[l], t2l[u], 1, sg);
        }
        else{
            int s = read<int>(), t = read<int>(), l = lca(s, t), res = INF, u = s;
            while(top[u] != top[l]) updmin(res, query(t2l[top[u]], t2l[u], 1)), u = fat[top[u]];
            updmin(res, query(t2l[l], t2l[u], 1));
            u = t;
            while(top[u] != top[l]) updmin(res, query(t2l[top[u]], t2l[u], 1)), u = fat[top[u]];
            updmin(res, query(t2l[l], t2l[u], 1));
            write(res, "\n");
        }
    }
    lovely _lzy_;
}
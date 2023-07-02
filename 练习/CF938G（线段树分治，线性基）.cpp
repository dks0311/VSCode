#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define LL long long
// #define int long long
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
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 2e5 + 5;
int n, m, q;





struct linear_base{
    int a[35];
    linear_base(){init(a, 0);}
    void insert(int x){
        dF(i, 31, 0){
            if(!(x >> i)) continue;
            if(!a[i]){a[i] = x; break;}
            x ^= a[i];
        }
    }
    int query(int x){
        dF(i, 31, 0) if(x >> i & 1) x ^= a[i];
        return x;
    }
}lb[20];
int now;





struct DSU{
    struct node{
        int fa, sz, dis;
        node(){fa = sz = dis = 0;}
        node(int _fa, int _sz, int _dis){fa = _fa, sz = _sz, dis = _dis;}
    }tr[N];
    int st[N << 2], top;
    node stk[N << 2];
    DSU(){top = 0; uF(i, 1, 2e5) tr[i] = node(i, 1, 0);}
    int get(int u){return u == tr[u].fa ? u : get(tr[u].fa);}
    int get_dis(int u){return u == tr[u].fa ? 0 : tr[u].dis ^ get_dis(tr[u].fa);}
    inline void merge(int u, int v, int w){
        w ^= get_dis(u) ^ get_dis(v);
        u = get(u), v = get(v);
        if(u == v){lb[now].insert(w); return;}
        if(tr[u].sz > tr[v].sz) std::swap(u, v);
        st[++ top] = u, stk[top] = tr[u];
        st[++ top] = v, stk[top] = tr[v];
        tr[v].sz += tr[u].sz, tr[u] = node(v, 0, w);
        return;
    }
    inline void cancel(){tr[st[top]] = stk[top], -- top;}
}dsu;







PII qw[N << 1], pt[N << 1];
int ww[N << 1];
struct node{
    int l, r;
    std::vector<int> e;
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
void insert(int l, int r, int p, int e){
    if(l > r) return;
    if(l <= tr[p].l && tr[p].r <= r){tr[p].e.push_back(e); return;}
    int mid = tr[p].l + tr[p].r >> 1;
    if(l <= mid) insert(l, r, p << 1, e);
    if(r > mid) insert(l, r, p << 1 | 1, e);
}
void calc(int p){
    int tmp1 = now ++, tmp2 = dsu.top;
    lb[now] = lb[now - 1];
    uf(i, 0, tr[p].e.size()){
        int x = tr[p].e[i];
        dsu.merge(pt[x].X, pt[x].Y, ww[x]);
    }
    if(tr[p].l == tr[p].r)
        write(lb[now].query(dsu.get_dis(qw[tr[p].l].X) ^ dsu.get_dis(qw[tr[p].l].Y)), "\n");
    else{calc(p << 1); calc(p << 1 | 1);}
    while(dsu.top > tmp2) dsu.cancel();
    now = tmp1;
}





PII ti[N << 1];
std::map<PII, int> id;
signed main(){
    n = read<int>(), m = read<int>();
    int tm = 0, tot = 0;
    uF(i, 1, m){
        int u = read<int>(), v = read<int>(); ww[++ tot] = read<int>();
        ti[id[(PII){u, v}] = id[(PII){v, u}] = tot] = (PII){1, -1}, pt[tot] = (PII){u, v};
    }
    q = read<int>();
    while(q --){
        int opt = read<int>(), u = read<int>(), v = read<int>();
        if(opt == 1)
            ww[++ tot] = read<int>(), pt[tot] = (PII){u, v}, ti[id[(PII){u, v}] = id[(PII){v, u}] = tot] = (PII){tm + 1, -1};
        else if(opt == 2) ti[id[(PII){u, v}]].Y = tm;
        else qw[++ tm] = (PII){u, v};
    }
    build(1, tm, 1);
    uF(i, 1, tot) if(ti[i].Y == -1) ti[i].Y = tm;
    uF(i, 1, tot) insert(ti[i].X, ti[i].Y, 1, i);
    calc(1);
    lovely _lzy_;
}
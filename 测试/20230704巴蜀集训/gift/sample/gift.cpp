#include <bits/stdc++.h>
namespace _default{
    using namespace std;
    #define lovely return
    #define _lzy_ 0
    #define LL long long
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
    const int MOD = 1e9 + 7, INF = 0x3f3f3f3f;
    const DB EPS = 1e-8;
    template<typename T> T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0){putchar('-'); x = -x;}
        if(!x) putchar('0');
        while(x) st[++ top] = x % 10, x /= 10;
        while(top) putchar(st[top --] + 48);
        printf("%s", s);
    }
    template<typename T> void updmin(T &x, T y){if(x > y) x = y;}
    template<typename T> void updmax(T &x, T y){if(x < y) x = y;}
    template<typename T> void updadd(T &x, T y){(x += y % MOD) %= MOD;}
    template<typename T> void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
#define BS bitset<1005>
const int N = 3e5 + 5;
int n, m, q;
int co[N];
BS sum[N];
int head[N], to[N], ne[N], idx;
void Add_Edge(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
int fa[N], dpt[N], son[N], sz[N];
void DFS1(int u, int fat){
    dpt[u] = dpt[fat] + 1, sz[u] = 1, sum[u][co[u]] = 1;
    ef(i, u){
        int v = to[i]; DFS1(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}
int dfn[N], id[N], top[N], ts;
void DFS2(int u, int t){
    id[dfn[u] = ++ ts] = u, top[u] = t;
    if(u != t) sum[u] |= sum[fa[u]];
    if(son[u]) DFS2(son[u], t);
    ef(i, u) if(to[i] != son[u]) DFS2(to[i], to[i]);
}
int LCA(int u, int v){
    while(top[u] != top[v]){
        if(dpt[top[u]] < dpt[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dpt[u] < dpt[v] ? u : v;
}
struct Node{
    int l, r;
    BS sum;
    Node(){l = r = 0; sum.reset();}
}tr[N << 2];
void Pushup(int p){tr[p].sum = tr[p << 1].sum | tr[p << 1 | 1].sum;}
void Build(int l, int r, int p){
    tr[p].l = l, tr[p].r = r;
    if(l == r){tr[p].sum[co[id[l]]] = 1; return;}
    int mid = l + r >> 1;
    Build(l, mid, p << 1);
    Build(mid + 1, r, p << 1 | 1);
    Pushup(p);
}
BS Section_Query_sum(int l, int r, int p){
    if(l <= tr[p].l && tr[p].r <= r) return tr[p].sum;
    int mid = tr[p].l + tr[p].r >> 1; BS res; res.reset();
    if(l <= mid) res |= Section_Query_sum(l, r, p << 1);
    if(r > mid) res |= Section_Query_sum(l, r, p << 1 | 1);
    return res;
}
BS Query(int u, int v){
    BS res; res.reset();
    while(top[u] != top[v]) res |= sum[u], u = fa[top[u]];
    res |= Section_Query_sum(dfn[v], dfn[u], 1);
    return res;
}
int p[10];
BS pc[10], dp[1 << 5 | 5];
signed main(){
    n = read<int>(), m = read<int>(), q = read<int>();
    if(!q) return 0;
    uF(i, 2, n){fa[i] = read<int>(); Add_Edge(fa[i], i);}
    uF(i, 1, n) co[i] = read<int>();
    DFS1(1, 0);
    DFS2(1, 1);
    Build(1, n, 1);
    while(q --){
        int k = read<int>(), lca, ans = INF;
        uF(i, 1, k){
            p[i] = read<int>();
            lca = i == 1 ? p[i] : LCA(lca, p[i]);
        }
        uF(i, 1, k) pc[i] = Query(p[i], lca);
        uf(s, 1, 1 << k){
            uF(i, 1, k) if(s >> i - 1 & 1){
                dp[s] = dp[s - (1 << i - 1)] | pc[i];
                break;
            }
            int cnt = 0;
            uf(i, 0, k) cnt += s >> i & 1;
            updmin(ans, (int)(dp[s].count() / cnt));
        }
        write(ans * k, "\n");
    }
    lovely _lzy_;
}
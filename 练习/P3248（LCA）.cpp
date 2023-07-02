/*
author: 牛肉爱吃dks
starting time: 2023.06.05 11:54:26
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
#define uf(i, x, y) for(int i = (x); i < (y); ++ i)
#define dF(i, x, y) for(int i = (x); i >= (y); -- i)
#define df(i, x, y) for(int i = (x); i > (y); -- i)
#define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
#define PII std::pair<int, int>
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void write(T x, std::string s){
    static int st[40]; int top = 0;
    if(x < 0){putchar('-'); x = -x;}
    if(!x) putchar('0');
    while(x) st[++ top] = x % 10, x /= 10;
    while(top) putchar(st[top --] + 48);
    std::cout << s;
}
const int N = 1e5 + 5;
int n, m, q;
struct president_tree{
    struct node{
        int ls, rs, cnt;
        node(){ls = rs = cnt = 0;}
        node(int _cnt){ls = rs = 0, cnt = _cnt;}
    }tr[N * 20];
    int rt[N], idx;
    president_tree(){memset(rt, 0, sizeof rt); idx = 0;}
    inline void pushup(int u){tr[u].cnt = tr[tr[u].ls].cnt + tr[tr[u].rs].cnt;}
    void insert(int l, int r, int p, int &now, int x){
        tr[now = ++ idx].cnt = tr[p].cnt + 1;
        if(l == r) return;
        int mid = l + r >> 1;
        if(x <= mid){
            insert(l, mid, tr[p].ls, tr[now].ls, x);
            tr[now].rs = tr[p].rs;
        }
        else{
            insert(mid + 1, r, tr[p].rs, tr[now].rs, x);
            tr[now].ls = tr[p].ls;
        }
        pushup(now);
    }
    int query(int l, int r, int L, int R, int rk){
        if(l == r) return l;
        int mid = l + r >> 1;
        if(rk <= tr[tr[R].ls].cnt - tr[tr[L].ls].cnt) return query(l, mid, tr[L].ls, tr[R].ls, rk);
        else return query(mid + 1, r, tr[L].rs, tr[R].rs, rk - tr[tr[R].ls].cnt + tr[tr[L].ls].cnt);
    }
}S;
namespace tree1{
    int head[N], ne[N << 1], to[N << 1], idx;
    int dpt[N], f[N][20], sz[N], pos[N], tot;
    inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
    void dfs(int u, int fa){
        pos[u] = ++ tot, f[u][0] = fa, sz[u] = 1;
        S.insert(1, n, S.rt[tot - 1], S.rt[tot], u);
        uF(i, 1, 16) f[u][i] = f[f[u][i - 1]][i - 1];
        ef(i, u){
            int v = to[i];
            if(v == fa) continue;
            dpt[v] = dpt[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    inline int lca(int u, int v){
        if(dpt[u] < dpt[v]) std::swap(u, v);
        dF(i, 16, 0) if(dpt[f[u][i]] >= dpt[v]) u = f[u][i];
        if(u == v) return u;
        dF(i, 16, 0) if(f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
        return f[u][0];
    }
}
namespace tree2{
    int head[N], ne[N], to[N], idx;
    int dpt[N], f[N][20], dis[N];
    int fat[N], st[N], rt[N], tot;
    inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
    void dfs(int u, int fa){
        f[u][0] = fa;
        uF(i, 1, 16) f[u][i] = f[f[u][i - 1]][i - 1];
        dpt[u] = dpt[fa] + 1, dis[u] = tree1::dpt[fat[u]] - tree1::dpt[rt[fa]] + dis[fa] + 1;
        ef(i, u) dfs(to[i], u);
    }
    inline PII lca(int U, int v, int V){
        dF(i, 16, 0) if(dpt[f[U][i]] >= dpt[V] && f[U][i] != V) U = f[U][i];
        if(f[U][0] == V) return (PII){tree1::lca(fat[U], v), V};
        dF(i, 16, 0) if(f[U][i] != f[V][i]) U = f[U][i], V = f[V][i];
        return (PII){tree1::lca(fat[U], fat[V]), f[U][0]};
    }
}
int get_id(int u, int U){
    if(U == 1) return u;
    using tree2::rt;
    using tree2::st;
    using tree1::pos;
    using tree1::sz;
    return S.query(1, n, S.rt[pos[rt[U]] - 1], S.rt[pos[rt[U]] + sz[rt[U]] - 1], u - st[U] + 1);
}
int get_dis(int u, int U){return tree1::dpt[u] - tree1::dpt[tree2::rt[U]] + tree2::dis[U];}
signed main(){
    n = read<int>(), m = read<int>(), q = read<int>();
    uf(i, 1, n){
        int u = read<int>(), v = read<int>();
        tree1::add(u, v); tree1::add(v, u);
    }
    tree1::dfs(1, 0);
    tree2::tot = 1, tree2::st[1] = 1, tree2::st[2] = tree1::sz[1] + 1, tree2::rt[1] = 1;
    uF(i, 1, m){
        using namespace tree2;
        int u = read<int>(), v = read<int>();
        int V = std::upper_bound(st + 1, st + tot + 1, v) - st - 1;
        v = get_id(v, V);
        fat[++ tot] = v;
        rt[tot] = u;
        st[tot + 1] = st[tot] + tree1::sz[u];
        add(V, tot);
    }
    tree2::dfs(1, 0);
    while(q --){
        using tree2::st;
        using tree2::tot;
        int u = read<int>(), v = read<int>();
        int U = std::upper_bound(st + 1, st + tot + 1, u) - st - 1;
        int V = std::upper_bound(st + 1, st + tot + 1, v) - st - 1;
        u = get_id(u, U), v = get_id(v, V);
        if(U == V){
            using tree1::dpt;
            write(dpt[u] + dpt[v] - 2 * dpt[tree1::lca(u, v)], "\n");
            continue;
        }
        if(tree2::dpt[U] < tree2::dpt[V]){std::swap(U, V); std::swap(u, v);}
        PII tmp = tree2::lca(U, v, V); int l = tmp.first, L = tmp.second;
        write(get_dis(u, U) + get_dis(v, V) - 2 * get_dis(l, L), "\n");
    }
    lovely _lzy_;
}
/*
author: 牛肉爱吃dks
starting time: 2023.06.03 21:04:39
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
template<typename T1, typename T2> inline int max(T1 x, T2 y){return x > y ? x : y;}
template<typename T1, typename T2> inline int min(T1 x, T2 y){return x < y ? x : y;}
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmlt(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
const int N = 1e5 + 5, INF = 2147483647;
int n, m, a[N];
struct fhq_treap{
    struct node{
        int ls, rs, key;
        int val, sz;
        node(){ls = rs = key = val = sz = 0;}
        node(int _key, int _val){ls = rs = 0, sz = 1, key = _key, val = _val;}
    }tr[N * 20];
    int rt[N << 2], idx;
    fhq_treap(){memset(rt, 0, sizeof rt); idx = 0;}
    inline void pushup(int u){tr[u].sz = tr[tr[u].ls].sz + 1 + tr[tr[u].rs].sz;}
    inline int new_node(int val){tr[++ idx] = node(rand(), val); return idx;}
    void split(int val, int p, int &u, int &v){
        if(!p) u = v = 0;
        else{
            if(tr[p].val <= val){u = p; split(val, tr[p].rs, tr[u].rs, v);}
            else{v = p; split(val, tr[p].ls, u, tr[v].ls);}
            pushup(p);
        }
    }
    int merge(int u, int v){
        if(!u || !v) return u + v;
        if(tr[u].key > tr[v].key){tr[u].rs = merge(tr[u].rs, v); pushup(u); return u;}
        else{tr[v].ls = merge(u, tr[v].ls); pushup(v); return v;}
    }
    inline void insert(int val, int id){
        int u, v; split(val, rt[id], u, v);
        rt[id] = merge(u, merge(new_node(val), v));
    }
    inline void del(int val, int id){
        int u, v, w; split(val, rt[id], u, w); split(val - 1, u, u, v);
        v = merge(tr[v].ls, tr[v].rs), rt[id] = merge(u, merge(v, w));
    }
    inline int get_rank(int val, int id){
        int u, v; split(val - 1, rt[id], u, v);
        int res = tr[u].sz + 1; rt[id] = merge(u, v);
        return res;
    }
    inline int get_prev(int val, int id){
        int u, v; split(val - 1, rt[id], u, v);
        if(!tr[u].sz) return -INF;
        int p = u; while(tr[p].rs) p = tr[p].rs;
        rt[id] = merge(u, v);
        return tr[p].val;
    }
    inline int get_next(int val, int id){
        int u, v; split(val, rt[id], u, v);
        if(!tr[v].sz) return INF;
        int p = v; while(tr[p].ls) p = tr[p].ls;
        rt[id] = merge(u, v);
        return tr[p].val;
    }
}S1;
struct segment_tree{
    struct node{int l, r; node(){l = r = 0;}}tr[N << 2];
    inline void init(int p){for(int i = tr[p].l; i <= tr[p].r; ++ i) S1.insert(a[i], p);}
    void build(int l, int r, int p){
        tr[p].l = l, tr[p].r = r;
        init(p);
        if(l == r) return;
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
    }
    int get_rank(int val, int l, int r, int p){
        if(l <= tr[p].l && tr[p].r <= r) return S1.get_rank(val, p);
        int mid = tr[p].l + tr[p].r >> 1, res = 0;
        if(l <= mid) res += get_rank(val, l, r, p << 1) - 1;
        if(r > mid) res += get_rank(val, l, r, p << 1 | 1) - 1;
        return res + 1;
    }
    inline int get_val(int rk, int l, int r){
        int ll = 0, rr = 1e8;
        while(ll < rr){
            int mid = ll + rr + 1 >> 1;
            if(get_rank(mid, l, r, 1) <= rk) ll = mid;
            else rr = mid - 1;
        }
        return ll;
    }
    inline void modify(int pos, int last, int val, int p){
        S1.del(last, p); S1.insert(val, p);
        if(tr[p].l == tr[p].r) return;
        int mid = tr[p].l + tr[p].r >> 1;
        if(pos <= mid) modify(pos, last, val, p << 1);
        else modify(pos, last, val, p << 1 | 1);
    }
    inline int get_prev(int val, int l, int r, int p){
        if(l <= tr[p].l && tr[p].r <= r) return S1.get_prev(val, p);
        int mid = tr[p].l + tr[p].r >> 1, res = -INF;
        if(l <= mid) updmax(res, get_prev(val, l, r, p << 1));
        if(r > mid) updmax(res, get_prev(val, l, r, p << 1 | 1));
        return res;
    }
    inline int get_next(int val, int l, int r, int p){
        if(l <= tr[p].l && tr[p].r <= r) return S1.get_next(val, p);
        int mid = tr[p].l + tr[p].r >> 1, res = INF;
        if(l <= mid) updmin(res, get_next(val, l, r, p << 1));
        if(r > mid) updmin(res, get_next(val, l, r, p << 1 | 1));
        return res;
    }
}S2;
signed main(){
    srand(time(0));
    n = read<int>(), m = read<int>();
    uF(i, 1, n) a[i] = read<int>();
    S2.build(1, n, 1);
    while(m --){
        int opt = read<int>();
        if(opt == 1){
            int l = read<int>(), r = read<int>(), val = read<int>();
            write(S2.get_rank(val, l, r, 1), "\n");
        }
        else if(opt == 2){
            int l = read<int>(), r = read<int>(), rk = read<int>();
            write(S2.get_val(rk, l, r), "\n");
        }
        else if(opt == 3){
            int pos = read<int>(), val = read<int>();
            S2.modify(pos, a[pos], val, 1);
            a[pos] = val;
        }
        else if(opt == 4){
            int l = read<int>(), r = read<int>(), val = read<int>();
            write(S2.get_prev(val, l, r, 1), "\n");
        }
        else if(opt == 5){
            int l = read<int>(), r = read<int>(), val = read<int>();
            write(S2.get_next(val, l, r, 1), "\n");
        }
    }
    lovely _lzy_;
}
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
#define uf(i, x, y) for(int i = (x); i < (y); ++ i)
#define dF(i, x, y) for(int i = (x); i >= (y); -- i)
#define df(i, x, y) for(int i = (x); i > (y); -- i)
#define ef(i, u) for(int i = head[u]; i; i = ne[i])
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
const int N = 1e5 + 5;
struct node{
    int ls, rs, key;
    int dp[4][4], v[4], cnt, sz;
    node(){ls = rs = key = sz = cnt = 0; memset(dp, 0, sizeof dp); memset(v, 0, sizeof v);}
    node(int _key, int a, int b, int c, int _cnt){
        ls = rs = sz = 0, key = _key, v[0] = v[3] = a, v[1] = b, v[2] = c, cnt = _cnt;
        memset(dp, 0, sizeof dp);
    }
}tr[N << 1];
int n, idx, root, last;
int t[4][4];
inline void pushup(int u){
    int ls = tr[u].ls, rs = tr[u].rs;
    memset(tr[u].dp, 0, sizeof tr[u].dp);
    tr[u].sz = tr[ls].sz + tr[u].cnt + tr[rs].sz;
    uf(l, 0, 4) uf(r, l, 4) uF(mid, l, r) updmax(tr[u].dp[l][r], tr[u].v[mid] * tr[u].cnt);
    if(ls){
        memcpy(t, tr[u].dp, sizeof t);
        memset(tr[u].dp, 0, sizeof tr[u].dp);
        uf(l, 0, 4) uf(r, l, 4) uF(mid, l, r)
            updmax(tr[u].dp[l][r], tr[ls].dp[l][mid] + t[mid][r]);
    }
    if(rs){
        memcpy(t, tr[u].dp, sizeof t);
        memset(tr[u].dp, 0, sizeof tr[u].dp);
        uf(l, 0, 4) uf(r, l, 4) uF(mid, l, r)
            updmax(tr[u].dp[l][r], t[l][mid] + tr[rs].dp[mid][r]);
    }
    return;
}
inline int new_node(int a, int b, int c, int cnt){
    tr[++ idx] = node(rand(), a, b, c, cnt);
    pushup(idx);
    return idx;
}
void split(int sz, int p, int &u, int &v){
    if(!p) u = v = 0;
    else{
        if(tr[tr[p].ls].sz < sz){
            u = p;
            split(sz - tr[tr[p].ls].sz - tr[p].cnt, tr[p].rs, tr[u].rs, v);
        }
        else{
            v = p;
            split(sz, tr[p].ls, u, tr[v].ls);
        }
        pushup(p);
    }
    return;
}
int merge(int u, int v){
    if(!u || !v) return u + v;
    if(tr[u].key > tr[v].key){
        tr[u].rs = merge(tr[u].rs, v);
        pushup(u);
        return u;
    }
    else{
        tr[v].ls = merge(u, tr[v].ls);
        pushup(v);
        return v;
    }
}
inline int get_max(int p){
    while(tr[p].rs) p = tr[p].rs;
    return tr[p].cnt;
}
inline void insert(int sz, int a, int b, int c, int cnt){
    int u, v, w;
    split(sz, root, u, w);
    if(tr[u].sz == sz){
        root = merge(u, merge(new_node(a, b, c, cnt), w));
        return;
    }
    split(tr[u].sz - get_max(u), u, u, v);
    int tmp = tr[v].cnt - sz + tr[u].sz, na = tr[v].v[0], nb = tr[v].v[1], nc = tr[v].v[2];
    tr[v].cnt = sz - tr[u].sz;
    pushup(v);
    root = merge(merge(u, v), merge(new_node(a, b, c, cnt), merge(new_node(na, nb, nc, tmp), w)));
    return;
}
signed main(){
    srand(time(0));
    n = read<int>();
    uF(i, 1, n){
        int p = read<int>(), a = read<int>(), b = read<int>(), c = read<int>(), x = read<int>();
        insert(p, a, b, c, x);
        int ans = tr[root].dp[0][3];
        write(ans - last, "\n");
        last = ans;
    }
    lovely _lzy_;
}
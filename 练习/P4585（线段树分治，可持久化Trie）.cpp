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
const int N = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m, a[N];
struct Trie{
    struct node{int son[2], ti; node(){init(son, 0); ti = 0;}}tr[N * 17 * 17];
    int rt[N << 2], idx;
    Trie(){init(rt, 0); idx = 0;}
    void insert(int x, int id, int ti){
        if(!rt[id]) rt[id] = ++ idx;
        int now = rt[id];
        dF(i, 17, 0){
            int c = x >> i & 1;
            if(!tr[now].son[c]) tr[now].son[c] = ++ idx;
            updmax(tr[now = tr[now].son[c]].ti, ti);
        }
    }
    int query(int x, int id, int ti){
        int now = rt[id], res = 0;
        dF(i, 17, 0){
            int c = x >> i & 1;
            if(tr[now].son[c ^ 1] && tr[tr[now].son[c ^ 1]].ti >= ti) res |= 1 << i, now = tr[now].son[c ^ 1];
            else now = tr[now].son[c];
        }
        return res;
    }
}trie;
struct Segment_Tree{
    struct node{int l, r; node(){l = r = 0;}}tr[N << 2];
    void strct(int p){uF(i, tr[p].l, tr[p].r) trie.insert(a[i], p, INF);}
    void build(int l, int r, int p){
        tr[p].l = l, tr[p].r = r;
        strct(p);
        if(l == r) return;
        int mid = l + r >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
    }
    void insert(int p, int x, int y, int ti){
        trie.insert(y, p, ti);
        if(tr[p].l == tr[p].r) return;
        int mid = tr[p].l + tr[p].r >> 1;
        if(x <= mid) insert(p << 1, x, y, ti);
        else insert(p << 1 | 1, x, y, ti);
    }
    int query(int l, int r, int p, int x, int ti){
        if(l <= tr[p].l && tr[p].r <= r) return trie.query(x, p, ti);
        int mid = tr[p].l + tr[p].r >> 1, res = 0;
        if(l <= mid) updmax(res, query(l, r, p << 1, x, ti));
        if(r > mid) updmax(res, query(l, r, p << 1 | 1, x, ti));
        return res;
    }
}S;
signed main(){
    n = read<int>(), m = read<int>();
    uF(i, 1, n) a[i] = read<int>();
    S.build(1, n, 1);
    int ti = 0;
    uF(i, 1, m){
        int opt = read<int>();
        if(!opt || i == 1) ++ ti;
        if(!opt){
            int s = read<int>(), v = read<int>();
            S.insert(1, s, v, ti);
        }
        else{
            int l = read<int>(), r = read<int>(), x = read<int>(), d = read<int>();
            write(S.query(l, r, 1, x, ti - d + 1), "\n");
        }
    }
    lovely _lzy_;
}
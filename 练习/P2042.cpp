/*
author: 牛肉爱吃dks
starting time: 2023.06.05 21:36:57
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
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
template<typename T1, typename T2> inline int max(T1 x, T2 y){return x > y ? x : y;}
template<typename T1, typename T2> inline int min(T1 x, T2 y){return x < y ? x : y;}
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmul(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
const int INF = 5e8;
int n, m;
#define sz(u) (u ? u -> sz : 0)
#define sum(u) (u ? u -> sum : 0)
#define lm(u) (u ? u -> lm : 0)
#define rm(u) (u ? u -> rm : 0)
#define mm(u) (u ? u -> mm : 0)
#define mx(u) (u ? u -> mx : -INF)
struct node{
    node *ls, *rs;
    int key, sz, val, sum, lm, rm, mm, cov, rev, mx;
    node(){
        ls = rs = NULL;
        key = sz = val = rev = sum = lm = rm = mm = 0, mx = -INF;
        cov = INF;
    }
    node(int _key, int _val){
        ls = rs = NULL;
        key = _key, sz = 1;
        val = sum = _val;
        lm = rm = mm = max(_val, 0);
        cov = INF, rev = 0, mx = -INF;
    }
    inline void _cov(int x){
        sum = sz * x, val = cov = mx = x;
        lm = rm = mm = max(sum, 0);
    }
    inline void _rev(){
        std::swap(ls, rs);
        std::swap(lm, rm);
        rev ^= 1;
    }
    inline void pushup(){
        sz = sz(ls) + 1 + sz(rs);
        sum = sum(ls) + val + sum(rs);
        lm = max(lm(ls), sum(ls) + val + lm(rs));
        rm = max(rm(ls) + val + sum(rs), rm(rs));
        mm = max(rm(ls) + val + lm(rs), max(mm(ls), mm(rs)));
        mx = max(val, max(mx(ls), mx(rs)));
    }
    inline void pushdown(){
        if(cov != INF){
            if(ls) ls -> _cov(cov);
            if(rs) rs -> _cov(cov); 
            cov = INF;
        }
        if(rev){
            if(ls) ls -> _rev();
            if(rs) rs -> _rev();
            rev = 0;
        }
    }
}*rt = NULL;
void rls(node *u){
    if(!u) return;
    rls(u -> ls);
    rls(u -> rs);
    delete u;
}
inline node *new_node(int val){
    return new node(rand(), val);
}
void split(int sz, node *p, node *&u, node *&v){
    if(!p) u = v = NULL;
    else{
        p -> pushdown();
        if(sz(p -> ls) < sz){u = p; split(sz - sz(p -> ls) - 1, p -> rs, u -> rs, v);}
        else{v = p; split(sz, p -> ls, u, v -> ls);}
        p -> pushup();
    }
}
node *merge(node *u, node *v){
    if(!u || !v) return u ? u : v;
    else if(u -> key > v -> key){
        u -> pushdown();
        u -> rs = merge(u -> rs, v);
        u -> pushup();
        return u;
    }
    else{
        v -> pushdown();
        v -> ls = merge(u, v -> ls);
        v -> pushup();
        return v;
    }
}
inline void insert(int sz, node *x){
    node *u, *v;
    split(sz, rt, u, v);
    rt = merge(u, merge(x, v));
}
inline void del(int l, int r){
    node *u, *v, *w;
    split(r, rt, u, w);
    split(l - 1, u, u, v);
    rt = merge(u, w);
    rls(v);
}
inline int query_sum(int l, int r){
    node *u, *v, *w;
    split(r, rt, u, w);
    split(l - 1, u, u, v);
    int res = sum(v);
    rt = merge(u, merge(v, w));
    return res;
}
inline void cov(int l, int r, int x){
    node *u, *v, *w;
    split(r, rt, u, w);
    split(l - 1, u, u, v);
    v -> _cov(x);
    rt = merge(u, merge(v, w));
}
inline void rev(int l, int r){
    node *u, *v, *w;
    split(r, rt, u, w);
    split(l - 1, u, u, v);
    v -> _rev();
    rt = merge(u, merge(v, w));
}
signed main(){
    srand(time(0));
    n = read<int>(), m = read<int>();
    uf(i, 0, n){
        int x = read<int>();
        rt = merge(rt, new_node(x));
    }
    while(m --){
        std::string opt; std::cin >> opt;
        if(opt == "INSERT"){
            int pos = read<int>(), k = read<int>();
            node *v = NULL;
            uf(i, 0, k){
                int x = read<int>();
                v = merge(v, new_node(x));
            }
            insert(pos, v);
        }
        else if(opt == "DELETE"){
            int pos = read<int>(), k = read<int>();
            del(pos, pos + k - 1);
        }
        else if(opt == "MAKE-SAME"){
            int pos = read<int>(), k = read<int>(), x = read<int>();
            cov(pos, pos + k - 1, x);
        }
        else if(opt == "REVERSE"){
            int pos = read<int>(), k = read<int>();
            rev(pos, pos + k - 1);
        }
        else if(opt == "GET-SUM"){
            int pos = read<int>(), k = read<int>();
            write(query_sum(pos, pos + k - 1), "\n");
        }
        else{
            if(mx(rt) < 0) write(mx(rt), "\n");
            else write(mm(rt), "\n");
        }
    }
    lovely _lzy_;
}
/*
author: 牛肉爱吃dks
starting time: 2023.06.04 12:42:55
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define ll long long
#define int long long
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
#define uf(i, x, y) for(int i = (x); i < (y); ++ i)
#define dF(i, x, y) for(int i = (x); i >= (y); -- i)
#define df(i, x, y) for(int i = (x); i > (y); -- i)
#define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
const int MOD = 20130426;
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
template<typename T1, typename T2> inline void updmul(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
const int N = 1e5 + 5;
int n = 100001, m, rt, X, now, idx;
struct node{
    int ls, rs, key, add, mul, val, sz;
    node(){ls = rs = key = add = val = sz = 0, mul = 1;}
    node(int _key, int _val){ls = rs = add = 0, key = _key, val = _val, sz = mul = 1;}
}tr[N << 1];
inline void mul(int u, int x){updmul(tr[u].val, x); updmul(tr[u].mul, x); updmul(tr[u].add, x);}
inline void add(int u, int x){updadd(tr[u].val, x); updadd(tr[u].add, x);}
inline void pushdown(int u){
    mul(tr[u].ls, tr[u].mul); mul(tr[u].rs, tr[u].mul);
    add(tr[u].ls, tr[u].add); add(tr[u].rs, tr[u].add);
    tr[u].mul = 1, tr[u].add = 0;
}
inline void pushup(int u){tr[u].sz = tr[tr[u].ls].sz + 1 + tr[tr[u].rs].sz;}
inline int new_node(int val){tr[++ idx] = node(rand(), val); return idx;}
void split(int sz, int p, int &u, int &v){
    if(!p) u = v = 0;
    else{
        pushdown(p);
        if(tr[tr[p].ls].sz < sz){u = p; split(sz - tr[tr[p].ls].sz - 1, tr[p].rs, tr[u].rs, v);}
        else{v = p; split(sz, tr[p].ls, u, tr[v].ls);}
        pushup(p);
    }
}
int merge(int u, int v){
    if(!u || !v) return u + v;
    if(tr[u].key > tr[v].key){
        pushdown(u);
        tr[u].rs = merge(tr[u].rs, v);
        pushup(u);
        return u;
    }
    else{
        pushdown(v);
        tr[v].ls = merge(u, tr[v].ls);
        pushup(v);
        return v;
    }
}
inline void insert(int sz, int val){
    int u, v; split(sz, rt, u, v);
    rt = merge(u, merge(new_node(val), v));
}
inline void mulx(int l, int r){
    int u, v, w, x, y;//[1,l - 1] [l, r - 1] {r} {r + 1} [r + 2, n]
    split(r + 1, rt, u, y);
    split(r, u, u, x);
    split(r - 1, u, u, w);
    split(l - 1, u, u, v);
    tr[x].val += tr[w].val;
    rt = merge(u, merge(new_node(0), merge(v, merge(x, y))));
}
void modify_add(int l, int r, int x){
    int u, v, w; split(r, rt, u, w); split(l - 1, u, u, v);
    add(v, x);
    rt = merge(u, merge(v, w));
}
void modify_mul(int l, int r, int x){
    int u, v, w; split(r, rt, u, w); split(l - 1, u, u, v);
    mul(v, x);
    rt = merge(u, merge(v, w));
}
int calc(int u){
    int res = 0;
    pushdown(u);
    if(tr[u].ls) updadd(res, calc(tr[u].ls));
    updadd(res, tr[u].val * now); updmul(now, X);   
    if(tr[u].rs) updadd(res, calc(tr[u].rs));
    return res;
}
signed main(){
    srand(time(0));
    read(m);
    uF(i, 1, n) insert(0, 0);
    while(m --){
        std::string opt; std::cin >> opt;
        if(opt == "mul"){
            int l = read<int>() + 1, r = read<int>() + 1, x = read<int>();
            modify_mul(l, r, x);
        }
        else if(opt == "add"){
            int l = read<int>() + 1, r = read<int>() + 1, x = read<int>();
            modify_add(l, r, x);
        }
        else if(opt == "mulx"){
            int l = read<int>() + 1, r = read<int>() + 1;
            mulx(l, r);
        }
        else{
            now = 1; read(X);
            write(calc(rt), "\n");
        }
    }
    lovely _lzy_;
}
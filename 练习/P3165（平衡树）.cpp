/*
author: 牛肉爱吃dks
starting time: 2023.06.04 17:47:53
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define ll long long
#define int long long
#define PII std::pair<int, int>
#define X first
#define Y second
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
const int N = 1e5 + 5, INF = 0x3f3f3f3f;
int n, a[N];
struct node{
    node *ls, *rs;
    int key, sz, rev;
    PII val, mn;
    node(){ls = rs = NULL; key = sz = rev; val = mn = (PII){0, 0};}
    node(int _key, PII _val){ls = rs = NULL; rev = 0; key = _key, val = mn = _val, sz = 1;}
}*rt;
#define get_sz(u) ((u) ? (u) -> sz : 0)
#define get_mn(u) ((u) ? (u) -> mn : (PII){INF, INF})
inline void pushup(node *u){
    if(!u) return;
    u -> sz = get_sz(u -> ls) + 1 + get_sz(u -> rs);
    u -> mn = min(u -> val, min(get_mn(u -> ls), get_mn(u -> rs)));
}
inline void rev(node *u){if(!u) return; std::swap(u -> ls, u -> rs); u -> rev ^= 1;}
inline void pushdown(node *u){if(u && u -> rev){rev(u -> ls); rev(u -> rs); u -> rev = 0;}}
void split(int sz, node *p, node *&u, node *&v){
    if(!p) u = v = NULL;
    else{
        pushdown(p);
        if(get_sz(p -> ls) < sz){u = p; split(sz - get_sz(u -> ls) - 1, p -> rs, u -> rs, v);}
        else{v = p; split(sz, p -> ls, u, v -> ls);}
        pushup(p);
    }
}
node *merge(node *u, node *v){
    if(!u || !v) return u ? u : v;
    if(u -> key > v -> key){pushdown(u); u -> rs = merge(u -> rs, v); pushup(u); return u;}
    else{pushdown(v); v -> ls = merge(u, v -> ls); pushup(v); return v;}
}
inline void insert(int sz, PII val){
    node *u, *v; split(sz, rt, u, v);
    rt = merge(u, merge(new node(rand(), val), v));
}
inline int query(){
    node *u = rt;
    int res = 1;
    while(u){
        pushdown(u);
        if(get_mn(u -> ls) == rt -> mn) u = u -> ls;
        else if(u -> val == rt -> mn) return res + get_sz(u -> ls);
        else res += get_sz(u -> ls) + 1, u = u -> rs;
    }
    return res;
}
signed main(){
    read(n);
    uF(i, 1, n) insert(i - 1, (PII){read<int>(), i});
    uF(i, 1, n){
        int p = query();
        write(i + p - 1, " ");
        node *u, *v, *w; split(p, rt, u, w); split(p - 1, u, u, v);
        rev(u); rt = merge(u, w);
    }
    lovely _lzy_;
}
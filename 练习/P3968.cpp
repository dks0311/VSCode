/*
author: 牛肉爱吃dks
starting time: 2023.06.05 08:54:55
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
int n, m;
std::unordered_map<int, int> pos;
#define get_mx(u) (u ? u -> mx : 0)
#define get_sz(u) (u ? u -> sz : 0)
struct node{
    node *ls, *rs;
    int key, pos, len, mx, sz;
    node(){ls = rs = NULL; key = pos = len = mx = sz = 0;}
    node(int _key, int _pos, int _len){ls = rs = NULL, key = _key, pos = _pos, mx = len = _len, sz = 1;}
    inline void pushup(){
        mx = max(len, max(get_mx(ls), get_mx(rs)));
        sz = get_sz(ls) + 1 + get_sz(rs);
    }
}*rt;
void split(int pos, node *p, node *&u, node *&v){
    if(!p) u = v = NULL;
    else{
        if(p -> pos <= pos){u = p; split(pos, p -> rs, u -> rs, v);}
        else{v = p; split(pos, p -> ls, u, v -> ls);}
        p -> pushup();
    }
}
node *merge(node *u, node *v){
    if(!u || !v) return u ? u : v;
    if(u -> key > v -> key){u -> rs = merge(u -> rs, v); u -> pushup(); return u;}
    else{v -> ls = merge(u, v -> ls); v -> pushup(); return v;}
}
inline int get_prev(int pos){
    node *u, *v; split(pos - 1, rt, u, v);
    if(!u) return 0;
    node *p = u;
    while(p -> rs) p = p -> rs;
    int pos1 = p -> pos;
    rt = merge(u, v);
    return pos1;
}
inline int get_len(int pos){return pos - get_prev(pos) - 1;}
inline void update(int pos){
    node *u, *v, *w; split(pos, rt, u, w);
    if(!w) return;
    node *p = w;
    while(p -> ls) p = p -> ls;
    int pos1 = p -> pos;
    split(pos1, w, v, w);
    rt = merge(u, merge(v, w));
    int len = get_len(pos1);
    split(pos1, rt, u, w); split(pos1 - 1, u, u, v);
    v -> len = len; v -> pushup();
    rt = merge(u, merge(v, w));
}
inline void insert(int pos){
    int len = get_len(pos);
    node *u, *v; split(pos, rt, u, v);
    rt = merge(u, merge(new node(rand(), pos, len), v));
    update(pos);
}
inline void del(int pos){
    node *u, *v, *w;
    split(pos, rt, u, w); split(pos - 1, u, u, v);
    rt = merge(u, w);
    update(pos);
}
inline int get_pos(){
    node *u = rt;
    while(u){
        if(get_mx(u -> rs) == rt -> mx) u = u -> rs;
        else if(u -> len == rt -> mx) break;
        else u = u -> ls;
    }
    return u -> pos - (u -> len + 1 >> 1);
}
inline int query(int l, int r){
    node *u, *v, *w; split(r, rt, u, w), split(l - 1, u, u, v);
    int res = get_sz(v);
    rt = merge(u, merge(v, w));
    return res;
}
signed main(){
    srand(time(0));
    read(n), read(m);
    insert(n + 1);
    while(m --){
        int k; read(k);
        if(!k){
            int l = read<int>(), r = read<int>();
            write(query(l, r), "\n");
        }
        else if(!pos.count(k) || !pos[k]){
            pos[k] = get_pos();
            insert(pos[k]);
        }
        else{
            del(pos[k]);
            pos[k] = 0;
        }
    }
    lovely _lzy_;
}
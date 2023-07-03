/*
author: 牛肉爱吃dks
starting time: 2023.06.05 11:15:54
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
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
int n;
#define get_sz(u) (u ? u -> sz : 0)
#define get(u, x) (u ? u -> x : 0)
struct node{
    node *ls, *rs;
    int key, val, sz;
    node(){ls = rs = NULL, key = val = sz = 0;}
    node(int _key, int _val){ls = rs = NULL, key = _key, val = _val, sz = 1;}
    inline void pushup(){sz = get_sz(ls) + 1 + get_sz(rs);}
}*rt;
void split(int val, node *p, node *&u, node *&v){
    if(!p) u = v = NULL;
    else{
        if(p -> val <= val){
            u = p; 
            split(val, p -> rs, u -> rs, v);
        }
        else{
            v = p;
            split(val, p -> ls, u, v -> ls);
        }
        p -> pushup();
    }
}
node *merge(node *u, node *v){
    if(!u || !v) return u ? u : v;
    if(u -> key > v -> key){
        u -> rs = merge(u -> rs, v);
        u -> pushup();
        return u;
    }
    else{
        v -> ls = merge(u, v -> ls);
        v -> pushup();
        return v;
    }
}
inline int get_val(int rk){
    node *u = rt;
    while(u){
        if(rk <= get(u -> ls, sz)) u = u -> ls;
        else if(rk == get(u -> ls, sz) + 1) return u -> val;
        else rk -= get_sz(u -> ls) + 1, u = u -> rs;
    }
}
inline void insert(int val){
    node *u, *v;
    split(val - 1, rt, u, v);
    rt = merge(u, merge(new node(rand(), val), v));
}
inline void del(int val){
    node *u, *v, *w;
    split(val, rt, u, w);
    split(val - 1, u, u, v);
    rt = merge(u, w);
    delete v;
}
signed main(){
    srand(time(0));
    read(n);
    uF(i, 1, n) insert(i);
    int now = 1;
    while(n --){
        int x = read<int>(), sz = rt -> sz;
        now = (now + x - 1 + sz) % sz + 1;
        int val = get_val(now);
        write(val, "\n");
        del(val);
    }
    lovely _lzy_;
}
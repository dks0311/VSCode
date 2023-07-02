/*
author: 牛肉爱吃dks
starting time: 2023.06.04 08:51:12
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
inline int h_0(int l, int r){return r - l + 1;}
inline int h_1(int l, int r){return (l + r) * (r - l + 1) >> 1;}
inline int h_2(int l, int r){-- l; return (r * (r + 1) * (r + r + 1) - l * (l + 1) * (l + l + 1)) / 6;}
const int N = 1e5 + 5;
int n, m, a[N];
struct Val{
    int v0, v1, v2;
    Val(){v0 = v1 = v2 = 0;}
    Val(int _v0, int _v1, int _v2){v0 = _v0, v1 = _v1, v2 = _v2;}
    Val operator + (const Val &t) const{return Val(v0 + t.v0, v1 + t.v1, v2 + t.v2);}
};
//v0:a[i] v1:a[i] * i v2:a[i] * i * i
struct node{int l, r, add; Val val; node(){l = r = add = 0, val = Val();}}tr[N << 2];
inline void add(int p, int x){
    tr[p].val.v0 += h_0(tr[p].l, tr[p].r) * x;
    tr[p].val.v1 += h_1(tr[p].l, tr[p].r) * x;
    tr[p].val.v2 += h_2(tr[p].l, tr[p].r) * x;
    tr[p].add += x;
}
inline void pushup(int p){tr[p].val = tr[p << 1].val + tr[p << 1 | 1].val;}
inline void pushdown(int p){if(tr[p].add){add(p << 1, tr[p].add); add(p << 1 | 1, tr[p].add); tr[p].add = 0;}}
void build(int l, int r, int p){
    tr[p].l = l, tr[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    pushup(p);
}
void modify(int l, int r, int x, int p){
    if(l <= tr[p].l && tr[p].r <= r){add(p, x); return;}
    pushdown(p);
    int mid = tr[p].l + tr[p].r >> 1;
    if(l <= mid) modify(l, r, x, p << 1);
    if(r > mid) modify(l, r, x, p << 1 | 1);
    pushup(p);
}
Val query(int l, int r, int p){
    if(l <= tr[p].l && tr[p].r <= r) return tr[p].val;
    pushdown(p);
    int mid = tr[p].l + tr[p].r >> 1; Val res = Val();
    if(l <= mid) res = res + query(l, r, p << 1);
    if(r > mid) res = res + query(l, r, p << 1 | 1);
    return res;
}
signed main(){
    n = read<int>(), m = read<int>();
    build(1, n - 1, 1);
    while(m --){
        char opt; std::cin >> opt;
        if(opt == 'C'){
            int l = read<int>(), r = read<int>() - 1, v = read<int>();
            modify(l, r, v, 1);
        }
        else{
            int l = read<int>(), r = read<int>() - 1;
            Val res = query(l, r, 1);
            int x = res.v0 * (-l * r - l + r + 1) + res.v1 * (l + r) + res.v2 * -1;
            int y = (r - l + 1) * (r - l) / 2 + (r - l + 1), t = std::__gcd(x, y);
            printf("%lld/%lld\n", x / t, y / t);
        }
    }
    lovely _lzy_;
}
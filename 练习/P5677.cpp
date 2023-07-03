/*
author: 牛肉爱吃dks
starting time: 2023.06.07 13:54:24
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define ll long long
#define int long long
#define DB double
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
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmul(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
template<typename T> void debug(const char *s, T *a, int l, int r){
    printf("%s:\n", s);
    uF(i, l, r) std::cout << a[i] << " ";
    puts("");
}
const int N = 3e5 + 5;
int n, m, tot;
struct Query{
    int l, r, id;
    bool operator < (const Query &t) const{return r < t.r;}
    Query(){l = r = id = 0;}
    Query(int _l, int _r, int _id){l = _l, r = _r, id = _id;}
}q[N];
struct Pair{
    int l, r;
    bool operator < (const Pair &t) const{return r < t.r;}
    Pair(){l = r = 0;}
    Pair(int _l, int _r){l = min(_l, _r), r = max(_l, _r);}
}b[N << 1];
PII a[N];
int t[N];
inline int lowbit(int x){return x & -x;}
inline void add(int x){for(; x <= n; x += lowbit(x)) ++ t[x];}
inline int query(int x){
    int res = 0;
    for(; x; x -= lowbit(x)) res += t[x];
    return res;
}
signed main(){
    n = read<int>(), m = read<int>();
    if(n == 1){
        puts("0");
        return 0;
    }
    uF(i, 1, n) a[i] = (PII){read<int>(), i};
    std::sort(a + 1, a + n + 1);
    uF(i, 1, n){
        if(i == 1) b[++ tot] = Pair(a[1].Y, a[2].Y);
        else if(i == n) b[++ tot] = Pair(a[n - 1].Y, a[n].Y);
        else{
            int x = min(a[i].X - a[i - 1].X, a[i + 1].X - a[i].X);
            if(a[i].X - a[i - 1].X == x) b[++ tot] = Pair(a[i].Y, a[i - 1].Y);
            if(a[i + 1].X - a[i].X == x) b[++ tot] = Pair(a[i + 1].Y, a[i].Y);
        }
    }
    uF(i, 1, m){
        int l = read<int>(), r = read<int>();
        q[i] = Query(l, r, i);
    }
    std::sort(q + 1, q + m + 1);
    std::sort(b + 1, b + tot + 1);
    // for(int i = 1; i <= m; ++ i) printf("%d %d %d\n", q[i].l, q[i].r, q[i].id);
    int p = 1, ans = 0;
    uF(i, 1, m){
        for(; p <= tot && b[p].r <= q[i].r; ++ p) add(b[p].l);
        ans += (p - 1 - query(q[i].l - 1)) * q[i].id;
    }
    write(ans, "\n");
    lovely _lzy_;
}
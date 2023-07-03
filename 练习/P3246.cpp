/*
author: 牛肉爱吃dks
starting time: 2023.06.04 11:03:42
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
template<typename T1, typename T2> inline void updmlt(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
const int N = 1e5 + 5;
int n, m, a[N], part, ans[N];
int st[N], top, lm[N][20], rm[N][20], slm[N], srm[N];
struct Query{
    int l, r, id;
    bool operator < (const Query &t) const{return l / part != t.l / part ? l < t.l : (l / part & 1 ? r < t.r : r > t.r);}
}q[N];
inline int calcl(int l, int r){
    int p = l;
    dF(i, 16, 0) if(rm[p][i] <= r && rm[p][i]) p = rm[p][i];
    return srm[l] - srm[p] + a[p] * (r - p + 1);
}
inline int calcr(int l, int r){
    int p = r;
    dF(i, 16, 0) if(lm[p][i] >= l) p = lm[p][i];
    return slm[r] - slm[p] + a[p] * (p - l + 1);
}
signed main(){
    read(n), read(m);
    part = sqrt(n);
    uF(i, 1, n) read(a[i]);
    uF(i, 1, m) q[i] = (Query){read<int>(), read<int>(), i};
    std::sort(q + 1, q + m + 1);
    uF(i, 1, n){
        while(top && a[i] < a[st[top]]) -- top;
        lm[i][0] = st[top], st[++ top] = i;
    }
    st[0] = n + 1, top = 0;
    dF(i, n, 1){
        while(top && a[i] <= a[st[top]]) -- top;
        rm[i][0] = st[top], st[++ top] = i;
    }
    uF(j, 1, 16) uF(i, 1, n) lm[i][j] = lm[lm[i][j - 1]][j - 1], rm[i][j] = rm[rm[i][j - 1]][j - 1];
    uF(i, 1, n) slm[i] = slm[lm[i][0]] + (i - lm[i][0]) * a[i];
    dF(i, n, 1) srm[i] = srm[rm[i][0]] + (rm[i][0] - i) * a[i];
    int l = 1, r = 0, res = 0;
    uF(i, 1, m){
        while(l > q[i].l) res += calcl(-- l, r);
        while(r < q[i].r) res += calcr(l, ++ r);
        while(l < q[i].l) res -= calcl(l ++, r);
        while(r > q[i].r) res -= calcr(l, r --);
        ans[q[i].id] = res;
    }
    uF(i, 1, m) write(ans[i], "\n");
    lovely _lzy_;
}
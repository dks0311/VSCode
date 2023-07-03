#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define LL long long
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
#define init(x, y) memset(x, y, sizeof x)
#define copy(x, y) memcpy(x, y, sizeof x)
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
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
const int N = 2e5 + 5;
int n, a, b, ans, idx;
struct node{int ls, rs, sz; node(){ls = rs = sz = 0;}}tr[N * 20];
inline void pushup(int u){tr[u].sz = tr[tr[u].ls].sz + tr[tr[u].rs].sz;}
int insert(int l, int r, int x){
    int now = ++ idx;
    tr[now].sz = 1;
    if(l == r) return now;
    int mid = l + r >> 1;
    if(x <= mid) tr[now].ls = insert(l, mid, x);
    else tr[now].rs = insert(mid + 1, r, x);
    return now;
}
int merge(int l, int r, int u, int v){
    if(!u || !v) return u + v;
    a += tr[tr[u].rs].sz * tr[tr[v].ls].sz;
    b += tr[tr[u].ls].sz * tr[tr[v].rs].sz;
    tr[u].sz += tr[v].sz;
    if(l == r){tr[u].sz += tr[v].sz; return u;}
    int mid = l + r >> 1;
    tr[u].ls = merge(l, mid, tr[u].ls, tr[v].ls);
    tr[u].rs = merge(mid + 1, r, tr[u].rs, tr[v].rs);
    return u;
}
int input(){
    int x = read<int>();
    if(!x){
        int u = input(), v = input();
        a = b = 0;
        int tmp = merge(1, n, u, v);
        ans += min(a, b);
        return tmp;
    }
    return insert(1, n, x);
}
signed main(){
    n = read<int>();
    input();
    write(ans, "\n");
    lovely _lzy_;
}
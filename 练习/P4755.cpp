#include <bits/stdc++.h>
using namespace std;
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
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 1e5 + 5;
int n, a[N], b[N];
int f[N][20], lg[N];
struct QUERY{
    int x, v, w;
    QUERY(){x = v = w = 0;}
    QUERY(int _x, int _v, int _w){x = _x, v = _v, w = _w;}
};
vector<QUERY> q;
inline int query(int l, int r){
    int len = lg[r - l + 1];
    if(a[f[l][len]] > a[f[r - (1 << len) + 1][len]]) return f[l][len];
    return f[r - (1 << len) + 1][len];
}
void calc(int l, int r){
    if(l > r) return;
    int mid = query(l, r);
    if(mid - l <= r - mid)
        uF(i, l, mid) q.push_back(QUERY(r, 1, (int)a[mid] / a[i])), q.push_back(QUERY(mid - 1, -1, (int)a[mid] / a[i]));
    else
        uF(i, mid, r) q.push_back(QUERY(mid, 1, (int)a[mid] / a[i])), q.push_back(QUERY(l - 1, -1, (int)a[mid] / a[i]));
    calc(l, mid - 1);
    calc(mid + 1, r);
}
int t[N];
inline int lowbit(int x){return x & -x;}
inline void add(int x){
    for(; x <= n; x += lowbit(x)) ++ t[x];
}
inline int query(int x){
    int res = 0;
    for(; x; x -= lowbit(x)) res += t[x];
    return res;
}
signed main(){
    n = read<int>();
    uF(i, 1, n) a[i] = b[i] = read<int>(), f[i][0] = i;
    sort(b + 1, b + n + 1);
    int tot = unique(b + 1, b + n + 1) - b - 1;
    uF(j, 1, 16) uF(i, 1, n){
        f[i][j] = f[i][j - 1];
        if(i + (1 << j - 1) <= n && a[f[i + (1 << j - 1)][j - 1]] > a[f[i][j]])
            f[i][j] = f[i + (1 << j - 1)][j - 1];
    }
    uF(i, 2, n) lg[i] = lg[i >> 1] + 1;
    calc(1, n);
    for(auto &t : q) t.w = upper_bound(b + 1, b + tot + 1, t.w) - b - 1;
    sort(q.begin(), q.end(), [](QUERY a, QUERY b){return a.x < b.x;});
    int p = 0, res = 0;
    for(auto t : q){
        while(p < t.x) add(lower_bound(b + 1, b + tot + 1, a[++ p]) - b);
        int tmp = query(t.w) * t.v;
        res += query(t.w) * t.v;
    }
    write(res, "\n");
    lovely _lzy_;
}
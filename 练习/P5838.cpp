#include <bits/stdc++.h>
using namespace std;
#define lovely return
#define _lzy_ 0
#define LL long long
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
int n, m;
int head[N], ne[N << 1], to[N << 1], idx;
int a[N], p[N], co[N], tag[N];
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
std::vector<PII> q[N];
PII r[N];
void dfs(int u, int fa){
    int tmp = p[a[fa]];
    p[a[fa]] = u;
    for(auto t : q[u])
        if(!r[t.Y].X) r[t.Y].X = p[t.X];
        else r[t.Y].Y = p[t.X];
    ef(i, u) if(to[i] != fa) dfs(to[i], u);
    p[a[fa]] = tmp;
}
signed main(){
    n = read<int>(), m = read<int>();
    uF(i, 1, n) a[i] = read<int>(), p[i] = 1;
    uf(i, 1, n){
        int u = read<int>(), v = read<int>();
        add(u, v); add(v, u);
    }
    uF(i, 1, m){
        int u = read<int>(), v = read<int>(), c = read<int>();
        q[u].push_back((PII){c, i});
        q[v].push_back((PII){c, i});
        co[i] = c;
        if(c == a[u] || c == a[v]) tag[i] = 1;
    }
    dfs(1, 0);
    uF(i, 1, m) 
        if(tag[i] || r[i].X != r[i].Y) putchar('1');
        else putchar('0');
    lovely _lzy_;
}
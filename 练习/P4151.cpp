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
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 5e4 + 5, M = 2e5 + 5;
int n, m;
int head[N], ne[M], to[M], wgt[M], idx;
inline void add(int u, int v, int w){to[++ idx] = v, ne[idx] = head[u], head[u] = idx, wgt[idx] = w;}
struct linear_base{
    int a[65];
    void insert(int x){
        dF(i, 60, 0){
            if(!(x >> i)) continue;
            if(!a[i]){a[i] = x; break;}
            x ^= a[i];
        }
    }
    int query(int x){
        dF(i, 60, 0) if(!(x >> i & 1)) x ^= a[i];
        return x;
    }
}lb;
int dis[N];
bool vis[N], vise[M];
void dfs(int u){
    vis[u] = true;
    ef(i, u){
        if(vise[i]) continue;
        vise[i] = vise[i ^ 1] = true;
        int v = to[i];
        if(vis[v]){
            lb.insert(dis[u] ^ wgt[i] ^ dis[v]);
            continue;
        }
        dis[v] = dis[u] ^ wgt[i];
        dfs(v);
    }
}
signed main(){
    n = read<int>(), m = read<int>();
    uF(i, 1, m){
        int u = read<int>(), v = read<int>(), w = read<int>();
        add(u, v, w); add(v, u, w);
    }
    dfs(1);
    write(lb.query(dis[n]), "\n");
    lovely _lzy_;
}
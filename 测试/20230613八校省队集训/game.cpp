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
const int N = 5e5 + 5;
int n, m;
// int head[N], ne[N], to[N], idx;
// inline void add(int u, int v){
//     to[++ idx] = v, ne[idx] = head[u], head[u] = idx;
// }
struct Edge{int u, v;}e[N];
int flag[N], c[N << 1];
int dfs(int p, int ab){
    if(p == n + 1){
        uF(i, 1, m)
            if(!c[e[i].u] && c[e[i].v]) return 0;
        return 1;
    }
    int res = ab ^ 1;
    c[p << 1] = 0, c[p << 1 | 1] = 1;
    if(ab) res = max(res, dfs(p + 1, 0));
    else res = min(res, dfs(p + 1, 1));
    c[p << 1] = 1, c[p << 1 | 1] = 0;
    if(ab) res = max(res, dfs(p + 1, 0));
    else res = min(res, dfs(p + 1, 1));
    return res;
}
int dfs1(int p, int ab){
    if(p == n + 1){
        uF(i, 1, m)
            if(!c[e[i].u] && c[e[i].v]) return 0;
        return 1;
    }
    uF(i, 1, m) if(c[e[i].u] && !c[e[i].v]) return 0;
    int res = ab ^ 1;
    c[p << 1] = 0, c[p << 1 | 1] = 1;
    if(ab) res = max(res, dfs1(p + 1, 0));
    else res = min(res, dfs1(p + 1, 1));
    c[p << 1] = 1, c[p << 1 | 1] = 0;
    if(ab) res = max(res, dfs1(p + 1, 0));
    else res = min(res, dfs1(p + 1, 1));
    return res;
}
signed main(){
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    n = read<int>(), m = read<int>();
    uF(i, 1, m){
        e[i].u = read<int>() + 1, e[i].v = read<int>() + 1;
        if((e[i].u ^ 1) == e[i].v) ++ flag[e[i].u >> 1];
    }
    bool flag1 = true;
    uF(i, 1, n) if(!flag[i]) flag1 = false;
    if(flag1){
        if(n > 1) puts("Bob");
        else if(n == 1 && flag[1] > 1) puts("Bob");
        else puts("Alice");
    }
    else if(n <= 10){
        if(dfs(1, 1)) puts("Alice");
        else puts("Bob");
    }
    else if(n <= 100){
        if(dfs1(1, 1)) puts("Alice");
        else puts("Bob");
    }
    else{
        srand(time(0));
        if(rand() & 1) puts("Alice");
        else puts("Bob");
    }
    lovely _lzy_;
}
#include <bits/stdc++.h>
namespace _default{
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
    #define sett(x, y) memset(x, y, sizeof x)
    #define copy(x, y) memcpy(x, y, sizeof x)
    const int MOD = 1e9 + 7, INF = 0x3f3f3f3f;
    const DB EPS = 1e-8;
    template<typename T> T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0){putchar('-'); x = -x;}
        if(!x) putchar('0');
        while(x) st[++ top] = x % 10, x /= 10;
        while(top) putchar(st[top --] + 48);
        printf("%s", s);
    }
    template<typename T> void updmin(T &x, T y){if(x > y) x = y;}
    template<typename T> void updmax(T &x, T y){if(x < y) x = y;}
    template<typename T> void updadd(T &x, T y){(x += y % MOD) %= MOD;}
    template<typename T> void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
const int N = 1e3 + 5;
int n, m, ans;
int d[N][N][4], f[N][N];
bool bl[N][N], vis[N][N];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool check(PII p){
    int x = p.X, y = p.Y;
    return (!bl[x][y] && !vis[x][y] && x >= 1 && x <= n && y >= 1 && y <= n);
}
void BFS(){
    queue<pair<PII, int> > q;
    q.push({{0, 1}, -1});
    while(!q.empty()){
        pair<PII, int> tmp = q.front(); q.pop();
        PII u = tmp.X;
        if(u.X) ans += tmp.Y;
        uf(i, 0, 4){
            PII v = {u.X + dx[i], u.Y + dy[i]};
            while(check(v)){
                vis[v.X][v.Y] = true;
                q.push({{v.X, v.Y}, tmp.Y + 1});
                v.X += dx[i], v.Y += dy[i];
            }
        }
    }
}
signed main(){
    freopen("mirror.in", "r", stdin);
    freopen("mirror.out", "w", stdout);
    n = read<int>(), m = read<int>();
    uF(i, 1, m){
        int x = read<int>(), y = read<int>();
        bl[x][y] = true;
    }
    BFS();
    write(ans, "\n");
    lovely _lzy_;
}
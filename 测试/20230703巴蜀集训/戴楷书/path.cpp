#include <bits/stdc++.h>
namespace _default{
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
    #define sett(x, y) memset(x, y, sizeof x)
    #define copy(x, y) memcpy(x, y, sizeof x)
    const int MOD = 1e9 + 7, INF = 0x3f3f3f3f;
    const DB EPS = 1e-8;
    template<typename T> inline T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> inline void write(T x, const char *s = ""){
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
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
const int N = 1e3 + 5;
int n, m, c[N];
bool flag = true;
namespace _40pts{
    vector<int> pp[N];
    int p[15], d[N][N];
    bool chs[N];
    void Solve(){
        memset(d, 0x3f, sizeof d);
        int tot = 0;
        uF(i, 2, n){
            if(!p[c[i]]) p[c[i]] = ++ tot;
            pp[p[c[i]]].push_back(i);
        }
        uF(i, 1, m){
            int u = read<int>() + 1, v = read<int>() + 1, w = read<int>();
            updmin(d[u][v], w);
        }
        int ans = INF;
        chs[n + 1] = true;
        uF(s, 0, 1 << tot){
            uF(i, 1, tot){
                if(!(s >> i - 1 & 1)) continue;
                for(auto x : pp[i]) chs[x] = true;
            }
            int last = 1, res = 0;
            uF(i, 2, n + 1){
                if(!chs[i]) continue;
                if(d[last][i] == INF){res = INF; break;}
                res += d[last][i], last = i;
            }
            updmin(ans, res);
            uF(i, 1, tot){
                if(!(s >> i - 1 & 1)) continue;
                for(auto x : pp[i]) chs[x] = false;
            }
        }
        write(ans == INF ? -1 : ans, "\n");
    }
}
signed main(){
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    n = read<int>(), m = read<int>();
    uF(i, 2, n) c[i] = read<int>(), flag = c[i] > 10 ? false : flag;
    if(flag || n <= 10){
        _40pts::Solve();
        return 0;
    }
    else puts("-1");
    lovely _lzy_;
}
/*
7 11
1 2 3 3 1 3
0 1 1
1 2 1
2 4 1
4 5 1
5 6 1
6 7 1
0 2 10
2 5 2
5 7 3
2 7 1
3 4 1
*/
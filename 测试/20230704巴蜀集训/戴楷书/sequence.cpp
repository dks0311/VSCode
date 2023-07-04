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
    const int MOD = 998244353, INF = 0x3f3f3f3f;
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
const int N = 1 << 20 | 5;
int n, l[15], r[15];
int wl[15], wr[15];
int f[32][N], C[11][11], aannss[32];
int DFS(int wei, int s){
    if(wei == -1) return 1;
    if(f[wei][s] != -1) return f[wei][s];
    if(!s) return aannss[wei + 1];
    int res = 0, tot = 0, tt = 0, dc = 0, ds = 0;
    vector<int> xz;
    uf(i, 0, n){
        int lml = (s >> (i << 1) & 1) ? l[i] >> wei & 1 : -1;
        int lmr = (s >> (i << 1 | 1) & 1) ? r[i] >> wei & 1 : -1;
        if(!(s >> (i << 1) & 3)) ++ tot;
        else if(lml == 1 || lmr == 0 || lml == lmr){
            int c = (lml == 1);
            if(lml != -1 && c == lml && wei > wl[i]) ds |= 1 << (i << 1);
            if(lmr != -1 && c == lmr && wei > wr[i]) ds |= 1 << (i << 1 | 1);
            ++ tt, dc += c;
        }
        else xz.push_back(i);
    }
    uf(ss, 0, 1 << (n - tot - tt)){
        int ns = 0, cnt = 0;
        uf(i, 0, n - tot - tt) cnt += ss >> i & 1;
        bool flag = true;
        for(int i = 0; i < n - tot - tt; ++ i){
            int c = ss >> i & 1;
            int lml = (s >> (xz[i] << 1) & 1) ? l[xz[i]] >> wei & 1 : -1;
            int lmr = (s >> (xz[i] << 1 | 1) & 1) ? r[xz[i]] >> wei & 1 : -1;
            if(lml != -1 && c == lml && wei > wl[xz[i]]) ns |= 1 << (xz[i] << 1);
            if(lmr != -1 && c == lmr && wei > wr[xz[i]]) ns |= 1 << (xz[i] << 1 | 1);
        }
        if(!flag) continue;
        ns |= ds, cnt += dc;
        if(cnt % 3 == 0)
            updadd(res, DFS(wei - 1, ns) * (1 + C[tot][3] + C[tot][6] + C[tot][9]));
        else if(cnt % 3 == 1)
            updadd(res, DFS(wei - 1, ns) * (C[tot][2] + C[tot][5] + C[tot][8]));
        else
            updadd(res, DFS(wei - 1, ns) * (C[tot][1] + C[tot][4] + C[tot][7]));
    }
    return f[wei][s] = res;
}
signed main(){
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    n = read<int>();
    uF(i, 0, n){
        C[i][0] = 1;
        uF(j, 1, i) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    aannss[0] = 1;
    uF(i, 1, 30) aannss[i] = aannss[i - 1] * (1ll + C[n][3] + C[n][6] + C[n][9]) % MOD;
    uf(i, 0, n) l[i] = read<int>(), r[i] = read<int>();
    uf(i, 0, n){
        wl[i] = wr[i] = -1;
        uf(j, 0, 30){
            if(wl[i] == -1 && l[i] >> j & 1) wl[i] = j;
            if(wr[i] == -1 && !(r[i] >> j & 1)) wr[i] = j;
        }
    }
    sett(f, -1);
    int s = 0;
    uf(i, 0, n){
        if(wl[i] != -1) s |= 1 << (i << 1);
        if(wr[i] != -1) s |= 1 << (i << 1 | 1);
    }
    write(DFS(29, s), "\n");
    lovely _lzy_;
}
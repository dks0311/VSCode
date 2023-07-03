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
    const int MOD = 1e9 + 7;
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
const int N = 1e6 + 5;
int T, C, n, m;
int a[N], b[N], pa[N], pb[N], p[N];
int ne[N];
vector<int> ans;
signed main(){
    freopen("xiz2.in", "r", stdin);
    freopen("xiz.out", "w", stdout);
    T = read<int>(), C = read<int>();
    // scanf("%lld%lld", &T, &C);
    // printf("T:%lld C:%lld\n", T, C);
    while(T --){
        n = read<int>(), m = read<int>();
        uF(i, 1, n) a[i] = read<int>();
        uF(i, 1, m) b[i] = read<int>();
        // printf("n:%d m:%d\n", n, m);
        // puts("114512");
        sett(p, 0);
        uF(i, 1, n) pa[i] = p[a[i]] ? i - p[a[i]] : 0, p[a[i]] = i;
        sett(p, 0);
        uF(i, 1, n) pb[i] = p[b[i]] ? i - p[b[i]] : 0, p[b[i]] = i;
        // uF(i, 1, n) write(pa[i], " ");
        // puts("");
        // uF(i, 1, m) write(pb[i], " ");
        // puts("");
        // uF(i, 1, C) write(p[i], " ");
        // puts("");
        // puts("114513");
        for(int i = 2, j = 0; i <= m; ++ i){
            while(j && !(pb[i] == pb[j + 1] || pb[i] >= j + 1 && !pb[j + 1])) j = ne[j];
            if(pb[i] == pb[j + 1] || pb[i] >= j + 1 && !pb[j + 1]) ++ j;
            ne[i] = j;
        }
        // puts("114514");
        ans.clear();
        for(int i = 1, j = 0; i <= n; ++ i){
            while(j && !(pa[i] == pb[j + 1] || pa[i] >= j + 1 && !pb[j + 1])) j = ne[j];
            if(pa[i] == pb[j + 1] || pa[i] >= j + 1 && !pb[j + 1]) ++ j;
            if(j == m){
                ans.push_back(i - m + 1);
                j = ne[j];
            }
        }
        // puts("114515");
        write(ans.size(), "\n");
        for(auto x : ans) write(x, " ");
        puts("");
        // puts("114516");
    }
    lovely _lzy_;
}
/*
3 3
6 3
1 2 1 2 3 2
3 1 3
6 3
1 2 1 2 1 2
3 1 3
6 3
1 1 2 1 2 1
3 1 3
*/
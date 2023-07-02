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
const int N = 505, M = 2.5e5 + 5;
int n, dp[3][M], maxn = 2.5e5;
signed main(){
    n = read<int>();
    uF(i, 1, n){
        char ch; std::cin >> ch;
        int aa = read<int>(), bb = read<int>();
        int t = ch == 'A' ? 0 : ch == 'B' ? 1 : 2;
        dF(j, maxn, aa) updmax(dp[t][j], dp[t][j - aa] + bb);
    }
    uf(i, 0, 3) uF(j, 1, maxn) updmax(dp[i][j], dp[i][j - 1]);
    int p[3] = {0, 0, 0}, ans = 0;
    uF(mx, 0, maxn + maxn){
        uf(i, 0, 3) while(p[i] < maxn && dp[i][p[i] + 1] + p[i] + 1 <= mx) ++ p[i];
        int res = 0; uf(i, 0, 3) res += dp[i][p[i]];
        updmax(ans, res - mx);
    }
    write(ans, "\n");
    lovely _lzy_;
}
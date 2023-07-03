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
int n, f[2][N][20], lg[N], ans;
inline int query1(int l, int r){
    int len = lg[r - l + 1];
    return max(f[0][l][len], f[0][r - (1 << len) + 1][len]);
}
inline int query2(int l, int r){
    int len = lg[r - l + 1];
    return min(f[1][l][len], f[1][r - (1 << len) + 1][len]);
}
signed main(){
    n = read<int>();
    uF(i, 1, n) f[0][i][0] = read<int>();
    uF(i, 1, n) f[1][i][0] = read<int>();
    uF(j, 1, 17) uF(i, 1, n){
        f[0][i][j] = f[0][i][j - 1], f[1][i][j] = f[1][i][j - 1];
        if(i + (1 << j - 1) <= n)
            updmax(f[0][i][j], f[0][i + (1 << j - 1)][j - 1]),
            updmin(f[1][i][j], f[1][i + (1 << j - 1)][j - 1]);
    }
    uF(i, 2, n) lg[i] = lg[i >> 1] + 1;
    uF(i, 1, n){
        if(f[0][i][0] > f[1][i][0]) continue;
        if(query1(i, n) < query2(i, n)) continue;
        int l = i, r = n;
        while(l < r){
            int mid = l + r >> 1;
            if(query1(i, mid) - query2(i, mid) >= 0) r = mid;
            else l = mid + 1;
        }
        if(f[0][i][0] == f[1][i][0]) l = i;
        if(query1(i, l) != query2(i, l)) continue;
        int L = l;
        l = i, r = n;
        while(l < r){
            int mid = l + r + 1 >> 1;
            if(query1(i, mid) - query2(i, mid) <= 0) l = mid;
            else r = mid - 1;
        }
        if(query1(i, n) == query2(i, n)) l = n;
        if(query1(i, l) != query2(i, l)) continue;
        int R = l;
        ans += R - L + 1;
    }
    write(ans, "\n");
    lovely _lzy_;
}
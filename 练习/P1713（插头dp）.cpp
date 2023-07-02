#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
const int MOD = 1e9 + 7;
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline void write(int x, std::string s){
    static int st[40]; int top = 0;
    if(x < 0){putchar('-'); x = -x;}
    if(!x) putchar('0');
    while(x) st[++ top] = x % 10, x /= 10;
    while(top) putchar(st[top --] + 48);
    std::cout << s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
inline void updmin(int &x, int y){if(x > y) x = y;}
inline void updmax(int &x, int y){if(x < y) x = y;}
inline void updadd(int &x, int y){(x += y % MOD) %= MOD;}
inline void updmlt(int &x, int y){x += (y % MOD) % MOD;}
const int N = 1e6 + 5, M = N * 3;
int n, m, g[15][15];
int h[2][M], dp[2][M], q[2][N], cnt[2];
inline int find(int cur, int state){
    int t = state % M;
    while(h[cur][t] != state && h[cur][t] != -1) if(++ t == M) t = 0;
    return t;
}
inline void insert(int cur, int state, int val){
    int t = find(cut, state);
    if(h[cur][t] == -1) h[cur][t] = state, dp[cur][t] = val, q[cur][++ cnt[cur]] = t;
    else updmax(dp[cur][t], val);
}
inline int get(int state, int k){return state >> k + k & 3;}
inline int form(int x, int k){return x << k + k;}
signed main(){
    n = read(), m = read();
    for(int i = 1; i <= n; ++ i) for(int j = 1; j <= n; ++ j) g[i][j] = 1;
    for(int i = 1; i <= m; ++ i) g[n - read() + 1][read()] = 0;
    memset(h, -1, sizeof h);
    lovely _lzy_;
}
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
const int MOD = 20110520;
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
int n, m, g[105][105], end_x, end_y;
int h[2][M], dp[2][M], q[2][N], cnt[2];
char s[105];
inline int find(int cur, int state){
    int t = state % M;
    while(h[cur][t] != state && h[cur][t] != -1) if(++ t == M) t = 0;
    return t;
}
inline void insert(int cur, int state, int val){
    int t = find(cur, state);
    if(h[cur][t] == -1) h[cur][t] = state, dp[cur][t] = val, q[cur][++ cnt[cur]] = t;
    else updadd(dp[cur][state], val);
}
inline int get(int state, int k){return state >> k + k & 3;}
inline int form(int x, int k){return x << k + k;}
signed main(){
    n = read(), m = read();
    for(int i = 1; i <= n; ++ i){
        scanf("%s", s + 1);
        for(int j = 1; j <= m; ++ j)
            if(s[j] == '_') g[i][j] = 1;
    }
    if(n < m){
        std::swap(n, m);
        for(int i = 2; i <= n; ++ i)
            for(int j = 1; j < i; ++ j) std::swap(g[i][j], g[j][i]);
    }
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j)
            if(g[i][j]) end_x = i, end_y = j;
    memset(h, -1, sizeof h);
    int cur = 0, ans = 0;
    insert(cur, 0, 1);
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= cnt[cur]; ++ j)
            h[cur][q[cur][j]] <<= 2;
        for(int j = 1; j <= m; ++ j){
            int last = cur; cur = cur ^ 1, cnt[cur] = 0;
            memset(h[cur], -1, sizeof h[cur]);
            for(int k = 1; k <= cnt[last]; ++ k){
                int state = h[last][q[last][k]], val = dp[last][q[last][k]];
                int x = get(state, j - 1), y = get(state, j);
                if(!g[i][j]) insert(cur, state, val);
                else if(!x && !y){
                    if(g[i][j + 1] && g[i + 1][j]) insert(cur, state ^ form(2, j - 1) ^ form(2, j), val);
                    if(g[i][j + 1]) insert(cur, state ^ form(1, j), val);
                    if(g[i + 1][j]) insert(cur, state ^ form(1, j - 1), val);
                }
                else if(!x && y == 1){
                    if(g[i][j + 1]) insert(cur, state ^ form(3, j), val);
                    if(g[i + 1][j]) insert(cur, state ^ form(1, j - 1) ^ form(1, j), val);
                }
                else if(!x && y == 2){
                    if(g[i + 1][j]) insert(cur, state ^ form(2, j - 1) ^ form(2, j), val);
                    insert(cur, state ^ form(2, j), val);
                    if(i == end_x && j == end_y) updadd(ans, val);
                }
                else if(x == 1 && !y){
                    if(g[i][j + 1]) insert(cur, state ^ form(1, j - 1) ^ form(1, j), val);
                    if(g[i + 1][j]) insert(cur, state ^ form(3, j - 1), val);
                }
                else if(x == 2 && !y){
                    if(g[i][j + 1]) insert(cur, state ^ form(2, j - 1) ^ form(2, j), val);
                    insert(cur, state ^ form(2, j - 1), val);
                    if(i == end_x && j == end_y) updadd(ans, val);
                }
                else if(x == 1 && y == 1){
                    insert(cur, state ^ form(1, j - 1) ^ form(1, j), val);
                    if(i == end_x && j == end_y) updadd(ans, val);
                }
            }
        }
    }
    printf("%d\n", ans);
    lovely _lzy_;
}
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
#define PII std::pair<int, int>
#define X first
#define Y second
const int MOD = 1e9 + 7;
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
inline void updmin(int &x, int y){if(x > y) x = y;}
inline void updmax(int &x, int y){if(x < y) x = y;}
inline void updadd(int &x, int y){(x += y) %= MOD;}
inline void updmlt(int &x, int y){x = x * y % MOD;}
const int N = 15, M = 1 << 9 | 5;
struct lzy{PII p; int state;};
int n, m, d;
int v[N], val[M], f[N][N][M];
bool vis[N][N][M], mp[N][N];
PII b[N];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
void spfa(PII st){
    std::queue<lzy> q;
    memset(vis, false, sizeof vis);
    memset(f, 0x3f, sizeof f);
    q.push((lzy){st, 0});
    vis[st.X][st.Y][0] = true, f[st.X][st.Y][0] = 0;
    while(!q.empty()){
        lzy tmp = q.front(); q.pop();
        int x = tmp.p.X, y = tmp.p.Y, s = tmp.state;
        vis[x][y][s] = false;
        for(int i = 0; i < 4; ++ i){
            int nx = x + dx[i], ny = y + dy[i], ns = s;
            if(nx < 1 || nx > n || ny < 1 || ny > m || mp[nx][ny]) continue;
            for(int j = 0; j < d; ++ j)
                if((x == b[j].X && nx < b[j].X || x < b[j].X && nx == b[j].X) && y > b[j].Y) ns ^= 1 << j;
            if(vis[nx][ny][ns]) continue;
            if(f[nx][ny][ns] > f[x][y][s] + 1){
                f[nx][ny][ns] = f[x][y][s] + 1;
                vis[nx][ny][ns] = true;
                q.push((lzy){(PII){nx, ny}, ns});
            }
        }
    }
}
signed main(){
    n = read(), m = read(), d = read();
    for(int i = 0; i < d; ++ i) v[i] = read();
    for(int i = 0; i < 1 << d; ++ i)
        for(int j = 0; j < d; ++ j)
            if(i >> j & 1) val[i] += v[j];
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j){
            char ch; std::cin >> ch;
            if(ch == '#') mp[i][j] = true;
            else if(ch != '0') b[ch - '0' - 1] = (PII){i, j}, mp[i][j] = true;
        }
    int ans = 0;
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= m; ++ j){
            if(!mp[i][j]) spfa((PII){i, j});
            for(int k = 0; k < 1 << d; ++ k){
                updmax(ans, val[k] - f[i][j][k]);
            }
        }
    }
    printf("%d\n", ans);
    lovely _lzy_;
}
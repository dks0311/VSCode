#include <bits/stdc++.h>
#define ll long long
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 4e4 + 5, M = N * 3;
int n, m;
int g[35][35], q[2][N], cnt[2];
ll h[2][M], v[2][M];
inline int find(int cur, ll state){
    int t = state % M;
    while(h[cur][t] != -1 && h[cur][t] != state) if(++ t == M) t = 0;
    return t;
}
inline void insert(int cur, ll state, ll w){
    int t = find(cur, state);
    if(h[cur][t] == -1)
        h[cur][t] = state, v[cur][t] = w, q[cur][++ cnt[cur]] = t;
    else v[cur][t] += w;
    return;
}
inline int get(ll state, int k){
    if(k <= m) return state >> k & 1;
    else if(k == m + 1) return state >> m + 1 & 3;
    else return state >> m + 3 & 3;
}
int main(){
    n = read(), m = read();
    for(int i = 1; i <= n; ++ i){
        char str[35]; scanf("%s", str + 1);
        for(int j = 1; j <= m; ++ j)
            g[i][j] = str[j] == '.';
    }
    memset(h, -1, sizeof h);
    int cur = 0;
    ll ans = 0;
    insert(cur, 0, 1);
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= cnt[cur]; ++ j)
            h[cur][q[cur][j]] = (h[cur][q[cur][j]] & (1ll << m + 1) - 1) << 1 ^ h[cur][q[cur][j]] & 15 << m + 1;
        for(int j = 1; j <= m; ++ j){
            int last = cur; cur ^= 1, cnt[cur] = 0;
            memset(h[cur], -1, sizeof h[cur]);
            for(int k = 1; k <= cnt[last]; ++ k){
                ll state = h[last][q[last][k]], w = v[last][q[last][k]];
                int x = get(state, j - 1), y = get(state, j);
                ll z1 = get(state, m + 1), z2 = get(state, m + 2);
                if(!g[i][j]) insert(cur, state, w);
                else if(!x && !y){
                    if(g[i + 1][j] && z1 < 3) insert(cur, state ^ 1ll << j - 1 ^ z1 << m + 1 ^ z1 + 1 << m + 1, w);
                    insert(cur, state, w);
                }
                else if(!x && y){
                    if(g[i][j + 1]) insert(cur, state, w);
                    if(g[i + 1][j]) insert(cur, state ^ 1ll << j - 1 ^ 1ll << j, w);
                }
                else if(x && !y){
                    if(z2 == 2) ans += w;
                    if(z2 < 2) insert(cur, state ^ 1ll << j - 1 ^ z2 << m + 3 ^ z2 + 1 << m + 3, w);
                    if(g[i][j + 1]) insert(cur, state ^ 1ll << j - 1 ^ 1ll << j, w);
                }
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
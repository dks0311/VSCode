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
const int N = 5e4 + 5, M = N * 3;
int T, n, m, end_x, end_y;
int g[20][20], q[2][N], cnt[2];
int h[2][M];
ll v[2][M];
inline int find(int cur, int state){
    int t = state % M;
    while(h[cur][t] != -1 && h[cur][t] != state) if(++ t == M) t = 0;
    return t;
}
inline void insert(int cur, int state, ll w){
    int t = find(cur, state);
    if(h[cur][t] == -1)
        h[cur][t] = state, v[cur][t] = w, q[cur][++ cnt[cur]] = t;
    else v[cur][t] += w;
    return;
}
inline int get(int state, int k){return state >> k & 1;}
inline int form(int k, int x){return x << k;}
int main(){
    T = read();
    while(T --){
        memset(g, 0, sizeof g);
        memset(h, -1, sizeof h);
        memset(cnt, 0, sizeof cnt);
        n = read(), m = read();
        end_x = end_y = 0;
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= m; ++ j){
                g[i][j] = read();
                if(g[i][j]) end_x = i, end_y = j;
            }
        if(!end_x){puts("1"); continue;}
        int cur = 0;
        ll ans = 0;
        insert(cur, 0, 1);
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= cnt[cur]; ++ j)
                h[cur][q[cur][j]] <<= 1;
            for(int j = 1; j <= m; ++ j){
                int last = cur; cur ^= 1, cnt[cur] = 0;
                memset(h[cur], -1, sizeof h[cur]);
                for(int k = 1; k <= cnt[last]; ++ k){
                    int state = h[last][q[last][k]];
                    ll w = v[last][q[last][k]];
                    int x = get(state, j - 1), y = get(state, j);
                    if(!g[i][j]) insert(cur, state, w);
                    else if(!x && !y){
                        if(g[i][j + 1] && g[i + 1][j]) insert(cur, state ^ form(j - 1, 1) ^ form(j, 1), w);
                    }
                    else if(!x && y){
                        if(g[i][j + 1]) insert(cur, state, w);
                        if(g[i + 1][j]) insert(cur, state ^ form(j, y) ^ form(j - 1, y), w);
                    }
                    else if(x && !y){
                        if(g[i][j + 1]) insert(cur, state ^ form(j - 1, x) ^ form(j, x), w);
                        if(g[i + 1][j]) insert(cur, state, w);
                    }
                    else{
                        insert(cur, state ^ form(j - 1, x) ^ form(j, y), w);
                        if(i == end_x && j == end_y) ans += 1ll * w;
                    }
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
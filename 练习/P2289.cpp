#include <bits/stdc++.h>
#define ll __int128
#define int __int128
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int write(ll x){
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 1e5 + 5, M = N * 3;
int n, m, end_x, end_y;
int g[25][25], q[2][N], cnt[2];
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
inline int get(int state, int k){return state >> k + k & 3;}
inline int form(int k, int x){return x << k + k;}
main(){
    n = read(), m = read();
    if(n == 1 || m == 1){puts("1"); return 0;}
    if(m > n) std::swap(n, m);
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j) g[i][j] = 1;
    end_x = n, end_y = m;
    memset(h, -1, sizeof h);
    int cur = 0;
    ll ans = 0;
    insert(cur, 0, 1);
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= cnt[cur]; ++ j)
            h[cur][q[cur][j]] <<= 2;
        for(int j = 1; j <= m; ++ j){
            int last = cur; cur ^= 1, cnt[cur] = 0;
            memset(h[cur], -1, sizeof h[cur]);
            for(int k = 1; k <= cnt[last]; ++ k){
                int state = h[last][q[last][k]];
                ll w = v[last][q[last][k]];
                int x = get(state, j - 1), y = get(state, j);
                if(!g[i][j]) insert(cur, state, w);
                else if(!x && !y){
                    if(g[i][j + 1] && g[i + 1][j]) insert(cur, state ^ form(j - 1, 1) ^ form(j, 2), w);
                }
                else if(!x && y){
                    if(g[i][j + 1]) insert(cur, state, w);
                    if(g[i + 1][j]) insert(cur, state ^ form(j, y) ^ form(j - 1, y), w);
                }
                else if(x && !y){
                    if(g[i][j + 1]) insert(cur, state ^ form(j - 1, x) ^ form(j, x), w);
                    if(g[i + 1][j]) insert(cur, state, w);
                }
                else if(x == 1 && y == 1)
                    for(int l = j + 1, c = 1; ; ++ l){
                        int tmp = get(state, l);
                        if(tmp == 1) ++ c;
                        else if(tmp == 2)
                            if(!-- c){
                                insert(cur, state ^ form(j - 1, x) ^ form(j, y) ^ form(l, 3), w);
                                break;
                            }
                    }
                else if(x == 2 && y == 2)
                    for(int l = j - 2, c = 1; ; -- l){
                        int tmp = get(state, l);
                        if(tmp == 2) ++ c;
                        else if(tmp == 1)
                            if(!-- c){
                                insert(cur, state ^ form(j - 1, x) ^ form(j, y) ^ form(l, 3), w);
                                break;
                            }
                    }
                else if(x == 2 && y == 1) insert(cur, state ^ form(j - 1, x) ^ form(j, y), w);
                else ans += 1ll * w * (i == end_x && j == end_y);
            }
        }
    }
    write(ans * 2);
    return 0;
}
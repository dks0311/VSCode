#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void write(T x, std::string s){
    static int st[40]; int top = 0;
    if(x < 0){putchar('-'); x = -x;}
    if(!x) putchar('0');
    while(x) st[++ top] = x % 10, x /= 10;
    while(top) putchar(st[top --] + 48);
    std::cout << s;
}
template<typename T1, typename T2> inline int max(T1 x, T2 y){return x > y ? x : y;}
template<typename T1, typename T2> inline int min(T1 x, T2 y){return x < y ? x : y;}
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmlt(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
const int N = 5e3 + 5, M = N * 3;
int n, m;
int a[105][10];
int h[2][M], dp[2][M], q[2][N], cnt[2];
inline int find(int cur, int state){
    int t = state % M;
    while(h[cur][t] != state && h[cur][t] != -1) if(++ t == M) t = 0;
    return t;
}
inline void insert(int cur, int state, int val){
    int t = find(cur, state);
    if(h[cur][t] == -1) h[cur][t] = state, dp[cur][t] = val, q[cur][++ cnt[cur]] = t;
    else updmax(dp[cur][state], val);
}
inline int get(int state, int k){return state >> k + k & 3;}
inline int form(int x, int k){return x << k + k;}
inline bool chk(int x, int y){return (x && x <= n && y && y <= m);}
signed main(){
    n = read<int>(), m = read<int>();
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= m; ++ j) a[i][j] = read<int>();
    memset(h, -1, sizeof h);
    int cur = 0, ans = -0x3f3f3f3f;
    insert(cur, 0, 0);
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= cnt[cur]; ++ j) h[cur][q[cur][j]] <<= 2;
        for(int j = 1; j <= m; ++ j){
            int last = cur; cur ^= 1, cnt[cur] = 0;
            memset(h[cur], -1, sizeof h[cur]);
            for(int k = 1; k <= cnt[last]; ++ k){
                int state = h[last][q[last][k]], val = dp[last][q[last][k]], nval = val + a[i][j];
                int x = get(state, j - 1), y = get(state, j);
                if(!x && !y){
                    if(chk(i, j + 1) && chk(i + 1, j)) insert(cur, state ^ form(1, j - 1) ^ form(2, j), nval);
                    insert(cur, state, val);
                }
                else if(!x && y){
                    if(chk(i, j + 1)) insert(cur, state, nval);
                    if(chk(i + 1, j)) insert(cur, state ^ form(y, j - 1) ^ form(y, j), nval);
                }
                else if(x && !y){
                    if(chk(i, j + 1)) insert(cur, state ^ form(x, j - 1) ^ form(x, j), nval);
                    if(chk(i + 1, j)) insert(cur, state, nval);
                }
                else if(x == 1 && y == 1){
                    for(int l = j + 1, t = 1; l <= m; ++ l)
                        if(get(state, l) == 1) ++ t;
                        else if(get(state, l) == 2 && !-- t){
                            insert(cur, state ^ form(x, j - 1) ^ form(y, j) ^ form(3, l), nval);
                            break;
                        }
                }
                else if(x == 2 && y == 2){
                    for(int l = j - 2, t = 1; l; -- l)
                        if(get(state, l) == 2) ++ t;
                        else if(get(state, l) == 1 && !-- t){
                            insert(cur, state ^ form(x, j - 1) ^ form(y, j) ^ form(3, l), nval);
                            break;
                        }
                }
                else if(x == 2 && y == 1) insert(cur, state ^ form(x, j - 1) ^ form(y, j), nval);
                else ans = max(ans, nval);
            }
        }
    }
    write(ans, "");
    lovely _lzy_;
}
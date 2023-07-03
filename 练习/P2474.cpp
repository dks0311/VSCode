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
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
inline void updmin(int &x, int y){if(x > y) x = y;}
inline void updmax(int &x, int y){if(x < y) x = y;}
inline void updadd(int &x, int y){(x += y) %= MOD;}
inline void updmlt(int &x, int y){x = x * y % MOD;}
const int N = 55;
int n, a, b;
int dp1[N][N], dp2[N][N];//1:min 2:max
signed main(){
    n = read(), a = read(), b = read();
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++ j){
            char ch; std::cin >> ch;
            if(i == j || ch == '=') dp1[i][j] = dp2[i][j] = 0;
            else if(ch == '-') dp1[i][j] = -2, dp2[i][j] = -1;
            else if(ch == '+') dp1[i][j] = 1, dp2[i][j] = 2;
            else if(ch == '?') dp1[i][j] = -2, dp2[i][j] = 2;
        }
    for(int k = 1; k <= n; ++ k)
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= n; ++ j)
                updmax(dp1[i][j], dp1[i][k] + dp1[k][j]),
                updmin(dp2[i][j], dp2[i][k] + dp2[k][j]);
    int resa = 0, resb = 0, resc = 0;
    for(int i = 2; i <= n; ++ i){
        for(int j = 1; j < i; ++ j){
            if(i == a || i == b || j == a || j == b) continue;
            if(dp1[a][i] > dp2[j][b] || dp1[b][i] > dp2[j][a] || dp1[a][j] > dp2[i][b] || dp1[b][j] > dp2[i][a]) ++ resa;
            if(dp1[a][i] == dp2[a][i] && dp1[j][b] == dp2[j][b] && dp1[a][i] == dp1[j][b]) ++ resb;
            else if(dp1[a][j] == dp2[a][j] && dp1[i][b] == dp2[i][b] && dp1[a][j] == dp1[i][b]) ++ resb;
            if(dp2[a][i] < dp1[j][b] || dp2[b][i] < dp1[j][a] || dp2[a][j] < dp1[i][b] || dp2[b][j] < dp1[i][a]) ++ resc;
        }
    }
    printf("%d %d %d\n", resa, resb, resc);
    lovely _lzy_;
}
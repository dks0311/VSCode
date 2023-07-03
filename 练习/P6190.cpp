#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define int long long
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
const int N = 105, M = 2.5e3 + 5;
struct matrix{
    int a[N][N], lx, ly;
    matrix(){memset(a, 0x3f, sizeof a); lx = ly = 0;}
    matrix(int _lx, int _ly){memset(a, 0x3f, sizeof a); lx = _lx, ly = _ly;}
    matrix operator * (const matrix &b) const{
        matrix c = matrix(lx, b.ly);
        for(int k = 0; k < ly; ++ k)
            for(int i = 0; i < c.lx; ++ i)
                for(int j = 0; j < c.ly; ++ j) updmin(c.a[i][j], a[i][k] + b.a[k][j]);
        return c;
    }
};
struct edge{int u, v, w;}e[M];
int n, m, kk;
int f[N][N][2];
inline matrix ksm(matrix a, int b){
    matrix ans = a; -- b;
    while(b){
        if(b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
signed main(){
    n = read(), m = read(), kk = read();
    memset(f, 0x3f, sizeof f);
    for(int i = 1; i <= m; ++ i){
        int u = read(), v = read(), w = read();
        f[u][v][0] = w;
        e[i] = (edge){u, v, w};
    }
    for(int i = 1; i <= n; ++ i) f[i][i][0] = 0;
    for(int k = 1; k <= n; ++ k)
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= n; ++ j)
                updmin(f[i][j][0], f[i][k][0] + f[k][j][0]);
    if(!kk){printf("%lld\n", f[1][n][0]); return 0;}
    for(int k = 1; k <= m; ++ k){
        int u = e[k].u, v = e[k].v, w = e[k].w;
        for(int i = 1; i <= n; ++ i)
            for(int j = 1; j <= n; ++ j)
                updmin(f[i][j][1], min(f[i][j][0], f[i][u][0] + f[v][j][0] - w));
    }
    matrix ans = matrix(n, n);
    for(int i = 0; i < n; ++ i)
        for(int j = 0; j < n; ++ j) ans.a[i][j] = f[i + 1][j + 1][1];
    printf("%lld\n", ksm(ans, kk).a[0][n - 1]);
    lovely _lzy_;
}
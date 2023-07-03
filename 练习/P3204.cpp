#include <bits/stdc++.h>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 130, M = 1 << 10 | 5, MOD = 30031;
int n, k, p;
struct matrix{
    int a[N][N];
    int lx, ly;
    matrix(){memset(a, 0, sizeof a); lx = ly = 0;}
    matrix(int _lx, int _ly){memset(a, 0, sizeof a); lx = _lx, ly = _ly;}
    matrix operator * (const matrix &b)const{
        matrix c = matrix(lx, b.ly);
        for(int i = 0; i < c.lx; ++ i)
            for(int j = 0; j < c.ly; ++ j)
                for(int k = 0; k < ly; ++ k) (c.a[i][j] += a[i][k] * b.a[k][j] % MOD) %= MOD;
        return c;
    }
};
int id[M], num[N], tot;
int lowbit(int x){return x & -x;}
bool check(int x){
    int sum = 0;
    if((x & 1) == 0) return false;
    while(x) ++ sum, x -= lowbit(x);
    return sum == k;
}
matrix ksm(matrix a, int b){
    matrix ans = a;
    -- b;
    while(b){
        if(b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}
int main(){
    n = read(), k = read(), p = read();
    for(int i = 0; i < 1 << p; ++ i) if(check(i)) id[i] = tot, num[tot ++] = i;
    // for(int i = 0; i < tot; ++ i){
    //     int x = num[i];
    //     printf("%d:%d:", i, x);
    //     while(x){
    //         printf("%d ", x & 1);
    //         x >>= 1;
    //     }
    //     puts("");
    // }
    matrix trans = matrix(tot, tot);
    for(int i = 0; i < tot; ++ i)
        for(int j = 0; j < tot; ++ j)
            if(lowbit(num[i] >> 1 ^ num[j]) == (num[i] >> 1 ^ num[j])) trans.a[j][i] = 1;
    // for(int i = 0; i < tot; ++ i){
    //     for(int j = 0; j < tot; ++ j) printf("%d ", trans.a[i][j]);
    //     puts("");
    // }
    matrix ans = matrix(tot, 1);
    ans.a[id[(1 << k) - 1]][0] = 1;
    trans = ksm(trans, n - k);
    ans = trans * ans;
    printf("%d\n", ans.a[id[(1 << k) - 1]][0]);
    return 0;
}
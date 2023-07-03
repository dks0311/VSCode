#include <bits/stdc++.h>
namespace _default{
    using namespace std;
    #define lovely return
    #define _lzy_ 0
    #define LL long long
    #define int long long
    #define DB double
    #define PII std::pair<int, int>
    #define X first
    #define Y second
    #define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
    #define uf(i, x, y) for(int i = (x); i < (y); ++ i)
    #define dF(i, x, y) for(int i = (x); i >= (y); -- i)
    #define df(i, x, y) for(int i = (x); i > (y); -- i)
    #define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
    #define sett(x, y) memset(x, y, sizeof x)
    #define copy(x, y) memcpy(x, y, sizeof x)
    const int MOD = 1e9 + 7;
    const DB EPS = 1e-8;
    template<typename T> inline T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> inline void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0){putchar('-'); x = -x;}
        if(!x) putchar('0');
        while(x) st[++ top] = x % 10, x /= 10;
        while(top) putchar(st[top --] + 48);
        printf("%s", s);
    }
    template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
    template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
    template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
    template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
const int N = 1e7;
int T;
int mu[N + 5], phi[N + 5];
bool not_prime[N + 5];
vector<int> prime;
inline void xxs(){
    mu[1] = phi[1] = 1;
    uF(i, 2, N){
        if(!not_prime[i]){
            mu[i] = -1, phi[i] = i - 1;
            prime.push_back(i);
        }
        for(auto j : prime){
            if(i * j > N) break;
            not_prime[i * j] = true;
            if(i % j == 0){
                phi[i * j] = phi[i] * j;
                break;
            }
            mu[i * j] = -mu[i];
            phi[i * j] = phi[i] * (j - 1);
        }
    }
    uF(i, 2, N) phi[i] += phi[i - 1], mu[i] += mu[i - 1];
}
unordered_map<int, int> sphi, smu;
int Get_Sum_phi(int n){
    if(n <= N) return phi[n];
    if(sphi[n]) return sphi[n];
    int res = n * (n + 1) >> 1;
    for(int l = 2, r; l <= n; l = r + 1){
        r = n / (n / l);
        res -= (r - l + 1) * Get_Sum_phi(n / l);
    }
    return sphi[n] = res;
}
int Get_Sum_mu(int n){
    if(n <= N) return mu[n];
    if(smu[n]) return smu[n];
    int res = 1;
    for(int l = 2, r; l <= n; l = r + 1){
        r = n / (n / l);
        res -= (r - l + 1) * Get_Sum_mu(n / l);
    }
    return smu[n] = res;
}
signed main(){
    xxs();
    T = read<int>();
    while(T --){
        int n = read<int>();
        write(Get_Sum_phi(n), " ");
        write(Get_Sum_mu(n), "\n");
    }
    lovely _lzy_;
}
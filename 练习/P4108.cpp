/*
author: 牛肉爱吃dks
starting time: 2023.06.06 11:32:16
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define LL long long
#define int long long
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
#define uf(i, x, y) for(int i = (x); i < (y); ++ i)
#define dF(i, x, y) for(int i = (x); i >= (y); -- i)
#define df(i, x, y) for(int i = (x); i > (y); -- i)
#define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
#define gcd(x, y) std::__gcd(x, y)
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void read(T &x){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    x = f ? ~s + 1 : s;
}
template<typename T> inline void write(T x, const char *s){
    static int st[40]; int top = 0;
    if(x < 0){putchar('-'); x = -x;}
    if(!x) putchar('0');
    while(x) st[++ top] = x % 10, x /= 10;
    while(top) putchar(st[top --] + 48);
    printf("%s", s);
}
template<typename T1, typename T2> inline int max(T1 x, T2 y){return x > y ? x : y;}
template<typename T1, typename T2> inline int min(T1 x, T2 y){return x < y ? x : y;}
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmul(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
const int N = 1e5 + 5, M = 350;
int n, m, a[N];
int ll[M], rr[M], bl[N], part;
int pre_xor[N], end_gcd[N];
bool change[M];
std::unordered_map<int, int> mp[M];
void debug(const char *s, int *a, int l, int r){
    printf("%s:\n", s);
    uF(i, l, r) std::cout << a[i] << " ";
    puts("");
}
signed main(){
    n = read<int>(); part = sqrt(n);
    uf(i, 0, n) a[i] = read<int>();
    uf(i, 0, n) bl[i] = i / part;
    uF(i, 0, bl[n - 1]) ll[i] = i * part, rr[i] = min((i + 1) * part - 1, n - 1);
    int now = 0;
    uf(i, 0, n){
        if((i && bl[i] == bl[i - 1]) && a[i] % now != 0) change[bl[i]] = true;
        now = gcd(now, a[i]);
        if(rr[bl[i]] == i) end_gcd[bl[i]] = now;
    }
    uf(i, 0, n){
        pre_xor[i] = i == ll[bl[i]] ? a[i] : pre_xor[i - 1] ^ a[i];
        if(!mp[bl[i]].count(pre_xor[i])) mp[bl[i]][pre_xor[i]] = i;
    }
    m = read<int>();
    while(m --){
        std::string s; std::cin >> s;
        if(s == "MODIFY"){
            int x = read<int>(), y = read<int>();
            int b = bl[x], now = b ? end_gcd[b - 1] : 0;
            a[x] = y, change[b] = false;
            mp[b].clear();
            uF(i, ll[b], rr[b]){
                if(i != ll[b] && a[i] % now) change[b] = true;
                now = gcd(now, a[i]);
            }
            uF(i, ll[b], rr[b]){
                pre_xor[i] = i == ll[b] ? a[i] : pre_xor[i - 1] ^ a[i];
                if(!mp[b].count(pre_xor[i])) mp[b][pre_xor[i]] = i;
            }
        }
        else{
            int x = read<int>();
            int now_gcd = 0, now_xor = 0;
            bool flag = false;
            uF(i, 0, bl[n - 1]){
                if(change[i]){
                    uF(j, ll[i], rr[i])
                        if((now_gcd = gcd(now_gcd, a[j])) * (now_xor ^= a[j]) == x){
                            flag = true;
                            write(j, "\n");
                            break;
                        }
                }
                else{
                    now_gcd = gcd(now_gcd, a[ll[i]]);
                    if(x % now_gcd == 0 && mp[i].count(x / now_gcd ^ now_xor)){
                        flag = true;
                        write(mp[i][x / now_gcd ^ now_xor], "\n");
                        break;
                    }
                    now_xor ^= pre_xor[rr[i]];
                }
                if(flag) break;
            }
            if(!flag) puts("no");
        }
    }
    lovely _lzy_;
}
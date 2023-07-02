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
const int N = 1e5 + 5;
int n, a[N];
int ne[N], sign[N], dp[N], pre[N];
bool use[3];
char s[5];
struct Sec{
    int l, r, s;
    Sec(int _l = 0, int _r = 0, int _s = 1) : l(_l), r(_r), s(_s){}
}b[N];
inline void Solve(int l, int r){
    int last = l - 1, sum = 1, tot = 0;
    uF(i, l, r){
        if(a[i] == 1){
            if(last + 1 <= i - 1) b[++ tot] = Sec(last + 1, i - 1, sum);
            last = i, sum = 1;
        }
        else{
            sum *= a[i];
            if(sum > 1e9) break;
        }
    }
    if(sum > 1e9){
        for(int i = l; i <= r && a[i] == 1; ++ i) sign[i + 1] = 2;
        for(int i = r; i >= l && a[i] == 1; -- i) sign[i] = 2;
        return;
    }
    if(last != r) b[++ tot] = Sec(last + 1, r, sum);
    sum = 1;
    uF(i, 1, tot){
        if(sum > 1e9){
            for(int i = l; i <= r && a[i] == 1; ++ i) sign[i + 1] = 2;
            for(int i = r; i >= l && a[i] == 1; -- i) sign[i] = 2;
            return;
        }
        sum *= b[i].s;
    }
    if(sum > 1e9){
        for(int i = l; i <= r && a[i] == 1; ++ i) sign[i + 1] = 2;
        for(int i = r; i >= l && a[i] == 1; -- i) sign[i] = 2;
        return;
    }
    b[0].r = l - 1;
    uF(i, 1, tot){
        dp[i] = 0, sum = b[i].s;
        dF(j, i - 1, 0){
            if(dp[i] < dp[j] + b[j + 1].l - b[j].r - 1 + sum)
                dp[i] = dp[j] + b[j + 1].l - b[j].r - 1 + sum, pre[i] = j;
            sum *= b[j].s;
        }
    }
    for(int i = l + 1; i <= b[1].l; ++ i) sign[i] = 2;
    for(int i = b[tot].r + 1; i <= r; ++ i) sign[i] = 2;
    int cur = tot;
    while(cur){
        uF(i, b[pre[cur]].r + 1, b[pre[cur] + 1].l) sign[i] = 2;
        cur = pre[cur];
    }
}
signed main(){
    n = read<int>();
    uF(i, 1, n) a[i] = read<int>();
    scanf("%s", s); int len = strlen(s);
    uf(i, 0, len){
        if(s[i] == '+') use[0] = true;
        else if(s[i] == '-') use[1] = true;
        else use[2] = true;
    }
    if(use[0] && use[2]){
        int last = 0;
        uF(i, 1, n){
            if(!a[i]){
                Solve(last + 1, i - 1);
                last = i, sign[i] = sign[i + 1] = 2;
            }
        }
        if(last < n) Solve(last + 1, n);
        write(a[1]);
        uF(i, 2, n){
            putchar(sign[i] ? '+' : '*');
            write(a[i]);
        }
    }
    else if(use[2] && !use[1]){
        uf(i, 1, n) write(a[i], "*");
        write(a[n]);
    }
    else if(use[2] && use[1]){
        bool flag = true;
        uf(i, 1, n){
            if(!a[i + 1] && flag) write(a[i], "-");
            else write(a[i], "*");
        }
        write(a[n]);
    }
    else if(use[0]){
        uf(i, 1, n) write(a[i], "+");
        write(a[n]);
    }
    else{
        uf(i, 1, n) write(a[i], "-");
        write(a[n]);
    }
    puts("");
    lovely _lzy_;
}
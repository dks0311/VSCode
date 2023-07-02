#include <bits/stdc++.h>
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
#define init(x, y) memset(x, y, sizeof x)
#define copy(x, y) memcpy(x, y, sizeof x)
const int MOD = 1e9 + 7;
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
template<typename T> inline void write(T x, const char *s){
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
const int M = 500;
struct node{PII p; int f;};
int Hsh(node x){
    return (x.p.X % M) * (x.p.Y % M) % M * ((x.f << 1) + (x.f << 4)) % M;
}
int Hsh(PII x){
    return ((x.X % M) * (x.Y % M) + (x.X % M) + (x.Y % M)) % M;
}
template<typename T1, typename T2>
struct Hash{
    T1 h[M];
    T2 v[M];
    bool vis[M], del[M];
    int Find(T1 x){int t = Hsh(x); while(vis[t] && h[t] != x) if(++ t == M) t = 0; return t;}
    inline bool Exist(T1 x){int t = Find(x); return (vis[t] && !del[t]);}
    inline void Modify(T1 x, T2 y){int t = Find(x); h[t] = x, v[t] = y, vis[t] = true, del[t] = false;}
    inline T2 Query(T1 x){return v[Find(x)];}
    inline void Delete(T1 x){del[Find(x)] = true;}
};
Hash<node, PII> mp;
Hash<node, bool> vis;
Hash<PII, int> cnt;
const int N = 105;
int n, tot;
std::vector<PII> v;
signed main(){
    n = read<int>();
    uF(i, 1, n){
        PII a, b;
        a.X = read<int>(), a.Y = read<int>(), b.X = read<int>(), b.Y = read<int>();
        if(a.X + a.Y > b.X + b.Y) std::swap(a, b);
        if(a.X == b.X) mp[(node){a, 0}] = b, mp[(node)(b, 2)] = a;
        else mp[(node){a, 1}] = b, mp[(node){b, 3}] = a;
        int aa = cnt.Query(a), bb = cnt.Query(b);
        cnt.Modify(a, aa + 1);
        cnt.Modify(b, bb + 1);
        aa & 1 ? ++ tot : -- tot;
        bb & 1 ? ++ tot : -- tot;
        v.push_back(a); v.push_back(b);
    }
    if(tot > 2){
        puts("0");
        lovely _lzy_;
    }
    for(auto p : v){
        uf(i, 0, 4){
            while(mp.Exist((node){mp.Query((node){p, i}), i})){
                PII tp = mp.Query((node){p, i});
                mp.Modify((node){p, i}, mp.Query((node){tp, i}));
                mp.Delete((node){tp, i}), mp.Delete((node){tp, (i + 2) % 4});
            }
        }
    }
    PII p = v[0];
    write(p.X, " ");
    write(p.Y, "\n");
    int ans = 0;
    while(true){
        bool flag = false;
        for(int i = 0; i < 3; ++ i)
            if(mp.Exist((node){p, i}) && !vis.Query((node){p, i})){
                vis.Modify((node){p, i}, true);
                p = mp.Query((node){p, i});
                flag = true;
                break;
            }
        if(!flag) break;
        write(p.X, " ");
        write(p.Y, "\n");
    }
    lovely _lzy_;
}
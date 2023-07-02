/*
author: 牛肉爱吃dks
starting time: 2023.06.07 15:02:16
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define ll long long
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
#define bit(x) std::bitset<x>
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
template<typename T> inline T max(T x, T y){return x > y ? x : y;}
template<typename T> inline T min(T x, T y){return x < y ? x : y;}
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmul(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
template<typename T> void debug(const char *s, T *a, int l, int r){
    printf("%s:\n", s);
    uF(i, l, r) std::cout << a[i] << " ";
    puts("");
}
const int N = 505, M = 1e3 + 5;
int n, m, q;





inline void print(std::bitset<M> x){
    bool flag = false;
    dF(i, 1000, 0){
        if(x[i]) putchar('1'), flag = true;
        else if(flag) putchar('0');
    }
    puts("");
}





/*----------建图----------*/
bit(M) wgt[M];
int head[N], ne[M], to[M], idx = 1;
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
/*----------建图----------*/





/*----------线性基-----------*/
int st[M], top;
bit(M) lb[M];
inline void insert(bit(M) x){
    // printf("insert:"); print(x);
    if(x.none()) return;
    dF(i, 1000, 0){
        if(!x[i]) continue;
        if(!lb[i][i]){lb[i] = x; st[++ top] = i; break;}
        x ^= lb[i];
    }
}
inline bit(M) query(){
    bit(M) res;
    dF(i, 1000, 0)
        if(lb[i][i] && !res[i]) res ^= lb[i];
    return res;
}
/*----------线性基----------*/





/*----------生成树----------*/
bit(M) dis[N];
bool vis[N], vise[M];
void dfs(int u){
    vis[u] = true;
    ef(i, u){
        int v = to[i];
        if(vise[i]) continue;
        vise[i] = vise[i ^ 1] = true;
        if(vis[v]){
            insert(dis[u] ^ wgt[i] ^ dis[v]);
            continue;
        }
        dis[v] = dis[u] ^ wgt[i];
        dfs(v);
    }
}
/*----------生成树----------*/





/*----------线段树分治----------*/
struct Edge{int u, v; bit(M) w;}e[M];
struct node{
    int l, r;
    std::vector<int> e;
}tr[M << 2];
void build(int l, int r, int p){
    tr[p].l = l, tr[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
}
void insert(int l, int r, int p, int e){
    if(l <= tr[p].l && tr[p].r <= r){tr[p].e.push_back(e); return;}
    int mid = tr[p].l + tr[p].r >> 1;
    if(l <= mid) insert(l, r, p << 1, e);
    if(r > mid) insert(l, r, p << 1 | 1, e);
}
void calc(int p){
    int tmp = top;
    uf(i, 0, tr[p].e.size()) insert(e[tr[p].e[i]].w ^ dis[e[tr[p].e[i]].u] ^ dis[e[tr[p].e[i]].v]);
    if(tr[p].l == tr[p].r) print(query());
    else{calc(p << 1); calc(p << 1 | 1);}
    while(top > tmp) lb[st[top --]].reset();
}
/*----------线段树分治----------*/





int p[M];//p[i]:i号边上一次出现的操作编号
PII ti[M];
char s[M];
inline void read(bit(M) &w){
    w.reset();
    scanf("%s", s); int len = strlen(s);
    uf(i, 0, len) w[len - 1 - i] = s[i] - '0';
}
signed main(){
    n = read<int>(), m = read<int>(), q = read<int>();



    /*-----建图，生成树-----*/
    uF(i, 1, m){
        int u = read<int>(), v = read<int>();
        bit(M) w; read(w);
        add(u, v); wgt[idx] = w;
        add(v, u); wgt[idx] = w;
    }
    dfs(1);
    /*-----建图，生成树-----*/



    /*-----记录操作-----*/
    int id = 0, tot = 0;
    uF(i, 1, q){
        std::string opt; std::cin >> opt;
        if(opt == "Add"){
            int u = read<int>(), v = read<int>();
            bit(M) w; read(w);
            e[++ tot] = (Edge){u, v, w};
            ti[tot].X = i, p[++ id] = tot;
        }
        else if(opt == "Cancel"){
            int k = read<int>();
            ti[p[k]].Y = i - 1;
        }
        else{
            int k = read<int>();
            bit(M) w; read(w);
            e[++ tot] = e[p[k]]; e[tot].w = w;
            ti[p[k]].Y = i - 1, ti[p[k] = tot].X = i;
        }
    }
    /*-----记录操作-----*/



    /*-----处理答案-----*/
    if(q) build(1, q, 1);
    uF(i, 1, tot) insert(ti[i].X, ti[i].Y ? ti[i].Y : q, 1, i);
    print(query());
    if(q) calc(1);
    /*-----处理答案-----*/
    lovely _lzy_;
}
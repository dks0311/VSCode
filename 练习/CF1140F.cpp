#include <bits/stdc++.h>
#pragma GCC optimize(3)
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
template<typename T> inline T max(T x, T y){return x > y ? x : y;}
template<typename T> inline T min(T x, T y){return x < y ? x : y;}
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
const int N = 3e5 + 5, M = N * 2;
int n;
LL ans;
PII op[N], ti[N];
int Hsh(PII x){
    return x.X * x.X % M * x.Y % M * x.Y % M;
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
Hash<PII, int> id;
struct DSU{
    struct node{
        int fa, sx, sy;
        node(){fa = sx = sy = 0;}
        node(int _fa, int _sx, int _sy){fa = _fa, sx = _sx, sy = _sy;}
        inline LL Calc(){return 1ll * sx * sy;}
    }tr[N << 1];
    int get(int u){return u == tr[u].fa ? u : get(tr[u].fa);}
    struct modify{
        modify *pre;
        node u, v;
        int id_u, id_v, ans, save;
        modify(){pre = NULL, id_u = id_v = ans = save = 0;}
        modify(modify *_pre, node _u, node _v, int _id_u, int _id_v, int _ans){
            pre = _pre, u = _u, v = _v, id_u = _id_u, id_v = _id_v, ans = _ans, save = 0;
        }
    }*head_modify = NULL;
    inline void Init(){
        uF(i, 1, n) tr[i] = node(i, 1, 0);
        uF(i, n + 1, n + n) tr[i] = node(i, 0, 1);
    }
    inline void Merge(int u, int v){
        u = get(u), v = get(v);
        if(u == v) return;
        if(tr[u].sx + tr[u].sy > tr[v].sx + tr[v].sy) std::swap(u, v);
        head_modify = new modify(head_modify, tr[u], tr[v], u, v, ans);
        ans -= tr[v].Calc() + tr[u].Calc();
        tr[u].fa = v, tr[v].sx += tr[u].sx, tr[v].sy += tr[u].sy;
        ans += tr[v].Calc();
    }
    inline void Save(){if(head_modify) ++ head_modify -> save;}
    void Cancel(){
        while(head_modify && !(head_modify -> save)){
            tr[head_modify -> id_u] = head_modify -> u;
            tr[head_modify -> id_v] = head_modify -> v;
            ans = head_modify -> ans;
            modify *tmp = head_modify;
            head_modify = head_modify -> pre;
            delete tmp;
        }
        if(head_modify) -- head_modify -> save;
    }
}dsu;
struct node{int l, r; std::vector<int> op;}tr[N << 2];
void Build(int l, int r, int p){
    tr[p].l = l, tr[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    Build(l, mid, p << 1);
    Build(mid + 1, r, p << 1 | 1);
}
void Insert(int l, int r, int p, int op){
    if(l <= tr[p].l && tr[p].r <= r){tr[p].op.push_back(op); return;}
    int mid = tr[p].l + tr[p].r >> 1;
    if(l <= mid) Insert(l, r, p << 1, op);
    if(r > mid) Insert(l, r, p << 1 | 1, op);
}
void Calculate(int p){
    dsu.Save();
    int tmp = ans;
    uf(i, 0, tr[p].op.size())
        dsu.Merge(op[tr[p].op[i]].X, op[tr[p].op[i]].Y + n);
    if(tr[p].l == tr[p].r) write(ans, " ");
    else Calculate(p << 1), Calculate(p << 1 | 1);
    dsu.Cancel();
}
signed main(){
    n = read<int>();
    int tot = 0;
    uF(i, 1, n){
        int x = read<int>(), y = read<int>();
        if(!id.Exist((PII){x, y})){
            op[++ tot] = (PII){x, y}, ti[tot].X = i;
            id.Modify((PII){x, y}, tot);
        }
        else{
            ti[id.Query((PII){x, y})].Y = i - 1;
            id.Delete((PII){x, y});
        }
    }
    Build(1, n, 1);
    dsu.Init();
    uF(i, 1, tot) Insert(ti[i].X, ti[i].Y ? ti[i].Y : n, 1, i);
    Calculate(1);
    lovely _lzy_;
}
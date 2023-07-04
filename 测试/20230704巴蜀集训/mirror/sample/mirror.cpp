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
    #define mk(x, y) make_pair((x), (y))
    const int MOD = 1e9 + 7, INF = 0x3f3f3f3f;
    const DB EPS = 1e-8;
    template<typename T> T read(){
        T s = 0; int f = 0; char ch = getchar();
        while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
        while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
        return f ? ~s + 1 : s;
    }
    template<typename T> void write(T x, const char *s = ""){
        static int st[40]; int top = 0;
        if(x < 0){putchar('-'); x = -x;}
        if(!x) putchar('0');
        while(x) st[++ top] = x % 10, x /= 10;
        while(top) putchar(st[top --] + 48);
        printf("%s", s);
    }
    template<typename T> void updmin(T &x, T y){if(x > y) x = y;}
    template<typename T> void updmax(T &x, T y){if(x < y) x = y;}
    template<typename T> void updadd(T &x, T y){(x += y % MOD) %= MOD;}
    template<typename T> void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
    int cmp(DB a, DB b){if(fabs(a - b) < EPS) return 0; return a - b > EPS ? 1 : -1;}
}
using namespace _default;
const int N = 1e5 + 5, M = 1e7 + 5;
int n, m, ans;
PII bl[N];
pair<int, PII> segx[N << 1], segy[N << 1];
int cx, cy;
vector<int> px[N], py[N];
vector<PII> seg[N];
struct Node{
    vector<int> fa;
    int ls, rs, seg;
}tr[M];
int currt, tot, start;
int head[M], ne[M], to[M], idx;
bool vis[M];
void Add_Edge(int u, int v){
    // printf("bian:%d %d\n", u, v);
    to[++ idx] = v, ne[idx] = head[u], head[u] = idx;
}
void Insert(int l, int r, int p, int &now, int x, int y){
    now = ++ tot;
    if(l == r){
        // printf("  %d %d %d %d\n", x, segx[y].Y.X, segx[y].Y.Y, now);
        if(!start && l == 1) start = now;
        tr[now].seg = y;
        return;
    }
    int mid = l + r >> 1;
    if(x <= mid){
        Insert(l, mid, tr [p].ls, tr[now].ls, x, y);
        tr[now].rs = tr[p].rs;
    }
    else{
        Insert(mid + 1, r, tr[p].rs, tr[now].rs, x, y);
        tr[now].ls = tr[p].ls;
    }
    if(tr[now].ls) tr[tr[now].ls].fa.push_back(now);
    if(tr[now].rs) tr[tr[now].rs].fa.push_back(now);
}
void lianbian(int l, int r, int now, int id){
    if(!now) return;
    if(segy[id].Y.X <= l && r <= segy[id].Y.Y){
        Add_Edge(id, now); Add_Edge(now, id);
        return;
    }
    int mid = l + r >> 1;
    if(segy[id].Y.X <= mid) lianbian(l, mid, tr[now].ls, id);
    if(segy[id].Y.Y > mid) lianbian(mid + 1, r, tr[now].rs, id);
}
queue<pair<PII, int> > q;
void tuozhan1(int u, int x){
    if(!tr[u].ls){
        if(vis[u]) return;
        vis[u] = true;
        q.push(mk(mk(u, x), 0));
        return;
    }
    tuozhan1(tr[u].ls, x);
    tuozhan1(tr[u].rs, x);
}
void tuozhan0(int u, int x){
    ef(i, u){
        int v = to[i];
        if(vis[v]) continue;
        vis[v] = true;
        q.push(mk(mk(v, x), 1));
    }
    for(auto f : tr[u].fa) tuozhan0(f, x);
}
void BFS(){
    q.push(mk(mk(start, 0), 0));
    vis[start] = true;
    while(!q.empty()){
        pair<PII, int> tmp = q.front(); q.pop();
        // printf("bfs:%d %d %d\n", tmp.X.X, tmp.X.Y, tmp.Y);
        int u = tmp.X.X;
        if(tmp.Y) ans += tmp.X.Y * (segy[tmp.X.X].Y.Y - segy[tmp.X.X].Y.X + 1);
        else ans += tmp.X.Y * (segx[tr[tmp.X.X].seg].Y.Y - segx[tr[tmp.X.X].seg].Y.X + 1);
        if(tmp.Y) ef(i, u) tuozhan1(to[i], tmp.X.Y + 1);
        else tuozhan0(u, tmp.X.Y + 1);
    }
}
signed main(){
    freopen("ex_mirror2.in", "r", stdin);
    // freopen("mirror.out", "w", stdout);
    n = read<int>(), m = read<int>();
    uF(i, 1, m)
        bl[i].Y = read<int>(), bl[i].X = read<int>(),
        px[bl[i].X].push_back(bl[i].Y), py[bl[i].Y].push_back(bl[i].X);
    uF(i, 1, n) sort(px[i].begin(), px[i].end()), sort(py[i].begin(), py[i].end());
    uF(i, 1, n){
        int last = 0;
        for(auto y : px[i]){
            if(y > last + 1) segx[++ cx] = mk(i, mk(last + 1, y - 1)), seg[last + 1].push_back(mk(i, cx));
            last = y;
        }
        if(n > last) segx[++ cx] = mk(i, mk(last + 1, n)), seg[last + 1].push_back(mk(i, cx));
        last = 0;
        for(auto x : py[i]){
            if(x > last + 1) segy[++ cy] = mk(i, mk(last + 1, x - 1));
            last = x;
        }
        if(n > last) segy[++ cy] = mk(i, mk(last + 1, n));
    }
    // printf("竖向的线段:\n");
    // uF(i, 1, cx) printf("%d %d %d\n", segx[i].X, segx[i].Y.X, segx[i].Y.Y);
    // printf("横向的线段:\n");
    // uF(i, 1, cy) printf("%d %d %d\n", segy[i].X, segy[i].Y.X, segy[i].Y.Y);
    tot = cy;
    int cur = 1;
    uF(i, 1, n){
        for(auto sg : seg[i]){
            Insert(1, n, currt, currt, sg.X, sg.Y);
        }
        // printf("%d\n", seg[i].size());
        while(segy[cur].X == i){
            lianbian(1, n, currt, cur);
            ++ cur;
        }
    }
    // printf("start:%d\n", start);
    // for(auto f : tr[11].fa) printf("%d ", f);
    // puts("");
    BFS();
    write((ans - n * n + m) / 2, "\n");
    lovely _lzy_;
}
/*
3 2
2 2
2 1
啊啊啊啊打不下去了
*/
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
const int N = 2e4 + 5, INF = 1e18;
struct node{int l, r, add, mn;}tr[N << 2];
int n, m;
int pos[N], cst[N], rpy[N], rcv[N], dp[N], st[N];
std::vector<int> end[N];
inline void pushup(int p){tr[p].mn = min(tr[p << 1].mn, tr[p << 1 | 1].mn);}
inline void add(int p, int x){tr[p].mn += x, tr[p].add += x;}
inline void pushdown(int p){
    if(tr[p].add){
        add(p << 1, tr[p].add), add(p << 1 | 1, tr[p].add); 
        tr[p].add = 0;
    }
}
void build(int l, int r, int p){
    tr[p].l = l, tr[p].r = r;
    if(l == r){tr[p].mn = dp[l]; return;}
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
    pushup(p);
}
void modify(int l, int r, int x, int p){
    if(l > r) return;
    if(l <= tr[p].l && tr[p].r <= r){add(p, x); return;}
    pushdown(p);
    int mid = tr[p].l + tr[p].r >> 1;
    if(l <= mid) modify(l, r, x, p << 1);
    if(r > mid) modify(l, r, x, p << 1 | 1);
    pushup(p);
}
int query(int l, int r, int p){
    if(l > r) return INF;
    if(l <= tr[p].l && tr[p].r <= r) return tr[p].mn;
    pushdown(p);
    int mid = tr[p].l + tr[p].r >> 1, res = INF;
    if(l <= mid) updmin(res, query(l, r, p << 1));
    if(r > mid) updmin(res, query(l, r, p << 1 | 1));
    return res;
}
signed main(){
    n = read(), m = read();
    for(int i = 2; i <= n; ++ i) pos[i] = read();
    for(int i = 1; i <= n; ++ i) cst[i] = read();
    for(int i = 1; i <= n; ++ i){
        rcv[i] = read();
        end[std::upper_bound(pos + 1, pos + n + 1, pos[i] + rcv[i]) - pos - 1].push_back(i);
        st[i] = std::lower_bound(pos + 1, pos + n + 1, pos[i] - rcv[i]) - pos;
    }
    for(int i = 1; i <= n; ++ i) rpy[i] = read();
    int ans;
    for(int i = 1, now = 0; i <= n; ++ i){
        dp[i] = now + cst[i];
        for(int j = 0; j < end[i].size(); ++ j)
            now += rpy[end[i][j]];
        ans = now;
    }
    for(int k = 1; k <= m; ++ k){
        for(int i = 0; i < N << 2; ++ i) tr[i].add = 0;
        build(1, n, 1);
        for(int i = 1; i <= n; ++ i){
            dp[i] = query(1, i - 1, 1) + cst[i];
            for(int j = 0; j < end[i].size(); ++ j){
                modify(1, st[end[i][j]] - 1, rpy[end[i][j]], 1);
            }
        }
        updmin(ans, query(1, n, 1));
    }
    printf("%lld\n", ans);
    lovely _lzy_;
}
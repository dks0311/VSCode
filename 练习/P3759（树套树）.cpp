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
template<typename T> inline void updadd(T &x, T y){x = ((x + y) % MOD + MOD) % MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}
inline int lowbit(int x){return x & -x;}
const int N = 5e4 + 5;
int n, m, ans;
int v[N], a[N], p[N], pp[N];
struct Value_Segment_Tree{
    struct Node{
        int ls, rs, sum, cnt;
        Node(){
            ls = rs = cnt = sum = 0;
        }
    }tr[N * 80];
    int idx;
    int trash[N], top;
    Value_Segment_Tree(){
        idx = top = 0;
    }
    inline void Recycle(int x){
        tr[x] = Node();
        trash[++ top] = x;
    }
    inline int New_Node(){
        if(top) return trash[top --];
        else return ++ idx;
    }
    void Insert(int l, int r, int &now, int x, int y){
        if(!now) now = New_Node();
        updadd(tr[now].sum, y);
        updadd(tr[now].cnt, y / labs(y));
        if(l == r){
            if(!tr[now].sum) Recycle(now), now = 0;
            return;
        }
        int mid = l + r >> 1;
        if(x <= mid) Insert(l, mid, tr[now].ls, x, y);
        else Insert(mid + 1, r, tr[now].rs, x, y);
        if(!tr[now].sum) Recycle(now), now = 0;
        return;
    }
    int Query_sum(int l, int r, int now, int L, int R){
        if(!now) return 0;
        if(L <= l && r <= R) return tr[now].sum;
        int mid = l + r >> 1, res = 0;
        if(L <= mid) updadd(res, Query_sum(l, mid, tr[now].ls, L, R));
        if(R > mid) updadd(res, Query_sum(mid + 1, r, tr[now].rs, L, R));
        return res;
    }
    int Query_cnt(int l, int r, int now, int L, int R){
        if(!now) return 0;
        if(L <= l && r <= R) return tr[now].cnt;
        int mid = l + r >> 1, res = 0;
        if(L <= mid) updadd(res, Query_cnt(l, mid, tr[now].ls, L, R));
        if(R > mid) updadd(res, Query_cnt(mid + 1, r, tr[now].rs, L, R));
        return res;
    }
}S1;
struct BIT{
    int tr[N];
    inline void Add(int x, int y, int z){
        for(; x <= n; x += lowbit(x)) S1.Insert(1, n, tr[x], y, z);
    }
    inline void Build(){
        uF(i, 1, n) Add(i, a[i], v[i]);
    }
    inline int Query_sum(int x, int l, int r){
        int res = 0, f = 0;
        if(l > r) swap(l, r), f = 1;
        for(; x; x -= lowbit(x)) res += S1.Query_sum(1, n, tr[x], l, r);
        return f ? ~res + 1 : res;
    }
    inline int Query_cnt(int x, int l, int r){
        int res = 0, f = 0;
        if(l > r) swap(l, r), f = 1;
        for(; x; x -= lowbit(x)) res += S1.Query_cnt(1, n, tr[x], l, r);
        return f ? ~res + 1 : res;
    }
}S2;
inline void Swap(int x, int y){
    if(x == y) return;
    if(x > y) swap(x, y);
    updadd(ans, S2.Query_sum(y - 1, a[x], a[y]) - S2.Query_sum(x, a[x], a[y]) << 1);
    updadd(ans, (S2.Query_cnt(y - 1, a[x], n) - S2.Query_cnt(x, a[x], n)) * v[x]);
    updadd(ans, (S2.Query_cnt(x, 1, a[x]) - S2.Query_cnt(y - 1, 1, a[x])) * v[x]);
    updadd(ans, (S2.Query_cnt(x, a[y], n) - S2.Query_cnt(y - 1, a[y], n)) * v[y]);
    updadd(ans, (S2.Query_cnt(y - 1, 1, a[y]) - S2.Query_cnt(x, 1, a[y])) * v[y]);
    updadd(ans, a[x] < a[y] ? v[x] + v[y] : -v[x] - v[y]);
    S2.Add(x, a[x], -v[x]), S2.Add(y, a[y], -v[y]);
    S2.Add(x, a[y], v[y]), S2.Add(y, a[x], v[x]);
    swap(a[x], a[y]); swap(v[x], v[y]);
    // printf("%d %d %d\n", x, y, ans);
}
signed main(){
    n = read<int>(), m = read<int>();
    uF(i, 1, n) p[i] = read<int>(), v[p[i]] = read<int>(), a[i] = pp[i] = i;
    S2.Build();
    uF(i, 1, n){
        if(a[i] != p[i]){
            int x = a[i], y = a[pp[p[i]]];
            Swap(i, pp[p[i]]);
            swap(pp[x], pp[y]);
        }
    }
    while(m --){
        int x = read<int>(), y = read<int>();
        Swap(x, y);
        write(ans, "\n");
    }
    lovely _lzy_;
}
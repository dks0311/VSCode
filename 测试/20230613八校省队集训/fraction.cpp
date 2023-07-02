#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define LL long long
// #define int long long
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
const int MOD = 998244353;
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
template<typename T> inline void updmin(T &x, T y){if(x > y) x = y;}
template<typename T> inline void updmax(T &x, T y){if(x < y) x = y;}
template<typename T> inline void updadd(T &x, T y){(x += y % MOD) %= MOD;}
template<typename T> inline void updmul(T &x, T y){(x *= y % MOD) %= MOD;}const int BUF_SIZ=1<<18;
typedef unsigned long long ull;
int n, m;
struct MY_GENERATOR{
	int type; ull seed;
	inline ull nextInt(){
		ull z = (seed += 0x9E37793B5F4A7C15ULL);
		z = (z ^ (z >> 30)) * 0xBE99136D1CE4E5B9ULL;
		z = (z ^ (z >> 27)) * 0x94A749BB033BD1FBULL;
		return z ^ (z >> 31);
	}
	int get(){return nextInt() % 998244352 + 1;}
	inline void get(int lastans, int &l, int &r){
		if(type == 2){
			if(!type) lastans = 0;
			l=((1 + (nextInt() >> 33)) ^ lastans) % (n - 1) + 1;
			r=((1 + (nextInt() >> 33)) ^ lastans) % (n - 1) + 1;
			if(l > r) std::swap(l, r);
		}
		else{
			read(l), read(r);
			if(type) l ^= lastans, r ^= lastans;
		}
	}
}gen;
const int N = 3e6 + 5;
int a[N], p[N], pos[N], nia[N];
int f[N][23], lg[N];
int st[N], top, ml[N], mr[N];
int ksm(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1) ans = 1ll * ans * a % MOD;
        a = 1ll * a * a % MOD;
        b >>= 1;
    }
    return ans;
}
inline int inv(int x){return ksm(x, MOD - 2);}
inline int query(int l, int r){
    int len = lg[r - l + 1];
    return max(f[l][len], f[r - (1 << len) + 1][len]);
}
struct BT{
    int ni[N << 1], ls[N << 1], rs[N << 1], val[N << 1];
    int idx;
    inline void pushup(int u){
        val[u] = 1ll * val[ls[u]] * ni[rs[u]] % MOD;
        ni[u] = 1ll * ni[ls[u]] * val[rs[u]] % MOD;
    }
    int build(int l, int r){
        if(l > r){val[++ idx] = a[l], ni[idx] = nia[l]; return idx;}
        int mid = pos[query(l, r)];
        ls[mid] = build(l, mid - 1);
        rs[mid] = build(mid + 1, r);
        pushup(mid);
        return mid;
    }
}bt;
std::vector<int> son[N];
struct LT{
    int b[N], nib[N];
    void dfs(int u, int fa){
        b[u] = 1ll * b[fa] * bt.val[bt.rs[u]] % MOD, nib[u] = 1ll * nib[fa] * bt.ni[bt.rs[u]] % MOD;
        for(auto v : son[u]) dfs(v, u);
    }
    inline void build(){
        dF(i, n - 2, 1) if(mr[i] != n) son[mr[i]].push_back(i);
        b[0] = nib[0] = 1;
        dF(i, n - 1, 1) if(mr[i] == n) dfs(i, 0);
    }
}lt;
struct RT{
    int dpt[N], b[N], nib[N];
    void dfs(int u, int fa){
        dpt[u] = dpt[fa] + 1;
        int x = bt.ni[bt.ls[u]];
        if(dpt[u] & 1) b[u] = 1ll * b[fa] * bt.val[bt.ls[u]] % MOD, nib[u] = 1ll * nib[fa] * x % MOD;
        else b[u] = 1ll * b[fa] * x % MOD, nib[u] = 1ll * nib[fa] * bt.val[bt.ls[u]] % MOD;
        for(auto v : son[u]) dfs(v, u);
    }
    inline void build(){
        uf(i, 2, n) if(ml[i]) son[ml[i]].push_back(i);
        b[0] = nib[0] = 1;
        uf(i, 1, n) if(!ml[i]) dfs(i, 0);
    }
}rt;
inline void solve1(){
    uf(i, 1, n) pos[p[i]] = i, f[i][0] = p[i];
    uF(j, 1, 21) uf(i, 1, n){
        f[i][j] = f[i][j - 1];
        if(i + (1 << j - 1) < n) updmax(f[i][j], f[i + (1 << j - 1)][j - 1]);
    }
    uf(i, 2, n) lg[i] = lg[i >> 1] + 1;
    uf(i, 1, n){
        while(top && p[st[top]] < p[i]) -- top;
        ml[i] = st[top], st[++ top] = i;
    }
    st[top = 0] = n;
    dF(i, n - 1, 1){
        while(top && p[st[top]] < p[i]) -- top;
        mr[i] = st[top], st[++ top] = i;
    }
    bt.idx = n - 1;
    bt.build(1, n - 1);
    lt.build();
    uf(i, 1, n) son[i].clear();
    rt.build();
}
inline int solve2(int l, int r){
    int mid = pos[query(l, r)];
    int x = 1ll * lt.nib[l] * lt.b[mid] % MOD * a[l] % MOD;
    int y = rt.dpt[mid] & 1 ? 1ll * rt.b[r] * rt.nib[mid] % MOD : 1ll * rt.nib[r] * rt.b[mid] % MOD;
    y = rt.dpt[r] - rt.dpt[mid] & 1 ? 1ll * y * a[r + 1] % MOD : 1ll * y * nia[r + 1] % MOD;
    return 1ll * x * y % MOD;
}
signed main(){
    freopen("fraction.in", "r", stdin);
    freopen("fraction.out", "w", stdout);
    read(n), read(m);
    read(gen.type), read(gen.seed);
    ++ n;
    uF(i, 1, n) a[i] = gen.get(), nia[i] = inv(a[i]);
    uf(i, 1, n) read(p[i]);
    solve1();
    int l, r, lastans = 0;
    ull final_ans = 0;
    for(int t = 1; t <= m; ++ t){
        gen.get(lastans, l, r);
        int ansnow = 0;
        ansnow = solve2(l, r);
        lastans = ansnow;
        final_ans ^= 1ull * t * ansnow;
    }
    printf("%llu\n", final_ans);
    lovely _lzy_;
}
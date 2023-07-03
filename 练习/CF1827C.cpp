#include <bits/stdc++.h>
#define int long long
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 5e5 + 5;
int T, n;
int last, tot;
int dp[N], lzy[N];
int head[N], ne[N], to[N], idx;
char s[N];
std::vector<int> v[N];
struct node{
    int son[26], len, fail;
    node(){memset(son, 0, sizeof son); len = fail = 0;}
}tr[N];
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
int get_fail(int p, int i){
    while(i - tr[p].len - 1 <= 0 || s[i] != s[i - tr[p].len - 1]) p = tr[p].fail;
    return p;
}
void build(){
    for(int i = 0; i <= tot; ++ i) tr[i] = node();
    last = 1, tot = 1;
    tr[1].len = -1, tr[0].fail = 1;
    for(int i = 1; i <= n; ++ i){
        int c = s[i] - 'a';
        int p = get_fail(last, i);
        if(!tr[p].son[c]){
            tr[++ tot].fail = tr[get_fail(tr[p].fail, i)].son[c];
            tr[p].son[c] = tot, tr[tot].len = tr[p].len + 2;
            v[tot].push_back(i);
        }
        else v[tr[p].son[c]].push_back(i);
        last = tr[p].son[c];
    }
}
void dfs(int u, int l){
    if(!l && tr[u].len && tr[u].len % 2 == 0) l = tr[u].len;
    if(l) for(int i = 0; i < v[u].size(); ++ i) lzy[v[u][i]] = l;
    for(int i = head[u]; i; i = ne[i]) dfs(to[i], l);
}
main(){
    T = read();
    while(T --){
        for(int i = 0; i <= tot; ++ i) v[i].clear();
        n = read();
        scanf("%s", s + 1);
        for(int i = 1; i <= n; ++ i) dp[i] = 1;
        build();
        for(int i = 0; i <= tot; ++ i)
            if(i != 1) add(tr[i].fail, i);
        dfs(1, 0);
        int ans = 0;
        for(int i = 0; i <= n; ++ i) dp[i] = 1;
        for(int i = 1; i <= n; ++ i)
            if(lzy[i]) dp[i] += dp[i - lzy[i]];
        for(int i = 1; i <= n; ++ i) ans += dp[i] - 1;
        printf("%lld\n", ans);
        for(int i = 1; i <= n; ++ i) lzy[i] = 0;
        for(int i = 0; i <= tot; ++ i) head[i] = 0;
        idx = 0;
    }
    return 0;
}
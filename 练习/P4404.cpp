#include <bits/stdc++.h>
#define PII std::pair<int, int>
inline int read(){
    int s = 0, f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
inline int max(int x, int y){return x > y ? x : y;}
inline int min(int x, int y){return x < y ? x : y;}
const int N = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m, tot, ans;
int a[N], b[N], ne[N], p[N], vis[N];
std::priority_queue<PII> q, del;
int main(){
    n = read(), m = read();
    for(int i = 1; i <= n; ++ i) a[i] = b[i] = read();
    std::sort(b + 1, b + n + 1);
    int len = std::unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; ++ i) a[i] = std::lower_bound(b + 1, b + len + 1, a[i]) - b;
    for(int i = n; i; -- i){
        ne[i] = p[a[i]] ? p[a[i]] : INF;
        p[a[i]] = i;
    }
    // for(int i = 1; i <= n; ++ i) printf("%d ", a[i]);
    for(int i = 1; i <= n; ++ i){
        if(vis[a[i]]){
            del.push((PII){vis[a[i]], a[i]});
            q.push((PII){vis[a[i]] = ne[i], a[i]});
            ++ ans;
        }//已有，更新
        else if(tot < m){
            q.push((PII){vis[a[i]] = ne[i], a[i]});
            ++ tot;
        }//没有，但有空间，直接放进去
        else{
            while(!del.empty() && q.top() == del.top()){q.pop(); del.pop();}
            PII tmp = q.top(); q.pop();
            vis[tmp.second] = 0;
            q.push((PII){vis[a[i]] = ne[i], a[i]});
        }//没有，也没空间，替换
    }
    printf("%d\n", n - ans);
    return 0;
}
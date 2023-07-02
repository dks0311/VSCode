#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
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
const int N = 2e4 + 5, M = 1e7 + 5;
std::vector<std::string> a;
std::map<std::string, std::string> mp;
std::map<std::string, int> id;
int n;
int head[N], ne[M], to[M], idx;
int dist[N], in[N], pre[N];
inline void add(int u, int v){to[++ idx] = v, ne[idx] = head[u], head[u] = idx;}
void print(int u){
    if(pre[u]) print(pre[u]);
    std::cout << mp[a[u - 1]] << std::endl;
}
signed main(){
    std::string s;
    while(std::cin >> s){
        std::string x = s;
        std::sort(x.begin(), x.end());
        mp[x] = s;
        a.push_back(x);
    }
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    n = a.size();
    for(int i = 0; i < n; ++ i) id[a[i]] = i + 1;
    for(int i = 0; i < n; ++ i)
        for(char ch = 'a'; ch <= 'z'; ++ ch){
            s = a[i];
            s.insert(lower_bound(s.begin(), s.end(), ch), ch);
            if(id.count(s)){add(i + 1, id[s]); ++ in[id[s]];}
        }
    std::queue<int> q;
    for(int i = 1; i <= n; ++ i) if(!in[i]){q.push(i); dist[i] = 1;};
    while(!q.empty()){  
        int u = q.front(); q.pop();
        for(int i = head[u]; i; i = ne[i]){
            int v = to[i];
            if(dist[u] + 1 > dist[v])
                dist[v] = dist[u] + 1, pre[v] = u;
            if(!-- in[v]) q.push(v);
        }
    }
    int pos = 0;
    for(int i = 1; i <= n; ++ i) if(dist[i] > dist[pos]) pos = i;
    printf("%d\n", dist[pos]);
    print(pos);
    lovely _lzy_;
}
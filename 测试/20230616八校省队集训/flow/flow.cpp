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
inline int ksm(register int a, register int b, register int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

const int N=1e5+5;
const int NN=1e5+5;
const int INF=1e15;

int n,k;
int mp[N][15][15];

namespace _4pts{
	int a[NN];
	void mian(){
		memset(a,0,sizeof a);
		int ans=0,lst=0;
		for(int i=1;i<n;++i){
			a[i]=read<int>();
			if(a[i]==0){
				ans+=lst*(lst+1)/2;
				lst=0;
			}
			else ++lst;
		}
		write(ans, "\n");
	}
}

int m,e,s,t;
int to[N],ne[N],val[N],h[N],now[N];
inline void add(int x, int y, int z){
	to[++e]=y,val[e]=z,ne[e]=h[x],h[x]=e;
}
inline void adde(int x, int y, int z){
	add(x,y,z);
	add(y,x,0);
}

queue<int> q;
int dep[N];
inline bool bfs(){
	while(q.size()) q.pop();
	memset(dep,0,sizeof dep);
	dep[s]=1;
	q.push(s);
	now[s]=h[s];
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=ne[i]){
			int y=to[i];
			if(val[i] && !dep[y]){
				q.push(y);
				dep[y]=dep[x]+1;
				now[y]=h[y];
				if(y==t) return 1;
			}
		}
	}
	return 0;
}

inline int dfs(int x,int flow){
	if(x==t) return flow;
	int rest=flow,i;
	for(i=now[x];i && rest;i=ne[i]){
		int y=to[i];
		if(dep[y]==dep[x]+1 && val[i]){
			int k=dfs(y,min(rest,val[i]));
			if(!k) dep[y]=0;
			val[i]-=k;
			val[i^1]+=k;
			rest-=k;
		}
	}
	now[x]=i;
	return flow-rest;
}

inline int maxflow(){
	int maxflow=0,flow;
	while(bfs()){
		while(flow=dfs(s,INF)) maxflow+=flow;
	}
	return maxflow;
}

inline int ha(int x,int y){
	return (x-1)*k+y;
}

int rem[N];

signed main() {
	// freopen("flow.in","r",stdin);
	// freopen("flow.out","w",stdout);
	
	n=read<int>(),k=read<int>();
	if(k==1){
		_4pts::mian();
		return 0;
	}
	
	for(int i=1;i<n;++i){
		char c[15];
		for(int j=1;j<=k;++j){
			scanf("%s",c+1);
			for(int jj=1;jj<=k;++jj){
				mp[i][j][jj]=(c[jj]=='1');
			}
		}
	}
	
	int ans=0;
	for(int i=1;i<n;++i){
		memset(h,0,sizeof h);
		e=1,s=0,t=100000;
		for(int j=1;j<=k;++j){
			adde(s,ha(i,j)<<1,1);
			adde(ha(i,j)<<1,ha(i,j)<<1|1,1);
			adde(ha(i+1,j)<<1,ha(i+1,j)<<1|1,1);
		}
		for(int j=1;j<=k;++j){
			for(int jj=1;jj<=k;++jj){
				if(mp[i][j][jj]){
					adde(ha(i,j)<<1|1,ha(i+1,jj)<<1,1);
				}
			}
		}
		int cnt=0;
		rem[++cnt]=e;
		for(int now=i+1;now<n;++now){
			for(int j=1;j<=k;++j){
				adde(ha(now+1,j)<<1,ha(now+1,j)<<1|1,1);
			}
			for(int j=1;j<=k;++j){
				for(int jj=1;jj<=k;++jj){
					if(mp[now][j][jj]){
						adde(ha(now,j)<<1|1,ha(now+1,jj)<<1,1);
					}
				}
			}
			rem[++cnt]=e;
		}
		int kaka=0;
		for(int ka=cnt,now=n;ka>=1;--ka,--now){
			e=rem[ka];
			for(int j=1;j<=k;++j){
				adde(ha(now,j)<<1|1,t,1);
			}
			int tmp=maxflow();
			ans+=kaka+tmp;
			kaka+=tmp;
		}
	}
	
	write(ans, "\n");
	
    return 0;
}
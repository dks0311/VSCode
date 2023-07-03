#include<bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define ll long long
inline int read(){
	int s = 0, f = 0; char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
	while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
	return f ? ~s + 1 : s;
}
inline ll min(ll x, ll y){return x < y ? x : y;}
inline ll max(ll x, ll y){return y < x ? x : y;}
const int N = 1e7 + 5;
const ll INF = 1e18;
int T, n, k, m, a[N], b[N], id[N];
unsigned int SA, SB, SC;int p, A, B;
unsigned int rng61(){
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t = SA;
	SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC;
}
void gen(){
	scanf("%d%d%d%d%u%u%u%d%d", &n, &k, &m, &p, &SA, &SB, &SC, &A, &B);
	for(int i = 1; i <= p; i++) scanf("%d%d", &a[i], &b[i]);
	for(int i = p + 1; i <= n; i++){
		a[i] = (rng61() % A + 1) % m;
		b[i] = rng61() % B + 1;
	}
}
ll ct[2500][205], c[2500][205], dp[2500][205];
signed main(){
	T = read();
	while(T --){
		gen();
		memset(ct, 0, sizeof ct);
		memset(c, 0, sizeof c);
        memset(dp, 0, sizeof dp);
		for(int i = 1; i <= p; ++ i) a[i] %= m;
		for(int i = 1; i <= n; ++ i){
			if(i < 1 << k + 1){id[i] = i; ct[i][a[i]] += b[i];}
			else id[i] = id[i >> k + 1], ct[id[i]][a[i]] += b[i];
		}
		int tot = min(n, (1 << k + 1) - 1);
		for(int i = 1; i <= tot; ++ i)
			for(int j = 0; j < m; ++ j)
				for(int k = 0; k < m; ++ k)
					c[i][j] += (j - k + m) % m * ct[i][k];
		for(int u = tot; u; -- u){
			if((u << 1 | 1) <= tot){
				for(int i = 0; i < m; ++ i) dp[u][i] = INF;
				for(int i = 0; i < m; ++ i){
					for(int j = 0; j < m; ++ j){
						dp[u][i] = min(dp[u][i], c[u][(i - j + m) % m] + dp[u << 1][j] + dp[u << 1 | 1][j]);
					}
				}
			}
			else if((u << 1) <= tot){
				for(int i = 0; i < m; ++ i) dp[u][i] = INF;
				for(int i = 0; i < m; ++ i){
					for(int j = 0; j < m; ++ j){
						dp[u][i] = min(dp[u][i], c[u][(i - j + m) % m] + dp[u << 1][j]);
					}
				}
			}
            else if(u >> k) memcpy(dp[u], c[u], sizeof dp[u]);
		}
		printf("%lld\n", dp[1][0]);
	}
	lovely _lzy_;
}
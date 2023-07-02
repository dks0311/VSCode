#include<bits/stdc++.h>
const int N = 505;
int T, n, W, p, q;
int x[505], y[505], z[505], a[505], b[505], c[505], d[505], e[505], f[505];
struct node{int x, y, z;}dks[505];
int lzy[505];
int ans = 1e9;
void dfs(int step){
	if(step > n){
		for(int i = 1; i <= q; ++ i){
			int x = dks[i].x, y = dks[i].y;
			int z = dks[i].z;
			if(z == 0) if(lzy[x] > lzy[y]) return;
			if(z == 1) if(lzy[x] != lzy[y]) return;
			if(z == 2) if(lzy[x] >= lzy[y]) return;
		}
		int res = 0;
		for(int i = 1; i <= n; ++ i) res += lzy[i];
		for(int i = 1;i <= p; ++ i){
			res += (a[i] * abs(lzy[x[i]] - lzy[y[i]]) + b[i] * abs(lzy[y[i]] - lzy[z[i]]) + c[i] * abs(lzy[z[i]] - lzy[x[i]])\
            + d[i] * (lzy[x[i]] - lzy[y[i]]) + e[i] * (lzy[y[i]] - lzy[z[i]]) + f[i] * (lzy[z[i]] - lzy[x[i]]));
		}
		ans=std::min(ans,res);
		return;
	}
	lzy[step] = W;
	dfs(step + 1);
	lzy[step] = -W;
	dfs(step + 1);
	lzy[step] = 0;
	return;
}
int main(){
	freopen("variable.in","r",stdin);
	freopen("variable.out","w",stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d%d", &n, &W, &p, &q);
		for(int i = 1; i <= p; ++ i)
            scanf("%d%d%d%d%d%d%d%d%d", &x[i], &y[i], &z[i], &a[i], &b[i], &c[i], &d[i], &e[i], &f[i]);
		for(int i = 1; i <= q; ++ i) scanf("%d%d%d", &dks[i].x, &dks[i].y, &dks[i].z);
		ans = 1e9;
		dfs(1);
		printf("%d\n", ans);
	}
	return 0;
}
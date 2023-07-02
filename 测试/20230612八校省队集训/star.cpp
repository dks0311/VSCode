#include <bits/stdc++.h>
using namespace std;
#define double long double
template<typename T> inline T read(){
    T s = 0; int f = 0; char ch = getchar();
    while(!isdigit(ch)){if(ch == '-') f = 1; ch = getchar();}
    while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
    return f ? ~s + 1 : s;
}
const double eps = 1e-10;
int cmp(double x) {
    if(fabs(x) < eps) return 0;
    return (x < 0) ? -1 : 1;
}
struct Point {double x, y;};
bool operator < (const Point &A, const Point &B) { return cmp(B.x - A.x) == 1 || (cmp(A.x - B.x) == 0 && cmp(B.y - A.y) == 1);}
inline double get_k(Point a, Point b){if(!cmp(a.x - b.x)) return 1e18; return (b.y - a.y) / (b.x - a.x);}
inline double S(Point a, Point b, Point c){
    a.x -= c.x, a.y -= c.y, b.x -= c.x, b.y -= c.y;
    return fabs(a.x * b.y - a.y * b.x) / 2.0;
}
int convexhull_dw(Point *pp, int n, Point *Poly) {
    sort(pp + 1, pp + n + 1);
    int m = 0;
    for (int i = 1; i <= n; i++) {
        while (m > 1 && cmp(get_k(Poly[m], Poly[m - 1]) - get_k(pp[i], Poly[m])) != -1) m--;
        Poly[++ m] = pp[i];
    }
    return m;
}
int convexhull_up(Point *pp, int n, Point *Poly){
    sort(pp + 1, pp + n + 1);
    int m = 0;
    for (int i = n; i >= 1; i--) {
        while (m > 1 && cmp(get_k(Poly[m], Poly[m - 1]) - get_k(pp[i], Poly[m])) != -1) m--;
        Poly[++ m] = pp[i];
    }
    return m;
}
const int N = 3e3 + 5;
int T, n;
int cnt[5], p[5];
Point star[5][N];
Point tb_up[N], tb_dw[N];
double ans;
signed main(){
    freopen("star.in", "r", stdin);
    freopen("star.out", "w", stdout);
    T = read<int>();
    while(T --){
        memset(cnt, 0, sizeof cnt);
        n = read<int>();
        for(int i = 1; i <= n; ++ i){
            int x = read<int>(), y = read<int>(), c = read<int>();
            star[c][++ cnt[c]] = (Point){x, y};
        }
        for(int i = 0; i < 3; ++ i) p[i] = i;
        if(cnt[p[0]] > cnt[p[2]]) std::swap(p[0], p[2]);
        if(cnt[p[1]] > cnt[p[2]]) std::swap(p[1], p[2]);
        int tot_dw = convexhull_dw(star[p[2]], cnt[p[2]], tb_dw);
        int tot_up = convexhull_up(star[p[2]], cnt[p[2]], tb_up);
        ans = 0;
        for(int i = 1; i <= cnt[p[0]]; ++ i){
            for(int j = 1; j <= cnt[p[1]]; ++ j){
                Point x = star[p[0]][i], y = star[p[1]][j];
                double k = get_k(x, y);
                int l = 2, r = tot_up;
                while(l < r){
                    int mid = l + r + 1 >> 1;
                    if(cmp(get_k(tb_up[mid], tb_up[mid - 1]) - k) == 1) r = mid - 1;
                    else l = mid;
                }
                for(int k = l - 3; k <= l + 3; ++ k)
                    if(k && k <= tot_up) ans = max(ans, S(x, y, tb_up[k]));
                l = 2, r = tot_dw;
                while(l < r){
                    int mid = l + r + 1 >> 1;
                    if(cmp(get_k(tb_dw[mid], tb_dw[mid - 1]) - k) == 1) r = mid - 1;
                    else l = mid;
                }
                for(int k = l - 3; k <= l + 3; ++ k)
                    if(k && k <= tot_dw) ans = max(ans, S(x, y, tb_dw[k]));
                
                ans = max(ans, S(x, y, tb_dw[1]));
                ans = max(ans, S(x, y, tb_dw[tot_dw]));
                ans = max(ans, S(x, y, tb_up[1]));
                ans = max(ans, S(x, y, tb_up[tot_up]));
            }
        }
        printf("%.1LF\n", ans);
    }
    return 0;
}
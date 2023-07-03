/*
author: 牛肉爱吃dks
starting time: 2023.06.06 14:55:25
*/
#include <bits/stdc++.h>
#define lovely return
#define _lzy_ 0
#define ll long long
#define int long long
#define DB double
#define uF(i, x, y) for(int i = (x); i <= (y); ++ i)
#define uf(i, x, y) for(int i = (x); i < (y); ++ i)
#define dF(i, x, y) for(int i = (x); i >= (y); -- i)
#define df(i, x, y) for(int i = (x); i > (y); -- i)
#define ef(i, u) for(int i = head[(u)]; i; i = ne[i])
const int MOD = 1e9 + 7;
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
template<typename T1> inline T1 max(T1 x, T1 y){return x > y ? x : y;}
template<typename T1> inline T1 min(T1 x, T1 y){return x < y ? x : y;}
template<typename T1, typename T2> inline void updmin(T1 &x, T2 y){if(x > y) x = y;}
template<typename T1, typename T2> inline void updmax(T1 &x, T2 y){if(x < y) x = y;}
template<typename T1, typename T2> inline void updadd(T1 &x, T2 y){(x += y % MOD) %= MOD;}
template<typename T1, typename T2> inline void updmul(T1 &x, T2 y){(x *= y % MOD) %= MOD;}
template<typename T> void debug(const char *s, T *a, int l, int r){
    printf("%s:\n", s);
    uF(i, l, r) std::cout << a[i] << " ";
    puts("");
}
const int N = 1e5 + 5;
const DB EPS = 1e-8;
int n, tot, ans[40005], mx[40005];
typedef struct segment{int id; DB k, b;} seg;
seg sg[N];
struct node{
    int l, r;
    seg s;
    bool flag;
    node(){l = r = 0, s = (seg){0, 0}, flag = false;}
}tr[N << 2];
DB get_cross(seg a, seg b){return (b.b - a.b) / (a.k - b.k);}
DB get_value(seg a, DB x){return a.k * x + a.b;}
bool cmp (DB a, DB b){return b - a > EPS;}
bool eq(DB a, DB b){return fabs(a - b) < EPS;}
seg get_seg(DB x, DB y, DB xx, DB yy, int id){
    if(x == xx) return (seg){id, 0.0, max(y, yy)};
    DB k = (y - yy) * 1.0 / (x - xx);
    DB b = y - k * x;
    return (seg){id, k, b};
}
void build(int l, int r, int p){
    tr[p].l = l, tr[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(l, mid, p << 1);
    build(mid + 1, r, p << 1 | 1);
}
#define cross get_cross(s, tr[p].s)
void insert(int l, int r, int p, seg s){
    if(!tr[p].l) return;
    int mid = tr[p].l + tr[p].r >> 1;
    if((cmp(l, tr[p].l) || eq(l, tr[p].l)) && (cmp(tr[p].r, r) || eq(tr[p].r, r))){
        if(!tr[p].flag){
            tr[p].s = s;
            tr[p].flag = true;
            return;
        } //之前没有线段
        if(eq(tr[p].s.k, s.k) || cmp(tr[p].s.k, s.k)){ //插入线段斜率大于原有线段
            if(cmp(tr[p].s.b, s.b) || cmp(cross, tr[p].l)) tr[p].s = s; //插入线段完全覆盖原有线段
            else if(cmp(cross, mid)){ //交点在左边，插入线段在mid的值更大
                insert(l, r, p << 1, tr[p].s);
                tr[p].s = s;
            }
            else if(eq(cross, mid)){ //交点在中间，判断编号
                if(tr[p].s.id > s.id){
                    insert(l, r, p << 1, tr[p].s);
                    tr[p].s = s;
                }
                else insert(l, r, p << 1 | 1, s);
            }
            else if(cmp(cross, tr[p].r)) //交点在右边，原有线段在mid的值更大
                insert(l, r, p << 1 | 1, s);
        }
        else{ //插入线段斜率小于原有线段
            if(cmp(tr[p].r, cross)) tr[p].s = s; //插入线段完全覆盖原有线段
            else if(cmp(mid, cross)){ //交点在右边，插入线段在mid的值更大
                insert(l, r, p << 1 | 1, tr[p].s); 
                tr[p].s = s;
            } //交点在左边，原有线段在mid的值更大
            else if(eq(cross, mid)){
                if(tr[p].s.id > s.id){
                    insert(l, r, p << 1 | 1, tr[p].s);
                    tr[p].s = s;
                }
                else insert(l, r, p << 1, s);
            }
            else if(cmp(tr[p].l, cross))
                insert(l, r, p << 1, s);
        }
        return;
    }
    if(l <= mid) insert(l, r, p << 1, s);
    if(r > mid) insert(l, r, p << 1 | 1, s);
}
int query(DB x, int p){
    if(tr[p].l == tr[p].r) return tr[p].s.id;
    int mid = tr[p].l + tr[p].r >> 1, id = 0;
    if(x <= mid) id = query(x, p << 1);
    else id = query(x, p << 1 | 1);
    return (cmp(get_value(sg[id], x), get_value(tr[p].s, x))\
    || eq(get_value(sg[id], x), get_value(tr[p].s, x)) && tr[p].s.id < id) ? tr[p].s.id : id;
}
signed main(){
    n = read<int>();
    build(1, 40000, 1);
    int last = 0;
    while(n --){
        int opt = read<int>();
        if(opt){
            int x = (read<int>() + last - 1) % 39989 + 1;
            int y = (read<int>() + last - 1) % 1000000000 + 1;
            int xx = (read<int>() + last - 1) % 39989 + 1;
            int yy = (read<int>() + last - 1) % 1000000000 + 1;
            if(x > xx) std::swap(x, xx), std::swap(y, yy);
            sg[tot] = get_seg(x, y, xx, yy, ++ tot);
            insert(x, xx, 1, get_seg(x, y, xx, yy, tot));
        }
        else{
            int x = (read<int>() + last - 1) % 39989 + 1;
            write(last = query(x, 1), "\n");
        }
    }
    lovely _lzy_;
}
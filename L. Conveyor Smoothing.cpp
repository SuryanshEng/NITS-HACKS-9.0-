#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
int Lc[N], Rc[N], S[N], cnt;
unsigned P[N];
ll Vl[N], Z[N];
mt19937 rng(712367);
void ap(int x, ll d) { if (x) Vl[x] += d, Z[x] += d; }
void pd(int x) { if (Z[x]) ap(Lc[x], Z[x]), ap(Rc[x], Z[x]), Z[x] = 0; }
void up(int x) { S[x] = S[Lc[x]] + S[Rc[x]] + 1; }
void splitSz(int x, int k, int &a, int &b) {
    if (!x) { a = b = 0; return; }
    pd(x);
    if (S[Lc[x]] < k) { a = x; splitSz(Rc[x], k - S[Lc[x]] - 1, Rc[x], b); }
    else { b = x; splitSz(Lc[x], k, a, Lc[x]); }
    up(x);
}
void splitKey(int x, ll v, int &a, int &b) {
    if (!x) { a = b = 0; return; }
    pd(x);
    if (Vl[x] <= v) { a = x; splitKey(Rc[x], v, Rc[x], b); }
    else { b = x; splitKey(Lc[x], v, a, Lc[x]); }
    up(x);
}
int mrg(int a, int b) {
    if (!a || !b) return a | b;
    if (P[a] > P[b]) { pd(a); Rc[a] = mrg(Rc[a], b); up(a); return a; }
    pd(b); Lc[b] = mrg(a, Lc[b]); up(b); return b;
}
ll kth(int x, int k) {
    while (true) {
        pd(x);
        int s = S[Lc[x]];
        if (k <= s) x = Lc[x];
        else if (k == s + 1) return Vl[x];
        else k -= s + 1, x = Rc[x];
    }
}
int nw(ll v) {
    ++cnt; Lc[cnt] = Rc[cnt] = 0; S[cnt] = 1; P[cnt] = rng(); Vl[cnt] = v; Z[cnt] = 0;
    return cnt;
}
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; ll U, V, C, D;
        scanf("%d %lld %lld %lld %lld", &n, &U, &V, &C, &D);
        cnt = 0; int root = 0; ll mn = 0;
        for (int i = 1; i <= n; i++) {
            ll a; scanf("%lld", &a);
            if (i > 1) {
                int m = i - 1;
                int l = (int)max(0LL, m - D), r = (int)max(0LL, m - C);
                int x, y, z;
                splitSz(root, l, x, y);
                splitSz(y, 2 * m - l - r, y, z);
                ap(x, -V); ap(z, U);
                root = mrg(mrg(x, y), z);
                ll p = kth(root, m), q = kth(root, m + 1);
                if (a < p) mn += p - a;
                else if (a > q) mn += a - q;
            }
            int x, y;
            splitKey(root, a, x, y);
            root = mrg(mrg(x, mrg(nw(a), nw(a))), y);
        }
        printf("%lld\n", mn);
    }
}
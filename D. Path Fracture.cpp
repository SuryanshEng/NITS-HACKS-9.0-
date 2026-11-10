#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M = 998244353;
const int N = 200005, LG = 18;
int up[LG][N], tin[N], sz[N], dep[N], T;
ll G[N], IG[N], inv[N], mn[N];
vector<int> g[N];
ll pw(ll b, ll e) { ll r = 1; b %= M; for (; e; e >>= 1, b = b * b % M) if (e & 1) r = r * b % M; return r; }
bool anc(int a, int b) { return tin[a] <= tin[b] && tin[b] < tin[a] + sz[a]; }
int lca(int a, int b) {
    if (anc(a, b)) return a;
    if (anc(b, a)) return b;
    for (int j = LG - 1; j >= 0; j--) if (!anc(up[j][a], b)) a = up[j][a];
    return up[0][a];
}
int jump(int v, int d) { for (int j = 0; j < LG; j++) if (d >> j & 1) v = up[j][v]; return v; }
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) { int x, y; cin >> x >> y; g[x].push_back(y); g[y].push_back(x); }
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (M - M / i) * inv[M % i] % M;
    vector<int> ord, st = {1};
    up[0][1] = 1; dep[1] = 0;
    vector<int> par(n + 1, 0);
    while (!st.empty()) {
        int u = st.back(); st.pop_back();
        tin[u] = T++; ord.push_back(u);
        for (int v : g[u]) if (v != up[0][u]) { up[0][v] = u; dep[v] = dep[u] + 1; st.push_back(v); }
    }
    for (int i = n - 1; i >= 0; i--) { int u = ord[i]; sz[u] += 1; if (u != 1) sz[up[0][u]] += sz[u]; }
    G[1] = IG[1] = 1;
    for (int u : ord) if (u != 1) {
        int p = up[0][u];
        ll f = sz[p] - sz[u];
        G[u] = G[p] * f % M; IG[u] = IG[p] * inv[f] % M;
    }
    for (int j = 1; j < LG; j++) for (int v = 1; v <= n; v++) up[j][v] = up[j - 1][up[j - 1][v]];
    int q; cin >> q;
    while (q--) {
        int k; cin >> k;
        vector<int> v(k);
        for (int &x : v) cin >> x;
        if (k == 1) { cout << "1\n"; continue; }
        sort(v.begin(), v.end(), [](int a, int b) { return tin[a] < tin[b]; });
        for (int i = 0; i + 1 < k; i++) v.push_back(lca(v[i], v[i + 1]));
        sort(v.begin(), v.end(), [](int a, int b) { return tin[a] < tin[b]; });
        v.erase(unique(v.begin(), v.end()), v.end());
        int m = v.size();
        for (int x : v) mn[x] = 0;
        ll L = m, prod = 1;
        vector<int> s;
        vector<int> pr(m, 0);
        for (int i = 0; i < m; i++) {
            int x = v[i];
            while (!s.empty() && !anc(s.back(), x)) s.pop_back();
            if (!s.empty()) {
                int p = s.back(), d = dep[x] - dep[p] - 1;
                int ca = jump(x, d);
                prod = prod * G[x] % M * IG[ca] % M;
                L += d;
                mn[p] += sz[ca];
                pr[i] = 1;
            }
            s.push_back(x);
        }
        for (int i = 0; i < m; i++) {
            int x = v[i];
            ll sv = n - mn[x] - (pr[i] ? n - sz[x] : 0);
            prod = prod * (sv % M) % M;
        }
        cout << prod * pw(n, L - 2) % M << "\n";
    }
}
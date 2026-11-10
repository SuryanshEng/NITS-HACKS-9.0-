#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005, LG = 17;
const ll INF = 4e18;
int up[LG][N], dep[N];
ll mn[LG][N];
int a, b;
pair<int, ll> qry(int u, int v) {
    ll m = INF;
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int j = 0; j < LG; j++)
        if (d >> j & 1) m = min(m, mn[j][u]), u = up[j][u];
    if (u == v) return {u, m};
    for (int j = LG - 1; j >= 0; j--)
        if (up[j][u] != up[j][v]) {
            m = min({m, mn[j][u], mn[j][v]});
            u = up[j][u]; v = up[j][v];
        }
    m = min({m, mn[0][u], mn[0][v]});
    return {up[0][u], m};
}
int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[qry(u, v).first]; }

bool add(int x) {
    int da = dist(a, x), db = dist(b, x), dab = dist(a, b);
    if (da + db == dab) return true;
    if (dab + db == da) { b = x; return true; }
    if (dab + da == db) { a = x; return true; }
    return false;
}
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        vector<array<int, 3>> E(n - 1);
        vector<vector<pair<int, int>>> g(n + 1);
        for (auto &e : E) {
            scanf("%d %d %d", &e[1], &e[2], &e[0]);
            g[e[1]].push_back({e[2], e[0]});
            g[e[2]].push_back({e[1], e[0]});
        }
        sort(E.rbegin(), E.rend());
        vector<int> q = {1};
        up[0][1] = 1; mn[0][1] = INF; dep[1] = 0;
        vector<char> vis(n + 1, 0); vis[1] = 1;
        for (size_t i = 0; i < q.size(); i++) {
            int u = q[i];
            for (auto [v, w] : g[u]) if (!vis[v]) {
                vis[v] = 1; up[0][v] = u; mn[0][v] = w; dep[v] = dep[u] + 1; q.push_back(v);
            }
        }
        for (int j = 1; j < LG; j++)
            for (int v = 1; v <= n; v++) {
                int m = up[j - 1][v];
                up[j][v] = up[j - 1][m];
                mn[j][v] = min(mn[j - 1][v], mn[j - 1][m]);
            }
        ll ans = -INF;
        ll best2 = 0;
        for (int v = 1; v <= n; v++) {
            ll f = 0, s = 0;
            for (auto [u, w] : g[v]) {
                if (w > f) s = f, f = w;
                else if (w > s) s = w;
            }
            if (g[v].size() >= 2) best2 = max(best2, s);
        }
        ans = best2 - E[0][0];
        {
            ll am = 0;
            for (int x : {E[0][1], E[0][2]})
                for (auto [u, w] : g[x]) if (w != E[0][0]) am = max(am, (ll)w);
            ans = max(ans, am - E[1][0]);
        }
        a = b = E[0][1];
        add(E[0][1]); add(E[0][2]);
        for (int i = 1; i <= n - 2; i++) {
            if (!add(E[i][1]) || !add(E[i][2])) break;
            int k = i + 1;
            ll nw = (k <= n - 2) ? E[k][0] : 0;
            ans = max(ans, qry(a, b).second - nw);
        }
        printf("%lld\n", ans);
    }
}
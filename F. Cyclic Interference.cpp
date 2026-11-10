#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M = 998244353;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<ll> cnt(n, 0);
        for (int i = 0; i < m; i++) { int v; cin >> v; cnt[v]++; }
        ll S = 0, c0 = 0;
        for (int i = 0; i < n; i++) {
            ll a; cin >> a; a %= M;
            S = (S + a) % M;
            c0 = (c0 + a * a) % M;
        }
        ll E = 0;
        for (ll c : cnt) E = (E + c * c) % M;
        ll tot = ((ll)m * m) % M;
        ll ans = E * (n - 1) % M * c0 % M;
        ans = (ans + (tot - E + M) % M * ((S * S - c0 % M + M) % M)) % M;
        cout << ans << "\n";
    }
}
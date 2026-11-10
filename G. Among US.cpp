#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M = 1000000007;
ll pw(ll b, ll e) { ll r = 1; b %= M; if (b < 0) b += M; for (; e; e >>= 1, b = b * b % M) if (e & 1) r = r * b % M; return r; }
int main() {
    int k; cin >> k;
    int n = k + 3;
    vector<ll> y(n), f(k + 5, 1), C(k + 2);
    for (int i = 1; i < k + 5; i++) f[i] = f[i - 1] * i % M;
    for (int i = 0; i <= k + 1; i++) C[i] = f[k + 1] * pw(f[i] * f[k + 1 - i] % M, M - 2) % M;
    for (int i = 0; i < n; i++) {
        cout << "? " << i << endl;
        cin >> y[i]; y[i] %= M; if (y[i] < 0) y[i] += M;
    }
    auto syn = [&](vector<ll> &v, int j) {
        ll s = 0;
        for (int i = 0; i <= k + 1; i++) {
            ll t = C[i] * v[j + i] % M;
            s = (s + (i & 1 ? M - t : t)) % M;
        }
        return s;
    };
    if (syn(y, 0) || syn(y, 1)) {
        for (int p = 0; p < n; p++) {
            vector<ll> z = y;
            ll s, c;
            if (p <= k + 1) { s = syn(y, 0); c = C[p] * (p & 1 ? M - 1 : 1) % M; }
            else { s = syn(y, 1); c = C[k + 1] * ((k + 1) & 1 ? M - 1 : 1) % M; }
            ll e = s * pw(c, M - 2) % M;
            z[p] = ((z[p] - e) % M + M) % M;
            if (!syn(z, 0) && !syn(z, 1)) { y = z; break; }
        }
    }
    vector<ll> m(k + 2, 0);
    m[0] = 1;
    int deg = 0;
    for (int i = 0; i <= k; i++) {
        vector<ll> nm(k + 2, 0);
        for (int d = 0; d <= deg; d++) {
            nm[d + 1] = (nm[d + 1] + m[d]) % M;
            nm[d] = (nm[d] + (M - i) % M * m[d]) % M;
        }
        m = nm; deg++;
    }
    vector<ll> res(k + 1, 0), q(k + 1);
    for (int i = 0; i <= k; i++) {
        q[k] = m[k + 1];
        for (int d = k; d >= 1; d--) q[d - 1] = (m[d] + (ll)i * q[d]) % M;
        ll den = f[i] * f[k - i] % M;
        if ((k - i) & 1) den = (M - den) % M;
        ll sc = y[i] * pw(den, M - 2) % M;
        for (int d = 0; d <= k; d++) res[d] = (res[d] + sc * q[d]) % M;
    }
    cout << "!";
    for (ll v : res) cout << " " << v;
    cout << endl;
}
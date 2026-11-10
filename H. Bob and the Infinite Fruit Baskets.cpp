#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 L;
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; ll k; scanf("%d %lld", &n, &k);
        vector<ll> C(n + 1, 0), S(n + 1, 0); 
        for (int i = 0; i < n; i++) scanf("%lld", &C[i]);
        for (int i = 0; i < n; i++) scanf("%lld", &S[i]);
        n++;
        int cur = 0;
        for (int i = 1; i < n; i++)
            if (C[i] > C[cur] || (C[i] == C[cur] && S[i] < S[cur])) cur = i;
        ll d = 0; L ans = 0;
        while (d < k) {
            ll nd = LLONG_MAX; int nx = -1; ll bv = 0;
            for (int j = 0; j < n; j++) {
                if (S[j] >= S[cur]) continue;
                ll x = (C[cur] - C[j]) / (S[cur] - S[j]) + 1;
                if (x >= k) continue;
                ll v = (x < nd || nx < 0 || x <= nd) ? C[j] - S[j] * x : 0;
                if (x < nd || (x == nd && (v > bv || (v == bv && S[j] < S[nx])))) {
                    nd = x; nx = j; bv = v;
                }
            }
            ll e = (nx < 0) ? k : nd; // segment [d, e)
            L cnt = e - d, sd = (L)(d + e - 1) * cnt / 2;
            ans += cnt * C[cur] - sd * S[cur];
            d = e;
            if (nx < 0) break;
            cur = nx;
        }
        printf("%lld\n", (ll)ans);
    }
}
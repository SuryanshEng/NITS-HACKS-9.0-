#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
const int MX = 2000005;
ll f[MX], inv[MX];
ll pw(ll b, ll e){
    ll r = 1; b %= MOD;
    while(e){ if(e & 1) r = r * b % MOD; b = b * b % MOD; e >>= 1; }
    return r;
}
ll C(int n, int r){
    if(r < 0 || r > n) return 0;
    return f[n] * inv[r] % MOD * inv[n - r] % MOD;
}
int main(){
    f[0] = 1;
    for(int i = 1; i < MX; i++) f[i] = f[i-1] * i % MOD;
    inv[MX-1] = pw(f[MX-1], MOD - 2);
    for(int i = MX - 1; i > 0; i--) inv[i-1] = inv[i] * i % MOD;
    int t; scanf("%d", &t);
    while(t--){
        int n, s; scanf("%d %d", &n, &s);
        int h = s / 2;
        ll ans = C(s + n - 1, n - 1);
        ans = (ans - (ll)n % MOD * C(s - h - 1 + n - 1, n - 1) % MOD + MOD) % MOD;
        printf("%lld\n", ans);
    }
}
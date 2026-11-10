#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        ll h, k; cin >> h >> k;
        ll lo = 0, hi = 2000000000LL;
        while(lo < hi){
            ll mid = (lo + hi + 1) / 2;
            __int128 v = (__int128)(mid + 1) * (mid + 2) * k;
            if(v <= (__int128)2 * h) lo = mid; else hi = mid - 1;
        }
        cout << lo << "\n";
    }
}
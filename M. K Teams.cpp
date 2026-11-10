#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        long long n, k; cin >> n >> k;
        if(n < 2 * k || n > 3 * k){
            cout << -1 << "\n";
            continue;
        }
        long long extra = n - 2 * k;
        for(long long i = 0; i < k; i++){
            cout << (i < extra ? 3 : 2) << (i + 1 < k ? " " : "\n");
        }
    }
}
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> a(n);
        bool odd = false, even = false;
        for(auto &x : a){
            cin >> x;
            if(x & 1) odd = true; else even = true;
        }
        if(odd && even || is_sorted(a.begin(), a.end())) cout << "YES\n";
        else cout << "NO\n";
    }
}
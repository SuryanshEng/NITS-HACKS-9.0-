#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<pair<int,ll>> Path;
Path build(ll x, ll y){
    Path p;
    while(!(x == 1 && y == 1)){
        if(x > y){
            ll c = (y == 1) ? x - 1 : x / y;
            p.push_back({0, c});
            x -= c * y;
        } else {
            ll c = (x == 1) ? y - 1 : y / x;
            p.push_back({1, c});
            y -= c * x;
        }
    }
    reverse(p.begin(), p.end());
    return p;
}
int main(){
    int t; scanf("%d", &t);
    while(t--){
        ll x1, y1, x2, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        Path a = build(x1, y1), b = build(x2, y2);
        vector<pair<int,ll>> common;
        size_t i = 0;
        while(i < a.size() && i < b.size()){
            if(a[i].first != b[i].first) break;
            ll c = min(a[i].second, b[i].second);
            common.push_back({a[i].first, c});
            if(a[i].second != b[i].second) break;
            i++;
        }
        ll x = 1, y = 1;
        for(auto &[d, c] : common){
            if(d == 0) x += c * y;
            else y += c * x;
        }
        printf("%lld %lld\n", x, y);
    }
}
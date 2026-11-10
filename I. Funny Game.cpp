#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        int c[30] = {};
        for (int &x : a) {
            cin >> x;
            for (int b = 0; b < 30; b++) c[b] += x >> b & 1;
        }
        int B = -1;
        for (int b = 29; b >= 0; b--) if (c[b] & 1) { B = b; break; }
        if (B < 0) { cout << "DRAW\n"; continue; }
        if (c[B] % 4 == 1) { cout << "ALICE\n"; continue; }
        int x = 0;
        for (int v : a) x ^= __builtin_popcount(v & ~(1 << B));
        cout << (x ? "ALICE\n" : "BOB\n");
    }
}
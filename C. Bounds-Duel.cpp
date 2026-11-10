#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        int k, D; ll L, R;
        cin >> k >> L >> R >> D;
        vector<int> Ld(k), Rd(k);
        for(int i = k - 1; i >= 0; i--){
            Ld[i] = L % 10; L /= 10;
            Rd[i] = R % 10; R /= 10;
        }
        vector<char> nxt(D * 4), cur(D * 4);
        for(int m = 0; m < D; m++)
            for(int f = 0; f < 4; f++) nxt[m * 4 + f] = (m != 0);
        for(int i = k - 1; i >= 0; i--){
            for(int m = 0; m < D; m++){
                for(int tl = 0; tl < 2; tl++)
                    for(int tr = 0; tr < 2; tr++){
                        int lo = tl ? Ld[i] : 0;
                        int hi = tr ? Rd[i] : 9;
                        bool win = false;
                        for(int d = lo; d <= hi && !win; d++){
                            int nm = (int)(((ll)m * 10 + d) % D);
                            int ntl = tl && d == Ld[i];
                            int ntr = tr && d == Rd[i];
                            if(!nxt[nm * 4 + ntl * 2 + ntr]) win = true;
                        }
                        cur[m * 4 + tl * 2 + tr] = win;
                    }
            }
            swap(cur, nxt);
        }
        cout << (nxt[0 * 4 + 3] ? "Alice" : "Bob") << "\n";
    }
}
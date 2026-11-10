#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2000001;
const ll M=1e9+7;
int sp[N],rs[N],ex[N];
ll G[N];
int main(){
    cin.tie(0)->sync_with_stdio(0);
    vector<int> pr;
    G[1]=1;
    for(int i=2;i<N;i++){
        if(!sp[i])sp[i]=i,pr.push_back(i);
        for(int p:pr){
            if(p>sp[i]||(ll)i*p>=N)break;
            sp[i*p]=p;
        }
    }
    vector<ll> g(N);
    g[1]=1;
    for(int i=2;i<N;i++){
        int p=sp[i],j=i/p;
        if(j%p==0)rs[i]=rs[j],ex[i]=ex[j]+1;
        else rs[i]=j,ex[i]=1;
        ll v=ex[i]==1?p-1:ex[i]==2?M-p:0;
        g[i]=g[rs[i]]*v%M;
    }
    rs[1]=1;
    for(int i=1;i<N;i++)G[i]=(G[i-1]+g[i])%M;
    int t;cin>>t;
    while(t--){
        int n,m;cin>>n>>m;
        ll r=0;
        for(int l=1,h;l<=min(n,m);l=h+1){
            int a=n/l,b=m/l;
            h=min(n/a,m/b);
            r=(r+(ll)a*b%M*((G[h]-G[l-1]+M)%M))%M;
        }
        cout<<r<<'\n';
    }
}
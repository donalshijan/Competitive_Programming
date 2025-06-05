#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio ios::sync_with_stdio(false); cin.tie(0);

int main() {
    fastio;
    ll t;
    cin>>t;
    while(t--){
        ll n,m,p,q;
        cin>>n>>m>>p>>q;
        cout<<(( n%p==0 && (n/p)*q!=m)?"NO":"YES");cout<<endl;

    }

    return 0;
}

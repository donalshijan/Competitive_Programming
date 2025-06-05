#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio ios::sync_with_stdio(false); cin.tie(0);

int main() {
    fastio;

    ll t;
    cin>>t;
    while(t--){
        ll n;
        cin>>n;
        vector<ll> a(n);
        ll firstElement;
        ll count=0;
        for(ll i =0; i<n ;i++) {
            cin>>a[i]; 
            if(a[i]<0) a[i]*=-1;
            if(i==0) firstElement = a[i];
            else count += (a[i]<firstElement) ? 1 : 0; 
        }
        if(count<=n/2) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
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
        for(auto& x : a) cin>>x;
        int count = 0;
        bool lying = false;
        for(int i = 0; i<a.size() ;i++)  if(i!=0 && a[i]==0 && a[i-1]==0) { lying=true; break;} else count+=a[i]; 
        lying ?  cout<<"YES"<<endl : ( count<a.size() ? cout<<"NO"<<endl : cout<<"YES"<<endl );
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio ios::sync_with_stdio(false); cin.tie(0);

void BruteForce(vector<int>& cyclists, int n,long long& minCost, long long& curCost){
    if(n==0) { minCost = min(minCost,curCost); return; }
    curCost += cyclists[n-1];
    BruteForce(cyclists,n-1,minCost,curCost);
    curCost -= cyclists[n-1];
    for(int i =n-2;i>=0;i--){
        curCost +=  (n-1)-i;
        swap(cyclists[n-1],cyclists[i]);
        curCost += cyclists[n-1];
        BruteForce(cyclists,n-1,minCost,curCost);
        curCost -= cyclists[n-1];
        swap(cyclists[n-1],cyclists[i]);
        curCost -= (n-1)-i;
    }
    for(int i =n;i<cyclists.size();i++){
        curCost += i-(n-1);
        swap(cyclists[n-1],cyclists[i]);
        curCost += cyclists[n-1];
        BruteForce(cyclists,n-1,minCost,curCost);
        curCost -= cyclists[n-1];
        swap(cyclists[n-1],cyclists[i]);
        curCost -= i-(n-1);
    }
}

int main() {
    fastio;

    ll number_of_test_cases;
    cin>>number_of_test_cases;
    while(number_of_test_cases--){
        ll n ;
        cin>>n;
        vector<ll> cyclists(n);
        for(auto& c : cyclists) cin>>c;
        vector<ll> dp(n+1,LLONG_MAX);
        dp[n]=0;
        for(ll i = n-1 ; i>=0;i--){
            // i is the position to overtake next
            ll best_cyclist_to_overtake_with = i;
            for(ll j = best_cyclist_to_overtake_with; j<n; j++) if(cyclists[best_cyclist_to_overtake_with]>cyclists[j]) best_cyclist_to_overtake_with = j;
            for(ll j = best_cyclist_to_overtake_with; j<n; j++) dp[i]=min(dp[i],dp[j+1]+2LL*(j-best_cyclist_to_overtake_with) + (best_cyclist_to_overtake_with - i) + cyclists[best_cyclist_to_overtake_with]*(j-i+1LL));
        }
        cout<<dp[0]<<endl;
        // long long minCost=LONG_MAX; long long curCost=0;BruteForce(cyclists,n,minCost,curCost);cout<<minCost<<endl;
    }
    return 0;
}


/*

1 99 5 99 , 3 -> 5
99 99 5 , 1 3 -> 4
99 99 , 1 5 3 -> 2
99 , 1 99 5 3 -> 2
, 1 99 99 5 3 -> 2
              => 15

5 99 3 99 , 1 -> 5
5 99 3 , 1 99 -> 2
5 99 , 1 3 99 -> 2
5 , 1 99 3 99 -> 2
, 1 5 99 3 99 -> 2
              => 13

a  = [01 99 99 99 99 99 03 99 99 99 99 05 99 99 99 07 99 99 09]
dp = [55 MM MM MM MM MM MM MM MM MM MM MM MM MM MM 34 29 19 09 0]
*/
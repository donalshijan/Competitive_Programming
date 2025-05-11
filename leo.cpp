#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio ios::sync_with_stdio(false); cin.tie(0);

long long minCostToGetFirst(vector<int>& cyclists, int cur_position,int cyclist_with_smallest_agility_behind_pos){
    long long cost=0;
    int rider_ahead_pos=cur_position-1;
    while(rider_ahead_pos>=0)
    {
        if(cyclist_with_smallest_agility_behind_pos==-1 || cyclists[cyclist_with_smallest_agility_behind_pos]>cyclists[rider_ahead_pos]){
            // look for smaller agility ahead to swap with where it is only worth doing the
            int i;
            bool foundSwapCandidate=false;
            int swapPos;
            for(i = 0;i<rider_ahead_pos;i++) if(cyclists[i]<cyclists[rider_ahead_pos] && (rider_ahead_pos - i + cyclists[i])<cyclists[rider_ahead_pos] ) {
                if(!foundSwapCandidate) foundSwapCandidate=true,swapPos=i;
                else if((rider_ahead_pos - i + cyclists[i]) < (rider_ahead_pos - swapPos + cyclists[swapPos])) swapPos = i;
            }
            if(foundSwapCandidate) { cost+=rider_ahead_pos-swapPos; cost+=cyclists[swapPos]; swap(cyclists[swapPos],cyclists[rider_ahead_pos]);}
            else cost+=cyclists[rider_ahead_pos];

            cur_position--;
            cyclist_with_smallest_agility_behind_pos=rider_ahead_pos;
            rider_ahead_pos--;
        }
        else{
            // see if swaping with rider behind will help
            if(1+cyclists[cyclist_with_smallest_agility_behind_pos]<cyclists[rider_ahead_pos]){
                cost+=1+cyclists[cyclist_with_smallest_agility_behind_pos];
                swap(cyclists[cyclist_with_smallest_agility_behind_pos],cyclists[rider_ahead_pos]);
                cyclist_with_smallest_agility_behind_pos=rider_ahead_pos;
            }
            else{
                cost+=cyclists[rider_ahead_pos];
            }
            rider_ahead_pos--;
            cur_position--;
        }
    }
    return cost;
}
void BruteForce(vector<int>& cyclists, int n,long long& minCost, long long& curCost){
    if(n==0) { minCost = min(minCost,curCost); return; }
    curCost+=cyclists[n-1];
    BruteForce(cyclists,n-1,minCost,curCost);
    curCost-=cyclists[n-1];
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

    int number_of_test_cases;
    cin>>number_of_test_cases;
    while(number_of_test_cases--){
        int n ;
        cin>>n;
        vector<int> cyclists(n);
        for(auto& c : cyclists) cin>>c;
        {
        // long long minCost=LONG_MAX; long long curCost=0;BruteForce(cyclists,n,minCost,curCost);cout<<minCost<<endl;
        cout<<minCostToGetFirst(cyclists,n,-1)<<endl;
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio ios::sync_with_stdio(false); cin.tie(0);

int findMex(vector<int>& towers){
    int mex=0;
    for(int i = 0 ;i<towers.size();i++){
        if(towers[i]>mex) break;
        if (towers[i]==mex) mex++;
    }
    return mex;
}
void simulateFallingTowers(vector<int>& towers,vector<int>& permutation){
    for(int i =0;i<permutation.size();i++){
        int cur_tower_ind = permutation[i];
        int cur_tower_height=towers[cur_tower_ind];
        for(int j = 1;j<=cur_tower_height && (cur_tower_ind+j)<towers.size();j++) towers[cur_tower_ind+j]++;
        towers[cur_tower_ind]=0;
    }
}
int solve(vector<int>& towers,int n ){
    int max_mex=0;
    vector<int> permutation(n);
    for(int i =0;i<n;i++) permutation[i]=i;
    do{ 
        vector<int> copy = towers;
        simulateFallingTowers(copy,permutation);
        if(is_sorted(copy.begin(),copy.end())){
            max_mex = max(max_mex, findMex(copy));
        }
    }while(next_permutation(permutation.begin(),permutation.end()));
    return max_mex;
}
bool checkMexAchievable(vector<int>& towers,int n , int mex){
    vector<int> num_of_broken_towers_whose_propogation_effect_end_here(n,0);
    int max_possible_num_of_prev_broken_towers_with_block_propogation_still_in_effect = 0;
    for(int i =0;i<n;i++){
        max_possible_num_of_prev_broken_towers_with_block_propogation_still_in_effect-=num_of_broken_towers_whose_propogation_effect_end_here[i];
        int min_num_for_towers_in_block_propogation_effect_needed =  max(0,i-(n-mex)); 
        // because one tower's propogation only adds 1 to a position,
        // if you want a tower of height k blocks at position i,
        // you need k towers before it broken and propogating it's blocks to have this position get filled by k blocks , one from each.
        if(max_possible_num_of_prev_broken_towers_with_block_propogation_still_in_effect<min_num_for_towers_in_block_propogation_effect_needed) return false;
        // if not we can definitely build the height of blocks required here,
        // and we can only build that required height here, by breaking this tower first and using the propogated blocks from breaking the towers previous to it later.
        // That is because the problem makes it mandatory to break every tower, so the answer for this must come from previous tower break propogations
        // happening later, after it has been broken, as it's height gets reduced to zero when broken.
        // If the height required here is k and num of towers whose propogation effect is in play is t,
        // we should make sure those t-k towers will be broken before we break this, 
        // because that way, those t-k blocks get added to this tower's height, which is towers[i]
        // and then we break this tower so that we get to maximize the range upto where we can propogate blocks when breaking this tower,
        // and are still left with k towers before it to break later and build answer for this pos.
        // by maximimizing this range we ensure,
        // that we are more likely to have more than minimum numbers of towers in block propogation effect needed for later positions. 
        // this increment adds this tower to the possible prev ones that can be broken and be in propogation effect, to be considered in next iteration for next position.
        max_possible_num_of_prev_broken_towers_with_block_propogation_still_in_effect++;
        int block_propogation_range_end_index_of_breaking_this_tower = i + max_possible_num_of_prev_broken_towers_with_block_propogation_still_in_effect-min_num_for_towers_in_block_propogation_effect_needed+towers[i];
        if(block_propogation_range_end_index_of_breaking_this_tower<n)
        num_of_broken_towers_whose_propogation_effect_end_here[block_propogation_range_end_index_of_breaking_this_tower]++;

    }
    return true;
}
int greedySolution(vector<int>& towers,int n){
    int l = 1;
    int r = n+1;
    while(r-l>1){
        int mex = l+ (r-l)/2;
        if(checkMexAchievable(towers,n,mex)){
            l=mex;
        }
        else{
            r=mex;
        }
    }
    return l;
}
int main() {
    fastio;

    // Your code here
    int number_of_test_cases;
    cin>>number_of_test_cases;
    while(number_of_test_cases--){
        int n;
        cin>>n;
        vector<int> towers(n);
        for(int& x : towers) cin>>x;
        cout<<greedySolution(towers,n)<<endl;
    }

    return 0;
}
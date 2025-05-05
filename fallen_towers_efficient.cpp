#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Check if we can achieve a MEX of 'target'
bool canAchieveMex(const vector<ll>& tower_heights, ll target) {
    ll n = tower_heights.size();
    
    // Difference array to efficiently track block additions
    vector<ll> diff_array(n, 0);
    
    // Total blocks that have fallen onto the current tower
    ll accumulated_blocks = 0;
    
    for (ll position = 0; position < n; position++) {
        // Apply the difference array - update our accumulated blocks
        accumulated_blocks -= diff_array[position];
        
        // For MEX = target, we need values [0,1,2,...,target-1]
        // If position is one of the last (target) positions, it needs (position-(n-target)) blocks
        // to create the sequence [0,1,2,...,target-1] at the end
        ll min_blocks_needed = max(0LL, position - (n - target));
        
        // If we don't have enough blocks, we can't achieve this MEX
        if (accumulated_blocks < min_blocks_needed) {
            return false;
        }
        
        // We'll use (min_blocks_needed) blocks to achieve our target value
        // The rest (accumulated_blocks - min_blocks_needed) can be used to collapse towers
        // Plus one more block from collapsing the current tower
        ll extra_blocks_available = accumulated_blocks - min_blocks_needed + 1;
        
        // When we collapse this tower, its height (tower_heights[position]) blocks will fall onto subsequent towers
        // plus any extra blocks we've allocated for collapsing
        ll blocks_to_propagate = tower_heights[position] + extra_blocks_available;
        
        // Mark the end of the range where these blocks will no longer affect future towers
        ll end_effect = position + blocks_to_propagate;
        if (end_effect < n) {
            diff_array[end_effect]++;
        }
        
        // We've used one block to collapse this tower
        accumulated_blocks++;
    }
    
    return true;
}

ll solveMaxMex(const vector<ll>& tower_heights) {
    ll n = tower_heights.size();
    
    // Binary search for the maximum achievable MEX
    ll left = 1;          // Minimum possible MEX is at least 1
    ll right = n + 1;     // Maximum possible MEX is at most n+1
    
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        
        if (canAchieveMex(tower_heights, mid)) {
            left = mid;    // We can achieve this MEX, try higher
        } else {
            right = mid;   // We can't achieve this MEX, try lower
        }
    }
    
    return left;  // This is the maximum achievable MEX
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int test_cases;
    cin >> test_cases;
    
    while (test_cases--) {
        ll n;
        cin >> n;
        
        vector<ll> tower_heights(n);
        for (ll& height : tower_heights) {
            cin >> height;
        }
        
        cout << solveMaxMex(tower_heights) << endl;
    }
    
    return 0;
}
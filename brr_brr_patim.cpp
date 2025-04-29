#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<vector<int>> grid(n, vector<int>(n));
        unordered_set<int> remaining;
        vector<int> result;

        // Fill the grid
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> grid[i][j];

        // Step 1: fill the set with all elements from 1 to 2n
        for (int i = 1; i <= 2 * n; ++i)
            remaining.insert(i);

        // Step 2: Traverse last column from bottom to top
        for (int i = n - 1; i >= 0; --i) {
            int val = grid[i][n - 1];
            result.push_back(val);
            remaining.erase(val);
        }

        // Step 3: Traverse top row from second last to first column
        for (int j = n - 2; j >= 0; --j) {
            int val = grid[0][j];
            result.push_back(val);
            remaining.erase(val);
        }

        // Step 4: Add remaining value
        if (!remaining.empty())
            result.push_back(*remaining.begin());

        // Output the result
        for (int i=result.size()-1;i>=0; i--)
            cout << result[i] << " ";
        cout << "\n";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
using ll = long long;

// Stores all zebra-like numbers up to 10^18
vector<ll> zebraNumbers;

// Function to generate zebra-like numbers (odd numbers with alternating bits)
void generateZebraNumbers() {
    for (ll start = 1; start < (1LL << 60); start = (start << 2) | 1) {
        if (start > 1e18) break;
        zebraNumbers.push_back(start);
    }
}

// Memoized function to compute the minimum zebra value for x
map<ll, int> memo;
int minZebraValue(ll x) {
    if (x == 0) return 0;
    if (memo.count(x)) return memo[x];

    int minValue = 1e9;
    for (ll z : zebraNumbers) {
        if (z > x) break;
        minValue = min(minValue, 1 + minZebraValue(x - z));
    }
    return memo[x] = minValue;
}

// Function to count numbers in range [l, r] with zebra value k
int countZebraValueInRange(ll l, ll r, int k) {
    int count = 0;
    for (ll x = l; x <= r; x++) {
        if (minZebraValue(x) == k) {
            count++;
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute all zebra-like numbers
    generateZebraNumbers();

    int t;
    cin >> t;
    while (t--) {
        ll l, r;
        int k;
        cin >> l >> r >> k;
        cout << countZebraValueInRange(l, r, k) << "\n";
    }

    return 0;
}

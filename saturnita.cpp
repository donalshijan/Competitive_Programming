#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define fastio ios::sync_with_stdio(false); cin.tie(0);

int divide_k(int k, int a, unordered_map<ll, int>& cache) {
    ll key = (1LL * k << 17) | a; // combine k and a uniquely (bit-shift)
    if (cache.count(key)) return cache[key];

    int original_k = k;
    while (k % a == 0) k /= a;
    return cache[key] = k;
}

int main() {
    fastio;

    int t;
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n + 1); // 1-based indexing
        for (int i = 1; i <= n; ++i) cin >> a[i];

        unordered_map<ll, int> cache;

        while (q--) {
            int k, l, r;
            cin >> k >> l >> r;

            int ans = 0;
            for (int i = l; i <= r; ++i) {
                k = divide_k(k, a[i], cache);
                ans += k;
                if (k == 1) {
                    ans += (r - i) * 1;
                    break;
                }
            }

            cout << ans << '\n';
        }

        cache.clear(); // Clear cache to prevent MLE
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m, l, r;
        cin >> n >> m >> l >> r;

        int distLeft = 0 - l;
        int distRight = r - 0;

        int lprime, rprime;

        if (distLeft >= distRight) {
            // Left side can go further
            if (m <= distLeft) {
                lprime = 0 - m;
                rprime = 0;
            } else {
                lprime = l;
                rprime = 0 + (m - distLeft);
            }
        } else {
            // Right side can go further
            if (m <= distRight) {
                lprime = 0;
                rprime = 0 + m;
            } else {
                rprime = r;
                lprime = 0 - (m - distRight);
            }
        }

        cout << lprime << " " << rprime << "\n";
    }
    return 0;
}

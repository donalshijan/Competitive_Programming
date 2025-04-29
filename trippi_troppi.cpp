#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(NULL);

    int t;
    cin >> t;
    cin.ignore(); // Ignore newline after the number

    while (t--) {
        string line, result;
        getline(cin, line);

        int count = 0;
        result += line[0]; // First character
        count++;

        for (int i = 1; i < line.size() && count < 3; ++i) {
            if (line[i] == ' ' && i + 1 < line.size()) {
                result += line[i + 1];
                count++;
            }
        }

        cout << result << '\n';
    }

    return 0;
}
